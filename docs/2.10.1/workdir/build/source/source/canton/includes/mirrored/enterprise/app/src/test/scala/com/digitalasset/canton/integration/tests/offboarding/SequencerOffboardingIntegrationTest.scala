// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.offboarding

import com.daml.nonempty.NonEmpty
import com.digitalasset.canton.config.CantonRequireTypes.String255
import com.digitalasset.canton.config.EnterpriseDbConfig
import com.digitalasset.canton.crypto.admin.grpc.PrivateKeyMetadata
import com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition
import com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition.{
  distributedSingleDomainWithMultipleDbSequencers,
  distributedSingleDomainWithTwoSequencers,
}
import com.digitalasset.canton.integration.plugins.{
  UsePostgres,
  UseReferenceBlockSequencer,
  UseSharedStorage,
}
import com.digitalasset.canton.integration.tests.sequencer.{SequencerTestUtils, reference}
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.participant.domain.DomainConnectionConfig
import com.digitalasset.canton.sequencing.{SequencerConnection, SequencerConnections}
import com.digitalasset.canton.topology.transaction.TopologyChangeOp
import com.digitalasset.canton.{DomainAlias, SequencerAlias}

import scala.concurrent.duration.DurationInt

abstract class SequencerOffboardingIntegrationTest(val name: String)
    extends EnterpriseIntegrationTest
    with SequencerTestUtils
    with SharedEnterpriseEnvironment {

  s"using an environment with 2 $name sequencer nodes and a domain configured with both" should {

    "bootstrap domain with multiple sequencers and " +
      "have participants connected to different sequencers be able to ping" in { implicit env =>
        import env.*

        domainManager1.setup.bootstrap_domain(Seq(sequencer1, sequencer2), Seq(mediator1))

        mediator1.health.initialized() shouldBe true
        sequencer1.health.initialized() shouldBe true
        sequencer2.health.initialized() shouldBe true

        participant1.domains.connect_local(sequencer1)
        participant2.domains.connect_local(sequencer2)

        participant1.health.ping(participant2, timeout = 30.seconds)
      }

    "mediator can switch to sequencer1 only" in { implicit env =>
      import env.*

      // needed to prevent the mediator from getting a tombstone on re-connection reading the last message
      participant1.health.ping(participant2, timeout = 30.seconds)

      val mergedConn = SequencerConnection
        .merge(Seq(sequencer1, sequencer2).map(_.sequencerConnection))
        .value
      mediator1.sequencer_connection.get() shouldBe Some(SequencerConnections.single(mergedConn))

      // user-manual-entry-begin: SequencerOffboardingSwitchAwayMediator
      val conn1 = sequencer1.sequencerConnection
      mediator1.sequencer_connection.set(SequencerConnections.single(conn1))
      // user-manual-entry-end: SequencerOffboardingSwitchAwayMediator

      mediator1.sequencer_connection.get() shouldBe Some(SequencerConnections.single(conn1))

      participant1.health.ping(participant2, timeout = 30.seconds)
    }

    "domain manager can switch to sequencer1 only" in { implicit env =>
      import env.*

      val mergedConn = SequencerConnection
        .merge(Seq(sequencer1, sequencer2).map(_.sequencerConnection))
        .value

      domainManager1.sequencer_connection.get() shouldBe Some(
        SequencerConnections.single(mergedConn)
      )

      // user-manual-entry-begin: SequencerOffboardingSwitchAwayDomainManager
      val conn1 = sequencer1.sequencerConnection
      domainManager1.sequencer_connection.set(conn1)
      // user-manual-entry-end: SequencerOffboardingSwitchAwayDomainManager

      domainManager1.sequencer_connection.get() shouldBe Some(
        SequencerConnections.single(conn1)
      )

      assertDomainManagerCanSequenceMessages()
    }

    "participant 2 can switch to sequencer 1 only" in { implicit env =>
      import env.*

      val domainAlias = sequencer2.name
      val domainAlias255 = String255.tryCreate(domainAlias)

      participant2.domains.list_registered() should matchPattern {
        case Seq(
              (
                DomainConnectionConfig(
                  DomainAlias(`domainAlias255`),
                  SequencerConnections(aliasToConnection, _),
                  _,
                  _,
                  _,
                  _,
                  _,
                  _,
                ),
                true,
              )
            )
            if aliasToConnection == NonEmpty(
              Map,
              SequencerAlias.tryCreate("DefaultSequencer") -> sequencer2.sequencerConnection,
            ) =>
      }

      // user-manual-entry-begin: SequencerOffboardingSwitchAwayParticipant
      participant2.domains.disconnect(domainAlias)
      participant2.domains.modify(
        domainAlias,
        _.copy(sequencerConnections = SequencerConnections.single(sequencer1.sequencerConnection)),
      )
      participant2.domains.reconnect(domainAlias)
      // user-manual-entry-end: SequencerOffboardingSwitchAwayParticipant

      participant1.health.ping(participant2, timeout = 30.seconds)
    }

    "sequencer 2 can be off-boarded" in { implicit env =>
      import env.*

      // TODO(#22509) Introduce a single off-boarding command
      // user-manual-entry-begin: SequencerOffboardingRemoveExclusiveKeys
      def keyIdAndPurpose(privateKeyMetadata: PrivateKeyMetadata) =
        (privateKeyMetadata.id, privateKeyMetadata.purpose)

      val sequencer2KeyIdsAndPurposes = sequencer2.keys.secret.list().map(keyIdAndPurpose)
      val sequencer2ExclusiveKeyIdsAndPurposes =
        sequencer2KeyIdsAndPurposes.toSet.diff(
          sequencers.all
            .filter(_.name != sequencer2.name)
            .flatMap(_.keys.secret.list())
            .map(
              keyIdAndPurpose
            )
            .toSet
        )
      sequencer2ExclusiveKeyIdsAndPurposes.foreach { case (keyId, keyPurpose) =>
        domainManager1.topology.owner_to_key_mappings
          .authorize(
            TopologyChangeOp.Remove,
            sequencer2.id,
            keyId,
            keyPurpose,
          )
      }

      // Avoids error logs in the decommissioned sequencer that are to be expected but may be confusing
      sequencer2.stop()

      // The increased timeout is needed here: once the sequencer is stopped, the other sequencers
      //  need a bit of time to mark it as offline.
      participant1.health.ping(participant2, timeout = 30.seconds)

      // The sequencer and the locally stored cryptographic material can now be disposed of
      // user-manual-entry-end: SequencerOffboardingRemoveExclusiveKeys

      assertDomainManagerCanSequenceMessages()
    }
  }
}

class PostgresSequencerOffboardingIntegrationTest
    extends SequencerOffboardingIntegrationTest("Postgres") {

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    distributedSingleDomainWithMultipleDbSequencers

  registerPlugin(new UsePostgres(loggerFactory))

  registerPlugin(
    UseSharedStorage.forSequencers(
      "sequencer1",
      Seq("sequencer2", "sequencer3", "sequencer4"),
      loggerFactory,
    )
  )
}

class ReferenceBlockSequencerOffboardingIntegrationTest
    extends SequencerOffboardingIntegrationTest(reference.DriverName) {

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    distributedSingleDomainWithTwoSequencers

  private lazy val plugin: UseReferenceBlockSequencer[EnterpriseDbConfig.Postgres] =
    reference.createPlugin[EnterpriseDbConfig.Postgres](loggerFactory)

  registerPlugin(plugin)
  registerPlugin(new UsePostgres(loggerFactory))
}
