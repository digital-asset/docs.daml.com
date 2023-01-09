..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. enterprise-only::

Ethereum Domain
---------------

Introduction
~~~~~~~~~~~~~~~~~

The Canton Enterprise Ethereum Sequencer integration interacts via an Ethereum client with a smart contract ``Sequencer.sol``
deployed on an external Ethereum network. It uses the blockchain as source-of-truth for sequenced events and
is currently tested with the Ethereum client `Hyperledger Besu <https://www.hyperledger.org/use/besu>`_.
The :ref:`architecture document <ethereum-architecture>` contains more details on the architecture of the integration.


.. _ethereum-getting-started:

The Ethereum Demo
~~~~~~~~~~~~~~~~~

Prerequisites
^^^^^^^^^^^^^

To run the demo Canton Ethereum deployment, you will need access
to a Canton Enterprise release, the
:ref:`Canton Enterprise docker repository <docker-instructions>`, as well as having docker, docker-compose, and Hyperledger Besu
(`instructions here <https://besu.hyperledger.org/en/stable/HowTo/Get-Started/Installation-Options/Install-Binaries>`_)
installed.

Introduction
^^^^^^^^^^^^

The demo Ethereum deployment can be found inside the examples
directory of the Canton Enterprise release. Unpack the Canton Enterprise release
and then ``cd`` into ``examples/e03-ethereum-sequencer``.

The script ``./run.sh`` from the folder ``examples``
will create a new Besu testnet for the demo deployment and then start the demo.
It has two scenarios: a simple and an advanced scenario.
Both scenarios will start several dockerised services:

* An ethereum testnet, using four Besu nodes with the IBFT consensus protocol.
  This is the same for the simple and advanced scenario.
* An instance of Canton. This includes two Participants and a Canton Enterprise
  Domain with one Ethereum sequencer for the simple scenario and two Ethereum sequencers for the advanced scenario.
  The respective Canton configurations are in ``canton-conf/simple`` and ``canton-conf/advanced``.

The environment variable ``CANTON_VERSION`` is used to select the version of
Canton to use for the demo deployment. This should normally be set to the
version of the Canton Enterprise release being used, but can alternatively be
set to a different version or ``dev`` for the latest main build of Canton.

Simple Scenario
^^^^^^^^^^^^^^^

The simple scenario uses one Canton sequencer whose corresponding ``Sequencer.sol`` contract is
automatically deployed on startup. It uses mutual TLS between Canton and Besu but doesn't enable authorization.

Advanced Scenario
^^^^^^^^^^^^^^^^^

The advanced scenario uses two Canton sequencers, mutual TLS, Ethereum wallets, enables authorization and uses
deploy_sequencer_contract for ``Sequencer.sol`` deployment. In particular, it demonstrates how

* deploy_sequencer_contract can be orchestrated to automatically deploy a ``Sequencer.sol`` instance and configure
  both sequencers to interact with the ``Sequencer.sol`` instance when automatic deployment can't be used.
* authorize_ledger_identity, along with use of Ethereum wallets, can be orchestrated to allow
  another sequencer to interact with a ``Sequencer.sol`` instance when it has authorization enabled.


Running a scenario
^^^^^^^^^^^^^^^^^^^^^^^^^^

To start the simple or advanced demo scenario run:

.. code-block:: bash

    <<canton-release>>/examples/e03-ethereum-sequencer$ CANTON_VERSION=<your version> ./run.sh simple

or

.. code-block:: bash

    <<canton-release>>/examples/e03-ethereum-sequencer$ CANTON_VERSION=<your version> ./run.sh advanced

A new Besu testnet will be created and the demo will begin running with the
created testnet. Once the demo is initialized and running, it will print out

.. code-block:: bash

    ******************************
    Successfully initialized Canton-on-Ethereum
    ******************************

You will then be able to interact with the two participants via their ledger
APIs (or their admin APIs) respectively running on ports ``5011`` and ``5021`` (or ``5012`` and ``5022``).

For example, you can start an instance of the Canton console to connect to the
two remote participants. You can find the Canton binary in ``bin/canton`` of
the Canton Enterprise release artifact.

.. code-block:: bash

    <<canton-release>>/examples/e03-ethereum-sequencer$ ../../bin/canton -c canton-conf/remote.conf

You can then perform various commands in the Canton console:

.. code-block:: bash

    @ remoteParticipant1.id
    res5: ParticipantId = ParticipantId(
      UniqueIdentifier(Identifier("participant1"), Namespace(Fingerprint("01e69a39e2c821fc98eaeb22994b47084162122a01ebcb16dfb2514ccafcedd43d")))
    )

    @ remoteParticipant2.id
    res6: ParticipantId = ParticipantId(
      UniqueIdentifier(Identifier("participant2"), Namespace(Fingerprint("014aeb29dddff83678bc6f1194c363c6f0d18d3a6c9655927a7fb5adc84ec0532c")))
    )

    @ remoteParticipant1.domains.list_connected
    res7: Seq[(com.digitalasset.canton.DomainAlias, com.digitalasset.canton.DomainId)] = List(
      (Domain 'mydomain', mydomain::01537eb8...)
    )

    @ remoteParticipant1.health.ping(remoteParticipant2)
    res8: concurrent.duration.Duration = 968 milliseconds

To shutdown and remove all Docker containers, you can execute ``stop-with-purge.sh``:

.. code-block:: bash

    <<canton-release>>/examples/e03-ethereum-sequencer$ ./stop-with-purge.sh

Generating a Clean Testnet
^^^^^^^^^^^^^^^^^^^^^^^^^^

The directory ``examples/e03-ethereum-sequencer/ibft-testnet`` contains the
script ``generate-testnet.sh``. This automatically generates a clean Besu
network in a ``testnet`` directory, including new randomized private keys.
``generate-testnet.sh`` is automatically called by ``run.sh`` but you may want to understand and edit it to
create your own custom Besu deployment.

When ``generate-testnet.sh`` is run:

* The state from any previous runs of ``generate-testnet.sh`` is deleted and a new directory ``testnet`` is created.
* A genesis file, a set of keys for four Besu nodes and TLS certificates for Canton and Besu are automatically
  generated. These can be found in the folders ``testnet/nodei`` (where i has values 1 to 4) and
  ``testnet/tls``. respectively.
* The four Besu nodes are started via calling ``start-node.sh``.

If the script finds Besu keys or TLS certificates in the same directory as the script, it will attempt to reuse them.
This significantly reduces startup time if you want to test different network configurations.

The generated Besu testnet has been configured largely following these
tutorials:

* https://besu.hyperledger.org/en/stable/Tutorials/Private-Network/Create-IBFT-Network/
* and https://besu.hyperledger.org/en/stable/HowTo/Configure/FreeGas/

Note that the RPC HTTP APIs ``ETH`` and ``TXPOOL`` of Besu need to be enabled when using the Besu driver.

Customization of the Besu network
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The parameters of the generated testnet can be changed by modifying the
``genesis.json`` file defined inline in ``generate-testnet.sh``.
Similarly, the CLI options with which the Besu nodes are started can be configured by modifying ``start-node.sh``

Customization of the Demo Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can also modify the Canton configurations and bootstrap scripts for the demo if, for example, 
you want to `add persistence to the participants <https://www.canton.io/docs/dev/user-manual/usermanual/static_conf.html#persistence>`_.
The Canton configurations are found in

* ``canton-conf/simple`` and
* ``canton-conf/advanced``

for the simple and advanced scenarios, respectively.
If you want to change Ethereum-specific configuration options, (e.g. to configure a different
wallet) please refer to the documentation section on this page and the corresponding
`scaladoc configuration option <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/domain/sequencing/config/EthereumLedgerNodeConfig.html>`_.

Note that if you change port mappings
in the Canton config file you may also need to update the corresponding docker compose files
in directory ``docker-compose/``.


Error codes
~~~~~~~~~~~

The Ethereum Sequencer application auto-detects many common configuration and deployment issues and logs them
as warnings or errors with :ref:`error codes <error_codes>`. If you see such a warning or error, please refer to
the `respective error code explanation and resolution <https://www.canton.io/docs/dev/user-manual/usermanual/error_codes.html#ethereumerrors>`_.


TLS configuration
~~~~~~~~~~~~~~~~~

Canton supports mutual TLS between Canton and Ethereum client nodes and the demo contains an example of how to
configure this.
Concretely, the TLS configuration for Canton expects a key store and the path to the Ethereum TLS certificates:

.. code-block:: none

    _tls {
      canton-key-store {
        path="/canton/testnet-working/tls/canton_store.p12"
        password="password"
      }
      ethereum-certificate-path = "/canton/testnet-working/tls/besu_cert.pem"
    }
    
    canton.sequencers.ethereumSequencer1.sequencer.config.tls = ${_tls}
    


The demo also contains the utility script ``ibft-testnet/generate-tls.sh`` which is called by ``generate-testnet.sh``
and writes the TLS certificates to ``ibft-testnet/testnet/tls``. These certificates are then used by ``start-node.sh``.

If Canton is not configured to use TLS with an Ethereum node, it will attempt to communicate via a HTTP endpoint on the Ethereum node (and HTTPS for TLS).

For more details on the Canton configuration, please see the scaladocs of the `TLS configuration <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/domain/sequencing/config/EthereumLedgerNodeConfig$$TlsConfig.html>`_.
For more details on how to configure Besu to accept TLS connections (as done in the demo, see especially file ``start-node.sh``), please see the `Besu documentation <https://besu.hyperledger.org/en/21.10.6/HowTo/Configure/TLS/Configure-TLS/#create-the-known-clients-file>`_.

Ethereum accounts and wallets
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Canton allows you to configure an Ethereum wallet (and therefore an Ethereum account) to be used by an Ethereum sequencer application.
The configured Ethereum account is used for all interactions of the Ethereum sequencer with the Ethereum
blockchain. If no Ethereum account is explicitly configured, a random Ethereum account is used.

.. TODO(i8913): maybe add more details about nonces here

.. note:: When multiple Ethereum sequencer applications interact with the same ``Sequencer.sol`` instance,
    each Ethereum Sequencer process needs to use a separate Ethereum account.
    Otherwise, transactions may get stuck due to nonce mismatches.


Canton allows configuring a wallet in `UTC JSON <https://theethereum.wiki/accounts__addresses__public_and_private_keys__and_tokens/#UTC_JSON_Keystore_File>`_
and `BIP 39 format <https://en.bitcoin.it/wiki/BIP_0039>`_.

The Ethereum demo includes examples of mix-in wallet configuration files for both formats;
the UTC JSON-based wallet mix-in looks as follows:

.. code-block:: none

    canton.sequencers.ethereumSequencer2.sequencer.config.wallet {
      type = "utc-json-wallet"
      password = "password"
      wallet-path = "advanced/utc-wallet.json"
    }


with following ``utc-wallet.json``:

.. code-block:: none

    canton.sequencers.ethereumSequencer2.sequencer.config.wallet {
      type = "utc-json-wallet"
      password = "password"
      wallet-path = "advanced/utc-wallet.json"
    }


The BIP39-based wallet mix-in looks as follows:

.. code-block:: none

    canton.sequencers.ethereumSequencer2.sequencer.config.wallet {
      type = "utc-json-wallet"
      password = "password"
      wallet-path = "advanced/utc-wallet.json"
    }


For more details, please refer to the `Canton scaladoc documentation <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/domain/sequencing/config/EthereumLedgerNodeConfig$$WalletConfig.html>`_.

Deployment of the sequencer contract
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Single sequencer
^^^^^^^^^^^^^^^^

When using a single sequencer, the easiest way to deploy the corresponding sequencer is by configuring automatic deployment:

.. code-block:: none

              contract {
                type = "automatic-deployment",
                }


This will deploy the ``Sequencer.sol`` smart contract during initialization of the sequencer.

.. TODO(#8487): clarify what happens when restarting something with automatic deployment

Multiple sequencers
^^^^^^^^^^^^^^^^^^^

When deploying multiple Ethereum sequencers for a single domain, it is currently not possible to use automatic
deployment because each sequencer would deploy a separate smart contract. Instead you should first manually deploy
``Sequencer.sol`` or use the console command
`deploy_sequencer_contract <https://www.canton.io/docs/dev/user-manual/usermanual/console.html#deploy-sequencer-contract>`_ and then start the sequencers with all sequencers pointing to the same smart contract.
The Ethereum demo illustrates how to do the latter in file ``docker-compose/docker-compose-advanced.yaml``.

Manual deployment
^^^^^^^^^^^^^^^^^

If you want to manually deploy ``Sequencer.sol`` to your Ethereum network, the file
``<<canton-release/examples/e03-ethereum-sequencer/ibft-testnet/sequencer-binary``
contains the compiled Solidity code you need to deploy. For Besu, for example, you will need to specify the
contents of ``sequencer-binary`` in ``"code": "..."`` as documented `here <https://besu.hyperledger.org/en/stable/HowTo/Configure/Contracts-in-Genesis/#pre-deploying-contracts-in-the-genesis-file>`_.
However, we recommend deploying ``Sequencer.sol`` using automatic deployment or using `deploy_sequencer_contract <https://www.canton.io/docs/dev/user-manual/usermanual/console.html#deploy-sequencer-contract>`_
so you can deploy ``Sequencer.sol`` without needing to restart the blockchain network.

Authorization
~~~~~~~~~~~~~


.. note:: Authorization is an early-access feature and may still significantly change in future releases.

The Ethereum integration offers a simple, optional on-chain authorization mechanism:
inside ``Sequencer.sol`` a "whitelist" of authorized accounts is maintained.
If an Ethereum account is authorized (i.e. part of the list of authorized accounts),
it can authorize other Ethereum accounts and call functions of ``Sequencer.sol``.
If an Ethereum account isn't authorized, any interaction with ``Sequencer.sol``, except the check whether it is authorized,
will fail. Initially, only the Ethereum account which deployed ``Sequencer.sol`` is authorized.

Authorization is enabled or disabled by setting ``authorizationEnabled`` `in the configuration <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/domain/sequencing/config/EthereumLedgerNodeConfig.html>`_ to ``true`` or ``false``:

.. code-block:: none

              authorization-enabled = "false"
              //          ethereum-manual-entry-begin: AutomaticDeployment
              contract {
                type = "automatic-deployment",
                }
              //  ethereum-manual-entry-end: AutomaticDeployment
              tls {
                  canton-key-store {
                    path = "./enterprise/app/src/pack/examples/e03-ethereum-sequencer/ibft-testnet/testnet/tls/canton_store.p12"
                    password = "password"
                  }
                  ethereum-certificate-path = "./enterprise/app/src/pack/examples/e03-ethereum-sequencer/ibft-testnet/testnet/tls/besu_cert.pem"
              }
            }
          }
      }
    }


To authorize another Ethereum account, you can use the console command
`sequencer.authorize_ledger_identity <https://www.canton.io/docs/dev/user-manual/usermanual/console.html#sequencer-authorize-ledger-identity>`_
from a Sequencer that is already authorized.
Please refer to ``canton-conf/advanced/ping.canton`` for an example use of ``sequencer.authorize_ledger_identity``.

.. note::
   If access to all authorized Ethereum accounts for a ``Sequencer.sol`` contract instance with authorization enabled is lost, then access to this ``Sequencer.sol`` contract instance is lost. Recovery from this state is only possible, if
   access to one of the authorized Ethereum accounts is restored.


Requirements for the Ethereum Network
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Canton Ethereum integration is currently tested with the
`IBFT 2.0 consensus protocol <https://besu.hyperledger.org/en/stable/HowTo/Configure/Consensus-Protocols/IBFT/>`__
as illustrated in the demo.
Other setups are possible, but they should fulfill the following requirements:

.. TODO(#4940): Be more precise about how the mining rate changes performance.

* The Ethereum client `Hyperledger Besu <https://besu.hyperledger.org/en/stable>`__ should be used and expose the RPC
    HTTP APIs ``ETH`` and ``TXPOOL``.
* Currently, a free gas network is required. This means setting the gas
  price to zero.
* The block size limit (often measured in gas, and sometimes referred to as
  the 'gas limit') must be larger than any message to be sequenced. It is
  recommended to set this parameter as high as possible.
* The contract size limit must be big enough for the Canton Ethereum Domain
  to store all required state for sequencing messages. It is recommended to set
  this parameter as high as possible.
* Proof of authority protocols are recommended over proof of work.
* Currently, consensus protocols must have
  `immediate finality <https://besu.hyperledger.org/en/stable/Concepts/Consensus-Protocols/Comparing-PoA/#immediate-finality>`_.
  This means that ledger forks should not occur with the chosen consensus protocol.

Furthermore, we also have some suggestions to improve throughput and latency irrespective of the choice of Ethereum client.

Throughput
^^^^^^^^^^^

Generally, the throughput of a Canton system using Ethereum-based sequencers is limited by the throughput of the Ethereum client.
Thus, if an Ethereum-based sequencer does not deliver the desired throughput, the throughput and deployment of the Ethereum clients should be optimized in the first instance.
For Besu performance optimization, some recommendations can be found `in the Besu documentation <https://besu.hyperledger.org/en/latest/HowTo/Use-Privacy/Performance-Best-Practices/#general-performance>`_ - in particular, it is crucial to use a fast storage media.


Latency
^^^^^^^

Within a Canton transaction, there are three sequential sequencing steps, that is, a single Canton transaction leads to at least three sequential messages sent to the sequencer.
This is illustrated, e.g., in the :ref:`message sequence diagram <canton-core-message-sequence-tx-diagram>` of the Canton 101 section.
As a result, a Canton transaction also leads to at least three Ethereum transactions within three different blocks.
Thus, to achieve relatively low latencies, the Ethereum network networks must be configured with a frequent block mining frequency (configured via ``blockperiodseconds`` in Besu)
and ideally co-located with the Canton sequencer node. A block mining frequency of at
least one block per second is recommended.

Trust Properties of the Ethereum Sequencer Integration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The demo integration uses two participants and two different Ethereum
Sequencer nodes. Each participant chooses its preferred Ethereum Sequencer
node, and this node performs reads and writes on behalf of the participant.
Therefore, each participant must trust its chosen Ethereum Sequencer node.
Additionally, each participant must trust some proportion of the nodes in the
Ethereum network as determined by the consensus protocol.

.. _ethereum-high-availability:

High Availability
~~~~~~~~~~~~~~~~~

The Ethereum sequencer currently supports connecting to just one Ethereum client node.
The sequencer node monitors its dependencies and signals to its users any potential issue
that would prevent it from operating correctly.

The health information is exposed as a `Grpc Health service <https://github.com/grpc/grpc/blob/master/doc/health-checking.md>`__;
sequencer clients use this in order to determine whether a sequencer is usable or or not. The
health state is also included in the sequencer status accessible on the Admin API. In order to benefit
from higher availability, clients must connect to multiple sequencers such that they can fail over
automatically to healthy sequencers once some of them become unhealthy.

The following health checks are implemented:

- Can the sequencer node connect and read from the Ethereum RPC API by calling the `eth_synching <https://www.quicknode.com/docs/ethereum/eth_synching>`__ method and check whether a result can be obtained?
- Can the sequencer node connect to its database?

