// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.offboarding

import com.digitalasset.canton.console.CommandFailure
import com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition
import com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition.singleDomainWithManyParticipants
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.logging.SuppressionRule
import com.digitalasset.canton.topology.transaction.{RequestSide, TopologyChangeOp}
import org.slf4j.event.Level

import scala.concurrent.duration.DurationInt

class ParticipantOffboardingIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment {

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    singleDomainWithManyParticipants

  "A domain with multiple participants" should {

    "bootstrap" in { implicit env =>
      import env.*

      participants.all.domains.connect_local(da)

      participant1.health.ping(participant2, timeout = 30.seconds)
      participant1.health.ping(participant3, timeout = 30.seconds)
      participant2.health.ping(participant3, timeout = 30.seconds)
    }

    "successfully off-board a participant" in { implicit env =>
      import env.*

      val domain = da
      val domainId = domain.id

      // user-manual-entry-begin: OffboardParticipant
      // Disable the participant on all the sequencers to remove any sequencer data associated with it
      //  and allow sequencer pruning
      sequencers.all.foreach(_.sequencer.disable_member(participant2))

      // Remove the participant from the topology
      domain.topology.participant_domain_states.authorize(
        TopologyChangeOp.Remove,
        domainId,
        participant2.id,
        RequestSide.From,
      )
      // user-manual-entry-end: OffboardParticipant

      participant1.health.ping(participant3, timeout = 30.seconds)

      Seq(participant1, participant3).foreach { sourceParticipant =>
        loggerFactory.assertLogs(
          SuppressionRule.Level(Level.WARN) || SuppressionRule.Level(Level.ERROR)
        )(
          a[CommandFailure] should be thrownBy sourceParticipant.health.ping(
            participant2,
            timeout = 1.second,
          ),
          log =>
            log.warningMessage should include(
              "The participant is not connected to any domain where the given informees are known"
            ),
          log =>
            log.errorMessage should include(
              "Unable to ping PAR::participant2"
            ),
        )
      }
    }
  }
}
