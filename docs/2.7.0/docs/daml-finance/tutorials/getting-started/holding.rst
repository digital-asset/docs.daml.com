.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Holding
#######

This tutorial introduces the core asset model of the library through a simple example. The purpose
is to illustrate the concepts of :ref:`account <account>`, :ref:`instrument <instrument>`, and
:ref:`holding <holding>`, as well as showing how to work with Daml interfaces.

We are going to:

#. create accounts for Alice and Bob at the Bank
#. issue a cash instrument
#. credit a cash holding to Alice’s account

We expect the reader to be familiar with the basic building blocks of Daml. If that is not the case,
a suitable introduction can be found `here <https://www.digitalasset.com/developers/learn>`_.
In particular, `An Introduction to Daml <https://docs.daml.com/daml/intro/0_Intro.html>`_
would be a good starting point.

This example refers to the :doc:`Transfer <transfer>` tutorial script in the sense that it explains
the accounts and holdings required for that tutorial.

Explanation of Holdings
***********************

As described in the :ref:`Asset model <holding-asset-model>`, a holding contract represents the
ownership of a certain amount of an :ref:`instrument <instrument>` by an owner at a custodian.

A holding implementation can have specific properties such as being :ref:`fungible <fungibility>` or
:ref:`non-transferable <transferability>`.

Instruments vs Holdings
=======================

* An instrument defines *what* a party holds (the rights and obligations).
* A holding defines *how much* (i.e., the amount) of an instrument and *against which party* (i.e.,
  the custodian) the instrument is being held.

Bearer Tokens vs Holdings
=========================

* Bearer tokens mean that *any* party in possession of the token is presumed to be the owner of the
  asset.
* Holdings, on the other hand, *restrict* the ownership of the asset to parties that have an account
  (a vetted relationship) at a custodian.

.. _structure-of-code-dependencies:

Structure of the Code and Dependencies
**************************************

The code includes

- four workflows defined in the ``Workflows`` folder
- four Daml scripts defined in the ``Scripts`` folder

The ``Workflows`` encapsulate the core business logic of the application, whereas the ``Scripts``
are meant to be executed on a one-off basis.

If you take a closer look at the ``Workflows``, you will recognize three propose / accept patterns
to:

- create an account
- make a deposit to the account

The ``Transfer`` and `DvP`` workflows will be used in the next tutorials, so please ignore those for
now.

Modules in the ``Workflows`` folder depend only on *interface* packages of ``daml-finance`` (the
packages that start with ``Daml.Finance.Interface.*``), as you can see from the import list.

This is important, as it decouples the user-defined business logic from the template implementations
used in ``daml-finance`` which makes it easier to upgrade the application. The user-defined business
logic in the ``Workflows`` will not need to be modified nor re-compiled to work with
upgraded (ie., newer versions of) *implementation* packages.

On the other hand, modules in the ``Scripts`` folder depend on both the *interface* packages and
the *implementation* packages (in this case, ``Daml.Finance.Account``, ``Daml.Finance.Holding``,
and ``Daml.Finance.Instrument.Token``). This is not problematic as scripts are meant to be run only
once when the application is initialized.

Sample Code
***********

In order to show how this works in practice, let us explore the ``Holding`` script step-by-step.

Create ``Holding`` and ``Account`` Factories
============================================

The first instruction instantiates an account factory. This is a template that is used by a party
(the Bank in this case) to create accounts as part of the ``CreateAccount`` workflow.

.. literalinclude:: /_templates/quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- CREATE_ACCOUNT_FACTORY_BEGIN
  :end-before: -- CREATE_ACCOUNT_FACTORY_END

Notice how the ``ContractId`` is immediately converted to an interface upon creation: this is
because our workflows do not have any knowledge of concrete template implementations.

Similarly, we define a holding factory, which is used within an account to ``Credit`` and ``Debit``
holdings.

.. literalinclude:: /_templates/quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- CREATE_HOLDING_FACTORY_BEGIN
  :end-before: -- CREATE_HOLDING_FACTORY_END

This factory contract can be used to create
:ref:`Fungible <type-daml-finance-holding-fungible-factory-35358>` holdings, which are defined in
:ref:`Daml.Finance.Holding.Fungible <module-daml-finance-holding-fungible-7201>`
and are both :ref:`fungible <fungibility>`, as well as :ref:`transferable <transferability>`.

We are adding a so-called *public party* as an observer to the holding factory. This is done to
ensure that parties, which have `readAs` rights of the public party, have visibility over the
contract. This is required when you want to transfer the holding, which will be shown in the next
tutorial.

Open Alice’s and Bob’s Accounts
===============================

Once the factory templates are setup, we leverage our ``CreateAccount`` workflow to create accounts
at the Bank for Alice and Bob.

The creation of an account needs to be authorized by both the ``custodian`` and the ``owner``, i.e.,
by the Bank and Alice in our case. Authorization is collected using an propose / accept pattern.

.. literalinclude:: /_templates/quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- SETUP_ALICE_ACCOUNT_BEGIN
  :end-before: -- SETUP_ALICE_ACCOUNT_END

Bob’s account is created in a similar fashion.

Create the Cash Instrument
==========================

In order to credit Alice’s account with some cash, we first introduce a cash
:ref:`Instrument <type-daml-finance-interface-instrument-token-instrument-instrument-4350>`
in our model.

.. literalinclude:: /_templates/quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- ISSUE_CASH_INSTRUMENT_BEGIN
  :end-before: -- ISSUE_CASH_INSTRUMENT_END

An instrument is a representation of what it is that we are holding against the Bank. It can be as
simple as just a textual label (like in this case) or it can include complex on-ledger lifecycling
logic.

To hold one unit of the cash instrument in this scenario means that we can claim ``USD 1``
(commercial bank money) from the custodian of the holding.

Notice how in this case the Bank acts both as the issuer and depository of the cash instrument. This
means that we fully trust the Bank with any action concerning the instrument.

Deposit Cash in Alice’s Account
===============================

We can now deposit cash in Alice’s account. It is possible to create a holding directly using the
``Fungible`` template:

.. code-block:: daml

  aliceHoldingRequest <- submit alice do
    createCmd HoldingRequest with
      instrument = instrumentKey
      account = aliceAccount
      amount = 1000.0
      owner = alice
      custodian = bank

  aliceHoldingCid <- submit bank do exerciseCmd aliceHoldingRequest Accept

However, this makes the application dependent on the implementation package. As explained in
:ref:`Application Architecture <application-architecture>`, it is better to depend on the interface
layer to maximize upgradability and minimize the impact of incremental changes to your application
or Daml Finance.

Instead, we create the holding using the ``CreditAccount`` workflow, which uses the interface layer.

.. literalinclude:: /_templates/quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- CREATE_ALICE_HOLDING_BEGIN
  :end-before: -- CREATE_ALICE_HOLDING_END

Alice creates a request to deposit ``USD 1000`` at the Bank, the Bank then accepts the request and
a corresponding
:ref:`Holding <type-daml-finance-interface-holding-base-base-14854>` is created.

You can imagine that the latter step happens only after Alice has shown up at the Bank and
delivered physical banknotes corresponding to the amount of the deposit.

Frequently Asked Questions
**************************

What are accounts used for?
===========================

An account is used as the proof of a business relationship between an owner and a custodian: Alice
may transfer cash to Bob because Bob has a valid account at the Bank.

This is done to avoid that Alice transfers cash to Charlie without Charlie being vetted and
acknowledged by the Bank.

The account is also used to determine who actually authorizes incoming and outgoing transfers. For
the account at hand, the owner acts as a controller for both incoming and outgoing transfers. For an
other account, you could for example let the custodian be the controller instead.

Why do we need factories?
=========================

You might be wondering why we use account factories and holding factories instead of creating an
:ref:`Account <type-daml-finance-account-account-account-12745>` or
:ref:`Holding <type-daml-finance-holding-fungible-fungible-28517>`
directly.

This is done to avoid having to reference ``Daml.Finance.Holding`` directly in user workflows (and
hence simplify upgrading procedures).

This is based on the assumption that there are very few factory contracts which are setup on ledger
initialization.

Summary
*******

You know how to setup basic accounts, holdings, and instruments. The key concepts to take away are:

* Holdings represent the ownership of a financial instrument at a custodian.
* Instruments define the economic terms of a financial contract.
* Accounts ensure that only known parties can obtain ownership.
* Factories are used to create the respective contracts without having to depend on implementation
  packages.
