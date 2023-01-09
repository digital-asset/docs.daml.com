.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-swap-util-63208:

Module Daml.Finance.Instrument.Swap.Util
========================================

Functions
---------

.. _function-daml-finance-instrument-swap-util-datetodateclocktime-79159:

`dateToDateClockTime <function-daml-finance-instrument-swap-util-datetodateclocktime-79159_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_

  Maps a ``Date`` to ``Time`` using the rule in the ``DateClock``\.

.. _function-daml-finance-instrument-swap-util-getholidaycalendars-89806:

`getHolidayCalendars <function-daml-finance-instrument-swap-util-getholidaycalendars-89806_>`_
  \: `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`\]

  Retrieve holiday calendar(s) from the ledger\.

.. _function-daml-finance-instrument-swap-util-rollschedule-57348:

`rollSchedule <function-daml-finance-instrument-swap-util-rollschedule-57348_>`_
  \: (\[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`\]) \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ :ref:`Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285>`

  Retrieve holiday calendar(s) from the ledger and roll out a schedule\.
