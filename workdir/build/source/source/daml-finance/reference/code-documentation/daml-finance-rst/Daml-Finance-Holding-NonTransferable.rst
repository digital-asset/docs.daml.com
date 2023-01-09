.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-holding-nontransferable-44402:

Module Daml.Finance.Holding.NonTransferable
===========================================

Templates
---------

.. _type-daml-finance-holding-nontransferable-factory-31443:

**template** `Factory <type-daml-finance-holding-nontransferable-factory-31443_>`_

  Implementation of the corresponding Holding Factory\.

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

  + **interface instance** :ref:`F <type-daml-finance-interface-holding-factory-f-28062>` **for** `Factory <type-daml-finance-holding-nontransferable-factory-31443_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-holding-nontransferable-factory-31443_>`_

.. _type-daml-finance-holding-nontransferable-nontransferable-68229:

**template** `NonTransferable <type-daml-finance-holding-nontransferable-nontransferable-68229_>`_

  Implementation of a non\-transferable holding\.
  ``NonTransferable`` implements the interface ``Base.I`` (which requires ``Disclosure.I`` to be
  implemented)\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - instrument
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The instrument of which units are held\.
     * - account
       - :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`
       - The account at which the holding is held\. Defines the holding's owner and custodian\.
     * - amount
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - Number of units\.
     * - lock
       - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Lock <type-daml-finance-interface-holding-base-lock-32912>`
       - An optional lock of a holding\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-holding-base-i-67605>` **for** `NonTransferable <type-daml-finance-holding-nontransferable-nontransferable-68229_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `NonTransferable <type-daml-finance-holding-nontransferable-nontransferable-68229_>`_

Data Types
----------

.. _type-daml-finance-holding-nontransferable-f-30033:

**type** `F <type-daml-finance-holding-nontransferable-f-30033_>`_
  \= `Factory <type-daml-finance-holding-nontransferable-factory-31443_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-holding-nontransferable-t-90863:

**type** `T <type-daml-finance-holding-nontransferable-t-90863_>`_
  \= `NonTransferable <type-daml-finance-holding-nontransferable-nontransferable-68229_>`_

  Type synonym for ``NonTransferable``\.
