.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-swap-currency-instrument-67721:

Module Daml.Finance.Instrument.Swap.Currency.Instrument
=======================================================

Templates
---------

.. _type-daml-finance-instrument-swap-currency-instrument-instrument-482:

**template** `Instrument <type-daml-finance-instrument-swap-currency-instrument-instrument-482_>`_

  This template models a currency swap\.
  It pays a fix vs fix rate (in different currencies) at the end of every payment period\.
  The principal in the foreign currency is calculated using an fx rate and the principal amount in
  the base currency\. The principal is not exchanged\.
  For example\: USD 1000k principal, fx rate 1\.10 \-\> EUR 1100k principal
  3% fix rate on USD 1000k vs
  2% fix rate on EUR 1100k

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
     * - ownerReceivesBase
       - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
       - Indicate whether a holding owner of this instrument receives the base currency leg or the foreign currency leg of the swap\.
     * - baseRate
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The interest rate of the base currency\. For example, in case of \"3% in USD\" this should be 0\.03\.
     * - foreignRate
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The interest rate of the foreign currency\. For example, in case of \"2% in EUR\" this should be 0\.02\.
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
     * - baseCurrency
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The base currency of the swap\. For example, in the case of USD this should be a USD cash instrument\.
     * - foreignCurrency
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The foreign currency of the swap\. For example, in case of EUR this should be a EUR cash instrument\.
     * - fxRate
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The fx rate used to convert from the base currency principal amount to the foreign currency principal amount\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The observers of the instrument\.
     * - lastEventTimestamp
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` **for** `Instrument <type-daml-finance-instrument-swap-currency-instrument-instrument-482_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-dynamic-instrument-i-39105>` **for** `Instrument <type-daml-finance-instrument-swap-currency-instrument-instrument-482_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-swap-currency-instrument-instrument-482_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-swap-currency-instrument-i-90910>` **for** `Instrument <type-daml-finance-instrument-swap-currency-instrument-instrument-482_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-swap-currency-instrument-instrument-482_>`_

Data Types
----------

.. _type-daml-finance-instrument-swap-currency-instrument-t-1922:

**type** `T <type-daml-finance-instrument-swap-currency-instrument-t-1922_>`_
  \= `Instrument <type-daml-finance-instrument-swap-currency-instrument-instrument-482_>`_

  Type synonym for ``Instrument``\.
