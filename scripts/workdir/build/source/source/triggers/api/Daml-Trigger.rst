.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-trigger-87671:

Daml.Trigger
============

Typeclasses
-----------

.. _class-daml-trigger-actiontriggerany-90512:

**class** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ m **where**

  Features possible in ``initialize``, ``updateState``, and ``rule``\.

  .. _function-daml-trigger-querycontractid-40543:

  `queryContractId <function-daml-trigger-querycontractid-40543_>`_
    \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ a \=\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ a \-\> m (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ a)

    Find the contract with the given ``id`` in the ACS, if present\.

  .. _function-daml-trigger-getreadas-52092:

  `getReadAs <function-daml-trigger-getreadas-52092_>`_
    \: m \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\]

  .. _function-daml-trigger-getactas-74141:

  `getActAs <function-daml-trigger-getactas-74141_>`_
    \: m `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  **instance** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ `TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_

  **instance** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

.. _class-daml-trigger-actiontriggerupdate-23164:

**class** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ m \=\> `ActionTriggerUpdate <class-daml-trigger-actiontriggerupdate-23164_>`_ m **where**

  Features possible in ``updateState`` and ``rule``\.

  .. _function-daml-trigger-getcommandsinflight-10479:

  `getCommandsInFlight <function-daml-trigger-getcommandsinflight-10479_>`_
    \: m (`Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ :ref:`CommandId <type-daml-trigger-lowlevel-commandid-51507>` \[:ref:`Command <type-daml-trigger-lowlevel-command-96878>`\])

    Retrieve command submissions made by this trigger that have not yet
    completed\. If the trigger has restarted, it will not contain commands from
    before the restart; therefore, this should be treated as an optimization
    rather than an absolute authority on ledger state\.

  **instance** `ActionTriggerUpdate <class-daml-trigger-actiontriggerupdate-23164_>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `ActionTriggerUpdate <class-daml-trigger-actiontriggerupdate-23164_>`_ (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

Data Types
----------

.. _type-daml-trigger-trigger-91122:

**data** `Trigger <type-daml-trigger-trigger-91122_>`_ s

  This is the type of your trigger\. ``s`` is the user\-defined state type which
  you can often leave at ``()``\.

  .. _constr-daml-trigger-trigger-72183:

  `Trigger <constr-daml-trigger-trigger-72183_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - initialize
         - `TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_ s
         - Initialize the user\-defined state based on the ACS\.
       * - updateState
         - :ref:`Message <type-daml-trigger-lowlevel-message-7580>` \-\> `TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s ()
         - Update the user\-defined state based on a transaction or completion message\. It can manipulate the state with ``get``, ``put``, and ``modify``, or query the ACS with ``query``\.
       * - rule
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s ()
         - The rule defines the main logic of your trigger\. It can send commands to the ledger using ``emitCommands`` to change the ACS\. The rule depends on the following arguments\:  * The party your trigger is running as\. * The user\-defined state\.  and can retrieve other data with functions in ``TriggerA``\:  * The current state of the ACS\. * The current time (UTC in wallclock mode, Unix epoch in static mode) * The commands in flight\.
       * - registeredTemplates
         - :ref:`RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468>`
         - The templates the trigger will receive events for\.
       * - heartbeat
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_
         - Send a heartbeat message at the given interval\.

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"heartbeat\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialize\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) (`TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"registeredTemplates\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) :ref:`RegisteredTemplates <type-daml-trigger-lowlevel-registeredtemplates-41468>`

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"rule\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) (`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s ())

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"updateState\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) (:ref:`Message <type-daml-trigger-lowlevel-message-7580>` \-\> `TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s ())

.. _type-daml-trigger-internal-triggera-21640:

**data** `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s a

  TriggerA is the type used in the ``rule`` of a Daml trigger\.
  Its main feature is that you can call ``emitCommands`` to
  send commands to the ledger\.

  **instance** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `ActionTriggerUpdate <class-daml-trigger-actiontriggerupdate-23164_>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `ActionState <https://docs.daml.com/daml/stdlib/DA-Action-State-Class.html#class-da-action-state-class-actionstate-80467>`_ s (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `HasTime <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-hastime-96546>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `Applicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-applicative-9257>`_ (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"rule\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) (`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s ())

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"runTriggerA\" (`TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s a) (ACS \-\> :ref:`TriggerRule <type-daml-trigger-lowlevel-triggerrule-55319>` (TriggerAState s) a)

.. _type-daml-trigger-internal-triggerinitializea-81008:

**data** `TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_ a

  TriggerInitializeA is the type used in the ``initialize`` of a Daml
  trigger\. It can query, but not emit commands or update the state\.

  **instance** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ `TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ `TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_

  **instance** `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ `TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_

  **instance** `Applicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-applicative-9257>`_ `TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"initialize\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) (`TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"runTriggerInitializeA\" (`TriggerInitializeA <type-daml-trigger-internal-triggerinitializea-81008_>`_ a) (TriggerInitState \-\> a)

.. _type-daml-trigger-internal-triggerupdatea-82551:

**data** `TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s a

  TriggerUpdateA is the type used in the ``updateState`` of a Daml
  trigger\. It has similar actions in common with ``TriggerA``, but
  cannot use ``emitCommands`` or ``getTime``\.

  **instance** `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

  **instance** `ActionTriggerUpdate <class-daml-trigger-actiontriggerupdate-23164_>`_ (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

  **instance** `ActionState <https://docs.daml.com/daml/stdlib/DA-Action-State-Class.html#class-da-action-state-class-actionstate-80467>`_ s (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

  **instance** `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

  **instance** `Applicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-applicative-9257>`_ (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"runTriggerUpdateA\" (`TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s a) (TriggerUpdateState \-\> `State <https://docs.daml.com/daml/stdlib/DA-Action-State.html#type-da-action-state-type-state-76783>`_ s a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"updateState\" (`Trigger <type-daml-trigger-trigger-91122_>`_ s) (:ref:`Message <type-daml-trigger-lowlevel-message-7580>` \-\> `TriggerUpdateA <type-daml-trigger-internal-triggerupdatea-82551_>`_ s ())

Functions
---------

.. _function-daml-trigger-query-49540:

`query <function-daml-trigger-query-49540_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ a, `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ m) \=\> m \[(`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ a, a)\]

  Extract the contracts of a given template from the ACS\.

.. _function-daml-trigger-queryfilter-40304:

`queryFilter <function-daml-trigger-queryfilter-40304_>`_
  \: (`Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ m, `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ a, `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ m) \=\> (a \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_) \-\> m \[(`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ a, a)\]

  Extract the contracts of a given template from the ACS and filter
  to those that match the predicate\.

.. _function-daml-trigger-querycontractkey-43722:

`queryContractKey <function-daml-trigger-querycontractkey-43722_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ a, `HasKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-haskey-87616>`_ a k, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ k, `ActionTriggerAny <class-daml-trigger-actiontriggerany-90512_>`_ m, `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ m) \=\> k \-\> m (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ a, a))

  Find the contract with the given ``key`` in the ACS, if present\.

.. _function-daml-trigger-emitcommands-47366:

`emitCommands <function-daml-trigger-emitcommands-47366_>`_
  \: \[:ref:`Command <type-daml-trigger-lowlevel-command-96878>`\] \-\> \[:ref:`AnyContractId <type-daml-trigger-lowlevel-anycontractid-26036>`\] \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s :ref:`CommandId <type-daml-trigger-lowlevel-commandid-51507>`

  Send a transaction consisting of the given commands to the ledger\.
  The second argument can be used to mark a list of contract ids as pending\.
  These contracts will automatically be filtered from getContracts until we
  either get the corresponding transaction event for this command or
  a failing completion\.

.. _function-daml-trigger-dedupcreate-7622:

`dedupCreate <function-daml-trigger-dedupcreate-7622_>`_
  \: (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ t, `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t) \=\> t \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s ()

  Create the template if it’s not already in the list of commands
  in flight (it will still be created if it is in the ACS)\.

  Note that this will send the create as a single\-command transaction\.
  If you need to send multiple commands in one transaction, use
  ``emitCommands`` with ``createCmd`` and handle filtering yourself\.

.. _function-daml-trigger-dedupcreateandexercise-11898:

`dedupCreateAndExercise <function-daml-trigger-dedupcreateandexercise-11898_>`_
  \: (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ t, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ c, `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r) \=\> t \-\> c \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s ()

  Create the template and exercise a choice on it if it’s not already in the list of commands
  in flight (it will still be created if it is in the ACS)\.

  Note that this will send the create and exercise as a
  single\-command transaction\. If you need to send multiple commands
  in one transaction, use ``emitCommands`` with ``createAndExerciseCmd``
  and handle filtering yourself\.

.. _function-daml-trigger-dedupexercise-2238:

`dedupExercise <function-daml-trigger-dedupexercise-2238_>`_
  \: (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ c, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r) \=\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t \-\> c \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s ()

  Exercise the choice on the given contract if it is not already
  in flight\.

  Note that this will send the exercise as a single\-command transaction\.
  If you need to send multiple commands in one transaction, use
  ``emitCommands`` with ``exerciseCmd`` and handle filtering yourself\.

  If you are calling a consuming choice, you might be better off by using
  ``emitCommands`` and adding the contract id to the pending set\.

.. _function-daml-trigger-dedupexercisebykey-2449:

`dedupExerciseByKey <function-daml-trigger-dedupexercisebykey-2449_>`_
  \: (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ c, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ k, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r, `TemplateKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-templatekey-95200>`_ t k) \=\> k \-\> c \-\> `TriggerA <type-daml-trigger-internal-triggera-21640_>`_ s ()

  Exercise the choice on the given contract if it is not already
  in flight\.

  Note that this will send the exercise as a single\-command transaction\.
  If you need to send multiple commands in one transaction, use
  ``emitCommands`` with ``exerciseCmd`` and handle filtering yourself\.

.. _function-daml-trigger-runtrigger-90430:

`runTrigger <function-daml-trigger-runtrigger-90430_>`_
  \: `Trigger <type-daml-trigger-trigger-91122_>`_ s \-\> :ref:`BatchTrigger <type-daml-trigger-lowlevel-batchtrigger-33124>` (TriggerState s)

  Transform the high\-level trigger type into the batching trigger from ``Daml.Trigger.LowLevel``\.

