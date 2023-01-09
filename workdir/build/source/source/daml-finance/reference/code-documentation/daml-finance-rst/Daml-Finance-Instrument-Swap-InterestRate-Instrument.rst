.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-swap-interestrate-instrument-86260:

Module Daml.Finance.Instrument.Swap.InterestRate.Instrument
===========================================================

Templates
---------

.. _type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927:

**template** `Instrument <type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927_>`_

  This template models an interest rate swap\.
  It pays a fix vs floating rate at the end of every payment period\.
  The floating leg depends on a reference rate (observed at the beginning of the swap payment
  period)\. For example\: 3M Euribor vs 2\.5% fix\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - depository
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The depository of the instrument\.
     * - issuer
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The issuer of the instrument\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - An identifier of the instrument\.
     * - version
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The instrument's version\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A description of the instrument\.
     * - referenceRateId
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The floating rate reference ID\. For example, in case of \"3M Euribor vs 2\.5% fix\" this should be a valid reference to the \"3M Euribor\" reference rate\.
     * - ownerReceivesFix
       - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
       - Indicate whether a holding owner of this instrument receives the fix or the floating leg of the swap\.
     * - fixRate
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The interest rate of the fix leg\. For example, in case of \"3M Euribor vs 2\.5% fix\" this should be 0\.025\.
     * - periodicSchedule
       - :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>`
       - The schedule for the periodic swap payments\.
     * - holidayCalendarIds
       - \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\]
       - The identifiers of the holiday calendars to be used for the swap payment schedule\.
     * - calendarDataProvider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The reference data provider to use for the holiday calendar\.
     * - dayCountConvention
       - :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`
       - The day count convention used to calculate day count fractions\. For example\: Act360\.
     * - currency
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The currency of the swap\. For example, if the swap pays in USD this should be a USD cash instrument\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The observers of the instrument\.
     * - lastEventTimestamp
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` **for** `Instrument <type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-dynamic-instrument-i-39105>` **for** `Instrument <type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-swap-interestrate-instrument-i-65057>` **for** `Instrument <type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927_>`_

Data Types
----------

.. _type-daml-finance-instrument-swap-interestrate-instrument-t-74093:

**type** `T <type-daml-finance-instrument-swap-interestrate-instrument-t-74093_>`_
  \= `Instrument <type-daml-finance-instrument-swap-interestrate-instrument-instrument-52927_>`_

  Type synonym for ``Instrument``\.
