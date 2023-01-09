.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-bond-floatingrate-instrument-98586:

Module Daml.Finance.Instrument.Bond.FloatingRate.Instrument
===========================================================

Templates
---------

.. _type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025:

**template** `Instrument <type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025_>`_

  This template models a floating rate bond\.
  It pays a floating coupon rate at the end of every coupon period\.
  This consists of a reference rate (observed at the beginning of the coupon period) plus a coupon
  spread\. For example, 3M Euribor \+ 0\.5%\.

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
       - The floating rate reference ID\. For example, in case of \"3M Euribor \+ 0\.5%\" this should be a valid reference to the \"3M Euribor\" reference rate\. FLOATING\_RATE\_BOND\_TEMPLATE\_UNTIL\_REFRATE\_END
     * - couponSpread
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The floating rate coupon spread\. For example, in case of \"3M Euribor \+ 0\.5%\" this should be 0\.005\.
     * - periodicSchedule
       - :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>`
       - The schedule for the periodic coupon payments\.
     * - holidayCalendarIds
       - \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\]
       - The identifiers of the holiday calendars to be used for the coupon schedule\.
     * - calendarDataProvider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The reference data provider to use for the holiday calendar\.
     * - dayCountConvention
       - :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`
       - The day count convention used to calculate day count fractions\. For example\: Act360\.
     * - currency
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The currency of the bond\. For example, if the bond pays in USD this should be a USD cash instrument\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The observers of the instrument\.
     * - lastEventTimestamp
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` **for** `Instrument <type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-dynamic-instrument-i-39105>` **for** `Instrument <type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-bond-floatingrate-instrument-i-64015>` **for** `Instrument <type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025_>`_

Data Types
----------

.. _type-daml-finance-instrument-bond-floatingrate-instrument-t-57047:

**type** `T <type-daml-finance-instrument-bond-floatingrate-instrument-t-57047_>`_
  \= `Instrument <type-daml-finance-instrument-bond-floatingrate-instrument-instrument-67025_>`_

  Type synonym for ``Instrument``\.
