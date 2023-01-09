.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-data-reference-time-54882:

Module Daml.Finance.Interface.Data.Reference.Time
=================================================

This module defines an interface for ``BusinessTime`` rules, which are contracts to control and
keep track of business time\.

Interfaces
----------

.. _type-daml-finance-interface-data-reference-time-time-91391:

**interface** `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_

  An interface to manage and control business time\. Controlled time rules (i\.e\. clocks) are
  managed by entities that have control certain business time events\. These can be trading\-open /
  \-close on an exchange, start\-of\-day / end\-of\-day events of a trading desk, or just a daily
  clock tick to signal the passing of aticking\. Intervals in which
  the clock \"ticks\" don't have to be regular, and can e\.g\. consider business days only\.

  + **Choice Advance**

    Advance time to its next state\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - eventId
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Event identifier\.
       * - eventDescription
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Event description\.

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
         - The party retrieving the view\.

  + **Choice Rewind**

    Rewind time to its previous state\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - eventId
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Event identifier\.
       * - eventDescription
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Event description\.

  + **Method advance \:** Advance \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Event <type-daml-finance-interface-lifecycle-event-time-event-90457>`)

    Implementation of the ``Advance`` choice\.

  + **Method asTimeObservable \:** :ref:`I <type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421>`

  + **Method rewind \:** Rewind \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Event <type-daml-finance-interface-lifecycle-event-time-event-90457>`)

    Implementation of the ``Rewind`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-data-reference-time-hasimplementation-48746:

**class** `Implementation <type-daml-finance-interface-data-reference-time-implementation-34332_>`_ t \=\> `HasImplementation <class-daml-finance-interface-data-reference-time-hasimplementation-48746_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-data-reference-time-i-30870:

**type** `I <type-daml-finance-interface-data-reference-time-i-30870_>`_
  \= `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_

  Type synonym for ``Time``\.

.. _type-daml-finance-interface-data-reference-time-implementation-34332:

**type** `Implementation <type-daml-finance-interface-data-reference-time-implementation-34332_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_, :ref:`Implementation <type-daml-finance-interface-lifecycle-observable-timeobservable-implementation-4157>` t)

  Type constraint for requiring templates to implement ``Time``\.

.. _type-daml-finance-interface-data-reference-time-v-63297:

**type** `V <type-daml-finance-interface-data-reference-time-v-63297_>`_
  \= `View <type-daml-finance-interface-data-reference-time-view-14455_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_ `V <type-daml-finance-interface-data-reference-time-v-63297_>`_

.. _type-daml-finance-interface-data-reference-time-view-14455:

**data** `View <type-daml-finance-interface-data-reference-time-view-14455_>`_

  View for ``Time``\.

  .. _constr-daml-finance-interface-data-reference-time-view-58532:

  `View <constr-daml-finance-interface-data-reference-time-view-58532_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - providers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties controlling time\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Textual identifier for the time rule\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-data-reference-time-view-14455_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-data-reference-time-view-14455_>`_

Functions
---------

.. _function-daml-finance-interface-data-reference-time-astimeobservable-25104:

`asTimeObservable <function-daml-finance-interface-data-reference-time-astimeobservable-25104_>`_
  \: `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_ \-\> :ref:`I <type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421>`

.. _function-daml-finance-interface-data-reference-time-advance-98051:

`advance <function-daml-finance-interface-data-reference-time-advance-98051_>`_
  \: `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_ \-\> Advance \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Event <type-daml-finance-interface-lifecycle-event-time-event-90457>`)

.. _function-daml-finance-interface-data-reference-time-rewind-33531:

`rewind <function-daml-finance-interface-data-reference-time-rewind-33531_>`_
  \: `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_ \-\> Rewind \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Time <type-daml-finance-interface-data-reference-time-time-91391_>`_, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Event <type-daml-finance-interface-lifecycle-event-time-event-90457>`)
