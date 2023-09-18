.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to use the calendar, schedule and day count utility functions
#################################################################

The Daml Finance library contains date related utility functions that are used to implement industry
standard conventions. These are used internally in instruments like Bonds and Swaps. However, there
are use cases where it could be useful to understand these in more detail, for example if you want
to:

- develop your own instruments that depend on schedules, business day shifts and/or day count
  conventions
- understand and validate the implementation of current Daml Finance instruments
- compose existing daml finance instruments, for example define multiple zero coupon bonds according to a
  specific schedule of expiries
- use this calendar and schedule related functionality for non-financial use cases

Calendar
========

The Calendar (link) module contains various utility functions related to business days and date adjustments.

Business days and non-business days are distinguished by defining a holiday calendar, for example:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_HOLIDAY_CALENDAR_DATA_BEGIN
  :end-before: -- CREATE_HOLIDAY_CALENDAR_DATA_END

This HolidayCalendarData (link) type describes which dates are non-business days.

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

Quite often, we are required to find out the date of a given number of business days in the future:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_BUSINESS_DAYS_BEGIN
  :end-before: -- TEST_ADD_BUSINESS_DAYS_END

This also works with business days in the past, just pass in a negative offset:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_BUSINESS_DAYS_NEGATIVE_OFFSET_BEGIN
  :end-before: -- TEST_ADD_BUSINESS_DAYS_NEGATIVE_OFFSET_END

Finally, it is also possible to adjust a date according to a given business day convention:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADJUST_DATE_BEGIN
  :end-before: -- TEST_ADJUST_DATE_END

The different conventions are described in the BusinessDayConventionEnum (link).

RollConvention
==============

The RollConvention module provides utility functions to add a period to a given date:

For example, you can add a day, week, month or a year to a given date:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_ADD_PERIOD_DAY_WEEK_MONTH_YEAR_BEGIN
  :end-before: -- TEST_ADD_PERIOD_DAY_WEEK_MONTH_YEAR_END

This can also handle edge cases, for example in case of a monthly roll to a date that may not exist,
because the resulting month has fewer days than the starting month:

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
convention, as described in RollConventionEnum (link). For example, for an end-of-month roll:

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

This also takes leap days into account:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_NEXT_DOM_PAST_EOFEB_BEGIN
  :end-before: -- TEST_NEXT_DOM_PAST_EOFEB_END

Similarly, it is also possible to roll to the *previous* period:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- TEST_PREVIOUS_DOM_FROM_EOFEB_BEGIN
  :end-before: -- TEST_PREVIOUS_DOM_FROM_EOFEB_END

Schedule
========

While the above RollConvention functions can be useful on their own, they are often required in the
context of rolling out a schedule. This functionality is included in the Schedule module.

For example, let us define a periodic 3M schedule that rolls on the 30th of the month:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_END

We would expect this period schedule to correspond to four periods of 3M each:

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

An important aspect of schedules is the concept of stub periods. The above schedule only had regular
3M periods. However, if the sample schedule would start one month later:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_PERIODIC_SCHEDULE_WITH_STUB_BEGIN
  :end-before: -- CREATE_PERIODIC_SCHEDULE_WITH_STUB_END

it would only have 11 months in total, which is does not match with neither
3 nor 4 regular 3M periods. Instead, we need to define a stub period, so that the rest of the schedule is regular.
In the example above, we did this by defining a start date for the first regular period. This implies a short initial
stub period, in our case 2 months. We would expect the following schedule:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_EXPECTED_SCHEDULE_RESULT_WITH_STUB_BEGIN
  :end-before: -- CREATE_EXPECTED_SCHEDULE_RESULT_WITH_STUB_END

Different stub types can be configured using the StubPeriodTypeEnum (link) data type.

Again, let us roll out this schedule to get the and
compare it to the expected result:

.. literalinclude:: ../../../src/test/daml/Daml/Finance/Util/Test/Date/Calendar.daml
  :language: daml
  :start-after: -- CREATE_SCHEDULE_WITH_STUB_BEGIN
  :end-before: -- CREATE_SCHEDULE_WITH_STUB_END

DayCount
========

Many interest paying instruments require an exact definition of how many days of interest belong to
each payment period. For example, consider a one year bond that pays a quarterly coupon according
to the following schedule:

This bond will not have the same number of days in each period, which will typically result in a
different coupon amounts for the periods. There are various market conventions for this, severeral
of which are supported using the DayCountConventionEnum.

For example, consider the Act360 day count convention:

This can be used to determine the coupon of amount in this period:

