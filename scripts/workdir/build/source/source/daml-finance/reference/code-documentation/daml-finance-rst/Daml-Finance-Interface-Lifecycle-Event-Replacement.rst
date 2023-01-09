.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-event-replacement-2440:

Module Daml.Finance.Interface.Lifecycle.Event.Replacement
=========================================================

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-event-replacement-event-46565:

**interface** `Event <type-daml-finance-interface-lifecycle-event-replacement-event-46565_>`_

  Event interface for the replacement of units of an instrument with a basket of other
  instruments (e\.g\. stock merger)\.

  + **Choice Archive**

    (no fields)

  + **Choice GetView**

    Retrieves the event view\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party retrieving the view\.

  + **Method asEvent \:** :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`

    Conversion to base ``Event`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-event-replacement-hasimplementation-5972:

**class** `Implementation <type-daml-finance-interface-lifecycle-event-replacement-implementation-44134_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-event-replacement-hasimplementation-5972_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-event-replacement-i-34852:

**type** `I <type-daml-finance-interface-lifecycle-event-replacement-i-34852_>`_
  \= `Event <type-daml-finance-interface-lifecycle-event-replacement-event-46565_>`_

  Type synonym for ``Event``\.

.. _type-daml-finance-interface-lifecycle-event-replacement-implementation-44134:

**type** `Implementation <type-daml-finance-interface-lifecycle-event-replacement-implementation-44134_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Event <type-daml-finance-interface-lifecycle-event-replacement-event-46565_>`_, :ref:`Implementation <type-daml-finance-interface-lifecycle-event-implementation-22192>` t)

  Type constraint for requiring templates to implement ``Event``\.

.. _type-daml-finance-interface-lifecycle-event-replacement-v-6579:

**type** `V <type-daml-finance-interface-lifecycle-event-replacement-v-6579_>`_
  \= `View <type-daml-finance-interface-lifecycle-event-replacement-view-89113_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Event <type-daml-finance-interface-lifecycle-event-replacement-event-46565_>`_ `V <type-daml-finance-interface-lifecycle-event-replacement-v-6579_>`_

.. _type-daml-finance-interface-lifecycle-event-replacement-view-89113:

**data** `View <type-daml-finance-interface-lifecycle-event-replacement-view-89113_>`_

  View for ``Event``\.

  .. _constr-daml-finance-interface-lifecycle-event-replacement-view-59094:

  `View <constr-daml-finance-interface-lifecycle-event-replacement-view-59094_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - effectiveTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Time on which the replacement is effectuated\.
       * - targetInstrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - Instrument the replacement event applies to\.
       * - perUnitReplacement
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Instrument quantities the target instrument is replaced with\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-event-replacement-view-89113_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-event-replacement-view-89113_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-event-replacement-asevent-26575:

`asEvent <function-daml-finance-interface-lifecycle-event-replacement-asevent-26575_>`_
  \: `Event <type-daml-finance-interface-lifecycle-event-replacement-event-46565_>`_ \-\> :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`
