.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-inflationlinked-factory-57553:

Module Daml.Finance.Interface.Instrument.Bond.InflationLinked.Factory
=====================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170:

**interface** `Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170_>`_

  Factory interface to instantiate inflation\-linked bond instruments\.

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
       * - inflationLinked
         - :ref:`InflationLinked <type-daml-finance-interface-instrument-bond-inflationlinked-types-inflationlinked-39550>`
         - Attributes to create an inflation linked bond\.
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

.. _class-daml-finance-interface-instrument-bond-inflationlinked-factory-hasimplementation-50579:

**class** `Implementation <type-daml-finance-interface-instrument-bond-inflationlinked-factory-implementation-93639_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-bond-inflationlinked-factory-hasimplementation-50579_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-bond-inflationlinked-factory-f-79068:

**type** `F <type-daml-finance-interface-instrument-bond-inflationlinked-factory-f-79068_>`_
  \= `Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-instrument-bond-inflationlinked-factory-implementation-93639:

**type** `Implementation <type-daml-finance-interface-instrument-bond-inflationlinked-factory-implementation-93639_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-instrument-bond-inflationlinked-factory-v-9548:

**type** `V <type-daml-finance-interface-instrument-bond-inflationlinked-factory-v-9548_>`_
  \= `View <type-daml-finance-interface-instrument-bond-inflationlinked-factory-view-64920_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170_>`_ `V <type-daml-finance-interface-instrument-bond-inflationlinked-factory-v-9548_>`_

.. _type-daml-finance-interface-instrument-bond-inflationlinked-factory-view-64920:

**data** `View <type-daml-finance-interface-instrument-bond-inflationlinked-factory-view-64920_>`_

  View of ``Factory``\.

  .. _constr-daml-finance-interface-instrument-bond-inflationlinked-factory-view-54835:

  `View <constr-daml-finance-interface-instrument-bond-inflationlinked-factory-view-54835_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-bond-inflationlinked-factory-view-64920_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-bond-inflationlinked-factory-view-64920_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-bond-inflationlinked-factory-asdisclosure-17204:

`asDisclosure <function-daml-finance-interface-instrument-bond-inflationlinked-factory-asdisclosure-17204_>`_
  \: `Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-instrument-bond-inflationlinked-factory-createtick-29643:

`create' <function-daml-finance-interface-instrument-bond-inflationlinked-factory-createtick-29643_>`_
  \: `Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`)

.. _function-daml-finance-interface-instrument-bond-inflationlinked-factory-remove-38721:

`remove <function-daml-finance-interface-instrument-bond-inflationlinked-factory-remove-38721_>`_
  \: `Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
