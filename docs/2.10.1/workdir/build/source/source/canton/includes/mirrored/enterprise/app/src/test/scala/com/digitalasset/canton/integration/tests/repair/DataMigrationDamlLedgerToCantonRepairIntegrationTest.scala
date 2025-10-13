// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.repair

import cats.syntax.either.*
import com.daml.ledger.api.v1.admin.party_management_service.PartyDetails
import com.daml.ledger.api.v1.event.CreatedEvent
import com.daml.ledger.javaapi.data.Transaction
import com.digitalasset.canton.BigDecimalImplicits.*
import com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent
import com.digitalasset.canton.admin.api.client.commands.{GrpcAdminCommand, LedgerApiCommands}
import com.digitalasset.canton.admin.api.client.data.TemplateId
import com.digitalasset.canton.config.RequireTypes.{Port, PositiveInt}
import com.digitalasset.canton.config.{
  ClientConfig,
  InitConfigBase,
  NonNegativeDuration,
  TlsClientConfig,
}
import com.digitalasset.canton.console.{
  ConsoleEnvironment,
  FeatureFlag,
  LocalParticipantReference,
  ParticipantReference,
}
import com.digitalasset.canton.examples.java.{iou, paint}
import com.digitalasset.canton.integration.*
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  EnterpriseTestConsoleEnvironment,
  HasIdentityStateCopy,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.logging.SuppressingLogger.LogEntryOptionality
import com.digitalasset.canton.participant.ledger.api.client.ValueRemapper
import com.digitalasset.canton.participant.pruning.AcsCommitmentProcessor.Errors
import com.digitalasset.canton.topology.{PartyId, SafeSimpleString}
import com.digitalasset.canton.util.EntitySyntax
import com.digitalasset.canton.{HasExecutionContext, LfPartyId}
import io.grpc.stub.AbstractStub
import monocle.macros.syntax.lens.*

import java.util.concurrent.atomic.AtomicReference
import scala.jdk.CollectionConverters.*

trait DataMigrationDamlLedgerToCantonRepairIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with EntitySyntax[EnterpriseTestConsoleEnvironment]
    with HasExecutionContext
    with HasIdentityStateCopy
    with RepairTestUtil {

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.multiDomain
      .addConfigTransform(
        ConfigTransforms.updateDomainConfig("acme")(
          _.focus(_.init.identity).replace(Some(InitConfigBase.Identity()))
        )
      )
      .addConfigTransform(ConfigTransforms.enableAdvancedCommands(FeatureFlag.Repair))

  override val defaultParticipant: String = "participant4"

  private val houseOwners = Seq("Alice", "Bob", "Carol", "Dylan")
  private val painters = Seq("Kahlo", "OKeeffe", "Renoir", "vanGogh")
  private val banks = Seq("Citi", "PostFinance")

  // expected counts based on each painter making an offer to each house owner once for each bank
  private val paintOffersPerHouseOwner = painters.size * banks.size
  private val paintOffersPerPainter = houseOwners.size * banks.size
  // expected iou counts: each house owner has one iou spread equally over the banks
  private val iousPerBank = houseOwners.size / banks.size

  private val acsFromOtherDamlLedger = new AtomicReference[Seq[CreatedEvent]](Seq.empty)

  "Initialize a source daml ledger and export contracts via ledger api" in { implicit env =>
    import env.*
    val exportLedger = participant4

    exportLedger.domains.connect_local(da)
    exportLedger.dars.upload(CantonExamplesPath)

    (houseOwners ++ painters ++ banks).foreach(party =>
      exportLedger.ledger_api.parties.allocate(party, party)
    )

    for {
      houseOwner <- houseOwners
      painter <- painters
      bank <- banks
    } yield mayIPaintYourHouse(
      painter.toPartyId(),
      houseOwner.toPartyId(),
      bank.toPartyId(),
      exportLedger,
    )

    houseOwners.zip(banks ++ banks).foreach { case (houseOwner, bank) =>
      createIou(bank.toPartyId(), houseOwner.toPartyId(), exportLedger)
    }

    val expectedCounts: Map[PartyId, Int] =
      (houseOwners.map(_.toPartyId() -> (paintOffersPerHouseOwner + 1)) // plus one iou
        ++ painters.map(_.toPartyId() -> paintOffersPerPainter)
        ++ banks.map(_.toPartyId() -> iousPerBank)).toMap

    assertAcsCounts((exportLedger, expectedCounts))

    // From here on disconnect from the "da" domain to freeze the export source daml ledger.
    exportLedger.domains.disconnect("da")
    exportLedger.domains.list_connected() shouldBe Nil

    // user-manual-entry-begin: ExportAcs
    val acs =
      queryActiveContractsFromDamlLedger(
        exportLedger.config.ledgerApi.address,
        exportLedger.config.ledgerApi.port,
        TemplateId
          .templateIdsFromJava(
            iou.Iou.TEMPLATE_ID_WITH_PACKAGE_ID,
            paint.OfferToPaintHouseByPainter.TEMPLATE_ID_WITH_PACKAGE_ID,
          ),
        exportLedger.config.ledgerApi.tls.map(_.clientConfig),
      )

    val acsExported = removeCantonSpecifics(acs).toList
    // user-manual-entry-end: ExportAcs

    // "Generalize" events from canton to not look like they originated from a canton ledger, i.e. not to include
    // canton-specific suffixes in party ids. This helps demonstrate that we can import contracts from
    // non-canton ledger types such as the daml sandbox.
    acsFromOtherDamlLedger.set(acsExported)
  }

  "Adapt and import contracts into canton participants via repair.add" in { implicit env =>
    import env.*

    val acsExported = acsFromOtherDamlLedger.get
    val darPath = CantonExamplesPath
    val importLedgerDomain = acme
    val consoleEnvironment = env

    // user-manual-entry-begin: PrepareImport
    // Decide on which canton participants to host which parties along with their contracts.
    // We place house owners, painters, and banks on separate participants.
    val participants = Seq(participant1, participant2, participant3)
    val partyAssignments =
      Seq(participant1 -> houseOwners, participant2 -> painters, participant3 -> banks)

    // Connect to domain prior to uploading dars and parties.
    participants.foreach { participant =>
      participant.domains.connect_local(importLedgerDomain)
      participant.dars.upload(darPath)
    }

    // Create canton party ids and remember mapping of plain to canton party ids.
    val toCantonParty: Map[String, String] =
      partyAssignments.flatMap { case (participant, parties) =>
        val partyMappingOnParticipant = parties.map { party =>
          participant.ledger_api.parties.allocate(party, party)
          party -> lookUpPartyId(participant, party).toLf
        }
        partyMappingOnParticipant
      }.toMap

    // Create traffic on all participants so that the repair commands will pick an identity snapshot that is aware of
    // all party allocations
    participants.foreach { participant =>
      participant.health.ping(participant, workflowId = importLedgerDomain.name)
    }

    // Switch the ACS to be based on canton party ids.
    val acsToImportToCanton =
      acsExported.map(ValueRemapper.convertEvent(identity, toCantonParty(_)))
    // user-manual-entry-end: PrepareImport

    // user-manual-entry-begin: ImportAcs
    // Disconnect from domain temporarily to allow import to be performed.
    participants.foreach(_.domains.disconnect(importLedgerDomain.name))

    // Pick a ledger create time according to the domain's clock.
    val ledgerCreateTime =
      consoleEnvironment.environment.domains
        .getRunning(importLedgerDomain.name)
        .getOrElse(throw new IllegalArgumentException("No running domain node"))
        .clock
        .now
        .toInstant

    // Specify protocol version used in the installation e.g. com.digitalasset.canton.version.ProtocolVersion.latest
    val protocolVersion = testedProtocolVersion

    val contractsWithRecomputedContractIds =
      utils
        .recompute_contract_ids(
          participant1,
          acsToImportToCanton.view
            .map(WrappedCreatedEvent)
            .map { event =>
              utils.contract_data_to_instance(event.toContractData, ledgerCreateTime)
            }
            .toSeq,
          protocolVersion,
        )
        ._1

    val createdEventsAndContractsToImport =
      acsToImportToCanton zip contractsWithRecomputedContractIds

    // Filter active contracts based on participant parties and upload.
    partyAssignments.foreach { case (participant, rawParties) =>
      val parties = rawParties.map(toCantonParty(_))
      val participantAcs = createdEventsAndContractsToImport.collect {
        case (event, contract)
            if event.signatories.intersect(parties).nonEmpty
              || event.observers.intersect(parties).nonEmpty
              || event.witnessParties.intersect(parties).nonEmpty =>
          repairContract(contract)
      }

      participant.repair.add(importLedgerDomain.name, participantAcs, ignoreAlreadyAdded = false)
    }

    // user-manual-entry-end: ImportAcs

    def verifyActiveContractCounts() =
      Map[LocalParticipantReference, (Boolean, Boolean)](
        participant1 -> ((true, true)),
        participant2 -> ((true, false)),
        participant3 -> ((false, true)),
      ).foreach { case (participant, (hostsPaintOfferStakeholder, hostsIouStakeholder)) =>
        val expectedCounts =
          (houseOwners.map { houseOwner =>
            houseOwner.toPartyId(participant) ->
              ((if (hostsPaintOfferStakeholder) paintOffersPerHouseOwner else 0)
                + (if (hostsIouStakeholder) 1 else 0))
          }
            ++ painters.map { painter =>
              painter.toPartyId(participant) -> (if (hostsPaintOfferStakeholder)
                                                   paintOffersPerPainter
                                                 else 0)
            }
            ++ banks.map { bank =>
              bank.toPartyId(participant) -> (if (hostsIouStakeholder) iousPerBank else 0)
            }).toMap[PartyId, Int]

        assertAcsCounts((participant, expectedCounts))
      }

    /*
      If the test fails because of Errors.MismatchError.NoSharedContracts error, it could be worth to
      extend the scope of the suppressing logger.
     */
    loggerFactory.assertLogsUnorderedOptional(
      {
        // Finally reconnect to the domain.
        // user-manual-entry-begin: ReconnectAfterImportAcs
        participants.foreach(_.domains.reconnect(importLedgerDomain.name))
        // user-manual-entry-end: ReconnectAfterImportAcs

        verifyActiveContractCounts()
      },
      /*
        Since P1 de/re-connect before P3, we may end up in the case where commitment
        sent by P1 is non-empty but local commitment computed by P3 is empty.
       */
      LogEntryOptionality.Optional -> (_.shouldBeCantonErrorCode(
        Errors.MismatchError.NoSharedContracts
      )),
    )
  }

  "Exercise contracts migrated to canton" in { implicit env =>
    import env.*

    // user-manual-entry-begin: UseImportedLedger
    def yesYouMayPaintMyHouse(
        houseOwner: PartyId,
        painter: PartyId,
        participant: ParticipantReference,
    ): Unit = {
      val iouContract = participant.ledger_api.javaapi.acs.await(iou.Iou.COMPANION)(houseOwner)
      val bank = iouContract.data.payer
      val paintProposal = participant.ledger_api.javaapi.acs
        .await(paint.OfferToPaintHouseByPainter.COMPANION)(
          houseOwner,
          pp => pp.data.painter == painter.toProtoPrimitive && pp.data.bank == bank,
        )
      val cmd = paintProposal.id
        .exerciseAcceptByOwner(iouContract.id)
        .commands
        .asScala
        .toSeq
      val _ = clue(
        s"$houseOwner accepts paint proposal by $painter financing through $bank"
      )(participant.ledger_api.javaapi.commands.submit(Seq(houseOwner), cmd))
    }

    // Have each house owner accept one of the paint offers to illustrate use of the imported ledger.
    houseOwners.zip(painters).foreach { case (houseOwner, painter) =>
      yesYouMayPaintMyHouse(
        lookUpPartyId(participant1, houseOwner),
        lookUpPartyId(participant1, painter),
        participant1,
      )
    }

    // Illustrate that acceptance of have resulted in
    {
      val paintHouseContracts = painters.map { painter =>
        participant2.ledger_api.javaapi.acs
          .await(paint.PaintHouse.COMPANION)(lookUpPartyId(participant2, painter))
      }
      assert(paintHouseContracts.size == 4)
    }
    // user-manual-entry-end: UseImportedLedger

    Map[LocalParticipantReference, (Boolean, Boolean, Boolean)](
      participant1 -> ((true, false, true)),
      participant2 -> ((true, true, false)),
      participant3 -> ((false, true, false)),
    ).foreach {
      case (
            participant,
            (hostsPaintOfferStakeholder, hostsIouStakeholder, hostsIouCreationWitness),
          ) =>
        val expectedCounts =
          (houseOwners.map { houseOwner =>
            houseOwner.toPartyId(participant) -> (if (hostsPaintOfferStakeholder)
                                                    paintOffersPerHouseOwner
                                                  else 0)
          }
            ++ painters.map { painter =>
              painter.toPartyId(participant) -> ((if (hostsPaintOfferStakeholder)
                                                    paintOffersPerPainter
                                                  else 0)
                + (if (hostsIouStakeholder || hostsIouCreationWitness) 1 else 0))
            }
            ++ banks.map { bank =>
              bank.toPartyId(participant) -> (if (hostsIouStakeholder || hostsIouCreationWitness)
                                                iousPerBank
                                              else 0)
            }).toMap[PartyId, Int]

        assertAcsCounts((participant, expectedCounts))
    }

    // also see if we can create new contracts
    clue("creating new iou for first painter")(
      createIou(
        banks.headOption.value.toPartyId(participant3),
        painters.headOption.value.toPartyId(participant3),
        participant3,
      )
    )
    clue("creating new iou for last painter")(
      createIou(
        banks.lastOption.value.toPartyId(participant3),
        painters.lastOption.value.toPartyId(participant3),
        participant3,
      )
    )
  }

  private def createIou(
      payer: PartyId,
      owner: PartyId,
      participant: ParticipantReference,
  ): iou.Iou.ContractId =
    createContract(participant, payer, owner)

  private def mayIPaintYourHouse(
      painter: PartyId,
      houseOwner: PartyId,
      bank: PartyId,
      participant: ParticipantReference,
  ): Transaction =
    participant.ledger_api.javaapi.commands.submit_flat(
      Seq(painter),
      new paint.OfferToPaintHouseByPainter(
        houseOwner.toProtoPrimitive,
        painter.toProtoPrimitive,
        bank.toProtoPrimitive,
        new iou.Amount(100.toBigDecimal, "USD"),
      ).create.commands.asScala.toSeq,
    )

  // user-manual-entry-begin: ImportHelperFunctions
  def queryActiveContractsFromDamlLedger(
      hostname: String,
      port: Port,
      templateFilter: Seq[TemplateId],
      tls: Option[TlsClientConfig],
      token: Option[String] = None,
  )(implicit consoleEnvironment: ConsoleEnvironment): Seq[CreatedEvent] = {

    // Helper to query the ledger api using the specified command.
    def queryLedgerApi[Svc <: AbstractStub[Svc], Result](
        command: GrpcAdminCommand[_, _, Result]
    ): Either[String, Result] =
      consoleEnvironment.grpcLedgerCommandRunner
        .runCommand("sourceLedger", command, ClientConfig(hostname, port, tls), token)
        .toEither

    (for {
      // Identify all the parties on the ledger and narrow down the list to local parties.
      allParties <- queryLedgerApi(
        LedgerApiCommands.PartyManagementService.ListKnownParties(identityProviderId = "")
      )
      localParties = allParties.collect {
        case PartyDetails(party, _, isLocal, _, _) if isLocal => LfPartyId.assertFromString(party)
      }

      // Query the ActiveContractsService for the actual contracts
      acs <- queryLedgerApi(
        LedgerApiCommands.AcsService
          .GetActiveContracts(
            localParties.toSet,
            templateFilter = templateFilter,
            limit = PositiveInt.MaxValue,
            timeout = NonNegativeDuration.maxTimeout,
            includeCreatedEventBlob = true,
          )(consoleEnvironment.environment.scheduler)
      )
    } yield acs.map(_.event)).valueOr(err =>
      throw new IllegalStateException(s"Failed to query parties, ledger id, or acs: $err")
    )
  }

  def removeCantonSpecifics(acs: Seq[CreatedEvent]): Seq[CreatedEvent] = {
    def stripPartyIdSuffix(suffixedPartyId: String): String =
      suffixedPartyId.split(SafeSimpleString.delimiter).head

    acs.map { event =>
      ValueRemapper.convertEvent(identity, stripPartyIdSuffix)(event)
    }
  }

  def lookUpPartyId(participant: ParticipantReference, party: String): PartyId =
    participant.parties
      .list(filterParty = party + SafeSimpleString.delimiter)
      .map(_.party)
      .headOption
      .getOrElse(throw new IllegalArgumentException("Unknown party"))
  // user-manual-entry-end: ImportHelperFunctions

}

class DataMigrationDamlLedgerToCantonRepairIntegrationTestDefault //TODO(i9565): beware -- in-memory integration tests can be flaky due to a known issue
    extends DataMigrationDamlLedgerToCantonRepairIntegrationTest

//class DataMigrationDamlLedgerToCantonRepairIntegrationTestPostgres
//    extends DataMigrationDamlLedgerToCantonRepairIntegrationTest {
//  registerPlugin(new UsePostgres(loggerFactory))
//}

//class DataMigrationDamlLedgerToCantonRepairIntegrationTestOracle
//    extends DataMigrationDamlLedgerToCantonRepairIntegrationTest {
//  registerPlugin(new UseOracle(loggerFactory))
//}
