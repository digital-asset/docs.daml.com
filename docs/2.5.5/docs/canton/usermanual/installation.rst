..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _installation:

Installing Canton
=================

This guide will guide you through the process of setting up your Canton nodes to build a distributed Daml
ledger. You will learn

#. How to setup and configure a domain
#. How to setup and configure one or more participant nodes

.. note::

    As no topology is the same, this guide will point out different configuration options as notes
    wherever possible.


This guide uses the example configurations you can find in the release bundle under ``example/03-advanced-configuration``
and explains you how to leverage these examples for your purposes. Therefore, any file named in this guide
will refer to subdirectories of the advanced configuration example.


Downloading Canton
------------------

The Canton Open Source code is available from `Github <https://github.com/digital-asset/daml/releases>`__.
You can also use our Canton Docker images by following our :ref:`Docker instructions <docker-instructions>`.

Daml Enterprise includes an enterprise version of the Canton ledger. If you have entitlement to Daml Enterprise
you can download the enterprise version of Canton by following the `Installing Daml Enterprise instructions
<https://docs.daml.com/getting-started/installation.html#installing-the-enterprise-edition>`__ and downloading the
appropriate Canton artifact.


Your Topology
-------------
The first question we need to address is what the topology is that you are going after. The Canton topology
is made up of parties, participants and domains, as depicted in the following figure.

.. https://app.lucidchart.com/documents/edit/da3c4533-a787-4669-b1e9-2446996072dc/0_0
.. figure:: ../images/topology.svg
   :align: center
   :width: 80%

The Daml code will run on the participant node and expresses smart contracts between parties.
Parties are hosted on participant nodes. Participant nodes will synchronise their state with other
participant nodes by exchanging messages with each other through domains. Domains are nodes that integrate
with the underlying storage technology such as databases or other distributed ledgers. As the Canton protocol
is written in a way that assumes that Participant nodes don't trust each other, you would normally expect that
every organisation runs only one participant node, except for scaling purposes.

If you want to build up a test-network for yourself, you need at least a participant node and a domain.

..
   You can either use your own domain or leverage the :ref:`global domain <connect-global-domain>`.

.. todo::
   `Mention the global domain <https://github.com/DACH-NY/canton/issues/7564>`_

Environment Variables
---------------------
For our convenience in this guide, we will use a few environment variables to refer to a set of directions.
Please set the environment variable "CANTON" to point to the place where you have unpacked the canton release bundle.

.. code-block:: bash

    cd ./canton-X.Y.Z
    export CANTON=`pwd`

And then set another variable that points to the advanced example directory

.. code-block:: bash

    export CONF="$CANTON/examples/03-advanced-configuration"

Selecting your Storage Layer
----------------------------

In order to run any kind of node, you need to decide how and if you want to persist the
data. You currently have three choices: don't persist and just use in-memory stores which will be deleted if you restart
your node or persist using ``Postgres`` or ``Oracle`` databases.

For this purpose, there are some storage :ref:`mixin configurations <configuration-mixin>` (``storage/``) defined. These storage mixins
can be used with any of the node configurations. The in-memory configurations just work out of the
box without further configuration. The database based persistence will be explained in a subsequent section,
as you first need to initialise the database.

The mixins work by defining a shared variable which can be referenced by any node configuration

::

    storage = ${_shared.storage}
    storage.parameters.databaseName = "participant1"

If you ever see the following error: ``Could not resolve substitution to a value: ${_shared.storage}``, then
you forgot to add the persistence mixin configuration file.

.. note::

    Please also consult the more :ref:`detailed section on persistence configurations <persistence-config>`.

Persistence using Postgres
~~~~~~~~~~~~~~~~~~~~~~~~~~

While in-memory is great for testing and demos, for more serious tasks, you need to use a database as a persistence layer.
Both the community version and the enterprise version support Postgres as a persistence layer. Make sure that you have
a running Postgres server and you need to create one database per node. The recommended Postgres version to use is 11,
as this is tested the most thoroughly.

The Postgres storage mixin is provided by the file ``storage/postgres.conf``.

If you just want to experiment, you can use Docker to get a Postgres database up and running quickly.
Here are a few commands that come in handy.

First, pull Postgres and start it up.

.. code-block:: bash

    docker pull postgres:14.8-bullseye
    docker run --rm --name pg-docker -e POSTGRES_PASSWORD=docker -d -p 5432:5432 postgres:14.8-bullseye

Then, you can run ``psql`` using:

.. code-block:: bash

    docker exec -it pg-docker psql -U postgres -d postgres

This will invoke ``psql`` interactively. You can exit the prompt with Ctrl-D. If you want to just cat commands, change ``-it`` to ``-i`` in
above command.

Then, create a user for the database using the following SQL command

.. code-block:: sql

    create user canton with encrypted password 'supersafe';

and create a new database for each node, granting the newly created user appropriate permissions

.. code-block:: sql

    create database participant1;
    grant all privileges on database participant1 to canton;

These commands create a database named ``participant1`` and grant the user named ``canton`` access to it using the
password ``supersafe``. Needless to say, you should use your own, secure password.

In order to use the storage mixin, you need to either write these settings into the configuration file, or
pass them using environment variables:

.. code-block:: bash

    export POSTGRES_USER=canton
    export POSTGRES_PASSWORD=supersafe

If you want to run also other nodes with Postgres, you need to create additional databases, one for each.

You can reset the database by dropping then re-creating it:

.. code-block:: sql

    drop database participant1;
    create database participant1;
    grant all privileges on database participant1 to canton;

.. note::

    The storage mixin provides you with an initial configuration. Please consult the more :ref:`extended documentation <persistence-config>`
    for further options.

If you are setting up a few nodes for a test network, you can use a little helper script to create the SQL commands
to setup users and databases:

.. code-block:: bash

   python3 examples/03-advanced-configuration/storage/dbinit.py \
      --type=postgres --user=canton --password=<choose-wisely> --participants=2 --domains=1 --drop

The command will just create the SQL commands for your convenience. You can pipe the output directly into the
``psql`` command

.. code-block:: bash

   python3 examples/03-advanced-configuration/storage/dbinit.py ... | psql -p 5432 -h localhost ...

Setting up a Participant
------------------------

Now that you have made your persistence choice (assuming Postgres hereafter, for
Oracle refer to :ref:`Oracle Persistence <persistence-oracle>`), you could start
your participant just by using one of the example files such as
``$CONF/nodes/participant1.conf`` and start the Canton process using the
``Postgres`` persistence mixin:

.. code-block:: bash

    $CANTON/bin/canton -c $CONF/storage/postgres.conf -c $CONF/nodes/participant1.conf

While this would work, we recommend that you rename your node by changing the configuration file appropriately.

.. note::

    By default, the node will initialise itself automatically using the identity commands :ref:`identity-commands`.
    As a result, the node will create the necessary keys and topology transactions and will initialise itself using
    the name used in the configuration file. Please consult the :ref:`identity management section <identity_management_user_manual>`
    for further information.

This was everything necessary to startup your participant node. However, there are a few steps that you want to take care
of in order to secure the participant and make it usable.

Secure the APIs
~~~~~~~~~~~~~~~

#. By default, all APIs in Canton are only accessible from localhost. If you want to connect to your node from other
   machines, you need to bind to ``0.0.0.0`` instead of localhost. You can do this by setting
   ``address = 0.0.0.0`` within the respective API configuration sections or include the ``api/public.conf``
   configuration mixin.

#. The participant node is managed through the administration API. If you use the console, almost all requests will
   go through the administration API. We recommend that you setup mutual TLS authentication as described in
   the :ref:`TLS documentation section <tls-configuration>`.

#. Applications and users will interact with the participant node using the ledger API. We recommend that you secure your
   API by using TLS. You should also authorize your clients using either JWT or TLS client certificates. The TLS configuration
   is the same as on the administration API.

#. In the example set, there are a set of additional configuration options which allow you to define various
   `JWT <https://jwt.io>`__ based authorizations checks, enforced by the ledger API server. The settings map exactly to the
   options documented as part of the `Daml SDK <https://docs.daml.com/tools/sandbox.html#running-with-authentication>`__.
   There are a few configuration mix-ins defined in ``api/jwt`` for your convenience.

Configure Applications, Users and Connection
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Canton distinguishes static configuration from dynamic configuration. Static configuration are items which are not
supposed to change and are therefore captured in the configuration file. An example is to which port to bind to. Dynamic
configuration are items such as Daml archives (DARs), domain connections or parties. All such changes are effected through
the administration API or the console.

.. note::

    Please consult the section on the :ref:`console commands <canton_console>` and :ref:`administration APIs <administration_apis>`.

If you don't know how to connect to domains, onboard parties or provision Daml code, please read the
:ref:`getting started guide <canton-getting-started>`.

.. todo::
   `Mention the global domain <https://github.com/DACH-NY/canton/issues/7564>`_

..
  .. _connect-global-domain:
  Connect to the Global Domain
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  We are currently operating a global domain. Right now, it is still a testnet, which we reset from time to time. You can
  connect to it using
  ::
      participant1.domains.connect("global", "https://canton.global")


Setting up a Domain
-------------------
In order to setup a domain, you need to decide what kind of domain you want to run. We provide integrations for
different domain infrastructures. These integrations have different levels of maturity. Your current options are

#. Postgres based domain (simplest choice)
#. :ref:`Oracle based domain <oracle-domain>`
#. Hyperledger Fabric based domain
#. Ethereum based domain (demo)

This section will explain how to setup an in-process based domain using Postgres. All other domains are a set of
microservices and part of the Enterprise edition. In any case, you will need to operate the main domain
process which is the point of contact where participants connect to for the initial handshake and parameter download.
The details of how to set this up for other domains than the in-process based Postgres domain are covered by the individual documentations.

.. note::

   Please contact us at sales@digitalasset.com to get access to the Fabric or Ethereum based integration.


The domain requires independent of the underlying ledger a place to store some governance data (or also the messages in
transit in the case of Postgres based domains). The configuration settings for this storage are equivalent to the
settings used for the participant node.

Once you have picked the storage type, you can start the domain using

.. code-block:: bash

    $CANTON/bin/canton -c $CONF/storage/postgres.conf -c $CONF/nodes/domain1.conf

Secure the APIs
~~~~~~~~~~~~~~~

#. As with the participant node, all APIs bind by default to localhost. You need to bind to ``0.0.0.0`` if you want to
   access the APIs from other machines. Again, you can use the appropriate mixin ``api/public.conf``.
#. The administration API should be secured using client certificates as described in :ref:`TLS documentation section <tls-configuration>`.
#. The public API needs to be properly secured using TLS. Please follow the :ref:`corresponding instructions <public-api-configuration>`.

Next Steps
~~~~~~~~~~
The above configuration provides you with an initial setup. Without going into details, the next steps would be:

#. Configure who can join the domain by setting an appropriate permissioning strategy (default is "everyone can join").
#. Configure domain parameters
#. Setup a service agreements which any client connecting has to sign before using the domain.


Multi-Node Setup
----------------

If desired, you can run many nodes in the same process. This is convenient for testing and demonstration purposes. You
can either do this by listing several node configurations in the same configuration file or by invoking the Canton process
with several separate configuration files (which get merged together).

.. code-block:: bash

    $CANTON/bin/canton -c $CONF/storage/postgres.conf -c $CONF/nodes/domain1.conf,$CONF/nodes/participant1.conf
