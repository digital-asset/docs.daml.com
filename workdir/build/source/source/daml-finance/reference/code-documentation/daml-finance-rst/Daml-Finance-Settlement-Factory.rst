.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-settlement-factory-257:

Module Daml.Finance.Settlement.Factory
======================================

Templates
---------

.. _type-daml-finance-settlement-factory-factory-53518:

**template** `Factory <type-daml-finance-settlement-factory-factory-53518_>`_

  Factory template that implements the ``Factory`` interface\.
  It is used to create a set of settlement ``Instruction``\\s, and a ``Batch`` to atomically settle
  them\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Party providing the facility\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`F <type-daml-finance-interface-settlement-factory-f-21995>` **for** `Factory <type-daml-finance-settlement-factory-factory-53518_>`_
