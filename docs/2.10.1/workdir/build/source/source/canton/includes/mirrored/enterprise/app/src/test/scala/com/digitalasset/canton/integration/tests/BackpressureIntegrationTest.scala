// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests

import cats.syntax.functor.*
import com.digitalasset.canton.BigDecimalImplicits.*
import com.digitalasset.canton.concurrent.Threading
import com.digitalasset.canton.console.{
  CommandFailure,
  DomainReference,
  LocalParticipantReference,
  ParticipantReference,
}
import com.digitalasset.canton.domain.sequencing.sequencer.{
  HasProgrammableSequencer,
  ProgrammableSequencer,
  SendDecision,
}
import com.digitalasset.canton.examples.java.iou.{Amount, Iou}
import com.digitalasset.canton.integration.{ConfigTransforms, EnterpriseEnvironmentDefinition}
import com.digitalasset.canton.ledger.error.LedgerApiErrors.ParticipantBackpressure
import com.digitalasset.canton.participant.admin.ResourceLimits
import com.digitalasset.canton.participant.protocol.TransactionProcessor.SubmissionErrors.ParticipantOverloaded
import com.digitalasset.canton.{DiscardOps, config}
import monocle.macros.syntax.lens.*
import org.scalatest.Assertion

import java.util.concurrent.atomic.{AtomicBoolean, AtomicInteger}
import scala.concurrent.{Future, Promise}
import scala.jdk.CollectionConverters.*

trait BackpressureIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with HasProgrammableSequencer {

  val maxInFlight = 10

  override def environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.singleDomain
      .addConfigTransforms(
        ProgrammableSequencer.configOverride(this.getClass.toString, loggerFactory),
        // Bump the ACS pruning interval so that we don't get warnings about pruning taking too long
        ConfigTransforms.acsPruningInterval(config.NonNegativeFiniteDuration.ofDays(1)),
        ConfigTransforms.updateAllParticipantConfigs_(
          _.focus(_.parameters.warnIfOverloadedFor)
            .replace(Some(config.NonNegativeFiniteDuration.ofMillis(100)))
        ),
      )
      .withSetup { implicit env =>
        import env.*
        participants.local.dars.upload(CantonExamplesPath)
        participants.local.domains.connect_local(da)

        // Code snippet just for the user manual
        // user-manual-entry-begin: SetResourceLimits
        participant1.resources.set_resource_limits(
          ResourceLimits(
            // Allow for submitting at most 200 commands per second
            maxRate = Some(200),

            // Limit the number of in-flight requests to 500.
            // A "request" includes every transaction that needs to be validated by participant1:
            // - transactions originating from commands submitted to participant1
            // - transaction originating from commands submitted to different participants.
            // The chosen configuration allows for processing up to 100 requests per second
            // with an average latency of 5 seconds.
            maxDirtyRequests = Some(500),

            // Allow submission bursts of up to `factor * maxRate`
            maxBurstFactor = 0.5,
          )
        )
        // user-manual-entry-end: SetResourceLimits

        participants.local.foreach(_.resources.set_resource_limits(ResourceLimits.noLimit))
      }

  def submitCommandsAndCheckResult(
      mainSubmitter: LocalParticipantReference,
      preloadSubmitter: LocalParticipantReference,
      preloadCount: Int,
      testCount: Int,
      minSuccesses: Int,
      maxSuccesses: Int,
      testSubmissionRate: Int = Integer.MAX_VALUE,
      expectOverloaded: Boolean = false,
  )(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*

    loggerFactory.assertLoggedWarningsAndErrorsSeq(
      {
        val releaseAllMessages = Promise[Unit]()
        try {
          // Holding back non-requests to keep all requests dirty until released.
          getProgrammableSequencer(da.name).setPolicy_("hold non-requests") {
            case r if !r.isRequest => SendDecision.HoldBack(releaseAllMessages.future)
            case _ => SendDecision.Process
          }

          logger.info("Preloading the system")
          val preloadInfo =
            submitCommands(preloadSubmitter, mainSubmitter, da, preloadCount, Integer.MAX_VALUE)

          eventually() {
            val load = mainSubmitter.underlying.value.sync.computeTotalLoad
            load shouldBe preloadCount withClue s"Only $load out of $preloadCount requests made it to Phase 3 during preloading."
            preloadInfo.numFailures
              .get() shouldBe 0 withClue "- unexpected failures during preloading"
          }

          logger.info("Starting the actual tests.")
          val testInfo =
            submitCommands(mainSubmitter, mainSubmitter, da, testCount, testSubmissionRate)

          eventually() {
            val load = mainSubmitter.underlying.value.sync.computeTotalLoad
            load should be >= (minSuccesses + preloadCount) withClue s"Only $load out of ${minSuccesses + preloadCount} requests made it to Phase 3 during the test."
            testInfo.numFailures
              .get() should be >= (testCount - maxSuccesses) withClue s"- too few rejections during testing"
          }

          logger.info("Releasing all messages to clean up the test.")
          releaseAllMessages.success(())

          // Await termination of all commands.
          preloadInfo.done.futureValue
          preloadInfo.numSuccesses.get() shouldBe preloadCount
          preloadInfo.numFailures.get() shouldBe 0

          testInfo.done.futureValue
          testInfo.numSuccesses.get() should be >= minSuccesses withClue "- too few successes."
          testInfo.numSuccesses.get() should be <= maxSuccesses withClue "- too many successes."
          testInfo.numFailures.get() + testInfo.numSuccesses.get() shouldBe testCount
        } finally {
          releaseAllMessages.trySuccess(())
        }
      },
      entries => {
        val numBackpressure = new AtomicInteger()
        val isOverloaded = new AtomicBoolean()
        forEvery(entries) { entry =>
          if (entry.loggerName.contains("EnterpriseEnvironmentDefinition")) {
            // Message logged at the client side
            entry.shouldBeCantonErrorCode(ParticipantBackpressure)
            // Important to use ABORTED, because it is not used by GRPC internally and it indicates that a retry makes sense.
            entry.message should include("ABORTED/")
            numBackpressure.incrementAndGet()
          } else if (entry.loggerName.contains("CantonSyncService")) {
            // Logged by the participant if too many messages need to be rejected
            entry.shouldBeCantonErrorCode(ParticipantOverloaded)
            isOverloaded.set(true)
          } else {
            fail(s"Unexpected logger name: $entry")
          }
        }

        if (maxSuccesses < testCount) numBackpressure.get() should be > 0
        if (expectOverloaded) isOverloaded.get() shouldBe true
        succeed
      },
    )
  }

  case class SubmissionInfo(
      done: Future[Unit],
      numSuccesses: AtomicInteger,
      numFailures: AtomicInteger,
  )

  def submitCommands(
      submitter: ParticipantReference,
      observer: ParticipantReference,
      domain: DomainReference,
      total: Int,
      submissionRate: Int,
  )(implicit env: EnterpriseTestConsoleEnvironment): SubmissionInfo = {
    import env.*
    val numSuccesses = new AtomicInteger()
    val numFailures = new AtomicInteger()
    val done = Future
      .traverse((0 until total).toList) { _ =>
        // Wait a bit so that the "burst" is not too extreme.
        Threading.sleep(1000L / submissionRate)
        Future {
          (if (submitCommand(submitter, observer, domain)) numSuccesses else numFailures)
            .incrementAndGet()
            .discard
        }
      }
      .void
    SubmissionInfo(done, numSuccesses, numFailures)
  }

  def submitCommand(
      submitter: ParticipantReference,
      observer: ParticipantReference,
      domain: DomainReference,
  )(implicit env: EnterpriseTestConsoleEnvironment): Boolean = {
    import env.*

    val amount = new Amount(100.toBigDecimal, "USD")
    val iou = new Iou(
      submitter.adminParty.toProtoPrimitive,
      observer.adminParty.toProtoPrimitive,
      amount,
      List.empty.asJava,
    )
    try {
      submitter.ledger_api.javaapi.commands
        .submit(
          Seq(submitter.adminParty),
          iou.create.commands.asScala.toSeq,
          workflowId = domain.name,
        )
      true
    } catch {
      case _: CommandFailure => false // backpressure has kicked in
    }

  }

  "A participant" when {
    "backpressure is disabled" can {
      s"processes all commands at once" in { implicit env =>
        import env.*
        submitCommandsAndCheckResult(
          participant1,
          participant1,
          maxInFlight,
          maxInFlight,
          maxInFlight,
          maxInFlight,
        )
      }
    }

    "max-in-flight is enabled" should {
      s"reject all additional commands" in { implicit env =>
        import env.*

        participant1.resources.set_resource_limits(ResourceLimits(Some(maxInFlight), None))

        submitCommandsAndCheckResult(participant1, participant1, maxInFlight, maxInFlight, 0, 0)
      }

      s"report an overloaded participant" in { implicit env =>
        import env.*

        participant1.resources.set_resource_limits(ResourceLimits(Some(maxInFlight), None))

        submitCommandsAndCheckResult(
          participant1,
          participant1,
          maxInFlight,
          200,
          0,
          0,
          testSubmissionRate = 1000,
          expectOverloaded = true,
        )
      }
    }

    "max-in-flight is enabled and another participant is creating load" should {
      s"reject all additional commands" in { implicit env =>
        import env.*
        submitCommandsAndCheckResult(participant1, participant2, maxInFlight, maxInFlight, 0, 0)
      }
    }

    "a rate limit is enabled" should {
      "reject some commands" in { implicit env =>
        import env.*

        // Preload the participant with a high number of commands to check that the number of in-flight commands does not make a difference.
        val preloadCount = maxInFlight * 2

        // Choose a low limit, so that we can submit at a much higher rate. (2000 commands/s seems realistic.)
        val rateLimit = 5

        // The rate limiter must never reject the first command.
        val minAccepted = 1 // the first command must succeed in any case

        // The rate limiter may accept a second command, as it may hit a second cycle.
        // A third command/cycle should be impossible, as the second cycle takes 1s.
        // (But if we ever see a 3rd command in CI, we may bump this.)
        val maxAccepted = 2

        // Make sure to test more than maxAccepted.
        val testCount = maxAccepted * 2

        participant1.resources.set_resource_limits(
          ResourceLimits(None, Some(rateLimit), maxBurstFactor = 0.01)
        )

        submitCommandsAndCheckResult(
          participant1,
          participant2,
          preloadCount,
          testCount,
          minAccepted,
          maxAccepted,
        )
      }
    }

    "both max-in-flight and a rate limit is enabled" should {

      // Preload the participant by 50% so that we can test the interplay of maxDirtyRequests and rate limit.
      val preloadCount = maxInFlight / 2

      // The goal is to get at least maxInFlight commands accepted in total.
      val minAccepted = maxInFlight - preloadCount

      // Choose the rate limit such that minAccepted can be submitted within a single cycle
      val rateLimit = minAccepted * 10

      "reject extra commands when submitting at limit rate" in { implicit env =>
        import env.*

        // More commands may get accepted, as it takes time until requests get dirty.
        val maxAccepted = minAccepted * 4

        // Make sure to test more than maxAccepted
        val testCount = maxAccepted * 2

        participant1.resources.set_resource_limits(
          ResourceLimits(Some(maxInFlight), Some(rateLimit), maxBurstFactor = 0.01)
        )

        submitCommandsAndCheckResult(
          participant1,
          participant2, // preload through participant2, so that participant1's rate limit does not get in the way
          preloadCount,
          testCount,
          minAccepted,
          maxAccepted,
          rateLimit,
        )
      }

      "reject most commands when submitting at a fast rate" in { implicit env =>
        import env.*

        // More commands may get accepted depending on how long the test runs
        val maxAccepted = minAccepted * 4

        // Make sure to test more than maxAccepted
        // But don't test too many commands, because otherwise the submission may take too long.
        val testCount = maxAccepted + minAccepted

        participant1.resources.set_resource_limits(
          ResourceLimits(
            Some(maxInFlight),
            Some(rateLimit),
            // we need to at least allow the min accepted burst to go through
            maxBurstFactor = minAccepted / rateLimit.toDouble,
          )
        )

        submitCommandsAndCheckResult(
          participant1,
          participant2,
          preloadCount,
          testCount,
          minAccepted,
          maxAccepted,
        )
      }
    }

    "max-dirty-requests is zero" should {
      "reject all commands" in { implicit env =>
        import env.*

        participant1.resources.set_resource_limits(ResourceLimits(Some(0), None))

        assertOneCommandRejectedWithBackpressure(participant1, da)
      }
    }

    def assertOneCommandRejectedWithBackpressure(
        participant: ParticipantReference,
        domain: DomainReference,
    )(implicit env: EnterpriseTestConsoleEnvironment): Assertion =
      loggerFactory.assertLoggedWarningsAndErrorsSeq(
        submitCommand(participant, participant, domain) shouldBe false,
        forEvery(_) { entry =>
          if (entry.loggerName.contains("EnterpriseEnvironmentDefinition")) {
            entry.shouldBeCantonErrorCode(ParticipantBackpressure)
            entry.message should include("ABORTED/")
          } else if (entry.loggerName.contains("CantonSyncService")) {
            entry.shouldBeCantonErrorCode(ParticipantOverloaded)
          } else {
            fail(s"Unexpected logger name: $entry")
          }
        },
      )

    "the rate limit is zero" should {
      "reject all commands" in { implicit env =>
        import env.*

        participant1.resources.set_resource_limits(ResourceLimits(None, Some(0)))

        assertOneCommandRejectedWithBackpressure(participant1, da)
      }
    }
  }
}

class BackpressureIntegrationTestDefault
    extends BackpressureIntegrationTest //TODO(i9565): beware -- in-memory integration tests can be flaky due to a known issue

//class BackpressureIntegrationTestPostgres extends BackpressureIntegrationTest {
//  registerPlugin(new UsePostgres(loggerFactory))
//}

// Do not run this on Oracle, as the test is inherently racy and
// the dockerized Oracle we use in CI is not performant enough for this.
//class BackpressureIntegrationTestOracle extends BackpressureIntegrationTest {
//  registerPlugin(new UseOracle(loggerFactory))
//}
