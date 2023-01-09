.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-util-date-calendar-17588:

Module Daml.Finance.Util.Date.Calendar
======================================

Functions
---------

.. _function-daml-finance-util-date-calendar-merge-27357:

`merge <function-daml-finance-util-date-calendar-merge-27357_>`_
  \: \[:ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`\] \-\> :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>`

  Merge multiple holiday calendars into a single one\. ``id``\\s are concatenated by ``,``\.

.. _function-daml-finance-util-date-calendar-isholiday-90681:

`isHoliday <function-daml-finance-util-date-calendar-isholiday-90681_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_

  Check if Date is a holiday\.

.. _function-daml-finance-util-date-calendar-isbusinessday-18409:

`isBusinessDay <function-daml-finance-util-date-calendar-isbusinessday-18409_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_

  Check if Date is a business day\.

.. _function-daml-finance-util-date-calendar-nextbusinessday-93322:

`nextBusinessDay <function-daml-finance-util-date-calendar-nextbusinessday-93322_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Get next business day\.

.. _function-daml-finance-util-date-calendar-previousbusinessday-3102:

`previousBusinessDay <function-daml-finance-util-date-calendar-previousbusinessday-3102_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Get previous business day\.

.. _function-daml-finance-util-date-calendar-nextorsamebusinessday-41239:

`nextOrSameBusinessDay <function-daml-finance-util-date-calendar-nextorsamebusinessday-41239_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Get next or same business day\.

.. _function-daml-finance-util-date-calendar-previousorsamebusinessday-31403:

`previousOrSameBusinessDay <function-daml-finance-util-date-calendar-previousorsamebusinessday-31403_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Get previous or same business day\.

.. _function-daml-finance-util-date-calendar-nextsameorlastinmonthbusinessday-99135:

`nextSameOrLastInMonthBusinessDay <function-daml-finance-util-date-calendar-nextsameorlastinmonthbusinessday-99135_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Get next or same business day if before end of month\. Otherwise get last business day in month\.

.. _function-daml-finance-util-date-calendar-previoussameorfirstinmonthbusinessday-25034:

`previousSameOrFirstInMonthBusinessDay <function-daml-finance-util-date-calendar-previoussameorfirstinmonthbusinessday-25034_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Get previous or same business day if before end of month\. Otherwise get first business day in
  month\.

.. _function-daml-finance-util-date-calendar-addbusinessdays-56333:

`addBusinessDays <function-daml-finance-util-date-calendar-addbusinessdays-56333_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Add business days to a Date\.

.. _function-daml-finance-util-date-calendar-adjustdate-66741:

`adjustDate <function-daml-finance-util-date-calendar-adjustdate-66741_>`_
  \: :ref:`HolidayCalendarData <type-daml-finance-interface-types-date-calendar-holidaycalendardata-60004>` \-\> :ref:`BusinessDayConventionEnum <type-daml-finance-interface-types-date-calendar-businessdayconventionenum-88986>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_

  Adjust date according to the given business day convention\.
