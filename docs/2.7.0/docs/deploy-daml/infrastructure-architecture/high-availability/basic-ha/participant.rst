.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. enterprise-only::

.. _ha_participant_arch:

Replicating Participant Nodes
-----------------------------

Participant nodes are replicated in an active-passive configuration with a shared database. 

The active node services requests while one or more passive replicas wait in warm-standby mode, ready to take over if the active replica fails.

High-Level System Design
~~~~~~~~~~~~~~~~~~~~~~~~

A logical participant node - shown below - contains multiple physical participant node replicas, all using a shared database. 

Each replica exposes its own Ledger API although these can be hidden by a single Ledger API endpoint running on a highly available load balancer.

.. _participant-ha-system-topology:
.. https://lucid.app/lucidchart/cd96a3a6-e10b-4edc-bfb3-a70e484d7c06
.. image:: participant-ha-system-topology.svg
   :align: center
   :width: 100%

The load balancer configuration contains details of all Ledger API server addresses and the ports for the participant node replicas. Replicas expose their active or passive status via a health endpoint.

Periodically polling the health API endpoint, the load balancer identifies a replica as offline if it is passive. Requests are then *only* sent to the active participant node.

.. IMPORTANT::
  The health endpoint polling frequency can affect the failover duration.

During failover, requests may still go to the former active replica; which rejects them. The application retries until the requests are forwarded to the new active replica.

Shared Database
"""""""""""""""

The replicas require a shared database for the following reasons:

1. To share the command ID deduplication state of the Ledger API command submission service. This prevents double submission of commands in case of failover.
2. To obtain consistent ledger offsets without which the application cannot seamlessly failover to another replica. The database stores ledger offsets in a non-deterministic manner based on the insertion order of publishing events in the multi-domain event log.

Leader Election
~~~~~~~~~~~~~~~

A leader election establishes the active replica. The participant node sets the chosen active replica as single writer to the shared database. 

Exclusive, application-level database locks - tied to the database connection lifetime - enforce the leader election and set the chosen replica as single writer. 

.. NOTE::
  Alternative approaches for leader election, such as Raft, are unsuitable because the leader status can be lost in between the leader check and the use of the shared resource, i.e. writing to the database. Therefore, we cannot guarantee a single writer.

Exclusive Lock Acquisition
""""""""""""""""""""""""""

A participant node replica acquires an exclusive application-level lock (e.g. `Postgres advisory lock <https://www.postgresql.org/docs/11/explicit-locking.html#ADVISORY-LOCKS>`_) which is bound to a particular database connection. The active replica that acquires the lock becomes the leader. The replica then uses the same connection for all writes that are not idempotent. 

.. NOTE::
  Using the same connection for writes ensures that the lock is active while writes are performed.

Lock ID Allocation
""""""""""""""""""

Exclusive application level locks are identified by a 30 bit integer lock id which is allocated based on a scope name and counter. 

The lock counter differentiates locks used in Canton from each other, depending on their usage. The scope name ensures the uniqueness of the lock id for a given lock counter. The allocation process generates a unique lock id by hashing and truncating the scope and counter to 30 bits.

.. NOTE::
  On Oracle, the lock scope is the schema name, i.e. user name. On PostgreSQL, it is the name of the database. 
  
Participant replicas must allocate lock ids and counters consistently. It is, therefore, crucial that replicas are configured with the same storage configuration, e.g. for Oracle using the correct username to allocate the lock ids within the correct scope.

Prevent Passive Replica Activity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. IMPORTANT::
  Passive replicas do not hold the exclusive lock and cannot write to the shared database. 

To avoid passive replicas attempting to write to the database - any such attempt fails and produces an error - we use a coarse-grained guard on domain connectivity and API services.

To prevent the passive replica from processing domain events, and ensure it rejects incoming Ledger API requests, we keep the passive replica disconnected from the domains as a coarse-grained enforcement.

Lock Loss and Failover
""""""""""""""""""""""

If the active replica crashes or loses connection to the database, the lock is released and a passive replica can claim the lock and become active. Any pending writes in the formerly active replica fail due to losing the underlying connection and the corresponding lock.

The active replica has a grace period in which it may rebuild the connection and reclaim the lock to avoid unnecessary failover on short connection interruptions. 

The passive replicas continuously attempt to acquire the lock within a configurable interval. Once the lock is acquired, the participant replication manager sets the state of the successful replica to active.

When a passive replica becomes active, it connects to previously connected domains to resume event processing. The new active replica accepts incoming requests, e.g. on the Ledger API. The former active replica, that is now passive, rejects incoming requests as it can no longer write to the shared database.