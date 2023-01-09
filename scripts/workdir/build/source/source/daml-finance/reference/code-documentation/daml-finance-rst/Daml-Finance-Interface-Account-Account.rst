.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-account-account-92922:

Module Daml.Finance.Interface.Account.Account
=============================================

We recommend to import this module qualified\.

Interfaces
----------

.. _type-daml-finance-interface-account-account-account-9624:

**interface** `Account <type-daml-finance-interface-account-account-account-9624_>`_

  An interface which represents an established relationship between a provider and an owner\.

  + **Choice Archive**

    (no fields)

  + **Choice Credit**

    Creates a new ``Holding`` in the corresponding ``Account``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - quantity
         - :ref:`Quantity <type-daml-finance-interface-types-common-types-quantity-60153>` :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>` `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - The target ``Instrument`` and corresponding amount\.

  + **Choice Debit**

    Removes an existing ``Holding``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - holdingCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`
         - The ``Holding``'s contract id\.

  + **Choice GetView**

    Retrieves the interface view\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party fetching the view\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method credit \:** Credit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`)

    Implementation of the ``Credit`` choice\.

  + **Method debit \:** Debit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of the ``Debit`` choice\.

  + **Method getKey \:** :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`

    Get the unique key of the ``Account``\.

Typeclasses
-----------

.. _class-daml-finance-interface-account-account-hasimplementation-21470:

**class** `Implementation <type-daml-finance-interface-account-account-implementation-74020_>`_ t \=\> `HasImplementation <class-daml-finance-interface-account-account-hasimplementation-21470_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-account-account-controllers-36430:

**data** `Controllers <type-daml-finance-interface-account-account-controllers-36430_>`_

  Controllers of the account (related to transfers)\.

  .. _constr-daml-finance-interface-account-account-controllers-79723:

  `Controllers <constr-daml-finance-interface-account-account-controllers-79723_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - outgoing
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties instructing a transfer (outgoing)\.
       * - incoming
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties approving a transfer (incoming)\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Controllers <type-daml-finance-interface-account-account-controllers-36430_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Controllers <type-daml-finance-interface-account-account-controllers-36430_>`_

.. _type-daml-finance-interface-account-account-i-54958:

**type** `I <type-daml-finance-interface-account-account-i-54958_>`_
  \= `Account <type-daml-finance-interface-account-account-account-9624_>`_

  Type synonym for ``Account``\.

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-account-factory-factory-52816>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-account-account-i-54958_>`_))

.. _type-daml-finance-interface-account-account-implementation-74020:

**type** `Implementation <type-daml-finance-interface-account-account-implementation-74020_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-account-account-i-54958_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Account`` along with ``Disclosure``\.

.. _type-daml-finance-interface-account-account-r-61445:

**type** `R <type-daml-finance-interface-account-account-r-61445_>`_
  \= Reference

  Type synonym for ``Reference``\. This type is currently used as a work\-around given the lack of
  interface keys\.

.. _type-daml-finance-interface-account-account-v-78825:

**type** `V <type-daml-finance-interface-account-account-v-78825_>`_
  \= `View <type-daml-finance-interface-account-account-view-21119_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Account <type-daml-finance-interface-account-account-account-9624_>`_ `V <type-daml-finance-interface-account-account-v-78825_>`_

.. _type-daml-finance-interface-account-account-view-21119:

**data** `View <type-daml-finance-interface-account-account-view-21119_>`_

  View for ``Account``\.

  .. _constr-daml-finance-interface-account-account-view-80168:

  `View <constr-daml-finance-interface-account-account-view-80168_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - custodian
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party providing accounting services\.
       * - owner
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party owning this account\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Identifier for the account\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Human readable description of the account\.
       * - holdingFactoryCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`F <type-daml-finance-interface-holding-factory-f-28062>`
         - Associated holding factory\.
       * - controllers
         - `Controllers <type-daml-finance-interface-account-account-controllers-36430_>`_
         - Parties controlling transfers\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-account-account-view-21119_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-account-account-view-21119_>`_

Functions
---------

.. _function-daml-finance-interface-account-account-tokey-90427:

`toKey <function-daml-finance-interface-account-account-tokey-90427_>`_
  \: `View <type-daml-finance-interface-account-account-view-21119_>`_ \-\> :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`

  Convert the account's 'View' to its key\.

.. _function-daml-finance-interface-account-account-asdisclosure-79899:

`asDisclosure <function-daml-finance-interface-account-account-asdisclosure-79899_>`_
  \: `Account <type-daml-finance-interface-account-account-account-9624_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-account-account-getkey-13539:

`getKey <function-daml-finance-interface-account-account-getkey-13539_>`_
  \: `Account <type-daml-finance-interface-account-account-account-9624_>`_ \-\> :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`

.. _function-daml-finance-interface-account-account-credit-27165:

`credit <function-daml-finance-interface-account-account-credit-27165_>`_
  \: `Account <type-daml-finance-interface-account-account-account-9624_>`_ \-\> Credit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`)

.. _function-daml-finance-interface-account-account-debit-82741:

`debit <function-daml-finance-interface-account-account-debit-82741_>`_
  \: `Account <type-daml-finance-interface-account-account-account-9624_>`_ \-\> Debit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

.. _function-daml-finance-interface-account-account-exerciseinterfacebykey-13671:

`exerciseInterfaceByKey <function-daml-finance-interface-account-account-exerciseinterfacebykey-13671_>`_
  \: (`HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ i, `HasExercise <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercise-70422>`_ i d r) \=\> :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>` \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> d \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ r

  Exercise interface by key\.
  This method can be used to exercise a choice on an ``Account`` given its ``AccountKey``\.
  Requires as input the ``AccountKey``, the actor fetching the account and the choice arguments\.
  For example\:

  .. code-block:: daml

    exerciseInterfaceByKey @Account.I accountKey actor Account.Debit with holdingCid

.. _function-daml-finance-interface-account-account-disclose-32452:

`disclose <function-daml-finance-interface-account-account-disclose-32452_>`_
  \: (`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`) \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>` \-\> :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>` \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-account-account-i-54958_>`_)

  Disclose account\.

.. _function-daml-finance-interface-account-account-undisclose-11023:

`undisclose <function-daml-finance-interface-account-account-undisclose-11023_>`_
  \: (`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`) \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>` \-\> :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>` \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-account-account-i-54958_>`_))

  Undisclose account\.
