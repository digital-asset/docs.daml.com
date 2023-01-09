.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-settlement-types-44085:

Module Daml.Finance.Interface.Settlement.Types
==============================================

Data Types
----------

.. _type-daml-finance-interface-settlement-types-allocation-46483:

**data** `Allocation <type-daml-finance-interface-settlement-types-allocation-46483_>`_

  Describes an allocation of an ``Instruction``\.

  .. _constr-daml-finance-interface-settlement-types-unallocated-82559:

  `Unallocated <constr-daml-finance-interface-settlement-types-unallocated-82559_>`_

    An unallocated instruction\.

  .. _constr-daml-finance-interface-settlement-types-pledge-99803:

  `Pledge <constr-daml-finance-interface-settlement-types-pledge-99803_>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`)

    Settle the instruction with the pledged asset\.

  .. _constr-daml-finance-interface-settlement-types-creditreceiver-50700:

  `CreditReceiver <constr-daml-finance-interface-settlement-types-creditreceiver-50700_>`_

    Settle the instruction by crediting the receiver account (where the sender is custodian)\.

  .. _constr-daml-finance-interface-settlement-types-settleoffledger-15836:

  `SettleOffledger <constr-daml-finance-interface-settlement-types-settleoffledger-15836_>`_

    Settle the instruction off\-ledger\.

  .. _constr-daml-finance-interface-settlement-types-passthroughfrom-69429:

  `PassThroughFrom <constr-daml-finance-interface-settlement-types-passthroughfrom-69429_>`_ (:ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`, `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_)

    Settle the instruction with the holding coming from the specified instruction and account\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Allocation <type-daml-finance-interface-settlement-types-allocation-46483_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Allocation <type-daml-finance-interface-settlement-types-allocation-46483_>`_

.. _type-daml-finance-interface-settlement-types-approval-84286:

**data** `Approval <type-daml-finance-interface-settlement-types-approval-84286_>`_

  Describes an approval of an ``Instruction``\.

  .. _constr-daml-finance-interface-settlement-types-unapproved-57468:

  `Unapproved <constr-daml-finance-interface-settlement-types-unapproved-57468_>`_

    An unapproved instruction\.

  .. _constr-daml-finance-interface-settlement-types-takedelivery-14079:

  `TakeDelivery <constr-daml-finance-interface-settlement-types-takedelivery-14079_>`_ :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`

    Take delivery to the specified account\.

  .. _constr-daml-finance-interface-settlement-types-debitsender-39086:

  `DebitSender <constr-daml-finance-interface-settlement-types-debitsender-39086_>`_

    Debit the sender account with the provided asset (where the receiver is custodian)\.

  .. _constr-daml-finance-interface-settlement-types-settleoffledgeracknowledge-98269:

  `SettleOffledgerAcknowledge <constr-daml-finance-interface-settlement-types-settleoffledgeracknowledge-98269_>`_

    Acknowledge settlement of the instruction off\-ledger\.

  .. _constr-daml-finance-interface-settlement-types-passthroughto-68260:

  `PassThroughTo <constr-daml-finance-interface-settlement-types-passthroughto-68260_>`_ (:ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`, `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_)

    Take delivery to the specified account\. The holding is then immediately allocated to the
    specified instruction\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Approval <type-daml-finance-interface-settlement-types-approval-84286_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Approval <type-daml-finance-interface-settlement-types-approval-84286_>`_

.. _type-daml-finance-interface-settlement-types-instructionkey-43940:

**data** `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  A unique key for Instructions\.

  .. _constr-daml-finance-interface-settlement-types-instructionkey-78969:

  `InstructionKey <constr-daml-finance-interface-settlement-types-instructionkey-78969_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - requestors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties requesting settlement of the instruction\.
       * - batchId
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Id of the batch the instruction belongs to\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - A unique identifier for an instruction\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ :ref:`Instruction <type-daml-finance-settlement-instruction-instruction-35758>` `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_ `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ :ref:`Instruction <type-daml-finance-settlement-instruction-instruction-35758>` `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ :ref:`Instruction <type-daml-finance-settlement-instruction-instruction-35758>` `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ :ref:`Instruction <type-daml-finance-settlement-instruction-instruction-35758>` `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ :ref:`Instruction <type-daml-finance-settlement-instruction-instruction-35758>` `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ :ref:`Instruction <type-daml-finance-settlement-instruction-instruction-35758>` `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ :ref:`Instruction <type-daml-finance-settlement-instruction-instruction-35758>` `InstructionKey <type-daml-finance-interface-settlement-types-instructionkey-43940_>`_

.. _type-daml-finance-interface-settlement-types-routedstep-10086:

**data** `RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086_>`_

  Describes a transfer of a position between two parties\.
  The custodian at which the position is held is also specified\.

  .. _constr-daml-finance-interface-settlement-types-routedstep-70775:

  `RoutedStep <constr-daml-finance-interface-settlement-types-routedstep-70775_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - sender
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party transferring the asset\.
       * - receiver
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party receiving the asset\.
       * - custodian
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The custodian at which the asset is held\.
       * - quantity
         - :ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`
         - The instrument and amount to be transferred\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086_>`_

  **instance** HasMethod :ref:`RouteProvider <type-daml-finance-interface-settlement-routeprovider-routeprovider-53805>` \"discover\" (Discover \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086_>`_\])

.. _type-daml-finance-interface-settlement-types-step-78661:

**data** `Step <type-daml-finance-interface-settlement-types-step-78661_>`_

  Describes a transfer of a position between two parties\.

  .. _constr-daml-finance-interface-settlement-types-step-97764:

  `Step <constr-daml-finance-interface-settlement-types-step-97764_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - sender
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party transferring the asset\.
       * - receiver
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party receiving the asset\.
       * - quantity
         - :ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`
         - The instrument and amount to be transferred\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Step <type-daml-finance-interface-settlement-types-step-78661_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `Step <type-daml-finance-interface-settlement-types-step-78661_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Step <type-daml-finance-interface-settlement-types-step-78661_>`_
