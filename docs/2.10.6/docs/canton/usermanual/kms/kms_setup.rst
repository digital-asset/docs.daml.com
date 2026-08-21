..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _kms_setup:

Canton Configuration of a KMS
=============================

.. enterprise-only::

Canton supports using a Key Management Service (KMS) to increase security of
stored private keys.
Note that for Canton to actually use a KMS you also need to decide and configure one of the
**two independent ways** to use this service:

- :ref:`Encrypted Private Key Storage <encrypted_private_key_storage>`
- :ref:`External Key Storage <external_key_storage>`

The KMS configuration is currently enabled for `Amazon Web Services (AWS)
KMS` and `Google Cloud Provider (GCP) KMS` in Canton Enterprise.


