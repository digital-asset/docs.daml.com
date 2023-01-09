.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-fpml-fpmltypes-35062:

Module Daml.Finance.Interface.Instrument.Swap.Fpml.FpmlTypes
============================================================

Data Types
----------

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-73867:

**data** `AdjustableDate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-73867_>`_

  A type for defining a date that shall be subject to adjustment if it would otherwise fall on a
  day that is not a business day in the specified business centers, together with the convention
  for adjusting the date\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-49022:

  `AdjustableDate <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-49022_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - unadjustedDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - A date subject to adjustment\.
       * - dateAdjustments
         - `BusinessDayAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058_>`_
         - The business day convention and financial business centers used for adjusting the date if it would otherwise fall on a day that is not a business date in the specified business centers\. adjustedDate \: Optional IdentifiedDate \^ The date once the adjustment has been performed\. (Note that this date may change if the business center holidays change)\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `AdjustableDate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-73867_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `AdjustableDate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-73867_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businesscentertime-18156:

**data** `BusinessCenterTime <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businesscentertime-18156_>`_

  A type for defining a time with respect to a business day calendar location\. For example,
  11\:00am London time\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-businesscentertime-94273:

  `BusinessCenterTime <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-businesscentertime-94273_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - hourMinuteTime
         - `HourMinuteTime <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-hourminutetime-69567_>`_
         - A time specified in hh\:mm\:ss format where the second component must be '00', e\.g\., 11am would be represented as 11\:00\:00\.
       * - businessCenter
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `BusinessCenterTime <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businesscentertime-18156_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `BusinessCenterTime <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businesscentertime-18156_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058:

**data** `BusinessDayAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058_>`_

  A type defining the business day convention and financial business centers used for adjusting
  any relevant date if it would otherwise fall on a day that is not a business day in the
  specified business centers\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-34311:

  `BusinessDayAdjustments <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-34311_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - businessDayConvention
         - :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>`
         - The convention for adjusting a date if it would otherwise fall on a day that is not a business day\.
       * - businessCenters
         - \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\]
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `BusinessDayAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `BusinessDayAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculation-37694:

**data** `Calculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculation-37694_>`_

  The parameters used in the calculation of fixed or floating rate period amounts\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculation-38381:

  `Calculation <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculation-38381_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - notionalScheduleValue
         - `NotionalScheduleValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedulevalue-48881_>`_
         -
       * - rateTypeValue
         - `RateTypeValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypevalue-5034_>`_
         -
       * - dayCountFraction
         - :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Calculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculation-37694_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Calculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculation-37694_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodamount-361:

**data** `CalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodamount-361_>`_

  The calculation period amount parameters\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodamount-73314:

  `CalculationPeriodAmount <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodamount-73314_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - calculation
         - `Calculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculation-37694_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `CalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodamount-361_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodamount-361_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-27905:

**data** `CalculationPeriodDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-27905_>`_

  The calculation periods dates schedule\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-92640:

  `CalculationPeriodDates <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-92640_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - effectiveDate
         - `AdjustableDate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-73867_>`_
         -
       * - terminationDate
         - `AdjustableDate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-adjustabledate-73867_>`_
         -
       * - calculationPeriodDatesAdjustments
         - `CalculationPeriodDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddatesadjustments-79386_>`_
         -
       * - firstRegularPeriodStartDate
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         -
       * - lastRegularPeriodEndDate
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         -
       * - calculationPeriodFrequency
         - `CalculationPeriodFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodfrequency-88564_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `CalculationPeriodDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-27905_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CalculationPeriodDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-27905_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddatesadjustments-79386:

**data** `CalculationPeriodDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddatesadjustments-79386_>`_

  The business day convention to apply to each calculation period end date if it would otherwise
  fall on a day that is not a business day in the specified financial business centers\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddatesadjustments-18825:

  `CalculationPeriodDatesAdjustments <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddatesadjustments-18825_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - businessDayConvention
         - :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>`
         -
       * - businessCenters
         - \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\]
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `CalculationPeriodDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddatesadjustments-79386_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CalculationPeriodDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddatesadjustments-79386_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodfrequency-88564:

**data** `CalculationPeriodFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodfrequency-88564_>`_

  A type defining the frequency at which calculation period end dates occur within the regular
  part of the calculation period schedule and thier roll date convention\. In case the calculation
  frequency is of value T (term), the period is defined by the
  swap\\swapStream\\calculationPerioDates\\effectiveDate and the
  swap\\swapStream\\calculationPerioDates\\terminationDate\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodfrequency-37465:

  `CalculationPeriodFrequency <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodfrequency-37465_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - periodMultiplier
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         - A time period multiplier, e\.g\., 1, 2 or 3 etc\. If the period value is T (Term) then periodMultiplier must contain the value 1\.
       * - period
         - :ref:`PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659>`
         - A time period, e\.g\., a day, week, month, year or term of the stream\.
       * - rollConvention
         - :ref:`RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360>`
         - Used in conjunction with a frequency and the regular period start date of a calculation period, determines each calculation period end date within the regular part of a calculation period schedule\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `CalculationPeriodFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodfrequency-88564_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CalculationPeriodFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodfrequency-88564_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daterelativetoenum-54982:

**data** `DateRelativeToEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daterelativetoenum-54982_>`_

  The specification of whether payments/resets occur relative to the first or last day of a
  calculation period\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodstartdate-76683:

  `CalculationPeriodStartDate <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodstartdate-76683_>`_

    Payments/Resets will occur relative to the first day of each calculation period\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodenddate-41578:

  `CalculationPeriodEndDate <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodenddate-41578_>`_

    Payments/Resets will occur relative to the last day of each calculation period\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `DateRelativeToEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daterelativetoenum-54982_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `DateRelativeToEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daterelativetoenum-54982_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daytypeenum-13752:

**data** `DayTypeEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daytypeenum-13752_>`_

  A day type classification used in counting the number of days between two dates\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-business-59211:

  `Business <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-business-59211_>`_

    When calculating the number of days between two dates the count includes only business
    days\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calendar-50359:

  `Calendar <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-calendar-50359_>`_

    When calculating the number of days between two dates the count includes all calendar days\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-commoditybusiness-80941:

  `CommodityBusiness <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-commoditybusiness-80941_>`_

    When calculating the number of days between two dates the count includes only commodity
    business days\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-currencybusiness-65434:

  `CurrencyBusiness <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-currencybusiness-65434_>`_

    When calculating the number of days between two dates the count includes only currency
    business days\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-exchangebusiness-78596:

  `ExchangeBusiness <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-exchangebusiness-78596_>`_

    When calculating the number of days between two dates the count includes only stock
    exchange business days\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-scheduledtradingday-75056:

  `ScheduledTradingDay <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-scheduledtradingday-75056_>`_

    When calculating the number of days between two dates the count includes only scheduled
    trading days\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `DayTypeEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daytypeenum-13752_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `DayTypeEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daytypeenum-13752_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-21284:

**data** `FixedRateSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-21284_>`_

  Specify the fixed rate

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-46667:

  `FixedRateSchedule <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-46667_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - initialValue
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - The initial rate or amount, as the case may be\. An initial rate of 5% would be represented as 0\.05\. step \: \[Step\] \^ The schedule of step date and value pairs\. On each step date the associated step value becomes effective\. A list of steps may be ordered in the document by ascending step date\. An FpML document containing an unordered list of steps is still regarded as a conformant document\. type\_ \: Optional SpreadScheduleType

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `FixedRateSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-21284_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `FixedRateSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-21284_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-87647:

**data** `FixingDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-87647_>`_

  Specifies the fixing date relative to the reset date in terms of a business days offset and an
  associated set of financial business centers\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-34656:

  `FixingDates <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-34656_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - periodMultiplier
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         -
       * - period
         - :ref:`PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659>`
         -
       * - dayType
         - `DayTypeEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daytypeenum-13752_>`_
         -
       * - businessDayConvention
         - :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>`
         -
       * - businessCenters
         - \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\]
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `FixingDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-87647_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `FixingDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-87647_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-65118:

**data** `FloatingRateCalculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-65118_>`_

  A type defining the floating rate and definitions
  relating to the calculation of floating rate amounts\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-75209:

  `FloatingRateCalculation <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-75209_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - floatingRateIndex
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - indexTenor
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Period <type-daml-finance-interface-types-date-rollconvention-period-21180>`
         - The ISDA Designated Maturity, i\.e\., the tenor of the floating rate\. floatingRateMultiplierSchedule \: Optional Schedule \^ A rate multiplier or multiplier schedule to apply to the floating rate\. A multiplier schedule is expressed as explicit multipliers and dates\. In the case of a schedule, the step dates may be subject to adjustment in accordance with any adjustments specified in the calculationPeriodDatesAdjustments\. The multiplier can be a positive or negative decimal\. This element should only be included if the multiplier is not equal to 1 (one) for the term of the stream\. spreadSchedule \: \[SpreadSchedule\]
       * - spreadSchedule
         - `SpreadSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-spreadschedule-59448_>`_
         - The ISDA Spread or a Spread schedule expressed as explicit spreads and dates\. In the case of a schedule, the step dates may be subject to adjustment in accordance with any adjustments specified in calculationPeriodDatesAdjustments\. The spread is a per annum rate, expressed as a decimal\. For purposes of determining a calculation period amount, if positive the spread will be added to the floating rate and if negative the spread will be subtracted from the floating rate\. A positive 10 basis point (0\.1%) spread would be represented as 0\.001\. rateTreatment \: Optional RateTreatmentEnum \^ The specification of any rate conversion which needs to be applied to the observed rate before being used in any calculations\. The two common conversions are for securities quoted on a bank discount basis which will need to be converted to either a Money Market Yield or Bond Equivalent Yield\. See the Annex to the 2000 ISDA Definitions, Section 7\.3\. Certain General Definitions Relating to Floating Rate Options, paragraphs (g) and (h) for definitions of these terms\. capRateSchedule \: \[StrikeSchedule\] \^ The cap rate or cap rate schedule, if any, which applies to the floating rate\. The cap rate (strike) is only required where the floating rate on a swap stream is capped at a certain level\. A cap rate schedule is expressed as explicit cap rates and dates and the step dates may be subject to adjustment in accordance with any adjustments specified in calculationPeriodDatesAdjustments\. The cap rate is assumed to be exclusive of any spread and is a per annum rate, expressed as a decimal\. A cap rate of 5% would be represented as 0\.05\. floorRateSchedule \: \[StrikeSchedule\] \^ The floor rate or floor rate schedule, if any, which applies to the floating rate\. The floor rate (strike) is only required where the floating rate on a swap stream is floored at a certain strike level\. A floor rate schedule is expressed as explicit floor rates and dates and the step dates may be subject to adjustment in accordance with any adjustments specified in calculationPeriodDatesAdjustments\. The floor rate is assumed to be exclusive of any spread and is a per annum rate, expressed as a decimal\. A floor rate of 5% would be represented as 0\.05\. initialRate \: Optional Decimal \^ The initial floating rate reset agreed between the principal parties involved in the trade\. This is assumed to be the first required reset rate for the first regular calculation period\. It should only be included when the rate is not equal to the rate published on the source implied by the floating rate index\. An initial rate of 5% would be represented as 0\.05\. finalRateRounding \: Optional Rounding \^ The rounding convention to apply to the final rate used in determination of a calculation period amount\. averagingMethod \: Optional AveragingMethodEnum \^ If averaging is applicable, this component specifies whether a weighted or unweighted average method of calculation is to be used\. The component must only be included when averaging applies\. negativeInterestRateTreatment \: Optional NegativeInterestRateTreatmentEnum \^ The specification of any provisions for calculating payment obligations when a floating rate is negative (either due to a quoted negative floating rate or by operation of a spread that is subtracted from the floating rate)\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `FloatingRateCalculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-65118_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `FloatingRateCalculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-65118_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-9742:

**data** `FxLinkedNotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-9742_>`_

  The notional amount or notional amount schedule (FX linked)\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-95887:

  `FxLinkedNotionalSchedule <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-95887_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - constantNotionalScheduleReference
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - initialValue
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         -
       * - varyingNotionalCurrency
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - varyingNotionalFixingDates
         - `FixingDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-87647_>`_
         -
       * - fxSpotRateSource
         - `FxSpotRateSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxspotratesource-67475_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `FxLinkedNotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-9742_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `FxLinkedNotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-9742_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxspotratesource-67475:

**data** `FxSpotRateSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxspotratesource-67475_>`_

  A type defining the rate source and fixing time for
  an fx rate\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxspotratesource-21706:

  `FxSpotRateSource <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxspotratesource-21706_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - primaryRateSource
         - `InformationSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-informationsource-42318_>`_
         - The primary source for where the rate observation will occur\. Will typically be either a page or a reference bank published rate\. secondaryRateSource \: Optional InformationSource \^ An alternative, or secondary, source for where the rate observation will occur\. Will typically be either a page or a reference bank published rate\.
       * - fixingTime
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `BusinessCenterTime <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businesscentertime-18156_>`_
         - The time at which the spot currency exchange rate will be observed\. It is specified as a time in a business day calendar location, e\.g\., 11\:00am London time\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `FxSpotRateSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxspotratesource-67475_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `FxSpotRateSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxspotratesource-67475_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-hourminutetime-69567:

**type** `HourMinuteTime <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-hourminutetime-69567_>`_
  \= `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

  A type defining a time specified in hh\:mm\:ss format where the second component must be '00',
  e\.g\., 11am would be represented as 11\:00\:00\.

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-informationsource-42318:

**data** `InformationSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-informationsource-42318_>`_

  A type defining the source for a piece of information (e\.g\. a rate refix or an fx fixing)\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-informationsource-33837:

  `InformationSource <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-informationsource-33837_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - rateSource
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - An information source for obtaining a market rate\. For example, Bloomberg, Reuters, Telerate etc\. rateSourcePage \: Optional RateSourcePage
       * - rateSourcePage
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A specific page for the rate source for obtaining a market rate\. rateSourcePageHeading \: Optional String \^ The heading for the rate source on a given rate source page\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `InformationSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-informationsource-42318_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `InformationSource <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-informationsource-42318_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedule-89363:

**data** `NotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedule-89363_>`_

  The notional amount or notional amount schedule\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedule-46206:

  `NotionalSchedule <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedule-46206_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - notionalStepSchedule
         - `NotionalStepSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalstepschedule-61517_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `NotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedule-89363_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `NotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedule-89363_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedulevalue-48881:

**data** `NotionalScheduleValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedulevalue-48881_>`_

  Specifies how the notional schedule is defined\: either regular or fx linked\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalscheduleregular-96595:

  `NotionalSchedule_Regular <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalscheduleregular-96595_>`_ `NotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedule-89363_>`_

    Regular notional schedule\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedulefxlinked-32855:

  `NotionalSchedule_FxLinked <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedulefxlinked-32855_>`_ `FxLinkedNotionalSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fxlinkednotionalschedule-9742_>`_

    FX linked notional schedule\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `NotionalScheduleValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedulevalue-48881_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `NotionalScheduleValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalschedulevalue-48881_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalstepschedule-61517:

**data** `NotionalStepSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalstepschedule-61517_>`_

  The notional amount or notional amount schedule expressed as explicit outstanding notional
  amounts and dates\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalstepschedule-47772:

  `NotionalStepSchedule <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalstepschedule-47772_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - initialValue
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         -
       * - step
         - \[`Step <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-step-69338_>`_\]
         -
       * - currency
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `NotionalStepSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalstepschedule-61517_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `NotionalStepSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-notionalstepschedule-61517_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentdates-54029:

**data** `PaymentDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentdates-54029_>`_

  The payment dates schedule\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentdates-27056:

  `PaymentDates <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentdates-27056_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - calculationPeriodDatesReference
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - paymentFrequency
         - `PaymentFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentfrequency-58152_>`_
         -
       * - firstPaymentDate
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         -
       * - lastRegularPaymentDate
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         -
       * - payRelativeTo
         - `DateRelativeToEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daterelativetoenum-54982_>`_
         -
       * - paymentDatesAdjustments
         - `BusinessDayAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-businessdayadjustments-31058_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `PaymentDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentdates-54029_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `PaymentDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentdates-54029_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentfrequency-58152:

**data** `PaymentFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentfrequency-58152_>`_

  The frequency at which regular payment dates occur\. If the payment frequency is equal to the
  frequency defined in the calculation period dates component then one calculation period
  contributes to each payment amount\. If the payment frequency is less frequent than the
  frequency defined in the calculation period dates component then more than one calculation
  period will contribute to the payment amount\. A payment frequency more frequent than the
  calculation period frequency or one that is not a multiple of the calculation period frequency
  is invalid\. If the payment frequency is of value T (term), the period is defined by the
  swap\\swapStream\\calculationPerioDates\\effectiveDate and the
  swap\\swapStream\\calculationPerioDates\\terminationDate\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentfrequency-8369:

  `PaymentFrequency <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentfrequency-8369_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - periodMultiplier
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         -
       * - period
         - :ref:`PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659>`
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `PaymentFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentfrequency-58152_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `PaymentFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentfrequency-58152_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-44478:

**data** `PrincipalExchanges <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-44478_>`_

  A type defining which principal exchanges occur for
  the stream\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-61115:

  `PrincipalExchanges <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-61115_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - initialExchange
         - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
         - A true/false flag to indicate whether there is an initial exchange of principal on the effective date\.
       * - finalExchange
         - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
         - A true/false flag to indicate whether there is a final exchange of principal on the termination date\.
       * - intermediateExchange
         - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
         - A true/false flag to indicate whether there are intermediate or interim exchanges of principal during the term of the swap\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `PrincipalExchanges <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-44478_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `PrincipalExchanges <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-44478_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypevalue-5034:

**data** `RateTypeValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypevalue-5034_>`_

  Specifies whether the swapStream has a fixed or a floating rate\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypefixed-9778:

  `RateType_Fixed <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypefixed-9778_>`_ `FixedRateSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixedrateschedule-21284_>`_

    Fixed rate\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypefloating-65775:

  `RateType_Floating <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypefloating-65775_>`_ `FloatingRateCalculation <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-floatingratecalculation-65118_>`_

    Floating rate\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `RateTypeValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypevalue-5034_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `RateTypeValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-ratetypevalue-5034_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-61198:

**data** `ResetDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-61198_>`_

  The reset dates schedule\. This only applies for a floating rate stream\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-44651:

  `ResetDates <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-44651_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - calculationPeriodDatesReference
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - resetRelativeTo
         - `DateRelativeToEnum <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-daterelativetoenum-54982_>`_
         -
       * - fixingDates
         - `FixingDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-fixingdates-87647_>`_
         -
       * - resetFrequency
         - `ResetFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetfrequency-87171_>`_
         -
       * - resetDatesAdjustments
         - `ResetDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdatesadjustments-23359_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `ResetDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-61198_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `ResetDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-61198_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdatesadjustments-23359:

**data** `ResetDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdatesadjustments-23359_>`_

  The business day convention to apply to each reset date if it would otherwise fall on a day
  that is not a business day in the specified financial business centers\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdatesadjustments-69412:

  `ResetDatesAdjustments <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdatesadjustments-69412_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - businessDayConvention
         - :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>`
         -
       * - businessCenters
         - \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\]
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `ResetDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdatesadjustments-23359_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `ResetDatesAdjustments <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdatesadjustments-23359_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetfrequency-87171:

**data** `ResetFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetfrequency-87171_>`_

  The frequency at which reset dates occur\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetfrequency-86178:

  `ResetFrequency <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetfrequency-86178_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - periodMultiplier
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         -
       * - period
         - :ref:`PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659>`
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `ResetFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetfrequency-87171_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `ResetFrequency <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetfrequency-87171_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-spreadschedule-59448:

**data** `SpreadSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-spreadschedule-59448_>`_

  Adds an optional spread type element to the Schedule to identify a long or short spread value\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-spreadschedule-80225:

  `SpreadSchedule <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-spreadschedule-80225_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - initialValue
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - The initial rate or amount, as the case may be\. An initial rate of 5% would be represented as 0\.05\. step \: \[Step\] \^ The schedule of step date and value pairs\. On each step date the associated step value becomes effective\. A list of steps may be ordered in the document by ascending step date\. An FpML document containing an unordered list of steps is still regarded as a conformant document\. type\_ \: Optional SpreadScheduleType

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `SpreadSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-spreadschedule-59448_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `SpreadSchedule <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-spreadschedule-59448_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-step-69338:

**data** `Step <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-step-69338_>`_

  The schedule of step date and non\-negative value pairs\. On each step date the associated step
  value becomes effective\. A list of steps may be ordered in the document by ascending step date\.
  An FpML document containing an unordered list of steps is still regarded as a conformant
  document\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-step-98131:

  `Step <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-step-98131_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - stepDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         -
       * - stepValue
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Step <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-step-69338_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Step <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-step-69338_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-23577:

**data** `StubCalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-23577_>`_

  The stub calculation period amount parameters\. This element must only be included if there is
  an initial or final stub calculation period\. Even then, it must only be included if either the
  stub references a different floating rate tenor to the regular calculation periods, or if the
  stub is calculated as a linear interpolation of two different floating rate tenors, or if a
  specific stub rate or stub amount has been negotiated\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-44422:

  `StubCalculationPeriodAmount <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-44422_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - calculationPeriodDatesReference
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - initialStub
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `StubValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvalue-47596_>`_
         -
       * - finalStub
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `StubValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvalue-47596_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `StubCalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-23577_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `StubCalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-23577_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656:

**data** `StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656_>`_

  The rates to be applied to the initial or final stub may be the linear interpolation of two
  different rates\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-92621:

  `StubFloatingRate <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-92621_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - floatingRateIndex
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - indexTenor
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Period <type-daml-finance-interface-types-date-rollconvention-period-21180>`
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvalue-47596:

**data** `StubValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvalue-47596_>`_

  Specifies how the stub amount is calculated\. A single floating rate tenor different to that
  used for the regular part of the calculation periods schedule may be specified, or two floating
  tenors may be specified\. If two floating rate tenors are specified then Linear Interpolation
  (in accordance with the 2000 ISDA Definitions, Section 8\.3\. Interpolation) is assumed to apply\.
  Alternatively, an actual known stub rate or stub amount may be specified\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvaluefloatingrate-69521:

  `StubValue_FloatingRate <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvaluefloatingrate-69521_>`_ \[`StubFloatingRate <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubfloatingrate-69656_>`_\]

    The rates to be applied to the initial or final stub may be the linear interpolation of two
    different rates\. While the majority of the time, the rate indices will be the same as that
    specified in the stream and only the tenor itself will be different, it is possible to
    specift two different rates\. For example, a 2 month stub period may use the linear
    interpolation of a 1 month and 3 month rate\. The different rates would be specified in this
    component\. Note that a maximum of two rates can be specified\. If a stub period uses the
    same floating rate index, including tenor, as the regular calculation periods then this
    should not be specified again within this component, i\.e\., the stub calculation period
    amount component may not need to be specified even if there is an initial or final stub
    period\. If a stub period uses a different floating rate index compared to the regular
    calculation periods then this should be specified within this component\. If specified here,
    they are likely to have id attributes, allowing them to be referenced from within the
    cashflows component\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvaluestubrate-28947:

  `StubValue_StubRate <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvaluestubrate-28947_>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

    An actual rate to apply for the initial or final stub period may have been agreed between
    the principal parties (in a similar way to how an initial rate may have been agreed for the
    first regular period)\. If an actual stub rate has been agreed then it would be included in
    this component\. It will be a per annum rate, expressed as a decimal\. A stub rate of 5%
    would be represented as 0\.05\.
    | StubValue\_StubAmount Money
    \^ An actual amount to apply for the initial or final stub period may have been agreed between
    the two parties\. If an actual stub amount has been agreed then it would be included in this
    component\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `StubValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvalue-47596_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `StubValue <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubvalue-47596_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811:

**data** `SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811_>`_

  The swap streams, describing each leg of the swap\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-52622:

  `SwapStream <constr-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-52622_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - payerPartyReference
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - receiverPartyReference
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - calculationPeriodDates
         - `CalculationPeriodDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperioddates-27905_>`_
         -
       * - paymentDates
         - `PaymentDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-paymentdates-54029_>`_
         -
       * - resetDates
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `ResetDates <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-resetdates-61198_>`_
         -
       * - calculationPeriodAmount
         - `CalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-calculationperiodamount-361_>`_
         -
       * - stubCalculationPeriodAmount
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `StubCalculationPeriodAmount <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-stubcalculationperiodamount-23577_>`_
         -
       * - principalExchanges
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `PrincipalExchanges <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-principalexchanges-44478_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811_>`_
