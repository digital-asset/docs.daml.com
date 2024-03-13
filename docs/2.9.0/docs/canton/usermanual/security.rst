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

The scope of cryptographic keys covers all Canton-protocol-specific keys,
private keys for TLS, as well as additional keys required for the sync domain
integrations, e.g., with Besu.

Supported Cryptographic Schemes in Canton
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Within Canton we use the cryptographic primitives of signing, symmetric and
asymmetric encryption, and MAC with the following supported schemes:

.. _canton_supported_keys:

.. table:: **Supported Cryptographic Schemes** - (**D =** default, **S =** supported, **P =** partially supported, for instance just signature verification but no signing with a private key, and **/ =** not supported. Inside the brackets **[<scheme>]** are the values to use when configuring Canton)

    +--------------------------------------------------------+------------+-----------+----------+
    | **Crypto Provider**                                    |    Tink    |    JCE    |    KMS   |
    +========================================================+============+===========+==========+
    | **Signing**                                                                                |
    +--------------------------------------------------------+------------+-----------+----------+
    | Ed25519 `[ed-25519]`                                   |      D     |     D     |     P    |
    +--------------------------------------------------------+------------+-----------+----------+
    | ECDSA P-256 `[ec-dsa-p-256]`                           |      S     |     S     |     D    |
    +--------------------------------------------------------+------------+-----------+----------+
    | ECDSA P-384 `[ec-dsa-p-384]`                           |      S     |     S     |     S    |
    +--------------------------------------------------------+------------+-----------+----------+
    | **Symmetric Encryption**                                                                   |
    +--------------------------------------------------------+------------+-----------+----------+
    | AES128-GCM `[aes-128-gcm]`                             |      D     |     D     |     D    |
    +--------------------------------------------------------+------------+-----------+----------+
    | **Asymmetric Encryption**                                                                  |
    +--------------------------------------------------------+------------+-----------+----------+
    | ECIES on P-256 with HMAC-SHA256 and AES128-GCM         |      D     |     D     |     P    |
    | `[ecies-p-256-hkdf-hmac-sha-256-aes-128-gcm]`          |            |           |          |
    +--------------------------------------------------------+------------+-----------+----------+
    | ECIES on P-256 with HMAC-SHA256 and AES128-CBC         |      /     |     S     |     P    |
    | `[ecies-p-256-hkdf-hmac-sha-256-aes-128-cbc]`          |            |           |          |
    +--------------------------------------------------------+------------+-----------+----------+
    | RSA 2048 with OAEP and SHA-256                         |      /     |     S     |     D    |
    | `[rsa-2048-oaep-sha-256]`                              |            |           |          |
    +--------------------------------------------------------+------------+-----------+----------+
    | **MAC**                                                                                    |
    +--------------------------------------------------------+------------+-----------+----------+
    | HMAC with SHA-256 `[hmac-sha-256]`                     |      D     |     D     |     D    |
    +--------------------------------------------------------+------------+-----------+----------+

Key Generation and Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~

Canton keys are generated in the node and stored in the node's primary storage
by default. This does not guarantee that the private keys are protected at rest
or at runtime, for instance against a malicious administrator. To counter these
threats, Canton allows for the use of a Key Management Service (KMS) to
either: (a) `encrypt the stored private keys and protect them at rest` or (b)
`directly use the KMS to store and manage the private keys` to protect the keys
at rest and runtime. You can find more information on how to configure this
service in :ref:`Key Management Service (KMS) Setup <kms>`.


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

Synchronization Domain Topology Manager Keys
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Synchronization Domain Namespace Signing Key
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The sync domain topology manager governs the namespace of the sync domain and has a
signing key pair for the namespace. The hash of the public key forms the
namespace and all entities in the sync domain (mediator, sequencer, the topology
manager itself) may have identities under the sync domain namespace.

The sync domain topology manager signs and thereby authorizes the following topology
transactions:

- `NamespaceDelegation` to register the namespace public key for the new namespace
- `OwnerToKeyMapping` to register both its own signing public key (see next
  section) and the signing public keys of the other sync domain entities as part of
  the sync domain onboarding
- `ParticipantState` to enable a new participant on the sync domain
- `MediatorDomainState` to enable a new mediator on the sync domain

Signing Key
^^^^^^^^^^^

The sync domain topology manager is not part of the Canton transaction protocol, but
it receives topology transactions via the sequencer. Therefore, in addition to
the sync domain namespace, the sync domain topology manager has a signing key pair, which
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

Synchronizer Domain Node Keys
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The sync domain node embeds a sequencer, mediator, and sync domain topology manager. The
set of keys remains the same as for the individual nodes.

Canton Console Keys
~~~~~~~~~~~~~~~~~~~

When the Canton console runs separately from the node and mutual authentication is
configured on the Admin API, then the console requires a TLS client certificate
and the corresponding private key as a file.

Cryptographic Key Management
----------------------------

.. _rotating-canton-keys:

Rotating Canton Node Keys
~~~~~~~~~~~~~~~~~~~~~~~~~

Canton supports the rotation of node keys (signing and encryption) during live
operation through its topology management. In order to ensure continuous
operation, the new key is added first and then the previous key is removed.

For participant nodes, sync domain nodes, and sync domain topology managers, the
nodes can rotate their keys directly using their own identity manager with
the following command for example:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/KeyManagementIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: RotateNodeKeys
   :end-before: user-manual-entry-end: RotateNodeKeys
   :dedent:

On a participant node both the signing and encryption key pairs are rotated. On a sync domain and sync domain manager node only
the signing key pair, because they do not have an encryption key pair. Identity namespace root or intermediate keys are
not rotated with this command, see below for commands on namespace key management.

For sequencer and mediator nodes that are part of a sync domain, the sync domain topology
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

Ledger-API Authorization
------------------------

The Ledger API provides :ref:`authorization support <ledger-api-jwt-configuration>` using `JWT <https://jwt.io>`_
tokens. While the JWT token authorization allows third-party applications to be authorized properly, it poses some issues
for Canton internal services such as the `PingService` or the `DarService`, which are used to manage sync domain-wide
concerns. Therefore Canton generates a new admin bearer token (64 bytes, randomly generated, hex-encoded) on each startup,
which is communicated to these services internally and used by these services to
authorize themselves on the Ledger API. The admin token allows to act as any party registered on that participant node.

The admin token is only used within the same process. Therefore, in order to obtain this token, an attacker needs to be
able to either dump the memory or capture the network traffic, which typically only a privileged user can do.

It is important to enable TLS together with JWT support in general, as otherwise tokens can be leaked to an attacker
that has the ability to inspect network traffic.
