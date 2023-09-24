..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _sequencer_connections:

Sequencer Connections
=====================

Any member of a Canton network, whether a participant, mediator or topology manager, connects to the sync
domain by virtue of connecting to a sequencer of that sync domain (there can be multiple thereof). The
component managing this connection is called the ``SequencerClient``.

A participant can connect to multiple sync domains (preview) simultaneously, but a mediator or topology
manager will only connect to a single sync domain. Therefore, managing the sequencer connections of a participant
differs slightly from managing a mediator or topology manager connection.

In the following sections, we will explain how to manage such sequencer connections.

Participant Connections
-----------------------

The :ref:`sync domain connectivity commands <participant_domain_connectivity>` allow the administrator of a Canton node
to manage connectivity to sync domains. Generally, the key command to add new connections is given by the
:ref:`register command <domains.register>`. While this is the command with the broadest ability to configure
the connection, there are a few convenience macros that combine a series of steps to simplify administrative
operations.

Connect Using Macros
^^^^^^^^^^^^^^^^^^^^

.. _connectivity_participant_connect_local:

Connect to Local Sequencers
~~~~~~~~~~~~~~~~~~~~~~~~~~~

When a participant should connect to a sequencer or sync domain that is running in the same process, you
can use the ``domains.connect_local`` macro and simply provide the reference to the local node.

.. snippet:: participant_connectivity
    .. assert:: { domainManager1.setup.bootstrap_domain(Seq(sequencer1), mediators.local); true }
    .. success:: participant1.domains.connect_local(sequencer1)
    .. assert:: { participant1.health.ping(participant1); true }
    .. assert:: { Seq(sequencer2, sequencer3).foreach(_.health.wait_for_initialized()); true }

The ``connect_local`` macro will generate the appropriate configuration settings for the provided sequencer and instruct
the participant to connect to it using the ``register`` command.

Please note that you can also pass a local ``DomainReference`` to the ``connect_local`` call in case you are running an
embedded sync domain.

.. _connectivity_participant_connect_remote:

Connect to Remote Sequencers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you are connecting to a sequencer that is running on a remote host, you need to know the address and port
the sequencer is configured to listen to. You can print out the port the sequencer is listening to using:

.. snippet:: participant_connectivity
    .. success:: sequencer1.config.publicApi.port

You can also check that the address is set such that remote processes can connect to it:

.. snippet:: participant_connectivity
    .. success:: sequencer1.config.publicApi.address
    .. assert:: sequencer1.config.publicApi.address == "0.0.0.0"

By default, a sequencer will listen to ``127.0.0.1``, which is localhost. These is a safe default and
it means that only processes running locally can connect to the sequencer (it is also set by default
for the Ledger API and the Admin API). If you want to support remote processes connecting to the given
sequencer, you need to explicitly configure it using:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/documentation-snippets/open-public-api.conf

In this example, ``sequencer1`` and ``sequencer2`` are configured without TLS, whereas ``sequencer3`` is configured
to use TLS:

.. snippet:: participant_connectivity
    .. success:: sequencer3.config.publicApi.tls
    .. assert:: sequencer3.config.publicApi.tls.nonEmpty

To connect to ``sequencer3`` using the ``connect`` macro, we need to create an URL string:

.. snippet:: participant_connectivity
    .. success:: val port = sequencer3.config.publicApi.port
    .. success:: val url = s"https://127.0.0.1:${port}"

Please note that you need to adjust the ``https`` to ``http`` if you are not using ``TLS`` on the public sequencer Api.
If the sequencer is using TLS certificates (e.g. self-signed) that cannot be automatically validated using your
JVMs trust store, you have to provide the custom certificate such that the client can verify the sequencer public API
TLS certificate. Let's assume that this root certificate is given by:

.. snippet:: participant_connectivity
    .. success:: val certificatesPath = "tls/root-ca.crt"

You can now connect the participant to the sequencer using:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.connect("mydomain", connection = url, certificatesPath = certificatesPath)
    .. assert:: { participant2.health.ping(participant2); true }

.. _connectivity_participant_connect_ha:

Connect to High-Availability Sequencers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. enterprise-only::

The Daml Enterprise version of Canton lets you connect a participant to multiple sequencers for the purpose of high
availability. If one sequencer shuts down, the participant will then automatically fail over to the second
sequencer.

Such a connection can be configured using the ``connect_multi``:

.. snippet:: participant_connectivity
    .. success:: participant3.domains.connect_multi("mydomain", Seq(sequencer1, sequencer2))
    .. assert:: { participant3.health.ping(participant3); true }

In such a setting, if a sequencer node goes down, the participant will round-robin through the available list of sequencers.
The :ref:`reference documentation <domains.connect_multi>` provides further information on how to
connect to highly available sequencers, and the :ref:`high availability guide <ha_user_manual>` has instructions
on how to set up highly available sync domains.

Currently, all the sequencer connections used by a node need to be using TLS or not. A mixed mode where one sequencer
is using TLS and another not is not supported.

.. _connectivity_participant_connect_using_register:

Connect Using Register
~~~~~~~~~~~~~~~~~~~~~~

The highest level of control over your sync domain connection is given by using ``register`` with a configuration of
type ``DomainConnectionConfig``. By default, the connection configuration only requires two arguments: the sync domain
alias and the connection URL. In this guide, we'll cover all arguments.

First, we need to associate the sync domain connection to an alias. An alias is an arbitrary name chosen by the operator of
the participant to manage the given connection:

.. snippet:: participant_connectivity
    .. success:: val domainAlias = "mydomain"

A sync domain alias is just a string wrapped into the type "DomainAlias". This is done implicitly in the console, which allows
you to use a string instead.

Next, you need to create a connection description of type ``SequencerConnection``. The public sequencer API in Canton
is based on gRPC, which uses ``HTTP 2.0``. In this example, we build the URLs by inspecting the configurations:

.. snippet:: participant_connectivity
    .. success:: val urls = Seq(sequencer1, sequencer2).map(_.config.publicApi.port).map(port => s"http://127.0.0.1:${port}")

However, the URL can also be entered as a string. A connection is then built using:

.. snippet:: participant_connectivity
    .. success:: val sequencerConnectionWithoutHighAvailability = com.digitalasset.canton.sequencing.GrpcSequencerConnection.tryCreate(urls(0))

A second sequencer URL can be added using:

.. snippet:: participant_connectivity
    .. success:: val sequencerConnection = sequencerConnectionWithoutHighAvailability.addEndpoints(urls(1))

While the ``connect`` macros allow you to pass in a file path as an argument for the optional TLS certificate, you need
to resolve this argument and load the certificate into a ``ByteString`` when working with ``GrpcSequencerConnection``.
There is a utility function that allows you to read a certificate from a file into a ByteString such that it can be used
to create an appropriate sequencer connection:

.. snippet:: participant_connectivity
    .. success:: val certificate = com.digitalasset.canton.util.BinaryFileUtil.tryReadByteStringFromFile("tls/root-ca.crt")
    .. success:: val connectionWithTLS = com.digitalasset.canton.sequencing.GrpcSequencerConnection.tryCreate("https://daml.com", customTrustCertificates = Some(certificate))

Next, you can assign a priority to the sync domain by setting the priority parameter:

.. snippet:: participant_connectivity
    .. success:: val priority = 10 // default is 0 if not set

This parameter is used to determine the sync domain to which a transaction should be sent if there are multiple sync domains
connected (early access feature). The sync domain with the highest priority that can run a certain transaction is selected.

Finally, when configuring a sync domain connection, the parameter ``manualConnect`` can be used when the sync domain
should not be auto-reconnected on startup. By default, you would set:

.. snippet:: participant_connectivity
    .. success:: val manualConnect = false

If a sync domain connection is configured to be manual, it will not reconnect automatically on startup; it has to
be reconnected specifically using:

.. snippet:: participant_connectivity
    .. success:: participant3.domains.reconnect("mydomain")

Very security-sensitive users that do not trust TLS to check for authenticity of the sequencer API can additionally
pass an optional ``domainId`` of the target sync domain into the configuration. In this case, the participant will check
that the sequencer it is connecting to can produce the cryptographic evidence that it actually is the expected sync domain.
The domainId can be obtained from the sync domain manager:

.. snippet:: participant_connectivity
    .. success:: val domainId = Some(domainManager1.id)

These parameters together can be used to define a connection configuration:

.. snippet:: participant_connectivity
    .. success:: val config = DomainConnectionConfig(domain = "mydomain", sequencerConnection, manualConnect, domainId, priority)

All other parameters are expert settings and should not be used. The ``config`` object can now be used to connect a
participant to a sequencer:

.. snippet:: participant_connectivity
    .. success:: participant4.domains.register(config)

.. _connectivity_participant_inspect:

Inspect Connections
^^^^^^^^^^^^^^^^^^^

You can inspect the registered sync domain connections using:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.list_registered()
    .. assert::  participant2.domains.list_registered().length == 1

You can also get the aliases of the currently connected sync domains using:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.list_connected()
    .. assert::  participant2.domains.list_connected().length == 1

And you can inspect the configuration of a specific sync domain connection using:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.config("mydomain")

.. _connectivity_participant_modify:

Modify Connections
^^^^^^^^^^^^^^^^^^

Sync domain connection configurations can be updated using the ``modify`` function:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.modify("mydomain", _.copy(priority = 20))

The second argument is a mapping function which receives as input argument a ``DomainConnectionConfig``
and needs to return a ``DomainConnectionConfig``. Every case class has a default ``copy`` method that allows
overriding arguments.

.. todo(#13058): immediately apply a new sequencer connection config

The modify command on the participant will only take effect after restarting the sync domain connection
explicitly (or restarting the entire node):

.. snippet:: participant_connectivity
    .. success:: participant2.domains.disconnect("mydomain")
    .. success:: participant2.domains.reconnect("mydomain")

On the mediator and sync domain manager node, the change is effected immediately.

Update a Custom TLS Trust Certificate
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In some cases (in particular in test environments), you might be using self-signed certificates
as a root of trust for the TLS sequencer connection. Whenever this root of trust changes, the clients
need to update the custom root certificate accordingly.

This can be done through the following steps. First, you need to load the certificate from a file:

.. snippet:: participant_connectivity
    .. success:: val certificate = com.digitalasset.canton.util.BinaryFileUtil.tryReadByteStringFromFile("tls/root-ca.crt")

This step loads the root certificate from a file and stores it into a variable that can be used subsequently.
Next, you create a new connection object, passing in the certificate:

.. snippet:: participant_connectivity
    .. success:: val connection = com.digitalasset.canton.sequencing.GrpcSequencerConnection.tryCreate(url, customTrustCertificates = Some(certificate))

Finally, you update the sequencer connection settings on the participant node:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.modify("mydomain", _.copy(sequencerConnections=SequencerConnections.single(connection)))

For mediators/sync domain managers, you can update the certificate accordingly.

.. _connectivity_participant_reconnect:

Enable and Disable Connections
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A participant can disconnect from a sync domain using:

.. snippet:: participant_connectivity
    .. assert:: participant2.domains.list_connected().length == 1
    .. success:: participant2.domains.disconnect("mydomain")
    .. assert:: participant2.domains.list_connected().isEmpty

Reconnecting to the sync domain can be done either on a per sync domain basis:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.reconnect("mydomain")

Or for all registered sync domains that are not configured to require a manual connection:

.. snippet:: participant_connectivity
    .. success:: participant2.domains.reconnect_all()


Mediator and Synchronization Domain Manager
-------------------------------------------

Both the mediator and the sync domain manager connect to the sync domain using sequencer connections. The sequencer connections
are configured when the nodes are initialized:

.. snippet:: participant_connectivity
    .. success(output=6):: mediator1.mediator.help("initialize")

The sequencer connection of a mediator and sync domain manager can be inspected using:

.. snippet:: participant_connectivity
    .. success:: mediator1.sequencer_connection.get()

In some cases, the connection settings have to be updated. For this purpose, the two following functions can be used.
First, the connection information can just be set using:

.. snippet:: participant_connectivity
    .. success:: mediator1.sequencer_connection.set(sequencer1.sequencerConnection)

It can also be amended using:

.. snippet:: participant_connectivity
    .. success:: mediator1.sequencer_connection.modify(_.addEndpoints(sequencer2.sequencerConnection))
    .. assert:: participant2.health.maybe_ping(participant2).nonEmpty

Please note that the connection changes immediately, without requiring a restart.
