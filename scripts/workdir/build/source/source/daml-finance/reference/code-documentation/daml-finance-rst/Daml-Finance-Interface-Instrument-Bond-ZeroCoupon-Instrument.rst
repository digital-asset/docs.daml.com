.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-zerocoupon-instrument-59755:

Module Daml.Finance.Interface.Instrument.Bond.ZeroCoupon.Instrument
===================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-bond-zerocoupon-instrument-instrument-17192:

**interface** `Instrument <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-instrument-17192_>`_

  Instrument interface representing a zero coupon bond\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-bond-zerocoupon-instrument-hasimplementation-52197:

**class** `Implementation <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-implementation-43961_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-bond-zerocoupon-instrument-hasimplementation-52197_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-bond-zerocoupon-instrument-i-81577:

**type** `I <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-i-81577_>`_
  \= `Instrument <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-instrument-17192_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-bond-zerocoupon-instrument-implementation-43961:

**type** `Implementation <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-implementation-43961_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-instrument-17192_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-bond-zerocoupon-instrument-v-57710:

**type** `V <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-v-57710_>`_
  \= `View <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-view-40026_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-instrument-17192_>`_ `V <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-v-57710_>`_

.. _type-daml-finance-interface-instrument-bond-zerocoupon-instrument-view-40026:

**data** `View <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-view-40026_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-bond-zerocoupon-instrument-view-64025:

  `View <constr-daml-finance-interface-instrument-bond-zerocoupon-instrument-view-64025_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - zeroCoupon
         - :ref:`ZeroCoupon <type-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-49144>`
         - Attributes of a zero coupon bond\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-view-40026_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-view-40026_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-bond-zerocoupon-instrument-asbaseinstrument-81841:

`asBaseInstrument <function-daml-finance-interface-instrument-bond-zerocoupon-instrument-asbaseinstrument-81841_>`_
  \: `Instrument <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-instrument-17192_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
