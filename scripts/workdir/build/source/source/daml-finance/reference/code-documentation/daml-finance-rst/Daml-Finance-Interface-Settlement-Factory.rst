.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-settlement-factory-75196:

Module Daml.Finance.Interface.Settlement.Factory
================================================

Interfaces
----------

.. _type-daml-finance-interface-settlement-factory-factory-31525:

**interface** `Factory <type-daml-finance-interface-settlement-factory-factory-31525_>`_

  An interface used to generate settlement instructions\.

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

  + **Choice Instruct**

    Generate settlement instructions, and a batch for settling them\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instructors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties requesting to instruct a settlement\.
       * - settlers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Any of the parties can trigger the final settlement\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Factory identifier\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Batch description\.
       * - contextId
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Identifier to link a batch to a context (e\.g\. the ``Effect`` it originated from)\.
       * - routedSteps
         - \[:ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`\]
         - Routed settlement steps to instruct\.
       * - settlementTime
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Settlement time (if any)\.

  + **Method instruct \:** Instruct \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-batch-i-3768>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-instruction-i-90342>`\])

    Implementation of the ``Instruct`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-settlement-factory-hasimplementation-4562:

**class** `Implementation <type-daml-finance-interface-settlement-factory-implementation-25262_>`_ t \=\> `HasImplementation <class-daml-finance-interface-settlement-factory-hasimplementation-4562_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-settlement-factory-f-21995:

**type** `F <type-daml-finance-interface-settlement-factory-f-21995_>`_
  \= `Factory <type-daml-finance-interface-settlement-factory-factory-31525_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-settlement-factory-i-11228:

**type** `I <type-daml-finance-interface-settlement-factory-i-11228_>`_
  \= `Factory <type-daml-finance-interface-settlement-factory-factory-31525_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-settlement-factory-implementation-25262:

**type** `Implementation <type-daml-finance-interface-settlement-factory-implementation-25262_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `F <type-daml-finance-interface-settlement-factory-f-21995_>`_

  Type constraint for requiring templates to implement ``Factory``\.

.. _type-daml-finance-interface-settlement-factory-v-52475:

**type** `V <type-daml-finance-interface-settlement-factory-v-52475_>`_
  \= `View <type-daml-finance-interface-settlement-factory-view-36353_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-settlement-factory-factory-31525_>`_ `V <type-daml-finance-interface-settlement-factory-v-52475_>`_

.. _type-daml-finance-interface-settlement-factory-view-36353:

**data** `View <type-daml-finance-interface-settlement-factory-view-36353_>`_

  View for ``Factory``\.

  .. _constr-daml-finance-interface-settlement-factory-view-28268:

  `View <constr-daml-finance-interface-settlement-factory-view-28268_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party providing the facility\.
       * - observers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Observers\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-settlement-factory-view-36353_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-settlement-factory-view-36353_>`_

Functions
---------

.. _function-daml-finance-interface-settlement-factory-instruct-80328:

`instruct <function-daml-finance-interface-settlement-factory-instruct-80328_>`_
  \: `Factory <type-daml-finance-interface-settlement-factory-factory-31525_>`_ \-\> Instruct \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-batch-i-3768>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-instruction-i-90342>`\])
