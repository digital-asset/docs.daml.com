..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _scaling_and_performance:

Scaling and Performance
=======================

Network Scaling
---------------

The scaling and performance characteristics of a Canton-based system
are determined by many factors. The simplest approach is to deploy Canton as a simple monolith where vertical scaling would
add more CPUs, memory, etc. to the compute resource. However, the most frequent and expected deployment of Canton is as a distributed, micro-service architecture, running in
different data centers of different organizations, with many opportunities to
incrementally increase throughput. This is outlined below.

The ledger state in Canton does not exist globally so there is no
single node that, by design, hosts all contracts. Instead, participant nodes are
involved in transactions that operate on the ledger state on a strict
need-to-know basis (data minimization), only exchanging (encrypted)
information on the domains used as coordination points for the given
input contracts. For example, if participants Alice and Bank transact
on an i-owe-you contract on domain A, another participant Bob, or
another domain B, does not receive a single bit related to this
transaction. This is in contrast to blockchains, where each node has to
process each block regardless of how active or directly affected
they are by a given transaction. This lends itself to a
micro-service approach that can scale horizontally.

The micro-services deployment of Canton includes the set of
participant and domain nodes (hereafter, "participant" or
"participants" and "domain" or "domains" respectively), as well as the
services internal to the domain (e.g., Topology Manager). In general,
each Canton micro-service follows the best practice of having its own
local database which increases throughput. Deploying a service
to its
own compute server increases throughput because of the additional CPU and
disk capacity. A vertical scaling approach can be used to
increase throughput if a single service becomes a bottleneck, along
with the option of horizontal scaling that is discussed next.

An initial Canton deployment can increase its scaling in multiple
ways that build on each other. If a single participant node has many
parties, then throughput can be increased by migrating parties off to
a new, additional participant node (currently supported as a manual
early access feature). For example, if 100 parties are performing
multi-lateral transactions with each other, then the system can
reallocate parties to 10 participants with 10 parties each, or 100
participants with 1 party each. As most of the computation occurs on
the participants, a domain can sustain a very substantial load from
multiple participants. If the domain were to be a bottleneck then the
Sequencer(s), Topology Manager, and Mediator can be run on their own
compute server which increases the domain throughput. Therefore, new
compute servers with additional Canton nodes can be added to the
network when needed, allowing the entire system to scale horizontally.

If even more throughput is needed then the multiple-domain feature of
Canton can be leveraged to increase throughput. In a large and active network
where a domain reaches the capacity limit, additional domains can be
rolled out, such that the workflows can be sharded over the available
domains (early access). This is a standard technique for load
balancing where the client application does the load balancing via sharding.

If a single party is a bottleneck then the throughput can be increased
by sharding the workflow across multiple parties hosted on separate participants. If a workflow
is involving some large operator (i.e. an exchange), then an option
would be to shard the operator by creating two operator parties and
distribute the workflows evenly over the two operators (eventually hosted on different participants), and by adding
some intermediate steps for the few cases where the workflows would
span across the two shards.

Some anti-patterns need to be avoided for the
maximum scaling opportunity. For example, having
almost all of the parties on a single participant is an anti-pattern to
be avoided since that participant will be a bottleneck. Similarly,
the design of the Daml model has a strong impact on the degree to which sharding
is possible. For example, having a Daml application that introduces a
synchronization party
through which all transactions need to be validated introduces a
bottleneck so it is also an anti-pattern to avoid.

The bottom line is that a Canton system can scale out horizontally if
commands involve only a small number of participants and domains.


.. enterprise-only::

Node Scaling
------------

The Daml Enterprise edition of Canton supports the following scaling of nodes:

- The database-backed drivers (Postgres and Oracle) can run in an active-active setup with parallel processing,
  supporting multiple writer and reader processes. Thus, such nodes can scale horizontally.

- The enterprise participant node processes transactions in parallel (except the process of conflict detection which
  by definition must be sequential), allowing much higher throughput than the community version. The community version
  is processing each transaction sequentially.
  Canton processes make use of multiple CPUs and will detect the number of available CPUs automatically.
  The number of parallel threads can be controlled by setting the JVM properties
  `scala.concurrent.context.numThreads` to the desired value.

Generally, the performance of Canton nodes is currently storage I/O bound. Therefore, their performance depends on the
scaling behavior and throughput performance of the underlying storage layer, which can be a database or a distributed
ledger for some drivers. Therefore, appropriately sizing the database is key to achieving the necessary performance.

On a related note: the Daml interpretation is a pure operation, without side-effects. Therefore, the interpretation
of each transaction can run in parallel, and only the conflict detection between transactions must run sequentially.

Performance and Sizing
----------------------

A Daml workflow can be computationally arbitrarily complex, performing lots of computation (cpu!) or fetching many
contracts (io!), and involve different numbers of parties, participants, and domains. Canton nodes store their entire
data in the storage layer (database), with additional indexes. Every workflow and topology is different,
and therefore, sizing requirements depend on the Daml application that is going to run, and on the resource
requirements of the storage layer. Therefore, to obtain sizing estimates you must measure the resource usage
of dominant workflows using a representative topology and setup of your use case.

Batching
--------

As every transaction comes with an overhead (signatures, symmetric encryption keys, serialization and wrapping into
messages for transport, HTTP headers, etc), we recommend designing the applications submitting commands in a way that
batches smaller requests together into a single transaction.

Optimal batch sizes depend on the workflow and the topology and need to be determined experimentally.

Asynchronous Submissions
------------------------

In order to achieve best performance, we suggest that you use asynchronous command submissions. However,
please note that the async submission is only partially asynchronous, as the initial command interpretation
and transaction building is included in that step, while the transaction validation and result finalization is
not. This means that an async submission takes between 50 to 1000 ms, depending on command size and complexity.
In the extreme case with a single thread submitting transactions, this would mean that you would only achieve a rate of
one command per second.

If you use synchronous command submissions, the system will wait for the entire transaction to complete, which will
require even more threads. Also, please note that the synchronous command submission has a default upper limit of 256
in flight commands, which can be reconfigured using

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/command-service-max-commands-in-flight.conf


Storage Estimation
------------------
A priori storage estimation of a Canton installation is tricky. As explained above, storage usage depends on topology, payload, Daml models used, and what type
of storage layer is configured. However, the following example may help you understand the storage usage for your use case:

First, a command submitted through the ledger API is sent to the participant as a serialized gRPC request.

This command is first interpreted and translated into a Daml-LF transaction. The interpreted transaction is next translated into a Canton transaction view-decomposition, which is a privacy-preserving
representation of the full transaction tree structure.
A transaction typically consists of several transaction views; in the worst case, every action node in the transaction tree becomes a separate transaction view.
Each view contains the full set of arguments required by that view, including the contract arguments of the input contracts.
So the data representation can be multiplied quite a bit. Here, we cannot estimate the resulting size without having a concrete example.
For simplicity, let us consider the simple case where a participant is exercising a simple "Transfer" choice on an
typical "Iou" contract to a new owner, preserving the other contract arguments.
We assume that the old and new owners of the IOU are hosted on the same participant whereas the IOU issuer is hosted on a second participant.

The resulting Canton transaction consists of two views (one for the **Exercise** node of the Transfer choice and one for the **Create** node of the transferred IOU).
Both views contain some metadata such as the package and template identifiers, contract keys, stakeholders, and involved participants.
The view for the **Exercise** node contains the contract arguments of the input IOU, say of size `Y`.
The view for the **Create** node contains the updated contract arguments for the created contract, again of size `Y`.
Note that there is no fixed relation between the command size `X` and the size of the input contracts `Y`.
Typically `X` only contains the receiver of the transfer, but not the contract arguments that are stored on the ledger.

Then, we observe the following storage usage:

- Two encrypted envelopes with payload `Y` each, one symmetric key per
  view and informee participant of that view, two root hashes for each
  participant and the participant IDs as recipients at the sequencer
  store, and the informee tree for the mediator (informees and
  transaction metadata, but no payload), together with the sequencer
  database indexes.
- Two encrypted envelopes with payload `Y` each and the symmetric keys for the views, in the participant events table of each participant (as both receive the data)
- Decrypted new resulting contract of size `Y` in the private contract store and some status information of that contract on the active contract journal of the sync service.
- The full decrypted transaction with a payload of size `Y` for the created contract, in the sync service linear event log. This transaction does not contain the input contract arguments.
- The full decrypted transaction with `Y` in the indexer events table, excluding input contracts, but including newly divulged input contracts.

If we assume that payloads dominate the storage requirements, we conclude that the storage requirement is given by the payload multiplication
due to the view decomposition. In our example, the transaction requires `5*Y` storage on each participant and `2*Y` on the sequencer.
For the two participants and the sequencer, this makes `12*Y` in total.

Additionally to this, some indexes have to be built by the database to serve the contracts and events efficiently.
The exact estimation of the size usage of such indexes for each database layer is beyond the scope of our documentation.

.. note::

   Please note that we do have plans to remove the storage duplication between the sync service and the indexer. Ideally,
   will be able to reduce the storage on the participant for this example from `5*Y` down to `3*Y`: once for the unencrypted created contract and twice for the two encrypted transaction views.

Generally, to recover used storage, a participant and a domain can be pruned. Pruning is available on Canton Enterprise
through a :ref:`set of console commands <ledger-pruning-commands>` and allows removal of past events and archived contracts
based on a timestamp. The storage usage of a Canton deployment can be kept constant by continuously removing
obsolete data. Non-repudiation and auditability of the unpruned history are preserved due to the bilateral commitments.


Set Up Canton to Get the Best Performance
-----------------------------------------

In this section, the findings from internal performance tests are outlined to help you achieve optimal performance for your Canton application.

System Design / Architecture
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We recommend the version of Canton included in the Daml Enterprise edition, which is heavily optimized when compared with the community edition.

Plan your topology such that your Daml parties can be partitioned into independent blocks.
That means most of your Daml commands involve parties of a single block only.
It is ok if some commands involve parties of several (or all) blocks, as long as this happens only very rarely.
In particular, avoid having a single master party that is involved in every command, because that party bottlenecks the system.

If your participants are becoming a bottleneck, add more participant nodes to your system.
Make sure that each block runs on its own participant.
If your domain(s) are becoming a bottleneck, add more domain nodes and distribute the load evenly over all domains.

Prefer sending big commands with multiple actions (creates / exercises) over sending numerous small commands.
Avoid sending unnecessary commands through the ledger API.
Try to minimize the payload of commands.

Further information can be found in Section :ref:`scaling_and_performance`.

Hardware and Database
~~~~~~~~~~~~~~~~~~~~~

Do not run Canton nodes with an in-memory storage or with an H2 storage in production or during performance tests.
You may observe very good performance in the beginning, but performance can degrade substantially once the data stores fill up.

Measure memory usage, CPU usage and disk throughput and improve your hardware as needed.
For simplicity, it makes sense to start on a single machine.
Once the resources of a machine are becoming a bottleneck, distribute your nodes and databases to different machines.

Try to make sure that the latency between a Canton node and its database is very low (ideally in the order of microseconds).
Prefer hosting a Canton node and its database on the same machine.
This is likely faster than running several Canton nodes on the same machine and the databases on a separate machine;
for, the latency between Canton nodes is much less performance critical than the latency between a Canton node and its database.

Optimize the configuration of your database, and make sure the database has sufficient memory and is stored on SSD disks with a very high throughput.
For Postgres, `this online tool <https://pgtune.leopard.in.ua/>`_ is a good starting point for finding reasonable parameters.

.. _performance_configuration:

Configuration
~~~~~~~~~~~~~

In the following, we go through the parameters with known impact on performance.

**Timeouts.** Under high load, you may observe that commands timeout.
This will negatively impact throughput, because the commands consume resources without contributing to the number of accepted commands.
To avoid this situation increase timeout parameters from the Canton console:

.. literalinclude:: /canton/includes/mirrored/scripts/canton-testing/config/run-domains.canton
   :start-after: user-manual-entry-begin: BumpDomainTimeouts
   :end-before: user-manual-entry-end: BumpDomainTimeouts

If timeouts keep occurring, change your setup to submit commands at a lower rate.
In addition, take the next paragraph on resource limits into account.

.. _tuning_resource_limits:

**Tune resource limits.** Resource limits are used to prevent ledger applications from overloading Canton by sending
commands at an excessive rate.
While resource limits are necessary to protect the system from denial of service attacks in a production environment,
they can prevent Canton from achieving maximum throughput.
Resource limits can be configured as follows from the Canton console:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/BackpressureIntegrationTest.scala
   :start-after: user-manual-entry-begin: SetResourceLimits
   :end-before: user-manual-entry-end: SetResourceLimits
   :dedent:

As a rule of thumb, configure ``maxDirtyRequests`` to be slightly larger than ``throughput * latency``, where

- ``throughput`` is the number of requests per second Canton needs to handle and
- ``latency`` is the time taken to process a single request while Canton is receiving requests at rate ``throughput``.

You should run performance tests to ensure that ``throughput`` and ``latency`` are actually realistic.
Otherwise, an application may overload Canton by submitting more requests than Canton can handle.

Configure the ``maxRate`` parameter to be slightly higher than the expected maximal ``throughput``.

If you need to support command bursts, configure the ``maxBurstFactor`` accordingly. Then,
the ``maxRate`` limitation will only start to enforce the rate after having received the initial burst
of ``maxBurstFactor * maxRate``.

To find optimal resource limits you need to run performance tests.
The ``maxDirtyRequest`` parameter will protect Canton from being overloaded, if requests are arriving at a constant rate.
The ``maxRate`` parameter offers additional protection, if requests are arriving at a variable rate.

If you choose higher resource limits, you may observe a higher throughput, at the risk of a higher latency.
In the extreme case however, latency grows so much that commands will timeout;
as a result, the command processing consumes resources even though some commands are not committed to the ledger.

If you choose lower resource limits, you may observe a lower latency, at the cost of lower throughput and
commands getting rejected with the error code ``PARTICIPANT_BACKPRESSURE``.

**Size of connection pools.** Make sure that every node uses a connection pool to communicate with the database.
This avoids the extra cost of creating a new connection on every database query.
Canton chooses a suitable connection pool by default.
Configure the maximum number of connections such that the database is fully loaded, but not overloaded. Allocating
too many database connections will lead to resource waste (each thread costs), context switching and contention on the
database system, slowing the overall system down. You can notice this on the query latencies reported by canton going
up.

Try to observe the ``db-storage.queue`` metrics. If they are large, then the system performance may benefit from
tuning the number of database connections.
Detailed instructions can be found in the Section :ref:`max_connection_settings`.

**Throttling configuration for SequencerClient.**
The ``SequencerClient`` is the component responsible for managing the connection of any member (participant,
mediator, or topology manager) in a Canton network to the domain. Each domain can have multiple sequencers,
and the ``SequencerClient`` connects to one of them. However, there is a possibility that the ``SequencerClient``
can become overwhelmed and struggle to keep up with the incoming messages. To address this issue, a configuration
parameter called ``maximum-in-flight-event-batches`` is available:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/documentation-snippets/sequencer-client-throttling.conf

By setting the ``maximum-in-flight-event-batches`` parameter, you can control the maximum number of event batches
that the system processes concurrently. This configuration helps prevent overload and ensures that the
system can handle the workload effectively.

It's important to note that the value you choose for ``maximum-in-flight-event-batches`` impacts the ``SequencerClient``'s
performance in several ways. A higher value can potentially increase the ``SequencerClient``'s throughput, allowing it to
handle more events simultaneously. However, this comes at the cost of higher memory consumption and longer
processing times for each batch.

On the other hand, a lower value for ``maximum-in-flight-event-batches`` might limit the throughput, as it
can process fewer events concurrently. However, this approach can result in more stable and predictable ``SequencerClient``
behavior.

To monitor the performance of the ``SequencerClient`` and ensure it is operating within the desired limits, you
can observe the metric ``sequencer-client.handler.actual-in-flight-event-batches``. This metric provides the
current value of the in-flight event batches, indicating how close it is to the configured limit. Additionally,
you can also reference the metric ``sequencer-client.handler.max-in-flight-event-batches`` to determine the
configured maximum value.

By monitoring these metrics, you can gain insights into the actual workload being processed and assess whether
it is approaching the specified limit. This information is valuable for maintaining optimal ``SequencerClient``
performance and preventing any potential bottlenecks or overload situations.

**Size of database task queue.** If you are seeing frequent ``RejectedExecutionExceptions`` when Canton queries the database,
increase the size of the task queue, as described in Section :ref:`database_task_queue_full`. The rejection is otherwise
harmless. It just points out that the database is overloaded.

**Database Latency.** Ensure that the database latency is low. The higher the database latency, the lower the actual
bandwidth and the lower the throughput of the system.

**Turn on High-Throughput Sequencer.** The database sequencer has a number of parameters that can be tuned. The trade-off
is low-latency or high-throughput. In the low-latency setting, every submission will be immediately processed as a single
item. In the high-throughput setting, the sequencer will accumulate a few events before writing them together at once.
While the latency added is only a few ms, it does make a difference during development and testing of your Daml applications.
Therefore, the default setting is ``low-latency``. A production deployment with high throughput demand should choose the
``high-throughput`` setting by configuring:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/documentation-snippets/high-throughput-sequencer.conf

There are additional parameters that can in theory be fine-tuned, but we recommend to leave the defaults and use either
high-throughput or low-latency. In our experience, a high-throughput sequencer can handle several thousand submissions
per second.

**JVM heap size.** In case you observe ``OutOfMemoryErrors`` or high overhead of garbage collection, you must increase the heap size of the JVM,
as described in Section :ref:`jvm_arguments`.
Use tools of your JVM provider (such as VisualVM) to monitor the garbage collector to check whether the heap size is tight.

**Size of thread pools.** Every Canton process has a thread pool for executing internal tasks.
By default, the size of the thread-pool is configured as the number of (virtual) cores of the underlying (physical) machine.
If the underlying machine runs other processes (e.g., a database) or if Canton runs inside of a container,
the thread-pool may be too big, resulting in excessive context switching.
To avoid that, configure the size of the thread pool explicitly like this:

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/scala/com/digitalasset/canton/integration/tests/release/CliIntegrationTest.scala
   :start-after: user-manual-entry-begin: SetNumThreads
   :end-before: user-manual-entry-end: SetNumThreads
   :dedent:

As a result, Canton will log the following line:

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/scala/com/digitalasset/canton/integration/tests/release/CliIntegrationTest.scala
   :start-after: user-manual-entry-begin: LogNumThreads
   :end-before: user-manual-entry-end: LogNumThreads
   :dedent:

**Asynchronous commits.** If you are using a Postgres database, configure the participant's ledger API server
to commit database transactions asynchronously by including the following line into your Canton configuration:

.. literalinclude:: /canton/includes/mirrored/scripts/canton-testing/config/participants.conf
   :start-after: user-manual-entry-begin: AsynchronousCommitMode
   :end-before: user-manual-entry-end: AsynchronousCommitMode

**Logging Settings.** Make sure that Canton outputs log messages only at level INFO and above
and turn off immediate log flushing using the ``--log-immediate-flush=false`` commandline flag,
at the risk of missing log entries during a host system crash.

**Replication.** If (and **only if**) using single nodes for participant, sequencer, and/or mediator, replication can be turned off by setting
``replication.enabled = false`` in their respective configuration.

.. warning::

    While replication can be turned off to try to obtain performance gains, it must **not** be disabled when running multiple nodes
    for HA.

.. _caching_configuration:

**Caching Configuration.** In some cases, you might also want to tune caching configurations and either
reduce or increase them, depending on your situation. This can also be helpful if you need to reduce the memory
foot-print of Canton, which can be large, as the default cache configurations are tailored for high-throughput,
high-memory and small transaction sizes.

Generally, the caches that usually matter with respect to size are the contract caches and the in-memory
fan-out event buffer. You can tune these using the following configurations. The values depicted here are
the ones recommended for smaller memory-footprints and are therefore also helpful if you run into out-of-memory
issues:

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/caching-configs.conf
