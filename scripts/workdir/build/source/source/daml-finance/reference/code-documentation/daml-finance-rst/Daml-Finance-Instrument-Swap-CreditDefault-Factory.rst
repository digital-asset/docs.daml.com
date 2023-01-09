.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-swap-creditdefault-factory-17039:

Module Daml.Finance.Instrument.Swap.CreditDefault.Factory
=========================================================

Templates
---------

.. _type-daml-finance-instrument-swap-creditdefault-factory-factory-20084:

**template** `Factory <type-daml-finance-instrument-swap-creditdefault-factory-factory-20084_>`_

  Factory template for instrument creation\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The factory's provider\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The factory's observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`Factory <type-daml-finance-interface-instrument-swap-creditdefault-factory-factory-17381>` **for** `Factory <type-daml-finance-instrument-swap-creditdefault-factory-factory-20084_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-instrument-swap-creditdefault-factory-factory-20084_>`_
