..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _participant_kms_migration:

Participant Node Migration to KMS
---------------------------------

To migrate an existing participant node connected to a sync domain with a non-KMS-compatible provider
and start using KMS external keys, you need to follow one of the next guides.
The general idea is to replicate the old node into a new one that uses a KMS crypto provider and connects to
a KMS-compatible sync domain (e.g. :ref:`running JCE with KMS-supported encryption and
signing keys <external_key_storage_interoperability>`).

We offer two different ways of doing this migration: (a): :ref:`migrate to a new participant that uses the same namespace
identity <participant_kms_migration_same_namespace>` and (b) :ref:`migrate to a new participant with an entire new identity
and namespace <participant_kms_migration_new_namespace>`. The first option
does not require us to change the party ids for the active contracts in the old participant, and it can be done
by a single operator, because it is a transparent process for the other operators and their shared contracts. However,
the old domain must support the new protocol version and the original root namespace key must be kept safe to allow
the future migration to a new protocol version.
The second option re-writes the contracts with new party identifiers in line with the new participant namespace.
Therefore, you do not need to preserve the original root namespace key for a future migration. This works even if the
old domain node does not support the new protocol version. However, for it to work, a single operator must control all the
contracts or all participant operators have to agree on this rewrite.

