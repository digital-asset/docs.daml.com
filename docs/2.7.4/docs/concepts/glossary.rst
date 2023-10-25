.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0


Glossary of Concepts
####################

A guide to Daml, Canton, and related terminology.

Daml Concepts
*************

Atomic Transaction
==================

A transaction in a database or system where either all the actions within the transaction are successfully completed, or none of them are.

Composability
=============

The ability of an `application provider <#daml-application-provider-app-provider>`__ to implement business processes that reuse processes implemented by other `applications <#daml-application-app>`__.

For example, a trading application may be able to reuse the processes for changing asset ownership implemented in the asset issuance applications of the assets in question. In that context, the settlement of a DvP obligation is a workflow composed of workflows from three applications: the trading application and the issuance application for each of the two assets being exchanged.

Daml
====

A platform for building and running sophisticated, multi-party `applications <#daml-application-app>`__. At its core, it contains a smart contract `language <#daml-language>`__, a ledger model, a synchronization protocol, and application development `tooling <#developer-tools>`__. Daml includes `Canton <#canton>`__.

Daml Application (App)
======================

An application for running business processes across multiple real-world entities using `Daml <#daml>`__ and `Canton <#canton>`__ to synchronize the state of these processes across the entities. Typically includes Daml `templates <#template>`__, a backend, and query stores supporting a web frontend.

Daml Application Provider (App Provider)
========================================

An entity building, operating, and evolving a `Daml application <#daml-application-app>`__.

Daml Application User (App User)
================================

Any entity using a `Daml application <#daml-application-app>`__. Not to be confused with a `Participant User <#participant-user>`__.

Daml Enterprise
===============

A product sold and supported by Digital Asset. It is a superset of features beyond the Daml open-source offering. The primary differences between the `open-source Daml <#daml-open-source>`__ technology stack and the Daml Enterprise product are that Daml Enterprise supports high availability and is more scalable. 

Daml Hub
========

A Platform-as-a-Service (PaaS) offering for Daml `Daml <#daml>`__ and `Canton <#canton>`__ that simplifies operations, accelerates deployment, and provides a fully managed gateway to the Canton Network for application builders and users.

Daml Language
=============

A purpose-built language for the rapid development of `composable <#composability>`__ multi-party `applications <#daml-application-app>`__. It is a modern, ergonomically designed functional language that carefully avoids many
of the pitfalls that hinder multi-party application development in other languages.

Daml Ledger
===========

The union of all Daml `contract <#contract>`__ records stored by the `participant nodes <#participant-node>`__. These records form a virtual global shared ledger in the sense that all contracts and changes to them are synchronized across all participant nodes hosting one of their stakeholder parties.

Daml Ledger Model
=================

The integrity and privacy guarantees that a `Daml ledger <#daml-ledger>`__ provides to the entities operating and using it through their `Daml application <#daml-application-app>`__. For full documentation see `Daml Ledger Model <https://docs.daml.com/concepts/ledger-model/index.html>`__.

Daml Model
==========

The set of Daml `contract <#contract>`__ `templates <#template>`__ used by a `Daml application <#daml-application-app>`__ to describe the data schema for the state and the allowed state transitions of the business processes run by the Daml application.

Daml (Open Source)
==================
Daml as a core technology and platform is open source. References to the enterprise version specifically name `Daml Enterprise <#daml-enterprise>`__.

Daml Transaction
================

A list of ledger actions committed to the `Daml ledger <#daml-ledger>`__ atomically. Note that `Canton <#canton>`__ also supports governance transactions, such as topology changes, which are not Daml transactions.

Daml Developer Tools
********************

Assistant
=========

A command-line tool for many tasks related to Daml. Using it, you can write `Daml <#daml-language>`__, compile it, launch other developer tools, and download new `SDK <#daml-sdk>`__ versions.

Daml SDK
========

A single package that includes all Daml developer tooling: the Daml Studio VS Code extension, the Daml compiler, Standard Library, Assistant, Navigator, Sandbox, codegen utility, etc.

Navigator
=========

A GUI tool for exploring the ledger. You can use it to see what contracts can be seen by different parties and submit commands on behalf of those parties. To learn more, see `Navigator </tools/navigator/index.html>`__.

Sandbox
=======
A lightweight Daml ledger implementation with a single participant node and a single sync domain, both running in-memory. It is used to simulate a Daml ledger at development and developer testing time. To learn more, see `Daml Sandbox </tools/sandbox.html>`__.

Studio
======

A plugin for Visual Studio Code, and the Integrated Development Environment (IDE) for writing Daml code. To learn more, see `Daml Studio </daml/daml-studio.html>`__.

Daml Ledger Concepts
********************

Action
======

This term has two meanings in the context of Daml: the Action typeclass and ledger actions. Ledger actions are related to the typeclass Action in that the return type of Daml functions Create, Exercise, and Fetch is Update, which is an instance of typeclass Action. However, the typeclass Action also includes data types that are not related to any interaction with the ledger such as Either, Optional etc.

Action Typeclass
----------------

The Daml equivalent of Haskell class `Monad <https://en.wikibooks.org/wiki/Haskell/Understanding_monads>`__.

Ledger Action
-------------

Ledger actions are commands performed and recorded on the ledger. There are only four kinds of ledger actions: create, exercise, fetch, and key assertion. 

Authorization, Signing
======================

How `parties <#daml-party>`__ involved in a transaction indicate that they have approved it. Each action has an associated set of parties that need to authorize it.

At runtime, the Daml execution engine computes the required authorizing parties from this mapping. It also computes which parties have given authorization to the action in question. The Daml authorization model is comprised of the following rules:

* An action that creates or archives a contract must be authorized by all signatories of the contract
* An action that exercises a choice on a contract must be authorized by all controllers of the choice
* A fetch action must be authorized by at least one stakeholder on the contract
* A lookupByKey action must be authorized by all key maintainers

Actions performed in the body of a choice are authorized by (i.e. carry the authority of) all controllers of the choice and all signatories of the contract on which the choice is exercised.

Choice
======

A function (or a block of code) that a set of parties specified as choice controllers can jointly exercise on a contract. A choice is a part of a Daml `templates <#template>`__. 

For full documentation on choices, see `Reference: Choices </daml/reference/choices.html>`__.

Consuming Choice
----------------

A choice that `archives <#active-contract-archived-contract>`__ the `contract <#contract>`__ when `exercised <#exercise>`__. 

Nonconsuming Choice
-------------------

A choice that does NOT `archive <#active-contract-archived-contract>`__ the `contract <#contract>`__ it is on when `exercised <#exercise>`__. This means the choice can be exercised more than once on the same contract.

However, syntactic sugar can be added to a nonconsuming choice to make it preconsuming or postconsuming.

Preconsuming Choice
-------------------

A choice marked preconsuming `archives <#active-contract-archived-contract>`__ the `contract <#contract>`__ at the start of that `exercise <#exercise>`__.

Postconsuming Choice
--------------------

A choice marked postconsuming `archives <#active-contract-archived-contract>`__ the `contract <#contract>`__ at the end of the `exercise <#exercise>`__ choice body.

Contract
========

A record on a `ledger <#daml-ledger>`__. Contracts are created from blueprints called `templates <#template>`__ and include:

* data (arguments)
* `Daml parties <#daml-party>`__ (signatory, observer)
* `choices <#choices>`__ (and controllers)

Contracts are immutable: once they are created on the ledger, the information in the contract cannot be changed. The only thing that can happen to them is that they can be `archived <#active-contract-archived-contract>`__.

Active Contract/Archived Contract
---------------------------------

When a `contract <#contract>`__ is created on a `ledger <#daml-ledger>`__, it becomes active. Later it can be archived if the signatories of the contract decide to archive it or some other `consuming choice <#consuming-choice>`__ is exercised on the contract

Once the contract is archived, it is no longer valid, and choices can no longer be exercised on it.

Active Contract Set (ACS)
-------------------------

The set of active contracts in the system at any one time: the totality of all the `contracts <#contract>`__ that have been created and have not been `archived <#active-contract-archived-contract>`__ since. 

Contract Key
============

Allows you to fetch a `contract <#contract>`__ of a particular `template <#template>`__ using a synthetic key, similar to an index on a database table.

A contract key requires a maintainer: a simple contract key would be something like a tuple of text and maintainer, like (accountId, bank).

See `Reference: Contract Keys </daml/reference/contract-keys.html>`__.

In Daml 2.x, you can also perform a lookup using a contract key if there is no contract associated with that contract key.

Create
======

An update that creates a `contract <#contract>`__ on the `ledger <#daml-ledger>`__.

Contract creation requires `authorization <#authorization-signing>`__ from all its signatories, or the update fails. For how to get authorization, see the `propose-accept </daml/patterns/initaccept.html>`__ and `multiple-party agreement </daml/patterns/multiparty-agreement.html>`__ patterns.

Daml-LF
=======

When you compile Daml source code, the underlying format is Daml-LF. Daml-LF is similar to `Daml <#daml-language>`__, but stripped down to a core set of features. The relationship between the surface Daml syntax and Daml-LF is loosely similar to that between Java and JVM bytecode.

Daml-LF is also the format you interact with on the `Ledger API <#ledger-api>`__. For example, when exercising a choice you specify the choice argument as a Daml-LF value.

Daml Scripts
============

These provide a way of testing `Daml <#daml-language>`__ code during development. You can run Daml Scripts inside `Daml Studio <#daml-studio>`__, or write them to be executed on `Sandbox <#sandbox>`__ when it starts up.

They are useful for:

* clearly expressing the intended workflow of your contracts
* ensuring that parties can only create contracts, observe contracts, and exercise choices that they are meant to
* acting as regression tests to confirm that everything keeps working correctly

In Daml Studio, Daml Script runs in an emulated ledger. You specify a linear sequence of actions that various parties take, and these are evaluated in order, according to the same consistency, authorization, and privacy rules as they would be on a Daml ledger. Daml Studio shows you the resulting transaction graph, and (if a Daml Script fails) what caused it to fail.

See `Test Templates Using Daml Script </daml/intro/2_DamlScript.html#testing-using-script>`__.

DAR File, DALF File
===================

A Daml Archive file; the result of compiling `Daml <#daml-language>`__ code using the `Assistant <#Assistant>`__ which can be interpreted using a Daml interpreter.
You upload ``.dar`` files to a `ledger <#daml-ledger>`__ to create `contracts <#contract>`__ from the `templates <#template>`__ in that file.
A ``.dar`` contains multiple ``.dalf`` files. A ``.dalf`` file is the output of a compiled Daml package. Its underlying format is Daml-LF.

Exercise
========

An action that exercises a `choice <#choice>`__ on a `contract <#contract>`__ on the `ledger <#ledger>`__ using the provided choice argument. If the choice is `consuming <#consuming-choice>`__, the exercise `archives <#active-contract-archived-contract>`__ the contract; if it is nonconsuming, the contract stays active.
Exercising a choice requires `authorization <#authorization-signing>`__ from all of the `controllers <#controller>`__ of the choice.

See `Reference: Updates </daml/reference/updates.html>`__.

Flexible Controllers
====================

`Choice <#choice>`__ controllers can be specified as coming from the payload of the `contract <#contract>`__ or the arguments of the choice. In the latter case, we say that the choice uses flexible controllers. In other words, a choice uses flexible controllers if the controllers of the choice are provided when the choice is `exercised <#exercise>`__ rather than when the contract is created.

Ledger API
==========

An API that is exposed by a participant node to access its view of the Daml ledger shared with the other participant nodes and submit changes to it. Users access and manipulate the ledger state through the ledger API. An alternative name for the ledger API is the gRPC ledger API if disambiguation from other technologies is needed. See `The Ledger API </app-dev/ledger-api.html>`__. 

The following libraries wrap the ledger API for more native experience application development.

Java Bindings
-------------

An idiomatic Java library for interacting with the ledger API.JVM of the ledger API. See `Java Bindings </app-dev/bindings-java/index.html>`__.

Python Bindings
---------------

A Python library (formerly known as DAZL) for interacting with the ledger API. See `Python Bindings </app-dev/bindings-python.html>`__.

Ledger API Authorization
========================

Ledger API authorization restricts access to a `participant node <#participant-node>`__'s APIs by requiring a valid token that authorizes the user to act as a given `participant user <#participant-user>`__. This participant user then has a set of rights (including which parties it is allowed to act and readAs) that determine whether a given request is rejected.

This is orthogonal to authorization in Daml models: Ledger API authorization determines whether a request to the ledger API is correctly authorized given a token. Authorization in Daml models controls which party is allowed to perform a given action, e.g., exercise a choice.

Standard Library
================
A set of Daml functions, classes, and more that make developing with Daml easier.
For documentation, see :doc:`Daml Standard Library </daml/stdlib/index>`.

Subtransaction Privacy
======================

A system where participants in a transaction `only learn about the subset of the transaction they are directly involved in </ledger-model/ledger-privacy.html>`__, including the consequences of the exercised choices, but not about any other part of the transaction. This applies to both the content of the transaction as well as other involved participants.

Template
========
A blueprint for creating a `contract <#contract>`__. This is the Daml code you write.
For full documentation on what can be in a template, see `Reference: Templates </daml/reference/templates.html>`__.

Trust Domain
============

A trust domain encompasses a part of the system operated by a single real-world entity. This subsystem may consist of one or more physical nodes. In a Daml `application <#daml-application-app>`__, an `application provider <#daml-application-provider-app-provider>`__ typically runs a `sync domain <#synchronization-sync-domain>`__, a `participant node <#participant-node>`__, and an application backend within its trust domain. Application users typically also run their own participant node and the application UI in their own trust domain. 

User Management
***************

An API service that handles the `users <#participant-user>`__ on a `participant node <#participant-node>`__ and their access to other `Ledger API <#ledger-api>`__ services. 

(Daml) Party
============

Daml parties are used to identify roles in the business processes implemented by Daml `applications <#daml-application-app>`__. These roles often represent a person or a legal entity. Parties can create `contracts <#contract>`__ and exercise `choices <#choice>`__.
Access control on Daml contracts and their choices is specified at the granularity of parties. Thus, signatories, observers, controllers, and maintainers are all parties, represented by the Party data type in Daml.

Parties are hosted on `participant nodes <#participant-node>`__ and a participant node can host more than one party. A party can be hosted on several participant nodes simultaneously.

Choice Observer
---------------
A party that is guaranteed to see a particular `choice <#choice>`__ being exercised on a `contract <#contract>`__ and all the consequences of that choice.

Controller
----------
A party that can exercise a particular `choice <#choice>`__ on a particular `contract <#contract>`__.

Maintainer
----------
A party that is part of a `contract key <#contract-keys>`__. They must always be a signatory on the `contract <#contract>`__ for which they maintain the key.
For documentation on contract keys, see `Reference: Contract Keys </daml/reference/contract-keys.html>`__.

Observer
--------

A party that can see an instance of a `contract <#contract>`__ and all the information about it. Observers do NOT have the right to consent to the creation of the contract. Observers can see the contract creation and the archiving `choice <#choice>`__, but not the exercise of nonconsuming, preconsuming, or postconsuming choices.

Signatory
---------
A party that MUST consent to the creation of the `contract <#contract>`__ by authorizing it: if all signatories do not authorize, contract creation fails. Once the contract is created, signatories can see the contract and all exercises of `choices <#choice>`__ on that contract.

For documentation on signatories, see `Reference: Templates </daml/reference/templates.html>`__.

Stakeholder
-----------

Stakeholder is not a term used within the Daml language, but the concept refers to the signatories and observers collectively. That is, it means all of the parties that are interested in a `contract <#contract>`__'s creation and archival.

For documentation on observers, see `Reference: Templates </daml/reference/templates.html>`__.

(Participant) User
==================

On each `participant node <#participant-node>`__ you can create users with human-readable user IDs that follow a format usable by the participant node operator. Each user has a set of user rights that allow it to behave as the equivalent of one or more `parties <#daml-party>`__. These can include admin rights (allowing administration operations like allocating other users), read as rights, and/or act as rights.  

Users help manage access to a participant node’s `Ledger API <#ledger-api>`__ for end users and their UIs and/or custom backend. Users are local to a specific participant node and are authenticated using an IAM configured and controlled by the participant node operator. Every participant node operator uses an IAM of their choice. Applications cannot address users on different participant nodes by their UserID, and UserIDs are never part of `Daml code <#daml-language>`__ – smart contract logic always uses Daml party IDs. 

Canton
******

Canton Protocol
===============

The technology that synchronizes `participant nodes <#participant-node>`__ across any Daml-enabled blockchain or database.  The Canton protocol not only makes Daml
applications portable between different underlying `synchronization technologies <#synchronization-technology>`__, but also allows applications to transact with each other across them.

.. Synchronization technology.  Not 'Environment', 'Infrastructure layer', 'Messaging layer', 'Topology layer', 'Underlying <enter-any-previous-term>'

Synchronization Technology
==========================

The database or blockchain that Daml uses for synchronization, messaging, and topology. Daml runs on a range of synchronization technologies, from centralized
databases to fully distributed deployments, and users can employ the technology that best suits their technical and operational needs.

Canton Concepts
***************

Participant Node
================

A server that provides users with consistent programmatic access to a ledger through the `Ledger API <#ledger-api>`__. The participant nodes handle transaction signing and
validation, such that users don't have to deal with cryptographic primitives but can trust the participant node that the data they are observing has been properly verified to be correct.

Synchronization (Sync) Domain
=============================

A set of services that provide total ordered, guaranteed delivery multi-cast to the participants. This means that participant nodes communicate with each other by sending end-to-end encrypted messages
through the domain.

The `sequencer service <#sequencer>`__ of the sync domain orders these messages without knowing about the content and ensures that every participant receives the messages in the same order.

The other services of the sync domain are the `mediator <#mediator>`__ and the `domain identity manager <#domain-identity-manager>`__.

Private Contract Store
======================

Every participant node manages its own private contract store (PCS) which contains only contracts the participant is privy to. There is no global state or global contract store.

Virtual Global Ledger
=====================

While every participant has their own private contract store (PCS), the `Canton protocol <#canton-protocol>`__ guarantees that the contracts which are stored in the PCS are well-authorized
and that any change to the store is justified, authorized, and valid. The result is that every participant only possesses a small part of the *virtual global ledger*. All the local
stores together make up that *virtual global ledger* and they are thus synchronized. The Canton protocol guarantees that the virtual ledger provides integrity, privacy,
transparency, and auditability. The ledger is logically global, even though physically, it runs on segregated and isolated domains that are not aware of each other.

Mediator
========

A service provided by the sync `domain <#domain>`__ and used by the `Canton protocol <#canton-protocol>`__. The mediator acts as commit coordinator, collecting individual transaction verdicts issued by validating
participants and aggregating them into a single result. The mediator does not learn about the content of the transaction, they only learn about the involved participants.

Sequencer
=========

A service provided by the sync `domain <#domain>`__, used by the `Canton protocol <#canton-protocol>`__. The sequencer forwards encrypted addressed messages from participants and ensures that every member receives
the messages in the same order. Think about registered and sealed mail delivered according to the postal date stamp.

Sync Domain Identity Manager
============================

A service provided by the sync `domain <#domain>`__, used by the `Canton protocol <#canton-protocol>`__. Participants join a new sync domain by registering with the domain identity manager. The domain
identity manager establishes a consistent identity state among all participants. The domain identity manager only forwards identity updates. It can not invent them.

Consensus
=========

The Canton protocol does not use PBFT or any similar consensus algorithm. There is no proof of work or proof of stake involved. Instead, Canton uses a variant of a stakeholder-based
two-phase commit protocol. As such, only stakeholders of a transaction are involved in it and need to process it, providing efficiency, privacy, and horizontal scalability. Canton-based
ledgers are resilient to malicious participants as long as there is at least a single honest participant. A domain integration itself might be using the consensus mechanism of the underlying
platform, but participant nodes will not be involved in that process.

.. Transaction
.. ===========

.. A transaction is composed of a series of actions.

.. Create (trans)action
.. --------------------

.. Exercise (trans)action
.. ----------------------

.. Fetch (trans)action
.. -------------------

.. Commit
.. ======

.. Privacy, visibility
.. ===================

.. Consistency
.. ===========

.. Conformance
.. ===========
