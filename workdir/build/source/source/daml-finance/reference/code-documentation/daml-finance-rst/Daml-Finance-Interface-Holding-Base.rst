.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-holding-base-24195:

Module Daml.Finance.Interface.Holding.Base
==========================================

Interfaces
----------

.. _type-daml-finance-interface-holding-base-base-14854:

**interface** `Base <type-daml-finance-interface-holding-base-base-14854_>`_

  Base interface for a holding\.

  + **Choice Acquire**

    Lock a contract\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - newLockers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties which restrain the contract's ability to perform specified actions\.
       * - context
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Reason for acquiring a lock\.
       * - lockType
         - `LockType <type-daml-finance-interface-holding-base-locktype-20540_>`_
         - Type of lock to acquire

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

  + **Choice Release**

    Unlock a locked contract\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - context
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  + **Method acquire \:** Acquire \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Base <type-daml-finance-interface-holding-base-base-14854_>`_)

    Implementation of the ``Acquire`` choice\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method release \:** Release \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Base <type-daml-finance-interface-holding-base-base-14854_>`_)

    Implementation of the ``Release`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-holding-base-hasimplementation-31795:

**class** `Implementation <type-daml-finance-interface-holding-base-implementation-87781_>`_ t \=\> `HasImplementation <class-daml-finance-interface-holding-base-hasimplementation-31795_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-holding-base-i-67605:

**type** `I <type-daml-finance-interface-holding-base-i-67605_>`_
  \= `Base <type-daml-finance-interface-holding-base-base-14854_>`_

  Type synonym for ``Base``\.

  **instance** HasMethod :ref:`Account <type-daml-finance-interface-account-account-account-9624>` \"credit\" (Credit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-base-i-67605_>`_))

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-holding-factory-factory-80308>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-base-i-67605_>`_))

  **instance** HasMethod :ref:`Transferable <type-daml-finance-interface-holding-transferable-transferable-24986>` \"asBase\" `I <type-daml-finance-interface-holding-base-i-67605_>`_

  **instance** HasMethod :ref:`Batch <type-daml-finance-interface-settlement-batch-batch-97497>` \"cancel\" (Cancel \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-base-i-67605_>`_\])

  **instance** HasMethod :ref:`Batch <type-daml-finance-interface-settlement-batch-batch-97497>` \"settle\" (Settle \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-base-i-67605_>`_\])

  **instance** HasMethod :ref:`Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569>` \"allocate\" (Allocate \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569>`, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-base-i-67605_>`_)))

  **instance** HasMethod :ref:`Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569>` \"cancel\" (Cancel \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-base-i-67605_>`_)))

  **instance** HasMethod :ref:`Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569>` \"execute\" (Execute \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-holding-base-i-67605_>`_)))

.. _type-daml-finance-interface-holding-base-implementation-87781:

**type** `Implementation <type-daml-finance-interface-holding-base-implementation-87781_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-holding-base-i-67605_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Holding`` along with ``Disclosure``\.

.. _type-daml-finance-interface-holding-base-lock-32912:

**data** `Lock <type-daml-finance-interface-holding-base-lock-32912_>`_

  Locking details\.

  .. _constr-daml-finance-interface-holding-base-lock-86361:

  `Lock <constr-daml-finance-interface-holding-base-lock-86361_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lockers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties which are locking the contract\.
       * - context
         - `Set <https://docs.daml.com/daml/stdlib/DA-Set.html#type-da-set-types-set-90436>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Why this lock is held by the locking parties\.
       * - lockType
         - `LockType <type-daml-finance-interface-holding-base-locktype-20540_>`_
         - The type of lock applied\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Lock <type-daml-finance-interface-holding-base-lock-32912_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Lock <type-daml-finance-interface-holding-base-lock-32912_>`_

.. _type-daml-finance-interface-holding-base-locktype-20540:

**data** `LockType <type-daml-finance-interface-holding-base-locktype-20540_>`_

  Type of lock held\.

  .. _constr-daml-finance-interface-holding-base-semaphore-31337:

  `Semaphore <constr-daml-finance-interface-holding-base-semaphore-31337_>`_

    A one time only lock\.

  .. _constr-daml-finance-interface-holding-base-reentrant-77300:

  `Reentrant <constr-daml-finance-interface-holding-base-reentrant-77300_>`_

    A mutual exclusion lock where the same lockers may lock a contract multiple times\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `LockType <type-daml-finance-interface-holding-base-locktype-20540_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `LockType <type-daml-finance-interface-holding-base-locktype-20540_>`_

.. _type-daml-finance-interface-holding-base-v-39458:

**type** `V <type-daml-finance-interface-holding-base-v-39458_>`_
  \= `View <type-daml-finance-interface-holding-base-view-44702_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Base <type-daml-finance-interface-holding-base-base-14854_>`_ `V <type-daml-finance-interface-holding-base-v-39458_>`_

.. _type-daml-finance-interface-holding-base-view-44702:

**data** `View <type-daml-finance-interface-holding-base-view-44702_>`_

  View for ``Base``\.

  .. _constr-daml-finance-interface-holding-base-view-84815:

  `View <constr-daml-finance-interface-holding-base-view-84815_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - Instrument being held\.
       * - account
         - :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`
         - Key of the account holding the assets\.
       * - amount
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - Size of the holding\.
       * - lock
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Lock <type-daml-finance-interface-holding-base-lock-32912_>`_
         - When a contract is locked, contains the locking details\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-holding-base-view-44702_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-holding-base-view-44702_>`_

Functions
---------

.. _function-daml-finance-interface-holding-base-asdisclosure-65162:

`asDisclosure <function-daml-finance-interface-holding-base-asdisclosure-65162_>`_
  \: `Base <type-daml-finance-interface-holding-base-base-14854_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-holding-base-acquire-55898:

`acquire <function-daml-finance-interface-holding-base-acquire-55898_>`_
  \: `Base <type-daml-finance-interface-holding-base-base-14854_>`_ \-\> Acquire \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Base <type-daml-finance-interface-holding-base-base-14854_>`_)

.. _function-daml-finance-interface-holding-base-release-67297:

`release <function-daml-finance-interface-holding-base-release-67297_>`_
  \: `Base <type-daml-finance-interface-holding-base-base-14854_>`_ \-\> Release \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Base <type-daml-finance-interface-holding-base-base-14854_>`_)

.. _function-daml-finance-interface-holding-base-getlockers-29612:

`getLockers <function-daml-finance-interface-holding-base-getlockers-29612_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Base <type-daml-finance-interface-holding-base-base-14854_>`_ \=\> t \-\> :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`

  Get the lockers of a holding\.
