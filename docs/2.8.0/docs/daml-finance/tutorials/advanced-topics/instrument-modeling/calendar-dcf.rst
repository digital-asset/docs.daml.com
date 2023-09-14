.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to use the calendar, schedule and day count utility functions
#################################################################

The Daml Finance library contains date related utility functions that are used to implement industry
standard conventions. These are used internally in instruments like Bonds and Swaps. However, there
are use cases where it could be useful to understand these in more detail, for example if you want
to:

- understand and validate the implementation of current Daml Finance instruments
- develop your own instruments that depend on schedules, business day shifts and/or day count
  conventions
- compose existing daml finance instruments, for example a set of zero coupon bonds according to a
  specific schedule of expiries
- use this calendar and schedule related functionality for non-financial use cases

Calendar
========

The Calendar module contains various utility functions related to business days and date adjustments.

For example, given a current date and a holiday calendar, we can check whether it is a business day:
isBusinessDay

It is also possible to get the previous and the next business day:
previousBusinessDay, nextBusinessDay

Quite often, we are required to find out the date of a given number of business days in the future:
addBusinessDays

This also works with business days in the past, just pass in a negative offset:
addBusinessDays

Finally, it is also possible to adjust a date according to a given business day convention:
adjustDate

RollConvention
==============

The RollConvention module provides utility functions to add a period to a given date:

For example, you can add a day, week, month or a year to a given date:
addPeriod

This can also handle edge cases, for example in case of a monthly roll to a date that may not exist:
addPeriod jan 31 to end of feb

Sometimes, it is important to adjust the period according to a specific market convention:
next jan 31 to end of feb

Similarly, it is also possible to get the previous period:
previous

Schedule
========

While the above RollConvention functions can be useful on their own, they are often required in the
context of rolling out a schedule. This functionality is included in the Schedule module.

For example, let us define a periodic schedule

We can then roll out this schedule to get the specific start and end date for each period. These
dates are both available as adjusted and unadjusted.
createSchedule

An important aspect of schedules is the concept of stub periods. For example, consider a yearly
schedule between Jan 15 2023 and May 15 2025. Clearly, regular periods are not sufficient here.
Instead, we need to define a stub period, so that the rest of the schedule is regular:
periodic schedule
createSchedule

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

