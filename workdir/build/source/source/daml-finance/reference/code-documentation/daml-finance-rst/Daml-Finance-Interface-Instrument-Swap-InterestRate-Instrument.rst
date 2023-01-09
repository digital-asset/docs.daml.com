.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-interestrate-instrument-49463:

Module Daml.Finance.Interface.Instrument.Swap.InterestRate.Instrument
=====================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-swap-interestrate-instrument-instrument-68848:

**interface** `Instrument <type-daml-finance-interface-instrument-swap-interestrate-instrument-instrument-68848_>`_

  Instrument interface representing an interest rate swap\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-swap-interestrate-instrument-hasimplementation-56341:

**class** `Implementation <type-daml-finance-interface-instrument-swap-interestrate-instrument-implementation-77761_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-swap-interestrate-instrument-hasimplementation-56341_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-swap-interestrate-instrument-i-65057:

**type** `I <type-daml-finance-interface-instrument-swap-interestrate-instrument-i-65057_>`_
  \= `Instrument <type-daml-finance-interface-instrument-swap-interestrate-instrument-instrument-68848_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-swap-interestrate-instrument-implementation-77761:

**type** `Implementation <type-daml-finance-interface-instrument-swap-interestrate-instrument-implementation-77761_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-swap-interestrate-instrument-instrument-68848_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-swap-interestrate-instrument-v-32630:

**type** `V <type-daml-finance-interface-instrument-swap-interestrate-instrument-v-32630_>`_
  \= `View <type-daml-finance-interface-instrument-swap-interestrate-instrument-view-60770_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-swap-interestrate-instrument-instrument-68848_>`_ `V <type-daml-finance-interface-instrument-swap-interestrate-instrument-v-32630_>`_

.. _type-daml-finance-interface-instrument-swap-interestrate-instrument-view-60770:

**data** `View <type-daml-finance-interface-instrument-swap-interestrate-instrument-view-60770_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-swap-interestrate-instrument-view-32477:

  `View <constr-daml-finance-interface-instrument-swap-interestrate-instrument-view-32477_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - interestRate
         - :ref:`InterestRate <type-daml-finance-interface-instrument-swap-interestrate-types-interestrate-57390>`
         - Attributes of an interest rate swap\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-swap-interestrate-instrument-view-60770_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-swap-interestrate-instrument-view-60770_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-swap-interestrate-instrument-asbaseinstrument-59393:

`asBaseInstrument <function-daml-finance-interface-instrument-swap-interestrate-instrument-asbaseinstrument-59393_>`_
  \: `Instrument <type-daml-finance-interface-instrument-swap-interestrate-instrument-instrument-68848_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
