.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Internal Settlement
###################

This tutorial builds upon the concepts introduced in the
:doc:`Settlement <../getting-started/settlement>` getting-started tutorial. Compared to our previous
:doc:`Enhanced Transfers <transfer>` tutorial, which demonstrated the "direct" transfer a holding
between sender to receiver (at a single custodian), it delves further into the settlement mechanism
with a batch and related instructions. This intricate process enables the adjustment of record books
across multiple entities and instrument holdings simultaneously.

In this tutorial, we will limit the complexity by focusing on a single custodian and the transfer of
a singular instrument. The next tutorial will explore the broader scenario involving multiple
custodians. Eager learners are encouraged to extend this tutorial and the following one by
incorporating more than one instrument as an exercise.

Understanding Internal Settlement with Examples
***********************************************

To start, let us briefly revist the concept of a
:ref:`Batch <type-daml-finance-interface-settlement-batch-batch-97497>`, which consists of one or
more :ref:`Instructions <type-daml-finance-interface-settlement-instruction-instruction-30569>`.
Each instruction signifies a
:ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`, delineating the
quantity of an instrument to be transferred from a sender to a receiver at a specific custodian. For
an instruction to be prepared for settlement (or execution), the sender-side must furnish an
:ref:`Allocation <type-daml-finance-interface-settlement-types-allocation-46483>`, and the
receiver-side must provide an
:ref:`Approval <type-daml-finance-interface-settlement-types-approval-84286>`.

This tutorial will walk you through three example scripts for settling instructions at a single
custodian: ``runWrappedTransferSettlement``, ``runCreditDebitSettlement``, and
``runPassThroughSettlement``.

The allocation processes in these scripts involve methods to commit a pre-existing holding
(``Pledge``), a newly created holding (``CreditReceiver``), and a holding received concurrently
(``PassThroughFrom``).

The approval methods entail taking delivery of a holding to an account (``TakeDelivery``),
immediately nullifying the holding (``DebitSender``), and passing the holding through (as
allocation) to another instruction (``PassThroughTo``).

Each script kicks off with ``runSetupInternalSettlement`` which initiates parties, an instrument
issued by the Central Bank, accounts for Alice, Bob, and Charlie at a Bank, and a settlement
factory:

.. literalinclude:: ../../finance-settlement/daml/Scripts/Internal.daml
  :language: daml
  :start-after: -- WRAPPED_TRANSFER_SETUP_BEGIN
  :end-before: -- WRAPPED_TRANSFER_SETUP_END

The settlement factory is employed by a party, known as the requestor, to create a batch and
instructions from a list of routed steps. In the scripts, the requestor is also responsible for
settling the batch once all instructions have been allocated and approved.

Wrapped Transfer
================

The first example encapsulates a transfer from Alice to Bob, from our previous
:doc:`Enhanced Transfers <transfer>` tutorial, by creating a batch and a single instruction:

.. literalinclude:: ../../finance-settlement/daml/Scripts/Internal.daml
  :language: daml
  :start-after: -- WRAPPED_TRANSFER_INSTRUCT_BEGIN
  :end-before: -- WRAPPED_TRANSFER_INSTRUCT_END

Here, Alice allocates by pledging a holding, Bob approves by taking delivery to his account at the
Bank, and the requestor finally settles the batch:

.. literalinclude:: ../../finance-settlement/daml/Scripts/Internal.daml
  :language: daml
  :start-after: -- WRAPPED_TRANSFER_SETTLE_BEGIN
  :end-before: -- WRAPPED_TRANSFER_SETTLE_END

Note that this occurs without involving the Bank, and either Alice or Bob could also take the role
as the requestor. As a result of running this script, Alice's holding is transferred to Bob.

Credit and Debit
================

An alternative approach to transfer the holding from Alice to Bob includes the Bank as an
intermediary.

.. literalinclude:: ../../finance-settlement/daml/Scripts/Internal.daml
  :language: daml
  :start-after: -- CREDIT_DEBIT_INSTRUCT_BEGIN
  :end-before: -- CREDIT_DEBIT_INSTRUCT_END

Similar to the previous scenario, Alice allocates by pledging a holding, and Bob approves by taking
delivery to his account. However, in this case, the Bank plays an intermediary role by allocating
and approving, debiting the sender and crediting the receiver, respectively:

.. literalinclude:: ../../finance-settlement/daml/Scripts/Internal.daml
  :language: daml
  :start-after: -- CREDIT_DEBIT_SETTLE_BEGIN
  :end-before: -- CREDIT_DEBIT_SETTLE_END

We could have made the Bank approve and allocate its instructions by taking delivery to an account
it owns and pledging a holding where it acts as the custodian. However, this would necessitate
"dummy" accounts and holdings, which can be avoided using the ``DebitSender`` and ``CreditReceiver``
methods. These methods are exclusively accessible to the custodian.

Pass Through
============

The final script of this tutorial demonstrates how holdings received in the same settlement process
can be allocated to a subsequent instruction. We again use two instructions, ``instruction1`` and
``instruction2``, but now with Charlie as the intermediary:

.. literalinclude:: ../../finance-settlement/daml/Scripts/Internal.daml
  :language: daml
  :start-after: -- PASS_THROUGH_INSTRUCT_BEGIN
  :end-before: -- PASS_THROUGH_INSTRUCT_END

As in previous examples, Alice allocates by pledging a holding, and Bob approves by taking delivery
to his account. The intermediary, Charlie, allocates using
``PassThroughTo (charlieAccount, instruction2)`` and approves with
``PassThroughFrom (charlieAccount, instruction1)``, essentially enabling the holding Charlie
receives from Alice to pass-through to Bob:

.. literalinclude:: ../../finance-settlement/daml/Scripts/Internal.daml
  :language: daml
  :start-after: -- PASS_THROUGH_SETTLE_BEGIN
  :end-before: -- PASS_THROUGH_SETTLE_END

The significant advantage of the pass-through method is that Charlie doesn't need any holdings
upfront as he's at a net zero position for incoming and outgoing holdings in this settlement process.

Note that the Bank could have utilized the pass-through approach to achieve the same result, but it
would still require a "dummy" account.

Run the Script
**************

The code for this tutorial can be executed via the ``runWrappedTransferSettlement``,
``runCreditDebitSettlement``, and ``runPassThroughSettlement`` functions in the ``Internal.daml``
module.

Summary
*******

By the end of this tutorial, you should have a good grasp on how to apply various allocation and
approval methods at a single custodian. The key points are:

* A custodian can utilize the ``DebitSender`` and ``CreditReceiver`` methods to bypass the need for
  "dummy" accounts and holdings when approving and allocating instructions, respectively.
* A holding settled via an intermediary at the same custodian can be passed through, thus
  eliminating the requirement for the intermediary to possess the holding upfront.

In the forthcoming tutorial, we will delve into more complex settlement transactions involving
multiple custodians.
