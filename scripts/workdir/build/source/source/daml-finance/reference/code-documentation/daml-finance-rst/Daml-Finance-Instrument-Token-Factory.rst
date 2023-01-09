.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-token-factory-62942:

Module Daml.Finance.Instrument.Token.Factory
============================================

Templates
---------

.. _type-daml-finance-instrument-token-factory-factory-92123:

**template** `Factory <type-daml-finance-instrument-token-factory-factory-92123_>`_

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

  + **interface instance** :ref:`Factory <type-daml-finance-interface-instrument-token-factory-factory-52788>` **for** `Factory <type-daml-finance-instrument-token-factory-factory-92123_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-instrument-token-factory-factory-92123_>`_

Data Types
----------

.. _type-daml-finance-instrument-token-factory-f-37465:

**type** `F <type-daml-finance-instrument-token-factory-f-37465_>`_
  \= `Factory <type-daml-finance-instrument-token-factory-factory-92123_>`_

  Type synonym for ``Factory``\.
