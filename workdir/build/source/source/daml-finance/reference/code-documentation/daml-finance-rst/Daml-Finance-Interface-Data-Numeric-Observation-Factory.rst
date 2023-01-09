.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-data-numeric-observation-factory-57560:

Module Daml.Finance.Interface.Data.Numeric.Observation.Factory
==============================================================

Interfaces
----------

.. _type-daml-finance-interface-data-numeric-observation-factory-factory-27189:

**interface** `Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189_>`_

  Factory contract used to create, remove and view a ``Numeric.Observation``\.

  + **Choice Archive**

    (no fields)

  + **Choice Create**

    Create an ``Observation``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The reference data provider\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - A textual identifier\.
       * - observations
         - `Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - The time\-dependent values\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - Observers\.

  + **Choice Remove**

    Archive an ``Observation``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The parties authorizing the removal\.
       * - observationCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-data-numeric-observation-i-26176>`
         - The observation to be removed\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure.I`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-data-numeric-observation-i-26176>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-data-numeric-observation-factory-hasimplementation-47118:

**class** `Implementation <type-daml-finance-interface-data-numeric-observation-factory-implementation-43614_>`_ t \=\> `HasImplementation <class-daml-finance-interface-data-numeric-observation-factory-hasimplementation-47118_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-data-numeric-observation-factory-f-61851:

**type** `F <type-daml-finance-interface-data-numeric-observation-factory-f-61851_>`_
  \= `Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-data-numeric-observation-factory-implementation-43614:

**type** `Implementation <type-daml-finance-interface-data-numeric-observation-factory-implementation-43614_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `F <type-daml-finance-interface-data-numeric-observation-factory-f-61851_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-data-numeric-observation-factory-v-31371:

**type** `V <type-daml-finance-interface-data-numeric-observation-factory-v-31371_>`_
  \= `View <type-daml-finance-interface-data-numeric-observation-factory-view-28625_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189_>`_ `V <type-daml-finance-interface-data-numeric-observation-factory-v-31371_>`_

.. _type-daml-finance-interface-data-numeric-observation-factory-view-28625:

**data** `View <type-daml-finance-interface-data-numeric-observation-factory-view-28625_>`_

  .. _constr-daml-finance-interface-data-numeric-observation-factory-view-95140:

  `View <constr-daml-finance-interface-data-numeric-observation-factory-view-95140_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - The observers of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-data-numeric-observation-factory-view-28625_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-data-numeric-observation-factory-view-28625_>`_

Functions
---------

.. _function-daml-finance-interface-data-numeric-observation-factory-asdisclosure-55845:

`asDisclosure <function-daml-finance-interface-data-numeric-observation-factory-asdisclosure-55845_>`_
  \: `Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-data-numeric-observation-factory-createtick-39780:

`create' <function-daml-finance-interface-data-numeric-observation-factory-createtick-39780_>`_
  \: `Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-data-numeric-observation-i-26176>`)

.. _function-daml-finance-interface-data-numeric-observation-factory-remove-10792:

`remove <function-daml-finance-interface-data-numeric-observation-factory-remove-10792_>`_
  \: `Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
