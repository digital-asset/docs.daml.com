.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-rule-claim-6739:

Module Daml.Finance.Interface.Lifecycle.Rule.Claim
==================================================

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-rule-claim-claim-29284:

**interface** `Claim <type-daml-finance-interface-lifecycle-rule-claim-claim-29284_>`_

  Interface for contracts that allow holders to claim an ``Effect`` and generate
  ``SettlementInstruction``\\s\.

  + **Choice Archive**

    (no fields)

  + **Choice ClaimEffect**

    Claim an effect and generate corresponding settlement instructions\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - claimer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party claiming the effect\.
       * - holdingCids
         - \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`\]
         - The holdings to process\.
       * - effectCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`
         - The effect to process\.
       * - batchId
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Identifier used for the generated settlement batch\.

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

  + **Method claimEffect \:** ClaimEffect \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `ClaimResult <type-daml-finance-interface-lifecycle-rule-claim-claimresult-56601_>`_

    Implementation of the ``ClaimEffect`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-rule-claim-hasimplementation-80539:

**class** `Implementation <type-daml-finance-interface-lifecycle-rule-claim-implementation-82369_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-rule-claim-hasimplementation-80539_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-rule-claim-claimresult-56601:

**data** `ClaimResult <type-daml-finance-interface-lifecycle-rule-claim-claimresult-56601_>`_

  Data type wrapping the results of ``Claim``ing an ``Effect``\.

  .. _constr-daml-finance-interface-lifecycle-rule-claim-claimresult-69654:

  `ClaimResult <constr-daml-finance-interface-lifecycle-rule-claim-claimresult-69654_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - batchCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-batch-i-3768>`
         - Batch used to batch\-settle settlement instructions\.
       * - instructionCids
         - \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-instruction-i-90342>`\]
         - Settlement instructions to settle all effect consequences\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `ClaimResult <type-daml-finance-interface-lifecycle-rule-claim-claimresult-56601_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `ClaimResult <type-daml-finance-interface-lifecycle-rule-claim-claimresult-56601_>`_

  **instance** HasMethod `Claim <type-daml-finance-interface-lifecycle-rule-claim-claim-29284_>`_ \"claimEffect\" (ClaimEffect \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `ClaimResult <type-daml-finance-interface-lifecycle-rule-claim-claimresult-56601_>`_)

.. _type-daml-finance-interface-lifecycle-rule-claim-i-33665:

**type** `I <type-daml-finance-interface-lifecycle-rule-claim-i-33665_>`_
  \= `Claim <type-daml-finance-interface-lifecycle-rule-claim-claim-29284_>`_

  Type synonym for ``Claim``\.

.. _type-daml-finance-interface-lifecycle-rule-claim-implementation-82369:

**type** `Implementation <type-daml-finance-interface-lifecycle-rule-claim-implementation-82369_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-lifecycle-rule-claim-i-33665_>`_

  Type constraint for requiring templates to implement ``Settlement``\.

.. _type-daml-finance-interface-lifecycle-rule-claim-v-1238:

**type** `V <type-daml-finance-interface-lifecycle-rule-claim-v-1238_>`_
  \= `View <type-daml-finance-interface-lifecycle-rule-claim-view-67522_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Claim <type-daml-finance-interface-lifecycle-rule-claim-claim-29284_>`_ `V <type-daml-finance-interface-lifecycle-rule-claim-v-1238_>`_

.. _type-daml-finance-interface-lifecycle-rule-claim-view-67522:

**data** `View <type-daml-finance-interface-lifecycle-rule-claim-view-67522_>`_

  View for ``Settlement``\.

  .. _constr-daml-finance-interface-lifecycle-rule-claim-view-9331:

  `View <constr-daml-finance-interface-lifecycle-rule-claim-view-9331_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - providers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Providers of the claim rule\. Together with the actors of the ``ClaimEffect`` choice the authorization requirements to upgrade the holdings being claimed have to be met\.
       * - claimers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Any of the parties can claim an effect\.
       * - settlers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Any of the parties can trigger settlement of the resulting batch\.
       * - routeProviderCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-settlement-routeprovider-i-46608>`
         - RouteProvider contract used to discover settlement routes\.
       * - settlementFactoryCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`F <type-daml-finance-interface-settlement-factory-f-21995>`
         - Settlement factory contract used to create a ``Batch`` of ``Instruction``\\s\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-rule-claim-view-67522_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-rule-claim-view-67522_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-rule-claim-claimeffect-76781:

`claimEffect <function-daml-finance-interface-lifecycle-rule-claim-claimeffect-76781_>`_
  \: `Claim <type-daml-finance-interface-lifecycle-rule-claim-claim-29284_>`_ \-\> ClaimEffect \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `ClaimResult <type-daml-finance-interface-lifecycle-rule-claim-claimresult-56601_>`_
