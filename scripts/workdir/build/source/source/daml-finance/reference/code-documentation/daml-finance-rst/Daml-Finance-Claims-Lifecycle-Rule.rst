.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-claims-lifecycle-rule-53980:

Module Daml.Finance.Claims.Lifecycle.Rule
=========================================

Templates
---------

.. _type-daml-finance-claims-lifecycle-rule-rule-6996:

**template** `Rule <type-daml-finance-claims-lifecycle-rule-rule-6996_>`_

  Rule to process a time update event for instruments that are modelled using \"on\-the\-fly\"
  claims (the tree is not stored on\-ledger but generated dynamically)\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Providers of the distribution rule\.
     * - lifecycler
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Party performing the lifecycling\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers of the distribution rule\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Identifier for the rule contract\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Textual description\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-rule-lifecycle-i-18685>` **for** `Rule <type-daml-finance-claims-lifecycle-rule-rule-6996_>`_
