..
   Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _decommissioning-nodes:

Decommissioning Canton Nodes and Sync Domain Entities
=====================================================

This guide assumes general familiarity with Canton, in particular :ref:`Canton identity management concepts <identity_management_user_manual>`
and :ref:`operations from the Canton console <canton_console>`.

Note that, while onboarding new nodes is always possible,
**a decommissioned node or entity is effectively disposed of and cannot rejoin a sync domain**.
**Decommissioning is thus an irreversible operation**.

In addition, **decommissioning procedures are currently experimental**; regardless, **backing up nodes to be decommissioned
before decommissioning them is strongly recommended**.

.. _decommissioning-participants:

Decommissioning a Participant Node
----------------------------------

Prerequisites
^^^^^^^^^^^^^

Be mindful that making a participant unavailable (by disconnecting it from the sync domain or
decommissioning it) might block other workflows and/or prevent other parties from exercising choices on
their contracts.

As an example, consider the following scenario:

* Party `bank` is hosted on participant `P1` and party `alice` is hosted on participant `P2`.
* An active contract exists with `bank` as signatory and `alice` as observer.
* `P1` is decommissioned.

If `bank` is not multi-hosted, any attempt by `alice` to use the contract fails because
`bank` cannot confirm. The contract remains active on `P2` forever unless purged
via the repair service and only non-consuming choices and fetches can be committed.

Similar considerations apply if `P2` were to be decommissioned, even though `alice` is “only” an observer: if `alice`
is not multi-hosted, the contract would remain active on `P1` until purged via the repair service and only
non-consuming choices and fetches could be committed.

Additionally, when `P1` is decommissioned `P2` stops receiving ACS commitments from `P1`, which may prevent pruning.
The same applies in reverse if `P2` is decommissioned.

Thus, properly decommissioning a participant requires the following high-level steps:

1. *Ensuring that the prerequisites are met*: ensure that active contracts and workflows using them are not "stuck" due to parties required to operate on them becoming unavailable.

.. note::
   More specifically, for a contract action to be committed:

   - For “create” actions all stakeholders must be hosted on active participants.
   - For consuming “exercise” actions all stakeholders, actors, choice observers,
     and choice authorizers must be hosted on active participants.

   The definition of “informee” is covered by the :ref:`ledger privacy model <privacy>` section.

   The exact prerequisites to be met in order to decommission a participant therefore depend on the design
   of the Daml application and should be accounted and tested for in the initial Daml design process.

2. *Decommissioning*: remove the participant from the topology state.

After that, the participant can be disposed of.

Decommissioning a participant once the prerequisites are met
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. Stop applications from sending commands to the Ledger API of the participant to be decommissioned
   to avoid failed commands and errors.
#. Disconnect the participant to be decommissioned from all sync domains as described in 
   :ref:`enabling and disabling connections <connectivity_participant_reconnect>`.
#. Use the :ref:`sequencer.disable_member <sequencer.disable_member>` command to disable the participant
   being decommissioned in all sequencers and remove any sequencer data associated with it.
#. Use the :ref:`topology.participant_domain_states.authorize <topology.participant_domain_states.authorize>` command
   to remove the participant from the domain topology via the domain manager.

The following code snippet demonstrates the last two steps:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/ParticipantOffboardingIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: OffboardParticipant
   :end-before: user-manual-entry-end: OffboardParticipant
   :dedent:

.. _decommissioning-sequencers:

Decommissioning a Sequencer
---------------------------

Sequencers are part of a sync domain’s messaging infrastructure and do not store application contracts,
so they are disposable as long as precautions are taken to avoid disrupting the synchronization services.
This means, concretely, ensuring that:

#. No active participant nor active mediator is connected to the sequencer to be decommissioned.
#. All active participants and mediators are connected to an active sequencer.

After that, the sequencer can be decommissioned by removing it from the sync domain’s topology and finally disposed of.

Disconnecting all nodes from the sequencer to be decommissioned
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Change the sequencer connection on the mediators connected to the sequencer to be decommissioned
  to use another active sequencer, as per :ref:`mediator and domain manager connectivity <connectivity_mediator_and_domain_manager>`:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: SequencerOffboardingSwitchAwayMediator
   :end-before: user-manual-entry-end: SequencerOffboardingSwitchAwayMediator
   :dedent:

* Change the domain manager’s sequencer connection to another active sequencer, using the :ref:`sequencer_connection.set <sequencer_connection.set>` command:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: SequencerOffboardingSwitchAwayDomainManager
   :end-before: user-manual-entry-end: SequencerOffboardingSwitchAwayDomainManager
   :dedent:

* Reconnect participants to the sync domain, as described in :ref:`domain connectivity <participant_domain_connectivity>`, using a sequencer connectio
  to another active sequencer:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: SequencerOffboardingSwitchAwayParticipant
   :end-before: user-manual-entry-end: SequencerOffboardingSwitchAwayParticipant
   :dedent:

Decommissioning the sequencer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sequencers are part of the sync domain by virtue of having their node ID equal to the domain ID,
which also means they all have the same node ID. Since a sequencer’s identity is the same as the sync domain’s identity,
you should leave identity and namespace mappings intact.

However, a sequencer may use its own cryptographic material distinct from other sequencers.
In that case, owner-to-key mappings must be removed for the keys it exclusively owns:

#. Find the keys on the sequencer to be decommissioned using the :ref:`keys.secret.list <keys.secret.list>` command.
#. Among those keys, find the ones not shared by other sequencers. You can do this by issuing the :ref:`keys.secret.list <keys.secret.list>` command
   on each of them: the fingerprints that appear only on the sequencer node to be decommissioned
   correspond to its exclusively-owned keys.
#. Remove the mappings for its exclusively owned keys using the :ref:`topology.owner_to_key_mappings.authorize <topology.owner_to_key_mappings.authorize>`
   command.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: SequencerOffboardingRemoveExclusiveKeys
   :end-before: user-manual-entry-end: SequencerOffboardingRemoveExclusiveKeys
   :dedent:

Finally, the cryptographic material exclusively owned by a decommissioned sequencer must also be disposed of:

- If it was stored only on the decommissioned sequencer, it must be disposed of together with the decommissioned
  sequencer node.
- However, if a decommissioned sequencer’s cryptographic material is managed via a KMS system, it must be disposed of
  through the KMS; refer to your KMS’ documentation and internal procedures to handle this.
  KMS-managed cryptographic material of sequencer nodes.

.. _decommissioning-mediators:

Decommissioning a Mediator
--------------------------

Mediators are also part of a sync domain’s messaging infrastructure and do not store application contracts,
so they are disposable as long as precautions are taken to avoid disrupting the synchronization services.
This means ensuring that at least one mediator remains on the sync domain.

If other mediators exist on the sync domain, a mediator can be decommissioned using a single console command
:ref:`setup.offboard_mediator <setup.offboard_mediator>`.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/MediatorOffboardingIntegrationTest.scala
   :language: scala
   :start-after: user-manual-entry-begin: OffboardMediator
   :end-before: user-manual-entry-end: OffboardMediator
   :dedent:
