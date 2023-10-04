..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _encrypted_private_key_storage:

Encrypted Private Key Storage with a Key Management Service (KMS)
=================================================================

.. enterprise-only::

By default Canton keys are generated in the node and stored in the node's primary storage.
We currently support a version of Canton that can use a KMS to `protect Canton's private keys at rest`.
We (1) store Canton's private keys in a node's database in an encrypted form and
then (2) upon startup the KMS decrypts these keys for use by Canton. The unencrypted keys are stored
in memory so this approach increases security without impacting performance. This is a common approach
used by KMS vendors; using a symmetric encryption key, called the `KMS wrapper key`, to encrypt and
decrypt the stored, private keys.

If you wish to know more you can read section: :ref:`Protect Private Keys With Envelope Encryption and a Key Management Service <kms_envelope_architecture>`.

Configure a KMS in Canton
-------------------------

To start using this feature we need to first enable KMS for Canton:

:ref:`--Configure KMS for Canton-- <kms_setup>`

When using a KMS to envelope encrypt the private keys stored in Canton, it needs to be configured
with the following list of authorized actions (i.e. IAM permissions):

.. _encrypted_private_key_storage_permissions:

+-------------------------------------------+-------------------------------------------+
| **AWS**                                   | **GCP**                                   |
+===========================================+===========================================+
| `kms:CreateKey`                           | `cloudkms.cryptoKeyVersions.create`       |
+-------------------------------------------+-------------------------------------------+
| `kms:TagResource`                         | `-`                                       |
+-------------------------------------------+-------------------------------------------+
| `kms:Encrypt`                             | `cloudkms.cryptoKeyVersions.useToEncrypt` |
+-------------------------------------------+-------------------------------------------+
| `kms:Decrypt`                             | `cloudkms.cryptoKeyVersions.useToDecrypt` |
+-------------------------------------------+-------------------------------------------+
| `kms:DescribeKey`                         | `cloudkms.cryptoKeys.get`                 |
+-------------------------------------------+-------------------------------------------+

If you plan to use cross-account key usage then the permissions for key rotation in Canton, namely
`kms:CreateKey` or `cloudkms.cryptoKeyVersions.create`,
do not have to be configured as they do not apply in that use case.

Configure an Encrypted Private Key Storage in Canton
----------------------------------------------------

.. warning::
    You cannot mix an encrypted private key storage configuration with an external private key storage
    configuration.

Encrypted private key storage support can be enabled for a new installation (i.e., during the node
bootstrap) or for an existing deployment. **In both cases the keys are encrypted and stored in encrypted form
in the Canton node's database in a transparent way without the need for the node manager to be actively engaged.**

In the example below the encrypted private key storage
integration is enabled for a participant node (called ``participant1``).
The same applies for any other node, such as a sync domain manager, a mediator, or a sequencer.

The most important setting that enables an encrypted private key storage using a
KMS is ``type = kms``. This is shown below. If this is not specified, Canton
stores the keys using its default approach, which is in unencrypted form.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: PrivateKeyStoreConfig
   :end-before: user-manual-entry-end: PrivateKeyStoreConfig

There are two ways to choose the KMS wrapper key: (1) use an already existing KMS key or; (2)
let Canton generate one.
To use an already existing KMS key, you must specify its identifier. For example, for AWS KMS this can
be one of the following:

- Key id: `“1234abcd-12ab-34cd-56ef-1234567890ab”`
- Key ARN (Amazon Resource Name): `“arn:aws:kms:us-east-1:1234abcd-12ab-34cd-56ef-1234567890ab”`
- Key alias: `“alias/test-key”`

Please be aware that an AWS KMS key needs to be configured with the following settings:

- Key specification: `SYMMETRIC_DEFAULT <https://docs.aws.amazon.com/kms/latest/developerguide/asymmetric-key-specs.html>`_
- Key usage: `ENCRYPT_DECRYPT <https://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#symmetric-cmks>`_

Similarly, for GCP KMS we can use:

- Key name: `test-key`
- Key RN (Resource Name): `projects/gcp-kms-testing/locations/us-east1/keyRings/canton-test-keys/cryptoKeys/test-key/cryptoKeyVersions/1`

And your key needs to be configured with the following settings:

- Key algorithm: `GOOGLE_SYMMETRIC_ENCRYPTION <https://cloud.google.com/kms/docs/algorithms>`_
- Key purpose: `ENCRYPT_DECRYPT`

If no ``wrapper-key-id`` is specified, Canton creates a symmetric key in the KMS. After subsequent restarts the operator does not need to specify the identifier for the newly
created key; Canton stores the generated wrapper key id in the database.

An example with a pre-defined AWS KMS key is shown below:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsKeyConfig
   :end-before: user-manual-entry-end: KmsKeyConfig

An example configuration that puts it all together is below:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled.conf
   :language: none

.. _backup-kms:

.. note::
    The wrapper keys used to encrypt the private keys need
    to live as long as the Canton database backups, so care must be taken when
    deleting database backup files or `KMS wrapper keys`. Otherwise, a Canton node restored from a database
    backup may try to decrypt the private keys with a `KMS wrapper key` that was previously deleted.

Revert Encrypted Private Key Storage
------------------------------------

If you wish to change the encrypted private key store and revert back to using an unencrypted store,
you must restart the nodes with an updated configuration that includes

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-reverted.conf
   :language: none
   :start-after: user-manual-entry-begin: EncryptedStoreReverted
   :end-before: user-manual-entry-end: EncryptedStoreReverted

.. warning::
    We strongly advise against this as it will force Canton to decrypt its private keys and store them in clear.

For subsequent restarts we recommend deleting all encrypted private key store configurations
including the KMS configuration. We have forced the manual configuration of the ``reverted`` flag to prevent any unwanted
decryption of the database (e.g. by unintentionally deleting the KMS configuration).
You can enable again private key encryption by deleting the ``reverted`` tag and re-configuring the KMS.

.. _manual-kms-wrapper-key-rotation:

Manual Wrapper Key Rotation
---------------------------

Currently AWS and GCP offer automatic KMS symmetric key rotation (yearly for AWS and user-defined for GCP).
Canton extends this by enabling node administrators to manually rotate the KMS wrapper
key using the following command:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/RotateWrapperKeyIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: ManualWrapperKeyRotation
   :end-before: user-manual-entry-end: ManualWrapperKeyRotation
   :dedent:

You can optionally pass a wrapper key id to change to or let Canton generate a new key based on the current
KMS configuration.

.. note::
    Changing the key specification (e.g. enable multi region) during rotation is for now
    only possible with AWS, by updating the configuration before rotating the wrapper key.

