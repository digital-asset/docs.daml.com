.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-data-time-ledgertime-84639:

Module Daml.Finance.Data.Time.LedgerTime
========================================

Templates
---------

.. _type-daml-finance-data-time-ledgertime-ledgertime-44359:

**template** `LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359_>`_

  A ``LedgerTime`` is a template used to retrieve current ledger time as a ``TimeObservable``\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - The time providers\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - The ledger time identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The ledger time description\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421>` **for** `LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359_>`_

Data Types
----------

.. _type-daml-finance-data-time-ledgertime-t-49800:

**type** `T <type-daml-finance-data-time-ledgertime-t-49800_>`_
  \= `LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359_>`_

  Type synonym for ``LedgerTime``\.
