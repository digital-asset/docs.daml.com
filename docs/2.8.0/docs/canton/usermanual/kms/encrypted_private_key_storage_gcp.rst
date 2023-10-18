..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _encrypted_private_key_storage_gcp:

Configure Encrypted Private Key Storage with a GCP KMS
======================================================

.. enterprise-only::

The following section describes all the steps you need to enable encrypted private key storage in Canton
using a GCP KMS.
For more information about what this means please consult
:ref:`Protect Private Keys With Envelope Encryption and a Key Management Service <kms_envelope_architecture>`.
These steps include configuring a GCP KMS, as well as, configuring this particular mode of operation.

.. _encrypted_private_key_storage_permissions_gcp:

Configure an GCP KMS in Canton
------------------------------

To start using this feature we need to first enable GCP KMS for Canton:

:ref:`--Configure GCP KMS for Canton-- <kms_gcp_setup>`

When using a GCP KMS to envelope encrypt the private keys stored in Canton, it needs to be configured
with the following list of authorized actions (i.e. IAM permissions):

- `cloudkms.cryptoKeyVersions.create`
- `cloudkms.cryptoKeyVersions.useToEncrypt`
- `cloudkms.cryptoKeyVersions.useToDecrypt`
- `cloudkms.cryptoKeys.get`

If you plan to use cross-account key usage then the permission `cloudkms.cryptoKeyVersions.create`
does not have to be configured as it does not apply in that use case.

Configure an Encrypted Private Key Storage in Canton
----------------------------------------------------

Encrypted private key storage support can be enabled for a new installation (i.e., during the node
bootstrap) or for an existing deployment. **In both cases the keys are encrypted and stored in encrypted form
in the Canton node's database in a transparent way without the need for the node manager to be actively engaged.**

.. note::
    You can mix nodes with and without encrypted private stores,
    even they are using a different KMS for encrypting the privates keys.

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

There are two ways to choose the GCP KMS wrapper key: (1) use an already existing GCP KMS key or; (2)
let Canton generate one.
To use an already existing GCP KMS key, you must specify its identifier. For example, this can
be one of the following:

- Key name: `test-key`
- Key RN (Resource Name): `projects/gcp-kms-testing/locations/us-east1/keyRings/canton-test-keys/cryptoKeys/test-key/cryptoKeyVersions/1`

And your key needs to be configured with the following settings:

- Key algorithm: `GOOGLE_SYMMETRIC_ENCRYPTION <https://cloud.google.com/kms/docs/algorithms>`_
- Key purpose: `ENCRYPT_DECRYPT`

If no ``wrapper-key-id`` is specified, Canton creates a symmetric key in the KMS. After subsequent restarts the operator does not need to specify the identifier for the newly
created key; Canton stores the generated wrapper key id in the database.

An example with a pre-defined GCP KMS key is shown below:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: KmsKeyConfig
   :end-before: user-manual-entry-end: KmsKeyConfig

An example configuration that puts it all together is below:

.. code-block:: none

    canton.domain-managers.domainManager1.crypto = ${_shared_gcp.crypto}
    canton.sequencers.sequencer1.crypto = ${_shared_gcp.crypto}
    canton.mediators.mediator1.crypto = ${_shared_gcp.crypto}
    canton.participants.participant3.crypto = ${_shared_gcp.crypto}

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: EncryptedStoreConfigDistributedDomainAwsKms
   :end-before: user-manual-entry-end: EncryptedStoreConfigDistributedDomainAwsKms

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
including the GCP KMS configuration. We have forced the manual configuration of the ``reverted`` flag to prevent any unwanted
decryption of the database (e.g. by unintentionally deleting the GCP KMS configuration).
You can enable again private key encryption by deleting the ``reverted`` tag and re-configuring the GCP KMS.

.. _manual-gcp-kms-wrapper-key-rotation:

Manual Wrapper Key Rotation
---------------------------

GCP offers automatic KMS symmetric key rotation (user-defined time).
Canton extends this by enabling node administrators to manually rotate the KMS wrapper
key using the following command:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/RotateWrapperKeyIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: ManualWrapperKeyRotation
   :end-before: user-manual-entry-end: ManualWrapperKeyRotation
   :dedent:

You can optionally pass a wrapper key id to change to or let Canton generate a new key based on the current GCP
KMS configuration.

.. warning::
    Changing the key specification (e.g. enable multi region) during rotation is not currently possible.



