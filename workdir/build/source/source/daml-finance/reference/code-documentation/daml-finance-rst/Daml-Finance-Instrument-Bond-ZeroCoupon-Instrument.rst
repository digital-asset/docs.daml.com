.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-bond-zerocoupon-instrument-52804:

Module Daml.Finance.Instrument.Bond.ZeroCoupon.Instrument
=========================================================

Templates
---------

.. _type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619:

**template** `Instrument <type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619_>`_

  This template models a zero coupon bond\.
  It does not pay any coupons, only the redemption amount at maturity\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - depository
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The depository of the instrument\.
     * - issuer
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The issuer of the instrument\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - An identifier of the instrument\.
     * - version
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The instrument's version\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A description of the instrument\.
     * - issueDate
       - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
       - The date when the bond was issued\.
     * - maturityDate
       - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
       - The redemption date of the bond\.
     * - currency
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The currency of the bond\. For example, if the bond pays in USD this should be a USD cash instrument\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The observers of the instrument\.
     * - lastEventTimestamp
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` **for** `Instrument <type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-dynamic-instrument-i-39105>` **for** `Instrument <type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-i-81577>` **for** `Instrument <type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619_>`_

Data Types
----------

.. _type-daml-finance-instrument-bond-zerocoupon-instrument-t-99417:

**type** `T <type-daml-finance-instrument-bond-zerocoupon-instrument-t-99417_>`_
  \= `Instrument <type-daml-finance-instrument-bond-zerocoupon-instrument-instrument-53619_>`_

  Type synonym for ``Instrument``\.
