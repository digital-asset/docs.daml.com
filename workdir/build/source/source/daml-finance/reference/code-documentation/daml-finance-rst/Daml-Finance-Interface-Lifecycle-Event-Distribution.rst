.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-event-distribution-91943:

Module Daml.Finance.Interface.Lifecycle.Event.Distribution
==========================================================

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-event-distribution-event-73224:

**interface** `Event <type-daml-finance-interface-lifecycle-event-distribution-event-73224_>`_

  Event interface for the distribution of units of an instrument for each unit of a target
  instrument (e\.g\. share or cash dividends)\.

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

.. _class-daml-finance-interface-lifecycle-event-distribution-hasimplementation-40767:

**class** `Implementation <type-daml-finance-interface-lifecycle-event-distribution-implementation-3945_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-event-distribution-hasimplementation-40767_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-event-distribution-i-8313:

**type** `I <type-daml-finance-interface-lifecycle-event-distribution-i-8313_>`_
  \= `Event <type-daml-finance-interface-lifecycle-event-distribution-event-73224_>`_

  Type synonym for ``Event``\.

.. _type-daml-finance-interface-lifecycle-event-distribution-implementation-3945:

**type** `Implementation <type-daml-finance-interface-lifecycle-event-distribution-implementation-3945_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Event <type-daml-finance-interface-lifecycle-event-distribution-event-73224_>`_, :ref:`Implementation <type-daml-finance-interface-lifecycle-event-implementation-22192>` t)

  Type constraint for requiring templates to implement ``Distribution``\.

.. _type-daml-finance-interface-lifecycle-event-distribution-v-45406:

**type** `V <type-daml-finance-interface-lifecycle-event-distribution-v-45406_>`_
  \= `View <type-daml-finance-interface-lifecycle-event-distribution-view-23882_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Event <type-daml-finance-interface-lifecycle-event-distribution-event-73224_>`_ `V <type-daml-finance-interface-lifecycle-event-distribution-v-45406_>`_

.. _type-daml-finance-interface-lifecycle-event-distribution-view-23882:

**data** `View <type-daml-finance-interface-lifecycle-event-distribution-view-23882_>`_

  View for ``Event``\.

  .. _constr-daml-finance-interface-lifecycle-event-distribution-view-77651:

  `View <constr-daml-finance-interface-lifecycle-event-distribution-view-77651_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - effectiveTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Time on which the distribution is effectuated\.
       * - targetInstrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - Instrument the distribution event applies to\.
       * - newInstrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - Instrument after the distribution has been claimed\.
       * - perUnitDistribution
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Distributed quantities per unit held\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-event-distribution-view-23882_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-event-distribution-view-23882_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-event-distribution-asevent-91086:

`asEvent <function-daml-finance-interface-lifecycle-event-distribution-asevent-91086_>`_
  \: `Event <type-daml-finance-interface-lifecycle-event-distribution-event-73224_>`_ \-\> :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`
