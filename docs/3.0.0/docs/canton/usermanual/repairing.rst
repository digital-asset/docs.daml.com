..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

Repairing Nodes
===============

The Canton platform is generally built to self-heal and automatically recover from issues.
As such, if there is a situation where some degradation can be expected, there exists
a mechanism that yields graceful degradation and automated recovery from said issues.

Common examples are database outages (retry until success) or network outages (failover
and reconnect until success).

Canton reports such issues as warnings to alert the operator about the degradation of
its dependencies, but generally, does not require any manual intervention to recover from
a degradation.

However, not all situations can be foreseen and corruption of systems can
always happen in unanticipated ways. Therefore,
Canton can always be manually repaired. This means that
whatever the corruption is, there is always a series of operational steps that can be made in
order to recover the correct state of a node.
If several nodes in the distributed system are affected,
it may be necessary to coordinate the recovery among the affected nodes.

Conceptually, this means that Canton recovery is structured along the four layers:

  1. Automated self-recovery and self-healing.
  2. Recovery from crash or restart by re-creating a consistent state from the persisted store.
  3. Standard disaster recovery from a database backup in case of database outage and replay
     from domain.
  4. Corruption disaster recovery using repair and other console commands to re-establish a
     consistent state within the distributed system.

If you run into corruption issues, you need to first understand what caused the issue.
Ideally, you can contact our support team to help you diagnose the issue and provide you
with a custom recipe on how to recover from your issue (and prevent recurrence).

The toolbox the support engineers have at hand are:

- Exporting / importing secret keys
- Manually initializing nodes
- Exporting / importing DARs
- Exporting / importing topology transactions
- Manually adding or removing contracts from the active contract set
- Moving contracts from one domain to another
- Manually ignoring faulty transactions (and then using add / remove contract to repair the ACS).

All these methods are very powerful but dangerous. You should not attempt to repair your nodes on
your own as you risk severe data corruption.

Keep in mind that the corruption of the system state may not have been discovered immediately; thus, the corruption may
have leaked out through the APIs to the applications using the corrupted node.
Bringing the node back into a correct state with respect to the other nodes in the distributed system can
therefore make the application state inconsistent with the node's state. Accordingly, the application
should either re-initialize itself from the repaired state or itself offer tools to fix inconsistencies.

.. _repairing-participants:

Repairing Participants
----------------------

Canton enables interoperability of distributed `participants <https://docs.daml.com/concepts/glossary.html#participant-node>`__
and `domains <https://docs.daml.com/concepts/glossary.html#domain>`__.
Particularly in distributed settings without trust assumptions, faults in one part of the system should ideally produce
minimal irrecoverable damage to other parts.
For example if a domain is irreparably lost, the participants previously connected to that domain need to recover and be
empowered to continue their workflows on a new domain.

This guide will illustrate how to replace a lost domain with a new domain providing business continuity to affected
participants.

Recovering from a Lost Domain
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  .. _recovering_from_lost_domain:

.. note::
    Please note that the given section describes a preview feature, due to the fact that using
    multiple domains is only a preview feature.

Suppose that a set of participants have been conducting workflows via a domain that runs into trouble. In fact consider
that the domain has gotten into such a disastrous state that the domain is beyond repair, for example:

- The domain has experienced data loss and is unable to be restored from backups or the backups are missing crucial
  recent history.
- The domain data is found to be corrupt causing participants to lose trust in the domain as a mediator.

Next the participant operators each examine their local state, and upon coordinating conclude that their participants'
active contracts are "mostly the same". This domain-recovery repair demo illustrates how the participants can

- coordinate to agree on a set of contracts to use moving forward, serving as a new consistent state,
- copying over the agreed-upon set of contracts to a brand new domain,
- "fail over" to the new domain,
- and finally continue running workflows on the new domain having recovered from the permanent loss of the old domain.

Repairing an actual Topology
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
To follow along with this guide, ensure you have :ref:`installed and unpacked the Canton release bundle <installation>`
and run the following commands from the "canton-X.Y.Z" directory to set up the initial topology.

.. code-block:: bash

    export CANTON=`pwd`
    export CONF="$CANTON/examples/03-advanced-configuration"
    export REPAIR="$CANTON/examples/07-repair"
    bin/canton \
      -c $REPAIR/participant1.conf,$REPAIR/participant2.conf,$REPAIR/domain-repair-lost.conf,$REPAIR/domain-repair-new.conf \
      -c $CONF/storage/postgres.conf,$REPAIR/enable-preview-commands.conf \
      --bootstrap $REPAIR/domain-repair-init.canton

To simplify the demonstration, this not only sets up the starting topology of

- two participants, "participant1" and "participant2", along with
- one domain "lostDomain" that is about to become permanently unavailable leaving "participant1" and "participant2"
  unable to continue executing workflows,

but also already includes the ingredients needed to recover:

- The setup includes "newDomain" that we will rely on as a replacement domain, and
- we already enable the "enable-preview-commands" configuration needed to make available the "repair.change_domain"
  command.

In practice you would only add the new domain once you have the need to recover from domain loss and also only then
enable the repair commands.

We simulate "lostDomain" permanently disappearing by stopping the domain and never bringing it up again to emphasize
the point that the participants no longer have access to any state from domain1.
We also disconnect "participant1" and "participant2" from "lostDomain" to reflect that the participants have "given up"
on the domain and recognize the need for a replacement for business continuity.
The fact that we disconnect the participants "at the same time" is somewhat artificial as in practice the participants
might have lost connectivity to the domain at different times (more on reconciling contracts below).

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/repair/DomainRepairIntegrationTest.scala
   :start-after: user-manual-entry-begin: ConsiderDomainBroken
   :end-before: user-manual-entry-end: ConsiderDomainBroken
   :dedent:

.. https://app.lucidchart.com/documents/edit/e2a390cf-bef7-4d27-b10c-ca78d02624e3/0_0
.. figure:: images/repair-lost-domain.svg
     :alt: "lostDomain" has become unavailable and neither participant can connect anymore

Even though the domain is "the node that has broken", recovering entails repairing the participants using the
"newDomain" already set up.
As of now, participant repairs have to be performed in an offline fashion requiring participants being repaired to be
disconnected from the the new domain. However we temporarily connect to the domain, to let the topology state
initialize, and disconnect only once the parties can be used on the new domain.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/repair/DomainRepairIntegrationTest.scala
   :start-after: user-manual-entry-begin: InitializeIdentityStateAndDisconnect
   :end-before: user-manual-entry-end: InitializeIdentityStateAndDisconnect
   :dedent:

With the participants connected neither to "lostDomain" nor "newDomain", each participant can

- locally look up the active contracts assigned to the lost domain using the "testing.pcs_search" command made
  available via the "features.enable-testing-commands" configuration,
- and invoke "repair.change_domain" (enabled via the "features.enable-preview-commands" configuration) in order to
  "move" the contracts to the new domain.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/repair/DomainRepairIntegrationTest.scala
   :start-after: user-manual-entry-begin: ChangeContractsDomain
   :end-before: user-manual-entry-end: ChangeContractsDomain
   :dedent:

.. note::

    The code snippet above includes a check that the contracts shared among the participants match (as determined by
    each participant, "sharedContracts1" by "participant1" and "sharedContracts2" by "participant2).
    Should the contracts not match (as could happen if the participants had lost connectivity to the domain at
    different times), this check fails soliciting the participant operators to reach an agreement on the set of contracts.
    The agreed-upon set of active contracts may for example be

    - the intersection of the active contracts among the participants
    - or perhaps the union (for which the operators can use the "repair.add" command to create the contracts missing
      from one participant).

    Also note that both the repair commands and the "testing.pcs_search" command are currently "preview" features, and
    therefore their names may change.

Once each participant has associated the contracts with "newDomain", let's have them reconnect, and we should be able
to confirm that the new domain is able to execute workflows from where the lost domain disappeared.

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/repair/DomainRepairIntegrationTest.scala
   :start-after: user-manual-entry-begin: VerifyNewDomainWorks
   :end-before: user-manual-entry-end: VerifyNewDomainWorks
   :dedent:

.. https://app.lucidchart.com/documents/edit/f8f60027-3539-4d56-b1b7-060a4754dcd4/0_0
.. figure:: images/repair-new-domain.svg
     :alt: "newDomain" has replaced "lostDomain"

In practice, we would now be in a position to remove the "lostDomain" from both participants and to disable the repair
commands again to prevent accidental use of these "dangerously powerful" tools.

This guide has demonstrated how participants can recover from losing a domain that has been permanently lost or somehow
become irreparably corrupted.


Repair Macros
-------------

Some operations are combined as macros, which are a series of consecutive repair commands,
coded as a single command. While we discourage you from using these commands on your own,
we document them here for the sake of completeness.
These macros are available only in the enterprise edition.

Clone Identity
~~~~~~~~~~~~~~

Many nodes can be rehydrated from a domain, as long as the domain is not pruned. In such situations,
you might want to reset your node while keeping the identity and the secret keys of the node.
This can be done using the repair macros.

You need local console access to the node. If you are running your production node in a container,
you need to create a new configuration file that allows you to access the database of the node
from an interactive console. Make sure that the normal node process is stopped and that nothing else
is accessing the same database (e.g. ensure that replication is turned on). Also, make sure that
the nodes are configured to not perform auto-initialization, as this would create a new identity.
You ensure that by setting the corresponding auto-init configuration option to false:

.. code-block:: bash

    canton.participants.myparticipant.init.auto-init = false

Then start Canton interactively using:

.. code-block:: bash

    ./bin/canton -c myconfig --manual-start

Starting with ``--manual-start`` will prevent the participant to attempt to reconnect to the domains.
Then, you can download the identity state of the node to a directory on the machine you are running the
process:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RepairMacroCloneIdentityDownload
   :end-before: architecture-handbook-entry-end: RepairMacroCloneIdentityDownload
   :dedent:

This will store the secret keys, the topology state and the identity onto the disk in the given directory.
You can run the ``identity.download`` command on all nodes. However, mediator and sequencer
nodes will only store their keys in files, as the sequencer's identity is attached to the domain identity
and the mediator's identity is set only later during initialization.

The ``dars.download`` command is a convenience command to download all dars that have been
added to the participant via the console command ``participant.dars.upload``. Dars that
were uploaded through the Ledger API need to be manually re-uploaded to the new participant.

Once the data is stored, stop the node and then truncate the database (please back it up
before). Then restart the node and upload the identity data again:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RepairMacroCloneIdentityUpload
   :end-before: architecture-handbook-entry-end: RepairMacroCloneIdentityUpload
   :dedent:

Please note that dar uploading is only necessary for participants.

Now, depending on the node type, you need to re-integrate the node into the domain. For the
domain nodes, you need to grab the static domain parameters and the domain id from the
domain manager. If you have remote access to the domain manager, you can run

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RehydrationGrabInitData
   :end-before: architecture-handbook-entry-end: RehydrationGrabInitData
   :dedent:

You also want to grab the mediator identities for each mediator using:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RehydrationGrabMediatorId
   :end-before: architecture-handbook-entry-end: RehydrationGrabMediatorId
   :dedent:

For the sequencer, rehydration works only if the domain uses a blockchain;
the database-only sequencers cannot rehydrate. So rehydration for blockchain-based sequencers will be:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RehydrationSequencer
   :end-before: architecture-handbook-entry-end: RehydrationSequencer
   :dedent:

For the domain manager, it looks like:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RehydrationDomainManager
   :end-before: architecture-handbook-entry-end: RehydrationDomainManager
   :dedent:

For the mediator, it would be:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RehydrationMediator
   :end-before: architecture-handbook-entry-end: RehydrationMediator
   :dedent:

For a participant, you would reconnect it to the domain using a normal connect:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/sequencer/RehydrationIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: RepairMacroCloneIdentityConnect
   :end-before: architecture-handbook-entry-end: RepairMacroCloneIdentityConnect
   :dedent:

Note that this will replay all transactions from the domain. However, command deduplication
will only be fully functional once the participant catches up with the domain. Therefore, you
need to ensure that applications relying on command deduplication do not submit commands
during recovery.
