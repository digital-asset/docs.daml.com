.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-trigger-lowlevel-64058:

Daml.Trigger.LowLevel
=====================

Typeclasses
-----------

.. _class-daml-trigger-lowlevel-actiontrigger-4488:

**class** `HasTime <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-hastime-96546>`_ m \=\> `ActionTrigger <class-daml-trigger-lowlevel-actiontrigger-4488_>`_ m **where**

  Low\-level trigger actions\.

  .. _function-daml-trigger-lowlevel-lifttf-75467:

  `liftTF <function-daml-trigger-lowlevel-lifttf-75467_>`_
    \: TriggerF a \-\> m a

  **instance** `ActionTrigger <class-daml-trigger-lowlevel-actiontrigger-4488_>`_ (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s)

  **instance** `ActionTrigger <class-daml-trigger-lowlevel-actiontrigger-4488_>`_ `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_

Data Types
----------

.. _type-daml-trigger-lowlevel-activecontracts-6750:

**data** `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_

  .. _constr-daml-trigger-lowlevel-activecontracts-64149:

  `ActiveContracts <constr-daml-trigger-lowlevel-activecontracts-64149_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - activeContracts
         - \[`Created <type-daml-trigger-lowlevel-created-33521_>`_\]
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"acs\" `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"activeContracts\" `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_ \[`Created <type-daml-trigger-lowlevel-created-33521_>`_\]

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialState\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) (`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s)

.. _type-daml-trigger-lowlevel-anycontractid-26036:

**data** `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  This type represents the contract id of an unknown template\.
  You can use ``fromAnyContractId`` to check which template it corresponds to\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"activeContracts\" ACS (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `TemplateTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-templatetyperep-33792>`_ (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_ `AnyTemplate <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anytemplate-63703>`_))

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractId\" `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ ())

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractId\" `Archived <type-daml-trigger-lowlevel-archived-67782_>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractId\" `Command <type-daml-trigger-lowlevel-command-96878_>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractId\" `Created <type-daml-trigger-lowlevel-created-33521_>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"pendingContracts\" ACS (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"pendingContracts\" (TriggerAState s) (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"templateId\" `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_ `TemplateTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-templatetyperep-33792>`_

.. _type-daml-trigger-lowlevel-archived-67782:

**data** `Archived <type-daml-trigger-lowlevel-archived-67782_>`_

  The data in an ``Archived`` event\.

  .. _constr-daml-trigger-lowlevel-archived-34319:

  `Archived <constr-daml-trigger-lowlevel-archived-34319_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - eventId
         - `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_
         -
       * - contractId
         - `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Archived <type-daml-trigger-lowlevel-archived-67782_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Archived <type-daml-trigger-lowlevel-archived-67782_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractId\" `Archived <type-daml-trigger-lowlevel-archived-67782_>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"eventId\" `Archived <type-daml-trigger-lowlevel-archived-67782_>`_ `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_

.. _type-daml-trigger-lowlevel-batchtrigger-33124:

**data** `BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s

  Batching trigger is (approximately) a left\-fold over ``Message`` with
  an accumulator of type ``s``\.

  .. _constr-daml-trigger-lowlevel-batchtrigger-31933:

  `BatchTrigger <constr-daml-trigger-lowlevel-batchtrigger-31933_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - initialState
         - `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s
         -
       * - update
         - \[`Message <type-daml-trigger-lowlevel-message-7580_>`_\] \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ()
         -
       * - registeredTemplates
         - `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_
         -
       * - heartbeat
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"heartbeat\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialState\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) (`TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"registeredTemplates\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"update\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) (\[`Message <type-daml-trigger-lowlevel-message-7580_>`_\] \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ())

.. _type-daml-trigger-lowlevel-command-96878:

**data** `Command <type-daml-trigger-lowlevel-command-96878_>`_

  A ledger API command\. To construct a command use ``createCmd`` and ``exerciseCmd``\.

  .. _constr-daml-trigger-lowlevel-createcommand-47079:

  `CreateCommand <constr-daml-trigger-lowlevel-createcommand-47079_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - templateArg
         - `AnyTemplate <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anytemplate-63703>`_
         -

  .. _constr-daml-trigger-lowlevel-exercisecommand-74023:

  `ExerciseCommand <constr-daml-trigger-lowlevel-exercisecommand-74023_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - contractId
         - `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_
         -
       * - choiceArg
         - `AnyChoice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anychoice-86490>`_
         -

  .. _constr-daml-trigger-lowlevel-createandexercisecommand-92581:

  `CreateAndExerciseCommand <constr-daml-trigger-lowlevel-createandexercisecommand-92581_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - templateArg
         - `AnyTemplate <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anytemplate-63703>`_
         -
       * - choiceArg
         - `AnyChoice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anychoice-86490>`_
         -

  .. _constr-daml-trigger-lowlevel-exercisebykeycommand-48604:

  `ExerciseByKeyCommand <constr-daml-trigger-lowlevel-exercisebykeycommand-48604_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - tplTypeRep
         - `TemplateTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-templatetyperep-33792>`_
         -
       * - contractKey
         - `AnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anycontractkey-68193>`_
         -
       * - choiceArg
         - `AnyChoice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anychoice-86490>`_
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"choiceArg\" `Command <type-daml-trigger-lowlevel-command-96878_>`_ `AnyChoice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anychoice-86490>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commands\" `Commands <type-daml-trigger-lowlevel-commands-84262_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\]

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandsInFlight\" (TriggerAState s) (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandsInFlight\" (TriggerState s) (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandsInFlight\" TriggerUpdateState (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractId\" `Command <type-daml-trigger-lowlevel-command-96878_>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractKey\" `Command <type-daml-trigger-lowlevel-command-96878_>`_ `AnyContractKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anycontractkey-68193>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"templateArg\" `Command <type-daml-trigger-lowlevel-command-96878_>`_ `AnyTemplate <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anytemplate-63703>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"tplTypeRep\" `Command <type-daml-trigger-lowlevel-command-96878_>`_ `TemplateTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-templatetyperep-33792>`_

.. _type-daml-trigger-lowlevel-commandid-51507:

**data** `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  .. _constr-daml-trigger-lowlevel-commandid-24540:

  `CommandId <constr-daml-trigger-lowlevel-commandid-24540_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_


  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandId\" `Commands <type-daml-trigger-lowlevel-commands-84262_>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandId\" `Completion <type-daml-trigger-lowlevel-completion-8224_>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandId\" `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandsInFlight\" (TriggerAState s) (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandsInFlight\" (TriggerState s) (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandsInFlight\" TriggerUpdateState (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"pendingContracts\" ACS (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_\])

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"pendingContracts\" (TriggerAState s) (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_ \[`AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_\])

.. _type-daml-trigger-lowlevel-commands-84262:

**data** `Commands <type-daml-trigger-lowlevel-commands-84262_>`_

  A set of commands that are submitted as a single transaction\.

  .. _constr-daml-trigger-lowlevel-commands-60307:

  `Commands <constr-daml-trigger-lowlevel-commands-60307_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - commandId
         - `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_
         -
       * - commands
         - \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\]
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandId\" `Commands <type-daml-trigger-lowlevel-commands-84262_>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commands\" `Commands <type-daml-trigger-lowlevel-commands-84262_>`_ \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\]

.. _type-daml-trigger-lowlevel-completion-8224:

**data** `Completion <type-daml-trigger-lowlevel-completion-8224_>`_

  A completion message\.
  Note that you will only get completions for commands emitted from the trigger\.
  Contrary to the ledger API completion stream, this also includes
  synchronous failures\.

  .. _constr-daml-trigger-lowlevel-completion-76245:

  `Completion <constr-daml-trigger-lowlevel-completion-76245_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - commandId
         - `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_
         -
       * - status
         - `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_
         -

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Completion <type-daml-trigger-lowlevel-completion-8224_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandId\" `Completion <type-daml-trigger-lowlevel-completion-8224_>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"status\" `Completion <type-daml-trigger-lowlevel-completion-8224_>`_ `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_

.. _type-daml-trigger-lowlevel-completionstatus-55948:

**data** `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_

  .. _constr-daml-trigger-lowlevel-failed-41528:

  `Failed <constr-daml-trigger-lowlevel-failed-41528_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - status
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         -
       * - message
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  .. _constr-daml-trigger-lowlevel-succeeded-44003:

  `Succeeded <constr-daml-trigger-lowlevel-succeeded-44003_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - transactionId
         - `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_
         -

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"message\" `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"status\" `Completion <type-daml-trigger-lowlevel-completion-8224_>`_ `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"status\" `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_ `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"transactionId\" `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_ `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_

.. _type-daml-trigger-lowlevel-created-33521:

**data** `Created <type-daml-trigger-lowlevel-created-33521_>`_

  The data in a ``Created`` event\.

  .. _constr-daml-trigger-lowlevel-created-24390:

  `Created <constr-daml-trigger-lowlevel-created-24390_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - eventId
         - `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_
         -
       * - contractId
         - `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_
         -
       * - argument
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `AnyTemplate <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anytemplate-63703>`_
         -
       * - views
         - \[InterfaceView\]
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"activeContracts\" `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_ \[`Created <type-daml-trigger-lowlevel-created-33521_>`_\]

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"argument\" `Created <type-daml-trigger-lowlevel-created-33521_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `AnyTemplate <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-any-anytemplate-63703>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"contractId\" `Created <type-daml-trigger-lowlevel-created-33521_>`_ `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"eventId\" `Created <type-daml-trigger-lowlevel-created-33521_>`_ `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"views\" `Created <type-daml-trigger-lowlevel-created-33521_>`_ \[InterfaceView\]

.. _type-daml-trigger-lowlevel-event-20139:

**data** `Event <type-daml-trigger-lowlevel-event-20139_>`_

  An event in a transaction\.
  This definition should be kept consistent with the object ``EventVariant`` defined in
  triggers/runner/src/main/scala/com/digitalasset/daml/lf/engine/trigger/Converter\.scala

  .. _constr-daml-trigger-lowlevel-createdevent-33321:

  `CreatedEvent <constr-daml-trigger-lowlevel-createdevent-33321_>`_ `Created <type-daml-trigger-lowlevel-created-33521_>`_


  .. _constr-daml-trigger-lowlevel-archivedevent-50254:

  `ArchivedEvent <constr-daml-trigger-lowlevel-archivedevent-50254_>`_ `Archived <type-daml-trigger-lowlevel-archived-67782_>`_


  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"events\" `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_ \[`Event <type-daml-trigger-lowlevel-event-20139_>`_\]

.. _type-daml-trigger-lowlevel-eventid-75698:

**data** `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_

  .. _constr-daml-trigger-lowlevel-eventid-55625:

  `EventId <constr-daml-trigger-lowlevel-eventid-55625_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_


  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"eventId\" `Archived <type-daml-trigger-lowlevel-archived-67782_>`_ `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"eventId\" `Created <type-daml-trigger-lowlevel-created-33521_>`_ `EventId <type-daml-trigger-lowlevel-eventid-75698_>`_

.. _type-daml-trigger-lowlevel-message-7580:

**data** `Message <type-daml-trigger-lowlevel-message-7580_>`_

  Either a transaction or a completion\.
  This definition should be kept consistent with the object ``MessageVariant`` defined in
  triggers/runner/src/main/scala/com/digitalasset/daml/lf/engine/trigger/Converter\.scala

  .. _constr-daml-trigger-lowlevel-mtransaction-71358:

  `MTransaction <constr-daml-trigger-lowlevel-mtransaction-71358_>`_ `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_


  .. _constr-daml-trigger-lowlevel-mcompletion-42369:

  `MCompletion <constr-daml-trigger-lowlevel-mcompletion-42369_>`_ `Completion <type-daml-trigger-lowlevel-completion-8224_>`_


  .. _constr-daml-trigger-lowlevel-mheartbeat-78836:

  `MHeartbeat <constr-daml-trigger-lowlevel-mheartbeat-78836_>`_


  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"update\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) (\[`Message <type-daml-trigger-lowlevel-message-7580_>`_\] \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ())

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"update\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) (`Message <type-daml-trigger-lowlevel-message-7580_>`_ \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ())

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"updateState\" (:ref:`Trigger <type-daml-trigger-trigger-91122>` s) (`Message <type-daml-trigger-lowlevel-message-7580_>`_ \-\> :ref:`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551>` s ())

.. _type-daml-trigger-lowlevel-registeredtemplates-41468:

**data** `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_

  .. _constr-daml-trigger-lowlevel-alltemplates-1479:

  `AllTemplates <constr-daml-trigger-lowlevel-alltemplates-1479_>`_

    Listen to events for all templates known by the triggers' runner\.

  .. _constr-daml-trigger-lowlevel-registeredtemplates-54723:

  `RegisteredTemplates <constr-daml-trigger-lowlevel-registeredtemplates-54723_>`_ \[RegisteredTemplate\]


  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"registeredTemplates\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"registeredTemplates\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"registeredTemplates\" (:ref:`Trigger <type-daml-trigger-trigger-91122>` s) `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_

.. _type-daml-trigger-lowlevel-transaction-35381:

**data** `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_

  .. _constr-daml-trigger-lowlevel-transaction-96842:

  `Transaction <constr-daml-trigger-lowlevel-transaction-96842_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - transactionId
         - `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_
         -
       * - commandId
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_
         -
       * - events
         - \[`Event <type-daml-trigger-lowlevel-event-20139_>`_\]
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commandId\" `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"events\" `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_ \[`Event <type-daml-trigger-lowlevel-event-20139_>`_\]

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"transactionId\" `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_ `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_

.. _type-daml-trigger-lowlevel-transactionid-96020:

**data** `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_

  .. _constr-daml-trigger-lowlevel-transactionid-86775:

  `TransactionId <constr-daml-trigger-lowlevel-transactionid-86775_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_


  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"transactionId\" `CompletionStatus <type-daml-trigger-lowlevel-completionstatus-55948_>`_ `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"transactionId\" `Transaction <type-daml-trigger-lowlevel-transaction-35381_>`_ `TransactionId <type-daml-trigger-lowlevel-transactionid-96020_>`_

.. _type-daml-trigger-lowlevel-trigger-87117:

**data** `Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s

  .. _constr-daml-trigger-lowlevel-trigger-67054:

  `Trigger <constr-daml-trigger-lowlevel-trigger-67054_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - initialState
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s
         -
       * - update
         - `Message <type-daml-trigger-lowlevel-message-7580_>`_ \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ()
         -
       * - registeredTemplates
         - `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_
         -
       * - heartbeat
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"heartbeat\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialState\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) (`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"registeredTemplates\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) `RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"update\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) (`Message <type-daml-trigger-lowlevel-message-7580_>`_ \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ())

.. _type-daml-trigger-lowlevel-triggerconfig-22465:

**data** `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_

  .. _constr-daml-trigger-lowlevel-triggerconfig-69158:

  `TriggerConfig <constr-daml-trigger-lowlevel-triggerconfig-69158_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - maxInFlightCommands
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         - maximum number of commands that should be allowed to be in\-flight at any point in time\. Exceeding this value will eventually lead to the trigger run raising an InFlightCommandOverflowException exception\.
       * - maxActiveContracts
         - `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_
         - maximum number of active contracts that we will allow to be stored Exceeding this value will lead to the trigger runner raising an ACSOverflowException exception\.

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"config\" (TriggerAState s) `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"config\" (TriggerState s) `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"config\" `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"maxActiveContracts\" `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_ `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"maxInFlightCommands\" `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_ `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_

.. _type-daml-trigger-lowlevel-triggerrule-55319:

**data** `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s a

  .. _constr-daml-trigger-lowlevel-triggerrule-70640:

  `TriggerRule <constr-daml-trigger-lowlevel-triggerrule-70640_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - runTriggerRule
         - StateT s (Free TriggerF) a
         -

  **instance** `ActionTrigger <class-daml-trigger-lowlevel-actiontrigger-4488_>`_ (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s)

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s)

  **instance** `ActionState <https://docs.daml.com/daml/stdlib/DA-Action-State-Class.html#class-da-action-state-class-actionstate-80467>`_ s (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s)

  **instance** `HasTime <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-hastime-96546>`_ (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s)

  **instance** `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s)

  **instance** `Applicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-applicative-9257>`_ (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"runTriggerA\" (:ref:`TriggerA <type-daml-trigger-internal-triggera-21640>` s a) (ACS \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ (TriggerAState s) a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"runTriggerRule\" (`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s a) (StateT s (Free TriggerF) a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"update\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) (\[`Message <type-daml-trigger-lowlevel-message-7580_>`_\] \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ())

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"update\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) (`Message <type-daml-trigger-lowlevel-message-7580_>`_ \-\> `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s ())

.. _type-daml-trigger-lowlevel-triggersetup-21291:

**data** `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ a

  .. _constr-daml-trigger-lowlevel-triggersetup-32438:

  `TriggerSetup <constr-daml-trigger-lowlevel-triggersetup-32438_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - runTriggerSetup
         - Free TriggerF a
         -

  **instance** `ActionTrigger <class-daml-trigger-lowlevel-actiontrigger-4488_>`_ `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_

  **instance** `HasTime <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-hastime-96546>`_ `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_

  **instance** `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_

  **instance** `Applicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-applicative-9257>`_ `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialState\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) (`TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialState\" (`Trigger <type-daml-trigger-lowlevel-trigger-87117_>`_ s) (`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"runTriggerSetup\" (`TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ a) (Free TriggerF a)

.. _type-daml-trigger-lowlevel-triggersetuparguments-43774:

**data** `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_

  .. _constr-daml-trigger-lowlevel-triggersetuparguments-31601:

  `TriggerSetupArguments <constr-daml-trigger-lowlevel-triggersetuparguments-31601_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actAs
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         -
       * - readAs
         - \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\]
         -
       * - acs
         - `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_
         -
       * - config
         - `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"acs\" `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ `ActiveContracts <type-daml-trigger-lowlevel-activecontracts-6750_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"actAs\" `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"config\" `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ `TriggerConfig <type-daml-trigger-lowlevel-triggerconfig-22465_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialState\" (`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124_>`_ s) (`TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ \-\> `TriggerSetup <type-daml-trigger-lowlevel-triggersetup-21291_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"readAs\" `TriggerSetupArguments <type-daml-trigger-lowlevel-triggersetuparguments-43774_>`_ \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\]

Functions
---------

.. _function-daml-trigger-lowlevel-toanycontractid-76263:

`toAnyContractId <function-daml-trigger-lowlevel-toanycontractid-76263_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t \-\> `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_

  Wrap a ``ContractId t`` in ``AnyContractId``\.

.. _function-daml-trigger-lowlevel-fromanycontractid-26940:

`fromAnyContractId <function-daml-trigger-lowlevel-fromanycontractid-26940_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> `AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036_>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t)

  Check if a ``AnyContractId`` corresponds to the given template or return
  ``None`` otherwise\.

.. _function-daml-trigger-lowlevel-fromcreated-89793:

`fromCreated <function-daml-trigger-lowlevel-fromcreated-89793_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> `Created <type-daml-trigger-lowlevel-created-33521_>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`EventId <type-daml-trigger-lowlevel-eventid-75698_>`_, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t, t)

  Check if a ``Created`` event corresponds to the given template\.

.. _function-daml-trigger-lowlevel-fromarchived-75110:

`fromArchived <function-daml-trigger-lowlevel-fromarchived-75110_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> `Archived <type-daml-trigger-lowlevel-archived-67782_>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`EventId <type-daml-trigger-lowlevel-eventid-75698_>`_, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t)

  Check if an ``Archived`` event corresponds to the given template\.

.. _function-daml-trigger-lowlevel-registeredtemplate-19464:

`registeredTemplate <function-daml-trigger-lowlevel-registeredtemplate-19464_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> RegisteredTemplate

.. _function-daml-trigger-lowlevel-createcmd-30183:

`createCmd <function-daml-trigger-lowlevel-createcmd-30183_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `HasAgreement <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasagreement-49535>`_ t) \=\> t \-\> `Command <type-daml-trigger-lowlevel-command-96878_>`_

  Create a contract of the given template\.

.. _function-daml-trigger-lowlevel-exercisecmd-11267:

`exerciseCmd <function-daml-trigger-lowlevel-exercisecmd-11267_>`_
  \: `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r \=\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t \-\> c \-\> `Command <type-daml-trigger-lowlevel-command-96878_>`_

  Exercise the given choice\.

.. _function-daml-trigger-lowlevel-createandexercisecmd-68943:

`createAndExerciseCmd <function-daml-trigger-lowlevel-createandexercisecmd-68943_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r) \=\> t \-\> c \-\> `Command <type-daml-trigger-lowlevel-command-96878_>`_

  Create a contract of the given template and immediately exercise
  the given choice on it\.

.. _function-daml-trigger-lowlevel-exercisebykeycmd-9886:

`exerciseByKeyCmd <function-daml-trigger-lowlevel-exercisebykeycmd-9886_>`_
  \: (`Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r, `TemplateKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-templatekey-95200>`_ t k) \=\> k \-\> c \-\> `Command <type-daml-trigger-lowlevel-command-96878_>`_

.. _function-daml-trigger-lowlevel-fromcreate-82874:

`fromCreate <function-daml-trigger-lowlevel-fromcreate-82874_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> `Command <type-daml-trigger-lowlevel-command-96878_>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ t

  Check if the command corresponds to a create command
  for the given template\.

.. _function-daml-trigger-lowlevel-fromcreateandexercise-72826:

`fromCreateAndExercise <function-daml-trigger-lowlevel-fromcreateandexercise-72826_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r) \=\> `Command <type-daml-trigger-lowlevel-command-96878_>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (t, c)

  Check if the command corresponds to a create and exercise command
  for the given template\.

.. _function-daml-trigger-lowlevel-fromexercise-93498:

`fromExercise <function-daml-trigger-lowlevel-fromexercise-93498_>`_
  \: `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r \=\> `Command <type-daml-trigger-lowlevel-command-96878_>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t, c)

  Check if the command corresponds to an exercise command
  for the given template\.

.. _function-daml-trigger-lowlevel-fromexercisebykey-26585:

`fromExerciseByKey <function-daml-trigger-lowlevel-fromexercisebykey-26585_>`_
  \: (`Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r, `TemplateKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-templatekey-95200>`_ t k) \=\> `Command <type-daml-trigger-lowlevel-command-96878_>`_ \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (k, c)

  Check if the command corresponds to an exercise by key command
  for the given template\.

.. _function-daml-trigger-lowlevel-execstatet-77408:

`execStateT <function-daml-trigger-lowlevel-execstatet-77408_>`_
  \: `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ m \=\> StateT s m a \-\> s \-\> m s

.. _function-daml-trigger-lowlevel-zoom-69133:

`zoom <function-daml-trigger-lowlevel-zoom-69133_>`_
  \: `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ m \=\> (t \-\> s) \-\> (t \-\> s \-\> t) \-\> StateT s m a \-\> StateT t m a

.. _function-daml-trigger-lowlevel-simulaterule-22272:

`simulateRule <function-daml-trigger-lowlevel-simulaterule-22272_>`_
  \: `TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319_>`_ s a \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ \-\> s \-\> (s, \[`Commands <type-daml-trigger-lowlevel-commands-84262_>`_\], a)

  Run a rule without running it\. May lose information from the rule;
  meant for testing purposes only\.

.. _function-daml-trigger-lowlevel-submitcommands-74008:

`submitCommands <function-daml-trigger-lowlevel-submitcommands-74008_>`_
  \: `ActionTrigger <class-daml-trigger-lowlevel-actiontrigger-4488_>`_ m \=\> \[`Command <type-daml-trigger-lowlevel-command-96878_>`_\] \-\> m `CommandId <type-daml-trigger-lowlevel-commandid-51507_>`_

