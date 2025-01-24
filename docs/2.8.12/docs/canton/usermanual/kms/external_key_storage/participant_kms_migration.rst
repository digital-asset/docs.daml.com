..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _participant_kms_migration:

Participant Node Migration to KMS
---------------------------------

To migrate an existing participant node connected to a domain with a non KMS-compatible provider
and start using KMS external keys, you need to manually execute the following steps.
The general idea is to replicate the old node into a new one that uses a KMS crypto provider and connects to
a KMS-compatible domain (e.g. :ref:`running JCE with KMS supported encryption and
signing keys <external_key_storage_interoperability>`).

First, delegate the namespace of the old participant to the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsSetupNamespaceDelegation
   :end-before: user-manual-entry-end: KmsSetupNamespaceDelegation
   :dedent:

Secondly, you must recreate all parties of the old participant in the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsRecreatePartiesInNewParticipant
   :end-before: user-manual-entry-end: KmsRecreatePartiesInNewParticipant
   :dedent:

Finally, you need to transfer the active contracts of all the parties from the old participant to the new one and
connect to the new domain:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsMigrateACSofParties
   :end-before: user-manual-entry-end: KmsMigrateACSofParties
   :dedent:

The end result is a new participant node with its keys stored and managed by a KMS connected to a domain
that is able to communicate using the appropriate key schemes.

You need to follow the same steps if you want to migrate a node back to using a `non-KMS` provider.