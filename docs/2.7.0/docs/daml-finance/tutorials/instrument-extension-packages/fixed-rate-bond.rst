.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to Use a Fixed Rate Bond (Time-based Lifecycling)
#####################################################

This tutorial describes how to define and lifecycle a fixed rate bond instrument. It is similar to
the :doc:`Lifecycling <lifecycling>` tutorial, in that it describes how lifecycle rules and events
can be used to evolve instruments over time. However, there is one main difference:

* The :doc:`Lifecycling <lifecycling>` tutorial describes a dividend event, which is something that
  the issuer defines on an ongoing basis. When the date and amount of a dividend payment has been
  defined, the issuer creates a distribution event accordingly.
* This tutorial describes a fixed rate bond, where all coupon payments are defined in advance. They
  are all encoded in the instrument definition. Hence, the issuer does not need to create
  distribution events on an ongoing bases. Instead, one lifecycle rule in combination with time
  events (a date clock) are used to lifecycle the bond.

We are going to:

#. create a fixed rate bond instrument and a holding on it
#. create a lifecycle rule
#. create a lifecycle event (time event: DateClockUpdate)
#. process the event to produce the effects of a coupon payment
#. instruct settlement by presenting a bond holding
#. settle the resulting batch atomically

This example builds on the previous :doc:`Settlement <settlement>` tutorial script in the sense that
the same parties, accounts and the existing holding factory are used.

Run the Script
**************

The code for this tutorial can be executed via the ``runFixedRateBond`` function in the
``FixedRateBond.daml`` module.

The first part executes the script from the previous :doc:`Settlement <settlement>` tutorial to
arrive at the initial state for this scenario.

Instrument and Holding
======================

We start by creating our fixed rate bond instrument. Here are the key terms:

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_FIXED_RATE_BOND_VARIABLES_BEGIN
  :end-before: -- CREATE_FIXED_RATE_BOND_VARIABLES_END

We also need holiday calendars, which are used to adjust non-business days:

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_FIXED_RATE_BOND_CALENDARS_BEGIN
  :end-before: -- CREATE_FIXED_RATE_BOND_CALENDARS_END

The coupon dates and the redemption date are described using a periodic schedule. This also allows
us to define a stub period (if required):

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_END

We can now create the bond instrument using a factory:

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_FIXED_RATE_BOND_INSTRUMENT_BEGIN
  :end-before: -- CREATE_FIXED_RATE_BOND_INSTRUMENT_END

Lifecycle Events and Rule
=========================

Next, we create a lifecycle rule (which can be used to process all time events):

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_LIFECYCLE_RULE_BEGIN
  :end-before: -- CREATE_LIFECYCLE_RULE_END

Furthermore, we create a time event corresponding to the date of the first coupon payment:

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_CLOCK_UPDATE_EVENT_BEGIN
  :end-before: -- CREATE_CLOCK_UPDATE_EVENT_END

Now, we have what we need to lifecycle the bond:

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- LIFECYCLE_BOND_BEGIN
  :end-before: -- LIFECYCLE_BOND_END

The result of this is an effect describing the per-unit asset movements to be executed for token
holders. Each holder can now present their holding to *claim* the effect and instruct settlement of
the associated entitlements.

A :ref:`Claim Rule <module-daml-finance-lifecycle-rule-claim-99318>` allows a holder of the
target instrument to claim the effect resulting from the time event:

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_CLAIM_RULE_BEGIN
  :end-before: -- CREATE_CLAIM_RULE_END

By presenting their holding they can instruct the settlement of the holding transfers described in
the effect:

.. literalinclude:: ../../quickstart-finance/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CLAIM_EFFECT_BEGIN
  :end-before: -- CLAIM_EFFECT_END

As a side-effect of settling the entitlements, the presented holding is exchanged for a holding of
a new bond version. This is to prevent a holder from benefiting from a given effect twice.

In our example of a bond coupon, only a single instruction is generated: the movement of cash from
the bank to the bond holder. This instruction along with its batch is settled the usual way, as
described in the previous :doc:`Settlement <settlement>` tutorial.

.. literalinclude:: ../../quickstart-finance/daml/Scripts/Lifecycling.daml
  :language: daml
  :start-after: -- EFFECT_SETTLEMENT_BEGIN
  :end-before: -- EFFECT_SETTLEMENT_END

Note that the bank in this case does not actually transfer the cash from another account, but simply
credits Bob's account by using the ``CreditReceiver`` allocation type. In a real-world bond coupon
scenario one would additionally model the flow of funds from the issuer to the bank using the same
lifecycle process as described above.

Frequently Asked Questions
**************************

Which party should create and sign the lifecycle rules and events?
==================================================================

In the simplified scenario for this tutorial, we have used the bank as both the *issuer* and
*depository* for the instruments involved. In a real-world case, instruments and their corresponding
lifecycle rules and events would be maintained by an actual issuer, with the depository acting as a
3rd-party trust anchor.

Which parties typically take which actions in the lifecycle workflow?
=====================================================================

The lifecycle interfaces governing the process leave the controllers of the various choices in the
process up to the implementation.

* Typically, we would expect the issuer of an instrument to be responsible to generate lifecycle
  events (for example, announcing dividends or stock splits).
* Lifecycle rules on the other hand are often controlled by 3rd-party calculation agents.
* The claiming of lifecycle effects is by default the responsibility of the owner of a holding. If
  instead the owner wants to delegate this responsibility to their custodian they can do so via a
  delegation contract.
* The party executing settlement can be chosen as well, as described in the previous tutorial on
  :doc:`Settlement <settlement>`.

Which party should take the role as *lifecycler*?
=================================================

From a design perspective, a lifecycler is often the party that defines the lifecycle events
happening on an instrument (although they can be different). In the simplified example above, it is
the bank. In a more realistic example, it would probably be the issuer.
In some special cases, if we really need the owner to be the lifecycler, we can use a delegation
contract.

The lifecycler is currently trusted with:

* Timely and complete Event processing
* Providing accurate Observations

Which party is the provider of the Effect?
==========================================

Most of the time the provider of the Effect is the lifecycler. However, in some cases we may want to
avoid disclosing the claimed holdings to the lifecycler. The provider of the Effect gets to see all
holdings claimed against that one Effect contract. If we wish to avoid that, we then need a
different effect provider.

Can an instrument act as its own lifecycle rule?
================================================

Yes, an instrument can implement the ``Lifecycle`` interface directly such that the lifecycle rules
are contained within the instrument itself. There are, however, advantages to separating this logic
out into rule contracts:

* Keeping lifecycle rules in a different package from your instruments allows you to independently
  upgrade or patch them without affecting your live instruments.
* Having separate rules allows to change the lifecycle properties of an instrument dynamically at
  runtime. For example, an instrument can initially be created without support for doing asset
  distributions. Then, at a later point, the issuer might decide to start paying dividends. They can
  now simply add a distribution rule to the running system to enable this new lifecycle event for
  their instrument without affecting the actual live instrument itself (or any holdings on it).

Can I integrate a holding ownership change (of the target instrument) within lifecycling?
=========================================================================================

Lifecycling will not change the ownership of the target instrument. You should use the
:doc:`Transfer <transfer>` pattern to do a delivery-versus-payment as a separate step from the
lifecycling.

However, there usually is a change of ownership of the other consumed/produced instruments when
lifecycling (e.g. when paying out a dividend cash is moved from one party to another).

Summary
*******

You have learned how to use lifecycle rules and events to describe the behavior of an instrument.
The key concepts to take away are:

* Lifecycle events represent different ways of how an instrument can evolve.
* A lifecycle rule contains logic to calculate the effects an event has on an instrument and its
  holdings.
* A claim rule is used to instruct settlement for a given effect using a holding.
