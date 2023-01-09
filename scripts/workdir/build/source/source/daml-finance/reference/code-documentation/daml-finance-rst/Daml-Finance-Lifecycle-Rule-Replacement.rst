.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-lifecycle-rule-replacement-6984:

Module Daml.Finance.Lifecycle.Rule.Replacement
==============================================

Templates
---------

.. _type-daml-finance-lifecycle-rule-replacement-rule-7648:

**template** `Rule <type-daml-finance-lifecycle-rule-replacement-rule-7648_>`_

  Rule contract that defines the replacement of units of an instrument with a basket of other
  instruments (e\.g\. stock merger)\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Providers of the replacement rule\.
     * - lifecycler
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Party performing the lifecycling\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Identifier for the rule contract\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Textual description\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-rule-lifecycle-i-18685>` **for** `Rule <type-daml-finance-lifecycle-rule-replacement-rule-7648_>`_

Data Types
----------

.. _type-daml-finance-lifecycle-rule-replacement-t-34745:

**type** `T <type-daml-finance-lifecycle-rule-replacement-t-34745_>`_
  \= `Rule <type-daml-finance-lifecycle-rule-replacement-rule-7648_>`_

  Type synonym for ``Rule``\.
