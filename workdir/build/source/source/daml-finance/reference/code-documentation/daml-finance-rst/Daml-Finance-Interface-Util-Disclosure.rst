.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-util-disclosure-87755:

Module Daml.Finance.Interface.Util.Disclosure
=============================================

Interfaces
----------

.. _type-daml-finance-interface-util-disclosure-disclosure-97052:

**interface** `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_

  An interface for managing the visibility of contracts for non\-authorizing parties\.

  + **Choice AddObservers**

    Add a single new observer context to the existing observers\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - disclosers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Party calling this choice\.
       * - observersToAdd
         - (`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`)
         - Observer context to add to a contract\.

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

  + **Choice RemoveObservers**

    Remove observers from a context\.
    None is returned if no update is needed\. Parties for a context can be removed if any
    of the disclosers are part of the observers to be removed or the disclosureControllers\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - disclosers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties calling this choice\.
       * - observersToRemove
         - (`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`)
         - Observer context to remove\.

  + **Choice SetObservers**

    Set the observers for a contract\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - disclosers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Party calling this choice\.
       * - newObservers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - Observers to set for this contract\. This overrides the existing observers\.

  + **Method addObservers \:** AddObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_)

    Implementation of the ``AddObservers`` choice\.

  + **Method removeObservers \:** `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_ \-\> RemoveObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_))

    Implementation of the ``RemoveObservers`` choice\.

  + **Method setObservers \:** SetObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_)

    Implementation of the ``SetObservers`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-util-disclosure-hasimplementation-29141:

**class** `Implementation <type-daml-finance-interface-util-disclosure-implementation-41553_>`_ t \=\> `HasImplementation <class-daml-finance-interface-util-disclosure-hasimplementation-29141_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-util-disclosure-i-26993:

**type** `I <type-daml-finance-interface-util-disclosure-i-26993_>`_
  \= `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_

  Type synonym for ``Disclosure``\.

  **instance** HasMethod :ref:`Account <type-daml-finance-interface-account-account-account-9624>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-account-factory-factory-52816>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-data-numeric-observation-factory-factory-27189>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Observation <type-daml-finance-interface-data-numeric-observation-observation-2365>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-data-reference-holidaycalendar-factory-factory-18729>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`HolidayCalendar <type-daml-finance-interface-data-reference-holidaycalendar-holidaycalendar-37549>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Base <type-daml-finance-interface-holding-base-base-14854>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-holding-factory-factory-80308>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-base-instrument-instrument-22935>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-fixedrate-factory-factory-49085>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-floatingrate-factory-factory-39036>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-inflationlinked-factory-factory-80170>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-bond-zerocoupon-factory-factory-11542>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-equity-factory-factory-60517>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-generic-factory-factory-64962>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-asset-factory-factory-87851>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-creditdefault-factory-factory-17381>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-currency-factory-factory-84231>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-foreignexchange-factory-factory-25462>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-fpml-factory-factory-21199>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-swap-interestrate-factory-factory-25358>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-token-factory-factory-52788>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  **instance** HasMethod :ref:`Instruction <type-daml-finance-interface-settlement-instruction-instruction-30569>` \"asDisclosure\" `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

.. _type-daml-finance-interface-util-disclosure-implementation-41553:

**type** `Implementation <type-daml-finance-interface-util-disclosure-implementation-41553_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-util-disclosure-i-26993_>`_

  Type constraint for requiring templates to implement ``Disclosure``\.

.. _type-daml-finance-interface-util-disclosure-v-33606:

**type** `V <type-daml-finance-interface-util-disclosure-v-33606_>`_
  \= `View <type-daml-finance-interface-util-disclosure-view-8818_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_ `V <type-daml-finance-interface-util-disclosure-v-33606_>`_

.. _type-daml-finance-interface-util-disclosure-view-8818:

**data** `View <type-daml-finance-interface-util-disclosure-view-8818_>`_

  View for ``Disclosure``\.

  .. _constr-daml-finance-interface-util-disclosure-view-81921:

  `View <constr-daml-finance-interface-util-disclosure-view-81921_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - disclosureControllers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Disjunction choice controllers\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - Observers with context\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-util-disclosure-view-8818_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-util-disclosure-view-8818_>`_

Functions
---------

.. _function-daml-finance-interface-util-disclosure-setobservers-55668:

`setObservers <function-daml-finance-interface-util-disclosure-setobservers-55668_>`_
  \: `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_ \-\> SetObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_)

.. _function-daml-finance-interface-util-disclosure-addobservers-99063:

`addObservers <function-daml-finance-interface-util-disclosure-addobservers-99063_>`_
  \: `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_ \-\> AddObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_)

.. _function-daml-finance-interface-util-disclosure-removeobservers-66171:

`removeObservers <function-daml-finance-interface-util-disclosure-removeobservers-66171_>`_
  \: `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_ \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_ \-\> RemoveObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Disclosure <type-daml-finance-interface-util-disclosure-disclosure-97052_>`_))

.. _function-daml-finance-interface-util-disclosure-flattenobservers-47974:

`flattenObservers <function-daml-finance-interface-util-disclosure-flattenobservers-47974_>`_
  \: :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>` \-\> :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`

  Flattens observers which use the ``PartiesMap`` into a ``Set Party`` for usage in template
  definitions\. For example\:

  .. code-block:: daml

    observer $ flattenObservers observers
