.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to Use a Fixed Rate Bond (Time-based Lifecycling)
#####################################################

This tutorial describes how to define and lifecycle a fixed rate bond instrument. It is similar to
the :doc:`Lifecycling tutorial <../getting-started/lifecycling>`, in that it describes how lifecycle
rules and events can be used to evolve instruments over time. However, there is one main difference:

* The :doc:`Lifecycling tutorial <../getting-started/lifecycling>` describes a dividend event, which
  is something that the issuer defines *on an ongoing basis*. Only once the date and amount of a
  dividend payment has been defined, the issuer creates a distribution event accordingly.
* This tutorial describes a fixed rate bond, where all coupon payments are defined *in advance*.
  They are all encoded in the instrument definition. Hence, the issuer does not need to create
  distribution events on an ongoing bases. Instead, one lifecycle rule in combination with time
  events (a date clock) are used to lifecycle the bond.

Check out the :doc:`Lifecycling concepts <../../concepts/lifecycling>` for a more in-depth
description of the evolution of financial instruments over their lifetime.

In this tutorial, we are going to:

#. create a fixed rate bond instrument and book a holding on it
#. create a lifecycle rule
#. create a lifecycle event (time event: ``DateClockUpdate``)
#. process the event to produce the effects of a coupon payment
#. instruct settlement by presenting a bond holding
#. settle the resulting batch atomically

This example builds on the previous :doc:`Settlement <../getting-started/settlement>` tutorial
script. Some required concepts are explained there, so please check out that tutorial before you
continue below.

Run the Script
**************

The code for this tutorial can be executed via the ``runFixedRateBond`` function in the
``FixedRateBond.daml`` module.

Instrument and Holding
======================

:ref:`Fixed rate bonds <module-daml-finance-instrument-bond-fixedrate-instrument-67993>`
pay a constant coupon rate at the end of each each coupon period. The coupon rate is quoted on an
annualized basis (per annum, p.a.), but it could be paid more frequently (e.g. quarterly).
As an example we will create a bond instrument paying a 1.1% p.a. coupon with a 12M coupon period.
We start by creating our instrument. Here are the key terms:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_FIXED_RATE_BOND_VARIABLES_BEGIN
  :end-before: -- CREATE_FIXED_RATE_BOND_VARIABLES_END

The :ref:`day count convention <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`
is used to determine how many days, i.e., what fraction of a full year, each coupon period has. This
will determine the exact coupon amount that will be paid each period.

The :ref:`business day convention <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>`
determines *how* a coupon date is adjusted if it falls on a non-business day.

We also need holiday calendars, which determine *when* to adjust dates:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_FIXED_RATE_BOND_CALENDARS_BEGIN
  :end-before: -- CREATE_FIXED_RATE_BOND_CALENDARS_END

The coupon dates and the redemption date are described using a
:ref:`PeriodicSchedule <constr-daml-finance-interface-types-date-schedule-periodicschedule-99705>`:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_END

This is used to determine the periods that are used to calculate the coupon. There are a few things
to note here:

- The :ref:`RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360>`
  defines whether dates are rolled at the end of the month or on a given date of the month. In our
  example above, we went for the latter option.
- The :ref:`StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372>`
  allows you to explicitly specify what kind of stub period the bond should have. This is optional
  and not used in the example above. Instead, we defined the stub implicitly by specifying a
  ``firstRegularPeriodStartDate``: since the time between the issue date and the first regular
  period start date is less than 12M (our regular coupon period), this implies a short initial
  stub period.

Now that we have defined the terms we can create the bond instrument using a factory:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_FIXED_RATE_BOND_INSTRUMENT_BEGIN
  :end-before: -- CREATE_FIXED_RATE_BOND_INSTRUMENT_END

Finally, we create a bond holding in Bob's account:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_FIXED_RATE_BOND_HOLDING_BEGIN
  :end-before: -- CREATE_FIXED_RATE_BOND_HOLDING_END

A holding represents the ownership of a certain amount of an :ref:`instrument <instrument>` by an
owner at a custodian. Check out the :doc:`Holding <../getting-started/holding>` tutorial for more
details.

Now, we have both an instrument definition and a holding. Let us now proceed to lifecycle the bond.

Lifecycle Events and Rule
=========================

As mentioned earlier, we only need one single lifecycle rule to process all time events (since all
coupon payments are pre-defined in the instrument terms):

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_LIFECYCLE_RULE_BEGIN
  :end-before: -- CREATE_LIFECYCLE_RULE_END

In order to lifecycle a coupon payment, we create a time event corresponding to the date of the
first coupon:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_CLOCK_UPDATE_EVENT_BEGIN
  :end-before: -- CREATE_CLOCK_UPDATE_EVENT_END

Now, we have what we need to actually lifecycle the bond:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- LIFECYCLE_BOND_BEGIN
  :end-before: -- LIFECYCLE_BOND_END

The result of this is an effect describing the per-unit asset movements to be executed for bond
holders. Each holder can now present their holding to *claim* the effect and instruct settlement of
the associated entitlements.

A :ref:`Claim Rule <module-daml-finance-lifecycle-rule-claim-99318>` allows a holder of the
target instrument to claim the effect resulting from the time event:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CREATE_CLAIM_RULE_BEGIN
  :end-before: -- CREATE_CLAIM_RULE_END

By presenting their holding they can instruct the settlement of the holding transfers described in
the effect:

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- CLAIM_EFFECT_BEGIN
  :end-before: -- CLAIM_EFFECT_END

As a side-effect of settling the entitlements, the presented holding is exchanged for a holding of
a new bond version. This is to prevent a holder from benefiting from a given effect twice (in our
case: receiving the same coupon twice).

In our example of a bond coupon, only a single instruction is generated: the movement of cash from
the bank to the bond holder. This instruction along with its batch is settled the usual way, as
described in the previous :doc:`Settlement <../getting-started/settlement>` tutorial.

.. literalinclude:: ../../finance-instruments/daml/Scripts/FixedRateBond.daml
  :language: daml
  :start-after: -- EFFECT_SETTLEMENT_BEGIN
  :end-before: -- EFFECT_SETTLEMENT_END

Note that the bank in this case does not actually transfer the cash from another account, but simply
credits Bob's account by using the ``CreditReceiver`` allocation type. In a real-world bond coupon
scenario one would additionally model the flow of funds from the issuer to the bank using the same
lifecycle process as described above.

Check out the :doc:`Settlement concepts <../../concepts/settlement>` for a more in-depth
description of the different steps in the settlement process and the settlement modes supported
by the library.

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

* Typically, we would expect the issuer of an instrument to define the instrument terms, which in
  our example above govern the date and amount of each bond coupon.
* Lifecycle rules on the other hand are often controlled by 3rd-party calculation agents.
* The claiming of lifecycle effects is by default the responsibility of the owner of a holding. If
  instead the owner wants to delegate this responsibility to their custodian they can do so via a
  delegation contract.
* The party executing settlement can be chosen as well, as described in the previous tutorial on
  :doc:`Settlement <../getting-started/settlement>`.

Summary
*******

You have learned how to create a fixed coupon bond and how to use a lifecycle rule and events to
process the payments pre-defined by the instrument.
The key concepts to take away are:

* Lifecycle events cause the bond instrument to evolve over time.
* A lifecycle rule contains logic to calculate the effects an event has on an instrument and its
  holdings.
* A claim rule is used to instruct settlement for a given effect using a holding.
