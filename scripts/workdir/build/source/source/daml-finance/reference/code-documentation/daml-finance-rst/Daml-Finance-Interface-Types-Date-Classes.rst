.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-types-date-classes-73544:

Module Daml.Finance.Interface.Types.Date.Classes
================================================

Typeclasses
-----------

.. _class-daml-finance-interface-types-date-classes-hasutctimeconversion-83616:

**class** `HasUTCTimeConversion <class-daml-finance-interface-types-date-classes-hasutctimeconversion-83616_>`_ a **where**

  Types that can be converted to UTC time\.

  .. _function-daml-finance-interface-types-date-classes-toutctime-25113:

  `toUTCTime <function-daml-finance-interface-types-date-classes-toutctime-25113_>`_
    \: a \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_

  **instance** `HasUTCTimeConversion <class-daml-finance-interface-types-date-classes-hasutctimeconversion-83616_>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>`

  **instance** `HasUTCTimeConversion <class-daml-finance-interface-types-date-classes-hasutctimeconversion-83616_>`_ :ref:`Unit <type-daml-finance-data-time-dateclock-types-unit-52065>`
