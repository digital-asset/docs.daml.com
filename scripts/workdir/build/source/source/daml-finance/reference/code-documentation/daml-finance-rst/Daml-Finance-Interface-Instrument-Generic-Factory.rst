.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-generic-factory-11761:

Module Daml.Finance.Interface.Instrument.Generic.Factory
========================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-generic-factory-factory-64962:

**interface** `Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962_>`_

  Factory interface to instantiate generic instruments using Contingent Claims\.

  + **Choice Archive**

    (no fields)

  + **Choice Create**

    Create a new generic instrument\.

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
         - A description of the instrument\.
       * - claims
         - :ref:`C <type-daml-finance-interface-claims-types-c-53263>`
         - The claim tree\.
       * - acquisitionTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - The claim's acquisition time\. This usually corresponds to the start date of the contract\.
       * - lastEventTimestamp
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - The instrument's observers\.

  + **Choice Remove**

    Archive a generic instrument\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument's key\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method create' \:** Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`)

    Implementation of ``Create`` choice\.

  + **Method remove \:** Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()

    Implementation of ``Remove`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-generic-factory-hasimplementation-59857:

**class** `Implementation <type-daml-finance-interface-instrument-generic-factory-implementation-90495_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-generic-factory-hasimplementation-59857_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-generic-factory-f-66772:

**type** `F <type-daml-finance-interface-instrument-generic-factory-f-66772_>`_
  \= `Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962_>`_

  Type synonym for ``Factory``\.

.. _type-daml-finance-interface-instrument-generic-factory-implementation-90495:

**type** `Implementation <type-daml-finance-interface-instrument-generic-factory-implementation-90495_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Factory`` along with ``Disclosure``\.

.. _type-daml-finance-interface-instrument-generic-factory-v-36292:

**type** `V <type-daml-finance-interface-instrument-generic-factory-v-36292_>`_
  \= `View <type-daml-finance-interface-instrument-generic-factory-view-99088_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962_>`_ `V <type-daml-finance-interface-instrument-generic-factory-v-36292_>`_

.. _type-daml-finance-interface-instrument-generic-factory-view-99088:

**data** `View <type-daml-finance-interface-instrument-generic-factory-view-99088_>`_

  .. _constr-daml-finance-interface-instrument-generic-factory-view-43709:

  `View <constr-daml-finance-interface-instrument-generic-factory-view-43709_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The provider of the ``Factory``\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-generic-factory-view-99088_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-generic-factory-view-99088_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-generic-factory-asdisclosure-73420:

`asDisclosure <function-daml-finance-interface-instrument-generic-factory-asdisclosure-73420_>`_
  \: `Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-instrument-generic-factory-createtick-4723:

`create' <function-daml-finance-interface-instrument-generic-factory-createtick-4723_>`_
  \: `Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962_>`_ \-\> Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`)

.. _function-daml-finance-interface-instrument-generic-factory-remove-33913:

`remove <function-daml-finance-interface-instrument-generic-factory-remove-33913_>`_
  \: `Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962_>`_ \-\> Remove \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ ()
