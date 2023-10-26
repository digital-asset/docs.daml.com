..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _encrypted_private_key_storage_gcp:

Configure Encrypted Private Key Storage with GCP KMS
====================================================

.. enterprise-only::

The following section describes the steps needed to enable :ref:`Encrypted Private Keys Storage <kms_envelope_architecture>`
in Canton using GCP KMS. These steps include configuring GCP KMS, as well as, configuring this particular mode of operation.

.. note::
    Nodes configured with and without encrypted private key storage can interact with each other,
    including nodes using different KMS providers.

.. _encrypted_private_key_storage_permissions_gcp:

GCP KMS Configuration
---------------------

To start using this feature we need to first enable GCP KMS for Canton:

:ref:`--Configure GCP KMS for Canton-- <kms_gcp_setup>`

The following IAM permissions are required:

- `cloudkms.cryptoKeyVersions.create`
- `cloudkms.cryptoKeyVersions.useToEncrypt`
- `cloudkms.cryptoKeyVersions.useToDecrypt`
- `cloudkms.cryptoKeys.get`

When you are using cross-account keys, you do not need the `cloudkms.cryptoKeyVersions.create` permission.

Encrypted Private Key Storage Configuration
-------------------------------------------

Both new and existing nodes can be configured to use this feature.
**In both cases, keys are stored encrypted in the Canton node's database**

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
    canton.participants.participant1.crypto = ${_shared_gcp.crypto}

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: EncryptedStoreConfigDistributedDomainGcpKms
   :end-before: user-manual-entry-end: EncryptedStoreConfigDistributedDomainGcpKms

.. important::
    Restoring from a database backup will require access to the wrapper keys used during the encryption of the data in the backup.
    Deleting the wrapper keys would render the backup unusable.

Revert Encrypted Private Key Storage
------------------------------------

Encrypted Private Key Storage can be reverted back to unencrypted storage.
To prevent accidental reverts, simply deleting the `private-key-store` configuration will **not** revert
back to unencrypted storage. Instead the following configuration must be added:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-reverted.conf
   :language: none
   :start-after: user-manual-entry-begin: EncryptedStoreReverted
   :end-before: user-manual-entry-end: EncryptedStoreReverted

.. warning::
    We strongly advise against this as it will force Canton to decrypt its private keys and store them in clear.

Encrypted private key storage can be enabled again by deleting the ``reverted`` field and re-configuring it as shown in
:ref:`Encrypted Private Key Storage Configuration <encrypted_private_key_storage_gcp>`.

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



