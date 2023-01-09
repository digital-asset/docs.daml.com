.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-settlement-instruction-10970:

Module Daml.Finance.Interface.Settlement.Instruction
====================================================

Interfaces
----------

.. _type-daml-finance-interface-settlement-instruction-instruction-30569:

**interface** `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_

  An interface for providing a single instruction to transfer an asset\.

  + **Choice Allocate**

    Allocates this instruction and optionally returns a previously allocated (mutated) asset\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The parties allocating the instruction\.
       * - allocation
         - :ref:`Allocation <type-daml-finance-interface-settlement-types-allocation-46483>`
         - Allocation of an instruction\.

  + **Choice Approve**

    Approves this instruction\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The parties approving the instruction\.
       * - approval
         - :ref:`Approval <type-daml-finance-interface-settlement-types-approval-84286>`
         - Approval of an instruction\.

  + **Choice Archive**

    (no fields)

  + **Choice Cancel**

    Cancels this instruction\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The parties canceling the instruction\.

  + **Choice Execute**

    Executes this instruction\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The parties executing the instruction\.

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

  + **Method allocate \:** Allocate \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`))

    Implementation of the ``Allocate`` choice\.

  + **Method approve \:** Approve \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_)

    Implementation of the ``Approve`` choice\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method cancel \:** Cancel \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`))

    Implementation of the ``Cancel`` choice\.

  + **Method execute \:** Execute \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`))

    Implementation of the ``Execute`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-settlement-instruction-hasimplementation-40548:

**class** `Implementation <type-daml-finance-interface-settlement-instruction-implementation-17580_>`_ t \=\> `HasImplementation <class-daml-finance-interface-settlement-instruction-hasimplementation-40548_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-settlement-instruction-i-90342:

**type** `I <type-daml-finance-interface-settlement-instruction-i-90342_>`_
  \= `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_

  Type synonym for ``Instruction``\.

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-settlement-factory-factory-31525>` \"instruct\" (Instruct \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-batch-i-3768>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-settlement-instruction-i-90342_>`_\]))

.. _type-daml-finance-interface-settlement-instruction-implementation-17580:

**type** `Implementation <type-daml-finance-interface-settlement-instruction-implementation-17580_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-settlement-instruction-i-90342_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Instruction`` along with ``Disclosure``\.

.. _type-daml-finance-interface-settlement-instruction-v-83729:

**type** `V <type-daml-finance-interface-settlement-instruction-v-83729_>`_
  \= `View <type-daml-finance-interface-settlement-instruction-view-45863_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_ `V <type-daml-finance-interface-settlement-instruction-v-83729_>`_

.. _type-daml-finance-interface-settlement-instruction-view-45863:

**data** `View <type-daml-finance-interface-settlement-instruction-view-45863_>`_

  View for ``Instruction``\.

  .. _constr-daml-finance-interface-settlement-instruction-view-23498:

  `View <constr-daml-finance-interface-settlement-instruction-view-23498_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - requestors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties that instructed settlement\.
       * - settlers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties that can execute the Instruction\.
       * - batchId
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Batch identifier\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Instruction identifier\.
       * - routedStep
         - :ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`
         - Instruction details to execute\.
       * - settlementTime
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Settlement time (if any)\.
       * - allocation
         - :ref:`Allocation <type-daml-finance-interface-settlement-types-allocation-46483>`
         - Allocation from the sender\.
       * - approval
         - :ref:`Approval <type-daml-finance-interface-settlement-types-approval-84286>`
         - Approval from the receiver\.
       * - signedSenders
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Additional signatories, used to collect authorization (on sending side)\.
       * - signedReceivers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Additional signatories, used to collect authorization (on receiving side)\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-settlement-instruction-view-45863_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-settlement-instruction-view-45863_>`_

Functions
---------

.. _function-daml-finance-interface-settlement-instruction-asdisclosure-49219:

`asDisclosure <function-daml-finance-interface-settlement-instruction-asdisclosure-49219_>`_
  \: `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-settlement-instruction-allocate-71473:

`allocate <function-daml-finance-interface-settlement-instruction-allocate-71473_>`_
  \: `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_ \-\> Allocate \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`))

.. _function-daml-finance-interface-settlement-instruction-approve-37030:

`approve <function-daml-finance-interface-settlement-instruction-approve-37030_>`_
  \: `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_ \-\> Approve \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_)

.. _function-daml-finance-interface-settlement-instruction-execute-46460:

`execute <function-daml-finance-interface-settlement-instruction-execute-46460_>`_
  \: `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_ \-\> Execute \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`))

.. _function-daml-finance-interface-settlement-instruction-cancel-79088:

`cancel <function-daml-finance-interface-settlement-instruction-cancel-79088_>`_
  \: `Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569_>`_ \-\> Cancel \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`))
