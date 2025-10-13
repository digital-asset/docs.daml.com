// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.security.kms

import better.files.File
import com.digitalasset.canton.annotations.UnstableTest
import com.digitalasset.canton.config.RequireTypes.PositiveInt
import com.digitalasset.canton.console.ParticipantReference
import com.digitalasset.canton.console.commands.DomainChoice
import com.digitalasset.canton.examples.java.IouSyntax
import com.digitalasset.canton.integration.ConfigTransforms
import com.digitalasset.canton.integration.integration.ConfigTransform
import com.digitalasset.canton.integration.plugins.{
  ContinuityConfig,
  ExtraConfig,
  RunVersion,
  UseExternalProcessContinuity,
}
import com.digitalasset.canton.integration.tests.security.kms.KmsMigrationWithNewNamespaceIntegrationTest.{
  exportImportAcs,
  reCreateParties,
}
import com.digitalasset.canton.integration.tests.security.kms.gcp.GcpKmsCryptoIntegrationTestBase
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  EnterpriseTestConsoleEnvironment,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.time.DelegatingSimClock
import com.digitalasset.canton.topology.{DomainId, Identifier, PartyId, UniqueIdentifier}
import com.digitalasset.canton.util.{ReleaseUtils, ResourceUtil}
import com.digitalasset.canton.version.{ProtocolVersion, ReleaseVersion}
import com.digitalasset.canton.{DomainAlias, HasExecutionContext}
import monocle.macros.syntax.lens.*

import scala.jdk.CollectionConverters.*

/** Test the active contracts migration from a non-KMS participant to a new KMS-participant by
  * rewriting the party identifiers in the active contracts. Currently only works with contracts created
  * with PV3 (unauthenticated contract ids).
  *
  * Environment:
  * p1: with KMS
  * p2: with JCE with KMS-aligned crypto schemes
  * p3: default crypto config (Tink, default schemes)
  *
  * da (domainManager1, etc.): with JCE using KMS-aligned schemes
  * acme (domainManager2, etc.): default crypto config (Tink, default schemes) WITH PROTOCOL VERSION 3
  *
  * NOTE: In this migration we allocate parties on the new KMS participant for each party on the existing participant
  * node, only keeping the display name the same, but the namespace of the
  * new parties will match the new KMS participant's namespace. It requires the old domain to be using Protocol Version
  * 3, in particular unauthenticated ContractIds.
  */
abstract class KmsMigrationWithNewNamespaceIntegrationTest(
    oldProtocolVersion: ProtocolVersion
) extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with KmsCryptoIntegrationTestBase
    with KmsMigrationTestBase
    with HasExecutionContext {

  // This release supports both ProtocolVersions 3 and 4
  private val Release_2_6_5 = ReleaseVersion.tryCreate("2.6.5")
  private lazy val binDir = ReleaseUtils.retrieve(Release_2_6_5).futureValue

  require(oldProtocolVersion == ProtocolVersion.v3 || oldProtocolVersion == ProtocolVersion.v4)

  private val oldParticipantConfig =
    s"""
         |canton {
         |  participants {
         |    $oldParticipantName {
         |      admin-api.port = 5032
         |      ledger-api.port = 5031
         |      storage {
         |        type = memory
         |      }
         |    }
         |  }
         |}
         |
         |""".stripMargin

  private val oldDmConfig =
    s"""
         |canton {
         |  domain-managers {
         |    $oldDmName {
         |      admin-api.port = 5026
         |      init.domain-parameters.protocol-version = 5 // mandatory parameter to be replaced afterwards with protocol version 3
         |      storage {
         |        type = memory
         |      }
         |    }
         |  }
         |}
         |
         |""".stripMargin

  /* We set the protocol version to 3 as an extra configuration to avoid errors during the parsing of the original
   * configuration file. If we set it to 3 directly in that file, Canton complains that the selected
   * protocol version is deprecated and cannot be used.
   */
  private def createExtraDomainConfig(protocolVersion: ProtocolVersion): ExtraConfig =
    ExtraConfig.With(
      s"canton.domain-managers.$oldDmName.init.domain-parameters.protocol-version=${protocolVersion.toProtoPrimitiveS}",
      // suppresses warning as it is unhelpful when trying to analyse an issue in the logs
      s"canton.domain-managers.$oldDmName.init.domain-parameters.dont-warn-on-deprecated-pv=true",
    )

  private val oldSequencerConfig =
    s"""
         |canton {
         |  sequencers {
         |    $oldSequencerName.sequencer.type = database
         |  }
         |}
         |
         |""".stripMargin

  private val oldMediatorConfig =
    s"""
         |canton {
         |  mediators {
         |    $oldMediatorName { }
         |  }
         |}
         |
         |""".stripMargin

  private val external =
    new UseExternalProcessContinuity(
      loggerFactory,
      extParsAndConfigs = Map(
        oldParticipantName -> File.newTemporaryFile().write(oldParticipantConfig)
      ),
      externalManagersAndConfigs = Map(oldDmName -> File.newTemporaryFile().write(oldDmConfig)),
      externalSequencersAndConfigs =
        Map(oldSequencerName -> File.newTemporaryFile().write(oldSequencerConfig)),
      externalMediatorsAndConfigs =
        Map(oldMediatorName -> File.newTemporaryFile().write(oldMediatorConfig)),
      fileNameHint = this.getClass.getSimpleName,
    )
  registerPlugin(external)

  private def createRunConfig(
      config: String,
      nodeName: String,
      extraConfigArgs: ExtraConfig = ExtraConfig.Empty,
  ) =
    ContinuityConfig(
      nodeName,
      RunVersion.Release(binDir),
      extraConfigArgs,
      Some(external.newFile(nodeName, config)),
    )

  private val oldDmRunConfig = createRunConfig(
    oldDmConfig,
    oldDmName,
    createExtraDomainConfig(oldProtocolVersion),
  )
  private val oldSequencerRunConfig = createRunConfig(
    oldSequencerConfig,
    oldSequencerName,
  )
  private val oldMediatorRunConfig = createRunConfig(
    oldMediatorConfig,
    oldMediatorName,
  )
  private val oldParticipantRunConfig = createRunConfig(
    oldParticipantConfig,
    oldParticipantName,
  )

  private val oldNodesConfigs =
    Seq(oldDmRunConfig, oldSequencerRunConfig, oldMediatorRunConfig, oldParticipantRunConfig)

  override protected val extraConfiguration: Option[ConfigTransform] = Some({
    val extraConfig = ConfigTransforms.useStaticTime
    // for protocol version 3, we need to allow for unauthenticated contract ids in the new participant since
    // the contract ids in the old participant are not authenticated
    if (oldProtocolVersion == ProtocolVersion.v3)
      extraConfig.compose(
        ConfigTransforms.updateParticipantConfig(newParticipantName)(
          _.focus(_.parameters.allowForUnauthenticatedContractIds).replace(true)
        )
      )
    else extraConfig
  })

  private var partyIdsOldToPartyIdsNew: Map[PartyId, PartyId] = Map.empty

  s"migrate old non-KMS ${oldProtocolVersion.toProtoPrimitiveS} participant to new KMS ${testedProtocolVersion.toProtoPrimitiveS} participant" +
    s" with a new namespace" can {
      "setup domain to migrate from" in { implicit env =>
        import env.*

        val participantNew = p(newParticipantName)

        oldNodesConfigs.foreach(external.start)

        val domainManagerOld = rdm(oldDmName)
        val sequencerOld = rs(oldSequencerName)
        val mediatorOld = rm(oldMediatorName)
        val participantOld = rp(oldParticipantName)
        val remoteDomainNodes = Seq(domainManagerOld, sequencerOld, mediatorOld)

        remoteDomainNodes.foreach(_.health.wait_for_running())
        domainManagerOld.setup.bootstrap_domain(Seq(sequencerOld), Seq(mediatorOld))
        remoteDomainNodes.foreach(_.health.wait_for_initialized())

        participantOld.health.wait_for_running()
        participantOld.health.wait_for_initialized()

        participantOld.domains.connect_single(
          oldDomainAlias,
          sequencerOld.sequencerConnection,
        )

        participantNew.dars.upload(CantonExamplesPath)
        participantOld.dars.upload(CantonExamplesPath)

        val alice = participantOld.parties.enable("Alice", waitForDomain = DomainChoice.All)
        val bob = participantOld.parties.enable("Bob", waitForDomain = DomainChoice.All)

        // Create some contract for alice and bob on the oldParticipant
        val (obligor, owner, participant) = (alice, bob, participantOld)
        val contract = IouSyntax.testIou(obligor, owner)
        participant.ledger_api.javaapi.commands
          .submit_flat(Seq(obligor), contract.create.commands.asScala.toSeq)

      }

      "re-create Alice/Bob on new participant" in { implicit env =>
        import env.*

        val participantNew = p(newParticipantName)
        val participantOld = p(oldParticipantName)

        partyIdsOldToPartyIdsNew = reCreateParties(
          participantNew,
          participantOld,
          participantOld.uid,
          oldDomainAlias,
        )

        val namespaceNew = participantNew.id.uid.namespace
        val namespaceOld = participantOld.id.uid.namespace

        partyIdsOldToPartyIdsNew
          .map { case (pOld, pNew) => pOld.toLf -> pNew.toLf } shouldBe Map[String, String](
          UniqueIdentifier(Identifier.tryCreate("Alice"), namespaceOld).toProtoPrimitive ->
            UniqueIdentifier(Identifier.tryCreate("Alice"), namespaceNew).toProtoPrimitive,
          UniqueIdentifier(Identifier.tryCreate("Bob"), namespaceOld).toProtoPrimitive ->
            UniqueIdentifier(Identifier.tryCreate("Bob"), namespaceNew).toProtoPrimitive,
        )
      }

      "migrate DARs" in { implicit env =>
        import env.*

        val participantNew = p(newParticipantName)
        val participantOld = p(oldParticipantName)

        // user-manual-entry-begin: KmsMigrateDarsNewNs
        // Migrate DARs from old to new participant
        utils.migrate_dars(participantOld, participantNew)
      // user-manual-entry-end: KmsMigrateDarsNewNs
      }

      "export and import ACS for Alice/Bob" in { implicit env =>
        import env.*

        val participantOld = p(oldParticipantName)
        val participantNew = p(newParticipantName)

        val aliceOld = participantOld.parties.find("Alice")
        val bobOld = participantOld.parties.find("Bob")

        exportImportAcs(
          p(newParticipantName),
          participantOld,
          dm(newDmName).id,
          partyIdsOldToPartyIdsNew,
          testedProtocolVersion,
          env.environment.simClock.value,
          () => external.stop(oldParticipantRunConfig),
          withContractIdRemap = false,
        )

        val aliceP1 = participantNew.parties.find("Alice")
        val bobP1 = participantNew.parties.find("Bob")

        aliceP1 should not equal aliceOld
        bobP1 should not equal bobOld

        eventually() {
          participantNew.ledger_api.acs.of_party(aliceP1) should not be empty
          participantNew.ledger_api.acs.of_party(bobP1) should not be empty
        }

        participantNew.health.ping(participant2)
      }

      migratedEnvTest()
    }
}

object KmsMigrationWithNewNamespaceIntegrationTest {

  def reCreateParties(
      participantNew: ParticipantReference,
      participantOld: ParticipantReference,
      participantOldUid: UniqueIdentifier,
      oldDomainAlias: DomainAlias,
  )(implicit env: EnterpriseTestConsoleEnvironment): Map[PartyId, PartyId] = {
    import env.*

    // user-manual-entry-begin: KmsRecreatePartiesInNewParticipantNewNs

    /* Disconnect the old participant from the old domain to avoid new parties or contracts being created
     * Make sure domain and the old participant are quiet before exporting the parties or the ACS
     */
    participantOld.domains.disconnect(oldDomainAlias)

    // Determine all parties hosted on the old participants, except for admin parties
    val partiesOld =
      participantOld.ledger_api.parties
        .list()
        .filter(party =>
          party.party.toProtoPrimitive != participantOldUid.toProtoPrimitive && party.isLocal
        )

    /* Allocate new parties on the new participant with the same name and
     * display name as on the old participant, but in the namespace of the
     * new participant
     */
    val partyIdsOldToPartyIdsNew = partiesOld.map { partyDetailsOld =>
      val oldParty = partyDetailsOld.party
      val partyId =
        participantNew.ledger_api.parties
          .allocate(oldParty.uid.id.toProtoPrimitive, partyDetailsOld.displayName)
          .party
      oldParty -> partyId
    }.toMap
    // user-manual-entry-end: KmsRecreatePartiesInNewParticipantNewNs

    utils.synchronize_topology()

    partyIdsOldToPartyIdsNew
  }

  def exportImportAcs(
      participantNew: ParticipantReference,
      participantOld: ParticipantReference,
      newKmsDomainId: DomainId,
      partyIdsOldToPartyIdsNew: Map[PartyId, PartyId],
      newProtocolVersion: ProtocolVersion,
      clock: DelegatingSimClock,
      stopOldParticipant: () => Unit,
      withContractIdRemap: Boolean,
  )(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*

    // user-manual-entry-begin: KmsMigrateACSofPartiesNewNs
    // Export the acs of the old participant
    val acsOld = participantOld.ledger_api.acs.of_all(
      limit = PositiveInt.MaxValue,
      includeCreatedEventBlob = true,
    )

    // Connect new participant to the new sequencer
    participantNew.domains.reconnect_all()

    /* Create traffic on the new participant so that the repair commands will
     * pick an identity snapshot that is aware of all party allocations
     */
    participantNew.health.ping(participantNew.id)

    // Disconnect new participants from the domain to be able to import the ACS
    participantNew.domains.disconnect_all()

    // Pick a ledger create time according to the domain's clock.
    val ledgerCreateTime = clock.now.toInstant

    // Switch the ACS to be based on the new party ids.
    val participantNewACS = utils.change_contracts_party_ids(
      partyIdsOldToPartyIdsNew,
      acsOld,
      newKmsDomainId,
      ledgerCreateTime,
      newProtocolVersion,
      withContractIdRemap,
    )

    // Upload ACS to new participants
    File.temporaryFile(prefix = s"migration-${participantNew.name}", suffix = "gz") { tempFile =>
      val outputStream = tempFile.newGzipOutputStream()
      ResourceUtil.withResource(outputStream)(s => participantNewACS.foreach(_.writeDelimitedTo(s)))
      outputStream.flush()
      val partiesHostedOnParticipantNew = partyIdsOldToPartyIdsNew.values.toSet
      participantNew.repair.import_acs(tempFile.canonicalPath, partiesHostedOnParticipantNew)
    }

    // Kill/stop the old participant
    stopOldParticipant()

    // Connect the new participant to the new domain
    participantNew.domains.reconnect_all()
    // user-manual-entry-end: KmsMigrateACSofPartiesNewNs
  }

}

@UnstableTest
class GcpKmsPV3MigrationWithNewNamespaceIntegrationTest
    extends KmsMigrationWithNewNamespaceIntegrationTest(ProtocolVersion.v3)
    with GcpKmsCryptoIntegrationTestBase
