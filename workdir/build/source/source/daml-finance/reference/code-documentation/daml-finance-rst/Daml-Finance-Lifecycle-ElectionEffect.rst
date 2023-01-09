.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-lifecycle-electioneffect-99924:

Module Daml.Finance.Lifecycle.ElectionEffect
============================================

Templates
---------

.. _type-daml-finance-lifecycle-electioneffect-electioneffect-28146:

**template** `ElectionEffect <type-daml-finance-lifecycle-electioneffect-electioneffect-28146_>`_

  A contract encoding the consequences of an election for one unit of the target instrument\.
  It needs to be claimed with a holding of the right amount and is consumed after claiming\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - The effect provider\.
     * - custodian
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The custodian of the holding put forward for election\.
     * - owner
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The owner of the holding put forward for election\.
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
     * - amount
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The elected amount\.
     * - otherConsumed
       - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
       - Consumed quantities (not including the target instrument)\.
     * - otherProduced
       - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
       - Produced quantities (not including the produced instrument)\.
     * - settlementTime
       - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - The effect's settlement time (if any)\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>` **for** `ElectionEffect <type-daml-finance-lifecycle-electioneffect-electioneffect-28146_>`_

Data Types
----------

.. _type-daml-finance-lifecycle-electioneffect-t-5245:

**type** `T <type-daml-finance-lifecycle-electioneffect-t-5245_>`_
  \= `ElectionEffect <type-daml-finance-lifecycle-electioneffect-electioneffect-28146_>`_

  Type synonym for ``ElectionEffect``\.
