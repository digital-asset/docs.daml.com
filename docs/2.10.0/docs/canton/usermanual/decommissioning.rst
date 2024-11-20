..
   Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _decommissioning-nodes:

Decommissioning Canton Nodes
============================

This guide assumes general familiarity with Canton, in particular
:ref:`Canton identity management concepts <identity_management>` and
:ref:`operations from the Canton console`.

The focus is on how to decommission a Canton node. Note that, while onboarding new nodes is always possible,
a decommissioned node is effectively disposed of and cannot rejoin a domain anymore.
Decommissioning is thus an irreversible operation.

In addition, decommissioning procedures are currently experimental; regardless, backing up nodes to be decommissioned
before decommissioning them is strongly recommended.

.. _decommissioning-participants:

Decommission a Participant Node
===============================

Restrictions
------------

Operators need to be mindful that making a participant unavailable (by disconnecting it from the domain or
decommissioning it) might block other workflows and might prevent other parties from exercising choices on
their contracts.

As an example, consider the following scenario:

* Party `bank` is hosted on participant `P1` and party `alice` on participant `P2`.
* An active contract exists with `bank` as signatory and `alice` as observer.
* `P1` is decommissioned.

If `bank` is not multi-hosted, then any attempt of `alice` to use the contract will fail because
`bank` will not confirm. So the contract will remain active on `P2` forever unless purged
via the repair service and only non-consuming choices and fetches can be committed.

Similar considerations apply if `P2` were to be off-boarded, even though `alice` is “only” an observer: if `alice`
is not multi-hosted, the contract would remain active on `P1` until purged via the repair service and only
non-consuming choices and fetches could be committed.

Additionally, `P2` will stop receiving ACS commitments from `P1`, which may prevent pruning.
The same applies vice versa, if `P2` is decommissioned.

Thus, properly decommissioning a participant requires the following high-level steps:

#. Ensuring that the prerequisites are met: ensure that active contracts and workflows using them
   are not "stuck" due to parties required to operate on them becoming unavailable.
   .. note::
       More in detail, for a contract action to be committed, all the action "informees" must be hosted on the domain:
       - For “create” actions this means that all stakeholders must be hosted on active participants.
       - For consuming “exercise” actions this means that all stakeholders, actors, choice observers
         and choice authorizers must be hosted on active participants.
       The definition of “informee” is covered by the :ref:`ledger privacy model <ledger-privacy>` section.
       The correct procedure to perform this step depends thus on the specifics of Daml templates used
       in the Daml application and must consequently be designed, implemented and tested specifically for it.
#. Decommissioning: remove the participant from the topology state.

After that, the participant can be disposed of.

Detailed steps to decommission a participant once the prerequisites are met
---------------------------------------------------------------------------

#. Applications should stop sending commands to the Ledger API of the participant to be decommissioned
   in order to avoid failed commands and confusing errors in clients and in the participant’s logs.
#. Disconnect the participant to be decommissioned from all domains as described in the section about
   :ref:`enabling and disabling connections <connectivity-participant-reconnect>`.
#. Disable the participant to be decommissioned in all sequencers to remove any sequencer data associated with it;
   this can be done through the :ref:`sequencer.disable_member <TODO>` command.
#. Remove the participant to be decommissioned from the domain topology via the domain manager to ensure that
   it is not considered part of the domain anymore, so that it cannot rejoin nor interfere with the ACS
   (Active Contracts Set) commitments exchanged between participants.
   Use the :ref:`topology.participant_domain_states.authorize <TODO>` command to do that.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/ParticipantOffboardingIntegrationTest.scala
   :start-after: user-manual-entry-begin: OffboardParticipant
   :end-before: user-manual-entry-end: OffboardParticipant
   :dedent:

.. _decommissioning-sequencers:

Decommission a Sequencer Node
=============================

Sequencers are part of a synchronization domain’s messaging infrastructure and don’t store application contracts,
so they are disposable on condition that precautions are taken to avoid disrupting the synchronization services.
This means, concretely, ensuring that:

#. No active participant nor active mediator is connected to the sequencer node to be decommissioned.
#. All active participants and mediators are connected to an active sequencer node.

After that, the sequencer can be decommissioned by removing it from the domain’s topology and finally disposed of.

Disconnecting all nodes from the sequencer to be decommissioned
---------------------------------------------------------------

* Change the sequencer connection on the mediators connected to the sequencer to be decommissioned, so that
  they use another active sequencer, as per :ref:`mediator and domain manager connectivity <TODO>`.:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :start-after: user-manual-entry-begin: SequencerOffboardingSwitchAwayMediator
   :end-before: user-manual-entry-end: SequencerOffboardingSwitchAwayMediator
   :dedent:

* Change the domain manager’s sequencer connection to not use the sequencer to be decommissioned,
  but instead another active sequencer using the :ref:`sequencer_connection.set <TODO>` command.:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :start-after: user-manual-entry-begin: SequencerOffboardingSwitchAwayDomainManager
   :end-before: user-manual-entry-end: SequencerOffboardingSwitchAwayDomainManager
   :dedent:

* Reconnect participants to the domain, as described in :ref:`domain connectivity <TODO>`, using a sequencer connection
  that doesn’t point to the sequencer to be decommissioned, but instead uses another active sequencer:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :start-after: user-manual-entry-begin: SequencerOffboardingSwitchAwayParticipant
   :end-before: user-manual-entry-end: SequencerOffboardingSwitchAwayParticipant
   :dedent:

Decommissioning the sequencer after having disconnected all nodes
-----------------------------------------------------------------

Sequencers are part of the domain simply by virtue of having their node ID equal to the domain ID,
which also means they all have the same node ID. Since a sequencer’s identity is the same as the domain’s identity,
identity and namespace mappings should be left intact.

However, a sequencer node may use its own cryptographic material distinct from other sequencer nodes.
In that case, owner-to-key mappings must be removed for the keys it exclusively owns:

#. Find the keys on the sequencer to be decommissioned using the :ref:`key.secret.list <TODO>` command.
#. Among those keys, find the ones not shared by other sequencers by issuing the :ref:`key.secret.list <TODO>` command
  on each one of them: the fingerprints that appear only on the sequencer node to be decommissioned
  correspond to its exclusively owned keys.
#. Remove the mappings for its exclusively owned keys using the :ref:`topology.owner_to_key_mappings.authorize <TODO>`
  command.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/SequencerOffboardingIntegrationTest.scala
   :start-after: user-manual-entry-begin: SequencerOffboarding
   :end-before: user-manual-entry-end: SequencerOffboarding
   :dedent:

Finally, the cryptographic material exclusively owned by a decommissioned sequencer must also be disposed of:

* If it was stored only on the decommissioned sequencer node, it will have to be disposed of
  together with the decommissioned sequencer node.
* However, if a decommissioned sequencer’s cryptographic material is managed via a KMS system, it must be disposed of
  through the KMS; in that case, please refer to your KMS’ documentation and internal procedures to handle
  KMS-managed cryptographic material of sequencer nodes.

.. _decommissioning-mediators:

Decommission a Mediator Node
============================

Mediators are also of a synchronization domain’s messaging infrastructure and don’t store application contracts,
so they are disposable on condition that precautions are taken to avoid disrupting the synchronization services.
This means, concretely, ensuring that at least one mediator remains on the domain.

If other mediators exist on the domain, a mediator can be decommissioned using a single console command
:ref:`setup.offboard_mediator <TODO>`.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/offboarding/MediatorOffboardingIntegrationTest.scala
   :start-after: user-manual-entry-begin: OffboardMediator
   :end-before: user-manual-entry-end: OffboardMediator
   :dedent:
