..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _external_key_storage:

Configure External Key Storage with a Key Management Service (KMS)
==================================================================

.. enterprise-only::

Canton can delegate all asymmetric decryption and signing operations to a KMS. In that mode, private keys
are stored in the KMS, not in Canton's own storage nor in memory. Decryption and signing operations each
require an API call to the KMS. A Canton node still stores
the corresponding public keys in its stores so that it can verify signatures and
encrypt messages without having to rely on the KMS.

See :ref:`Externalize Private Keys With a Key Management Service <kms_external_architecture>` for more details.

Currently Canton supports external key storage with `Amazon Web Services (AWS) KMS
<https://aws.amazon.com/kms/>`_ or
`Google Cloud Provider (GCP) KMS <https://cloud.google.com/security-key-management?hl=en>`_.
