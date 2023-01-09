.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-zerocoupon-types-74248:

Module Daml.Finance.Interface.Instrument.Bond.ZeroCoupon.Types
==============================================================

Data Types
----------

.. _type-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-49144:

**data** `ZeroCoupon <type-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-49144_>`_

  Describes the attributes of a Zero Coupon bond\.

  .. _constr-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-57769:

  `ZeroCoupon <constr-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-57769_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument's key\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - The description of the bond\.
       * - issueDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - The date when the bond was issued\.
       * - maturityDate
         - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
         - The redemption date of the bond\.
       * - currency
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The currency of the bond\. For example, if the bond pays in USD this should be a USD cash instrument\.
       * - lastEventTimestamp
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `ZeroCoupon <type-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-49144_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `ZeroCoupon <type-daml-finance-interface-instrument-bond-zerocoupon-types-zerocoupon-49144_>`_
