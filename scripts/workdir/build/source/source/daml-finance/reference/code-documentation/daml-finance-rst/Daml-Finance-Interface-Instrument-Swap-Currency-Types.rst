.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-currency-types-6291:

Module Daml.Finance.Interface.Instrument.Swap.Currency.Types
============================================================

Data Types
----------

.. _type-daml-finance-interface-instrument-swap-currency-types-currencyswap-33117:

**data** `CurrencySwap <type-daml-finance-interface-instrument-swap-currency-types-currencyswap-33117_>`_

  Describes the attributes of a Currency swap\.

  .. _constr-daml-finance-interface-instrument-swap-currency-types-currencyswap-82444:

  `CurrencySwap <constr-daml-finance-interface-instrument-swap-currency-types-currencyswap-82444_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument's key\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - The description of the swap\.
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
       * - lastEventTimestamp
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `CurrencySwap <type-daml-finance-interface-instrument-swap-currency-types-currencyswap-33117_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CurrencySwap <type-daml-finance-interface-instrument-swap-currency-types-currencyswap-33117_>`_
