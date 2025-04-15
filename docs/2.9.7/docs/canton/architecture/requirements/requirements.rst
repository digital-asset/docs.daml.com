..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _requirements:

##############################
Canton High-Level Requirements
##############################

As detailed in the :ref:`DA ledger model <da-ledgers>`, the Daml ledger interoperability protocol
provides parties with a *virtual shared ledger*, which
contains their interaction history and the current state of their shared Daml contracts. To access
the ledger, the parties must deploy (or have someone deploy for them)
the so-called *participant nodes*. The participant nodes then expose
the *Ledger API*, which enables the parties to request changes
and get notified about the changes to the ledger. To apply the
changes, the participant nodes run a synchronization protocol.
We can visualize the setup as follows.

.. https://www.lucidchart.com/documents/edit/a8b76352-e58a-4a9b-b7a5-f671164d0a97
.. image:: ./images/da-ledger-architecture.svg
   :width: 100%
   :align: center

In general, the setup might be more complicated than shown above, as a single participant node can
provide services for more than one party and parties can be hosted on multiple participant nodes.
Note, however, that this feature is currently limited. In particular, a party hosted on multiple
participants should be on-boarded on all of them before participating to any transaction.

In this section, we list the high-level functional requirements on
the Ledger API, as well as non-functional requirements on the
synchronization protocol.

..
    Subsequent sections then:

      #. detail the :ref:`design <architecture-in-depth>` of our Ledger
         API implementation, including the detailed :ref:`system model and
         the trust assumptions <system-model-and-trust-assumptions>` of one
         of the implementations.

      #. perform an :ref:`analysis <requirements-analysis>` of how the
         implementation satisfies the requirements.

.. _requirements-functional:

Functional requirements
-----------------------

Functional requirements specify the constraints on and between the system's
observable outputs and inputs.  A difficulty in
specifying the requirements for the synchronization service is that the system and
its inputs and outputs are distributed, and that the system can
include **Byzantine** participant nodes, i.e., participants that are
malicious, malfunctioning or compromised. The system
does not have to give any guarantees to parties using such nodes, beyond the ability to
recover from malfunction/compromise. However, the system must protect the
**honestly represented parties** (i.e., parties all of whose participant nodes implement the
synchronization service correctly) from malicious behavior. To account for this in our
requirements, we exploit the fact that the conceptual
purpose of the ledger synchronization service is to provide parties
with a virtual shared ledger and we:

  #. use such a shared ledger and the associated properties (described in
     the :ref:`DA ledger model <da-ledgers>`) to constrain the
     input-output relation;

  #. express all requirements from the perspective of an honestly represented party;

  #. use the same shared ledger for all parties and requirements,
     guaranteeing synchronization.

We express the high-level functional requirements as user stories,
always from the perspective of an honestly represented party, i.e., Ledger API user, and
thus omit the role. As the observable inputs and outputs, we take the
Ledger API inputs and outputs. Additionally, we assume that crashes and recoveries of
participant nodes are observable.
The requirements ensure that the virtual shared ledger describes a world
that is compatible with the honestly represented parties' perspectives,
but it may deviate in any respect from what Byzantine nodes present to their parties.
We call such parties **dishonestly represented parties**.

Some requirements have explicit exceptions and design limitations.
Exceptions are fundamental, and cannot be improved on by further
design iterations.
Design limitations refer to the design of the Canton synchronization protocol and can be improved in future versions.
We discuss the consequences of the most important exceptions
and design limitations :ref:`later in the section
<requirements-exceptions>`.

.. note::

   The fulfillment of these requirements is conditional on the
   system's assumptions
   (in particular, any trusted participants must behave correctly).

   ..
      :ref:`system's assumptions <system-model-and-trust-assumptions>`

   ..
      |ContractKeySymbolInfo|

.. _synchronization-hlreq:

* **Synchronization**. I want the platform to provide a
  virtual ledger (according to the :ref:`DA ledger model
  <da-ledgers>`) that is shared with all other parties in the system
  (honestly represented or not), so that I stay synchronized with my counterparties.

  .. _change-requests-possible-hlreq:

* **Change requests possible**. I want to be able to submit change
  requests to the shared ledger.

  .. _change-request-identification-hlreq:

* **Change request identification**. I want to be able to assign an
  identifier to all my change requests.

  .. _change-request-deduplication-hlreq:

* **Change request deduplication**. I want the system to deduplicate
  my change requests with the same identifiers, if they are submitted
  within a time window configurable per participant, so that my applications
  can resend change requests in case of a restart without adding the
  changes to the ledger twice.

  .. _bounded-decision-time-hlreq:

* **Bounded decision time**. I want to be able to learn within some
  bounded time from the submission (on the order of minutes) the decision about my change request,
  i.e., whether it was added to the ledger or not.

  **Design limitation**: If the participant node used for the
  submission crashes, the bound can be exceeded. In this case the application
  should fail over to another participant replica.

  .. _consensus-hlreq:

* **Consensus**. I want that all honestly represented counterparties come to the
  same conclusion of either accepting or rejecting a transaction according to
  the :ref:`DA ledger model <da-ledgers>`.

  .. _transparency-hlreq:

* **Transparency**. I want to get notified in a timely fashion (on the
  order of seconds) about the changes to my :ref:`projection of the
  shared ledger <da-model-projections>`, according to the DA ledger
  model, so that I stay synchronized with my counterparties.

  **Design limitation**: If the participant has crashed, is overloaded, or in case of network failures, the bound can be
  exceeded. In the case of a crash the application should fail over to another
  participant replica.

  **Design limitation**: If the submitter node is malicious it can encrypt the
  transaction payload with the wrong key that my participant cannot decrypt it.
  I will be notified about a transaction but able to see its contents.

  .. _integrity-validity-hlreq:

* **Integrity: ledger validity**. I want the shared ledger to be :ref:`valid according to
  the DA ledger model <da-model-integrity>`.

  ..
     .. note::
        For :ref:`contract keys <contract-key-integrity>`, validity includes key uniqueness, key assertion validity, and key authorization.

  .. _integrity-validity-hlreq-consistency-exception:

  **Exception**: The :ref:`consistency <da-model-consistency>` aspect
  of the validity requirement on the shared ledger can be violated for
  contracts with no honestly represented signatories, even if I am an observer on the contract.

  ..
     **Exception 2**: The aspects :ref:`key uniqueness <contract-key-uniqueness>` and :ref:`key assertion validity <contract-key-assertion-validity>`
     of the validity requirement on the shared ledger can be violated for
     keys with no honestly represented maintainers, even if I am a non-maintainer stakeholder of contracts with that key.

  .. _integrity-authenticity-hlreq:

* **Integrity: request authenticity**.
  I want the shared ledger to contain a record
  of a change with me as one of the requesters if and only if:

  1. I actually requested that exact change,
     i.e., I submitted the change via the command submission service, and
  2. I am notified that my change request was added to the shared ledger, unless my participant node crashes forever,

  so that, together with the ledger validity requirement, I can be
  sure that the ledger contains no records of:

  1. obligations imposed on me,
  2. rights taken away from me, and
  3. my counterparties removing their existing obligations

  without my explicit consent.
  In particular, I am the only requester of any such change.
  Note that this requirement implies that the change is done atomically,
  i.e. either it is added in its entirety, or not at all.

  **Remark:**
  As functional requirements apply only to honestly represented parties,
  any dishonestly represented party can be a requester of a commit on the virtual shared ledger,
  even if it has never submitted a command via the command submission service.
  However, this is possible only if **no** requester of the commit is honestly represented.

  .. note::
     The two integrity requirements come with further limitations and trust assumptions, whenever the
     :ref:`trust-liveness trade-offs <configurable-trust-liveness-trade-off-hlreq>` below are used.

  .. _non-repudiation-hlreq:

* **Non-repudiation**. I want the service to provide me with
  irrefutable evidence of all ledger
  changes that I get notified about, so that I can prove to a third
  party (e.g., a court) that a contract of which I am a stakeholder was
  created or archived at a certain point in time.

  This item is scheduled on the Daml roadmap.

  .. todo::
     #. `Ledger evidence for Non-repudiation <https://github.com/DACH-NY/canton/issues/158>`_.

  .. _finality-hlreq:

* **Finality**. I want the shared ledger to be append-only, so that, once I am
  notified about a change to the ledger, that change cannot be removed from the ledger.

  .. _Daml-package-uploads-hlreq:

* **Daml package uploads**. I want to be able to upload a new Daml
  package to my participant node, so that I can start using new Daml
  contract templates or upgraded versions of existing ones. The
  authority to upload packages can be limited to particular parties
  (e.g., a participant administrator party), or done through a
  separate API.

  .. _Daml-package-notification-hlreq:

* **Daml package notification**. I want to be able to get notified about new
  packages distributed to me by other parties in the system, so that I
  can inspect the contents of the package, either automatically or
  manually.

  .. _automated-Daml-package-distribution-hlreq:

* **Automated Daml package distribution**. I want the system to be able to
  notify counterparties about my uploaded Daml packages before the first
  time that I submit a change request that includes a contract that
  both comes from this new package and has the counterparty as a
  stakeholder on it.

  **Limitation** The package distribution does not happen automatically on first
  use of a package, because manual (:ref:`Daml package vetting
  <Daml-package-vetting-hlreq>`) would lead to a rejection of the transaction.

  .. _Daml-package-vetting-hlreq:

* **Daml package vetting**. I want to be able to explicitly approve
  (manually or automatically, e.g., based on a signature by a trusted
  party) every new package sent to me by another party, so that the
  participant node does not execute any code that has not been
  approved. The authority to vet packages can be limited to particular
  parties, or done through a separate API.

  **Exception**: I cannot approve a package without approving all of
  its dependencies first.

  .. _no-unnecessary-rejections-hlreq:

* **No unnecessary rejections**. I want the system to add all my well-authorized
  and Daml-conformant change requests to the ledger, unless:

    #. they are duplicated, or
    #. they use Daml templates my counterparties' participants have not vetted, or
    #. they conflict with other changes that are included in the
       shared ledger prior to or at approximately the same time as my request, or
    #. the processing capacity of my participant node or the participant
       nodes of my counterparties is exhausted by
       other change requests submitted by myself or others roughly
       simultaneously,

  in which case I want the decision to include the appropriate reason
  for rejection.

  **Exception 1**: This requirement may be violated whenever my
  participant node crashes, or if there is contention in the system
  (multiple conflicting requests are issued in a short period of time).
  The rejection reason reported
  in the decision in the exceptional case must differ from those
  reported because of other causes listed in this requirement.

  **Exception 2**: If my change request contains an exercise on a contract identifier, and I have not witnessed
  (e.g., through :ref:`divulgence <da-model-divulgence>`) any actions on a contract with this identifier in my
  :ref:`projection of the shared ledger <da-model-projections>` (according to the DA ledger model), then my change
  request may fail.

  **Design limitation 1**: My change requests can also be rejected if
  a participant of some counterparty (hosting a signatory or an observer) in my change request is
  crashed, unless some trusted participant (e.g., one run by a market operator) is a
  stakeholder participant on all contracts in my change request.

  **Design limitation 2**: My change requests can also be rejected if
  any of my counterparties in the change request is Byzantine, unless
  some trusted participant (e.g., one run by a market operator) is a stakeholder participant on
  all contracts in my change request.

  **Design limitation 3**: If the underlying sequencer queue is full
  for a participant, then we can get an unnecessary rejection. We assume
  however that the queue size is so large that it can be considered to be
  infinite, so this unnecessary rejection doesn't happen in practice, and
  the situation would be resolved operationally before the queue fills up.

  **Design limitation 4**: If the mediator of the sync domain has crashed and lost
  the in-flight transaction, which then times out.

  .. todo::
    #. `Referee for algorithmic dispute resolution <https://github.com/DACH-NY/canton/issues/191>`_
    #. `Improved Fairness <https://github.com/DACH-NY/canton/issues/194>`_.

  ..
     **Design limitation 5**:
     My change request can be rejected if I am not a maintainer of all keys
     that must be looked up to execute my change request.
     This includes lookups that determine that there is no active contract for a key.

  .. _seek-support-for-notifications-hlreq:

* **Seek support for notifications**. I want to be able to receive
  notifications (about ledger changes and about the decisions on
  my change requests) only from a particular known offset, so that I can
  synchronize my application state with the set of active contracts on
  the shared ledger after crashes and other events, without having to
  read all historical changes.

  **Exception**: A participant can define a bound on how far in the
  past the seek can be requested.

  .. _active-contract-snapshots-hlreq:

* **Active contract snapshots**. I want the system to provide me a way
  to obtain a recent (on the order of seconds) snapshot of the set of
  active contracts on the shared ledger, so that I can initialize my
  application state and synchronize with the set of active contracts
  on the ledger efficiently.

  .. _request-processing-limited-to-participants-hlreq:

* **Change request processing limited to participant nodes**. I want only the following (and no other) functionality
  related to change request processing:

  #. submitting change requests
  #. receiving information about change request processing and results
  #. (possibly) vetting Daml packages

  to be exposed on the Ledger API, so that the unavailability of my or my counterparties' applications
  cannot influence whether a change I previously requested through the API is included in the shared ledger, except if
  the request is using packages not previously vetted.
  Note that this inclusion may still be influenced by the availability of my counterparties' participant nodes (as
  specified in the limitations on the :ref:`requirement on no unnecessary rejections <no-unnecessary-rejections-hlreq>`)

Resource limits
---------------

This section specifies upper bounds on the sizes of data structures.
The system must be able to process data structures within the given size limits.

If a data structure exceeds a limit, the system must reject transactions containing the data structure.
Note that it would be impossible to check violations of resource limits at compile time;
therefore the Daml compiler will not emit an error or warning if a resource limit is violated.

**Maximum transaction depth:** 100

  **Definition:** The maximum number of levels (except for the top-level) in a transaction tree.

  **Example:** The following transaction has a depth of 2:

  .. image:: ./images/action-structure-paint-offer.svg
     :align: left
     :width: 70%

  **Purpose:** This limit is to mitigate the higher cost of implementing stack-safe algorithms on transaction trees.
  The limit may be relaxed in future versions.

**Maximum depth of a Daml value:** 100

  **Definition:** The maximum numbers of nestings in a Daml value.

  **Example:**

  - The value "17" has a depth of 0.
  - The value "{myField: 17}" has a depth of 1.
  - The value "[{myField: 17}]" has a depth of 2.
  - The value "['observer1', 'observer2', ..., 'observer100']" has a depth of 1.

  **Purpose:**

  1. Applications interfacing the DA ledger likely have to process Daml values and likely are developed outside of DA.
     By limiting the depth of Daml values, application developers have to be less concerned about stack usage of their
     applications.
     So the limit effectively facilitates the development of applications.

  #. This limit allows for a readable wire format for Daml-LF values,
     as it is not necessary to flatten values before transmission.

.. _requirements-nonfunctional:

Non-functional requirements
---------------------------

These requirements specify the characteristics of the internal system
operation. In addition to the participant nodes, the implementation of
the synchronization protocol may involve a set of additional
operational entities. For example, this set can include a sequencer.
We call a single deployment of such a set of operational
entities a **sync domain**, and refer to the entities as **sync domain
entities**.

As before, the requirements are expressed as user stories, with the user always
being the Ledger API user. Additionally, we list specific requirements for
financial market infrastructure providers. Some requirements have explicit
exceptions; we discuss the consequences of these exceptions :ref:`later in the
section <requirements-exceptions>`.

.. _privacy-hlreq:

* **Privacy**. I want the visibility of the ledger contents to be
  restricted according to the :ref:`privacy model of DA ledgers
  <da-model-privacy>`, so that the information about any (sub)action
  on the ledger is provided only to participant nodes of parties privy
  to this action. In particular, other participant nodes must not receive
  any information about the action, not even in an encrypted form.

  **Exception**: Sync domain entities operated by trusted third parties
  (such as market operators) may receive encrypted versions of any of
  the ledger data (but not plain text).

  **Design limitation 1**: Participant nodes of parties privy to an
  action (according to the ledger privacy model) may learn the following:

  * How deeply the action lies within a ledger commit.

  * How many sibling actions each parent action has.

  * The transaction identifiers (but not the transactions' contents)
    that have created the contracts used by the action.

  **Design limitation 2**: Sync domain entities operated by trusted third
  parties may learn the hierarchical structure and stakeholders of all
  actions of the ledger (but none of the contents of the contracts,
  such as templates used or their arguments).

  .. todo::
    #. `Mediator Free Synchronization <https://github.com/DACH-NY/canton/issues/195>`_.

  .. _transaction-stream-auditability-hlreq:

* **Transaction stream auditability**. I want the system to be able to
  convince a third party (e.g., an auditor) that they have been
  presented with my complete transaction stream within a configurable
  time period (on the order of years), so that they can be
  sure that the stream represents a complete record of my ledger
  projection, with no omissions or additions.

  **Exception**: The evidence can be linear in the size of my
  transaction stream.

  **Design limitation**: The evidence need not be privacy-preserving
  with respect to other parties with whom I share participant nodes,
  and the process can be manual.

  This item is scheduled on the Daml roadmap.

  .. todo::
    #. `Transaction stream auditability <https://github.com/DACH-NY/canton/issues/215>`_.

.. _service-auditability-hlreq:

* **Service Auditability**. I want the synchronization protocol
  implementation to store all requests and responses of all participant
  nodes within a configurable time period (on the order of years), so that
  an independent third party can manually audit the correct behavior of any
  individual participant and ensure that all requests and responses it sent comply
  with the protocol.

  **Remarks** The system operator has to make a trade-off between preserving
  data for auditability and deleting data for system efficiency (see
  :ref:`Pruning <pruning-hlreq>`).

  This item is scheduled on the Daml roadmap.

  .. todo::
    #. `Participant node audit tool <https://github.com/DACH-NY/canton/issues/162>`_
    #. `Mediator audit tool <https://github.com/DACH-NY/canton/issues/164>`_

.. _gdpr-compliance-hlreq:

* **GDPR Compliance**. I want the system to be compliant with the General Data
  Protection Regulation (GDPR).

  .. todo::
    #. `GDPR Compliance <https://github.com/DACH-NY/canton/issues/157>`_

.. _configurable-trust-liveness-trade-off-hlreq:

* **Configurable trust-liveness trade-off**. I want each sync domain to
  allow me to choose from a predefined (by the sync domain) set of trade-offs
  between trust and liveness for my change requests, so that my change
  requests get included in the ledger even if some of the participant nodes
  of my counterparties are offline or Byzantine, at the expense of
  making additional trust assumptions: on (1) the sync domain entities (for
  privacy and integrity), and/or (2) participant nodes run by
  counterparties in my change request that are marked as "VIP" by
  the sync domain (for integrity), and/or (3) participant nodes run by other counterparties
  in my change request (also for integrity).

  **Exception**: If the honest and online participants do not
  have sufficient information about the activeness of the contracts
  used by my change request, the request can still be rejected.

  **Design limitation**: The only trade-off allowed by the current design is through confirmation policies.
  Currently, the only fully supported policies are the full, signatory, and VIP confirmation policies.
  The implementation does not support the serialization of other policies.
  Furthermore, integrity need not hold under other policies.
  This corresponds to allowing only the trade-off (2) above (making additional trust assumptions on VIP participants).
  In this case, the VIP participants must be trusted.

  ..
     :ref:`confirmation policies  <sirius-overview-confirmation-response>`.

  .. todo::
    #. `Attestator for Liveness <https://github.com/DACH-NY/canton/issues/186>`_.

  **Note**: If a participant is trusted, then the trust assumption
  extends to all parties hosted by the participant.
  Conversely, the system does not support to trust a participant for the actions
  performed on behalf of one party and distrust the same participant for the
  actions performed on behalf of a different party.

  .. _workflow-isolation-hlreq:

* **Workflow isolation**. I want the system to be built such that
  workflows (groups of change requests serving a particular business
  purpose) that are independent, i.e. do not conflict with other, do
  not affect each other's performance.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Priority based Basic Capacity Management <https://github.com/DACH-NY/canton/issues/179>`_
    #. `Quota based Advanced Capacity Management <https://github.com/DACH-NY/canton/issues/192>`_.

.. _pruning-hlreq:

* **Pruning**. I want the system to provide data pruning
  capabilities, so that the required hot storage capacity
  for each participant node depends only on:

    #. the size of currently active contracts whose processing the node is involved in,
    #. the node's past traffic volume within a (per-participant) configurable time window

  and does not otherwise grow unboundedly as the system continues
  operating. Cold storage requirements are allowed to keep growing
  continuously with system operation, for auditability purposes.

  .. _multi-domain-participant-nodes-hlreq:

* **Multi-sync-domain participant nodes**. I want to be able to use
  multiple sync domains simultaneously from the same participant node.

  This item is only delivered in an experimental state and scheduled on the
  roadmap for GA.

  .. _internal-participant-node-domain-hlreq:

* **Internal participant node sync domain**. I want to be able to use
  an internal sync domain for workflows involving only local parties
  exclusively hosted by the participant node.

  This item is scheduled on the roadmap.

  .. _connecting-to-domains-hlreq:

* **Connecting to sync domain**. I want to be able to connect my participant
  node to a new sync domain at any point in time, as long as I am accepted
  by the sync domain operators.

  **Exception** If the participant has been connected to a sync domain with unique
  contract key mode turned on, then connecting to another sync domain is forbidden.

  .. _workflow-transfer-hlreq:

* **Workflow transfer**. I want to be able to transfer the processing
  of any Daml contract that I am a stakeholder of or have delegation
  rights on, from one sync domain to another sync domain that has been
  vetted as appropriate by all contract stakeholders through some
  procedure defined by the synchronization service, so that I can use
  sync domains with better performance, do load balancing and
  disaster recovery.

  .. _workflow-composability-hlreq:

* **Workflow composability**. I want to be able to atomically execute
  steps (Daml actions) in different workflows across different sync domains, as long as
  there exists a single sync domains to which all participants in all
  workflows are connected.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Atomic Multi-Sync-Domain Transactions <https://github.com/DACH-NY/canton/issues/167>`_.

.. _standards-compliant-cryptography-hlreq:

* **Standards compliant cryptography**. I want the system to be built
  using configurable cryptographic primitives approved by standardization
  bodies such as NIST, so that I can rely on existing audits and hardware
  security module support for all the primitives.

.. _secure-private-keys-hlreq:

* **Secure storage of cryptographic private keys**. I want the system to store
  cryptographic private keys in a secure way to prevent unauthorized access to
  the keys.

  .. _upgradability-hlreq:

* **Upgradability**. I want to be able to upgrade system components,
  both individually and jointly, so that I can deploy fixes and
  improvements to the components and the protocol without stopping the
  system's operation.

  **Design Limitation 1** When a sync domain needs to be upgraded to a new protocol
  version a new sync domain is deployed and the participants migrate the active
  contracts' synchronization to the new sync domain.

  **Design Limitation 2** When a replicated node needs to be upgraded, all
  replicas of the node need to be upgraded at the same time.

  .. todo::
    #. `Upgradability <https://github.com/DACH-NY/canton/issues/169>`_.

.. _semantic-versioning-hlreq:

* **Semantic versioning**. I want all interfaces, protocols and
  persistent data schemas to be versioned, so that version mismatches
  are prevented. The versioning scheme must be semantic, so that
  breaking changes always bump the major versions.

  **Remark** Every change in the Canton protocol leads to a new major version of
  the protocol, but a Canton node can support multiple protocols without
  requiring a major version change.

  ..
     .. _backwards-forwards-protocol-compatibility-major-version-hlreq:

   * **Backwards and forward protocol compatibility within a major
     version**. I want system components supporting the same major
     version of the protocol to be able to communicate seamlessly.

  .. _domain-approved-protocol-versions-hlreq:

* **Synch domain approved protocol versions**. I want sync domains to specify the
  allowed set of protocol versions on the sync domain, so that old versions
  of the protocol can be decommissioned, and new versions can be
  introduced and rolled back if operational problems are discovered.

  **Design limitation**: Initially, the sync domain can specify only a
  single protocol version as allowed, which can change over time.

  .. _multiple-protocol-compatibility-hlreq:

* **Multiple protocol compatibility**. I want new versions of system components
  to still support at least one previous major version of the synchronization
  protocol, so that entities capable of using newer versions of the protocol can
  still use sync domains that specify only old versions as allowed.

.. _testability-participant-node-upgrades-historic-data-hlreq:

* **Testability of participant node upgrades on historical data**. I
  want to be able to test new versions of participant nodes against
  historical data from a time window and compare the results to those
  obtained from old versions, so that I can increase my certainty that
  the new version does not introduce unintended differences in
  behavior.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Testability of participant node upgrades on historical data <https://github.com/DACH-NY/canton/issues/175>`_.

.. _seamless-participant-failover-hlreq:

* **Seamless participant failover**. I want the applications using
  the ledger API to seamlessly fail over to my other participant nodes,
  once one of my nodes crashes.

  **Design limitation** An external load balancer is required in front of the
  participant node replicas to direct requests to the appropriate replica.

.. _seamless-domain-entities-failover-hlreq:

* **Seamless failover for sync domain entities**. I want the implementation of all
  sync domain entities to include seamless failover capabilities, so that
  the system can continue operating uninterruptedly on the failure
  of an instance of a sync domain entity.

.. _backups-hlreq:

* **Backups**. I want to be able to periodically back up
  the system state (ledger databases) so that it can be
  subsequently restored if required for disaster recovery purposes.

.. _site-wide-disaster-recovery-hlreq:

* **Site-wide disaster recovery**. I want the system to be built with
  the ability to recover from the failure of an entire data center by
  moving the operations to a different data center, without loss of
  data.

  .. todo::
    #. `Participant site disaster recovery <https://github.com/DACH-NY/canton/issues/189>`_.
    #. `Sync domain site disaster recovery <https://github.com/DACH-NY/canton/issues/190>`_.

.. _participant-compromise-recovery-hlreq:

* **Participant corruption recovery**. I want to have a procedure in
  place that can be followed to recover from a malfunctioning or a
  corrupted participant node, so that when the procedure is finished
  I obtain the same guarantees (in particular, integrity and
  transparency) as the honest participants on the part of the shared
  ledger created after the end of the recovery procedure.

  .. todo::
    #. `Participant site compromise attack recovery <https://github.com/DACH-NY/canton/issues/187>`_.

.. _domain-entity-compromise-recovery-hlreq:

* **Sync domain entity corruption recovery**. I want to have a procedure
  in place that can be followed to recover a malfunctioning or corrupted sync domain entity,
  so that the system guarantees can be restored after the procedure
  is complete.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Sync domain entities compromise attack recovery <https://github.com/DACH-NY/canton/issues/188>`_.

.. _fundamental-dispute-resolution:

* **Fundamental dispute resolution**. I want to have a procedure in place
  that allows me to limit and resolve the damage to the ledger state in
  the case of a fundamental dispute on the outcome of a transaction that
  was added to the virtual shared ledger, so that I could reconcile the
  set of active contracts with my counterparties in case of any disagreement
  over this set. Example causes of disagreement include disagreement
  with the state found after recovering a compromised participant, or
  disagreement due to a change in the regulatory environment making
  some existing contracts illegal.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Fundamental dispute resolution <https://github.com/DACH-NY/canton/issues/185>`_.

.. _distributed-recovery-participant-data-hlreq:

* **Distributed recovery of participant data**. I want to be able to reconstruct
  which of my contracts are currently active from the information that
  the participants of my counterparties store, so that I can recover
  my data in case of a catastrophic event. This assumes that the other
  participants are cooperating and have not suffered catastrophic
  failures themselves.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Distributed recovery of participant data <https://github.com/DACH-NY/canton/issues/193>`_

.. _adding-parties-to-participants-hlreq:

* **Adding parties to participants**. I want to be able to start using
  the system at any point in time, by choosing to use a new or
  an already existing participant node.

.. _identity-information-updates-hlreq:

* **Identity information updates**. I want the synchronization protocol
  to track updates of the topology state, so that the
  parties can switch participants, and participants can roll and/or
  revoke keys, while ensuring continuous system operation.

  .. _party-migration-hlreq:

* **Party migration**. I want to be able to switch from using one
  participant node to using another participant node, without losing
  the data about the set of active contracts on the shared ledger that
  I am a stakeholder of. The new participant node does not need to provide me with
  the ledger changes prior to migration.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Party migration between participant nodes <https://github.com/DACH-NY/canton/issues/197>`_

.. _parties-using-multiple-participants-hlreq:

* **Parties using multiple participants**. I want to be able to use
  the system through multiple participant nodes, so that I can
  do load balancing, and continue using the system even if one of my
  participant nodes crashes.

  **Design limitation** The usage of multiple participants by a single party is
  not seamless as with :ref:`participant high availability
  <seamless-participant-failover-hlreq>`, because ledger offsets are different
  between participant nodes unless it is a replicated participant and command
  deduplication state is not shared among multiple participant nodes.

  .. _read-only-participants-hlreq:

* **Read-only participants**. I want to be able to configure some
  participants as read-only, so that I can provide a live stream of
  the changes to my ledger view to an auditor, without giving them the
  ability to submit change requests.

  .. _reuse-of-off-the-shelf-solutions-hlreq:

* **Reuse of off-the-shelf solutions**. I want the system to rely on
  industry-standard abstractions for:

    #. messaging
    #. persistent storage (e.g., SQL)
    #. identity providers (e.g., Oauth)
    #. metrics (e.g., MetricsRegistry)
    #. logging (e.g., Logback)
    #. monitoring (e.g., exposing ``/health`` endpoints)

   so that I can use off-the-shelf solutions for these purposes.

.. _metrics-on-apis-hlreq:

* **Metrics on APIs**. I want the system to provide metrics
  on the state of all API endpoints in the system, and make
  them available on both link endpoints.

.. _metrics-on-processing-hlreq:

* **Metrics on processing**. I want the system to provide metrics for
  every major processing phase within the system.

.. _component-health-monitoring-hlreq:

* **Component health monitoring**. I want the system to provide
  monitoring information for every system component, so that I
  am alerted when a component fails.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Component health monitoring <https://github.com/DACH-NY/canton/issues/205>`_.

.. _remote-debugability-hlreq:

* **Remote debugability**. I want the system to capture sufficient
  information such that I can debug remotely and post-mortem any issue
  in environments that are not within my control (OP).

.. _horizontal-scalability-hlreq:

* **Horizontal scalability**. I want the system to be able to
  horizontally scale all parallelizable parts of the system, by adding
  processing units for these parts.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Horizontal scalability <https://github.com/DACH-NY/canton/issues/207>`_.

.. _large-transaction-support-hlreq:

* **Large transaction support**. I want the system to support
  large transactions such that I can guarantee atomicity of large-scale
  workflows.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Large transaction support <https://github.com/DACH-NY/canton/issues/210>`_.

.. _resilience-to-erroneous-behavior-hlreq:

* **Resilience to erroneous behavior**. I want the system
  to be resilient against erroneous behavior of users and participants
  such that I can entrust the system to handle my business.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Resilience to erroneous behavior <https://github.com/DACH-NY/canton/issues/211>`_.

.. _resilience-to-faulty-domain-behavior-hlreq:

* **Resilience to faulty sync domain behavior**. I want the system
  to be able to detect and recover from faulty behavior of
  sync domain components, such that occasional issues do not break the system
  permanently.

  This item is scheduled on the roadmap.

  .. todo::
    #. `Resilience to faulty sync domain behavior <https://github.com/DACH-NY/canton/issues/212>`_.

.. _requirements-known-limitations:

Known limitations
-----------------

In this section, we explain the current limitations of Canton that we intend to overcome in future versions.

Limitations that apply always
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Missing Key features
^^^^^^^^^^^^^^^^^^^^

* **Cross-sync-domain transactions** currently require the submitter of the transaction to transfer all used contracts
  to a common sync domain.
  Cross-sync-domain transactions without first transferring to a single sync domain are not supported yet.
  Only the stakeholders of a contract may transfer the contract to a different sync domain.
  Therefore, if a transaction spans several sync domains and makes use of delegation to non-stakeholders,
  the submitter currently needs to coordinate with other participants to run the transaction,
  because the submitter by itself cannot transfer all used contracts to a single sync domain.

Reliability
^^^^^^^^^^^

* **H2 support:** The H2 database backend is not supported for production scenarios, therefore data continuity is also not guaranteed.

Manageability
^^^^^^^^^^^^^

* **Party migration** is still an experimental feature.
  A party can already be migrated to a "fresh" participant that has not yet been connected to any sync domains.
  Party migration is currently a manual process that needs to be executed with some care.

Security
^^^^^^^^

* **Denial of service attacks:** We have not yet implemented all countermeasures
  to denial of service attacks. However, the sync domain already protects against
  faulty participants sending too many requests and message size limits protect
  against malicious participants trying to send large amounts of data via a
  sync domain. Further rate limit on the ledger API protects against malicious/faulty
  applications.

* **Public identity information:**
  The topology state of a sync domain (i.e., participants known to the sync domain and parties hosted by them) is known to
  all participants connected to the sync domain.

.. todo::
   #. `Only selectively disclose topology information <https://github.com/DACH-NY/canton/issues/1251>`_.


Limitations that apply only sometimes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Manageability
^^^^^^^^^^^^^

* **Multi-participant parties:**
  Hosting a party on several participants is an experimental feature.
  If such a party is involved in a contract transfer, the transfer may result in a ledger fork,
  because the ledger API is not able to represent the situation that a contract is transferred out of scope of a participant.
  If one of the participants hosting a party is temporarily disabled, the participant may end up in an outdated state.
  The ledger API does not support managing parties hosted on several participants.

* **Disabling parties:**
  If a party is disabled on a participant, it will remain visible on the ledger API of the participant,
  although it cannot be used anymore.

* **Pruning:**
  The public API does not yet allow for pruning of contract transfers and
  rotated cryptographic keys. An offline participant can prevent the pruning of
  contracts by its counter-participants.

* **DAR and package management through the ledger API:**
  A participant provides two APIs for managing DARs and Daml packages: the ledger API and the admin API.
  When a DAR is uploaded through the ledger API, only the contained packages can be retrieved through the admin API;
  the DAR itself cannot.
  When a package is uploaded through the ledger API,
  Canton needs to perform some asynchronous processing until the package is ready to use.
  The ledger API does not allow for querying whether a package is ready to use.
  Therefore, the admin API should be preferred for managing DARs and packages.

.. _requirements-exceptions:

Requirement Exceptions: Notes
-----------------------------

In this section, we explain the consequences of the exceptions to the requirements.
In contrast to the :ref:`known limitations <requirements-known-limitations>`,
a requirements exception is a fundamental limitation of Canton that will most likely not be overcome in the
foreseeable future.

Ledger consistency
~~~~~~~~~~~~~~~~~~

The validity requirement on the ledger made an exception for the
:ref:`consistency <da-model-consistency>` of contracts without honestly represented
signatories. We explain the exception using the paint offer example
from the :ref:`ledger model <da-ledgers>`. Recall that the example
assumed contracts of the form `PaintOffer houseOwner painter obligor`
with the `painter` as the signatory, and the `houseOwner` as an
observer (while the obligor is not a stakeholder).  Additionally,
assume that we extend the model with an action that allows the painter to rescind the offer.
The resulting model is then:

.. https://www.lucidchart.com/documents/edit/96a86974-9b00-427f-bc59-095c81590ea9
.. image:: ./images/consistency-exception-model.svg
   :align: center
   :width: 100%

Assume that Alice (`A`) is the house owner, `P` the painter, and that
the painter is dishonestly represented, in that he employs a malicious participant, while Alice is honestly represented.
Then, the following shared ledgers are allowed, together with their projections for `A`, which in
this case are just the list of transactions in the shared ledger.

.. https://www.lucidchart.com/documents/edit/a2b76760-fbd8-4542-b4e0-75de28ff7993
.. image:: ./images/consistency-exception-ledger.svg
   :align: center
   :width: 100%

.. https://www.lucidchart.com/documents/edit/770beafe-28cf-4e2d-9183-029e8141c7c8/0
.. image:: ./images/consistency-exception-no-create.svg
   :align: center
   :width: 100%

That is, the dishonestly represented painter can rescind the offer twice in the
shared ledger, even though the offer is not active any more by the
time it is rescinded (and thus consumed) for the second time,
violating the consistency criterion.
Similarly, the dishonestly represented painter can rescind an offer that was never created in the first place.

However, this exception is not a problem for the stated benefits of
the integrity requirement, as the resulting ledgers still ensure that
honestly represented parties cannot have obligations imposed on them or rights taken
away from them, and that their counterparties cannot escape their
existing obligations. For instance, the example of a malicious Alice
double spending her IOU:

.. https://www.lucidchart.com/documents/edit/35aaa658-7a71-475d-b9a6-963d7cd0cc0a
.. image:: ./images/double-spend-with-stakeholders.svg
   :width: 100%
   :align: center

is still disallowed even under the exception, as long as the bank is
honestly represented. If the bank was dishonestly represented, then the double spend would be possible.
But the bank would not gain anything by this dishonest behavior -- it would
just incur more obligations.

No unnecessary rejections
~~~~~~~~~~~~~~~~~~~~~~~~~

This requirement made exceptions for (1) contention, and included a
design limitation for (2) crashes/Byzantine behavior of participant
nodes. Contention is a fundamental limitation, given the requirement
for a bounded decision time. Consider a sequence :math:`cr_1, \ldots cr_n` of
change requests, each of which conflicts with the previous one, but
otherwise have no conflicts, except for maybe :math:`cr_1`. Then all the
odd-numbered requests should get added to the ledger exactly when :math:`cr_1` is
added, and the even-numbered ones exactly when :math:`cr_1` is rejected.
Since detecting conflicts and other forms of processing (e.g.
communication, Daml interpretation) incur processing delays,
deciding precisely whether :math:`cr_n` gets added to the ledger takes time proportional
to :math:`n`. By lengthening the sequence of requests, we eventually
exceed any fixed bound within which we must decide on :math:`cr_n`.

Crashes and Byzantine behavior can inhibit liveness.
To cope, the so-called VIP confirmation policy allows any trusted participant to add change requests to the ledger without the involvement of other parties.
This policy can be used in settings where there is a central trusted party.
Today's financial markets are an example of such a setting.

.. :ref:`VIP confirmation policy <def-vip-confirmation-policy>`

The no-rejection guarantees can be further improved by constructing
Daml models that ensure that the submitter is a stakeholder on all contracts in a transaction.
That way,
rejects due to Byzantine behavior of other participants can be
detected by the submitter. Furthermore, if necessary, the
synchronization service itself could be changed to improve its
properties in a future version, by including so-called bounded timeout extensions and attestators.

Privacy
~~~~~~~

Consider a transaction where Alice buys some shares from Bob (a
delivery-versus-payment transaction). The shares are registered at the
share registry SR, and Alice is paying with an IOU issued to her by a
bank. We depict the transaction in the first image below. Next, we
show the bank's projection of this transaction, according to the DA
ledger model. Below, we demonstrate what the bank's view obtained
through the ledger synchronization protocol may look like. The bank
sees that the transfer happens as a direct consequence of another
action that has an additional consequence. However, the bank learns
nothing else about the parent action or this other consequence. It
does not learn that the parent action was on a DvP contract, that the
other consequence is a transfer of shares, and that this consequence
has further consequences. It learns neither the number nor the
identities of the parties involved in any part of the transaction
other than the IOU transfer. This illustrates the first design
limitation for the privacy requirement.

At the bottom, we see that the sync domain entities run by a trusted third
party can learn the complete structure of the transaction and the
stakeholders of all actions in the transaction (second design
limitations). Lastly, they also see some data about the contracts on
which the actions are performed, but this data is visible *only in an
encrypted form*. The decryption keys are never shared with the sync domain
entities.



.. https://www.lucidchart.com/documents/edit/53985915-f311-451f-aff6-b5835e57c71c
.. image:: ./images/privacy-leaks-dvp.svg
   :align: center
   :width: 80%


.. comment
   .. .. toctree::
      :maxdepth: 2

      requirements/functional.rst
      requirements/security.rst
      requirements/other.rst
