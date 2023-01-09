.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-account-factory-11691:

Module Daml.Finance.Interface.Account.Factory
=============================================

Interfaces
----------

.. _type-daml-finance-interface-account-factory-factory-52816:

**interface** `Factory <type-daml-finance-interface-account-factory-factory-52816_>`_

  Interface that allows implementing templates to create accounts\.

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
       * - account
         - :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`
         - The account's key\.
       * - holdingFactoryCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`F <type-daml-finance-interface-holding-factory-f-28062>`
         - Associated holding factory for the account\.
       * - controllers
         - :ref:`Controllers <type-daml-finance-interface-account-account-controllers-36430>`
         - Controllers of the account\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Human readable description of the account\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - The account's observers\.

  + **Choice Remove**

    Archive an account\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - account
         - :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`
         - The account's key\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-account-account-i-54958>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-account-factory-hasimplementation-19809:

**class** `Implementation <type-daml-finance-interface-account-factory-implementation-6213_>`_ t \=\> `HasImplementation <class-daml-finance-interface-account-factory-hasimplementation-19809_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-account-factory-f-92594:

**type** `F <type-daml-finance-interface-account-factory-f-92594_>`_
  \= `Factory <type-daml-finance-interface-account-factory-factory-52816_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-account-factory-implementation-6213:

**type** `Implementation <type-daml-finance-interface-account-factory-implementation-6213_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `F <type-daml-finance-interface-account-factory-f-92594_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-account-factory-v-23074:

**type** `V <type-daml-finance-interface-account-factory-v-23074_>`_
  \= `View <type-daml-finance-interface-account-factory-view-92606_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-account-factory-factory-52816_>`_ `V <type-daml-finance-interface-account-factory-v-23074_>`_

.. _type-daml-finance-interface-account-factory-view-92606:

**data** `View <type-daml-finance-interface-account-factory-view-92606_>`_

  .. _constr-daml-finance-interface-account-factory-view-95721:

  `View <constr-daml-finance-interface-account-factory-view-95721_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-account-factory-view-92606_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-account-factory-view-92606_>`_

Functions
---------

.. _function-daml-finance-interface-account-factory-asdisclosure-53570:

`asDisclosure <function-daml-finance-interface-account-factory-asdisclosure-53570_>`_
  \: `Factory <type-daml-finance-interface-account-factory-factory-52816_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-account-factory-createtick-34357:

`create' <function-daml-finance-interface-account-factory-createtick-34357_>`_
  \: `Factory <type-daml-finance-interface-account-factory-factory-52816_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-account-account-i-54958>`)

.. _function-daml-finance-interface-account-factory-remove-76719:

`remove <function-daml-finance-interface-account-factory-remove-76719_>`_
  \: `Factory <type-daml-finance-interface-account-factory-factory-52816_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
