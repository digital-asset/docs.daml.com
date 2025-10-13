// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.sequencer

import com.daml.nonempty.NonEmpty
import com.daml.test.evidence.scalatest.ScalaTestSupport.Implicits.*
import com.daml.test.evidence.tag.Reliability.*
import com.digitalasset.canton.config.RequireTypes.Port
import com.digitalasset.canton.console.{CommandFailure, ParticipantReference}
import com.digitalasset.canton.data.CantonTimestamp
import com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition.distributedSingleDomain
import com.digitalasset.canton.integration.integration.ConfigTransform
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  EnterpriseTestConsoleEnvironment,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.integration.{ConfigTransforms, EnterpriseEnvironmentDefinition}
import com.digitalasset.canton.networking.Endpoint
import com.digitalasset.canton.protocol.messages.DefaultOpenEnvelope
import com.digitalasset.canton.sequencing.protocol.Batch
import com.digitalasset.canton.sequencing.{
  GrpcSequencerConnection,
  SequencerConnection,
  SequencerConnections,
}
import com.digitalasset.canton.topology.SequencerId
import com.digitalasset.canton.{DomainAlias, SequencerAlias}

import java.time.Duration
import scala.concurrent.duration.DurationInt

abstract class DynamicOnboardingIntegrationTest(val name: String)
    extends EnterpriseIntegrationTest
    with SequencerTestUtils
    with SharedEnterpriseEnvironment
    with ReliabilityTestSuite {

  protected val domainInitializationTimeout: Duration = Duration.ofSeconds(20)

  /** Hook for allowing sequencer integrations to adjust the base test config */
  protected def additionalConfigTransforms: ConfigTransform =
    ConfigTransforms.identity

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    transformEnv(distributedSingleDomain)

  protected def transformEnv(
      env: EnterpriseEnvironmentDefinition
  ): EnterpriseEnvironmentDefinition = env.withManualStart
    .addConfigTransform(additionalConfigTransforms)
    .withSetup(implicit env => setupEnv)

  private def setupEnv(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*
    nodes.local.start()
  }

  private def modifyConnection(
      participant: ParticipantReference,
      name: DomainAlias,
      connection: SequencerConnection,
  ): Unit = {
    participant.domains.disconnect(name)
    participant.domains.modify(
      name,
      _.copy(sequencerConnections = SequencerConnections.single(connection)),
    )
    participant.domains.reconnect(name)
  }

  var aggregationSequenced2: CantonTimestamp = _
  var maxSequencingTimeOfAggregation: CantonTimestamp = _
  var timestampOfSigningKeyAgg: CantonTimestamp = _
  var aggregatedBatch: Batch[DefaultOpenEnvelope] = _

  s"using an environment with 2 $name sequencer nodes and a domain configured with only one of them" should {
    "bootstrap domain with external sequencer and have participant be able to ping using domain's sequencer" in {
      implicit env =>
        import env.*

        mediator1.health.initialized() shouldBe false
        sequencer1.health.initialized() shouldBe false

        domainManager1.setup.bootstrap_domain(Seq(sequencer1), Seq(mediator1))

        mediator1.health.initialized() shouldBe true
        sequencer1.health.initialized() shouldBe true

        participant1.domains.connect_local(sequencer1)
        participant3.domains.connect_local(sequencer1)
        participant1.health.ping(participant3, timeout = 30.seconds)
    }

    "bootstrap command be idempotent and have no effect if called again" in { implicit env =>
      import env.*
      domainManager1.setup.bootstrap_domain(Seq(sequencer1), Seq(mediator1))
      participant1.health.ping(participant1, timeout = 30.seconds)
    }

    "participant should be able to ping using dynamically onboarded sequencer" in { implicit env =>
      import env.*
      sequencer1.health.initialized() shouldBe true
      sequencer2.health.initialized() shouldBe false

      // user-manual-entry-begin: DynamicallyOnboardSequencer
      domainManager1.setup.onboard_new_sequencer(
        initialSequencer = sequencer1,
        newSequencer = sequencer2,
      )
      // user-manual-entry-end: DynamicallyOnboardSequencer

      sequencer2.health.initialized() shouldBe true

      // Restart the new sequencer to make sure that the initialization survives a restart
      sequencer2.stop()
      sequencer2.start()

      participant2.domains.connect_local(sequencer2)
      participant1.health.ping(participant2, timeout = 30.seconds)
    }

    "participant should be able to switch to new sequencer even if it has received no transactions after the onboarding" taggedAs
      ReliabilityTest(
        Component("Participant", "connected to sequencer"),
        AdverseScenario(
          dependency = "sequencer",
          details = "connected sequencer fails",
        ),
        Remediation(
          remediator = "multiple sequencers",
          action = "participant is manually switched over to use a difference sequencer",
        ),
        outcome = "participant continues to process and submit transactions",
      ) in { implicit env =>
        import env.*

        // This is crucial because the participant will re-request the last event in its sequenced event store
        // and the new sequencer will serve only events from after when the snapshot was taken,
        // which happens before the sequencer onboarding transaction.
        val domainId = domainManager1.id
        eventually() {
          val sequencerTx = participant3.topology.owner_to_key_mappings.list(
            filterStore = domainId.filterString,
            filterKeyOwnerUid = domainId.filterString,
            filterKeyOwnerType = Some(SequencerId.Code),
          )
          // Participant3 has received the onboarding transaction if there are two key mappings for sequencers
          sequencerTx.length shouldBe 2
        }
        modifyConnection(participant3, sequencer1.name, sequencer2.sequencerConnection)
        participant3.health.ping(participant1, timeout = 30.seconds)
      }

    "mediator can change sequencer connection" in { implicit env =>
      import env.*

      // needed to prevent the mediator from getting a tombstone on re-connection reading the last message
      participant1.health.ping(participant3, timeout = 30.seconds)

      val conn1 = sequencer1.sequencerConnection
      mediator1.sequencer_connection.get() shouldBe Some(SequencerConnections.single(conn1))

      val conn2 = sequencer2.sequencerConnection
      mediator1.sequencer_connection.set(SequencerConnections.single(conn2))
      mediator1.sequencer_connection.get() shouldBe Some(SequencerConnections.single(conn2))
      participant1.health.ping(participant2, timeout = 30.seconds)

      mediator1.sequencer_connection.modify_connections(
        _.addEndpoints(SequencerAlias.Default, conn1)
      )

      mediator1.sequencer_connection.get() shouldBe Some(
        SequencerConnections.single(SequencerConnection.merge(Seq(conn2, conn1)).value)
      )
      participant1.health.ping(participant2, timeout = 30.seconds)
    }

    "participant 3 can eventually change the connection to sequencer 2" in { implicit env =>
      import env.*

      modifyConnection(participant3, sequencer1.name, sequencer2.sequencerConnection)
      participant3.health.ping(participant1, timeout = 30.seconds)
    }

    "domain manager can change sequencer connection" in { implicit env =>
      import env.*

      val conn1 = sequencer1.sequencerConnection
      val conn2 = sequencer2.sequencerConnection
      val mergedConn = SequencerConnection
        .merge(Seq(sequencer1, sequencer2).map(_.sequencerConnection))
        .value

      domainManager1.sequencer_connection.get() shouldBe Some(SequencerConnections.single(conn1))

      domainManager1.sequencer_connection.modify_connections(
        _.addEndpoints(SequencerAlias.Default, conn2)
      )
      domainManager1.sequencer_connection.get() shouldBe Some(
        SequencerConnections.single(mergedConn)
      )
      assertDomainManagerCanSequenceMessages()

      domainManager1.sequencer_connection.set(SequencerConnections.single(conn2))
      domainManager1.sequencer_connection.get() shouldBe Some(SequencerConnections.single(conn2))
      assertDomainManagerCanSequenceMessages()
    }

    "cannot change to an invalid connection" in { implicit env =>
      import env.*

      val invalidConnection =
        GrpcSequencerConnection(
          NonEmpty(Seq, Endpoint("fake-host", Port.tryCreate(100))),
          false,
          None,
          SequencerAlias.Default,
        )

      val conn = mediator1.sequencer_connection.get()

      loggerFactory.suppressWarningsAndErrors {
        // trying to set the connection to an invalid one will fail the sequencer handshake step
        a[CommandFailure] should be thrownBy mediator1.sequencer_connection.set(
          SequencerConnections.single(invalidConnection)
        )
      }

      // the previous connection details should not have been changed in this case
      mediator1.sequencer_connection.get() shouldBe conn

      // everything still works
      participant1.health.ping(participant2, timeout = 30.seconds)
    }

  }
}
