.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-base-instrument-57320:

Module Daml.Finance.Interface.Instrument.Base.Instrument
========================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-base-instrument-instrument-22935:

**interface** `Instrument <type-daml-finance-interface-instrument-base-instrument-instrument-22935_>`_

  Base interface for all instruments\. This interface does not define any lifecycling logic\.

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
         - The party retrieving the view\.

  + **Method asDisclosure \:** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

    Conversion to ``Disclosure`` interface\.

  + **Method getKey \:** :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`

    Get the unique key for the ``Instrument``\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-base-instrument-hasimplementation-37642:

**class** `Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-base-instrument-hasimplementation-37642_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-base-instrument-i-67236:

**type** `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_
  \= `Instrument <type-daml-finance-interface-instrument-base-instrument-instrument-22935_>`_

  Type synonym for ``Instrument``\.

  **instance** HasMethod :ref:`Claim <type-daml-finance-interface-claims-claim-claim-8835>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-fixedrate-factory-factory-49085>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-bond-fixedrate-instrument-instrument-55963>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-floatingrate-factory-factory-39036>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-bond-floatingrate-instrument-instrument-7806>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-bond-inflationlinked-instrument-instrument-4132>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-bond-zerocoupon-instrument-instrument-17192>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-equity-factory-factory-60517>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-equity-instrument-instrument-99859>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-generic-instrument-instrument-11652>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-asset-factory-factory-87851>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-swap-asset-instrument-instrument-70853>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-creditdefault-factory-factory-17381>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-swap-creditdefault-instrument-instrument-24051>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-currency-factory-factory-84231>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-swap-currency-instrument-instrument-50369>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-foreignexchange-factory-factory-25462>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-swap-foreignexchange-instrument-instrument-74416>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-fpml-factory-factory-21199>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-swap-fpml-instrument-instrument-3449>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-interestrate-factory-factory-25358>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-swap-interestrate-instrument-instrument-68848>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-token-factory-factory-52788>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_))

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-token-instrument-instrument-4350>` \"asBaseInstrument\" `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ GetCid (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_)

.. _type-daml-finance-interface-instrument-base-instrument-implementation-67110:

**type** `Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint for requiring templates to implement ``Instrument`` along with ``Disclosure``\.

.. _type-daml-finance-interface-instrument-base-instrument-k-58546:

**type** `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_
  \= :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`

  Type synonym for ``InstrumentKey``\.

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ GetCid (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_)

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ SetCid (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `R <type-daml-finance-interface-instrument-base-instrument-r-56343_>`_)

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ SetObservers (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `R <type-daml-finance-interface-instrument-base-instrument-r-56343_>`_)

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_

.. _type-daml-finance-interface-instrument-base-instrument-q-62956:

**type** `Q <type-daml-finance-interface-instrument-base-instrument-q-62956_>`_
  \= :ref:`Quantity <type-daml-finance-interface-types-common-types-quantity-60153>` :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>` `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  Instrument quantity\.

.. _type-daml-finance-interface-instrument-base-instrument-r-56343:

**type** `R <type-daml-finance-interface-instrument-base-instrument-r-56343_>`_
  \= Reference

  Type synonym for ``Reference``\. This type is currently used as a work\-around given the lack of
  interface keys\.

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ SetCid (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `R <type-daml-finance-interface-instrument-base-instrument-r-56343_>`_)

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ SetObservers (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `R <type-daml-finance-interface-instrument-base-instrument-r-56343_>`_)

.. _type-daml-finance-interface-instrument-base-instrument-v-38963:

**type** `V <type-daml-finance-interface-instrument-base-instrument-v-38963_>`_
  \= `View <type-daml-finance-interface-instrument-base-instrument-view-86425_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-base-instrument-instrument-22935_>`_ `V <type-daml-finance-interface-instrument-base-instrument-v-38963_>`_

.. _type-daml-finance-interface-instrument-base-instrument-view-86425:

**data** `View <type-daml-finance-interface-instrument-base-instrument-view-86425_>`_

  View for ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-base-instrument-view-82976:

  `View <constr-daml-finance-interface-instrument-base-instrument-view-82976_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - issuer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The instrument's issuer\.
       * - depository
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The instrument's depository\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - A versioned instrument identifier\.
       * - version
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A textual instrument version\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A human readable description of the instrument\.
       * - validAsOf
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Timestamp as of which the instrument is valid\. This usually coincides with the timestamp of the event that creates the instrument\. It usually does not coincide with ledger time\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-base-instrument-view-86425_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-base-instrument-view-86425_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-base-instrument-asdisclosure-6717:

`asDisclosure <function-daml-finance-interface-instrument-base-instrument-asdisclosure-6717_>`_
  \: `Instrument <type-daml-finance-interface-instrument-base-instrument-instrument-22935_>`_ \-\> :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`

.. _function-daml-finance-interface-instrument-base-instrument-getkey-81449:

`getKey <function-daml-finance-interface-instrument-base-instrument-getkey-81449_>`_
  \: `Instrument <type-daml-finance-interface-instrument-base-instrument-instrument-22935_>`_ \-\> :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`

.. _function-daml-finance-interface-instrument-base-instrument-exerciseinterfacebykey-27297:

`exerciseInterfaceByKey <function-daml-finance-interface-instrument-base-instrument-exerciseinterfacebykey-27297_>`_
  \: (`HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ i, `HasExercise <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercise-70422>`_ i d r) \=\> `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> d \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ r

  Exercise interface by key\.
  This method can be used to exercise a choice on an ``Instrument`` given its ``InstrumentKey``\.
  Requires as input the ``InstrumentKey``, the actor fetching the instrument and the choice
  arguments\. For example\:

.. _function-daml-finance-interface-instrument-base-instrument-tokey-12561:

`toKey <function-daml-finance-interface-instrument-base-instrument-tokey-12561_>`_
  \: `V <type-daml-finance-interface-instrument-base-instrument-v-38963_>`_ \-\> `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_

  Convert the instrument's View to its key\.

.. _function-daml-finance-interface-instrument-base-instrument-fetchinstrument-77672:

`fetchInstrument <function-daml-finance-interface-instrument-base-instrument-fetchinstrument-77672_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>` \=\> t \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `I <type-daml-finance-interface-instrument-base-instrument-i-67236_>`_

  Fetch instrument from holding\.

.. _function-daml-finance-interface-instrument-base-instrument-qty-82779:

`qty <function-daml-finance-interface-instrument-base-instrument-qty-82779_>`_
  \: `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> `K <type-daml-finance-interface-instrument-base-instrument-k-58546_>`_ \-\> `Q <type-daml-finance-interface-instrument-base-instrument-q-62956_>`_

  Wraps an amount and an instrument key into an instrument quantity\.

.. _function-daml-finance-interface-instrument-base-instrument-scale-11943:

`scale <function-daml-finance-interface-instrument-base-instrument-scale-11943_>`_
  \: `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> `Q <type-daml-finance-interface-instrument-base-instrument-q-62956_>`_ \-\> `Q <type-daml-finance-interface-instrument-base-instrument-q-62956_>`_

  Scale ``Quantity`` by the provided factor\.
