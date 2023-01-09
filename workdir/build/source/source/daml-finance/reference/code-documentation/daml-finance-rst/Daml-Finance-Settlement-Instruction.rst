.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-settlement-instruction-87187:

Module Daml.Finance.Settlement.Instruction
==========================================

Templates
---------

.. _type-daml-finance-settlement-instruction-instruction-35758:

**template** `Instruction <type-daml-finance-settlement-instruction-instruction-35758_>`_

  Instruction is used to settle a single settlement ``Step``\. In order to settle the instruction,

  * the sender must allocate a suitable holding
  * the receiver must define the receiving account

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
     * - batchId
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Trade identifier\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Instruction identifier\.
     * - routedStep
       - :ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`
       - Routed settlement step\.
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
       - Additional signatories, used to collect authorization\.
     * - signedReceivers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Additional signatories, used to collect authorization\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-settlement-instruction-i-90342>` **for** `Instruction <type-daml-finance-settlement-instruction-instruction-35758_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instruction <type-daml-finance-settlement-instruction-instruction-35758_>`_

Data Types
----------

.. _type-daml-finance-settlement-instruction-t-45988:

**type** `T <type-daml-finance-settlement-instruction-t-45988_>`_
  \= `Instruction <type-daml-finance-settlement-instruction-instruction-35758_>`_

  Type synonym for ``Instruction``\.
