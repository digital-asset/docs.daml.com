// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.security.kms

import better.files.File
import com.digitalasset.canton.integration.tests.security.kms.aws.AwsKmsCryptoIntegrationTestBase
import com.digitalasset.canton.integration.tests.security.kms.gcp.GcpKmsCryptoIntegrationTestBase
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.topology.transaction.TopologyChangeOp

/** Test the active contracts migration from a non-KMS participant to a new KMS-participant by moving the
  * old namespace delegation to the new participant (thus maintaining its identity)
  * and exporting/importing the active contracts. Currently only works if
  * the old non-KMS participant supports the PV of the new KMS participant, and you
  * specify the target PV on the topology transaction during export.
  *
  * Environment:
  * p1: with KMS
  * p2: with JCE with KMS-aligned crypto schemes
  * p3: default crypto config (Tink, default schemes)
  *
  * da (domainManager1, etc.): with JCE using KMS-aligned schemes
  * acme (domainManager2, etc.): default crypto config (Tink, default schemes) WITH THE SAME PROTOCOL VERSION as da
  *
  * NOTE: In this migration we are able to keep the old namespace by delegating
  * the namespace of the old participant to a new participant that makes use of a KMS. However, this requires
  * saving the old root namespace key offline to allow for future domain upgrades, since these upgrades require
  * the signing of the topology requests with the root namespace key. We assume that the Protocol Version
  * of the new domain is supported by the old domain (in this case it matches).
  */
trait KmsMigrationWithSameNamespaceIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with KmsCryptoIntegrationTestBase
    with KmsMigrationTestBase {

  override protected val environmentConfigs: List[String] = List(
    "distributed-two-domains-three-participants-topology.conf"
  )

  s"migrate non-KMS participant to new KMS participant with the same namespace" must {
    setupLocalEnvTest()

    "setup namespace delegation" in { implicit env =>
      import env.*

      val participantOld = p(oldParticipantName)
      val participantNew = p(newParticipantName)

      // user-manual-entry-begin: KmsSetupNamespaceDelegationSameNs
      val namespaceOld = participantOld.uid.namespace.fingerprint
      val namespaceNew = participantNew.uid.namespace.fingerprint

      val rootNamespaceDelegationOld = participantOld.topology.namespace_delegations
        .list(filterNamespace = namespaceOld.toProtoPrimitive)
        .head
        .context
        .serialized

      val namespaceKeyNew = participantNew.keys.public.download(namespaceNew)
      participantOld.keys.public.upload(namespaceKeyNew, Some("pNew-namespace-key"))

      // Delegate namespace of old participant to new participant
      val delegation = participantOld.topology.namespace_delegations.authorize(
        ops = TopologyChangeOp.Add,
        namespace = namespaceOld,
        authorizedKey = namespaceNew,
      )

      participantNew.topology.load_transaction(rootNamespaceDelegationOld)
      participantNew.topology.load_transaction(delegation)
    // user-manual-entry-end: KmsSetupNamespaceDelegationSameNs
    }

    "re-create Alice/Bob on new participant" in { implicit env =>
      import env.*

      val participantOld = p(oldParticipantName)
      val participantNew = p(newParticipantName)

      val newDomainAlias = s(newSequencerName).name

      // user-manual-entry-begin: KmsRecreatePartiesInNewParticipantSameNs

      /* Disconnect the old participant from the old domain to avoid new parties or contracts being created
       * Make sure domain and the old participant are quiet before exporting the parties or the ACS
       */
      participantOld.domains.disconnect(oldDomainAlias)

      // Disconnect from new KMS-compatible domain to prepare migration of parties and contracts
      participantNew.domains.disconnect(newDomainAlias)

      // Determine all parties hosted on the old participants, except for admin parties
      val parties = participantOld.ledger_api.parties
        .list()
        .filter(party =>
          party.party.toProtoPrimitive != participantOld.uid.toProtoPrimitive && party.isLocal
        )
        .map(_.party)

      parties.foreach { party =>
        participantNew.topology.party_to_participant_mappings
          .authorize(ops = TopologyChangeOp.Add, party = party, participant = participantNew.id)
      }
    // user-manual-entry-end: KmsRecreatePartiesInNewParticipantSameNs

    }

    "migrate DARs" in { implicit env =>
      import env.*

      val participantNew = p(newParticipantName)
      val participantOld = p(oldParticipantName)

      // user-manual-entry-begin: KmsMigrateDarsSameNs
      // Migrate DARs from old to new participant
      utils.migrate_dars(participantOld, participantNew)
    // user-manual-entry-end: KmsMigrateDarsSameNs
    }

    "export and import ACS for Alice/Bob" in { implicit env =>
      import env.*

      val participantOld = lp(oldParticipantName)
      val participantNew = p(newParticipantName)

      val aliceOld = participantOld.parties.find("Alice")
      val bobOld = participantOld.parties.find("Bob")

      val oldDomainManager = dm(oldDmName)
      val newKmsDomainManager = dm(newDmName)

      val newKmsDomainAlias = s(newSequencerName).name

      val oldDomainId = oldDomainManager.id
      val newKmsDomainId = newKmsDomainManager.id

      // user-manual-entry-begin: KmsMigrateACSofPartiesSameNs
      val parties = participantOld.ledger_api.parties
        .list()
        .filter(party =>
          party.party.toProtoPrimitive != participantOld.uid.toProtoPrimitive && party.isLocal
        )
        .map(_.party)

      // There should be no conflicts between the protocol version of the old domain and the new domain
      val protocolVersion = newKmsDomainManager.config.init.domainParameters.initialProtocolVersion

      File.usingTemporaryFile("participantOld-acs", suffix = ".txt") { acsFile =>
        val acsFileName = acsFile.toString

        // Export from old participant
        participantOld.repair.export_acs(
          parties = parties.toSet,
          outputFile = acsFileName,
          contractDomainRenames = Map(oldDomainId -> (newKmsDomainId, protocolVersion)),
          partiesOffboarding = false,
        )

        // Import to new participant
        participantNew.repair.import_acs(acsFileName, parties.toSet)
      }

      // Kill/stop the old participant
      participantOld.stop()

      // Connect the new participant to the new domain
      participantNew.domains.reconnect(newKmsDomainAlias)
      // user-manual-entry-end: KmsMigrateACSofPartiesSameNs

      val aliceP1 = participantNew.parties.find("Alice")
      val bobP1 = participantNew.parties.find("Bob")

      aliceP1 shouldEqual aliceOld
      bobP1 shouldEqual bobOld

      eventually() {
        participantNew.ledger_api.acs.of_party(aliceP1) should not be empty
        participantNew.ledger_api.acs.of_party(bobP1) should not be empty
      }

      participantNew.health.ping(participant2)
    }

    migratedEnvTest()
  }
}

class AwsKmsMigrationWithSameNamespaceIntegrationTest
    extends KmsMigrationWithSameNamespaceIntegrationTest
    with AwsKmsCryptoIntegrationTestBase

class GcpKmsMigrationWithSameNamespaceIntegrationTest
    extends KmsMigrationWithSameNamespaceIntegrationTest
    with GcpKmsCryptoIntegrationTestBase
