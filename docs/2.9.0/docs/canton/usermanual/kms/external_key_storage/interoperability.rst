..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _external_key_storage_interoperability:

Interoperability with other nodes
---------------------------------

By default nodes in Canton run a ``tink`` provider that is not compatible with KMS provider
that stores the Canton private keys.
If you want to continue to have other nodes
running a `non-KMS Canton` you are obliged to use a ``jce`` provider
and you must explicitly configure it to use the KMS supported algorithms as the required algorithms. Here is an
example on how to set it up for a simple distributed synchronizer:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/aws-kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: JceProviderDomainConfig
   :end-before: user-manual-entry-end: JceProviderDomainConfig

And here is an example for a participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/aws-kms-provider-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: JceProviderParticipantConfig
   :end-before: user-manual-entry-end: JceProviderParticipantConfig

In other words, a node running with a ``kms`` provider (which is externally storing Canton private keys)
is only ever able to communicate with other nodes running
a ``kms`` or ``jce`` providers.

See :ref:`this table <canton_supported_keys>` for a description of cryptographic schemes supported by the KMS provider.

