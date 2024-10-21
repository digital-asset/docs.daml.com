..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _canton_upgrading:

Upgrade To a New Release
========================

This section covers the processes to upgrade Canton participant nodes and sync domains.
Upgrading Daml applications is covered `elsewhere <https://docs.daml.com/upgrade/upgrade.html>`_.

As elaborated in the :ref:`versioning guide <canton_versioning>`, new features, improvements
and fixes are released regularly. To benefit from these changes, the Canton-based system
must be upgraded.

There are two key aspects that need to be addressed when upgrading a system:

- :ref:`Upgrading the Canton binary<upgrade_canton_binary>` that is used to run a node.
- :ref:`Upgrading the protocol version<change_pv>` that defines how nodes interact with each other.

Canton is a distributed system, where no single operator controls all nodes. Therefore,
we must support the situation where nodes are upgraded individually, providing a safe upgrade
mechanism that requires the minimal amount of synchronized actions within a network.

A Canton binary supports :ref:`multiple protocol versions <protocol_version>`, and new protocol
versions are introduced in a backward-compatible way with a new binary
(see :ref:`version table <release-version-to-protocol-version-table>`). Therefore, any upgrade
of a protocol used in a distributed Canton network is done by individually upgrading all binaries
and subsequently changing the protocol version used among the nodes to the
desired one.

The following is a general guide. Before upgrading to a specific version, please check the
individual notes for each version.

This guide also assumes that the upgrade is a minor or a patch release. Major release upgrades might
differ and will be covered separately if necessary.

.. warning::

    Upgrading requires care and preparation.
      * **Please back up your data before any upgrade.**
      * **Please test your upgrade thoroughly before attempting to upgrade your production system.**

.. _upgrade_canton_binary:

Upgrade Canton Binary
---------------------

A Canton node consists of one or more processes, where each process is defined by

- A Java Virtual Machine application running a versioned JAR of Canton.
- A set of configuration files describing the node that is being run.
- An optional bootstrap script passed via ``--boostrap``, which runs on startup.
- A database (with a specific schema), holding the data of the node.

To upgrade the node,

#. Replace the Canton binary (which contains the Canton JAR).
#. Test that the configuration files can still be parsed by the new process.
#. Test that the bootstrap script you are using is still working.
#. Upgrade the database schema.

Generally, all changes to configuration files should be backward compatible, and therefore not
be affected by the upgrade process. In rare cases, there might be a minor change to the configuration
file necessary in order to support the upgrade process. Sometimes, fixing a substantial bug
might require a minor breaking change to the API. The same applies to Canton scripts.

The schema in the database is versioned and managed using `Flyway <https://flywaydb.org/>`_. Detecting
and applying changes is done by Canton using that library. Understanding this background can be helpful
to troubleshoot issues.

Preparation
~~~~~~~~~~~

First, please download the new Canton binary that you want to upgrade to and store it on the test
system where you plan to test the upgrade process.

Then, obtain a recent backup of the database of the node and deploy it to a database server
of your convenience, such that **you can test the upgrade process without affecting your production system**.
While we extensively test the upgrade process ourselves, we cannot exclude the eventuality that you are using the system
in a non-anticipated way. Testing is cumbersome, but breaking a production system is worse.

If you are upgrading a participant, then we suggest that you also use an in-memory sync domain which you can
tear down after you have tested that the upgrade of the participant is working. You might do that by adding
a simple sync domain definition as a configuration mixin to your participant configuration.

Generally, if you are running a high-availability setup, please take all nodes offline before
performing an upgrade. If the update requires a database migration (check the release notes), avoid
running older and newer binaries in a replicated setup, as the two binaries might expect a different
database layout.

You can upgrade the binaries of a microservice-based sync domain in any order, as long as you upgrade
the binaries of nodes accessing the same database at the same time. For example, you could upgrade
the binary of a replicated mediator node on one weekend and an active-active database sequencer on
another weekend.

Back Up Your Database
~~~~~~~~~~~~~~~~~~~~~

Before you upgrade the database and binary, please ensure that you have backed up your data,
such that you can roll back to the previous version in case of an issue. You can back up your
data by cloning it. In Postgres, the command is:

.. code:: sql

    CREATE DATABASE newdb WITH TEMPLATE originaldb OWNER dbuser;

When doing this, you need to change the database name and user name in above command to match
your setup.

.. _test-your-config:

Test your Configuration
~~~~~~~~~~~~~~~~~~~~~~~

Test that the configuration still works

.. code-block:: bash

    ./bin/canton -v -c storage-for-upgrade-testing.conf -c mynode.conf --manual-start

Here, the files ``storage-for-upgrade-testing.conf`` and ``mynode.conf`` need to be adjusted
to match your case.

If Canton starts and shows the command prompt of the console, then the configuration was
parsed successfully.

The command line option ``--manual-start`` prevents the node from starting up automatically,
as we first need to migrate the database.

.. _migrating_the_database:

Migrating the Database
~~~~~~~~~~~~~~~~~~~~~~

Canton does not perform a database migration automatically. Migrations
need to be forced. If you start a node that requires a database migration, you will
observe the following Flyway error:

.. snippet:: migrating_participant
    .. failure:: participant.start()

The database schema definitions are versioned and hashed. This error informs us about the current
database schema version and how many migrations need to be applied. This check runs at
startup, so if the node starts, the migrations was successful.

We can now force the migration to a new schema using:

.. snippet:: migrating_participant
    .. success:: participant.db.migrate()

You can also :ref:`configure the migrations to be applied automatically <migrate_and_start_mode>`.
Please note that you need to ensure that the user account the node is using to access the database
allows to change the database schema. How long the migration takes depends on the version
of the binary (see migration notes), the size of the database and the performance of the database server.

We recommend cleaning up your database before you start your node. On Postgres, run

.. code:: sql

    VACUUM FULL;

Otherwise, the restart may take a long time while the database is cleaning itself up.

Subsequently, you can successfully start the node

.. snippet:: migrating_participant
    .. success:: participant.start()

Please note that the procedure remains the same for all other types of nodes,
with a participant node used here as an example.

Test Your Upgrade
~~~~~~~~~~~~~~~~~

Once your node is up and running, you can test it by running a ping. If you are testing
the upgrade of your participant node, then you might want to connect to the test sync domain

.. snippet:: migrating_participant
    .. success:: testdomain.start()
    .. success:: participant.domains.connect_local(testdomain)

If you did the actual upgrade of the production instance, then you would just reconnect
to the current sync domain before running the ping:

.. snippet:: migrating_participant
    .. success:: participant.domains.reconnect_all()

You can check that the sync domain is up and running using

.. snippet:: migrating_participant
    .. success:: participant.domains.list_connected()
    .. assert:: RES.length == 1

Finally, you can ping the participant to see if the system is operational

.. snippet:: migrating_participant
    .. success:: participant.health.ping(participant)

The ping command creates two contracts between the admin parties, then exercises and archives them -- providing an end-to-end test of ledger functionality.

Version Specific Notes
~~~~~~~~~~~~~~~~~~~~~~

.. _upgrade_to_2.9:

Upgrade to Release 2.9
^^^^^^^^^^^^^^^^^^^^^^

Protocol Versions
"""""""""""""""""
The recommended protocol version is 5 (see :ref:`here <protocol_version>` for more information about protocol versions).

Version 2.9 does not offer support for protocol versions 3 and 4.
If your sync domain is running one of these protocol versions, upgrade as described :ref:`below <one_step_migration>`.

Protocol version should be set explicitly
"""""""""""""""""""""""""""""""""""""""""
Until now, sync domains were configured to pick the latest protocol version by default.
Since the protocol version is an important parameter of the sync domain, having this value set behind
the scenes caused unwanted behavior.

You now must specify the protocol version for your sync domain:

.. code:: text

    myDomain {
        init.domain-parameters.protocol-version = 5
    }

For a domain manager:

.. code:: text

    domainManager {
        init.domain-parameters.protocol-version = 5
    }


Deactivated sync domain data cleanup
""""""""""""""""""""""""""""""""""""
Version 2.9 adds a new repair command :ref:`participant.repair.purge_deactivated_domain <repair.purge_deactivated_domain>`
to delete data of a defunct domain.

Using this command is recommended for removing any remaining but unnecessary data from previous
sync domains that were migrated using the :ref:`participant.repair.migrate_domain <repair.migrate_domain>`
command.

Note that the ``migrate_domain`` command in 2.9 now automatically removes such data,
but only for the sync domain on which it has been invoked.

Paging in Party Management
""""""""""""""""""""""""""
The `ListKnownParties` method on the `PartyManagementService` now returns at most 10,000 results by default
to avoid memory issues in participants that know more than 10,000 parties.

The `next_page_token` can be used to request the next page (see `request <https://docs.daml.com/2.9.0/app-dev/grpc/proto-docs.html#com-daml-ledger-api-v1-admin-listknownpartiesrequest>`_
and `response <https://docs.daml.com/2.9.0/app-dev/grpc/proto-docs.html#com-daml-ledger-api-v1-admin-listknownpartiesresponse>`_).

.. _upgrade_to_2.8:

Upgrade to Release 2.8
^^^^^^^^^^^^^^^^^^^^^^

Version 2.8 extends the database schema. If you use the "migrate and start" feature, the database schema will be automatically updated.
Otherwise, perform the manual database migration steps outlined in the :ref:`database migration steps <migrating_the_database>`.

Protocol versions 3 and 4 are deprecated
""""""""""""""""""""""""""""""""""""""""
Protocol versions 3 and 4 are now marked as deprecated and will be removed in ``2.9``. Protocol version 5 should be preferred for any new deployment.

Configuration changes
"""""""""""""""""""""

**KMS wrapper-key configuration value**:
The configuration value for the KMS wrapper-key now accepts a simple string.
Update your configuration as follows:

.. code:: text

    crypto.private-key-store.encryption.wrapper-key-id = { str = "..."} # version 2.7
    crypto.private-key-store.encryption.wrapper-key-id = "..." # version 2.8


**Indexer Schema Migration and Cache Weight Configuration**:
Remove the following configuration lines related to the indexer and Ledger API server schema migration and cache weight:

.. code:: text

    participants.participant.parameters.ledger-api-server-parameters.indexer.schema-migration-attempt-backoff
    participants.participant.parameters.ledger-api-server-parameters.indexer.schema-migration-attempts
    participants.participant.ledger-api.max-event-cache-weight
    participants.participant.ledger-api.max-contract-cache-weight

**SQL Batching Parameter**:
The expert mode SQL batching parameter has been moved. Generally, we recommend not changing this parameter unless advised by support.

.. code:: text

    canton.participants.participant.parameters.stores.max-items-in-sql-clause # version 2.7
    canton.participants.participant.parameters.batching.max-items-in-sql-clause # version 2.8

Breaking console commands
"""""""""""""""""""""""""

**Key Management Commands**:
The ``owner_to_key_mappings.rotate_key`` command was changed to avoid unwanted key rotations.
It now expects a node reference to perform additional checks.

**Sync domain filtering in testing commands**:
To improve consistency and code safety, some testing console commands now expect an optional sync domain alias (rather than a plain sync domain alias).
For example, the following call needs to be rewritten:

.. code:: text

    participant.testing.event_search("da") # version 2.7
    participant.testing.event_search(Some("da")) # version 2.8

The impacted console commands are: ``participant.testing.event_search`` and ``participant.testing.transaction_search``

Packaging
"""""""""
We have reverted the packaging change introduced in version 2.7.0;
the Bouncy Castle JAR is now included back in the Canton JAR.
However, users with Oracle JRE must explicitly add the Bouncy Castle library to the classpath when running Canton.

.. code-block:: text

    java -cp bcprov-jdk15on-1.70.jar:canton-with-drivers-2.8.0-all.jar com.digitalasset.canton.CantonEnterpriseApp

Breaking Error Code
"""""""""""""""""""

The error code ``SEQUENCER_DELIVER_ERROR`` is superseded by two new error codes:
``SEQUENCER_SUBMISSION_REQUEST_MALFORMED`` and ``SEQUENCER_SUBMISSION_REQUEST_REFUSED``.
Update your client applications code accordingly.


Deprecations
""""""""""""
``SequencerConnection.addConnection`` is deprecated. Use ``SequencerConnection.addEndpoints`` instead.

.. _upgrade_to_2.7:

Upgrade to Release 2.7
^^^^^^^^^^^^^^^^^^^^^^
Version 2.7 slightly extends the database schema. Therefore, you will have to perform the :ref:`database migration steps <migrating_the_database>`.
Alternatively, you can enable the new "migrate and start" mode in Canton, which triggers an automatic update of the database schema
when a new minor version is deployed.
This mode can be enabled by setting the appropriate storage parameter:

.. code:: text

    canton.X.Y.storage.parameters.migrate-and-start = yes

To benefit from the new security features in protocol version 5,
you must :ref:`upgrade the sync domain accordingly <canton_domain_protocol_version_upgrading>`.

Activation of unsupported features
""""""""""""""""""""""""""""""""""
In order to activate unsupported features, you now need to explicitly enable `dev-version-support` on the sync domain (in addition to the non-standard config flag).
More information can be found in the :ref:`documentation <how-do-i-enable-unsupported-features>`.

Breaking changes around console commands
""""""""""""""""""""""""""""""""""""""""

**Key rotation**
The command ``keys.secret.rotate_wrapper_key`` now returns a different error code.
An ``INVALID_WRAPPER_KEY_ID`` error has been replaced by an ``INVALID_KMS_KEY_ID`` error.

**Adding sequencer connection**
The configuration of the sequencer client has been updated to accommodate multiple sequencers and their endpoints:
method ``addConnection`` has been renamed to ``addEndpoints`` to better reflect the fact that it modifies an endpoint for the sequencer.

Hence, the command to add a new sequencer connection to the mediator would be changed to:

.. code:: text

    mediator1.sequencer_connection.modifyConnections(
        _.addEndpoints(SequencerAlias.Default, connection)
    )


Unique contract key deprecation
"""""""""""""""""""""""""""""""
The unique-contract-keys parameters for both participant nodes and sync domains are now marked as deprecated.
As of this release, the meaning and default value (true) remain unchanged.
However, contract key uniqueness will not be available in the next major version, featuring multi-sync-domain connectivity.
If you are already setting this key to false explicitly (preview), this behavior will be the default one after the configuration key is removed.
If you don't explicitly set this value to false, you are encouraged to evaluate evolving your existing applications and services to avoid relying on this feature.
You can read more on the topic in the :ref:`documentation <canton_keys>`.

Causality tracking
""""""""""""""""""
An obsolete early access feature to enable causality tracking, related to preview multi-sync-domain, was removed. If you enabled it, you need to remove the following config lines, as they will not compile anymore:

.. code:: text

    participants.participant.init.parameters.unsafe-enable-causality-tracking = true
    participants.participant.parameters.enable-causality-tracking = true

Besu and Fabric drivers
"""""""""""""""""""""""
In order to allow for independent updates of the different components, we have moved the drivers into a separate jar, which needs to be loaded into a separate classpath.
As a result, deployments that use Fabric or Besu need to additionally download the jar and place it in the appropriate directory.
Please :ref:`consult the installation documentation <canton-enterprise-drivers>` on how to obtain this additional jar.

Removal of deploy_sequencer_contract
""""""""""""""""""""""""""""""""""""
The command ``deploy_sequencer_contract`` has been removed and exchanged with a deployment through genesis block in examples.
The ``deploy_sequencer_contract``, while convenient, is ill-suited for any production environment and can cause more damage than harm.
The deployment of a sequencing contract should only happen once on the blockchain;
however, adding deployment as part of the bootstrapping script would cause a redeployment each time bootstrapping is done.


Ledger API error codes
""""""""""""""""""""""
The error codes and metadata of gRPC errors returned as part of failed command interpretation from the Ledger API have been updated to include more information.
Previously, most errors from the Daml engine would be given as either ``GenericInterpretationError`` or ``InvalidArgumentInterpretationError``.
They now all have their own codes and encode relevant information in the gRPC Status metadata.
Specific error changes are as follows:
* ``GenericInterpretationError`` (Code: ``DAML_INTERPRETATION_ERROR``) with gRPC status ``FAILED_PRECONDITION`` is now split into:

    * ``DisclosedContractKeyHashingError`` (Code: ``DISCLOSED_CONTRACT_KEY_HASHING_ERROR``) with gRPC status ``FAILED_PRECONDITION``
    * ``UnhandledException`` (Code: ``UNHANDLED_EXCEPTION``) with gRPC status ``FAILED_PRECONDITION``
    * ``InterpretationUserError`` (Code: ``INTERPRETATION_USER_ERROR``) with gRPC status ``FAILED_PRECONDITION``
    * ``TemplatePreconditionViolated`` (Code: ``TEMPLATE_PRECONDITION_VIOLATED``) with gRPC status ``INVALID_ARGUMENT``

* ``InvalidArgumentInterpretationError`` (Code: ``DAML_INTERPRETER_INVALID_ARGUMENT``) with gRPC status ``INVALID_ARGUMENT`` is now split into:

    * ``CreateEmptyContractKeyMaintainers`` (Code: ``CREATE_EMPTY_CONTRACT_KEY_MAINTAINERS``) with gRPC status ``INVALID_ARGUMENT``
    * ``FetchEmptyContractKeyMaintainers`` (Code: ``FETCH_EMPTY_CONTRACT_KEY_MAINTAINERS``) with gRPC status ``INVALID_ARGUMENT``
    * ``WronglyTypedContract`` (Code: ``WRONGLY_TYPED_CONTRACT``) with gRPC status ``FAILED_PRECONDITION``
    * ``ContractDoesNotImplementInterface`` (Code: ``CONTRACT_DOES_NOT_IMPLEMENT_INTERFACE``) with gRPC status ``INVALID_ARGUMENT``
    * ``ContractDoesNotImplementRequiringInterface`` (Code: ``CONTRACT_DOES_NOT_IMPLEMENT_REQUIRING_INTERFACE``) with gRPC status ``INVALID_ARGUMENT``
    * ``NonComparableValues`` (Code: ``NON_COMPARABLE_VALUES``) with gRPC status ``INVALID_ARGUMENT``
    * ``ContractIdInContractKey`` (Code: ``CONTRACT_ID_IN_CONTRACT_KEY``) with gRPC status ``INVALID_ARGUMENT``
    * ``ContractIdComparability`` (Code: ``CONTRACT_ID_COMPARABILITY``) with gRPC status ``INVALID_ARGUMENT``
    * ``InterpretationDevError`` (Code: ``INTERPRETATION_DEV_ERROR``) with gRPC status ``FAILED_PRECONDITION``

* The ``ContractKeyNotVisible`` error (previously encapsulated by ``GenericInterpretationError``) is now transformed into a ``ContractKeyNotFound`` to avoid information leaking.

.. _upgrade_to_2.6:

Upgrade to Release 2.6
^^^^^^^^^^^^^^^^^^^^^^
Version 2.6 changes the database schema used. Therefore, you must perform the
database migration steps. Depending on the size of the database, this operation can take many hours.
Vacuuming your database before starting your nodes helps avoid long startup times. Otherwise, the participant
node can refuse to start due to extremely long initial database response times.

.. _upgrade_to_2.5:

Upgrade to Release 2.5
^^^^^^^^^^^^^^^^^^^^^^
Version 2.5 will slightly extend the database schema used. Therefore, you will have to perform the
database migration steps.

Some configuration arguments have changed. While rewrite rules are in place for backward compatibility,
we recommend that you test your configuration before upgrading and update the settings to avoid
using deprecated flags.

IMPORTANT: Existing sync domains and sync domain managers need to be reconfigured to keep on working. It is important
that before attempting the binary upgrade, you configure the currently used protocol version explicitly:

.. code:: text

    canton.domains.mydomain.init.domain-parameters.protocol-version = 3

Nodes persist the static sync domain parameters used during initialization now. Version 2.5 is the last version
that will require this explicit configuration setting during upgrading.

If you started the sync domain node accidentally before changing your configuration, your participants won't be able to
reconnect to the sync domain, as they will fail with a message like:

    DOMAIN_PARAMETERS_CHANGED(9,d5dfa5ce): The sync domain parameters have changed

To recover from this, you need to force a reset of the stored static sync domain parameters using:

.. code:: text

    canton.domains.mydomain.init.domain-parameters.protocol-version = 3
    canton.domains.mydomain.init.domain-parameters.reset-stored-static-config = yes

To benefit from protocol version 4, you will have to :ref:`upgrade the sync domain accordingly <canton_domain_protocol_version_upgrading>`.

.. _upgrade_to_2.4:

Upgrade to Release 2.4
^^^^^^^^^^^^^^^^^^^^^^
Version 2.4 will slightly extend the database schema used. Therefore, you will have to perform the
database migration steps.

There have been a few consistency improvements to some console commands. In particular, we have renamed
a few of the arguments and changed some of their types. As we have included automatic conversion
and the change only affects special arguments (mainly timeouts), your script should still work. However,
we recommend that you test your scripts for compilation issues. Please check the detailed release
notes on the specific changes and their impact.

There was no change to the protocol. Participants and sync domains running 2.3 can also run 2.4, as
both versions use the same protocol version.

.. _upgrade_to_2.3:

Upgrade to Release 2.3
^^^^^^^^^^^^^^^^^^^^^^
Version 2.3 will slightly extend the database schema used. Therefore, you will have to perform the
database migration steps.

Furthermore, the Canton binary with version 2.3 has introduced a new protocol version 3, and deprecated the
previous protocol version 2. In order to keep a node operational that is using protocol version 2,
you need to turn on support for the deprecated protocol version.

On the participant, you need to turn on support for deprecated protocols explicitly:

.. code:: text

    canton.participants.myparticipant.parameters.minimum-protocol-version = 2.0.0

The default settings have changed to use protocol 3, while existing sync domains run protocol 2.
Therefore, if you upgrade the binary on sync domains and sync domain manager nodes, you need to explicitly
set the protocol version as follows:

.. code:: text

    canton.domains.mydomain.init.domain-parameters.protocol-version = 2.0.0

**You cannot upgrade the protocol of a deployed sync domain!** You need to keep it running with the existing protocol.
Please follow the protocol upgrade guide to learn how to introduce a new protocol version.

.. _change_pv:

Change the Canton Protocol Version
----------------------------------

The Canton protocol is defined by the semantics and the wire format used by the nodes
to communicate to each other. In order to process transactions, all nodes must be able
to understand and speak the same protocol.

Therefore, a new protocol can be introduced only once all nodes have been upgraded
to a binary that can run the version.

.. _canton_domain_protocol_version_upgrading:

Upgrade the Synchronization Domain to a new Protocol Version
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A sync domain is tied to a protocol version. This protocol version is configured when
the sync domain is initialized and cannot be changed afterward. Therefore, **you can
not upgrade the protocol version of a sync domain**. Instead, you deploy a new sync domain
side by side with the old sync domain process.

This applies to all sync domain services, be it sequencer, mediator, or topology manager.

With that, the protocol upgrade process boils down to:

#. **Deploy a new sync domain with the new protocol version**

   Deploy a new sync domain and ensure that the new sync
   domain is using the desired protocol version.

   Also make sure to use different databases (or at least different schemas in the same database)
   for the sync domain services (domain node, mediator, sequencer node, and topology manager), channel names,
   smart contract addresses, etc.

   The new sync domain must be completely separate, but you can reuse
   your DLT backend as long as you use different sequencer contract addresses or Fabric channels.

#. **Carry out a hard sync domain migration**

   Instruct the participants individually using the :ref:`hard sync domain migration<hard_sync_domain_upgrade>`
   to use the new sync domain.

.. note::

    Currently, the sync domain ID cannot be preserved during upgrades.

.. note::

    To use the same database with different schemas for the old and the new sync domains,
    set the ``currentSchema`` either in the JDBC URL or as a parameter in ``storage.config.properties``.

.. _hard_sync_domain_upgrade:

Hard Synchronization Domain Migration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning::

    Ensure that you have appropriate backups in place and have tested this procedure before applying
    it to your production system.

A hard sync domain migration is performed using the :ref:`respective migration command <repair.migrate_domain>`.

.. _enable-repair-commands:

You must enable this command using a special config switch:

.. code:: text

    canton.features.enable-repair-commands=yes

Assuming that you have several participants all connected to a sync domain named ``olddomain``,
ensure that there are no pending transactions.
You can do that by either controlling your applications, or by
:ref:`setting the resource limits <resources.set_resource_limits>` to 0 on all participants:

.. snippet:: migrating_protocol
    .. assert:: { participant.db.migrate(); true }
    .. assert:: { participant.start(); true }
    .. assert:: { participant.domains.connect_local(olddomain); true }
    .. success:: participant.resources.set_resource_limits(ResourceLimits(Some(0), Some(0)))

This rejects any new command and finishes processing the pending commands. Once you are sure that
your participant node is idle, disconnect the participant node from the old sync domain:

.. snippet:: migrating_protocol
    .. success:: participant.domains.disconnect("olddomain")

Test that the participant is disconnected from the sync domain by checking the list of active connections:

.. snippet:: migrating_protocol
    .. success:: participant.domains.list_connected()
    .. assert:: participant.domains.list_connected().isEmpty

This is a good time to perform a backup of the database before proceeding:

.. code:: sql

    CREATE DATABASE newdb WITH TEMPLATE originaldb OWNER dbuser;

.. warning::

    Following steps modify the participant's data storage.
    Without a database backup for your participant, a potential recovery becomes
    significantly more difficult.

Next, we want to run the migration step. For this, we need to run the ``repair.migrate_domain`` command.
The command expects two input arguments: The alias of the source sync domain and a sync domain connection
configuration for the new sync domain.

In order to build a sync domain connection config, we can just type

.. snippet:: migrating_protocol
    .. success(output=5):: val config = DomainConnectionConfig("newdomain", GrpcSequencerConnection.tryCreate("https://127.0.0.1:5018"))

where the URL should point to the correct sync domain. If you are testing the upgrade
process locally in a single Canton process using a target sync domain named ``newdomain`` (which is
what we are doing in this example), you can grab the connection details using

.. snippet:: migrating_protocol
    .. success(output=5):: val config = DomainConnectionConfig("newdomain", newdomain.sequencerConnection)

Now, using this configuration object, we can trigger the hard sync domain connection migration using

.. snippet:: migrating_protocol
    .. success:: participant.repair.migrate_domain("olddomain", config)

This command registers the new sync domain and re-associate the contracts tied to ``olddomain`` to
the new sync domain. In addition, some data specific to the old domain is automatically deleted.

Once all participants have performed the migration, they can reconnect to the sync domain:

.. snippet:: migrating_protocol
    .. success:: participant.domains.reconnect_all()

Now, the new sync domain should be connected:

.. snippet:: migrating_protocol
    .. success:: participant.domains.list_connected()
    .. assert:: participant.domains.list_connected().map(_.domainAlias.unwrap) == Seq("newdomain")

As we've previously set the resource limits to 0, we need to reset this back:

.. snippet:: migrating_protocol
    .. success:: participant.resources.set_resource_limits(ResourceLimits(None, None))

Finally, we can test that the participant can process a transaction by running a ping on the new sync domain:

.. snippet:: migrating_protocol
    .. success:: participant.health.ping(participant)

.. note::

    Currently, the hard migration is the only supported way to migrate a production system.
    This is because unique contract keys are restricted to a single sync domain.

While the sync domain migration command is mainly used for upgrading, it can also be used to recover
contracts associated with a broken sync domain.

After the upgrade, the participants may report a mismatch between commitments during the first commitment
exchange, as they might have performed the migration at slightly different times. The warning should
eventually stop once all participants are back up and connected.

Expected Performance
^^^^^^^^^^^^^^^^^^^^

Performance-wise, we can note the following: when we migrate contracts, we write directly into
the respective event logs. This means that on the source sync domain, we insert a transfer-out, while
we write a transfer-in and the contract into the target sync domain. Writing this information is substantially
faster than any kind of transaction processing (several thousand migrations per second on a
single CPU/16-core test server). However, with very large datasets, the process can
still take quite some time. Therefore, we advise you to measure the time the migration takes during
the upgrade test to understand the necessary downtime required for the migration.

Furthermore, upon reconnecting, the participant needs to recompute the new set of commitments. This can take
a while for large numbers of contracts.

.. _one_step_migration:

One-Step Migration
------------------

The *one-step migration* covers a :ref:`binary upgrade <upgrade_canton_binary>` from Canton version 2.3 and following minor versions
up to this minor release version. Additionally, it :ref:`changes the protocol version <change_pv>` supported by
these prior releases to a protocol version supported by this minor release version
(see also the :ref:`protocol version table <release-version-to-protocol-version-table>`).

.. note::

    There is no need for a one-step migration when upgrading from one release version to another, as long
    as both :ref:`release versions support the protocol version <release-version-to-protocol-version-table>`
    that your current sync domain uses.
    Follow the steps for :ref:`upgrading the Canton binary <upgrade_canton_binary>` instead.

.. warning::

    Every upgrade requires specific and thorough testing before applying it to a particular production
    environment. Even though the one-step migration process has been tested through automatic and manual
    tests, and its steps are known to work, additional measures and configuration may be required to
    address the peculiarities of your environment.

One-Step Migration Recipe for 2.10
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
General recipe to migrate from a sync domain running on a :ref:`2.3 <upgrade_to_2.3>`,
:ref:`2.4 <upgrade_to_2.4>`, :ref:`2.5 <upgrade_to_2.5>`, :ref:`2.6 <upgrade_to_2.6>`,
:ref:`2.7 <upgrade_to_2.7>` or :ref:`2.8 <upgrade_to_2.8>` release and protocol
version 3 or 4 to a new sync domain running on the 2.10 release and protocol version 5:

.. note::

    Although version 2.10 supports other protocol versions, protocol version 5 is recommended.

.. note::

    When upgrading from 2.9 to 2.10, follow the steps for :ref:`upgrading the Canton binary <upgrade_canton_binary>`
    instead, as both 2.9 and 2.10 support protocol version 5.

#. Start a new sync domain running protocol version 5
#. :ref:`Halt activity on the old sync domain <halt-activity-current-domain>`
#. Wait for pending transactions to complete or time out
#. Backup the current sync domain including participants
#. Participants: Upgrade the binary to 2.10
#. Participants: :ref:`Enable repair commands <enable-repair-commands>`
#. All nodes: :ref:`Test the configuration <test-your-config>` considering this :ref:`additional change <test-your-config-details>` if your old domain runs protocol version 3.
#. All nodes: :ref:`Apply the DB migrations <migrating_the_database>`
#. Participants: Connect to the new sync domain, then disconnect from all domains
#. Participants: Invoke :ref:`command<repair.migrate_domain>` ``repair.migrate_domain``
#. Participants: Reconnect to the new sync domain
#. Decommission the old domain

.. _halt-activity-current-domain:

Halt activity on the current sync domain
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
For a sync domain running protocol version 4 and above, set the
:ref:`dynamic domain parameter <dynamic_domain_parameters>` ``maxRatePerParticipant``
to 0 on each participant.

Otherwise, use

.. code-block:: text

    participant.resources.set_resource_limits(ResourceLimits(Some(0), Some(0)))

to set the resource limits to 0 on each participant.

.. _test-your-config-details:

Test the configuration - Additional change if you were running protocol version 3
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When migrating from protocol version 3, which uses an unauthenticated contract id scheme,
you may need to specifically allow it on the participants.

.. code-block:: text

    canton.participants.<nodeName>.parameters.allow-for-unauthenticated-contract-ids=true

Please adjust ``<nodeName>`` to match your case.

**IMPORTANT**: Please note that you MUST set the flag on ALL the participants connected to the domain.
Failure to do so will end up in critical failures of the participants.
