.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-data-numeric-observation-78761:

Module Daml.Finance.Data.Numeric.Observation
============================================

Templates
---------

.. _type-daml-finance-data-numeric-observation-factory-23070:

**template** `Factory <type-daml-finance-data-numeric-observation-factory-23070_>`_

  Implementation of the corresponding Observation Factory\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The factory's provider\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The factory's observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`F <type-daml-finance-interface-data-numeric-observation-factory-f-61851>` **for** `Factory <type-daml-finance-data-numeric-observation-factory-23070_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-data-numeric-observation-factory-23070_>`_

.. _type-daml-finance-data-numeric-observation-observation-8434:

**template** `Observation <type-daml-finance-data-numeric-observation-observation-8434_>`_

  An implementation of ``NumericObservable`` that explicitly stores time\-dependent numerical
  values\. For example, it can be used for equity or rate fixings\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The reference data provider\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - A textual identifier\.
     * - observations
       - `Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - The time\-dependent values\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-data-numeric-observation-i-26176>` **for** `Observation <type-daml-finance-data-numeric-observation-observation-8434_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>` **for** `Observation <type-daml-finance-data-numeric-observation-observation-8434_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Observation <type-daml-finance-data-numeric-observation-observation-8434_>`_

Data Types
----------

.. _type-daml-finance-data-numeric-observation-t-12710:

**type** `T <type-daml-finance-data-numeric-observation-t-12710_>`_
  \= `Observation <type-daml-finance-data-numeric-observation-observation-8434_>`_

  Type synonym for ``Observation``\.
