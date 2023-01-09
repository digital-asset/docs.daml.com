.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-event-43586:

Module Daml.Finance.Interface.Lifecycle.Event
=============================================

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-event-event-2931:

**interface** `Event <type-daml-finance-interface-lifecycle-event-event-2931_>`_

  A lifecycle event\. These events are ordered based on the corresponding event time\.

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


Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-event-hasimplementation-79426:

**class** `Implementation <type-daml-finance-interface-lifecycle-event-implementation-22192_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-event-hasimplementation-79426_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-event-i-17082:

**type** `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_
  \= `Event <type-daml-finance-interface-lifecycle-event-event-2931_>`_

  Type synonym for ``Event``\.

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859>` \"declareDividend\" (DeclareDividend \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859>` \"declareReplacement\" (DeclareReplacement \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859>` \"declareStockSplit\" (DeclareStockSplit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_))

  **instance** HasMethod :ref:`Election <type-daml-finance-interface-instrument-generic-election-election-25324>` \"asEvent\" `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_

  **instance** HasMethod :ref:`Event <type-daml-finance-interface-lifecycle-event-distribution-event-73224>` \"asEvent\" `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_

  **instance** HasMethod :ref:`Event <type-daml-finance-interface-lifecycle-event-replacement-event-46565>` \"asEvent\" `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_

  **instance** HasMethod :ref:`Event <type-daml-finance-interface-lifecycle-event-time-event-90457>` \"asEvent\" `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_

.. _type-daml-finance-interface-lifecycle-event-implementation-22192:

**type** `Implementation <type-daml-finance-interface-lifecycle-event-implementation-22192_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-lifecycle-event-i-17082_>`_

  Type constraint for requiring templates to implement ``Event``\.

.. _type-daml-finance-interface-lifecycle-event-v-14749:

**type** `V <type-daml-finance-interface-lifecycle-event-v-14749_>`_
  \= `View <type-daml-finance-interface-lifecycle-event-view-20515_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Event <type-daml-finance-interface-lifecycle-event-event-2931_>`_ `V <type-daml-finance-interface-lifecycle-event-v-14749_>`_

.. _type-daml-finance-interface-lifecycle-event-view-20515:

**data** `View <type-daml-finance-interface-lifecycle-event-view-20515_>`_

  View for ``Event``\.

  .. _constr-daml-finance-interface-lifecycle-event-view-84160:

  `View <constr-daml-finance-interface-lifecycle-event-view-84160_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - providers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Providers of the event\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Identifier for the event\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A human readable description of the event\.
       * - eventTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - The time of the event\. This allows ordering of events\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-event-view-20515_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-event-view-20515_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-event-geteventtime-83763:

`getEventTime <function-daml-finance-interface-lifecycle-event-geteventtime-83763_>`_
  \: `Event <type-daml-finance-interface-lifecycle-event-event-2931_>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_

  Given an event, retrieves the event time\.
