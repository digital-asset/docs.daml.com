.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to use the calendar, schedule and day count utility functions
#################################################################

The Daml Finance library contains date related utility functions that are used to implement industry
standard conventions. These are mainly used internally in instruments like Bonds and Swaps. However,
there are use cases where it would be helfpul for users to understand these in more detail, for
example if you want to:

- develop your own instruments that depend on business day shifts, schedules, and/or day count
  conventions
- understand and validate the implementation of current Daml Finance instruments
- compose existing Daml Finance instruments, for example define a series of zero coupon bonds
  according to a specific schedule of expiries
- use this calendar and schedule related functionality for non-financial use cases

Calendar
========

The :ref:`Calendar <module-daml-finance-util-date-calendar-17588>` module contains various utility
functions related to business days and date adjustments.

Business days and non-business days are distinguished by defining a holiday calendar, for example:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_HOLIDAY_CALENDAR_DATA_BEGIN
  :end-before: -- CREATE_HOLIDAY_CALENDAR_DATA_END

The :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`
type describes the set of non-business days by defining which days of the week belong to the weekend
and which dates are general holidays.

We can now check whether a given date is a business day:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_IS_BUSINESS_DAY_BEGIN
  :end-before: -- TEST_IS_BUSINESS_DAY_END

It is also possible to get the previous and the next business day:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_PREVIOUS_BUSINESS_DAY_BEGIN
  :end-before: -- TEST_PREVIOUS_BUSINESS_DAY_END

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_NEXT_BUSINESS_DAY_BEGIN
  :end-before: -- TEST_NEXT_BUSINESS_DAY_END

Quite often, we are required to find out the date that corresponds to a given number of business
days in the future:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_BUSINESS_DAYS_BEGIN
  :end-before: -- TEST_ADD_BUSINESS_DAYS_END

This also works with a given number of business days in the past, just pass in a negative offset:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_BUSINESS_DAYS_NEGATIVE_OFFSET_BEGIN
  :end-before: -- TEST_ADD_BUSINESS_DAYS_NEGATIVE_OFFSET_END

Finally, it is also possible to adjust a date according to a given business day convention:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADJUST_DATE_BEGIN
  :end-before: -- TEST_ADJUST_DATE_END

The different conventions are described in the
:ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>`.
In particular, they describe what should happen if the next/previous business day is around month
end.

RollConvention
==============

The :ref:`RollConvention <module-daml-finance-util-date-rollconvention-88672>` module provides
utility functions to add a period to a given date.

For example, you can add a day, week, month or a year to a given date:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_PERIOD_DAY_WEEK_MONTH_YEAR_BEGIN
  :end-before: -- TEST_ADD_PERIOD_DAY_WEEK_MONTH_YEAR_END

This function can also handle edge cases, for example in case of a monthly roll to a date that may
not exist, because the resulting month has fewer days than the starting month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_PERIOD_MONTH_END_EDGE_CASE_BEGIN
  :end-before: -- TEST_ADD_PERIOD_MONTH_END_EDGE_CASE_END

If you need to *subtract* a period, just use a negative offset:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_PERIOD_NEGATIVE_OFFSET_BEGIN
  :end-before: -- TEST_ADD_PERIOD_NEGATIVE_OFFSET_END

Sometimes, it is important to find the start date of the next period according to a specific market
convention, as described in the
:ref:`RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360>`.
For example, for an end-of-month roll:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_NEXT_EOM_BEGIN
  :end-before: -- TEST_NEXT_EOM_END

Alternatively, we can also define a roll to a specific day of the month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_NEXT_DOM1_BEGIN
  :end-before: -- TEST_NEXT_DOM1_END

If the destination month does not have enough days, it will default to the last day of the month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_NEXT_DOM_PAST_EOM_BEGIN
  :end-before: -- TEST_NEXT_DOM_PAST_EOM_END

This function also takes leap days into account:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_NEXT_DOM_PAST_EOFEB_BEGIN
  :end-before: -- TEST_NEXT_DOM_PAST_EOFEB_END

Similarly, it is possible to roll to the *previous* period:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_PREVIOUS_DOM_FROM_EOFEB_BEGIN
  :end-before: -- TEST_PREVIOUS_DOM_FROM_EOFEB_END

Schedule
========

While the above :ref:`RollConvention <module-daml-finance-util-date-rollconvention-88672>` functions
can be useful on their own, they are often required in the context of rolling out a schedule. This
functionality is included in the :ref:`Date.Schedule <module-daml-finance-util-date-schedule-32303>`
module.

For example, let us define a periodic 3M schedule that rolls on the 30th of the month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_END

We would expect this periodic schedule to correspond to four periods of 3M each:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_EXPECTED_SCHEDULE_RESULT_BEGIN
  :end-before: -- CREATE_EXPECTED_SCHEDULE_RESULT_END

Now, let us roll out this schedule to get the specific start and end date for each period, and
compare it to the expected result:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_SCHEDULE_BEGIN
  :end-before: -- CREATE_SCHEDULE_END

An important aspect of schedules is the concept of *stub periods*. The above schedule only had
regular 3M periods. However, if the sample schedule would start one month later:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_WITH_STUB_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_WITH_STUB_END

it would only have 11 months in total, which is does not match with neither 3 nor 4 regular 3M
periods. Instead, we need to define a stub period, so that the rest of the schedule is regular.
In the example above, we did this by defining a start date for the first regular period. This
implies a short initial stub period, in our case 2 months. We would expect the following schedule:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_EXPECTED_SCHEDULE_RESULT_WITH_STUB_BEGIN
  :end-before: -- CREATE_EXPECTED_SCHEDULE_RESULT_WITH_STUB_END

Different stub types can be configured using the
:ref:`StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372>`
data type. You can configure whether the stub period should be at the beginning or at the end of the
schedule, as well as whether the stub period should be longer or shorter than a regular period.

Let us roll out this schedule (indluding the stub period) and compare it to the expected result:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_SCHEDULE_WITH_STUB_BEGIN
  :end-before: -- CREATE_SCHEDULE_WITH_STUB_END

The schedule periods can be used to represent different aspects of a financial instrument, for
example:

- calculation periods, which define e.g. *how* an interest rate is calculated
- payment periods, which define e.g. *when* a bond coupon or a swap payment should be paid

DayCount
========

Many instruments that pay interest require an exact definition of how many days of interest belong
to each payment period. The :ref:`Date.DayCount <module-daml-finance-util-date-daycount-38239>`
module provides functions for this.

For example, consider a one year bond that pays a quarterly coupon according to a given schedule,
like the ones described in the previous chapter.

This bond will not have the same number of days in each period, which will typically result in
different coupon amounts for the periods. There are various market conventions for this, several of
which are supported using the
:ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`.

For example, consider the schedule with a short initial stub in the previous chapter. If we want to
calculate the ``Act360`` day count convention:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CALCULATE_ACT360_DCF_PERIOD1_BEGIN
  :end-before: -- CALCULATE_ACT360_DCF_PERIOD1_END

which corresponds to the 2M short initial stub period. This day count fraction can be used to
calculate a bond coupon or a swap payment for the given period, by multiplying it with the yearly
interest rate of the instrument, e.g. 4% per annum.

We can compare this initial day count fraction with those of the 2nd and 3rd periods of this
schedule, which are both regular (3M):

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CALCULATE_ACT360_DCF_PERIOD2AND3_BEGIN
  :end-before: -- CALCULATE_ACT360_DCF_PERIOD2AND3_END

These day count fractions are clearly greater than the one of the first period, since they
correspond to 3M instead of 2M. Note that they differ slightly, because they do not contain the
exact same number of days.

In addition to ``Act360``, the
:ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`
also supports several other day count conventions. Some of them can be computed using
:ref:`calcDcf <function-daml-finance-util-date-daycount-calcdcf-20432>`, using only a start and an
end date as an input, as described above.
Others, e.g. ``ActActISDA``, require additional information. They can be calculated using the
:ref:`calcPeriodDcf <function-daml-finance-util-date-daycount-calcperioddcf-63067>` function
instead, which also contains stub information as well as the schedule end date and the payment
frequency:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CALCULATE_ACTACTISDA_DCF_SCHEDULE_PERIOD_BEGIN
  :end-before: -- CALCULATE_ACTACTISDA_DCF_SCHEDULE_PERIOD_END
