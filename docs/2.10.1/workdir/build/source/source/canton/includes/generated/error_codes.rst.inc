
.. _1. grpcerrors_canton_error_codes:

1. GrpcErrors
=============


.. _aborted_due_to_shutdown_canton_error_codes:

ABORTED_DUE_TO_SHUTDOWN
-----------------------
* **Explanation**: This error is returned when processing of the request was aborted due to the node shutting down.
* **Resolution**: Retry the request against an active and available node.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `ABORTED_DUE_TO_SHUTDOWN <../../canton/scaladoc/com/digitalasset/canton/networking/grpc/CantonGrpcUtil$$GrpcErrors$$AbortedDueToShutdown$.html>`_


.. _2. authorizationcheckserrors_canton_error_codes:

2. AuthorizationChecksErrors
============================


.. _access_token_expired_canton_error_codes:

ACCESS_TOKEN_EXPIRED
--------------------
* **Explanation**: This rejection is given when a valid JWT token used for some period of time expires.
* **Resolution**: Ask your participant operator or IDP provider to give you an appropriate JWT token.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `ACCESS_TOKEN_EXPIRED <../../canton/scaladoc/com/digitalasset/canton/auth/AuthorizationChecksErrors$$AccessTokenExpired$.html>`_


.. _internal_authorization_error_canton_error_codes:

INTERNAL_AUTHORIZATION_ERROR
----------------------------
* **Explanation**: An internal system authorization error occurred.
* **Resolution**: Contact the participant operator.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INTERNAL_AUTHORIZATION_ERROR <../../canton/scaladoc/com/digitalasset/canton/auth/AuthorizationChecksErrors$$InternalAuthorizationError$.html>`_


.. _invalid_token_canton_error_codes:

INVALID_TOKEN
-------------
* **Explanation**: This error is emitted when a submitted ledger API command contains an invalid token.
* **Resolution**: Inspect the reason given and correct your application.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_TOKEN <../../canton/scaladoc/com/digitalasset/canton/auth/AuthorizationChecksErrors$$InvalidToken$.html>`_


.. _permission_denied_canton_error_codes:

PERMISSION_DENIED
-----------------
* **Explanation**: This rejection is given if the supplied authorization token is not sufficient for the intended command. The exact reason is logged on the participant, but not given to the user for security reasons.
* **Resolution**: Inspect your command and your token or ask your participant operator for an explanation why this command failed.
* **Category**: InsufficientPermission
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status PERMISSION_DENIED without any details for security reasons.
* **Scaladocs**: `PERMISSION_DENIED <../../canton/scaladoc/com/digitalasset/canton/auth/AuthorizationChecksErrors$$PermissionDenied$.html>`_


.. _stale_stream_authorization_canton_error_codes:

STALE_STREAM_AUTHORIZATION
--------------------------
* **Explanation**: The stream was aborted because the authenticated user's rights changed, and the user might thus no longer be authorized to this stream. 
* **Resolution**: The application should automatically retry fetching the stream. It will either succeed, or fail with an explicit denial of authentication or permission.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `STALE_STREAM_AUTHORIZATION <../../canton/scaladoc/com/digitalasset/canton/auth/AuthorizationChecksErrors$$StaleUserManagementBasedStreamClaims$.html>`_


.. _unauthenticated_canton_error_codes:

UNAUTHENTICATED
---------------
* **Explanation**: This rejection is given if the submitted command does not contain a JWT token on a participant enforcing JWT authentication.
* **Resolution**: Ask your participant operator or IDP provider to give you an appropriate JWT token.
* **Category**: AuthInterceptorInvalidAuthenticationCredentials
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status UNAUTHENTICATED without any details for security reasons.
* **Scaladocs**: `UNAUTHENTICATED <../../canton/scaladoc/com/digitalasset/canton/auth/AuthorizationChecksErrors$$Unauthenticated$.html>`_


.. _3. participanterrorgroup_canton_error_codes:

3. ParticipantErrorGroup
========================


.. _3.1. errors_canton_error_codes:

3.1. Errors
===========


.. _acs_commitment_internal_error_canton_error_codes:

ACS_COMMITMENT_INTERNAL_ERROR
-----------------------------
* **Explanation**: This error indicates that there was an internal error within the ACS commitment processing.
* **Resolution**: Inspect error message for details.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side.
* **Scaladocs**: `ACS_COMMITMENT_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/pruning/AcsCommitmentProcessor$$Errors$$InternalError$.html>`_


.. _3.1.1. mismatcherror_canton_error_codes:

3.1.1. MismatchError
====================


.. _acs_commitment_alarm_canton_error_codes:

ACS_COMMITMENT_ALARM
--------------------
* **Explanation**: The participant has detected that another node is behaving maliciously.
* **Resolution**: Contact support.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `ACS_COMMITMENT_ALARM <../../canton/scaladoc/com/digitalasset/canton/participant/pruning/AcsCommitmentProcessor$$Errors$$MismatchError$$AcsCommitmentAlarm$.html>`_


.. _acs_commitment_mismatch_canton_error_codes:

ACS_COMMITMENT_MISMATCH
-----------------------
* **Explanation**: This error indicates that a remote participant has sent a commitment over an ACS for a period which does not match the local commitment. This error occurs if a remote participant has manually changed contracts using repair, or due to byzantine behavior, or due to malfunction of the system. The consequence is that the ledger is forked, and some commands that should pass will not.
* **Resolution**: Please contact the other participant in order to check the cause of the mismatch. Either repair the store of this participant or of the counterparty.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `ACS_COMMITMENT_MISMATCH <../../canton/scaladoc/com/digitalasset/canton/participant/pruning/AcsCommitmentProcessor$$Errors$$MismatchError$$CommitmentsMismatch$.html>`_


.. _acs_mismatch_no_shared_contracts_canton_error_codes:

ACS_MISMATCH_NO_SHARED_CONTRACTS
--------------------------------
* **Explanation**: This error indicates that a remote participant has sent a commitment over an ACS for a period, while this participant does not think that there is a shared contract state. This error occurs if a remote participant has manually changed contracts using repair, or due to byzantine behavior, or due to malfunction of the system. The consequence is that the ledger is forked, and some commands that should pass will not.
* **Resolution**: Please contact the other participant in order to check the cause of the mismatch. Either repair the store of this participant or of the counterparty.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `ACS_MISMATCH_NO_SHARED_CONTRACTS <../../canton/scaladoc/com/digitalasset/canton/participant/pruning/AcsCommitmentProcessor$$Errors$$MismatchError$$NoSharedContracts$.html>`_


.. _3.1.2. degradationerror_canton_error_codes:

3.1.2. DegradationError
=======================


.. _acs_commitment_degradation_canton_error_codes:

ACS_COMMITMENT_DEGRADATION
--------------------------
* **Explanation**: The participant has detected that ACS computation is taking to long and trying to catch up.
* **Resolution**: Catch up mode is enabled and the participant should recover on its own.
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `ACS_COMMITMENT_DEGRADATION <../../canton/scaladoc/com/digitalasset/canton/participant/pruning/AcsCommitmentProcessor$$Errors$$DegradationError$$AcsCommitmentDegradation$.html>`_


.. _acs_commitment_degradation_with_ineffective_config_canton_error_codes:

ACS_COMMITMENT_DEGRADATION_WITH_INEFFECTIVE_CONFIG
--------------------------------------------------
* **Explanation**: The participant is configured to engage catchup mode, however configuration is invalid to have any effect
* **Resolution**: Please update catchup mode to have a catchUpIntervalSkip higher than 1
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `ACS_COMMITMENT_DEGRADATION_WITH_INEFFECTIVE_CONFIG <../../canton/scaladoc/com/digitalasset/canton/participant/pruning/AcsCommitmentProcessor$$Errors$$DegradationError$$AcsCommitmentDegradationWithIneffectiveConfig$.html>`_


.. _3.2. ledgerapierrorgroup_canton_error_codes:

3.2. LedgerApiErrorGroup
========================


.. _3.2.1. commandexecutionerrors_canton_error_codes:

3.2.1. CommandExecutionErrors
=============================


.. _failed_to_determine_ledger_time_canton_error_codes:

FAILED_TO_DETERMINE_LEDGER_TIME
-------------------------------
* **Explanation**: This error occurs if the participant fails to determine the max ledger time of the used contracts. Most likely, this means that one of the contracts is not active anymore which can happen under contention. It can also happen with contract keys. 
* **Resolution**: Retry the transaction submission.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `FAILED_TO_DETERMINE_LEDGER_TIME <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$FailedToDetermineLedgerTime$.html>`_


.. _interpretation_time_exceeded_canton_error_codes:

INTERPRETATION_TIME_EXCEEDED
----------------------------
* **Explanation**: This error occurs when the interpretation of a command exceeded the time limit, defined as the maximum time that can be assigned by the ledger when it starts processing the command. It corresponds to the time assigned upon submission by the participant (the ledger time) + a tolerance defined by the `ledgerTimeToRecordTimeTolerance` ledger configuration parameter. Reasons for exceeding this limit can vary: the participant may be under high load, the command interpretation may be very complex, or even run into an infinite loop due to a mistake in the Daml code. 
* **Resolution**: Due to the halting problem, we cannot determine whether the interpretation will eventually complete. As a developer: inspect your code for possible non-terminating loops or consider reducing its complexity. As an operator: check and possibly update the resources allocated to the system, as well as the time-related configuration parameters (see "Time on Daml Ledgers" in the "Daml Ledger Model Concepts" doc section and the `set_ledger_time_record_time_tolerance` console command). 
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `INTERPRETATION_TIME_EXCEEDED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$TimeExceeded$.html>`_


.. _3.2.1.1. package_canton_error_codes:

3.2.1.1. Package
================


.. _allowed_language_versions_canton_error_codes:

ALLOWED_LANGUAGE_VERSIONS
-------------------------
* **Explanation**: This error indicates that the uploaded DAR is based on an unsupported language version.
* **Resolution**: Use a DAR compiled with a language version that this participant supports.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `ALLOWED_LANGUAGE_VERSIONS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Package$$AllowedLanguageVersions$.html>`_


.. _package_validation_failed_canton_error_codes:

PACKAGE_VALIDATION_FAILED
-------------------------
* **Explanation**: This error occurs if a package referred to by a command fails validation. This should not happen as packages are validated when being uploaded.
* **Resolution**: Contact support.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `PACKAGE_VALIDATION_FAILED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Package$$PackageValidationFailed$.html>`_


.. _3.2.1.2. preprocessing_canton_error_codes:

3.2.1.2. Preprocessing
======================


.. _command_preprocessing_failed_canton_error_codes:

COMMAND_PREPROCESSING_FAILED
----------------------------
* **Explanation**: This error occurs if a command fails during interpreter pre-processing.
* **Resolution**: Inspect error details and correct your application.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `COMMAND_PREPROCESSING_FAILED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Preprocessing$$PreprocessingFailed$.html>`_


.. _3.2.1.3. interpreter_canton_error_codes:

3.2.1.3. Interpreter
====================


.. _contract_does_not_implement_interface_canton_error_codes:

CONTRACT_DOES_NOT_IMPLEMENT_INTERFACE
-------------------------------------
* **Explanation**: This error occurs when you try to coerce/use a contract via an interface that it does not implement.
* **Resolution**: Ensure the contract you are calling does implement the interface you are using to do so. Avoid writing LF/low-level interface implementation classes manually.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `CONTRACT_DOES_NOT_IMPLEMENT_INTERFACE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$ContractDoesNotImplementInterface$.html>`_


.. _contract_does_not_implement_requiring_interface_canton_error_codes:

CONTRACT_DOES_NOT_IMPLEMENT_REQUIRING_INTERFACE
-----------------------------------------------
* **Explanation**: This error occurs when you try to create/use a contract that does not implement the requiring interfaces of some other interface that it does implement.
* **Resolution**: Ensure you implement all required interfaces correctly, and avoid writing LF/low-level interface implementation classes manually.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `CONTRACT_DOES_NOT_IMPLEMENT_REQUIRING_INTERFACE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$ContractDoesNotImplementRequiringInterface$.html>`_


.. _contract_id_comparability_canton_error_codes:

CONTRACT_ID_COMPARABILITY
-------------------------
* **Explanation**: This error occurs when you attempt to compare a global and local contract ID of the same discriminator.
* **Resolution**: Avoid constructing contract IDs manually.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `CONTRACT_ID_COMPARABILITY <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$ContractIdComparability$.html>`_


.. _contract_id_in_contract_key_canton_error_codes:

CONTRACT_ID_IN_CONTRACT_KEY
---------------------------
* **Explanation**: This error occurs when a contract key contains a contract ID, which is illegal for hashing reasons.
* **Resolution**: Ensure your contracts key field cannot contain a contract ID.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `CONTRACT_ID_IN_CONTRACT_KEY <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$ContractIdInContractKey$.html>`_


.. _contract_not_active_canton_error_codes:

CONTRACT_NOT_ACTIVE
-------------------
* **Explanation**: This error occurs if an exercise or fetch happens on a transaction-locally consumed contract.
* **Resolution**: This error indicates an application error.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `CONTRACT_NOT_ACTIVE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$ContractNotActive$.html>`_


.. _create_empty_contract_key_maintainers_canton_error_codes:

CREATE_EMPTY_CONTRACT_KEY_MAINTAINERS
-------------------------------------
* **Explanation**: This error occurs when you try to create a contract that has a key, but with empty maintainers.
* **Resolution**: Check the definition of the contract key's maintainers, and ensure this list won't be empty given your creation arguments.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `CREATE_EMPTY_CONTRACT_KEY_MAINTAINERS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$CreateEmptyContractKeyMaintainers$.html>`_


.. _daml_authorization_error_canton_error_codes:

DAML_AUTHORIZATION_ERROR
------------------------
* **Explanation**: This error occurs if a Daml transaction fails due to an authorization error. An authorization means that the Daml transaction computed a different set of required submitters than you have provided during the submission as `actAs` parties.
* **Resolution**: This error type occurs if there is an application error.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DAML_AUTHORIZATION_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$AuthorizationError$.html>`_


.. _daml_interpretation_error_canton_error_codes:

DAML_INTERPRETATION_ERROR
-------------------------
* **Explanation**: This error occurs if a Daml transaction fails during interpretation.
* **Resolution**: This error type occurs if there is an application error.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DAML_INTERPRETATION_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$GenericInterpretationError$.html>`_


.. _daml_interpreter_invalid_argument_canton_error_codes:

DAML_INTERPRETER_INVALID_ARGUMENT
---------------------------------
* **Explanation**: This error occurs if a Daml transaction fails during interpretation due to an invalid argument.
* **Resolution**: This error type occurs if there is an application error.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DAML_INTERPRETER_INVALID_ARGUMENT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$InvalidArgumentInterpretationError$.html>`_


.. _disallowed_interface_exercise_canton_error_codes:

DISALLOWED_INTERFACE_EXERCISE
-----------------------------
* **Explanation**: Exercising an LF 1.15 interface implemented by an LF 1.17 (or newer) template is disallowed since 2.10.1
* **Resolution**: Use LF 1.17 for the interface definition.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DISALLOWED_INTERFACE_EXERCISE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$DisallowedInterfaceExercise$.html>`_


.. _disclosed_contract_key_hashing_error_canton_error_codes:

DISCLOSED_CONTRACT_KEY_HASHING_ERROR
------------------------------------
* **Explanation**: This error occurs if a user attempts to provide a key hash for a disclosed contract which we have already cached to be different.
* **Resolution**: Ensure the contract ID and contract payload you have provided in your disclosed contract is correct.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DISCLOSED_CONTRACT_KEY_HASHING_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$DisclosedContractKeyHashingError$.html>`_


.. _fetch_empty_contract_key_maintainers_canton_error_codes:

FETCH_EMPTY_CONTRACT_KEY_MAINTAINERS
------------------------------------
* **Explanation**: This error occurs when you try to fetch a contract by key, but that key would have empty maintainers.
* **Resolution**: Check the definition of the contract key's maintainers, and ensure this list won't be empty given the contract key you are fetching.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `FETCH_EMPTY_CONTRACT_KEY_MAINTAINERS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$FetchEmptyContractKeyMaintainers$.html>`_


.. _interpretation_dev_error_canton_error_codes:

INTERPRETATION_DEV_ERROR
------------------------
* **Explanation**: This error is a catch-all for errors thrown by in-development features, and should never be thrown in production.
* **Resolution**: See the error message for details of the specific in-development feature error. If this is production, avoid using development features.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INTERPRETATION_DEV_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$InterpretationDevError$.html>`_


.. _interpretation_user_error_canton_error_codes:

INTERPRETATION_USER_ERROR
-------------------------
* **Explanation**: This error occurs when a user calls abort or error on an LF version before native exceptions were introduced.
* **Resolution**: Either remove the call to abort, error or perhaps assert, or ensure you are exercising your contract choice as the author expects.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INTERPRETATION_USER_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$InterpretationUserError$.html>`_


.. _non_comparable_values_canton_error_codes:

NON_COMPARABLE_VALUES
---------------------
* **Explanation**: This error occurs when you attempt to compare two values of different types using the built-in comparison types.
* **Resolution**: Avoid using the low level comparison build, and instead use the Eq class.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `NON_COMPARABLE_VALUES <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$NonComparableValues$.html>`_


.. _template_precondition_violated_canton_error_codes:

TEMPLATE_PRECONDITION_VIOLATED
------------------------------
* **Explanation**: This error occurs when a contract's pre-condition (the ensure clause) is violated on contract creation.
* **Resolution**: Ensure the contract argument you are passing into your create doesn't violate the conditions of the contract.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `TEMPLATE_PRECONDITION_VIOLATED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$TemplatePreconditionViolated$.html>`_


.. _unhandled_exception_canton_error_codes:

UNHANDLED_EXCEPTION
-------------------
* **Explanation**: This error occurs when a user throws an error and does not catch it with try-catch.
* **Resolution**: Either your error handling in a choice body is insufficient, or you are using a contract incorrectly.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `UNHANDLED_EXCEPTION <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$UnhandledException$.html>`_


.. _value_nesting_canton_error_codes:

VALUE_NESTING
-------------
* **Explanation**: This error occurs when you nest values too deeply.
* **Resolution**: Restructure your code and reduce value nesting.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `VALUE_NESTING <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$ValueNesting$.html>`_


.. _wrongly_typed_contract_canton_error_codes:

WRONGLY_TYPED_CONTRACT
----------------------
* **Explanation**: This error occurs when you try to fetch/use a contract in some way with a contract ID that doesn't match the template type on the ledger.
* **Resolution**: Ensure the contract IDs you are using are of the type we expect on the ledger. Avoid unsafely coercing contract IDs.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `WRONGLY_TYPED_CONTRACT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$WronglyTypedContract$.html>`_


.. _3.2.1.3.1. lookuperrors_canton_error_codes:

3.2.1.3.1. LookupErrors
=======================


.. _contract_key_not_found_canton_error_codes:

CONTRACT_KEY_NOT_FOUND
----------------------
* **Explanation**: This error occurs if the Daml engine interpreter cannot resolve a contract key to an active contract. This can be caused by either the contract key not being known to the participant, or not being known to the submitting parties or the contract representing an already archived key.
* **Resolution**: This error type occurs if there is contention on a contract.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `CONTRACT_KEY_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$LookupErrors$$ContractKeyNotFound$.html>`_


.. _3.2.1.3.2. upgradeerror_canton_error_codes:

3.2.1.3.2. UpgradeError
=======================


.. _contract_not_upgradable_canton_error_codes:

CONTRACT_NOT_UPGRADABLE
-----------------------
* **Explanation**: An attempt was made to upgrade a template compiled with a daml language version before 1.17
* **Resolution**: If possible archive this contract and re-create it with a template compiled with daml 1.17 or above
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `CONTRACT_NOT_UPGRADABLE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$UpgradeError$$ContractNotUpgradable$.html>`_


.. _interpretation_upgrade_error_downgrade_drop_defined_field_canton_error_codes:

INTERPRETATION_UPGRADE_ERROR_DOWNGRADE_DROP_DEFINED_FIELD
---------------------------------------------------------
* **Explanation**: An optional contract field with a value of Some may not be dropped during downgrading
* **Resolution**: There is data that is newer than the implementation it is being used it, and thus is not compatible. Ensure new data (i.e. those with additional fields as `Some`) is only used with new choices
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INTERPRETATION_UPGRADE_ERROR_DOWNGRADE_DROP_DEFINED_FIELD <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$UpgradeError$$DowngradeDropDefinedField$.html>`_


.. _interpretation_upgrade_error_downgrade_failed_canton_error_codes:

INTERPRETATION_UPGRADE_ERROR_DOWNGRADE_FAILED
---------------------------------------------
* **Explanation**: An optional contract field with a value of Some may not be dropped during downgrading
* **Resolution**: There is data that is newer than the implementation using it, and thus is not compatible. Ensure new data (i.e. those with additional fields as `Some`) is only used with new/compatible choices
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INTERPRETATION_UPGRADE_ERROR_DOWNGRADE_FAILED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$UpgradeError$$DowngradeFailed$.html>`_


.. _interpretation_upgrade_error_validation_failed_canton_error_codes:

INTERPRETATION_UPGRADE_ERROR_VALIDATION_FAILED
----------------------------------------------
* **Explanation**: Validation fails when trying to upgrade the contract
* **Resolution**: Verify that neither the signatories, nor the observers, nor the contract key, nor the key's maintainers have changed
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INTERPRETATION_UPGRADE_ERROR_VALIDATION_FAILED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$UpgradeError$$ValidationFailed$.html>`_


.. _interpretation_upgrade_error_view_mismatch_canton_error_codes:

INTERPRETATION_UPGRADE_ERROR_VIEW_MISMATCH
------------------------------------------
* **Explanation**: View mismatch when trying to upgrade the contract
* **Resolution**: Verify that the interface views of the contract have not changed
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INTERPRETATION_UPGRADE_ERROR_VIEW_MISMATCH <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/CommandExecutionErrors$$Interpreter$$UpgradeError$$ViewMismatch$.html>`_


.. _3.2.2. adminserviceserrorgroup_canton_error_codes:

3.2.2. AdminServicesErrorGroup
==============================


.. _3.2.2.1. partymanagementserviceerrors_canton_error_codes:

3.2.2.1. PartyManagementServiceErrors
=====================================


.. _concurrent_party_details_update_detected_canton_error_codes:

CONCURRENT_PARTY_DETAILS_UPDATE_DETECTED
----------------------------------------
* **Explanation**: Concurrent updates to a party can be controlled by supplying an update request with a resource version (this is optional). A party's resource version can be obtained by reading the party on the Ledger API. There was attempt to update a party using a stale resource version, indicating that a different process had updated the party earlier.
* **Resolution**: Read this party again to obtain its most recent state and in particular its most recent resource version. Use the obtained information to build and send a new update request.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `CONCURRENT_PARTY_DETAILS_UPDATE_DETECTED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/PartyManagementServiceErrors$$ConcurrentPartyDetailsUpdateDetected$.html>`_


.. _internal_party_record_already_exists_canton_error_codes:

INTERNAL_PARTY_RECORD_ALREADY_EXISTS
------------------------------------
* **Explanation**: Each on-ledger party known to this participant node can have a participant's local metadata assigned to it. The local information about a party referred to by this request was found when it should have been not found.
* **Resolution**: This error can indicate a problem with the server's storage or implementation.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INTERNAL_PARTY_RECORD_ALREADY_EXISTS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/PartyManagementServiceErrors$$InternalPartyRecordAlreadyExists$.html>`_


.. _internal_party_record_not_found_canton_error_codes:

INTERNAL_PARTY_RECORD_NOT_FOUND
-------------------------------
* **Explanation**: Each on-ledger party known to this participant node can have a participant's local metadata assigned to it. The local information about a party referred to by this request was not found when it should have been found.
* **Resolution**: This error can indicate a problem with the server's storage or implementation.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INTERNAL_PARTY_RECORD_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/PartyManagementServiceErrors$$InternalPartyRecordNotFound$.html>`_


.. _invalid_party_details_update_request_canton_error_codes:

INVALID_PARTY_DETAILS_UPDATE_REQUEST
------------------------------------
* **Explanation**: There was an attempt to update a party using an invalid update request.
* **Resolution**: Inspect the error details for specific information on what made the request invalid. Retry with an adjusted update request.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_PARTY_DETAILS_UPDATE_REQUEST <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/PartyManagementServiceErrors$$InvalidUpdatePartyDetailsRequest$.html>`_


.. _max_party_details_annotations_size_exceeded_canton_error_codes:

MAX_PARTY_DETAILS_ANNOTATIONS_SIZE_EXCEEDED
-------------------------------------------
* **Explanation**: A party can have at most 256kb worth of annotations in total measured in number of bytes in UTF-8 encoding. There was an attempt to allocate or update a party such that this limit would have been exceeded.
* **Resolution**: Retry with fewer annotations or delete some of the party's existing annotations.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `MAX_PARTY_DETAILS_ANNOTATIONS_SIZE_EXCEEDED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/PartyManagementServiceErrors$$MaxPartyAnnotationsSizeExceeded$.html>`_


.. _party_not_found_canton_error_codes:

PARTY_NOT_FOUND
---------------
* **Explanation**: The party referred to by the request was not found.
* **Resolution**: Check that you are connecting to the right participant node and that the party is spelled correctly.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `PARTY_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/PartyManagementServiceErrors$$PartyNotFound$.html>`_


.. _3.2.2.2. usermanagementserviceerrors_canton_error_codes:

3.2.2.2. UserManagementServiceErrors
====================================


.. _concurrent_user_update_detected_canton_error_codes:

CONCURRENT_USER_UPDATE_DETECTED
-------------------------------
* **Explanation**: Concurrent updates to a user can be controlled by supplying an update request with a resource version (this is optional). A user's resource version can be obtained by reading the user on the Ledger API. There was attempt to update a user using a stale resource version, indicating that a different process had updated the user earlier.
* **Resolution**: Read this user again to obtain its most recent state and in particular its most recent resource version. Use the obtained information to build and send a new update request.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `CONCURRENT_USER_UPDATE_DETECTED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/UserManagementServiceErrors$$ConcurrentUserUpdateDetected$.html>`_


.. _invalid_user_update_request_canton_error_codes:

INVALID_USER_UPDATE_REQUEST
---------------------------
* **Explanation**: There was an attempt to update a user using an invalid update request.
* **Resolution**: Inspect the error details for specific information on what made the request invalid. Retry with an adjusted update request.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_USER_UPDATE_REQUEST <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/UserManagementServiceErrors$$InvalidUpdateUserRequest$.html>`_


.. _max_user_annotations_size_exceeded_canton_error_codes:

MAX_USER_ANNOTATIONS_SIZE_EXCEEDED
----------------------------------
* **Explanation**: A user can have at most 256kb worth of annotations in total measured in number of bytes in UTF-8 encoding. There was an attempt to create or update a user such that this limit would have been exceeded.
* **Resolution**: Retry with fewer annotations or delete some of the user's existing annotations.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `MAX_USER_ANNOTATIONS_SIZE_EXCEEDED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/UserManagementServiceErrors$$MaxUserAnnotationsSizeExceeded$.html>`_


.. _too_many_user_rights_canton_error_codes:

TOO_MANY_USER_RIGHTS
--------------------
* **Explanation**: A user can have only a limited number of user rights. There was an attempt to create a user with too many rights or grant too many rights to a user.
* **Resolution**: Retry with a smaller number of rights or delete some of the already existing rights of this user. Contact the participant operator if the limit is too low.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `TOO_MANY_USER_RIGHTS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/UserManagementServiceErrors$$TooManyUserRights$.html>`_


.. _user_already_exists_canton_error_codes:

USER_ALREADY_EXISTS
-------------------
* **Explanation**: There already exists a user with the same user-id.
* **Resolution**: Check that you are connecting to the right participant node and the user-id is spelled correctly, or use the user that already exists.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `USER_ALREADY_EXISTS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/UserManagementServiceErrors$$UserAlreadyExists$.html>`_


.. _user_not_found_canton_error_codes:

USER_NOT_FOUND
--------------
* **Explanation**: The user referred to by the request was not found.
* **Resolution**: Check that you are connecting to the right participant node and the user-id is spelled correctly, if yes, create the user.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `USER_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/UserManagementServiceErrors$$UserNotFound$.html>`_


.. _3.2.2.3. identityproviderconfigserviceerrors_canton_error_codes:

3.2.2.3. IdentityProviderConfigServiceErrors
============================================


.. _idp_config_already_exists_canton_error_codes:

IDP_CONFIG_ALREADY_EXISTS
-------------------------
* **Explanation**: There already exists an identity provider configuration with the same identity provider id.
* **Resolution**: Check that you are connecting to the right participant node and the identity provider id is spelled correctly, or use an identity provider that already exists.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `IDP_CONFIG_ALREADY_EXISTS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/IdentityProviderConfigServiceErrors$$IdentityProviderConfigAlreadyExists$.html>`_


.. _idp_config_by_issuer_not_found_canton_error_codes:

IDP_CONFIG_BY_ISSUER_NOT_FOUND
------------------------------
* **Explanation**: The identity provider config referred to by the request was not found.
* **Resolution**: Check that you are connecting to the right participant node and the identity provider config is spelled correctly, or create the configuration.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `IDP_CONFIG_BY_ISSUER_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/IdentityProviderConfigServiceErrors$$IdentityProviderConfigByIssuerNotFound$.html>`_


.. _idp_config_issuer_already_exists_canton_error_codes:

IDP_CONFIG_ISSUER_ALREADY_EXISTS
--------------------------------
* **Explanation**: There already exists an identity provider configuration with the same issuer.
* **Resolution**: Check that you are connecting to the right participant node and the identity provider id is spelled correctly, or use an identity provider that already exists.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `IDP_CONFIG_ISSUER_ALREADY_EXISTS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/IdentityProviderConfigServiceErrors$$IdentityProviderConfigIssuerAlreadyExists$.html>`_


.. _idp_config_not_found_canton_error_codes:

IDP_CONFIG_NOT_FOUND
--------------------
* **Explanation**: The identity provider config referred to by the request was not found.
* **Resolution**: Check that you are connecting to the right participant node and the identity provider config is spelled correctly, or create the configuration.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `IDP_CONFIG_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/IdentityProviderConfigServiceErrors$$IdentityProviderConfigNotFound$.html>`_


.. _invalid_identity_provider_update_request_canton_error_codes:

INVALID_IDENTITY_PROVIDER_UPDATE_REQUEST
----------------------------------------
* **Explanation**: There was an attempt to update an identity provider config using an invalid update request.
* **Resolution**: Inspect the error details for specific information on what made the request invalid. Retry with an adjusted update request.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_IDENTITY_PROVIDER_UPDATE_REQUEST <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/IdentityProviderConfigServiceErrors$$InvalidUpdateIdentityProviderConfigRequest$.html>`_


.. _too_many_identity_provider_configs_canton_error_codes:

TOO_MANY_IDENTITY_PROVIDER_CONFIGS
----------------------------------
* **Explanation**: A system can have only a limited number of identity provider configurations. There was an attempt to create an identity provider configuration.
* **Resolution**: Delete some of the already existing identity provider configurations. Contact the participant operator if the limit is too low.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `TOO_MANY_IDENTITY_PROVIDER_CONFIGS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/IdentityProviderConfigServiceErrors$$TooManyIdentityProviderConfigs$.html>`_


.. _3.2.3. adminserviceerrors_canton_error_codes:

3.2.3. AdminServiceErrors
=========================


.. _configuration_entry_rejected_canton_error_codes:

CONFIGURATION_ENTRY_REJECTED
----------------------------
* **Explanation**: This rejection is given when a new configuration is rejected.
* **Resolution**: Fetch newest configuration and/or retry.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `CONFIGURATION_ENTRY_REJECTED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/AdminServiceErrors$$ConfigurationEntryRejected$.html>`_


.. _internally_invalid_key_canton_error_codes:

INTERNALLY_INVALID_KEY
----------------------
* **Explanation**: A cryptographic key used by the configured system is not valid
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INTERNALLY_INVALID_KEY <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/AdminServiceErrors$$InternallyInvalidKey$.html>`_


.. _package_upload_rejected_canton_error_codes:

PACKAGE_UPLOAD_REJECTED
-----------------------
* **Explanation**: This rejection is given when a package upload is rejected.
* **Resolution**: Refer to the detailed message of the received error.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PACKAGE_UPLOAD_REJECTED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/AdminServiceErrors$$PackageUploadRejected$.html>`_


.. _3.2.4. consistencyerrors_canton_error_codes:

3.2.4. ConsistencyErrors
========================


.. _contract_not_found_canton_error_codes:

CONTRACT_NOT_FOUND
------------------
* **Explanation**: This error occurs if the Daml engine can not find a referenced contract. This can be caused by either the contract not being known to the participant, or not being known to the submitting parties or already being archived.
* **Resolution**: This error type occurs if there is contention on a contract.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `CONTRACT_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$ContractNotFound$.html>`_


.. _disclosed_contract_invalid_canton_error_codes:

DISCLOSED_CONTRACT_INVALID
--------------------------
* **Explanation**: This error occurs if the disclosed payload or metadata of one of the contracts does not match the actual payload or metadata of the contract.
* **Resolution**: Re-submit the command using valid disclosed contract payload and metadata.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DISCLOSED_CONTRACT_INVALID <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$DisclosedContractInvalid$.html>`_


.. _duplicate_command_canton_error_codes:

DUPLICATE_COMMAND
-----------------
* **Explanation**: A command with the given command id has already been successfully processed.
* **Resolution**: The correct resolution depends on the use case. If the error received pertains to a submission retried due to a timeout, do nothing, as the previous command has already been accepted. If the intent is to submit a new command, re-submit using a distinct command id. 
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `DUPLICATE_COMMAND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$DuplicateCommand$.html>`_


.. _duplicate_contract_key_canton_error_codes:

DUPLICATE_CONTRACT_KEY
----------------------
* **Explanation**: This error signals that within the transaction we got to a point where two contracts with the same key were active.
* **Resolution**: This error indicates an application error.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `DUPLICATE_CONTRACT_KEY <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$DuplicateContractKey$.html>`_


.. _inconsistent_canton_error_codes:

INCONSISTENT
------------
* **Explanation**: At least one input has been altered by a concurrent transaction submission.
* **Resolution**: The correct resolution depends on the business flow, for example it may be possible to proceed without an archived contract as an input, or the transaction submission may be retried to load the up-to-date value of a contract key.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INCONSISTENT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$Inconsistent$.html>`_


.. _inconsistent_contracts_canton_error_codes:

INCONSISTENT_CONTRACTS
----------------------
* **Explanation**: An input contract has been archived by a concurrent transaction submission.
* **Resolution**: The correct resolution depends on the business flow, for example it may be possible to proceed without the archived contract as an input, or a different contract could be used.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INCONSISTENT_CONTRACTS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$InconsistentContracts$.html>`_


.. _inconsistent_contract_key_canton_error_codes:

INCONSISTENT_CONTRACT_KEY
-------------------------
* **Explanation**: An input contract key was re-assigned to a different contract by a concurrent transaction submission.
* **Resolution**: Retry the transaction submission.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INCONSISTENT_CONTRACT_KEY <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$InconsistentContractKey$.html>`_


.. _invalid_ledger_time_canton_error_codes:

INVALID_LEDGER_TIME
-------------------
* **Explanation**: The ledger time of the submission violated some constraint on the ledger time.
* **Resolution**: Retry the transaction submission.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INVALID_LEDGER_TIME <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$InvalidLedgerTime$.html>`_


.. _submission_already_in_flight_canton_error_codes:

SUBMISSION_ALREADY_IN_FLIGHT
----------------------------
* **Explanation**: Another command submission with the same change ID (application ID, command ID, actAs) is already being processed.
* **Resolution**: Listen to the command completion stream until a completion for the in-flight command submission is published. Alternatively, resubmit the command. If the in-flight submission has finished successfully by then, this will return more detailed information about the earlier one. If the in-flight submission has failed by then, the resubmission will attempt to record the new transaction on the ledger. 
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `SUBMISSION_ALREADY_IN_FLIGHT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/ConsistencyErrors$$SubmissionAlreadyInFlight$.html>`_


.. _3.2.5. packageserviceerrors_canton_error_codes:

3.2.5. PackageServiceErrors
===========================


.. _dar_not_self_consistent_canton_error_codes:

DAR_NOT_SELF_CONSISTENT
-----------------------
* **Explanation**: This error indicates that the uploaded Dar is broken because it is missing internal dependencies.
* **Resolution**: Contact the supplier of the Dar.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DAR_NOT_SELF_CONSISTENT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Validation$$SelfConsistency$.html>`_


.. _dar_not_valid_upgrade_canton_error_codes:

DAR_NOT_VALID_UPGRADE
---------------------
* **Explanation**: This error indicates that the uploaded Dar is invalid because it doesn't upgrade the packages it claims to upgrade.
* **Resolution**: Contact the supplier of the Dar.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DAR_NOT_VALID_UPGRADE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Validation$$Upgradeability$.html>`_


.. _dar_validation_error_canton_error_codes:

DAR_VALIDATION_ERROR
--------------------
* **Explanation**: This error indicates that the validation of the uploaded dar failed.
* **Resolution**: Inspect the error message and contact support.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DAR_VALIDATION_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Validation$$ValidationError$.html>`_


.. _known_dar_version_canton_error_codes:

KNOWN_DAR_VERSION
-----------------
* **Explanation**: This error indicates that the Dar upload failed upgrade checks because a package with the same version and package name has been previously uploaded.
* **Resolution**: Inspect the error message and contact support.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `KNOWN_DAR_VERSION <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Validation$$UpgradeVersion$.html>`_


.. _package_service_internal_error_canton_error_codes:

PACKAGE_SERVICE_INTERNAL_ERROR
------------------------------
* **Explanation**: This error indicates an internal issue within the package service.
* **Resolution**: Inspect the error message and contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `PACKAGE_SERVICE_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$InternalError$.html>`_


.. _shutdown_interrupted_package_vetting_canton_error_codes:

SHUTDOWN_INTERRUPTED_PACKAGE_VETTING
------------------------------------
* **Explanation**: Package vetting has been aborted because the participant is shutting down.
* **Resolution**: Re-submit the vetting request when the participant node is available again.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SHUTDOWN_INTERRUPTED_PACKAGE_VETTING <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$ParticipantShuttingDown$.html>`_


.. _3.2.5.1. reading_canton_error_codes:

3.2.5.1. Reading
================


.. _dar_parse_error_canton_error_codes:

DAR_PARSE_ERROR
---------------
* **Explanation**: This error indicates that the content of the Dar file could not be parsed successfully.
* **Resolution**: Inspect the error message and contact support.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DAR_PARSE_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Reading$$ParseError$.html>`_


.. _invalid_dar_canton_error_codes:

INVALID_DAR
-----------
* **Explanation**: This error indicates that the supplied dar file was invalid.
* **Resolution**: Inspect the error message for details and contact support.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_DAR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Reading$$InvalidDar$.html>`_


.. _invalid_dar_file_name_canton_error_codes:

INVALID_DAR_FILE_NAME
---------------------
* **Explanation**: This error indicates that the supplied dar file name did not meet the requirements to be stored in the persistence store.
* **Resolution**: Inspect error message for details and change the file name accordingly
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_DAR_FILE_NAME <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Reading$$InvalidDarFileName$.html>`_


.. _invalid_legacy_dar_canton_error_codes:

INVALID_LEGACY_DAR
------------------
* **Explanation**: This error indicates that the supplied zipped dar is an unsupported legacy Dar.
* **Resolution**: Please use a more recent dar version.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_LEGACY_DAR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Reading$$InvalidLegacyDar$.html>`_


.. _invalid_zip_entry_canton_error_codes:

INVALID_ZIP_ENTRY
-----------------
* **Explanation**: This error indicates that the supplied zipped dar file was invalid.
* **Resolution**: Inspect the error message for details and contact support.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_ZIP_ENTRY <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Reading$$InvalidZipEntry$.html>`_


.. _zip_bomb_canton_error_codes:

ZIP_BOMB
--------
* **Explanation**: This error indicates that the supplied zipped dar is regarded as zip-bomb.
* **Resolution**: Inspect the dar and contact support.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `ZIP_BOMB <../../canton/scaladoc/com/digitalasset/canton/ledger/error/PackageServiceErrors$$Reading$$ZipBomb$.html>`_


.. _3.2.6. writeservicerejectionerrors_canton_error_codes:

3.2.6. WriteServiceRejectionErrors
==================================


.. _disputed_canton_error_codes:

DISPUTED
--------
* **Explanation**: An invalid transaction submission was not detected by the participant.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `DISPUTED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/WriteServiceRejectionErrors$$Disputed$.html>`_


.. _out_of_quota_canton_error_codes:

OUT_OF_QUOTA
------------
* **Explanation**: The Participant node did not have sufficient resource quota to submit the transaction.
* **Resolution**: Inspect the error message and retry after after correcting the underlying issue.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `OUT_OF_QUOTA <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/WriteServiceRejectionErrors$$OutOfQuota$.html>`_


.. _party_not_known_on_ledger_canton_error_codes:

PARTY_NOT_KNOWN_ON_LEDGER
-------------------------
* **Explanation**: One or more informee parties have not been allocated.
* **Resolution**: Check that all the informee party identifiers are correct, allocate all the informee parties, request their allocation or wait for them to be allocated before retrying the transaction submission.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `PARTY_NOT_KNOWN_ON_LEDGER <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/WriteServiceRejectionErrors$$PartyNotKnownOnLedger$.html>`_


.. _submitter_cannot_act_via_participant_canton_error_codes:

SUBMITTER_CANNOT_ACT_VIA_PARTICIPANT
------------------------------------
* **Explanation**: A submitting party is not authorized to act through the participant.
* **Resolution**: Contact the participant operator or re-submit with an authorized party.
* **Category**: InsufficientPermission
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status PERMISSION_DENIED without any details for security reasons.
* **Scaladocs**: `SUBMITTER_CANNOT_ACT_VIA_PARTICIPANT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/WriteServiceRejectionErrors$$SubmitterCannotActViaParticipant$.html>`_


.. _submitting_party_not_known_on_ledger_canton_error_codes:

SUBMITTING_PARTY_NOT_KNOWN_ON_LEDGER
------------------------------------
* **Explanation**: The submitting party has not been allocated.
* **Resolution**: Check that the party identifier is correct, allocate the submitting party, request its allocation or wait for it to be allocated before retrying the transaction submission.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `SUBMITTING_PARTY_NOT_KNOWN_ON_LEDGER <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/WriteServiceRejectionErrors$$SubmittingPartyNotKnownOnLedger$.html>`_


.. _3.2.6.1. internal_canton_error_codes:

3.2.6.1. Internal
=================


.. _internally_duplicate_keys_canton_error_codes:

INTERNALLY_DUPLICATE_KEYS
-------------------------
* **Explanation**: The participant didn't detect an attempt by the transaction submission to use the same key for two active contracts.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INTERNALLY_DUPLICATE_KEYS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/WriteServiceRejectionErrors$$Internal$$InternallyDuplicateKeys$.html>`_


.. _internally_inconsistent_keys_canton_error_codes:

INTERNALLY_INCONSISTENT_KEYS
----------------------------
* **Explanation**: The participant didn't detect an inconsistent key usage in the transaction. Within the transaction, an exercise, fetch or lookupByKey failed because the mapping of `key -> contract ID` was inconsistent with earlier actions.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INTERNALLY_INCONSISTENT_KEYS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/WriteServiceRejectionErrors$$Internal$$InternallyInconsistentKeys$.html>`_


.. _3.2.7. requestvalidationerrors_canton_error_codes:

3.2.7. RequestValidationErrors
==============================


.. _invalid_argument_canton_error_codes:

INVALID_ARGUMENT
----------------
* **Explanation**: This error is emitted when a submitted ledger API command contains an invalid argument.
* **Resolution**: Inspect the reason given and correct your application.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_ARGUMENT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$InvalidArgument$.html>`_


.. _invalid_deduplication_period_canton_error_codes:

INVALID_DEDUPLICATION_PERIOD
----------------------------
* **Explanation**: This error is emitted when a submitted ledger API command specifies an invalid deduplication period.
* **Resolution**: Inspect the error message, adjust the value of the deduplication period or ask the participant operator to increase the maximum deduplication period.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INVALID_DEDUPLICATION_PERIOD <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$InvalidDeduplicationPeriodField$.html>`_


.. _invalid_field_canton_error_codes:

INVALID_FIELD
-------------
* **Explanation**: This error is emitted when a submitted ledger API command contains a field value that cannot be understood.
* **Resolution**: Inspect the reason given and correct your application.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_FIELD <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$InvalidField$.html>`_


.. _ledger_id_mismatch_canton_error_codes:

LEDGER_ID_MISMATCH
------------------
* **Explanation**: Every ledger API command contains a ledger-id which is verified against the running ledger.      This error indicates that the provided ledger-id does not match the expected one.
* **Resolution**: Ensure that your application is correctly configured to use the correct ledger.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `LEDGER_ID_MISMATCH <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$LedgerIdMismatch$.html>`_


.. _missing_field_canton_error_codes:

MISSING_FIELD
-------------
* **Explanation**: This error is emitted when a mandatory field is not set in a submitted ledger API command.
* **Resolution**: Inspect the reason given and correct your application.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `MISSING_FIELD <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$MissingField$.html>`_


.. _non_hexadecimal_offset_canton_error_codes:

NON_HEXADECIMAL_OFFSET
----------------------
* **Explanation**: The supplied offset could not be converted to a binary offset.
* **Resolution**: Ensure the offset is specified as a hexadecimal string.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `NON_HEXADECIMAL_OFFSET <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$NonHexOffset$.html>`_


.. _offset_after_ledger_end_canton_error_codes:

OFFSET_AFTER_LEDGER_END
-----------------------
* **Explanation**: This rejection is given when a read request uses an offset beyond the current ledger end.
* **Resolution**: Use an offset that is before the ledger end.
* **Category**: InvalidGivenCurrentSystemStateSeekAfterEnd
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status OUT_OF_RANGE including a detailed error message.
* **Scaladocs**: `OFFSET_AFTER_LEDGER_END <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$OffsetAfterLedgerEnd$.html>`_


.. _offset_out_of_range_canton_error_codes:

OFFSET_OUT_OF_RANGE
-------------------
* **Explanation**: This rejection is given when a read request uses an offset invalid in the requests' context.
* **Resolution**: Inspect the error message and use a valid offset.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `OFFSET_OUT_OF_RANGE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$OffsetOutOfRange$.html>`_


.. _participant_pruned_data_accessed_canton_error_codes:

PARTICIPANT_PRUNED_DATA_ACCESSED
--------------------------------
* **Explanation**: This rejection is given when a read request tries to access pruned data.
* **Resolution**: Use an offset that is after the pruning offset.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PARTICIPANT_PRUNED_DATA_ACCESSED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$ParticipantPrunedDataAccessed$.html>`_


.. _3.2.7.1. notfound_canton_error_codes:

3.2.7.1. NotFound
=================


.. _ledger_configuration_not_found_canton_error_codes:

LEDGER_CONFIGURATION_NOT_FOUND
------------------------------
* **Explanation**: The ledger configuration could not be retrieved. This could happen due to incomplete initialization of the participant or due to an internal system error.
* **Resolution**: Contact the participant operator.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `LEDGER_CONFIGURATION_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$NotFound$$LedgerConfiguration$.html>`_


.. _no_templates_for_package_name_and_qualified_name_canton_error_codes:

NO_TEMPLATES_FOR_PACKAGE_NAME_AND_QUALIFIED_NAME
------------------------------------------------
* **Explanation**: The queried type reference for the specified package name and template qualified-name does not reference any template uploaded on this participant
* **Resolution**: Use a template qualified-name referencing already uploaded template-ids or ask the participant operator to upload the necessary packages.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `NO_TEMPLATES_FOR_PACKAGE_NAME_AND_QUALIFIED_NAME <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$NotFound$$NoTemplatesForPackageNameAndQualifiedName$.html>`_


.. _package_names_not_found_canton_error_codes:

PACKAGE_NAMES_NOT_FOUND
-----------------------
* **Explanation**: The queried package names do not match packages uploaded on this participant.
* **Resolution**: Use valid package names or ask the participant operator to upload the necessary packages.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `PACKAGE_NAMES_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$NotFound$$PackageNamesNotFound$.html>`_


.. _package_not_found_canton_error_codes:

PACKAGE_NOT_FOUND
-----------------
* **Explanation**: This rejection is given when a read request tries to access a package which does not exist on the ledger.
* **Resolution**: Use a package id pertaining to a package existing on the ledger.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `PACKAGE_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$NotFound$$Package$.html>`_


.. _templates_or_interfaces_not_found_canton_error_codes:

TEMPLATES_OR_INTERFACES_NOT_FOUND
---------------------------------
* **Explanation**: The queried template or interface ids do not exist.
* **Resolution**: Use valid template or interface ids in your query or ask the participant operator to upload the package containing the necessary interfaces/templates.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `TEMPLATES_OR_INTERFACES_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$NotFound$$TemplateOrInterfaceIdsNotFound$.html>`_


.. _transaction_not_found_canton_error_codes:

TRANSACTION_NOT_FOUND
---------------------
* **Explanation**: The transaction does not exist or the requesting set of parties are not authorized to fetch it.
* **Resolution**: Check the transaction id and verify that the requested transaction is visible to the requesting parties.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `TRANSACTION_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/ledger/error/groups/RequestValidationErrors$$NotFound$$Transaction$.html>`_


.. _3.3. transactionerrorgroup_canton_error_codes:

3.3. TransactionErrorGroup
==========================


.. _3.3.1. transactionroutingerror_canton_error_codes:

3.3.1. TransactionRoutingError
==============================


.. _automatic_transfer_for_transaction_failed_canton_error_codes:

AUTOMATIC_TRANSFER_FOR_TRANSACTION_FAILED
-----------------------------------------
* **Explanation**: This error indicates that the automated transfer could not succeed, as the current topology does not    allow the transfer to complete, mostly due to lack of confirmation permissions of the involved parties.
* **Resolution**: Inspect the message and your topology and ensure appropriate permissions exist.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `AUTOMATIC_TRANSFER_FOR_TRANSACTION_FAILED <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$AutomaticTransferForTransactionFailure$.html>`_


.. _routing_internal_error_canton_error_codes:

ROUTING_INTERNAL_ERROR
----------------------
* **Explanation**: This error indicates an internal error in the Canton domain router.
* **Resolution**: Please contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `ROUTING_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$RoutingInternalError$.html>`_


.. _unable_to_get_topology_snapshot_canton_error_codes:

UNABLE_TO_GET_TOPOLOGY_SNAPSHOT
-------------------------------
* **Explanation**: This error indicates that topology information could not be queried.
* **Resolution**: Check that the participant is connected to the domain.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `UNABLE_TO_GET_TOPOLOGY_SNAPSHOT <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$UnableToQueryTopologySnapshot$.html>`_


.. _3.3.1.1. malformedinputerrors_canton_error_codes:

3.3.1.1. MalformedInputErrors
=============================


.. _disclosed_contract_authentication_failed_canton_error_codes:

DISCLOSED_CONTRACT_AUTHENTICATION_FAILED
----------------------------------------
* **Explanation**: A provided disclosed contract could not be authenticated against the provided contract id.
* **Resolution**: Ensure that disclosed contracts provided with command submission match the original contract creation content as sourced from the Ledger API. If the problem persists, contact the participant operator.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `DISCLOSED_CONTRACT_AUTHENTICATION_FAILED <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$MalformedInputErrors$$DisclosedContractAuthenticationFailed$.html>`_


.. _invalid_disclosed_contract_canton_error_codes:

INVALID_DISCLOSED_CONTRACT
--------------------------
* **Explanation**: A provided disclosed contract could not be processed.
* **Resolution**: Ensure that disclosed contracts provided with command submission have an authenticated contract id (i.e. have been created in participant nodes running Canton protocol version 4 or higher) and match the original contract creation format and content as sourced from the Ledger API. If the problem persists, contact the participant operator.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_DISCLOSED_CONTRACT <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$MalformedInputErrors$$InvalidDisclosedContract$.html>`_


.. _invalid_domain_alias_canton_error_codes:

INVALID_DOMAIN_ALIAS
--------------------
* **Explanation**: The WorkflowID defined in the transaction metadata is not a valid domain alias.
* **Resolution**: Check that the workflow ID (if specified) corresponds to a valid domain alias.     A typical rejection reason is a too-long domain alias. 
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `INVALID_DOMAIN_ALIAS <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$MalformedInputErrors$$InvalidDomainAlias$.html>`_


.. _invalid_domain_id_canton_error_codes:

INVALID_DOMAIN_ID
-----------------
* **Explanation**: The WorkflowID defined in the transaction metadata contains an invalid domain id.
* **Resolution**: Check that the workflow ID (if specified) corresponds to a valid domain ID after the ``domain-id:`` marker string.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `INVALID_DOMAIN_ID <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$MalformedInputErrors$$InvalidDomainId$.html>`_


.. _invalid_party_identifier_canton_error_codes:

INVALID_PARTY_IDENTIFIER
------------------------
* **Explanation**: The given party identifier is not a valid Canton party identifier.
* **Resolution**: Ensure that your commands only refer to correct and valid Canton party identifiers of parties that are properly enabled on the system
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_PARTY_IDENTIFIER <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$MalformedInputErrors$$InvalidPartyIdentifier$.html>`_


.. _invalid_submitter_canton_error_codes:

INVALID_SUBMITTER
-----------------
* **Explanation**: The party defined as a submitter can not be parsed into a valid Canton party.
* **Resolution**: Check that you only use correctly setup party names in your application.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_SUBMITTER <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$MalformedInputErrors$$InvalidSubmitter$.html>`_


.. _3.3.1.2. topologyerrors_canton_error_codes:

3.3.1.2. TopologyErrors
=======================


.. _informees_not_active_canton_error_codes:

INFORMEES_NOT_ACTIVE
--------------------
* **Explanation**: This error indicates that the informees are known, but there is no connected domain on which all the informees are hosted.
* **Resolution**: Ensure that there is such a domain, as Canton requires a domain where all informees are present.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INFORMEES_NOT_ACTIVE <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$InformeesNotActive$.html>`_


.. _not_connected_to_all_contract_domains_canton_error_codes:

NOT_CONNECTED_TO_ALL_CONTRACT_DOMAINS
-------------------------------------
* **Explanation**: This error indicates that the transaction is referring to contracts on domains to which this participant is currently not connected.
* **Resolution**: Check the status of your domain connections.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `NOT_CONNECTED_TO_ALL_CONTRACT_DOMAINS <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$NotConnectedToAllContractDomains$.html>`_


.. _no_common_domain_canton_error_codes:

NO_COMMON_DOMAIN
----------------
* **Explanation**: This error indicates that there is no common domain to which all submitters can submit and all informees are connected.
* **Resolution**: Check that your participant node is connected to all domains you expect and check that the parties are hosted on these domains as you expect them to be.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `NO_COMMON_DOMAIN <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$NoCommonDomain$.html>`_


.. _no_domain_for_submission_canton_error_codes:

NO_DOMAIN_FOR_SUBMISSION
------------------------
* **Explanation**: This error indicates that no valid domain was found for submission.
* **Resolution**: Check the status of your domain connections, that packages are vetted and that you are connected to domains running recent protocol versions.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `NO_DOMAIN_FOR_SUBMISSION <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$NoDomainForSubmission$.html>`_


.. _no_domain_on_which_all_submitters_can_submit_canton_error_codes:

NO_DOMAIN_ON_WHICH_ALL_SUBMITTERS_CAN_SUBMIT
--------------------------------------------
* **Explanation**: This error indicates that a transaction has been sent where the system can not find any active " +      "domain on which this participant can submit in the name of the given set of submitters.
* **Resolution**: Ensure that you are connected to a domain where this participant has submission rights.     Check that you are actually connected to the domains you expect to be connected and check that     your participant node has the submission permission for each submitting party.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `NO_DOMAIN_ON_WHICH_ALL_SUBMITTERS_CAN_SUBMIT <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$NoDomainOnWhichAllSubmittersCanSubmit$.html>`_


.. _submitters_not_active_canton_error_codes:

SUBMITTERS_NOT_ACTIVE
---------------------
* **Explanation**: This error indicates that the submitters are known, but there is no connected domain on which all the submitters are hosted.
* **Resolution**: Ensure that there is such a domain, as Canton requires a domain where all submitters are present.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SUBMITTERS_NOT_ACTIVE <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$SubmittersNotActive$.html>`_


.. _submitter_always_stakeholder_canton_error_codes:

SUBMITTER_ALWAYS_STAKEHOLDER
----------------------------
* **Explanation**: This error indicates that the transaction requires contract transfers for which the submitter must be a stakeholder.
* **Resolution**: Check that your participant node is connected to all domains you expect and check that the parties are hosted on these domains as you expect them to be.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SUBMITTER_ALWAYS_STAKEHOLDER <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$SubmitterAlwaysStakeholder$.html>`_


.. _unknown_contract_domains_canton_error_codes:

UNKNOWN_CONTRACT_DOMAINS
------------------------
* **Explanation**: This error indicates that the transaction is referring to contracts whose domain is not currently known.
* **Resolution**: Ensure all transfer operations on contracts used by the transaction have completed.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `UNKNOWN_CONTRACT_DOMAINS <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$UnknownContractDomains$.html>`_


.. _unknown_informees_canton_error_codes:

UNKNOWN_INFORMEES
-----------------
* **Explanation**: This error indicates that the transaction is referring to some informees that are not known on any connected domain.
* **Resolution**: Check the list of submitted informees and check if your participant is connected to the domains you are expecting it to be.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `UNKNOWN_INFORMEES <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$UnknownInformees$.html>`_


.. _unknown_submitters_canton_error_codes:

UNKNOWN_SUBMITTERS
------------------
* **Explanation**: This error indicates that the transaction is referring to some submitters that are not known on any connected domain.
* **Resolution**: Check the list of provided submitters and check if your participant is connected to the domains you are expecting it to be.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `UNKNOWN_SUBMITTERS <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$TopologyErrors$$UnknownSubmitters$.html>`_


.. _3.3.1.3. configurationerrors_canton_error_codes:

3.3.1.3. ConfigurationErrors
============================


.. _input_contract_has_unauthenticated_id_canton_error_codes:

INPUT_CONTRACT_HAS_UNAUTHENTICATED_ID
-------------------------------------
* **Explanation**: An input contract uses an unauthenticated ID.
* **Resolution**: The presence of contracts with unauthenticated IDs indicates that these contracts have likely been created using an earlier version of Canton. Unauthenticated contract IDs are deprecated as they have security implications, and are no longer allowed by default. In order to still permit the submission of transactions that use them, you must configure the participants with the `allow-for-unauthenticated-contract-ids` flag set to true. See the following point in the documentation:  https://docs.daml.com/canton/usermanual/upgrading.html#test-the-configuration-additional-change-if-you-were-running-protocol-version-3 IMPORTANT: Please note that you MUST set the flag on ALL the participants connected to the domain. Failure to do so will end up in critical failures of the participants. 
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INPUT_CONTRACT_HAS_UNAUTHENTICATED_ID <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$ConfigurationErrors$$InputContractHasUnauthenticatedId$.html>`_


.. _invalid_prescribed_domain_id_canton_error_codes:

INVALID_PRESCRIBED_DOMAIN_ID
----------------------------
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INVALID_PRESCRIBED_DOMAIN_ID <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$ConfigurationErrors$$InvalidPrescribedDomainId$.html>`_


.. _multi_domain_support_not_enabled_canton_error_codes:

MULTI_DOMAIN_SUPPORT_NOT_ENABLED
--------------------------------
* **Explanation**: This error indicates that a transaction has been submitted that requires multi-domain support.     Multi-domain support is a preview feature that needs to be enabled explicitly by configuration.
* **Resolution**: Set canton.features.enable-preview-commands = yes
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `MULTI_DOMAIN_SUPPORT_NOT_ENABLED <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$ConfigurationErrors$$MultiDomainSupportNotEnabled$.html>`_


.. _submission_domain_not_ready_canton_error_codes:

SUBMISSION_DOMAIN_NOT_READY
---------------------------
* **Explanation**: This error indicates that the transaction should be submitted to a domain which is not connected or not configured.
* **Resolution**: Ensure that the domain specified in the workflowId is correctly connected.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `SUBMISSION_DOMAIN_NOT_READY <../../canton/scaladoc/com/digitalasset/canton/participant/sync/TransactionRoutingError$$ConfigurationErrors$$SubmissionDomainNotReady$.html>`_


.. _3.3.2. submissionerrors_canton_error_codes:

3.3.2. SubmissionErrors
=======================


.. _chosen_mediator_is_inactive_canton_error_codes:

CHOSEN_MEDIATOR_IS_INACTIVE
---------------------------
* **Explanation**: The mediator chosen for the transaction got deactivated before the request was sequenced.
* **Resolution**: Resubmit.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `CHOSEN_MEDIATOR_IS_INACTIVE <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$InactiveMediatorError$.html>`_


.. _contract_authentication_failed_canton_error_codes:

CONTRACT_AUTHENTICATION_FAILED
------------------------------
* **Explanation**: At least one of the transaction's input contracts could not be authenticated.
* **Resolution**: Retry the submission with correctly authenticated contracts.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `CONTRACT_AUTHENTICATION_FAILED <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$ContractAuthenticationFailed$.html>`_


.. _domain_backpressure_canton_error_codes:

DOMAIN_BACKPRESSURE
-------------------
* **Explanation**: This error occurs when the sequencer refuses to accept a command due to backpressure.
* **Resolution**: Wait a bit and retry, preferably with some backoff factor.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `DOMAIN_BACKPRESSURE <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$DomainBackpressure$.html>`_


.. _domain_without_mediator_canton_error_codes:

DOMAIN_WITHOUT_MEDIATOR
-----------------------
* **Explanation**: The participant routed the transaction to a domain without an active mediator.
* **Resolution**: Add a mediator to the domain.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `DOMAIN_WITHOUT_MEDIATOR <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$DomainWithoutMediatorError$.html>`_


.. _malformed_request_canton_error_codes:

MALFORMED_REQUEST
-----------------
* **Explanation**: This error has not yet been properly categorised into sub-error codes.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `MALFORMED_REQUEST <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$MalformedRequest$.html>`_


.. _not_sequenced_timeout_canton_error_codes:

NOT_SEQUENCED_TIMEOUT
---------------------
* **Explanation**: This error occurs when the transaction was not sequenced within the pre-defined max-sequencing time and has therefore timed out. The max-sequencing time is derived from the transaction's ledger time via the ledger time model skews. 
* **Resolution**: Resubmit if the delay is caused by high load. If the command requires substantial processing on the participant, specify a higher minimum ledger time with the command submission so that a higher max sequencing time is derived. Alternatively, you can increase the dynamic domain parameter ledgerTimeRecordTimeTolerance. 
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `NOT_SEQUENCED_TIMEOUT <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$TimeoutError$.html>`_


.. _package_not_vetted_by_recipients_canton_error_codes:

PACKAGE_NOT_VETTED_BY_RECIPIENTS
--------------------------------
* **Explanation**: This error occurs if a transaction was submitted referring to a package that a receiving participant has not vetted. Any transaction view can only refer to packages that have explicitly been approved by the receiving participants.
* **Resolution**: Ensure that the receiving participant uploads and vets the respective package.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PACKAGE_NOT_VETTED_BY_RECIPIENTS <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$PackageNotVettedByRecipients$.html>`_


.. _participant_overloaded_canton_error_codes:

PARTICIPANT_OVERLOADED
----------------------
* **Explanation**: The participant has rejected all incoming commands during a configurable grace period.
* **Resolution**: Configure more restrictive resource limits (enterprise only). Change applications to submit commands at a lower rate. Configure a higher value for `myParticipant.parameters.warnIfOverloadedFor`.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `PARTICIPANT_OVERLOADED <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$ParticipantOverloaded$.html>`_


.. _sequencer_request_failed_canton_error_codes:

SEQUENCER_REQUEST_FAILED
------------------------
* **Explanation**: This error occurs when the command cannot be sent to the domain.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `SEQUENCER_REQUEST_FAILED <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$SequencerRequest$.html>`_


.. _submission_during_shutdown_canton_error_codes:

SUBMISSION_DURING_SHUTDOWN
--------------------------
* **Explanation**: This error occurs when a command is submitted while the system is performing a shutdown.
* **Resolution**: Assuming that the participant will restart or failover eventually, retry in a couple of seconds.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `SUBMISSION_DURING_SHUTDOWN <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$SubmissionDuringShutdown$.html>`_


.. _unknown_contract_domain_canton_error_codes:

UNKNOWN_CONTRACT_DOMAIN
-----------------------
* **Explanation**: This error occurs if a transaction was submitted referring to a contract that is not known on the domain. This can occur in case of race conditions between a transaction and an archival or transfer-out.
* **Resolution**: Check domain for submission and/or re-submit the transaction.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `UNKNOWN_CONTRACT_DOMAIN <../../canton/scaladoc/com/digitalasset/canton/participant/protocol/TransactionProcessor$$SubmissionErrors$$UnknownContractDomain$.html>`_


.. _3.3.3. syncserviceinjectionerror_canton_error_codes:

3.3.3. SyncServiceInjectionError
================================


.. _command_injection_failure_canton_error_codes:

COMMAND_INJECTION_FAILURE
-------------------------
* **Explanation**: This errors occurs if an internal error results in an exception.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `COMMAND_INJECTION_FAILURE <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceInjectionError$$InjectionFailure$.html>`_


.. _node_is_passive_replica_canton_error_codes:

NODE_IS_PASSIVE_REPLICA
-----------------------
* **Explanation**: This error results if a command is submitted to the passive replica.
* **Resolution**: Send the command to the active replica.
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `NODE_IS_PASSIVE_REPLICA <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceInjectionError$$PassiveReplica$.html>`_


.. _not_connected_to_any_domain_canton_error_codes:

NOT_CONNECTED_TO_ANY_DOMAIN
---------------------------
* **Explanation**: This errors results if a command is submitted to a participant that is not connected to any domain.
* **Resolution**: Connect your participant to the domain where the given parties are hosted.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `NOT_CONNECTED_TO_ANY_DOMAIN <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceInjectionError$$NotConnectedToAnyDomain$.html>`_


.. _3.3.4. localreject_canton_error_codes:

3.3.4. LocalReject
==================


.. _3.3.4.1. malformedrejects_canton_error_codes:

3.3.4.1. MalformedRejects
=========================


.. _local_verdict_bad_root_hash_messages_canton_error_codes:

LOCAL_VERDICT_BAD_ROOT_HASH_MESSAGES
------------------------------------
* **Explanation**: This rejection is made by a participant if a transaction does not contain valid root hash messages.
* **Resolution**: This indicates a race condition due to a in-flight topology change, or malicious or faulty behaviour.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `LOCAL_VERDICT_BAD_ROOT_HASH_MESSAGES <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$MalformedRejects$$BadRootHashMessages$.html>`_


.. _local_verdict_creates_existing_contracts_canton_error_codes:

LOCAL_VERDICT_CREATES_EXISTING_CONTRACTS
----------------------------------------
* **Explanation**: This error indicates that the transaction would create already existing contracts.
* **Resolution**: This error indicates either faulty or malicious behaviour.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `LOCAL_VERDICT_CREATES_EXISTING_CONTRACTS <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$MalformedRejects$$CreatesExistingContracts$.html>`_


.. _local_verdict_failed_model_conformance_check_canton_error_codes:

LOCAL_VERDICT_FAILED_MODEL_CONFORMANCE_CHECK
--------------------------------------------
* **Explanation**: This rejection is made by a participant if a transaction fails a model conformance check.
* **Resolution**: This indicates either malicious or faulty behaviour.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `LOCAL_VERDICT_FAILED_MODEL_CONFORMANCE_CHECK <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$MalformedRejects$$ModelConformance$.html>`_


.. _local_verdict_malformed_payload_canton_error_codes:

LOCAL_VERDICT_MALFORMED_PAYLOAD
-------------------------------
* **Explanation**: This rejection is made by a participant if a view of the transaction is malformed.
* **Resolution**: This indicates either malicious or faulty behaviour.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `LOCAL_VERDICT_MALFORMED_PAYLOAD <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$MalformedRejects$$Payloads$.html>`_


.. _local_verdict_malformed_request_canton_error_codes:

LOCAL_VERDICT_MALFORMED_REQUEST
-------------------------------
* **Explanation**: This rejection is made by a participant if a request is malformed.
* **Resolution**: Please contact support.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `LOCAL_VERDICT_MALFORMED_REQUEST <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$MalformedRejects$$MalformedRequest$.html>`_


.. _3.3.4.2. consistencyrejections_canton_error_codes:

3.3.4.2. ConsistencyRejections
==============================


.. _local_verdict_duplicate_key_canton_error_codes:

LOCAL_VERDICT_DUPLICATE_KEY
---------------------------
* **Explanation**: If the participant provides unique contract key support,     this error will indicate that a transaction would create a unique key which already exists.
* **Resolution**: It depends on your use case and application whether and when retrying makes sense or not.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_DUPLICATE_KEY <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$ConsistencyRejections$$DuplicateKey$.html>`_


.. _local_verdict_inactive_contracts_canton_error_codes:

LOCAL_VERDICT_INACTIVE_CONTRACTS
--------------------------------
* **Explanation**: The transaction is referring to contracts that have either been previously                 archived, transferred to another domain, or do not exist.
* **Resolution**: Inspect your contract state and try a different transaction.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_INACTIVE_CONTRACTS <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$ConsistencyRejections$$InactiveContracts$.html>`_


.. _local_verdict_inconsistent_key_canton_error_codes:

LOCAL_VERDICT_INCONSISTENT_KEY
------------------------------
* **Explanation**: If the participant provides unique contract key support,     this error will indicate that a transaction expected a key to be unallocated, but a contract for the key already exists.
* **Resolution**: It depends on your use case and application whether and when retrying makes sense or not.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_INCONSISTENT_KEY <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$ConsistencyRejections$$InconsistentKey$.html>`_


.. _local_verdict_locked_contracts_canton_error_codes:

LOCAL_VERDICT_LOCKED_CONTRACTS
------------------------------
* **Explanation**: The transaction is referring to locked contracts which are in the process of being     created, transferred, or archived by another transaction. If the other transaction fails, this transaction could be successfully retried.
* **Resolution**: Retry the transaction
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_LOCKED_CONTRACTS <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$ConsistencyRejections$$LockedContracts$.html>`_


.. _local_verdict_locked_keys_canton_error_codes:

LOCAL_VERDICT_LOCKED_KEYS
-------------------------
* **Explanation**: The transaction is referring to locked keys which are in the process of being     modified by another transaction.
* **Resolution**: Retry the transaction
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_LOCKED_KEYS <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$ConsistencyRejections$$LockedKeys$.html>`_


.. _3.3.4.3. timerejects_canton_error_codes:

3.3.4.3. TimeRejects
====================


.. _local_verdict_ledger_time_out_of_bound_canton_error_codes:

LOCAL_VERDICT_LEDGER_TIME_OUT_OF_BOUND
--------------------------------------
* **Explanation**: This error is thrown if the ledger time and the record time differ more than permitted.     This can happen in an overloaded system due to high latencies or for transactions with long interpretation times.
* **Resolution**: For long-running transactions, specify a ledger time with the command submission or adjust the dynamic domain parameter ledgerTimeRecordTimeTolerance (and possibly the participant and mediator reaction timeout). For short-running transactions, simply retry.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_LEDGER_TIME_OUT_OF_BOUND <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TimeRejects$$LedgerTime$.html>`_


.. _local_verdict_submission_time_out_of_bound_canton_error_codes:

LOCAL_VERDICT_SUBMISSION_TIME_OUT_OF_BOUND
------------------------------------------
* **Explanation**: This error is thrown if the submission time and the record time differ more than permitted.     This can happen in an overloaded system due to high latencies or for transactions with long interpretation times.
* **Resolution**: For long-running transactions, adjust the ledger time bounds used with the command submission. For short-running transactions, simply retry.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_SUBMISSION_TIME_OUT_OF_BOUND <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TimeRejects$$SubmissionTime$.html>`_


.. _local_verdict_timeout_canton_error_codes:

LOCAL_VERDICT_TIMEOUT
---------------------
* **Explanation**: This rejection is sent if the participant locally determined a timeout.
* **Resolution**: In the first instance, resubmit your transaction. If the rejection still appears spuriously, consider increasing the `participantResponseTimeout` or `mediatorReactionTimeout` values in the `DynamicDomainParameters`. If the rejection appears unrelated to timeout settings, validate that the sequencer and mediator function correctly. 
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `LOCAL_VERDICT_TIMEOUT <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TimeRejects$$LocalTimeout$.html>`_


.. _3.3.4.4. transferinrejects_canton_error_codes:

3.3.4.4. TransferInRejects
==========================


.. _transfer_in_already_completed_canton_error_codes:

TRANSFER_IN_ALREADY_COMPLETED
-----------------------------
* **Explanation**: This rejection is emitted by a participant if a transfer-in has already been completed.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `TRANSFER_IN_ALREADY_COMPLETED <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TransferInRejects$$AlreadyCompleted$.html>`_


.. _transfer_in_contract_already_active_canton_error_codes:

TRANSFER_IN_CONTRACT_ALREADY_ACTIVE
-----------------------------------
* **Explanation**: This rejection is emitted by a participant if a transfer-in has already been made by another entity.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `TRANSFER_IN_CONTRACT_ALREADY_ACTIVE <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TransferInRejects$$ContractAlreadyActive$.html>`_


.. _transfer_in_contract_already_archived_canton_error_codes:

TRANSFER_IN_CONTRACT_ALREADY_ARCHIVED
-------------------------------------
* **Explanation**: This rejection is emitted by a participant if a transfer would be invoked on an already archived contract.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `TRANSFER_IN_CONTRACT_ALREADY_ARCHIVED <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TransferInRejects$$ContractAlreadyArchived$.html>`_


.. _transfer_in_contract_is_locked_canton_error_codes:

TRANSFER_IN_CONTRACT_IS_LOCKED
------------------------------
* **Explanation**: This rejection is emitted by a participant if a transfer-in is referring to an already locked contract.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `TRANSFER_IN_CONTRACT_IS_LOCKED <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TransferInRejects$$ContractIsLocked$.html>`_


.. _3.3.4.5. transferoutrejects_canton_error_codes:

3.3.4.5. TransferOutRejects
===========================


.. _transfer_out_activeness_check_failed_canton_error_codes:

TRANSFER_OUT_ACTIVENESS_CHECK_FAILED
------------------------------------
* **Explanation**: Activeness check failed for transfer out submission. This rejection occurs if the contract to be transferred has already been transferred or is currently locked (due to a competing transaction) on domain.
* **Resolution**: Depending on your use-case and your expectation, retry the transaction.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `TRANSFER_OUT_ACTIVENESS_CHECK_FAILED <../../canton/scaladoc/com/digitalasset/canton/protocol/messages/LocalReject$$TransferOutRejects$$ActivenessCheckFailed$.html>`_


.. _3.3.5. commanddeduplicationerror_canton_error_codes:

3.3.5. CommandDeduplicationError
================================


.. _malformed_deduplication_offset_canton_error_codes:

MALFORMED_DEDUPLICATION_OFFSET
------------------------------
* **Explanation**: The specified deduplication offset is syntactically malformed.
* **Resolution**: Use a deduplication offset that was produced by this participant node.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `MALFORMED_DEDUPLICATION_OFFSET <../../canton/scaladoc/com/digitalasset/canton/participant/sync/CommandDeduplicationError$$MalformedDeduplicationOffset$.html>`_


.. _3.4. syncserviceerror_canton_error_codes:

3.4. SyncServiceError
=====================


.. _party_allocation_without_connected_domain_canton_error_codes:

PARTY_ALLOCATION_WITHOUT_CONNECTED_DOMAIN
-----------------------------------------
* **Explanation**: The participant is not connected to a domain and can therefore not allocate a party   because the party notification is configured as ``party-notification.type = via-domain``.
* **Resolution**: Connect the participant to a domain first or change the participant's party notification config to ``eager``.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PARTY_ALLOCATION_WITHOUT_CONNECTED_DOMAIN <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$PartyAllocationNoDomainError$.html>`_


.. _sync_service_alarm_canton_error_codes:

SYNC_SERVICE_ALARM
------------------
* **Explanation**: The participant has detected that another node is behaving maliciously.
* **Resolution**: Contact support.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `SYNC_SERVICE_ALARM <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceAlarm$.html>`_


.. _sync_service_already_added_canton_error_codes:

SYNC_SERVICE_ALREADY_ADDED
--------------------------
* **Explanation**: This error results on an attempt to register a new domain under an alias already in use.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_ALREADY_ADDED <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceAlreadyAdded$.html>`_


.. _sync_service_domain_became_passive_canton_error_codes:

SYNC_SERVICE_DOMAIN_BECAME_PASSIVE
----------------------------------
* **Explanation**: This error is logged when a sync domain is disconnected because the participant became passive.
* **Resolution**: Fail over to the active participant replica.
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_DOMAIN_BECAME_PASSIVE <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceDomainBecamePassive$.html>`_


.. _sync_service_domain_disabled_us_canton_error_codes:

SYNC_SERVICE_DOMAIN_DISABLED_US
-------------------------------
* **Explanation**: This error is logged when the synchronization service shuts down because the remote domain has disabled this participant.
* **Resolution**: Contact the domain operator and inquire why you have been booted out.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_DOMAIN_DISABLED_US <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceDomainDisabledUs$.html>`_


.. _sync_service_domain_disconnected_canton_error_codes:

SYNC_SERVICE_DOMAIN_DISCONNECTED
--------------------------------
* **Explanation**: This error is logged when a sync domain is unexpectedly disconnected from the Canton sync service (after having previously been connected)
* **Resolution**: Please contact support and provide the failure reason.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `SYNC_SERVICE_DOMAIN_DISCONNECTED <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceDomainDisconnect$.html>`_


.. _sync_service_domain_must_be_offline_canton_error_codes:

SYNC_SERVICE_DOMAIN_MUST_BE_OFFLINE
-----------------------------------
* **Explanation**: This error is emitted when an operation is attempted such as repair that requires the domain connection to be disconnected and clean.
* **Resolution**: Disconnect the domain before attempting the command.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_DOMAIN_MUST_BE_OFFLINE <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceDomainMustBeOffline$.html>`_


.. _sync_service_domain_must_not_have_in_flight_transactions_canton_error_codes:

SYNC_SERVICE_DOMAIN_MUST_NOT_HAVE_IN_FLIGHT_TRANSACTIONS
--------------------------------------------------------
* **Explanation**: This error is emitted when a domain migration is attempted while transactions are still in-flight on the source domain.
* **Resolution**: Ensure the source domain has no in-flight transactions by reconnecting participants to the source domain, halting activity on the participants and waiting for in-flight transactions to complete or time out. Afterwards invoke `migrate_domain` again. As a last resort, you may force the domain migration ignoring in-flight transactions using the `force` flag on the command. Be advised, forcing a migration may lead to a ledger fork.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_DOMAIN_MUST_NOT_HAVE_IN_FLIGHT_TRANSACTIONS <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceDomainMustNotHaveInFlightTransactions$.html>`_


.. _sync_service_domain_status_must_be_inactive_canton_error_codes:

SYNC_SERVICE_DOMAIN_STATUS_MUST_BE_INACTIVE
-------------------------------------------
* **Explanation**: This error is logged when a sync domain is not inactive.
* **Resolution**: If you attempt to purge a domain that has not been deactivated, this error will be emitted. Please ensure that the specified domain has a status of `Inactive` before attempting to purge it.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_DOMAIN_STATUS_MUST_BE_INACTIVE <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceDomainStatusMustBeInactive$.html>`_


.. _sync_service_domain_status_not_active_canton_error_codes:

SYNC_SERVICE_DOMAIN_STATUS_NOT_ACTIVE
-------------------------------------
* **Explanation**: This error is logged when a sync domain has a non-active status.
* **Resolution**: If you attempt to connect to a domain that has either been migrated off or has a pending migration, this error will be emitted. Please complete the migration before attempting to connect to it.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_DOMAIN_STATUS_NOT_ACTIVE <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceDomainIsNotActive$.html>`_


.. _sync_service_internal_error_canton_error_codes:

SYNC_SERVICE_INTERNAL_ERROR
---------------------------
* **Explanation**: This error indicates an internal issue.
* **Resolution**: Please contact support and provide the failure reason.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `SYNC_SERVICE_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceInternalError$.html>`_


.. _sync_service_unknown_domain_canton_error_codes:

SYNC_SERVICE_UNKNOWN_DOMAIN
---------------------------
* **Explanation**: This error results if a domain connectivity command is referring to a domain alias that has not been registered.
* **Resolution**: Please confirm the domain alias is correct, or configure the domain before (re)connecting.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `SYNC_SERVICE_UNKNOWN_DOMAIN <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncServiceError$$SyncServiceUnknownDomain$.html>`_


.. _3.4.1. syncdomainmigrationerror_canton_error_codes:

3.4.1. SyncDomainMigrationError
===============================


.. _broken_domain_migration_canton_error_codes:

BROKEN_DOMAIN_MIGRATION
-----------------------
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `BROKEN_DOMAIN_MIGRATION <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncDomainMigrationError$$InternalError$.html>`_


.. _invalid_domain_migration_request_canton_error_codes:

INVALID_DOMAIN_MIGRATION_REQUEST
--------------------------------
* **Explanation**: This error results when invalid arguments are passed to the migration command.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INVALID_DOMAIN_MIGRATION_REQUEST <../../canton/scaladoc/com/digitalasset/canton/participant/sync/SyncDomainMigrationError$$InvalidArgument$.html>`_


.. _3.4.2. domainregistryerror_canton_error_codes:

3.4.2. DomainRegistryError
==========================


.. _domain_registry_internal_error_canton_error_codes:

DOMAIN_REGISTRY_INTERNAL_ERROR
------------------------------
* **Explanation**: This error indicates that there has been an internal error noticed by Canton.
* **Resolution**: Contact support and provide the failure reason.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `DOMAIN_REGISTRY_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$DomainRegistryInternalError$.html>`_


.. _topology_conversion_error_canton_error_codes:

TOPOLOGY_CONVERSION_ERROR
-------------------------
* **Explanation**: This error indicates that there was an error converting topology transactions during connecting to a domain.
* **Resolution**: Contact the operator of the topology management for this node.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `TOPOLOGY_CONVERSION_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$TopologyConversionError$.html>`_


.. _3.4.2.1. configurationerrors_canton_error_codes:

3.4.2.1. ConfigurationErrors
============================


.. _cannot_issue_domain_trust_certificate_canton_error_codes:

CANNOT_ISSUE_DOMAIN_TRUST_CERTIFICATE
-------------------------------------
* **Explanation**: This error indicates that the participant can not issue a domain trust certificate. Such a certificate is necessary to become active on a domain. Therefore, it must be present in the authorized store of the participant topology manager.
* **Resolution**: Manually upload a valid domain trust certificate for the given domain or upload the necessary certificates such that participant can issue such certificates automatically.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `CANNOT_ISSUE_DOMAIN_TRUST_CERTIFICATE <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConfigurationErrors$$CanNotIssueDomainTrustCertificate$.html>`_


.. _domain_parameters_changed_canton_error_codes:

DOMAIN_PARAMETERS_CHANGED
-------------------------
* **Explanation**: Error indicating that the domain parameters have been changed, while this isn't supported yet.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DOMAIN_PARAMETERS_CHANGED <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConfigurationErrors$$DomainParametersChanged$.html>`_


.. _incompatible_unique_contract_keys_mode_canton_error_codes:

INCOMPATIBLE_UNIQUE_CONTRACT_KEYS_MODE
--------------------------------------
* **Explanation**: This error indicates that the domain this participant is trying to connect to is a domain where unique     contract keys are supported, while this participant is already connected to other domains. Multiple domains and     unique contract keys are mutually exclusive features.
* **Resolution**: Use isolated participants for domains that require unique keys.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INCOMPATIBLE_UNIQUE_CONTRACT_KEYS_MODE <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConfigurationErrors$$IncompatibleUniqueContractKeysMode$.html>`_


.. _invalid_domain_connection_canton_error_codes:

INVALID_DOMAIN_CONNECTION
-------------------------
* **Explanation**: This error indicates there is a validation error with the configured connections for the domain
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INVALID_DOMAIN_CONNECTION <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConfigurationErrors$$InvalidDomainConnections$.html>`_


.. _misconfigured_static_domain_parameters_canton_error_codes:

MISCONFIGURED_STATIC_DOMAIN_PARAMETERS
--------------------------------------
* **Explanation**: This error indicates that the participant is configured to connect to multiple domain sequencers but their static domain parameters are different from other sequencers.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `MISCONFIGURED_STATIC_DOMAIN_PARAMETERS <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConfigurationErrors$$MisconfiguredStaticDomainParameters$.html>`_


.. _sequencers_from_different_domains_are_configured_canton_error_codes:

SEQUENCERS_FROM_DIFFERENT_DOMAINS_ARE_CONFIGURED
------------------------------------------------
* **Explanation**: This error indicates that the participant is configured to connect to multiple domain sequencers from different domains.
* **Resolution**: Carefully verify the connection settings.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCERS_FROM_DIFFERENT_DOMAINS_ARE_CONFIGURED <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConfigurationErrors$$SequencersFromDifferentDomainsAreConfigured$.html>`_


.. _3.4.2.2. handshakeerrors_canton_error_codes:

3.4.2.2. HandshakeErrors
========================


.. _domain_alias_duplication_canton_error_codes:

DOMAIN_ALIAS_DUPLICATION
------------------------
* **Explanation**: This error indicates that the domain alias was previously used to     connect to a domain with a different domain id. This is a known situation when an existing participant     is trying to connect to a freshly re-initialised domain.
* **Resolution**: Carefully verify the connection settings.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DOMAIN_ALIAS_DUPLICATION <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$HandshakeErrors$$DomainAliasDuplication$.html>`_


.. _domain_crypto_handshake_failed_canton_error_codes:

DOMAIN_CRYPTO_HANDSHAKE_FAILED
------------------------------
* **Explanation**: This error indicates that the domain is using crypto settings which are                 either not supported or not enabled on this participant.
* **Resolution**: Consult the error message and adjust the supported crypto schemes of this participant.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DOMAIN_CRYPTO_HANDSHAKE_FAILED <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$HandshakeErrors$$DomainCryptoHandshakeFailed$.html>`_


.. _domain_handshake_failed_canton_error_codes:

DOMAIN_HANDSHAKE_FAILED
-----------------------
* **Explanation**: This error indicates that the participant to domain handshake has failed.
* **Resolution**: Inspect the provided reason for more details and contact support.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DOMAIN_HANDSHAKE_FAILED <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$HandshakeErrors$$HandshakeFailed$.html>`_


.. _domain_id_mismatch_canton_error_codes:

DOMAIN_ID_MISMATCH
------------------
* **Explanation**: This error indicates that the domain-id does not match the one that the     participant expects. If this error happens on a first connect, then the domain id     defined in the domain connection settings does not match the remote domain.     If this happens on a reconnect, then the remote domain has been reset for some reason.
* **Resolution**: Carefully verify the connection settings.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DOMAIN_ID_MISMATCH <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$HandshakeErrors$$DomainIdMismatch$.html>`_


.. _service_agreement_acceptance_failed_canton_error_codes:

SERVICE_AGREEMENT_ACCEPTANCE_FAILED
-----------------------------------
* **Explanation**: This error indicates that the domain requires the participant to accept a                 service agreement before connecting to it.
* **Resolution**: Use the commands $participant.domains.get_agreement and $participant.domains.accept_agreement to accept the agreement.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SERVICE_AGREEMENT_ACCEPTANCE_FAILED <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$HandshakeErrors$$ServiceAgreementAcceptanceFailed$.html>`_


.. _3.4.2.3. connectionerrors_canton_error_codes:

3.4.2.3. ConnectionErrors
=========================


.. _domain_is_not_available_canton_error_codes:

DOMAIN_IS_NOT_AVAILABLE
-----------------------
* **Explanation**: This error results if the GRPC connection to the domain service fails with GRPC status UNAVAILABLE.
* **Resolution**: Check your connection settings and ensure that the domain can really be reached.
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `DOMAIN_IS_NOT_AVAILABLE <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConnectionErrors$$DomainIsNotAvailable$.html>`_


.. _failed_to_connect_to_sequencer_canton_error_codes:

FAILED_TO_CONNECT_TO_SEQUENCER
------------------------------
* **Explanation**: This error indicates that the participant failed to connect to the sequencer.
* **Resolution**: Inspect the provided reason.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `FAILED_TO_CONNECT_TO_SEQUENCER <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConnectionErrors$$FailedToConnectToSequencer$.html>`_


.. _failed_to_connect_to_sequencers_canton_error_codes:

FAILED_TO_CONNECT_TO_SEQUENCERS
-------------------------------
* **Explanation**: This error indicates that the participant failed to connect to the sequencers.
* **Resolution**: Inspect the provided reason.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `FAILED_TO_CONNECT_TO_SEQUENCERS <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConnectionErrors$$FailedToConnectToSequencers$.html>`_


.. _grpc_connection_failure_canton_error_codes:

GRPC_CONNECTION_FAILURE
-----------------------
* **Explanation**: This error indicates that the participant failed to connect due to a general GRPC error.
* **Resolution**: Inspect the provided reason and contact support.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `GRPC_CONNECTION_FAILURE <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConnectionErrors$$GrpcFailure$.html>`_


.. _participant_is_not_active_canton_error_codes:

PARTICIPANT_IS_NOT_ACTIVE
-------------------------
* **Explanation**: This error indicates that the connecting participant has either not yet been activated by the domain operator.     If the participant was previously successfully connected to the domain, then this error indicates that the domain     operator has deactivated the participant.
* **Resolution**: Contact the domain operator and inquire the permissions your participant node has on the given domain.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PARTICIPANT_IS_NOT_ACTIVE <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainRegistryError$$ConnectionErrors$$ParticipantIsNotActive$.html>`_


.. _3.5. adminworkflowservices_canton_error_codes:

3.5. AdminWorkflowServices
==========================


.. _can_not_automatically_vet_admin_workflow_package_canton_error_codes:

CAN_NOT_AUTOMATICALLY_VET_ADMIN_WORKFLOW_PACKAGE
------------------------------------------------
* **Explanation**: This error indicates that the admin workflow package could not be vetted. The admin workflows is a set of packages that are pre-installed and can be used for administrative processes. The error can happen if the participant is initialised manually but is missing the appropriate signing keys or certificates in order to issue new topology transactions within the participants namespace. The admin workflows can not be used until the participant has vetted the package.
* **Resolution**: This error can be fixed by ensuring that an appropriate vetting transaction is issued in the name of this participant and imported into this participant node. If the corresponding certificates have been added after the participant startup, then this error can be fixed by either restarting the participant node, issuing the vetting transaction manually or re-uploading the Dar (leaving the vetAllPackages argument as true)
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `CAN_NOT_AUTOMATICALLY_VET_ADMIN_WORKFLOW_PACKAGE <../../canton/scaladoc/com/digitalasset/canton/participant/admin/AdminWorkflowServices$$CanNotAutomaticallyVetAdminWorkflowPackage$.html>`_


.. _3.6. repairserviceerror_canton_error_codes:

3.6. RepairServiceError
=======================


.. _contract_purge_error_canton_error_codes:

CONTRACT_PURGE_ERROR
--------------------
* **Explanation**: A contract cannot be purged due to an error.
* **Resolution**: Retry after operator intervention.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `CONTRACT_PURGE_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$ContractPurgeError$.html>`_


.. _contract_serialization_error_canton_error_codes:

CONTRACT_SERIALIZATION_ERROR
----------------------------
* **Explanation**: A contract cannot be serialized due to an error.
* **Resolution**: Retry after operator intervention.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `CONTRACT_SERIALIZATION_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$SerializationError$.html>`_


.. _import_acs_error_canton_error_codes:

IMPORT_ACS_ERROR
----------------
* **Explanation**: Import Acs has failed.
* **Resolution**: Retry after operator intervention.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `IMPORT_ACS_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$ImportAcsError$.html>`_


.. _inconsistent_acs_snapshot_canton_error_codes:

INCONSISTENT_ACS_SNAPSHOT
-------------------------
* **Explanation**: The ACS snapshot cannot be returned because it contains inconsistencies. This is likely due to the request happening concurrently with pruning.
* **Resolution**: Retry the operation
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `INCONSISTENT_ACS_SNAPSHOT <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$InconsistentAcsSnapshot$.html>`_


.. _invalid_acs_snapshot_timestamp_canton_error_codes:

INVALID_ACS_SNAPSHOT_TIMESTAMP
------------------------------
* **Explanation**: The participant does not support serving an ACS snapshot at the requested timestamp, likely because some concurrent processing has not yet finished.
* **Resolution**: Make sure that the specified timestamp has been obtained from the participant in some way. If so, retry after a bit (possibly repeatedly).
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `INVALID_ACS_SNAPSHOT_TIMESTAMP <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$InvalidAcsSnapshotTimestamp$.html>`_


.. _invalid_argument_repair_canton_error_codes:

INVALID_ARGUMENT_REPAIR
-----------------------
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_ARGUMENT_REPAIR <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$InvalidArgument$.html>`_


.. _unavailable_acs_snapshot_canton_error_codes:

UNAVAILABLE_ACS_SNAPSHOT
------------------------
* **Explanation**: The participant does not support serving an ACS snapshot at the requested timestamp because its database has already been pruned, e.g., by the continuous background pruning process.
* **Resolution**: The snapshot at the requested timestamp is no longer available. Pick a more recent timestamp if possible.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `UNAVAILABLE_ACS_SNAPSHOT <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$UnavailableAcsSnapshot$.html>`_


.. _unsupported_protocol_version_participant_canton_error_codes:

UNSUPPORTED_PROTOCOL_VERSION_PARTICIPANT
----------------------------------------
* **Explanation**: The participant does not support the requested protocol version.
* **Resolution**: Specify a protocol version that the participant supports or upgrade the participant to a release that supports the requested protocol version.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `UNSUPPORTED_PROTOCOL_VERSION_PARTICIPANT <../../canton/scaladoc/com/digitalasset/canton/participant/admin/repair/RepairServiceError$$UnsupportedProtocolVersionParticipant$.html>`_


.. _3.7. cantonpackageserviceerror_canton_error_codes:

3.7. CantonPackageServiceError
==============================


.. _dar_not_found_canton_error_codes:

DAR_NOT_FOUND
-------------
* **Explanation**: The hash specified in the request does not match a DAR stored on the participant.
* **Resolution**: Check the provided hash and re-try the operation.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `DAR_NOT_FOUND <../../canton/scaladoc/com/digitalasset/canton/participant/admin/CantonPackageServiceError$$DarNotFound$.html>`_


.. _package_missing_dependencies_canton_error_codes:

PACKAGE_MISSING_DEPENDENCIES
----------------------------
* **Explanation**: An operation could not be executed due to a missing package dependency.
* **Resolution**: Fix the broken dependency state by re-uploading the missing package and retry the operation.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `PACKAGE_MISSING_DEPENDENCIES <../../canton/scaladoc/com/digitalasset/canton/participant/admin/CantonPackageServiceError$$PackageMissingDependencies$.html>`_


.. _package_or_dar_removal_error_canton_error_codes:

PACKAGE_OR_DAR_REMOVAL_ERROR
----------------------------
* **Explanation**: Errors raised by the Package Service on package removal.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PACKAGE_OR_DAR_REMOVAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/admin/CantonPackageServiceError$$PackageRemovalErrorCode$.html>`_


.. _3.8. ledgerapierrors_canton_error_codes:

3.8. LedgerApiErrors
====================


.. _heap_memory_over_limit_canton_error_codes:

HEAP_MEMORY_OVER_LIMIT
----------------------
* **Explanation**: This error happens when the JVM heap memory pool exceeds a pre-configured limit.
* **Resolution**: The following actions can be taken: 1. Review the historical use of heap space by inspecting the metric given in the message. 2. Review the current heap space limits configured in the rate limiting configuration. 3. Try to space out requests that are likely to require a large amount of memory to process.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `HEAP_MEMORY_OVER_LIMIT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/LedgerApiErrors$$HeapMemoryOverLimit$.html>`_


.. _ledger_api_internal_error_canton_error_codes:

LEDGER_API_INTERNAL_ERROR
-------------------------
* **Explanation**: This error occurs if there was an unexpected error in the Ledger API.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `LEDGER_API_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/LedgerApiErrors$$InternalError$.html>`_


.. _maximum_number_of_streams_canton_error_codes:

MAXIMUM_NUMBER_OF_STREAMS
-------------------------
* **Explanation**: This error happens when the number of concurrent gRPC streaming requests exceeds the configured limit.
* **Resolution**: The following actions can be taken: 1. Review the historical need for concurrent streaming by inspecting the metric given in the message. 2. Review the maximum streams limit configured in the rate limiting configuration. 3. Try to space out streaming requests such that they do not need to run in parallel with each other.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `MAXIMUM_NUMBER_OF_STREAMS <../../canton/scaladoc/com/digitalasset/canton/ledger/error/LedgerApiErrors$$MaximumNumberOfStreams$.html>`_


.. _participant_backpressure_canton_error_codes:

PARTICIPANT_BACKPRESSURE
------------------------
* **Explanation**: This error occurs when a participant rejects a command due to excessive load. Load can be caused by the following factors: 1. when commands are submitted to the participant through its Ledger API, 2. when the participant receives requests from other participants through a connected domain.
* **Resolution**: Wait a bit and retry, preferably with some backoff factor. If possible, ask other participants to send fewer requests; the domain operator can enforce this by imposing a rate limit.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `PARTICIPANT_BACKPRESSURE <../../canton/scaladoc/com/digitalasset/canton/ledger/error/LedgerApiErrors$$ParticipantBackpressure$.html>`_


.. _threadpool_overloaded_canton_error_codes:

THREADPOOL_OVERLOADED
---------------------
* **Explanation**: This happens when the rate of submitted gRPC requests requires more CPU or database power than is available.
* **Resolution**: The following actions can be taken: Here the 'queue size' for the threadpool is considered as reported by the executor itself. 1. Review the historical 'queue size' growth by inspecting the metric given in the message. 2. Review the maximum 'queue size' limits configured in the rate limiting configuration. 3. Try to space out requests that are likely to require a lot of CPU or database power.   
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `THREADPOOL_OVERLOADED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/LedgerApiErrors$$ThreadpoolOverloaded$.html>`_


.. _3.9. indexerrors_canton_error_codes:

3.9. IndexErrors
================


.. _3.9.1. databaseerrors_canton_error_codes:

3.9.1. DatabaseErrors
=====================


.. _index_db_invalid_result_set_canton_error_codes:

INDEX_DB_INVALID_RESULT_SET
---------------------------
* **Explanation**: This error occurs if the result set returned by a query against the Index database is invalid.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INDEX_DB_INVALID_RESULT_SET <../../canton/scaladoc/com/digitalasset/canton/ledger/error/IndexErrors$$DatabaseErrors$$ResultSetError$.html>`_


.. _index_db_sql_non_transient_error_canton_error_codes:

INDEX_DB_SQL_NON_TRANSIENT_ERROR
--------------------------------
* **Explanation**: This error occurs if a non-transient error arises when executing a query against the index database.
* **Resolution**: Contact the participant operator.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INDEX_DB_SQL_NON_TRANSIENT_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/IndexErrors$$DatabaseErrors$$SqlNonTransientError$.html>`_


.. _index_db_sql_transient_error_canton_error_codes:

INDEX_DB_SQL_TRANSIENT_ERROR
----------------------------
* **Explanation**: This error occurs if a transient error arises when executing a query against the index database.
* **Resolution**: Re-submit the request.
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `INDEX_DB_SQL_TRANSIENT_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/IndexErrors$$DatabaseErrors$$SqlTransientError$.html>`_


.. _3.10. pruningserviceerror_canton_error_codes:

3.10. PruningServiceError
=========================


.. _internal_pruning_error_canton_error_codes:

INTERNAL_PRUNING_ERROR
----------------------
* **Explanation**: Pruning has failed because of an internal server error.
* **Resolution**: Identify the error in the server log.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `INTERNAL_PRUNING_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/PruningServiceError$$InternalServerError$.html>`_


.. _non_canton_offset_canton_error_codes:

NON_CANTON_OFFSET
-----------------
* **Explanation**: The supplied offset has an unexpected lengths.
* **Resolution**: Ensure the offset has originated from this participant and is 9 bytes in length.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `NON_CANTON_OFFSET <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/PruningServiceError$$NonCantonOffset$.html>`_


.. _no_internal_participant_data_before_canton_error_codes:

NO_INTERNAL_PARTICIPANT_DATA_BEFORE
-----------------------------------
* **Explanation**: The participant does not hold internal ledger state up to and including the specified time and offset.
* **Resolution**: The participant holds no internal ledger data before or at the time and offset specified as parameters to `find_safe_offset`. Typically this means that the participant has already pruned all internal data up to the specified time and offset. Accordingly this error indicates that no safe offset to prune could be located prior.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `NO_INTERNAL_PARTICIPANT_DATA_BEFORE <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/PruningServiceError$$NoInternalParticipantDataBefore$.html>`_


.. _pruning_not_supported_in_community_edition_canton_error_codes:

PRUNING_NOT_SUPPORTED_IN_COMMUNITY_EDITION
------------------------------------------
* **Explanation**: Pruning is not supported in the Community Edition.
* **Resolution**: Upgrade to the Enterprise Edition.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PRUNING_NOT_SUPPORTED_IN_COMMUNITY_EDITION <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/PruningServiceError$$PruningNotSupportedInCommunityEdition$.html>`_


.. _shutdown_interrupted_pruning_canton_error_codes:

SHUTDOWN_INTERRUPTED_PRUNING
----------------------------
* **Explanation**: Pruning has been aborted because the participant is shutting down.
* **Resolution**: After the participant is restarted, the participant ensures that it is in a consistent state. Therefore no intervention is necessary. After the restart, pruning can be invoked again as usual to prune the participant up to the desired offset.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SHUTDOWN_INTERRUPTED_PRUNING <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/PruningServiceError$$ParticipantShuttingDown$.html>`_


.. _unsafe_to_prune_canton_error_codes:

UNSAFE_TO_PRUNE
---------------
* **Explanation**: Pruning is not possible at the specified offset at the current time.
* **Resolution**: Specify a lower offset or retry pruning after a while. Generally, you can only prune    older events. In particular, the events must be older than the sum of mediator reaction timeout    and participant timeout for every domain. And, you can only prune events that are older than the    deduplication time configured for this participant.    Therefore, if you observe this error, you either just prune older events or you adjust the settings    for this participant.    The error details field `safe_offset` contains the highest offset that can currently be pruned, if any.    
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `UNSAFE_TO_PRUNE <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/PruningServiceError$$UnsafeToPrune$.html>`_


.. _3.11. participantreplicationserviceerror_canton_error_codes:

3.11. ParticipantReplicationServiceError
========================================


.. _participant_replication_internal_error_canton_error_codes:

PARTICIPANT_REPLICATION_INTERNAL_ERROR
--------------------------------------
* **Explanation**: Internal error emitted upon internal participant replication errors
* **Resolution**: Contact support
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `PARTICIPANT_REPLICATION_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/ParticipantReplicationServiceError$$InternalError$.html>`_


.. _participant_replication_not_supported_by_storage_canton_error_codes:

PARTICIPANT_REPLICATION_NOT_SUPPORTED_BY_STORAGE
------------------------------------------------
* **Explanation**: Error emitted if the supplied storage configuration does not support replication.
* **Resolution**: Use a participant storage backend supporting replication.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PARTICIPANT_REPLICATION_NOT_SUPPORTED_BY_STORAGE <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/ParticipantReplicationServiceError$$UnsupportedConfig$.html>`_


.. _3.12. commonerrors_canton_error_codes:

3.12. CommonErrors
==================


.. _request_deadline_exceeded_canton_error_codes:

REQUEST_DEADLINE_EXCEEDED
-------------------------
* **Explanation**: The request has not been submitted for processing as its predefined deadline has expired.
* **Resolution**: Retry the request with a greater deadline.
* **Category**: DeadlineExceededRequestStateUnknown
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status DEADLINE_EXCEEDED including a detailed error message.
* **Scaladocs**: `REQUEST_DEADLINE_EXCEEDED <../../canton/scaladoc/com/digitalasset/canton/ledger/error/CommonErrors$$RequestDeadlineExceeded$.html>`_


.. _request_time_out_canton_error_codes:

REQUEST_TIME_OUT
----------------
* **Explanation**: This rejection is given when a request processing status is not known and a time-out is reached.
* **Resolution**: Retry for transient problems. If non-transient contact the operator as the time-out limit might be too short.
* **Category**: DeadlineExceededRequestStateUnknown
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status DEADLINE_EXCEEDED including a detailed error message.
* **Scaladocs**: `REQUEST_TIME_OUT <../../canton/scaladoc/com/digitalasset/canton/ledger/error/CommonErrors$$RequestTimeOut$.html>`_


.. _server_is_shutting_down_canton_error_codes:

SERVER_IS_SHUTTING_DOWN
-----------------------
* **Explanation**: This rejection is given when the participant node is shutting down.
* **Resolution**: Retry the request against an active and available node or contact the participant operator if the error is unexpected.
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `SERVER_IS_SHUTTING_DOWN <../../canton/scaladoc/com/digitalasset/canton/ledger/error/CommonErrors$$ServerIsShuttingDown$.html>`_


.. _service_internal_error_canton_error_codes:

SERVICE_INTERNAL_ERROR
----------------------
* **Explanation**: This error occurs if one of the services encountered an unexpected exception.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `SERVICE_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/ledger/error/CommonErrors$$ServiceInternalError$.html>`_


.. _service_not_running_canton_error_codes:

SERVICE_NOT_RUNNING
-------------------
* **Explanation**: This rejection is given when the requested service is not running. It has not started or has already been shut down.
* **Resolution**: Retry re-submitting the request. If the error persists, contact the participant operator.
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `SERVICE_NOT_RUNNING <../../canton/scaladoc/com/digitalasset/canton/ledger/error/CommonErrors$$ServiceNotRunning$.html>`_


.. _unsupported_operation_canton_error_codes:

UNSUPPORTED_OPERATION
---------------------
* **Explanation**: This error category is used to signal that an unimplemented code-path has been triggered by a client or participant operator request.
* **Resolution**: This error is caused by a participant node misconfiguration or by an implementation bug. Resolution requires participant operator intervention.
* **Category**: InternalUnsupportedOperation
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status UNIMPLEMENTED without any details for security reasons.
* **Scaladocs**: `UNSUPPORTED_OPERATION <../../canton/scaladoc/com/digitalasset/canton/ledger/error/CommonErrors$$UnsupportedOperation$.html>`_


.. _4. ethereumerrors_canton_error_codes:

4. EthereumErrors
=================


.. _4.1. configurationerrors_canton_error_codes:

4.1. ConfigurationErrors
========================


.. _ahead_of_head_canton_error_codes:

AHEAD_OF_HEAD
-------------
* **Explanation**: This warning is logged on startup if the sequencer is configured to only start reading from a block that wasn't mined yet by the blockchain (e.g. sequencer is supposed to start reading from block 500, but the latest block is only 100). This is likely due to a misconfiguration. 
* **Resolution**: This issue frequently occurs when the blockchain is reset but the sequencer database configuration is  not updated or the sequencer database (which persists the last block that was read by the sequencer) is not reset.  Validate these settings and ensure that the sequencer is still reading from the same blockchain. 
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `AHEAD_OF_HEAD <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$ConfigurationErrors$$AheadOfHead$.html>`_


.. _attempt_to_change_immutable_value_canton_error_codes:

ATTEMPT_TO_CHANGE_IMMUTABLE_VALUE
---------------------------------
* **Explanation**: The sequencer smart contract has detected that a value that is immutable after being set for the first time (either the signing tolerance or the topology manager ID) was attempted to be changed.  Most frequently this error occurs during testing when a Canton Ethereum sequencer process without persistence is restarted while pointing to the same smart sequencer contract. An Ethereum sequencer attempts to set the topology manager ID during initialization, however, without persistence the topology manager ID is randomly regenerated on the restart which leads to the sequencer attempting to change the topology manager ID in the sequencer smart contract. 
* **Resolution**: Deploy a new instance of the sequencer contract and configure the Ethereum sequencer to use that instance. If the errors occur because an Ethereum sequencer process is restarted without persistence, deploy a fresh instance of the sequencer contract and configure persistence for restarts. 
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `ATTEMPT_TO_CHANGE_IMMUTABLE_VALUE <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$ConfigurationErrors$$AttemptToChangeImmutableValue$.html>`_


.. _besu_version_mismatch_canton_error_codes:

BESU_VERSION_MISMATCH
---------------------
* **Explanation**: This error is logged when the sequencer detects that the version of the Besu client it connects to is not what is expected / supported. 
* **Resolution**: Either deploy the documented required version or set canton.parameters.non-standard-config = true.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `BESU_VERSION_MISMATCH <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$ConfigurationErrors$$BesuVersionMismatch$.html>`_


.. _ethereum_cant_query_version_canton_error_codes:

ETHEREUM_CANT_QUERY_VERSION
---------------------------
* **Explanation**:  As one of the first steps when initializing a Besu sequencer, Canton attempts to query the version (attribute) of the Sequencer.sol contract. 
* **Resolution**: Usually, the root cause of this is a deployment or configuration problem. Ensure that a Sequencer.sol contract is deployed on the configured address on the latest block when attempting  to initialize the Canton Besu sequencer node. If this error persists, a malicious user may  be attempting to interfere with the Ethereum network. 
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `ETHEREUM_CANT_QUERY_VERSION <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$ConfigurationErrors$$UnableToQueryVersion$.html>`_


.. _many_blocks_behind_head_canton_error_codes:

MANY_BLOCKS_BEHIND_HEAD
-----------------------
* **Explanation**: This error is logged when the sequencer is currently processing blocks that are very far behind the head of the blockchain of the connected Ethereum network. The Ethereum sequencer won't observe new transactions in the blockchain until it has caught up to the head. This may take a long time depending on the blockchain length and number of Canton transaction in the blocks. Empirically, we have observed that the Canton sequencer processes roughly 500 empty blocks/second. This may vary strongly for non-empty blocks. The sequencer logs once it has caught up to within `blocksBehindBlockchainHead` blocks behind the blockchain head. 
* **Resolution**: Wait until the sequencer has caught up to the head of the blockchain. Alternatively, consider changing the configuration of `block-to-read-from` of the Ethereum sequencer when initializing it against an Ethereum network that already mined a lot of blocks. 
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `MANY_BLOCKS_BEHIND_HEAD <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$ConfigurationErrors$$ManyBlocksBehindHead$.html>`_


.. _not_free_gas_network_canton_error_codes:

NOT_FREE_GAS_NETWORK
--------------------
* **Explanation**: This error is logged when during setup the sequencer detects that it isn't connected to a free-gas network. This usually leads to transactions silently being dropped by Ethereum nodes. You should only use a non-free-gas network, if you have configured an Ethereum wallet for the sequencer to use and have given it gas. 
* **Resolution**: Change the configuration of the Ethereum network to a free-gas network. 
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `NOT_FREE_GAS_NETWORK <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$ConfigurationErrors$$NotFreeGasNetwork$.html>`_


.. _wrong_evm_bytecode_canton_error_codes:

WRONG_EVM_BYTECODE
------------------
* **Explanation**: Canton validates on startup that the configured address on the blockchain contains the EVM bytecode of the sequencer smart contract in the latest block. This error indicates that no bytecode or the wrong bytecode was found. This is a serious error and means that the sequencer can't sequence events. 
* **Resolution**: This frequently error occurs when updating the Canton system without updating the sequencer contract deployed on the blockchain. Validate that the sequencer contract corresponding to the current Canton release is deployed in the latest blockchain blocks on the configured address. Another common reason for this error is that the wrong contract address was configured. 
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `WRONG_EVM_BYTECODE <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$ConfigurationErrors$$WrongEVMBytecode$.html>`_


.. _4.2. transactionerrors_canton_error_codes:

4.2. TransactionErrors
======================


.. _ethereum_transaction_invalid_canton_error_codes:

ETHEREUM_TRANSACTION_INVALID
----------------------------
* **Explanation**:  This error happens when the Sequencer Ethereum application reads a transaction from the blockchain which is malformed (e.g, invalid member, arguments aren't parseable or too large). This could happen if a malicious or faulty Ethereum Sequencer node is placing faulty data on the blockchain. 
* **Resolution**: Generally, Canton should recover automatically from this error. The faulty transactions are simply skipped by all non-malicious/non-faulty sequencers in a deterministic way, so the integrity of the event stream across sequencer nodes should be maintained. If you continue to see this error, investigate whether some of the sequencer nodes in the network are misbehaving. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `ETHEREUM_TRANSACTION_INVALID <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$TransactionErrors$$InvalidTransaction$.html>`_


.. _ethereum_transaction_receipt_fetching_failed_canton_error_codes:

ETHEREUM_TRANSACTION_RECEIPT_FETCHING_FAILED
--------------------------------------------
* **Explanation**: This error occurs when the Ethereum sequencer attempts to fetch the transaction receipt for a previously submitted transaction but receives an exception. Usually, this is caused by network errors, the Ethereum client node being overloaded or the Ethereum sequencer reaching its `transactionReceiptPollingAttempts` for a given transaction. The fetching of transaction receipts of submitted transactions is separate from the Ethereum sequencer's read-stream used to ingest new transactions. Thus, in this sense, this error is purely informative and can be caused by transient issues (such as a transient network outage). Note, that the Canton nonce manager refreshes his cache whenever this error occurs which may unblock stuck transactions with a too-high nonce. 
* **Resolution**: Usually, this error should resolve by itself. If you frequently see this error, ensure that the Ethereum account of the Ethereum sequencer is used by no one else and that the Ethereum client doesn't drop submitted transactions through being overloaded or reaching a full txpool. If this errors keeps occurring, please contact support. 
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `ETHEREUM_TRANSACTION_RECEIPT_FETCHING_FAILED <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$TransactionErrors$$ReceiptFetchingFailed$.html>`_


.. _ethereum_transaction_submission_failed_canton_error_codes:

ETHEREUM_TRANSACTION_SUBMISSION_FAILED
--------------------------------------
* **Explanation**:  This error is logged when the Sequencer Ethereum application receives an error when attempting to submit a transaction to the transaction pool of the Ethereum client. Common causes for this are network errors, or when the Ethereum account of the Sequencer Ethereum application is used by another application. Less commonly, this error might also indirectly be caused if the transaction pool of the Ethereum client is full or flushed. 
* **Resolution**: Generally, Canton should recover automatically from this error. If you continue to see this error, investigate possible root causes such as poor network connections, if the Ethereum wallet of the Ethereum Sequencer application is being reused by another application, and the health of the Ethereum client. 
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `ETHEREUM_TRANSACTION_SUBMISSION_FAILED <../../canton/scaladoc/com/digitalasset/canton/error/EthereumErrors$$TransactionErrors$$SubmissionFailed$.html>`_


.. _5. topologymanagementerrorgroup_canton_error_codes:

5. TopologyManagementErrorGroup
===============================


.. _5.1. topologymanagererror_canton_error_codes:

5.1. TopologyManagerError
=========================


.. _duplicate_topology_transaction_canton_error_codes:

DUPLICATE_TOPOLOGY_TRANSACTION
------------------------------
* **Explanation**: This error indicates that a transaction has already been added previously.
* **Resolution**: Nothing to do as the transaction is already registered. Note however that a revocation is " +   final. If you want to re-enable a statement, you need to re-issue an new transaction.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `DUPLICATE_TOPOLOGY_TRANSACTION <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$DuplicateTransaction$.html>`_


.. _illegal_removal_of_domain_trust_certificate_canton_error_codes:

ILLEGAL_REMOVAL_OF_DOMAIN_TRUST_CERTIFICATE
-------------------------------------------
* **Explanation**: This error indicates that a participant is trying to rescind their domain trust certificate while still being hosting parties.
* **Resolution**: The participant should work with the owners of the parties mentioned in the ``parties`` field in the error details metadata to get itself removed from the list of hosting participants of those parties.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `ILLEGAL_REMOVAL_OF_DOMAIN_TRUST_CERTIFICATE <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$IllegalRemovalOfDomainTrustCertificate$.html>`_


.. _increase_of_ledger_time_record_time_tolerance_canton_error_codes:

INCREASE_OF_LEDGER_TIME_RECORD_TIME_TOLERANCE
---------------------------------------------
* **Explanation**: This error indicates that it has been attempted to increase the ``ledgerTimeRecordTimeTolerance`` domain parameter in an insecure manner. Increasing this parameter may disable security checks and can therefore be a security risk. 
* **Resolution**: Make sure that the new value of ``ledgerTimeRecordTimeTolerance`` is at most half of the ``mediatorDeduplicationTimeout`` domain parameter. Use ``myDomain.service.set_ledger_time_record_time_tolerance`` for securely increasing ledgerTimeRecordTimeTolerance. Alternatively, add the ``force = true`` flag to your command, if security is not a concern for you. The security checks will be effective again after twice the new value of ``ledgerTimeRecordTimeTolerance``. Using ``force = true`` is safe upon domain bootstrapping. 
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INCREASE_OF_LEDGER_TIME_RECORD_TIME_TOLERANCE <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$IncreaseOfLedgerTimeRecordTimeTolerance$.html>`_


.. _insufficient_keys_canton_error_codes:

INSUFFICIENT_KEYS
-----------------
* **Explanation**: This error indicates that members referenced in a topology transaction have not declared at least one signing key or at least 1 encryption key or both.
* **Resolution**: Ensure that all members referenced in the topology transaction have declared at least one signing key and at least one encryption key, then resubmit the failed transaction. The metadata details of this error contain the members with the missing keys in the field ``members``.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `INSUFFICIENT_KEYS <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$InsufficientKeys$.html>`_


.. _invalid_domain_canton_error_codes:

INVALID_DOMAIN
--------------
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_DOMAIN <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$WrongDomain$.html>`_


.. _invalid_threshold_canton_error_codes:

INVALID_THRESHOLD
-----------------
* **Explanation**: This error indicates that a threshold in the submitted transaction was higher than the number of members that would have to satisfy that threshold.
* **Resolution**: Submit the topology transaction with a lower threshold. The metadata details of this error contain the expected maximum in the field ``expectedMaximum``.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_THRESHOLD <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$InvalidThreshold$.html>`_


.. _invalid_topology_tx_signature_error_canton_error_codes:

INVALID_TOPOLOGY_TX_SIGNATURE_ERROR
-----------------------------------
* **Explanation**: This error indicates that the uploaded signed transaction contained an invalid signature.
* **Resolution**: Ensure that the transaction is valid and uses a crypto version understood by this participant.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `INVALID_TOPOLOGY_TX_SIGNATURE_ERROR <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$InvalidSignatureError$.html>`_


.. _invalid_traffic_limit_canton_error_codes:

INVALID_TRAFFIC_LIMIT
---------------------
* **Explanation**: This error indicates that the attempted update of the extra traffic limits for a particular member failed because the new limit is lower than the current limit.
* **Resolution**: Extra traffic limits can only be increased. Submit the topology transaction with a higher limit. The metadata details of this error contain the expected minimum value in the field ``expectedMinimum``.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `INVALID_TRAFFIC_LIMIT <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$InvalidTrafficLimit$.html>`_


.. _no_appropriate_signing_key_in_store_canton_error_codes:

NO_APPROPRIATE_SIGNING_KEY_IN_STORE
-----------------------------------
* **Explanation**: This error results if the topology manager did not find a secret key in its store to authorize a certain topology transaction.
* **Resolution**: Inspect your topology transaction and your secret key store and check that you have the    appropriate certificates and keys to issue the desired topology transaction. If the list of candidates is empty,    then you are missing the certificates.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `NO_APPROPRIATE_SIGNING_KEY_IN_STORE <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$NoAppropriateSigningKeyInStore$.html>`_


.. _no_corresponding_active_tx_to_revoke_canton_error_codes:

NO_CORRESPONDING_ACTIVE_TX_TO_REVOKE
------------------------------------
* **Explanation**: This error indicates that the attempt to add a removal transaction was rejected, as the mapping / element affecting the removal did not exist.
* **Resolution**: Inspect the topology state and ensure the mapping and the element id of the active transaction you are trying to revoke matches your revocation arguments.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `NO_CORRESPONDING_ACTIVE_TX_TO_REVOKE <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$NoCorrespondingActiveTxToRevoke$.html>`_


.. _public_key_not_in_store_canton_error_codes:

PUBLIC_KEY_NOT_IN_STORE
-----------------------
* **Explanation**: This error indicates that a command contained a fingerprint referring to a public key not being present in the public key store.
* **Resolution**: Upload the public key to the public key store using $node.keys.public.load(.) before retrying.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PUBLIC_KEY_NOT_IN_STORE <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$PublicKeyNotInStore$.html>`_


.. _removing_key_dangling_transactions_must_be_forced_canton_error_codes:

REMOVING_KEY_DANGLING_TRANSACTIONS_MUST_BE_FORCED
-------------------------------------------------
* **Explanation**: This error indicates that the attempted key removal would create dangling topology transactions, making the node unusable.
* **Resolution**: Add the `force = true` flag to your command if you are really sure what you are doing.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `REMOVING_KEY_DANGLING_TRANSACTIONS_MUST_BE_FORCED <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$RemovingKeyWithDanglingTransactionsMustBeForced$.html>`_


.. _removing_last_key_must_be_forced_canton_error_codes:

REMOVING_LAST_KEY_MUST_BE_FORCED
--------------------------------
* **Explanation**: This error indicates that the attempted key removal would remove the last valid key of the given entity, making the node unusable.
* **Resolution**: Add the `force = true` flag to your command if you are really sure what you are doing.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `REMOVING_LAST_KEY_MUST_BE_FORCED <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$RemovingLastKeyMustBeForced$.html>`_


.. _secret_key_not_in_store_canton_error_codes:

SECRET_KEY_NOT_IN_STORE
-----------------------
* **Explanation**: This error indicates that the secret key with the respective fingerprint can not be found.
* **Resolution**: Ensure you only use fingerprints of secret keys stored in your secret key store.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SECRET_KEY_NOT_IN_STORE <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$SecretKeyNotInStore$.html>`_


.. _serial_mismatch_canton_error_codes:

SERIAL_MISMATCH
---------------
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SERIAL_MISMATCH <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$SerialMismatch$.html>`_


.. _topology_manager_alarm_canton_error_codes:

TOPOLOGY_MANAGER_ALARM
----------------------
* **Explanation**: The topology manager has received a malformed message from another node.
* **Resolution**: Inspect the error message for details.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `TOPOLOGY_MANAGER_ALARM <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$TopologyManagerAlarm$.html>`_


.. _topology_manager_internal_error_canton_error_codes:

TOPOLOGY_MANAGER_INTERNAL_ERROR
-------------------------------
* **Explanation**: This error indicates that there was an internal error within the topology manager.
* **Resolution**: Inspect error message for details.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `TOPOLOGY_MANAGER_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$InternalError$.html>`_


.. _topology_mapping_already_exists_canton_error_codes:

TOPOLOGY_MAPPING_ALREADY_EXISTS
-------------------------------
* **Explanation**: This error indicates that a topology transaction would create a state that already exists and has been authorized with the same key.
* **Resolution**: Your intended change is already in effect.
* **Category**: InvalidGivenCurrentSystemStateResourceExists
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ALREADY_EXISTS including a detailed error message.
* **Scaladocs**: `TOPOLOGY_MAPPING_ALREADY_EXISTS <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$MappingAlreadyExists$.html>`_


.. _unauthorized_topology_transaction_canton_error_codes:

UNAUTHORIZED_TOPOLOGY_TRANSACTION
---------------------------------
* **Explanation**: This error indicates that the attempt to add a transaction was rejected, as the signing key is not authorized within the current state.
* **Resolution**: Inspect the topology state and ensure that valid namespace or identifier delegations of the signing key exist or upload them before adding this transaction.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `UNAUTHORIZED_TOPOLOGY_TRANSACTION <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$UnauthorizedTransaction$.html>`_


.. _unknown_members_canton_error_codes:

UNKNOWN_MEMBERS
---------------
* **Explanation**: This error indicates that the topology transaction references members that are currently unknown.
* **Resolution**: Wait for the onboarding of the members to be become active or remove the unknown members from the topology transaction. The metadata details of this error contain the unknown member in the field ``members``.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `UNKNOWN_MEMBERS <../../canton/scaladoc/com/digitalasset/canton/topology/TopologyManagerError$$UnknownMembers$.html>`_


.. _5.1.1. domaintopologymanagererror_canton_error_codes:

5.1.1. DomainTopologyManagerError
=================================


.. _alien_domain_entities_canton_error_codes:

ALIEN_DOMAIN_ENTITIES
---------------------
* **Explanation**: This error is returned if a transaction attempts to add keys for alien domain manager or sequencer entities to this domain topology manager.
* **Resolution**: Use a participant topology manager if you want to manage foreign domain keys
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `ALIEN_DOMAIN_ENTITIES <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologyManagerError$$AlienDomainEntities$.html>`_


.. _failed_to_add_member_canton_error_codes:

FAILED_TO_ADD_MEMBER
--------------------
* **Explanation**: This error indicates an external issue with the member addition hook.
* **Resolution**: Consult the error details.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `FAILED_TO_ADD_MEMBER <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologyManagerError$$FailedToAddMember$.html>`_


.. _malicous_or_faulty_onboarding_request_canton_error_codes:

MALICOUS_OR_FAULTY_ONBOARDING_REQUEST
-------------------------------------
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `MALICOUS_OR_FAULTY_ONBOARDING_REQUEST <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologyManagerError$$InvalidOrFaultyOnboardingRequest$.html>`_


.. _participant_not_initialized_canton_error_codes:

PARTICIPANT_NOT_INITIALIZED
---------------------------
* **Explanation**: This error is returned if a domain topology manager attempts to activate a    participant without having all necessary data, such as keys or domain trust certificates.
* **Resolution**: Register the necessary keys or trust certificates and try again.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `PARTICIPANT_NOT_INITIALIZED <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologyManagerError$$ParticipantNotInitialized$.html>`_


.. _wrong_domain_canton_error_codes:

WRONG_DOMAIN
------------
* **Explanation**: This error is returned if a transaction restricted to a domain should be added to another domain.
* **Resolution**: Recreate the content of the transaction with a correct domain identifier.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `WRONG_DOMAIN <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologyManagerError$$WrongDomain$.html>`_


.. _wrong_protocol_version_canton_error_codes:

WRONG_PROTOCOL_VERSION
----------------------
* **Explanation**: This error is returned if a transaction has a protocol version different than the one spoken on the domain.
* **Resolution**: Recreate the transaction with a correct protocol version.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `WRONG_PROTOCOL_VERSION <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologyManagerError$$WrongProtocolVersion$.html>`_


.. _5.1.2. participanttopologymanagererror_canton_error_codes:

5.1.2. ParticipantTopologyManagerError
======================================


.. _cannot_vet_due_to_missing_packages_canton_error_codes:

CANNOT_VET_DUE_TO_MISSING_PACKAGES
----------------------------------
* **Explanation**: This error indicates that a package vetting command failed due to packages not existing locally. This can be due to either the packages not being present or their dependencies being missing. When vetting a package, the package must exist on the participant, as otherwise the participant will not be able to process a transaction relying on a particular package.
* **Resolution**: Ensure that the package exists locally before issuing such a transaction.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `CANNOT_VET_DUE_TO_MISSING_PACKAGES <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$CannotVetDueToMissingPackages$.html>`_


.. _dangerous_key_use_command_requires_force_canton_error_codes:

DANGEROUS_KEY_USE_COMMAND_REQUIRES_FORCE
----------------------------------------
* **Explanation**: This error indicates that a dangerous owner to key mapping authorization was rejected. This is the case if a command is run that could break a participant. If the command was run to assign a key for the given participant, then the command was rejected because the key is not in the participants private store. If the command is run on a participant to issue transactions for another participant, then such commands must be run with force, as they are very dangerous and could easily break the participant. As an example, if we assign an encryption key to a participant that the participant does not have, then the participant will be unable to process an incoming transaction. Therefore we must be very careful to not create such situations. 
* **Resolution**: Set force=true if you really know what you are doing.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DANGEROUS_KEY_USE_COMMAND_REQUIRES_FORCE <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$DangerousKeyUseCommandRequiresForce$.html>`_


.. _dangerous_vetting_commands_require_force_canton_error_codes:

DANGEROUS_VETTING_COMMANDS_REQUIRE_FORCE
----------------------------------------
* **Explanation**: This error indicates that a dangerous package vetting command was rejected. This is the case if a vetting command, if not run correctly, could potentially lead to a ledger fork. The vetting authorization checks the participant for the presence of the given set of packages (including their dependencies) and allows only to vet for the given participant id. In rare cases where a more centralised topology manager is used, this behaviour can be overridden with force. However, if a package is vetted but not present on the participant, the participant will refuse to process any transaction of the given domain until the problematic package has been uploaded.
* **Resolution**: Set force=true if you really know what you are doing.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DANGEROUS_VETTING_COMMANDS_REQUIRE_FORCE <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$DangerousVettingCommandsRequireForce$.html>`_


.. _dependencies_not_check_only_or_vetted_canton_error_codes:

DEPENDENCIES_NOT_CHECK_ONLY_OR_VETTED
-------------------------------------
* **Explanation**: This error indicates a packages topology request marking a set of packages as check-only failed due to dependencies not being marked as vetted or check-only. The system requires that not only the main packages are marked checked-only explicitly but also all dependencies must be declared as either vetted or check-only. This is necessary as not all participants are required to have the same packages installed and therefore not every participant can resolve the dependencies implicitly.
* **Resolution**: Vet the dependencies first and then repeat your attempt.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DEPENDENCIES_NOT_CHECK_ONLY_OR_VETTED <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$DependenciesNotCheckOnlyNorVetted$.html>`_


.. _dependencies_not_vetted_canton_error_codes:

DEPENDENCIES_NOT_VETTED
-----------------------
* **Explanation**: This error indicates a vetting request failed due to dependencies not being vetted. On every vetting request, the set supplied packages is analysed for dependencies. The system requires that not only the main packages are vetted explicitly but also all dependencies. This is necessary as not all participants are required to have the same packages installed and therefore not every participant can resolve the dependencies implicitly.
* **Resolution**: Vet the dependencies first and then repeat your attempt.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DEPENDENCIES_NOT_VETTED <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$DependenciesNotVetted$.html>`_


.. _disable_party_with_active_contracts_requires_force_canton_error_codes:

DISABLE_PARTY_WITH_ACTIVE_CONTRACTS_REQUIRES_FORCE
--------------------------------------------------
* **Explanation**: This error indicates that a dangerous PartyToParticipant mapping deletion was rejected. If the command is run and there are active contracts where the party is a stakeholder these contracts will become inoperable and will never get pruned, leaking storage. 
* **Resolution**: Set force=true if you really know what you are doing.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DISABLE_PARTY_WITH_ACTIVE_CONTRACTS_REQUIRES_FORCE <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$DisablePartyWithActiveContractsRequiresForce$.html>`_


.. _main_dar_package_referenced_externally_canton_error_codes:

MAIN_DAR_PACKAGE_REFERENCED_EXTERNALLY
--------------------------------------
* **Explanation**: The operation has failed due to the DAR's main package being referenced in other uploaded and enabled DARs.
* **Resolution**: First disable the other DARs or explicitly remove the offending topology transaction(s) referencing the main package. Then, re-try the operation.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `MAIN_DAR_PACKAGE_REFERENCED_EXTERNALLY <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$MainDarPackageReferencedExternally$.html>`_


.. _package_topology_state_update_timeout_canton_error_codes:

PACKAGE_TOPOLOGY_STATE_UPDATE_TIMEOUT
-------------------------------------
* **Explanation**: This error indicates that a package topology state update has timed out.
* **Resolution**: Retry the operation or check that no concurrent operations have affected the awaited topology state.
* **Category**: DeadlineExceededRequestStateUnknown
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status DEADLINE_EXCEEDED including a detailed error message.
* **Scaladocs**: `PACKAGE_TOPOLOGY_STATE_UPDATE_TIMEOUT <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$PackageTopologyStateUpdateTimeout$.html>`_


.. _uninitialized_participant_canton_error_codes:

UNINITIALIZED_PARTICIPANT
-------------------------
* **Explanation**: This error indicates that a request involving topology management was attempted on a participant that is not yet initialised. During initialisation, only namespace and identifier delegations can be managed.
* **Resolution**: Initialise the participant and retry.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `UNINITIALIZED_PARTICIPANT <../../canton/scaladoc/com/digitalasset/canton/participant/topology/ParticipantTopologyManagerError$$UninitializedParticipant$.html>`_


.. _5.1.3. domain_canton_error_codes:

5.1.3. Domain
=============


.. _domain_node_initialisation_failed_canton_error_codes:

DOMAIN_NODE_INITIALISATION_FAILED
---------------------------------
* **Explanation**: This error indicates that the initialisation of a domain node failed due to invalid arguments.
* **Resolution**: Consult the error details.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DOMAIN_NODE_INITIALISATION_FAILED <../../canton/scaladoc/com/digitalasset/canton/domain/Domain$$FailedToInitialiseDomainNode$.html>`_


.. _5.1.3.1. grpcsequencerauthenticationservice_canton_error_codes:

5.1.3.1. GrpcSequencerAuthenticationService
===========================================


.. _client_authentication_faulty_canton_error_codes:

CLIENT_AUTHENTICATION_FAULTY
----------------------------
* **Explanation**: This error indicates that a client failed to authenticate with the sequencer due to a reason possibly pointing out to faulty or malicious behaviour. The message is logged on the server in order to support an operator to provide explanations to clients struggling to connect.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `CLIENT_AUTHENTICATION_FAULTY <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/service/GrpcSequencerAuthenticationService$$SequencerAuthenticationFaultyOrMalicious$.html>`_


.. _client_authentication_rejected_canton_error_codes:

CLIENT_AUTHENTICATION_REJECTED
------------------------------
* **Explanation**: This error indicates that a client failed to authenticate with the sequencer. The message is logged on the server in order to support an operator to provide explanations to clients struggling to connect.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side.
* **Scaladocs**: `CLIENT_AUTHENTICATION_REJECTED <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/service/GrpcSequencerAuthenticationService$$SequencerAuthenticationFailure$.html>`_


.. _5.2. domaintopologysender_canton_error_codes:

5.2. DomainTopologySender
=========================


.. _topology_dispatching_degradation_canton_error_codes:

TOPOLOGY_DISPATCHING_DEGRADATION
--------------------------------
* **Explanation**: This warning occurs when the topology dispatcher experiences timeouts while trying to register topology transactions.
* **Resolution**: This error should normally self-recover due to retries. If issue persist, contact support and investigate system state.
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `TOPOLOGY_DISPATCHING_DEGRADATION <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologySender$$TopologyDispatchingDegradation$.html>`_


.. _topology_dispatching_internal_error_canton_error_codes:

TOPOLOGY_DISPATCHING_INTERNAL_ERROR
-----------------------------------
* **Explanation**: This error is emitted if there is a fundamental, un-expected situation during topology dispatching. In such a situation, the topology state of a newly onboarded participant or of all domain members might become outdated
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `TOPOLOGY_DISPATCHING_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/domain/topology/DomainTopologySender$$TopologyDispatchingInternalError$.html>`_


.. _6. configerrors_canton_error_codes:

6. ConfigErrors
===============


.. _cannot_parse_config_files_canton_error_codes:

CANNOT_PARSE_CONFIG_FILES
-------------------------
* **Explanation**: This error is usually thrown because a config file doesn't contain configs in valid HOCON format. The most common cause of an invalid HOCON format is a forgotten bracket.
* **Resolution**: Make sure that all files are in valid HOCON format.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: Config errors are logged and output to stdout if starting Canton with a given configuration fails
* **Scaladocs**: `CANNOT_PARSE_CONFIG_FILES <../../canton/scaladoc/com/digitalasset/canton/config/ConfigErrors$$CannotParseFilesError$.html>`_


.. _cannot_read_config_files_canton_error_codes:

CANNOT_READ_CONFIG_FILES
------------------------
* **Explanation**: This error is usually thrown when Canton can't find a given configuration file.
* **Resolution**: Make sure that the path and name of all configuration files is correctly specified. 
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: Config errors are logged and output to stdout if starting Canton with a given configuration fails
* **Scaladocs**: `CANNOT_READ_CONFIG_FILES <../../canton/scaladoc/com/digitalasset/canton/config/ConfigErrors$$CannotReadFilesError$.html>`_


.. _config_substitution_error_canton_error_codes:

CONFIG_SUBSTITUTION_ERROR
-------------------------
* **Resolution**: A common cause of this error is attempting to use an environment variable that isn't defined within a config-file. 
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: Config errors are logged and output to stdout if starting Canton with a given configuration fails
* **Scaladocs**: `CONFIG_SUBSTITUTION_ERROR <../../canton/scaladoc/com/digitalasset/canton/config/ConfigErrors$$SubstitutionError$.html>`_


.. _config_validation_error_canton_error_codes:

CONFIG_VALIDATION_ERROR
-----------------------
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: Config errors are logged and output to stdout if starting Canton with a given configuration fails
* **Scaladocs**: `CONFIG_VALIDATION_ERROR <../../canton/scaladoc/com/digitalasset/canton/config/ConfigErrors$$ValidationError$.html>`_


.. _generic_config_error_canton_error_codes:

GENERIC_CONFIG_ERROR
--------------------
* **Resolution**:  In general, this can be one of many errors since this is the 'miscellaneous category' of configuration errors. One of the more common errors in this category is an 'unknown key' error. This error usually means that  a keyword that is not valid (e.g. it may have a typo 'bort' instead of 'port'), or that a valid keyword  at the wrong part of the configuration hierarchy was used (e.g. to enable database replication for a participant, the correct configuration  is `canton.participants.participant2.replication.enabled = true` and not `canton.participants.replication.enabled = true`).  Please refer to the scaladoc of either `CantonEnterpriseConfig` or `CantonCommunityConfig` (depending on whether the community or enterprise version is used) to find the valid configuration keywords and the correct position in the configuration hierarchy. 
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: Config errors are logged and output to stdout if starting Canton with a given configuration fails
* **Scaladocs**: `GENERIC_CONFIG_ERROR <../../canton/scaladoc/com/digitalasset/canton/config/ConfigErrors$$GenericConfigError$.html>`_


.. _no_config_files_canton_error_codes:

NO_CONFIG_FILES
---------------
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: Config errors are logged and output to stdout if starting Canton with a given configuration fails
* **Scaladocs**: `NO_CONFIG_FILES <../../canton/scaladoc/com/digitalasset/canton/config/ConfigErrors$$NoConfigFiles$.html>`_


.. _7. commanderrors_canton_error_codes:

7. CommandErrors
================


.. _console_command_internal_error_canton_error_codes:

CONSOLE_COMMAND_INTERNAL_ERROR
------------------------------
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: These errors are shown as errors on the console.
* **Scaladocs**: `CONSOLE_COMMAND_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/console/CommandErrors$$CommandInternalError$.html>`_


.. _console_command_timed_out_canton_error_codes:

CONSOLE_COMMAND_TIMED_OUT
-------------------------
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: These errors are shown as errors on the console.
* **Scaladocs**: `CONSOLE_COMMAND_TIMED_OUT <../../canton/scaladoc/com/digitalasset/canton/console/CommandErrors$$ConsoleTimeout$.html>`_


.. _node_not_started_canton_error_codes:

NODE_NOT_STARTED
----------------
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: These errors are shown as errors on the console.
* **Scaladocs**: `NODE_NOT_STARTED <../../canton/scaladoc/com/digitalasset/canton/console/CommandErrors$$NodeNotStarted$.html>`_


.. _8. databasestorageerror_canton_error_codes:

8. DatabaseStorageError
=======================


.. _db_connection_lost_canton_error_codes:

DB_CONNECTION_LOST
------------------
* **Explanation**: This error indicates that the connection to the database has been lost.
* **Resolution**: Inspect error message for details.
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `DB_CONNECTION_LOST <../../canton/scaladoc/com/digitalasset/canton/resource/DatabaseStorageError$$DatabaseConnectionLost$.html>`_


.. _db_storage_degradation_canton_error_codes:

DB_STORAGE_DEGRADATION
----------------------
* **Explanation**: This error indicates that degradation of database storage components.
* **Resolution**: This error indicates performance degradation. The error occurs when a database task has been rejected, typically due to having a too small task queue. The task will be retried after a delay. If this error occurs frequently, however, you may want to consider increasing the task queue. (Config parameter: canton.<path-to-my-node>.storage.config.queueSize).
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `DB_STORAGE_DEGRADATION <../../canton/scaladoc/com/digitalasset/canton/resource/DatabaseStorageError$$DatabaseStorageDegradation$.html>`_


.. _9. handshakeerrors_canton_error_codes:

9. HandshakeErrors
==================


.. _deprecated_protocol_version_canton_error_codes:

DEPRECATED_PROTOCOL_VERSION
---------------------------
* **Explanation**: This error is logged or returned if a participant or domain are using deprecated protocol versions. Deprecated protocol versions might not be secure anymore.
* **Resolution**: Migrate to a new domain that uses the most recent protocol version.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `DEPRECATED_PROTOCOL_VERSION <../../canton/scaladoc/com/digitalasset/canton/version/HandshakeErrors$$DeprecatedProtocolVersion$.html>`_


.. _deprecating_protocol_version_canton_error_codes:

DEPRECATING_PROTOCOL_VERSION
----------------------------
* **Explanation**: This error is logged or returned if a participant or domain are using a protocol versions which will be deprecated.
* **Resolution**: Consider migration to a new domain that uses the most recent protocol version.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `DEPRECATING_PROTOCOL_VERSION <../../canton/scaladoc/com/digitalasset/canton/version/HandshakeErrors$$DeprecatingProtocolVersion$.html>`_


.. _10. envelopeopenererror_canton_error_codes:

10. EnvelopeOpenerError
=======================


.. _event_deserialization_error_canton_error_codes:

EVENT_DESERIALIZATION_ERROR
---------------------------
* **Explanation**:  This error indicates that the sequencer client was unable to parse a message. This indicates that the message has been created by a bogus or malicious sender. The message will be dropped. 
* **Resolution**: If no other errors are reported, Canton has recovered automatically. You should still consider to start an investigation to understand why the sender has sent an invalid message.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `EVENT_DESERIALIZATION_ERROR <../../canton/scaladoc/com/digitalasset/canton/sequencing/handlers/EnvelopeOpenerError$$EnvelopeOpenerDeserializationError$.html>`_


.. _11. fabricerrors_canton_error_codes:

11. FabricErrors
================


.. _11.1. configurationerrors_canton_error_codes:

11.1. ConfigurationErrors
=========================


.. _fabric_ahead_of_head_canton_error_codes:

FABRIC_AHEAD_OF_HEAD
--------------------
* **Explanation**: This warning is logged on startup if the sequencer is configured to only start reading from a block that wasn't ordered yet by the blockchain (e.g. sequencer is supposed to start reading from block 500, but the latest block is only 100). This is likely due to a misconfiguration. 
* **Resolution**: This issue frequently occurs when the blockchain is reset but the sequencer database configuration is  not updated or the sequencer database (which persists the last block that was read by the sequencer) is not reset.  Validate these settings and ensure that the sequencer is still reading from the same blockchain. 
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `FABRIC_AHEAD_OF_HEAD <../../canton/scaladoc/com/digitalasset/canton/error/FabricErrors$$ConfigurationErrors$$AheadOfHead$.html>`_


.. _fabric_many_blocks_behind_head_canton_error_codes:

FABRIC_MANY_BLOCKS_BEHIND_HEAD
------------------------------
* **Explanation**: This error is logged when the sequencer is currently processing blocks that are very far behind the head of the blockchain of the connected Fabric network. The Fabric sequencer won't observe new transactions in the blockchain until it has caught up to the head. This may take a long time depending on the blockchain length and number of Canton transaction in the blocks. Empirically, we have observed that the Canton sequencer processes roughly 500 empty blocks/second. This may vary strongly for non-empty blocks. 
* **Resolution**: Change the configuration of `startBlockHeight` for the Fabric sequencer when working with an existing (not fresh) Fabric network. Alternatively, wait until the sequencer has caught up to the head of the blockchain. 
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `FABRIC_MANY_BLOCKS_BEHIND_HEAD <../../canton/scaladoc/com/digitalasset/canton/error/FabricErrors$$ConfigurationErrors$$ManyBlocksBehindHead$.html>`_


.. _11.2. transactionerrors_canton_error_codes:

11.2. TransactionErrors
=======================


.. _fabric_transaction_invalid_canton_error_codes:

FABRIC_TRANSACTION_INVALID
--------------------------
* **Explanation**:  This error happens when the Sequencer Fabric application reads a transaction from the blockchain which is malformed (e.g, missing arguments, arguments aren't parseable or too large). This could happen if a malicious or faulty Fabric Sequencer node is placing faulty data on the blockchain. 
* **Resolution**: Generally, Canton should recover automatically from this error. The faulty transactions are simply skipped by all non-malicious/non-faulty sequencers in a deterministic way, so the integrity of the event stream across sequencer nodes should be maintained. If you continue to see this error, investigate whether some of the sequencer nodes in the network are misbehaving. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `FABRIC_TRANSACTION_INVALID <../../canton/scaladoc/com/digitalasset/canton/error/FabricErrors$$TransactionErrors$$InvalidTransaction$.html>`_


.. _fabric_transaction_proposal_submission_failed_canton_error_codes:

FABRIC_TRANSACTION_PROPOSAL_SUBMISSION_FAILED
---------------------------------------------
* **Explanation**:  An error happened with the Fabric transaction proposal submissions possibly due to some of the peers being down or due to network issues. Thus won't stop the transaction workflow, because there might still be enough successful responses to satisfy the endorsement policy. Therefore the transaction might still go through successfully despite this being logged. 
* **Resolution**: Generally, Canton should recover automatically from this error. If you continue to see this error, investigate possible root causes such as poor network connections, if the Fabric sequencer is properly configured with enough peers and if they are running. 
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `FABRIC_TRANSACTION_PROPOSAL_SUBMISSION_FAILED <../../canton/scaladoc/com/digitalasset/canton/error/FabricErrors$$TransactionErrors$$TransactionProposalSubmissionFailed$.html>`_


.. _fabric_transaction_submission_failed_canton_error_codes:

FABRIC_TRANSACTION_SUBMISSION_FAILED
------------------------------------
* **Explanation**:  This error is logged when the Sequencer Fabric application receives an error during any of the transaction flow steps that prevents the submission of a transaction over the Fabric client. Common causes for this are network errors, peers that are down or that there aren't enough configured endorsers. 
* **Resolution**: Generally, Canton should recover automatically from this error. If you continue to see this error, investigate possible root causes such as poor network connections, if the Fabric sequencer is properly configured with enough peers and if they are running. 
* **Category**: TransientServerFailure
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status UNAVAILABLE including a detailed error message.
* **Scaladocs**: `FABRIC_TRANSACTION_SUBMISSION_FAILED <../../canton/scaladoc/com/digitalasset/canton/error/FabricErrors$$TransactionErrors$$SubmissionFailed$.html>`_


.. _12. sequencererror_canton_error_codes:

12. SequencerError
==================


.. _invalid_acknowledgement_signature_canton_error_codes:

INVALID_ACKNOWLEDGEMENT_SIGNATURE
---------------------------------
* **Explanation**:  This error indicates that the sequencer has detected an invalid acknowledgement request signature. This most likely indicates that the request is bogus and has been created by a malicious sequencer. So it will not get processed. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `INVALID_ACKNOWLEDGEMENT_SIGNATURE <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$InvalidAcknowledgementSignature$.html>`_


.. _invalid_acknowledgement_timestamp_canton_error_codes:

INVALID_ACKNOWLEDGEMENT_TIMESTAMP
---------------------------------
* **Explanation**:  This error indicates that the member has acknowledged a timestamp that is after the events it has received. This violates the sequencing protocol. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `INVALID_ACKNOWLEDGEMENT_TIMESTAMP <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$InvalidAcknowledgementTimestamp$.html>`_


.. _invalid_envelope_signature_canton_error_codes:

INVALID_ENVELOPE_SIGNATURE
--------------------------
* **Explanation**:  This error indicates that the sequencer has detected an invalid envelope signature in the submission request. This most likely indicates that the request is bogus and has been created by a malicious sequencer. So it will not get processed. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `INVALID_ENVELOPE_SIGNATURE <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$InvalidEnvelopeSignature$.html>`_


.. _invalid_ledger_event_canton_error_codes:

INVALID_LEDGER_EVENT
--------------------
* **Explanation**:  The sequencer has detected that some event that was placed on the ledger cannot be parsed. This may be due to some sequencer node acting maliciously or faulty. The event is ignored and processing continues as usual. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `INVALID_LEDGER_EVENT <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$InvalidLedgerEvent$.html>`_


.. _invalid_sequencer_pruning_request_on_chain_canton_error_codes:

INVALID_SEQUENCER_PRUNING_REQUEST_ON_CHAIN
------------------------------------------
* **Explanation**:  This error indicates that some sequencer node has distributed an invalid sequencer pruning request via the blockchain. Either the sequencer nodes got out of sync or one of the sequencer nodes is buggy. The sequencer node will stop processing to prevent the danger of severe data corruption. 
* **Resolution**: Stop using the domain involving the sequencer nodes. Contact support.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `INVALID_SEQUENCER_PRUNING_REQUEST_ON_CHAIN <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$InvalidPruningRequestOnChain$.html>`_


.. _invalid_submission_request_signature_canton_error_codes:

INVALID_SUBMISSION_REQUEST_SIGNATURE
------------------------------------
* **Explanation**:  This error indicates that the sequencer has detected an invalid submission request signature. This most likely indicates that the request is bogus and has been created by a malicious sequencer. So it will not get processed. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `INVALID_SUBMISSION_REQUEST_SIGNATURE <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$InvalidSubmissionRequestSignature$.html>`_


.. _max_request_size_exceeded_canton_error_codes:

MAX_REQUEST_SIZE_EXCEEDED
-------------------------
* **Explanation**: This error means that the request size has exceeded the configured value maxRequestSize.
* **Resolution**: Send smaller requests or increase the maxRequestSize in the domain parameters
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `MAX_REQUEST_SIZE_EXCEEDED <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$MaxRequestSizeExceeded$.html>`_


.. _max_sequencing_time_exceeded_canton_error_codes:

MAX_SEQUENCING_TIME_EXCEEDED
----------------------------
* **Explanation**:  This error indicates that a request was not sequenced because the sequencing time would exceed the max-sequencing-time of the request. This error usually happens if either a participant or mediator node is too slowly responding to requests, or if it is catching up after some downtime. In rare cases, it can happen if the sequencer nodes are massively overloaded. If it happens repeatedly, this information might indicate that there is a problem with the respective participant or mediator node. 
* **Resolution**: Inspect the time difference between sequenced and max-sequencing-time. If the time difference is large, then some remote node is catching up but sending messages during catch-up. If the difference is not too large, then the submitting node or this sequencer node might be overloaded.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side.
* **Scaladocs**: `MAX_SEQUENCING_TIME_EXCEEDED <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$ExceededMaxSequencingTime$.html>`_


.. _missing_submission_request_signature_timestamp_canton_error_codes:

MISSING_SUBMISSION_REQUEST_SIGNATURE_TIMESTAMP
----------------------------------------------
* **Explanation**:  This error indicates that the sequencer has detected that the signed submission request being processed is missing a signature timestamp. It indicates that the sequencer node that placed the request is not following the protocol as there should always be a defined timestamp. This request will not get processed. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `MISSING_SUBMISSION_REQUEST_SIGNATURE_TIMESTAMP <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$MissingSubmissionRequestSignatureTimestamp$.html>`_


.. _multiple_mediator_recipients_canton_error_codes:

MULTIPLE_MEDIATOR_RECIPIENTS
----------------------------
* **Explanation**:  This error indicates that the participant is trying to send envelopes to multiple mediators or mediator groups in the same submission request. This most likely indicates that the request is bogus and has been created by a malicious sequencer. So it will not get processed. 
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `MULTIPLE_MEDIATOR_RECIPIENTS <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$MultipleMediatorRecipients$.html>`_


.. _payload_to_event_time_bound_exceeded_canton_error_codes:

PAYLOAD_TO_EVENT_TIME_BOUND_EXCEEDED
------------------------------------
* **Explanation**: This warning indicates that the time difference between storing the payload and writing the" event exceeded the configured time bound, which resulted in the message to be discarded. This can happen during some failure event on the database which causes unexpected delay between these two database operations. (The two events need to be sufficiently close together to support pruning of payloads by timestamp). 
* **Resolution**: The submitting node will usually retry the command, but you should check the health of the sequencer node, in particular with respect to database processing.
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `PAYLOAD_TO_EVENT_TIME_BOUND_EXCEEDED <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/errors/SequencerError$$PayloadToEventTimeBoundExceeded$.html>`_


.. _13. enterprisegrpcvaultserviceerror_canton_error_codes:

13. EnterpriseGrpcVaultServiceError
===================================


.. _invalid_kms_key_id_canton_error_codes:

INVALID_KMS_KEY_ID
------------------
* **Explanation**: Selected KMS key id is invalid
* **Resolution**: Specify a valid key id and retry.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `INVALID_KMS_KEY_ID <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/EnterpriseGrpcVaultServiceError$$InvalidKmsKeyId$.html>`_


.. _no_encrypted_private_key_store_error_canton_error_codes:

NO_ENCRYPTED_PRIVATE_KEY_STORE_ERROR
------------------------------------
* **Explanation**: Node is not running an encrypted private store
* **Resolution**: Verify that an encrypted store and KMS config are set for this node.
* **Category**: InternalUnsupportedOperation
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status UNIMPLEMENTED without any details for security reasons.
* **Scaladocs**: `NO_ENCRYPTED_PRIVATE_KEY_STORE_ERROR <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/EnterpriseGrpcVaultServiceError$$NoEncryptedPrivateKeyStoreError$.html>`_


.. _register_kms_key_internal_error_canton_error_codes:

REGISTER_KMS_KEY_INTERNAL_ERROR
-------------------------------
* **Explanation**: Internal error emitted upon failing to register a KMS key in Canton
* **Resolution**: Contact support
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `REGISTER_KMS_KEY_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/EnterpriseGrpcVaultServiceError$$RegisterKmsKeyInternalError$.html>`_


.. _wrapper_key_already_in_use_error_canton_error_codes:

WRAPPER_KEY_ALREADY_IN_USE_ERROR
--------------------------------
* **Explanation**: Selected wrapper key id for rotation is already in use
* **Resolution**: Select a different key id and retry.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `WRAPPER_KEY_ALREADY_IN_USE_ERROR <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/EnterpriseGrpcVaultServiceError$$WrapperKeyAlreadyInUseError$.html>`_


.. _wrapper_key_disabled_or_deleted_error_canton_error_codes:

WRAPPER_KEY_DISABLED_OR_DELETED_ERROR
-------------------------------------
* **Explanation**: Selected wrapper key id for rotation cannot be used because key is disabled or set to be deleted
* **Resolution**: Specify a key id from an active key and retry.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `WRAPPER_KEY_DISABLED_OR_DELETED_ERROR <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/EnterpriseGrpcVaultServiceError$$WrapperKeyDisabledOrDeletedError$.html>`_


.. _wrapper_key_not_exist_error_canton_error_codes:

WRAPPER_KEY_NOT_EXIST_ERROR
---------------------------
* **Explanation**: Selected wrapper key id for rotation does not match any existing KMS key
* **Resolution**: Specify a key id that matches an existing KMS key and retry.
* **Category**: InvalidGivenCurrentSystemStateResourceMissing
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status NOT_FOUND including a detailed error message.
* **Scaladocs**: `WRAPPER_KEY_NOT_EXIST_ERROR <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/EnterpriseGrpcVaultServiceError$$WrapperKeyNotExistError$.html>`_


.. _wrapper_key_rotation_internal_error_canton_error_codes:

WRAPPER_KEY_ROTATION_INTERNAL_ERROR
-----------------------------------
* **Explanation**: Internal error emitted upon internal wrapper key rotation errors
* **Resolution**: Contact support
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `WRAPPER_KEY_ROTATION_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/EnterpriseGrpcVaultServiceError$$WrapperKeyRotationInternalError$.html>`_


.. _14. mediatorerror_canton_error_codes:

14. MediatorError
=================


.. _mediator_internal_error_canton_error_codes:

MEDIATOR_INTERNAL_ERROR
-----------------------
* **Explanation**: Request processing failed due to a violation of internal invariants. It indicates a bug at the mediator.
* **Resolution**: Contact support.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `MEDIATOR_INTERNAL_ERROR <../../canton/scaladoc/com/digitalasset/canton/error/MediatorError$$InternalError$.html>`_


.. _mediator_invalid_message_canton_error_codes:

MEDIATOR_INVALID_MESSAGE
------------------------
* **Explanation**: The mediator has received an invalid message (request or response). The message will be discarded. As a consequence, the underlying request may be rejected. No corruption of the ledger is to be expected. This error is to be expected after a restart or failover of a mediator.
* **Resolution**: Address the cause of the error. Let the submitter retry the command.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level WARN on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `MEDIATOR_INVALID_MESSAGE <../../canton/scaladoc/com/digitalasset/canton/error/MediatorError$$InvalidMessage$.html>`_


.. _mediator_received_malformed_message_canton_error_codes:

MEDIATOR_RECEIVED_MALFORMED_MESSAGE
-----------------------------------
* **Explanation**: The mediator has received a malformed message. This may occur due to a bug at the sender of the message. The message will be discarded. As a consequence, the underlying request may be rejected. No corruption of the ledger is to be expected.
* **Resolution**: Contact support.
* **Category**: SecurityAlert
* **Conveyance**: This error is logged with log-level WARN on the server side. It is exposed on the API with grpc-status INVALID_ARGUMENT without any details for security reasons.
* **Scaladocs**: `MEDIATOR_RECEIVED_MALFORMED_MESSAGE <../../canton/scaladoc/com/digitalasset/canton/error/MediatorError$$MalformedMessage$.html>`_


.. _mediator_says_tx_timed_out_canton_error_codes:

MEDIATOR_SAYS_TX_TIMED_OUT
--------------------------
* **Explanation**: This rejection indicates that the transaction has been rejected by the mediator as it didn't receive enough confirmations within the participant response timeout.    The field "unresponsiveParties" in the error info contains the comma-separated list of parties that failed to send a response within the participant response timeout. This field is only present since protocol version 6
* **Resolution**: Check that all involved participants are available and not overloaded.
* **Category**: ContentionOnSharedResources
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status ABORTED including a detailed error message.
* **Scaladocs**: `MEDIATOR_SAYS_TX_TIMED_OUT <../../canton/scaladoc/com/digitalasset/canton/error/MediatorError$$Timeout$.html>`_


.. _15. protodeserializationerror_canton_error_codes:

15. ProtoDeserializationError
=============================


.. _proto_deserialization_failure_canton_error_codes:

PROTO_DESERIALIZATION_FAILURE
-----------------------------
* **Explanation**: This error indicates that an incoming administrative command could not be processed due to a malformed message.
* **Resolution**: Inspect the error details and correct your application
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `PROTO_DESERIALIZATION_FAILURE <../../canton/scaladoc/com/digitalasset/canton/ProtoDeserializationError$$ProtoDeserializationFailure$.html>`_


.. _16. sequencererrors_canton_error_codes:

16. SequencerErrors
===================


.. _sequencer_aggregate_submission_already_sent_canton_error_codes:

SEQUENCER_AGGREGATE_SUBMISSION_ALREADY_SENT
-------------------------------------------
* **Explanation**: This error occurs when the sequencer has already sent out the aggregate submission for the request.
* **Resolution**: This is expected to happen during operation of a system with aggregate submissions enabled. No action required.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_AGGREGATE_SUBMISSION_ALREADY_SENT <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$AggregateSubmissionAlreadySent$.html>`_


.. _sequencer_aggregate_submission_stuffing_canton_error_codes:

SEQUENCER_AGGREGATE_SUBMISSION_STUFFING
---------------------------------------
* **Explanation**: This error occurs when the sequencer already received the same submission request from the same sender.
* **Resolution**: This error indicates that an aggregate submission has already been accepted by the sequencer and for some reason there is a repeated submission. This is likely caused by retrying a submission. This can usually be ignored.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_AGGREGATE_SUBMISSION_STUFFING <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$AggregateSubmissionStuffing$.html>`_


.. _sequencer_max_sequencing_time_too_far_canton_error_codes:

SEQUENCER_MAX_SEQUENCING_TIME_TOO_FAR
-------------------------------------
* **Explanation**: Maximum sequencing time on the submission request is exceeding the maximum allowed interval into the future. Could be result of a concurrent dynamic domain parameter change for sequencerAggregateSubmissionTimeout.
* **Resolution**: In case there was a recent concurrent dynamic domain parameter change, simply retry the submission. Otherwise this error code indicates a bug in Canton (a faulty node behaviour). Please contact customer support.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_MAX_SEQUENCING_TIME_TOO_FAR <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$MaxSequencingTimeTooFar$.html>`_


.. _sequencer_not_enough_traffic_credit_canton_error_codes:

SEQUENCER_NOT_ENOUGH_TRAFFIC_CREDIT
-----------------------------------
* **Explanation**: Sequencer has refused a submission request due to insufficient credits in the sender's traffic balance.
* **Resolution**: Acquire more traffic credits with the system by topping up traffic credits for the sender.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_NOT_ENOUGH_TRAFFIC_CREDIT <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$TrafficCredit$.html>`_


.. _sequencer_signing_timestamp_after_sequencing_timestamp_canton_error_codes:

SEQUENCER_SIGNING_TIMESTAMP_AFTER_SEQUENCING_TIMESTAMP
------------------------------------------------------
* **Explanation**: Timestamp of the signing key on the submission request is later than the sequencing time.
* **Resolution**: This indicates a bug in Canton (a faulty node behaviour). Please contact customer support.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_SIGNING_TIMESTAMP_AFTER_SEQUENCING_TIMESTAMP <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$SigningTimestampAfterSequencingTimestamp$.html>`_


.. _sequencer_signing_timestamp_missing_canton_error_codes:

SEQUENCER_SIGNING_TIMESTAMP_MISSING
-----------------------------------
* **Explanation**: Timestamp of the signing key is missing on the submission request.
* **Resolution**: This indicates a bug in Canton (a faulty node behaviour). Please contact customer support.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_SIGNING_TIMESTAMP_MISSING <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$SigningTimestampMissing$.html>`_


.. _sequencer_signing_timestamp_too_early_canton_error_codes:

SEQUENCER_SIGNING_TIMESTAMP_TOO_EARLY
-------------------------------------
* **Explanation**: Timestamp of the signing key on the submission request is earlier than allowed by the dynamic domain parameters.
* **Resolution**: This indicates a bug in Canton (a faulty node behaviour). Please contact customer support.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_SIGNING_TIMESTAMP_TOO_EARLY <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$SigningTimestampTooEarly$.html>`_


.. _sequencer_submission_request_malformed_canton_error_codes:

SEQUENCER_SUBMISSION_REQUEST_MALFORMED
--------------------------------------
* **Explanation**: This error occurs when the sequencer cannot parse the submission request.
* **Resolution**: This usually indicates a misconfiguration of the system components or an application bug and requires operator intervention.
* **Category**: InvalidIndependentOfSystemState
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status INVALID_ARGUMENT including a detailed error message.
* **Scaladocs**: `SEQUENCER_SUBMISSION_REQUEST_MALFORMED <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$SubmissionRequestMalformed$.html>`_


.. _sequencer_submission_request_refused_canton_error_codes:

SEQUENCER_SUBMISSION_REQUEST_REFUSED
------------------------------------
* **Explanation**: This error occurs when the sequencer cannot accept submission request due to the current state of the system.
* **Resolution**: This usually indicates a misconfiguration of the system components or an application bug and requires operator intervention. Please refer to a specific error message to understand the exact cause.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_SUBMISSION_REQUEST_REFUSED <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$SubmissionRequestRefused$.html>`_


.. _sequencer_tombstone_persisted_canton_error_codes:

SEQUENCER_TOMBSTONE_PERSISTED
-----------------------------
* **Explanation**: An onboarded sequencer has put a tombstone in place of an event with a timestamp older than the sequencer signing key.
* **Resolution**: Clients should connect to another sequencer with older event history to consume the tombstoned events before reconnecting to the recently onboarded sequencer.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_TOMBSTONE_PERSISTED <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$PersistTombstone$.html>`_


.. _sequencer_unknown_recipients_canton_error_codes:

SEQUENCER_UNKNOWN_RECIPIENTS
----------------------------
* **Explanation**: This error happens when a submission request specifies nodes that are not known to the sequencer.
* **Resolution**: This indicates a bug in Canton (a faulty node behaviour). Please contact customer support.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_UNKNOWN_RECIPIENTS <../../canton/scaladoc/com/digitalasset/canton/sequencing/protocol/SequencerErrors$$UnknownRecipients$.html>`_


.. _17. resilientsequencersubscription_canton_error_codes:

17. ResilientSequencerSubscription
==================================


.. _sequencer_fork_detected_canton_error_codes:

SEQUENCER_FORK_DETECTED
-----------------------
* **Explanation**: This error is logged when a sequencer client determined a ledger fork, where a sequencer node responded with different events for the same timestamp / counter. Whenever a client reconnects to a domain, it will start with the last message received and compare whether that last message matches the one it received previously. If not, it will report with this error. A ledger fork should not happen in normal operation. It can happen if the backups have been taken in a wrong order and e.g. the participant was more advanced than the sequencer. 
* **Resolution**: You can recover by restoring the system with a correctly ordered backup. Please consult the respective sections in the manual.
* **Category**: SystemInternalAssumptionViolated
* **Conveyance**: This error is logged with log-level ERROR on the server side. It is exposed on the API with grpc-status INTERNAL without any details for security reasons.
* **Scaladocs**: `SEQUENCER_FORK_DETECTED <../../canton/scaladoc/com/digitalasset/canton/sequencing/client/ResilientSequencerSubscription$$ForkHappened$.html>`_


.. _sequencer_subscription_lost_canton_error_codes:

SEQUENCER_SUBSCRIPTION_LOST
---------------------------
* **Explanation**: This warning is logged when a sequencer subscription is interrupted. The system will keep on retrying to reconnect indefinitely.
* **Resolution**: Monitor the situation and contact the server operator if the issues does not resolve itself automatically.
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `SEQUENCER_SUBSCRIPTION_LOST <../../canton/scaladoc/com/digitalasset/canton/sequencing/client/ResilientSequencerSubscription$$LostSequencerSubscription$.html>`_


.. _18. sequencersubscriptionerror_canton_error_codes:

18. SequencerSubscriptionError
==============================


.. _sequencer_tombstone_encountered_canton_error_codes:

SEQUENCER_TOMBSTONE_ENCOUNTERED
-------------------------------
* **Explanation**: This error indicates that a sequencer subscription to a recently onboarded sequencer attempted to read an event replaced with a tombstone. A tombstone occurs if the timestamp associated with the event predates the validity of the sequencer's signing key. This error results in the sequencer client disconnecting from the sequencer.
* **Resolution**: Connect to another sequencer with older event history to consume the tombstoned events before reconnecting to the recently onboarded sequencer.
* **Category**: InvalidGivenCurrentSystemStateOther
* **Conveyance**: This error is logged with log-level INFO on the server side and exposed on the API with grpc-status FAILED_PRECONDITION including a detailed error message.
* **Scaladocs**: `SEQUENCER_TOMBSTONE_ENCOUNTERED <../../canton/scaladoc/com/digitalasset/canton/sequencing/client/SequencerSubscriptionError$$TombstoneEncountered$.html>`_


.. _19. clock_canton_error_codes:

19. Clock
=========


.. _system_clock_running_backwards_canton_error_codes:

SYSTEM_CLOCK_RUNNING_BACKWARDS
------------------------------
* **Explanation**: This error is emitted if the unique time generation detects that the host system clock is lagging behind the unique time source by more than a second. This can occur if the system processes more than 2e6 events per second (unlikely) or when the underlying host system clock is running backwards.
* **Resolution**: Inspect your host system. Generally, the unique time source is not negatively affected by a clock moving backwards and will keep functioning. Therefore, this message is just a warning about something strange being detected.
* **Category**: BackgroundProcessDegradationWarning
* **Conveyance**: This error is logged with log-level WARN on the server side.
* **Scaladocs**: `SYSTEM_CLOCK_RUNNING_BACKWARDS <../../canton/scaladoc/com/digitalasset/canton/time/Clock$$SystemClockRunningBackwards$.html>`_
