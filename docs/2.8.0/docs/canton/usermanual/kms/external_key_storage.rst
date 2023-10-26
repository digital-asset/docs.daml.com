..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _external_key_storage:

Configure External Key Storage and Usage with a Key Management Service (KMS)
============================================================================

.. enterprise-only::

Canton can use a KMS to `generate and store the private keys itself`.
We directly use a KMS to generate and store Canton's private keys
and then use its API to securely sign an decrypt messages. A Canton node still stores
the corresponding public keys in its stores so that it can verify signatures and
encrypt messages without having to rely on the KMS.

If you wish to know more you can read section: :ref:`Externalize Private Keys With a Key Management Service <kms_external_architecture>`.

Currently Canton supports external key storage and usage with an `Amazon Web Services (AWS) KMS
<https://aws.amazon.com/kms/>`_ or
a `Google Cloud Provider (GCP) KMS <https://cloud.google.com/security-key-management?hl=en>`_.
