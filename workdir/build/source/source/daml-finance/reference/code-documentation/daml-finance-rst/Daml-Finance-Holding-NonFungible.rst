.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-holding-nonfungible-86571:

Module Daml.Finance.Holding.NonFungible
=======================================

Templates
---------

.. _type-daml-finance-holding-nonfungible-factory-4448:

**template** `Factory <type-daml-finance-holding-nonfungible-factory-4448_>`_

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

  + **interface instance** :ref:`F <type-daml-finance-interface-holding-factory-f-28062>` **for** `Factory <type-daml-finance-holding-nonfungible-factory-4448_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-holding-nonfungible-factory-4448_>`_

.. _type-daml-finance-holding-nonfungible-nonfungible-53393:

**template** `NonFungible <type-daml-finance-holding-nonfungible-nonfungible-53393_>`_

  Implementation of a non\-fungible holding\.
  ``NonFungible`` implements the interface ``Transferable.I`` (which requires ``Base.I`` and
  ``Disclosure.I`` to be implemented)\.

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

  + **interface instance** :ref:`I <type-daml-finance-interface-holding-base-i-67605>` **for** `NonFungible <type-daml-finance-holding-nonfungible-nonfungible-53393_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-holding-transferable-i-13335>` **for** `NonFungible <type-daml-finance-holding-nonfungible-nonfungible-53393_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `NonFungible <type-daml-finance-holding-nonfungible-nonfungible-53393_>`_

Data Types
----------

.. _type-daml-finance-holding-nonfungible-f-56290:

**type** `F <type-daml-finance-holding-nonfungible-f-56290_>`_
  \= `Factory <type-daml-finance-holding-nonfungible-factory-4448_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-holding-nonfungible-t-34500:

**type** `T <type-daml-finance-holding-nonfungible-t-34500_>`_
  \= `NonFungible <type-daml-finance-holding-nonfungible-nonfungible-53393_>`_

  Type synonym for ``NonFungible``\.
