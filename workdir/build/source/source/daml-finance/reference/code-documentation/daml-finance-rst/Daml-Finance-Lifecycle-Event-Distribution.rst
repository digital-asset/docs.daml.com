.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-lifecycle-event-distribution-17302:

Module Daml.Finance.Lifecycle.Event.Distribution
================================================

Templates
---------

.. _type-daml-finance-lifecycle-event-distribution-event-46459:

**template** `Event <type-daml-finance-lifecycle-event-distribution-event-46459_>`_

  Event contract for the distribution of units of an instrument for each unit of a target
  instrument (e\.g\. share or cash dividends)\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Providers of the distribution event\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Event Identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Event description\.
     * - effectiveTime
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - Time on which the distribution is effectuated\.
     * - targetInstrument
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - Instrument the distribution event applies to\.
     * - newInstrument
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - Instrument after the distribution has been claimed\.
     * - perUnitDistribution
       - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
       - Distributed quantities per unit held\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-event-distribution-i-8313>` **for** `Event <type-daml-finance-lifecycle-event-distribution-event-46459_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>` **for** `Event <type-daml-finance-lifecycle-event-distribution-event-46459_>`_

Data Types
----------

.. _type-daml-finance-lifecycle-event-distribution-t-61859:

**type** `T <type-daml-finance-lifecycle-event-distribution-t-61859_>`_
  \= `Event <type-daml-finance-lifecycle-event-distribution-event-46459_>`_

  Type synonym for ``Event``\.
