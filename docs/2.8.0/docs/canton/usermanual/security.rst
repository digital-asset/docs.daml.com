..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _canton-security:

Security
========

Cryptographic Key Usage
-----------------------

This section covers the generation and usage of cryptographic keys in the Canton
nodes. It assumes that the configuration sets `auto-init = true` which leads to the
generation of the default keys on a node's startup.

The scope of cryptographic keys covers all Canton-protocol specific keys,
private keys for TLS, as well as additional keys required for the domain
integrations, e.g., with Besu.

Supported Cryptographic Schemes in Canton
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Within Canton we use the cryptographic primitives of signing, symmetric and
asymmetric encryption, and MAC with the following supported schemes (`D` = `default`, `S` = `supported`,
`P` = `partially supported` for instance just signature verification but no signing with a private key,
and `/` = `not supported`):

.. _canton_supported_keys:

+--------------------------------------------------------+------------+-----------+----------+
| **Crypto Provider**                                    |    Tink    |    JCE    |    KMS   |
+========================================================+============+===========+==========+
| **Signing**                                                                                |
+--------------------------------------------------------+------------+-----------+----------+
| Ed25519                                                |      D     |     D     |     P    |
+--------------------------------------------------------+------------+-----------+----------+
| ECDSA P-256                                            |      S     |     S     |     D    |
+--------------------------------------------------------+------------+-----------+----------+
| ECDSA P-384                                            |      S     |     S     |     S    |
+--------------------------------------------------------+------------+-----------+----------+
| **Symmetric Encryption**                                                                   |
+--------------------------------------------------------+------------+-----------+----------+
| AES128-GCM                                             |      D     |     D     |     D    |
+--------------------------------------------------------+------------+-----------+----------+
| **Asymmetric Encryption**                                                                  |
+--------------------------------------------------------+------------+-----------+----------+
| ECIES on P-256 with HMAC-SHA256 and AES128-GCM         |      D     |     D     |     /    |
+--------------------------------------------------------+------------+-----------+----------+
| ECIES on P-256 with HMAC-SHA256 and AES128-CBC         |      /     |     S     |     /    |
+--------------------------------------------------------+------------+-----------+----------+
| RSA 2048 with OAEP using SHA-256                       |      /     |     S     |     D    |
+--------------------------------------------------------+------------+-----------+----------+
| **MAC**                                                                                    |
+--------------------------------------------------------+------------+-----------+----------+
| HMAC with SHA-256                                      |      D     |     D     |     D    |
+--------------------------------------------------------+------------+-----------+----------+

Key Generation and Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~

Keys can either be generated in the node and stored in the node's primary storage or generated and stored by
an external key management system (KMS).
We currently support a version of Canton that can use a KMS to either:
:ref:`(a) protect Canton's private keys at rest <encrypted_private_key_storage>`
or :ref:`(b) generate and store the private keys itself <external_key_storage>`.
This version is available only as part of Daml Enterprise.

You can find more background information on this key management feature in
:ref:`Secure Cryptographic Private Key Storage <kms_architecture>`.

The following section :ref:`Key Management Service Setup <kms_setup>` describes how to configure KMS for Canton.

Public Key Distribution using Topology Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The public keys of the corresponding key pairs that are used for signing and
asymmetric encryption within Canton are distributed using Canton's Topology
Management. Specifically, signing and asymmetric encryption public keys are
distributed using `OwnerToKeyMapping` transactions, which associate a node with
a public key for either signing or encryption, and `NamespaceDelegation` for
namespace signing public keys.

See :ref:`Topology Transactions <topology_transactions>` for details on the specific
topology transactions in use.

Common Node Keys
~~~~~~~~~~~~~~~~

Each node provides an Admin API for administrative purposes, which is secured
using TLS.

The node reads the private key for the TLS server certificate from a file at startup.

Participant Node Keys
~~~~~~~~~~~~~~~~~~~~~

Participant Namespace Signing Key
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A Canton participant node spans its own identity namespace, for instance for its
own id and the Daml parties allocated on the participant node. The namespace is
the hash of the public key of the participant namespace signing key.

The private key is used to sign and thereby authorize all topology transactions
for this namespace and this participant, including the following transactions:

- Root `NamespaceDelegation` for the new identity namespace of the participant
- `OwnerToKeyMapping` for all the public keys that the participant will generate
  and use (these keys will be explained in the follow-up sections)
- `PartyToParticipant` for the parties allocated on this participant
- `VettedPackages` for the packages that have been vetted by this participant

Signing Key
^^^^^^^^^^^

In addition to the topology signing key, a participant node will generate
another signing key pair that is used for the Canton transaction protocol in the
following cases:

- Sequencer Authentication: Signing the nonce generated by the sequencer as
  part of its challenge-response authentication protocol. The sequencer verifies
  the signature with the public key registered for the member in the topology
  state.
- Transaction Protocol
  - The Merkle tree root hash of confirmation requests is signed for a top-level view.
  - The confirmation responses sent to the mediator are signed as a whole.
  - The Merkle tree root hash of transfer-in and transfer-out messages is signed.
- Pruning: Signing of ACS commitments.

Participant Encryption Key
^^^^^^^^^^^^^^^^^^^^^^^^^^

In addition to a signing key pair, a participant node also generates a key pair
for encryption based on an asymmetric encryption scheme. A transaction payload is
encrypted for a recipient based on the recipient's public encryption key that is
part of the topology state.

See the next section on how a transaction is encrypted using an ephemeral
symmetric key.

View Encryption Key
^^^^^^^^^^^^^^^^^^^

A transaction is composed of multiple views due to sub-transaction privacy.
Instead of duplicating each view by directly encrypting the view for each
recipient using their participant encryption public key, Canton derives a
symmetric key for each view to encrypt that view. The key is derived using a
HKDF from a secure seed that is only stored encrypted under the public
encryption key of a participants. Thereby, only the encrypted seed is duplicated
but not a view.

Ledger API TLS Key
^^^^^^^^^^^^^^^^^^

The private key for the TLS server certificate is provided as a file, which can
optionally be encrypted and the symmetric decryption key is fetched from a given
URL.

Domain Topology Manager Keys
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Domain Namespace Signing Key
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The domain topology manager governs the namespace of the domain and has a
signing key pair for the namespace. The hash of the public key forms the
namespace and all entities in the domain (mediator, sequencer, the topology
manager itself) may have identities under the domain namespace.

The domain topology manager signs and thereby authorizes the following topology
transactions:

- `NamespaceDelegation` to register the namespace public key for the new namespace
- `OwnerToKeyMapping` to register both its own signing public key (see next
  section) and the signing public keys of the other domain entities as part of
  the domain onboarding
- `ParticipantState` to enable a new participant on the domain
- `MediatorDomainState` to enable a new mediator on the domain

Signing Key
^^^^^^^^^^^

The domain topology manager is not part of the Canton transaction protocol, but
it receives topology transactions via the sequencer. Therefore, in addition to
the domain namespace, the domain topology manager has a signing key pair, which
is registered in the topology state for the topology manager. This signing key
is used to perform the challenge-response protocol of the sequencer.

Sequencer Node Keys
~~~~~~~~~~~~~~~~~~~

Signing Key
^^^^^^^^^^^

The sequencer has a signing key pair that is used to sign all events the
sequencer sends to a subscriber.

Ethereum Sequencer
^^^^^^^^^^^^^^^^^^

The Ethereum-based sequencer is a client of a Besu node and additional keys are
used in this deployment:

- TLS client certificate and private key to authenticate towards a Besu node if
  mutual authentication is configured.
- A Wallet (in BIP-39 or UTC / JSON format), which contains or will result in a
  signing key pair for Ethereum transactions.

Fabric Sequencer
^^^^^^^^^^^^^^^^

The Fabric-based sequencer is a Fabric application connecting to an
organization's peer node and the following additional keys are required:

- TLS client certificate and private key to authenticate towards a Fabric peer
  node if mutual authentication is required.
- The client identity's certificate and private key.

Public API TLS Key
^^^^^^^^^^^^^^^^^^

The private key for the TLS server certificate is provided as a file.

Mediator Node Keys
~~~~~~~~~~~~~~~~~~

Signing Key
^^^^^^^^^^^

The mediator node is part of the Canton transaction protocol and uses a signing
key pair for the following:

- Sequencer Authentication: Signing of the challenge as part of the
  sequencer challenge-response protocol.
- Signing of transaction results, transfer results, and rejections of malformed
  mediator requests.

Domain Node Keys
~~~~~~~~~~~~~~~~

The domain node embeds a sequencer, mediator, and domain topology manager. The
set of keys remains the same as for the individual nodes.

Canton Console Keys
~~~~~~~~~~~~~~~~~~~

When the Canton console runs separate from the node and mutual authentication is
configured on the Admin API, then the console requires a TLS client certificate
and corresponding private key as a file.

Cryptographic Key Management
----------------------------

.. _rotating-canton-keys:

Rotating Canton Node Keys
~~~~~~~~~~~~~~~~~~~~~~~~~

Canton supports rotation of node keys (signing and encryption) during live
operation through its topology management. In order to ensure continuous
operation, the new key is added first and then the previous key is removed.

For participant nodes, domain nodes, and domain topology managers, the
nodes can rotate their keys directly using their own identity manager with
the following command for example:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/KeyManagementIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: RotateNodeKeys
   :end-before: user-manual-entry-end: RotateNodeKeys
   :dedent:

On a participant node both the signing and encryption key pairs are rotated. On a domain and domain manager node only
the signing key pair, because they do not have a encryption key pair. Identity namespace root or intermediate keys are
not rotated with this command, see below for commands on namespace key management.

For sequencer and mediator nodes that are part of a domain, the domain topology
manager authorizes the key rotation and a reference needs to be passed in to the command, for example:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/KeyManagementIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: RotateNodeKeys2
   :end-before: user-manual-entry-end: RotateNodeKeys2
   :dedent:

We can also individually rotate a key by running the following command for example:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/KeyManagementIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: RotateNodeKey
   :end-before: user-manual-entry-end: RotateNodeKey
   :dedent:

A fingerprint of a key can be retrieved from the list of public keys:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/KeyManagementIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: ListPublicKeys
   :end-before: user-manual-entry-end: ListPublicKeys
   :dedent:

Namespace Intermediate Key Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Relying on the namespace root key to authorize topology transactions
for the namespace is problematic because we cannot rotate the root key without
losing the namespace. Instead we can create intermediate keys for the
namespace, similar to an intermediate certificate authority, in the following way:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/KeyManagementIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: CreateNamespaceIntermediateKey
   :end-before: architecture-handbook-entry-end: CreateNamespaceIntermediateKey
   :dedent:

We can rotate an intermediate key by creating a new one and renewing the existing
topology transactions that have been authorized with the previous intermediate
key. First the new intermediate key has to be created in the same way as the
initial intermediate key. To rotate the intermediate key and renew existing
topology transactions:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/KeyManagementIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RotateNamespaceIntermediateKey
   :end-before: architecture-handbook-entry-end: RotateNamespaceIntermediateKey
   :dedent:

Moving the Namespace Secret Key to Offline Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An identity is ultimately bound to a particular secret key. Owning that secret key gives full authority over the entire
namespace. From a security standpoint, it is therefore critical to keep the namespace secret key confidential. This can
be achieved by moving the key off the node for offline storage. The identity management system can still be used by
creating a new key and an appropriate intermediate certificate. The following steps illustrate how:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/CryptoIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: ExportKeyForOfflineStorage
   :end-before: architecture-handbook-entry-end: ExportKeyForOfflineStorage
   :dedent:

When the root namespace key is required, it can be imported again on the original node or
on another, using the following steps:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/CryptoIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: ImportFromOfflineStorage
   :end-before: architecture-handbook-entry-end: ImportFromOfflineStorage
   :dedent:

Identifier Delegation Key Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Identifier delegations work similar to namespace delegations, however a key is
only allowed to operate on a specific identity and not an entire namespace (cf.
:ref:`Topology Transactions <topology_transactions>`).

Therefore the key management for identifier delegations also works the same way
as for namespace delegations, where all the topology transactions authorized by
the previous identifier delegation key have to be renewed.

Key Management Service Setup
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. enterprise-only::

Canton supports using a Key Management Service (KMS) to increase security of
stored private keys. There are currently **two independent ways** to use this service:

- :ref:`Encrypted Private Key Storage <encrypted_private_key_storage>`
- :ref:`External Key Storage and Usage <external_key_storage>`

The KMS integration is currently enabled for `Amazon Web Services (AWS)
KMS` and `Google Cloud Provider (GCP) KMS` in Canton Enterprise.

.. _kms_config:

Canton Configuration of a KMS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Like other Canton capabilities, KMS integration is enabled within a Canton
node's configuration file. A KMS for AWS or GCP is configured in the following way:

- ``type`` specifies which KMS to use.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: AwsKmsConfig
   :end-before: user-manual-entry-end: AwsKmsConfig

Specific to AWS:

- ``region`` specifies which region the AWS KMS is bound to.
- ``multi-region-key`` flag enables the replication of keys generated by the KMS. With replication turned on, the operator can replicate a key from one region to another (Note: replication of a key is not done automatically by Canton) and change the region configured in Canton at a later point in time without any other key rotation required. **The standard single-region approach is applicable for most scenarios**.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: GcpKmsConfig
   :end-before: user-manual-entry-end: GcpKmsConfig

Specific to GCP:

- ``location-id`` specifies which region the GCP KMS is bound to.
- ``project-id`` specifies which project are we binding to.
- ``keyRingId`` specifies the keyring to use. Contrary to AWS, multi region keys are enabled for an entire keyring. Therefore, the KMS operator is responsible for setting the keyring correctly depending on the systems' needs.

Configure AWS Credentials and Permissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Depending on how the KMS is intended to be used, it will require different permission settings. More details are provided
for the two different setups: :ref:`(a) encrypted private store permissions <external_key_storage_permissions>`,
:ref:`(b) external storage and usage permissions <encrypted_private_key_storage_permissions>`.

To make the API calls to the AWS KMS, Canton uses the `standard AWS credential access
<https://docs.aws.amazon.com/general/latest/gr/aws-sec-cred-types.html>`_. For example, the standard
environment variables of `AWS_ACCESS_KEY_ID` and `AWS_SECRET_ACCESS_KEY` can
be used. Alternatively, you can specify an AWS profile file (e.g. use a temporary access
profile credentials - `sts`).

For GCP, Canton uses a `GCP service account
<https://cloud.google.com/docs/authentication/provide-credentials-adc#local-user-cred>`_. For example,
the standard environment variable `GOOGLE_APPLICATION_CREDENTIALS` can be used after
setting up a local Application Default Credentials (ADC) file for our service account.

The protection and rotation of
the credentials for AWS or GCP are the responsibility of the node operator.

Auditability
^^^^^^^^^^^^

AWS and GCP provide tools to monitor KMS keys. For AWS to set automatic external logging, refer to the
`AWS official documentation <https://docs.aws.amazon.com/kms/latest/developerguide/monitoring-overview.html>`_.
This includes instructions on how to set AWS Cloud Trail or Cloud Watch Alarms
to keep track of usage of KMS keys or of performed crypto operations.
For GCP you can refer to the `GCP official documentation
<https://cloud.google.com/kms/docs/audit-logging>`_ for information on logging.
Errors resulting from the use of KMS keys are logged in Canton.

Logging
^^^^^^^

For further auditability, Canton can be configured to log every call made to the AWS KMS.
To enable this feature, set the ``audit-logging`` field of the KMS configuration to ``true``.
By default, when using a file-based logging configuration, such logs will be written into the main canton log file.
To write them to a dedicated log file, set the ``KMS_LOG_FILE_NAME`` environment variable or ``--kms-log-file-name`` CLI
flag to the path of the file.
These and other parameters can be configured using environment variables or CLI flags:

.. list-table:: KMS logging configuration
   :widths: 20 20 40 20
   :header-rows: 1

   * - Environment variable
     - CLI Flag
     - Purpose
     - Default
   * - KMS_LOG_FILE_NAME
     - --kms-log-file-name
     - Path to a dedicated KMS log file
     - not set
   * - KMS_LOG_IMMEDIATE_FLUSH
     - --kms-log-immediate-flush
     - When true, logs will be immediately flushed to the KMS log file
     - true
   * - KMS_LOG_FILE_ROLLING_PATTERN
     - --kms-log-file-rolling-pattern
     - Pattern to use when using the rolling file strategy to roll KMS log files
     - yyyy-MM-dd
   * - KMS_LOG_FILE_HISTORY
     - --kms-log-file-history
     - Maximum number of KMS log files to keep when using the rolling file strategy
     - 0 (i.e. no limit)

Sample of an AWS KMS audit log:

.. code-block:: none

    2023-09-12 15:44:54,426 [env-execution-context-27] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Sending request [06cc259e220da647]: DecryptRequest(CiphertextBlob=** Ciphertext placeholder **, KeyId=91c48ce4-ec80-44c1-a219-fdd07f12f002, EncryptionAlgorithm=RSAES_OAEP_SHA_256) to https://kms.us-east-1.amazonaws.com/
    2023-09-12 15:44:54,538 [aws-java-sdk-NettyEventLoop-1-15] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Received response [06cc259e220da647]: [Aws-Id: 1836823c-bb8a-44bf-883d-f33d696bf84f] - DecryptResponse(Plaintext=** Redacted plaintext placeholder **, KeyId=arn:aws:kms:us-east-1:724647588434:key/91c48ce4-ec80-44c1-a219-fdd07f12f002, EncryptionAlgorithm=RSAES_OAEP_SHA_256)
    2023-09-12 15:44:54,441 [env-execution-context-138] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Sending request [e28450df3a98ea23]: SignRequest(KeyId=f23b5b37-b4e8-494d-b2bc-1fca12308c99, Message=** Sign message text placeholder **, MessageType=RAW, SigningAlgorithm=ECDSA_SHA_256) to https://kms.us-east-1.amazonaws.com/
    2023-09-12 15:44:54,554 [aws-java-sdk-NettyEventLoop-1-2] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Received response [e28450df3a98ea23]: [Aws-Id: 7085bcf3-1a36-4048-a38b-014b441afa11] - SignResponse(KeyId=arn:aws:kms:us-east-1:724647588434:key/f23b5b37-b4e8-494d-b2bc-1fca12308c99, Signature=** Signature message text placeholder **, SigningAlgorithm=ECDSA_SHA_256)

Note that sensitive data is removed before logging.
The general log format is as follows:

``tid:<canton_trace_id> - Sending request [<canton_kms_request_id>]: <request details>``
``tid:<canton_trace_id> - Received response [<canton_kms_request_id>]: [Aws-Id: <aws_request_id>] - <response details>``

Ledger-API Authorization
------------------------

The Ledger API provides :ref:`authorization support <ledger-api-jwt-configuration>` using `JWT <https://jwt.io>`_
tokens. While the JWT token authorization allows third party applications to be authorized properly, it poses some issues
for Canton internal services such as the `PingService` or the `DarService`, which are used to manage domain wide
concerns. Therefore Canton generates a new admin bearer token (64 bytes, randomly generated, hex-encoded) on each startup,
which is communicated to these services internally and used by these services to
authorize themselves on the Ledger API. The admin token allows to act as any party registered on that participant node.

The admin token is only used within the same process. Therefore, in order to obtain this token, an attacker needs to be
able to either dump the memory or capture the network traffic, which typically only a privileged user can do.

It is important to enable TLS together with JWT support in general, as otherwise tokens can be leaked to an attacker
that has the ability to inspect network traffic.
