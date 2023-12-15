..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _external_key_storage_gcp:

Configure External Key Storage with GCP KMS
===========================================

.. enterprise-only::

The following section describes the steps needed to enable :ref:`External Key Storage <kms_external_architecture>`
in Canton using GCP KMS. These steps include configuring GCP KMS, as well as configuring this particular mode of operation.

.. _external_key_storage_permissions_gcp:

GCP KMS Configuration
---------------------

To start using this feature you must first enable a KMS for Canton.

:ref:`--Configure GCP KMS for Canton-- <kms_gcp_setup>`

The following IAM permissions are required:

- `cloudkms.cryptoKeyVersions.create`
- `cloudkms.cryptoKeyVersions.useToDecrypt`
- `cloudkms.cryptoKeyVersions.useToSign`
- `cloudkms.cryptoKeyVersions.get`
- `cloudkms.cryptoKeyVersions.viewPublicKey`

When you are using cross-account keys, you do not need the `cloudkms.cryptoKeyVersions.create` permission.

External Key Storage Configuration
----------------------------------

External key storage support can be enabled for a new installation (i.e., during the node
bootstrap) or for an existing deployment.
**Be aware that if a node has already been deployed you need to** :ref:`perform a node migration <participant_kms_migration>`.
Simply adding the following configuration is not enough.

In the example below, you configure a Canton participant node (called ``participant1``) to generate and
store private keys in an external GCP KMS. The same configuration is applicable for all other node entities, including the domain manager,
mediators, and sequencers.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/aws-kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsProviderConfig
   :end-before: user-manual-entry-end: KmsProviderConfig

An example configuration that puts together both KMS and external storage configuration is shown below:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/gcp-kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: GcpKmsProviderFullConfig
   :end-before: user-manual-entry-end: GcpKmsProviderFullConfig

Setup with Pre-Generated Keys
-----------------------------

In the previous example, Canton creates its own keys on startup and initializes the identity of the nodes automatically.
To use pre-generated keys, you need to manually initialize the identity of the nodes by
adding the following to each node's configuration:

.. code-block:: none

    <node>.init.auto-init = false

This is only applicable for ``participant`` and ``domain/domain-manager`` nodes.

Afterwards, we need to register the keys in Canton by running the key registration command on each node.
For example for a ``participant`` you would run:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/topology/TopologyManagementHelper.scala
   :language: scala
   :start-after: user-manual-entry-begin: ManualRegisterKmsKeys
   :end-before: user-manual-entry-end: ManualRegisterKmsKeys
   :dedent:

where `xyzKmsKeyId` is the GCP KMS identifier for a specific key (e.g. `KMS Key ARN`).

Here is a reminder of the initial keys that each node owns:

.. table:: List of keys that each node owns

    +-----------------------------------+------------+--------------------+---------------+--------------+-----------------+
    | **Keys**                          | **Domain** | **Domain-Manager** | **Sequencer** | **Mediator** | **Participant** |
    +===================================+============+====================+===============+==============+=================+
    | `(Signing) Namespace Key`         | x          | x                  |               |              | x               |
    +-----------------------------------+------------+--------------------+---------------+--------------+-----------------+
    | `Signing Key`                     | x          | x                  | x             | x            | x               |
    +-----------------------------------+------------+--------------------+---------------+--------------+-----------------+
    | `(Asymmetric) Encryption Key`     |            |                    |               |              | x               |
    +-----------------------------------+------------+--------------------+---------------+--------------+-----------------+

Depending on the key purpose and the default signing and encryption schemes defined in Canton,
you need to pre-generate the corresponding GCP KMS keys with the correct settings:

.. table:: GCP key configuration

    +-------------------+-----------------------------------------------------------------------+-----------------------------------------------------+
    | **Provider**      | **SIGNING**                                                           | **ENCRYPTION**                                      |
    +===================+=======================================================================+=====================================================+
    | GCP               | - **Key Purpose:** `ASYMMETRIC_SIGN`                                  | - **Key Purpose:** `ASYMMETRIC_DECRYPT`             |
    |                   | - **Key Algorithms:** `EC_SIGN_P256_SHA256` or `EC_SIGN_P384_SHA384`  | - **Key Algorithm:** `RSA_DECRYPT_OAEP_2048_SHA256` |
    +-------------------+-----------------------------------------------------------------------+-----------------------------------------------------+

Below are links to guides on how to manually initialize participant and domain nodes.
In those guides, keys are generated using console commands such as:

.. code-block:: none

    val identityKey = participant.keys.secret.generate_signing_key(name = participant.name + "-namespace")

Make sure to **replace those commands with the ones shown above** with which you registered your existing keys
instead of generating new ones.

- :ref:`initialize domain <manually-init-domain>`
- :ref:`initialize participants <manually-init-participant>`