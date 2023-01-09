.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-equity-instrument-13224:

Module Daml.Finance.Interface.Instrument.Equity.Instrument
==========================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-equity-instrument-instrument-99859:

**interface** `Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859_>`_

  An interface for a generic equity instrument\.

  + **Choice Archive**

    (no fields)

  + **Choice DeclareDividend**

    Declare a dividend distribution to shareholders\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Event identifier of the dividend distribution\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Description of the dividend event\.
       * - effectiveTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Time at which the dividend is distributed\.
       * - newInstrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - Instrument held after the dividend distribution (i\.e\. \"ex\-dividend\" stock)\.
       * - perUnitDistribution
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Distributed quantities per unit held\.

  + **Choice DeclareReplacement**

    Declare a replacement event, where units of the instrument are replaced by a basket of
    other instruments\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Distribution Id\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Description of the replacement event\.
       * - effectiveTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Time the replacement is to be executed\.
       * - perUnitReplacement
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Payout offered to shareholders per held share\.

  + **Choice DeclareStockSplit**

    Declare a stock split\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Event identifier of the stock split\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Description of the stock split event\.
       * - effectiveTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Time at which the stock split is effective\.
       * - newInstrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - Instrument to be held after the stock split is executed\.
       * - adjustmentFactor
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - Adjustment factor for the stock split\.

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
         - The party retrieving the view\.

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to base ``Instrument`` interface\.

  + **Method declareDividend \:** DeclareDividend \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`)

    Implementation fo the ``DeclareDividend`` choice\.

  + **Method declareReplacement \:** DeclareReplacement \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`)

    Implementation fo the ``DeclareReplacement`` choice\.

  + **Method declareStockSplit \:** DeclareStockSplit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`)

    Implementation fo the ``DeclareStockSplit`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-equity-instrument-hasimplementation-48374:

**class** `Implementation <type-daml-finance-interface-instrument-equity-instrument-implementation-8194_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-equity-instrument-hasimplementation-48374_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-equity-instrument-i-74160:

**type** `I <type-daml-finance-interface-instrument-equity-instrument-i-74160_>`_
  \= `Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-equity-instrument-implementation-8194:

**type** `Implementation <type-daml-finance-interface-instrument-equity-instrument-implementation-8194_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-instrument-equity-instrument-i-74160_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-equity-instrument-v-19687:

**type** `V <type-daml-finance-interface-instrument-equity-instrument-v-19687_>`_
  \= `View <type-daml-finance-interface-instrument-equity-instrument-view-54781_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859_>`_ `V <type-daml-finance-interface-instrument-equity-instrument-v-19687_>`_

.. _type-daml-finance-interface-instrument-equity-instrument-view-54781:

**data** `View <type-daml-finance-interface-instrument-equity-instrument-view-54781_>`_

  View for ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-equity-instrument-view-37680:

  `View <constr-daml-finance-interface-instrument-equity-instrument-view-37680_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument's key\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-equity-instrument-view-54781_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-equity-instrument-view-54781_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-equity-instrument-asbaseinstrument-75198:

`asBaseInstrument <function-daml-finance-interface-instrument-equity-instrument-asbaseinstrument-75198_>`_
  \: `Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

.. _function-daml-finance-interface-instrument-equity-instrument-declaredividend-19644:

`declareDividend <function-daml-finance-interface-instrument-equity-instrument-declaredividend-19644_>`_
  \: `Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859_>`_ \-\> DeclareDividend \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`)

.. _function-daml-finance-interface-instrument-equity-instrument-declarestocksplit-95101:

`declareStockSplit <function-daml-finance-interface-instrument-equity-instrument-declarestocksplit-95101_>`_
  \: `Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859_>`_ \-\> DeclareStockSplit \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`)

.. _function-daml-finance-interface-instrument-equity-instrument-declarereplacement-33010:

`declareReplacement <function-daml-finance-interface-instrument-equity-instrument-declarereplacement-33010_>`_
  \: `Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859_>`_ \-\> DeclareReplacement \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`)
