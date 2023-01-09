..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _api_configuration:

Api Configuration
=================
A domain node exposes two main APIs: the admin-api and the public-api, while the participant node
exposes the ledger-api and the admin-api. In this section, we will explain what the APIs do and how
they can be configured. All APIs are based on `GRPC <https://grpc.io/>`_, which is an efficient RPC
and streaming protocol with client support in almost all relevant programming languages. Native
bindings can be built using the :ref:`API definitions <administration_apis>`.

Default Ports
-------------

Canton assigns ports automatically for all the APIs of all the configured nodes if the port has not been configured explicitly.
The ports are allocated according to the following scheme:

.. code-block:: scala

      /** Participant node default ports */
      val ledgerApiPort = defaultPortStart(4001)
      val participantAdminApiPort = defaultPortStart(4002)
    
      /** Domain node default ports */
      val domainPublicApiPort = defaultPortStart(4201)
      val domainAdminApiPort = defaultPortStart(4202)
    
      /** External sequencer node default ports (enterprise-only) */
      val sequencerPublicApiPort = defaultPortStart(4401)
      val sequencerAdminApiPort = defaultPortStart(4402)
    
      /** External mediator node default port (enterprise-only) */
      val mediatorAdminApiPort = defaultPortStart(4602)
    
      /** Domain node default ports */
      val domainManagerAdminApiPort = defaultPortStart(4801)
    
      /** Increase the default port number for each new instance by portStep */
      private val portStep = 10


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
client, and depending on the settings, server or mutual authentication.

A full configuration example is given by

.. code-block:: none

    canton.participants.participant4.ledger-api {
      address = "127.0.0.1" // IP / DNS must be SAN of certificate to allow local connections from the canton process
      port = 5041
      tls {
        // the certificate to be used by the server
        cert-chain-file = "./tls/participant.crt"
        // private key of the server
        private-key-file = "./tls/participant.pem"
        // trust collection, which means that all client certificates will be verified using the trusted
        // certificates in this store. if omitted, the JVM default trust store is used.
        trust-collection-file = "./tls/root-ca.crt"
        // define whether clients need to authenticate as well (default not)
        client-auth = {
          // none, optional and require are supported
          type = require
          // If clients are required to authenticate as well, we need to provide a client
          // certificate and the key, as Canton has internal processes that need to connect to these
          // APIs. If the server certificate is trusted by the trust-collection, then you can
          // just use the server certificates. Otherwise, you need to create separate ones.
          admin-client {
            cert-chain-file = "./tls/admin-client.crt"
            private-key-file = "./tls/admin-client.pem"
          }
        }
        // minimum-server-protocol-version = ...
        // ciphers = ...
      }
    }
    


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

Note that the configuration hierarchy for a `remote participant console <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/participant/config/RemoteParticipantConfig.html>`__ is slightly different
from the in-process console or participant shown above. For configuring a remote console with TLS, please see the `scaladocs for a TlsClientConfig <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/config/TlsClientConfig.html>`__
(see also :ref:`how scaladocs relates to the configuration <configuration_reference>`).

If you need to create a set of testing TLS certificates, you can use the following openssl commands:

.. code-block:: none

    DAYS=3650
    
    function create_key {
      local name=$1
      openssl genrsa -out "${name}.key" 4096
      # netty requires the keys in pkcs8 format, therefore convert them appropriately
      openssl pkcs8 -topk8 -nocrypt -in "${name}.key" -out "${name}.pem"
    }
    
    # create self signed certificate
    function create_certificate {
      local name=$1
      local subj=$2
      openssl req -new -x509 -sha256 -key "${name}.key" \
                  -out "${name}.crt" -days ${DAYS} -subj "$subj"
    }
    
    # create certificate signing request with subject and SAN
    # we need the SANs as our certificates also need to include localhost or the
    # loopback IP for the console access to the admin-api and the ledger-api
    function create_csr {
      local name=$1
      local subj=$2
      local san=$3
      (
        echo "authorityKeyIdentifier=keyid,issuer"
        echo "basicConstraints=CA:FALSE"
        echo "keyUsage = digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment"
      ) > ${name}.ext
      if [[ -n $san ]]; then
        echo "subjectAltName=${san}" >> ${name}.ext
      fi
      # create certificate (but ensure that localhost is there as SAN as otherwise, admin local connections won't work)
      openssl req -new -sha256 -key "${name}.key" -out "${name}.csr" -subj "$subj"
    }
    
    function sign_csr {
      local name=$1
      local sign=$2
      openssl x509 -req -sha256 -in "${name}.csr" -extfile "${name}.ext" -CA "${sign}.crt" -CAkey "${sign}.key" -CAcreateserial  \
                   -out "${name}.crt" -days ${DAYS}
      rm "${name}.ext" "${name}.csr"
    }
    
    function print_certificate {
      local name=$1
      openssl x509 -in "${name}.crt" -text -noout
    }
    
    # create root certificate
    create_key "root-ca"
    create_certificate "root-ca" "/O=TESTING/OU=ROOT CA/emailAddress=canton@digitalasset.com"
    #print_certificate "root-ca"
    
    # create domain certificate
    create_key "domain"
    create_csr "domain" "/O=TESTING/OU=DOMAIN/CN=localhost/emailAddress=canton@digitalasset.com" "DNS:localhost,IP:127.0.0.1"
    sign_csr "domain" "root-ca"
    print_certificate "domain"
    
    # create participant certificate
    create_key "participant"
    create_csr "participant" "/O=TESTING/OU=PARTICIPANT/CN=localhost/emailAddress=canton@digitalasset.com" "DNS:localhost,IP:127.0.0.1"
    sign_csr "participant" "root-ca"
    
    # create participant client key and certificate
    create_key "admin-client"
    create_csr "admin-client" "/O=TESTING/OU=ADMIN CLIENT/CN=localhost/emailAddress=canton@digitalasset.com"
    sign_csr "admin-client" "root-ca"
    print_certificate "admin-client"
    


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
connection, all GRPC connections enable keep-alive by default. An example configuration for an adjusted setting is given below:

.. code-block:: none

    canton.participants.participant2 {
      admin-api 	{
        address = "127.0.0.1"
        port = 5022
        keep-alive-server {
          time = 40s
          timeout = 20s
          permit-keep-alive-time = 20s
        }
      }
      sequencer-client {
        keep-alive-client {
          time = 60s
          timeout = 30s
        }
      }
    }


GRPC client connections are configured with ``keep-alive-client``, with two settings: ``time``, and ``timeout``.
The effect of the ``time`` and ``timeout`` settings are described in the `GRPC documentation <https://grpc.github.io/grpc-java/javadoc/io/grpc/ManagedChannelBuilder.html#keepAliveTime-long-java.util.concurrent.TimeUnit>`__.

Servers can additionally change another setting: ``permit-keep-alive-time``. This specifies the most aggressive keep-alive time
that a client is permitted to use. If a client uses keep-alive ``time`` that is more aggressive than the ``permit-keep-alive-time``, the connection will be terminated with a GOAWAY frame with "too_many_pings" as the debug data.
This setting is described in more detail in the `GRPC documentation <https://grpc.github.io/grpc-java/javadoc/io/grpc/netty/NettyServerBuilder.html#permitKeepAliveTime-long-java.util.concurrent.TimeUnit>`__
and `GRPC manual page <https://github.com/grpc/grpc/blob/master/doc/keepalive.md>`__.

Max Inbound Message Size
------------------------

The APIs exposed by both the participant (ledger API and admin API) as well as
by the domain (public API and admin API) have an upper limit on incoming message
size. To increase this limit to accommodate larger payloads, the flag
``max-inbound-message-size`` has to be set for the respective API to the maximum
message size in **bytes**.

For example, to configure a participant's ledger API limit to 20MB:

.. code-block:: none

    canton.participants.participant2.ledger-api {
      address = "127.0.0.1"
      port = 5021
      max-inbound-message-size = 20971520
    }


Participant Configuration
-------------------------

Ledger Api
~~~~~~~~~~
The configuration of the ledger API is similar to the admin API configuration, except that the
group starts with ``ledger-api`` instead of ``admin-api``.

.. _ledger-api-jwt-configuration:

JWT Authorization
^^^^^^^^^^^^^^^^^

The Ledger Api supports `JWT <https://jwt.io/>`_ based authorization checks. Please consult the
`Daml SDK manual <https://docs.daml.com/tools/sandbox.html#sandbox-authorization>`_
to understand the various configuration options and their security aspects. Canton exposes precisely the same
JWT authorization options as explained therein.

In order to enable JWT authorization checks, your safe configuration options are

.. code-block:: none

    _shared {
      ledger-api {
        auth-services = [{
          // type can be
          //   jwt-rs-256-crt
          //   jwt-es-256-crt
          //   jwt-es-512-crt
          type = jwt-rs-256-crt
          // we need a certificate file (abcd.cert)
          certificate = ${JWT_CERTIFICATE_FILE}
        }]
      }
    }


.. code-block:: none

    _shared {
      ledger-api {
        auth-services = [{
          type = jwt-rs-256-jwks
          // we need a URL to a jwks key, e.g. https://path.to/jwks.key
          url = ${JWT_URL}
        }]
      }
    }


while there is also unsafe ``HMAC256`` based support, which can be enabled using

.. code-block:: none

    _shared {
      ledger-api {
        auth-services = [{
          type = unsafe-jwt-hmac-256
          secret = "not-safe-for-production"
        }]
      }
    }


Note that you can define multiple authorization plugins. If more than one is defined, the system will use the claim of the
first auth plugin that does not return Unauthorized.

Leeway Parameters for JWT Authorization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can define leeway parameters for authorization using JWT tokens.
An authorization which fails due to clock skew between the signing and the verification of the tokens can be eased by
specifying a leeway window in which the token should still be considered valid.
Leeway can be defined either specifically for the **Expiration Time ("exp")**, **Not Before ("nbf")** and
**Issued At ("iat")** claims of the token or by a default value for all three. The values defining the
leeway for each of the three specific fields override the default value if present. The leeway parameters should be
given in seconds and can be defined as in the example configuration below:

.. code-block:: none

    _shared {
      parameters.ledger-api-server-parameters.jwt-timestamp-leeway {
        default = 5
        expires-at = 10
        issued-at = 15
        not-before = 20
      }
    }


Limiting concurrent GRPC requests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

(Preview feature) The Ledger Api server limits the number of parallel requests accepted on the Api based on
system resource usage. We recommend to keep the default values. However, they can be changed using the following
configuration options:

.. code-block:: none

    // re-configure the default rate limit values
    canton.participants.participant1.ledger-api.rate-limit = {
        max-api-services-queue-size = 20000
        max-streams = 1000
        // These settings are highly sensitive to the operating environment and should
        // only be configured where memory profiling has highlighted spikes in memory
        // usage that need to be flattened
        max-used-heap-space-percentage = 100
        min-free-heap-space-bytes = 0
    }
    // turn off rate limits for participant2
    canton.participants.participant2.ledger-api.rate-limit = null

Turning the rate limits off can be achieved by setting them to ``null``.

Domain Configurations
---------------------

.. _public-api-configuration:


Public Api
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

.. code-block:: none

    canton.domains.mydomain.public-api {
        token-expiration-time = 60m
        nonce-expiration-time = 1m
    }

However, we suggest keeping the default values.

TLS Encryption
^^^^^^^^^^^^^^
As with the admin-api, network traffic can (and should) be encrypted using TLS. This is particularly
crucial for the Public API.

An example configuration section which enables TLS encryption and server-side TLS authentication is given by

.. code-block:: none

    canton.domains.acme.public-api {
      port = 5028
      address = localhost // defaults to 127.0.0.1
      tls {
        cert-chain-file = "./tls/domain.crt"
        private-key-file = "./tls/domain.pem"
        // minimum-server-protocol-version = TLSv1.3, optional argument
        // ciphers = null // use null to default to JVM ciphers
      }
    }


If TLS is used on the server side with a self-signed certificate, we need to pass the
certificate chain during the connect call of the participant. Otherwise, the default root
certificates of the Java runtime will be used. An example would be:

.. code-block:: none

        participant3.domains.connect(
          domainAlias = "acme",
          connection = s"https://$hostname:$port",
          certificatesPath = certs, // path to certificate chain file (.pem) of server
        )


Limiting concurrent GRPC requests (preview feature)
---------------------------------------------------

In large-scale deployments a Canton node may get more GRPC requests than it can cope with, leading to requests timing
out. Canton has an experimental integration with `concurrency-limits <https://github.com/Netflix/concurrency-limits>`_
to limit the number of concurrent requests and prevent nodes from becoming overloaded.

Canton's GRPC services can be configured to use various options provided by the concurrency-limits library:

* A fixed limit on concurrent requests

.. code-block:: none

    canton.participants.participant1.admin-api.concurrency-limit {
        type = "fixed-limit"
        limit = "10"
    }


* A dynamic limit for the number of concurrent requests, inspired by TCP Vegas

.. code-block:: none

    canton.participants.participant1.admin-api.concurrency-limit {
        # Values are defaults from https://github.com/Netflix/concurrency-limits
        type = "vegas-limit"
        max-concurrency = 1000
        smoothing = 1.0
    }


* A gradient-based algorithm to dynamically infer the concurrency limit

.. code-block:: none

    canton.participants.participant1.admin-api.concurrency-limit {
        # Values are defaults from https://github.com/Netflix/concurrency-limits
        type = "gradient-2-limit"
        max-concurrency = 200
        smoothing = 0.2
        rtt-tolerance = 1.5
    }


* Any of these options, with an added smoothing window

.. code-block:: none

    canton.participants.participant1.admin-api.concurrency-limit {
        # Values are defaults from https://github.com/Netflix/concurrency-limits
        type = "windowed-limit"
        window-size = 10
        delegate = {
            type = gradient-2-limit
            max-concurrency = 200
            smoothing = 0.2
            rtt-tolerance = 1.5
        }
    }


See the `concurrency-limits <https://github.com/Netflix/concurrency-limits>`_ library for more information on these
different options.
