..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. enterprise-only::

.. _ha_user_manual:

High Availability Usage
=======================

This section looks at some of the components already mentioned and supplies useful Canton commands.

Synchronizer Manager
--------------------

As explained in :ref:`domain-architecture`, a synchronizer internally comprises a sequencer, a mediator, and a topology manager.
When running a simple synchronizer (configured with ``canton.domains``, as shown in most of the examples), this node will be running a topology manager,
a sequencer, and a mediator all internally.

It is possible to run sequencer(s) and mediator(s) as standalone nodes, as will be explained in the next topics.
But to complete the synchronizer setup, it is also necessary to run a synchronizer manager node (configured with ``canton.domain-managers``),
which takes care of the bootstrapping of the distributed synchronizer setup and runs the topology manager.

The synchronizer bootstrapping process is explained in :ref:`domain_bootstrapping`.

The synchronizer manager can be made highly available by running an active node and an arbitrary number of replicated passive nodes
on hot standby, similar to the mediator HA mechanism (see below). The only requirement is shared storage between all the synchronizer
manager instances, which must be either Postgres or Oracle. Nodes automatically handle their state and become active/passive
whenever the active instance fails, such that from a configuration perspective this is entirely transparent.

An example configuration of a standalone HA synchronizer manager node could therefore look like this:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/external-domain-managers.conf


In a replicated setup, only the active synchronizer manager can be used to issue topology transactions (for instance bootstrapping a synchronizer or onboarding new mediators/sequencers).
To find out if a synchronizer manager is active, one can run `domainManager1.health.active` in the Canton console (for a synchronizer manager node named `domainManager1`).
Another way to avoid this manual check is to place a load balancer in front of the synchronizer managers and let it pick the active instance.
See :ref:`Load Balancer Configuration <load-balancer-configuration>` for more information.

Commands that indirectly use the synchronizer manager (for instance connecting a participant to a synchronizer) will automatically be picked up by the active synchronizer manager, so this is only relevant when
issuing commands directly against a specific synchronizer manager.

HA Setup on Oracle
------------------

The HA approach that is used by the participant, mediator, and sequencer nodes
requires additional permissions to be granted on Oracle to the database user.

All replicas of a node must be configured with the same DB user
name. The DB user must have the following permissions granted::

  GRANT EXECUTE ON SYS.DBMS_LOCK TO $username
  GRANT SELECT ON V_$LOCK TO $username
  GRANT SELECT ON V_$MYSTAT TO $username

In the above commands the ``$username`` must be replaced with the configured DB
user name. These permissions allow the DB user to request application-level
locks on Oracle, as well as to query the state of locks and its own session
information.

For a high-availability deployment the underlying Oracle store must be set up in
a highly available manner (for example, using Oracle RAC or Veritas VCS).

Oracle high availability is supported only when the database presents to the
Canton nodes as a single, logical Oracle database. There is no support for
horizontal scaling through sharding or other multi-database RAC features beyond
simple HA clustering.

.. _ha_mediator:

Mediator
--------

The mediator service uses a hot standby mechanism with an arbitrary number of replicas.
During a mediator fail-over, all in-flight requests get purged.
As a result, these requests will timeout at the participants.
The applications need to retry the underlying commands.

Running a Stand-Alone Mediator Node
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A synchronizer may be statically configured with a single embedded mediator node or it may be configured to work with external mediators.
Once the synchronizer has been initialized further mediators can be added at runtime.

By default, a synchronizer will run an embedded mediator node itself.
This is useful in simple deployments where all synchronizer functionality can be co-located on a single host.
In a distributed setup where synchronizer services are operated over many machines,
you can instead configure a synchronizer manager node and bootstrap the synchronizer with mediator(s) running externally.

Mediator nodes can be defined in the same manner as Canton participants and synchronizers.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/external-mediators.conf
   :start-after: user-manual-entry-begin: ExternalMediatorNode
   :end-before: user-manual-entry-end: ExternalMediatorNode
   :dedent:

When the synchronizer starts it will automatically provide the embedded mediator information about the synchronizer.
External mediators have to be initialized using runtime administration in order to complete the synchronizer initialization.

HA Configuration
~~~~~~~~~~~~~~~~

HA mediator support is only available in the Daml Enterprise version of Canton and
only PostgreSQL and Oracle-based storage are supported for HA.

Mediator node replicas are configured in the Canton configuration file as
individual stand-alone mediator nodes with two required changes for each
mediator node replica:

- Using the same storage configuration to ensure access to the shared database.
- Set ``replication.enabled = true`` for each mediator node replica.

.. note::

    Starting from canton 2.4.0, mediator replication is enabled by default when using supported storage.

Only the active mediator node replica has to be initialized through the synchronizer
bootstrap commands. The passive replicas observe the initialization via the
shared database.

Further replicas can be started at runtime without any additional setup. They
remain passive until the current active mediator node replica fails.

.. _ha_sequencer:

Sequencer
---------

The database-based sequencer can be horizontally scaled and placed behind a load balancer to provide
high availability and performance improvements.

Deploy multiple sequencer nodes for the synchronizer with the following configuration:

 - All sequencer nodes share the same database so ensure that the storage configuration for each sequencer matches.
 - All sequencer nodes must be configured with `high-availability.enabled = true`.

.. note::

    Starting from Canton 2.4.0, sequencer high availability is enabled by default when using supported storage.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/external-ha-sequencers.conf
   :start-after: user-manual-entry-begin: SequencerHAConfig
   :end-before: user-manual-entry-end: SequencerHAConfig

The synchronizer node only supports embedded sequencers, so a distributed setup using a synchronizer manager node must then be
configured to use these sequencer nodes by pointing it at these external services.

Once configured the synchronizer must be bootstrapped with the new external sequencer using the
:ref:`bootstrap_synchronizer <domain_bootstrapping>` operational process.
These sequencers share a database so just use a single instance for bootstrapping and the replicas
will come online once the shared database has a sufficient state for starting.

As these nodes are likely running in separate processes you could run this command entirely externally using a remote
administration configuration.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/external-ha-sequencers-remote-admin.conf
   :start-after: user-manual-entry-begin: SequencerHARemoteConfig
   :end-before: user-manual-entry-end: SequencerHARemoteConfig

There are two methods available for exposing the horizontally scaled sequencer instances to participants.

.. _total_node_count:

Total Node Count
~~~~~~~~~~~~~~~~
The ``sequencer.high-availability.total-node-count`` parameter is used to divide up time among the database sequencers.
The parameter should not be changed once a set of sequencer nodes has been deployed. Because each message sequenced must
have a unique timestamp, a sequencer node will use timestamps `modulo` the ``total-node-count`` plus its own index to create timestamps that do not conflict with other sequencer nodes while sequencing the messages in a parallel
database insertion process. Canton uses microseconds, which yields a theoretical max throughput of 1 million messages
per second per synchronizer. Now, this theoretical throughput is divided equally among all sequencer nodes
(``total-node-count``). Therefore, if you set ``total-node-count`` too high, then a sequencer might not be able to
operate at the maximum theoretical throughput. We recommend keeping the default value of ``10``, as all above explanations
are only theoretical and we have not yet seen a database/hard disk that can handle the theoretical throughput.
Also note that a message might contain multiple events, such that we are talking about high numbers here.

External load balancer
~~~~~~~~~~~~~~~~~~~~~~

Using a load balancer is recommended when you have a http2+grpc supporting load balancer available, and can't/don't
want to expose details of the backend sequencers to clients.
An advanced deployment could also support elastically scaling the number of sequencers available and dynamically
reconfigure the load balancer for this updated set.

An example `HAProxy <http://www.haproxy.org/>`__ configuration for exposing GRPC services without TLS looks like::

  frontend domain_frontend
    bind 1234 proto h2
    default_backend domain_backend

  backend domain_backend
    option httpchk
    http-check connect
    http-check send meth GET uri /health
    balance roundrobin
    server sequencer1 sequencer1.local:1234 proto h2 check port 8080
    server sequencer2 sequencer2.local:1234 proto h2 check port 8080
    server sequencer3 sequencer3.local:1234 proto h2 check port 8080

Please note that for quick failover, you also need to add HTTP health checks, as
otherwise, you have to wait for the TCP timeout to occur before failover happens. The public API of the sequencer
exposes the standard `GRPC health endpoints <https://github.com/grpc/grpc/blob/master/doc/health-checking.md>`__, but
these are currently not supported by HAProxy, hence you need to fall back on the HTTP/health endpoint.

Client-side load balancing
~~~~~~~~~~~~~~~~~~~~~~~~~~

Using client-side load balancing is recommended where an external load-balancing service is unavailable (or lacks http2+grpc
support), and the set of sequencers is static and can be configured at the client.

To simply specify multiple sequencers use the ``domains.connect_multi`` console command when registering/connecting to the synchronizer::

  myparticipant.domains.connect_multi(
    "my_domain_alias",
    Seq("https://sequencer1.example.com", "https://sequencer2.example.com", "https://sequencer3.example.com")
  )

See the :ref:`sequencer connectivity documentation <sequencer_connections>` for more details on how to add many sequencer URLs
when combined with other synchronizer connection options.
The synchronizer connection configuration can also be changed at runtime to add or replace configured sequencer connections.
Note the synchronizer will have to be disconnected and reconnected at the participant for the updated configuration to be used.

Participant
-----------

High availability of a participant node is achieved by running multiple
participant node replicas that have access to a shared database.

Participant node replicas are configured in the Canton configuration file as
individual participants with two required changes for each participant node
replica:

- Using the same storage configuration to ensure access to the shared database.
  Only PostgreSQL and Oracle-based storage is supported for HA. For Oracle it is crucial that the participant replicas
  use the same username to access the shared database.
- Set ``replication.enabled = true`` for each participant node replica.

.. note::

    Starting from Canton 2.4.0, participant replication is enabled by default when using supported storage.


Synchronizer Connectivity during Fail-over
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

During fail-over from one replica to another, the new active replica re-connects to all configured synchronizers for which
``manualConnect = false``. This means if the former active replica was manually connected to a synchronizer, this synchronizer
connection is not automatically re-established during fail-over but must be performed manually again.

Manual Trigger of a Fail-over
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fail-over from the active to a passive replica is done automatically when the active replica has a failure, but one can also initiate a graceful fail-over
with the following command:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/ReplicatedParticipantTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: SetPassive
   :end-before: user-manual-entry-end: SetPassive
   :dedent:

The command succeeds if there is at least another passive replica that takes
over from the current active replica, otherwise the active replica remains
active.

.. _load-balancer-configuration:

Load Balancer Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Many replicated participants can be placed behind an appropriately sophisticated load balancer that will by health checks
determine which participant instance is active and direct ledger and admin api requests to that instance appropriately.
This makes participant replication and failover transparent from the perspective of the ledger-api application or canton console
administering the logical participant, as they will simply be pointed at the load balancer.

Participants should be configured to expose an "IsActive" health status on our health HTTP server using the following
monitoring configuration:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/health-check-is-active.conf
   :start-after: user-manual-entry-begin: IsActiveHealthCheck
   :end-before: user-manual-entry-end: IsActiveHealthCheck

Once running this server will report a http 200 status code on a http/1 GET request to `/health` if the participant
is currently the active replica.
Otherwise, an error will be returned.

To use a load balancer it must support http/1 health checks for routing requests on a separate http/2 (GRPC) server.
This is possible with `HAProxy <http://www.haproxy.org/>`__ using the following example configuration::

  global
      log stdout format raw local0

  defaults
      log global
      mode http
      option httplog
      # enabled so long running connections are logged immediately upon connect
      option logasap

  # expose the admin-api and ledger-api as separate servers
  frontend admin-api
      bind :15001 proto h2
      default_backend admin-api

  backend admin-api
      # enable http health checks
      option httpchk
      # required to create a separate connection to query the load balancer.
      # this is particularly important as the health HTTP server does not support h2
      # which would otherwise be the default.
      http-check connect
      # set the health check uri
      http-check send meth GET uri /health

      # list all participant backends
      server participant1 participant1.lan:15001 proto h2 check port 8080
      server participant2 participant2.lan:15001 proto h2 check port 8080
      server participant3 participant3.lan:15001 proto h2 check port 8080

  # repeat a similar configuration to the above for the ledger-api
  frontend ledger-api
      bind :15000 proto h2
      default_backend ledger-api

  backend ledger-api
      option httpchk
      http-check connect
      http-check send meth GET uri /health

      server participant1 participant1.lan:15000 proto h2 check port 8080
      server participant2 participant2.lan:15000 proto h2 check port 8080
      server participant3 participant3.lan:15000 proto h2 check port 8080
