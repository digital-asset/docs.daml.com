..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _sequencer_connections:

Sequencer Connections
=====================

Any member of a Canton network, whether a participant, mediator or topology manager, connects to the
domain by virtue of connecting to a sequencer of that domain (there can be multiple thereof). The
component managing this connection is called the ``SequencerClient``.

A participant can connect to multiple domains (preview) simultaneously, but a mediator or topology
manager will only connect to a single domain. Therefore, managing the sequencer connections of a participant
differs slightly from managing a mediator or topology manager connection.

In the following sections, we will explain how to manage such sequencer connections.

Participant Connections
-----------------------

The :ref:`domain connectivity commands <participant_domain_connectivity>` allow the administrator of a Canton node
to manage connectivity to domains. Generally, the key command to add new connections is given by the
:ref:` register command <participant.domains.register>`. While this is the command with the broadest ability to configure
the connection, there are a few convenience macros that combine a series of steps to simplify administrative
operations.

Connect Using Macros
^^^^^^^^^^^^^^^^^^^^

.. _connectivity_participant_connect_local:

Connect to Local Sequencers
~~~~~~~~~~~~~~~~~~~~~~~~~~~

When a participant should connect to a sequencer or domain that is running in the same process, you
can use the ``domains.connect_local`` macro and simply provide the reference to the local node.

    
.. code-block:: none

    @ participant1.domains.connect_local(sequencer1)
    
    
    

The ``connect_local`` macro will generate the appropriate configuration settings for the provided sequencer and instruct
the participant to connect to it using the ``register`` command.

Please note that you can also pass a local ``DomainReference`` to the ``connect_local`` call in case you are running an
embedded domain.

.. _connectivity_participant_connect_remote:

Connect to Remote Sequencers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you are connecting to a sequencer that is running on a remote host, you need to know the address and port
the sequencer is configured to listen to. You can print out the port the sequencer is listening to using:

.. code-block:: none

    @ sequencer1.config.publicApi.port
    res2: Port = 15057

You can also check that the address is set such that remote processes can connect to it:

.. code-block:: none

    @ sequencer1.config.publicApi.address
    res3: String = "0.0.0.0"
    

By default, a sequencer will listen to ``127.0.0.1``, which is localhost. These is a safe default and
it means that only processes running locally can connect to the sequencer (it is also set by default
for the Ledger API and the Admin API). If you want to support remote processes connecting to the given
sequencer, you need to explicitly configure it using:

.. code-block:: none

    // enable access of remote processes to the sequencer
    canton.sequencers.sequencer1.public-api.address = 0.0.0.0

In this example, ``sequencer1`` and ``sequencer2`` are configured without TLS, whereas ``sequencer3`` is configured
to use TLS:

.. code-block:: none

    @ sequencer3.config.publicApi.tls
    res4: Option[TlsBaseServerConfig] = Some(
      value = TlsBaseServerConfig(
        certChainFile = ExistingFile(file = ./tls/sequencer3-127.0.0.1.crt),
        privateKeyFile = ExistingFile(file = ./tls/sequencer3-127.0.0.1.pem),
        minimumServerProtocolVersion = Some(value = "TLSv1.2"),
        ciphers = Some(
          value = List(
            "TLS_AES_256_GCM_SHA384",
            "TLS_CHACHA20_POLY1305_SHA256",
            "TLS_AES_128_GCM_SHA256",
            "TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384",
            "TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256"
          )
        )
      )
    )
    

To connect to ``sequencer3`` using the ``connect`` macro, we need to create an URL string:

.. code-block:: none

    @ val port = sequencer3.config.publicApi.port
    port : Port = 15053
.. code-block:: none

    @ val url = s"https://127.0.0.1:${port}"
    url : String = "https://127.0.0.1:15053"

Please note that you need to adjust the ``https`` to ``http`` if you are not using ``TLS`` on the public sequencer Api.
If the sequencer is using TLS certificates (e.g. self-signed) that cannot be automatically validated using your
JVMs trust store, you have to provide the custom certificate such that the client can verify the sequencer public API
TLS certificate. Let's assume that this root certificate is given by:

.. code-block:: none

    @ val certificatesPath = "tls/root-ca.crt"
    certificatesPath : String = "tls/root-ca.crt"

You can now connect the participant to the sequencer using:

.. code-block:: none

    @ participant2.domains.connect("mydomain", connection = url, certificatesPath = certificatesPath)
    res8: DomainConnectionConfig = DomainConnectionConfig(
      domain = Domain 'mydomain',
      sequencerConnection = GrpcSequencerConnection(
        endpoints = https://127.0.0.1:15053,
        transportSecurity = true,
        customTrustCertificates = Some(2d2d2d2d2d42)
      ),
      manualConnect = false,
      domainId = None(),
      priority = 0,
      initialRetryDelay = None(),
      maxRetryDelay = None()
    )
    

.. _connectivity_participant_connect_ha:

Connect to High-Availability Sequencers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. enterprise-only::

The Enterprise version of Canton lets you connect a participant to multiple sequencers for the purpose of high
availability. If one sequencer shuts down, the participant will then automatically fail over to the second
sequencer.

Such a connection can be configured using the ``connect_multi``:

.. code-block:: none

    @ participant3.domains.connect_multi("mydomain", Seq(sequencer1, sequencer2))
    res9: DomainConnectionConfig = DomainConnectionConfig(
      domain = Domain 'mydomain',
      sequencerConnection = GrpcSequencerConnection(
        endpoints = Seq(http://0.0.0.0:15057, http://127.0.0.1:15055),
        transportSecurity = false,
        customTrustCertificates = None()
      ),
      manualConnect = false,
      domainId = None(),
      priority = 0,
      initialRetryDelay = None(),
      maxRetryDelay = None()
    )
    

In such a setting, if a sequencer node goes down, the participant will round-robin through the available list of sequencers.
The :ref:`reference documentation <domains.connect_multi>` provides further information on how to
connect to highly available sequencers, and the :ref:`high availability guide <ha_user_manual>` has instructions
on how to set up highly available domains.

Currently, all the sequencer connections used by a node need to be using TLS or not. A mixed mode where one sequencer
is using TLS and another not is not supported.

.. _connectivity_participant_connect_using_register:

Connect Using Register
~~~~~~~~~~~~~~~~~~~~~~

The highest level of control over your domain connection is given by using ``register`` with a configuration of
type ``DomainConnectionConfig``. By default, the connection configuration only requires two arguments: the domain
alias and the connection URL. In this guide, we'll cover all arguments.

First, we need to associate the domain connection to an alias. An alias is an arbitrary name chosen by the operator of
the participant to manage the given connection:

.. code-block:: none

    @ val domainAlias = "mydomain"
    domainAlias : String = "mydomain"

A domain alias is just a string wrapped into the type "DomainAlias". This is done implicitly in the console, which allows
you to use a string instead.

Next, you need to create a connection description of type ``SequencerConnection``. The public sequencer API in Canton
is based on gRPC, which uses ``HTTP 2.0``. In this example, we build the URLs by inspecting the configurations:

.. code-block:: none

    @ val urls = Seq(sequencer1, sequencer2).map(_.config.publicApi.port).map(port => s"http://127.0.0.1:${port}")
    urls : Seq[String] = List("http://127.0.0.1:15057", "http://127.0.0.1:15055")

However, the url can also be entered as a string. A connection is then built using:

.. code-block:: none

    @ val sequencerConnectionWithoutHighAvailability = com.digitalasset.canton.sequencing.GrpcSequencerConnection.tryCreate(urls(0))
    sequencerConnectionWithoutHighAvailability : com.digitalasset.canton.sequencing.GrpcSequencerConnection = GrpcSequencerConnection(
      endpoints = http://127.0.0.1:15057,
      transportSecurity = false,
      customTrustCertificates = None()
    )

A second sequencer URL can be added using:

.. code-block:: none

    @ val sequencerConnection = sequencerConnectionWithoutHighAvailability.addConnection(urls(1))
    sequencerConnection : com.digitalasset.canton.sequencing.SequencerConnection = GrpcSequencerConnection(
      endpoints = Seq(http://127.0.0.1:15057, http://127.0.0.1:15055),
      transportSecurity = false,
      customTrustCertificates = None()
    )

While the ``connect`` macros allow you to pass in a file path as an argument for the optional TLS certificate, you need
to resolve this argument and load the certificate into a ``ByteString`` when working with ``GrpcSequencerConnection``.
There is a utility function that allows you to read a certificate from a file into a ByteString such that it can be used
to create an appropriate sequencer connection:

.. code-block:: none

    @ val certificate = com.digitalasset.canton.util.BinaryFileUtil.tryReadByteStringFromFile("tls/root-ca.crt")
    certificate : com.google.protobuf.ByteString = <ByteString@3c0f533c size=1960 contents="-----BEGIN CERTIFICATE-----\nMIIFeTCCA2GgAwIBAgI...">
.. code-block:: none

    @ val connectionWithTLS = com.digitalasset.canton.sequencing.GrpcSequencerConnection.tryCreate("https://daml.com", customTrustCertificates = Some(certificate))
    connectionWithTLS : com.digitalasset.canton.sequencing.GrpcSequencerConnection = GrpcSequencerConnection(
      endpoints = https://daml.com:443,
      transportSecurity = true,
      customTrustCertificates = Some(2d2d2d2d2d42)
    )

Next, you can assign a priority to the domain by setting the priority parameter:

.. code-block:: none

    @ val priority = 10 // default is 0 if not set
    priority : Int = 10

This parameter is used to determine the domain to which a transaction should be sent if there are multiple domains
connected (early access feature). The domain with the highest priority that can run a certain transaction will be picked.

Finally, when configuring a domain connection, the parameter ``manualConnect`` can be used when the domain
should not be auto-reconnected on startup. By default, you would set:

.. code-block:: none

    @ val manualConnect = false
    manualConnect : Boolean = false

If a domain connection is configured to be manual, it will not reconnect automatically on startup; it has to
be reconnected specifically using:

.. code-block:: none

    @ participant3.domains.reconnect("mydomain")
    res18: Boolean = true

Very security sensitive users that do not trust TLS to check for authenticity of the sequencer API can additionally
pass an optional ``domainId`` of the target domain into the configuration. In this case, the participant will check
that the sequencer it is connecting to can produce the cryptographic evidence that it actually is the expected domain.
The domainId can be obtained from the domain manager:

.. code-block:: none

    @ val domainId = Some(domainManager1.id)
    domainId : Some[DomainId] = Some(value = domainManager1::1220b030210e...)

These parameters together can be used to define a connection configuration:

.. code-block:: none

    @ val config = DomainConnectionConfig(domain = "mydomain", sequencerConnection, manualConnect, domainId, priority)
    config : DomainConnectionConfig = DomainConnectionConfig(
      domain = Domain 'mydomain',
      sequencerConnection = GrpcSequencerConnection(
        endpoints = Seq(http://127.0.0.1:15057, http://127.0.0.1:15055),
        transportSecurity = false,
        customTrustCertificates = None()
      ),
      manualConnect = false,
      domainId = Some(domainManager1::1220b030210e...),
      priority = 10,
      initialRetryDelay = None(),
      maxRetryDelay = None()
    )

All other parameters are expert settings and should not be used. The ``config`` object can now be used to connect a
participant to a sequencer:

.. code-block:: none

    @ participant4.domains.register(config)
    

.. _connectivity_participant_inspect:

Inspect Connections
^^^^^^^^^^^^^^^^^^^

You can inspect the registered domain connections using:

.. code-block:: none

    @ participant2.domains.list_registered()
    res22: Seq[(DomainConnectionConfig, Boolean)] = Vector(
      (
        DomainConnectionConfig(
          domain = Domain 'mydomain',
          sequencerConnection = GrpcSequencerConnection(
            endpoints = https://127.0.0.1:15053,
            transportSecurity = true,
            customTrustCertificates = Some(2d2d2d2d2d42)
          ),
          manualConnect = false,
          domainId = None(),
          priority = 0,
          initialRetryDelay = None(),
          maxRetryDelay = None()
        ),
        true
      )
    )
    

You can also get the aliases of the currently connected domains using:

.. code-block:: none

    @ participant2.domains.list_connected()
    res23: Seq[ListConnectedDomainsResult] = Vector(
      ListConnectedDomainsResult(
        domainAlias = Domain 'mydomain',
        domainId = domainManager1::1220b030210e...,
        healthy = true
      )
    )
    

And you can inspect the configuration of a specific domain connection using:

.. code-block:: none

    @ participant2.domains.config("mydomain")
    res24: Option[DomainConnectionConfig] = Some(
      value = DomainConnectionConfig(
        domain = Domain 'mydomain',
        sequencerConnection = GrpcSequencerConnection(
          endpoints = https://127.0.0.1:15053,
          transportSecurity = true,
          customTrustCertificates = Some(2d2d2d2d2d42)
        ),
        manualConnect = false,
        domainId = None(),
        priority = 0,
        initialRetryDelay = None(),
        maxRetryDelay = None()
      )
    )

.. _connectivity_participant_modify:

Modify Connections
^^^^^^^^^^^^^^^^^^

Domain connection configurations can be updated using the ``modify`` function:

.. code-block:: none

    @ participant2.domains.modify("mydomain", _.copy(priority = 20))
    

The second argument is a mapping function which receives as input argument a ``DomainConnectionConfig``
and needs to return a ``DomainConnectionConfig``. Every case class has a default ``copy`` method that allows
overriding arguments.

Update a Custom TLS Trust Certificate
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In some cases (in particular in test environments), you might be using self-signed certificates
as a root of trust for the TLS sequencer connection. Whenever this root of trust changes, the clients
need to update the custom root certificate accordingly.

This can be done through the following steps. First, you need to load the certificate from a file:

.. code-block:: none

    @ val certificate = com.digitalasset.canton.util.BinaryFileUtil.tryReadByteStringFromFile("tls/root-ca.crt")
    certificate : com.google.protobuf.ByteString = <ByteString@cb6c133 size=1960 contents="-----BEGIN CERTIFICATE-----\nMIIFeTCCA2GgAwIBAgI...">

This step loads the root certificate from a file and stores it into a variable that can be used subsequently.
Next, you create a new connection object, passing in the certificate:

.. code-block:: none

    @ val connection = com.digitalasset.canton.sequencing.GrpcSequencerConnection.tryCreate(url, customTrustCertificates = Some(certificate))
    connection : com.digitalasset.canton.sequencing.GrpcSequencerConnection = GrpcSequencerConnection(
      endpoints = https://127.0.0.1:15053,
      transportSecurity = true,
      customTrustCertificates = Some(2d2d2d2d2d42)
    )

Finally, you update the sequencer connection settings on the participant node:

.. code-block:: none

    @ participant2.domains.modify("mydomain", _.copy(sequencerConnection=connection))
    

For mediators / domain managers, you can update the certificate accordingly.

.. _connectivity_participant_reconnect:

Enable and Disable Connections
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A participant can disconnect from a domain using:

    
.. code-block:: none

    @ participant2.domains.disconnect("mydomain")
    
    

Reconnecting to the domain can be done either on a per domain basis:

.. code-block:: none

    @ participant2.domains.reconnect("mydomain")
    res30: Boolean = true

Or for all registered domains that are not configured to require a manual connection:

.. code-block:: none

    @ participant2.domains.reconnect_all()
    


Mediator and Domain Manager
---------------------------

Both the mediator and the domain manager connect to the domain using sequencer connections. The sequencer connections
are configured when the nodes are initialized:

.. code-block:: none

    @ mediator1.mediator.help("initialize")
    initialize(domainId: com.digitalasset.canton.topology.DomainId, mediatorId: com.digitalasset.canton.topology.MediatorId, domainParameters: com.digitalasset.canton.admin.api.client.data.StaticDomainParameters, sequencerConnection: com.digitalasset.canton.sequencing.SequencerConnection, topologySnapshot: Option[com.digitalasset.canton.topology.store.StoredTopologyTransactions[com.digitalasset.canton.topology.transaction.TopologyChangeOp.Positive]], cryptoType: String): com.digitalasset.canton.crypto.PublicKey
    Initialize a mediator

The sequencer connection of a mediator and domain manager can be inspected using:

.. code-block:: none

    @ mediator1.sequencer_connection.get()
    res33: Option[com.digitalasset.canton.sequencing.SequencerConnection] = Some(
      value = GrpcSequencerConnection(
        endpoints = http://0.0.0.0:15057,
        transportSecurity = false,
        customTrustCertificates = None()
      )
    )

In some cases, the connection settings have to be updated. For this purpose, the two following functions can be used.
First, the connection information can just be set using:

.. code-block:: none

    @ mediator1.sequencer_connection.set(sequencer1.sequencerConnection)
    

It can also be amended using:

.. code-block:: none

    @ mediator1.sequencer_connection.modify(_.addConnection(sequencer2.sequencerConnection))
    
    

Please note that the connection changes immediately, without requiring a restart.