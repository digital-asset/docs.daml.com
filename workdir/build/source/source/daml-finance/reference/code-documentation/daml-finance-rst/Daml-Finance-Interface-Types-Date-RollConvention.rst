.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-types-date-rollconvention-76363:

Module Daml.Finance.Interface.Types.Date.RollConvention
=======================================================

Data Types
----------

.. _type-daml-finance-interface-types-date-rollconvention-period-21180:

**data** `Period <type-daml-finance-interface-types-date-rollconvention-period-21180_>`_

  A data type to define periods\.

  .. _constr-daml-finance-interface-types-date-rollconvention-period-50287:

  `Period <constr-daml-finance-interface-types-date-rollconvention-period-50287_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - period
         - `PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659_>`_
         - A period, e\.g\., a day, week, month or year\.
       * - periodMultiplier
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         - A period multiplier, e\.g\., 1, 2 or 3 etc\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Period <type-daml-finance-interface-types-date-rollconvention-period-21180_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Period <type-daml-finance-interface-types-date-rollconvention-period-21180_>`_

.. _type-daml-finance-interface-types-date-rollconvention-periodenum-51659:

**data** `PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659_>`_

  An enum type to specify a period, e\.g\., day or week\.

  .. _constr-daml-finance-interface-types-date-rollconvention-d-42425:

  `D <constr-daml-finance-interface-types-date-rollconvention-d-42425_>`_

    Day

  .. _constr-daml-finance-interface-types-date-rollconvention-m-75108:

  `M <constr-daml-finance-interface-types-date-rollconvention-m-75108_>`_

    Month

  .. _constr-daml-finance-interface-types-date-rollconvention-w-62138:

  `W <constr-daml-finance-interface-types-date-rollconvention-w-62138_>`_

    Week

  .. _constr-daml-finance-interface-types-date-rollconvention-y-88208:

  `Y <constr-daml-finance-interface-types-date-rollconvention-y-88208_>`_

    Year

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `PeriodEnum <type-daml-finance-interface-types-date-rollconvention-periodenum-51659_>`_

.. _type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360:

**data** `RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360_>`_

  An enum type to specify how to roll dates\.

  .. _constr-daml-finance-interface-types-date-rollconvention-eom-27598:

  `EOM <constr-daml-finance-interface-types-date-rollconvention-eom-27598_>`_

    Rolls on month end\.

  .. _constr-daml-finance-interface-types-date-rollconvention-dom-21751:

  `DOM <constr-daml-finance-interface-types-date-rollconvention-dom-21751_>`_ `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_

    Rolls on the corresponding day of the month\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `RollConventionEnum <type-daml-finance-interface-types-date-rollconvention-rollconventionenum-73360_>`_
