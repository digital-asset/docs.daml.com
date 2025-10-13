// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.pruning

import com.digitalasset.canton.admin.api.client.data.PruningSchedule
import com.digitalasset.canton.environment.EnterpriseEnvironment
import com.digitalasset.canton.integration.plugins.UseOracle
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  EnterpriseTestConsoleEnvironment,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.integration.{
  BaseEnvironmentDefinition,
  EnterpriseEnvironmentDefinition,
}

/** The PruningDocumentationTest illustrates best practices on how to prune the canton nodes
  * for freeing up storage space.
  *
  * (If pruning was not an enterprise feature, this would be an ExampleIntegrationTest.)
  */
abstract class PruningDocumentationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment {

  override def environmentDefinition
      : BaseEnvironmentDefinition[EnterpriseEnvironment, EnterpriseTestConsoleEnvironment] =
    EnterpriseEnvironmentDefinition.singleDomain

  import com.digitalasset.canton.console.ConsoleEnvironment
  import com.digitalasset.canton.data.CantonTimestamp

  import java.time.Duration

  def pruneAllNodesInTest(implicit env: ConsoleEnvironment): CantonTimestamp => Unit = {
    import env.*

    // user-manual-entry-begin: PruneAllNodes
    import com.digitalasset.canton.console.{CommandFailure, ParticipantReference}
    import com.digitalasset.canton.data.CantonTimestamp

    def pruneAllNodes(pruneUpToIncluding: CantonTimestamp): Unit = {
      // If pruning a particular component fails, alert the user, but proceed pruning other components.
      // Therefore prune failures in one component still allow other components to be pruned
      // minimizing the chance of running out of overall storage space.
      def alertOnErrorButMoveOn(
          component: String,
          ts: CantonTimestamp,
          invokePruning: CantonTimestamp => Unit,
      ): Unit =
        try {
          invokePruning(ts)
        } catch {
          case _: CommandFailure =>
            logger.warn(
              s"Error pruning $component up to $ts. See previous log error for details. Moving on..."
            )
        }

      // Helper to prune a participant by time for consistency with domain prune signatures
      def pruneParticipantAt(p: ParticipantReference)(pruneUpToIncluding: CantonTimestamp): Unit = {
        val pruneUpToOffset = p.pruning.get_offset_by_time(pruneUpToIncluding.toInstant)
        pruneUpToOffset match {
          case Some(offset) => p.pruning.prune(offset)
          case None => logger.info(s"Nothing to prune up to $pruneUpToIncluding")
        }
      }

      val participantsToPrune = participants.all
      val domainsToPrune = domains.all

      // Prune all nodes one after the other rather than in parallel to limit the impact on concurrent workload.
      participantsToPrune.foreach(participant =>
        alertOnErrorButMoveOn(participant.name, pruneUpToIncluding, pruneParticipantAt(participant))
      )

      domainsToPrune.foreach { domain =>
        alertOnErrorButMoveOn(
          s"${domain.name} sequencer",
          pruneUpToIncluding,
          domain.sequencer.pruning.prune_at,
        )
        alertOnErrorButMoveOn(
          s"${domain.name} mediator",
          pruneUpToIncluding,
          domain.mediator.prune_at,
        )
      }
    }
    // user-manual-entry-end: PruneAllNodes

    pruneAllNodes
  }

  "steps documented in canton manual operational processes pruning section still compile and don't get wedged" in {
    implicit env =>
      import env.*
      val pruneAllNodes = pruneAllNodesInTest

      participants.local.foreach(_.domains.connect_local(da))
      participant2.health.ping(participant1)

      // user-manual-entry-begin: ProdConfig
      import java.time.Duration
      val retainMostRecent = Duration.ofDays(30)
      pruneAllNodes(CantonTimestamp.now().minus(retainMostRecent))
    // user-manual-entry-end: ProdConfig
  }

  "test steps documented in canton manual operational processes pruning section for oracle workaround" in {
    implicit env =>
      val pruneAllNodes = pruneAllNodesInTest

      // Tracking jira for ledger-api-server potentially performing this automatically: https://digitalasset.atlassian.net/browse/DPP-884

      // user-manual-entry-begin: TestConfig
      // An example test environment configuration in which hardly any data is retained.
      val pruningFrequency = Duration.ofDays(1)
      val retainMostRecent = Duration.ofMinutes(20)
      val pruningStartedAt = CantonTimestamp.now()
      val isOracle = true

      // Deleting the majority of rows from an Oracle table has been observed to
      // take a long time. Avoid non-linear performance degradation by breaking up one prune call into
      // several calls with progressively more recent pruning timestamps.
      if (isOracle && retainMostRecent.compareTo(pruningFrequency) < 0) {
        val numChunks = 8L
        val delta = pruningFrequency.minus(retainMostRecent).dividedBy(numChunks)
        for (chunk <- 1L to numChunks) yield {
          val chunkRetentionTimestamp = pruningFrequency.minus(delta.multipliedBy(chunk))
          pruneAllNodes(pruningStartedAt.minus(chunkRetentionTimestamp))
        }
      }

      pruneAllNodes(pruningStartedAt.minus(retainMostRecent))
    // user-manual-entry-end: TestConfig
  }

  "test that ensures the documentation is up to date with how to configure scheduled pruning" in {
    implicit env =>
      import env.*
      val participant = participants.all.head
      val domain = domains.all.head
      import com.digitalasset.canton.config
      import scala.concurrent.duration.*

      @scala.annotation.unused
      def checkCompiles(): Unit = {

        // user-manual-entry-begin: AutoPruneAllNodes
        participant.pruning.set_schedule("0 0 8 ? * SAT", 8.hours, 90.days)
        domain.sequencer.pruning.set_schedule("0 0 8 ? * SAT", 8.hours, 90.days)
        domain.mediator.set_schedule("0 0 8 ? * SAT", 8.hours, 90.days)
        // user-manual-entry-end: AutoPruneAllNodes

      }

      def set_schedule(
          cron: String,
          maxDuration: config.PositiveDurationSeconds,
          retention: config.PositiveDurationSeconds,
      ): Unit =
        PruningSchedule(cron, maxDuration, retention).discard

      val retention = 90.days

      // user-manual-entry-begin: PruningScheduleExamples
      set_schedule("0 0 20 * * ?", 2.hours, retention) // run every evening at 8pm GMT for two hours
      set_schedule("0 /5 * * * ?", 1.minute, retention) // run every 5 minutes for one minute
      set_schedule("0 0 0 31 12 ? 2023", 1.day, retention) // run for one specific day
    // user-manual-entry-end: PruningScheduleExamples

  }

}

//class PruningDocumentationTestDefault extends PruningDocumentationTest

//class PruningDocumentationTestPostgres extends PruningDocumentationTest {
//  registerPlugin(new UsePostgres(loggerFactory))
//}

class PruningDocumentationTestOracle extends PruningDocumentationTest {
  registerPlugin(new UseOracle(loggerFactory))
}
