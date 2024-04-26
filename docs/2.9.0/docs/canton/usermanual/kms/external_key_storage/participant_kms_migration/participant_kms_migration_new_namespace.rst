..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _participant_kms_migration_new_namespace:

Participant Node Migration with a New Namespace
-----------------------------------------------

To migrate a non-KMS participant to a KMS-enabled one we need to make sure we have this new participant
connected to a domain that runs the required cryptographic schemes (see table x) and enable KMS for that participant.
Afterwards, we transfer all parties, contracts and DARs from the old participant to the new one. Since,
in this case we do not transfer the identities from the old node to the new one we need to re-write our contracts
so that they refer to the correct party ids. With this method, we can easily migrate our old participant
that runs an older protocol version to a new participant with KMS enabled. Furthermore,
we do not need to safe-keep the old node's root namespace key because our participant namespace changes.

First, you must recreate all parties of the old participant in the new participant, keeping the same display name,
but with different ids:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithNewNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsRecreatePartiesInNewParticipantNewNs
   :end-before: user-manual-entry-end: KmsRecreatePartiesInNewParticipantNewNs
   :dedent:

Secondly, you should migrate your DARs to the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithNewNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsMigrateDarsNewNs
   :end-before: user-manual-entry-end: KmsMigrateDarsNewNs
   :dedent:

Finally, you need to transfer the active contracts of all the parties from the old participant to the new one and
re-write the party ids mentioned in those contracts to match the new party ids. We can then connect to the new sync domain:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithNewNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsMigrateACSofPartiesNewNs
   :end-before: user-manual-entry-end: KmsMigrateACSofPartiesNewNs
   :dedent:

The result is a new participant node, in a different namespace, with its keys stored and managed by a KMS connected to a sync domain
that can communicate using the appropriate key schemes.

You need to follow the same steps if you want to migrate a node back to using a `non-KMS` provider.