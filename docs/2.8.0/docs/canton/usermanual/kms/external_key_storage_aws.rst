..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _external_key_storage_aws:

Configure External Key Storage and Usage with an AWS KMS
========================================================

.. enterprise-only::

The following section describes all the steps you need to enable private keys to be externally stored and managed
by an AWS KMS. For more information about what this means please consult
:ref:`Externalize Private Keys With a Key Management Service <kms_external_architecture>`.
These steps include configuring an AWS KMS, as well as, configuring this particular mode of operation.

.. _external_key_storage_permissions_aws:

Configure an AWS KMS in Canton
------------------------------

To start using this feature we need to first enable a KMS for Canton.

:ref:`--Configure AWS KMS for Canton-- <_kms_aws_setup>`

When we rely on an AWS KMS to generate, store, and manage the necessary private keys, it must be configured
with the following list of authorized actions:

+-------------------------------------------+
| **AWS**                                   |
+===========================================+
| `kms:CreateKey`                           |
+-------------------------------------------+
| `kms:TagResource`                         |
+-------------------------------------------+
| `kms:Decrypt`                             |
+-------------------------------------------+
| `kms:Sign`                                |
+-------------------------------------------+
| `kms:DescribeKey`                         |
+-------------------------------------------+
| `kms:GetPublicKey`                        |
+-------------------------------------------+

If you plan to use cross-account key usage then the permissions for key rotation in Canton, namely
`kms:CreateKey` and `kms:TagResource`,
do not have to be configured as they do not apply in that use case.

Canton Configuration for External Key Storage and Usage
-------------------------------------------------------

External key storage and usage support can be enabled for a new installation (i.e., during the node
bootstrap) or for an existing deployment.
**Be aware that if a node has already been deployed you need to** :ref:`perform a node migration <participant_kms_migration>`.
Simply adding the following configuration is not enough.

In the example below, we configure **a new** Canton participant node (called ``participant1``) to generate and
store private keys in an external KMS. The same configuration is applicable for all other node entities, e.g. domain-manager,
mediators, sequencers.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsProviderConfig
   :end-before: user-manual-entry-end: KmsProviderConfig

An example configuration that puts together both AWS KMS and external storage configuration is shown below:

.. KmsProviderFullConfig
.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsProviderConfig
   :end-before: user-manual-entry-end: KmsProviderConfig

By default nodes run a ``tink`` provider that is not compatible with KMS provider. If you want to continue to have other nodes
running a ``non-KMS Canton`` you are obliged to use a ``jce`` provider
and you must explicitly configure it to use the KMS supported algorithms as the required algorithms. Here is an
example for a domain:

.. JceProviderDomainConfig
.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsProviderConfig
   :end-before: user-manual-entry-end: KmsProviderConfig

And here is an example for a participant:

.. JceProviderDomainConfig
.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsProviderConfig
   :end-before: user-manual-entry-end: KmsProviderConfig

In other words, a node running with a ``kms`` provider is only ever able to communicate with other nodes running
a ``kms`` or ``jce`` providers.

An AWS KMS only supports the :ref:`following cryptographic schemes <canton_supported_keys>`.

Setup with Pre-Generated Keys
-----------------------------

In the previous example, Canton creates its own keys on startup and initializes the identity of the nodes automatically.
If we want to use pre-generated keys, we need to manually initialize the identity of the nodes by
adding the following flag in the config:

.. code-block:: none

    <node>.init.auto-init = false

This is applicable for ``participant`` and ``domain/domain-manager`` nodes.

Afterwards, we need register the keys in Canton by running the key registration command on each node.
For example for a ``participant`` we would run:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/topology/TopologyManagementHelper.scala
   :language: scala
   :start-after: user-manual-entry-begin: ManualRegisterKmsKeys
   :end-before: user-manual-entry-end: ManualRegisterKmsKeys
   :dedent:

where `xyzKmsKeyId` is the AWS KMS identifier for a specific key (e.g. `KMS Key RN`). If we are using, for example,
`AWS cross account keys <https://docs.aws.amazon.com/kms/latest/developerguide/key-policy-modifying-external-accounts.html>`_
be aware that using the key id is not enough and we are required to register the key using its `ARN`.

Here is a brief reminder of the initial keys that each node owns:

+-----------------------------------+------------+--------------------+---------------+--------------+-----------------+
| **Keys**                          | **Domain** | **Domain-Manager** | **Sequencer** | **Mediator** | **Participant** |
+===================================+============+====================+===============+==============+=================+
| `(Signing) Namespace Key`         | x          | x                  |               |              | x               |
+-----------------------------------+------------+--------------------+---------------+--------------+-----------------+
| `Signing Key`                     | x          | x                  | x             | x            | x               |
+-----------------------------------+------------+--------------------+---------------+--------------+-----------------+
| `(Asymmetric) Encryption Key`     | x          | x                  |               |              | x               |
+-----------------------------------+------------+--------------------+---------------+--------------+-----------------+

Depending on the key purpose and the default signing and encryption schemes defined in Canton,
you need to pre-generate the corresponding AWS KMS keys with the correct settings:

+-------------------+-----------------------------------------------------------------------+-----------------------------------------------------+
| **Provider**      | **SIGNING**                                                           | **ENCRYPTION**                                      |
+===================+=======================================================================+=====================================================+
| AWS               | - **Key Purpose:** `SIGN_VERIFY`                                      | - **Key Purpose:** `ENCRYPT_DECRYPT`                |
|                   | - **Key Algorithms:** `ECC_NIST_P256` or `ECC_NIST_P384`              | - **Key Algorithm:** `RSA_2048`                     |
+-------------------+-----------------------------------------------------------------------+-----------------------------------------------------+

Finally, using the previously registered keys, **we need to initialize our nodes**:

- :ref:`initialize domain <manually-init-domain>`
- :ref:`initialize participants <manually-init-participant>`

Please be aware that for this specific use-case **we must use the keys that we registered and not generate new ones**.
In other words, registering the keys replaces the `Keys Initialization` step in the guide to :ref:`manually initialize a node <manually_initializing_node>`.

.. _participant_aws_kms_migration:

Participant Node Migration to KMS Crypto Provider
-------------------------------------------------

To migrate an existing participant node connected to a domain with a non KMS-compatible provider
and start using KMS external keys, we need to manually execute the following steps.
The general idea is to replicate the old node into a new one that uses a KMS provider and connects to
a KMS-compatible domain (e.g. running JCE with KMS supported encryption and
signing keys).

First, we need to delegate the namespace of the old participant to the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsSetupNamespaceDelegation
   :end-before: user-manual-entry-end: KmsSetupNamespaceDelegation
   :dedent:

Secondly, we must recreate all parties of the old participant in the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsRecreatePartiesInNewParticipant
   :end-before: user-manual-entry-end: KmsRecreatePartiesInNewParticipant
   :dedent:

Finally, we need to transfer the active contracts of all the parties from the old participant to the new one and
connect to the new domain:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsMigrateACSofParties
   :end-before: user-manual-entry-end: KmsMigrateACSofParties
   :dedent:

The end result is a new participant node with its keys stored and managed by a KMS connected to a domain
that is able to communicate using the appropriate key schemes.

You need to follow the same steps if you wish to migrate a node back to using a non-KMS provider.

.. _manual-aws-kms-key-rotation:

Manual KMS key rotation
-----------------------

Canton keys can still be manually rotated even if they are externally stored in a KMS.
To do that we can use the same :ref:`standard rotate key commands <rotating-canton-keys>` or,
if we already have a pre-generated AWS KMS key to rotate to, run the following command:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/RotateKmsKeyIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: RotateKmsNodeKey
   :end-before: user-manual-entry-end: RotateKmsNodeKey
   :dedent:

AWS does not offer automatic rotation of asymmetric keys so
the node operator needs to be responsible for periodically rotating these keys.