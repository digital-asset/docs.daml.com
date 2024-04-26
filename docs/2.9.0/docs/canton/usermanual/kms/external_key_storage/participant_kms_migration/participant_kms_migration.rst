..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _participant_kms_migration:

Participant Node Migration
--------------------------

To migrate an existing participant node connected to a sync domain with a non-KMS-compatible provider
and start using KMS external keys, you need to manually execute the following steps.
The general idea is to replicate the old node into a new one that uses a KMS provider and connects to
a KMS-compatible sync domain (e.g. :ref:`running JCE with KMS-supported encryption and
signing keys <external_key_storage_interoperability>`).

.. note::

    This process applies to any type of Participant node migration, not just KMS-related ones.

We offer two different ways of doing this migration: (a): :ref:`migrate to a new participant that uses the same namespace
identity <participant_kms_migration_same_namespace>` and (b) :ref:`migrate to a new participant with an entire new identity
and namespace <participant_kms_migration_new_namespace>`. The first option
does not require us to change the party ids for the active contracts in the old participant, but both
old and new domain have to use the same protocol version: Furthermore, the original root namespace key must
be kept safe to allow the future migration to a new protocol version. The second option re-writes the contracts
with a new party id in line with the new participant namespace. Therefore, we do not need to preserve the original
root namespace key for a future migration. This works even if the domain nodes don't share the same protocol version.



