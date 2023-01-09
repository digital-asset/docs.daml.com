.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-lifecycle-rule-claim-99318:

Module Daml.Finance.Lifecycle.Rule.Claim
========================================

Templates
---------

.. _type-daml-finance-lifecycle-rule-claim-rule-90062:

**template** `Rule <type-daml-finance-lifecycle-rule-claim-rule-90062_>`_

  Rule contract that allows an actor to claim effects, returning settlement instructions\.

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
       - RouteProvider used to discover settlement routes\.
     * - settlementFactoryCid
       - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`F <type-daml-finance-interface-settlement-factory-f-21995>`
       - Settlement factory contract used to create a ``Batch`` of ``Instruction``\\s\.
     * - netInstructions
       - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
       - Configure whether netting should be enabled for quantities having the same (instrument, sender, receiver)\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-rule-claim-i-33665>` **for** `Rule <type-daml-finance-lifecycle-rule-claim-rule-90062_>`_

Data Types
----------

.. _type-daml-finance-lifecycle-rule-claim-t-31399:

**type** `T <type-daml-finance-lifecycle-rule-claim-t-31399_>`_
  \= `Rule <type-daml-finance-lifecycle-rule-claim-rule-90062_>`_

  Type synonym for ``Rule``\.
