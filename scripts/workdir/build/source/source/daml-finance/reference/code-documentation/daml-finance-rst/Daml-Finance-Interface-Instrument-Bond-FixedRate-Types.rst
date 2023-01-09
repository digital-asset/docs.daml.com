.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-fixedrate-types-40221:

Module Daml.Finance.Interface.Instrument.Bond.FixedRate.Types
=============================================================

Data Types
----------

.. _type-daml-finance-interface-instrument-bond-fixedrate-types-fixedrate-80866:

**data** `FixedRate <type-daml-finance-interface-instrument-bond-fixedrate-types-fixedrate-80866_>`_

  Describes the attributes of a Fixed Rate Bond\.

  .. _constr-daml-finance-interface-instrument-bond-fixedrate-types-fixedrate-27839:

  `FixedRate <constr-daml-finance-interface-instrument-bond-fixedrate-types-fixedrate-27839_>`_

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
         - The description of the bond\.
       * - couponRate
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - The fixed coupon rate, per annum\. For example, in case of a \"3\.5% p\.a\. coupon\" this should be 0\.035\.
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
       * - lastEventTimestamp
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `FixedRate <type-daml-finance-interface-instrument-bond-fixedrate-types-fixedrate-80866_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `FixedRate <type-daml-finance-interface-instrument-bond-fixedrate-types-fixedrate-80866_>`_
