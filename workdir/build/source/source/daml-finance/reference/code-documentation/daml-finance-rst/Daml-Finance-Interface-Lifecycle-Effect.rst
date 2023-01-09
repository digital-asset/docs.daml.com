.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-effect-16050:

Module Daml.Finance.Interface.Lifecycle.Effect
==============================================

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-effect-effect-69649:

**interface** `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_

  Interface for contracts exposing effects of lifecycling processes\.

  + **Choice Archive**

    (no fields)

  + **Choice Calculate**

    Given a holding, it calculates the instrument quantities to settle\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actor
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party calculating the quantities to settle\.
       * - holdingCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`
         - The holding being targeted\.

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

  + **Choice SetProviders**

    Set the provider of the effect\. The provider has visibility on all sub\-transactions
    triggered by ``Claim``\\ing an effect\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - newProviders
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The new provider\.

  + **Method calculate \:** Calculate \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `CalculationResult <type-daml-finance-interface-lifecycle-effect-calculationresult-55343_>`_

    Implementation of the ``Calculate`` choice\.

  + **Method setProviders \:** SetProviders \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_)

    Implementation of the ``SetProviders`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-effect-hasimplementation-26488:

**class** `Implementation <type-daml-finance-interface-lifecycle-effect-implementation-16520_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-effect-hasimplementation-26488_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-effect-calculationresult-55343:

**data** `CalculationResult <type-daml-finance-interface-lifecycle-effect-calculationresult-55343_>`_

  Data type encapsulating the effect's calculation result\.

  .. _constr-daml-finance-interface-lifecycle-effect-calculationresult-87932:

  `CalculationResult <constr-daml-finance-interface-lifecycle-effect-calculationresult-87932_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - consumed
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Consumed quantities\.
       * - produced
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Produced quantities\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `CalculationResult <type-daml-finance-interface-lifecycle-effect-calculationresult-55343_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CalculationResult <type-daml-finance-interface-lifecycle-effect-calculationresult-55343_>`_

  **instance** HasMethod `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_ \"calculate\" (Calculate \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `CalculationResult <type-daml-finance-interface-lifecycle-effect-calculationresult-55343_>`_)

.. _type-daml-finance-interface-lifecycle-effect-i-11106:

**type** `I <type-daml-finance-interface-lifecycle-effect-i-11106_>`_
  \= `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_

  Type synonym for ``Effect``\.

  **instance** HasMethod :ref:`Election <type-daml-finance-interface-instrument-generic-election-election-25324>` \"apply\" (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Election <type-daml-finance-interface-instrument-generic-election-election-25324>` \-\> Apply \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-lifecycle-effect-i-11106_>`_\]))

  **instance** HasMethod :ref:`Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711>` \"applyElection\" (ApplyElection \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-lifecycle-effect-i-11106_>`_\]))

  **instance** HasMethod :ref:`Lifecycle <type-daml-finance-interface-lifecycle-rule-lifecycle-lifecycle-97652>` \"evolve\" (Evolve \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-lifecycle-effect-i-11106_>`_\]))

.. _type-daml-finance-interface-lifecycle-effect-implementation-16520:

**type** `Implementation <type-daml-finance-interface-lifecycle-effect-implementation-16520_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-lifecycle-effect-i-11106_>`_

  Type constraint for requiring templates to implement ``Effect``\.

.. _type-daml-finance-interface-lifecycle-effect-v-39253:

**type** `V <type-daml-finance-interface-lifecycle-effect-v-39253_>`_
  \= `View <type-daml-finance-interface-lifecycle-effect-view-32411_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_ `V <type-daml-finance-interface-lifecycle-effect-v-39253_>`_

.. _type-daml-finance-interface-lifecycle-effect-view-32411:

**data** `View <type-daml-finance-interface-lifecycle-effect-view-32411_>`_

  View for ``Effect``\.

  .. _constr-daml-finance-interface-lifecycle-effect-view-17386:

  `View <constr-daml-finance-interface-lifecycle-effect-view-17386_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - providers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The parties providing the claim processing\.
       * - targetInstrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - A holding on this instrument is required to claim the effect\.
       * - producedInstrument
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The new version of the target instrument, when it exists\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - A textual identifier\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A human readable description of the Effect\.
       * - settlementTime
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - The effect's settlement time (if any)\.
       * - otherConsumed
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Consumed quantities (in addition to the target instrument)\.
       * - otherProduced
         - \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\]
         - Produced quantities (in addition to the produced instrument)\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-effect-view-32411_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-effect-view-32411_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-effect-setproviders-76442:

`setProviders <function-daml-finance-interface-lifecycle-effect-setproviders-76442_>`_
  \: `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_ \-\> SetProviders \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_)

.. _function-daml-finance-interface-lifecycle-effect-calculate-16959:

`calculate <function-daml-finance-interface-lifecycle-effect-calculate-16959_>`_
  \: `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_ \-\> Calculate \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Effect <type-daml-finance-interface-lifecycle-effect-effect-69649_>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `CalculationResult <type-daml-finance-interface-lifecycle-effect-calculationresult-55343_>`_
