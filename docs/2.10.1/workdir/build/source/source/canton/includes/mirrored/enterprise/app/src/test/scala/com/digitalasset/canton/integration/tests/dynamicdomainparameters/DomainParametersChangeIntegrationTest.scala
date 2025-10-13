// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.dynamicdomainparameters

import com.daml.test.evidence.scalatest.AccessTestScenario
import com.daml.test.evidence.scalatest.ScalaTestSupport.Implicits.*
import com.daml.test.evidence.tag.Security.SecurityTest.Property.SecureConfiguration
import com.daml.test.evidence.tag.Security.{Attack, SecurityTest, SecurityTestSuite}
import com.digitalasset.canton.admin.api.client.data.{
  DynamicDomainParameters as ConsoleDynamicDomainParameters,
  DynamicDomainParametersV0,
  DynamicDomainParametersV1,
  DynamicDomainParametersV2,
}
import com.digitalasset.canton.config.RequireTypes.NonNegativeInt
import com.digitalasset.canton.config.{
  NonNegativeDuration,
  NonNegativeFiniteDuration,
  PositiveDurationSeconds,
}
import com.digitalasset.canton.console.DomainReference
import com.digitalasset.canton.data.CantonTimestamp
import com.digitalasset.canton.integration.*
import com.digitalasset.canton.integration.plugins.UsePostgres
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.logging.SuppressionRule
import com.digitalasset.canton.protocol.DynamicDomainParameters as DynamicDomainParametersInternal
import com.digitalasset.canton.time.SimClock
import com.digitalasset.canton.topology.TopologyManagerError
import com.digitalasset.canton.topology.TopologyManagerError.IncreaseOfLedgerTimeRecordTimeTolerance
import com.digitalasset.canton.version.ProtocolVersion
import monocle.macros.syntax.lens.*
import org.scalatest.Assertion
import org.scalatest.concurrent.PatienceConfiguration
import org.slf4j.event.Level

import scala.concurrent.Future
import scala.concurrent.duration.*

trait DomainParametersFixture {
  protected def increaseParticipantResponseTimeout(
      old: ConsoleDynamicDomainParameters
  ): ConsoleDynamicDomainParameters =
    old.update(participantResponseTimeout = old.participantResponseTimeout.plusSeconds(1))

  protected def getCurrentDomainParameters(d: DomainReference): ConsoleDynamicDomainParameters = {
    val domainParameters =
      d.topology.domain_parameters_changes.list(filterStore = "Authorized").map(_.item)

    assert(domainParameters.sizeIs == 1)
    domainParameters.head
  }
}

trait DomainParametersChangeIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with DomainParametersFixture
    with SecurityTestSuite
    with AccessTestScenario {

  private lazy val staticReconciliationInterval = PositiveDurationSeconds.ofSeconds(1)
  private lazy val dynamicReconciliationInterval = PositiveDurationSeconds.ofSeconds(2)

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.multiDomain.addConfigTransforms(
      ConfigTransforms.useStaticTime,
      // Disable retries in the ping service so that any submission error is reported reliably
      // This makes the log messages more deterministic.
      ConfigTransforms.updateAllParticipantConfigs_(
        _.focus(_.parameters.adminWorkflow.retries).replace(0)
      ),
    ) withSetup { implicit env =>
      import env.*

      participant1.domains.connect_local(da)
    }

  private lazy val defaultParameters = ConsoleDynamicDomainParameters(
    DynamicDomainParametersInternal.initialValues(
      new SimClock(loggerFactory = loggerFactory),
      testedProtocolVersion,
    )
  ).value

  "A domain operator" can {
    "list and set domain parameters" in { implicit env =>
      import env.*

      val domainParameters1 = increaseParticipantResponseTimeout(defaultParameters)
      val domainParameters2 = increaseParticipantResponseTimeout(domainParameters1)
      val domainParameters3 = increaseParticipantResponseTimeout(domainParameters2)

      getCurrentDomainParameters(da) shouldBe defaultParameters
      getCurrentDomainParameters(acme) shouldBe defaultParameters

      da.service.set_dynamic_domain_parameters(domainParameters1)
      getCurrentDomainParameters(da) shouldBe domainParameters1
      getCurrentDomainParameters(acme) shouldBe defaultParameters

      da.service.set_dynamic_domain_parameters(domainParameters2)
      acme.service.set_dynamic_domain_parameters(domainParameters3)
      getCurrentDomainParameters(da) shouldBe domainParameters2
      getCurrentDomainParameters(acme) shouldBe domainParameters3
    }

    "update domain parameters" in { implicit env =>
      import env.*

      val currentDomainParameters = getCurrentDomainParameters(da)
      val modifier = increaseParticipantResponseTimeout _
      val expectedNewDomainParameters = modifier(currentDomainParameters)

      da.service.update_dynamic_domain_parameters(modifier)

      getCurrentDomainParameters(da) shouldBe expectedNewDomainParameters
    }

    "update reconciliation interval" in { implicit env =>
      import env.*

      val newDynamicReconciliationInterval =
        PositiveDurationSeconds.ofSeconds(
          dynamicReconciliationInterval.asJava.getSeconds + 1
        )

      val reconciliationTest = TestDynamicParams[PositiveDurationSeconds](
        setDynamicParameter = da.service.set_reconciliation_interval(_),
        setDynamicParameterThrow =
          (d: PositiveDurationSeconds) => da.service.set_reconciliation_interval(d),
        getDynamicParameter = _ => da.service.get_reconciliation_interval,
        initialValue = dynamicReconciliationInterval,
        newValue = newDynamicReconciliationInterval,
        name = "reconciliation interval",
      )
      TestDynamicParams.runTest(reconciliationTest)
    }

    "update maxRatePerParticipant" in { implicit env =>
      import env.*

      val initialValue = NonNegativeInt.tryCreate(10)

      val maxRatePerParticipantTest = TestDynamicParams[NonNegativeInt](
        setDynamicParameter = da.service.set_max_rate_per_participant(_),
        setDynamicParameterThrow = da.service.set_max_rate_per_participant(_),
        getDynamicParameter = _ => da.service.get_max_rate_per_participant,
        initialValue = initialValue,
        newValue = initialValue * 10,
        name = "max rate per participant",
      )
      TestDynamicParams.runTest(maxRatePerParticipantTest)
    }

    "update maxRequestSize" in { implicit env =>
      import env.*

      val initialValue = NonNegativeInt.tryCreate(60000)

      val maxRequestSizeTest = TestDynamicParams[NonNegativeInt](
        setDynamicParameter = da.service.set_max_request_size(_),
        setDynamicParameterThrow = da.service.set_max_request_size(_),
        getDynamicParameter = _ => da.service.get_max_request_size,
        initialValue = initialValue,
        newValue = initialValue * 10,
        name = "max request size",
      )
      TestDynamicParams.runTest(maxRequestSizeTest)
    }

    // This is just for the snippets
    "perform simple domain parameters operations" in { implicit env =>
      import env.*

      val mydomain = acme

      /*
        This does not test much, the only goal is to have the snippets included in the
        documentation. We don't use proper `snippets` because we would need to introduce
        a new environment which makes the documentation generation slower.
       */

      // user-manual-entry-begin:-begin: GetDynamicDomainParameters
      mydomain.service.get_dynamic_domain_parameters
      // user-manual-entry-begin:-end: GetDynamicDomainParameters

      // user-manual-entry-begin:-begin: GetSingleDynamicDomainParameter
      mydomain.service.get_reconciliation_interval
      mydomain.service.get_max_rate_per_participant
      mydomain.service.get_max_request_size
      mydomain.service.get_mediator_deduplication_timeout
      // user-manual-entry-begin:-end: GetSingleDynamicDomainParameter

      // user-manual-entry-begin:-begin: SetDynamicDomainParameters
      mydomain.service.set_reconciliation_interval(5.seconds)
      mydomain.service.set_max_rate_per_participant(100)
      mydomain.service.set_max_request_size(100000)
      mydomain.service.set_mediator_deduplication_timeout(2.minutes)
      // user-manual-entry-begin:-end: SetDynamicDomainParameters

      // user-manual-entry-begin:-begin: UpdateDynamicDomainParameters
      mydomain.service.update_dynamic_domain_parameters(
        _.update(
          participantResponseTimeout = 10.seconds,
          topologyChangeDelay = 1.second,
        )
      )
    // user-manual-entry-begin:-end: UpdateDynamicDomainParameters
    }

    "update maxRatePerParticipant to 0 and expect it to fail" in { implicit env =>
      import env.*

      val zero = NonNegativeInt.tryCreate(0)
      Seq(participant1, participant2).foreach(_.domains.connect_local(da))
      val ping = participant1.health.ping(participant2.id)
      assert(ping.gt(0.second))

      da.service.set_max_rate_per_participant(zero)
      eventually() {
        da.service.get_max_rate_per_participant shouldBe zero
      }

      val expectedMessages = Seq(
        "Overloaded(Submission rate exceeds rate limit of 0/s.)",
        "failed with reason MaxRetriesReached",
      )

      loggerFactory.assertLogsSeq(SuppressionRule.LevelAndAbove(Level.WARN))(
        participant1.health
          .maybe_ping(participant2.id, NonNegativeDuration.tryFromDuration(3.seconds)),
        forEvery(_) { entry =>
          assert(expectedMessages.exists(entry.message.contains(_)))
        },
      )
    }

    "set the same domain parameters twice" in { implicit env =>
      import env.*
      da.service.set_dynamic_domain_parameters(defaultParameters)
      getCurrentDomainParameters(da) shouldBe defaultParameters

      da.service.set_dynamic_domain_parameters(defaultParameters)
      getCurrentDomainParameters(da) shouldBe defaultParameters
    }

    "not change domain parameters on alien domains" in { implicit env =>
      import env.*

      assertThrowsAndLogsCommandFailures(
        da.topology.domain_parameters_changes
          .authorize(acme.id, defaultParameters, testedProtocolVersion),
        entry => {
          entry.shouldBeCommandFailure(TopologyManagerError.NoAppropriateSigningKeyInStore)
        },
      )
    }

    val secureConfigurationAsset: SecurityTest = SecurityTest(
      property = SecureConfiguration,
      asset = "domain",
    )

    def increaseTol(p: ConsoleDynamicDomainParameters): ConsoleDynamicDomainParameters =
      p.update(ledgerTimeRecordTimeTolerance = p.ledgerTimeRecordTimeTolerance * 2)

    def increaseDedup(p: ConsoleDynamicDomainParameters): ConsoleDynamicDomainParameters =
      p match {
        case p0: DynamicDomainParametersV0 => p0
        case p1: DynamicDomainParametersV1 =>
          p1.copy(mediatorDeduplicationTimeout = p1.mediatorDeduplicationTimeout * 2)
        case p2: DynamicDomainParametersV2 =>
          p2.copy(mediatorDeduplicationTimeout = p2.mediatorDeduplicationTimeout * 2)
      }

    "not configure insecure values for mediatorDeduplicationTimeout and ledgerTimeRecordTimeTolerance" taggedAs secureConfigurationAsset
      .setAttack(
        Attack(
          actor = "a malicious participant",
          threat = "submits two requests with the same UUID",
          mitigation = "The mediator rejects the second requests.",
        )
      ) in { _ =>
      // Prevent construction of domain parameters with mediatorDeduplicationTimeout being too low
      val d = NonNegativeFiniteDuration.ofSeconds(10)
      val ex = the[RuntimeException] thrownBy DynamicDomainParametersV1(
        NonNegativeFiniteDuration.Zero,
        NonNegativeFiniteDuration.Zero,
        NonNegativeFiniteDuration.Zero,
        d,
        d,
        d,
        PositiveDurationSeconds.ofSeconds(1),
        NonNegativeInt.zero,
        NonNegativeInt.zero,
      )
      ex.getMessage shouldBe "The ledgerTimeRecordTimeTolerance (10s) must be at most half of the mediatorDeduplicationTimeout (10s)."
    }

    "require force to immediately increase ledgerTimeRecordTimeTolerance" taggedAs secureConfigurationAsset
      .setAttack(
        Attack(
          actor = "a domain operator",
          threat = "configures a too high value for ledgerTimeRecordTimeTolerance by accident",
          mitigation = "the domain rejects the request",
        )
      ) in { implicit env =>
      import env.*

      // Refuse to increase ledgerTimeRecordTimeTolerance without increasing mediatorDeduplicationTimeout
      val oldTol = da.service.get_dynamic_domain_parameters.ledgerTimeRecordTimeTolerance
      val oldDedup = da.service.get_mediator_deduplication_timeout

      val oldToErrorMessage = (oldTol * 2).toInternal.toString
      val oldDedupErrorMessage = oldDedup.toInternal.toString

      assertThrowsAndLogsCommandFailures(
        da.service.set_ledger_time_record_time_tolerance(oldTol * 2),
        _.shouldBeCommandFailure(
          IncreaseOfLedgerTimeRecordTimeTolerance,
          s"Unable to increase ledgerTimeRecordTimeTolerance to $oldToErrorMessage, " +
            s"because it must not be more than half of mediatorDeduplicationTimeout ($oldDedupErrorMessage).",
        ),
      )

      // Increase mediatorDeduplicationTimeout up front so it won't prevent increasing tolerance
      da.service.update_dynamic_domain_parameters(increaseDedup)

      // Require force to increase the parameter.
      assertThrowsAndLogsCommandFailures(
        da.service.update_dynamic_domain_parameters(increaseTol),
        _.shouldBeCommandFailure(
          IncreaseOfLedgerTimeRecordTimeTolerance,
          s"The parameter ledgerTimeRecordTimeTolerance can currently not be increased to",
        ),
      )

      // Increase the parameter when using force
      val params = da.service.get_dynamic_domain_parameters
      val newParams = increaseTol(params)
      da.service.update_dynamic_domain_parameters(increaseTol, force = true)

      da.service.get_dynamic_domain_parameters shouldBe newParams
    }

    "securely increase ledgerTimeRecordTimeTolerance" taggedAs_ {
      secureConfigurationAsset.setHappyCase(_)
    } in { implicit env =>
      import env.*

      val tol = da.service.get_dynamic_domain_parameters.ledgerTimeRecordTimeTolerance
      val dedup = da.service.get_mediator_deduplication_timeout
      assume(tol * 2 == dedup)

      da.service.set_mediator_deduplication_timeout(dedup * 2)

      logger.info("Request increase of tol...")
      val updateF = Future {
        da.service.set_ledger_time_record_time_tolerance(tol * 2)
      }

      // Without this the clock jumps from :00m to :08m,
      // sometimes before the update of parameters from set_ledger_time_record_time_tolerance reaches the sequencer,
      // which thus fails with "exceed max-sequencing-time" which is set to the default of 5m
      logger.info(s"Advance clock to the point where no exceed max-sequencing-time can occur")
      env.environment.simClock.value.advance(dedup.asJava) // jump to 4m

      logger.info("Wait until dedup has been increased...")
      // Also verify that tol has not yet been increased.
      val increaseDedupTs = eventually() {
        // Complex construction, because we need to query the domain store and we need to retrieve
        // the timestamp of the transaction to properly advance the simClock.
        val tx = da.topology.domain_parameters_changes
          .list(da.id.filterString)
          .sortBy(_.context.validFrom)(implicitly[Ordering[java.time.Instant]].reverse)
          .headOption
          .value
        tx.item.ledgerTimeRecordTimeTolerance shouldBe tol
        if (testedProtocolVersion < ProtocolVersion.v7) {
          tx.item
            .asInstanceOf[DynamicDomainParametersV1]
            .mediatorDeduplicationTimeout shouldBe dedup * 2
        } else {
          tx.item
            .asInstanceOf[DynamicDomainParametersV2]
            .mediatorDeduplicationTimeout shouldBe dedup * 2
        }

        CantonTimestamp.assertFromInstant(tx.context.validFrom)
      }

      // set_ledger_time_record_time_tolerance submits a no-op transaction for ledgerTimeRecordTimeTolerance to "synchronize" internally.
      // however, there's a race condition with advancing the clock. particularly if the submission of that no-op transaction
      // from the authorized store to the domain happens before advancing the clock, the request will exceed its maximum record time.
      // by synchronizing the topology here, we wait for the no-op transaction to fully go through, but still keep
      // the secure update mechanism waiting until the clock is advanced.
      utils.synchronize_topology()

      // Advance clock to the point that tol can be increased
      val increaseTolMinTs = increaseDedupTs.plus((dedup * 2).asJava)
      logger.info(s"Advance clock to the point that tol can be increased: $increaseTolMinTs")
      env.environment.simClock.value.advanceTo(increaseTolMinTs)

      updateF.futureValue(
        // Provide a bit more time since setting record time tolerance needs to wait
        // for change to be secure which flakily takes more than the default timeout of 20 seconds. #14578
        timeout = PatienceConfiguration.Timeout(60.seconds)
      )

      logger.info(s"Verify that tol has effectively been increased...")
      da.service.get_dynamic_domain_parameters.ledgerTimeRecordTimeTolerance shouldBe tol * 2
      da.service.get_mediator_deduplication_timeout shouldBe dedup * 2
    }
  }

  "A participant" can {
    "query the domain parameters" in { implicit env =>
      import env.*

      eventually() {
        // participant needs a bit more time before seeing the changes
        participant1.topology.domain_parameters_changes.get_latest(
          da.id
        ) shouldBe getCurrentDomainParameters(da)
      }
    }
  }
  private[dynamicdomainparameters] case class TestDynamicParams[P](
      setDynamicParameter: P => Unit,
      setDynamicParameterThrow: P => Unit,
      getDynamicParameter: Unit => P,
      initialValue: P,
      newValue: P,
      name: String,
  )

  private object TestDynamicParams {
    def runTest[P](test: TestDynamicParams[P]): Assertion = {
      // initial setup
      test.setDynamicParameter(test.initialValue)

      val initialParameterValue = test.getDynamicParameter(())
      val expectedInitialParameterValue = test.initialValue

      initialParameterValue shouldBe expectedInitialParameterValue

      test.setDynamicParameter(test.newValue)
      test.getDynamicParameter(()) shouldBe test.newValue

    }
  }
}

class DomainParametersChangeIntegrationTestDefault
    extends DomainParametersChangeIntegrationTest //TODO(i9565): beware -- in-memory integration tests can be flaky due to a known issue

//class DomainParametersChangeIntegrationTestPostgres extends DomainParametersChangeIntegrationTest {
//  registerPlugin(new UsePostgres(loggerFactory))
//}

//class DomainParametersChangeIntegrationTestOracle extends DomainParametersChangeIntegrationTest {
//  registerPlugin(new UseOracle(loggerFactory))
//}

class DomainParametersRestartIntegrationTestPostgres
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with DomainParametersFixture {
  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.singleDomain

  registerPlugin(new UsePostgres(loggerFactory))

  private lazy val defaultParameters =
    ConsoleDynamicDomainParameters.defaultValues(testedProtocolVersion)

  "Dynamic domain parameters" should {
    "not be read from config upon restart" in { implicit env =>
      import env.*

      // initial setup
      getCurrentDomainParameters(da) shouldBe defaultParameters

      // change domain parameters
      val newDomainParameters = increaseParticipantResponseTimeout(defaultParameters)
      da.service.set_dynamic_domain_parameters(newDomainParameters)
      getCurrentDomainParameters(da) shouldBe newDomainParameters

      // restarting the domain
      da.stop()
      da.is_running shouldBe false
      da.start()

      // we should get the new value upon restart
      getCurrentDomainParameters(da) shouldBe newDomainParameters
    }
  }
}
