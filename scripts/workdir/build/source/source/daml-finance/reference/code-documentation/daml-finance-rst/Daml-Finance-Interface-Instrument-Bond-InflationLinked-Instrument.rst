.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-inflationlinked-instrument-38495:

Module Daml.Finance.Interface.Instrument.Bond.InflationLinked.Instrument
========================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-bond-inflationlinked-instrument-instrument-4132:

**interface** `Instrument <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-instrument-4132_>`_

  Instrument interface representing an inflation linked bond\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-bond-inflationlinked-instrument-hasimplementation-71363:

**class** `Implementation <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-implementation-48917_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-bond-inflationlinked-instrument-hasimplementation-71363_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-bond-inflationlinked-instrument-i-9413:

**type** `I <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-i-9413_>`_
  \= `Instrument <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-instrument-4132_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-bond-inflationlinked-instrument-implementation-48917:

**type** `Implementation <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-implementation-48917_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-instrument-4132_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-bond-inflationlinked-instrument-v-20306:

**type** `V <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-v-20306_>`_
  \= `View <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-view-9454_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-instrument-4132_>`_ `V <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-v-20306_>`_

.. _type-daml-finance-interface-instrument-bond-inflationlinked-instrument-view-9454:

**data** `View <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-view-9454_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-bond-inflationlinked-instrument-view-97683:

  `View <constr-daml-finance-interface-instrument-bond-inflationlinked-instrument-view-97683_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - inflationLinked
         - :ref:`InflationLinked <type-daml-finance-interface-instrument-bond-inflationlinked-types-inflationlinked-39550>`
         - Attributes of an inflation linked bond\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-view-9454_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-view-9454_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-bond-inflationlinked-instrument-asbaseinstrument-82709:

`asBaseInstrument <function-daml-finance-interface-instrument-bond-inflationlinked-instrument-asbaseinstrument-82709_>`_
  \: `Instrument <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-instrument-4132_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
