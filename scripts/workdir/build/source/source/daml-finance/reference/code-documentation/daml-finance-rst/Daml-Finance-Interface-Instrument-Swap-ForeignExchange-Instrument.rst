.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-foreignexchange-instrument-90743:

Module Daml.Finance.Interface.Instrument.Swap.ForeignExchange.Instrument
========================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-swap-foreignexchange-instrument-instrument-74416:

**interface** `Instrument <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-instrument-74416_>`_

  Instrument interface representing an FX swap\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-swap-foreignexchange-instrument-hasimplementation-25399:

**class** `Implementation <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-implementation-17537_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-swap-foreignexchange-instrument-hasimplementation-25399_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-swap-foreignexchange-instrument-i-43105:

**type** `I <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-i-43105_>`_
  \= `Instrument <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-instrument-74416_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-swap-foreignexchange-instrument-implementation-17537:

**type** `Implementation <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-implementation-17537_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-instrument-74416_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-swap-foreignexchange-instrument-v-10678:

**type** `V <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-v-10678_>`_
  \= `View <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-view-47906_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-instrument-74416_>`_ `V <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-v-10678_>`_

.. _type-daml-finance-interface-instrument-swap-foreignexchange-instrument-view-47906:

**data** `View <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-view-47906_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-swap-foreignexchange-instrument-view-98651:

  `View <constr-daml-finance-interface-instrument-swap-foreignexchange-instrument-view-98651_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - foreignExchange
         - :ref:`ForeignExchange <type-daml-finance-interface-instrument-swap-foreignexchange-types-foreignexchange-32192>`
         - Attributes of an FX swap\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-view-47906_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-view-47906_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-swap-foreignexchange-instrument-asbaseinstrument-46001:

`asBaseInstrument <function-daml-finance-interface-instrument-swap-foreignexchange-instrument-asbaseinstrument-46001_>`_
  \: `Instrument <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-instrument-74416_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
