..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

Manage Participants
===================

.. _participant_bootstrapping:

Manual vs Automatic Identity Initialization
-------------------------------------------

Similarly to a domain, a participant node can either be initialized automatically, the default behaviour,
or manually. Managing the initialization manually is particularly useful when a participant:

1. Does not control its own identity;
2. When you do not want to store its identity key on the node for security reasons;
3. When you want to set a participant's keys by yourself.

If you want to disable the automatic initialization of a participant node you have to set:

.. code-block:: none

    participant.init.auto-init = false

Keys Initialization
-------------------

Besides a namespace key and a signing key a participant node also has an asymmetric encryption key that it
uses to decrypt encrypted transactions. Key are created automatically, however, if you are manually setting up your
participant node you must use the following commands to generate your signing keys (for namespace and signing)
and the encryption key:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/topology/TopologyManagementHelper.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: ManualInitKeys
   :end-before: architecture-handbook-entry-end: ManualInitKeys
   :dedent:

We reiterate again the fact that if you are using a Key Management Service (KMS) to handle Canton's keys
and you want to use a set of pre-generated keys you must use instead the commands `register_kms_signing_key()` and
`register_kms_encryption_key()`

Please refer to :ref:`External Key Storage with a Key Management Service (KMS) <external_key_storage>` for more details.

Participant Manual Initialization
---------------------------------
The following steps describe how to manually initialize a participant node after the keys have been generated:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/topology/TopologyManagementHelper.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: ManualInitParticipant
   :end-before: architecture-handbook-entry-end: ManualInitParticipant
   :dedent: