..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _canton_keys:

Contract Keys in Canton
=======================

Daml provides a "contract key" mechanism for contracts, similar to primary keys in relational databases. When using
multi-sync-domain topologies, Canton will support the full syntax of contract keys, but only a reduced semantics.
That is, all valid Daml contracts using keys will run on Canton, but their behavior may deviate from the prescribed one.
This document explains the deviation, as well as ways of recovering the full functionality of keys in some scenarios.
It assumes a reasonable familiarity with Daml.

.. note::
    This section covers a preview feature, when using contract keys in a multi-sync-domain setup. By default,
    contract key uniqueness is enabled, and therefore this section does not apply.
    However, contract key uniqueness will soon be deprecated, as uniqueness cannot be enforced among
    multiple sync domains. We encourage you to build your models already anticipating this change.


Keys have two main functions:

* Simplifying the modeling of mutable state in Daml.
   Daml contracts are immutable and can be only created and archived.
   Mutating a contract ``C`` is modeled by archiving ``C`` and creating a new contract ``C'`` which is a modified version of ``C``.
   Other than keys, Daml offers no means to capture the relation between ``C`` and ``C'``.
   After archiving ``C``, any contract ``D`` that contains the contract ID of ``C`` is left with a dangling reference.
   This makes it cumbersome to model mutable state that is split across multiple contracts.
   Keys provide mutable references in Daml; giving ``C`` and ``C'`` the same key ``K`` allows ``D`` to store ``K`` as a reference that will start pointing to ``C'`` after archiving ``C``.

* Checking that no active contract with a given key exists at some point in time.
   This mainly serves to provide uniqueness guarantees, which are useful in many cases.
   One is that they can serve to de-duplicate data coming from external sources.
   Another one is that they allow "natural" mutable references, e.g., referring to a user by their username or e-mail.

Canton participants and sync domains can be run in two modes:

#. In *unique-contract-key (UCK) mode*, contract keys in Canton provide both functions; there can be at most one active contract for each key on a UCK sync domain.
    However, only UCK participants can connect to UCK sync domains and the first UCK sync domain a UCK participant connects to is the only sync domain that the participant can connect to in its lifetime.
    UCK sync domains and their participants are thus isolated islands that are deprived of Canton's composability and interoperability features.

#. In *non-unique-keys mode*, contract keys in Canton provide the first, but not the second function, at least not without additional effort or restrictions.
   In particular:

   #. In Canton, two (or more) active contracts with the same key may exist simultaneously on the same or different sync domains.
   #. If no submitting party is a stakeholder of an active contract instance of template ``Template`` with the key ``k``
      visible on the submitting participant when the participant processes the submission,
      then a ``lookupByKey @Template k`` may return ``None``
      even if an active contract instance of template ``Template`` with the key ``k`` exists on the virtual shared ledger
      at the point in time when the transaction is committed.
   #. A ``fetchByKey @Template k`` or an ``exerciseByKey @Template k`` or a positive ``lookupByKey @Template k`` (returning ``Some cid``) may return any active contract of template ``Template`` with key ``k``.

In the remainder of the document we:

* give :ref:`more detailed examples <canton_keys_difference_examples>` of the differences above
* give an :ref:`overview of how keys are implemented <canton_keys_implementation_summary>` so that you can better understand their behavior
* show :ref:`workarounds for recovering the uniqueness functionality <canton_keys_workarounds>` in particular scenarios on normal sync domains
* give a :ref:`formal semantics of keys <canton_key_formal_semantics>` in Canton, in terms of the :ref:`Daml ledger model <da-ledgers>`
* explain how to :ref:`run a sync domain in UCK mode <canton_uck>`.


.. _canton_uck:

Synchronization Domains with Uniqueness Guarantees
--------------------------------------------------

By default, Canton sync domains and participants are currently configured to provide unique contract key (UCK) semantics. This will be deprecated in the future, as such a uniqueness constraint cannot be supported on
a distributed system in a useful way. The :ref:`semantic differences from the ledger model <canton_keys_difference_examples>`
disappear if the transactions are submitted to a participant connected to a Canton sync domain in :ref:`UCK mode <canton_uck>`.
The :ref:`workarounds <canton_keys_workarounds>` are therefore not needed.

A UCK participant can connect only to a UCK sync domain.
Moreover, once it has successfully connected to a UCK sync domain, it will refuse to connect to another sync domain.
Accordingly, conflict detection on a single sync domain suffices to check for key uniqueness.
Participants connected to a UCK sync domain check for key conflicts whenever they host one of the key maintainers:

* When a contract is created, they check that there is no other active contract with the same key.

* When the submitted transaction contains a negative key lookup, the participants check that there is indeed no active contract for the given key.

.. warning::
   Daml workflows deployed on a UCK sync domain are locked into this sync domain.
   They cannot use Canton's composability and interoperability features
   because the participants will refuse to connect to other sync domains.


Non-Unique Contract Keys Mode
-----------------------------

This section explains how contract keys behave on participants connected to Canton sync domains without unique contract keys.
This mode can be activated by setting

.. literalinclude:: /canton/includes/mirrored/community/app/src/test/resources/documentation-snippets/non-uck-mode.conf

.. note::

    The non-unique contract keys feature is preview-only. Currently, multiple keys will override each other.

.. _canton_keys_difference_examples:

Examples of Semantic Differences
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Double Key Creation
+++++++++++++++++++

Consider the following template:

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_KEYED
   :end-before: END_KEYED

The Daml contract key semantics prescribe that no two active ``Keyed`` contracts with the same keys should exist.
For example, consider the following Daml script:

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_MULTIPLE_CREATES
   :end-before: END_MULTIPLE_CREATES

Alice's submission must fail, since it attempts to create two contracts with the key ``(Alice, 1)``.
In Canton, however, the submission is legal and will succeed (if executed, for example, through Daml Script).
Thus, you cannot directly rely on keys to ensure the uniqueness of user-chosen usernames or external identifiers (e.g., order identifiers, health record identifiers, entity identifiers) in Canton.

False ``lookupByKey`` Negatives
+++++++++++++++++++++++++++++++

Similarly, your code might rely on the negative case of a ``lookupByKey``:

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_INITIALIZATION
   :end-before: END_INITIALIZATION

When running a process (represented by the ``Initialization`` template here), you might use a pattern like above to ensure that it is run only once.
The ``Initialization`` template does not have a key.
Nevertheless, if all processing happens through the ``Orchestrator`` template, there will only ever be one ``Initialization`` created for the given party and key.
For example, the following script creates only one ``Initialization`` contract:

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_LOOKUP_NONE
   :end-before: END_LOOKUP_NONE

In scripts, transactions are executed sequentially.
Alice's second submission above will always find the existing ``Keyed`` contract, and thus execute the ``Some`` branch of the ``Initialize`` choice.
In real-world applications, transactions may run concurrently.
Assume that ``initTx1`` and ``initTx2`` are run concurrently, and that these are the first two transactions running the ``Initialize`` choice.
Then, during their preparation, both of them might execute the ``None`` branch (i.e., ``lookupByKey`` might return a negative result), and thus both might try to create the ``Initialization`` contract.
However, negative ``lookupByKey`` results must be committed to the ledger, and the :ref:`key consistency requirements <da-model-key-consistency>` prohibit both of them committing.
Thus, one of ``initTx1`` and ``initTx2`` might fail, or they both might succeed (if one of them sees the effects of the other and then executes the ``Some`` branch), but in either case, only one ``Initialization`` contract will be created.

In Canton, however, it is possible that both ``initTx1`` and ``initTx2`` execute the ``None`` branch, yet both get committed.
For example, if the participant processes the submissions for ``initTx1`` and ``initTx2`` concurrently,
neither will see ``initTx1`` the ``Initialization`` contract created by ``initTx2`` nor vice versa.
Canton orders the transactions only after the commands have been interpreted,
and in normal mode it does not check the consistency of negative lookup by keys after ordering any more.
Thus, two ``Initialization`` contracts may get created.

Semantics of ``fetchByKey`` and Positive ``lookupByKey``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Daml also provides a ``fetchByKey`` operation.
Daml commands are evaluated against some active contract set.
When Daml encounters a ``fetchByKey`` command, it tries to find an active contract with the given key (and fails if it cannot).
Since Daml semantics prescribe that only one such contract may exist, it is clear which one to return.
For example, consider the script:

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_FETCH_BY_KEY
   :end-before: END_FETCH_BY_KEY

The script uses a helper template ``KeyedHelper`` shown at the end of this section
because ``fetchByKey`` and ``lookupByKey`` `cannot be used directly in a Daml script. <https://discuss.daml.com/t/in-daml-script-do-we-have-equivalent-command-for-lookupbykey-fetchbykey/919>`_

Daml's contract key semantics says that Alice's second submission must fail, since a contract with the given key already exists.
Thus, her third submission will always succeed, and return ``keyedId1``, since this is the only ``Keyed`` contract with the key ``(Alice, 1)``.
Similarly, her fourth submission will also successfully find a contract, which will be ``keyedId1``.

As discussed earlier, Alice's second submission in the above script will succeed in Canton.
Alice's third and fourth submissions thus may return different contract IDs, with each returning either ``keyedId1``, or ``keyedId2``.
Whichever one is returned, a successful ``fetchByKey`` and ``lookupByKey`` still guarantees that the returned contract is active at the time when the transaction gets committed.
As mentioned earlier, negative ``lookupByKey`` results may be spurious.

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_KEYED_HELPER
   :end-before: END_KEYED_HELPER


.. _canton_keys_implementation_summary:

Canton's Implementation of Keys
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Internally, a Canton participant node has a component that provides the gRPC interface (the "Ledger API Server"), and another component that synchronizes participants (the "sync service").
When a command is submitted, the Ledger API Server evaluates the command against its local view, including the resolution of key lookups (``lookupByKey`` and ``fetchByKey``).
Submitted commands are evaluated in parallel, both on a single node and across different nodes.

The evaluated command is then sent to the sync service, which runs Canton's :ref:`commit protocol <canton-overview>`.
The protocol provides a linear ordering of all transactions on a single sync domain, and participants check all transactions for conflicts, with an earlier-transaction-wins policy.
As participants only see parts of transactions (the joint :ref:`projection <da-model-projections>` of the parties they host), they only check conflicts on contracts for which they host stakeholders.
During conflict detection, positive key lookups (that find a contract ID based on a key) are treated as ordinary ``fetch`` commands on the found contract ID, and the contract ID is checked to still be active.
Negative key lookups, on the other hand, are never checked by Canton (a malicious submitter, for example, can always successfully claim that the lookup was negative).
Similarly, contract creations are not checked for duplicate keys.
Logically, both of these checks would require checking a "there is no such key" statement.
Canton does not check such statements.
While adding the check to the individual participants is straightforward, it is hard to get meaningful guarantees from such local checks because each participant has only a limited view of the entire virtual global ledger.
For example, the check could pass locally on a participant even though there exists a contract with the given key on some sync domain that the participant is not connected to.
Similarly, since the processing of different sync domains runs in parallel, it is unclear how to consistently handle the case where transactions on different sync domains create two contracts with the same key.

For integrity, the participants also re-evaluate the submitted command (or, more precisely, the subtransaction in the joint :ref:`projection <da-model-projections>` of the parties they host).
The commit protocol ensures that any two involved participants will evaluate the key lookups in the same way as the Ledger API Server of the submitting participant.
That is, if there are two active contracts with the key ``k``, the protocol ensures that a ``fetchByKey k`` will return the same contract on all participants.

Once the sync protocol commits a transaction, it informs the Ledger API server, which then atomically updates its set of active contracts.
The transactions are passed to the Ledger API server in the order in which they are recorded on the ledger.



.. _canton_keys_workarounds:

Workarounds for Recovering Uniqueness
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Since some form of uniqueness for ledger data is necessary in many cases, we list some strategies to achieve it in Canton
without being locked into a UCK sync domain.
The strategies' applicability depends on your contracts and the deployment setup of your application.
In general, none of the strategies apply to the case where creations and deletions of contracts with keys are delegated.

Setting: Single Maintainer, Single Participant Node
+++++++++++++++++++++++++++++++++++++++++++++++++++

Often, contracts may have a single maintainer (e.g., an "operator" that wants to have unique user names for its users).
In the simplest case, the maintainer party will be hosted on just one participant node.
This setting allows some simple options for recovering uniqueness.

Command ID Deduplication
""""""""""""""""""""""""

The Ledger API server deduplicates commands based on their IDs.
Note, however, that the IDs are deduplicated only within a configured window of time.
This can simplify the uniqueness bookkeeping of your application as follows.
Before your application sends a command that creates a contract with the key ``k``, it should first check that no contract with the key ``k`` exists in a recent ACS snapshot (obtained from the Ledger API).
Then, it should use a command ID that is a deterministic function of ``k`` to send the command.
This protects you from the race condition of creating the key twice concurrently, without having to keep track of commands in flight.
Caveats to keep in mind are:

- you need to know exactly which contracts with keys each of your commands will create
- your commands may only create contracts with a single key ``k``
- only the maintainer party may submit commands that create contracts with keys (i.e., do not delegate the creation to other parties).

However, these conditions are often true in simple cases (e.g., commands that create new users).

Generator Contract
""""""""""""""""""

Another approach is to funnel all creations of the keyed contracts through a "generator" contract.
An example generator for the ``Keyed`` template is shown below.

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_GENERATOR
   :end-before: END_GENERATOR

The main difference from the ``Orchestrator`` contract is that the ``Generate`` choice is consuming.
Caveats to keep in mind are:

- Your application must ensure that you only ever create one ``Generator`` contract (e.g., by creating one when initializing the application for the first time).
- All commands that create the ``Keyed`` contract must be issued by the maintainer. In particular, do not delegate choices on the ``Generator`` contract to other parties, because those parties may not have full visibility into all the ``Keyed`` contracts and ``lookupByKey`` may therefore wrongly return ``None``.
- You must not create ``Keyed`` contracts by any other means other than exercising the ``Generate`` choice.
- The ``Generate`` choice as shown above will not abort the command if the contract with the given key already exists, it will just return the existing contract.
  However, this is easy to change.
- This approach relies on a particular internal behavior of Canton (as discussed below).
  While we don't expect the behavior to change, we do not currently make strong guarantees that it will not change.
- If the participant is connected to multiple sync domains in future versions of Canton, the ``Generator`` contract cannot guarantee uniqueness, as explained below.
  To be future-proof, you should only use the ``Generator`` approach in settings when your participant is connected to a single sync domain.

A usage example script is below.

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_EX_GENERATOR
   :end-before: END_EX_GENERATOR

To understand why this works, first read how keys are :ref:`implemented in Canton <canton_keys_implementation_summary>`.
With this in mind, since the ``Generate`` choice is consuming, if you issue two or more concurrent commands that use the ``Generate`` choice, at most one of them will succeed (as the ``Generator`` contract will be archived when the first transaction commits).
Thus, all accepted commands will be evaluated sequentially by the Ledger API server.
As the server writes the results of accepted commands to its database atomically, the ``Keyed`` contract created by one command that uses ``Generate`` will either be visible to the following command that uses ``Generate``, or it will have been archived by some other, unrelated command in between.

If the participant is connected to multiple sync domains, the ``Generator`` contract can be reassigned between those sync domains.
Around such reassignments, it can happen that the Ledger API server already starts processing a command on the target sync domain before it has completely processed everything prior to the reassignment on the source sync domain.
The processing on the target sync domain does not necessarily see all key ``Keyed`` contracts created by predecessors of the current ``Generator`` contract, and therefore may create contracts with the same key multiple times.


Setting: Single Maintainer, Multiple Participants
+++++++++++++++++++++++++++++++++++++++++++++++++

Ensuring uniqueness with multiple participants is more complicated, and adds more restrictions on how you operate on the contract.

When there is a single maintainer hosted on multiple participant nodes,
the ``Generator`` approach works only under the following additional restriction:

- The ``Generator`` contract is never used with explicit disclosure for the following reasons:

The correctness argument is now more complicated than in the single-participant setting:
Since the ``Generate`` choice is consuming and there is at most one ``Generator`` contract at any time,
the ``Generator`` contract evolves sequentially, where the order is determined by the single sync domain that orders the ``Generate`` commands.
However, the ``lookupByKey`` operation is evaluated locally on the participant nodes possibly in a different order.
Without explicit disclosure, a command can successfully exercise a choice on a ``Generator`` contract only after the submitting participant has processed the transaction that created the ``Generator`` contract, because the partipant must fetch the ``Generator`` contract from its database.
So if the ``Generator`` contract is still active when the command is ordered on the sync domain,
no other ``Keyed`` contract was created in the meantime and a negative ``lookupByKey`` is correct.
Together with atomic database updates for transaction processing, uniqueness is therefore guaranteed.
This argument breaks when the ``Generator`` contract is explicitly disclosed:
then the partipant node can exercise a choice on a ``Generator`` contract before it has processed the transaction that creates it.

In the single-participant setting, explicit disclosure is not a problem
because the explicit disclosure can only be obtained via the Ledger API of the single participant that also submits the next command.
The participant thus has processed the creating transaction already and sees the created ``Keyed`` contracts.

Another approach is to track all "allocations" and "deallocations" of a key through a helper contract.

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_STATE
   :end-before: END_STATE

Caveats:

- Before creating a contract with the key ``k`` for the first time, your application must create the matching ``KeyState`` contract with ``allocated`` set to ``False``.
  Such a contract must be created at most once.
  In most cases, you should choose a "primary" participant on which you create such contracts.
- With a small number of exceptions, ``Keyed`` contracts must never be created or archived directly;
  this would break the synchronization with the corresponding ``KeyState`` contract.
  Instead, you must use the ``Allocate`` and ``Deallocate`` choices on the ``KeyState`` contract.
  The following exceptions are fine because Daml transactions execute atomically:
  
  * A consuming choices on the ``Keyed`` contract that immediately recreate a ``Keyed`` contract with the same key.
    
  * Ledger API commands that archive a ``Keyed`` contract and recreate a ``Keyed`` contract with the same key.
    
- Do not delegate consuming choices on the ``Keyed`` contract other than those that immediately recreate a ``Keyed`` contract with the same key.
  Instead, delegate appropriate adaptations of ``Deallocate`` on the corresponding ``KeyState`` contract.
  This ensures the above restriction that ``Keyed`` contracts are created and archived only through the ``KeyState`` contract choices.
  Non-consuming choices on ``Keyed`` contracts can be delegated without restrictions,
  and so can all the choices on ``KeyState``.
  
A usage example script is below.

.. literalinclude:: /canton/includes/mirrored/community/common/src/main/daml/CantonExamples/ContractKeys.daml
   :language: daml
   :start-after: BEGIN_EX_STATE
   :end-before: END_EX_STATE

The ``KeyState`` approach also works in the single maintainer, single participant setting.

An alternative to this approach, if you want to use a consuming choice ``ch`` on the ``Keyed`` template that doesn't recreate key, is to record the contract ID of the ``KeyState`` contract in the ``Keyed`` contract.
You can then call ``Deallocate`` from ``ch``, but you must first modify ``Deallocate`` to not perform a ``lookupByKey``.


Setting: Multiple Maintainers
+++++++++++++++++++++++++++++

Achieving uniqueness for contracts with multiple maintainers is more difficult, and the maintainers must trust each other.
To handle this case, follow the ``KeyState`` approach from the previous section.
The main difference is that the ``KeyState`` contracts must have multiple signatories.
Thus you must follow the usual Daml pattern of collecting signatories.
Be aware that you must still structure this such that you only ever create one ``KeyState`` contract.

.. _canton_key_formal_semantics:

Formal Semantics of Keys in Canton
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In terms of the :ref:`Daml ledger model <da-ledgers>`, Canton's virtual shared ledger satisfies key consistency only when it represents a single UCK sync domain.
In general, Canton's virtual shared ledger violates key consistency.
That is, ``NoSuchKey k`` actions may happen on the ledger even when there exists an active contract with the key ``k``.
Similarly, ``Create`` actions for a contract with the key ``k`` may appear on the ledger even if another active contract with the key ``k`` exists.

In terms of Daml evaluation, i.e., the translation of Daml into the ledger model transactions, the following changes:

- When evaluated against an active contract set, a ``fetchByKey k`` may result in a ``Fetch c`` action for any active contract ``c`` with the key ``k`` (in Canton, there can be multiple such contracts).
  In the current implementation, it will favor the most recently created contract within the single transaction.
  However, this is not guaranteed to hold in future versions of Canton.
  If no contract with key ``k`` is active, it will fail as usual.

- Similarly, ``lookupByKey k`` may result in a ``Fetch c`` for any active contract ``c`` with the key ``k`` of which the submitter is a stakeholder.
  If no such contract exists, it results in a ``NoSuchKey k`` as usual.

- Likewise, an ``exerciseByKey k`` may result in an ``Exercise`` on any contract ``c`` with the key ``k``.
  It fails if no contract with key ``k`` is active.


