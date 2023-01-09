.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-generic-election-94835:

Module Daml.Finance.Interface.Instrument.Generic.Election
=========================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-generic-election-election-25324:

**interface** `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_

  Interface implemented by templates that represents a claim\-based election\. This interface
  requires the ``Event`` interface implementation\.

  + **Choice Apply**

    Applies the election to the instrument, returning the new instrument as well as the
    corresponding effects\. The election is archived as part of this choice\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - observableCids
         - \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>`\]
         - Set of observables\.
       * - exercisableCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711_>`_
         - The contract that is used to apply an election to the instrument\.

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

  + **Method apply \:** `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_ \-\> Apply \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\])

    Implementation of the ``Apply`` choice\.

  + **Method asEvent \:** :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`

    Conversion to ``Event`` interface\.

.. _type-daml-finance-interface-instrument-generic-election-exercisable-33711:

**interface** `Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711_>`_

  Interface implemented by instruments that admit (claim\-based) elections\.

  + **Choice ApplyElection**

    Applies an election to the instrument\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - electionCid
         - `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_
         - The election\.
       * - observableCids
         - \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>`\]
         - Set of observables\.

  + **Choice Archive**

    (no fields)

  + **Choice Exercisable\_GetView**

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

  + **Method applyElection \:** ApplyElection \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\])

    Implementation of the ``ApplyElection`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-generic-election-hasimplementation-97189:

**class** `Implementation <type-daml-finance-interface-instrument-generic-election-implementation-58245_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-generic-election-hasimplementation-97189_>`_ t **where**


.. _class-daml-finance-interface-instrument-generic-election-exercisablehasimplementation-16317:

**class** `ExercisableImplementation <type-daml-finance-interface-instrument-generic-election-exercisableimplementation-45207_>`_ t \=\> `ExercisableHasImplementation <class-daml-finance-interface-instrument-generic-election-exercisablehasimplementation-16317_>`_ t **where**

  **instance** `ExercisableHasImplementation <class-daml-finance-interface-instrument-generic-election-exercisablehasimplementation-16317_>`_ `Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711_>`_

Data Types
----------

.. _type-daml-finance-interface-instrument-generic-election-exercisableimplementation-45207:

**type** `ExercisableImplementation <type-daml-finance-interface-instrument-generic-election-exercisableimplementation-45207_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711_>`_

  Type constraint for requiring templates to implement ``Exercisable``\.

.. _type-daml-finance-interface-instrument-generic-election-exercisableview-40272:

**data** `ExercisableView <type-daml-finance-interface-instrument-generic-election-exercisableview-40272_>`_

  View for ``Exercisable``\.

  .. _constr-daml-finance-interface-instrument-generic-election-exercisableview-59909:

  `ExercisableView <constr-daml-finance-interface-instrument-generic-election-exercisableview-59909_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lifecycler
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party processing the election\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `ExercisableView <type-daml-finance-interface-instrument-generic-election-exercisableview-40272_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `ExercisableView <type-daml-finance-interface-instrument-generic-election-exercisableview-40272_>`_

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711_>`_ `ExercisableView <type-daml-finance-interface-instrument-generic-election-exercisableview-40272_>`_

.. _type-daml-finance-interface-instrument-generic-election-i-85653:

**type** `I <type-daml-finance-interface-instrument-generic-election-i-85653_>`_
  \= `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_

  Type synonym for ``Election``\.

  **instance** HasMethod :ref:`Factory <type-daml-finance-interface-instrument-generic-election-factory-factory-64152>` \"create'\" (Create \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `I <type-daml-finance-interface-instrument-generic-election-i-85653_>`_))

.. _type-daml-finance-interface-instrument-generic-election-implementation-58245:

**type** `Implementation <type-daml-finance-interface-instrument-generic-election-implementation-58245_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-instrument-generic-election-i-85653_>`_, :ref:`Implementation <type-daml-finance-interface-lifecycle-event-implementation-22192>` t)

  Type constraint for requiring templates to implement ``Exercisable`` along with ``Event``\.

.. _type-daml-finance-interface-instrument-generic-election-v-57506:

**type** `V <type-daml-finance-interface-instrument-generic-election-v-57506_>`_
  \= `View <type-daml-finance-interface-instrument-generic-election-view-99038_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_ `V <type-daml-finance-interface-instrument-generic-election-v-57506_>`_

.. _type-daml-finance-interface-instrument-generic-election-view-99038:

**data** `View <type-daml-finance-interface-instrument-generic-election-view-99038_>`_

  View for ``Election``\.

  .. _constr-daml-finance-interface-instrument-generic-election-view-25157:

  `View <constr-daml-finance-interface-instrument-generic-election-view-25157_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - The identifier for an election\.
       * - description
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - A description of the instrument\.
       * - claim
         - :ref:`C <type-daml-finance-interface-claims-types-c-53263>`
         - The claim representation of the election (i\.e\., the elected sub\-tree)\.
       * - elector
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Parties on behalf of which the election is made\.
       * - counterparty
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Faces the ``elector`` in the ``Holding``\.
       * - electorIsOwner
         - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
         - ``True`` if election is on behalf of the owner of the holding, ``False`` otherwise\.
       * - observers
         - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
         - Observers of the election\.
       * - amount
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         - Number of instrument units to which the election applies\.
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party that is authorized to process the election and generate the new instrument version and effects\.
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument to which the election applies\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-generic-election-view-99038_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-generic-election-view-99038_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-generic-election-asevent-91514:

`asEvent <function-daml-finance-interface-instrument-generic-election-asevent-91514_>`_
  \: `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_ \-\> :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`

.. _function-daml-finance-interface-instrument-generic-election-apply-87612:

`apply <function-daml-finance-interface-instrument-generic-election-apply-87612_>`_
  \: `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_ \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_ \-\> Apply \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\])

.. _function-daml-finance-interface-instrument-generic-election-getelectiontime-13640:

`getElectionTime <function-daml-finance-interface-instrument-generic-election-getelectiontime-13640_>`_
  \: `Election <type-daml-finance-interface-instrument-generic-election-election-25324_>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_

  Retrieves the election's time\.

.. _function-daml-finance-interface-instrument-generic-election-applyelection-46753:

`applyElection <function-daml-finance-interface-instrument-generic-election-applyelection-46753_>`_
  \: `Exercisable <type-daml-finance-interface-instrument-generic-election-exercisable-33711_>`_ \-\> ApplyElection \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`, \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-effect-i-11106>`\])
