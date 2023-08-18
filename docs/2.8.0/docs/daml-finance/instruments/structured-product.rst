.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to use the Structured Product Instrument package
####################################################

To follow the script used in this tutorial, you can
`clone the Daml Finance repository <https://github.com/digital-asset/daml-finance>`_. In particular,
the Structured Product test folder
`Instrument/StructuredProduct/Test/ <https://github.com/digital-asset/daml-finance/blob/main/src/test/daml/Daml/Finance/Instrument/StructuredProduct/Test/>`_
is the starting point of this tutorial.

How to create a Structured Product Instrument
*********************************************

In order to create a structured product instrument, you first have to decide what type of payoff you
need. The
:doc:`structured product instrument packages <../packages/implementations/daml-finance-instrument-structuredproduct>`
currently supports the following types of payoffs:

Barrier Reverse Convertible
===========================

The
:ref:`BarrierReverseConvertible <module-daml-finance-instrument-structuredproduct-barrierreverseconvertible-instrument-95793>`
instrument models cash-settled, auto-exercising barrier reverse convertible (BRC) instruments. It
can be seen as a long fixed coupon bond and a short Down-And-In put option.

For example, consider a BRC that pays a fixed 5% coupon rate and has a barrier level of 30 USD. If
the underlying ever trades below this level, the put option is knocked in (activated). This would
reduce the redemption amount if the underlying closes below the strike price at expiry.

This example is taken from
`Instrument/StructuredProduct/Test/BarrierReverseConvertible.daml <src/test/daml/Daml/Finance/Instrument/StructuredProduct/Test/BarrierReverseConvertible.daml>`_
, where all the details are available.

You start by defining the terms:

.. literalinclude:: ../src/test/daml/Daml/Finance/Instrument/StructuredProduct/Test/BarrierReverseConvertible.daml
  :language: daml
  :start-after: -- CREATE_BARRIER_REVERSE_CONVERTIBLE_VARIABLES_BEGIN
  :end-before: -- CREATE_BARRIER_REVERSE_CONVERTIBLE_VARIABLES_END

Now that the terms have been defined, you can create the BRC instrument:

.. literalinclude:: ../src/test/daml/Daml/Finance/Instrument/StructuredProduct/Test/Util.daml
  :language: daml
  :start-after: -- CREATE_BARRIER_REVERSE_CONVERTIBLE_INSTRUMENT_BEGIN
  :end-before: -- CREATE_BARRIER_REVERSE_CONVERTIBLE_INSTRUMENT_END

Once this is done, you can create a holding on it using
:ref:`Account.Credit <module-daml-finance-interface-account-account-92922>`.

This BRC instrument is automatically exercised. This means that the decision whether or not to
exercise the embedded option is done automatically by comparing observations of the underlying to
the *strike* and *barrier* level of the instrument.
For this to work, you need to define an *Observation* as well:

.. literalinclude:: ../src/test/daml/Daml/Finance/Instrument/StructuredProduct/Test/BarrierReverseConvertible.daml
  :language: daml
  :start-after: -- CREATE_BARRIER_REVERSE_CONVERTIBLE_OBSERVATIONS_BEGIN
  :end-before: -- CREATE_BARRIER_REVERSE_CONVERTIBLE_OBSERVATIONS_END

Since this option instrument is cash-settled, the underlying asset will not change hands. Instead,
the cash value of the payoff is paid to the BRC holder.

Frequently Asked Questions
**************************

How do I calculate settlement payments for a structured product?
================================================================

Similar to a fixed coupon bond, a BRC instrument needs to be lifecycled on the coupon dates and at
expiry, in order to calculate the corresponding payments. This is described in the
:doc:`Lifecycling <../tutorials/lifecycling/fixed-rate-bond>` tutorial.
In addition, if the instrument has a barrier (which is the case for a BRC), it needs to be
lifecycled regularly during its lifetime to record any barrier breach, which would impact the
redemption payment.
