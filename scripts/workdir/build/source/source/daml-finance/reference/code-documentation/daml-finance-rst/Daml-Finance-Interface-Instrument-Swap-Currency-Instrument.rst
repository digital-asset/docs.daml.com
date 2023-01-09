.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-currency-instrument-11782:

Module Daml.Finance.Interface.Instrument.Swap.Currency.Instrument
=================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-swap-currency-instrument-instrument-50369:

**interface** `Instrument <type-daml-finance-interface-instrument-swap-currency-instrument-instrument-50369_>`_

  Instrument interface representing a currency swap\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-swap-currency-instrument-hasimplementation-97330:

**class** `Implementation <type-daml-finance-interface-instrument-swap-currency-instrument-implementation-14932_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-swap-currency-instrument-hasimplementation-97330_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-swap-currency-instrument-i-90910:

**type** `I <type-daml-finance-interface-instrument-swap-currency-instrument-i-90910_>`_
  \= `Instrument <type-daml-finance-interface-instrument-swap-currency-instrument-instrument-50369_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-swap-currency-instrument-implementation-14932:

**type** `Implementation <type-daml-finance-interface-instrument-swap-currency-instrument-implementation-14932_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-swap-currency-instrument-instrument-50369_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-swap-currency-instrument-v-53817:

**type** `V <type-daml-finance-interface-instrument-swap-currency-instrument-v-53817_>`_
  \= `View <type-daml-finance-interface-instrument-swap-currency-instrument-view-25999_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-swap-currency-instrument-instrument-50369_>`_ `V <type-daml-finance-interface-instrument-swap-currency-instrument-v-53817_>`_

.. _type-daml-finance-interface-instrument-swap-currency-instrument-view-25999:

**data** `View <type-daml-finance-interface-instrument-swap-currency-instrument-view-25999_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-swap-currency-instrument-view-5224:

  `View <constr-daml-finance-interface-instrument-swap-currency-instrument-view-5224_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - currencySwap
         - :ref:`CurrencySwap <type-daml-finance-interface-instrument-swap-currency-types-currencyswap-33117>`
         - Attributes of a currency swap\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-swap-currency-instrument-view-25999_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-swap-currency-instrument-view-25999_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-swap-currency-instrument-asbaseinstrument-11068:

`asBaseInstrument <function-daml-finance-interface-instrument-swap-currency-instrument-asbaseinstrument-11068_>`_
  \: `Instrument <type-daml-finance-interface-instrument-swap-currency-instrument-instrument-50369_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
