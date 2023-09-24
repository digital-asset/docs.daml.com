..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. enterprise-only::

Fabric Synchronization Domain
=============================

The Canton-on-Fabric integration runs a Canton sync domain where events are sequenced using the `Hyperledger Fabric <https://hyperledger-fabric.readthedocs.io/en/latest/whatis.html>`_ ledger.

Tutorial
--------

To run the demo Canton Fabric deployment, you will need access to the following:


- a Daml Enterprise release with drivers for access to the example files and the Canton binary
- :ref:`Canton Enterprise docker repository <docker-instructions>` access, in order to obtain the Canton docker image

Also make sure to have docker and docker-compose installed.

The following example explains how to set up Canton on Fabric using a topology with 2 sequencer nodes,
(belonging to two different organizations) a topology manager, a mediator, and two participant nodes.

The demo can be found in the examples directory of the Canton Enterprise release.
Unpack the Canton Enterprise release and then ``cd`` into ``examples/e01-fabric-domain/canton-on-fabric``.

Run the script ``./run.sh full``.

The script starts the following:

1. A Fabric ledger with 2 peers and one orderer node.
2. Two Canton Sequencer nodes that interact with the Fabric ledger.
3. A Canton process running a Canton topology manager, a mediator, and two participants. The configuration for this Canton process is in ``config/canton/demo.conf``

Once the script has finished setting up (you should see the ``canton`` service print "Successfully initialized Canton-on-Fabric" together with the Canton console startup message), you will be able to interact with the two participants using the config at ``config/remote/demo.conf``.

You can start an instance of the Canton console to connect to the two remote 
participants (provided you have also installed Canton):

.. code-block:: bash

    <<canton-release>>/examples/e01-fabric-domain/canton-on-fabric$ ../../../bin/canton -c config/remote/demo.conf

You can then perform various commands in the Canton console:

.. code-block:: bash

    @ remoteParticipant1.id
    res1: ParticipantId = PAR::participant1::012c7af9...

    @ remoteParticipant1.domains.list_connected
    res2: Seq[(com.digitalasset.canton.DomainAlias, com.digitalasset.canton.DomainId)] = List((Domain 'myDomain', myDomain::01dafa04...))

    @ remoteParticipant1.health.ping(remoteParticipant2)
    res3: concurrent.duration.Duration = 946 milliseconds

User Manual
-----------

The example files located at ``examples/e01-fabric-domain/canton-on-fabric`` provide you with more flexibility than to run the basic demo just shown.

You will find in this directory our main script called ``run.sh``. If you run the script, it will show you the help instructions with all the options that you can choose to run the deployment with.

The demo deployment will by default use the Canton version from the release.
If you wish to use a different version, you can specify it with the ``CANTON_VERSION``
environment variable. For example, ``export CANTON_VERSION=2.5.1`` to use Canton v2.5.1.
You can choose ``dev`` for the latest main build of Canton.

Depending on which options you choose, it will run a docker-compose command using a different subset of the following docker-compose files below:

- ``docker-compose-ledger.yaml``: Sets up the Fabric ledger. You can see that there is a service in it called ``ledger-setup`` that is a service responsible for creating the crypto materials, setting up the channel and deploying the chaincode. It uses a customized and simplified version of the ``test-network`` from `fabric-samples <https://github.com/hyperledger/fabric-samples/tree/v2.0.0/test-network>`_ inside a docker container.
- ``docker-compose-blockchain-explorer.yaml``: Runs a `blockchain explorer <https://github.com/hyperledger/blockchain-explorer>`_ that allows visualizing the Fabric ledger on the browser.
- ``docker-compose-canton.yaml``: Runs all Canton components: a topology manager, a mediator, the two Fabric sequencer(s), and two participants.

The bootstrapping process of the distributed sync domain is done by the
``docker-compose-canton.yaml`` docker-compose file which uses the ``config/canton/demo.canton`` script.
If you wish to learn more about this process please refer to :ref:`sync domain bootstrapping <domain_bootstrapping>`.

Run with Docker Compose
~~~~~~~~~~~~~~~~~~~~~~~

The script ``run.sh`` works by running ``docker-compose`` using a different combination of the ``docker-compose``
files shown above, depending on the arguments given to the script.

As was shown, to run Canton with two Fabric Sequencers in a multi-sequencer setup, run ``./run.sh full``.
That is equivalent to running the following docker-compose command:

.. code-block:: bash

    <<canton-release>>/examples/e01-fabric-domain/canton-on-fabric$ COMPOSE_PROJECT_NAME="fabric-sequencer-demo" docker-compose -f docker-compose-ledger.yaml -f docker-compose-canton.yaml up

Note that you can at this point connect the remote participants to this setup just like in demo from the tutorial.

Cleanup
~~~~~~~

When you're done running the sequencer, make sure to run ``./run.sh down``.
This will clean up all docker resources so that the next run can happen smoothly.

Using the Canton Binary instead of docker
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To run the full Canton setup separately outside of docker (with the canton binary or jar):

.. code-block:: bash

    <<canton-release>>/examples/e01-fabric-domain/canton-on-fabric$ ./run.sh ledger

After a few seconds you should see the two peers and one orderer nodes are up by running ``docker ps`` and
seeing two ``hyperledger/fabric-peer`` containers exposing ports 9051 and 7051 and one ``hyperledger/fabric-orderer``
exposing the port 7050. Next run the following:

.. code-block:: bash

    <<canton-release>>/examples/e01-fabric-domain/canton-on-fabric$ ../../../bin/canton -c config/self-contained/demo.conf --bootstrap config/canton/demo.canton

To run the jar file instead of the canton binary, simply replace ``../../../bin/canton`` above with ``java -jar ../../../lib/canton-enterprise-*.jar``.

Blockchain Explorer
~~~~~~~~~~~~~~~~~~~

If you wish to start the `Hyperledger Blockchain Explorer <https://github.com/hyperledger/blockchain-explorer>`_
to browse activity on the running Fabric Ledger,
add the ``-e`` flag when running ``./run.sh``.

Alternatively you can use docker-compose as shown before and add ``-f docker-compose-blockchain-explorer.yaml``.

You will then be able to see the explorer web UI in your browser if you go to ``http://localhost:8080``.

You can start the explorer separately after the ledger has been started by simply running the following command:

.. code-block:: bash

    <<canton-release>>/examples/e01-fabric-domain/canton-on-fabric$ COMPOSE_PROJECT_NAME="fabric-sequencer-demo" docker-compose -f docker-compose-blockchain-explorer.yaml up


Note that even when the explorer is working perfectly, it might output some error messages like the following which can be safely ignored:

.. code-block:: none

    [ERROR] FabricGateway - Failed to get block 0 from channel undefined :  TypeError: Cannot read property 'toString' of undefined

Fabric Setup
------------

The Fabric Sequencer operates on top of the Fabric Ledger and uses it as the source of truth for the state of the sequencer (all the messages and the order of them). 

In order for The Fabric Sequencer to successfully operate on a given Fabric Ledger,
that ledger must have been set up with at least one channel where the Canton Sequencer chaincode has been installed
and the sequencer needs to be configured properly to have access to the ledger.

As mentioned previously, for our demo setup we use a slightly modified version of
the ``test-network`` scripts from `fabric-samples <https://github.com/hyperledger/fabric-samples/tree/v2.0.0/test-network>`_ inside a docker container
to setup a simple local docker-based Fabric network.
This script uses many of the `Fabric CLI commands <https://hyperledger-fabric.readthedocs.io/en/release-2.2/command_ref.html>`_
to set up this network, such as `configtxgen <https://hyperledger-fabric.readthedocs.io/en/release-2.2/commands/configtxgen.html>`_,
`peer channel <https://hyperledger-fabric.readthedocs.io/en/release-2.2/commands/peerchannel.html>`_,
`peer chaincode <https://hyperledger-fabric.readthedocs.io/en/release-2.2/commands/peerchaincode.html>`_, and
`peer lifecycle <https://hyperledger-fabric.readthedocs.io/en/release-2.2/commands/peerlifecycle.html>`_.
In a real-life scenario one might use this CLI to set up the ledger or some specific UI provided by a cloud service provider
that hosts Blockchain services.

Regarding the chaincode setup, the Fabric Sequencer expects that the chaincode is initialized by calling the function ``init`` (no arguments needed) and with the ``--isInit`` flag turned on.
You can find the chaincode source at ``/ledger-setup/chaincode/src/github.com/digital-asset/sequencer``.

In order to configure a Fabric Sequencer in Canton, make sure to set ``canton.sequencers.<your sequencer>.sequencer.type = "fabric"``.
The rest of the Fabric sequencer-specific config will be under ``canton.sequencers.<your sequencer>.sequencer.config``.
Within this subconfig, you'll need to set the ``user`` key with Fabric client details so that the sequencer can invoke chaincode functions and read from the ledger.
You'll also need to set ``organizations`` details which include peers and orderers connection details that the sequencer will have access to.
You must define at least one peer that is from the same organization as your user.

The sequencer needs access to at least enough peers to fulfil the `chaincode endorsement policy <https://hyperledger-fabric.readthedocs.io/en/latest/policies/policies.html#chaincode-endorsement-policies>`__.
An endorsement policy that requires a single peer is enough and is what we recommend (more at :ref:`Endorsement Policies <fabric_endorsement>`).

It is possible to indicate the channel name with the ``channel.name`` key and the chaincode name with the ``channel.chaincode.name`` key (defaults to "sequencer").
This is all exemplified, including extensive commentary, in the config file used for the first sequencer of the demo, which you
can find at ``examples/e01-fabric-domain/canton-on-fabric/config/fabric/fabric-config-1.conf``.

By default, the sequencer application will start reading blocks from the ledger from the genesis block.
We can signal a later starting point by setting ``channel.chaincode.start-block-height`` to a specific number
in case the chaincode has been deployed much later than genesis.

Block Cutting Parameters and Performance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is possible to configure the block cutting parameters of the ledger by changing the file at ``ledger-setup/configtx/configtx.yaml``.

The relevant parameters are the following:

- ``Orderer.BatchTimeout``: The amount of time to wait before creating a block.
- ``Orderer.BatchSize.MaxMessageCount``: The maximum number of transactions to permit in a block (block size).

Note: In other kinds of Fabric Ledger setups, one should be able to configure these parameters in different ways.

If your use case operates under high traffic, you may benefit from increasing the block size in order to increase your throughput at the expense of latency.
If you care more about latency and don't need to support high traffic, then decreasing block size will be of help.

Currently, we have set the values of 200ms for batch timeout and 50 for block size as it has empirically shown to be a good tradeoff
after some rounds of long running tests, but feel free to pick parameters that fit your use-case best.

Note: See slide 17 of http://www.mscs.mu.edu/~mascots/Papers/blockchain.pdf for a discussion on block size influence on throughput and latency.

.. _fabric_authorization:

Authorization
~~~~~~~~~~~~~

When operating the Fabric infrastructure to support the Fabric Sequencer one may want to authorize only
certain organizations to determine the sequencer's behavior.

Only the organizations included in the `Fabric Channel <https://hyperledger-fabric.readthedocs.io/en/release-2.2/create_channel/create_channel_overview.html>`__
will be able to operate on the ledger.

Fabric `Policies <https://hyperledger-fabric.readthedocs.io/en/latest/policies/policies.html>`__ can also be used to limit how
the capabilities of organizations in the channel. See more on that under :ref:`Endorsement Policies <fabric_endorsement>` below.

.. _fabric_endorsement:

Endorsement Policies
~~~~~~~~~~~~~~~~~~~~

Fabric `Policies <https://hyperledger-fabric.readthedocs.io/en/latest/policies/policies.html>`__ can be used to define how members come to agreement on accepting or rejecting changes to the network, a channel or a smart contract.

Versatile policies can be written using combinations of ``AND``, ``OR`` and ``NOutOf`` (`more detail here <https://hyperledger-fabric.readthedocs.io/en/latest/policies/policies.html#how-do-you-write-a-policy-in-fabric>`__).

The most relevant kinds of policies for our purposes here are the `channel configuration policy <https://hyperledger-fabric.readthedocs.io/en/latest/policies/policies.html#an-example-channel-configuration-policy>`__ (defined at the channel level)
and `endorsement policies <https://hyperledger-fabric.readthedocs.io/en/latest/policies/policies.html#chaincode-endorsement-policies>`__  (defined at the chaincode level).

See other kinds of policies `here <https://hyperledger-fabric.readthedocs.io/en/release-2.2/security_model.html#policies>`__.

We recommend setting up a single peer endorsement policy.

We do not benefit from the chaincode endorsements because there is no mutable state in the chaincode or special logic that
needs to be endorsed. We care more about correct ordering of blocks, which is taken care of by the ordering service.
Because of that, there is no point in using more complex endorsement policies.
A single peer endorsement policy also simplify configuration and increases availability.
The demo we ship is configured like this (at `ledger-setup/configtx/configtx.yaml`, under `Application.Policies.Endorsement`.)

.. _fabric_ha:

High Availability
~~~~~~~~~~~~~~~~~

When configuring the Fabric sequencer, make sure to provide access to at least enough peers to fulfill the `chaincode endorsement policy <https://hyperledger-fabric.readthedocs.io/en/latest/policies/policies.html#chaincode-endorsement-policies>`__
that has been configured.

Access to additional peers may also be configured, to make the setup more highly available and to avoid a scenario where
the crash of one peer would cause transactions to stop going through due to lack of enough endorsements.

If a client is connected to more than one Fabric Sequencer and each sequencer defines a different set of connections to
Fabric peers (and orderers), the client will benefit from another level of availability.
If of the sequencers is not healthy, the client will simply fail over to the ones that are still healthy.
