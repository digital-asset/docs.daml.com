.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-account-account-19369:

Module Daml.Finance.Account.Account
===================================

Templates
---------

.. _type-daml-finance-account-account-account-12745:

**template** `Account <type-daml-finance-account-account-account-12745_>`_

  A relationship between a custodian and an asset owner\. It is referenced by holdings\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - custodian
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The account provider\.
     * - owner
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The account owner\.
     * - controllers
       - :ref:`Controllers <type-daml-finance-interface-account-account-controllers-36430>`
       - Controllers of transfers\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Identifier of the account\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Description of the account\.
     * - holdingFactoryCid
       - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`F <type-daml-finance-interface-holding-factory-f-28062>`
       - Associated holding factory\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-account-account-i-54958>` **for** `Account <type-daml-finance-account-account-account-12745_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Account <type-daml-finance-account-account-account-12745_>`_

.. _type-daml-finance-account-account-factory-12070:

**template** `Factory <type-daml-finance-account-account-factory-12070_>`_

  Template used to create accounts\.

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

  + **interface instance** :ref:`F <type-daml-finance-interface-account-factory-f-92594>` **for** `Factory <type-daml-finance-account-account-factory-12070_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-account-account-factory-12070_>`_

Data Types
----------

.. _type-daml-finance-account-account-t-86062:

**type** `T <type-daml-finance-account-account-t-86062_>`_
  \= `Account <type-daml-finance-account-account-account-12745_>`_

  Type synonym for ``Account``\.
