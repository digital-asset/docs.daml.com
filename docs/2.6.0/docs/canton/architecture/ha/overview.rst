..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

Canton High Availability: Overview and Principles
-------------------------------------------------

HA of Canton translates into the HA of its main components (see `Canton Concepts <https://docs.daml.com/concepts/glossary.html#canton-concepts>`__ for a description of each of the components):

  - the participant nodes, consisting of the following subcomponents:

    - gRPC server, which provides the Ledger API access

    - sync service, which executes the Canton protocol

    - indexer, which builds a read cache

  - the domains, which have the following subcomponents:

    - sequencer, which orders and delivers messages

    - mediator, which coordinates transaction processing

    - topology manager, that manages known identities on the domain

    - domain service, which manages registration

The components, their subcomponents, and their data stores are illustrated in the image below, where the arrows show the direction of the data flow, dashed lines denote the logical components, and solid lines denote maximal process separation, i.e., the subcomponents which can be run in separate processes.

.. _components-for-ha:
.. https://lucid.app/lucidchart/c6fc5988-ddcc-41e8-b7f0-c9d6db94f575/edit?invitationId=inv_b0ac9514-778a-426f-a61d-aa3f77d3b204
.. image:: images/canton-components-for-ha.svg
   :align: center
   :width: 100%

While multiple components can be run in the same process, to achieve HA, you should run each component in its own process.
That way, the availability of one component is not affected by the lack of availability of other ones, except for the workflows that directly involve both components.

In particular, the availability of a Canton participant `A` is not affected by the availability of a participant `B`, except for the workflows that:

  1. involve both `A` and `B` and where
  2. `A` and `B` don't have the same visibility into workflow data, i.e., they manage different parties involved in the workflow.

That is, if `A` and `B` host the same party `P`, then processing of transactions involving `P` can still continue as long as either `A` or `B` is available.
However, note that an application operating on behalf of `P` currently cannot
transparently fail over from `A` to `B` or vice versa, due to the difference in
offsets emitted on each participant.

Furthermore, the availability of `A` is also not affected by the availability of the domain `D`, except for the workflows that use `D`.
This allows each participant and domain to take care of its HA separately.
To achieve HA, the components will be replicated, and all replicas of the same component are assumed to have the same trust assumptions, i.e., the operators of one replica must trust the operators of the other replicas.

In general, whenever a component is backed by a database/ledger, the HA of the component currently relies on the HA of the database/ledger.
The component's operator must handle the HA of the database separately.
All database-backed Canton components are designed to be tolerant to temporary database outages.
During the failover period for the database, such Canton components halt processing until the database becomes available again, and resume processing thereafter.
Transactions that involve these Canton components may time out if the failover takes too long.
Nevertheless, they can be safely resubmitted, as command deduplication provides idempotency.

Canton components can expose a :ref:`health endpoint <health-check>`, that can be used to check the health of the components and its subcomponents.

In the following sections, we describe the HA approach of each component.
