.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-bond-inflationlinked-factory-70614:

Module Daml.Finance.Instrument.Bond.InflationLinked.Factory
===========================================================

Templates
---------

.. _type-daml-finance-instrument-bond-inflationlinked-factory-factory-8659:

**template** `Factory <type-daml-finance-instrument-bond-inflationlinked-factory-factory-8659_>`_

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

  + **interface instance** :ref:`Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170>` **for** `Factory <type-daml-finance-instrument-bond-inflationlinked-factory-factory-8659_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-instrument-bond-inflationlinked-factory-factory-8659_>`_

Data Types
----------

.. _type-daml-finance-instrument-bond-inflationlinked-factory-f-49073:

**type** `F <type-daml-finance-instrument-bond-inflationlinked-factory-f-49073_>`_
  \= `Factory <type-daml-finance-instrument-bond-inflationlinked-factory-factory-8659_>`_

  Type synonym for ``Factory``\.
