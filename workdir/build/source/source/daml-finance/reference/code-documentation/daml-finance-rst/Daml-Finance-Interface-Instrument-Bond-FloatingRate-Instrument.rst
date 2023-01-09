.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-floatingrate-instrument-46777:

Module Daml.Finance.Interface.Instrument.Bond.FloatingRate.Instrument
=====================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-bond-floatingrate-instrument-instrument-7806:

**interface** `Instrument <type-daml-finance-interface-instrument-bond-floatingrate-instrument-instrument-7806_>`_

  Instrument interface representing a floating rate bond\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-bond-floatingrate-instrument-hasimplementation-96379:

**class** `Implementation <type-daml-finance-interface-instrument-bond-floatingrate-instrument-implementation-96091_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-bond-floatingrate-instrument-hasimplementation-96379_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-bond-floatingrate-instrument-i-64015:

**type** `I <type-daml-finance-interface-instrument-bond-floatingrate-instrument-i-64015_>`_
  \= `Instrument <type-daml-finance-interface-instrument-bond-floatingrate-instrument-instrument-7806_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-bond-floatingrate-instrument-implementation-96091:

**type** `Implementation <type-daml-finance-interface-instrument-bond-floatingrate-instrument-implementation-96091_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-bond-floatingrate-instrument-instrument-7806_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-bond-floatingrate-instrument-v-48968:

**type** `V <type-daml-finance-interface-instrument-bond-floatingrate-instrument-v-48968_>`_
  \= `View <type-daml-finance-interface-instrument-bond-floatingrate-instrument-view-3812_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-bond-floatingrate-instrument-instrument-7806_>`_ `V <type-daml-finance-interface-instrument-bond-floatingrate-instrument-v-48968_>`_

.. _type-daml-finance-interface-instrument-bond-floatingrate-instrument-view-3812:

**data** `View <type-daml-finance-interface-instrument-bond-floatingrate-instrument-view-3812_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-bond-floatingrate-instrument-view-20199:

  `View <constr-daml-finance-interface-instrument-bond-floatingrate-instrument-view-20199_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - floatingRate
         - :ref:`FloatingRate <type-daml-finance-interface-instrument-bond-floatingrate-types-floatingrate-27992>`
         - Attributes of a floating rate bond\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-bond-floatingrate-instrument-view-3812_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-bond-floatingrate-instrument-view-3812_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-bond-floatingrate-instrument-asbaseinstrument-87695:

`asBaseInstrument <function-daml-finance-interface-instrument-bond-floatingrate-instrument-asbaseinstrument-87695_>`_
  \: `Instrument <type-daml-finance-interface-instrument-bond-floatingrate-instrument-instrument-7806_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
