..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _encrypted_private_key_storage_aws:

Configure Encrypted Private Key Storage with AWS KMS
====================================================

.. enterprise-only::

The following section describes the steps needed to enable :ref:`Encrypted Private Key Storage <kms_envelope_architecture>`
in Canton using AWS KMS. These steps include configuring AWS KMS, as well as configuring this particular mode of operation.

.. _encrypted_private_key_storage_permissions_aws:

AWS KMS Configuration
---------------------

To start using this feature you must first enable AWS KMS for Canton:

:ref:`--Configure AWS KMS for Canton-- <kms_aws_setup>`

The following IAM permissions are required:

- `kms:CreateKey`
- `kms:Encrypt`
- `kms:Decrypt`
- `kms:DescribeKey`

When you are using cross-account keys, you do not need the `kms:CreateKey` permission.

Encrypted Private Key Storage Configuration
-------------------------------------------

Both new and existing nodes can be configured to use this feature.
**In both cases, keys are stored encrypted in the Canton node's database**

The example below configures encrypted private key storage with AWS KMS,
for all nodes, in a simple distributed synchronizer environment.

.. code-block:: none

    canton.domain-managers.domainManager1.crypto = ${_shared_aws.crypto}
    canton.sequencers.sequencer1.crypto = ${_shared_aws.crypto}
    canton.mediators.mediator1.crypto = ${_shared_aws.crypto}
    canton.participants.participant1.crypto = ${_shared_aws.crypto}

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: EncryptedStoreConfigDistributedDomainAwsKms
   :end-before: user-manual-entry-end: EncryptedStoreConfigDistributedDomainAwsKms

As seen before, ``crypto.kms`` :ref:`configures AWS KMS <kms_aws_setup>`. Subsequently,
``crypto.private-key-store.encryption.type = kms`` enables encrypted private key storage using a
KMS.

Finally ``crypto.private-key-store.encryption.wrapper-key-id`` is an **optional field** to specify an existing (default)
KMS key to use as the encryption key. If this field is left empty, Canton creates a new key.

Supported values are:

- Key id: `“1234abcd-12ab-34cd-56ef-1234567890ab”`
- Key ARN (Amazon Resource Name): `“arn:aws:kms:us-east-1:1234abcd-12ab-34cd-56ef-1234567890ab”`
- Key alias: `“alias/test-key”`

Note that if you are using an existing AWS key, it should be created as follows:

- Key specification: `SYMMETRIC_DEFAULT <https://docs.aws.amazon.com/kms/latest/developerguide/asymmetric-key-specs.html>`_
- Key usage: `ENCRYPT_DECRYPT <https://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#symmetric-cmks>`_

After subsequent restarts the operator does not need to specify the identifier for the wrapper key;
Canton stores the generated wrapper key ID in the database.

.. important::
    Restoring from a database backup requires access to the wrapper keys used during the encryption of the data in the backup.
    Deleting the wrapper keys renders the backup unusable.

Revert Encrypted Private Key Storage
------------------------------------

Encrypted Private Key Storage can be reverted back to unencrypted storage.
To prevent accidental reverts, simply deleting the `private-key-store` configuration does **not** revert
to unencrypted storage. Instead, the following configuration must be added:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-reverted.conf
   :language: none
   :start-after: user-manual-entry-begin: EncryptedStoreReverted
   :end-before: user-manual-entry-end: EncryptedStoreReverted

.. warning::
    This forces Canton to decrypt its private keys and store them in clear; it is not recommended.

Encrypted private key storage can be enabled again by deleting the ``reverted`` field and reconfiguring it as shown in
:ref:`Encrypted Private Key Storage Configuration <encrypted_private_key_storage_aws>`.

.. _manual-aws-kms-wrapper-key-rotation:

Manual Wrapper Key Rotation
---------------------------

AWS offers automatic KMS symmetric key rotation (yearly).
Canton extends this by enabling node administrators to manually rotate the KMS wrapper
key using the following command:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/RotateWrapperKeyIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: ManualWrapperKeyRotation
   :end-before: user-manual-entry-end: ManualWrapperKeyRotation
   :dedent:

You can pass a wrapper key ID to change to or let Canton generate a new key based on the current
AWS KMS configuration.

.. note::
    Changing the key specification (e.g. enable multi region) during rotation can be done
    by updating the configuration before rotating the wrapper key.

Interoperability
----------------

Nodes configured with and without encrypted private key storage can interact with each other,
including nodes using different KMS providers.