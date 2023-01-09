.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-holding-fungible-63712:

Module Daml.Finance.Interface.Holding.Fungible
==============================================

Interfaces
----------

.. _type-daml-finance-interface-holding-fungible-fungible-60176:

**interface** `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_

  Interface for a fungible holding\.

  + **Choice Archive**

    (no fields)

  + **Choice ArchiveFungible**

    Archives the fungible contract\.

    (no fields)

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

  + **Choice Merge**

    Merge multiple fungible contracts into a single fungible contract\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - fungibleCids
         - \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_\]
         - The fungible contracts to merge which will get consumed\.

  + **Choice Split**

    Split a fungible contract into multiple contracts by amount\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - amounts
         - \[`Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_\]
         - The quantities to split the fungible asset by, creating a new contract per amount\.

  + **Method asTransferable \:** :ref:`I <type-daml-finance-interface-holding-transferable-i-13335>`

    Conversion to ``Transferable`` interface\.

  + **Method merge \:** Merge \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_)

    Implementation of the ``Merge`` choice\.

  + **Method split \:** Split \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `SplitResult <type-daml-finance-interface-holding-fungible-splitresult-30736_>`_

    Implementation of the ``Split`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-holding-fungible-hasimplementation-90342:

**class** `Implementation <type-daml-finance-interface-holding-fungible-implementation-48706_>`_ t \=\> `HasImplementation <class-daml-finance-interface-holding-fungible-hasimplementation-90342_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-holding-fungible-i-96400:

**type** `I <type-daml-finance-interface-holding-fungible-i-96400_>`_
  \= `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_

  Type synonym for ``Fungible``\.

.. _type-daml-finance-interface-holding-fungible-implementation-48706:

**type** `Implementation <type-daml-finance-interface-holding-fungible-implementation-48706_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-holding-fungible-i-96400_>`_, :ref:`Implementation <type-daml-finance-interface-holding-transferable-implementation-82963>` t)

  Type constraint for requiring templates to implement ``Fungible`` along with ``Transferable``\.

.. _type-daml-finance-interface-holding-fungible-splitresult-30736:

**data** `SplitResult <type-daml-finance-interface-holding-fungible-splitresult-30736_>`_

  Result of a call to ``Split``\.

  .. _constr-daml-finance-interface-holding-fungible-splitresult-30455:

  `SplitResult <constr-daml-finance-interface-holding-fungible-splitresult-30455_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - splitCids
         - \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_\]
         - The contract ids for the split holdings\.
       * - rest
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_)
         - Contract id for the holding on the remaining amount\. It is ``None`` when the split is exact\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `SplitResult <type-daml-finance-interface-holding-fungible-splitresult-30736_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `SplitResult <type-daml-finance-interface-holding-fungible-splitresult-30736_>`_

  **instance** HasMethod `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_ \"split\" (Split \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `SplitResult <type-daml-finance-interface-holding-fungible-splitresult-30736_>`_)

.. _type-daml-finance-interface-holding-fungible-v-41927:

**type** `V <type-daml-finance-interface-holding-fungible-v-41927_>`_
  \= `View <type-daml-finance-interface-holding-fungible-view-90781_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_ `V <type-daml-finance-interface-holding-fungible-v-41927_>`_

.. _type-daml-finance-interface-holding-fungible-view-90781:

**data** `View <type-daml-finance-interface-holding-fungible-view-90781_>`_

  View for ``Fungible``\.

  .. _constr-daml-finance-interface-holding-fungible-view-68048:

  `View <constr-daml-finance-interface-holding-fungible-view-68048_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - modifiers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties which have the authorization to modify a fungible asset\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-holding-fungible-view-90781_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-holding-fungible-view-90781_>`_

Functions
---------

.. _function-daml-finance-interface-holding-fungible-astransferable-68493:

`asTransferable <function-daml-finance-interface-holding-fungible-astransferable-68493_>`_
  \: `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_ \-\> :ref:`I <type-daml-finance-interface-holding-transferable-i-13335>`

.. _function-daml-finance-interface-holding-fungible-split-79593:

`split <function-daml-finance-interface-holding-fungible-split-79593_>`_
  \: `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_ \-\> Split \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `SplitResult <type-daml-finance-interface-holding-fungible-splitresult-30736_>`_

.. _function-daml-finance-interface-holding-fungible-merge-51057:

`merge <function-daml-finance-interface-holding-fungible-merge-51057_>`_
  \: `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_ \-\> Merge \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Fungible <type-daml-finance-interface-holding-fungible-fungible-60176_>`_)
