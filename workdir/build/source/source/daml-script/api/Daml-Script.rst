.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-script-55737:

Daml.Script
===========

Data Types
----------

.. _type-daml-script-commands-64301:

**data** `Commands <type-daml-script-commands-64301_>`_ a

  This is used to build up the commands send as part of ``submit``\.
  If you enable the ``ApplicativeDo`` extension by adding
  ``{-# LANGUAGE ApplicativeDo #-}`` at the top of your file, you can
  use ``do``\-notation but the individual commands must not depend
  on each other and the last statement in a ``do`` block
  must be of the form ``return expr`` or ``pure expr``\.

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ `Commands <type-daml-script-commands-64301_>`_

  **instance** `HasSubmit <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-hassubmit-5275>`_ `Script <type-daml-script-script-90248_>`_ `Commands <type-daml-script-commands-64301_>`_

  **instance** `Applicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-applicative-9257>`_ `Commands <type-daml-script-commands-64301_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commands\" (SubmitCmd a) (`Commands <type-daml-script-commands-64301_>`_ a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commands\" (SubmitMustFailCmd a) (`Commands <type-daml-script-commands-64301_>`_ a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"commands\" (SubmitTreePayload a) (`Commands <type-daml-script-commands-64301_>`_ ())

.. _type-daml-script-invaliduserid-88757:

**data** `InvalidUserId <type-daml-script-invaliduserid-88757_>`_

  Thrown if text for a user identifier does not conform to the format restriction\.

  .. _constr-daml-script-invaliduserid-32470:

  `InvalidUserId <constr-daml-script-invaliduserid-32470_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - m
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `InvalidUserId <type-daml-script-invaliduserid-88757_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `InvalidUserId <type-daml-script-invaliduserid-88757_>`_

  **instance** `HasFromAnyException <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasfromanyexception-16788>`_ `InvalidUserId <type-daml-script-invaliduserid-88757_>`_

  **instance** `HasMessage <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasmessage-3179>`_ `InvalidUserId <type-daml-script-invaliduserid-88757_>`_

  **instance** `HasThrow <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasthrow-30284>`_ `InvalidUserId <type-daml-script-invaliduserid-88757_>`_

  **instance** `HasToAnyException <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hastoanyexception-55973>`_ `InvalidUserId <type-daml-script-invaliduserid-88757_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"m\" `InvalidUserId <type-daml-script-invaliduserid-88757_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

.. _type-daml-script-participantname-93946:

**data** `ParticipantName <type-daml-script-participantname-93946_>`_

  .. _constr-daml-script-participantname-49773:

  `ParticipantName <constr-daml-script-participantname-49773_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - participantName
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"participantName\" `ParticipantName <type-daml-script-participantname-93946_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

.. _type-daml-script-partydetails-77837:

**data** `PartyDetails <type-daml-script-partydetails-77837_>`_

  The party details returned by the party management service\.

  .. _constr-daml-script-partydetails-14100:

  `PartyDetails <constr-daml-script-partydetails-14100_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - party
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party id
       * - displayName
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - Optional display name
       * - isLocal
         - `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_
         - True if party is hosted by the backing participant\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `PartyDetails <type-daml-script-partydetails-77837_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `PartyDetails <type-daml-script-partydetails-77837_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `PartyDetails <type-daml-script-partydetails-77837_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"continue\" (ListKnownPartiesPayload a) (\[`PartyDetails <type-daml-script-partydetails-77837_>`_\] \-\> a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"displayName\" `PartyDetails <type-daml-script-partydetails-77837_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"isLocal\" `PartyDetails <type-daml-script-partydetails-77837_>`_ `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"party\" `PartyDetails <type-daml-script-partydetails-77837_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

.. _type-daml-script-partyidhint-32256:

**data** `PartyIdHint <type-daml-script-partyidhint-32256_>`_

  A hint to the backing participant what party id to allocate\.
  Must be a valid PartyIdString (as described in @value\.proto@)\.

  .. _constr-daml-script-partyidhint-58239:

  `PartyIdHint <constr-daml-script-partyidhint-58239_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - partyIdHint
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"partyIdHint\" `PartyIdHint <type-daml-script-partyidhint-32256_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

.. _type-daml-script-script-90248:

**data** `Script <type-daml-script-script-90248_>`_ a

  This is the type of A Daml script\. ``Script`` is an instance of ``Action``,
  so you can use ``do`` notation\.

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `CanAssert <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-assert-canassert-67323>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `ActionCatch <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-actioncatch-69238>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `ActionThrow <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-actionthrow-37623>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `CanAbort <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-canabort-29060>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `HasSubmit <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-hassubmit-5275>`_ `Script <type-daml-script-script-90248_>`_ `Commands <type-daml-script-commands-64301_>`_

  **instance** `HasTime <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-hastime-96546>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `ActionFail <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-actionfail-34438>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `Applicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-applicative-9257>`_ `Script <type-daml-script-script-90248_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"dummy\" (`Script <type-daml-script-script-90248_>`_ a) ()

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"runScript\" (`Script <type-daml-script-script-90248_>`_ a) (() \-\> Free ScriptF (a, ()))

.. _type-daml-script-user-57134:

**data** `User <type-daml-script-user-57134_>`_

  User\-info record for a user in the user management service\.

  .. _constr-daml-script-user-42087:

  `User <constr-daml-script-user-42087_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - userId
         - `UserId <type-daml-script-userid-41343_>`_
         -
       * - primaryParty
         - `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `User <type-daml-script-user-57134_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `User <type-daml-script-user-57134_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `User <type-daml-script-user-57134_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"continue\" (GetUserPayload a) (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `User <type-daml-script-user-57134_>`_ \-\> a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"continue\" (ListAllUsersPayload a) (\[`User <type-daml-script-user-57134_>`_\] \-\> a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"primaryParty\" `User <type-daml-script-user-57134_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"user\" (CreateUserPayload a) `User <type-daml-script-user-57134_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" `User <type-daml-script-user-57134_>`_ `UserId <type-daml-script-userid-41343_>`_

.. _type-daml-script-useralreadyexists-59049:

**data** `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_

  Thrown if a user to be created already exists\.

  .. _constr-daml-script-useralreadyexists-71694:

  `UserAlreadyExists <constr-daml-script-useralreadyexists-71694_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - userId
         - `UserId <type-daml-script-userid-41343_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_

  **instance** `HasFromAnyException <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasfromanyexception-16788>`_ `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_

  **instance** `HasMessage <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasmessage-3179>`_ `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_

  **instance** `HasThrow <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasthrow-30284>`_ `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_

  **instance** `HasToAnyException <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hastoanyexception-55973>`_ `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_ `UserId <type-daml-script-userid-41343_>`_

.. _type-daml-script-userid-41343:

**data** `UserId <type-daml-script-userid-41343_>`_

  Identifier for a user in the user management service\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `UserId <type-daml-script-userid-41343_>`_

  **instance** `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ `UserId <type-daml-script-userid-41343_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" (DeleteUserPayload a) `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" (GetUserPayload a) `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" (GrantUserRightsPayload a) `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" (ListUserRightsPayload a) `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" (RevokeUserRightsPayload a) `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" `User <type-daml-script-user-57134_>`_ `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" `UserAlreadyExists <type-daml-script-useralreadyexists-59049_>`_ `UserId <type-daml-script-userid-41343_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" `UserNotFound <type-daml-script-usernotfound-3347_>`_ `UserId <type-daml-script-userid-41343_>`_

.. _type-daml-script-usernotfound-3347:

**data** `UserNotFound <type-daml-script-usernotfound-3347_>`_

  Thrown if a user cannot be located for a given user identifier\.

  .. _constr-daml-script-usernotfound-32978:

  `UserNotFound <constr-daml-script-usernotfound-32978_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - userId
         - `UserId <type-daml-script-userid-41343_>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `UserNotFound <type-daml-script-usernotfound-3347_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `UserNotFound <type-daml-script-usernotfound-3347_>`_

  **instance** `HasFromAnyException <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasfromanyexception-16788>`_ `UserNotFound <type-daml-script-usernotfound-3347_>`_

  **instance** `HasMessage <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasmessage-3179>`_ `UserNotFound <type-daml-script-usernotfound-3347_>`_

  **instance** `HasThrow <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hasthrow-30284>`_ `UserNotFound <type-daml-script-usernotfound-3347_>`_

  **instance** `HasToAnyException <https://docs.daml.com/daml/stdlib/DA-Exception.html#class-da-internal-exception-hastoanyexception-55973>`_ `UserNotFound <type-daml-script-usernotfound-3347_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"userId\" `UserNotFound <type-daml-script-usernotfound-3347_>`_ `UserId <type-daml-script-userid-41343_>`_

.. _type-daml-script-userright-58823:

**data** `UserRight <type-daml-script-userright-58823_>`_

  The rights of a user\.

  .. _constr-daml-script-participantadmin-50974:

  `ParticipantAdmin <constr-daml-script-participantadmin-50974_>`_


  .. _constr-daml-script-canactas-34048:

  `CanActAs <constr-daml-script-canactas-34048_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_


  .. _constr-daml-script-canreadas-62715:

  `CanReadAs <constr-daml-script-canreadas-62715_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_


  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `UserRight <type-daml-script-userright-58823_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `UserRight <type-daml-script-userright-58823_>`_

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"continue\" (GrantUserRightsPayload a) (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"continue\" (ListUserRightsPayload a) (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"continue\" (RevokeUserRightsPayload a) (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> a)

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"rights\" (CreateUserPayload a) \[`UserRight <type-daml-script-userright-58823_>`_\]

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"rights\" (GrantUserRightsPayload a) \[`UserRight <type-daml-script-userright-58823_>`_\]

  **instance** `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"rights\" (RevokeUserRightsPayload a) \[`UserRight <type-daml-script-userright-58823_>`_\]

Functions
---------

.. _function-daml-script-query-70370:

`query <function-daml-script-query-70370_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `IsParties <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-isparties-53750>`_ p) \=\> p \-\> `Script <type-daml-script-script-90248_>`_ \[(`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t, t)\]

  Query the set of active contracts of the template
  that are visible to the given party\.

.. _function-daml-script-queryfilter-79010:

`queryFilter <function-daml-script-queryfilter-79010_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ c, `IsParties <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-isparties-53750>`_ p) \=\> p \-\> (c \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_) \-\> `Script <type-daml-script-script-90248_>`_ \[(`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ c, c)\]

  Query the set of active contracts of the template
  that are visible to the given party and match the given predicate\.

.. _function-daml-script-querycontractid-59269:

`queryContractId <function-daml-script-querycontractid-59269_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `IsParties <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-isparties-53750>`_ p, `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_) \=\> p \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t \-\> `Script <type-daml-script-script-90248_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ t)

  Query for the contract with the given contract id\.

  Returns ``None`` if there is no active contract the party is a stakeholder on\.

  WARNING\: Over the gRPC and with the JSON API
  in\-memory backend this performs a linear search so only use this if the number of
  active contracts is small\.

  This is semantically equivalent to calling ``query``
  and filtering on the client side\.

.. _function-daml-script-queryinterface-28612:

`queryInterface <function-daml-script-queryinterface-28612_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ i, `HasInterfaceView <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfaceview-4492>`_ i v, `IsParties <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-isparties-53750>`_ p) \=\> p \-\> `Script <type-daml-script-script-90248_>`_ \[(`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ i, `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ v)\]

  Query the set of active contract views for an interface
  that are visible to the given party\.
  If the view function fails for a given contract id, The ``Optional v`` will be ``None``\.

  WARNING\: Information about instances with failed\-views is not currently returned over the JSON API\: the ``Optional v`` will be ``Some _`` for every element in the returned list\.

.. _function-daml-script-queryinterfacecontractid-82799:

`queryInterfaceContractId <function-daml-script-queryinterfacecontractid-82799_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ i, `HasInterfaceView <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfaceview-4492>`_ i v, `IsParties <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-isparties-53750>`_ p, `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_) \=\> p \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ i \-\> `Script <type-daml-script-script-90248_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ v)

  Query for the contract view with the given contract id\.

  Returns ``None`` if there is no active contract the party is a stakeholder on\.

  Returns ``None`` if the view function fails for the given contract id\.

  WARNING\: Over the gRPC and with the JSON API
  in\-memory backend this performs a linear search so only use this if the number of
  active contracts is small\.

  This is semantically equivalent to calling ``queryInterface``
  and filtering on the client side\.

.. _function-daml-script-querycontractkey-59148:

`queryContractKey <function-daml-script-querycontractkey-59148_>`_
  \: (`HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_, `TemplateKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-templatekey-95200>`_ t k, `IsParties <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-isparties-53750>`_ p) \=\> p \-\> k \-\> `Script <type-daml-script-script-90248_>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t, t))

  Returns ``None`` if there is no active contract with the given key that
  the party is a stakeholder on\.

  WARNING\: Over the gRPC and with the JSON API
  in\-memory backend this performs a linear search so only use this if the number of
  active contracts is small\.

  This is semantically equivalent to calling ``query``
  and filtering on the client side\.

.. _function-daml-script-settime-25783:

`setTime <function-daml-script-settime-25783_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ \-\> `Script <type-daml-script-script-90248_>`_ ()

  Set the time via the time service\.

  This is only supported in static time mode when running over the gRPC API
  and in Daml Studio\.

  Note that the ledger time service does not support going backwards in time\.
  However, you can go back in time in Daml Studio\.

.. _function-daml-script-passtime-93483:

`passTime <function-daml-script-passtime-93483_>`_
  \: `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_ \-\> `Script <type-daml-script-script-90248_>`_ ()

  Advance ledger time by the given interval\.

  Only supported in static time mode when running over the gRPC API
  and in Daml Studio\. Note that this is not an atomic operation over the
  gRPC API so no other clients should try to change time while this is
  running\.

  Note that the ledger time service does not support going backwards in time\.
  However, you can go back in time in Daml Studio\.

.. _function-daml-script-allocateparty-25641:

`allocateParty <function-daml-script-allocateparty-25641_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> `Script <type-daml-script-script-90248_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  Allocate a party with the given display name
  using the party management service\.

.. _function-daml-script-allocatepartywithhint-4422:

`allocatePartyWithHint <function-daml-script-allocatepartywithhint-4422_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> `PartyIdHint <type-daml-script-partyidhint-32256_>`_ \-\> `Script <type-daml-script-script-90248_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  Allocate a party with the given display name and id hint
  using the party management service\.

.. _function-daml-script-allocatepartyon-73640:

`allocatePartyOn <function-daml-script-allocatepartyon-73640_>`_
  \: `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  Allocate a party with the given display name
  on the specified participant using the party management service\.

.. _function-daml-script-allocatepartywithhinton-4287:

`allocatePartyWithHintOn <function-daml-script-allocatepartywithhinton-4287_>`_
  \: `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> `PartyIdHint <type-daml-script-partyidhint-32256_>`_ \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  Allocate a party with the given display name and id hint
  on the specified participant using the party management service\.

.. _function-daml-script-listknownparties-43632:

`listKnownParties <function-daml-script-listknownparties-43632_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `Script <type-daml-script-script-90248_>`_ \[`PartyDetails <type-daml-script-partydetails-77837_>`_\]

  List the parties known to the default participant\.

.. _function-daml-script-listknownpartieson-69281:

`listKnownPartiesOn <function-daml-script-listknownpartieson-69281_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ \[`PartyDetails <type-daml-script-partydetails-77837_>`_\]

  List the parties known to the given participant\.

.. _function-daml-script-sleep-20327:

`sleep <function-daml-script-sleep-20327_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `RelTime <https://docs.daml.com/daml/stdlib/DA-Time.html#type-da-time-types-reltime-23082>`_ \-\> `Script <type-daml-script-script-90248_>`_ ()

  Sleep for the given duration\.

  This is primarily useful in tests
  where you repeatedly call ``query`` until a certain state is reached\.

  Note that this will sleep for the same duration in both wallcock and static time mode\.

.. _function-daml-script-submitmulti-15979:

`submitMulti <function-daml-script-submitmulti-15979_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> `Commands <type-daml-script-commands-64301_>`_ a \-\> `Script <type-daml-script-script-90248_>`_ a

  ``submitMulti actAs readAs cmds`` submits ``cmds`` as a single transaction
  authorized by ``actAs``\. Fetched contracts must be visible to at least
  one party in the union of actAs and readAs\.

.. _function-daml-script-submitmultimustfail-53000:

`submitMultiMustFail <function-daml-script-submitmultimustfail-53000_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> `Commands <type-daml-script-commands-64301_>`_ a \-\> `Script <type-daml-script-script-90248_>`_ ()

  ``submitMultiMustFail actAs readAs cmds`` behaves like ``submitMulti actAs readAs cmds``
  but fails when ``submitMulti`` succeeds and the other way around\.

.. _function-daml-script-createcmd-13518:

`createCmd <function-daml-script-createcmd-13518_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> t \-\> `Commands <type-daml-script-commands-64301_>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t)

  Create a contract of the given template\.

.. _function-daml-script-exercisecmd-60078:

`exerciseCmd <function-daml-script-exercisecmd-60078_>`_
  \: `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r \=\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t \-\> c \-\> `Commands <type-daml-script-commands-64301_>`_ r

  Exercise a choice on the given contract\.

.. _function-daml-script-exercisebykeycmd-15385:

`exerciseByKeyCmd <function-daml-script-exercisebykeycmd-15385_>`_
  \: (`TemplateKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-templatekey-95200>`_ t k, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r) \=\> k \-\> c \-\> `Commands <type-daml-script-commands-64301_>`_ r

  Exercise a choice on the contract with the given key\.

.. _function-daml-script-createandexercisecmd-24632:

`createAndExerciseCmd <function-daml-script-createandexercisecmd-24632_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r) \=\> t \-\> c \-\> `Commands <type-daml-script-commands-64301_>`_ r

  Create a contract and exercise a choice on it in the same transaction\.

.. _function-daml-script-archivecmd-9667:

`archiveCmd <function-daml-script-archivecmd-9667_>`_
  \: `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t `Archive <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-archive-15178>`_ () \=\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t \-\> `Commands <type-daml-script-commands-64301_>`_ ()

  Archive the given contract\.

  ``archiveCmd cid`` is equivalent to ``exerciseCmd cid Archive``\.

.. _function-daml-script-script-23284:

`script <function-daml-script-script-23284_>`_
  \: `Script <type-daml-script-script-90248_>`_ a \-\> `Script <type-daml-script-script-90248_>`_ a

  Convenience helper to declare you are writing a Script\.

  This is only useful for readability and to improve type inference\.
  Any expression of type ``Script a`` is a valid script regardless of whether
  it is implemented using ``script`` or not\.

.. _function-daml-script-useridtotext-45015:

`userIdToText <function-daml-script-useridtotext-45015_>`_
  \: `UserId <type-daml-script-userid-41343_>`_ \-\> `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

  Extract the name\-text from a user identitifer\.

.. _function-daml-script-validateuserid-78737:

`validateUserId <function-daml-script-validateuserid-78737_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> `Script <type-daml-script-script-90248_>`_ `UserId <type-daml-script-userid-41343_>`_

  Construct a user identifer from text\. May throw InvalidUserId\.

.. _function-daml-script-createuser-28944:

`createUser <function-daml-script-createuser-28944_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `User <type-daml-script-user-57134_>`_ \-\> \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> `Script <type-daml-script-script-90248_>`_ ()

  Create a user with the given rights\. May throw UserAlreadyExists\.

.. _function-daml-script-createuseron-29549:

`createUserOn <function-daml-script-createuseron-29549_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `User <type-daml-script-user-57134_>`_ \-\> \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ ()

  Create a user with the given rights on the given participant\. May throw UserAlreadyExists\.

.. _function-daml-script-getuser-9321:

`getUser <function-daml-script-getuser-9321_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `Script <type-daml-script-script-90248_>`_ `User <type-daml-script-user-57134_>`_

  Fetch a user record by user id\. May throw UserNotFound\.

.. _function-daml-script-getuseron-11676:

`getUserOn <function-daml-script-getuseron-11676_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ `User <type-daml-script-user-57134_>`_

  Fetch a user record by user id from the given participant\. May throw UserNotFound\.

.. _function-daml-script-listallusers-36812:

`listAllUsers <function-daml-script-listallusers-36812_>`_
  \: `Script <type-daml-script-script-90248_>`_ \[`User <type-daml-script-user-57134_>`_\]

  List all users\. This function may make multiple calls to underlying paginated ledger API\.

.. _function-daml-script-listalluserson-5229:

`listAllUsersOn <function-daml-script-listalluserson-5229_>`_
  \: `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ \[`User <type-daml-script-user-57134_>`_\]

  List all users on the given participant\. This function may make multiple calls to underlying paginated ledger API\.

.. _function-daml-script-grantuserrights-42490:

`grantUserRights <function-daml-script-grantuserrights-42490_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> `Script <type-daml-script-script-90248_>`_ \[`UserRight <type-daml-script-userright-58823_>`_\]

  Grant rights to a user\. Returns the rights that have been newly granted\. May throw UserNotFound\.

.. _function-daml-script-grantuserrightson-44311:

`grantUserRightsOn <function-daml-script-grantuserrightson-44311_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ \[`UserRight <type-daml-script-userright-58823_>`_\]

  Grant rights to a user on the given participant\. Returns the rights that have been newly granted\. May throw UserNotFound\.

.. _function-daml-script-revokeuserrights-4297:

`revokeUserRights <function-daml-script-revokeuserrights-4297_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> `Script <type-daml-script-script-90248_>`_ \[`UserRight <type-daml-script-userright-58823_>`_\]

  Revoke rights for a user\. Returns the revoked rights\. May throw UserNotFound\.

.. _function-daml-script-revokeuserrightson-65444:

`revokeUserRightsOn <function-daml-script-revokeuserrightson-65444_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> \[`UserRight <type-daml-script-userright-58823_>`_\] \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ \[`UserRight <type-daml-script-userright-58823_>`_\]

  Revoke rights for a user on the given participant\. Returns the revoked rights\. May throw UserNotFound\.

.. _function-daml-script-deleteuser-89045:

`deleteUser <function-daml-script-deleteuser-89045_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `Script <type-daml-script-script-90248_>`_ ()

  Delete a user\. May throw UserNotFound\.

.. _function-daml-script-deleteuseron-3948:

`deleteUserOn <function-daml-script-deleteuseron-3948_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ ()

  Delete a user on the given participant\. May throw UserNotFound\.

.. _function-daml-script-listuserrights-47313:

`listUserRights <function-daml-script-listuserrights-47313_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `Script <type-daml-script-script-90248_>`_ \[`UserRight <type-daml-script-userright-58823_>`_\]

  List the rights of a user\. May throw UserNotFound\.

.. _function-daml-script-listuserrightson-20864:

`listUserRightsOn <function-daml-script-listuserrightson-20864_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Script <type-daml-script-script-90248_>`_ \[`UserRight <type-daml-script-userright-58823_>`_\]

  List the rights of a user on the given participant\. May throw UserNotFound\.

.. _function-daml-script-submituser-54488:

`submitUser <function-daml-script-submituser-54488_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `Commands <type-daml-script-commands-64301_>`_ a \-\> `Script <type-daml-script-script-90248_>`_ a

  Submit the commands with the actAs and readAs claims granted to a user\. May throw UserNotFound\.

.. _function-daml-script-submituseron-87509:

`submitUserOn <function-daml-script-submituseron-87509_>`_
  \: `HasCallStack <https://docs.daml.com/daml/stdlib/DA-Stack.html#type-ghc-stack-types-hascallstack-63713>`_ \=\> `UserId <type-daml-script-userid-41343_>`_ \-\> `ParticipantName <type-daml-script-participantname-93946_>`_ \-\> `Commands <type-daml-script-commands-64301_>`_ a \-\> `Script <type-daml-script-script-90248_>`_ a

  Submit the commands with the actAs and readAs claims granted to the user on the given participant\. May throw UserNotFound\.

