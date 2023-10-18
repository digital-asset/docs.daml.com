..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _encrypted_private_key_storage:

Configure Encrypted Private Key Storage with a Key Management Service (KMS)
===========================================================================

.. enterprise-only::

Canton can use a KMS to `protect Canton's private keys at rest`.
We (1) store Canton's private keys in a node's database in an encrypted form and
then (2) upon startup the KMS decrypts these keys for use by Canton. The unencrypted keys are stored
in memory so this approach increases security without impacting performance. This is a common approach
used by KMS vendors; using a symmetric encryption key, called the `KMS wrapper key`, to encrypt and
decrypt the stored, private keys.

If you wish to know more you can read
section: :ref:`Protect Private Keys With Envelope Encryption and a Key Management Service <kms_envelope_architecture>`.

Currently Canton supports encrypted private key storage with an `Amazon Web Services (AWS) KMS` or
a `Google Cloud Provider (GCP) KMS`.
