..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _external_key_storage_aws:

Configure External Key Storage with AWS KMS
===========================================

.. enterprise-only::

The following section describes the steps needed to enable :ref:`External Key Storage <kms_external_architecture>`
in Canton using AWS KMS. These steps include configuring AWS KMS, as well as configuring this particular mode of operation.

.. _external_key_storage_permissions_aws:

AWS KMS Configuration
---------------------

To start using this feature you must first enable a KMS for Canton.

:ref:`--Configure AWS KMS for Canton-- <kms_aws_setup>`

The following IAM permissions are required:

- `kms:CreateKey`
- `kms:TagResource`
- `kms:Decrypt`
- `kms:Sign`
- `kms:DescribeKey`
- `kms:GetPublicKey`

When you are using cross-account keys, you do not need the `kms:CreateKey` and `kms:TagResource` permissions.

External Key Storage Configuration
----------------------------------

External key storage support can be enabled for a new installation (i.e., during the node
bootstrap) or for an existing deployment.
**Be aware that if a node has already been deployed you need to** :ref:`perform a node migration <participant_kms_migration>`.
Simply adding the following configuration is not enough.

In the example below, we configure **a new** Canton participant node (called ``participant1``) to generate and
store private keys in an external AWS KMS. The same configuration is applicable for all other node entities, including the synchronizer manager,
mediators, and sequencers.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/aws-kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsProviderConfig
   :end-before: user-manual-entry-end: KmsProviderConfig

An example configuration that puts together both AWS KMS and external storage configuration is shown below:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/aws-kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: AwsKmsProviderFullConfig
   :end-before: user-manual-entry-end: AwsKmsProviderFullConfig

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

where `xyzKmsKeyId` is the AWS KMS identifier for a specific key (e.g. `KMS Key ARN`). When using
`AWS cross account keys <https://docs.aws.amazon.com/kms/latest/developerguide/key-policy-modifying-external-accounts.html>`_
the key ID can't be used, use the key `ARN` instead.

Here is a reminder of the initial keys that each node owns:

.. table:: List of keys that each node owns

    +-----------------------------------+------------------+--------------------------+---------------+--------------+-----------------+
    | **Keys**                          | **Synchronizer** | **Synchronizer Manager** | **Sequencer** | **Mediator** | **Participant** |
    +===================================+==================+==========================+===============+==============+=================+
    | `(Signing) Namespace Key`         | x                | x                        |               |              | x               |
    +-----------------------------------+------------------+--------------------------+---------------+--------------+-----------------+
    | `Signing Key`                     | x                | x                        | x             | x            | x               |
    +-----------------------------------+------------------+--------------------------+---------------+--------------+-----------------+
    | `(Asymmetric) Encryption Key`     |                  |                          |               |              | x               |
    +-----------------------------------+------------------+--------------------------+---------------+--------------+-----------------+

Depending on the key purpose and the default signing and encryption schemes defined in Canton,
you need to pre-generate the corresponding AWS KMS keys with the correct settings:

.. table:: AWS key configuration

    +-------------------+-----------------------------------------------------------------------+-----------------------------------------------------+
    | **Provider**      | **SIGNING**                                                           | **ENCRYPTION**                                      |
    +===================+=======================================================================+=====================================================+
    | AWS               | - **Key Purpose:** `SIGN_VERIFY`                                      | - **Key Purpose:** `ENCRYPT_DECRYPT`                |
    |                   | - **Key Algorithms:** `ECC_NIST_P256` or `ECC_NIST_P384`              | - **Key Algorithm:** `RSA_2048`                     |
    +-------------------+-----------------------------------------------------------------------+-----------------------------------------------------+

Below are links to guides on how to manually initialize participant nodes and synchronizer.
In those guides, keys are generated using console commands such as:

.. code-block:: none

    val identityKey = participant.keys.secret.generate_signing_key(name = participant.name + "-namespace")

Make sure to **replace those commands with the ones shown above** with which you registered your existing keys
instead of generating new ones.

- :ref:`initialize synchronizer <manually-init-domain>`
- :ref:`initialize participants <manually-init-participant>`