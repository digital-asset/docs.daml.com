..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _manual-kms-external-key-rotation:

Manual KMS key rotation
-----------------------

Canton keys, except the root namespace keys, can still be manually rotated even if they are externally stored in a KMS.
To do that you can use the :ref:`standard rotate key commands <rotating-canton-keys>` or,
if you already have a pre-generated KMS key to rotate to, run the following command:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/kms/RotateKmsKeyIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: RotateKmsNodeKey
   :end-before: user-manual-entry-end: RotateKmsNodeKey
   :dedent:

No current KMS service offers automatic rotation of asymmetric keys so
the node operator needs to be responsible for periodically rotating these keys.

If you need to rotate the namespace root key then you have to follow the same
:ref:`procedure <participant_kms_migration>` as migrating from a non-KMS to a KMS participant
including contract rewriting.