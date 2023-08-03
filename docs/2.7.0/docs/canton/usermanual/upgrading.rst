..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _canton_upgrading:

Upgrading
=========

This section covers the processes to upgrade Canton participant and domain nodes. Upgrading Daml
applications is `covered elsewhere <https://docs.daml.com/upgrade/upgrade.html>`_.

As elaborated in the :ref:`versioning guide <canton_versioning>`, new features, improvements
and fixes are released regularly. To benefit from these changes, the Canton-based system
must be upgraded.

There are two key aspects that need to be addressed when upgrading a system:

- Upgrading the Canton binary that is used to run a node.
- Upgrading the protocol version (wire format and semantics of the APIs used between the nodes).

Canton is a distributed system, where no single operator controls all nodes. Therefore,
we must support the situation where nodes are upgraded individually, providing a safe upgrade
mechanism that requires the minimal amount of synchronized actions within a network.

A Canton binary supports :ref:`multiple protocol versions <protocol_version>`, and new protocol
versions are introduced in a backwards compatible way with a new binary
(see :ref:`version table <release-version-to-protocol-version-table>`). Therefore, any upgrade
of a protocol used in a distributed Canton network is done by individually upgrading all binaries
and subsequently changing the protocol version used among the nodes to the
desired one.

The following recipe is a general guide. Before upgrading to a specific version, please check the
individual notes for each version.

This guide also assumes that the upgrade is a minor or a patch release. Major release upgrades might
differ and will be covered separately if necessary.

Please read the entire guide before proceeding, please backup your data before you do any upgrade,
and please test your upgrade carefully before attempting to upgrade your production system.

Upgrade Canton Binary
---------------------

A Canton node consists of one or more processes, where each process is defined by

- A Java Virtual Machine application running a versioned jar of Canton.
- A set of configuration files describing the node that is being run.
- An optional bootstrap script passed via ``--boostrap``, which runs on startup.
- A database (with a specific schema), holding the data of the node.

Therefore, to upgrade the node, you will need to not only replace the jar, but also test that
the configuration files can still be parsed by the new process, that the bootstrap script you
are using is still working, and you need to upgrade the database schema.

Generally, all changes to configuration files should be backwards compatible, and therefore not
be affected by the upgrade process. In rare cases, there might be a minor change to the configuration
file necessary in order to support the upgrade process. Sometimes, fixing a substantial bug
might require a minor breaking change to the API. The same applies to Canton scripts.

The schema in the database is versioned and managed using `Flyway <https://flywaydb.org/>`_. Detecting
and applying changes is done by Canton using that library. Understanding this background can be helpful
to troubleshoot issues.

Preparation
~~~~~~~~~~~

First, please download the new Canton binary that you want to upgrade to and store it on the test
system where you want to test the upgrade process first.

Then, obtain a recent backup of the database of the node and deploy it to a database server
of your convenience, such that **you can test the upgrade process without affecting your production system**.
While we extensively test the upgrade process ourselves, we cannot exclude the eventuality that you are using the system
in a non-anticipated way. Testing is cumbersome, but breaking a production system is worse.

If you are upgrading a participant, then we suggest that you also use an in-memory domain which you can
tear down after you've tested that the upgrade of the participant is working. You might do that by adding
a simple domain definition as a configuration mixin to your participant configuration.

Generally, if you are running an high-availability setup, please take all nodes offline before
performing an upgrade. If the update requires a database migration (check the release notes), avoid
running older and newer binaries in a replicated setup, as the two binaries might expect a different
database layout.

You can upgrade the binaries of a microservice-based domain in any order, as long as you upgrade
the binaries of nodes accessing the same database at the same time. For example, you could upgrade
the binary of a replicated mediator node on one weekend and an active-active database sequencer on
another weekend.

Back Up Your Database
~~~~~~~~~~~~~~~~~~~~~

Before you upgrade the database and binary, please ensure that you have backed up your data,
such that you can roll back to the previous version in case of an issue. You can backup your
data by cloning it. In Postgres, the command is:

.. code:: sql

    CREATE DATABASE newdb WITH TEMPLATE originaldb OWNER dbuser;

When doing this, you need to change the database name and user name in above command to match
your setup.

Test your Configuration
~~~~~~~~~~~~~~~~~~~~~~~

First, let's test that the configuration still works

.. code-block:: bash

    ./bin/canton -v -c storage-for-upgrade-testing.conf -c mynode.conf --manual-start

Here, the files ``storage-for-upgrade-testing.conf`` and ``mynode.conf`` need to be adjusted
to match your case.

If Canton starts and shows the command prompt of the console, then the configuration was
parsed successfully.

The command line option ``--manual-start`` will ensure that the node is not started automatically,
as we first need to migrate the database.

.. _migrating_the_database:

Migrating the Database
~~~~~~~~~~~~~~~~~~~~~~

Canton does not perform a database migration automatically. Migrations
need to be forced. If you start a node with that requires a database migration, you will
observe the following Flyway error:

.. snippet:: migrating_participant
    .. failure:: participant.start()

The database schema definitions are versioned and hashed. This error informs us about the current
database schema version and how many migrations need to be applied.

We can now force the migration to a new schema using:

.. snippet:: migrating_participant
    .. success:: participant.db.migrate()

Please note that you need to ensure that the user account the node is using to access the database
allows to change the database schema. How long the migration takes depends on the version
of the binary (see migration notes), the size of the database and the performance of the database server.

Subsequently, you can successfully start the node

.. snippet:: migrating_participant
    .. success:: participant.start()

Please note that while we've used a participant node here as an example, the behaviour
is the same for all other types of nodes.

Test Your Upgrade
~~~~~~~~~~~~~~~~~

Once your node is up and running, you can test it by running a ping. If you are testing
the upgrade of your participant node, then you might want to connect to the test domain

.. snippet:: migrating_participant
    .. success:: testdomain.start()
    .. success:: participant.domains.connect_local(testdomain)

If you did the actual upgrade of the production instance, then you would just reconnect
to the current domain before running the ping:

.. snippet:: migrating_participant
    .. success:: participant.domains.reconnect_all()

You can check that the domain is up and running using

.. snippet:: migrating_participant
    .. success:: participant.domains.list_connected()
    .. assert:: RES.length == 1

Finally, you can ping the participant to see if the system is operational

.. snippet:: migrating_participant
    .. success:: participant.health.ping(participant)

Version Specific Notes
~~~~~~~~~~~~~~~~~~~~~~

Upgrade to Release 2.7
^^^^^^^^^^^^^^^^^^^^^^
Version 2.7 will slightly extend the database schema used. Therefore, you will have to perform the :ref:`database migration steps <migrating_the_database>`.
Alternatively, you can enable the new "migrate and start" mode of Canton, which will trigger an automatic update of the database schema
when a new minor version is deployed.
This mode can be enabled by setting the appropriate storage parameter:

.. code:: bash

    canton.X.Y.storage.parameters.migrate-and-start = yes

In order to benefit from the new security features brought by protocol version 5,
you will have to :ref:`upgrade the domain accordingly <canton_domain_protocol_version_upgrading>`.

Breaking changes around console commands
""""""""""""""""""""""""""""""""""""""""

**Key rotation**
The command keys.secret.rotate_wrapper_key now returns a different error code.
An INVALID_WRAPPER_KEY_ID error has been replaced by an INVALID_KMS_KEY_ID error.

**Adding sequencer connection**
The configuration of the Sequencer Client has been updated to accommodate multiple sequencers and their endpoints:
method `addConnection` has been renamed to `addEndpoints` to better reflect the fact that it modifies an endpoint for the sequencer.

Hence, command to add a new sequencer connection to the mediator would be changed to:

.. code:: bash

    mediator1.sequencer_connection.modifyConnections(
        _.addEndpoints(SequencerAlias.Default, connection)
    )


Unique Contract Keys Deprecation
""""""""""""""""""""""""""""""""
The unique-contract-keys parameters for both participant and domain nodes are now marked as deprecated.
As of this release, the meaning and default value (true) remain unchanged.
However, contract key uniqueness will not be available in the next major version, featuring multi-domain connectivity.
If you are already setting this key to false explicitly (preview), this behavior will be the default one after the configuration key is removed.
If you don't explicitly set this value to false, you are encouraged to evaluate evolving your existing applications and services to avoid relying on this feature.
You can read more on the topic in the :ref:`documentation <canton_keys>`.

Causality Tracking
""""""""""""""""""
An obsolete early access feature to enable causality tracking, related to preview multi-domain, was removed. If you enabled it, you need to remove the following config lines, as they will not compile anymore:

.. code:: bash

    participants.participant.init.parameters.unsafe-enable-causality-tracking = true
    participants.participant.parameters.enable-causality-tracking = true

Besu and Fabric drivers
"""""""""""""""""""""""
In order to allow for independent updates of the different components, we have  separated out the drivers into a separate jar, which needs to be loaded into a separate classpath.
As a result, deployments that use Fabric or Besu need to additionally download the jar and place it in the appropriate directory.
Please :ref:`consult the installation documentation <canton-enterprise-drivers>` on how to obtain this additional jar.

Ledger API error codes
""""""""""""""""""""""

The error codes and metadata of GRPC errors returned as part of failed command interpretation from the Ledger API have been updated to include more information.
Previously, most errors from the Daml engine would be given as either `GenericInterpretationError` or `InvalidArgumentInterpretationError`.
They now all have their own codes and encode relevant information in the GRPC Status metadata.
Specific error changes are as follows:
* `GenericInterpretationError` (Code: `DAML_INTERPRETATION_ERROR`) with GRPC status `FAILED_PRECONDITION` is now split into:

    * `DisclosedContractKeyHashingError` (Code: `DISCLOSED_CONTRACT_KEY_HASHING_ERROR`) with GRPC status `FAILED_PRECONDITION`
    * `UnhandledException` (Code: `UNHANDLED_EXCEPTION`) with GRPC status `FAILED_PRECONDITION`
    * `InterpretationUserError` (Code: `INTERPRETATION_USER_ERROR`) with GRPC status `FAILED_PRECONDITION`
    * `TemplatePreconditionViolated` (Code: `TEMPLATE_PRECONDITION_VIOLATED`) with GRPC status `INVALID_ARGUMENT`

* `InvalidArgumentInterpretationError` (Code: `DAML_INTERPRETER_INVALID_ARGUMENT`) with GRPC status `INVALID_ARGUMENT` is now split into:

    * `CreateEmptyContractKeyMaintainers` (Code: `CREATE_EMPTY_CONTRACT_KEY_MAINTAINERS`) with GRPC status `INVALID_ARGUMENT`
    * `FetchEmptyContractKeyMaintainers` (Code: `FETCH_EMPTY_CONTRACT_KEY_MAINTAINERS`) with GRPC status `INVALID_ARGUMENT`
    * `WronglyTypedContract` (Code: `WRONGLY_TYPED_CONTRACT`) with GRPC status `FAILED_PRECONDITION`
    * `ContractDoesNotImplementInterface` (Code: `CONTRACT_DOES_NOT_IMPLEMENT_INTERFACE`) with GRPC status `INVALID_ARGUMENT`
    * `ContractDoesNotImplementRequiringInterface` (Code: `CONTRACT_DOES_NOT_IMPLEMENT_REQUIRING_INTERFACE`) with GRPC status `INVALID_ARGUMENT`
    * `NonComparableValues` (Code: `NON_COMPARABLE_VALUES`) with GRPC status `INVALID_ARGUMENT`
    * `ContractIdInContractKey` (Code: `CONTRACT_ID_IN_CONTRACT_KEY`) with GRPC status `INVALID_ARGUMENT`
    * `ContractIdComparability` (Code: `CONTRACT_ID_COMPARABILITY`) with GRPC status `INVALID_ARGUMENT`
    * `InterpretationDevError` (Code: `INTERPRETATION_DEV_ERROR`) with GRPC status `FAILED_PRECONDITION`

* The `ContractKeyNotVisible` error (previously encapsulated by `GenericInterpretationError`) is now transformed into a `ContractKeyNotFound` to avoid information leaking.

Upgrade to Release 2.5
^^^^^^^^^^^^^^^^^^^^^^
Version 2.5 will slightly extend the database schema used. Therefore, you will have to perform the
database migration steps.

Some configuration arguments have changed. While rewrite rules are in-place for backwards compatibility,
we recommend that you test your configuration prior to upgrading and update the settings to avoid
using deprecated flags.

IMPORTANT: Existing domains and domain managers need to be reconfigured to keep on working. It is important
that before attempting the binary upgrade, you configure the currently used protocol version explicitly:

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/enforce-protocol-version-domain-2.5.conf

Nodes persist the static domain parameters used during initialization now. Version 2.5 is the last version
that will require this explicit configuration setting during upgrading.

If you started the domain node accidentally before changing your configuration, your participants won't be able to
reconnect to the domain, as they will fail with a message like:

    DOMAIN_PARAMETERS_CHANGED(9,d5dfa5ce): The domain parameters have changed

To recover from this, you need to force a reset of the stored static domain parameters using:

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/reset-protocol-version-domain-2.5.conf

In order to benefit from protocol version 4, you will have to :ref:`upgrade the domain accordingly <canton_domain_protocol_version_upgrading>`.

Upgrade to Release 2.4
^^^^^^^^^^^^^^^^^^^^^^
Version 2.4 will slightly extend the database schema used. Therefore, you will have to perform the
database migration steps.

There have been a few consistency improvements to some console commands. In particular, we have renamed
a few of the arguments and changed some of their types. As we have included automatic conversion
and the change only affects special arguments (mainly timeouts), your script should still work. However,
we recommend that you test your scripts for compilation issues. Please check the detailed release
notes on the specific changes and their impact.

There was no change to the protocol. Participants / domains running 2.3 can also run 2.4, as
both versions use the same protocol version.

Upgrade to Release 2.3
^^^^^^^^^^^^^^^^^^^^^^
Version 2.3 will slightly extend the database schema used. Therefore, you will have to perform the
database migration steps.

Furthermore, the Canton binary with version 2.3 has introduced a new protocol version 3, and deprecated the
previous protocol version 2. In order to keep a node operational that is using protocol version 2,
you need to turn on support for the deprecated protocol version.

On the participant, you need to turn on support for deprecated protocols explicitly:

.. code:: bash

    canton.participants.myparticipant.parameters.minimum-protocol-version = 2.0.0

The default setting have changed to use protocol 3, while existing domains run protocol 2.
Therefore, if you upgrade the binary on domain and domain manager nodes, you need to explicitly
set the protocol version as follows:

.. code:: bash

    canton.domains.mydomain.init.domain-parameters.protocol-version = 2.0.0

**You cannot upgrade the protocol of a deployed domain!** You need to keep it running with the existing protocol.
Please follow the protocol upgrade guide to learn how to introduce a new protocol version.

Change the Canton Protocol Version
----------------------------------

The Canton protocol is defined by the semantics and the wire-format used by the nodes
to communicate to each other. In order to process transactions, all nodes must be able
to understand and speak the same protocol.

Therefore, a new protocol can be introduced only once all nodes have been upgraded
to a binary that can run the version.

.. _canton_domain_protocol_version_upgrading:

Upgrade the Domain to a new Protocol Version
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A domain is tied to a protocol version. This protocol version is configured when
the domain is initialized and cannot be changed afterwards. Therefore, **you can
not upgrade the protocol version of a domain**. Instead, you deploy a new domain
side by side of the old domain process.

This applies to all domain members, be it sequencer, mediator or topology manager.

Please note that currently, the domain-id cannot be preserved during upgrades.
The new domain must have a different domain-id due to the fact that the participant
internally is associating a domain connection with a domain-id, and that association
must be unique.

Therefore, the protocol upgrade process boils down to:

- Deploy a new domain next to the old domain. Ensure that the new domain is using the desired protocol version.
  Ensure that you are using different databases (or at least different schemas in the same database), channel names, smart contract addresses etc.
  It must be a completely separate domain (albeit you can reuse your DLT backend as long
  as you use different sequencer contract addresses or Fabric channels).
- Instruct the participants individually using the hard domain migration to use the new domain.

Note: to use the same database with different schemas for the old and the new domain, set the `currentSchema` either in the JDBC URL or as a parameter in `storage.config.properties`.

Hard Domain Connection Upgrade
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A hard domain connection upgrade can be performed using the :ref:`respective migration command <repair.migrate_domain>`.
Again, please ensure that you have appropriate backups in place and that you have tested this procedure before applying
it to your production system. You will have to enable these commands using a special config switch:

.. code:: bash

    canton.features.enable-repair-commands=yes

The process of a hard migration is quite straightforward. Assuming that we have several participants,
all connected to a domain named ``olddomain``, then ensure that there are no pending transactions.
You can do that by either controlling your applications, or by
:ref:`setting the resource limits <resources.set_resource_limits>` to 0 on all participants:

.. snippet:: migrating_protocol
    .. assert:: { participant.db.migrate(); true }
    .. assert:: { participant.start(); true }
    .. assert:: { participant.domains.connect_local(olddomain); true }
    .. success:: participant.resources.set_resource_limits(ResourceLimits(Some(0), Some(0)))

This will reject all commands and finish processing the pending commands. Once you are sure that
your participant node is idle, disconnect the participant node from the old domain
connection:

.. snippet:: migrating_protocol
    .. success:: participant.domains.disconnect("olddomain")

Test that the domain is disconnected by checking the list of active connections:

.. snippet:: migrating_protocol
    .. success:: participant.domains.list_connected()
    .. assert:: participant.domains.list_connected().isEmpty

This is now a good time to perform a backup of the database before proceeding:

.. code:: sql

    CREATE DATABASE newdb WITH TEMPLATE originaldb OWNER dbuser;

Next, we want to run the migration step. For this, we need to run the ``repair.migrate_domain`` command.
The command expects two input arguments: The alias of the source domain and a domain connection
configuration describing the new domain.

In order to build a domain connection config, we can just type

.. snippet:: migrating_protocol
    .. success(output=5):: val config = DomainConnectionConfig("newdomain", GrpcSequencerConnection.tryCreate("https://127.0.0.1:5018"))

where the URL should obviously point to the correct domain. If you are testing the upgrade
process locally in a single Canton process using a target domain named ``newdomain`` (which is
what we are doing in this example here ...), you can grab the connection details using

.. snippet:: migrating_protocol
    .. success(output=5):: val config = DomainConnectionConfig("newdomain", newdomain.sequencerConnection)

Now, using this configuration object, we can trigger the hard domain connection migration using

.. snippet:: migrating_protocol
    .. success:: participant.repair.migrate_domain("olddomain", config)

This command will register the new domain and re-associate the contracts tied to ``olddomain`` to
the new domain.

Once all participants have performed the migration, they can reconnect to the domain

.. snippet:: migrating_protocol
    .. success:: participant.domains.reconnect_all()

Now, the new domain should be connected:

.. snippet:: migrating_protocol
    .. success:: participant.domains.list_connected()
    .. assert:: participant.domains.list_connected().map(_.domainAlias.unwrap) == Seq("newdomain")

As we've previously set the resource limits to 0, we need to reset this back

.. snippet:: migrating_protocol
    .. success:: participant.resources.set_resource_limits(ResourceLimits(None, None))

Finally, we can test that the participant can process a transaction by running a ping on the new domain

.. snippet:: migrating_protocol
    .. success:: participant.health.ping(participant)

.. note::

    Note that currently, the hard migration is the only supported way to migrate a production system.
    This is due to the fact that unique contract keys are restricted to a single domain.

While the domain migration command is mainly used for upgrading, it can also be used to recover
contracts associated to a broken domain. Domain migrations can be performed back and forth,
allowing to roll back in case of issues.

After the upgrade, the participants may report mismatch between commitments during the first commitment
exchange, as they might have performed the migration at slightly different times. The warning should
eventually stop once all participants are back up and connected.

Expected Performance
^^^^^^^^^^^^^^^^^^^^

Performance-wise, we can note the following: when we migrate contracts, we write directly into
the respective event logs. This means that on the source domain, we insert transfer-out, while
we write a transfer-in and the contract into the target domain. Writing this information is substantially
faster than any kind of transaction processing (several thousand migrations per second on a
single cpu / 16 core test server). However, with very large datasets, the process can
still take quite some time. Therefore, we advise to measure the time the migration takes during
the upgrade test in order to understand the necessary downtime required for the migration.

Furthermore, upon reconnect, the participant needs to recompute the new set of commitments. This can take
a while for large numbers of contracts.

Soft Domain Connection Upgrade
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note ::

    The soft domain connection upgrade is currently only supported as an alpha feature.

The hard domain connection upgrade requires coordination among all participants in a network. The
soft domain connection upgrade is operationally much simpler, and can be leveraged using multi-domain
support (which exists as a pre-alpha feature only for now). By turning off non-unique contract keys,
participants can connect to multiple domains and transfer contracts between domains. This allows us to avoid using the ``repair.migrate_domain`` step.

Assuming the same setup as before, where the participant is connected to the old domain,
we can just connect it to the new domain

.. snippet:: soft_migration_with_transfer
    .. assert:: { participant.db.migrate(); true }
    .. assert:: { participant.start(); true }
    .. assert:: { participant.domains.connect_local(olddomain); true }
    .. success:: participant.domains.connect_local(newdomain)
    .. assert:: participant.domains.list_connected().map(_.domainAlias.unwrap).toSet == Set("newdomain", "olddomain")

Give the new connection precedence over the old connection by changing the ``priority`` flag of the new
domain connection:

.. snippet:: soft_migration_with_transfer
    .. success:: participant.domains.modify("newdomain", _.copy(priority=10))

You can check the priority settings of the domains using

.. snippet:: soft_migration_with_transfer
    .. success:: participant.domains.list_registered().map { case (c,_) => (c.domain, c.priority) }

Existing contracts will not automatically move over to the new domain. The domain router will
pick the domain by minimizing the number of transfers and the priority. Therefore, most contracts
will remain on the old domain without additional action. However, by using
the :ref:`transfer command <transfer.execute>`, contracts can be moved over to the new domain
one by one, such that eventually, all contracts are associated with the new domain, allowing
the old domain to be decommissioned and turned off.

The soft upgrade path provides a smooth user experience that does not require a hard migration of the domain connection
synchronised across all participants. Instead, participants upgrade individually, whenever they
are ready, allowing them to reverse the process if needed.
