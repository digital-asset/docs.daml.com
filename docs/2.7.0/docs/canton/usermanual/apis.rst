..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _api_configuration:

API Configuration
=================
A domain node exposes two main APIs: the admin-api and the public-api, while the participant node
exposes the ledger-api and the admin-api. In this section, we will explain what the APIs do and how
they can be configured.

Default Ports
-------------

Canton assigns ports automatically for all the APIs of all the configured nodes if the port has not been configured explicitly.
The ports are allocated according to the following scheme:

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/scala/com/digitalasset/canton/config/ConfigDefaults.scala
   :language: scala
   :start-after: user-manual-entry-begin: ConfigDefaults
   :end-before: user-manual-entry-end: ConfigDefaults
   :dedent:

Administration API
------------------
The nature and scope of the admin api on participant and domain nodes has some overlap. As an example,
you will find the same key management commands on the domain and the participant node API, whereas
the participant has different commands to connect to several domains.

The configuration currently is simple (see the TLS example below) and just takes an address and a port.
The address defaults to ``127.0.0.1`` and a default port is assigned if not explicitly configured.

You should not expose the admin-api publicly in an unsecured way as it serves administrative purposes only.

.. _tls-configuration:

TLS Configuration
-----------------

Both, the Ledger API and the admin API provide the same TLS capabilities and can be configured using
the same configuration directives. TLS provides end-to-end channel encryption between the server and
client, and depending on the settings, server or mutual authentication. Ensure that the required TLS
system dependencies are installed, e.g., `libcrypt1` on Ubuntu.

A full configuration example is given by

.. literalinclude:: /canton/includes/mirrored/enterprise/integration-testing/src/main/resources/include/participant4.conf
   :start-after: architecture-handbook-entry-begin: ParticipantTLSApi
   :end-before: architecture-handbook-entry-end: ParticipantTLSApi

These TLS settings allow a connecting client to ensure that it is talking to the right server.
In this example, we have also enabled client authentication, which means that the client needs to
present a valid certificate (and have the corresponding private key). The certificate is valid if
it has been signed by a key in the trust store.

The ``trust-collection-file`` allows us to provide a file based trust store. If omitted, the system
will default to the built-in ``JVM`` trust store. The file must contain all client certificates
(or parent certificates which were used to sign the client certificate) who are trusted to use
the API. The format is just a collection of PEM certificates (in the right order or hierarchy), not a
java based trust store.

In order to operate the server just with server-side authentication, you can just omit the section
on ``client-auth``. However, if ``client-auth`` is set to ``require``, then Canton also requires a client certificate,
as various Canton internal processes will connect to the process itself through the API.

All the private keys need to be in the ``pkcs8`` PEM format.

By default, Canton only uses new versions of TLS and strong ciphers. You can also override
the default settings using the variables ``ciphers`` and ``protocols``. If you set these settings to ``null``,
the default JVM values will be used.

.. note::
    Error messages on TLS issues provided by the networking library ``netty`` are less than optimal.
    If you are struggling with setting up TLS, please enable ``DEBUG`` logging on the ``io.netty`` logger.

Note that the configuration hierarchy for a `remote participant console <https://docs.daml.com/__VERSION__/canton/scaladoc/com/digitalasset/canton/participant/config/RemoteParticipantConfig.html>`__ is slightly different
from the in-process console or participant shown above. For configuring a remote console with TLS, please see the `scaladocs for a TlsClientConfig <https://docs.daml.com/__VERSION__/canton/scaladoc/com/digitalasset/canton/config/TlsClientConfig.html>`__
(see also :ref:`how scaladocs relates to the configuration <configuration_reference>`).

If you need to create a set of testing TLS certificates, you can use the following openssl commands:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/gen-test-certs.sh
   :start-after: architecture-handbook-entry-begin: GenTestCerts
   :end-before: architecture-handbook-entry-end: GenTestCerts

If you are having problems with SSL connectivity, you can enable SSL debugging by adding the following
flag to the command line when starting Canton:

.. code-block:: bash

    bin/canton -Djavax.net.debug=all

This will enable detailed SSL debugging information to be printed to the console, which can help you diagnose
and troubleshoot any problems you may be experiencing. It is recommended to only enable this flag when needed,
as the output can be very verbose and may impact the performance of your application.

Keep Alive
----------
In order to prevent load-balancers or firewalls from terminating long running RPC calls in the event of some silence on the
connection, all gRPC connections enable keep-alive by default. An example configuration for an adjusted setting is given below:

.. literalinclude:: /canton/includes/mirrored/enterprise/integration-testing/src/main/resources/include/participant2.conf
   :start-after: architecture-handbook-entry-begin: KeepAliveSettings
   :end-before: architecture-handbook-entry-end: KeepAliveSettings

gRPC client connections are configured with ``keep-alive-client``, with two settings: ``time``, and ``timeout``.
The effect of the ``time`` and ``timeout`` settings are described in the `gRPC documentation <https://grpc.github.io/grpc-java/javadoc/io/grpc/ManagedChannelBuilder.html#keepAliveTime-long-java.util.concurrent.TimeUnit>`__.

Servers can additionally change another setting: ``permit-keep-alive-time``. This specifies the most aggressive keep-alive time
that a client is permitted to use. If a client uses keep-alive ``time`` that is more aggressive than the ``permit-keep-alive-time``, the connection will be terminated with a GOAWAY frame with "too_many_pings" as the debug data.
This setting is described in more detail in the `gRPC documentation <https://grpc.github.io/grpc-java/javadoc/io/grpc/netty/NettyServerBuilder.html#permitKeepAliveTime-long-java.util.concurrent.TimeUnit>`__
and `gRPC manual page <https://github.com/grpc/grpc/blob/master/doc/keepalive.md>`__.

Max Inbound Message Size
------------------------

The APIs exposed by both the participant (ledger API and admin API) as well as
by the domain (public API and admin API) have an upper limit on incoming message
size. To increase this limit to accommodate larger payloads, the flag
``max-inbound-message-size`` has to be set for the respective API to the maximum
message size in **bytes**.

For example, to configure a participant's ledger API limit to 20MB:

.. literalinclude:: /canton/includes/mirrored/enterprise/integration-testing/src/main/resources/include/participant2.conf
   :start-after: architecture-handbook-entry-begin: MaxInboundMessageSizeSetting
   :end-before: architecture-handbook-entry-end: MaxInboundMessageSizeSetting

Participant Configuration
-------------------------

Ledger API
~~~~~~~~~~
The configuration of the ledger API is similar to the admin API configuration, except that the
group starts with ``ledger-api`` instead of ``admin-api``.

.. _ledger-api-jwt-configuration:

JWT Authorization
^^^^^^^^^^^^^^^^^

The Ledger API supports `JWT <https://jwt.io/>`_ based authorization checks as described in the
:doc:`Authorization documentation </app-dev/authorization>`.

In order to enable JWT authorization checks, your safe configuration options are

.. literalinclude:: /canton/includes/mirrored/community/app/src/pack/examples/03-advanced-configuration/api/jwt/certificate.conf

- ``jwt-rs-256-crt``.
  The participant will expect all tokens to be signed with RS256 (RSA Signature with SHA-256) with the public key loaded from the given X.509 certificate file.
  Both PEM-encoded certificates (text files starting with ``-----BEGIN CERTIFICATE-----``)
  and DER-encoded certificates (binary files) are supported.

- ``jwt-es-256-crt``.
  The participant will expect all tokens to be signed with ES256 (ECDSA using P-256 and SHA-256) with the public key loaded from the given X.509 certificate file.
  Both PEM-encoded certificates (text files starting with ``-----BEGIN CERTIFICATE-----``)
  and DER-encoded certificates (binary files) are supported.

- ``jwt-es-512-crt``.
  The participant will expect all tokens to be signed with ES512 (ECDSA using P-521 and SHA-512) with the public key loaded from the given X.509 certificate file.
  Both PEM-encoded certificates (text files starting with ``-----BEGIN CERTIFICATE-----``)
  and DER-encoded certificates (binary files) are supported.

Instead of specifying the path to a certificate, you can also a
`JWKS <https://tools.ietf.org/html/rfc7517>`__ URL. In that case, the
participant will expect all tokens to be signed with RS256 (RSA Signature
with SHA-256) with the public key loaded from the given JWKS URL.

.. literalinclude:: /canton/includes/mirrored/community/app/src/pack/examples/03-advanced-configuration/api/jwt/jwks.conf

.. warning::

  For testing purposes only, you can also specify a shared secret. In
  that case, the participant will expect all tokens to be signed with
  HMAC256 with the given plaintext secret. This is not considered safe for production.

.. literalinclude:: /canton/includes/mirrored/community/app/src/pack/examples/03-advanced-configuration/api/jwt/unsafe-hmac256.conf

.. note:: To prevent man-in-the-middle attacks, it is highly recommended to use
          TLS with server authentication as described in :ref:`tls-configuration` for
          any request sent to the Ledger API in production.

Note that you can define multiple authorization plugins. If more than one is defined, the system will use the claim of the
first auth plugin that does not return Unauthorized.

If no authorization plugins are defined, a default (wildcard) authorization method is used. Under it, all valid ledger API requests are accepted without the system performing any request authorization.
To explicitly define the default authorization method, use the following configuration:

.. literalinclude:: /canton/includes/mirrored/community/app/src/pack/examples/03-advanced-configuration/api/wildcard.conf

Leeway Parameters for JWT Authorization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can define leeway parameters for authorization using JWT tokens.
An authorization which fails due to clock skew between the signing and the verification of the tokens can be eased by
specifying a leeway window in which the token should still be considered valid.
Leeway can be defined either specifically for the **Expiration Time ("exp")**, **Not Before ("nbf")** and
**Issued At ("iat")** claims of the token or by a default value for all three. The values defining the
leeway for each of the three specific fields override the default value if present. The leeway parameters should be
given in seconds and can be defined as in the example configuration below:

.. literalinclude:: /canton/includes/mirrored/community/app/src/pack/examples/03-advanced-configuration/api/jwt/leeway-parameters.conf

Configuring the Target Audience for JWT Authorization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The default audience (``aud`` field in the audience based token) for authenticating on the Ledger API using JWT is
``https://daml.com/participant/jwt/aud/participant/${participantId}``. Other audiences can be configured explicitly
using the custom target audience configuration option:

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/ledger-api-target-audience.conf


Domain Configurations
---------------------

.. _public-api-configuration:


Public API
~~~~~~~~~~
The domain configuration requires the same configuration of the ``admin-api`` as the participant.
Next to the ``admin-api``, we need to configure the ``public-api``, which is the api where
all participants connect.

Authentication Token
^^^^^^^^^^^^^^^^^^^^
Authentication of the restricted services is built into the public sequencer api, leveraging the
participant signing keys. You don't need to do anything in order to set this up; it is enforced
automatically and can't be turned off. The same mechanism is used to check the authentication of
the domain topology manager and the mediator.

The token is generated during the handshake between the node and the sequencer. By default, it is valid for one hour.
The nodes automatically renew the token in the background before it expires. The lifetime of the
tokens and of the nonce can be reconfigured using

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/auth-token-config.conf

However, we suggest keeping the default values.

TLS Encryption
^^^^^^^^^^^^^^
As with the admin-api, network traffic can (and should) be encrypted using TLS. This is particularly
crucial for the Public API.

An example configuration section which enables TLS encryption and server-side TLS authentication is given by

.. literalinclude:: /canton/includes/mirrored/enterprise/integration-testing/src/main/resources/include/domain2.conf
   :start-after: architecture-handbook-entry-begin: DomainPublicApi
   :end-before: architecture-handbook-entry-end: DomainPublicApi

If TLS is used on the server side with a self-signed certificate, we need to pass the
certificate chain during the connect call of the participant. Otherwise, the default root
certificates of the Java runtime will be used. An example would be:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/MultiDomainIntegrationTests.scala
   :start-after: architecture-handbook-entry-begin: TlsConnect
   :end-before: architecture-handbook-entry-end: TlsConnect
   :dedent:

Usage of native libraries by Netty
----------------------------------

Canton ships with native libraries (for some processor architectures: x86_64, ARM64, S390_64) so that the Netty network access library
can take advantage of ``epoll`` on Linux, generally leading to improved performance and less pressure on the JVM garbage collector.
The available native is picked up automatically and it falls back to the standard NIO library if running on unsupported operating systems
or architectures.

Furthermore, the usage of the native library can also be switched off by setting the following:
`-Dio.netty.transport.noNative=true`.
Even when this is expected, falling back to NIO might lead to a warning being emitted at `DEBUG` level on your log.
