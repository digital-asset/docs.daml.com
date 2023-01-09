.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-data-numeric-observation-99152:

Module Daml.Finance.Interface.Data.Numeric.Observation
======================================================

Interfaces
----------

.. _type-daml-finance-interface-data-numeric-observation-observation-2365:

**interface** `Observation <type-daml-finance-interface-data-numeric-observation-observation-2365_>`_

  Interface for a time\-dependent numeric ``Observation``, where the values are explicitly stored on\-ledger\.

  + **Choice Archive**

    (no fields)

  + **Choice GetView**

    Retrieves the interface view\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party fetching the view\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method asNumericObservable \:** :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>`

    Conversion to ``NumericObservable`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-data-numeric-observation-hasimplementation-8758:

**class** `Implementation <type-daml-finance-interface-data-numeric-observation-implementation-58514_>`_ t \=\> `HasImplementation <class-daml-finance-interface-data-numeric-observation-hasimplementation-8758_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-data-numeric-observation-i-26176:

**type** `I <type-daml-finance-interface-data-numeric-observation-i-26176_>`_
  \= `Observation <type-daml-finance-interface-data-numeric-observation-observation-2365_>`_

  Type synonym for ``Observation``\.

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-data-numeric-observation-i-26176_>`_))

.. _type-daml-finance-interface-data-numeric-observation-implementation-58514:

**type** `Implementation <type-daml-finance-interface-data-numeric-observation-implementation-58514_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-data-numeric-observation-i-26176_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t, :ref:`Implementation <type-daml-finance-interface-lifecycle-observable-numericobservable-implementation-26558>` t)

  Type constraint for requiring templates to implement ``Observation`` along with ``Disclosure``
  as well as ``NumericObservable``\.

.. _type-daml-finance-interface-data-numeric-observation-v-32663:

**type** `V <type-daml-finance-interface-data-numeric-observation-v-32663_>`_
  \= `View <type-daml-finance-interface-data-numeric-observation-view-55341_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Observation <type-daml-finance-interface-data-numeric-observation-observation-2365_>`_ `V <type-daml-finance-interface-data-numeric-observation-v-32663_>`_

.. _type-daml-finance-interface-data-numeric-observation-view-55341:

**data** `View <type-daml-finance-interface-data-numeric-observation-view-55341_>`_

  View for ``Observation``\.

  .. _constr-daml-finance-interface-data-numeric-observation-view-52024:

  `View <constr-daml-finance-interface-data-numeric-observation-view-52024_>`_

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

Functions
---------

.. _function-daml-finance-interface-data-numeric-observation-asdisclosure-14305:

`asDisclosure <function-daml-finance-interface-data-numeric-observation-asdisclosure-14305_>`_
  \: `Observation <type-daml-finance-interface-data-numeric-observation-observation-2365_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-data-numeric-observation-asnumericobservable-17633:

`asNumericObservable <function-daml-finance-interface-data-numeric-observation-asnumericobservable-17633_>`_
  \: `Observation <type-daml-finance-interface-data-numeric-observation-observation-2365_>`_ \-\> :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>`
