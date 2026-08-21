..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _kms:

Key Management Service (KMS) Setup
==================================

.. enterprise-only::

By default Canton keys are generated in the node and stored in the node's primary storage.
We currently support a version of Canton that can use a KMS to either:
(a) :ref:`protect Canton's private keys at rest <encrypted_private_key_storage>`
or (b) :ref:`generate and store the private keys itself <external_key_storage>`.

You can find more background information on this key management feature in
:ref:`Secure Cryptographic Private Key Storage <kms_architecture>`.
See :ref:`Protect Private Keys With Envelope Encryption and a Key Management Service <kms_envelope_architecture>`
if you want to know how Canton can protect private keys while they remain internally stored in Canton using a KMS, or
:ref:`Externalize Private Keys With a Key Management Service <kms_external_architecture>`
for more details on how Canton can enable private keys to be generated and stored by an external KMS.

The following sections describe how to enable KMS support in Canton
and how to setup each mode of operation.
