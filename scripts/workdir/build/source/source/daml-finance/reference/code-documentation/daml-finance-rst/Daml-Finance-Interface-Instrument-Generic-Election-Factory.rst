.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-generic-election-factory-39535:

Module Daml.Finance.Interface.Instrument.Generic.Election.Factory
=================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-generic-election-factory-factory-64152:

**interface** `Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152_>`_

  Factory interface to instantiate elections on generic instruments\.

  + **Choice Archive**

    (no fields)

  + **Choice Create**

    Create a new Election\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties calling the ``Create`` choice\.
       * - elector
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Parties on behalf of which the election is made\.
       * - counterparty
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Faces the ``elector`` in the ``Holding``\.
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party that signs the election (together with the elector)\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - The identifier for an election\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A description of the instrument\.
       * - claim
         - :ref:`C <type-daml-finance-interface-claims-types-c-53263>`
         - The claim representation of the election (i\.e\., the elected sub\-tree)\.
       * - electorIsOwner
         - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
         - ``True`` if election is on behalf of the owner of the holding, ``False`` otherwise\.
       * - electionTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Time at which the election is put forward\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - Observers of the election\.
       * - amount
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - Number of instrument units to which the election applies\.
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument to which the election applies\.

  + **Choice Remove**

    Archive an account\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties executing the ``Remove`` choice\.
       * - electionCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-generic-election-i-85653>`
         - The election's contract id\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-generic-election-i-85653>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-generic-election-factory-hasimplementation-23421:

**class** `Implementation <type-daml-finance-interface-instrument-generic-election-factory-implementation-31725_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-generic-election-factory-hasimplementation-23421_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-generic-election-factory-f-41306:

**type** `F <type-daml-finance-interface-instrument-generic-election-factory-f-41306_>`_
  \= `Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-instrument-generic-election-factory-implementation-31725:

**type** `Implementation <type-daml-finance-interface-instrument-generic-election-factory-implementation-31725_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-instrument-generic-election-factory-v-10826:

**type** `V <type-daml-finance-interface-instrument-generic-election-factory-v-10826_>`_
  \= `View <type-daml-finance-interface-instrument-generic-election-factory-view-21222_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152_>`_ `V <type-daml-finance-interface-instrument-generic-election-factory-v-10826_>`_

.. _type-daml-finance-interface-instrument-generic-election-factory-view-21222:

**data** `View <type-daml-finance-interface-instrument-generic-election-factory-view-21222_>`_

  .. _constr-daml-finance-interface-instrument-generic-election-factory-view-39673:

  `View <constr-daml-finance-interface-instrument-generic-election-factory-view-39673_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-generic-election-factory-view-21222_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-generic-election-factory-view-21222_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-generic-election-factory-asdisclosure-24986:

`asDisclosure <function-daml-finance-interface-instrument-generic-election-factory-asdisclosure-24986_>`_
  \: `Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-instrument-generic-election-factory-createtick-65757:

`create' <function-daml-finance-interface-instrument-generic-election-factory-createtick-65757_>`_
  \: `Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-generic-election-i-85653>`)

.. _function-daml-finance-interface-instrument-generic-election-factory-remove-62855:

`remove <function-daml-finance-interface-instrument-generic-election-factory-remove-62855_>`_
  \: `Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
