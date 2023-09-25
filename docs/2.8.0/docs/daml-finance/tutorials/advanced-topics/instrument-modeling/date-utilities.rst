.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to use the calendar, schedule, and day count utility functions
#################################################################

The Daml Finance library contains date-related utility functions for
implementing industry-standard conventions. These functions are used
internally in instruments like bonds and swaps, but they can also be helpful in
your own custom use cases. For example, you can use these functions to:

- develop your own instruments that depend on business day shifts, schedules, and/or day count
  conventions
- understand and validate the implementation of existing Daml Finance instruments
- compose existing Daml Finance instruments, for example define a series of zero coupon bonds
  according to a specific schedule of expiries
- use these calendar and schedule related functionalities for non-financial use cases

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
and which dates are additional holidays.

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

This also works for a given number of business days in the *past*, just pass in a negative offset:

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

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_ADD_PERIOD_DAY_WEEK_MONTH_YEAR_BEGIN
  :end-before: -- TEST_ADD_PERIOD_DAY_WEEK_MONTH_YEAR_END

This function can also handle edge cases, for example when adding a period of one month to a date
that may not exist, because the resulting month has fewer days than the starting month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_ADD_PERIOD_MONTH_END_EDGE_CASE_BEGIN
  :end-before: -- TEST_ADD_PERIOD_MONTH_END_EDGE_CASE_END

If you need to *subtract* a period, just use a negative offset:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_ADD_PERIOD_NEGATIVE_OFFSET_BEGIN
  :end-before: -- TEST_ADD_PERIOD_NEGATIVE_OFFSET_END

Sometimes, it is important to find the start date of the next period according to a specific market
convention, as described in the
:ref:`RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360>`.
The *Roll convention* specifies which date to use in the next period.

For example, we can define an end-of-month roll:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_NEXT_EOM_BEGIN
  :end-before: -- TEST_NEXT_EOM_END

Alternatively, we can also define a roll to a specific day of the month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_NEXT_DOM1_BEGIN
  :end-before: -- TEST_NEXT_DOM1_END

If the resulting month does not have enough days, it will default to the last day of the month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_NEXT_DOM_PAST_EOM_BEGIN
  :end-before: -- TEST_NEXT_DOM_PAST_EOM_END

This function also takes leap days into account:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_NEXT_DOM_PAST_EOFEB_BEGIN
  :end-before: -- TEST_NEXT_DOM_PAST_EOFEB_END

Similarly, it is possible to roll to the *previous* period:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/RollConvention.daml
  :language: daml
  :start-after: -- TEST_PREVIOUS_DOM_FROM_EOFEB_BEGIN
  :end-before: -- TEST_PREVIOUS_DOM_FROM_EOFEB_END

While the above :ref:`RollConvention <module-daml-finance-util-date-rollconvention-88672>` functions
can be useful on their own, they are often used in the context of rolling out a schedule. This is
explained in the next section.

Schedule
========

The :ref:`Schedule <module-daml-finance-util-date-schedule-32303>` module contains functions for
creating a series of time periods.
A schedule can be used to represent different aspects of a financial instrument, for example:

- payment periods, which define e.g. *when* a bond coupon or a swap payment should be paid
- calculation periods, which define e.g. *how* the interest amount is calculated

For example, let us define a periodic 3M schedule that rolls on the 30th of the month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Schedule.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_END

Since there is one year between the start and the end date, we would expect this periodic schedule
to correspond to four periods of 3M each:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Schedule.daml
  :language: daml
  :start-after: -- CREATE_EXPECTED_SCHEDULE_RESULT_BEGIN
  :end-before: -- CREATE_EXPECTED_SCHEDULE_RESULT_END

Note that we distinguish between adjusted and unadjusted dates. The unadjusted date is the result of
adding a specified time period to the start date of the previous schedule period. This can fall on a
non-business day. By applying a
:ref:`BusinessDayAdjustment <type-daml-finance-interface-types-date-calendar-businessdayadjustment-93933>`,
we also get an adjusted date, which must fall on a business day.

Now, let us roll out this schedule to get the specific start and end date for each period, and
compare it to the expected result:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Schedule.daml
  :language: daml
  :start-after: -- CREATE_SCHEDULE_BEGIN
  :end-before: -- CREATE_SCHEDULE_END

An important aspect of schedules is the concept of *stub periods*. The above schedule only had
regular 3M periods. However, if the sample schedule would start one month later:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Schedule.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_WITH_STUB_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_WITH_STUB_END

it would only have 11 months in total, which does not match with neither 3 nor 4 regular 3M periods.
Instead, we need to define a stub period, so that the rest of the schedule is regular.
In the example above, we did this by defining a start date for the first regular period. This
implies a short initial stub period, in our case 2 months. We would expect the following schedule:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Schedule.daml
  :language: daml
  :start-after: -- CREATE_EXPECTED_SCHEDULE_RESULT_WITH_STUB_BEGIN
  :end-before: -- CREATE_EXPECTED_SCHEDULE_RESULT_WITH_STUB_END

Different stub types can be configured using the
:ref:`StubPeriodTypeEnum <type-daml-finance-interface-types-date-schedule-stubperiodtypeenum-69372>`
data type. You can configure whether the stub period should be at the beginning or at the end of the
schedule, as well as whether the stub period should be longer or shorter than a regular period.

Let us roll out this schedule, which includes a stub period, and compare it to the expected result:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Schedule.daml
  :language: daml
  :start-after: -- CREATE_SCHEDULE_WITH_STUB_BEGIN
  :end-before: -- CREATE_SCHEDULE_WITH_STUB_END


DayCount
========

Many instruments that pay interest (often expressed as an annualized rate) require an exact
definition of how many days of interest belong to each payment period. The
:ref:`DayCount <module-daml-finance-util-date-daycount-38239>` module provides functions for this.
In particular, a *day count fraction* (or *dcf* in short) can be calculated between two dates. This
indicates the fraction of a full year.

For example, consider a one year bond that pays a quarterly coupon according to a given schedule,
like the one described in the previous section.

This bond will not have the same number of days in each period, which will normally result in
different coupon amounts for each period. There are various market conventions for this, several of
which are supported using the
:ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`.

Consider the schedule with a short initial stub in the previous section. The following example
uses the ``Act360`` day count convention:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/DayCount.daml
  :language: daml
  :start-after: -- CALCULATE_ACT360_DCF_PERIOD1_BEGIN
  :end-before: -- CALCULATE_ACT360_DCF_PERIOD1_END

which corresponds to the 2M short initial stub period. This day count fraction can be used to
calculate a bond coupon or a swap payment for the given period, by multiplying it with the yearly
interest rate of the instrument, e.g. 4% per annum.

We can compare this initial day count fraction with those of the 2nd and 3rd periods of this
schedule, which are both regular (3M):

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/DayCount.daml
  :language: daml
  :start-after: -- CALCULATE_ACT360_DCF_PERIOD2AND3_BEGIN
  :end-before: -- CALCULATE_ACT360_DCF_PERIOD2AND3_END

These day count fractions are clearly greater than the one of the first period, since they
correspond to 3M instead of 2M. Note that they differ slightly: they do not contain the
exact same number of days.

In addition to ``Act360``, the
:ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>`
supports several other day count conventions. You can compute some of them with
:ref:`calcDcf <function-daml-finance-util-date-daycount-calcdcf-20432>`, using only a start and an
end date as an input as shown above.
Others, e.g. ``ActActISDA``, are a bit more complicated because they require additional information.
They can be calculated using the
:ref:`calcPeriodDcf <function-daml-finance-util-date-daycount-calcperioddcf-63067>` function
instead, which takes a schedule period (containing stub information) as input, as well as the
schedule end date and the payment frequency:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/DayCount.daml
  :language: daml
  :start-after: -- CALCULATE_ACTACTISDA_DCF_SCHEDULE_PERIOD_BEGIN
  :end-before: -- CALCULATE_ACTACTISDA_DCF_SCHEDULE_PERIOD_END
