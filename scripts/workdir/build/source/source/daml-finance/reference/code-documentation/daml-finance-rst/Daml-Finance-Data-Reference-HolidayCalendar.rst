.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-data-reference-holidaycalendar-10773:

Module Daml.Finance.Data.Reference.HolidayCalendar
==================================================

Templates
---------

.. _type-daml-finance-data-reference-holidaycalendar-factory-17210:

**template** `Factory <type-daml-finance-data-reference-holidaycalendar-factory-17210_>`_

  Implementation of the corresponding HolidayCalendar Factory\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The factory's provider\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The factory's observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`F <type-daml-finance-interface-data-reference-holidaycalendar-factory-f-7191>` **for** `Factory <type-daml-finance-data-reference-holidaycalendar-factory-17210_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-data-reference-holidaycalendar-factory-17210_>`_

.. _type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470:

**template** `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_

  Holiday calendar of an entity (typically an exchange or a currency)\.
  It is maintained by a reference data provider\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - calendar
       - :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`
       - Holiday Calendar Data used to define holidays\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The party maintaining the ``HolidayCalendar``\.

  + **Choice Archive**

    (no fields)

  + **Choice GetCalendar**

    Returns the calendar's ``HolidayCalendarData``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party fetching the calendar\.

  + **interface instance** :ref:`I <type-daml-finance-interface-data-reference-holidaycalendar-i-45368>` **for** `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_

Data Types
----------

.. _type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330:

**data** `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  Key used to look up the holiday calendar of an entity, as defined by a reference data provider\.

  .. _constr-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-86743:

  `HolidayCalendarKey <constr-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-86743_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party maintaining the ``HolidayCalendar``\.
       * - id
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A textual label identifying the calendar (e\.g\. \"NYSE\" for the New York Stock Exchange holiday calendar)\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_ GetCalendar :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_ `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ `HolidayCalendar <type-daml-finance-data-reference-holidaycalendar-holidaycalendar-1470_>`_ `HolidayCalendarKey <type-daml-finance-data-reference-holidaycalendar-holidaycalendarkey-10330_>`_
