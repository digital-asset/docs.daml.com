.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-token-factory-34763:

Module Daml.Finance.Interface.Instrument.Token.Factory
======================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-token-factory-factory-52788:

**interface** `Factory <type-daml-finance-interface-instrument-token-factory-factory-52788_>`_

  Factory interface to instantiate simple tokens\.

  + **Choice Archive**

    (no fields)

  + **Choice Create**

    Create a new account\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - token
         - :ref:`Token <type-daml-finance-interface-instrument-token-types-token-10344>`
         - Attributes to create a token\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - The instrument's observers\.

  + **Choice Remove**

    Archive an account\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The account's key\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-token-factory-hasimplementation-403:

**class** `Implementation <type-daml-finance-interface-instrument-token-factory-implementation-70329_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-token-factory-hasimplementation-403_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-token-factory-f-19486:

**type** `F <type-daml-finance-interface-instrument-token-factory-f-19486_>`_
  \= `Factory <type-daml-finance-interface-instrument-token-factory-factory-52788_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-instrument-token-factory-implementation-70329:

**type** `Implementation <type-daml-finance-interface-instrument-token-factory-implementation-70329_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Factory <type-daml-finance-interface-instrument-token-factory-factory-52788_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-instrument-token-factory-v-89006:

**type** `V <type-daml-finance-interface-instrument-token-factory-v-89006_>`_
  \= `View <type-daml-finance-interface-instrument-token-factory-view-69274_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-instrument-token-factory-factory-52788_>`_ `V <type-daml-finance-interface-instrument-token-factory-v-89006_>`_

.. _type-daml-finance-interface-instrument-token-factory-view-69274:

**data** `View <type-daml-finance-interface-instrument-token-factory-view-69274_>`_

  .. _constr-daml-finance-interface-instrument-token-factory-view-92683:

  `View <constr-daml-finance-interface-instrument-token-factory-view-92683_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-token-factory-view-69274_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-token-factory-view-69274_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-token-factory-asdisclosure-55414:

`asDisclosure <function-daml-finance-interface-instrument-token-factory-asdisclosure-55414_>`_
  \: `Factory <type-daml-finance-interface-instrument-token-factory-factory-52788_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-instrument-token-factory-createtick-28121:

`create' <function-daml-finance-interface-instrument-token-factory-createtick-28121_>`_
  \: `Factory <type-daml-finance-interface-instrument-token-factory-factory-52788_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`)

.. _function-daml-finance-interface-instrument-token-factory-remove-20403:

`remove <function-daml-finance-interface-instrument-token-factory-remove-20403_>`_
  \: `Factory <type-daml-finance-interface-instrument-token-factory-factory-52788_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
