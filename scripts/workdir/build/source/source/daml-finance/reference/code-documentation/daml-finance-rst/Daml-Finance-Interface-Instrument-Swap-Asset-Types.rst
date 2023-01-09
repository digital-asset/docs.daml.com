.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-asset-types-80415:

Module Daml.Finance.Interface.Instrument.Swap.Asset.Types
=========================================================

Data Types
----------

.. _type-daml-finance-interface-instrument-swap-asset-types-asset-84576:

**data** `Asset <type-daml-finance-interface-instrument-swap-asset-types-asset-84576_>`_

  Describes the attributes of an Asset swap\.

  .. _constr-daml-finance-interface-instrument-swap-asset-types-asset-4825:

  `Asset <constr-daml-finance-interface-instrument-swap-asset-types-asset-4825_>`_

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
       * - referenceAssetId
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - The reference asset ID\. For example, in case of \"AAPL total return vs 2\.5% fix\" this should be a valid reference to the AAPL fixings to be used for the total return calculation (dividend\-adjusted fixings)\.
       * - ownerReceivesFix
         - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
         - Indicate whether a holding owner of this instrument receives the fix or the asset leg of the swap\.
       * - fixRate
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - The interest rate of the fix leg\. For example, in case of \"AAPL total return vs 2\.5% fix\" this should be 0\.025\.
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
       * - lastEventTimestamp
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Asset <type-daml-finance-interface-instrument-swap-asset-types-asset-84576_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Asset <type-daml-finance-interface-instrument-swap-asset-types-asset-84576_>`_
