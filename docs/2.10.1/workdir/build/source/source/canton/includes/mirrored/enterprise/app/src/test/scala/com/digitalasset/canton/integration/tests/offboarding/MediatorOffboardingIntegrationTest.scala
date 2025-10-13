// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.offboarding

import com.digitalasset.canton.console.{
  DomainManagerNodeReference,
  LocalMediatorReference,
  ParticipantReference,
}
import com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.logging.SuppressionRule
import org.slf4j.event.Level

import scala.concurrent.duration.*

class MediatorOffboardingIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment {

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.multipleMediators

  protected def offboardMediator(
      domainManager: DomainManagerNodeReference,
      mediator: LocalMediatorReference,
      participants: Iterable[ParticipantReference],
  ): Unit = {
    val mediatorId = mediator.id // The ID cannot be accessed after stopping the node

    // TODO(#1251) remove this comment if/when mediator catch-up is implemented
    // user-manual-entry-begin: OffboardMediator
    // `setup.offboard_mediator` will log a warning with a message similar to the following:
    //
    //  "Mediator ... is deactivated and will miss out on topology transactions. This will break it"
    //
    //  This just means that the decommissioned mediator won't be able to join the domain anymore, as it won't receive
    //  topology transactions and its topology state will thus fork, which is an irreversible fault.
    //  Off-boarding a mediator is indeed an irreversible operation, but here it is being intentionally and explicitly
    //  requested, so in this case this warning can be safely ignored.
    domainManager.setup.offboard_mediator(mediatorId)
    mediator.stop()
    // user-manual-entry-end: OffboardMediator

    eventually() {
      participants.foreach(participant =>
        participant.topology.mediator_domain_states
          .list()
          .exists(_.item.mediator == mediatorId) shouldBe false
      )
    }
  }

  "A domain with multiple mediators" should {

    "bootstrap" in { implicit env =>
      import env.*

      domainManager1.setup.bootstrap_domain(Seq(sequencer1), Seq(mediator1, mediator2))

      sequencer1.health.initialized() shouldBe true
      mediator1.health.initialized() shouldBe true
      mediator2.health.initialized() shouldBe true

      participant1.domains.connect_local(sequencer1)
      participant2.domains.connect_local(sequencer1)
      participant1.health.ping(participant2, timeout = 30.seconds)
    }
  }

  "successfully off-board a mediator" in { implicit env =>
    import env.*

    // TODO(#1251) remove this log suppression+assertion if/when mediator catch-up is implemented
    loggerFactory.assertLogs(SuppressionRule.Level(Level.WARN))(
      offboardMediator(domainManager1, mediator2, Seq(participant1, participant2)),
      log => {
        log.warningMessage should include(
          "is deactivated and will miss out on topology transactions. This will break it"
        )
      },
    )

    participant1.health.ping(participant2, timeout = 30.seconds)
  }
}
