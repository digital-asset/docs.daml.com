.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-holding-transferable-88121:

Module Daml.Finance.Interface.Holding.Transferable
==================================================

Interfaces
----------

.. _type-daml-finance-interface-holding-transferable-transferable-24986:

**interface** `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_

  An interface respresenting a contract where ownership can be transferred to other parties\.

  + **Choice Archive**

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
         - The party retrieving the view\.

  + **Choice Transfer**

    Transfer a contract to a new owner\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties authorizing the transfer\.
       * - newOwnerAccount
         - :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`
         - Account contract id of the parties to transfer the contract to\.

  + **Method asBase \:** :ref:`I <type-daml-finance-interface-holding-base-i-67605>`

    Conversion to ``Base`` interface\.

  + **Method transfer \:** `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-transferable-i-13335_>`_ \-\> Transfer \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_)

    Implementation of the ``Transfer`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-holding-transferable-hasimplementation-43261:

**class** `Implementation <type-daml-finance-interface-holding-transferable-implementation-82963_>`_ t \=\> `HasImplementation <class-daml-finance-interface-holding-transferable-hasimplementation-43261_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-holding-transferable-i-13335:

**type** `I <type-daml-finance-interface-holding-transferable-i-13335_>`_
  \= `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_

  Type synonym for ``Transferable``\.

  **instance** HasMethod :ref:`Fungible <type-daml-finance-interface-holding-fungible-fungible-60176>` \"asTransferable\" `I <type-daml-finance-interface-holding-transferable-i-13335_>`_

  **instance** HasMethod `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_ \"transfer\" (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-transferable-i-13335_>`_ \-\> Transfer \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_))

.. _type-daml-finance-interface-holding-transferable-implementation-82963:

**type** `Implementation <type-daml-finance-interface-holding-transferable-implementation-82963_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-holding-transferable-i-13335_>`_, :ref:`Implementation <type-daml-finance-interface-holding-base-implementation-87781>` t)

  Type constraint for requiring templates to implement ``Transferable`` to
  also implement ``Base``\.

.. _type-daml-finance-interface-holding-transferable-v-6848:

**type** `V <type-daml-finance-interface-holding-transferable-v-6848_>`_
  \= `View <type-daml-finance-interface-holding-transferable-view-41948_>`_

  Type synonym for ``View``\.

.. _type-daml-finance-interface-holding-transferable-view-41948:

**data** `View <type-daml-finance-interface-holding-transferable-view-41948_>`_

  View for ``Transferable``\.

  .. _constr-daml-finance-interface-holding-transferable-view-20453:

  `View <constr-daml-finance-interface-holding-transferable-view-20453_>`_

    (no fields)

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-holding-transferable-view-41948_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-holding-transferable-view-41948_>`_

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_ `View <type-daml-finance-interface-holding-transferable-view-41948_>`_

Functions
---------

.. _function-daml-finance-interface-holding-transferable-asbase-78774:

`asBase <function-daml-finance-interface-holding-transferable-asbase-78774_>`_
  \: `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_ \-\> :ref:`I <type-daml-finance-interface-holding-base-i-67605>`

.. _function-daml-finance-interface-holding-transferable-transfer-91982:

`transfer <function-daml-finance-interface-holding-transferable-transfer-91982_>`_
  \: `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_ \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-transferable-i-13335_>`_ \-\> Transfer \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Transferable <type-daml-finance-interface-holding-transferable-transferable-24986_>`_)
