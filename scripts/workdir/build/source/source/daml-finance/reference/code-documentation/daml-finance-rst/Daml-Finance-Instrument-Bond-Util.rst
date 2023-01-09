.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-bond-util-70458:

Module Daml.Finance.Instrument.Bond.Util
========================================

Functions
---------

.. _function-daml-finance-instrument-bond-util-datetodateclocktime-47417:

`dateToDateClockTime <function-daml-finance-instrument-bond-util-datetodateclocktime-47417_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_

  Maps a ``Date`` to ``Time`` using the rule in the ``DateClock``\.

.. _function-daml-finance-instrument-bond-util-getholidaycalendars-3084:

`getHolidayCalendars <function-daml-finance-instrument-bond-util-getholidaycalendars-3084_>`_
  \: `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`\]

  Retrieve holiday calendar(s) from the ledger\.

.. _function-daml-finance-instrument-bond-util-rollschedule-46914:

`rollSchedule <function-daml-finance-instrument-bond-util-rollschedule-46914_>`_
  \: (\[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`\]) \-\> :ref:`PeriodicSchedule <type-daml-finance-interface-types-date-schedule-periodicschedule-97930>` \-\> \[`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ :ref:`Schedule <type-daml-finance-interface-types-date-schedule-schedule-17285>`

  Retrieve holiday calendar(s) from the ledger and roll out a schedule\.
