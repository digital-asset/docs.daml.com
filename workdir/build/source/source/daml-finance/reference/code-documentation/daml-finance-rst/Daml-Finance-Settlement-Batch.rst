.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-settlement-batch-95573:

Module Daml.Finance.Settlement.Batch
====================================

Templates
---------

.. _type-daml-finance-settlement-batch-batch-59698:

**template** `Batch <type-daml-finance-settlement-batch-batch-59698_>`_

  Allows you to atomically settle a set of settlement ``Step``\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - requestors
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Parties requesting the settlement\.
     * - settlers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Any of the parties can trigger the settlement\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Batch identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Batch description\.
     * - contextId
       - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Identifier to link a batch to a context (e\.g\. the ``Effect`` it originated from)\.
     * - routedStepsWithInstructionId
       - \[(:ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`, :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`)\]
       - The settlement ``RoutedStep``\\s and the identifiers of the corresponding ``Instruction``\\s\.
     * - settlementTime
       - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - Settlement time (if any)\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-settlement-batch-i-3768>` **for** `Batch <type-daml-finance-settlement-batch-batch-59698_>`_

Data Types
----------

.. _type-daml-finance-settlement-batch-batchkey-91766:

**data** `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  Type for batch key\.

  .. _constr-daml-finance-settlement-batch-batchkey-9039:

  `BatchKey <constr-daml-finance-settlement-batch-batchkey-9039_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - requestors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         -
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ `Batch <type-daml-finance-settlement-batch-batch-59698_>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_ `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ `Batch <type-daml-finance-settlement-batch-batch-59698_>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ `Batch <type-daml-finance-settlement-batch-batch-59698_>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ `Batch <type-daml-finance-settlement-batch-batch-59698_>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ `Batch <type-daml-finance-settlement-batch-batch-59698_>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ `Batch <type-daml-finance-settlement-batch-batch-59698_>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ `Batch <type-daml-finance-settlement-batch-batch-59698_>`_ `BatchKey <type-daml-finance-settlement-batch-batchkey-91766_>`_

.. _type-daml-finance-settlement-batch-t-36750:

**type** `T <type-daml-finance-settlement-batch-t-36750_>`_
  \= `Batch <type-daml-finance-settlement-batch-batch-59698_>`_

  Type synonym for ``Batch``\.
