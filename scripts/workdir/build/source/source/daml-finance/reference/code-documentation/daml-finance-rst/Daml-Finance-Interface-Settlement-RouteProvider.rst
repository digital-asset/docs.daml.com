.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-settlement-routeprovider-15164:

Module Daml.Finance.Interface.Settlement.RouteProvider
======================================================

Interfaces
----------

.. _type-daml-finance-interface-settlement-routeprovider-routeprovider-53805:

**interface** `RouteProvider <type-daml-finance-interface-settlement-routeprovider-routeprovider-53805_>`_

  An interface used to discover the settlement route for each ``Step``, i\.e\., ``[RoutedStep]``\.

  + **Choice Archive**

    (no fields)

  + **Choice Discover**

    Discover the settlement route for each ``Step``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - discoverors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties requesting to discover\.
       * - contextId
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Context for the discovery\.
       * - steps
         - \[:ref:`Step <type-daml-finance-interface-settlement-types-step-78661>`\]
         - Settlement steps to route\.

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

  + **Method discover \:** Discover \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`\]

    Implementation of the ``Discover`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-settlement-routeprovider-hasimplementation-56018:

**class** `Implementation <type-daml-finance-interface-settlement-routeprovider-implementation-71298_>`_ t \=\> `HasImplementation <class-daml-finance-interface-settlement-routeprovider-hasimplementation-56018_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-settlement-routeprovider-i-46608:

**type** `I <type-daml-finance-interface-settlement-routeprovider-i-46608_>`_
  \= `RouteProvider <type-daml-finance-interface-settlement-routeprovider-routeprovider-53805_>`_

  Type synonym for ``RouteProvider``\.

.. _type-daml-finance-interface-settlement-routeprovider-implementation-71298:

**type** `Implementation <type-daml-finance-interface-settlement-routeprovider-implementation-71298_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-settlement-routeprovider-i-46608_>`_

  Type constraint for requiring templates to implement ``Factory``\.

.. _type-daml-finance-interface-settlement-routeprovider-v-92135:

**type** `V <type-daml-finance-interface-settlement-routeprovider-v-92135_>`_
  \= `View <type-daml-finance-interface-settlement-routeprovider-view-63261_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `RouteProvider <type-daml-finance-interface-settlement-routeprovider-routeprovider-53805_>`_ `V <type-daml-finance-interface-settlement-routeprovider-v-92135_>`_

.. _type-daml-finance-interface-settlement-routeprovider-view-63261:

**data** `View <type-daml-finance-interface-settlement-routeprovider-view-63261_>`_

  View for ``RouteProvider``\.

  .. _constr-daml-finance-interface-settlement-routeprovider-view-38976:

  `View <constr-daml-finance-interface-settlement-routeprovider-view-38976_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party providing the ``RouteProvider`` facility\.
       * - observers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Observers\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-settlement-routeprovider-view-63261_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-settlement-routeprovider-view-63261_>`_

Functions
---------

.. _function-daml-finance-interface-settlement-routeprovider-discover-52075:

`discover <function-daml-finance-interface-settlement-routeprovider-discover-52075_>`_
  \: `RouteProvider <type-daml-finance-interface-settlement-routeprovider-routeprovider-53805_>`_ \-\> Discover \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`\]
