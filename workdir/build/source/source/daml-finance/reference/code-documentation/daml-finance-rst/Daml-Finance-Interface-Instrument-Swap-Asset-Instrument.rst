.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-asset-instrument-37258:

Module Daml.Finance.Interface.Instrument.Swap.Asset.Instrument
==============================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-swap-asset-instrument-instrument-70853:

**interface** `Instrument <type-daml-finance-interface-instrument-swap-asset-instrument-instrument-70853_>`_

  Instrument interface representing an asset swap\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-swap-asset-instrument-hasimplementation-10840:

**class** `Implementation <type-daml-finance-interface-instrument-swap-asset-instrument-implementation-60856_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-swap-asset-instrument-hasimplementation-10840_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-swap-asset-instrument-i-73906:

**type** `I <type-daml-finance-interface-instrument-swap-asset-instrument-i-73906_>`_
  \= `Instrument <type-daml-finance-interface-instrument-swap-asset-instrument-instrument-70853_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-swap-asset-instrument-implementation-60856:

**type** `Implementation <type-daml-finance-interface-instrument-swap-asset-instrument-implementation-60856_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-swap-asset-instrument-instrument-70853_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-swap-asset-instrument-v-63013:

**type** `V <type-daml-finance-interface-instrument-swap-asset-instrument-v-63013_>`_
  \= `View <type-daml-finance-interface-instrument-swap-asset-instrument-view-15851_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-swap-asset-instrument-instrument-70853_>`_ `V <type-daml-finance-interface-instrument-swap-asset-instrument-v-63013_>`_

.. _type-daml-finance-interface-instrument-swap-asset-instrument-view-15851:

**data** `View <type-daml-finance-interface-instrument-swap-asset-instrument-view-15851_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-swap-asset-instrument-view-35794:

  `View <constr-daml-finance-interface-instrument-swap-asset-instrument-view-35794_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - asset
         - :ref:`Asset <type-daml-finance-interface-instrument-swap-asset-types-asset-84576>`
         - Attributes of an asset swap\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-swap-asset-instrument-view-15851_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-swap-asset-instrument-view-15851_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-swap-asset-instrument-asbaseinstrument-69760:

`asBaseInstrument <function-daml-finance-interface-instrument-swap-asset-instrument-asbaseinstrument-69760_>`_
  \: `Instrument <type-daml-finance-interface-instrument-swap-asset-instrument-instrument-70853_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
