// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.repair

import com.digitalasset.canton.BigDecimalImplicits.*
import com.digitalasset.canton.HasExecutionContext
import com.digitalasset.canton.config.InitConfigBase
import com.digitalasset.canton.console.FeatureFlag
import com.digitalasset.canton.examples.java.iou
import com.digitalasset.canton.integration.*
import com.digitalasset.canton.integration.plugins.UsePostgres
import com.digitalasset.canton.integration.tests.{
  EnterpriseEntitySyntax,
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.logging.{LogEntry, SuppressingLogger, SuppressionRule}
import com.digitalasset.canton.sequencing.client.ResilientSequencerSubscription
import com.digitalasset.canton.topology.SequencerId
import monocle.macros.syntax.lens.*
import org.slf4j.event.Level

import scala.annotation.nowarn
import scala.jdk.CollectionConverters.*

@nowarn("msg=match may not be exhaustive")
trait DomainRepairIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with EnterpriseEntitySyntax
    with HasExecutionContext
    with RepairTestUtil {

  // two participant, two domain environment to use first domain to source some "real" contracts, then to be
  // considered "broken", and a second initially "empty" domain to use as replacement domain
  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.multiDomain
      .addConfigTransform(
        ConfigTransforms.updateDomainConfig(replacement)(
          _.focus(_.init.identity).replace(Some(InitConfigBase.Identity()))
        )
      )
      .addConfigTransform(ConfigTransforms.enableAdvancedCommands(FeatureFlag.Repair))

  "Able to set up participants with data and connect to replacement domain" in { implicit env =>
    import env.*
    Seq(participant1, participant2).foreach { p =>
      p.domains.connect_local(lostDomain)
      p.dars.upload(CantonExamplesPath)
    }

    participant1.ledger_api.parties.allocate(aliceS, aliceS)
    participant2.ledger_api.parties.allocate(bobS, bobS)

    val Alice = aliceS.toPartyId(participant1)
    val Bob = bobS.toPartyId(participant2)

    Range.apply(0, 3).foreach { _ =>
      createContract(participant1, Alice, Bob)
      createContract(participant2, Bob, Alice)
    }
    exerciseContract(participant1, Alice, createContract(participant1, Alice, Alice))
    exerciseContract(participant2, Bob, createContract(participant2, Bob, Bob))

    logger.debug("Checking that participants see contracts in ACS")

    assertAcsCounts(
      (participant1, Map(Alice -> 7, Bob -> 6)),
      (participant2, Map(Alice -> 6, Bob -> 7)),
    )

    val lostSubscriptionMessage = ResilientSequencerSubscription.LostSequencerSubscription
      .Warn(SequencerId(lostDomain.id), _logOnCreation = false)
      .cause

    loggerFactory.assertLogsSeq(SuppressionRule.LevelAndAbove(Level.WARN))(
      {
        // From here on consider the "da" domain broken.
        // user-manual-entry-begin: ConsiderDomainBroken
        lostDomain.stop()
        Seq(participant1, participant2).foreach { p =>
          p.domains.disconnect(lostDomain.name)
          // Also let the participant know not to attempt to reconnect to lostDomain
          p.domains.modify(lostDomain.name, _.copy(manualConnect = true))
        }
        // user-manual-entry-end: ConsiderDomainBroken
      },
      (logs: Seq[LogEntry]) => {
        val expectedMessages = List(
          "subscription implementation failed: GrpcSubscriptionError(Request failed for sequencer. Is the server running?",
          lostSubscriptionMessage,
        )

        SuppressingLogger.assertThatLogDoesntContainUnexpected(expectedMessages)(logs)
      },
    )

    logger.debug(
      "Participants disconnected from lost domain will now attempt to connect to new domain"
    )

    // Note that merely registering the domain is not good enough as we need the topology state to be built.
    // For that we connect to replacement domain and disconnect once the participants have the new domain topology state.
    // user-manual-entry-begin: InitializeIdentityStateAndDisconnect
    Seq(participant1, participant2).foreach(_.domains.connect_local(newDomain))

    // Wait for topology state to appear before disconnecting again.
    clue("newDomain initialization timed out") {
      eventually()(
        (
          participant1.domains.active(newDomain.name),
          participant2.domains.active(newDomain.name),
        ) shouldBe (true, true)
      )
    }

    // Run a few transactions on the new domain so that the topology state chosen by the repair commands
    // really is the active one that we've seen
    participant1.health.ping(participant2, workflowId = newDomain.name)

    Seq(participant1, participant2).foreach(_.domains.disconnect(newDomain.name))
    // user-manual-entry-end: InitializeIdentityStateAndDisconnect

    logger.debug("Participants disconnected from new domain")

    // At this point both domains are still registered.
    Seq(participant1, participant2).foreach(
      _.domains.list_registered().map(_._1.domain.unwrap).toSet shouldBe Set(
        lostDomain.name,
        newDomain.name,
      )
    )

    // And neither domain is connected.
    Seq(participant1, participant2).foreach(_.domains.list_connected() shouldBe Nil)
  }

  "Move contract instances from da domain to replacement domain invoking repair.change_domain" in {
    implicit env =>
      import env.*

      val Alice = aliceS.toPartyId(participant1)
      val Bob = bobS.toPartyId(participant2)

      // user-manual-entry-begin: ChangeContractsDomain
      // Extract participant contracts from "lostDomain".
      val contracts1 =
        participant1.testing.pcs_search(lostDomain.name, filterTemplate = "^Iou", activeSet = true)
      val contracts2 =
        participant2.testing.pcs_search(lostDomain.name, filterTemplate = "^Iou", activeSet = true)

      // Ensure that shared contracts match.
      val Seq(sharedContracts1, sharedContracts2) = Seq(contracts1, contracts2).map(
        _.filter { case (_isActive, contract) =>
          contract.metadata.stakeholders.contains(Alice.toLf) &&
          contract.metadata.stakeholders.contains(Bob.toLf)
        }.toSet
      )

      clue("checking if contracts match") {
        sharedContracts1 shouldBe sharedContracts2
      }

      // Finally change the contracts from "lostDomain" to "newDomain"
      participant1.repair.change_domain(
        contracts1.map(_._2.contractId),
        lostDomain.name,
        newDomain.name,
      )
      participant2.repair.change_domain(
        contracts2.map(_._2.contractId),
        lostDomain.name,
        newDomain.name,
        skipInactive = false,
      )
    // user-manual-entry-end: ChangeContractsDomain
  }

  // ignore if necessary as this step might not be legit yet if acs commitments don't error currently:
  "Able to exercise contracts moved to replacement domain" in { implicit env =>
    import env.*

    val Alice = aliceS.toPartyId(participant1)
    val Bob = bobS.toPartyId(participant2)

    // user-manual-entry-begin: VerifyNewDomainWorks
    Seq(participant1, participant2).foreach(_.domains.reconnect(newDomain.name))

    // Look up a couple of contracts moved from lostDomain
    val Seq(iouAlice, iouBob) = Seq(participant1 -> Alice, participant2 -> Bob).map {
      case (participant, party) =>
        participant.ledger_api.javaapi.acs
          .await[iou.Iou.Contract, iou.Iou.ContractId, iou.Iou](iou.Iou.COMPANION)(
            party,
            _.data.owner == party.toProtoPrimitive,
          )
    }

    // Ensure that we can create new contracts
    Seq(participant1 -> ((Alice, Bob)), participant2 -> ((Bob, Alice))).foreach {
      case (participant, (payer, owner)) =>
        participant.ledger_api.javaapi.commands.submit_flat(
          Seq(payer),
          new iou.Iou(
            payer.toProtoPrimitive,
            owner.toProtoPrimitive,
            new iou.Amount(200.toBigDecimal, "USD"),
            java.util.List.of(),
          ).create.commands.asScala.toSeq,
        )
    }

    // Even better: Confirm that we can exercise choices on the moved contracts
    Seq(participant2 -> ((Bob, iouBob)), participant1 -> ((Alice, iouAlice))).foreach {
      case (participant, (owner, iou)) =>
        participant.ledger_api.javaapi.commands
          .submit_flat(Seq(owner), iou.id.exerciseCall().commands.asScala.toSeq)
    }
    // user-manual-entry-end: VerifyNewDomainWorks

    // should observe two more contracts
    assertAcsCounts(
      (participant1, Map(Alice -> 9, Bob -> 8)),
      (participant2, Map(Alice -> 8, Bob -> 9)),
    )
    // after the exercise alice and bob each have three GetCash contracts (one from first test step only visible locally)
    assertAcsCountsWithFilter(
      _.templateId.isModuleEntity("Iou", "GetCash"),
      (participant1, Map(Alice -> 3, Bob -> 2)),
      (participant2, Map(Alice -> 2, Bob -> 3)),
    )

  }

}

//class DomainRepairIntegrationTestDefault extends DomainRepairIntegrationTest //TODO(i9565): beware -- in-memory integration tests can be flaky due to a known issue

class DomainRepairIntegrationTestPostgres extends DomainRepairIntegrationTest {
  registerPlugin(new UsePostgres(loggerFactory))
}

//class DomainRepairIntegrationTestOracle extends DomainRepairIntegrationTest {
//  registerPlugin(new UseOracle(loggerFactory))
//}
