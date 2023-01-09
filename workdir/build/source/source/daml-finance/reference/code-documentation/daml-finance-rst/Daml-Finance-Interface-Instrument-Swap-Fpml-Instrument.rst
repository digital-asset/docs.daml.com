.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-fpml-instrument-38654:

Module Daml.Finance.Interface.Instrument.Swap.Fpml.Instrument
=============================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-swap-fpml-instrument-instrument-3449:

**interface** `Instrument <type-daml-finance-interface-instrument-swap-fpml-instrument-instrument-3449_>`_

  Instrument interface representing a swap specified as FpML swapStreams\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-swap-fpml-instrument-hasimplementation-19626:

**class** `Implementation <type-daml-finance-interface-instrument-swap-fpml-instrument-implementation-72684_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-swap-fpml-instrument-hasimplementation-19626_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-swap-fpml-instrument-i-71302:

**type** `I <type-daml-finance-interface-instrument-swap-fpml-instrument-i-71302_>`_
  \= `Instrument <type-daml-finance-interface-instrument-swap-fpml-instrument-instrument-3449_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-swap-fpml-instrument-implementation-72684:

**type** `Implementation <type-daml-finance-interface-instrument-swap-fpml-instrument-implementation-72684_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-swap-fpml-instrument-instrument-3449_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-swap-fpml-instrument-v-64689:

**type** `V <type-daml-finance-interface-instrument-swap-fpml-instrument-v-64689_>`_
  \= `View <type-daml-finance-interface-instrument-swap-fpml-instrument-view-73287_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-swap-fpml-instrument-instrument-3449_>`_ `V <type-daml-finance-interface-instrument-swap-fpml-instrument-v-64689_>`_

.. _type-daml-finance-interface-instrument-swap-fpml-instrument-view-73287:

**data** `View <type-daml-finance-interface-instrument-swap-fpml-instrument-view-73287_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-swap-fpml-instrument-view-4952:

  `View <constr-daml-finance-interface-instrument-swap-fpml-instrument-view-4952_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - fpml
         - :ref:`Fpml <type-daml-finance-interface-instrument-swap-fpml-types-fpml-92648>`
         - Attributes of a swap specified as FpML swapStreams\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-swap-fpml-instrument-view-73287_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-swap-fpml-instrument-view-73287_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-swap-fpml-instrument-asbaseinstrument-93036:

`asBaseInstrument <function-daml-finance-interface-instrument-swap-fpml-instrument-asbaseinstrument-93036_>`_
  \: `Instrument <type-daml-finance-interface-instrument-swap-fpml-instrument-instrument-3449_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
