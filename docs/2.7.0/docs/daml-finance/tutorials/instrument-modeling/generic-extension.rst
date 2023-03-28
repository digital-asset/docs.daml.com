.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How To Model and Lifecycle Generic Instruments
##############################################

To follow the script used in this tutorial, you can
`clone the Daml Finance repository <https://github.com/digital-asset/daml-finance>`_. In particular,
the file ``src/test/daml/Daml/Finance/Instrument/Generic/Test/Intermediated/BondCoupon.daml`` is the
starting point of this tutorial.

How To Create a Generic Instrument
**********************************

The :doc:`Generic <../../packages/implementations/daml-finance-instrument-generic>` extension
provides a flexible framework to model generic instruments in Daml Finance. It encapsulates the
:doc:`Contingent Claims <../../concepts/contingent-claims>` library, which allows us to model the
economic terms of an instrument.

Define the Claim of a Bond
==========================

Consider a fixed rate bond which pays a 4% p.a. coupon with a 6M coupon period. Assume there are two
coupons remaining until maturity: one today and one in 180 days. This could be modeled in the
following way:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/Intermediated/BondCoupon.daml
  :language: daml
  :start-after: -- CREATE_CC_INSTRUMENT_VARIABLES_BEGIN
  :end-before: -- CREATE_CC_INSTRUMENT_VARIABLES_END

Keywords like
:ref:`when <function-contingentclaims-core-claim-when-17123>`,
:ref:`TimeGte <constr-contingentclaims-core-internal-claim-timegte-91610>`,
:ref:`scale <function-contingentclaims-core-claim-scale-79608>` and
:ref:`one <function-contingentclaims-core-claim-one-13168>`
are defined in the :doc:`Contingent Claims documentation <../../concepts/contingent-claims>`.

Now that we have specified the economic terms we can create a generic instrument:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/Intermediated/BondCoupon.daml
  :language: daml
  :start-after: -- CREATE_CC_INSTRUMENT_BEGIN
  :end-before: -- CREATE_CC_INSTRUMENT_END

This will create an instrument containing the
:doc:`Contingent Claims <../../concepts/contingent-claims>` tree on the ledger.

On a coupon payment date of the bond instrument above, the issuer will need to lifecycle the
instrument. This will result in a lifecycle effect for the coupon, which can be cash settled. This
is described in detail in :doc:`Getting Started: Lifecycling <../getting-started/lifecycling>`.

Define the Claim of a European Option
=====================================

Alternatively, if you want to model a European Option instead:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_CC_OPTION_INSTRUMENT_VARIABLES_BEGIN
  :end-before: -- CREATE_CC_OPTION_INSTRUMENT_VARIABLES_END

This uses the :ref:`european <function-contingentclaims-core-builders-european-99265>` builder
function, which is included in :doc:`Contingent Claims <../../concepts/contingent-claims>`.

Compared to the bond above, where the passage of time results in a coupon payment being due, this
option instrument requires a manual *Election*. The holder of the instrument needs to choose whether
or not to exercise the option. This is described in the next section.

.. _election-based-lifecycling:

Election based lifecycling of Contingent Claims based instruments
=================================================================

First, an Election factory is created:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_ELECTION_FACTORY_BEGIN
  :end-before: -- CREATE_ELECTION_FACTORY_END

Then, an election offer to *exercise* the option is created:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_ELECTION_OFFER_EXERCISE_BEGIN
  :end-before: -- CREATE_ELECTION_OFFER_EXERCISE_END

Similarly, an election offer to *expire* the option is also created:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_ELECTION_OFFER_EXPIRE_BEGIN
  :end-before: -- CREATE_ELECTION_OFFER_EXPIRE_END

Assuming the investor wants to exercise the option, an election candidate contract is created. In
order to do this, the investor presents a holding for which an election should be made, and also
specifies the amount that this election applies to. This amount cannot exceed the quantity of the
holding:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_TOO_BIG_ELECTION_CANDIDATE_BEGIN
  :end-before: -- CREATE_TOO_BIG_ELECTION_CANDIDATE_END

Instead, the elected amount must be the same as the holding quantity, or lower:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_ELECTION_CANDIDATE_BEGIN
  :end-before: -- CREATE_ELECTION_CANDIDATE_END

A time event is also required to indicate *when* the election is made:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_CLOCK_BEGIN
  :end-before: -- CREATE_CLOCK_END

It is now possible to create the *Election*:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_ELECTION_BEGIN
  :end-before: -- CREATE_ELECTION_END

A lifecycle rule is required to specify how to process the Election:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- CREATE_LIFECYCLE_RULE_BEGIN
  :end-before: -- CREATE_LIFECYCLE_RULE_END

Finally, it is possible to apply the Election according to the lifecycle rule provided:

.. literalinclude:: ../../src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml
  :language: daml
  :start-after: -- APPLY_ELECTION_BEGIN
  :end-before: -- APPLY_ELECTION_END

This create lifecycle effects, which can be claimed and settled in the usual way. This is described
in :doc:`Getting Started: Lifecycling <../getting-started/lifecycling>`.

How To Trade and Transfer a Generic Instrument
**********************************************

When you have created a holding on the above instrument it can be transfered to another party. This
is described in :doc:`Getting Started: Transfer <../getting-started/transfer>`.

In order to trade the instrument (transfer it in exchange for cash) you can also initiate a delivery
versus payment with atomic settlement. This is described in
:doc:`Getting Started: Settlement <../getting-started/settlement>`.

How to Process Lifecycle Events
*******************************


Note: the tutorial mainly describes time-based lifecycling. The European option above requires
an active ``Election`` by the holder. This is described in detail in
``src/test/daml/Daml/Finance/Instrument/Generic/Test/EuropeanOption.daml``.

How to Redeem a Generic Instrument
**********************************

On the redemption date, both the last coupon and the redemption amount with be paid. This is
processed in the same way as a single coupon payment described above.
