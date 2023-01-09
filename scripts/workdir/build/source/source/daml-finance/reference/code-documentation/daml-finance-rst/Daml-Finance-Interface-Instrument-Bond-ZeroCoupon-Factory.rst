.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-zerocoupon-factory-70433:

Module Daml.Finance.Interface.Instrument.Bond.ZeroCoupon.Factory
================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542:

**interface** `Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542_>`_

  Factory interface to instantiate zero\-coupon bond instruments\.

  + **Choice Archive**

    (no fields)

  + **Choice Create**

    Create a new instrument\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - zeroCoupon
         - :ref:`ZeroCoupon <type-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-49144>`
         - Attributes to create a zero coupon bond\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - The instrument's observers\.

  + **Choice Remove**

    Archive an instrument\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument's key\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-bond-zerocoupon-factory-hasimplementation-2253:

**class** `Implementation <type-daml-finance-interface-instrument-bond-zerocoupon-factory-implementation-25251_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-bond-zerocoupon-factory-hasimplementation-2253_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-bond-zerocoupon-factory-f-78752:

**type** `F <type-daml-finance-interface-instrument-bond-zerocoupon-factory-f-78752_>`_
  \= `Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-instrument-bond-zerocoupon-factory-implementation-25251:

**type** `Implementation <type-daml-finance-interface-instrument-bond-zerocoupon-factory-implementation-25251_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-instrument-bond-zerocoupon-factory-v-9232:

**type** `V <type-daml-finance-interface-instrument-bond-zerocoupon-factory-v-9232_>`_
  \= `View <type-daml-finance-interface-instrument-bond-zerocoupon-factory-view-55660_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542_>`_ `V <type-daml-finance-interface-instrument-bond-zerocoupon-factory-v-9232_>`_

.. _type-daml-finance-interface-instrument-bond-zerocoupon-factory-view-55660:

**data** `View <type-daml-finance-interface-instrument-bond-zerocoupon-factory-view-55660_>`_

  View of ``Factory``\.

  .. _constr-daml-finance-interface-instrument-bond-zerocoupon-factory-view-40717:

  `View <constr-daml-finance-interface-instrument-bond-zerocoupon-factory-view-40717_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-bond-zerocoupon-factory-view-55660_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-bond-zerocoupon-factory-view-55660_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-bond-zerocoupon-factory-asdisclosure-62600:

`asDisclosure <function-daml-finance-interface-instrument-bond-zerocoupon-factory-asdisclosure-62600_>`_
  \: `Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-instrument-bond-zerocoupon-factory-createtick-33935:

`create' <function-daml-finance-interface-instrument-bond-zerocoupon-factory-createtick-33935_>`_
  \: `Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`)

.. _function-daml-finance-interface-instrument-bond-zerocoupon-factory-remove-67429:

`remove <function-daml-finance-interface-instrument-bond-zerocoupon-factory-remove-67429_>`_
  \: `Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
