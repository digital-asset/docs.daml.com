.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-bond-fixedrate-instrument-67993:

Module Daml.Finance.Instrument.Bond.FixedRate.Instrument
========================================================

Templates
---------

.. _type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814:

**template** `Instrument <type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814_>`_

  This template models a fixed rate bond\.
  It pays a fixed coupon rate at the end of every coupon period\.

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
       - The identifier of the instrument\.
     * - version
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The instrument's version\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A description of the instrument\.
     * - couponRate
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The fixed coupon rate, per annum\. For example, in case of a \"3\.5% p\.a coupon\" this should be 0\.035\.
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
       - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\. FIXED\_RATE\_BOND\_TEMPLATE\_END

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` **for** `Instrument <type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-dynamic-instrument-i-39105>` **for** `Instrument <type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-bond-fixedrate-instrument-i-93672>` **for** `Instrument <type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814_>`_

Data Types
----------

.. _type-daml-finance-instrument-bond-fixedrate-instrument-t-25822:

**type** `T <type-daml-finance-instrument-bond-fixedrate-instrument-t-25822_>`_
  \= `Instrument <type-daml-finance-instrument-bond-fixedrate-instrument-instrument-23814_>`_

  Type synonym for ``Instrument``\.
