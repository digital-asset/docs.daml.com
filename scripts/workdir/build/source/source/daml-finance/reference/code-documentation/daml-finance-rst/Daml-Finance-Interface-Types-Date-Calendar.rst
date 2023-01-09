.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-types-date-calendar-23555:

Module Daml.Finance.Interface.Types.Date.Calendar
=================================================

Data Types
----------

.. _type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933:

**data** `BusinessDayAdjustment <type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933_>`_

  A data type to define how non\-business days are adjusted\.

  .. _constr-daml-finance-interface-types-date-calendar-businessdayadjustment-94056:

  `BusinessDayAdjustment <constr-daml-finance-interface-types-date-calendar-businessdayadjustment-94056_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - calendarIds
         - \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\]
         - A list of calendar ids to define holidays\.
       * - convention
         - `BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986_>`_
         - The business day convention used for the adjustment\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `BusinessDayAdjustment <type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `BusinessDayAdjustment <type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933_>`_

.. _type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986:

**data** `BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986_>`_

  An enum type to specify how a non\-business day is adjusted\.

  .. _constr-daml-finance-interface-types-date-calendar-following-80068:

  `Following <constr-daml-finance-interface-types-date-calendar-following-80068_>`_

    Adjust a non\-business day to the next business day\.

  .. _constr-daml-finance-interface-types-date-calendar-modifiedfollowing-81779:

  `ModifiedFollowing <constr-daml-finance-interface-types-date-calendar-modifiedfollowing-81779_>`_

    Adjust a non\-business day to the next business day
    unless it is not in the same month\. In this case use
    the previous business day\.

  .. _constr-daml-finance-interface-types-date-calendar-modifiedpreceding-94913:

  `ModifiedPreceding <constr-daml-finance-interface-types-date-calendar-modifiedpreceding-94913_>`_

    Adjust a non\-business day to the previous business day
    unless it is not in the same month\. In this case use
    the next business day\.

  .. _constr-daml-finance-interface-types-date-calendar-noadjustment-13478:

  `NoAdjustment <constr-daml-finance-interface-types-date-calendar-noadjustment-13478_>`_

    Non\-business days are not adjusted\.

  .. _constr-daml-finance-interface-types-date-calendar-preceding-57734:

  `Preceding <constr-daml-finance-interface-types-date-calendar-preceding-57734_>`_

    Adjust a non\-business day to the previous business day\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986_>`_

.. _type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004:

**data** `HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004_>`_

  Holiday Calendar Data used to define holidays (non\-business days)\.

  .. _constr-daml-finance-interface-types-date-calendar-holidaycalendardata-41957:

  `HolidayCalendarData <constr-daml-finance-interface-types-date-calendar-holidaycalendardata-41957_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - The id of the holiday calendar\.
       * - weekend
         - \[`DayOfWeek <https://docs.daml.com/daml/stdlib/DA-Date.html#type-da-date-types-dayofweek-18120>`_\]
         - A list of week days defining the weekend\.
       * - holidays
         - \[`Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_\]
         - A list of dates defining holidays\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004_>`_

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ :ref:`HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470>` :ref:`HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330>` GetCalendar `HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004_>`_
