.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-claims-util-builders-48637:

Module Daml.Finance.Claims.Util.Builders
========================================

This module includes utility functions used to build contingent claim trees that represent
specific payoffs\. A ``Schedule`` is usually used as an input to these utility functions\. Given
that schedules are defined in terms of dates, a claim where the time parameter is ``Date``
is returned\. These are then mapped to claims where the time parameter is ``Time`` using a
(user\-provided) conversion function\.

Functions
---------

.. _function-daml-finance-claims-util-builders-prepareandtagclaims-56847:

`prepareAndTagClaims <function-daml-finance-claims-util-builders-prepareandtagclaims-56847_>`_
  \: (`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> \[:ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>`\] \-\> `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Convert the claims to UTCTime and tag them\.

.. _function-daml-finance-claims-util-builders-createfixratepaymentclaimslist-73817:

`createFixRatePaymentClaimsList <function-daml-finance-claims-util-builders-createfixratepaymentclaimslist-73817_>`_
  \: :ref:`Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>` \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> \[:ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>`\]

.. _function-daml-finance-claims-util-builders-createfixratepaymentclaims-44625:

`createFixRatePaymentClaims <function-daml-finance-claims-util-builders-createfixratepaymentclaims-44625_>`_
  \: (`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> :ref:`Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>` \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Calculate a fix rate amount for each payment date and create claims\.

.. _function-daml-finance-claims-util-builders-createconditionalcreditfixratepaymentclaims-60895:

`createConditionalCreditFixRatePaymentClaims <function-daml-finance-claims-util-builders-createconditionalcreditfixratepaymentclaims-60895_>`_
  \: (`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> :ref:`Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>` \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>` \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Calculate a fix rate amount (if a credit event has not yet happened) for each payment date and
  create claims\.

.. _function-daml-finance-claims-util-builders-createcrediteventpaymentclaims-98407:

`createCreditEventPaymentClaims <function-daml-finance-claims-util-builders-createcrediteventpaymentclaims-98407_>`_
  \: (`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>` \-\> :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Calculate a (1\-recoveryRate) payment if a credit event just happened and create claims\.

.. _function-daml-finance-claims-util-builders-createfloatingratepaymentclaims-77749:

`createFloatingRatePaymentClaims <function-daml-finance-claims-util-builders-createfloatingratepaymentclaims-77749_>`_
  \: (`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> :ref:`Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>` \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>` \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Calculate a floating rate amount for each payment date and create claims\.
  The floating rate is always observed on the first day of each payment period and used for the
  corresponding payment on the last day of that payment period\. This means that the calculation
  agent needs to provide such an Observable, irrespective of the kind of reference rate used (e\.g\.
  a forward looking LIBOR or a backward looking SOFR\-COMPOUND)\.

.. _function-daml-finance-claims-util-builders-createassetperformancepaymentclaims-26407:

`createAssetPerformancePaymentClaims <function-daml-finance-claims-util-builders-createassetperformancepaymentclaims-26407_>`_
  \: (`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> :ref:`Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>` \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>` \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Calculate the asset performance for each payment date and create claims\.
  The performance is calculated using the reference asset from the start date to the end date of
  each payment period\. The reference asset Observable needs to contain the appropriate type of
  fixings\:

  * unadjusted fixings in case of a price return asset swap
  * adjusted fixings in case of a total return asset swap

.. _function-daml-finance-claims-util-builders-createfxadjustedprincipalclaim-32115:

`createFxAdjustedPrincipalClaim <function-daml-finance-claims-util-builders-createfxadjustedprincipalclaim-32115_>`_
  \: (`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Create an FX adjusted principal claim\.
  This can be used for both FX swaps (using the appropriate FX rate) and single currency bonds
  (setting the FX rate to 1\.0)\.
