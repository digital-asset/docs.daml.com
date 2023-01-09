.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-lifecycle-effect-1975:

Module Daml.Finance.Lifecycle.Effect
====================================

Templates
---------

.. _type-daml-finance-lifecycle-effect-effect-18432:

**template** `Effect <type-daml-finance-lifecycle-effect-effect-18432_>`_

  A contract encoding the consequences of a lifecycle event for one unit of the target
  instrument\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - The effect provider\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - The effect's identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The effect's description\.
     * - targetInstrument
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The target instrument\.
     * - producedInstrument
       - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The produced instrument, when it exists\.
     * - otherConsumed
       - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
       - Consumed quantities (in addition to the target instrument)\.
     * - otherProduced
       - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
       - Produced quantities (in additon to the produced instrument)\.
     * - settlementTime
       - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - The effect's settlement time (if any)\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>` **for** `Effect <type-daml-finance-lifecycle-effect-effect-18432_>`_

Data Types
----------

.. _type-daml-finance-lifecycle-effect-t-84092:

**type** `T <type-daml-finance-lifecycle-effect-t-84092_>`_
  \= `Effect <type-daml-finance-lifecycle-effect-effect-18432_>`_

  Type synonym for ``Effect``\.
