.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-swap-fpml-util-24838:

Module Daml.Finance.Instrument.Swap.Fpml.Util
=============================================

Data Types
----------

.. _type-daml-finance-instrument-swap-fpml-util-o-46768:

**type** `O <type-daml-finance-instrument-swap-fpml-util-o-46768_>`_
  \= :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ :ref:`Observable <type-daml-finance-interface-claims-types-observable-47872>`

Functions
---------

.. _function-daml-finance-instrument-swap-fpml-util-createcalculationperiodicschedule-96000:

`createCalculationPeriodicSchedule <function-daml-finance-instrument-swap-fpml-util-createcalculationperiodicschedule-96000_>`_
  \: :ref:`CalculationPeriodDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-27905>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>`

  Create a schedule for calculation periods\.

.. _function-daml-finance-instrument-swap-fpml-util-createpaymentperiodicschedule-77689:

`createPaymentPeriodicSchedule <function-daml-finance-instrument-swap-fpml-util-createpaymentperiodicschedule-77689_>`_
  \: :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>`

  Create a schedule for payment periods\.

.. _function-daml-finance-instrument-swap-fpml-util-getcalendarsandadjust-68138:

`getCalendarsAndAdjust <function-daml-finance-instrument-swap-fpml-util-getcalendarsandadjust-68138_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> :ref:`BusinessDayAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Retrieve holiday calendars and adjust a date as specified in a BusinessDayAdjustments FpML
  element

.. _function-daml-finance-instrument-swap-fpml-util-adjustdateaccordingtobusinessdayadjustments-16993:

`adjustDateAccordingToBusinessDayAdjustments <function-daml-finance-instrument-swap-fpml-util-adjustdateaccordingtobusinessdayadjustments-16993_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> :ref:`BusinessDayAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Adjust a date as specified in a BusinessDayAdjustments FpML element
  (or not at all if NoAdjustment)

.. _function-daml-finance-instrument-swap-fpml-util-getsinglestubrate-81189:

`getSingleStubRate <function-daml-finance-instrument-swap-fpml-util-getsinglestubrate-81189_>`_
  \: :ref:`StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656>` \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `O <type-daml-finance-instrument-swap-fpml-util-o-46768_>`_

  Define observable part of claim when one specific floating rate is provided for a stub period\.

.. _function-daml-finance-instrument-swap-fpml-util-getinterpolatedstubrate-67176:

`getInterpolatedStubRate <function-daml-finance-instrument-swap-fpml-util-getinterpolatedstubrate-67176_>`_
  \: :ref:`StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656>` \-\> :ref:`StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656>` \-\> :ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>` \-\> :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>` \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `O <type-daml-finance-instrument-swap-fpml-util-o-46768_>`_

  Linearly interpolates two rates within a period, as specified in
  https\://www\.isda\.org/a/aWkgE/Linear\-interpolation\-04022022\.pdf

.. _function-daml-finance-instrument-swap-fpml-util-getstubratefloating-79993:

`getStubRateFloating <function-daml-finance-instrument-swap-fpml-util-getstubratefloating-79993_>`_
  \: \[:ref:`StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656>`\] \-\> :ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>` \-\> :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>` \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `O <type-daml-finance-instrument-swap-fpml-util-o-46768_>`_

  Get the floating stub rate to be used for a stub period\.

.. _function-daml-finance-instrument-swap-fpml-util-getstubrate-16307:

`getStubRate <function-daml-finance-instrument-swap-fpml-util-getstubrate-16307_>`_
  \: :ref:`StubCalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-23577>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>` \-\> :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `O <type-daml-finance-instrument-swap-fpml-util-o-46768_>`_

  Get the stub rate to be used for a stub period\.
  Currently, three main options from the FpML schema are supported\:

  1. A fix stubRate\.
  2. One or two floating rates for the stub\.
  3. No specific stub rate defined \-\> use the same rate as is used for regular periods\.

.. _function-daml-finance-instrument-swap-fpml-util-alignpaymentschedule-97172:

`alignPaymentSchedule <function-daml-finance-instrument-swap-fpml-util-alignpaymentschedule-97172_>`_
  \: \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\]

  Align the payment schedule with the calculation schedule\.

.. _function-daml-finance-instrument-swap-fpml-util-verifyfxscheduleandgetid-16448:

`verifyFxScheduleAndGetId <function-daml-finance-instrument-swap-fpml-util-verifyfxscheduleandgetid-16448_>`_
  \: \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> :ref:`FxLinkedNotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-9742>` \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\])

.. _function-daml-finance-instrument-swap-fpml-util-getfxrateid-58450:

`getFxRateId <function-daml-finance-instrument-swap-fpml-util-getfxrateid-58450_>`_
  \: \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\])

.. _function-daml-finance-instrument-swap-fpml-util-getratefixingsandcalendars-23482:

`getRateFixingsAndCalendars <function-daml-finance-instrument-swap-fpml-util-getratefixingsandcalendars-23482_>`_
  \: :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> :ref:`ResetDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-61198>` \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (\[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\], :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`)

.. _function-daml-finance-instrument-swap-fpml-util-calculatefixpaymentclaimsfromswapstream-71274:

`calculateFixPaymentClaimsFromSwapStream <function-daml-finance-instrument-swap-fpml-util-calculatefixpaymentclaimsfromswapstream-71274_>`_
  \: :ref:`FixedRateSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-21284>` \-\> :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\] \-\> \[(`Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_, `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_)\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\]

  Create claims from swapStream that describes a fixed or floating coupon stream\.

.. _function-daml-finance-instrument-swap-fpml-util-calculateprincipalexchangepaymentclaims-93183:

`calculatePrincipalExchangePaymentClaims <function-daml-finance-instrument-swap-fpml-util-calculateprincipalexchangepaymentclaims-93183_>`_
  \: \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> \[(`Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_, `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_)\] \-\> \[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\] \-\> :ref:`PrincipalExchanges <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-44478>` \-\> :ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`

  Create principal exchange claims

.. _function-daml-finance-instrument-swap-fpml-util-calculatefloatingpaymentclaimsfromswapstream-81278:

`calculateFloatingPaymentClaimsFromSwapStream <function-daml-finance-instrument-swap-fpml-util-calculatefloatingpaymentclaimsfromswapstream-81278_>`_
  \: :ref:`FloatingRateCalculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-65118>` \-\> :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\] \-\> \[(`Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_, `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_)\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\]

  Create claims from swapStream that describes a fixed or floating coupon stream\.

.. _function-daml-finance-instrument-swap-fpml-util-calculateclaimsfromswapstream-57885:

`calculateClaimsFromSwapStream <function-daml-finance-instrument-swap-fpml-util-calculateclaimsfromswapstream-57885_>`_
  \: :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> \[:ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>`\] \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`Deliverable <type-daml-finance-interface-claims-types-deliverable-19293>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\]

  Create claims from swapStream that describes a fixed or floating coupon stream\.
