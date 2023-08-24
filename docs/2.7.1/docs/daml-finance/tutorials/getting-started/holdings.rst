.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Holdings
########

This tutorial introduces the core asset model of the library through a simple example. The purpose
is to illustrate the concepts of :ref:`account <account>`, :ref:`instrument <instrument>`, and
:ref:`holding <holding>`, as well as to show some useful patterns when working with Daml interfaces.

We are going to use the Daml Finance library to create tokenized cash on the ledger. This is done
in three steps:

#. we first create accounts for Alice and Bob at the Bank
#. we then proceed to issue a cash instrument, representing tokenized dollars
#. we finally credit a cash holding to Alice’s account

The holding contract represents the record of ownership on the ledger for Alice's tokenized cash.

Run the script
**************

In order to show how this works in practice, let us explore the ``Holding`` script step-by-step.

Create Account, Holding, and Instrument Factories
=================================================

The first instruction instantiates an account factory. This is a template that is used by a party
(the Bank in this case) to create accounts as part of the ``CreateAccount`` workflow.

.. literalinclude:: ../../quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- CREATE_ACCOUNT_FACTORY_BEGIN
  :end-before: -- CREATE_ACCOUNT_FACTORY_END

Notice how the ``ContractId`` is immediately converted to an interface upon creation: this is
because our workflows, such as ``CreateAccount``, do not have any knowledge of concrete template
implementations.

Similarly, we define a :ref:`holding factory <type-daml-finance-holding-fungible-factory-35358>`,
which is used within an account to create (``Credit``) holdings.

.. literalinclude:: ../../quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- CREATE_HOLDING_FACTORY_BEGIN
  :end-before: -- CREATE_HOLDING_FACTORY_END

This factory contract instantiates a specific implementation of holdings, which are defined in
:ref:`Daml.Finance.Holding.Fungible <module-daml-finance-holding-fungible-7201>`
and are both :ref:`fungible <fungibility>`, as well as :ref:`transferable <transferability>`.

Finally, we create a factory template which is used to instantiate :ref:`token instruments
<type-daml-finance-instrument-token-instrument-instrument-62305>`.

.. literalinclude:: ../../quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- CREATE_INSTRUMENT_FACTORY_BEGIN
  :end-before: -- CREATE_INSTRUMENT_FACTORY_END

Open Alice’s and Bob’s Accounts
===============================

Once the factory templates are setup, we leverage the ``CreateAccount`` workflow to create accounts
at the Bank for Alice and Bob.

The creation of an account needs to be authorized by both Alice and the Bank. Authorization is
collected using a propose / accept pattern.

.. literalinclude:: ../../quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- SETUP_ALICE_ACCOUNT_BEGIN
  :end-before: -- SETUP_ALICE_ACCOUNT_END

The Bank acts as the ``custodian``, or account provider, whereas Alice is the account ``owner``.
Bob’s account is created in a similar fashion.

Create the Cash Instrument
==========================

In order to credit Alice’s account with some cash, we first create a cash instrument. An instrument
is a representation of what it is that we are holding against the Bank. It can be as simple as just
a textual label (like the
:ref:`Token Instrument <type-daml-finance-interface-instrument-token-instrument-instrument-4350>`
used in this case) or it can include complex on-ledger lifecycling logic.

.. literalinclude:: ../../quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- ISSUE_CASH_INSTRUMENT_BEGIN
  :end-before: -- ISSUE_CASH_INSTRUMENT_END

Notice how in this case the Bank acts both as the issuer and depository of the cash instrument. This
means that we fully trust the Bank with any action concerning the instrument contract.

Deposit Cash in Alice’s Account
===============================

We can now deposit cash in Alice’s account, using the ``CreditAccount`` workflow.
Alice creates a request to deposit ``USD 1000`` at the Bank, the Bank then accepts the request and
a corresponding :ref:`Holding <type-daml-finance-interface-holding-base-base-14854>` is created.

.. literalinclude:: ../../quickstart-finance/daml/Scripts/Holding.daml
  :language: daml
  :start-after: -- CREATE_ALICE_HOLDING_BEGIN
  :end-before: -- CREATE_ALICE_HOLDING_END

You can imagine that the latter step happens only after Alice has shown up at the Bank and
delivered physical banknotes corresponding to the amount of the deposit.

The holding contract represents the record of ownership on the ledger. In this scenario,
Alice's holding of ``1000`` units of the cash instrument means that she is entitled to claim
``USD 1000`` from holding's custodian, the Bank.

To summarize

* an instrument defines *what* a party holds (the rights and obligations).
* a holding defines *how much* (i.e., the amount) of an instrument and *against which party* (i.e.,
  the custodian) the instrument is being held.

Frequently Asked Questions
**************************

What are accounts used for?
===========================

An account is used as the proof of a business relationship between an owner and a custodian: Alice
may transfer cash to Bob because Bob has a valid account at the Bank.

This is done to avoid that Alice transfers cash to Charlie without Charlie being vetted and
acknowledged by the Bank.

The account is also used to determine who is required to authorize incoming and outgoing transfers.
For the account at hand, the owner acts as a controller for both incoming and outgoing transfers.
The other options are explained as part of the settlement tutorials.

Why do we need factories?
=========================

You might be wondering why we use account factories and holding factories instead of creating an
:ref:`Account <type-daml-finance-account-account-account-12745>` or
:ref:`Holding <type-daml-finance-holding-fungible-fungible-28517>`
directly.

This is done to avoid having to reference the ``Daml.Finance.Holding`` package directly in the
user workflows (and hence simplify upgrading procedures).

This pattern is described in detail in the :ref:`Daml Finance Patterns <factory-pattern>` page and
is based on the assumption that there are very few factory contracts which are setup on
ledger initialization.

Summary
*******

You now know how to setup basic accounts, holdings, and instruments. The key concepts to take
away are:

* Holdings represent the ownership of a financial instrument at a custodian.
* Instruments define the economic terms of a financial contract.
* Accounts ensure that only known parties can obtain ownership.
* Factories are used to create the respective contracts without having to depend on implementation
  packages.
