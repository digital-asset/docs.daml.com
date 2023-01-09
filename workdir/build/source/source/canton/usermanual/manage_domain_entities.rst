..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

Manage Domain Entities
======================

.. _domain_bootstrapping:

Setting up a Distributed Domain With a Single Console
-----------------------------------------------------

If you're running a domain node in its default configuration as shown previously in this current page,
it will have a sequence and mediator embedded and these components will be automatically bootstrapped for you.

If your domain operates with external sequencers and mediators,
you will need to configure a domain manager node (which only runs topology management) and bootstrap your domain
with at least one external sequencer node and one external mediator node.

First make sure the nodes are fresh and have not yet been initialized:

.. code-block:: none

    @ mediator1.health.initialized()
    res1: Boolean = false
    
.. code-block:: none

    @ sequencer1.health.initialized()
    res2: Boolean = false
    
.. code-block:: none

    @ domainManager1.health.initialized()
    res3: Boolean = false
    

Now you can initialize the distributed domain as follows:

.. code-block:: none

    @ domainManager1.setup.bootstrap_domain(Seq(sequencer1), Seq(mediator1))
    
    
    
    

At this point a participant should be able to connect to a sequencer and operate on that domain:

.. code-block:: none

    @ participant1.domains.connect_local(sequencer1)
    
.. code-block:: none

    @ participant1.health.ping(participant1)
    res6: Duration = 744 milliseconds

Domain managers are configured as ``domain-managers`` under the ``canton`` configuration.
Domain managers are configured similarly to domain nodes, except that there are no sequencer, mediator, public api
or service agreement configs.

Please note that if your sequencer is database-based and you're horizontally scaling it as described under
:ref:`sequencer high availability <ha_sequencer>`, you do not need to pass all sequencer nodes into the command above.
Since they all share the same relational database, you only need to run this initialization step on one of them.

For non-database-based sequencer such as Ethereum or Fabric sequencers you need to have each node initialized individually.
You can either initialize such sequencers as part of the initial domain bootstrap shown above or
dynamically add a new sequencer at a later point as described in :ref:`operational processes <dynamically_adding_sequencers>`.

.. _domain_bootstrapping_separate_consoles:

Setting up a Distributed Domain With Separate Consoles
------------------------------------------------------

The process outlined in the previous section only works if all nodes are accessible from the same console environment.
If each node has its own isolated console environment, the bootstrapping process must be coordinated
in steps with the exchange of data via files using any secure channel of communication between the environments.

.. note::

    Please ensure that all of the nodes in the distributed domain are started before proceeding. 


Initially the domain manager must transmit its domain parameters from its console by saving the parameters to a file.
The domain id, serialized as a string, must also be transmitted.

.. code-block:: none

    @ domainManager1.service.get_static_domain_parameters.writeToFile("tmp/domain-bootstrapping-files/params.proto")
    
.. code-block:: none

    @ val domainIdString = domainManager1.id.toProtoPrimitive
    domainIdString : String = "domainManager1::1220288f45b6f17606b40ecbb958e2f1a4ef74e46886cf390d79613af467babdac35"

Then the sequencer must receive this file, deserialize it and initialize itself.
As part of the initialization, the sequencer creates a signing key pair whose public key it must then
transmit via file. Optionally, repeat this for any extra sequencer nodes.

.. code-block:: none

    @ val domainParameters = com.digitalasset.canton.admin.api.client.data.StaticDomainParameters.tryReadFromFile("tmp/domain-bootstrapping-files/params.proto")
    domainParameters : StaticDomainParameters = StaticDomainParametersV1(
      uniqueContractKeys = true,
      requiredSigningKeySchemes = Set(Ed25519, ECDSA-P256, ECDSA-P384),
      requiredEncryptionKeySchemes = Set(ECIES-P256_HMAC256_AES128-GCM),
      requiredSymmetricKeySchemes = Set(AES128-GCM),
      requiredHashAlgorithms = Set(Sha256),
      requiredCryptoKeyFormats = Set(Tink),
      protocolVersion = 4
    )
.. code-block:: none

    @ val domainId = DomainId.tryFromString(domainIdString)
    domainId : DomainId = domainManager1::1220288f45b6...
.. code-block:: none

    @ val initResponse = sequencer1.initialization.initialize_from_beginning(domainId, domainParameters)
    initResponse : com.digitalasset.canton.domain.sequencing.admin.protocol.InitResponse = InitResponse(
      keyId = "sequencer-id",
      publicKey = SigningPublicKey(id = 12200cbd0100..., format = Tink, scheme = Ed25519),
      replicated = false
    )
.. code-block:: none

    @ initResponse.publicKey.writeToFile("tmp/domain-bootstrapping-files/seq1-key.proto")
    

The domain manager must then authorize the sequencer's key. Optionally, repeat this for any extra sequencer keys.

.. code-block:: none

    @ val sequencerPublicKey = SigningPublicKey.tryReadFromFile("tmp/domain-bootstrapping-files/seq1-key.proto")
    sequencerPublicKey : SigningPublicKey = SigningPublicKey(id = 12200cbd0100..., format = Tink, scheme = Ed25519)
.. code-block:: none

    @ domainManager1.setup.helper.authorizeKey(sequencerPublicKey, "sequencer", SequencerId(domainManager1.id))
    

Now the mediator also needs to create a signing key pair and transmit it. Optionally, repeat this for any extra mediator nodes.

.. code-block:: none

    @ mediator1.keys.secret.generate_signing_key("initial-key").writeToFile("tmp/domain-bootstrapping-files/med1-key.proto")
    

The domain manager must now authorize the mediator's key and also authorize the mediator to act as part of this domain.
Optionally, repeat this for any extra mediator nodes.

.. code-block:: none

    @ val mediatorKey = SigningPublicKey.tryReadFromFile("tmp/domain-bootstrapping-files/med1-key.proto")
    mediatorKey : SigningPublicKey = SigningPublicKey(id = 1220589ae8df..., format = Tink, scheme = Ed25519)
.. code-block:: none

    @ val domainId = DomainId.tryFromString(domainIdString)
    domainId : DomainId = domainManager1::1220288f45b6...
.. code-block:: none

    @ domainManager1.setup.helper.authorizeKey(mediatorKey, "mediator1", MediatorId(domainId))
    
.. code-block:: none

    @ domainManager1.topology.mediator_domain_states.authorize(TopologyChangeOp.Add, domainId, MediatorId(domainId), RequestSide.Both)
    res13: com.google.protobuf.ByteString = <ByteString@32df567 size=560 contents="\n\255\004\n\333\001\n\326\001\n\323\001\022 hhMyfGR0PYrz500vuYB2mZvx6NeWysDdR...">

After that, still on the domain manager's console, the domain manager must collect the list of topology transactions, which include all the key authorizations and
a few other things it needs to broadcast to all domain members. This is now saved to a file.

.. code-block:: none

    @ domainManager1.topology.all.list().collectOfType[TopologyChangeOp.Positive].writeToFile("tmp/domain-bootstrapping-files/topology-transactions.proto")
    

The sequencer then reads this set of initial topology transactions and sequences it as the first message to be sequenced in this domain.
This will allow the domain members whose keys were authorized in previous steps to connect to this sequencer and operate with it.
The sequencer will then transmit its connection info.

.. code-block:: none

    @ val initialTopology = com.digitalasset.canton.topology.store.StoredTopologyTransactions.tryReadFromFile("tmp/domain-bootstrapping-files/topology-transactions.proto").collectOfType[TopologyChangeOp.Positive]
    initialTopology : store.StoredTopologyTransactions[TopologyChangeOp.Positive] = Seq(
      StoredTopologyTransaction(
        sequenced = 2023-01-03T23:26:43.487105Z,
        validFrom = 2023-01-03T23:26:43.487105Z,
        validUntil = 2023-01-03T23:26:43.487105Z,
        op = Add,
    ..
    
.. code-block:: none

    @ sequencer1.initialization.bootstrap_topology(initialTopology)
    
.. code-block:: none

    @ sequencer1.sequencerConnection.writeToFile("tmp/domain-bootstrapping-files/sequencer-connection.proto")
    

To initialize the mediator, it will need a connection to the sequencer and the domain parameters.
Optionally, repeat this for any extra mediator nodes.

.. code-block:: none

    @ val sequencerConnection = com.digitalasset.canton.sequencing.SequencerConnection.tryReadFromFile("tmp/domain-bootstrapping-files/sequencer-connection.proto")
    sequencerConnection : com.digitalasset.canton.sequencing.SequencerConnection = GrpcSequencerConnection(
      endpoints = http://127.0.0.1:15075,
      transportSecurity = false,
      customTrustCertificates = None()
    )
.. code-block:: none

    @ val domainParameters = com.digitalasset.canton.admin.api.client.data.StaticDomainParameters.tryReadFromFile("tmp/domain-bootstrapping-files/params.proto")
    domainParameters : StaticDomainParameters = StaticDomainParametersV1(
      uniqueContractKeys = true,
      requiredSigningKeySchemes = Set(Ed25519, ECDSA-P256, ECDSA-P384),
      requiredEncryptionKeySchemes = Set(ECIES-P256_HMAC256_AES128-GCM),
      requiredSymmetricKeySchemes = Set(AES128-GCM),
      requiredHashAlgorithms = Set(Sha256),
      requiredCryptoKeyFormats = Set(Tink),
      protocolVersion = 4
    )
.. code-block:: none

    @ mediator1.mediator.initialize(domainId, MediatorId(domainId), domainParameters, sequencerConnection, None)
    res20: PublicKey = SigningPublicKey(id = 1220878e403b..., format = Tink, scheme = Ed25519)
.. code-block:: none

    @ mediator1.health.wait_for_initialized()
    

The domain manager will also need a connection to the sequencer in order to complete its initialization .

.. code-block:: none

    @ val sequencerConnection = com.digitalasset.canton.sequencing.SequencerConnection.tryReadFromFile("tmp/domain-bootstrapping-files/sequencer-connection.proto")
    sequencerConnection : com.digitalasset.canton.sequencing.SequencerConnection = GrpcSequencerConnection(
      endpoints = http://127.0.0.1:15075,
      transportSecurity = false,
      customTrustCertificates = None()
    )
.. code-block:: none

    @ domainManager1.setup.init(sequencerConnection)
    
.. code-block:: none

    @ domainManager1.health.wait_for_initialized()
    

At this point the distributed domain should be completely initialized and a participant should be able to operate on this domain by connection to the sequencer.

.. code-block:: none

    @ participant1.domains.connect_local(sequencer1)
    
.. code-block:: none

    @ participant1.health.ping(participant1)
    res26: Duration = 645 milliseconds

Additionally, please note that if more than one sequencers have been initialized, any mediator node and domain manager can choose
to connect to just a subset of them.



.. _dynamically_adding_sequencers:

Adding new sequencers to distributed domain
-------------------------------------------

For non-database-based sequencers such as Ethereum or Fabric sequencers, you can either initialize them as part of the
regular :ref:`distributed domain bootstrapping process <domain_bootstrapping>` or dynamically add a new sequencer at a later point as follows:

.. code-block:: scala

          domainManager1.setup.onboard_new_sequencer(
            initialSequencer = sequencer1,
            newSequencer = sequencer2,
          )


Similarly to :ref:`initializing a distributed domain with separate consoles <domain_bootstrapping_separate_consoles>`,
dynamically onboarding new sequencers (supported by Fabric and Ethereum sequencers) can be achieved in separate consoles as follows:

.. code-block:: scala

    
            // Second sequencer's console: write signing key to file
            {
              secondSequencer.keys.secret
                .generate_signing_key(s"${secondSequencer.name}-signing")
                .writeToFile(file1)
            }
    
            // Domain manager's console: write domain params and current topology
            {
              domainManager1.service.get_static_domain_parameters.writeToFile(paramsFile)
    
              val sequencerSigningKey = SigningPublicKey.tryReadFromFile(file1)
    
              domainManager1.setup.helper.authorizeKey(
                sequencerSigningKey,
                s"${secondSequencer.name}-signing",
                sequencerId,
              )
    
              domainManager1.setup.helper.waitForKeyAuthorizationToBeSequenced(
                sequencerId,
                sequencerSigningKey,
              )
    
              domainManager1.topology.all
                .list(domainId.filterString)
                .collectOfType[TopologyChangeOp.Positive]
                .writeToFile(file1)
            }
    
            // Initial sequencer's console: read topology and write snapshot to file
            {
              val topologySnapshotPositive =
                StoredTopologyTransactions
                  .tryReadFromFile(file1)
                  .collectOfType[TopologyChangeOp.Positive]
    
              val sequencingTimestamp = topologySnapshotPositive.lastChangeTimestamp.getOrElse(
                sys.error("topology snapshot is empty")
              )
    
              sequencer.sequencer.snapshot(sequencingTimestamp).writeToFile(file2)
            }
    
            // Second sequencer's console: read topology, snapshot and domain params
            {
              val topologySnapshotPositive =
                StoredTopologyTransactions
                  .tryReadFromFile(file1)
                  .collectOfType[TopologyChangeOp.Positive]
    
              val state = SequencerSnapshot.tryReadFromFile(file2)
    
              val domainParameters = StaticDomainParameters.tryReadFromFile(paramsFile)
    
              secondSequencer.initialization
                .initialize_from_snapshot(
                  domainId,
                  topologySnapshotPositive,
                  state,
                  domainParameters,
                )
                .publicKey
    
              secondSequencer.health.initialized() shouldBe true
    
            }
    

