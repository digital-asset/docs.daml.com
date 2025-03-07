..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _persistence-config:

Persistence
===========

Participant nodes and sync domains both require storage configurations. Both use the same configuration
format and therefore support the same configuration options. There are three different configurations
available:

1. ``Memory`` - Using simple, hash-map backed in-memory stores which are deleted whenever a node is stopped.

2. ``Postgres`` - To use with the open source relational database `Postgres <https://www.postgresql.org/>`_.

3. ``Oracle`` - To use with Oracle DB (Enterprise only)

In order to set a certain storage type, we have to edit the storage section of the particular node, such
as ``canton.participants.myparticipant.storage.type = memory``. Memory storage does not require any other
setting.

For the actual database driver, Canton does not directly define how they are configured, but leverages
a third-party library (`slick <https://scala-slick.org/doc/3.3.1>`_) for it, exposing all configuration
methods therein. If you need to, please consult the `respective detailed documentation <https://scala-slick.org/doc/3.3.1/database.html#using-typesafe-config>`_
to learn about all configuration options if you want to leverage any exotic option. Here, we will only
describe our default, recommended and supported setup.

It is recommended to use a connection pool in production environments and
`consciously choose the size of the pool. <https://github.com/brettwooldridge/HikariCP/wiki/About-Pool-Sizing>`_

Please note that Canton will create, manage and upgrade the database schema directly. You don't have
to create tables yourselves.

Consult the reference ``config`` directory to get a set of configuration files to set your nodes up.

Postgres
--------

Our reference driver-based definition for Postgres configuration is:

.. literalinclude:: /canton/includes/mirrored/community/app/src/pack/config/storage/postgres.conf

You may use this configuration file with environment variables or adapt it accordingly. More detailed setup instructions
and options are available in the `Slick reference guide <https://scala-slick.org/doc/3.3.1/api/index.html#slick.jdbc.JdbcBackend$DatabaseFactoryDef@forConfig(String,Config,Driver,ClassLoader):Database>`_.
The above configurations are included in the reference ``config/storage`` folder and are sufficient to get started.

.. _ssl:

SSL
~~~

This snippet shows how SSL can be configured for Postgres. You can find more information about the settings in the
(`postgres documentation <https://jdbc.postgresql.org/documentation/head/ssl-client.html>`_):

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/postgres-ssl.conf

Note that all configuration properties for the database will be propagated to the Ledger API JDBC URL.

.. _postgres-performance-tuning:

Sizing and Performance
~~~~~~~~~~~~~~~~~~~~~~

Note that your Postgres database setup requires appropriate tuning to achieve the desired performance. Canton
is database-heavy. This section should give you a starting point for your tuning efforts. You may want to consult
the :ref:`troubleshooting section <how_to_measure_db_performance>` on how to analyze whether the database is a limiting factor.

This guide can give you a starting point for tuning. Ultimately, every use case is different and the exact resource requirements cannot
be predicted, but have to be measured.

First, ensure that the database you are using is appropriately sized for your use case. The number of cores depends on your
throughput requirements. The rule of thumb is:

- 1 db core per 1 participant core.
- 1 participant core for 30-100 ledger events per second (depends on the complexity of the commands).

The memory requirements depend on your data retention period and the size of the data you are storing. Ideally, you monitor the
database index cache hit/miss ratio. If your instance needs to keep on loading indexes from the disk, performance suffers.
It might make sense to start with 128GB, run a long-running scale & performance test, and `monitor the cache hit/miss ratio <https://www.postgresql.org/docs/current/monitoring-stats.html#MONITORING-PG-STATIO-ALL-INDEXES-VIEW>`__.

Most Canton indexes are contract-id based, which means that the index lookups are randomly distributed. Solid state drives with
high throughput perform much better than spinning disks for this purpose.

.. _shared_env_performance:

Predictability of Shared Environments
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The throughput and latency of a Canton node depends on the performance of the database.
Sharing hardware or software saves cost and better utilizes available resources, but it comes
with some drawbacks: If the database is operated in a shared environment such as the Cloud, where other applications are using the same
database or are operated on the same hardware, the performance of the Canton node varies due to
contention on shared resources. This is a natural effect of shared environments and cannot be entirely
avoided. It can be difficult to diagnose as a user of the shared environment due to lack of visibility into
the other applications and the host system.

If you are operating in a shared environment, you should monitor the performance of the database and expect
a higher variance in latency and throughput. 

.. _postgres-configuration:

Postgres Configuration
~~~~~~~~~~~~~~~~~~~~~~

For Postgres, `the PGTune online tool <https://pgtune.leopard.in.ua/>`_ is a good starting point for finding reasonable parameters
(use online transaction processing system), but you need to increase the settings of ``shared_buffers``, ``checkpoint_timeout``
and ``max_wal_size``, as explained below.

Beyond the initial configuration, note that most indexes Canton uses are "hash based".
Therefore, read and write access to these indexes is uniformly distributed. However, Postgres reads and writes indexes in
pages of 8kb, while a simple index might only be a couple of writes. Therefore, it is very important to be able to keep the
indexes in memory and only write updates to the disk from time to time; otherwise, a simple change of 32 bytes requires 8kb I/O
operations.

Configuring the ``shared_buffers`` setting to hold 60-70% of the host memory is recommended, rather than the default
suggestion of 25%, as the Postgres caching appears to be more effective than the host-based file access caching.

Also increase the following variables beyond their default: Increase the ``checkpoint_timeout`` so that
the flushing to disk includes several writes and not just one per page, accumulated over time, together with
a higher ``max_wal_size`` to ensure that the system does not prematurely flush before reaching the ``checkpoint_timeout``.
Monitor your system during load testing and tune the parameters accordingly to your use case.
The downside of changing the checkpointing parameters is that crash recovery takes longer.

.. _persistence-oracle:

Oracle
------

.. enterprise-only::

An Oracle database can be used as the local persistence for the Canton nodes.
The enterprise version of Canton comes with default configuration mixins using
Oracle as a database backend.

Persistence using Oracle has the following dependencies:

* Oracle Database 19c - requires version 19.11 or later
* Oracle Text 19c - a plugin schema to oracle database
* Intel x86-64 architecture

Installation and Setup of Oracle
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Assuming that Oracle has already been installed, the following configuration
aspects and setup steps are required.

Default Character Set and Collations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The database must use the recommended Oracle defaults for character sets and collations:

.. code-block:: sql

    AL32UTF8 encoding for NLS_CHARACTERSET
    AL32UTF8 or AL16UTF16 for NLS_NCHAR_CHARACTERSET
    BINARY for NLS_SORT and NLS_COMP

Otherwise, Canton will refuse to connect to the database and log an error message of the form

.. code-block:: bash

    DatabaseConfigError(Oracle NLS database parameter ... is ..., but should be ...)

In addition to keeping the default database characterset and collations
configurations, the Java user language must be set to ``en`` and the user
country to ``US`` (the default on most systems). This can be forced by setting
the ``JAVA_OPTS`` options via the command line additions ``-Duser.language=en
-Duser.country=US`` (see :ref:`JVM Arguments <jvm_arguments>`). Otherwise the node at startup
may complain about session ``NLS_SORT`` or ``NLS_COMP`` being different from
BINARY by logging these strings:

- ``DatabaseConfigError(Oracle NLS session parameter NLS_SORT is ..., but should be BINARY)``
- ``DatabaseConfigError(Oracle NLS session parameter NLS_COMP is ..., but should be BINARY)``

Database Replication
^^^^^^^^^^^^^^^^^^^^

To allow for recovery from data loss due to catastrophic events at data centers,
database replication should be enabled. The technical details of setting up
replication are out of scope of this manual. Canton on Oracle assumes that a
database transaction is reported as committed only after it has been persisted
to all database replicas. Please make sure this is the case to prevent data
corruption / data loss in case of a data center failover.

Setup Oracle Schemas
^^^^^^^^^^^^^^^^^^^^

For a simple Oracle-based Canton deployment with one sync domain and one participant
the following Oracle schemas (i.e., users) are required:

+--------------------------+-------------------+--------------------+-------------------------------+
| Component                | Schema name       | Description        | Authentication                |
+==========================+===================+====================+===============================+
|                          | DD4ODRUN          | Runtime user       | Password configured per 2.2.7 |
| Oracle sync domain       |                   |                    |                               |
+--------------------------+-------------------+--------------------+ Site administrator may change |
|                          | DD4OPRUN          | Runtime user for   | at will (i.e., default        |
| Participant              |                   | Participant Canton | password is never hardcoded   |
|                          |                   | component          | or assumed)                   |
|                          +-------------------+--------------------+                               |
|                          | DD4OPLEDG         | Runtime user for   |                               |
|                          |                   | Participant API    |                               |
|                          |                   | ledger component   |                               |
+--------------------------+-------------------+--------------------+-------------------------------+

The DD4ODRUN,  DD4OPRUN, and DD4OPLEDG users all need the following schema privileges:

- Quota Unlimited
- Create table
- Create type
- Create session
- Create view
- Create procedure
- Create sequence

Run the following commands as the system user (e.g., for the runtime user
(DD4OPRUN) provisioning using Oracle SQL\*Plus from the command line):

..
    The $ in the SQL below is not parsed properly so using bash parsing. See https://github.com/sphinx-doc/sphinx/issues/3175

.. code-block:: bash

    SQL> CREATE USER DD4OPRUN IDENTIFIED BY securepass;
    SQL> ALTER USER DD4OPRUN QUOTA UNLIMITED ON USERS;
    SQL> GRANT CREATE TABLE, CREATE TYPE, CREATE SESSION, CREATE VIEW, CREATE PROCEDURE, CREATE SEQUENCE, CREATE TRIGGER TO DD4OPRUN;
    SQL> GRANT EXECUTE ON SYS.DBMS_LOCK TO DD4OPRUN;
    SQL> GRANT SELECT ON V_$MYSTAT TO DD4OPRUN;
    SQL> GRANT SELECT ON V_$LOCK TO DD4OPRUN;
    SQL> GRANT SELECT ON V_$PARAMETER TO DD4OPRUN;

For additional sync domains or participant nodes create the corresponding schemas with
one schema per node.

If you are getting an error message like:

.. code-block:: bash

    ORA-65096: invalid common user or role name

you are most likely logged into the CDB instead of the PDB. Find the right PDB and
change the session:

.. code-block:: bash

    SQL> show pdbs
    SQL> alter session SET container = ORCLPDB1;

You can then test whether creating the user worked using ``sqlplus``:

.. code-block:: bash

    sqlplus -L DD4OPRUN/securepass@ORCLPDB1

Configuring Canton Nodes for Oracle
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following is an example configuration for an Oracle-backed sync domain for the
persistence of its sequencer, mediator, and topology manager nodes. The
placeholders ``<ORACLE_HOST>``, ``<ORACLE_PORT>``, and ``<ORACLE_DB>`` will need
to be replaced with the correct settings to match the environment and
``<ORACLE_USER>`` with a unique user for each node:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/pack/config/storage/oracle.conf

The environment variable for ``ORACLE_PASSWORD`` needs to be set and exported so that it
is accessible for substitution in the configuration files.

The persistence configuration for the Participant is an extended version-based
on the previous configuration for participant nodes with the addition of the
Ledger API JDBC URL string:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/pack/config/storage/oracle-participant.conf

.. _oracle-performance-tuning:

Performance Tuning
~~~~~~~~~~~~~~~~~~

The following configuration changes serve as an example to tune the performance
of Oracle. **NOTE:** The configuration changes need to be reviewed and adapted
to the specific application and environment.

Operating System Modifications
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Runtime Kernel Parameters**

The recommended Linux kernel is version 5.10 or later. For RHEL systems, a
mainline kernel can be installed from ELRepo, as follows:

.. code-block:: bash

    $ sudo dnf -y install https://www.elrepo.org/elrepo-release-8.el8.elrepo.noarch.rpm
    $ sudo rpm --import https://www.elrepo.org/RPM-GPG-KEY-elrepo.org
    $ sudo dnf makecache
    $ sudo dnf --disablerepo="*" --enablerepo="elrepo-kernel" install -y kernel-ml.x86_64

By default, the Linux kernel default settings are optimized for
general-purpose applications, and as such these settings can be unsuitable or
even detrimental to the performance and stability of I/O-heavy applications,
like databases.

Make the following additions to ``/etc/sysctl.conf``

.. code-block:: scala

    vm.swappiness = 5
    vm.dirty_background_ratio = 5
    vm.dirty_background_bytes = 25
    vm.nr_hugepages = 200
    fs.file-max = 6815744
    kernel.sem = 250 32000 100 128
    kernel.shmmni = 4096
    kernel.shmall = 1073741824
    kernel.shmmax = 4398046511104
    kernel.panic_on_oops = 1
    net.core.rmem_default = 262144
    net.core.rmem_max = 4194304
    net.core.wmem_default = 262144
    net.core.wmem_max = 1048576
    net.ipv4.conf.all.rp_filter = 2
    net.ipv4.conf.default.rp_filter = 2
    fs.aio-max-nr = 1048576
    net.ipv4.ip_local_port_range = 9000 65500

Either reboot the database server host or apply the changes to a running
server by running the following command from the terminal: ``sudo sysctl -p``.
Upon successfully applying the new settings, ``sysctl`` will output the newly
applied values to the console.

**Shared Memory (SHM) Segments**

Oracle database works best when it can keep as much working data in memory as
possible, shared amongst the different subsystems, running in their own
distinct OS-level processes. This memory space is used by the database System
Global Area (SGA) for allocating the buffer cache pools, shared and large
pools, Java process pools and stream pools, among other functions. To allocate
80% of total system memory (RAM) to the database instance, you need to
allocate fractionally more system memory to the shared memory area on the OS
level.

Run this command to calculate the allocation size of the SHM:

.. code-block:: bash

    $ printf "%.0f\n" `echo "(\`grep MemTotal /proc/meminfo | awk '{print $2}'\`/1024)*.82" | bc -s`
    105712

Next, update ``/etc/fstab`` to ensure the allocation:

.. code-block:: bash

    $ grep shm /etc/fstab
    tmpfs	/dev/shm	tmpfs	rw,nosuid,nodev,size=105712m	0	0

Again, either reboot the database server host, or apply the changes to a
running server by remounting the SHM tmpfs filesystem:

.. code-block:: bash

    $ sudo mount -o remount /dev/shm
    Verify the new settings:
    $ df -h -BM -P /dev/shm
    Filesystem     1048576-blocks   Used Available Capacity Mounted on
    tmpfs                 105712M 38912M    66800M      37% /dev/shm

System Container Configuration (CDB)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The System Container stores the system settings and metadata required to
manage all user databases. Now modify some of the default performance
settings, in multiple stages.

After each stage restart the service from within the ``sqlplus`` client, as
follows:

.. code-block:: sql

    SQL> SHUTDOWN;
    SQL> STARTUP;
    SQL> ALTER PLUGGABLE DATABASE ALL OPEN;
    SQL> ALTER SYSTEM REGISTER;

**Stage 1: Increase Database Memory Allocation**

Allocate 80% of total available system memory to the database instance. First,
calculate the value on the command line, as follows:

.. code-block:: bash

    $ printf "%.0f\n" `echo "(\`grep MemTotal /proc/meminfo | awk '{print $2}'\`/1024)*.8" | bc -s`
    103134

From the database client connected to the CDB, set the memory cap, and restart the database:

.. code-block:: sql

    SQL> ALTER SYSTEM SET MEMORY_TARGET = 103134M SCOPE = SPFILE;

**Stage 2: Set Runtime Values**

Also allocate 40% of total available system memory to the database's Program
Global Area (PGA). The PGA is a non-shared memory region that is allocated to the CDB
when the server starts. The PGA regions are also allocated per-process in the user
database, and you will allocate a total amount to be used by all processes.

Again calculate the value on the command line, as follows:

.. code-block:: bash

    $ printf "%.0f\n" `echo "(\`grep MemTotal /proc/meminfo | awk '{print $2}'\`/1024)*.4" | bc -s`
    51462

From the database client connected to the CDB, set the following and restart the database:

.. code-block:: sql

    SQL> ALTER SYSTEM SET PGA_AGGREGATE_TARGET = 51462M SCOPE = BOTH;
    SQL> ALTER SYSTEM SET RESOURCE_LIMIT = FALSE SCOPE = BOTH;
    SQL> ALTER SYSTEM SET OPEN_CURSORS = 16000 SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET JOB_QUEUE_PROCESSES = 2000 SCOPE = BOTH;
    SQL> ALTER SYSTEM SET USE_LARGE_PAGES = TRUE SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET SESSION_MAX_OPEN_FILES = 50 SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET PARALLEL_DEGREE_POLICY = AUTO SCOPE = BOTH;
    SQL> ALTER SYSTEM SET DB_BIG_TABLE_CACHE_PERCENT_TARGET = 20 SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET DB_CACHE_SIZE = 8G SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET JAVA_POOL_SIZE = 8G SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET OPTIMIZER_ADAPTIVE_REPORTING_ONLY = TRUE SCOPE = BOTH;
    SQL> ALTER SYSTEM SET OPTIMIZER_ADAPTIVE_STATISTICS = TRUE SCOPE = BOTH;
    SQL> ALTER SYSTEM SET OPTIMIZER_SESSION_TYPE = ADHOC SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET OPTIMIZER_USE_PENDING_STATISTICS = TRUE SCOPE = BOTH;
    SQL> ALTER SYSTEM SET FILESYSTEMIO_OPTIONS = SETALL SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET DISK_ASYNCH_IO = TRUE SCOPE = SPFILE;
    SQL> ALTER SYSTEM SET PARALLEL_THREADS_PER_CPU = 8 SCOPE = BOTH;
    SQL> ALTER SYSTEM SET PARALLEL_DEGREE_LIMIT = IO SCOPE = BOTH;

    -- NOTE: The following setting is recommended, but optional; some users have reported high memory usage when enabled.
    SQL> ALTER SYSTEM SET OPTIMIZER_CAPTURE_SQL_PLAN_BASELINES = TRUE SCOPE = BOTH;

.. _connections_per_node:

**NOTE: Please avoid setting explicit process and session limits.** Oracle
will derive intelligent limits for you. If you still need to set explicit
limits on your database, please ensure that the limits are sufficiently high
for the nodes that you intend to run. We recommend configuring at least **6
times more connections per node** than actively used to give sufficient buffer
for  `delayed connection clean-up by Oracle.
<https://community.oracle.com/tech/developers/discussion/362226/tns-listener-could-not-find-available-handler-witht-matching-protocol-stackq>`_.
The max connection settings can be configured as explained in :ref:`Max
Connection Settings <max_connection_settings>`.

If your database resource limits are lower than the database connections
created by the nodes, the nodes will fail to properly start or operate. If you
set the number of connections too low, the system will not perform at peak
throughput.

**Stage 3: Configure Pluggable Database (PDB) Runtime Values**

A Pluggable Database (PDB) is a user-created set of schemas, objects, and
related structures that appears logically to a client application as a
separate database. Do some initial configuration of the PDB to ensure it can
meet the performance requirements of the your application, after which you
will create new user schemas in the PDB.

If your application requires significantly larger tablespace, Oracle will
resize tablespaces on-the-fly, meaning persistence grows gradually over time
to fit the size requirements of the application; however, this comes at the
expense of performance, as the database regularly performs blocking I/O
operations to resize tablespaces, resulting in a volatile system load profile
and overall reduced transaction throughput.

Overcome this limitation by pre-allocating new ``TEMP``, ``USERS`` and ``UNDO`` tablespaces:

.. code-block:: sql

    SQL> CREATE BIGFILE TEMPORARY TABLESPACE temp_bigfile TEMPFILE '/opt/oracle/oradata/ORCLCDB/ORCLPDB1/temp_bigfile_01.dbf' SIZE 1T AUTOEXTEND ON MAXSIZE UNLIMITED;
    SQL> CREATE BIGFILE UNDO TABLESPACE undo_bigfile DATAFILE '/opt/oracle/oradata/ORCLCDB/ORCLPDB1/undo_bigfile_01.dbf' SIZE 1T AUTOEXTEND ON MAXSIZE UNLIMITED RETENTION GUARANTEE;
    SQL> CREATE BIGFILE TABLESPACE users_bigfile DATAFILE '/opt/oracle/oradata/ORCLCDB/ORCLPDB1/users_bigfile_01.dbf' SIZE 6T AUTOEXTEND ON MAXSIZE UNLIMITED;

And then reconfigure the PDB to use the new tablespaces by default:

.. code-block:: sql

    SQL> ALTER DATABASE SET DEFAULT BIGFILE TABLESPACE;
    SQL> ALTER DATABASE DEFAULT TEMPORARY TABLESPACE TEMP_BIGFILE;
    SQL> ALTER DATABASE DEFAULT TABLESPACE USERS_BIGFILE;
    SQL> ALTER SYSTEM SET UNDO_TABLESPACE = UNDO_BIGFILE SCOPE = BOTH;


Change the default retention to 30 minutes, giving better transaction rollback performance, after which you will restart the database:

.. code-block:: sql

    SQL> ALTER SYSTEM SET UNDO_RETENTION = 1800 SCOPE = BOTH;

General Settings
----------------

.. _max_connection_settings:

Max Connection Settings
~~~~~~~~~~~~~~~~~~~~~~~

The storage configuration can further be tuned using the following additional setting:

::

    canton.participants.<service-name>.storage.parameters.max-connections = X

This allows you to set the maximum number of DB connections used by a Canton
node. If the value is None or non-positive, the value will be the number of
processors. The setting has no effect if the number of connections is already
set via slick options (i.e. storage.config.numThreads).

If you are unsure how to size your connection pools,
`this article <https://github.com/brettwooldridge/HikariCP/wiki/About-Pool-Sizing>`_
may be a good starting point.

Generally, the number of connections should be up to two times the number of CPUs on the database machine.

The number of parallel indexer connections can be configured via

::

    canton.participants.<participant-name>.parameters.ledger-api-server-parameters.indexer.ingestion-parallelism = Y

The number ``Z`` of the connections used by the exclusive sequencer writer component is the final parameter that can be controlled.

::

    canton.sequencers.<sequencer-name>.sequencer.high-availability.exclusive-storage.max-connections = Z

A Canton participant node will establish up to ``X + Y + 2`` permanent connections with the database, whereas a sync domain
will use up to ``X`` permanent connections, except for a sequencer with HA setup that will allocate up to ``2X`` connections. During
startup, the node will use an additional set of at most ``X`` temporary connections during database initialisation.

The number ``X`` represents an upper bound of permanent connections and is divided internally for different purposes,
depending on the implementation. Consequently, the actual size of the write connection pool, for example, could be smaller.
Some of the allotted connections will be taken by the *read* pool, some will be taken by the *write* pool, and a single additional connection
will be reserved to a dedicated *main* connection responsible for managing the locking mechanism.

The following table summarizes the detailed split of the connection pools in different Canton nodes. ``R`` signifies a *read* pool, ``W``
a *write* pool, ``A`` a *ledger api* pool, ``I`` an *indexer* pool, ``RW`` a combined *read/write* pool, and ``M`` the *main* pool.

+-----------------------+--------------------+--------------------+--------------------+
|  Node Type            | Enterprise Edition | Enterprise Edition | Community Edition  |
|                       | with Replication   |                    |                    |
+=======================+====================+====================+====================+
| Participant           | | A = X / 2        | | A = X / 2        | | A = X / 2        |
|                       | | R = X / 4        | | R = X / 4        | | RW = X / 2       |
|                       | | W = X / 4 - 1    | | W = X / 4 - 1    | | I = Y            |
|                       | | M = 1            | | M = 1            |                    |
|                       | | I = Y            | | I = Y            |                    |
+-----------------------+--------------------+--------------------+--------------------+
| Mediator              | | R = X / 2        | N/A                | N/A                |
|                       | | W = X / 2 - 1    |                    |                    |
|                       | | M = 1            |                    |                    |
+-----------------------+--------------------+--------------------+--------------------+
| Sequencer             | RW =  X            | N/A                | N/A                |
+-----------------------+--------------------+--------------------+--------------------+
| Sequencer writer      | | R = X / 2        | N/A                | N/A                |
|                       | | W = X / 2 - 1    |                    |                    |
|                       | | M = 1            |                    |                    |
+-----------------------+--------------------+--------------------+--------------------+
| Sequencer             | | R = Z / 2        | N/A                | N/A                |
| exclusive writer      | | W = Z / 2        |                    |                    |
+-----------------------+--------------------+--------------------+--------------------+
| Sync domain manager   | | R = X / 2        | N/A                | N/A                |
|                       | | W = X / 2 - 1    |                    |                    |
|                       | | M = 1            |                    |                    |
+-----------------------+--------------------+--------------------+--------------------+
| Sync domain           | N/A                | RW = X             | RW = X             |
+-----------------------+--------------------+--------------------+--------------------+

The results of the divisions are always rounded down unless they yield a zero. In that case, a minimal pool
size of 1 is ascertained.

The values obtained from that formula can be overridden using explicit configuration settings for the *ledger API* ``A``,
the *read* ``R``, the *write* ``W`` pools.

::

    canton.participants.<participant-name>.storage.parameters.connection-allocation.num-reads = R-overwrite
    canton.participants.<participant-name>.storage.parameters.connection-allocation.num-writes = W-overwrite
    canton.participants.<participant-name>.storage.parameters.connection-allocation.num-ledger-api = A-overwrite

Similar parameters exist also for other Canton node types:

::

    canton.sequencers.sequencer.storage.parameters.connection-allocation...
    canton.mediators.mediator.storage.parameters.connection-allocation...
    canton.domain-managers.domain_manager.storage.parameters.connection-allocation...

Where a node operates a combined *read/write* connection pool, the numbers for ``R`` and ``W`` overwrites are added
together to determine the overall pool size.

The effective connection pool sizes are reported by the Canton nodes at startup.

::

    INFO  c.d.c.r.DbStorageMulti$:participant=participant_b - Creating storage, num-reads: 5, num-writes: 4

.. _queue_size:

Queue Size
~~~~~~~~~~

Canton may schedule more database queries than the database can handle. As a result, these queries
will be placed into the database queue. By default, the database queue has a size of 1000 queries.
Reaching the queueing limit will lead to a ``DB_STORAGE_DEGRADATION`` warning. The impact of this warning
is that the queuing will overflow into the asynchronous execution context and slowly degrade the processing,
which will result in fewer database queries being created. However, for high-performance
setups, such spikes might occur more regularly. Therefore, to avoid the degradation warning
appearing too frequently, the queue size can be configured using:

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/storage-queue-size.conf


.. _backup-and-restore:

Backup and Restore
------------------

It is recommended that your database is frequently backed up so that the data can be restored in case of a disaster.

In the case of a restore, a participant can replay missing data from the sync domain
as long as the sync domain's backup is more recent than that of the participant's.

.. todo::
  #. `Ability to recover from partial data loss on a sync domain <https://github.com/DACH-NY/canton/issues/4839>`_.

.. _order-of-backups:

Order of Backups
~~~~~~~~~~~~~~~~

It is important that the participant's backup is not more recent than that of
the domain's, as that would constitute a ledger fork. Therefore, if you back up
both participant and domain databases sequentially, the following constraints apply:

- If you run a composite domain node, always back up the participant database before the domain.

- If you run different nodes of the domain separately (sequencer, mediators, domain topology manager):

  - Back up the mediators, the domain manager, and participants before the sequencer;
    otherwise, they may not be able to reconnect to the sequencer (``ForkHappened``).
    The relative order of mediators, domain topology manager, and participants does not matter.

  - On a :ref:`permissioned domain <permissioned-domains>`, make sure
    no participant is registered with the domain topology manager
    between the backup of the domain topology manager and the backup of the sequencer.
    Otherwise, the participant may not work correctly after the recovery.

If you perform a complete system backup in a single step (for example, using
a cloud RDS), make sure no component writes to the database while the backup is in progress.

If you are using a domain integration such as Fabric or Besu, back up the sequencer node before backing
up the underlying domain storage (e.g. Besu files).

In case of a sync domain restore from a backup, if a participant is ahead of the
sync domain the participant will refuse to connect to the sync domain (``ForkHappened``) and you must
either:

- restore the participant's state to a backup before the disaster of the sync domain, or
- roll out a new sync domain as a repair strategy in order to :ref:`recover from a lost sync domain <recovering_from_lost_domain>`

The state of applications that interact with a participant's ledger API must be
backed up before the participant, otherwise the application state has to be
reset.

.. _restore_caveats:

Restore Caveats
~~~~~~~~~~~~~~~

When restoring Canton nodes from a backup, the following caveats apply due to
the loss of data between the point of backup and latest state of the nodes.

Incomplete Command Deduplication State
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After the restore, the participant's in-flight submission tracking will be out
of sync with what the participant has sent to the sequencer after the backup was
taken. If an application resubmits a duplicate command it may get accepted even
though it should have been deduplicated by the participant.

This tracking will be in sync again when:

 - the participant has processed all events from the sequencer, and
 - no queue on the sequencer includes any submission request of a transfer/transaction
   request from before the restore that could be sequenced again

Such submission requests have a max sequencing time of the ledger time plus the
ledger-time-record-time-tolerance of the sync domain. It should be enough to observe
a timestamp from the sync domain that is after the time when the participant was
stopped before the restore by more than the tolerance. Once such a timestamp is
observed, the in-flight submission tracking is in sync again and applications
can resume submitting commands with full command deduplication guarantees.

Application State Reset
^^^^^^^^^^^^^^^^^^^^^^^

If the application's state is newer than the participant's state, either because
the application was backed up after the participant or because the application is run by
a different organization and wasn't restored from a backup, then the application
state has to be reset. Otherwise the application has already requested and
processed transactions that were lost by the participant due to the gap between when
the backup was taken and when the node disaster happened.

This includes all applications that are ledger API clients of the participant,
including the JSON API server.

Private Keys
^^^^^^^^^^^^

Assume a scenario in which a node needs to rotate its cryptographic private key, which is
currently stored in the database of the node. If the key rotation has been
announced in the system before a backup has been performed, the new key will not
be available on a restore, but all other nodes in the system expect the new key
to be used.

To avoid this situation, perform the key rotation steps in this order:

#. Generate the new private key and store it in the database
#. Back up the database
#. Once the backup is complete, revoke the previous key


Postgres Example
~~~~~~~~~~~~~~~~

If you are using Postgres to persist the participant node or sync domain data, you can create backups to a file and restore it using Postgres's utility commands ``pg_dump`` and ``pg_restore`` as shown below:

Backing up Postgres database to a file:

.. code-block:: bash

    pg_dump -U <user> -h <host> -p <port> -w -F tar -f <fileName> <dbName>

Restoring Postgres database data from a file:

.. code-block:: bash

    pg_restore -U <user> -h <host> -p <port> -w -d <dbName> <fileName>

Although the approach shown above works for small deployments, it is not recommended for larger deployments.
For that, we suggest looking into incremental backups and refer to the resources below:

- `PostgreSQL Documentation: Backup and Restore <https://www.postgresql.org/docs/current/backup.html>`_
- `How incremental backups work in PostgreSQL <https://kcaps.medium.com/how-incremental-backups-work-in-postgresql-and-how-to-implement-them-in-10-minutes-d3689e8414d9>`_

.. _database_replication_dr:

Database Replication for Disaster Recovery
------------------------------------------

Synchronous Replication
~~~~~~~~~~~~~~~~~~~~~~~

We recommend that in production at least the sync domain should be run with offsite
synchronous replication to ensure that the state of the sync domain is always newer
than the state of the participants. However to avoid similar
:ref:`caveats as with backup restore <restore_caveats>` the participants should either use synchronous
replication too or as part of the manual disaster recovery failure procedure the
caveats have to be addressed.

A database backup allows you to recover the ledger up to the point when the last backup was created.
However, any command accepted after creation of the backup may be lost in case of a disaster.
Therefore, restoring a backup will likely result in data loss.

If such data loss is unacceptable, you need to run Canton against a replicated
database, which replicates its state to another site. If the original site is
down due to a disaster, Canton can be started in the other site based on the
replicated state in the database. It is crucial that there are no writers left
in the original site to the database, because the database mechanism used in
Canton to avoid multiple writers and thus avoid data corruption does not work
across sites.

For detailed instructions on how to setup a replicated database and how to perform failovers, we refer to the database system documentation,
e.g. `the high availability documentation <https://www.postgresql.org/docs/11/high-availability.html>`_ of PostgreSQL.

**It is strongly recommended to configure replication as synchronous.**
That means, the database should report a database transaction as successfully committed only after it has been persisted to all database replicas.
In PostgreSQL, this corresponds to the setting ``synchronous_commit = on``.
If you do not follow this recommendation, you may observe data loss and/or a
corrupt state after a database failover. Enabling synchronous replication
may impact the performance of Canton depending on the network latency between
the primary and offsite database.

For PostgreSQL, Canton strives to validate the database replication configuration and fail with an error, if a misconfiguration is detected.
However, this validation is of a best-effort nature; so it may fail to detect an incorrect replication configuration.
For Oracle, no attempt is made to validate the database configuration.
Overall, you should not rely on Canton detecting mistakes in the database configuration.
