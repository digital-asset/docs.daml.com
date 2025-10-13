// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests

import com.daml.error.utils.DeserializedCantonError
import com.daml.ledger.api.v1.ledger_offset.LedgerOffset
import com.daml.ledger.api.v1.ledger_offset.LedgerOffset.LedgerBoundary
import com.digitalasset.canton.DiscardOps
import com.digitalasset.canton.concurrent.Threading
import com.digitalasset.canton.config.RequireTypes.NonNegativeInt
import com.digitalasset.canton.console.commands.DomainAdministration
import com.digitalasset.canton.examples.java.iou.Dummy
import com.digitalasset.canton.integration.plugins.{UseOracle, UsePostgres}
import com.digitalasset.canton.integration.{ConfigTransforms, EnterpriseEnvironmentDefinition}
import com.digitalasset.canton.logging.LogEntry
import com.digitalasset.canton.participant.protocol.TransactionProcessor
import com.digitalasset.canton.util.ResourceUtil.withResource
import monocle.macros.syntax.lens.*
import org.scalatest.Assertion

import java.util.UUID
import scala.jdk.CollectionConverters.*

trait MaxRequestSizeCrashTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with EnterpriseEnvironmentSetupHelper {

  def domainAdministration(implicit
      env: EnterpriseTestConsoleEnvironment
  ): DomainAdministration

  def setOverrideMaxRequestSizeWithNewEnv(
      oldEnv: EnterpriseTestConsoleEnvironment,
      overrideMaxRequestSize: NonNegativeInt,
  )(f: EnterpriseTestConsoleEnvironment => Unit): Unit

  // High request size
  private val overrideMaxRequestSize = NonNegativeInt.tryCreate(30000)
  // Request size chosen so that even TimeProof requests are rejected
  private val lowMaxRequestSize: NonNegativeInt = NonNegativeInt.zero

  "Canton" should {
    "recover from failure due to too small request size " in { implicit env =>
      import env.*
      participant1.dars.upload(CantonTestsPath)

      // verify the ping is successful
      assertPingSucceeds(participant1, participant1)
      // change maxRequestSize
      domainAdministration.service.set_max_request_size(lowMaxRequestSize, force = true)
      domainAdministration.service.get_max_request_size shouldBe lowMaxRequestSize

      val topologyDelayChange =
        domainAdministration.service.get_dynamic_domain_parameters.topologyChangeDelay
      // wait for the topology change
      Threading.sleep(topologyDelayChange.unwrap.toMillis)

      val commandId = s"submit-async-dummy-${UUID.randomUUID().toString}"

      loggerFactory.assertLogs(
        {
          participant1.ledger_api.javaapi.commands.submit_async(
            Seq(participant1.adminParty),
            new Dummy(participant1.adminParty.toProtoPrimitive).create.commands.asScala.toSeq,
            commandId = commandId,
          )
          eventually() {
            assertRequestInvalidDueToExceedingBatchSize(commandId, lowMaxRequestSize.unwrap)
          }
        },
        _.warningMessage should include regex
          s"Failed to submit submission due to Error\\(RequestInvalid\\(Batch size \\(.* bytes\\) is exceeding maximum size \\(MaxRequestSize\\($lowMaxRequestSize\\) bytes\\)",
      )

      // restart Canton with overrideMaxRequestSize
      setOverrideMaxRequestSizeWithNewEnv(env, overrideMaxRequestSize) { implicit newEnv =>
        import newEnv.*
        // we verify that the dynamic parameter is still set to the low value
        domainAdministration(newEnv).service.get_max_request_size shouldBe lowMaxRequestSize
        // we verify that this time the dynamic parameter is ignored
        participant1.ledger_api.javaapi.commands
          .submit(
            Seq(participant1.adminParty),
            new Dummy(participant1.adminParty.toProtoPrimitive).create.commands.asScala.toSeq,
          )
          .discard
      }
    }
  }

  private def assertRequestInvalidDueToExceedingBatchSize(commandId: String, maxRequestSize: Int)(
      implicit env: EnterpriseTestConsoleEnvironment
  ): Assertion = {
    import env.*
    for {
      completion <- participant1.ledger_api.completions
        .list(
          partyId = participant1.adminParty,
          atLeastNumCompletions = 1,
          offset = new LedgerOffset().withBoundary(LedgerBoundary.LEDGER_BEGIN),
          filter = _.commandId == commandId,
        )
        .headOption
        .toRight("Expecting completion")
      status <- completion.status.toRight("Expecting status in completion")
      deserializedError <- DeserializedCantonError.fromGrpcStatus(status)
      sendError <- deserializedError.context.get("sendError").toRight("Missing error context")
    } yield {
      deserializedError.code.id shouldBe TransactionProcessor.SubmissionErrors.SequencerRequest.id
      sendError should fullyMatch regex s"RequestInvalid\\(Batch size .* is exceeding maximum size \\(MaxRequestSize\\($maxRequestSize\\) bytes.*"
    }
  }.fold(fail(_), identity)
}

trait CommunityMaxRequestSizeCrashTest extends MaxRequestSizeCrashTest {
  override def environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.singleDomain
      .addConfigTransforms(
        // Disable retries in the ping service so that any submission error is reported reliably
        // This makes the log messages more deterministic.
        ConfigTransforms.updateAllParticipantConfigs_(
          _.focus(_.parameters.adminWorkflow.retries).replace(0)
        )
      )
      .withSetup { implicit env =>
        import env.*
        participants.all.domains.connect_local(da)
      }

  override def domainAdministration(implicit
      env: EnterpriseTestConsoleEnvironment
  ): DomainAdministration = env.da

  override def setOverrideMaxRequestSizeWithNewEnv(
      oldEnv: EnterpriseTestConsoleEnvironment,
      overrideMaxRequestSize: NonNegativeInt,
  )(f: EnterpriseTestConsoleEnvironment => Unit): Unit = {
    stop(oldEnv)
    import oldEnv.*
    val newEnv = manualCreateEnvironmentWithPreviousState(
      oldEnv.actualConfig,
      _ =>
        Seq(
          ConfigTransforms
            .updateDomainConfig(da.name)(
              _.focus(_.publicApi.overrideMaxRequestSize)
                .replace(Some(overrideMaxRequestSize))
                .focus(_.sequencerClient.overrideMaxRequestSize)
                .replace(Some(overrideMaxRequestSize))
            ),
          ConfigTransforms.updateAllParticipantConfigs_(
            _.focus(_.sequencerClient.overrideMaxRequestSize).replace(Some(overrideMaxRequestSize))
          ),
        ).foldLeft(oldEnv.actualConfig)((newConfig, transform) => transform(newConfig)),
    )
    withResource(newEnv) { env =>
      handleStartupLogs(start(newEnv))
      f(env)
    }
  }

  private def stop(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*
    // user-manual-entry-begin: StopNonDistributedCanton
    participants.all.domains.disconnect(da.name)
    nodes.local.stop()
    // user-manual-entry-end: StopNonDistributedCanton
  }

  private def start(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*
    nodes.local.start()
    participants.all.domains.reconnect_all()
  }
}

class CommunityMaxRequestSizeCrashTestPostgres extends CommunityMaxRequestSizeCrashTest {
  registerPlugin(new UsePostgres(loggerFactory))
}

//class CommunityMaxRequestSizeCrashTestOracle extends CommunityMaxRequestSizeCrashTest {
//  registerPlugin(new UseOracle(loggerFactory))
//}

trait EnterpriseMaxRequestSizeCrashTest extends MaxRequestSizeCrashTest {
  override def environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.distributedSingleDomain
      .addConfigTransforms(
        // Disable retries in the ping service so that any submission error is reported reliably
        // This makes the log messages more deterministic.
        ConfigTransforms.updateAllParticipantConfigs_(
          _.focus(_.parameters.adminWorkflow.retries).replace(0)
        )
      )
      .withSetup { implicit env =>
        import env.*
        domainManager1.setup.bootstrap_domain(sequencers.all, Seq(mediator1))
        domainManager1.health.wait_for_initialized()
        participants.all.domains.connect_local(sequencer1)
      }

  override def setOverrideMaxRequestSizeWithNewEnv(
      oldEnv: EnterpriseTestConsoleEnvironment,
      overrideMaxRequestSize: NonNegativeInt,
  )(f: EnterpriseTestConsoleEnvironment => Unit): Unit = {
    stop(oldEnv)
    import oldEnv.*
    val newEnv = manualCreateEnvironmentWithPreviousState(
      oldEnv.actualConfig,
      configTransform = _ =>
        Seq(
          ConfigTransforms
            .updateDomainConfig(domainManager1.name)(
              _.focus(_.sequencerClient.overrideMaxRequestSize)
                .replace(Some(overrideMaxRequestSize))
            ),
          ConfigTransforms.updateSequencerConfig(sequencer1.name)(
            _.focus(_.publicApi.overrideMaxRequestSize)
              .replace(Some(overrideMaxRequestSize))
              .focus(_.sequencerClient.overrideMaxRequestSize)
              .replace(Some(overrideMaxRequestSize))
          ),
          ConfigTransforms.updateMediatorConfig(mediator1.name)(
            _.focus(_.sequencerClient.overrideMaxRequestSize)
              .replace(Some(overrideMaxRequestSize))
          ),
          ConfigTransforms.updateAllParticipantConfigs_(
            _.focus(_.sequencerClient.overrideMaxRequestSize).replace(Some(overrideMaxRequestSize))
          ),
        ).foldLeft(oldEnv.actualConfig)((newConfig, transform) => transform(newConfig)),
    )
    withResource(newEnv) { env =>
      handleStartupLogs(restart(newEnv))
      f(env)
    }
  }

  override def domainAdministration(implicit
      env: EnterpriseTestConsoleEnvironment
  ): DomainAdministration = env.domainManager1

  private def stop(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*
    // user-manual-entry-begin: StopDistributedCanton
    participants.all.domains.disconnect(sequencer1.name)
    nodes.local.stop()
    // user-manual-entry-end: StopDistributedCanton
  }

  private def restart(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*
    // user-manual-entry-begin: RestartCanton
    nodes.local.start()
    participants.all.domains.reconnect_all()
    // user-manual-entry-end: RestartCanton
  }
}

//class EnterpriseMaxRequestSizeCrashTestPostgres extends EnterpriseMaxRequestSizeCrashTest {
//  registerPlugin(new UsePostgres(loggerFactory))
//}

class EnterpriseMaxRequestSizeCrashTestOracle extends EnterpriseMaxRequestSizeCrashTest {
  registerPlugin(new UseOracle(loggerFactory))

  override val logsToBeHandledAtStartup: Option[Seq[LogEntry] => Assertion] = Some(
    LogEntry.assertLogSeq(
      Seq.empty,
      // Handle Oracle backend initialization delay
      Seq(e => assert(e.warningMessage.contains("Failed to initialize pool"))),
    )
  )
}
