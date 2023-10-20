..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
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

.. snippet:: distributed_domain_install
    .. success:: mediator1.health.initialized()
    .. assert:: !RES
    .. success:: sequencer1.health.initialized()
    .. assert:: !RES
    .. success:: domainManager1.health.initialized()
    .. assert:: !RES

The domain manager also needs its identity to be generated and ready before we can bootstrap the domain:

.. snippet:: distributed_domain_install
    .. success:: domainManager1.health.wait_for_identity()

.. note::

    This is technically only required when accessing the domain manager through a remote console, but is a good practice regardless.

Now you can initialize the distributed domain as follows:

.. snippet:: distributed_domain_install
    .. success:: domainManager1.setup.bootstrap_domain(Seq(sequencer1), Seq(mediator1))
    .. assert:: mediator1.health.initialized()
    .. assert:: sequencer1.health.initialized()
    .. assert:: domainManager1.health.initialized()

At this point a participant should be able to connect to a sequencer and operate on that domain:

.. snippet:: distributed_domain_install
    .. success:: participant1.domains.connect_local(sequencer1)
    .. success:: participant1.health.ping(participant1)

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

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: domainManager1.service.get_static_domain_parameters.writeToFile("tmp/domain-bootstrapping-files/params.proto")
    .. success:: val domainIdString = domainManager1.id.toProtoPrimitive

Then the sequencer must receive this file, deserialize it and initialize itself.
As part of the initialization, the sequencer creates a signing key pair whose public key it must then
transmit via file. Optionally, repeat this for any extra sequencer nodes.

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: val domainParameters = com.digitalasset.canton.admin.api.client.data.StaticDomainParameters.tryReadFromFile("tmp/domain-bootstrapping-files/params.proto")
    .. success:: val domainId = DomainId.tryFromString(domainIdString)
    .. success:: val initResponse = sequencer1.initialization.initialize_from_beginning(domainId, domainParameters)
    .. success:: initResponse.publicKey.writeToFile("tmp/domain-bootstrapping-files/seq1-key.proto")

The domain manager must then authorize the sequencer's key. Optionally, repeat this for any extra sequencer keys.

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: val sequencerPublicKey = SigningPublicKey.tryReadFromFile("tmp/domain-bootstrapping-files/seq1-key.proto")
    .. success:: domainManager1.setup.helper.authorizeKey(sequencerPublicKey, "sequencer", SequencerId(domainManager1.id))

Now the mediator also needs to create a signing key pair and transmit it. Optionally, repeat this for any extra mediator nodes.

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: mediator1.keys.secret.generate_signing_key("initial-key").writeToFile("tmp/domain-bootstrapping-files/med1-key.proto")

The domain manager must now authorize the mediator's key and also authorize the mediator to act as part of this domain.
Optionally, repeat this for any extra mediator nodes.

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: val mediatorKey = SigningPublicKey.tryReadFromFile("tmp/domain-bootstrapping-files/med1-key.proto")
    .. success:: val domainId = DomainId.tryFromString(domainIdString)
    .. success:: domainManager1.setup.helper.authorizeKey(mediatorKey, "mediator1", MediatorId(domainId))
    .. success:: domainManager1.topology.mediator_domain_states.authorize(TopologyChangeOp.Add, domainId, MediatorId(domainId), RequestSide.Both)

After that, still on the domain manager's console, the domain manager must collect the list of topology transactions, which include all the key authorizations and
a few other things it needs to broadcast to all domain members. This is now saved to a file.

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: domainManager1.topology.all.list().collectOfType[TopologyChangeOp.Positive].writeToFile("tmp/domain-bootstrapping-files/topology-transactions.proto")

The sequencer then reads this set of initial topology transactions and sequences it as the first message to be sequenced in this domain.
This will allow the domain members whose keys were authorized in previous steps to connect to this sequencer and operate with it.
The sequencer will then transmit its connection info.

.. snippet:: distributed_domain_install_separate_consoles
    .. success(output=6):: val initialTopology = com.digitalasset.canton.topology.store.StoredTopologyTransactions.tryReadFromFile("tmp/domain-bootstrapping-files/topology-transactions.proto").collectOfType[TopologyChangeOp.Positive]
    .. assert:: initialTopology.result.size == 6
    .. success:: sequencer1.initialization.bootstrap_topology(initialTopology)
    .. success:: SequencerConnections.single(sequencer1.sequencerConnection).writeToFile("tmp/domain-bootstrapping-files/sequencer-connection.proto")

To initialize the mediator, it will need a connection to the sequencer and the domain parameters.
Optionally, repeat this for any extra mediator nodes.

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: val sequencerConnections = SequencerConnections.tryReadFromFile("tmp/domain-bootstrapping-files/sequencer-connection.proto")
    .. success:: val domainParameters = com.digitalasset.canton.admin.api.client.data.StaticDomainParameters.tryReadFromFile("tmp/domain-bootstrapping-files/params.proto")
    .. success:: mediator1.mediator.initialize(domainId, MediatorId(domainId), domainParameters, sequencerConnections, None)
    .. success:: mediator1.health.wait_for_initialized()

The domain manager will also need a connection to the sequencer in order to complete its initialization .

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: val sequencerConnection = SequencerConnections.tryReadFromFile("tmp/domain-bootstrapping-files/sequencer-connection.proto")
    .. success:: domainManager1.setup.init(sequencerConnection)
    .. success:: domainManager1.health.wait_for_initialized()

At this point the distributed domain should be completely initialized and a participant should be able to operate on this domain by connection to the sequencer.

.. snippet:: distributed_domain_install_separate_consoles
    .. success:: participant1.domains.connect_local(sequencer1)
    .. success:: participant1.health.ping(participant1)

Additionally, please note that if more than one sequencers have been initialized, any mediator node and domain manager can choose
to connect to just a subset of them.


.. _dynamically_adding_sequencers:

Adding new sequencers to distributed domain
-------------------------------------------

For non-database-based sequencers such as Ethereum or Fabric sequencers, you can either initialize them as part of the
regular :ref:`distributed domain bootstrapping process <domain_bootstrapping>` or dynamically add a new sequencer at a later point as follows:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/DynamicOnboardingIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: DynamicallyOnboardSequencer
   :end-before: user-manual-entry-end: DynamicallyOnboardSequencer
   :dedent:

Similarly to :ref:`initializing a distributed domain with separate consoles <domain_bootstrapping_separate_consoles>`,
dynamically onboarding new sequencers (supported by Fabric and Ethereum sequencers) can be achieved in separate consoles as follows:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/DomainBootstrapWithMultipleConsolesAndSequencersTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: DynamicallyOnboardSequencerWithSeparateConsoles
   :end-before: user-manual-entry-end: DynamicallyOnboardSequencerWithSeparateConsoles
   :dedent:

A newly onboarded sequencer only serves events more recent than the "onboarding snapshot". In addition some events may belong to transactions initiated before
the sequencer was onboarded, but the sequencer is not in a position to sign such events and replaces them with "tombstones". If a participant (or mediator)
connects to a newly onboarded sequencer too soon and the subscription encounters a tombstone, the sequencer subscription aborts with a "FAILED_PRECONDITION" error
specifying "InvalidCounter" or "SEQUENCER_TOMBSTONE_ENCOUNTERED". If this occurs, the participant or mediator should connect to another sequencer with a longer
history of sequenced events before switching to the newly onboarded sequencer. To avoid such errors the best practice is to wait at least for the "maximum decision time"
(the sum of the ``participant_response_timeout`` and ``mediator_reaction_timeout`` dynamic domain parameters with a default of 30 seconds each) before connecting
nodes to a newly onboarded sequencer.
