.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-types-common-types-55444:

Module Daml.Finance.Interface.Types.Common.Types
================================================

Data Types
----------

.. _type-daml-finance-interface-types-common-types-accountkey-41482:

**data** `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  A unique key for Accounts\.

  .. _constr-daml-finance-interface-types-common-types-accountkey-87663:

  `AccountKey <constr-daml-finance-interface-types-common-types-accountkey-87663_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - custodian
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party providing accounting services\.
       * - owner
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party providing accounting services\.
       * - id
         - `Id <type-daml-finance-interface-types-common-types-id-31223_>`_
         - Unique identifier for an account\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** HasMethod :ref:`Account <type-daml-finance-interface-account-account-account-9624>` \"getKey\" `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_ GetCid (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Account <type-daml-finance-interface-account-account-account-9624>`)

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_ SetCid (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ Reference)

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_ SetObservers (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ Reference)

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_ `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ Reference `AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482_>`_

.. _type-daml-finance-interface-types-common-types-id-31223:

**data** `Id <type-daml-finance-interface-types-common-types-id-31223_>`_

  .. _constr-daml-finance-interface-types-common-types-id-63842:

  `Id <constr-daml-finance-interface-types-common-types-id-63842_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_


  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Id <type-daml-finance-interface-types-common-types-id-31223_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `Id <type-daml-finance-interface-types-common-types-id-31223_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Id <type-daml-finance-interface-types-common-types-id-31223_>`_

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_) `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_) `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

.. _type-daml-finance-interface-types-common-types-instrumentkey-12301:

**data** `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_

  A unique key for Instruments\.

  .. _constr-daml-finance-interface-types-common-types-instrumentkey-32970:

  `InstrumentKey <constr-daml-finance-interface-types-common-types-instrumentkey-32970_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - depository
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party providing depository services\.
       * - issuer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Issuer of instrument\.
       * - id
         - `Id <type-daml-finance-interface-types-common-types-id-31223_>`_
         - A unique identifier for an instrument\.
       * - version
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A textual instrument version\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-base-instrument-instrument-22935>` \"getKey\" `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_

  **instance** HasMethod :ref:`Election <type-daml-finance-interface-instrument-generic-election-election-25324>` \"apply\" (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Election <type-daml-finance-interface-instrument-generic-election-election-25324>` \-\> Apply \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\]))

  **instance** HasMethod :ref:`Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711>` \"applyElection\" (ApplyElection \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\]))

  **instance** HasMethod :ref:`Lifecycle <type-daml-finance-interface-lifecycle-rule-lifecycle-lifecycle-97652>` \"evolve\" (Evolve \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\]))

.. _type-daml-finance-interface-types-common-types-instrumentquantity-3096:

**type** `InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096_>`_
  \= `Quantity <type-daml-finance-interface-types-common-types-quantity-60153_>`_ `InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301_>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

.. _type-daml-finance-interface-types-common-types-parties-94211:

**type** `Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_
  \= `Set <https://docs.daml.com/daml/stdlib/DA-Set.html#type-da-set-types-set-90436>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  A set of parties\.

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_) `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasExerciseByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasexercisebykey-36549>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_) `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ ()

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasFromAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfromanycontractkey-95587>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasLookupByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haslookupbykey-92299>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasMaintainer <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasmaintainer-28932>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ :ref:`DateClock <type-daml-finance-data-time-dateclock-dateclock-90915>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

  **instance** `HasToAnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hastoanycontractkey-35010>`_ :ref:`LedgerTime <type-daml-finance-data-time-ledgertime-ledgertime-44359>` (`Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_, `Id <type-daml-finance-interface-types-common-types-id-31223_>`_)

.. _type-daml-finance-interface-types-common-types-partiesmap-10862:

**type** `PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862_>`_
  \= `Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ `Parties <type-daml-finance-interface-types-common-types-parties-94211_>`_

  Parties mapped to a specific key (or context)\.
  The textual key is the \"context\" which describes the value set of parties\.
  Allows for processes to add/remove parties for their specific purpose\.

.. _type-daml-finance-interface-types-common-types-quantity-60153:

**data** `Quantity <type-daml-finance-interface-types-common-types-quantity-60153_>`_ u a

  A dimensioned quantity\.

  .. _constr-daml-finance-interface-types-common-types-quantity-11140:

  `Quantity <constr-daml-finance-interface-types-common-types-quantity-11140_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - unit
         - u
         - The quantity's unit\.
       * - amount
         - a
         - A numerical amount\.

  **instance** (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ u, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ a) \=\> `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ (`Quantity <type-daml-finance-interface-types-common-types-quantity-60153_>`_ u a)

  **instance** (`Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ u, `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ a) \=\> `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ (`Quantity <type-daml-finance-interface-types-common-types-quantity-60153_>`_ u a)

  **instance** (`Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ u, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ a) \=\> `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ (`Quantity <type-daml-finance-interface-types-common-types-quantity-60153_>`_ u a)
