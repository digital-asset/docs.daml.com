.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-rule-lifecycle-50431:

Module Daml.Finance.Interface.Lifecycle.Rule.Lifecycle
======================================================

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-rule-lifecycle-lifecycle-97652:

**interface** `Lifecycle <type-daml-finance-interface-lifecycle-rule-lifecycle-lifecycle-97652_>`_

  Interface implemented by instruments that can be lifecycled (either by the instrument itself
  or by a separate rule contract)\.

  + **Choice Archive**

    (no fields)

  + **Choice Evolve**

    Process an event\. It returns a tuple of the lifecycled instrument (or the original
    instrument when the former does not exist) and the effects\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - eventCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`
         - The event\.
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The target instrument\.
       * - observableCids
         - \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>`\]
         - Set of numerical time\-dependent observables\.

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

  + **Method evolve \:** Evolve \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\])

    Implementation of the ``Evolve`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-rule-lifecycle-hasimplementation-46967:

**class** `Implementation <type-daml-finance-interface-lifecycle-rule-lifecycle-implementation-48349_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-rule-lifecycle-hasimplementation-46967_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-rule-lifecycle-i-18685:

**type** `I <type-daml-finance-interface-lifecycle-rule-lifecycle-i-18685_>`_
  \= `Lifecycle <type-daml-finance-interface-lifecycle-rule-lifecycle-lifecycle-97652_>`_

  Type synonym for ``Lifecycle``\.

.. _type-daml-finance-interface-lifecycle-rule-lifecycle-implementation-48349:

**type** `Implementation <type-daml-finance-interface-lifecycle-rule-lifecycle-implementation-48349_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-lifecycle-rule-lifecycle-i-18685_>`_

  Type constraint for requiring templates to implement ``Lifecycle``\.

.. _type-daml-finance-interface-lifecycle-rule-lifecycle-v-21018:

**type** `V <type-daml-finance-interface-lifecycle-rule-lifecycle-v-21018_>`_
  \= `View <type-daml-finance-interface-lifecycle-rule-lifecycle-view-32854_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Lifecycle <type-daml-finance-interface-lifecycle-rule-lifecycle-lifecycle-97652_>`_ `V <type-daml-finance-interface-lifecycle-rule-lifecycle-v-21018_>`_

.. _type-daml-finance-interface-lifecycle-rule-lifecycle-view-32854:

**data** `View <type-daml-finance-interface-lifecycle-rule-lifecycle-view-32854_>`_

  View for ``Lifecycle``\.

  .. _constr-daml-finance-interface-lifecycle-rule-lifecycle-view-29823:

  `View <constr-daml-finance-interface-lifecycle-rule-lifecycle-view-29823_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Identifier for the rule contract\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Textual description\.
       * - lifecycler
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party performing the lifecycling\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-rule-lifecycle-view-32854_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-rule-lifecycle-view-32854_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-rule-lifecycle-evolve-99336:

`evolve <function-daml-finance-interface-lifecycle-rule-lifecycle-evolve-99336_>`_
  \: `Lifecycle <type-daml-finance-interface-lifecycle-rule-lifecycle-lifecycle-97652_>`_ \-\> Evolve \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\])
