..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _ledger-pruning:

Ledger Pruning
==============

Pruning refers to the selective removal of old, stale, or unneeded data from participant, domain sequencer, and mediator
nodes. Nodes operate continuously for an indefinite amount of time on a limited amount of storage. In addition, privacy
demands may require removing Personally Identifiable Information (PII) upon request.

Pruning participant nodes means removing archived contracts (and associated transactions and events). Pruning never
removes active (i.e., non-archived) Daml contracts. For domain sequencers and mediators, pruning relates to the removal
of processed messages. Participants and domain sequencers and mediators can have different pruning schedules set.

Enable Automatic Pruning
------------------------

Enable automatic pruning by specifying a pruning schedule consisting of the following:

- A cron expression that designates regular pruning "begin times".
- A maximum duration specifying pruning "end times" relative to the begin times of the cron expression.
- A retention period to specify how far to prune relative to the current time.

For example, to run pruning every Saturday starting at 8am until 4pm (both in UTC):

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/pruning/PruningDocumentationTest.scala
   :start-after: user-manual-entry-begin: AutoPruneAllNodes
   :end-before: user-manual-entry-end: AutoPruneAllNodes
   :dedent:

Refer to the cron specification to customize the pruning schedule. Here are a few examples:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/pruning/PruningDocumentationTest.scala
   :start-after: user-manual-entry-begin: PruningScheduleExamples
   :end-before: user-manual-entry-end: PruningScheduleExamples
   :dedent:

For the maximum duration to specify a reliable pruning window "end time", the leading fields of the cron expression
should should not be wildcards (`*`) as illustrated in the examples above. If the hour field is fixed, so should the
fields for minute and second.

Monitoring Pruning Progress
---------------------------

Monitor the pruning state to determine that the pruning schedule allows participant, mediator, and sequencer pruning
to keep up with ledger growth, and is not stuck for one of the reasons described below in the "Common Notes".

Specifically, monitor the `max-event-age` metrics describing the age of the "oldest, un-pruned" event (in hours)::

  <participant>.prune.max-event-age
  <mediator>.max-event-age
  <sequencer>.max-event-age

The `max-event-age` metrics should not exceed the value of the pruning schedule `retention` plus the length of the
interval. For example, if your schedule specifies a retention of 30 days and a cron that calls for weekly
pruning, `max-event-age` must remain below 37 days. If for any node the `max-event-age` metric exceeds this upper limit,
you should consider allocating more time for pruning by reducing the interval between pruning windows or by
increasing the `maximum duration` pruning schedule setting.

Best Practices
--------------

- Pruning deletes data from the database, freeing up space, but it does not perform any database maintenance such as
  table resizing. PostgreSQL supports automatic and manual vacuuming for this purpose, but Oracle lacks such support and
  relies on the database administrator to manage freed database space.
- Pruning is an IO-heavy operation and would have an impact on overall system performance (lowering throughput during
  pruning by as much as 50% in our test environments), hence it is preferable to schedule pruning during maintenance
  windows such as after taking database backups or during low load.
- A catastrophic failure of a participant and its backup can be mitigated by rebuilding its state from the sequencer by
  replaying messages. However, this becomes impossible once the required messages have been pruned from the sequencer.
  For this reason, the backup strategy for participant nodes should be coordinated with the sequencer’s pruning schedule.
- For high availability nodes that share a common database, the pruning schedule has to be set on an active replica
  (participant, mediator) or one active shard (database sequencer).
- Participants, mediators, and sequencers also expose "manual" `prune*` methods that come with pitfalls. The methods
  might appear to be hanging unless the range of events and messages specified for pruning is not broken up into
  sufficiently small chunks. In addition, these manual methods have no built-in mechanism to resume on another node after
  a high-availability failover. Automatic pruning is recommended instead.

Current Limitations
-------------------


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


Refer to the Participant Pruning section to learn how pruning affects Daml applications and the Ledger API.
