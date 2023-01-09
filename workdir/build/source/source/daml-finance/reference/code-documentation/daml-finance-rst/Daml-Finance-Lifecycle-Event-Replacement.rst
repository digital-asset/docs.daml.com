.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-lifecycle-event-replacement-51859:

Module Daml.Finance.Lifecycle.Event.Replacement
===============================================

Templates
---------

.. _type-daml-finance-lifecycle-event-replacement-event-16120:

**template** `Event <type-daml-finance-lifecycle-event-replacement-event-16120_>`_

  Event contract for the replacement of units of an instrument with a basket of other
  instruments, e\.g\., a stock merger\.

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
       - Event identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Event description\.
     * - effectiveTime
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - Time on which the replacement is effectuated\.
     * - targetInstrument
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - Instrument the replacement event applies to\.
     * - perUnitReplacement
       - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
       - Instrument quantities the target instrument is replaced with\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>` **for** `Event <type-daml-finance-lifecycle-event-replacement-event-16120_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-event-replacement-i-34852>` **for** `Event <type-daml-finance-lifecycle-event-replacement-event-16120_>`_

Data Types
----------

.. _type-daml-finance-lifecycle-event-replacement-t-85632:

**type** `T <type-daml-finance-lifecycle-event-replacement-t-85632_>`_
  \= `Event <type-daml-finance-lifecycle-event-replacement-event-16120_>`_

  Type synonym for ``Event``\.
