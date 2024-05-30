..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _participant_kms_migration_new_namespace:

Participant Node Migration with a New Namespace
-----------------------------------------------

To migrate a non-KMS participant to a KMS-enabled one you need to make sure you have this new participant
connected to a KMS-compatible sync domain (e.g. :ref:`running JCE with KMS-supported encryption and
signing keys <external_key_storage_interoperability>`).
Afterwards, you transfer all parties, active contracts and DARs from the old participant to the new one. Since, in this
case, you do not transfer the identities from the old node to the new one. You need to re-write your contracts
to refer to the new party ids. With this method, you can easily migrate your old participant
that runs an older protocol version to a new participant with KMS enabled that can be running a more recent
protocol version. Furthermore, you do not need to safe-keep the old node's root namespace key, because
your participant namespace changes. However, for it to work a single operator must control
all the contracts or all participant operators have to agree on this rewrite.

.. warning::
    Currently this migration only works if you are migrating from an old participant node running protocol
    version 3. This only works for a single operator or if all other participant operators agree and
    follow the same steps.

First, you must recreate all parties of the old participant in the new participant, keeping the same display name,
but resulting in different ids due to the new namespace key:

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
re-write the party ids mentioned in those contracts to match the new party ids. You can then connect to the new sync domain:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithNewNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsMigrateACSofPartiesNewNs
   :end-before: user-manual-entry-end: KmsMigrateACSofPartiesNewNs
   :dedent:

The result is a new participant node, in a different namespace, with its keys stored and managed by a KMS connected to a sync domain
that can communicate using the appropriate key schemes.

You need to follow the same steps if you want to migrate a node back to using a `non-KMS` provider.