// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.sequencer

import cats.syntax.parallel.*
import com.daml.ledger.api.v1.event.CreatedEvent
import com.daml.ledger.api.v1.transaction.Transaction
import com.daml.ledger.javaapi
import com.daml.test.evidence.tag.Reliability.ReliabilityTestSuite
import com.digitalasset.canton.BigDecimalImplicits.*
import com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent
import com.digitalasset.canton.console.commands.DomainChoice
import com.digitalasset.canton.console.{LocalSequencerNodeReference, ParticipantReference}
import com.digitalasset.canton.environment.EnterpriseEnvironment
import com.digitalasset.canton.examples.java.iou
import com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition.fromResource
import com.digitalasset.canton.integration.integration.ConfigTransform
import com.digitalasset.canton.integration.plugins.UsePostgres
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  EnterpriseTestConsoleEnvironment,
  HasIdentityStateCopy,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.integration.{
  ConfigTransforms,
  EnterpriseEnvironmentDefinition,
  HasCycleUtils,
}
import com.digitalasset.canton.logging.LogEntry
import com.digitalasset.canton.logging.SuppressingLogger.LogEntryOptionality
import com.digitalasset.canton.participant.admin.workflows.java.pingpong
import com.digitalasset.canton.participant.ledger.api.client.JavaDecodeUtil
import com.digitalasset.canton.sequencing.SequencerConnections
import com.digitalasset.canton.topology.PartyId
import com.digitalasset.canton.util.FutureInstances.*
import monocle.macros.syntax.lens.*
import org.scalatest.Assertion

import scala.concurrent.Future
import scala.concurrent.duration.DurationInt
import scala.jdk.CollectionConverters.*

/** The operations performed in this test are the following:
  *
  * 1. Setting up participant and domain
  * 2. Generating ledger api data (cycle contracts)
  * 3. Migrating nodes data to new databases and rehydrating them
  * 4. Reconnecting the nodes and checking state of the system
  *
  * For database sequencers, nodes migrated in 3. are:
  * - domain manager
  * - mediator
  * - participant
  *
  * For blockchains sequencers, nodes migrated in 3. are:
  * - sequencer
  * - all the nodes migrated in the database setting
  */
@SuppressWarnings(Array("org.wartremover.warts.Null", "org.wartremover.warts.Var"))
abstract class RehydrationIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with HasCycleUtils[EnterpriseEnvironment, EnterpriseTestConsoleEnvironment]
    with HasIdentityStateCopy
    with ReliabilityTestSuite {

  /** Hook for allowing sequencer integrations to adjust the base test config */
  protected def additionalConfigTransforms: ConfigTransform =
    ConfigTransforms.identity

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    fromResource("rehydration-topology.conf").withManualStart
      .addConfigTransforms(
        ConfigTransforms.updateParticipantConfig("participant2")(
          _.focus(_.init.identity).replace(None)
        ),
        ConfigTransforms.updateMediatorConfig("mediator2")(
          _.focus(_.init.identity).replace(None)
        ),
        ConfigTransforms.updateDomainManagerConfig("domainManager2")(
          _.focus(_.init.identity).replace(None)
        ),
      )
      .addConfigTransform(additionalConfigTransforms)
      .withSetup(implicit env => setupEnv)

  private var alice: PartyId = _
  private var sequencer1: LocalSequencerNodeReference = _
  private var sequencer2: LocalSequencerNodeReference = _

  private var newSequencer: LocalSequencerNodeReference = _

  protected def isBlockchainSequencer: Boolean

  private def setupEnv(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*

    this.sequencer1 = sequencers.local(0)
    this.sequencer2 = sequencers.local(1)

    // Start up only one version of everything
    this.sequencer1.start()
    domainManager1.start()
    mediator1.start()
    domainManager1.setup.bootstrap_domain(Seq(this.sequencer1), Seq(mediator1))
    mediator1.health.initialized() shouldBe true
    this.sequencer1.health.initialized() shouldBe true

    participant1.start()
    participant1.domains.connect_local(
      this.sequencer1,
      // increase this delay in order to avoid the occurrence of SEQUENCER_SUBSCRIPTION_LOST warning
      maxRetryDelayMillis = Some(10L * 60L * 1000L),
    )

    alice = participant1.parties.enable("Alice", waitForDomain = DomainChoice.All)
  }

  private def runCycleRobust(
      party: PartyId,
      initiatorParticipant: ParticipantReference,
      responderParticipant: ParticipantReference,
      id: String,
      commandId: String = "",
  ): Unit = {
    val cycle = new pingpong.Cycle(id, party.toProtoPrimitive).create.commands.loneElement

    val transaction: javaapi.data.Transaction =
      initiatorParticipant.ledger_api.javaapi.commands.submit_flat(
        Seq(party),
        Seq(cycle),
        commandId = commandId,
      )
    val Seq(cycleContract) =
      JavaDecodeUtil.decodeAllCreated(pingpong.Cycle.COMPANION)(transaction): @unchecked

    // Wait until the transaction was observed on the responder participant
    val cycleTxId = transaction.getTransactionId
    eventually() {
      responderParticipant.ledger_api.transactions.by_id(Set(party), cycleTxId) shouldBe
        Symbol("defined")
    }

    val cycleEx = cycleContract.id.exerciseVoid().commands.asScala.toSeq
    responderParticipant.ledger_api.javaapi.commands.submit_flat(
      Seq(party),
      cycleEx,
      commandId = if (commandId.isEmpty) "" else s"$commandId-response",
    )
  }

  private var observedTx: Seq[Transaction] = _
  private var observedAcs: Map[String, CreatedEvent] = _

  private def acsAsMap(acs: Seq[WrappedCreatedEvent]): Map[String, CreatedEvent] =
    acs.map { case WrappedCreatedEvent(event) => event.contractId -> event }.toMap

  private val iterations: Int = 1
  private val transactionLimit: Int = iterations * 3
  private val acsLimit: Int = iterations

  "generate some ledger data that we want to replay afterwards" in { implicit env =>
    import env.*

    val runF = (1 to iterations: Seq[Int]).parTraverse_ { i =>
      Future {
        // in each iteration, we create and archive a cycle contract and we create another one so that we build up an ACS
        runCycleRobust(alice, participant1, participant1, s"RUN-CYCLE-#$i", s"run-cycle-$i")
        createCycleContract(participant1, alice, s"LEAKED CYCLE-#$i", s"create-cycle-$i")
      }
    }
    runF.futureValue

    participant1.dars.upload(CantonExamplesPath)
    participant1.ledger_api.javaapi.commands.submit(
      Seq(alice),
      new iou.Iou(
        alice.toProtoPrimitive,
        alice.toProtoPrimitive,
        new iou.Amount(100.toBigDecimal, "USD"),
        List.empty.asJava,
      ).create.commands.asScala.toSeq,
    )

    observedTx = participant1.ledger_api.transactions.flat(
      partyIds = Set(alice),
      completeAfter = transactionLimit + 10,
      timeout = 5.seconds,
    )
    observedAcs = acsAsMap(participant1.ledger_api.acs.of_all(acsLimit + 10))

    observedTx.nonEmpty shouldBe true
    observedAcs.nonEmpty shouldBe true
  }

  "move all nodes to a fresh database and rehydrate from blockchain" in { implicit env =>
    import env.*

    logger.debug("Start to move everything to fresh nodes")

    // architecture-handbook-entry-begin: RehydrationGrabInitData
    val domainId = domainManager1.id
    val domainParameters = domainManager1.service.get_static_domain_parameters
    // architecture-handbook-entry-end: RehydrationGrabInitData

    if (isBlockchainSequencer) {
      newSequencer = this.sequencer2

      // copy over the sequencer to the fresh sequencer
      better.files.File.usingTemporaryDirectory("sequencer") { dir =>
        val tempDirSequencer = dir.pathAsString
        clue("move sequencer1 to sequencer2") {
          repair.identity.download(this.sequencer1, tempDirSequencer)
          newSequencer.start()
          newSequencer.health.initialized() shouldBe false
          // architecture-handbook-entry-begin: RehydrationSequencer
          repair.identity.upload(newSequencer, tempDirSequencer)
          newSequencer.initialization.initialize_from_beginning(domainId, domainParameters)
          newSequencer.health.wait_for_initialized()
          // architecture-handbook-entry-end: RehydrationSequencer
        }
      }
      logger.debug("Moved sequencer1 to sequencer2")

    } else {
      // For db sequencers, we don't migrate sequencer and keep the old one
      newSequencer = this.sequencer1
    }

    // copy over the domainManager1 to the fresh domainManager2
    better.files.File.usingTemporaryDirectory("domainManager") { dir =>
      val tempDirDomainManager = dir.pathAsString
      clue("move domainManager1 to domainManager2") {
        repair.identity.download(domainManager1, tempDirDomainManager)
        domainManager1.stop()
        domainManager2.start()
        // architecture-handbook-entry-begin: RehydrationDomainManager
        repair.identity.upload(domainManager2, tempDirDomainManager)
        domainManager2.setup.init(
          SequencerConnections.single(newSequencer.sequencerConnection)
        )
        domainManager2.health.wait_for_initialized()
        // architecture-handbook-entry-end: RehydrationDomainManager
      }
      logger.debug("Moved domainManager1 to domainManager2")

    }

    // copy over the mediator1 to the fresh mediator2
    better.files.File.usingTemporaryDirectory("mediator") { dir =>
      val tempDirMediator = dir.pathAsString
      clue("move mediator1 to mediator2") {
        val mediatorId = locally {
          val mediator = mediator1
          // architecture-handbook-entry-begin: RehydrationGrabMediatorId
          val mediatorId = mediator.id
          // architecture-handbook-entry-end: RehydrationGrabMediatorId
          repair.identity.download(mediator1, tempDirMediator)
          mediator1.stop()
          mediatorId
        }
        locally {
          val mediator = mediator2
          mediator.start()
          // architecture-handbook-entry-begin: RehydrationMediator
          repair.identity.upload(mediator, tempDirMediator)
          mediator.mediator.initialize(
            domainId,
            mediatorId,
            domainParameters,
            SequencerConnections.single(newSequencer.sequencerConnection),
            topologySnapshot = None,
          )
          mediator.health.wait_for_initialized()
          // architecture-handbook-entry-end: RehydrationMediator
        }
        logger.debug("Moved mediator1 to mediator2")
      }
    }

    // copy over participant1 to the fresh participant2
    better.files.File.usingTemporaryDirectory("participant") { dir =>
      clue("move participant1 to participant2") {
        val tempDirParticipant = dir.pathAsString
        locally {
          val participant = participant1
          // architecture-handbook-entry-begin: RepairMacroCloneIdentityDownload
          repair.identity.download(participant, tempDirParticipant)
          repair.dars.download(participant, tempDirParticipant)
          participant.stop()
          // architecture-handbook-entry-end: RepairMacroCloneIdentityDownload
        }
        locally {
          logger.debug("Moving participant1 to participant2")
          val participant = participant2
          // architecture-handbook-entry-begin: RepairMacroCloneIdentityUpload
          participant.start()
          repair.identity.upload(participant, tempDirParticipant)
          repair.dars.upload(participant, tempDirParticipant)
          // architecture-handbook-entry-end: RepairMacroCloneIdentityUpload
        }
      }
    }
  }

  protected val expectedLogs: Seq[(LogEntryOptionality, LogEntry => Assertion)] = Seq(
    (
      LogEntryOptionality.OptionalMany,
      _.warningMessage should include("timed out at"),
    )
  )

  "reconnect the nodes" in { implicit env =>
    import env.*
    locally {
      val sequencer = newSequencer
      val participant = participant2
      logger.debug("Connecting new participant to new sequencer")

      loggerFactory.assertLogsUnorderedOptional(
        {
          // architecture-handbook-entry-begin: RepairMacroCloneIdentityConnect
          participant.domains.connect_local(sequencer)
          // architecture-handbook-entry-end: RepairMacroCloneIdentityConnect

          // send a ping such that we know that the participant has processed everything from the domain
          clue("performing ping") {
            participant.health.ping(participant, timeout = 30.seconds)
          }
        },
        expectedLogs *,
      )
    }
  }

  "check that ACS and transaction stream have been reconstructed correctly" in { implicit env =>
    import env.*
    // checking the transaction stream order makes only sense in a single-domain scenario
    // we explicitly do not check the following:
    // * completions because they may differ (e.g., if sequencing the transaction submission times out)
    // * ledger offsets because they are not stable

    val participantToCheck = participant2

    val reconstructedTx = participantToCheck.ledger_api.transactions.flat(
      partyIds = Set(alice),
      completeAfter = transactionLimit + 10,
      timeout = 5.seconds,
    )
    def stripOffsetAndTraceContext(tx: Transaction): Transaction =
      tx.copy(offset = "", traceContext = None)
    // We don't care about the ping because the ping doesn't involve alice
    reconstructedTx.size shouldBe observedTx.size
    reconstructedTx.lazyZip(observedTx).foreach { (reconstructed, observed) =>
      withClue(
        s"Transaction at original offset ${observed.offset} and reconstructed offset ${reconstructed.offset}"
      ) {
        stripOffsetAndTraceContext(observed) shouldBe stripOffsetAndTraceContext(reconstructed)
      }
    }

    val reconstructedAcs = acsAsMap(participantToCheck.ledger_api.acs.of_all(acsLimit + 10))

    observedAcs shouldBe reconstructedAcs
  }

  "run a few more operations" in { implicit env =>
    import env.*

    participant2.parties.enable("bob")
    participant2.health.ping(participant2)
  }
}

class RehydrationIntegrationTestPostgres extends RehydrationIntegrationTest {
  private val plugin = new UsePostgres(loggerFactory)

  registerPlugin(plugin)

  override protected def isBlockchainSequencer: Boolean = false
}
