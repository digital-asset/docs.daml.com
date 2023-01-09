.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-types-date-schedule-61944:

Module Daml.Finance.Interface.Types.Date.Schedule
=================================================

Data Types
----------

.. _type-daml-finance-interface-types-date-schedule-frequency-38655:

**data** `Frequency <type-daml-finance-interface-types-date-schedule-frequency-38655_>`_

  Frequency of a periodic schedule\.

  .. _constr-daml-finance-interface-types-date-schedule-frequency-73166:

  `Frequency <constr-daml-finance-interface-types-date-schedule-frequency-73166_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - period
         - :ref:`PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659>`
         - The period, e\.g\., day, month, etc\.
       * - periodMultiplier
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         - The period multiplier\.
       * - rollConvention
         - :ref:`RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360>`
         - The roll convention\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Frequency <type-daml-finance-interface-types-date-schedule-frequency-38655_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Frequency <type-daml-finance-interface-types-date-schedule-frequency-38655_>`_

.. _type-daml-finance-interface-types-date-schedule-periodicschedule-97930:

**data** `PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930_>`_

  A periodic schedule\.

  .. _constr-daml-finance-interface-types-date-schedule-periodicschedule-99705:

  `PeriodicSchedule <constr-daml-finance-interface-types-date-schedule-periodicschedule-99705_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - effectiveDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - Effective date, i\.e\., the (unadjusted) start date of the first period\.
       * - terminationDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - Termination date, i\.e\., the (unadjusted) end date of the last period\.
       * - firstRegularPeriodStartDate
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - The (unadjusted) start date of the first regular period (optional)\.
       * - lastRegularPeriodEndDate
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - The (unadjusted) end date of the last regular period (optional)\.
       * - frequency
         - `Frequency <type-daml-finance-interface-types-date-schedule-frequency-38655_>`_
         - The frequency of the periodic schedule\.
       * - businessDayAdjustment
         - :ref:`BusinessDayAdjustment <type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933>`
         - The business day adjustment to determine adjusted dates\.
       * - effectiveDateBusinessDayAdjustment
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`BusinessDayAdjustment <type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933>`
         - The (optional) business day adjustment of the effective date
       * - terminationDateBusinessDayAdjustment
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`BusinessDayAdjustment <type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933>`
         - The (optional) business day adjustment of the termination date
       * - stubPeriodType
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372_>`_
         - An optional stub to define a stub implicitly and not via ``firstRegularPeriodStartDate`` or ``lastRegularPeriodEndDate``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930_>`_

.. _type-daml-finance-interface-types-date-schedule-schedule-17285:

**type** `Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285_>`_
  \= \[`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784_>`_\]

  A schedule defined by a list of periods\.

.. _type-daml-finance-interface-types-date-schedule-scheduleperiod-76784:

**data** `SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784_>`_

  A single period in a schedule\.

  .. _constr-daml-finance-interface-types-date-schedule-scheduleperiod-14071:

  `SchedulePeriod <constr-daml-finance-interface-types-date-schedule-scheduleperiod-14071_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - adjustedEndDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - Adjusted end date\.
       * - adjustedStartDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - Adjusted start date\.
       * - unadjustedEndDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - Unadjusted end date\.
       * - unadjustedStartDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - Unadjusted start date\.
       * - stubType
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372_>`_
         - Indicates whether this period is a stub (and if so, what type of stub it is)

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784_>`_

.. _type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372:

**data** `StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372_>`_

  An enum type to specify a stub\.

  .. _constr-daml-finance-interface-types-date-schedule-longfinal-23770:

  `LongFinal <constr-daml-finance-interface-types-date-schedule-longfinal-23770_>`_

    A long (more than one period) final stub\.

  .. _constr-daml-finance-interface-types-date-schedule-longinitial-38264:

  `LongInitial <constr-daml-finance-interface-types-date-schedule-longinitial-38264_>`_

    A long (more than one period) initial stub\.

  .. _constr-daml-finance-interface-types-date-schedule-shortfinal-29169:

  `ShortFinal <constr-daml-finance-interface-types-date-schedule-shortfinal-29169_>`_

    A short (less than one period) final stub\.

  .. _constr-daml-finance-interface-types-date-schedule-shortinitial-42143:

  `ShortInitial <constr-daml-finance-interface-types-date-schedule-shortinitial-42143_>`_

    A short (less than one period) initial stub\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372_>`_
