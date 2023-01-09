.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-util-date-daycount-38239:

Module Daml.Finance.Util.Date.DayCount
======================================

Functions
---------

.. _function-daml-finance-util-date-daycount-calcdcf-20432:

`calcDcf <function-daml-finance-util-date-daycount-calcdcf-20432_>`_
  \: :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>` \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  Calculates the day count fraction given the correponding convention\.
  Currently 30E360 is not supported as we do not want to expose the maturity date of the product
  as an additional parameter\.

.. _function-daml-finance-util-date-daycount-calcperioddcf-63067:

`calcPeriodDcf <function-daml-finance-util-date-daycount-calcperioddcf-63067_>`_
  \: :ref:`DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281>` \-\> :ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> :ref:`Frequency <type-daml-finance-interface-types-date-schedule-frequency-38655>` \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  Calculate day count fraction for a schedule period\.
  It takes the following parameters\:

  * DayCountConventionEnum\: to specify which day count convention should be used
  * SchedulePeriod\: the schedule period for which the day count fraction should be calculated
  * Bool\: Whether day count fraction should be calculated on adjusted dates
    (if False\: unadjusted dates)
  * Date\: The maturity date of the instrument
  * Frequency\: the frequency of the schedule period

.. _function-daml-finance-util-date-daycount-calcperioddcfactactisda-92700:

`calcPeriodDcfActActIsda <function-daml-finance-util-date-daycount-calcperioddcfactactisda-92700_>`_
  \: :ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  Calculate Actual Actual day count fraction according to the ISDA method\.

.. _function-daml-finance-util-date-daycount-calcperioddcfactactisma-2363:

`calcPeriodDcfActActIsma <function-daml-finance-util-date-daycount-calcperioddcfactactisma-2363_>`_
  \: :ref:`SchedulePeriod <type-daml-finance-interface-types-date-schedule-scheduleperiod-76784>` \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> :ref:`Frequency <type-daml-finance-interface-types-date-schedule-frequency-38655>` \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  Calculate Actual Actual day count fraction according to the ISMA method\.

.. _function-daml-finance-util-date-daycount-calcdcfactactafb-34442:

`calcDcfActActAfb <function-daml-finance-util-date-daycount-calcdcfactactafb-34442_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

.. _function-daml-finance-util-date-daycount-calcdcfact360-50603:

`calcDcfAct360 <function-daml-finance-util-date-daycount-calcdcfact360-50603_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

.. _function-daml-finance-util-date-daycount-calcdcfact365fixed-87055:

`calcDcfAct365Fixed <function-daml-finance-util-date-daycount-calcdcfact365fixed-87055_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

.. _function-daml-finance-util-date-daycount-calcdcfact365l-74513:

`calcDcfAct365L <function-daml-finance-util-date-daycount-calcdcfact365l-74513_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

.. _function-daml-finance-util-date-daycount-calcdcf30360-14933:

`calcDcf30360 <function-daml-finance-util-date-daycount-calcdcf30360-14933_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

.. _function-daml-finance-util-date-daycount-calcdcf30360icma-73903:

`calcDcf30360Icma <function-daml-finance-util-date-daycount-calcdcf30360icma-73903_>`_
  \: `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

.. _function-daml-finance-util-date-daycount-calcdcf30e360-59313:

`calcDcf30E360 <function-daml-finance-util-date-daycount-calcdcf30e360-59313_>`_
  \: `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_ \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  Calculate 30E/360 day count fraction\.
