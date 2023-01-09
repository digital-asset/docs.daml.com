.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-data-reference-holidaycalendar-factory-22148:

Module Daml.Finance.Interface.Data.Reference.HolidayCalendar.Factory
====================================================================

Interfaces
----------

.. _type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729:

**interface** `Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729_>`_

  Interface that allows implementing templates to create holiday calendars\.

  + **Choice Archive**

    (no fields)

  + **Choice Create**

    Create a new Holiday Calendar\.

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
         - The calendar's provider\.

  + **Choice Remove**

    Archive an Holiday Calendar\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - calendarCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-data-reference-holidaycalendar-i-45368>`
         - The calendar's contractid\.
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The calendar's provider\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-data-reference-holidaycalendar-i-45368>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-data-reference-holidaycalendar-factory-hasimplementation-72090:

**class** `Implementation <type-daml-finance-interface-data-reference-holidaycalendar-factory-implementation-33922_>`_ t \=\> `HasImplementation <class-daml-finance-interface-data-reference-holidaycalendar-factory-hasimplementation-72090_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-data-reference-holidaycalendar-factory-f-7191:

**type** `F <type-daml-finance-interface-data-reference-holidaycalendar-factory-f-7191_>`_
  \= `Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-data-reference-holidaycalendar-factory-implementation-33922:

**type** `Implementation <type-daml-finance-interface-data-reference-holidaycalendar-factory-implementation-33922_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `F <type-daml-finance-interface-data-reference-holidaycalendar-factory-f-7191_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-data-reference-holidaycalendar-factory-v-76711:

**type** `V <type-daml-finance-interface-data-reference-holidaycalendar-factory-v-76711_>`_
  \= `View <type-daml-finance-interface-data-reference-holidaycalendar-factory-view-11773_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729_>`_ `V <type-daml-finance-interface-data-reference-holidaycalendar-factory-v-76711_>`_

.. _type-daml-finance-interface-data-reference-holidaycalendar-factory-view-11773:

**data** `View <type-daml-finance-interface-data-reference-holidaycalendar-factory-view-11773_>`_

  .. _constr-daml-finance-interface-data-reference-holidaycalendar-factory-view-48120:

  `View <constr-daml-finance-interface-data-reference-holidaycalendar-factory-view-48120_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-data-reference-holidaycalendar-factory-view-11773_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-data-reference-holidaycalendar-factory-view-11773_>`_

Functions
---------

.. _function-daml-finance-interface-data-reference-holidaycalendar-factory-asdisclosure-33449:

`asDisclosure <function-daml-finance-interface-data-reference-holidaycalendar-factory-asdisclosure-33449_>`_
  \: `Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-data-reference-holidaycalendar-factory-createtick-13624:

`create' <function-daml-finance-interface-data-reference-holidaycalendar-factory-createtick-13624_>`_
  \: `Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-data-reference-holidaycalendar-i-45368>`)

.. _function-daml-finance-interface-data-reference-holidaycalendar-factory-remove-77404:

`remove <function-daml-finance-interface-data-reference-holidaycalendar-factory-remove-77404_>`_
  \: `Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
