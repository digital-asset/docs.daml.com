..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _participant_kms_migration_same_namespace:

Participant Node Migration with the Same Namespace
--------------------------------------------------

One way of migrating a non-KMS participant to a new KMS-enabled one is to create a new participant
connected to a KMS-compatible sync domain (e.g. :ref:`running JCE with KMS-supported encryption and
signing keys <external_key_storage_interoperability>`) and then
transfer the data from the old node to the new one. In this example, we do not only transfer the parties, contracts and DARs,
but we also transfer the node's identity, and thus, both old and new participant will share the
same namespace. This has the advantage that it can be done in a multi-operator setting when the other operators
do not agree to this migration, because it is transparent to them and their shared contracts.

.. warning::
    You must save the :ref:`root namespace key <moving_namespace_to_offline_storage>` of the old participant
    somewhere offline so that it can be used, in the future, to migrate the node to a new protocol version.
    This is necessary because we require signing topology transactions with the root namespace key everytime
    we migrate a node to a new protocol version.

First, delegate the namespace of the old participant to the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithSameNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsSetupNamespaceDelegationSameNs
   :end-before: user-manual-entry-end: KmsSetupNamespaceDelegationSameNs
   :dedent:

Secondly, you must recreate all parties of the old participant in the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithSameNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsRecreatePartiesInNewParticipantSameNs
   :end-before: user-manual-entry-end: KmsRecreatePartiesInNewParticipantSameNs
   :dedent:

Thirdly, you should migrate your DARs to the new participant:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithSameNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsMigrateDarsSameNs
   :end-before: user-manual-entry-end: KmsMigrateDarsSameNs
   :dedent:

Finally, you need to transfer the active contracts of all the parties from the old participant to the new one and
connect to the new sync domain:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/KmsMigrationWithSameNamespaceIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: KmsMigrateACSofPartiesSameNs
   :end-before: user-manual-entry-end: KmsMigrateACSofPartiesSameNs
   :dedent:

The result is a new participant node, that retains the old namespace, with its keys stored and managed by a KMS connected to a sync domain
that can communicate using the appropriate key schemes.

You need to follow the same steps if you want to migrate a node back to using a `non-KMS` provider.