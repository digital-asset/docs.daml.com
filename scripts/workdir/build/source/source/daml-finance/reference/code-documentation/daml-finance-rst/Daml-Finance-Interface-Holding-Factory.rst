.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-holding-factory-6211:

Module Daml.Finance.Interface.Holding.Factory
=============================================

Interfaces
----------

.. _type-daml-finance-interface-holding-factory-factory-80308:

**interface** `Factory <type-daml-finance-interface-holding-factory-factory-80308_>`_

  Holding factory contract used to create (credit) and archive (debit) holdings\.

  + **Choice Archive**

    (no fields)

  + **Choice Create**

    Create a holding on the instrument in the corresponding account\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument of which units are held\.
       * - account
         - :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`
         - The account at which the holding is held\. Defines the holding's owner and custodian\.
       * - amount
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - Number of units\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - Observers of the holding to be credited\.

  + **Choice Remove**

    Archive a holding\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The parties authorizing the removal\.
       * - holdingCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`
         - The holding to be removed\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure.I`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-holding-factory-hasimplementation-30617:

**class** `Implementation <type-daml-finance-interface-holding-factory-implementation-8089_>`_ t \=\> `HasImplementation <class-daml-finance-interface-holding-factory-hasimplementation-30617_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-holding-factory-f-28062:

**type** `F <type-daml-finance-interface-holding-factory-f-28062_>`_
  \= `Factory <type-daml-finance-interface-holding-factory-factory-80308_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-holding-factory-implementation-8089:

**type** `Implementation <type-daml-finance-interface-holding-factory-implementation-8089_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `F <type-daml-finance-interface-holding-factory-f-28062_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-holding-factory-v-97582:

**type** `V <type-daml-finance-interface-holding-factory-v-97582_>`_
  \= `View <type-daml-finance-interface-holding-factory-view-14490_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-holding-factory-factory-80308_>`_ `V <type-daml-finance-interface-holding-factory-v-97582_>`_

.. _type-daml-finance-interface-holding-factory-view-14490:

**data** `View <type-daml-finance-interface-holding-factory-view-14490_>`_

  .. _constr-daml-finance-interface-holding-factory-view-56557:

  `View <constr-daml-finance-interface-holding-factory-view-56557_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-holding-factory-view-14490_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-holding-factory-view-14490_>`_

Functions
---------

.. _function-daml-finance-interface-holding-factory-asdisclosure-87254:

`asDisclosure <function-daml-finance-interface-holding-factory-asdisclosure-87254_>`_
  \: `Factory <type-daml-finance-interface-holding-factory-factory-80308_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-holding-factory-createtick-96473:

`create' <function-daml-finance-interface-holding-factory-createtick-96473_>`_
  \: `Factory <type-daml-finance-interface-holding-factory-factory-80308_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`)

.. _function-daml-finance-interface-holding-factory-remove-38419:

`remove <function-daml-finance-interface-holding-factory-remove-38419_>`_
  \: `Factory <type-daml-finance-interface-holding-factory-factory-80308_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
