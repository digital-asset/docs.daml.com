..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _ledger-pruning:

Ledger Pruning
==============

Pruning the ledger frees up storage space by deleting state no longer needed by participants, domain sequencers, and mediators.
It also serves as a mechanism to help implement right-to-forget mandates such as GDPR.

The following commands allow you to prune events and inactive contracts up to a specified time from the various components:

- Prune participants via the `prune` command specifying a "ledger offset" obtained by specifying a timestamp received by a call to "get_offset_by_time".
- Prune domain sequencers and mediators via their respective `prune_at` commands.

The pruning operations impact the "regular" workload (lowering throughput during pruning by as much as 50% in our test environments), so depending on your requirements it might make sense to schedule pruning at off-peak times or during maintenance windows such as after taking database backups.

The following canton console code illustrates best practices such as:

- The pruning commands used in the script will not delete any data that is still required for command processing.
  (E.g. it will only delete sequencer data that all clients of the sequencer have already read or acknowledged.)
  If the given timestamp is too high, the commands will fail.
- Error handling ensures that pruning errors raise an alert. Catching the `CommandFailure` exception also ensures that a problem encountered while pruning one component still lets pruning other components proceed allowing corresponding storage to be freed up.
- Pruning one node at a time rather than all nodes in parallel somewhat limits the impact on concurrently executing workload. If you configure pruning to run during a maintenance window with no concurrent workload, and as long as the database backend has sufficient capacity, you may prune participants and domains in parallel.

.. code-block:: none

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
                  s"Error pruning ${component} up to ${ts}. See previous log error for details. Moving on..."
                )
            }
    
          // Helper to prune a participant by time for consistency with domain prune signatures
          def pruneParticipantAt(p: ParticipantReference)(pruneUpToIncluding: CantonTimestamp): Unit = {
            val pruneUpToOffset = p.pruning.get_offset_by_time(pruneUpToIncluding.toInstant)
            pruneUpToOffset match {
              case Some(offset) => p.pruning.prune(offset)
              case None => logger.info(s"Nothing to prune up to ${pruneUpToIncluding}")
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


Invoke pruning from within your scheduling environment and by specifying the ledger data retention period like so:

.. code-block:: none

          import java.time.Duration
          val retainMostRecent = Duration.ofDays(30)
          pruneAllNodes(CantonTimestamp.now().minus(retainMostRecent))


Pruning Ledgers in Test Environments
------------------------------------

While it is a best practice for test environments to match production configurations, testing pruning involves challenges related to the amount of retained data:

- Test environments may not have the same amount of storage space to hold data volumes present in production.
- It may be impractical to wait long enough until test environments have accrued data to expected production retention times that are often measured in months.

As a result you may choose to prune test environments more aggressively. When using databases other than Oracle with a lower retention time, use the same code as when pruning production.
On Oracle however you may observe performance degradation when pruning the majority of the ledger data in one go. In such cases breaking up pruning invocations into multiple chunks likely speeds up pruning:

.. code-block:: none

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


Common Notes
------------

.. TODO(#9950): sequencer pruning can be blocked

- For high availability nodes that share a common database, pruning has to be invoked only once on an active replica
  (participant, mediator) or one active shard (database sequencer). For blockchain-based sequencers, you need
  to invoke pruning on each sequencer node. Please note that pruning of the blockchains themselves is not supported,
  as blockchains don't support it.
- The sequencer will only allow pruning of acknowledged events. As such, if a client such as a participant or mediator
  stops acknowledging events that have been sent to it, sequencer pruning will be blocked. This is a current
  limitation.
- Generally, idle sequencer clients will only acknowledge once they have observed subsequent events. This means that idle
  clients normally won't acknowledge the last event. Since each member requests a time-proof once per day,
  there is a default limitation that a system with idle but connected clients cannot be pruned with a retention window of less
  than 24 hours. As the topology manager connects to the sequencer but is often idle and only invoked on topology changes,
  this limitation manifests itself when pruning test environments where aggressive pruning windows of less
  than 24 hours are used. This can be fixed by adjusting the domain-tracker time of the topology manager:
  ``canton.domains.mydomain.time-tracker.min-observation-duration = 1h``.
- Pruning of participants requires the participant to have received a commitment from each counter-participant with which
  it shares a contract. If a participant becomes defunct and stops sending commitments, pruning of the participant will
  not work. Therefore, before you disable a participant, please make sure that is not involved in any contract. This is
  a current limitation.

.. TODO(#5690): pruning and disconnected participants (note above)
.. TODO(#5945): pruning with dangling parties (note above)