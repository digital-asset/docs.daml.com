.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-contingentclaims-core-builders-15004:

Module ContingentClaims.Core.Builders
=====================================

Functions
---------

.. _function-contingentclaims-core-builders-unrolldates-10100:

`unrollDates <function-contingentclaims-core-builders-unrolldates-10100_>`_
  \: `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_ \-\> `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_ \-\> \[`Month <https://docs.daml.com/daml/stdlib/DA-Date.html#type-da-date-types-month-22803>`_\] \-\> `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_ \-\> \[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\]

  Helper function to generate a series of fixing dates, e\.g\. for coupon payments in ``fixed``\.
  This assumes ``fixingMonths`` and ``fixingDates`` are ordered\.
  The Daml Finance library(https://github.com/digital-asset/daml-finance) has more
  feature\-complete date handling functions\.

.. _function-contingentclaims-core-builders-forward-81104:

`forward <function-contingentclaims-core-builders-forward-81104_>`_
  \: t \-\> :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Forward agreement\. Discounted by (potentially stochastic) interest rate ``r``\.

.. _function-contingentclaims-core-builders-fra-86142:

`fra <function-contingentclaims-core-builders-fra-86142_>`_
  \: t \-\> t \-\> :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Forward rate agreement\.

.. _function-contingentclaims-core-builders-zcb-58726:

`zcb <function-contingentclaims-core-builders-zcb-58726_>`_
  \: t \-\> x \-\> ccy \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x ccy o

  Zero Coupon Bond\.

.. _function-contingentclaims-core-builders-floating-52600:

`floating <function-contingentclaims-core-builders-floating-52600_>`_
  \: :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> ccy \-\> \[t\] \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x ccy o

  A floating rate bond\.

.. _function-contingentclaims-core-builders-fixed-67363:

`fixed <function-contingentclaims-core-builders-fixed-67363_>`_
  \: x \-\> x \-\> ccy \-\> \[t\] \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x ccy o

  A (fixed rate) coupon paying bond\.

.. _function-contingentclaims-core-builders-european-99265:

`european <function-contingentclaims-core-builders-european-99265_>`_
  \: t \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  European option on the passed claim\. e\.g\. call option on S&P 500\:

  .. code-block:: daml

    european (date 2021 05 14) (observe "SPX" - pure 4200)

.. _function-contingentclaims-core-builders-bermudan-21684:

`bermudan <function-contingentclaims-core-builders-bermudan-21684_>`_
  \: \[t\] \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Bermudan option on the passed claim\. Given a pre\-defined set of times
  {t\_1, t\_2, \.\., t\_N}, it allows the holder to acquire the underlying claim on at
  most one of these times\.

.. _function-contingentclaims-core-builders-american-63172:

`american <function-contingentclaims-core-builders-american-63172_>`_
  \: t \-\> t \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  American option (knock\-in)\. The lead parameter is the first possible acquisition date\.

.. _function-contingentclaims-core-builders-swap-38347:

`swap <function-contingentclaims-core-builders-swap-38347_>`_
  \: (\[t\] \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o) \-\> (\[t\] \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o) \-\> \[t\] \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Asset swap on specific fixing dates ``[t]``\. For example\:

  .. code-block:: daml

    fixedUsdVsFloatingEur : [t] -> Serializable.Claim Text
    fixedUsdVsFloatingEur =
      fixed 100.0 0.02 "USD" `swap` floating (observe "USDEUR" * pure 100.0) (observe "EUR1M") "EUR"
