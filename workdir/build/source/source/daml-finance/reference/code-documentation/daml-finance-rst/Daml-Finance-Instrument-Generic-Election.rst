.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-generic-election-56972:

Module Daml.Finance.Instrument.Generic.Election
===============================================

Templates
---------

.. _type-daml-finance-instrument-generic-election-election-43107:

**template** `Election <type-daml-finance-instrument-generic-election-election-43107_>`_

  An election, such as the exercise of an option\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - elector
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Entity making the election\.
     * - counterparty
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Faces the ``elector`` in the ``Holding``\.
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The provider of the election is an entity that has the authority to process the election and create a new instrument version\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Election identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A human readable description of the election\.
     * - instrument
       - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
       - The instrument to which the election applies\.
     * - amount
       - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
       - Number of units of instrument to which the election applies\.
     * - claim
       - :ref:`C <type-daml-finance-interface-claims-types-c-53263>`
       - The elected sub\-tree\.
     * - electorIsOwner
       - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
       - ``True`` if the elector is the owner of a claim, ``False`` otherwise\.
     * - electionTime
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - Time at which the election is put forward\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - A set of observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-generic-election-i-85653>` **for** `Election <type-daml-finance-instrument-generic-election-election-43107_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>` **for** `Election <type-daml-finance-instrument-generic-election-election-43107_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Election <type-daml-finance-instrument-generic-election-election-43107_>`_

.. _type-daml-finance-instrument-generic-election-factory-39485:

**template** `Factory <type-daml-finance-instrument-generic-election-factory-39485_>`_

  Factory template to create an ``Election``\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The provider of the ``Factory``\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - A set of observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`F <type-daml-finance-interface-instrument-generic-election-factory-f-41306>` **for** `Factory <type-daml-finance-instrument-generic-election-factory-39485_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Factory <type-daml-finance-instrument-generic-election-factory-39485_>`_

Data Types
----------

.. _type-daml-finance-instrument-generic-election-t-9669:

**type** `T <type-daml-finance-instrument-generic-election-t-9669_>`_
  \= `Election <type-daml-finance-instrument-generic-election-election-43107_>`_

  Type synonym for ``Election``\.
