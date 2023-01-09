.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-data-reference-holidaycalendar-19648:

Module Daml.Finance.Interface.Data.Reference.HolidayCalendar
============================================================

Interfaces
----------

.. _type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549:

**interface** `HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549_>`_

  Interface for contracts storing holiday calendar data on the ledger\.

  + **Choice Archive**

    (no fields)

  + **Choice GetView**

    Retrieves the interface view\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party fetching the view\.

  + **Choice UpdateCalendar**

    Updates the holiday calendar\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - newCalendar
         - :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`
         - The new ``HolidayCalendarData``\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method updateCalendar \:** UpdateCalendar \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549_>`_)

    Updates the holiday calendar\.

Typeclasses
-----------

.. _class-daml-finance-interface-data-reference-holidaycalendar-hasimplementation-34198:

**class** `Implementation <type-daml-finance-interface-data-reference-holidaycalendar-implementation-87002_>`_ t \=\> `HasImplementation <class-daml-finance-interface-data-reference-holidaycalendar-hasimplementation-34198_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-data-reference-holidaycalendar-i-45368:

**type** `I <type-daml-finance-interface-data-reference-holidaycalendar-i-45368_>`_
  \= `HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549_>`_

  Type synonym for ``HolidayCalendar``\.

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-data-reference-holidaycalendar-i-45368_>`_))

.. _type-daml-finance-interface-data-reference-holidaycalendar-implementation-87002:

**type** `Implementation <type-daml-finance-interface-data-reference-holidaycalendar-implementation-87002_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-data-reference-holidaycalendar-i-45368_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``HolidayCalendar`` along with ``Disclosure``\.

.. _type-daml-finance-interface-data-reference-holidaycalendar-v-21375:

**type** `V <type-daml-finance-interface-data-reference-holidaycalendar-v-21375_>`_
  \= `View <type-daml-finance-interface-data-reference-holidaycalendar-view-65781_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549_>`_ `V <type-daml-finance-interface-data-reference-holidaycalendar-v-21375_>`_

.. _type-daml-finance-interface-data-reference-holidaycalendar-view-65781:

**data** `View <type-daml-finance-interface-data-reference-holidaycalendar-view-65781_>`_

  View for ``HolidayCalendar``\.

  .. _constr-daml-finance-interface-data-reference-holidaycalendar-view-83984:

  `View <constr-daml-finance-interface-data-reference-holidaycalendar-view-83984_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The parties providing the ``HolidayCalendar``\.
       * - calendar
         - :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`
         - Holiday Calendar Data used to define holidays\.

Functions
---------

.. _function-daml-finance-interface-data-reference-holidaycalendar-asdisclosure-18593:

`asDisclosure <function-daml-finance-interface-data-reference-holidaycalendar-asdisclosure-18593_>`_
  \: `HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-data-reference-holidaycalendar-updatecalendar-54401:

`updateCalendar <function-daml-finance-interface-data-reference-holidaycalendar-updatecalendar-54401_>`_
  \: `HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549_>`_ \-\> UpdateCalendar \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549_>`_)
