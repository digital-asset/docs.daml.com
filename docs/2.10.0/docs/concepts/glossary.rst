.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0


Glossary of concepts
####################

Daml
****

.. _Atomic Transaction:
Atomic Transaction
==================

A transaction in a database or system where either all the actions within the transaction are successfully completed, or none of them are. If a system guarantees atomicity, it guarantees that there no record is left behind by an incomplete transaction, and all records are consistent in the case of a complete transaction. 

.. _Composability:
Composability
=============

The ability of an `application provider <Daml App Provider_>` to implement business processes that reuse processes implemented by other applications.

For example, a trading application may be able to reuse the processes for changing asset ownership implemented in the asset issuance applications of the assets in question. In that context, the settlement of a `DvP obligation <https://docs.daml.com/canton/architecture/overview.html_>` is a workflow composed from workflows of three applications: the trading application and the issuance application for each of the two assets being exchanged.

.. _Daml:
Daml
====

A platform for building and running sophisticated multi-party blockchain `applications <Daml App_>`. At its core, it contains a smart contract `language <Daml Language_>`, a `ledger model <Daml Ledger Model_>`, a synchronization protocol, and application development tooling. The smart contract language, ledger model, and synchronization protocol define the schema, semantics, and execution of transactions between parties. Daml includes Canton.

.. _Daml App:
Daml Application (App)
======================

An application for running business processes across multiple real-world entities using the Daml language and transaction processing model and the Canton synchronization protocol to manage obligations and privacy and to synchronize the state of these processes across the entities. An app typically includes Daml templates, a backend, and query stores supporting a web frontend.

.. _Daml App Provider:
Daml Application Provider (App Provider)
========================================

An entity building, operating, and evolving a Daml application, and making it accessible to app users.

.. _Daml App User:
Daml Application User (App User)
================================

An entity using a Daml application. Should not be confused with a participant user.

.. _Daml Enterprise:
Daml Enterprise
===============

A product sold and supported by Digital Asset. It contains a superset of features beyond the Daml open-source offering. The primary differences between the open-source Daml technology stack and the Daml Enterprise product are that Daml Enterprise supports high availability and is more scalable. 

.. _Daml Hub:
Daml Hub
========

A Platform-as-a-Service (PaaS) offering for Daml and Canton that simplifies operations, accelerates deployment, and provides one option for a managed gateway to the Canton Network for application builders and users.

.. _Daml Language:
Daml Language
=============

A purpose-built smart contract language. It is a modern, ergonomically designed functional language that carefully avoids many of the pitfalls that hinder multi-party application development in other languages.

.. _Daml Ledger:
Daml Ledger
===========

The union of all Daml contract records stored by participant nodes. These records form a virtual global shared ledger in the sense that all contracts and changes to them are synchronized across all participant nodes hosting one of their stakeholder parties.

.. _Daml Ledger Model:
Daml Ledger Model
=================

The integrity and privacy guarantees that a Daml ledger provides to the entities operating and using it through their Daml application. For full documentation see Daml Ledger Model.

.. _Daml Model:
Daml Model
==========

The set of Daml contract templates used by a Daml application to describe the data schema for the state and the allowed state transitions of the business processes run by the Daml application.

.. _Daml Open Source:
Daml (Open Source)
==================

Daml as a core technology and platform is open source. Refer to the open source version when you need to disambiguate against Daml Enterprise the product.

.. _Daml Transaction:
Daml Transaction
================

A list of ledger actions committed to the Daml ledger atomically. Note that Canton also supports governance transactions, such as topology changes, which are not Daml transactions.

.. _Daml Developer Tools:
Daml Developer Tools
********************

.. _Assistant:
Assistant
=========

A command-line tool for many tasks related to Daml. Using it, you can write Daml, compile it into .dar files, launch other developer tools, and download new SDK versions.

.. _Daml SDK:
Daml SDK
========

A single package that includes all Daml developer tooling: the Daml Studio VS Code extension, the Daml compiler, Standard Library, Assistant, Navigator, Sandbox, codegen utility etc.

.. _Navigator:
Navigator
=========

A GUI tool for exploring the ledger. You can use it to see what contracts can be seen by different parties, and submit commands on behalf of those parties. To learn more, see the Navigator documentation.

.. _Sandbox:
Sandbox
=======

A lightweight Daml ledger implementation with a single participant node and a single sync domain, both running in-memory. It is used to simulate a Daml ledger at development and developer testing time. To learn more, see Daml Sandbox.

.. _Studio:
Studio
======

A plugin for Visual Studio Code, and the Integrated Development Environment (IDE) for writing Daml code. To learn more, see Daml Studio.

Daml Ledger Concepts
********************

.. _Action:
Action
======

This term has two meanings in the context of Daml: the Action typeclass and ledger actions. Ledger actions are related to the typeclass Action in that the return type of Daml functions Create, Exercise, and Fetch is Update, which is an instance of typeclass Action. However, the typeclass Action also includes data types that are not related to any interaction with the ledger such as Either, Optional etc.

.. _Action Typeclass:
Action Typeclass
----------------

The Daml equivalent of Haskell class Monad.  

.. _Ledger Action:
Ledger Action
-------------

Ledger actions are commands performed and recorded on the ledger. There are four kinds of ledger actions: create, exercise, fetch and key assertion. 

.. _Authorization Signing:
Authorization, Signing
======================

The means by which parties involved in a transaction indicate that they have approved it. Each action has an associated set of parties that need to authorize it.
At runtime, the Daml execution engine computes the required authorizing parties from this mapping. It also computes which parties have given authorization to the action in question. The Daml authorization model is comprised of the following rules:
  * An action that creates or archives a contract must be authorized by all signatories of the contract
  * An action that exercises a choice on a contract must be authorized by all controllers of the choice
  * A fetch action must be authorized by at least one stakeholder on the contract
  * A lookupByKey action must be authorized by all key maintainers

Actions performed in the body of a choice are authorized (i.e. carry the authority of) all controllers of the choice and all signatories of the contract on which the choice is exercised.

.. _Choice:
Choice
======

A function (or a block of code) that a set of parties specified as choice controllers can jointly exercise on a contract. A choice is a part of a Daml Template. 

For full documentation on choices, see Reference: Choices.

.. _Consuming Choice:
Consuming Choice
----------------

A choice that archives the contract when exercised. 

.. _Nonconsuming Choice:
Nonconsuming Choice
-------------------

A choice that does NOT archive the contract it is on when exercised. This means the choice can be exercised more than once on the same contract. However, syntactic sugar can be added to a nonconsuming choice to make it preconsuming or postconsuming.

.. _Preconsuming Choice:
Preconsuming Choice
^^^^^^^^^^^^^^^^^^^

A choice marked preconsuming will archive the contract at the start of that exercise.

.. _Postconsuming Choice:
Postconsuming Choice
^^^^^^^^^^^^^^^^^^^^

A choice marked postconsuming will not archive the contract until the end of the exercise choice body.

.. _Contract:
Contract
========

A record on a ledger. Contracts are created from blueprints called templates, and include:
  * data (arguments)
  * Daml parties (signatory, observer)
  * choices (and controllers)

Contracts are immutable: once they are created on the ledger, the information in the contract cannot be changed. The only thing that can happen to them is that they can be archived.

.. _Active Archived:
Active Contract/Archived Contract
---------------------------------

When a contract is created on a ledger, it becomes active. It can be can be removed from archived status by being archived if the signatories of the contract decide to archive it or some other consuming choice is exercised on the contract

Once the contract is archived, it is no longer valid, and choices can no longer be exercised on it.

.. _ACS:
Active Contract Set (ACS)
-------------------------

The set of active contracts in the system at any one time: the totality of all the contracts that have been created but have not been archived yet. 

.. _Contract Key:
Contract Key
============

Allows you to fetch a contract of a particular template using a synthetic key, similar to an index on a database table.
A contract key requires a maintainer: a simple key would be something like a tuple of text and maintainer, like (accountId, bank).
See Reference: Contract Keys.

In Daml 2.x, you can also perform a lookup using a key in the event that there is no contract associated with a given key.

.. _Create:
Create
======

An update that creates a contract on the ledger.

Contract creation requires authorization from all its signatories, or the update will fail. For how to get authorization, see the propose-accept and multiple party agreement patterns.

.. _Daml-LF:
Daml-LF
=======

When you compile Daml source code into a .dar file, the underlying format is Daml-LF. Daml-LF is similar to Daml, but is stripped down to a core set of features. The relationship between the surface Daml syntax and Daml-LF is loosely similar to that between Java and JVM bytecode.

Daml-LF is also the format you interact with on the Ledger API, e.g., when exercising a choice you specify the choice argument as a Daml-LF value.

.. _Daml Scripts:
Daml Scripts
============

These provide a way of testing Daml code during development. You can run Daml Scripts inside Daml Studio, or write them to be executed on Sandbox when it starts up.

They are useful for:
  * clearly expressing the intended workflow of your contracts
  * ensuring that parties can only create contracts, observe contracts, and exercise choices that they are meant to
  * acting as regression tests to confirm that everything keeps working correctly

In Daml Studio, Daml Script runs in an emulated ledger. You specify a linear sequence of actions that various parties take, and these are evaluated in order, according to the same consistency, authorization, and privacy rules as they would be on a Daml ledger. Daml Studio shows you the resulting transaction graph, and (if a Daml Script fails) what caused it to fail.

See Test Templates Using Daml Script.

.. _DAR DALF:
DAR File, DALF File
===================

A Daml Archive file; the result of compiling Daml code using the Assistant which can be interpreted using a Daml interpreter.

You upload .dar files to a ledger in order to be able to create contracts from the templates in that file.

A .dar contains multiple .dalf files. A .dalf file is the output of a compiled Daml package. Its underlying format is Daml-LF.

.. _Exercise:
Exercise
========

An action that exercises a choice on a contract on the ledger using the provided choice argument. If the choice is consuming, the exercise will archive the contract; if it is nonconsuming, the contract will stay active.

Exercising a choice requires authorization from all of the controllers of the choice.

See Reference: Updates.

.. _Flexible Controllers:
Flexible Controllers
====================

Choice controllers can be specified as coming from the payload of the contract or from the arguments of the choice. In the latter case we say that the choice uses flexible controllers. In other words, a choice uses flexible controllers if the controllers of the choice are provided when the choice is exercised rather than when the contract is created.

.. _Ledger API:
Ledger API
==========

An API that is exposed by a participant node to access its view of the Daml ledger shared with the other participant nodes and submit changes to it. Users access and manipulate the ledger state through the ledger API. An alternative name for the ledger API is the gRPC ledger API if disambiguation from other technologies is needed. See The Ledger API. 

The following libraries wrap the ledger API for more native experience applications development.

.. _Java Bindings:
Java Bindings
-------------

An idiomatic Java library for interacting with the ledger API.JVM of the ledger API. See Java Bindings.

.. _Python Bindings:
Python Bindings
---------------

A Python library (formerly known as DAZL) for interacting with the ledger API. See Python Bindings.

.. _Ledger API Authorization:
Ledger API Authorization
========================

Ledger API authorization restricts the access to a participant node’s APIs by requiring a valid token that authorizes the user to act as a given participant user. This participant user then has a set of rights including which parties it is allowed to act and readAs which determine whether a given request is rejected.
This is orthogonal to authorization in Daml models: Ledger API authorization determines whether a request to the ledger API is correctly authorized given a token. Authorization in Daml models controls which party is allowed to perform a given action, e.g., exercise a choice.

.. _Smart Contract Upgrade:
Smart Contract Upgrade
======================

Smart Contract Upgrade (SCU) is a  feature in Initial Availability as of version 2.9 that allows different versions of a template to exist.  The core benefit is that application code can be enhanced or patched without having to stop the participant node. Often prefaced with the phrase “Zero Downtime” or “ZDT”.

.. _Standard Library:
Standard Library
================

A set of Daml functions, classes, and more that make developing with Daml easier.
For documentation, see The standard library.

.. _Subtransaction Privacy:
Subtransaction Privacy
======================

A system where participants to a transaction only learn about the subset of the transaction they are directly involved in, including the consequences of the exercised choices, but not about any other part of the transaction. This applies to both the content of the transaction as well as other involved participants.

.. _Template:
Template
========

A blueprint for creating a contract. This is the Daml code you write.

For full documentation on what can be in a template, see Reference: Templates.

.. _Trust Domain:
Trust Domain
============

A trust domain encompasses a part of the system operated by a single real-world entity. This subsystem may consist of one or more physical nodes. In a Daml application, an application provider typically runs a synchronizer, a participant node, and an application backend within its own trust domain. Application users typically also run their own participant node and the application UI in their own trust domain.

.. _User Management:
User Management
===============

An API service that handles the users on a participant node and their access to other Ledger API services. 

.. _Daml Party:
(Daml) Party
------------

Daml parties are used to identify roles in the business processes implemented by Daml applications. These roles often  represent a person or a legal entity. Parties can create contracts and exercise choices.

Access control on Daml contracts and their choices is specified at the granularity of parties. Thus, signatories, observers, controllers, and maintainers (see below) are all parties, represented by the Party data type in Daml.

Parties are hosted on participant nodes and a participant node can host more than one party. A party can be hosted on several participant nodes simultaneously.

.. _Choice Observer:
Choice Observer
^^^^^^^^^^^^^^^

A party guaranteed to see a particular choice being exercised on a contract, and all the consequences of that choice.

.. _Controller:
Controller
^^^^^^^^^^

A party that is able to exercise a particular choice on a particular contract.

.. _Maintainer:
Maintainer
^^^^^^^^^^

A party that is part of a contract key. They must always be a signatory on the contract that they maintain the key for.

For documentation on contract keys, see Reference: Contract Keys.

.. _Observer:
Observer
^^^^^^^^

A party that can see an instance of a contract and all the information about it. Observers do NOT have the right to consent to the creation of the contract. Observers can see the contract creation and the archiving choice, but not the exercise of nonconsuming, preconsuming, or postconsuming choices.

For documentation on observers, see Reference: Templates.

.. _Signatory:
Signatory
^^^^^^^^^

A party that MUST consent to the creation of the contract by authorizing it: if all signatories do not authorize, contract creation will fail. Once the contract is created, signatories can see the contract and all exercises of choices on that contract.

For documentation on signatories, see Reference: Templates.

.. _Stakeholder:
Stakeholder
^^^^^^^^^^^

Stakeholder is not a term used within the Daml language, but the concept refers to the signatories and observers collectively. That is, it means all of the parties that are interested in a contract creation and archival.

.. _Participant User:
(Participant) User
------------------

On each participant node you can create users with human-readable user IDs that follow a format usable by the participant node operator. Each user has a set of user rights that allow it to behave as the equivalent of one or more parties. These can include admin rights (allowing administration operations like allocating other users), read as rights, and/or act as rights.  

Users help manage access to a participant node’s Ledger API for end users and their UIs and/or custom backend. Users are local to a specific participant node and are authenticated using an IAM configured and controlled by the participant node operator.  Every participant node operator uses an IAM of their choice.  Applications cannot address users on different participant nodes by their UserID, and UserIDs are never part of Daml code – smart contract logic always uses Daml party IDs. 

Canton
******

.. _Canton:
Canton
======

Use when referring to the concept of Canton in general with no specifics to product, protocol, or features. 

May be used when referring only to the blockchain specifics of Daml.

.. _Canton Network:
Canton Network
==============

The set of all Canton participant nodes and synchronizers run by real-world entities across the world. See the Canton Network section for related terms.

.. _Canton Protocol:
Canton Protocol
===============

The technology which synchronizes changes to the Daml ledger across participant nodes while maintaining subtransaction privacy. The Canton Protocol makes Daml applications interoperable between different underlying synchronization technologies.
Daml Driver
The technology for running a synchronizer on top of a database (e.g., Postgres) or blockchain (e.g., CometBFT).

Canton Concepts
***************

.. _Consensus:
Consensus
=========

The Canton protocol relies on individual participant nodes to validate Daml transactions. There is no proof of work or proof of stake involved in transaction validation. Instead, Canton uses a stakeholder-based two-phase commit protocol. As such, only stakeholders of a transaction process it and validate it, providing efficiency, privacy and horizontal scalability. 
Separately a Canton synchronizer may use a BFT consensus protocol to agree on a common order for all messages, but that process does not involve transaction validation, and participant nodes will not be involved.

.. _Participant Node:
Participant Node
================

A server that provides users a consistent programmatic access to a ledger through the Ledger API. The participant node handles transaction signing and validation, such that users do not have to deal with cryptographic primitives but can trust the participant node to provide data that has been properly verified to be correct.

A participant node stores all the incoming and outgoing Daml Smart Contracts for one or more Daml parties. It also provides participant users with programmatic access to the Canton Network by handling transaction signing and validation, and manages the private contract store.

.. _PCS:
Private Contract Store (PCS)
============================

Every participant node manages its own private contract store (PCS) which contains only contracts the participant is privy to, and their transaction history. There is no global state or global contract store.

.. _Synchronizer:
Synchronizer
============

Daml uses the Canton synchronization protocol, also developed by Digital Asset, as its primary synchronization technology. Each implementation of the Canton protocol relies on an underlying ordering service to ensure that a set of participant nodes execute all transactions in the same order, and to ensure that the participant nodes all agree on the timestamps of these transactions.  This service  is provided by the synchronizer. 

The synchronizer provides total ordered, guaranteed delivery multi-cast service to the participants, along with atomic two-phase commits. This means that all participant nodes arrive at the same results in the same sequence for all transactions. Any transactions that fail ordering, delivery, and atomic two-phase commits are rejected and rolled back. Participant nodes communicate with each other by sending end-to-end encrypted messages through the synchronizer.

Note that the code and documentation for Canton 2.8 and 2.9 may refer to the synchronizer as the "domain" or "sync domain".

.. _Synchronizer Operator:
Synchronizer Operator
=====================

An entity that operates a synchronizer, controlling the hardware, software, and secret keys for that system. To transport data between nodes and determine the order of messages, each participant node connects to one or more private or public synchronizers. A synchronizer operator is sometimes referred to as a Canton Service Provider (CSP).

.. _Mediator:
Mediator
--------

A service provided by the synchronizer and used by the Canton protocol. The mediator acts as commit coordinator, collecting individual transaction verdicts issued by validating participants, and aggregates them into a single result. The mediator does not learn about the content of the transaction, only about the involved participants and the metadata of the transaction. 

.. _Ordering:
Ordering Layer/Service
----------------------

A service that assigns an order to transactions. Postgres is commonly used for this purpose, but decentralized Canton synchronizers use an ordering layer built using a BFT consensus protocol.

.. _Sequencer:
Sequencer
---------

A service provided by the synchronizer and used by the Canton protocol. The sequencer forwards encrypted addressed messages from participants and ensures that every member receives the messages in the same order. Think about registered and sealed mail delivered in the order of  the postal date stamp.

The sequencer service of the synchronizer delivers messages to the specified recipients without knowing about the content and ensures that every participant receives the messages in the same order.

.. _Topology State:
Topology State
--------------

The state of all delegation and mapping transactions in the network, plus sync domain governance updates.

.. _Traffic Management:
Traffic Management
------------------

Consists of three parts:
  1. Counting the traffic (in bytes) used by sequencer clients
  2. Enforcing that sequencer clients do not use more traffic than they are allowed to
  3. Setting maximum total traffic limits for sequencer clients 

1 and 2 are built into the Canton sequencer as of version 3.0. 3 is application-specific. The Super Validators operating nodes in the Global Synchronizer on Canton Network implement a specific  approach to Part 3 to create and track traffic balances. 

Canton Network
**************

.. _Canton Coin:
Canton Coin (CC)
================

A utility token issued by the Canton Coin Application.

Using Canton Coin is optional. Participant node operators who want to connect to one or more Super Validators operating the global synchronizer must burn Canton Coin to create a traffic balance. Similarly, participants who want to use the Canton Name Service directory application operated by any given Super Validator,  must burn Canton Coin in order to create a Canton Name subscription. However, other participant nodes may continue to use Canton and participate in the Canton Network without using Canton Coin.

.. _Canton Coin Application:
Canton Coin Application (CC)
============================

One of the initial applications deployed to the Canton Network. It is a public and permissionless application which serves multiple purposes:
  1. Provide an optional network-native mechanism to pay for network usage. For example, the Super Validators operating the global synchronizer require participants to acquire and burn Canton Coin to create traffic balances that they consume when using that service.
  2. Provide an optional network-native payment system.
  3. Provide a public gauge of network and application usage. Canton Coin gives visibility into the fees paid to different Application Providers as a proxy of the value their apps provide to users.
  4. Reward users who contribute value-add infrastructure, products, and services to the network.

.. _CC Scan:
Canton Coin Scan (CC Scan)
==========================

An app run as part of each super validator node that provides a read-only view of network activity like CC transactions, current coin configurations, and CC/USD price.

.. _CC User:
Canton Coin User
================

An entity that uses CC in the sense that it holds CC, or receives/sends transfers.

.. _Canton Name:
Canton Name
===========
An entry in the Canton Name Service. Each Canton Name is a user-defined, human-readable string of one or more human-readable words. Word separation is denoted with the “-” symbol.

Rights to a Canton Name may be purchased via a subscription. A subscription  to a Canton Name (that is, a payment for an entry in the Canton Name Service) is created by burning a specified quantity of  Canton Coin.

Each Canton Name is unique, but a given PartyID may have multiple Canton Names.

.. _Canton Name Service:
Canton Name Service
===================

A registry of Canton Names. The registry is offered as a decentralized application provided by each Super Validator operating node in the global synchronizers of the Canton Network, and is available to any Validator node linked to the global synchronizer.

.. _DSOP:
Decentralized Synchronizer Operations Party
===========================================

A Daml PartyID that executes operations agreed on by Super Validators through onchain voting processes, both automated and manual. The DSO party acts only when Super Validators have voted to direct that action by ⅔ majority.  

.. _Global Synchronizer:
Global Synchronizer
===================

A decentralized Canton synchronizer providing Canton Network synchronization for any Canton application, and whose synchronizer nodes are run as part of each Super Validator node.

.. _GSF:
Global Synchronizer Foundation
==============================

An organization that fosters the development and growth of the global synchronizer, and facilitates and provides transparency to its governance.

The Foundation’s primary responsibilities are:
  * Coordinating governance activities among the Super Validators
  * Ecosystem development
  * Marketing and communications
  * Operating one of the Super Validator nodes in the Global Synchronizer

.. _SV:
Super Validator (SV)
====================

A node participating in the full activities of the Global Synchronizer, including operating a synchronizer node and validating all Canton Coin transactions (or subtransactions). A super validator node consists of a participant node hosting an SV operator’s SV party, the super validator (SV) app which manages governance and automation of votes by Super Validators, the validator app which manages coin holdings of the Super Validator with rights to operate the node and the domain traffic of the Super Validator, and Canton Coin Scan, which provides a read-only overview of network activity.

.. _SVRO:
Super Validator Rights Owner
============================

A business entity that controls a full or partial right to control operations of a Super Validator node, and owns Canton Coin minted as part of that Super Validator right.

.. _SVO:
Super Validator Operator
========================

The entity controlling the hardware, software, and secret keys of an SV node. A Super Validator operator operates a Super Validator node on behalf of a Super Validator rights owner, which may be the same business entity, or separate.

.. _SVP:
Super Validator Party
=====================

The party representing a Super Validator on-ledger.

.. _Validator Node:
Validator Node
==============

A Canton participant node combined with the Canton Coin Validator App, which: 
  * Serves a Canton Coin wallet
  * Manages users and their Party IDs
  * Manages the connection to the Global Sync domain and the payment of domain traffic fees. 

.. _Validator Operator:
Validator Operator 
==================
The entity controlling the hardware, software, and secret keys of a Canton Network Validator Node.

.. _VOP:
Validator Operator Party
========================

A partyID used to represent the validator operator on ledger.
