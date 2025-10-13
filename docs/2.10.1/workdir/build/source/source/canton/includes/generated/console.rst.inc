..
   Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _canton_console_reference:

Console Commands
================

Top-level Commands
------------------------

The following commands are available for convenience:

.. _exit:


:ref:`exit <exit>`
	* **Summary**: Leave the console

.. _help:


:ref:`help <help>`
	* **Summary**: Help with console commands; type help("<command>") for detailed help for <command>



.. _health.dump:


:ref:`health.dump <health.dump>`
	* **Summary**: Generate and write a health dump of Canton's state for a bug report
	* **Arguments**: 
		* ``outputFile``: better.files.File
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``chunkSize``: Option[Int]
	* **Return type**: 
		* String
	* **Description**: Gathers information about the current Canton process and/or remote nodes if using the console with a remote config. The outputFile argument can be used to write the health dump to a specific path. The timeout argument can be increased when retrieving large health dumps from remote nodes. The chunkSize argument controls the size of the byte chunks streamed back from remote nodes. This can be used if encountering errors due to gRPC max inbound message size being too low.

.. _health.help:


:ref:`health.help <health.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


.. _console.command_timeout:


:ref:`console.command_timeout <console.command_timeout>`
	* **Summary**: Yields the timeout for running console commands
	* **Return type**: 
		* `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**: Yields the timeout for running console commands. When the timeout has elapsed, the console stops waiting for the command result. The command will continue running in the background.

.. _console.help:


:ref:`console.help <console.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _console.set_command_timeout:


:ref:`console.set_command_timeout <console.set_command_timeout>`
	* **Summary**: Sets the timeout for running console commands.
	* **Arguments**: 
		* ``newTimeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**: Sets the timeout for running console commands. When the timeout has elapsed, the console stops waiting for the command result. The command will continue running in the background. The new timeout must be positive.



.. _logging.get_level:


:ref:`logging.get_level <logging.get_level>`
	* **Summary**: Determine current logging level
	* **Arguments**: 
		* ``loggerName``: String
	* **Return type**: 
		* Option[ch.qos.logback.classic.Level]

.. _logging.help:


:ref:`logging.help <logging.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _logging.last_error_trace:


:ref:`logging.last_error_trace <logging.last_error_trace>`
	* **Summary**: Returns log events for an error with the same trace-id
	* **Arguments**: 
		* ``traceId``: String
	* **Return type**: 
		* Seq[String]

.. _logging.last_errors:


:ref:`logging.last_errors <logging.last_errors>`
	* **Summary**: Returns the last errors (trace-id -> error event) that have been logged locally
	* **Return type**: 
		* Map[String,String]

.. _logging.set_level:


:ref:`logging.set_level <logging.set_level>`
	* **Summary**: Dynamically change log level (TRACE, DEBUG, INFO, WARN, ERROR, OFF, null)
	* **Arguments**: 
		* ``loggerName``: String
		* ``level``: String



.. _utils.auto_close:


:ref:`utils.auto_close (Testing) <utils.auto_close>`
	* **Summary**: Register `AutoCloseable` object to be shutdown if Canton is shut down
	* **Arguments**: 
		* ``closeable``: AutoCloseable

.. _utils.change_contracts_party_ids:


:ref:`utils.change_contracts_party_ids <utils.change_contracts_party_ids>`
	* **Summary**: Change the party ids referenced by a sequence of contracts.
	* **Arguments**: 
		* ``partiesOldToPartiesNew``: Map[com.digitalasset.canton.topology.PartyId,com.digitalasset.canton.topology.PartyId]
		* ``acs``: `Seq[com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/commands/LedgerApiTypeWrappers$$WrappedCreatedEvent.html>`_
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``ledgerCreateTime``: java.time.Instant
		* ``targetProtocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
		* ``withContractIdRemap``: Boolean
	* **Return type**: 
		* Seq[com.digitalasset.canton.version.VersionedMessage[Nothing]]
	* **Description**: The `utils.change_contracts_party_ids` changes the party ids of multiple contracts based on a map of old party ids to new party ids. This is typically used during an ACS migration when the reference party ids have changed (e.g. due to them being recreated in another participant in a different namespace). This function also requires the selection of a specific ledger create time according to the domain's clock. It is also possible to modify the domain and protocol version for those contracts, which can be useful when contracts are being migrated to a participant connected to a domain and/or protocol version. If `withContractIdRemap` is enabled, all contracts are converted to a non-authenticated form. This process involves replacing the suffix of each contract ID with the non-authenticated marker and rewriting all contract IDs accordingly.

.. _utils.contract_data_to_instance:


:ref:`utils.contract_data_to_instance <utils.contract_data_to_instance>`
	* **Summary**: Convert contract data to a contract instance.
	* **Arguments**: 
		* ``contractData``: `com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.ContractData <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/commands/LedgerApiTypeWrappers$$ContractData.html>`_
		* ``ledgerTime``: java.time.Instant
	* **Return type**: 
		* `com.digitalasset.canton.protocol.SerializableContract <../../canton/scaladoc/com/digitalasset/canton/protocol/SerializableContract.html>`_
	* **Description**: The `utils.contract_data_to_instance` bridges the gap between `participant.ledger_api.acs` commands that return various pieces of "contract data" and the `participant.repair.add` command used to add "contract instances" as part of repair workflows. Such workflows (for example migrating contracts from other Daml ledgers to Canton participants) typically consist of extracting contract data using `participant.ledger_api.acs` commands, modifying the contract data, and then converting the `contractData` using this function before finally adding the resulting contract instances to Canton participants via `participant.repair.add`. Obtain the `contractData` by invoking `.toContractData` on the `WrappedCreatedEvent` returned by the corresponding `participant.ledger_api.acs.of_party` or `of_all` call. The `ledgerTime` parameter should be chosen to be a time meaningful to the domain on which you plan to subsequently invoke `participant.repair.add` on and will be retained alongside the contract instance by the `participant.repair.add` invocation.

.. _utils.contract_instance_to_data:


:ref:`utils.contract_instance_to_data <utils.contract_instance_to_data>`
	* **Summary**: Convert a contract instance to contract data.
	* **Arguments**: 
		* ``contract``: `com.digitalasset.canton.protocol.SerializableContract <../../canton/scaladoc/com/digitalasset/canton/protocol/SerializableContract.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.ContractData <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/commands/LedgerApiTypeWrappers$$ContractData.html>`_
	* **Description**: The `utils.contract_instance_to_data` converts a Canton "contract instance" to "contract data", a format more amenable to inspection and modification as part of repair workflows. This function consumes the output of the `participant.testing` commands and can thus be employed in workflows geared at verifying the contents of contracts for diagnostic purposes and in environments in which the "features.enable-testing-commands" configuration can be (at least temporarily) enabled.

.. _utils.generate_contract_id:


:ref:`utils.generate_contract_id <utils.generate_contract_id>`
	* **Summary**: Generate authenticated contract id.
	* **Arguments**: 
		* ``cryptoPureApi``: `com.digitalasset.canton.crypto.CryptoPureApi <../../canton/scaladoc/com/digitalasset/canton/crypto/CryptoPureApi.html>`_
		* ``rawContract``: `com.digitalasset.canton.protocol.SerializableRawContractInstance <../../canton/scaladoc/com/digitalasset/canton/protocol/SerializableRawContractInstance.html>`_
		* ``createdAt``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``discriminator``: com.digitalasset.canton.protocol.LfHash
		* ``contractSalt``: `com.digitalasset.canton.crypto.Salt <../../canton/scaladoc/com/digitalasset/canton/crypto/Salt.html>`_
		* ``metadata``: `com.digitalasset.canton.protocol.ContractMetadata <../../canton/scaladoc/com/digitalasset/canton/protocol/ContractMetadata.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* com.daml.lf.value.Value.ContractId.V1
	* **Description**: The `utils.generate_contract_id` generates "contract id" of a contract. Starting from protocol version 4, Canton uses the so called authenticated contract ids which depend on the details of the associated contracts. When aspects of a contract such as the parties involved change as part of repair or export/import procedure, the corresponding contract id must be recomputed. This function can be used as a tool to generate an id for an arbitrary contract content

.. _utils.generate_daml_script_participants_conf:


:ref:`utils.generate_daml_script_participants_conf <utils.generate_daml_script_participants_conf>`
	* **Summary**: Create a participants config for Daml script
	* **Arguments**: 
		* ``file``: Option[String]
		* ``useParticipantAlias``: Boolean
		* ``defaultParticipant``: `Option[com.digitalasset.canton.console.ParticipantReference] <../../canton/scaladoc/com/digitalasset/canton/console/ParticipantReference.html>`_
	* **Return type**: 
		* java.io.File
	* **Description**: The generated config can be passed to `daml script` via the `participant-config` parameter. More information about the file format can be found in the `documentation <https://docs.daml.com/daml-script/index.html#using-daml-script-in-distributed-topologies>`_: It takes three arguments: - file (default to "participant-config.json") - useParticipantAlias (default to true): participant aliases are used instead of UIDs - defaultParticipant (default to None): adds a default participant if provided 

.. _utils.generate_navigator_conf:


:ref:`utils.generate_navigator_conf <utils.generate_navigator_conf>`
	* **Summary**: Create a navigator ui-backend.conf for a participant
	* **Arguments**: 
		* ``participant``: `com.digitalasset.canton.console.LocalParticipantReference <../../canton/scaladoc/com/digitalasset/canton/console/LocalParticipantReference.html>`_
		* ``file``: Option[String]
	* **Return type**: 
		* java.io.File

.. _utils.help:


:ref:`utils.help <utils.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _utils.migrate_dars:


:ref:`utils.migrate_dars <utils.migrate_dars>`
	* **Summary**: Migrates dars from one participant to another.
	* **Arguments**: 
		* ``participantOld``: `com.digitalasset.canton.console.ParticipantReference <../../canton/scaladoc/com/digitalasset/canton/console/ParticipantReference.html>`_
		* ``participantNew``: `com.digitalasset.canton.console.ParticipantReference <../../canton/scaladoc/com/digitalasset/canton/console/ParticipantReference.html>`_
	* **Description**: The `utils.migrate_dars` copies all dars (not part of the AdminWorkflows) from a participant, saves them in a temporary file and then uploads them to another participant.

.. _utils.object_args:


:ref:`utils.object_args <utils.object_args>`
	* **Summary**: Reflective inspection of object arguments, handy to inspect case class objects
	* **Arguments**: 
		* ``obj``: T
	* **Return type**: 
		* List[String]
	* **Description**: Return the list field names of the given object. Helpful function when inspecting the return result.

.. _utils.read_all_messages_from_file:


:ref:`utils.read_all_messages_from_file <utils.read_all_messages_from_file>`
	* **Summary**: Reads several Protobuf messages from a file.
	* **Arguments**: 
		* ``fileName``: String
	* **Return type**: 
		* Seq[A]
	* **Description**: Fails with an exception, if the file can't be read or parsed.

.. _utils.read_byte_string_from_file:


:ref:`utils.read_byte_string_from_file <utils.read_byte_string_from_file>`
	* **Summary**: Reads a ByteString from a file.
	* **Arguments**: 
		* ``fileName``: String
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Fails with an exception, if the file can't be read.

.. _utils.read_first_message_from_file:


:ref:`utils.read_first_message_from_file <utils.read_first_message_from_file>`
	* **Summary**: Reads a single Protobuf message from a file.
	* **Arguments**: 
		* ``fileName``: String
	* **Return type**: 
		* A
	* **Description**: Fails with an exception, if the file can't be read or parsed.

.. _utils.recompute_contract_ids:


:ref:`utils.recompute_contract_ids <utils.recompute_contract_ids>`
	* **Summary**: Recompute authenticated contract ids.
	* **Arguments**: 
		* ``participant``: `com.digitalasset.canton.console.LocalParticipantReference <../../canton/scaladoc/com/digitalasset/canton/console/LocalParticipantReference.html>`_
		* ``acs``: `Seq[com.digitalasset.canton.protocol.SerializableContract] <../../canton/scaladoc/com/digitalasset/canton/protocol/SerializableContract.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* (Seq[com.digitalasset.canton.protocol.SerializableContract], Map[com.digitalasset.canton.protocol.LfContractId,com.digitalasset.canton.protocol.LfContractId])
	* **Description**: The `utils.recompute_contract_ids` regenerates "contract ids" of multiple contracts after their contents have changed. Starting from protocol version 4, Canton uses the so called authenticated contract ids which depend on the details of the associated contracts. When aspects of a contract such as the parties involved change as part of repair or export/import procedure, the corresponding contract id must be recomputed.

.. _utils.retry_until_true:


:ref:`utils.retry_until_true <utils.retry_until_true>`
	* **Summary**: Wait for a condition to become true
	* **Arguments**: 
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``maxWaitPeriod``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``condition``: => Boolean
		* ``failure``: => String
	* **Return type**: 
		* (condition: => Boolean, failure: => String): Unit
	* **Description**: Wait `timeout` duration until `condition` becomes true. Retry evaluating `condition` with an exponentially increasing back-off up to `maxWaitPeriod` duration between retries. 

.. _utils.retry_until_true_1:


:ref:`utils.retry_until_true <utils.retry_until_true_1>`
	* **Summary**: Wait for a condition to become true, using default timeouts
	* **Arguments**: 
		* ``condition``: => Boolean
	* **Description**:  Wait until condition becomes true, with a timeout taken from the parameters.timeouts.console.bounded configuration parameter.

.. _utils.synchronize_topology:


:ref:`utils.synchronize_topology <utils.synchronize_topology>`
	* **Summary**: Wait until all topology changes have been effected on all accessible nodes
	* **Arguments**: 
		* ``timeoutO``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_

.. _utils.type_args:


:ref:`utils.type_args <utils.type_args>`
	* **Summary**: Reflective inspection of type arguments, handy to inspect case class types
	* **Return type**: 
		* List[String]
	* **Description**: Return the list of field names of the given type. Helpful function when creating new objects for requests.

.. _utils.write_to_file:


:ref:`utils.write_to_file <utils.write_to_file>`
	* **Summary**: Writes a ByteString to a file.
	* **Arguments**: 
		* ``data``: com.google.protobuf.ByteString
		* ``fileName``: String

.. _utils.write_to_file_1:


:ref:`utils.write_to_file <utils.write_to_file_1>`
	* **Summary**: Writes a Protobuf message to a file.
	* **Arguments**: 
		* ``data``: scalapb.GeneratedMessage
		* ``fileName``: String

.. _utils.write_to_file_2:


:ref:`utils.write_to_file <utils.write_to_file_2>`
	* **Summary**: Writes several Protobuf messages to a file.
	* **Arguments**: 
		* ``data``: Seq[scalapb.GeneratedMessage]
		* ``fileName``: String



.. _ledger_api_utils.create:


:ref:`ledger_api_utils.create (Testing) <ledger_api_utils.create>`
	* **Summary**: Build create command
	* **Arguments**: 
		* ``packageId``: String
		* ``module``: String
		* ``template``: String
		* ``arguments``: Map[String,Any]
	* **Return type**: 
		* com.daml.ledger.api.v1.commands.Command

.. _ledger_api_utils.exercise:


:ref:`ledger_api_utils.exercise (Testing) <ledger_api_utils.exercise>`
	* **Summary**: Build exercise command from CreatedEvent
	* **Arguments**: 
		* ``choice``: String
		* ``arguments``: Map[String,Any]
		* ``event``: com.daml.ledger.api.v1.event.CreatedEvent
	* **Return type**: 
		* com.daml.ledger.api.v1.commands.Command

.. _ledger_api_utils.exercise_1:


:ref:`ledger_api_utils.exercise (Testing) <ledger_api_utils.exercise_1>`
	* **Summary**: Build exercise command
	* **Arguments**: 
		* ``packageId``: String
		* ``module``: String
		* ``template``: String
		* ``choice``: String
		* ``arguments``: Map[String,Any]
		* ``contractId``: String
	* **Return type**: 
		* com.daml.ledger.api.v1.commands.Command

.. _ledger_api_utils.help:


:ref:`ledger_api_utils.help <ledger_api_utils.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


Participant Commands
--------------------

.. _clear_cache:


:ref:`clear_cache (Testing) <clear_cache>`
	* **Summary**: Clear locally cached variables
	* **Description**: Some commands cache values on the client side. Use this command to explicitly clear the caches of these values.

.. _config:


:ref:`config <config>`
	* **Summary**: Return participant config
	* **Return type**: 
		* `com.digitalasset.canton.participant.config.LocalParticipantConfig <../../canton/scaladoc/com/digitalasset/canton/participant/config/LocalParticipantConfig.html>`_

.. _help_1:


:ref:`help <help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _id:


:ref:`id <id>`
	* **Summary**: Yields the globally unique id of this participant. Throws an exception, if the id has not yet been allocated (e.g., the participant has not yet been started).
	* **Return type**: 
		* `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_

.. _is_initialized:


:ref:`is_initialized <is_initialized>`
	* **Summary**: Check if the local instance is running and is fully initialized
	* **Return type**: 
		* Boolean

.. _is_running:


:ref:`is_running <is_running>`
	* **Summary**: Check if the local instance is running
	* **Return type**: 
		* Boolean

.. _start:


:ref:`start <start>`
	* **Summary**: Start the instance

.. _stop:


:ref:`stop <stop>`
	* **Summary**: Stop the instance

.. _testing.acs_search:


:ref:`testing.acs_search (Testing) <testing.acs_search>`
	* **Summary**: Lookup of active contracts
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``filterId``: String
		* ``filterPackage``: String
		* ``filterTemplate``: String
		* ``filterStakeholder``: `Option[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `List[com.digitalasset.canton.protocol.SerializableContract] <../../canton/scaladoc/com/digitalasset/canton/protocol/SerializableContract.html>`_

.. _testing.await_domain_time:


:ref:`testing.await_domain_time (Testing) <testing.await_domain_time>`
	* **Summary**: Await for the given time to be reached on the given domain
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``time``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_

.. _testing.await_domain_time_1:


:ref:`testing.await_domain_time (Testing) <testing.await_domain_time_1>`
	* **Summary**: Await for the given time to be reached on the given domain
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``time``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_

.. _testing.bong:


:ref:`testing.bong (Testing) <testing.bong>`
	* **Summary**: Send a bong to a set of target parties over the ledger. Levels > 0 leads to an exploding ping with exponential number of contracts. Throw a RuntimeException in case of failure.
	* **Arguments**: 
		* ``targets``: `Set[com.digitalasset.canton.topology.ParticipantId] <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``validators``: `Set[com.digitalasset.canton.topology.ParticipantId] <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``levels``: Long
		* ``gracePeriodMillis``: Long
		* ``workflowId``: String
		* ``id``: String
	* **Return type**: 
		* scala.concurrent.duration.Duration
	* **Description**: Initiates a racy ping to multiple participants,   measuring the roundtrip time of the fastest responder, with an optional timeout.   Grace-period is the time the bong will wait for a duplicate spent (which would indicate an error in the system) before exiting.   If levels > 0, the ping command will lead to a binary explosion and subsequent dilation of   contracts, where ``level`` determines the number of levels we will explode. As a result, the system will create   (2^(L+2) - 3) contracts (where L stands for ``level``).   Normally, only the initiator is a validator. Additional validators can be added using the validators argument.   The bong command comes handy to run a burst test against the system and quickly leads to an overloading state.

.. _testing.crypto_api:


:ref:`testing.crypto_api (Testing) <testing.crypto_api>`
	* **Summary**: Return the sync crypto api provider, which provides access to all cryptographic methods
	* **Return type**: 
		* `com.digitalasset.canton.crypto.SyncCryptoApiProvider <../../canton/scaladoc/com/digitalasset/canton/crypto/SyncCryptoApiProvider.html>`_

.. _testing.event_search:


:ref:`testing.event_search (Testing) <testing.event_search>`
	* **Summary**: Lookup of events
	* **Arguments**: 
		* ``domain``: `Option[com.digitalasset.canton.DomainAlias] <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``from``: Option[java.time.Instant]
		* ``to``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* Seq[(String, com.digitalasset.canton.participant.sync.TimestampedEvent)]
	* **Description**: Show the event logs. To select only events from a particular domain, use the domain alias.    Leave the domain empty to search the combined event log containing the events of all domains.    Note that if the domain is left blank, the values of `from` and `to` cannot be set.    This is because the combined event log isn't guaranteed to have increasing timestamps.   

.. _testing.fetch_domain_time:


:ref:`testing.fetch_domain_time (Testing) <testing.fetch_domain_time>`
	* **Summary**: Fetch the current time from the given domain
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_

.. _testing.fetch_domain_time_1:


:ref:`testing.fetch_domain_time (Testing) <testing.fetch_domain_time_1>`
	* **Summary**: Fetch the current time from the given domain
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_

.. _testing.fetch_domain_times:


:ref:`testing.fetch_domain_times (Testing) <testing.fetch_domain_times>`
	* **Summary**: Fetch the current time from all connected domains
	* **Arguments**: 
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_

.. _testing.find_clean_commitments_timestamp:


:ref:`testing.find_clean_commitments_timestamp (Testing) <testing.find_clean_commitments_timestamp>`
	* **Summary**: The latest timestamp before or at the given one for which no commitment is outstanding
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``beforeOrAt``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Return type**: 
		* `Option[com.digitalasset.canton.data.CantonTimestamp] <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Description**: The latest timestamp before or at the given one for which no commitment is outstanding. Note that this doesn't imply that pruning is possible at this timestamp, as the system might require some additional data for crash recovery. Thus, this is useful for testing commitments; use the commands in the pruning group for pruning. Additionally, the result needn't fall on a "commitment tick" as specified by the reconciliation interval.

.. _testing.help:


:ref:`testing.help <testing.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _testing.maybe_bong:


:ref:`testing.maybe_bong (Testing) <testing.maybe_bong>`
	* **Summary**: Like bong, but returns None in case of failure.
	* **Arguments**: 
		* ``targets``: `Set[com.digitalasset.canton.topology.ParticipantId] <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``validators``: `Set[com.digitalasset.canton.topology.ParticipantId] <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``levels``: Long
		* ``gracePeriodMillis``: Long
		* ``workflowId``: String
		* ``id``: String
	* **Return type**: 
		* Option[scala.concurrent.duration.Duration]

.. _testing.pcs_search:


:ref:`testing.pcs_search (Testing) <testing.pcs_search>`
	* **Summary**: Lookup contracts in the Private Contract Store
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``filterId``: String
		* ``filterPackage``: String
		* ``filterTemplate``: String
		* ``activeSet``: Boolean
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* List[(Boolean, com.digitalasset.canton.protocol.SerializableContract)]
	* **Description**: Get raw access to the PCS of the given domain sync controller.  The filter commands will check if the target value ``contains`` the given string.  The arguments can be started with ``^`` such that ``startsWith`` is used for comparison or ``!`` to use ``equals``.  The ``activeSet`` argument allows to restrict the search to the active contract set.  

.. _testing.sequencer_messages:


:ref:`testing.sequencer_messages (Testing) <testing.sequencer_messages>`
	* **Summary**: Retrieve all sequencer messages
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``from``: Option[java.time.Instant]
		* ``to``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.sequencing.PossiblyIgnoredProtocolEvent] <../../canton/scaladoc/com/digitalasset/canton/sequencing/index.html>`_
	* **Description**: Optionally allows filtering for sequencer from a certain time span (inclusive on both ends) and limiting the number of displayed messages. The returned messages will be ordered on most domain ledger implementations if a time span is given. Fails if the participant has never connected to the domain.

.. _testing.state_inspection:


:ref:`testing.state_inspection (Testing) <testing.state_inspection>`
	* **Summary**: Obtain access to the state inspection interface. Use at your own risk.
	* **Return type**: 
		* `com.digitalasset.canton.participant.admin.inspection.SyncStateInspection <../../canton/scaladoc/com/digitalasset/canton/participant/admin/inspection/SyncStateInspection.html>`_
	* **Description**: The state inspection methods can fatally and permanently corrupt the state of a participant. The API is subject to change in any way.

.. _testing.transaction_search:


:ref:`testing.transaction_search (Testing) <testing.transaction_search>`
	* **Summary**: Lookup of accepted transactions
	* **Arguments**: 
		* ``domain``: `Option[com.digitalasset.canton.DomainAlias] <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``from``: Option[java.time.Instant]
		* ``to``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* Seq[(String, com.digitalasset.canton.protocol.LfCommittedTransaction)]
	* **Description**: Show the accepted transactions as they appear in the event logs.    To select only transactions from a particular domain, use the domain alias.    Leave the domain empty to search the combined event log containing the events of all domains.    Note that if the domain is left blank, the values of `from` and `to` cannot be set.    This is because the combined event log isn't guaranteed to have increasing timestamps.   


Database
~~~~~~~~

.. _db.help:


:ref:`db.help <db.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _db.migrate:


:ref:`db.migrate <db.migrate>`
	* **Summary**: Migrates the instance's database if using a database storage
	* **Description**: When instances reside on different nodes, their database migration can be run in parallel to save time. Please not that the migration commands must however must be run on each node individually, because remote migration through `participants.remote...` is not supported. 

.. _db.repair_migration:


:ref:`db.repair_migration <db.repair_migration>`
	* **Summary**: Only use when advised - repairs the database migration of the instance's database
	* **Arguments**: 
		* ``force``: Boolean
	* **Description**: In some rare cases, we change already applied database migration files in a new release and the repair command resets the checksums we use to ensure that in general already applied migration files have not been changed. You should only use `db.repair_migration` when advised and otherwise use it at your own risk - in the worst case running it may lead to data corruption when an incompatible database migration (one that should be rejected because the already applied database migration files have changed) is subsequently falsely applied. 


Health
~~~~~~

.. _health.active:


:ref:`health.active <health.active>`
	* **Summary**: Check if the node is running and is the active instance (mediator, participant)
	* **Return type**: 
		* Boolean

.. _health.count_in_flight:


:ref:`health.count_in_flight <health.count_in_flight>`
	* **Summary**: Counts pending command submissions and transactions on a domain.
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.InFlightCount <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/InFlightCount.html>`_
	* **Description**: This command finds the current number of pending command submissions and transactions on a selected domain. There is no synchronization between pending command submissions and transactions. And the respective counts are an indication only! This command is in particular useful to re-assure oneself that there are currently no in-flight submissions or transactions present for the selected domain. Such re-assurance is then helpful to proceed with repair operations, for example.

.. _health.dump_1:


:ref:`health.dump <health.dump_1>`
	* **Summary**: Creates a zip file containing diagnostic information about the canton process running this node
	* **Arguments**: 
		* ``outputFile``: better.files.File
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``chunkSize``: Option[Int]
	* **Return type**: 
		* String

.. _health.help_1:


:ref:`health.help <health.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _health.initialized:


:ref:`health.initialized <health.initialized>`
	* **Summary**: Returns true if node has been initialized.
	* **Return type**: 
		* Boolean

.. _health.last_error_trace:


:ref:`health.last_error_trace <health.last_error_trace>`
	* **Summary**: Show all messages logged with the given traceId in a recent interval
	* **Arguments**: 
		* ``traceId``: String
	* **Return type**: 
		* Seq[String]
	* **Description**: Returns a list of buffered log messages associated to a given trace-id. Usually, the trace-id is taken from last_errors()

.. _health.last_errors:


:ref:`health.last_errors <health.last_errors>`
	* **Summary**: Show the last errors logged
	* **Return type**: 
		* Map[String,String]
	* **Description**: Returns a map with the trace-id as key and the most recent error messages as value. Requires that --log-last-errors is enabled (and not turned off).

.. _health.maybe_ping:


:ref:`health.maybe_ping (Testing) <health.maybe_ping>`
	* **Summary**: Sends a ping to the target participant over the ledger. Yields Some(duration) in case of success and None in case of failure.
	* **Arguments**: 
		* ``participantId``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``workflowId``: String
		* ``id``: String
	* **Return type**: 
		* Option[scala.concurrent.duration.Duration]

.. _health.ping:


:ref:`health.ping <health.ping>`
	* **Summary**: Sends a ping to the target participant over the ledger. Yields the duration in case of success and throws a RuntimeException in case of failure.
	* **Arguments**: 
		* ``participantId``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``workflowId``: String
		* ``id``: String
	* **Return type**: 
		* scala.concurrent.duration.Duration

.. _health.running:


:ref:`health.running <health.running>`
	* **Summary**: Check if the node is running
	* **Return type**: 
		* Boolean

.. _health.set_log_level:


:ref:`health.set_log_level <health.set_log_level>`
	* **Summary**: Change the log level of the process
	* **Arguments**: 
		* ``level``: ch.qos.logback.classic.Level
	* **Description**: If the default logback configuration is used, this will change the log level of the process.

.. _health.status:


:ref:`health.status <health.status>`
	* **Summary**: Get human (and machine) readable participant status information
	* **Return type**: 
		* com.digitalasset.canton.admin.api.client.data.NodeStatus[S]

.. _health.wait_for_identity:


:ref:`health.wait_for_identity <health.wait_for_identity>`
	* **Summary**: Wait for the node to have an identity
	* **Description**: This is specifically useful for the Domain Manager which needs its identity to be ready for bootstrapping, but for which we can't rely on wait_for_initialized() because it will be initialized only after being bootstrapped.

.. _health.wait_for_initialized:


:ref:`health.wait_for_initialized <health.wait_for_initialized>`
	* **Summary**: Wait for the node to be initialized

.. _health.wait_for_running:


:ref:`health.wait_for_running <health.wait_for_running>`
	* **Summary**: Wait for the node to be running


.. _participant_domain_connectivity:

Domain Connectivity
~~~~~~~~~~~~~~~~~~~

.. _domains.accept_agreement:


:ref:`domains.accept_agreement <domains.accept_agreement>`
	* **Summary**: Accept the service agreement of the given domain alias
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``agreementId``: String

.. _domains.active:


:ref:`domains.active <domains.active>`
	* **Summary**: Test whether a participant is connected to and permissioned on a domain reference, both from the perspective of the participant and the domain.
	* **Arguments**: 
		* ``reference``: `com.digitalasset.canton.console.commands.DomainAdministration <../../canton/scaladoc/com/digitalasset/canton/console/commands/DomainAdministration.html>`_
	* **Return type**: 
		* Boolean
	* **Description**: Yields false, if the domain has not been initialized, is not connected or is not healthy.

.. _domains.active_1:


:ref:`domains.active <domains.active_1>`
	* **Summary**: Test whether a participant is connected to and permissioned on a domain.
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Return type**: 
		* Boolean
	* **Description**: Yields false, if the domain is not connected or not healthy. Yields false, if the domain is configured in the Canton configuration and the participant is not active from the perspective of the domain.

.. _domains.config:


:ref:`domains.config <domains.config>`
	* **Summary**: Returns the current configuration of a given domain
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Return type**: 
		* `Option[com.digitalasset.canton.participant.domain.DomainConnectionConfig] <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_

.. _domains.connect:


:ref:`domains.connect <domains.connect>`
	* **Summary**: Macro to connect a participant to a domain given by connection
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``connection``: String
		* ``manualConnect``: Boolean
		* ``domainId``: `Option[com.digitalasset.canton.topology.DomainId] <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``certificatesPath``: String
		* ``priority``: Int
		* ``timeTrackerConfig``: `com.digitalasset.canton.config.DomainTimeTrackerConfig <../../canton/scaladoc/com/digitalasset/canton/config/DomainTimeTrackerConfig.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_
	* **Description**: The connect macro performs a series of commands in order to connect this participant to a domain. First, `register` will be invoked with the given arguments, but first registered with manualConnect = true. If you already set manualConnect = true, then nothing else will happen and you will have to do the remaining steps yourselves. Otherwise, if the domain requires an agreement, it is fetched and presented to the user for evaluation. If the user is fine with it, the agreement is confirmed. If you want to auto-confirm, then set the environment variable CANTON_AUTO_APPROVE_AGREEMENTS=yes. Finally, the command will invoke `reconnect` to startup the connection. If the reconnect succeeded, the registered configuration will be updated with manualStart = true. If anything fails, the domain will remain registered with `manualConnect = true` and you will have to perform these steps manually.     The arguments are:      domainAlias - The name you will be using to refer to this domain. Can not be changed anymore.      connection - The connection string to connect to this domain. I.e. https://url:port      manualConnect - Whether this connection should be handled manually and also excluded from automatic re-connect.      domainId - Optionally the domainId you expect to see on this domain.      certificatesPath - Path to TLS certificate files to use as a trust anchor.      priority - The priority of the domain. The higher the more likely a domain will be used.      timeTrackerConfig - The configuration for the domain time tracker.      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.     

.. _domains.connect_1:


:ref:`domains.connect <domains.connect_1>`
	* **Summary**: Macro to connect a participant to a domain given by connection
	* **Arguments**: 
		* ``config``: `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_
	* **Description**: This variant of connect expects a domain connection config. Otherwise the behaviour is equivalent to the connect command with explicit arguments. If the domain is already configured, the domain connection will be attempted. If however the domain is offline, the command will fail. Generally, this macro should only be used to setup a new domain. However, for convenience, we support idempotent invocations where subsequent calls just ensure that the participant reconnects to the domain. 

.. _domains.connect_ha:


:ref:`domains.connect_ha <domains.connect_ha>`
	* **Summary**: Deprecated macro to connect a participant to a domain that supports connecting via many endpoints
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``firstConnection``: `com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
		* ``additionalConnections``: `com.digitalasset.canton.sequencing.SequencerConnection* <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_
	* **Description**: Use the command connect_ha with the updated arguments list

.. _domains.connect_local:


:ref:`domains.connect_local <domains.connect_local>`
	* **Summary**: Macro to connect a participant to a locally configured domain given by reference
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.console.InstanceReferenceWithSequencerConnection <../../canton/scaladoc/com/digitalasset/canton/console/InstanceReferenceWithSequencerConnection.html>`_
		* ``manualConnect``: Boolean
		* ``alias``: `Option[com.digitalasset.canton.DomainAlias] <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``maxRetryDelayMillis``: Option[Long]
		* ``priority``: Int
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**:      The arguments are:      domain - A local domain or sequencer reference      manualConnect - Whether this connection should be handled manually and also excluded from automatic re-connect.      alias - The name you will be using to refer to this domain. Can not be changed anymore.      certificatesPath - Path to TLS certificate files to use as a trust anchor.      priority - The priority of the domain. The higher the more likely a domain will be used.      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.     

.. _domains.connect_multi:


:ref:`domains.connect_multi <domains.connect_multi>`
	* **Summary**: Macro to connect a participant to a domain that supports connecting via many endpoints
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``connections``: `Seq[com.digitalasset.canton.sequencing.SequencerConnection] <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_
	* **Description**: Domains can provide many endpoints to connect to for availability and performance benefits.     This version of connect allows specifying multiple endpoints for a single domain connection:      connect_multi("mydomain", Seq(sequencer1, sequencer2))      or:      connect_multi("mydomain", Seq("https://host1.mydomain.net", "https://host2.mydomain.net", "https://host3.mydomain.net"))     To create a more advanced connection config use domains.toConfig with a single host, then use config.addConnection to add additional connections before connecting:      config = myparticipaint.domains.toConfig("mydomain", "https://host1.mydomain.net", ...otherArguments)      config = config.addConnection("https://host2.mydomain.net", "https://host3.mydomain.net")      myparticipant.domains.connect(config)     The arguments are:      domainAlias - The name you will be using to refer to this domain. Can not be changed anymore.      connections - The sequencer connection definitions (can be an URL) to connect to this domain. I.e. https://url:port      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.     

.. _domains.connect_single:


:ref:`domains.connect_single <domains.connect_single>`
	* **Summary**: Macro to connect a participant to a domain that supports a single sequencer connection
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``sequencerConnection``: `com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_
	* **Description**: Calls a `connect_multi` macro with a single sequencer connection. This is particularly useful if we have a reference to a remote sequencer and can easily get the respective sequencer connection <sequencer>.sequencerConnection.     The arguments are:      domainAlias - The name you will be using to refer to this domain. Can not be changed anymore.      sequencerConnection - A single sequencer connection to connect to this domain. I.e. https://url:port      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.     

.. _domains.disconnect:


:ref:`domains.disconnect <domains.disconnect>`
	* **Summary**: Disconnect this participant from the given domain
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_

.. _domains.disconnect_all:


:ref:`domains.disconnect_all <domains.disconnect_all>`
	* **Summary**: Disconnect this participant from all connected domains

.. _domains.disconnect_local:


:ref:`domains.disconnect_local <domains.disconnect_local>`
	* **Summary**: Disconnect this participant from the given local domain
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.console.DomainReference <../../canton/scaladoc/com/digitalasset/canton/console/DomainReference.html>`_

.. _domains.get_agreement:


:ref:`domains.get_agreement <domains.get_agreement>`
	* **Summary**: Get the service agreement of the given domain alias and if it has been accepted already.
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Return type**: 
		* Option[(com.digitalasset.canton.participant.admin.v0.Agreement, Boolean)]

.. _domains.help:


:ref:`domains.help <domains.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _domains.id_of:


:ref:`domains.id_of <domains.id_of>`
	* **Summary**: Returns the id of the given domain alias
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_

.. _domains.is_connected:


:ref:`domains.is_connected <domains.is_connected>`
	* **Summary**: Test whether a participant is connected to a domain reference
	* **Arguments**: 
		* ``reference``: `com.digitalasset.canton.console.commands.DomainAdministration <../../canton/scaladoc/com/digitalasset/canton/console/commands/DomainAdministration.html>`_
	* **Return type**: 
		* Boolean

.. _domains.is_registered:


:ref:`domains.is_registered <domains.is_registered>`
	* **Summary**: Returns true if a domain is registered using the given alias
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Return type**: 
		* Boolean

.. _domains.list_connected:


:ref:`domains.list_connected <domains.list_connected>`
	* **Summary**: List the connected domains of this participant
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListConnectedDomainsResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListConnectedDomainsResult.html>`_

.. _domains.list_registered:


:ref:`domains.list_registered <domains.list_registered>`
	* **Summary**: List the configured active domains of this participant
	* **Return type**: 
		* Seq[(com.digitalasset.canton.participant.domain.DomainConnectionConfig, Boolean)]

.. _domains.modify:


:ref:`domains.modify <domains.modify>`
	* **Summary**: Modify existing domain connection
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``modifier``: `com.digitalasset.canton.participant.domain.DomainConnectionConfig => com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_

.. _domains.reconnect:


:ref:`domains.reconnect <domains.reconnect>`
	* **Summary**: Reconnect this participant to the given domain
	* **Arguments**: 
		* ``domainAlias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``retry``: Boolean
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* Boolean
	* **Description**: Idempotent attempts to re-establish a connection to a certain domain. If retry is set to false, the command will throw an exception if unsuccessful. If retry is set to true, the command will terminate after the first attempt with the result, but the server will keep on retrying to connect to the domain.     The arguments are:      domainAlias - The name you will be using to refer to this domain. Can not be changed anymore.      retry - Whether the reconnect should keep on retrying until it succeeded or abort noisly if the connection attempt fails.      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.     

.. _domains.reconnect_all:


:ref:`domains.reconnect_all <domains.reconnect_all>`
	* **Summary**: Reconnect this participant to all domains which are not marked as manual start
	* **Arguments**: 
		* ``ignoreFailures``: Boolean
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**:     The arguments are:      ignoreFailures - If set to true (default), we'll attempt to connect to all, ignoring any failure      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.   

.. _domains.reconnect_local:


:ref:`domains.reconnect_local <domains.reconnect_local>`
	* **Summary**: Reconnect this participant to the given local domain
	* **Arguments**: 
		* ``ref``: `com.digitalasset.canton.console.DomainReference <../../canton/scaladoc/com/digitalasset/canton/console/DomainReference.html>`_
		* ``retry``: Boolean
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* Boolean
	* **Description**: Idempotent attempts to re-establish a connection to the given local domain. Same behaviour as generic reconnect.     The arguments are:      ref - The domain reference to connect to      retry - Whether the reconnect should keep on retrying until it succeeded or abort noisly if the connection attempt fails.      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.     

.. _domains.register:


:ref:`domains.register <domains.register>`
	* **Summary**: Register new domain connection
	* **Arguments**: 
		* ``config``: `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_
	* **Description**: When connecting to a domain, we need to register the domain connection and eventually accept the terms of service of the domain before we can connect. The registration process is therefore a subset of the operation. Therefore, register is equivalent to connect if the domain does not require a service agreement. However, you would usually call register only in advanced scripts.


Packages
~~~~~~~~

.. _packages.find:


:ref:`packages.find <packages.find>`
	* **Summary**: Find packages that contain a module with the given name
	* **Arguments**: 
		* ``moduleName``: String
		* ``limitPackages``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.participant.admin.v0.PackageDescription] <../../canton/scaladoc/com/digitalasset/canton/participant/admin/v0/PackageDescription.html>`_

.. _packages.help:


:ref:`packages.help <packages.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _packages.list:


:ref:`packages.list <packages.list>`
	* **Summary**: List packages stored on the participant
	* **Arguments**: 
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.participant.admin.v0.PackageDescription] <../../canton/scaladoc/com/digitalasset/canton/participant/admin/v0/PackageDescription.html>`_
	* **Description**: Supported arguments:     limit - Limit on the number of packages returned (defaults to canton.parameters.console.default-limit)     

.. _packages.list_contents:


:ref:`packages.list_contents <packages.list_contents>`
	* **Summary**: List package contents
	* **Arguments**: 
		* ``packageId``: String
	* **Return type**: 
		* `Seq[com.digitalasset.canton.participant.admin.v0.ModuleDescription] <../../canton/scaladoc/com/digitalasset/canton/participant/admin/v0/ModuleDescription.html>`_

.. _packages.remove:


:ref:`packages.remove (Preview) <packages.remove>`
	* **Summary**: Remove the package from Canton's package store.
	* **Arguments**: 
		* ``packageId``: String
		* ``force``: Boolean
	* **Description**: The standard operation of this command checks that a package is unused and unvetted, and if so removes the package. The force flag can be used to disable the checks, but do not use the force flag unless you're certain you know what you're doing. 

.. _packages.synchronize_vetting:


:ref:`packages.synchronize_vetting <packages.synchronize_vetting>`
	* **Summary**: Ensure that all vetting transactions issued by this participant have been observed by all configured participants
	* **Arguments**: 
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**: Sometimes, when scripting tests and demos, a dar or package is uploaded and we need to ensure that commands are only submitted once the package vetting has been observed by some other connected participant known to the console. This command can be used in such cases.


DAR Management
~~~~~~~~~~~~~~

.. _dars.download:


:ref:`dars.download <dars.download>`
	* **Summary**: Downloads the DAR file with the given hash to the given directory
	* **Arguments**: 
		* ``darHash``: String
		* ``directory``: String

.. _dars.help:


:ref:`dars.help <dars.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _dars.list:


:ref:`dars.list <dars.list>`
	* **Summary**: List installed DAR files
	* **Arguments**: 
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
		* ``filterName``: String
	* **Return type**: 
		* `Seq[com.digitalasset.canton.participant.admin.v0.DarDescription] <../../canton/scaladoc/com/digitalasset/canton/participant/admin/v0/DarDescription.html>`_
	* **Description**: List DARs installed on this participant The arguments are:  filterName: filter by name (source description)  limit: Limit number of results (default none)    

.. _dars.list_contents:


:ref:`dars.list_contents <dars.list_contents>`
	* **Summary**: List contents of DAR files
	* **Arguments**: 
		* ``hash``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.DarMetadata <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DarMetadata.html>`_

.. _dars.remove:


:ref:`dars.remove (Preview) <dars.remove>`
	* **Summary**: Remove a DAR from the participant
	* **Arguments**: 
		* ``darHash``: String
		* ``synchronizeVetting``: Boolean
	* **Description**: Can be used to remove a DAR from the participant, if the following conditions are satisfied: 1. The main package of the DAR must be unused -- there should be no active contract from this package 2. All package dependencies of the DAR should either be unused or contained in another of the participant node's uploaded DARs. Canton uses this restriction to ensure that the package dependencies of the DAR don't become "stranded" if they're in use. 3. The main package of the dar should not be vetted. If it is vetted, Canton will try to automatically  revoke the vetting for the main package of the DAR, but this automatic vetting revocation will only succeed if the  main package vetting originates from a standard ``dars.upload``. Even if the automatic revocation fails, you can  always manually revoke the package vetting. If synchronizeVetting is true (default), then the command will block until the participant has observed the vetting transactions to be registered with the domain. 

.. _dars.upload:


:ref:`dars.upload <dars.upload>`
	* **Summary**: Upload a Dar to Canton
	* **Arguments**: 
		* ``path``: String
		* ``vetAllPackages``: Boolean
		* ``synchronizeVetting``: Boolean
	* **Return type**: 
		* String
	* **Description**: Daml code is normally shipped as a Dar archive and must explicitly be uploaded to a participant. A Dar is a collection of LF-packages, the native binary representation of Daml smart contracts. In order to use Daml templates on a participant, the Dar must first be uploaded and then vetted by the participant. Vetting will ensure that other participants can check whether they can actually send a transaction referring to a particular Daml package and participant. Vetting is done by registering a VettedPackages topology transaction with the topology manager. By default, vetting happens automatically and this command waits for the vetting transaction to be successfully registered on all connected domains. This is the safe default setting minimizing race conditions. If vetAllPackages is true (default), the packages will all be vetted on all domains the participant is registered. If synchronizeVetting is true (default), then the command will block until the participant has observed the vetting transactions to be registered with the domain. If alsoSynchronizeCheckOnly is true (default), then the command will block until the participant has observed the check-only packages transactions on the domain. Note that synchronize vetting might block on permissioned domains that do not just allow participants to update the topology state. In such cases, synchronizeVetting should be turned off. Synchronize vetting can be invoked manually using $participant.package.synchronize_vettings() 

.. _dars.validate:


:ref:`dars.validate <dars.validate>`
	* **Summary**: Validate DARs against the current participants' state
	* **Arguments**: 
		* ``path``: String
	* **Return type**: 
		* String
	* **Description**: Performs the same DAR and Daml package validation checks that the upload call performs,     but with no effects on the target participants: the DAR is not persisted or vetted.


Party Management
~~~~~~~~~~~~~~~~
The party management commands allow to conveniently enable and disable parties on the local node. Under the hood,
they use the more complicated but feature-richer identity management commands.

.. _parties.await_topology_observed:


:ref:`parties.await_topology_observed (Preview) <parties.await_topology_observed>`
	* **Summary**: Waits for any topology changes to be observed
	* **Arguments**: 
		* ``partyAssignment``: Set[(com.digitalasset.canton.topology.PartyId, T)]
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**: Will throw an exception if the given topology has not been observed within the given timeout.

.. _parties.disable:


:ref:`parties.disable <parties.disable>`
	* **Summary**: Disable party on participant
	* **Arguments**: 
		* ``name``: `com.digitalasset.canton.topology.Identifier <../../canton/scaladoc/com/digitalasset/canton/topology/Identifier.html>`_
		* ``force``: Boolean

.. _parties.enable:


:ref:`parties.enable <parties.enable>`
	* **Summary**: Enable/add party to participant
	* **Arguments**: 
		* ``name``: String
		* ``displayName``: Option[String]
		* ``waitForDomain``: `com.digitalasset.canton.console.commands.DomainChoice <../../canton/scaladoc/com/digitalasset/canton/console/commands/DomainChoice.html>`_
		* ``synchronizeParticipants``: `Seq[com.digitalasset.canton.console.ParticipantReference] <../../canton/scaladoc/com/digitalasset/canton/console/ParticipantReference.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
	* **Description**: This function registers a new party with the current participant within the participants namespace. The function fails if the participant does not have appropriate signing keys to issue the corresponding PartyToParticipant topology transaction. Optionally, a local display name can be added. This display name will be exposed on the ledger API party management endpoint. Specifying a set of domains via the `WaitForDomain` parameter ensures that the domains have enabled/added a party by the time the call returns, but other participants connected to the same domains may not yet be aware of the party. Additionally, a sequence of additional participants can be added to be synchronized to ensure that the party is known to these participants as well before the function terminates. 

.. _parties.find:


:ref:`parties.find <parties.find>`
	* **Summary**: Find a party from a filter string
	* **Arguments**: 
		* ``filterParty``: String
	* **Return type**: 
		* `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
	* **Description**: Will search for all parties that match this filter string. If it finds exactly one party, it will return that one. Otherwise, the function will throw.

.. _parties.help:


:ref:`parties.help <parties.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _parties.hosted:


:ref:`parties.hosted <parties.hosted>`
	* **Summary**: List parties hosted by this participant
	* **Arguments**: 
		* ``filterParty``: String
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListPartiesResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListPartiesResult.html>`_
	* **Description**: Inspect the parties hosted by this participant as used for synchronisation. The response is built from the timestamped topology transactions of each domain, excluding the authorized store of the given node. The search will include all hosted parties and is equivalent to running the `list` method using the participant id of the invoking participant.    filterParty: Filter by parties starting with the given string.    filterDomain: Filter by domains whose id starts with the given string.    asOf: Optional timestamp to inspect the topology state at a given point in time.    limit: How many items to return (defaults to canton.parameters.console.default-limit)    Example: participant1.parties.hosted(filterParty="alice")

.. _parties.list:


:ref:`parties.list <parties.list>`
	* **Summary**: List active parties, their active participants, and the participants' permissions on domains.
	* **Arguments**: 
		* ``filterParty``: String
		* ``filterParticipant``: String
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListPartiesResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListPartiesResult.html>`_
	* **Description**: Inspect the parties known by this participant as used for synchronisation. The response is built from the timestamped topology transactions of each domain, excluding the authorized store of the given node. For each known party, the list of active participants and their permission on the domain for that party is given.    filterParty: Filter by parties starting with the given string.    filterParticipant: Filter for parties that are hosted by a participant with an id starting with the given string    filterDomain: Filter by domains whose id starts with the given string.    asOf: Optional timestamp to inspect the topology state at a given point in time.    limit: Limit on the number of parties fetched (defaults to canton.parameters.console.default-limit).    Example: participant1.parties.list(filterParty="alice")    

.. _parties.set_display_name:


:ref:`parties.set_display_name <parties.set_display_name>`
	* **Summary**: Set party display name
	* **Arguments**: 
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``displayName``: String
	* **Description**: Locally set the party display name (shown on the ledger-api) to the given value

.. _parties.update:


:ref:`parties.update <parties.update>`
	* **Summary**: Update participant-local party details
	* **Arguments**: 
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``modifier``: `com.digitalasset.canton.admin.api.client.data.PartyDetails => com.digitalasset.canton.admin.api.client.data.PartyDetails <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PartyDetails.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.PartyDetails <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PartyDetails.html>`_
	* **Description**: Currently you can update only the annotations. You cannot update other user attributes.      party: party to be updated,      modifier: a function to modify the party details, e.g.: `partyDetails => { partyDetails.copy(annotations = partyDetails.annotations.updated("a", "b").removed("c")) }`


Key Administration
~~~~~~~~~~~~~~~~~~

.. _keys.help:


:ref:`keys.help <keys.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


.. _keys.public.download:


:ref:`keys.public.download <keys.public.download>`
	* **Summary**: Download public key
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString

.. _keys.public.download_to:


:ref:`keys.public.download_to <keys.public.download_to>`
	* **Summary**: Download public key and save it to a file
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``outputFile``: String
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_

.. _keys.public.help:


:ref:`keys.public.help <keys.public.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _keys.public.list:


:ref:`keys.public.list <keys.public.list>`
	* **Summary**: List public keys in registry
	* **Arguments**: 
		* ``filterFingerprint``: String
		* ``filterContext``: String
	* **Return type**: 
		* `Seq[com.digitalasset.canton.crypto.PublicKeyWithName] <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKeyWithName.html>`_
	* **Description**: Returns all public keys that have been added to the key registry.   Optional arguments can be used for filtering.

.. _keys.public.list_by_owner:


:ref:`keys.public.list_by_owner <keys.public.list_by_owner>`
	* **Summary**: List keys for given keyOwner.
	* **Arguments**: 
		* ``keyOwner``: `com.digitalasset.canton.topology.KeyOwner <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwner.html>`_
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListKeyOwnersResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListKeyOwnersResult.html>`_
	* **Description**: This command is a convenience wrapper for `list_key_owners`, taking an explicit keyOwner as search argument. The response includes the public keys.

.. _keys.public.list_owners:


:ref:`keys.public.list_owners <keys.public.list_owners>`
	* **Summary**: List active owners with keys for given search arguments.
	* **Arguments**: 
		* ``filterKeyOwnerUid``: String
		* ``filterKeyOwnerType``: `Option[com.digitalasset.canton.topology.KeyOwnerCode] <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwnerCode.html>`_
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListKeyOwnersResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListKeyOwnersResult.html>`_
	* **Description**: This command allows deep inspection of the topology state. The response includes the public keys. Optional filterKeyOwnerType type can be 'ParticipantId.Code' , 'MediatorId.Code','SequencerId.Code', 'DomainTopologyManagerId.Code'. 

.. _keys.public.upload:


:ref:`keys.public.upload <keys.public.upload>`
	* **Summary**: Upload public key
	* **Arguments**: 
		* ``filename``: String
		* ``name``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_

.. _keys.public.upload_1:


:ref:`keys.public.upload <keys.public.upload_1>`
	* **Summary**: Upload public key
	* **Arguments**: 
		* ``keyBytes``: com.google.protobuf.ByteString
		* ``name``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Description**: Import a public key and store it together with a name used to provide some context to that key.


.. _keys.secret.delete:


:ref:`keys.secret.delete <keys.secret.delete>`
	* **Summary**: Delete private key
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``force``: Boolean

.. _keys.secret.download:


:ref:`keys.secret.download <keys.secret.download>`
	* **Summary**: Download key pair
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString

.. _keys.secret.download_to:


:ref:`keys.secret.download_to <keys.secret.download_to>`
	* **Summary**: Download key pair and save it to a file
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``outputFile``: String
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_

.. _keys.secret.generate_encryption_key:


:ref:`keys.secret.generate_encryption_key <keys.secret.generate_encryption_key>`
	* **Summary**: Generate new public/private key pair for encryption and store it in the vault
	* **Arguments**: 
		* ``name``: String
		* ``scheme``: `Option[com.digitalasset.canton.crypto.EncryptionKeyScheme] <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionKeyScheme.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.EncryptionPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionPublicKey.html>`_
	* **Description**:  The optional name argument allows you to store an associated string for your convenience. The scheme can be used to select a key scheme and the default scheme is used if left unspecified.

.. _keys.secret.generate_signing_key:


:ref:`keys.secret.generate_signing_key <keys.secret.generate_signing_key>`
	* **Summary**: Generate new public/private key pair for signing and store it in the vault
	* **Arguments**: 
		* ``name``: String
		* ``scheme``: `Option[com.digitalasset.canton.crypto.SigningKeyScheme] <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningKeyScheme.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.SigningPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningPublicKey.html>`_
	* **Description**:  The optional name argument allows you to store an associated string for your convenience. The scheme can be used to select a key scheme and the default scheme is used if left unspecified.

.. _keys.secret.get_wrapper_key_id:


:ref:`keys.secret.get_wrapper_key_id <keys.secret.get_wrapper_key_id>`
	* **Summary**: Get the wrapper key id that is used for the encrypted private keys store
	* **Return type**: 
		* String

.. _keys.secret.help:


:ref:`keys.secret.help <keys.secret.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _keys.secret.list:


:ref:`keys.secret.list <keys.secret.list>`
	* **Summary**: List keys in private vault
	* **Arguments**: 
		* ``filterFingerprint``: String
		* ``filterName``: String
		* ``purpose``: `Set[com.digitalasset.canton.crypto.KeyPurpose] <../../canton/scaladoc/com/digitalasset/canton/crypto/KeyPurpose.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.crypto.admin.grpc.PrivateKeyMetadata] <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/PrivateKeyMetadata.html>`_
	* **Description**: Returns all public keys to the corresponding private keys in the key vault. Optional arguments can be used for filtering.

.. _keys.secret.register_kms_encryption_key:


:ref:`keys.secret.register_kms_encryption_key <keys.secret.register_kms_encryption_key>`
	* **Summary**: Register the specified KMS encryption key in canton storing its public information in the vault
	* **Arguments**: 
		* ``kmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.EncryptionPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionPublicKey.html>`_
	* **Description**:  The id for the KMS encryption key. The optional name argument allows you to store an associated string for your convenience.

.. _keys.secret.register_kms_signing_key:


:ref:`keys.secret.register_kms_signing_key <keys.secret.register_kms_signing_key>`
	* **Summary**: Register the specified KMS signing key in canton storing its public information in the vault
	* **Arguments**: 
		* ``kmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.SigningPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningPublicKey.html>`_
	* **Description**:  The id for the KMS signing key. The optional name argument allows you to store an associated string for your convenience.

.. _keys.secret.rotate_kms_node_key:


:ref:`keys.secret.rotate_kms_node_key <keys.secret.rotate_kms_node_key>`
	* **Summary**: Rotate a given node's keypair with a new pre-generated KMS keypair
	* **Arguments**: 
		* ``fingerprint``: String
		* ``newKmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates an existing encryption or signing key stored externally in a KMS with a pre-generated    key. For a sequencer or mediator node use `rotate_kms_node_key` with a domain manager reference as an argument. The fingerprint of the key we want to rotate. The id of the new KMS key (e.g. Resource Name). An optional name for the new key.

.. _keys.secret.rotate_node_key:


:ref:`keys.secret.rotate_node_key <keys.secret.rotate_node_key>`
	* **Summary**: Rotate a node's public/private key pair
	* **Arguments**: 
		* ``fingerprint``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates an existing encryption or signing key. NOTE: A namespace root or intermediate    signing key CANNOT be rotated by this command. For a sequencer or mediator node use `rotate_kms_node_key` with    a domain manager reference as an argument. The fingerprint of the key we want to rotate. An optional name for the new key.

.. _keys.secret.rotate_node_keys:


:ref:`keys.secret.rotate_node_keys <keys.secret.rotate_node_keys>`
	* **Summary**: Rotate the node's public/private key pairs
	* **Description**:  For a participant node it rotates the signing and encryption key pair. For a domain or domain manager node it rotates the signing key pair as those nodes do not have an encryption key pair. For a sequencer or mediator node use `rotate_node_keys` with a domain manager reference as an argument. NOTE: Namespace root or intermediate signing keys are NOT rotated by this command.

.. _keys.secret.rotate_wrapper_key:


:ref:`keys.secret.rotate_wrapper_key <keys.secret.rotate_wrapper_key>`
	* **Summary**: Change the wrapper key for encrypted private keys store
	* **Arguments**: 
		* ``newWrapperKeyId``: String
	* **Description**: Change the wrapper key (e.g. AWS KMS key) being used to encrypt the private keys in the store. newWrapperKeyId: The optional new wrapper key id to be used. If the wrapper key id is empty Canton will generate a new key based on the current configuration.

.. _keys.secret.upload:


:ref:`keys.secret.upload <keys.secret.upload>`
	* **Summary**: Upload a key pair
	* **Arguments**: 
		* ``pairBytes``: com.google.protobuf.ByteString
		* ``name``: Option[String]

.. _keys.secret.upload_1:


:ref:`keys.secret.upload <keys.secret.upload_1>`
	* **Summary**: Upload (load and import) a key pair from file
	* **Arguments**: 
		* ``filename``: String
		* ``name``: Option[String]


.. _identity-commands:

Topology Administration
~~~~~~~~~~~~~~~~~~~~~~~

The topology commands can be used to manipulate and inspect the topology state.
In all commands, we use fingerprints to refer to public keys. Internally, these
fingerprints are resolved using the key registry (which is a map of Fingerprint -> PublicKey).
Any key can be added to the key registry using the ``keys.public.load`` commands.

.. _topology.help:


:ref:`topology.help <topology.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.init_id:


:ref:`topology.init_id <topology.init_id>`
	* **Summary**: Initialize the node with a unique identifier
	* **Arguments**: 
		* ``identifier``: `com.digitalasset.canton.topology.Identifier <../../canton/scaladoc/com/digitalasset/canton/topology/Identifier.html>`_
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.topology.UniqueIdentifier <../../canton/scaladoc/com/digitalasset/canton/topology/UniqueIdentifier.html>`_
	* **Description**: Every node in Canton is identified using a unique identifier, which is composed of a user-chosen string and the fingerprint of a signing key. The signing key is the root key defining a so-called namespace, where the signing key has the ultimate control over issuing new identifiers. During initialisation, we have to pick such a unique identifier. By default, initialisation happens automatically, but it can be turned off by setting the auto-init option to false. Automatic node initialisation is usually turned off to preserve the identity of a participant or domain node (during major version upgrades) or if the topology transactions are managed through a different topology manager than the one integrated into this node.

.. _topology.load_transaction:


:ref:`topology.load_transaction <topology.load_transaction>`
	* **Summary**: Upload signed topology transaction
	* **Arguments**: 
		* ``bytes``: com.google.protobuf.ByteString
	* **Description**: Topology transactions can be issued with any topology manager. In some cases, such transactions need to be copied manually between nodes. This function allows for uploading previously exported topology transaction into the authorized store (which is the name of the topology managers transaction store.


.. _topology.stores.help:


:ref:`topology.stores.help <topology.stores.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.stores.list:


:ref:`topology.stores.list <topology.stores.list>`
	* **Summary**: List available topology stores
	* **Return type**: 
		* Seq[String]
	* **Description**: Topology transactions are stored in these stores. There are the following stores: "Authorized" - The authorized store is the store of a topology manager. Updates to the topology state are made by adding new transactions to the "Authorized" store. Both the participant and the domain nodes topology manager have such a store. A participant node will distribute all the content in the Authorized store to the domains it is connected to. The domain node will distribute the content of the Authorized store through the sequencer to the domain members in order to create the authoritative topology state on a domain (which is stored in the store named using the domain-id), such that every domain member will have the same view on the topology state on a particular domain. "<domain-id>" - The domain store is the authorized topology state on a domain. A participant has one store for each domain it is connected to. The domain has exactly one store with its domain-id. "Requested" - A domain can be configured such that when participant tries to register a topology transaction with the domain, the transaction is placed into the "Requested" store such that it can be analysed and processed with user defined process. 


.. _topology.namespace_delegations.authorize:


:ref:`topology.namespace_delegations.authorize <topology.namespace_delegations.authorize>`
	* **Summary**: Change namespace delegation
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``namespace``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``authorizedKey``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``isRootDelegation``: Boolean
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Delegates the authority to authorize topology transactions in a certain namespace to a certain key. The keys are referred to using their fingerprints. They need to be either locally generated or have been previously imported.   ops: Either Add or Remove the delegation.   namespace: The namespace whose authorization authority is delegated.   signedBy: Optional fingerprint of the authorizing key. The authorizing key needs to be either the authorizedKey        for root certificates. Otherwise, the signedBy key needs to refer to a previously authorized key, which        means that we use the signedBy key to refer to a locally available CA.   authorizedKey: Fingerprint of the key to be authorized. If signedBy equals authorizedKey, then this transaction          corresponds to a self-signed root certificate. If the keys differ, then we get an intermediate CA.   isRootDelegation: If set to true (default = false), the authorized key will be allowed to issue NamespaceDelegations.   synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node

.. _topology.namespace_delegations.help:


:ref:`topology.namespace_delegations.help <topology.namespace_delegations.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.namespace_delegations.list:


:ref:`topology.namespace_delegations.list <topology.namespace_delegations.list>`
	* **Summary**: List namespace delegation transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterNamespace``: String
		* ``filterSigningKey``: String
		* ``filterTargetKey``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListNamespaceDelegationResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListNamespaceDelegationResult.html>`_
	* **Description**: List the namespace delegation transaction present in the stores. Namespace delegations are topology transactions that permission a key to issue topology transactions within a certain namespace.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterNamespace: Filter for namespaces starting with the given filter string.     filterTargetKey: Filter for namespaces delegations for the given target key.     protocolVersion: Export the topology transactions in the optional protocol version.     


.. _topology.identifier_delegations.authorize:


:ref:`topology.identifier_delegations.authorize <topology.identifier_delegations.authorize>`
	* **Summary**: Change identifier delegation
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``identifier``: `com.digitalasset.canton.topology.UniqueIdentifier <../../canton/scaladoc/com/digitalasset/canton/topology/UniqueIdentifier.html>`_
		* ``authorizedKey``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Delegates the authority of a certain identifier to a certain key. This corresponds to a normal certificate which binds identifier to a key. The keys are referred to using their fingerprints. They need to be either locally generated or have been previously imported.   ops: Either Add or Remove the delegation.   signedBy: Refers to the optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.   authorizedKey: Fingerprint of the key to be authorized.   synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    

.. _topology.identifier_delegations.help:


:ref:`topology.identifier_delegations.help <topology.identifier_delegations.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.identifier_delegations.list:


:ref:`topology.identifier_delegations.list <topology.identifier_delegations.list>`
	* **Summary**: List identifier delegation transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterUid``: String
		* ``filterSigningKey``: String
		* ``filterTargetKey``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListIdentifierDelegationResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListIdentifierDelegationResult.html>`_
	* **Description**: List the identifier delegation transaction present in the stores. Identifier delegations are topology transactions that permission a key to issue topology transactions for a certain unique identifier.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterUid: Filter for unique identifiers starting with the given filter string.     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.owner_to_key_mappings.authorize:


:ref:`topology.owner_to_key_mappings.authorize <topology.owner_to_key_mappings.authorize>`
	* **Summary**: Change an owner to key mapping
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``keyOwner``: `com.digitalasset.canton.topology.KeyOwner <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwner.html>`_
		* ``key``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``purpose``: `com.digitalasset.canton.crypto.KeyPurpose <../../canton/scaladoc/com/digitalasset/canton/crypto/KeyPurpose.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Change a owner to key mapping. A key owner is anyone in the system that needs a key-pair known to all members (participants, mediator, sequencer, topology manager) of a domain.  ops: Either Add or Remove the key mapping update.  signedBy: Optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.  ownerType: Role of the following owner (Participant, Sequencer, Mediator, DomainTopologyManager)  owner: Unique identifier of the owner.  key: Fingerprint of key  purposes: The purposes of the owner to key mapping.  force: removing the last key is dangerous and must therefore be manually forced  synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node  

.. _topology.owner_to_key_mappings.help:


:ref:`topology.owner_to_key_mappings.help <topology.owner_to_key_mappings.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.owner_to_key_mappings.list:


:ref:`topology.owner_to_key_mappings.list <topology.owner_to_key_mappings.list>`
	* **Summary**: List owner to key mapping transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterKeyOwnerType``: `Option[com.digitalasset.canton.topology.KeyOwnerCode] <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwnerCode.html>`_
		* ``filterKeyOwnerUid``: String
		* ``filterKeyPurpose``: `Option[com.digitalasset.canton.crypto.KeyPurpose] <../../canton/scaladoc/com/digitalasset/canton/crypto/KeyPurpose.html>`_
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListOwnerToKeyMappingResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListOwnerToKeyMappingResult.html>`_
	* **Description**: List the owner to key mapping transactions present in the stores. Owner to key mappings are topology transactions defining that a certain key is used by a certain key owner. Key owners are participants, sequencers, mediators and domains.    filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)    useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.    timeQuery: The time query allows to customize the query by time. The following options are supported:         TimeQuery.HeadState (default): The most recent known state.         TimeQuery.Snapshot(ts): The state at a certain point in time.         TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store    operation: Optionally, what type of operation the transaction should have. State store only has "Add".    filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.    filterKeyOwnerType: Filter for a particular type of key owner (KeyOwnerCode).    filterKeyOwnerUid: Filter for key owners unique identifier starting with the given filter string.    filterKeyPurpose: Filter for keys with a particular purpose (Encryption or Signing)    protocolVersion: Export the topology transactions in the optional protocol version. 

.. _topology.owner_to_key_mappings.rotate_key:


:ref:`topology.owner_to_key_mappings.rotate_key <topology.owner_to_key_mappings.rotate_key>`
	* **Summary**: Rotate the key for an owner to key mapping
	* **Arguments**: 
		* ``nodeInstance``: `com.digitalasset.canton.console.InstanceReferenceCommon <../../canton/scaladoc/com/digitalasset/canton/console/InstanceReferenceCommon.html>`_
		* ``owner``: `com.digitalasset.canton.topology.KeyOwner <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwner.html>`_
		* ``currentKey``: `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
		* ``newKey``: `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates the key for an existing owner to key mapping by issuing a new owner to key mapping with the new key and removing the previous owner to key mapping with the previous key.    nodeInstance: The node instance that is used to verify that both current and new key pertain to this node. This avoids conflicts when there are different nodes with the same uuid (i.e., multiple sequencers).    owner: The owner of the owner to key mapping    currentKey: The current public key that will be rotated    newKey: The new public key that has been generated 


.. _topology.party_to_participant_mappings.authorize:


:ref:`topology.party_to_participant_mappings.authorize (Preview) <topology.party_to_participant_mappings.authorize>`
	* **Summary**: Change party to participant mapping
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``participant``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``side``: `com.digitalasset.canton.topology.transaction.RequestSide <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/RequestSide.html>`_
		* ``permission``: `com.digitalasset.canton.topology.transaction.ParticipantPermission <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/ParticipantPermission.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``replaceExisting``: Boolean
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Change the association of a party to a participant. If both identifiers are in the same namespace, then the request-side is Both. If they differ, then we need to say whether the request comes from the party (RequestSide.From) or from the participant (RequestSide.To). And, we need the matching request of the other side. Please note that this is a preview feature due to the fact that inhomogeneous topologies can not yet be properly represented on the Ledger API.    ops: Either Add or Remove the mapping    signedBy: Refers to the optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.    party: The unique identifier of the party we want to map to a participant.    participant: The unique identifier of the participant to which the party is supposed to be mapped.    side: The request side (RequestSide.From if we the transaction is from the perspective of the party, RequestSide.To from the participant.)    privilege: The privilege of the given participant which allows us to restrict an association (e.g. Confirmation or Observation).    replaceExisting: If true (default), replace any existing mapping with the new setting    synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    

.. _topology.party_to_participant_mappings.help:


:ref:`topology.party_to_participant_mappings.help <topology.party_to_participant_mappings.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.party_to_participant_mappings.list:


:ref:`topology.party_to_participant_mappings.list <topology.party_to_participant_mappings.list>`
	* **Summary**: List party to participant mapping transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterParty``: String
		* ``filterParticipant``: String
		* ``filterRequestSide``: `Option[com.digitalasset.canton.topology.transaction.RequestSide] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/RequestSide.html>`_
		* ``filterPermission``: `Option[com.digitalasset.canton.topology.transaction.ParticipantPermission] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/ParticipantPermission.html>`_
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListPartyToParticipantResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListPartyToParticipantResult.html>`_
	* **Description**: List the party to participant mapping transactions present in the stores. Party to participant mappings are topology transactions used to allocate a party to a certain participant. The same party can be allocated on several participants with different privileges. A party to participant mapping has a request-side that identifies whether the mapping is authorized by the party, by the participant or by both. In order to have a party be allocated to a given participant, we therefore need either two transactions (one with RequestSide.From, one with RequestSide.To) or one with RequestSide.Both.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterParty: Filter for parties starting with the given filter string.     filterParticipant: Filter for participants starting with the given filter string.     filterRequestSide: Optional filter for a particular request side (Both, From, To).     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.participant_domain_states.active:


:ref:`topology.participant_domain_states.active <topology.participant_domain_states.active>`
	* **Summary**: Returns true if the given participant is currently active on the given domain
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``participantId``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
	* **Return type**: 
		* Boolean
	* **Description**: Active means that the participant has been granted at least observation rights on the domain and that the participant has registered a domain trust certificate

.. _topology.participant_domain_states.authorize:


:ref:`topology.participant_domain_states.authorize <topology.participant_domain_states.authorize>`
	* **Summary**: Change participant domain states
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``domain``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``participant``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``side``: `com.digitalasset.canton.topology.transaction.RequestSide <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/RequestSide.html>`_
		* ``permission``: `com.digitalasset.canton.topology.transaction.ParticipantPermission <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/ParticipantPermission.html>`_
		* ``trustLevel``: `com.digitalasset.canton.topology.transaction.TrustLevel <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TrustLevel.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``replaceExisting``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Change the association of a participant to a domain. In order to activate a participant on a domain, we need both authorisation: the participant authorising its uid to be present on a particular domain and the domain to authorise the presence of a participant on said domain. If both identifiers are in the same namespace, then the request-side can be Both. If they differ, then we need to say whether the request comes from the domain (RequestSide.From) or from the participant (RequestSide.To). And, we need the matching request of the other side.    ops: Either Add or Remove the mapping    signedBy: Refers to the optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.    domain: The unique identifier of the domain we want the participant to join.    participant: The unique identifier of the participant.    side: The request side (RequestSide.From if we the transaction is from the perspective of the domain, RequestSide.To from the participant.)    permission: The privilege of the given participant which allows us to restrict an association (e.g. Confirmation or Observation). Will use the lower of if different between To/From.    trustLevel: The trust level of the participant on the given domain. Will use the lower of if different between To/From.    replaceExisting: If true (default), replace any existing mapping with the new setting    synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    

.. _topology.participant_domain_states.help:


:ref:`topology.participant_domain_states.help <topology.participant_domain_states.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.participant_domain_states.list:


:ref:`topology.participant_domain_states.list <topology.participant_domain_states.list>`
	* **Summary**: List participant domain states
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterDomain``: String
		* ``filterParticipant``: String
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListParticipantDomainStateResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListParticipantDomainStateResult.html>`_
	* **Description**: List the participant domain transactions present in the stores. Participant domain states are topology transactions used to permission a participant on a given domain. A participant domain state has a request-side that identifies whether the mapping is authorized by the participant (From), by the domain (To) or by both (Both). In order to use a participant on a domain, both have to authorize such a mapping. This means that by authorizing such a topology transaction, a participant acknowledges its presence on a domain, whereas a domain permissions the participant on that domain.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterDomain: Filter for domains starting with the given filter string.     filterParticipant: Filter for participants starting with the given filter string.     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.vetted_packages.authorize:


:ref:`topology.vetted_packages.authorize <topology.vetted_packages.authorize>`
	* **Summary**: Change package vettings
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``participant``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``packageIds``: Seq[com.daml.lf.data.Ref.PackageId]
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: A participant will only process transactions that reference packages that all involved participants have vetted previously. Vetting is done by registering a respective topology transaction with the domain, which can then be used by other participants to verify that a transaction is only using vetted packages. Note that all referenced and dependent packages must exist in the package store. By default, only vetting transactions adding new packages can be issued. Removing package vettings and issuing package vettings for other participants (if their identity is controlled through this participants topology manager) or for packages that do not exist locally can only be run using the force = true flag. However, these operations are dangerous and can lead to the situation of a participant being unable to process transactions.    ops: Either Add or Remove the vetting.    participant: The unique identifier of the participant that is vetting the package.    packageIds: The lf-package ids to be vetted.    signedBy: Refers to the fingerprint of the authorizing key which in turn must be authorized by a valid, locally existing certificate.  If none is given, a key is automatically determined.    synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    force: Flag to enable dangerous operations (default false). Great power requires great care.    

.. _topology.vetted_packages.help:


:ref:`topology.vetted_packages.help <topology.vetted_packages.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.vetted_packages.list:


:ref:`topology.vetted_packages.list <topology.vetted_packages.list>`
	* **Summary**: List package vetting transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterParticipant``: String
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListVettedPackagesResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListVettedPackagesResult.html>`_
	* **Description**: List the package vetting transactions present in the stores. Participants must vet Daml packages and submitters must ensure that the receiving participants have vetted the package prior to submitting a transaction (done automatically during submission and validation). Vetting is done by authorizing such topology transactions and registering with a domain.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterParticipant: Filter for participants starting with the given filter string.     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.all.help:


:ref:`topology.all.help <topology.all.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.all.list:


:ref:`topology.all.list <topology.all.list>`
	* **Summary**: List all transaction
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterAuthorizedKey``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.topology.store.StoredTopologyTransactions[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
	* **Description**: List all topology transactions in a store, independent of the particular type. This method is useful for exporting entire states.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterAuthorizedKey: Filter the topology transactions by the key that has authorized the transactions.     protocolVersion: Export the topology transactions in the optional protocol version. 

.. _topology.all.renew:


:ref:`topology.all.renew <topology.all.renew>`
	* **Summary**: Renew all topology transactions that have been authorized with a previous key using a new key
	* **Arguments**: 
		* ``filterAuthorizedKey``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``authorizeWith``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Description**: Finds all topology transactions that have been authorized by `filterAuthorizedKey` and renews those topology transactions by authorizing them with the new key `authorizeWith`.     filterAuthorizedKey: Filter the topology transactions by the key that has authorized the transactions.     authorizeWith: The key to authorize the renewed topology transactions. 


Ledger API Access
~~~~~~~~~~~~~~~~~
The following commands on a participant reference provide access to the participant's Ledger API services.

.. _ledger_api.help:


:ref:`ledger_api.help <ledger_api.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


.. _ledger-api-transaction-service:

Transaction Service
^^^^^^^^^^^^^^^^^^^

.. _ledger_api.transactions.by_id:


:ref:`ledger_api.transactions.by_id (Testing) <ledger_api.transactions.by_id>`
	* **Summary**: Get a (tree) transaction by its ID
	* **Arguments**: 
		* ``parties``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``id``: String
	* **Return type**: 
		* Option[com.daml.ledger.api.v1.transaction.TransactionTree]
	* **Description**: Get a transaction tree from the transaction stream by its ID. Returns None if the transaction is not (yet) known at the participant or if the transaction has been pruned via `pruning.prune`.

.. _ledger_api.transactions.domain_of:


:ref:`ledger_api.transactions.domain_of (Testing) <ledger_api.transactions.domain_of>`
	* **Summary**: Get the domain that a transaction was committed over.
	* **Arguments**: 
		* ``transactionId``: String
	* **Return type**: 
		* `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
	* **Description**: Get the domain that a transaction was committed over. Throws an error if the transaction is not (yet) known to the participant or if the transaction has been pruned via `pruning.prune`.

.. _ledger_api.transactions.end:


:ref:`ledger_api.transactions.end (Testing) <ledger_api.transactions.end>`
	* **Summary**: Get ledger end
	* **Return type**: 
		* com.daml.ledger.api.v1.ledger_offset.LedgerOffset

.. _ledger_api.transactions.flat:


:ref:`ledger_api.transactions.flat (Testing) <ledger_api.transactions.flat>`
	* **Summary**: Get flat transactions
	* **Arguments**: 
		* ``partyIds``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``completeAfter``: Int
		* ``beginOffset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``endOffset``: Option[com.daml.ledger.api.v1.ledger_offset.LedgerOffset]
		* ``verbose``: Boolean
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* Seq[com.daml.ledger.api.v1.transaction.Transaction]
	* **Description**: This function connects to the flat transaction stream for the given parties and collects transactions until either `completeAfter` transaction trees have been received or `timeout` has elapsed. The returned transactions can be filtered to be between the given offsets (default: no filtering). If the participant has been pruned via `pruning.prune` and if `beginOffset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error. If you need to specify filtering conditions for template IDs and including create event blobs for explicit disclosure, consider using `ledger_api.transactions.flat_with_tx_filter`.

.. _ledger_api.transactions.flat_with_tx_filter:


:ref:`ledger_api.transactions.flat_with_tx_filter (Testing) <ledger_api.transactions.flat_with_tx_filter>`
	* **Summary**: Get flat transactions
	* **Arguments**: 
		* ``filter``: com.daml.ledger.api.v1.transaction_filter.TransactionFilter
		* ``completeAfter``: Int
		* ``beginOffset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``endOffset``: Option[com.daml.ledger.api.v1.ledger_offset.LedgerOffset]
		* ``verbose``: Boolean
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* Seq[com.daml.ledger.api.v1.transaction.Transaction]
	* **Description**: This function connects to the flat transaction stream for the given transaction filter and collects transactions until either `completeAfter` transactions have been received or `timeout` has elapsed. The returned transactions can be filtered to be between the given offsets (default: no filtering). If the participant has been pruned via `pruning.prune` and if `beginOffset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error. If you only need to filter by a set of parties, consider using `ledger_api.transactions.flat` instead.

.. _ledger_api.transactions.help:


:ref:`ledger_api.transactions.help <ledger_api.transactions.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.transactions.start_measuring:


:ref:`ledger_api.transactions.start_measuring (Testing) <ledger_api.transactions.start_measuring>`
	* **Summary**: Starts measuring throughput at the transaction service
	* **Arguments**: 
		* ``parties``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``metricSuffix``: String
		* ``onTransaction``: com.daml.ledger.api.v1.transaction.TransactionTree => Unit
	* **Return type**: 
		* AutoCloseable
	* **Description**: This function will subscribe on behalf of `parties` to the transaction tree stream and notify various metrics: The metric `<name>.<metricSuffix>` counts the number of transaction trees emitted. The metric `<name>.<metricSuffix>-tx-node-count` tracks the number of root events emitted as part of transaction trees. The metric `<name>.<metricSuffix>-tx-size` tracks the number of bytes emitted as part of transaction trees. To stop measuring, you need to close the returned `AutoCloseable`. Use the `onTransaction` parameter to register a callback that is called on every transaction tree.

.. _ledger_api.transactions.subscribe_flat:


:ref:`ledger_api.transactions.subscribe_flat (Testing) <ledger_api.transactions.subscribe_flat>`
	* **Summary**: Subscribe to the flat transaction stream
	* **Arguments**: 
		* ``observer``: io.grpc.stub.StreamObserver[com.daml.ledger.api.v1.transaction.Transaction]
		* ``filter``: com.daml.ledger.api.v1.transaction_filter.TransactionFilter
		* ``beginOffset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``endOffset``: Option[com.daml.ledger.api.v1.ledger_offset.LedgerOffset]
		* ``verbose``: Boolean
	* **Return type**: 
		* AutoCloseable
	* **Description**: This function connects to the flat transaction stream and passes transactions to `observer` until the stream is completed. Only transactions for parties in `filter.filterByParty.keys` will be returned. Use `filter = TransactionFilter(Map(myParty.toLf -> Filters()))` to return all transactions for `myParty: PartyId`. The returned transactions can be filtered to be between the given offsets (default: no filtering). If the participant has been pruned via `pruning.prune` and if `beginOffset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error.

.. _ledger_api.transactions.subscribe_trees:


:ref:`ledger_api.transactions.subscribe_trees (Testing) <ledger_api.transactions.subscribe_trees>`
	* **Summary**: Subscribe to the transaction tree stream
	* **Arguments**: 
		* ``observer``: io.grpc.stub.StreamObserver[com.daml.ledger.api.v1.transaction.TransactionTree]
		* ``filter``: com.daml.ledger.api.v1.transaction_filter.TransactionFilter
		* ``beginOffset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``endOffset``: Option[com.daml.ledger.api.v1.ledger_offset.LedgerOffset]
		* ``verbose``: Boolean
	* **Return type**: 
		* AutoCloseable
	* **Description**: This function connects to the transaction tree stream and passes transaction trees to `observer` until the stream is completed. Only transaction trees for parties in `filter.filterByParty.keys` will be returned. Use `filter = TransactionFilter(Map(myParty.toLf -> Filters()))` to return all trees for `myParty: PartyId`. The returned transactions can be filtered to be between the given offsets (default: no filtering). If the participant has been pruned via `pruning.prune` and if `beginOffset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error.

.. _ledger_api.transactions.trees:


:ref:`ledger_api.transactions.trees (Testing) <ledger_api.transactions.trees>`
	* **Summary**: Get transaction trees
	* **Arguments**: 
		* ``partyIds``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``completeAfter``: Int
		* ``beginOffset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``endOffset``: Option[com.daml.ledger.api.v1.ledger_offset.LedgerOffset]
		* ``verbose``: Boolean
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* Seq[com.daml.ledger.api.v1.transaction.TransactionTree]
	* **Description**: This function connects to the transaction tree stream for the given parties and collects transaction trees until either `completeAfter` transaction trees have been received or `timeout` has elapsed. The returned transaction trees can be filtered to be between the given offsets (default: no filtering). If the participant has been pruned via `pruning.prune` and if `beginOffset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error.


Command Service
^^^^^^^^^^^^^^^

.. _ledger_api.commands.failed:


:ref:`ledger_api.commands.failed (Testing) <ledger_api.commands.failed>`
	* **Summary**: Investigate failed commands
	* **Arguments**: 
		* ``commandId``: String
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.platform.apiserver.execution.CommandStatus] <../../canton/scaladoc/com/digitalasset/canton/platform/apiserver/execution/CommandStatus.html>`_
	* **Description**: Same as status(..., state = CommandState.Failed).

.. _ledger_api.commands.help:


:ref:`ledger_api.commands.help <ledger_api.commands.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.commands.status:


:ref:`ledger_api.commands.status (Testing) <ledger_api.commands.status>`
	* **Summary**: Investigate successful and failed commands
	* **Arguments**: 
		* ``commandIdPrefix``: String
		* ``state``: com.daml.ledger.api.v1.admin.command_inspection_service.CommandState
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.platform.apiserver.execution.CommandStatus] <../../canton/scaladoc/com/digitalasset/canton/platform/apiserver/execution/CommandStatus.html>`_
	* **Description**: Find the status of commands. Note that only recent commands which are kept in memory will be returned.

.. _ledger_api.commands.submit:


:ref:`ledger_api.commands.submit (Testing) <ledger_api.commands.submit>`
	* **Summary**: Submit command and wait for the resulting transaction, returning the transaction tree or failing otherwise
	* **Arguments**: 
		* ``actAs``: `Seq[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``commands``: Seq[com.daml.ledger.api.v1.commands.Command]
		* ``workflowId``: String
		* ``commandId``: String
		* ``optTimeout``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``deduplicationPeriod``: `Option[com.digitalasset.canton.ledger.api.DeduplicationPeriod] <../../canton/scaladoc/com/digitalasset/canton/ledger/api/DeduplicationPeriod.html>`_
		* ``submissionId``: String
		* ``minLedgerTimeAbs``: Option[java.time.Instant]
		* ``readAs``: `Seq[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``disclosedContracts``: Seq[com.daml.ledger.api.v1.commands.DisclosedContract]
		* ``applicationId``: String
		* ``userPackageSelectionPreference``: Seq[com.digitalasset.canton.LfPackageId]
	* **Return type**: 
		* com.daml.ledger.api.v1.transaction.TransactionTree
	* **Description**: Submits a command on behalf of the `actAs` parties, waits for the resulting transaction to commit and returns it. If the timeout is set, it also waits for the transaction to appear at all other configured participants who were involved in the transaction. The call blocks until the transaction commits or fails; the timeout only specifies how long to wait at the other participants. Fails if the transaction doesn't commit, or if it doesn't become visible to the involved participants in the allotted time. Note that if the optTimeout is set and the involved parties are concurrently enabled/disabled or their participants are connected/disconnected, the command may currently result in spurious timeouts or may return before the transaction appears at all the involved participants.

.. _ledger_api.commands.submit_async:


:ref:`ledger_api.commands.submit_async (Testing) <ledger_api.commands.submit_async>`
	* **Summary**: Submit command asynchronously
	* **Arguments**: 
		* ``actAs``: `Seq[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``commands``: Seq[com.daml.ledger.api.v1.commands.Command]
		* ``workflowId``: String
		* ``commandId``: String
		* ``deduplicationPeriod``: `Option[com.digitalasset.canton.ledger.api.DeduplicationPeriod] <../../canton/scaladoc/com/digitalasset/canton/ledger/api/DeduplicationPeriod.html>`_
		* ``submissionId``: String
		* ``minLedgerTimeAbs``: Option[java.time.Instant]
		* ``readAs``: `Seq[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``disclosedContracts``: Seq[com.daml.ledger.api.v1.commands.DisclosedContract]
		* ``applicationId``: String
		* ``userPackageSelectionPreference``: Seq[com.digitalasset.canton.LfPackageId]
	* **Description**: Provides access to the command submission service of the Ledger API. See https://docs.daml.com/app-dev/services.html for documentation of the parameters.

.. _ledger_api.commands.submit_flat:


:ref:`ledger_api.commands.submit_flat (Testing) <ledger_api.commands.submit_flat>`
	* **Summary**: Submit command and wait for the resulting transaction, returning the flattened transaction or failing otherwise
	* **Arguments**: 
		* ``actAs``: `Seq[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``commands``: Seq[com.daml.ledger.api.v1.commands.Command]
		* ``workflowId``: String
		* ``commandId``: String
		* ``optTimeout``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``deduplicationPeriod``: `Option[com.digitalasset.canton.ledger.api.DeduplicationPeriod] <../../canton/scaladoc/com/digitalasset/canton/ledger/api/DeduplicationPeriod.html>`_
		* ``submissionId``: String
		* ``minLedgerTimeAbs``: Option[java.time.Instant]
		* ``readAs``: `Seq[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``disclosedContracts``: Seq[com.daml.ledger.api.v1.commands.DisclosedContract]
		* ``applicationId``: String
		* ``userPackageSelectionPreference``: Seq[com.digitalasset.canton.LfPackageId]
	* **Return type**: 
		* com.daml.ledger.api.v1.transaction.Transaction
	* **Description**: Submits a command on behalf of the `actAs` parties, waits for the resulting transaction to commit, and returns the "flattened" transaction. If the timeout is set, it also waits for the transaction to appear at all other configured participants who were involved in the transaction. The call blocks until the transaction commits or fails; the timeout only specifies how long to wait at the other participants. Fails if the transaction doesn't commit, or if it doesn't become visible to the involved participants in the allotted time. Note that if the optTimeout is set and the involved parties are concurrently enabled/disabled or their participants are connected/disconnected, the command may currently result in spurious timeouts or may return before the transaction appears at all the involved participants.


Command Completion Service
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. _ledger_api.completions.end:


:ref:`ledger_api.completions.end (Testing) <ledger_api.completions.end>`
	* **Summary**: Read the current command completion offset
	* **Return type**: 
		* com.daml.ledger.api.v1.ledger_offset.LedgerOffset

.. _ledger_api.completions.help:


:ref:`ledger_api.completions.help <ledger_api.completions.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.completions.list:


:ref:`ledger_api.completions.list (Testing) <ledger_api.completions.list>`
	* **Summary**: Lists command completions following the specified offset
	* **Arguments**: 
		* ``partyId``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``atLeastNumCompletions``: Int
		* ``offset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``applicationId``: String
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``filter``: com.daml.ledger.api.v1.completion.Completion => Boolean
	* **Return type**: 
		* Seq[com.daml.ledger.api.v1.completion.Completion]
	* **Description**: If the participant has been pruned via `pruning.prune` and if `offset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error.

.. _ledger_api.completions.list_with_checkpoint:


:ref:`ledger_api.completions.list_with_checkpoint (Testing) <ledger_api.completions.list_with_checkpoint>`
	* **Summary**: Lists command completions following the specified offset along with the checkpoints included in the completions
	* **Arguments**: 
		* ``partyId``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``atLeastNumCompletions``: Int
		* ``offset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``applicationId``: String
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``filter``: com.daml.ledger.api.v1.completion.Completion => Boolean
	* **Return type**: 
		* Seq[(com.daml.ledger.api.v1.completion.Completion, Option[com.daml.ledger.api.v1.command_completion_service.Checkpoint])]
	* **Description**: If the participant has been pruned via `pruning.prune` and if `offset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error.

.. _ledger_api.completions.subscribe:


:ref:`ledger_api.completions.subscribe (Testing) <ledger_api.completions.subscribe>`
	* **Summary**: Subscribe to the command completion stream
	* **Arguments**: 
		* ``observer``: io.grpc.stub.StreamObserver[com.daml.ledger.api.v1.completion.Completion]
		* ``parties``: `Seq[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``beginOffset``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
		* ``applicationId``: String
	* **Return type**: 
		* AutoCloseable
	* **Description**: This function connects to the command completion stream and passes command completions to `observer` until the stream is completed. Only completions for parties in `parties` will be returned. The returned completions start at `beginOffset` (default: `LEDGER_BEGIN`). If the participant has been pruned via `pruning.prune` and if `beginOffset` is lower than the pruning offset, this command fails with a `NOT_FOUND` error.


Active Contract Service
^^^^^^^^^^^^^^^^^^^^^^^

.. _ledger_api.acs.await_active_contract:


:ref:`ledger_api.acs.await_active_contract (Testing) <ledger_api.acs.await_active_contract>`
	* **Summary**: Wait until the party sees the given contract in the active contract service
	* **Arguments**: 
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``contractId``: `com.digitalasset.canton.protocol.LfContractId <../../canton/scaladoc/com/digitalasset/canton/protocol/index.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**: Will throw an exception if the contract is not found to be active within the given timeout

.. _ledger_api.acs.find_generic:


:ref:`ledger_api.acs.find_generic (Testing) <ledger_api.acs.find_generic>`
	* **Summary**: Generic search for contracts
	* **Arguments**: 
		* ``partyId``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``filter``: `com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent => Boolean <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/commands/LedgerApiTypeWrappers$$WrappedCreatedEvent.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/commands/LedgerApiTypeWrappers$$WrappedCreatedEvent.html>`_
	* **Description**: This search function returns an untyped ledger-api event. The find will wait until the contract appears or throw an exception once it times out.

.. _ledger_api.acs.help:


:ref:`ledger_api.acs.help <ledger_api.acs.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.acs.of_all:


:ref:`ledger_api.acs.of_all (Testing) <ledger_api.acs.of_all>`
	* **Summary**: List the set of active contracts for all parties hosted on this participant
	* **Arguments**: 
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
		* ``verbose``: Boolean
		* ``filterTemplates``: `Seq[com.digitalasset.canton.admin.api.client.data.TemplateId] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/TemplateId.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``identityProviderId``: String
		* ``includeCreatedEventBlob``: Boolean
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/commands/LedgerApiTypeWrappers$$WrappedCreatedEvent.html>`_
	* **Description**: This command will return the current set of active contracts for all parties.       Supported arguments:      - limit: limit (default set via canton.parameter.console)      - verbose: whether the resulting events should contain detailed type information      - filterTemplate: list of templates ids to filter for, empty sequence acts as a wildcard      - timeout: the maximum wait time for the complete acs to arrive      - identityProviderId: limit the response to parties governed by the given identity provider      - includeCreatedEventBlob: whether the result should contain the createdEventBlobs, it works only       if the filterTemplate is non-empty     

.. _ledger_api.acs.of_party:


:ref:`ledger_api.acs.of_party (Testing) <ledger_api.acs.of_party>`
	* **Summary**: List the set of active contracts of a given party
	* **Arguments**: 
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
		* ``verbose``: Boolean
		* ``filterTemplates``: `Seq[com.digitalasset.canton.admin.api.client.data.TemplateId] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/TemplateId.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``includeCreatedEventBlob``: Boolean
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/commands/LedgerApiTypeWrappers$$WrappedCreatedEvent.html>`_
	* **Description**: This command will return the current set of active contracts for the given party.       Supported arguments:      - party: for which party you want to load the acs      - limit: limit (default set via canton.parameter.console)      - verbose: whether the resulting events should contain detailed type information      - filterTemplate: list of templates ids to filter for, empty sequence acts as a wildcard      - timeout: the maximum wait time for the complete acs to arrive      - includeCreatedEventBlob: whether the result should contain the createdEventBlobs, it works only       if the filterTemplate is non-empty     


Package Service
^^^^^^^^^^^^^^^

.. _ledger_api.packages.check_upgrade_validity:


:ref:`ledger_api.packages.check_upgrade_validity <ledger_api.packages.check_upgrade_validity>`
	* **Summary**: Check a participant's Daml packages for upgrade validity
	* **Description**: Checks the upgradable Daml packages (compiled with LF 1.17) persisted on the participant for upgrade validity. It is recommended to run this check for all participants upgrading from Canton 2.10.0, before the upgrade procedure is started. If you are upgrading from older Canton versions (2.9.x and older) to Canton 2.10.1+, this check is not necessary. This command will fail if some packages in the participant's package store are not upgrade-compatible. Note: This command does not upload or modify any packages on the participant.

.. _ledger_api.packages.help:


:ref:`ledger_api.packages.help <ledger_api.packages.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.packages.list:


:ref:`ledger_api.packages.list (Testing) <ledger_api.packages.list>`
	* **Summary**: List Daml Packages
	* **Arguments**: 
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* Seq[com.daml.ledger.api.v1.admin.package_management_service.PackageDetails]

.. _ledger_api.packages.upload_dar:


:ref:`ledger_api.packages.upload_dar (Testing) <ledger_api.packages.upload_dar>`
	* **Summary**: Upload packages from Dar file
	* **Arguments**: 
		* ``darPath``: String
	* **Description**: Uploading the Dar can be done either through the ledger Api server or through the Canton admin Api. The Ledger Api is the portable method across ledgers. The Canton admin Api is more powerful as it allows for controlling Canton specific behaviour. In particular, a Dar uploaded using the ledger Api will not be available in the Dar store and can not be downloaded again. Additionally, Dars uploaded using the ledger Api will be vetted, but the system will not wait for the Dars to be successfully registered with all connected domains. As such, if a Dar is uploaded and then used immediately thereafter, a command might bounce due to missing package vettings.

.. _ledger_api.packages.validate_dar:


:ref:`ledger_api.packages.validate_dar (Testing) <ledger_api.packages.validate_dar>`
	* **Summary**: Validate a DAR against the current participants' state
	* **Arguments**: 
		* ``darPath``: String
	* **Description**: Performs the same DAR and Daml package validation checks that the upload call performs,     but with no effects on the target participants: the DAR is not persisted or vetted.


Party Management Service
^^^^^^^^^^^^^^^^^^^^^^^^

.. _ledger_api.parties.allocate:


:ref:`ledger_api.parties.allocate (Testing) <ledger_api.parties.allocate>`
	* **Summary**: Allocate a new party
	* **Arguments**: 
		* ``party``: String
		* ``displayName``: String
		* ``annotations``: Map[String,String]
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.PartyDetails <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PartyDetails.html>`_
	* **Description**: Allocates a new party on the ledger.      party: a hint for generating the party identifier      displayName: a human-readable name of this party      annotations: key-value pairs associated with this party and stored locally on this Ledger API server      identityProviderId: identity provider id

.. _ledger_api.parties.help:


:ref:`ledger_api.parties.help <ledger_api.parties.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.parties.list:


:ref:`ledger_api.parties.list (Testing) <ledger_api.parties.list>`
	* **Summary**: List parties known by the Ledger API server
	* **Arguments**: 
		* ``identityProviderId``: String
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.PartyDetails] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PartyDetails.html>`_
	* **Description**: Lists parties known by the Ledger API server.      identityProviderId: identity provider id

.. _ledger_api.parties.update:


:ref:`ledger_api.parties.update <ledger_api.parties.update>`
	* **Summary**: Update participant-local party details
	* **Arguments**: 
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``modifier``: `com.digitalasset.canton.admin.api.client.data.PartyDetails => com.digitalasset.canton.admin.api.client.data.PartyDetails <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PartyDetails.html>`_
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.PartyDetails <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PartyDetails.html>`_
	* **Description**: Currently you can update only the annotations. You cannot update other user attributes.      party: party to be updated,      modifier: a function to modify the party details, e.g.: `partyDetails => { partyDetails.copy(annotations = partyDetails.annotations.updated("a", "b").removed("c")) }`      identityProviderId: identity provider id

.. _ledger_api.parties.update_idp:


:ref:`ledger_api.parties.update_idp (Testing) <ledger_api.parties.update_idp>`
	* **Summary**: Update party's identity provider id
	* **Arguments**: 
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``sourceIdentityProviderId``: String
		* ``targetIdentityProviderId``: String
	* **Description**: Updates party's identity provider id.      party: party to be updated      sourceIdentityProviderId: source identity provider id      targetIdentityProviderId: target identity provider id      


Ledger Configuration Service
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. _ledger_api.configuration.help:


:ref:`ledger_api.configuration.help <ledger_api.configuration.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.configuration.list:


:ref:`ledger_api.configuration.list (Testing) <ledger_api.configuration.list>`
	* **Summary**: Obtain the ledger configuration
	* **Arguments**: 
		* ``expectedConfigs``: Int
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* Seq[com.daml.ledger.api.v1.ledger_configuration_service.LedgerConfiguration]
	* **Description**: Returns the current ledger configuration and subsequent updates until      the expected number of configs was retrieved or the timeout is over.


Ledger Api User Management Service
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. _ledger_api.users.create:


:ref:`ledger_api.users.create (Testing) <ledger_api.users.create>`
	* **Summary**: Create a user with the given id
	* **Arguments**: 
		* ``id``: String
		* ``actAs``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``primaryParty``: `Option[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``readAs``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``participantAdmin``: Boolean
		* ``isActive``: Boolean
		* ``annotations``: Map[String,String]
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.User <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/User.html>`_
	* **Description**: Users are used to dynamically managing the rights given to Daml applications. They allow us to link a stable local identifier (of an application) with a set of parties.      id: the id used to identify the given user      actAs: the set of parties this user is allowed to act as      primaryParty: the optional party that should be linked to this user by default      readAs: the set of parties this user is allowed to read as      participantAdmin: flag (default false) indicating if the user is allowed to use the admin commands of the Ledger Api      isActive: flag (default true) indicating if the user is active      annotations: the set of key-value pairs linked to this user      identityProviderId: identity provider id      

.. _ledger_api.users.delete:


:ref:`ledger_api.users.delete (Testing) <ledger_api.users.delete>`
	* **Summary**: Delete a user
	* **Arguments**: 
		* ``id``: String
		* ``identityProviderId``: String
	* **Description**: Delete a user by id.     id: user id     identityProviderId: identity provider id

.. _ledger_api.users.get:


:ref:`ledger_api.users.get (Testing) <ledger_api.users.get>`
	* **Summary**: Get the user data of the user with the given id
	* **Arguments**: 
		* ``id``: String
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.User <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/User.html>`_
	* **Description**: Fetch the data associated with the given user id failing if there is no such user. You will get the user's primary party, active status and annotations. If you need the user rights, use rights.list instead.      id: user id      identityProviderId: identity provider id

.. _ledger_api.users.help:


:ref:`ledger_api.users.help <ledger_api.users.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.users.list:


:ref:`ledger_api.users.list (Testing) <ledger_api.users.list>`
	* **Summary**: List users
	* **Arguments**: 
		* ``filterUser``: String
		* ``pageToken``: String
		* ``pageSize``: Int
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.UsersPage <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/UsersPage.html>`_
	* **Description**: List users of this participant node      filterUser: filter results using the given filter string      pageToken: used for pagination (the result contains a page token if there are further pages)      pageSize: default page size before the filter is applied      identityProviderId: identity provider id

.. _ledger_api.users.update:


:ref:`ledger_api.users.update (Testing) <ledger_api.users.update>`
	* **Summary**: Update a user
	* **Arguments**: 
		* ``id``: String
		* ``modifier``: `com.digitalasset.canton.admin.api.client.data.User => com.digitalasset.canton.admin.api.client.data.User <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/User.html>`_
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.User <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/User.html>`_
	* **Description**: Currently you can update the annotations, active status and primary party. You cannot update other user attributes.      id: id of the user to be updated      modifier: a function for modifying the user; e.g: `user => { user.copy(isActive = false, primaryParty = None, annotations = user.annotations.updated("a", "b").removed("c")) }`      identityProviderId: identity provider id      

.. _ledger_api.users.update_idp:


:ref:`ledger_api.users.update_idp (Testing) <ledger_api.users.update_idp>`
	* **Summary**: Update user's identity provider id
	* **Arguments**: 
		* ``id``: String
		* ``sourceIdentityProviderId``: String
		* ``targetIdentityProviderId``: String
	* **Description**: Updates user's identity provider id.      id: the id used to identify the given user      sourceIdentityProviderId: source identity provider id      targetIdentityProviderId: target identity provider id      


.. _ledger_api.users.rights.grant:


:ref:`ledger_api.users.rights.grant (Testing) <ledger_api.users.rights.grant>`
	* **Summary**: Grant new rights to a user
	* **Arguments**: 
		* ``id``: String
		* ``actAs``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``readAs``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``participantAdmin``: Boolean
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.UserRights <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/UserRights.html>`_
	* **Description**: Users are used to dynamically managing the rights given to Daml applications. This function is used to grant new rights to an existing user.      id: the id used to identify the given user      actAs: the set of parties this user is allowed to act as      readAs: the set of parties this user is allowed to read as      participantAdmin: flag (default false) indicating if the user is allowed to use the admin commands of the Ledger Api      identityProviderId: identity provider id      

.. _ledger_api.users.rights.help:


:ref:`ledger_api.users.rights.help <ledger_api.users.rights.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _ledger_api.users.rights.list:


:ref:`ledger_api.users.rights.list (Testing) <ledger_api.users.rights.list>`
	* **Summary**: List rights of a user
	* **Arguments**: 
		* ``id``: String
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.UserRights <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/UserRights.html>`_
	* **Description**: Lists the rights of a user, or the rights of the current user.       id: user id       identityProviderId: identity provider id

.. _ledger_api.users.rights.revoke:


:ref:`ledger_api.users.rights.revoke (Testing) <ledger_api.users.rights.revoke>`
	* **Summary**: Revoke user rights
	* **Arguments**: 
		* ``id``: String
		* ``actAs``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``readAs``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``participantAdmin``: Boolean
		* ``identityProviderId``: String
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.UserRights <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/UserRights.html>`_
	* **Description**: Use to revoke specific rights from a user.      id: the id used to identify the given user      actAs: the set of parties this user should not be allowed to act as      readAs: the set of parties this user should not be allowed to read as      participantAdmin: if set to true, the participant admin rights will be removed      identityProviderId: identity provider id      


Ledger Api Metering Service
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. _ledger_api.metering.get_report:


:ref:`ledger_api.metering.get_report (Testing) <ledger_api.metering.get_report>`
	* **Summary**: Get the ledger metering report
	* **Arguments**: 
		* ``from``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``to``: `Option[com.digitalasset.canton.data.CantonTimestamp] <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``applicationId``: Option[String]
	* **Return type**: 
		* String
	* **Description**: Returns the current ledger metering report      from: required from timestamp (inclusive)      to: optional to timestamp      application_id: optional application id to which we want to restrict the report      

.. _ledger_api.metering.help:


:ref:`ledger_api.metering.help <ledger_api.metering.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


Composability
~~~~~~~~~~~~~

.. _transfer.execute:


:ref:`transfer.execute (Preview) <transfer.execute>`
	* **Summary**: Transfer the contract from the origin domain to the target domain
	* **Arguments**: 
		* ``submittingParty``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``contractId``: `com.digitalasset.canton.protocol.LfContractId <../../canton/scaladoc/com/digitalasset/canton/protocol/index.html>`_
		* ``sourceDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``targetDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Description**: Macro that first calls transfer_out and then transfer_in. No error handling is done.

.. _transfer.help:


:ref:`transfer.help <transfer.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _transfer.in:


:ref:`transfer.in (Preview) <transfer.in>`
	* **Summary**: Transfer-in a contract in transit to the target domain
	* **Arguments**: 
		* ``submittingParty``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``transferId``: `com.digitalasset.canton.protocol.TransferId <../../canton/scaladoc/com/digitalasset/canton/protocol/TransferId.html>`_
		* ``targetDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``applicationId``: com.digitalasset.canton.LedgerApplicationId
		* ``submissionId``: String
		* ``workflowId``: String
		* ``commandId``: String
	* **Description**: Manually transfers a contract in transit into the target domain.    The command returns when the transfer-in has completed successfully.    If the transferExclusivityTimeout in the target domain's parameters is set to a positive value,    all participants of all stakeholders connected to both origin and target domain will attempt to transfer-in    the contract automatically after the exclusivity timeout has elapsed.    An application-id can be specified to uniquely identifies the application that have issued the transfer,    otherwise the default value will be used. An optional submission id can be set by the committer to the value    of their choice that allows an application to correlate completions to its submissions.

.. _transfer.lookup_contract_domain:


:ref:`transfer.lookup_contract_domain (Preview) <transfer.lookup_contract_domain>`
	* **Summary**: Lookup the active domain for the provided contracts
	* **Arguments**: 
		* ``contractIds``: `com.digitalasset.canton.protocol.LfContractId* <../../canton/scaladoc/com/digitalasset/canton/protocol/index.html>`_
	* **Return type**: 
		* Map[com.digitalasset.canton.protocol.LfContractId,String]

.. _transfer.out:


:ref:`transfer.out (Preview) <transfer.out>`
	* **Summary**: Transfer-out a contract from the source domain with destination target domain
	* **Arguments**: 
		* ``submittingParty``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``contractId``: `com.digitalasset.canton.protocol.LfContractId <../../canton/scaladoc/com/digitalasset/canton/protocol/index.html>`_
		* ``sourceDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``targetDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``applicationId``: com.digitalasset.canton.LedgerApplicationId
		* ``submissionId``: String
		* ``workflowId``: String
		* ``commandId``: String
	* **Return type**: 
		* `com.digitalasset.canton.protocol.TransferId <../../canton/scaladoc/com/digitalasset/canton/protocol/TransferId.html>`_
	* **Description**: Transfers the given contract out of the source domain with destination target domain.    The command returns the ID of the transfer when the transfer-out has completed successfully.    The contract is in transit until the transfer-in has completed on the target domain.    The submitting party must be a stakeholder of the contract and the participant must have submission rights    for the submitting party on the source domain. It must also be connected to the target domain.    An application-id can be specified to uniquely identify the application that have issued the transfer,    otherwise the default value will be used. An optional submission id can be set by the committer to the value    of their choice that allows an application to correlate completions to its submissions.

.. _transfer.search:


:ref:`transfer.search (Preview) <transfer.search>`
	* **Summary**: Search the currently in-flight transfers
	* **Arguments**: 
		* ``targetDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``filterSourceDomain``: `Option[com.digitalasset.canton.DomainAlias] <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``filterTimestamp``: Option[java.time.Instant]
		* ``filterSubmittingParty``: `Option[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.participant.admin.grpc.TransferSearchResult] <../../canton/scaladoc/com/digitalasset/canton/participant/admin/grpc/TransferSearchResult.html>`_
	* **Description**: Returns all in-flight transfers with the given target domain that match the filters, but no more than the limit specifies.


.. _ledger-pruning-commands:

Ledger Pruning
~~~~~~~~~~~~~~

.. _pruning.clear_schedule:


:ref:`pruning.clear_schedule <pruning.clear_schedule>`
	* **Summary**: Deactivate automatic pruning.

.. _pruning.find_safe_offset:


:ref:`pruning.find_safe_offset (Preview) <pruning.find_safe_offset>`
	* **Summary**: Return the highest participant ledger offset whose record time is before or at the given one (if any) at which pruning is safely possible
	* **Arguments**: 
		* ``beforeOrAt``: java.time.Instant
	* **Return type**: 
		* Option[com.daml.ledger.api.v1.ledger_offset.LedgerOffset]

.. _pruning.get_offset_by_time:


:ref:`pruning.get_offset_by_time <pruning.get_offset_by_time>`
	* **Summary**: Identify the participant ledger offset to prune up to based on the specified timestamp.
	* **Arguments**: 
		* ``upToInclusive``: java.time.Instant
	* **Return type**: 
		* Option[com.daml.ledger.api.v1.ledger_offset.LedgerOffset]
	* **Description**: Return the largest participant ledger offset that has been processed before or at the specified timestamp. The time is measured on the participant's local clock at some point while the participant has processed the the event. Returns ``None`` if no such offset exists.   

.. _pruning.get_participant_schedule:


:ref:`pruning.get_participant_schedule <pruning.get_participant_schedule>`
	* **Summary**: Inspect the automatic, participant-specific pruning schedule.
	* **Return type**: 
		* `Option[com.digitalasset.canton.admin.api.client.data.ParticipantPruningSchedule] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ParticipantPruningSchedule.html>`_
	* **Description**: The schedule consists of a "cron" expression and "max_duration" and "retention" durations as described in the ``get_schedule`` command description. Additionally "prune_internally" indicates if the schedule mandates pruning of internal state.  

.. _pruning.get_schedule:


:ref:`pruning.get_schedule <pruning.get_schedule>`
	* **Summary**: Inspect the automatic pruning schedule.
	* **Return type**: 
		* `Option[com.digitalasset.canton.admin.api.client.data.PruningSchedule] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PruningSchedule.html>`_
	* **Description**: The schedule consists of a "cron" expression and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period. Returns `None` if no schedule has been configured via `set_schedule` or if `clear_schedule` has been invoked.   

.. _pruning.help:


:ref:`pruning.help <pruning.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _pruning.locate_offset:


:ref:`pruning.locate_offset (Preview) <pruning.locate_offset>`
	* **Summary**: Identify the participant ledger offset to prune up to.
	* **Arguments**: 
		* ``n``: Long
	* **Return type**: 
		* com.daml.ledger.api.v1.ledger_offset.LedgerOffset
	* **Description**: Return the participant ledger offset that corresponds to pruning "n" number of transactions from the beginning of the ledger. Errors if the ledger holds less than "n" transactions. Specifying "n" of 1 returns the offset of the first transaction (if the ledger is non-empty).   

.. _pruning.prune:


:ref:`pruning.prune <pruning.prune>`
	* **Summary**: Prune the ledger up to the specified offset inclusively.
	* **Arguments**: 
		* ``pruneUpTo``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
	* **Description**: Prunes the participant ledger up to the specified offset inclusively returning ``Unit`` if the ledger has been successfully pruned. Note that upon successful pruning, subsequent attempts to read transactions via ``ledger_api.transactions.flat`` or ``ledger_api.transactions.trees`` or command completions via ``ledger_api.completions.list`` by specifying a begin offset lower than the returned pruning offset will result in a ``NOT_FOUND`` error. In the Enterprise Edition, ``prune`` performs a "full prune" freeing up significantly more space and also performs additional safety checks returning a ``NOT_FOUND`` error if ``pruneUpTo`` is higher than the offset returned by ``find_safe_offset`` on any domain with events preceding the pruning offset.

.. _pruning.prune_internally:


:ref:`pruning.prune_internally (Preview) <pruning.prune_internally>`
	* **Summary**: Prune only internal ledger state up to the specified offset inclusively.
	* **Arguments**: 
		* ``pruneUpTo``: com.daml.ledger.api.v1.ledger_offset.LedgerOffset
	* **Description**: Special-purpose variant of the ``prune`` command only available in the Enterprise Edition that prunes only partial, internal participant ledger state freeing up space not needed for serving ``ledger_api.transactions`` and ``ledger_api.completions`` requests. In conjunction with ``prune``, ``prune_internally`` enables pruning internal ledger state more aggressively than externally observable data via the ledger api. In most use cases ``prune`` should be used instead. Unlike ``prune``, ``prune_internally`` has no visible effect on the Ledger API. The command returns ``Unit`` if the ledger has been successfully pruned or an error if the timestamp performs additional safety checks returning a ``NOT_FOUND`` error if ``pruneUpTo`` is higher than the offset returned by ``find_safe_offset`` on any domain with events preceding the pruning offset.

.. _pruning.set_cron:


:ref:`pruning.set_cron <pruning.set_cron>`
	* **Summary**: Modify the cron used by automatic pruning.
	* **Arguments**: 
		* ``cron``: String
	* **Description**: The schedule is specified in cron format and refers to pruning start times in the GMT time zone. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _pruning.set_max_duration:


:ref:`pruning.set_max_duration <pruning.set_max_duration>`
	* **Summary**: Modify the maximum duration used by automatic pruning.
	* **Arguments**: 
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `maxDuration` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _pruning.set_participant_schedule:


:ref:`pruning.set_participant_schedule <pruning.set_participant_schedule>`
	* **Summary**: Activate automatic pruning according to the specified schedule with participant-specific options.
	* **Arguments**: 
		* ``cron``: String
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
		* ``pruneInternallyOnly``: Boolean
	* **Description**: Refer to the ``set_schedule`` description for information about the "cron", "max_duration", and "retention" parameters. Setting the "prune_internally_only" flag causes pruning to only remove internal state as described in more detail in the ``prune_internally`` command description.  

.. _pruning.set_retention:


:ref:`pruning.set_retention <pruning.set_retention>`
	* **Summary**: Update the pruning retention used by automatic pruning.
	* **Arguments**: 
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `retention` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this update, pruning is actively running, a best effort is made to pause pruning and restart with the newly specified retention. This allows for the case that the new retention mandates retaining more data than previously.   

.. _pruning.set_schedule:


:ref:`pruning.set_schedule <pruning.set_schedule>`
	* **Summary**: Activate automatic pruning according to the specified schedule.
	* **Arguments**: 
		* ``cron``: String
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The schedule is specified in cron format and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period.   


Bilateral Commitments
~~~~~~~~~~~~~~~~~~~~~

.. _commitments.computed:


:ref:`commitments.computed <commitments.computed>`
	* **Summary**: Lookup ACS commitments locally computed as part of the reconciliation protocol
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``start``: java.time.Instant
		* ``end``: java.time.Instant
		* ``counterParticipant``: `Option[com.digitalasset.canton.topology.ParticipantId] <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
	* **Return type**: 
		* Iterable[(com.digitalasset.canton.protocol.messages.CommitmentPeriod, com.digitalasset.canton.topology.ParticipantId, com.digitalasset.canton.protocol.messages.AcsCommitment.CommitmentType)]

.. _commitments.help:


:ref:`commitments.help <commitments.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _commitments.received:


:ref:`commitments.received <commitments.received>`
	* **Summary**: Lookup ACS commitments received from other participants as part of the reconciliation protocol
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``start``: java.time.Instant
		* ``end``: java.time.Instant
		* ``counterParticipant``: `Option[com.digitalasset.canton.topology.ParticipantId] <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
	* **Return type**: 
		* Iterable[com.digitalasset.canton.protocol.messages.SignedProtocolMessage[com.digitalasset.canton.protocol.messages.AcsCommitment]]
	* **Description**: The arguments are:    - domain: the alias of the domain    - start: lowest time exclusive    - end: highest time inclusive    - counterParticipant: optionally filter by counter participant    


.. _participant-repair:

Participant Repair
~~~~~~~~~~~~~~~~~~

.. _repair.add:


:ref:`repair.add <repair.add>`
	* **Summary**: Add specified contracts to specific domain on local participant.
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``contractsToAdd``: Seq[com.digitalasset.canton.protocol.SerializableContractWithWitnesses]
		* ``ignoreAlreadyAdded``: Boolean
		* ``ignoreStakeholderCheck``: Boolean
	* **Description**: This is a last resort command to recover from data corruption, e.g. in scenarios in which participant contracts have somehow gotten out of sync and need to be manually created. The participant needs to be disconnected from the specified "domain" at the time of the call, and as of now the domain cannot have had any inflight requests. For each "contractsToAdd", specify "witnesses", local parties, in case no local party is a stakeholder. The "ignoreAlreadyAdded" flag makes it possible to invoke the command multiple times with the same parameters in case an earlier command invocation has failed. As repair commands are powerful tools to recover from unforeseen data corruption, but dangerous under normal operation, use of this command requires (temporarily) enabling the "features.enable-repair-commands" configuration. In addition repair commands can run for an unbounded time depending on the number of contracts passed in. Be sure to not connect the participant to the domain until the call returns.     The arguments are:     - domain: the alias of the domain to which to add the contract     - contractsToAdd: list of contracts to add with witness information     - ignoreAlreadyAdded: (default true) if set to true, it will ignore contracts that already exist on the target domain.     - ignoreStakeholderCheck: (default false) if set to true, add will work for contracts that don't have a local party (useful for party migration).     

.. _repair.add_1:


:ref:`repair.add <repair.add_1>`
	* **Summary**: Add specified contracts to specific domain on local participant.
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
		* ``contractsToAdd``: Seq[com.digitalasset.canton.protocol.SerializableContractWithWitnesses]
		* ``onboardedParties``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
	* **Description**: This is a last resort command to recover from data corruption, e.g. in scenarios in which participant contracts have somehow gotten out of sync and need to be manually created. The participant needs to be disconnected from the specified "domain" at the time of the call, and as of now the domain cannot have had any inflight requests. The effects of the command will take affect upon reconnecting to the sync domain. As repair commands are powerful tools to recover from unforeseen data corruption, but dangerous under normal operation, use of this command requires (temporarily) enabling the "features.enable-repair-commands" configuration. In addition repair commands can run for an unbounded time depending on the number of contracts passed in. Be sure to not connect the participant to the domain until the call returns.     The arguments are:     - domainId: the id of the domain to which to add the contract     - protocolVersion: to protocol version used by the domain     - contractsToAdd: list of contracts to add with witness information     

.. _repair.change_domain:


:ref:`repair.change_domain <repair.change_domain>`
	* **Summary**: Move contracts with specified Contract IDs from one domain to another.
	* **Arguments**: 
		* ``contractIds``: `Seq[com.digitalasset.canton.protocol.LfContractId] <../../canton/scaladoc/com/digitalasset/canton/protocol/index.html>`_
		* ``sourceDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``targetDomain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``skipInactive``: Boolean
		* ``batchSize``: Int
	* **Description**: This is a last resort command to recover from data corruption in scenarios in which a domain is irreparably broken and formerly connected participants need to move contracts to another, healthy domain. The participant needs to be disconnected from both the "sourceDomain" and the "targetDomain". Also as of now the target domain cannot have had any inflight requests. Contracts already present in the target domain will be skipped, and this makes it possible to invoke this command in an "idempotent" fashion in case an earlier attempt had resulted in an error. The "skipInactive" flag makes it possible to only move active contracts in the "sourceDomain". As repair commands are powerful tools to recover from unforeseen data corruption, but dangerous under normal operation, use of this command requires (temporarily) enabling the "features.enable-repair-commands" configuration. In addition repair commands can run for an unbounded time depending on the number of contract ids passed in. Be sure to not connect the participant to either domain until the call returns.     Arguments:     - contractIds - set of contract ids that should be moved to the new domain     - sourceDomain - alias of the source domain     - targetDomain - alias of the target domain     - skipInactive - (default true) whether to skip inactive contracts mentioned in the contractIds list     - batchSize - (default 100) how many contracts to write at once to the database

.. _repair.download:


:ref:`repair.download <repair.download>`
	* **Summary**: Download all contracts for the given set of parties to a file.
	* **Arguments**: 
		* ``parties``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``partiesOffboarding``: Boolean
		* ``outputFile``: String
		* ``filterDomainId``: String
		* ``timestamp``: Option[java.time.Instant]
		* ``protocolVersion``: `Option[com.digitalasset.canton.version.ProtocolVersion] <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
		* ``chunkSize``: `Option[com.digitalasset.canton.config.RequireTypes.PositiveInt] <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
		* ``contractDomainRenames``: Map[com.digitalasset.canton.topology.DomainId,com.digitalasset.canton.topology.DomainId]
	* **Description**: This command can be used to download the current active contract set of a given set of parties to a text file. This is mainly interesting for recovery and operational purposes. The file will contain base64 encoded strings, one line per contract. The lines are written sorted according to their domain and contract id. This allows to compare the contracts stored by two participants using standard file comparison tools. The domain-id is printed with the prefix domain-id before the block of contracts starts. This command may take a long time to complete and may require significant resources. It will first load the contract ids of the active contract set into memory and then subsequently load the contracts in batches and inspect their stakeholders. As this operation needs to traverse the entire datastore, it might take a long time to complete. The command will return a map of domainId -> number of active contracts stored     The arguments are:     - parties: identifying contracts having at least one stakeholder from the given set     - partiesOffboarding: true if the parties will be offboarded (party migration)     - outputFile: the output file name where to store the data. Use .gz as a suffix to get a compressed file (recommended)     - filterDomainId: restrict the export to a given domain     - timestamp: optionally a timestamp for which we should take the state (useful to reconcile states of a domain)     - protocolVersion: optional the protocol version to use for the serialization. Defaults to the one of the domains.     - chunkSize: size of the byte chunks to stream back: default 1024 * 1024 * 2 = (2MB)     - contractDomainRenames: As part of the export, allow to rename the associated domain id of contracts from one domain to another based on the mapping.     

.. _repair.export_acs:


:ref:`repair.export_acs <repair.export_acs>`
	* **Summary**: Export active contracts for the given set of parties to a file.
	* **Arguments**: 
		* ``parties``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``partiesOffboarding``: Boolean
		* ``outputFile``: String
		* ``filterDomainId``: `Option[com.digitalasset.canton.topology.DomainId] <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``timestamp``: Option[java.time.Instant]
		* ``contractDomainRenames``: Map[com.digitalasset.canton.topology.DomainId,(com.digitalasset.canton.topology.DomainId, com.digitalasset.canton.version.ProtocolVersion)]
	* **Description**: This command exports the current Active Contract Set (ACS) of a given set of parties to ACS snapshot file. Afterwards, the 'import_acs' command allows importing it into a participant's ACS again. Such ACS export (and import) is interesting for recovery and operational purposes only. Note that the 'export_acs' command execution may take a long time to complete and may require significant resources. The arguments are: - parties: identifying contracts having at least one stakeholder from the given set - partiesOffboarding: true if the parties will be offboarded (party migration) - outputFile: the output file name where to store the data. Use .gz as a suffix to get a compressed file (recommended) - filterDomainId: restrict the export to a given domain - timestamp: optionally a timestamp for which we should take the state (useful to reconcile states of a domain) - contractDomainRenames: As part of the export, allow to rename the associated domain id of contracts from one domain to another based on the mapping.     

.. _repair.help:


:ref:`repair.help <repair.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _repair.ignore_events:


:ref:`repair.ignore_events <repair.ignore_events>`
	* **Summary**: Mark sequenced events as ignored.
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``fromInclusive``: `com.digitalasset.canton.SequencerCounter <../../canton/scaladoc/com/digitalasset/canton/index.html>`_
		* ``toInclusive``: `com.digitalasset.canton.SequencerCounter <../../canton/scaladoc/com/digitalasset/canton/index.html>`_
		* ``force``: Boolean
	* **Description**: This is the last resort to ignore events that the participant is unable to process. Ignoring events may lead to subsequent failures, e.g., if the event creating a contract is ignored and that contract is subsequently used. It may also lead to ledger forks if other participants still process the ignored events. It is possible to mark events as ignored that the participant has not yet received. The command will fail, if marking events between `fromInclusive` and `toInclusive` as ignored would result in a gap in sequencer counters, namely if `from <= to` and `from` is greater than `maxSequencerCounter + 1`, where `maxSequencerCounter` is the greatest sequencer counter of a sequenced event stored by the underlying participant. The command will also fail, if `force == false` and `from` is smaller than the sequencer counter of the last event that has been marked as clean. (Ignoring such events would normally have no effect, as they have already been processed.)

.. _repair.import_acs:


:ref:`repair.import_acs <repair.import_acs>`
	* **Summary**: Import active contracts from an Active Contract Set (ACS) snapshot file.
	* **Arguments**: 
		* ``inputFile``: String
		* ``onboardedParties``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``workflowIdPrefix``: String
	* **Description**: This command imports contracts from an ACS snapshot file into the participant's ACS. The given ACS snapshot file needs to be the resulting file from a previous 'export_acs' command invocation. Arguments are:  - inputFile: the path to the file containing the ACS export  - onboardedParties: the list of new parties whose contracts are imported     

.. _repair.migrate_domain:


:ref:`repair.migrate_domain <repair.migrate_domain>`
	* **Summary**: Migrate contracts from one domain to another one.
	* **Arguments**: 
		* ``source``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``target``: `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_
		* ``force``: Boolean
	* **Description**: Migrates all contracts associated with a domain to a new domain. This method will register the new domain, connect to it and then re-associate all contracts from the source domain to the target domain. Please note that this migration needs to be done by all participants at the same time. The target domain should only be used once all participants have finished their migration. WARNING: The migration does not start in case of in-flight transactions on the source domain. Forcing the migration may lead to a ledger fork! Instead of forcing the migration, ensure the source domain has no in-flight transactions by reconnecting all participants to the source domain, halting activity on these participants and waiting for the in-flight transactions to complete or time out. Forcing a migration is intended for disaster recovery when a source domain cannot be recovered anymore. The arguments are: source: the domain alias of the source domain target: the configuration for the target domain force: if true, migration is forced ignoring in-flight transactions. Defaults to false.     

.. _repair.purge:


:ref:`repair.purge <repair.purge>`
	* **Summary**: Purge contracts with specified Contract IDs from local participant.
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``contractIds``: `Seq[com.digitalasset.canton.protocol.LfContractId] <../../canton/scaladoc/com/digitalasset/canton/protocol/index.html>`_
		* ``offboardedParties``: `Set[com.digitalasset.canton.topology.PartyId] <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``ignoreAlreadyPurged``: Boolean
	* **Description**: This is a last resort command to recover from data corruption, e.g. in scenarios in which participant contracts have somehow gotten out of sync and need to be manually purged, or in situations in which stakeholders are no longer available to agree to their archival. The participant needs to be disconnected from the domain on which the contracts with "contractIds" reside at the time of the call, and as of now the domain cannot have had any inflight requests. The effects of the command will take affect upon reconnecting to the sync domain. The "ignoreAlreadyPurged" flag makes it possible to invoke the command multiple times with the same parameters in case an earlier command invocation has failed. As repair commands are powerful tools to recover from unforeseen data corruption, but dangerous under normal operation, use of this command requires (temporarily) enabling the "features.enable-repair-commands" configuration. In addition repair commands can run for an unbounded time depending on the number of contract ids passed in. Be sure to not connect the participant to the domain until the call returns. Arguments are:  - inputFile: the path to the file containing the ACS export  - offboardedParties: the list of parties that will be offboarded after the purge.

.. _repair.purge_deactivated_domain:


:ref:`repair.purge_deactivated_domain <repair.purge_deactivated_domain>`
	* **Summary**: Purge select data of a deactivated domain.
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
	* **Description**: This command deletes selected domain data and helps to ensure that stale data in the specified, deactivated domain is not acted upon anymore. The specified domain needs to be in the `Inactive` status for purging to occur. Purging a deactivated domain is typically performed automatically as part of a hard domain migration via ``repair.migrate_domain``.

.. _repair.unignore_events:


:ref:`repair.unignore_events <repair.unignore_events>`
	* **Summary**: Remove the ignored status from sequenced events.
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``fromInclusive``: `com.digitalasset.canton.SequencerCounter <../../canton/scaladoc/com/digitalasset/canton/index.html>`_
		* ``toInclusive``: `com.digitalasset.canton.SequencerCounter <../../canton/scaladoc/com/digitalasset/canton/index.html>`_
		* ``force``: Boolean
	* **Description**: This command has no effect on ordinary (i.e., not ignored) events and on events that do not exist. The command will fail, if marking events between `fromInclusive` and `toInclusive` as unignored would result in a gap in sequencer counters, namely if there is one empty ignored event with sequencer counter between `from` and `to` and another empty ignored event with sequencer counter greater than `to`. An empty ignored event is an event that has been marked as ignored and not yet received by the participant. The command will also fail, if `force == false` and `from` is smaller than the sequencer counter of the last event that has been marked as clean. (Unignoring such events would normally have no effect, as they have already been processed.)

.. _repair.upload:


:ref:`repair.upload <repair.upload>`
	* **Summary**: Import ACS snapshot
	* **Arguments**: 
		* ``inputFile``: String
	* **Description**: Uploads a binary into the participant's ACS


Resource Management
~~~~~~~~~~~~~~~~~~~

.. _resources.help:


:ref:`resources.help <resources.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _resources.resource_limits:


:ref:`resources.resource_limits <resources.resource_limits>`
	* **Summary**: Get the resource limits of the participant.
	* **Return type**: 
		* `com.digitalasset.canton.participant.admin.ResourceLimits <../../canton/scaladoc/com/digitalasset/canton/participant/admin/ResourceLimits.html>`_

.. _resources.set_resource_limits:


:ref:`resources.set_resource_limits <resources.set_resource_limits>`
	* **Summary**: Set resource limits for the participant.
	* **Arguments**: 
		* ``limits``: `com.digitalasset.canton.participant.admin.ResourceLimits <../../canton/scaladoc/com/digitalasset/canton/participant/admin/ResourceLimits.html>`_
	* **Description**: While a resource limit is attained or exceeded, the participant will reject any additional submission with GRPC status ABORTED. Most importantly, a submission will be rejected **before** it consumes a significant amount of resources. There are three kinds of limits: `maxDirtyRequests`, `maxRate` and `maxBurstFactor`. The number of dirty requests of a participant P covers (1) requests initiated by P as well as (2) requests initiated by participants other than P that need to be validated by P. Compared to the maximum rate, the maximum number of dirty requests reflects the load on the participant more accurately. However, the maximum number of dirty requests alone does not protect the system from "bursts": If an application submits a huge number of commands at once, the maximum number of dirty requests will likely be exceeded, as the system is registering dirty requests only during validation and not already during submission. The maximum rate is a hard limit on the rate of commands submitted to this participant through the ledger API. As the rate of commands is checked and updated immediately after receiving a new command submission, an application cannot exceed the maximum rate. The `maxBurstFactor` parameter (positive, default 0.5) allows to configure how permissive the rate limitation should be with respect to bursts. The rate limiting will be enforced strictly after having observed `max_burst` * `max_rate` commands. For the sake of illustration, let's assume the configured rate limit is ``100 commands/s`` with a burst ratio of 0.5. If an application submits 100 commands within a single second, waiting exactly 10 milliseconds between consecutive commands, then the participant will accept all commands. With a `maxBurstFactor` of 0.5, the participant will accept the first 50 commands and reject the remaining 50. If the application then waits another 500 ms, it may submit another burst of 50 commands. If it waits 250 ms, it may submit only a burst of 25 commands. Resource limits can only be changed, if the server runs Canton enterprise. In the community edition, the server uses fixed limits that cannot be changed.


Replication
~~~~~~~~~~~

.. _replication.help:


:ref:`replication.help <replication.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _replication.set_passive:


:ref:`replication.set_passive <replication.set_passive>`
	* **Summary**: Set the participant replica to passive
	* **Return type**: 
		* Boolean
	* **Description**: Trigger a graceful fail-over from this active replica to another passive replica. Returns true if another replica became active.


.. _participants-references:

Multiple Participants
---------------------

This section lists the commands available for a sequence of participants. They can be used on the
participant references ``participants.all``, ``.local`` or ``.remote`` as:

.. code-block:: scala

    participants.all.dars.upload("my.dar")

.. _dars.help_1:


:ref:`dars.help <dars.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _dars.upload_1:


:ref:`dars.upload <dars.upload_1>`
	* **Summary**: Upload DARs to participants
	* **Arguments**: 
		* ``darPath``: String
		* ``vetAllPackages``: Boolean
		* ``synchronizeVetting``: Boolean
	* **Return type**: 
		* Map[com.digitalasset.canton.console.ParticipantReference,String]
	* **Description**: If vetAllPackages is true, the participants will vet the package on all domains they are registered.     If synchronizeVetting is true, the command will block until the package vetting transaction has been registered with all connected domains.

.. _dars.validate_1:


:ref:`dars.validate <dars.validate_1>`
	* **Summary**: Validate DARs against the current participants' state
	* **Arguments**: 
		* ``darPath``: String
	* **Return type**: 
		* Map[com.digitalasset.canton.console.ParticipantReference,String]
	* **Description**: Performs the same DAR and Daml package validation checks that the upload call performs,     but with no effects on the target participants: the DAR is not persisted or vetted.


.. _domains.connect_local_1:


:ref:`domains.connect_local <domains.connect_local_1>`
	* **Summary**: Register and potentially connect to new local domain
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.console.InstanceReferenceWithSequencerConnection <../../canton/scaladoc/com/digitalasset/canton/console/InstanceReferenceWithSequencerConnection.html>`_
		* ``manualConnect``: Boolean
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**:      The arguments are:      domain - A local domain or sequencer reference      manualConnect - Whether this connection should be handled manually and also excluded from automatic re-connect.      synchronize - A timeout duration indicating how long to wait for all topology changes to have been effected on all local nodes.     

.. _domains.disconnect_1:


:ref:`domains.disconnect <domains.disconnect_1>`
	* **Summary**: Disconnect from domain
	* **Arguments**: 
		* ``alias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_

.. _domains.disconnect_all_1:


:ref:`domains.disconnect_all <domains.disconnect_all_1>`
	* **Summary**: Disconnect from all connected domains

.. _domains.disconnect_local_1:


:ref:`domains.disconnect_local <domains.disconnect_local_1>`
	* **Summary**: Disconnect from a local domain
	* **Arguments**: 
		* ``domain``: `com.digitalasset.canton.console.LocalDomainReference <../../canton/scaladoc/com/digitalasset/canton/console/LocalDomainReference.html>`_

.. _domains.help_1:


:ref:`domains.help <domains.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _domains.reconnect_1:


:ref:`domains.reconnect <domains.reconnect_1>`
	* **Summary**: Reconnect to domain
	* **Arguments**: 
		* ``alias``: `com.digitalasset.canton.DomainAlias <../../canton/scaladoc/com/digitalasset/canton/DomainAlias.html>`_
		* ``retry``: Boolean
	* **Description**: If retry is set to true (default), the command will return after the first attempt, but keep on trying in the background.

.. _domains.reconnect_all_1:


:ref:`domains.reconnect_all <domains.reconnect_all_1>`
	* **Summary**: Reconnect to all domains for which `manualStart` = false
	* **Arguments**: 
		* ``ignoreFailures``: Boolean
	* **Description**: If ignoreFailures is set to true (default), the reconnect all will succeed even if some domains are offline. The participants will continue attempting to establish a domain connection.

.. _domains.register_1:


:ref:`domains.register <domains.register_1>`
	* **Summary**: Register and potentially connect to domain
	* **Arguments**: 
		* ``config``: `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_


Domain Administration Commands
------------------------------

.. _clear_cache_1:


:ref:`clear_cache (Testing) <clear_cache_1>`
	* **Summary**: Clear locally cached variables
	* **Description**: Some commands cache values on the client side. Use this command to explicitly clear the caches of these values.

.. _config_1:


:ref:`config <config_1>`
	* **Summary**: Returns the domain configuration
	* **Return type**: 
		* LocalDomainReference.this.consoleEnvironment.environment.config.DomainConfigType

.. _defaultdomainconnection:


:ref:`defaultDomainConnection <defaultDomainConnection>`
	* **Summary**: Yields a domain connection config with default values except for the domain alias and the sequencer connection. May throw an exception if the domain alias or sequencer connection is misconfigured.
	* **Return type**: 
		* `com.digitalasset.canton.participant.domain.DomainConnectionConfig <../../canton/scaladoc/com/digitalasset/canton/participant/domain/DomainConnectionConfig.html>`_

.. _help_2:


:ref:`help <help_2>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _id_1:


:ref:`id <id_1>`
	* **Summary**: Yields the globally unique id of this domain. Throws an exception, if the id has not yet been allocated (e.g., the domain has not yet been started).
	* **Return type**: 
		* `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_

.. _is_initialized_1:


:ref:`is_initialized <is_initialized_1>`
	* **Summary**: Check if the local instance is running and is fully initialized
	* **Return type**: 
		* Boolean

.. _is_running_1:


:ref:`is_running <is_running_1>`
	* **Summary**: Check if the local instance is running
	* **Return type**: 
		* Boolean

.. _start_1:


:ref:`start <start_1>`
	* **Summary**: Start the instance

.. _stop_1:


:ref:`stop <stop_1>`
	* **Summary**: Stop the instance


Health
~~~~~~
.. _health.active_1:


:ref:`health.active <health.active_1>`
	* **Summary**: Check if the node is running and is the active instance (mediator, participant)
	* **Return type**: 
		* Boolean

.. _health.dump_2:


:ref:`health.dump <health.dump_2>`
	* **Summary**: Creates a zip file containing diagnostic information about the canton process running this node
	* **Arguments**: 
		* ``outputFile``: better.files.File
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``chunkSize``: Option[Int]
	* **Return type**: 
		* String

.. _health.help_2:


:ref:`health.help <health.help_2>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _health.initialized_1:


:ref:`health.initialized <health.initialized_1>`
	* **Summary**: Returns true if node has been initialized.
	* **Return type**: 
		* Boolean

.. _health.last_error_trace_1:


:ref:`health.last_error_trace <health.last_error_trace_1>`
	* **Summary**: Show all messages logged with the given traceId in a recent interval
	* **Arguments**: 
		* ``traceId``: String
	* **Return type**: 
		* Seq[String]
	* **Description**: Returns a list of buffered log messages associated to a given trace-id. Usually, the trace-id is taken from last_errors()

.. _health.last_errors_1:


:ref:`health.last_errors <health.last_errors_1>`
	* **Summary**: Show the last errors logged
	* **Return type**: 
		* Map[String,String]
	* **Description**: Returns a map with the trace-id as key and the most recent error messages as value. Requires that --log-last-errors is enabled (and not turned off).

.. _health.running_1:


:ref:`health.running <health.running_1>`
	* **Summary**: Check if the node is running
	* **Return type**: 
		* Boolean

.. _health.set_log_level_1:


:ref:`health.set_log_level <health.set_log_level_1>`
	* **Summary**: Change the log level of the process
	* **Arguments**: 
		* ``level``: ch.qos.logback.classic.Level
	* **Description**: If the default logback configuration is used, this will change the log level of the process.

.. _health.status_1:


:ref:`health.status <health.status_1>`
	* **Summary**: Get human (and machine) readable participant status information
	* **Return type**: 
		* com.digitalasset.canton.admin.api.client.data.NodeStatus[S]

.. _health.wait_for_identity_1:


:ref:`health.wait_for_identity <health.wait_for_identity_1>`
	* **Summary**: Wait for the node to have an identity
	* **Description**: This is specifically useful for the Domain Manager which needs its identity to be ready for bootstrapping, but for which we can't rely on wait_for_initialized() because it will be initialized only after being bootstrapped.

.. _health.wait_for_initialized_1:


:ref:`health.wait_for_initialized <health.wait_for_initialized_1>`
	* **Summary**: Wait for the node to be initialized

.. _health.wait_for_running_1:


:ref:`health.wait_for_running <health.wait_for_running_1>`
	* **Summary**: Wait for the node to be running


Database
~~~~~~~~

.. _db.help_1:


:ref:`db.help <db.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _db.migrate_1:


:ref:`db.migrate <db.migrate_1>`
	* **Summary**: Migrates the instance's database if using a database storage
	* **Description**: When instances reside on different nodes, their database migration can be run in parallel to save time. Please not that the migration commands must however must be run on each node individually, because remote migration through `participants.remote...` is not supported. 

.. _db.repair_migration_1:


:ref:`db.repair_migration <db.repair_migration_1>`
	* **Summary**: Only use when advised - repairs the database migration of the instance's database
	* **Arguments**: 
		* ``force``: Boolean
	* **Description**: In some rare cases, we change already applied database migration files in a new release and the repair command resets the checksums we use to ensure that in general already applied migration files have not been changed. You should only use `db.repair_migration` when advised and otherwise use it at your own risk - in the worst case running it may lead to data corruption when an incompatible database migration (one that should be rejected because the already applied database migration files have changed) is subsequently falsely applied. 


Participants
~~~~~~~~~~~~

.. _participants.active:


:ref:`participants.active <participants.active>`
	* **Summary**: Test whether a participant is permissioned on this domain
	* **Arguments**: 
		* ``participantId``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
	* **Return type**: 
		* Boolean

.. _participants.help:


:ref:`participants.help <participants.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _participants.list:


:ref:`participants.list <participants.list>`
	* **Summary**: List participant states
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListParticipantDomainStateResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListParticipantDomainStateResult.html>`_
	* **Description**: This command will list the currently valid state as stored in the authorized store. For a deep inspection of the identity management history, use the `topology.participant_domain_states.list` command.

.. _participants.set_state:


:ref:`participants.set_state <participants.set_state>`
	* **Summary**: Change state and trust level of participant
	* **Arguments**: 
		* ``participant``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``permission``: `com.digitalasset.canton.topology.transaction.ParticipantPermission <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/ParticipantPermission.html>`_
		* ``trustLevel``: `com.digitalasset.canton.topology.transaction.TrustLevel <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TrustLevel.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Description**: Set the state of the participant within the domain.   Valid permissions are 'Submission', 'Confirmation', 'Observation' and 'Disabled'.   Valid trust levels are 'Vip' and 'Ordinary'.   Synchronize timeout can be used to ensure that the state has been propagated into the node   


Sequencer
~~~~~~~~~

.. _sequencer.disable_member:


:ref:`sequencer.disable_member <sequencer.disable_member>`
	* **Summary**: Disable the provided member at the Sequencer that will allow any unread data for them to be removed
	* **Arguments**: 
		* ``member``: `com.digitalasset.canton.topology.Member <../../canton/scaladoc/com/digitalasset/canton/topology/Member.html>`_
	* **Description**: This will prevent any client for the given member to reconnect the Sequencer and allow any unread/unacknowledged data they have to be removed. This should only be used if the domain operation is confident the member will never need to reconnect as there is no way to re-enable the member. To view members using the sequencer run `sequencer.status()`."

.. _sequencer.help:


:ref:`sequencer.help <sequencer.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _sequencer.pruning.clear_schedule:


:ref:`sequencer.pruning.clear_schedule <sequencer.pruning.clear_schedule>`
	* **Summary**: Deactivate automatic pruning.

.. _sequencer.pruning.force_prune:


:ref:`sequencer.pruning.force_prune <sequencer.pruning.force_prune>`
	* **Summary**: Force remove data from the Sequencer including data that may have not been read by offline clients
	* **Arguments**: 
		* ``dryRun``: Boolean
	* **Return type**: 
		* String
	* **Description**: Will force pruning up until the default retention period by potentially disabling clients that have not yet read data we would like to remove. Disabling these clients will prevent them from ever reconnecting to the Domain so should only be used if the Domain operator is confident they can be permanently ignored. Run with `dryRun = true` to review a description of which clients will be disabled first. Run with `dryRun = false` to disable these clients and perform a forced pruning. 

.. _sequencer.pruning.force_prune_at:


:ref:`sequencer.pruning.force_prune_at <sequencer.pruning.force_prune_at>`
	* **Summary**: Force removing data from the Sequencer including data that may have not been read by offline clients up until the specified time
	* **Arguments**: 
		* ``timestamp``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``dryRun``: Boolean
	* **Return type**: 
		* String
	* **Description**: Similar to the above `force_prune` command but allows specifying the exact time at which to prune

.. _sequencer.pruning.force_prune_with_retention_period:


:ref:`sequencer.pruning.force_prune_with_retention_period <sequencer.pruning.force_prune_with_retention_period>`
	* **Summary**: Force removing data from the Sequencer including data that may have not been read by offline clients up until a custom retention period
	* **Arguments**: 
		* ``retentionPeriod``: scala.concurrent.duration.FiniteDuration
		* ``dryRun``: Boolean
	* **Return type**: 
		* String
	* **Description**: Similar to the above `force_prune` command but allows specifying a custom retention period

.. _sequencer.pruning.get_schedule:


:ref:`sequencer.pruning.get_schedule <sequencer.pruning.get_schedule>`
	* **Summary**: Inspect the automatic pruning schedule.
	* **Return type**: 
		* `Option[com.digitalasset.canton.admin.api.client.data.PruningSchedule] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PruningSchedule.html>`_
	* **Description**: The schedule consists of a "cron" expression and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period. Returns `None` if no schedule has been configured via `set_schedule` or if `clear_schedule` has been invoked.   

.. _sequencer.pruning.help:


:ref:`sequencer.pruning.help <sequencer.pruning.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _sequencer.pruning.locate_pruning_timestamp:


:ref:`sequencer.pruning.locate_pruning_timestamp <sequencer.pruning.locate_pruning_timestamp>`
	* **Summary**: Obtain a timestamp at or near the beginning of sequencer state
	* **Arguments**: 
		* ``index``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Option[com.digitalasset.canton.data.CantonTimestamp] <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Description**: This command provides insight into the current state of sequencer pruning when called with the default value of `index` 1. When pruning the sequencer manually via `prune_at` and with the intent to prune in batches, specify a value such as 1000 to obtain a pruning timestamp that corresponds to the "end" of the batch.

.. _sequencer.pruning.prune:


:ref:`sequencer.pruning.prune <sequencer.pruning.prune>`
	* **Summary**: Remove unnecessary data from the Sequencer up until the default retention point
	* **Return type**: 
		* String
	* **Description**: Removes unnecessary data from the Sequencer that is earlier than the default retention period. The default retention period is set in the configuration of the canton processing running this command under `parameters.retention-period-defaults.sequencer`. This pruning command requires that data is read and acknowledged by clients before considering it safe to remove. If no data is being removed it could indicate that clients are not reading or acknowledging data in a timely fashion (typically due to nodes going offline for long periods). You have the option of disabling the members running on these nodes to allow removal of this data, however this will mean that they will be unable to reconnect to the domain in the future. To do this run `force_prune(dryRun = true)` to return a description of which members would be disabled in order to prune the Sequencer. If you are happy to disable the described clients then run `force_prune(dryRun = false)` to permanently remove their unread data. Once offline clients have been disabled you can continue to run `prune` normally. 

.. _sequencer.pruning.prune_at:


:ref:`sequencer.pruning.prune_at <sequencer.pruning.prune_at>`
	* **Summary**: Remove data that has been read up until the specified time
	* **Arguments**: 
		* ``timestamp``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Return type**: 
		* String
	* **Description**: Similar to the above `prune` command but allows specifying the exact time at which to prune. The command will fail if a client has not yet read and acknowledged some data up to the specified time.

.. _sequencer.pruning.prune_with_retention_period:


:ref:`sequencer.pruning.prune_with_retention_period <sequencer.pruning.prune_with_retention_period>`
	* **Summary**: Remove data that has been read up until a custom retention period
	* **Arguments**: 
		* ``retentionPeriod``: scala.concurrent.duration.FiniteDuration
	* **Return type**: 
		* String
	* **Description**: Similar to the above `prune` command but allows specifying a custom retention period

.. _sequencer.pruning.set_cron:


:ref:`sequencer.pruning.set_cron <sequencer.pruning.set_cron>`
	* **Summary**: Modify the cron used by automatic pruning.
	* **Arguments**: 
		* ``cron``: String
	* **Description**: The schedule is specified in cron format and refers to pruning start times in the GMT time zone. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _sequencer.pruning.set_max_duration:


:ref:`sequencer.pruning.set_max_duration <sequencer.pruning.set_max_duration>`
	* **Summary**: Modify the maximum duration used by automatic pruning.
	* **Arguments**: 
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `maxDuration` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _sequencer.pruning.set_retention:


:ref:`sequencer.pruning.set_retention <sequencer.pruning.set_retention>`
	* **Summary**: Update the pruning retention used by automatic pruning.
	* **Arguments**: 
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `retention` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this update, pruning is actively running, a best effort is made to pause pruning and restart with the newly specified retention. This allows for the case that the new retention mandates retaining more data than previously.   

.. _sequencer.pruning.set_schedule:


:ref:`sequencer.pruning.set_schedule <sequencer.pruning.set_schedule>`
	* **Summary**: Activate automatic pruning according to the specified schedule.
	* **Arguments**: 
		* ``cron``: String
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The schedule is specified in cron format and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period.   

.. _sequencer.pruning.status:


:ref:`sequencer.pruning.status <sequencer.pruning.status>`
	* **Summary**: Status of the sequencer and its connected clients
	* **Return type**: 
		* `com.digitalasset.canton.domain.sequencing.sequencer.SequencerPruningStatus <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/SequencerPruningStatus.html>`_
	* **Description**: Provides a detailed breakdown of information required for pruning: - the current time according to this sequencer instance - domain members that the sequencer supports - for each member when they were registered and whether they are enabled - a list of clients for each member, their last acknowledgement, and whether they are enabled 


Mediator
~~~~~~~~

.. _mediator.clear_schedule:


:ref:`mediator.clear_schedule <mediator.clear_schedule>`
	* **Summary**: Deactivate automatic pruning.

.. _mediator.get_schedule:


:ref:`mediator.get_schedule <mediator.get_schedule>`
	* **Summary**: Inspect the automatic pruning schedule.
	* **Return type**: 
		* `Option[com.digitalasset.canton.admin.api.client.data.PruningSchedule] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PruningSchedule.html>`_
	* **Description**: The schedule consists of a "cron" expression and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period. Returns `None` if no schedule has been configured via `set_schedule` or if `clear_schedule` has been invoked.   

.. _mediator.help:


:ref:`mediator.help <mediator.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _mediator.locate_pruning_timestamp:


:ref:`mediator.locate_pruning_timestamp <mediator.locate_pruning_timestamp>`
	* **Summary**: Obtain a timestamp at or near the beginning of mediator state
	* **Arguments**: 
		* ``index``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Option[com.digitalasset.canton.data.CantonTimestamp] <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Description**: This command provides insight into the current state of mediator pruning when called with the default value of `index` 1. When pruning the mediator manually via `prune_at` and with the intent to prune in batches, specify a value such as 1000 to obtain a pruning timestamp that corresponds to the "end" of the batch.

.. _mediator.prune:


:ref:`mediator.prune <mediator.prune>`
	* **Summary**: Prune the mediator of unnecessary data while keeping data for the default retention period
	* **Description**: Removes unnecessary data from the Mediator that is earlier than the default retention period. The default retention period is set in the configuration of the canton node running this command under `parameters.retention-period-defaults.mediator`.

.. _mediator.prune_at:


:ref:`mediator.prune_at <mediator.prune_at>`
	* **Summary**: Prune the mediator of unnecessary data up to and including the given timestamp
	* **Arguments**: 
		* ``timestamp``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_

.. _mediator.prune_with_retention_period:


:ref:`mediator.prune_with_retention_period <mediator.prune_with_retention_period>`
	* **Summary**: Prune the mediator of unnecessary data while keeping data for the provided retention period
	* **Arguments**: 
		* ``retentionPeriod``: scala.concurrent.duration.FiniteDuration

.. _mediator.set_cron:


:ref:`mediator.set_cron <mediator.set_cron>`
	* **Summary**: Modify the cron used by automatic pruning.
	* **Arguments**: 
		* ``cron``: String
	* **Description**: The schedule is specified in cron format and refers to pruning start times in the GMT time zone. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _mediator.set_max_duration:


:ref:`mediator.set_max_duration <mediator.set_max_duration>`
	* **Summary**: Modify the maximum duration used by automatic pruning.
	* **Arguments**: 
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `maxDuration` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _mediator.set_retention:


:ref:`mediator.set_retention <mediator.set_retention>`
	* **Summary**: Update the pruning retention used by automatic pruning.
	* **Arguments**: 
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `retention` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this update, pruning is actively running, a best effort is made to pause pruning and restart with the newly specified retention. This allows for the case that the new retention mandates retaining more data than previously.   

.. _mediator.set_schedule:


:ref:`mediator.set_schedule <mediator.set_schedule>`
	* **Summary**: Activate automatic pruning according to the specified schedule.
	* **Arguments**: 
		* ``cron``: String
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The schedule is specified in cron format and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period.   


.. _mediator.testing.await_domain_time:


:ref:`mediator.testing.await_domain_time (Testing) <mediator.testing.await_domain_time>`
	* **Summary**: Await for the given time to be reached on the domain
	* **Arguments**: 
		* ``time``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_

.. _mediator.testing.fetch_domain_time:


:ref:`mediator.testing.fetch_domain_time (Testing) <mediator.testing.fetch_domain_time>`
	* **Summary**: Fetch the current time from the domain
	* **Arguments**: 
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_

.. _mediator.testing.help:


:ref:`mediator.testing.help <mediator.testing.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


.. _domain-keys-admin:

Key Administration
~~~~~~~~~~~~~~~~~~

.. _keys.help_1:


:ref:`keys.help <keys.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


.. _keys.public.download_1:


:ref:`keys.public.download <keys.public.download_1>`
	* **Summary**: Download public key
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString

.. _keys.public.download_to_1:


:ref:`keys.public.download_to <keys.public.download_to_1>`
	* **Summary**: Download public key and save it to a file
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``outputFile``: String
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_

.. _keys.public.help_1:


:ref:`keys.public.help <keys.public.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _keys.public.list_1:


:ref:`keys.public.list <keys.public.list_1>`
	* **Summary**: List public keys in registry
	* **Arguments**: 
		* ``filterFingerprint``: String
		* ``filterContext``: String
	* **Return type**: 
		* `Seq[com.digitalasset.canton.crypto.PublicKeyWithName] <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKeyWithName.html>`_
	* **Description**: Returns all public keys that have been added to the key registry.   Optional arguments can be used for filtering.

.. _keys.public.list_by_owner_1:


:ref:`keys.public.list_by_owner <keys.public.list_by_owner_1>`
	* **Summary**: List keys for given keyOwner.
	* **Arguments**: 
		* ``keyOwner``: `com.digitalasset.canton.topology.KeyOwner <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwner.html>`_
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListKeyOwnersResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListKeyOwnersResult.html>`_
	* **Description**: This command is a convenience wrapper for `list_key_owners`, taking an explicit keyOwner as search argument. The response includes the public keys.

.. _keys.public.list_owners_1:


:ref:`keys.public.list_owners <keys.public.list_owners_1>`
	* **Summary**: List active owners with keys for given search arguments.
	* **Arguments**: 
		* ``filterKeyOwnerUid``: String
		* ``filterKeyOwnerType``: `Option[com.digitalasset.canton.topology.KeyOwnerCode] <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwnerCode.html>`_
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListKeyOwnersResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListKeyOwnersResult.html>`_
	* **Description**: This command allows deep inspection of the topology state. The response includes the public keys. Optional filterKeyOwnerType type can be 'ParticipantId.Code' , 'MediatorId.Code','SequencerId.Code', 'DomainTopologyManagerId.Code'. 

.. _keys.public.upload_2:


:ref:`keys.public.upload <keys.public.upload_2>`
	* **Summary**: Upload public key
	* **Arguments**: 
		* ``filename``: String
		* ``name``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_

.. _keys.public.upload_3:


:ref:`keys.public.upload <keys.public.upload_3>`
	* **Summary**: Upload public key
	* **Arguments**: 
		* ``keyBytes``: com.google.protobuf.ByteString
		* ``name``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Description**: Import a public key and store it together with a name used to provide some context to that key.


.. _keys.secret.delete_1:


:ref:`keys.secret.delete <keys.secret.delete_1>`
	* **Summary**: Delete private key
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``force``: Boolean

.. _keys.secret.download_1:


:ref:`keys.secret.download <keys.secret.download_1>`
	* **Summary**: Download key pair
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString

.. _keys.secret.download_to_1:


:ref:`keys.secret.download_to <keys.secret.download_to_1>`
	* **Summary**: Download key pair and save it to a file
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``outputFile``: String
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_

.. _keys.secret.generate_encryption_key_1:


:ref:`keys.secret.generate_encryption_key <keys.secret.generate_encryption_key_1>`
	* **Summary**: Generate new public/private key pair for encryption and store it in the vault
	* **Arguments**: 
		* ``name``: String
		* ``scheme``: `Option[com.digitalasset.canton.crypto.EncryptionKeyScheme] <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionKeyScheme.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.EncryptionPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionPublicKey.html>`_
	* **Description**:  The optional name argument allows you to store an associated string for your convenience. The scheme can be used to select a key scheme and the default scheme is used if left unspecified.

.. _keys.secret.generate_signing_key_1:


:ref:`keys.secret.generate_signing_key <keys.secret.generate_signing_key_1>`
	* **Summary**: Generate new public/private key pair for signing and store it in the vault
	* **Arguments**: 
		* ``name``: String
		* ``scheme``: `Option[com.digitalasset.canton.crypto.SigningKeyScheme] <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningKeyScheme.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.SigningPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningPublicKey.html>`_
	* **Description**:  The optional name argument allows you to store an associated string for your convenience. The scheme can be used to select a key scheme and the default scheme is used if left unspecified.

.. _keys.secret.get_wrapper_key_id_1:


:ref:`keys.secret.get_wrapper_key_id <keys.secret.get_wrapper_key_id_1>`
	* **Summary**: Get the wrapper key id that is used for the encrypted private keys store
	* **Return type**: 
		* String

.. _keys.secret.help_1:


:ref:`keys.secret.help <keys.secret.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _keys.secret.list_1:


:ref:`keys.secret.list <keys.secret.list_1>`
	* **Summary**: List keys in private vault
	* **Arguments**: 
		* ``filterFingerprint``: String
		* ``filterName``: String
		* ``purpose``: `Set[com.digitalasset.canton.crypto.KeyPurpose] <../../canton/scaladoc/com/digitalasset/canton/crypto/KeyPurpose.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.crypto.admin.grpc.PrivateKeyMetadata] <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/PrivateKeyMetadata.html>`_
	* **Description**: Returns all public keys to the corresponding private keys in the key vault. Optional arguments can be used for filtering.

.. _keys.secret.register_kms_encryption_key_1:


:ref:`keys.secret.register_kms_encryption_key <keys.secret.register_kms_encryption_key_1>`
	* **Summary**: Register the specified KMS encryption key in canton storing its public information in the vault
	* **Arguments**: 
		* ``kmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.EncryptionPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionPublicKey.html>`_
	* **Description**:  The id for the KMS encryption key. The optional name argument allows you to store an associated string for your convenience.

.. _keys.secret.register_kms_signing_key_1:


:ref:`keys.secret.register_kms_signing_key <keys.secret.register_kms_signing_key_1>`
	* **Summary**: Register the specified KMS signing key in canton storing its public information in the vault
	* **Arguments**: 
		* ``kmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.SigningPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningPublicKey.html>`_
	* **Description**:  The id for the KMS signing key. The optional name argument allows you to store an associated string for your convenience.

.. _keys.secret.rotate_kms_node_key_1:


:ref:`keys.secret.rotate_kms_node_key <keys.secret.rotate_kms_node_key_1>`
	* **Summary**: Rotate a given node's keypair with a new pre-generated KMS keypair
	* **Arguments**: 
		* ``fingerprint``: String
		* ``newKmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates an existing encryption or signing key stored externally in a KMS with a pre-generated    key. For a sequencer or mediator node use `rotate_kms_node_key` with a domain manager reference as an argument. The fingerprint of the key we want to rotate. The id of the new KMS key (e.g. Resource Name). An optional name for the new key.

.. _keys.secret.rotate_node_key_1:


:ref:`keys.secret.rotate_node_key <keys.secret.rotate_node_key_1>`
	* **Summary**: Rotate a node's public/private key pair
	* **Arguments**: 
		* ``fingerprint``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates an existing encryption or signing key. NOTE: A namespace root or intermediate    signing key CANNOT be rotated by this command. For a sequencer or mediator node use `rotate_kms_node_key` with    a domain manager reference as an argument. The fingerprint of the key we want to rotate. An optional name for the new key.

.. _keys.secret.rotate_node_keys_1:


:ref:`keys.secret.rotate_node_keys <keys.secret.rotate_node_keys_1>`
	* **Summary**: Rotate the node's public/private key pairs
	* **Description**:  For a participant node it rotates the signing and encryption key pair. For a domain or domain manager node it rotates the signing key pair as those nodes do not have an encryption key pair. For a sequencer or mediator node use `rotate_node_keys` with a domain manager reference as an argument. NOTE: Namespace root or intermediate signing keys are NOT rotated by this command.

.. _keys.secret.rotate_wrapper_key_1:


:ref:`keys.secret.rotate_wrapper_key <keys.secret.rotate_wrapper_key_1>`
	* **Summary**: Change the wrapper key for encrypted private keys store
	* **Arguments**: 
		* ``newWrapperKeyId``: String
	* **Description**: Change the wrapper key (e.g. AWS KMS key) being used to encrypt the private keys in the store. newWrapperKeyId: The optional new wrapper key id to be used. If the wrapper key id is empty Canton will generate a new key based on the current configuration.

.. _keys.secret.upload_2:


:ref:`keys.secret.upload <keys.secret.upload_2>`
	* **Summary**: Upload a key pair
	* **Arguments**: 
		* ``pairBytes``: com.google.protobuf.ByteString
		* ``name``: Option[String]

.. _keys.secret.upload_3:


:ref:`keys.secret.upload <keys.secret.upload_3>`
	* **Summary**: Upload (load and import) a key pair from file
	* **Arguments**: 
		* ``filename``: String
		* ``name``: Option[String]


.. _domain-parties-admin:

Parties
~~~~~~~

.. _parties.help_1:


:ref:`parties.help <parties.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _parties.list_1:


:ref:`parties.list <parties.list_1>`
	* **Summary**: List active parties, their active participants, and the participants' permissions on domains.
	* **Arguments**: 
		* ``filterParty``: String
		* ``filterParticipant``: String
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListPartiesResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListPartiesResult.html>`_
	* **Description**: Inspect the parties known by this participant as used for synchronisation. The response is built from the timestamped topology transactions of each domain, excluding the authorized store of the given node. For each known party, the list of active participants and their permission on the domain for that party is given.    filterParty: Filter by parties starting with the given string.    filterParticipant: Filter for parties that are hosted by a participant with an id starting with the given string    filterDomain: Filter by domains whose id starts with the given string.    asOf: Optional timestamp to inspect the topology state at a given point in time.    limit: Limit on the number of parties fetched (defaults to canton.parameters.console.default-limit).    Example: participant1.parties.list(filterParty="alice")    


Service
~~~~~~~

.. _service.get_dynamic_domain_parameters:


:ref:`service.get_dynamic_domain_parameters <service.get_dynamic_domain_parameters>`
	* **Summary**: Get the Dynamic Domain Parameters configured for the domain
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_

.. _service.get_max_rate_per_participant:


:ref:`service.get_max_rate_per_participant <service.get_max_rate_per_participant>`
	* **Summary**: Get the max rate per participant
	* **Return type**: 
		* `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
	* **Description**: Depending on the protocol version used on the domain, the value will be     read either from the static domain parameters or the dynamic ones.

.. _service.get_max_request_size:


:ref:`service.get_max_request_size <service.get_max_request_size>`
	* **Summary**: Get the max request size
	* **Return type**: 
		* `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
	* **Description**: Depending on the protocol version used on the domain, the value will be     read either from the static domain parameters or the dynamic ones.     This value is not necessarily the one used by the sequencer node because it requires a restart     of the server to be taken into account.

.. _service.get_mediator_deduplication_timeout:


:ref:`service.get_mediator_deduplication_timeout <service.get_mediator_deduplication_timeout>`
	* **Summary**: Get the mediator deduplication timeout
	* **Return type**: 
		* `com.digitalasset.canton.config.NonNegativeFiniteDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeFiniteDuration.html>`_
	* **Description**: The method will fail, if the domain does not support the mediatorDeduplicationTimeout.

.. _service.get_reconciliation_interval:


:ref:`service.get_reconciliation_interval <service.get_reconciliation_interval>`
	* **Summary**: Get the reconciliation interval configured for the domain
	* **Return type**: 
		* `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: Depending on the protocol version used on the domain, the value will be     read either from the static domain parameters or the dynamic ones.

.. _service.get_static_domain_parameters:


:ref:`service.get_static_domain_parameters <service.get_static_domain_parameters>`
	* **Summary**: Get the Static Domain Parameters configured for the domain
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.StaticDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/StaticDomainParameters.html>`_

.. _service.help:


:ref:`service.help <service.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _service.list_accepted_agreements:


:ref:`service.list_accepted_agreements <service.list_accepted_agreements>`
	* **Summary**: List the accepted service agreements
	* **Return type**: 
		* `Seq[com.digitalasset.canton.domain.service.ServiceAgreementAcceptance] <../../canton/scaladoc/com/digitalasset/canton/domain/service/ServiceAgreementAcceptance.html>`_

.. _service.set_commitments_catch_up_config:


:ref:`service.set_commitments_catch_up_config <service.set_commitments_catch_up_config>`
	* **Summary**: Update the ACS commitments catch up config for the domain
	* **Arguments**: 
		* ``config``: `com.digitalasset.canton.protocol.CatchUpConfig <../../canton/scaladoc/com/digitalasset/canton/protocol/CatchUpConfig.html>`_
	* **Description**: The method will fail if the domain does not support the ``catchUpConfig`` parameter           (i.e., if the domain is running on protocol version lower than `6`)

.. _service.set_dynamic_domain_parameters:


:ref:`service.set_dynamic_domain_parameters <service.set_dynamic_domain_parameters>`
	* **Summary**: Set the Dynamic Domain Parameters configured for the domain
	* **Arguments**: 
		* ``dynamicDomainParameters``: `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_
		* ``force``: Boolean
	* **Description**: force: Enable potentially dangerous changes. Required to increase ``ledgerTimeRecordTimeTolerance``. Use ``set_ledger_time_record_time_tolerance`` to securely increase ``ledgerTimeRecordTimeTolerance``.

.. _service.set_ledger_time_record_time_tolerance:


:ref:`service.set_ledger_time_record_time_tolerance <service.set_ledger_time_record_time_tolerance>`
	* **Summary**: Update the `ledgerTimeRecordTimeTolerance` in the dynamic domain parameters.
	* **Arguments**: 
		* ``newLedgerTimeRecordTimeTolerance``: `com.digitalasset.canton.config.NonNegativeFiniteDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeFiniteDuration.html>`_
		* ``force``: Boolean
	* **Description**: If it would be insecure to perform the change immediately, the command will block and wait until it is secure to perform the change. The command will block for at most twice of ``newLedgerTimeRecordTimeTolerance``. If the domain does not support ``mediatorDeduplicationTimeout``, the method will update ``ledgerTimeRecordTimeTolerance`` immediately without blocking. The method will fail if ``mediatorDeduplicationTimeout`` is less than twice of ``newLedgerTimeRecordTimeTolerance``. Do not modify domain parameters concurrently while running this command, because the command may override concurrent changes. force: update ``ledgerTimeRecordTimeTolerance`` immediately without blocking. This is safe to do during domain bootstrapping and in test environments, but should not be done in operational production systems..

.. _service.set_max_inbound_message_size:


:ref:`service.set_max_inbound_message_size <service.set_max_inbound_message_size>`
	* **Summary**: Try to update the max rate per participant for the domain
	* **Arguments**: 
		* ``maxRequestSize``: `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
		* ``force``: Boolean
	* **Description**: If the max request size is dynamic, update the value.             The update won't have any effect unless the sequencer server is restarted.   If the max request size is not dynamic (i.e., if the domain is running   on protocol version lower than `4`), then it will throw an error.   

.. _service.set_max_rate_per_participant:


:ref:`service.set_max_rate_per_participant <service.set_max_rate_per_participant>`
	* **Summary**: Try to update the max rate per participant for the domain
	* **Arguments**: 
		* ``maxRatePerParticipant``: `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
	* **Description**: If the max rate per participant is dynamic, update the value.     If the max rate per participant is not dynamic (i.e., if the domain is running     on protocol version lower than `4`), then it will throw an error.     

.. _service.set_max_request_size:


:ref:`service.set_max_request_size <service.set_max_request_size>`
	* **Summary**: Try to update the max rate per participant for the domain
	* **Arguments**: 
		* ``maxRequestSize``: `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
		* ``force``: Boolean
	* **Description**: If the max request size is dynamic, update the value.             The update won't have any effect unless the sequencer server is restarted.   If the max request size is not dynamic (i.e., if the domain is running   on protocol version lower than `4`), then it will throw an error.   

.. _service.set_mediator_deduplication_timeout:


:ref:`service.set_mediator_deduplication_timeout <service.set_mediator_deduplication_timeout>`
	* **Summary**: Update the mediator deduplication timeout
	* **Arguments**: 
		* ``newMediatorDeduplicationTimeout``: `com.digitalasset.canton.config.NonNegativeFiniteDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeFiniteDuration.html>`_
	* **Description**: The method will fail: - if the domain does not support the ``mediatorDeduplicationTimeout`` parameter, - if the new value of ``mediatorDeduplicationTimeout`` is less than twice the value of ``ledgerTimeRecordTimeTolerance.``

.. _service.set_reconciliation_interval:


:ref:`service.set_reconciliation_interval <service.set_reconciliation_interval>`
	* **Summary**: Try to update the reconciliation interval for the domain
	* **Arguments**: 
		* ``newReconciliationInterval``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: If the reconciliation interval is dynamic, update the value.     If the reconciliation interval is not dynamic (i.e., if the domain is running     on protocol version lower than `4`), then it will throw an error.     

.. _service.update_dynamic_domain_parameters:


:ref:`service.update_dynamic_domain_parameters <service.update_dynamic_domain_parameters>`
	* **Summary**: Update the Dynamic Domain Parameters for the domain
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters => com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_
		* ``force``: Boolean
	* **Description**: force: Enable potentially dangerous changes. Required to increase ``ledgerTimeRecordTimeTolerance``. Use ``set_ledger_time_record_time_tolerance_securely`` to securely increase ``ledgerTimeRecordTimeTolerance``.

.. _service.update_dynamic_parameters:


:ref:`service.update_dynamic_parameters <service.update_dynamic_parameters>`
	* **Summary**: Update the Dynamic Domain Parameters for the domain
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters => com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_
		* ``force``: Boolean
	* **Description**: force: Enable potentially dangerous changes. Required to increase ``ledgerTimeRecordTimeTolerance``. Use ``set_ledger_time_record_time_tolerance_securely`` to securely increase ``ledgerTimeRecordTimeTolerance``.



.. _domain-topology-admin:

Topology Administration
~~~~~~~~~~~~~~~~~~~~~~~

Topology commands run on the domain topology manager immediately affect the topology state
of the domain, which means that all changes are immediately pushed to the connected participants.

.. _topology.help_1:


:ref:`topology.help <topology.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.init_id_1:


:ref:`topology.init_id <topology.init_id_1>`
	* **Summary**: Initialize the node with a unique identifier
	* **Arguments**: 
		* ``identifier``: `com.digitalasset.canton.topology.Identifier <../../canton/scaladoc/com/digitalasset/canton/topology/Identifier.html>`_
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.topology.UniqueIdentifier <../../canton/scaladoc/com/digitalasset/canton/topology/UniqueIdentifier.html>`_
	* **Description**: Every node in Canton is identified using a unique identifier, which is composed of a user-chosen string and the fingerprint of a signing key. The signing key is the root key defining a so-called namespace, where the signing key has the ultimate control over issuing new identifiers. During initialisation, we have to pick such a unique identifier. By default, initialisation happens automatically, but it can be turned off by setting the auto-init option to false. Automatic node initialisation is usually turned off to preserve the identity of a participant or domain node (during major version upgrades) or if the topology transactions are managed through a different topology manager than the one integrated into this node.

.. _topology.load_transaction_1:


:ref:`topology.load_transaction <topology.load_transaction_1>`
	* **Summary**: Upload signed topology transaction
	* **Arguments**: 
		* ``bytes``: com.google.protobuf.ByteString
	* **Description**: Topology transactions can be issued with any topology manager. In some cases, such transactions need to be copied manually between nodes. This function allows for uploading previously exported topology transaction into the authorized store (which is the name of the topology managers transaction store.


.. _topology.stores.help_1:


:ref:`topology.stores.help <topology.stores.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.stores.list_1:


:ref:`topology.stores.list <topology.stores.list_1>`
	* **Summary**: List available topology stores
	* **Return type**: 
		* Seq[String]
	* **Description**: Topology transactions are stored in these stores. There are the following stores: "Authorized" - The authorized store is the store of a topology manager. Updates to the topology state are made by adding new transactions to the "Authorized" store. Both the participant and the domain nodes topology manager have such a store. A participant node will distribute all the content in the Authorized store to the domains it is connected to. The domain node will distribute the content of the Authorized store through the sequencer to the domain members in order to create the authoritative topology state on a domain (which is stored in the store named using the domain-id), such that every domain member will have the same view on the topology state on a particular domain. "<domain-id>" - The domain store is the authorized topology state on a domain. A participant has one store for each domain it is connected to. The domain has exactly one store with its domain-id. "Requested" - A domain can be configured such that when participant tries to register a topology transaction with the domain, the transaction is placed into the "Requested" store such that it can be analysed and processed with user defined process. 


.. _topology.namespace_delegations.authorize_1:


:ref:`topology.namespace_delegations.authorize <topology.namespace_delegations.authorize_1>`
	* **Summary**: Change namespace delegation
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``namespace``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``authorizedKey``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``isRootDelegation``: Boolean
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Delegates the authority to authorize topology transactions in a certain namespace to a certain key. The keys are referred to using their fingerprints. They need to be either locally generated or have been previously imported.   ops: Either Add or Remove the delegation.   namespace: The namespace whose authorization authority is delegated.   signedBy: Optional fingerprint of the authorizing key. The authorizing key needs to be either the authorizedKey        for root certificates. Otherwise, the signedBy key needs to refer to a previously authorized key, which        means that we use the signedBy key to refer to a locally available CA.   authorizedKey: Fingerprint of the key to be authorized. If signedBy equals authorizedKey, then this transaction          corresponds to a self-signed root certificate. If the keys differ, then we get an intermediate CA.   isRootDelegation: If set to true (default = false), the authorized key will be allowed to issue NamespaceDelegations.   synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node

.. _topology.namespace_delegations.help_1:


:ref:`topology.namespace_delegations.help <topology.namespace_delegations.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.namespace_delegations.list_1:


:ref:`topology.namespace_delegations.list <topology.namespace_delegations.list_1>`
	* **Summary**: List namespace delegation transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterNamespace``: String
		* ``filterSigningKey``: String
		* ``filterTargetKey``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListNamespaceDelegationResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListNamespaceDelegationResult.html>`_
	* **Description**: List the namespace delegation transaction present in the stores. Namespace delegations are topology transactions that permission a key to issue topology transactions within a certain namespace.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterNamespace: Filter for namespaces starting with the given filter string.     filterTargetKey: Filter for namespaces delegations for the given target key.     protocolVersion: Export the topology transactions in the optional protocol version.     


.. _topology.identifier_delegations.authorize_1:


:ref:`topology.identifier_delegations.authorize <topology.identifier_delegations.authorize_1>`
	* **Summary**: Change identifier delegation
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``identifier``: `com.digitalasset.canton.topology.UniqueIdentifier <../../canton/scaladoc/com/digitalasset/canton/topology/UniqueIdentifier.html>`_
		* ``authorizedKey``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Delegates the authority of a certain identifier to a certain key. This corresponds to a normal certificate which binds identifier to a key. The keys are referred to using their fingerprints. They need to be either locally generated or have been previously imported.   ops: Either Add or Remove the delegation.   signedBy: Refers to the optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.   authorizedKey: Fingerprint of the key to be authorized.   synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    

.. _topology.identifier_delegations.help_1:


:ref:`topology.identifier_delegations.help <topology.identifier_delegations.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.identifier_delegations.list_1:


:ref:`topology.identifier_delegations.list <topology.identifier_delegations.list_1>`
	* **Summary**: List identifier delegation transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterUid``: String
		* ``filterSigningKey``: String
		* ``filterTargetKey``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListIdentifierDelegationResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListIdentifierDelegationResult.html>`_
	* **Description**: List the identifier delegation transaction present in the stores. Identifier delegations are topology transactions that permission a key to issue topology transactions for a certain unique identifier.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterUid: Filter for unique identifiers starting with the given filter string.     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.owner_to_key_mappings.authorize_1:


:ref:`topology.owner_to_key_mappings.authorize <topology.owner_to_key_mappings.authorize_1>`
	* **Summary**: Change an owner to key mapping
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``keyOwner``: `com.digitalasset.canton.topology.KeyOwner <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwner.html>`_
		* ``key``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``purpose``: `com.digitalasset.canton.crypto.KeyPurpose <../../canton/scaladoc/com/digitalasset/canton/crypto/KeyPurpose.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Change a owner to key mapping. A key owner is anyone in the system that needs a key-pair known to all members (participants, mediator, sequencer, topology manager) of a domain.  ops: Either Add or Remove the key mapping update.  signedBy: Optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.  ownerType: Role of the following owner (Participant, Sequencer, Mediator, DomainTopologyManager)  owner: Unique identifier of the owner.  key: Fingerprint of key  purposes: The purposes of the owner to key mapping.  force: removing the last key is dangerous and must therefore be manually forced  synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node  

.. _topology.owner_to_key_mappings.help_1:


:ref:`topology.owner_to_key_mappings.help <topology.owner_to_key_mappings.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.owner_to_key_mappings.list_1:


:ref:`topology.owner_to_key_mappings.list <topology.owner_to_key_mappings.list_1>`
	* **Summary**: List owner to key mapping transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterKeyOwnerType``: `Option[com.digitalasset.canton.topology.KeyOwnerCode] <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwnerCode.html>`_
		* ``filterKeyOwnerUid``: String
		* ``filterKeyPurpose``: `Option[com.digitalasset.canton.crypto.KeyPurpose] <../../canton/scaladoc/com/digitalasset/canton/crypto/KeyPurpose.html>`_
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListOwnerToKeyMappingResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListOwnerToKeyMappingResult.html>`_
	* **Description**: List the owner to key mapping transactions present in the stores. Owner to key mappings are topology transactions defining that a certain key is used by a certain key owner. Key owners are participants, sequencers, mediators and domains.    filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)    useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.    timeQuery: The time query allows to customize the query by time. The following options are supported:         TimeQuery.HeadState (default): The most recent known state.         TimeQuery.Snapshot(ts): The state at a certain point in time.         TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store    operation: Optionally, what type of operation the transaction should have. State store only has "Add".    filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.    filterKeyOwnerType: Filter for a particular type of key owner (KeyOwnerCode).    filterKeyOwnerUid: Filter for key owners unique identifier starting with the given filter string.    filterKeyPurpose: Filter for keys with a particular purpose (Encryption or Signing)    protocolVersion: Export the topology transactions in the optional protocol version. 

.. _topology.owner_to_key_mappings.rotate_key_1:


:ref:`topology.owner_to_key_mappings.rotate_key <topology.owner_to_key_mappings.rotate_key_1>`
	* **Summary**: Rotate the key for an owner to key mapping
	* **Arguments**: 
		* ``nodeInstance``: `com.digitalasset.canton.console.InstanceReferenceCommon <../../canton/scaladoc/com/digitalasset/canton/console/InstanceReferenceCommon.html>`_
		* ``owner``: `com.digitalasset.canton.topology.KeyOwner <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwner.html>`_
		* ``currentKey``: `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
		* ``newKey``: `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates the key for an existing owner to key mapping by issuing a new owner to key mapping with the new key and removing the previous owner to key mapping with the previous key.    nodeInstance: The node instance that is used to verify that both current and new key pertain to this node. This avoids conflicts when there are different nodes with the same uuid (i.e., multiple sequencers).    owner: The owner of the owner to key mapping    currentKey: The current public key that will be rotated    newKey: The new public key that has been generated 


.. _topology.party_to_participant_mappings.authorize_1:


:ref:`topology.party_to_participant_mappings.authorize (Preview) <topology.party_to_participant_mappings.authorize_1>`
	* **Summary**: Change party to participant mapping
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``party``: `com.digitalasset.canton.topology.PartyId <../../canton/scaladoc/com/digitalasset/canton/topology/PartyId.html>`_
		* ``participant``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``side``: `com.digitalasset.canton.topology.transaction.RequestSide <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/RequestSide.html>`_
		* ``permission``: `com.digitalasset.canton.topology.transaction.ParticipantPermission <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/ParticipantPermission.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``replaceExisting``: Boolean
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Change the association of a party to a participant. If both identifiers are in the same namespace, then the request-side is Both. If they differ, then we need to say whether the request comes from the party (RequestSide.From) or from the participant (RequestSide.To). And, we need the matching request of the other side. Please note that this is a preview feature due to the fact that inhomogeneous topologies can not yet be properly represented on the Ledger API.    ops: Either Add or Remove the mapping    signedBy: Refers to the optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.    party: The unique identifier of the party we want to map to a participant.    participant: The unique identifier of the participant to which the party is supposed to be mapped.    side: The request side (RequestSide.From if we the transaction is from the perspective of the party, RequestSide.To from the participant.)    privilege: The privilege of the given participant which allows us to restrict an association (e.g. Confirmation or Observation).    replaceExisting: If true (default), replace any existing mapping with the new setting    synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    

.. _topology.party_to_participant_mappings.help_1:


:ref:`topology.party_to_participant_mappings.help <topology.party_to_participant_mappings.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.party_to_participant_mappings.list_1:


:ref:`topology.party_to_participant_mappings.list <topology.party_to_participant_mappings.list_1>`
	* **Summary**: List party to participant mapping transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterParty``: String
		* ``filterParticipant``: String
		* ``filterRequestSide``: `Option[com.digitalasset.canton.topology.transaction.RequestSide] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/RequestSide.html>`_
		* ``filterPermission``: `Option[com.digitalasset.canton.topology.transaction.ParticipantPermission] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/ParticipantPermission.html>`_
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListPartyToParticipantResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListPartyToParticipantResult.html>`_
	* **Description**: List the party to participant mapping transactions present in the stores. Party to participant mappings are topology transactions used to allocate a party to a certain participant. The same party can be allocated on several participants with different privileges. A party to participant mapping has a request-side that identifies whether the mapping is authorized by the party, by the participant or by both. In order to have a party be allocated to a given participant, we therefore need either two transactions (one with RequestSide.From, one with RequestSide.To) or one with RequestSide.Both.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterParty: Filter for parties starting with the given filter string.     filterParticipant: Filter for participants starting with the given filter string.     filterRequestSide: Optional filter for a particular request side (Both, From, To).     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.participant_domain_states.active_1:


:ref:`topology.participant_domain_states.active <topology.participant_domain_states.active_1>`
	* **Summary**: Returns true if the given participant is currently active on the given domain
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``participantId``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
	* **Return type**: 
		* Boolean
	* **Description**: Active means that the participant has been granted at least observation rights on the domain and that the participant has registered a domain trust certificate

.. _topology.participant_domain_states.authorize_1:


:ref:`topology.participant_domain_states.authorize <topology.participant_domain_states.authorize_1>`
	* **Summary**: Change participant domain states
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``domain``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``participant``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``side``: `com.digitalasset.canton.topology.transaction.RequestSide <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/RequestSide.html>`_
		* ``permission``: `com.digitalasset.canton.topology.transaction.ParticipantPermission <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/ParticipantPermission.html>`_
		* ``trustLevel``: `com.digitalasset.canton.topology.transaction.TrustLevel <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TrustLevel.html>`_
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``replaceExisting``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: Change the association of a participant to a domain. In order to activate a participant on a domain, we need both authorisation: the participant authorising its uid to be present on a particular domain and the domain to authorise the presence of a participant on said domain. If both identifiers are in the same namespace, then the request-side can be Both. If they differ, then we need to say whether the request comes from the domain (RequestSide.From) or from the participant (RequestSide.To). And, we need the matching request of the other side.    ops: Either Add or Remove the mapping    signedBy: Refers to the optional fingerprint of the authorizing key which in turn refers to a specific, locally existing certificate.    domain: The unique identifier of the domain we want the participant to join.    participant: The unique identifier of the participant.    side: The request side (RequestSide.From if we the transaction is from the perspective of the domain, RequestSide.To from the participant.)    permission: The privilege of the given participant which allows us to restrict an association (e.g. Confirmation or Observation). Will use the lower of if different between To/From.    trustLevel: The trust level of the participant on the given domain. Will use the lower of if different between To/From.    replaceExisting: If true (default), replace any existing mapping with the new setting    synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    

.. _topology.participant_domain_states.help_1:


:ref:`topology.participant_domain_states.help <topology.participant_domain_states.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.participant_domain_states.list_1:


:ref:`topology.participant_domain_states.list <topology.participant_domain_states.list_1>`
	* **Summary**: List participant domain states
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterDomain``: String
		* ``filterParticipant``: String
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListParticipantDomainStateResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListParticipantDomainStateResult.html>`_
	* **Description**: List the participant domain transactions present in the stores. Participant domain states are topology transactions used to permission a participant on a given domain. A participant domain state has a request-side that identifies whether the mapping is authorized by the participant (From), by the domain (To) or by both (Both). In order to use a participant on a domain, both have to authorize such a mapping. This means that by authorizing such a topology transaction, a participant acknowledges its presence on a domain, whereas a domain permissions the participant on that domain.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterDomain: Filter for domains starting with the given filter string.     filterParticipant: Filter for participants starting with the given filter string.     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.vetted_packages.authorize_1:


:ref:`topology.vetted_packages.authorize <topology.vetted_packages.authorize_1>`
	* **Summary**: Change package vettings
	* **Arguments**: 
		* ``ops``: `com.digitalasset.canton.topology.transaction.TopologyChangeOp <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``participant``: `com.digitalasset.canton.topology.ParticipantId <../../canton/scaladoc/com/digitalasset/canton/topology/ParticipantId.html>`_
		* ``packageIds``: Seq[com.daml.lf.data.Ref.PackageId]
		* ``signedBy``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``synchronize``: `Option[com.digitalasset.canton.config.NonNegativeDuration] <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``force``: Boolean
	* **Return type**: 
		* com.google.protobuf.ByteString
	* **Description**: A participant will only process transactions that reference packages that all involved participants have vetted previously. Vetting is done by registering a respective topology transaction with the domain, which can then be used by other participants to verify that a transaction is only using vetted packages. Note that all referenced and dependent packages must exist in the package store. By default, only vetting transactions adding new packages can be issued. Removing package vettings and issuing package vettings for other participants (if their identity is controlled through this participants topology manager) or for packages that do not exist locally can only be run using the force = true flag. However, these operations are dangerous and can lead to the situation of a participant being unable to process transactions.    ops: Either Add or Remove the vetting.    participant: The unique identifier of the participant that is vetting the package.    packageIds: The lf-package ids to be vetted.    signedBy: Refers to the fingerprint of the authorizing key which in turn must be authorized by a valid, locally existing certificate.  If none is given, a key is automatically determined.    synchronize: Synchronize timeout can be used to ensure that the state has been propagated into the node    force: Flag to enable dangerous operations (default false). Great power requires great care.    

.. _topology.vetted_packages.help_1:


:ref:`topology.vetted_packages.help <topology.vetted_packages.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.vetted_packages.list_1:


:ref:`topology.vetted_packages.list <topology.vetted_packages.list_1>`
	* **Summary**: List package vetting transactions
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterParticipant``: String
		* ``filterSigningKey``: String
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListVettedPackagesResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListVettedPackagesResult.html>`_
	* **Description**: List the package vetting transactions present in the stores. Participants must vet Daml packages and submitters must ensure that the receiving participants have vetted the package prior to submitting a transaction (done automatically during submission and validation). Vetting is done by authorizing such topology transactions and registering with a domain.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterSigningKey: Filter for transactions that are authorized with a key that starts with the given filter string.     filterParticipant: Filter for participants starting with the given filter string.     protocolVersion: Export the topology transactions in the optional protocol version. 


.. _topology.all.help_1:


:ref:`topology.all.help <topology.all.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _topology.all.list_1:


:ref:`topology.all.list <topology.all.list_1>`
	* **Summary**: List all transaction
	* **Arguments**: 
		* ``filterStore``: String
		* ``useStateStore``: Boolean
		* ``timeQuery``: `com.digitalasset.canton.topology.store.TimeQuery <../../canton/scaladoc/com/digitalasset/canton/topology/store/TimeQuery.html>`_
		* ``operation``: `Option[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
		* ``filterAuthorizedKey``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.topology.store.StoredTopologyTransactions[com.digitalasset.canton.topology.transaction.TopologyChangeOp] <../../canton/scaladoc/com/digitalasset/canton/topology/transaction/TopologyChangeOp.html>`_
	* **Description**: List all topology transactions in a store, independent of the particular type. This method is useful for exporting entire states.     filterStore: Filter for topology stores starting with the given filter string (Authorized, <domain-id>, Requested)     useStateStore: If true (default), only properly authorized transactions that are part of the state will be selected.     timeQuery: The time query allows to customize the query by time. The following options are supported:          TimeQuery.HeadState (default): The most recent known state.          TimeQuery.Snapshot(ts): The state at a certain point in time.          TimeQuery.Range(fromO, toO): Time-range of when the transaction was added to the store     operation: Optionally, what type of operation the transaction should have. State store only has "Add".     filterAuthorizedKey: Filter the topology transactions by the key that has authorized the transactions.     protocolVersion: Export the topology transactions in the optional protocol version. 

.. _topology.all.renew_1:


:ref:`topology.all.renew <topology.all.renew_1>`
	* **Summary**: Renew all topology transactions that have been authorized with a previous key using a new key
	* **Arguments**: 
		* ``filterAuthorizedKey``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``authorizeWith``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Description**: Finds all topology transactions that have been authorized by `filterAuthorizedKey` and renews those topology transactions by authorizing them with the new key `authorizeWith`.     filterAuthorizedKey: Filter the topology transactions by the key that has authorized the transactions.     authorizeWith: The key to authorize the renewed topology transactions. 


Domain Manager Administration Commands
--------------------------------------

.. _clear_cache_2:


:ref:`clear_cache (Testing) <clear_cache_2>`
	* **Summary**: Clear locally cached variables
	* **Description**: Some commands cache values on the client side. Use this command to explicitly clear the caches of these values.

.. _config_2:


:ref:`config <config_2>`
	* **Summary**: Returns the domain configuration
	* **Return type**: 
		* `com.digitalasset.canton.domain.config.DomainManagerConfig <../../canton/scaladoc/com/digitalasset/canton/domain/config/DomainManagerConfig.html>`_

.. _help_3:


:ref:`help <help_3>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _id_2:


:ref:`id <id_2>`
	* **Summary**: Yields the globally unique id of this domain. Throws an exception, if the id has not yet been allocated (e.g., the domain has not yet been started).
	* **Return type**: 
		* `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_

.. _is_initialized_2:


:ref:`is_initialized <is_initialized_2>`
	* **Summary**: Check if the local instance is running and is fully initialized
	* **Return type**: 
		* Boolean

.. _is_running_2:


:ref:`is_running <is_running_2>`
	* **Summary**: Check if the local instance is running
	* **Return type**: 
		* Boolean

.. _start_2:


:ref:`start <start_2>`
	* **Summary**: Start the instance

.. _stop_2:


:ref:`stop <stop_2>`
	* **Summary**: Stop the instance


Setup
~~~~~

.. _setup.authorize_mediator:


:ref:`setup.authorize_mediator <setup.authorize_mediator>`
	* **Summary**: Authorize external Mediator node.
	* **Arguments**: 
		* ``mediatorId``: `com.digitalasset.canton.topology.MediatorId <../../canton/scaladoc/com/digitalasset/canton/topology/MediatorId.html>`_
	* **Description**: Use this command to reinstigate an external mediator node that has been offboarded via offboard_mediator.

.. _setup.bootstrap_domain:


:ref:`setup.bootstrap_domain <setup.bootstrap_domain>`
	* **Summary**: Bootstrap domain
	* **Arguments**: 
		* ``sequencers``: `Seq[com.digitalasset.canton.console.SequencerNodeReference] <../../canton/scaladoc/com/digitalasset/canton/console/SequencerNodeReference.html>`_
		* ``mediators``: `Seq[com.digitalasset.canton.console.MediatorReference] <../../canton/scaladoc/com/digitalasset/canton/console/MediatorReference.html>`_
	* **Description**: Use this command to bootstrap the domain with an initial set of external sequencer(s) and external mediator(s). Note that you only need to call this once, however it is safe to call it again if necessary in case something went wrong and this needs to be retried.

.. _setup.help:


:ref:`setup.help <setup.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _setup.init:


:ref:`setup.init <setup.init>`
	* **Summary**: Initialize domain
	* **Arguments**: 
		* ``sequencerConnection``: `com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
	* **Description**: This command triggers domain initialization and should be called once the initial topology data has been authorized and sequenced. This is called as part of the setup.bootstrap command, so you are unlikely to need to call this directly.

.. _setup.init_1:


:ref:`setup.init <setup.init_1>`
	* **Summary**: Initialize domain
	* **Arguments**: 
		* ``sequencerConnections``: `com.digitalasset.canton.sequencing.SequencerConnections <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
	* **Description**: This command triggers domain initialization and should be called once the initial topology data has been authorized and sequenced. This is called as part of the setup.bootstrap command, so you are unlikely to need to call this directly.

.. _setup.offboard_mediator:


:ref:`setup.offboard_mediator <setup.offboard_mediator>`
	* **Summary**: Offboard external Mediator node.
	* **Arguments**: 
		* ``mediatorId``: `com.digitalasset.canton.topology.MediatorId <../../canton/scaladoc/com/digitalasset/canton/topology/MediatorId.html>`_
		* ``force``: Boolean
	* **Description**: Use this command to offboard an onboarded external mediator node.     It removes the topology transaction that authorizes the given mediator ID to act as a mediator on the domain.     If you afterwards want to authorize an offboarded mediator again, use authorize_mediator.     You must apply force to offboard the last mediator of a domain.

.. _setup.onboard_mediator:


:ref:`setup.onboard_mediator <setup.onboard_mediator>`
	* **Summary**: Onboard external Mediator node.
	* **Arguments**: 
		* ``mediator``: `com.digitalasset.canton.console.MediatorReference <../../canton/scaladoc/com/digitalasset/canton/console/MediatorReference.html>`_
		* ``sequencerConnections``: `Seq[com.digitalasset.canton.console.InstanceReferenceWithSequencerConnection] <../../canton/scaladoc/com/digitalasset/canton/console/InstanceReferenceWithSequencerConnection.html>`_
	* **Description**: Use this command to onboard an external mediator node. If you're bootstrapping a domain with external sequencer(s) and this is the initial mediator, then use setup.bootstrap_domain instead. For adding additional external mediators or onboard an external mediator with a domain that runs a single embedded sequencer, use this command.Note that you only need to call this once.

.. _setup.onboard_new_sequencer:


:ref:`setup.onboard_new_sequencer <setup.onboard_new_sequencer>`
	* **Summary**: Dynamically onboard new Sequencer node.
	* **Arguments**: 
		* ``initialSequencer``: `com.digitalasset.canton.console.SequencerNodeReference <../../canton/scaladoc/com/digitalasset/canton/console/SequencerNodeReference.html>`_
		* ``newSequencer``: `com.digitalasset.canton.console.SequencerNodeReference <../../canton/scaladoc/com/digitalasset/canton/console/SequencerNodeReference.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Use this command to dynamically onboard a new sequencer node that's not part of the initial set of sequencer nodes. Do not use this for database sequencers.


Health
~~~~~~

.. _health.active_2:


:ref:`health.active <health.active_2>`
	* **Summary**: Check if the node is running and is the active instance (mediator, participant)
	* **Return type**: 
		* Boolean

.. _health.dump_3:


:ref:`health.dump <health.dump_3>`
	* **Summary**: Creates a zip file containing diagnostic information about the canton process running this node
	* **Arguments**: 
		* ``outputFile``: better.files.File
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``chunkSize``: Option[Int]
	* **Return type**: 
		* String

.. _health.help_3:


:ref:`health.help <health.help_3>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _health.initialized_2:


:ref:`health.initialized <health.initialized_2>`
	* **Summary**: Returns true if node has been initialized.
	* **Return type**: 
		* Boolean

.. _health.last_error_trace_2:


:ref:`health.last_error_trace <health.last_error_trace_2>`
	* **Summary**: Show all messages logged with the given traceId in a recent interval
	* **Arguments**: 
		* ``traceId``: String
	* **Return type**: 
		* Seq[String]
	* **Description**: Returns a list of buffered log messages associated to a given trace-id. Usually, the trace-id is taken from last_errors()

.. _health.last_errors_2:


:ref:`health.last_errors <health.last_errors_2>`
	* **Summary**: Show the last errors logged
	* **Return type**: 
		* Map[String,String]
	* **Description**: Returns a map with the trace-id as key and the most recent error messages as value. Requires that --log-last-errors is enabled (and not turned off).

.. _health.running_2:


:ref:`health.running <health.running_2>`
	* **Summary**: Check if the node is running
	* **Return type**: 
		* Boolean

.. _health.set_log_level_2:


:ref:`health.set_log_level <health.set_log_level_2>`
	* **Summary**: Change the log level of the process
	* **Arguments**: 
		* ``level``: ch.qos.logback.classic.Level
	* **Description**: If the default logback configuration is used, this will change the log level of the process.

.. _health.status_2:


:ref:`health.status <health.status_2>`
	* **Summary**: Get human (and machine) readable participant status information
	* **Return type**: 
		* com.digitalasset.canton.admin.api.client.data.NodeStatus[S]

.. _health.wait_for_identity_2:


:ref:`health.wait_for_identity <health.wait_for_identity_2>`
	* **Summary**: Wait for the node to have an identity
	* **Description**: This is specifically useful for the Domain Manager which needs its identity to be ready for bootstrapping, but for which we can't rely on wait_for_initialized() because it will be initialized only after being bootstrapped.

.. _health.wait_for_initialized_2:


:ref:`health.wait_for_initialized <health.wait_for_initialized_2>`
	* **Summary**: Wait for the node to be initialized

.. _health.wait_for_running_2:


:ref:`health.wait_for_running <health.wait_for_running_2>`
	* **Summary**: Wait for the node to be running


Database
~~~~~~~~

.. _db.help_2:


:ref:`db.help <db.help_2>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _db.migrate_2:


:ref:`db.migrate <db.migrate_2>`
	* **Summary**: Migrates the instance's database if using a database storage
	* **Description**: When instances reside on different nodes, their database migration can be run in parallel to save time. Please not that the migration commands must however must be run on each node individually, because remote migration through `participants.remote...` is not supported. 

.. _db.repair_migration_2:


:ref:`db.repair_migration <db.repair_migration_2>`
	* **Summary**: Only use when advised - repairs the database migration of the instance's database
	* **Arguments**: 
		* ``force``: Boolean
	* **Description**: In some rare cases, we change already applied database migration files in a new release and the repair command resets the checksums we use to ensure that in general already applied migration files have not been changed. You should only use `db.repair_migration` when advised and otherwise use it at your own risk - in the worst case running it may lead to data corruption when an incompatible database migration (one that should be rejected because the already applied database migration files have changed) is subsequently falsely applied. 


Sequencer Connection
~~~~~~~~~~~~~~~~~~~~

.. _sequencer_connection.get:


:ref:`sequencer_connection.get <sequencer_connection.get>`
	* **Summary**: Get Sequencer Connection
	* **Return type**: 
		* `Option[com.digitalasset.canton.sequencing.SequencerConnections] <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
	* **Description**: Use this command to get the currently configured sequencer connection details for this sequencer client. If this node has not yet been initialized, this will return None.

.. _sequencer_connection.help:


:ref:`sequencer_connection.help <sequencer_connection.help>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _sequencer_connection.modify:


:ref:`sequencer_connection.modify <sequencer_connection.modify>`
	* **Summary**: Modify Default Sequencer Connection
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.sequencing.SequencerConnection => com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
	* **Description**: Modify sequencer connection details for this sequencer client node, by passing a modifier function that operates on the existing default connection. 

.. _sequencer_connection.modify_connections:


:ref:`sequencer_connection.modify_connections <sequencer_connection.modify_connections>`
	* **Summary**: Modify Sequencer Connections
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.sequencing.SequencerConnections => com.digitalasset.canton.sequencing.SequencerConnections <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
	* **Description**: Modify sequencer connection details for this sequencer client node, by passing a modifier function that operates on the existing connection configuration. 

.. _sequencer_connection.set:


:ref:`sequencer_connection.set <sequencer_connection.set>`
	* **Summary**: Set Sequencer Connection
	* **Arguments**: 
		* ``connection``: `com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
	* **Description**: Set new sequencer connection details for this sequencer client node. This will replace any pre-configured connection details. This command will only work after the node has been initialized.

.. _sequencer_connection.set_1:


:ref:`sequencer_connection.set <sequencer_connection.set_1>`
	* **Summary**: Set Sequencer Connection
	* **Arguments**: 
		* ``connections``: `com.digitalasset.canton.sequencing.SequencerConnections <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
	* **Description**: Set new sequencer connection details for this sequencer client node. This will replace any pre-configured connection details. This command will only work after the node has been initialized.



Key Administration
~~~~~~~~~~~~~~~~~~

.. _keys.help_2:


:ref:`keys.help <keys.help_2>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String


.. _keys.public.download_2:


:ref:`keys.public.download <keys.public.download_2>`
	* **Summary**: Download public key
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString

.. _keys.public.download_to_2:


:ref:`keys.public.download_to <keys.public.download_to_2>`
	* **Summary**: Download public key and save it to a file
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``outputFile``: String
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_

.. _keys.public.help_2:


:ref:`keys.public.help <keys.public.help_2>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _keys.public.list_2:


:ref:`keys.public.list <keys.public.list_2>`
	* **Summary**: List public keys in registry
	* **Arguments**: 
		* ``filterFingerprint``: String
		* ``filterContext``: String
	* **Return type**: 
		* `Seq[com.digitalasset.canton.crypto.PublicKeyWithName] <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKeyWithName.html>`_
	* **Description**: Returns all public keys that have been added to the key registry.   Optional arguments can be used for filtering.

.. _keys.public.list_by_owner_2:


:ref:`keys.public.list_by_owner <keys.public.list_by_owner_2>`
	* **Summary**: List keys for given keyOwner.
	* **Arguments**: 
		* ``keyOwner``: `com.digitalasset.canton.topology.KeyOwner <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwner.html>`_
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListKeyOwnersResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListKeyOwnersResult.html>`_
	* **Description**: This command is a convenience wrapper for `list_key_owners`, taking an explicit keyOwner as search argument. The response includes the public keys.

.. _keys.public.list_owners_2:


:ref:`keys.public.list_owners <keys.public.list_owners_2>`
	* **Summary**: List active owners with keys for given search arguments.
	* **Arguments**: 
		* ``filterKeyOwnerUid``: String
		* ``filterKeyOwnerType``: `Option[com.digitalasset.canton.topology.KeyOwnerCode] <../../canton/scaladoc/com/digitalasset/canton/topology/KeyOwnerCode.html>`_
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListKeyOwnersResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListKeyOwnersResult.html>`_
	* **Description**: This command allows deep inspection of the topology state. The response includes the public keys. Optional filterKeyOwnerType type can be 'ParticipantId.Code' , 'MediatorId.Code','SequencerId.Code', 'DomainTopologyManagerId.Code'. 

.. _keys.public.upload_4:


:ref:`keys.public.upload <keys.public.upload_4>`
	* **Summary**: Upload public key
	* **Arguments**: 
		* ``filename``: String
		* ``name``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_

.. _keys.public.upload_5:


:ref:`keys.public.upload <keys.public.upload_5>`
	* **Summary**: Upload public key
	* **Arguments**: 
		* ``keyBytes``: com.google.protobuf.ByteString
		* ``name``: Option[String]
	* **Return type**: 
		* `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Description**: Import a public key and store it together with a name used to provide some context to that key.


.. _keys.secret.delete_2:


:ref:`keys.secret.delete <keys.secret.delete_2>`
	* **Summary**: Delete private key
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``force``: Boolean

.. _keys.secret.download_2:


:ref:`keys.secret.download <keys.secret.download_2>`
	* **Summary**: Download key pair
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_
	* **Return type**: 
		* com.google.protobuf.ByteString

.. _keys.secret.download_to_2:


:ref:`keys.secret.download_to <keys.secret.download_to_2>`
	* **Summary**: Download key pair and save it to a file
	* **Arguments**: 
		* ``fingerprint``: `com.digitalasset.canton.crypto.Fingerprint <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
		* ``outputFile``: String
		* ``protocolVersion``: `com.digitalasset.canton.version.ProtocolVersion <../../canton/scaladoc/com/digitalasset/canton/version/ProtocolVersion.html>`_

.. _keys.secret.generate_encryption_key_2:


:ref:`keys.secret.generate_encryption_key <keys.secret.generate_encryption_key_2>`
	* **Summary**: Generate new public/private key pair for encryption and store it in the vault
	* **Arguments**: 
		* ``name``: String
		* ``scheme``: `Option[com.digitalasset.canton.crypto.EncryptionKeyScheme] <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionKeyScheme.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.EncryptionPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionPublicKey.html>`_
	* **Description**:  The optional name argument allows you to store an associated string for your convenience. The scheme can be used to select a key scheme and the default scheme is used if left unspecified.

.. _keys.secret.generate_signing_key_2:


:ref:`keys.secret.generate_signing_key <keys.secret.generate_signing_key_2>`
	* **Summary**: Generate new public/private key pair for signing and store it in the vault
	* **Arguments**: 
		* ``name``: String
		* ``scheme``: `Option[com.digitalasset.canton.crypto.SigningKeyScheme] <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningKeyScheme.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.SigningPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningPublicKey.html>`_
	* **Description**:  The optional name argument allows you to store an associated string for your convenience. The scheme can be used to select a key scheme and the default scheme is used if left unspecified.

.. _keys.secret.get_wrapper_key_id_2:


:ref:`keys.secret.get_wrapper_key_id <keys.secret.get_wrapper_key_id_2>`
	* **Summary**: Get the wrapper key id that is used for the encrypted private keys store
	* **Return type**: 
		* String

.. _keys.secret.help_2:


:ref:`keys.secret.help <keys.secret.help_2>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _keys.secret.list_2:


:ref:`keys.secret.list <keys.secret.list_2>`
	* **Summary**: List keys in private vault
	* **Arguments**: 
		* ``filterFingerprint``: String
		* ``filterName``: String
		* ``purpose``: `Set[com.digitalasset.canton.crypto.KeyPurpose] <../../canton/scaladoc/com/digitalasset/canton/crypto/KeyPurpose.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.crypto.admin.grpc.PrivateKeyMetadata] <../../canton/scaladoc/com/digitalasset/canton/crypto/admin/grpc/PrivateKeyMetadata.html>`_
	* **Description**: Returns all public keys to the corresponding private keys in the key vault. Optional arguments can be used for filtering.

.. _keys.secret.register_kms_encryption_key_2:


:ref:`keys.secret.register_kms_encryption_key <keys.secret.register_kms_encryption_key_2>`
	* **Summary**: Register the specified KMS encryption key in canton storing its public information in the vault
	* **Arguments**: 
		* ``kmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.EncryptionPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/EncryptionPublicKey.html>`_
	* **Description**:  The id for the KMS encryption key. The optional name argument allows you to store an associated string for your convenience.

.. _keys.secret.register_kms_signing_key_2:


:ref:`keys.secret.register_kms_signing_key <keys.secret.register_kms_signing_key_2>`
	* **Summary**: Register the specified KMS signing key in canton storing its public information in the vault
	* **Arguments**: 
		* ``kmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.SigningPublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/SigningPublicKey.html>`_
	* **Description**:  The id for the KMS signing key. The optional name argument allows you to store an associated string for your convenience.

.. _keys.secret.rotate_kms_node_key_2:


:ref:`keys.secret.rotate_kms_node_key <keys.secret.rotate_kms_node_key_2>`
	* **Summary**: Rotate a given node's keypair with a new pre-generated KMS keypair
	* **Arguments**: 
		* ``fingerprint``: String
		* ``newKmsKeyId``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates an existing encryption or signing key stored externally in a KMS with a pre-generated    key. For a sequencer or mediator node use `rotate_kms_node_key` with a domain manager reference as an argument. The fingerprint of the key we want to rotate. The id of the new KMS key (e.g. Resource Name). An optional name for the new key.

.. _keys.secret.rotate_node_key_2:


:ref:`keys.secret.rotate_node_key <keys.secret.rotate_node_key_2>`
	* **Summary**: Rotate a node's public/private key pair
	* **Arguments**: 
		* ``fingerprint``: String
		* ``name``: String
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_
	* **Description**: Rotates an existing encryption or signing key. NOTE: A namespace root or intermediate    signing key CANNOT be rotated by this command. For a sequencer or mediator node use `rotate_kms_node_key` with    a domain manager reference as an argument. The fingerprint of the key we want to rotate. An optional name for the new key.

.. _keys.secret.rotate_node_keys_2:


:ref:`keys.secret.rotate_node_keys <keys.secret.rotate_node_keys_2>`
	* **Summary**: Rotate the node's public/private key pairs
	* **Description**:  For a participant node it rotates the signing and encryption key pair. For a domain or domain manager node it rotates the signing key pair as those nodes do not have an encryption key pair. For a sequencer or mediator node use `rotate_node_keys` with a domain manager reference as an argument. NOTE: Namespace root or intermediate signing keys are NOT rotated by this command.

.. _keys.secret.rotate_wrapper_key_2:


:ref:`keys.secret.rotate_wrapper_key <keys.secret.rotate_wrapper_key_2>`
	* **Summary**: Change the wrapper key for encrypted private keys store
	* **Arguments**: 
		* ``newWrapperKeyId``: String
	* **Description**: Change the wrapper key (e.g. AWS KMS key) being used to encrypt the private keys in the store. newWrapperKeyId: The optional new wrapper key id to be used. If the wrapper key id is empty Canton will generate a new key based on the current configuration.

.. _keys.secret.upload_4:


:ref:`keys.secret.upload <keys.secret.upload_4>`
	* **Summary**: Upload a key pair
	* **Arguments**: 
		* ``pairBytes``: com.google.protobuf.ByteString
		* ``name``: Option[String]

.. _keys.secret.upload_5:


:ref:`keys.secret.upload <keys.secret.upload_5>`
	* **Summary**: Upload (load and import) a key pair from file
	* **Arguments**: 
		* ``filename``: String
		* ``name``: Option[String]


Parties
~~~~~~~

.. _parties.help_2:


:ref:`parties.help <parties.help_2>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _parties.list_2:


:ref:`parties.list <parties.list_2>`
	* **Summary**: List active parties, their active participants, and the participants' permissions on domains.
	* **Arguments**: 
		* ``filterParty``: String
		* ``filterParticipant``: String
		* ``filterDomain``: String
		* ``asOf``: Option[java.time.Instant]
		* ``limit``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Seq[com.digitalasset.canton.admin.api.client.data.ListPartiesResult] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/ListPartiesResult.html>`_
	* **Description**: Inspect the parties known by this participant as used for synchronisation. The response is built from the timestamped topology transactions of each domain, excluding the authorized store of the given node. For each known party, the list of active participants and their permission on the domain for that party is given.    filterParty: Filter by parties starting with the given string.    filterParticipant: Filter for parties that are hosted by a participant with an id starting with the given string    filterDomain: Filter by domains whose id starts with the given string.    asOf: Optional timestamp to inspect the topology state at a given point in time.    limit: Limit on the number of parties fetched (defaults to canton.parameters.console.default-limit).    Example: participant1.parties.list(filterParty="alice")    


Service
~~~~~~~

.. _service.get_dynamic_domain_parameters_1:


:ref:`service.get_dynamic_domain_parameters <service.get_dynamic_domain_parameters_1>`
	* **Summary**: Get the Dynamic Domain Parameters configured for the domain
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_

.. _service.get_max_rate_per_participant_1:


:ref:`service.get_max_rate_per_participant <service.get_max_rate_per_participant_1>`
	* **Summary**: Get the max rate per participant
	* **Return type**: 
		* `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
	* **Description**: Depending on the protocol version used on the domain, the value will be     read either from the static domain parameters or the dynamic ones.

.. _service.get_max_request_size_1:


:ref:`service.get_max_request_size <service.get_max_request_size_1>`
	* **Summary**: Get the max request size
	* **Return type**: 
		* `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
	* **Description**: Depending on the protocol version used on the domain, the value will be     read either from the static domain parameters or the dynamic ones.     This value is not necessarily the one used by the sequencer node because it requires a restart     of the server to be taken into account.

.. _service.get_mediator_deduplication_timeout_1:


:ref:`service.get_mediator_deduplication_timeout <service.get_mediator_deduplication_timeout_1>`
	* **Summary**: Get the mediator deduplication timeout
	* **Return type**: 
		* `com.digitalasset.canton.config.NonNegativeFiniteDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeFiniteDuration.html>`_
	* **Description**: The method will fail, if the domain does not support the mediatorDeduplicationTimeout.

.. _service.get_reconciliation_interval_1:


:ref:`service.get_reconciliation_interval <service.get_reconciliation_interval_1>`
	* **Summary**: Get the reconciliation interval configured for the domain
	* **Return type**: 
		* `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: Depending on the protocol version used on the domain, the value will be     read either from the static domain parameters or the dynamic ones.

.. _service.get_static_domain_parameters_1:


:ref:`service.get_static_domain_parameters <service.get_static_domain_parameters_1>`
	* **Summary**: Get the Static Domain Parameters configured for the domain
	* **Return type**: 
		* `com.digitalasset.canton.admin.api.client.data.StaticDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/StaticDomainParameters.html>`_

.. _service.help_1:


:ref:`service.help <service.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _service.list_accepted_agreements_1:


:ref:`service.list_accepted_agreements <service.list_accepted_agreements_1>`
	* **Summary**: List the accepted service agreements
	* **Return type**: 
		* `Seq[com.digitalasset.canton.domain.service.ServiceAgreementAcceptance] <../../canton/scaladoc/com/digitalasset/canton/domain/service/ServiceAgreementAcceptance.html>`_

.. _service.set_commitments_catch_up_config_1:


:ref:`service.set_commitments_catch_up_config <service.set_commitments_catch_up_config_1>`
	* **Summary**: Update the ACS commitments catch up config for the domain
	* **Arguments**: 
		* ``config``: `com.digitalasset.canton.protocol.CatchUpConfig <../../canton/scaladoc/com/digitalasset/canton/protocol/CatchUpConfig.html>`_
	* **Description**: The method will fail if the domain does not support the ``catchUpConfig`` parameter           (i.e., if the domain is running on protocol version lower than `6`)

.. _service.set_dynamic_domain_parameters_1:


:ref:`service.set_dynamic_domain_parameters <service.set_dynamic_domain_parameters_1>`
	* **Summary**: Set the Dynamic Domain Parameters configured for the domain
	* **Arguments**: 
		* ``dynamicDomainParameters``: `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_
		* ``force``: Boolean
	* **Description**: force: Enable potentially dangerous changes. Required to increase ``ledgerTimeRecordTimeTolerance``. Use ``set_ledger_time_record_time_tolerance`` to securely increase ``ledgerTimeRecordTimeTolerance``.

.. _service.set_ledger_time_record_time_tolerance_1:


:ref:`service.set_ledger_time_record_time_tolerance <service.set_ledger_time_record_time_tolerance_1>`
	* **Summary**: Update the `ledgerTimeRecordTimeTolerance` in the dynamic domain parameters.
	* **Arguments**: 
		* ``newLedgerTimeRecordTimeTolerance``: `com.digitalasset.canton.config.NonNegativeFiniteDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeFiniteDuration.html>`_
		* ``force``: Boolean
	* **Description**: If it would be insecure to perform the change immediately, the command will block and wait until it is secure to perform the change. The command will block for at most twice of ``newLedgerTimeRecordTimeTolerance``. If the domain does not support ``mediatorDeduplicationTimeout``, the method will update ``ledgerTimeRecordTimeTolerance`` immediately without blocking. The method will fail if ``mediatorDeduplicationTimeout`` is less than twice of ``newLedgerTimeRecordTimeTolerance``. Do not modify domain parameters concurrently while running this command, because the command may override concurrent changes. force: update ``ledgerTimeRecordTimeTolerance`` immediately without blocking. This is safe to do during domain bootstrapping and in test environments, but should not be done in operational production systems..

.. _service.set_max_inbound_message_size_1:


:ref:`service.set_max_inbound_message_size <service.set_max_inbound_message_size_1>`
	* **Summary**: Try to update the max rate per participant for the domain
	* **Arguments**: 
		* ``maxRequestSize``: `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
		* ``force``: Boolean
	* **Description**: If the max request size is dynamic, update the value.             The update won't have any effect unless the sequencer server is restarted.   If the max request size is not dynamic (i.e., if the domain is running   on protocol version lower than `4`), then it will throw an error.   

.. _service.set_max_rate_per_participant_1:


:ref:`service.set_max_rate_per_participant <service.set_max_rate_per_participant_1>`
	* **Summary**: Try to update the max rate per participant for the domain
	* **Arguments**: 
		* ``maxRatePerParticipant``: `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
	* **Description**: If the max rate per participant is dynamic, update the value.     If the max rate per participant is not dynamic (i.e., if the domain is running     on protocol version lower than `4`), then it will throw an error.     

.. _service.set_max_request_size_1:


:ref:`service.set_max_request_size <service.set_max_request_size_1>`
	* **Summary**: Try to update the max rate per participant for the domain
	* **Arguments**: 
		* ``maxRequestSize``: `com.digitalasset.canton.config.RequireTypes.NonNegativeInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$NonNegativeInt$.html>`_
		* ``force``: Boolean
	* **Description**: If the max request size is dynamic, update the value.             The update won't have any effect unless the sequencer server is restarted.   If the max request size is not dynamic (i.e., if the domain is running   on protocol version lower than `4`), then it will throw an error.   

.. _service.set_mediator_deduplication_timeout_1:


:ref:`service.set_mediator_deduplication_timeout <service.set_mediator_deduplication_timeout_1>`
	* **Summary**: Update the mediator deduplication timeout
	* **Arguments**: 
		* ``newMediatorDeduplicationTimeout``: `com.digitalasset.canton.config.NonNegativeFiniteDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeFiniteDuration.html>`_
	* **Description**: The method will fail: - if the domain does not support the ``mediatorDeduplicationTimeout`` parameter, - if the new value of ``mediatorDeduplicationTimeout`` is less than twice the value of ``ledgerTimeRecordTimeTolerance.``

.. _service.set_reconciliation_interval_1:


:ref:`service.set_reconciliation_interval <service.set_reconciliation_interval_1>`
	* **Summary**: Try to update the reconciliation interval for the domain
	* **Arguments**: 
		* ``newReconciliationInterval``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: If the reconciliation interval is dynamic, update the value.     If the reconciliation interval is not dynamic (i.e., if the domain is running     on protocol version lower than `4`), then it will throw an error.     

.. _service.update_dynamic_domain_parameters_1:


:ref:`service.update_dynamic_domain_parameters <service.update_dynamic_domain_parameters_1>`
	* **Summary**: Update the Dynamic Domain Parameters for the domain
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters => com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_
		* ``force``: Boolean
	* **Description**: force: Enable potentially dangerous changes. Required to increase ``ledgerTimeRecordTimeTolerance``. Use ``set_ledger_time_record_time_tolerance_securely`` to securely increase ``ledgerTimeRecordTimeTolerance``.

.. _service.update_dynamic_parameters_1:


:ref:`service.update_dynamic_parameters <service.update_dynamic_parameters_1>`
	* **Summary**: Update the Dynamic Domain Parameters for the domain
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters => com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/DynamicDomainParameters.html>`_
		* ``force``: Boolean
	* **Description**: force: Enable potentially dangerous changes. Required to increase ``ledgerTimeRecordTimeTolerance``. Use ``set_ledger_time_record_time_tolerance_securely`` to securely increase ``ledgerTimeRecordTimeTolerance``.


Topology Administration
~~~~~~~~~~~~~~~~~~~~~~~

Same as :ref:`Domain Topology Administration <domain-topology-admin>`.

Sequencer Administration Commands
---------------------------------

.. _clear_cache_4:


:ref:`clear_cache (Testing) <clear_cache_4>`
	* **Summary**: Clear locally cached variables
	* **Description**: Some commands cache values on the client side. Use this command to explicitly clear the caches of these values.

.. _config_4:


:ref:`config <config_4>`
	* **Summary**: Returns the sequencer configuration
	* **Return type**: 
		* `com.digitalasset.canton.domain.sequencing.config.SequencerNodeConfig <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/config/SequencerNodeConfig.html>`_

.. _help_5:


:ref:`help <help_5>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _id_4:


:ref:`id <id_4>`
	* **Summary**: Yields the globally unique id of this sequencer. Throws an exception, if the id has not yet been allocated (e.g., the sequencer has not yet been started).
	* **Return type**: 
		* `com.digitalasset.canton.topology.SequencerId <../../canton/scaladoc/com/digitalasset/canton/topology/SequencerId.html>`_

.. _is_initialized_4:


:ref:`is_initialized <is_initialized_4>`
	* **Summary**: Check if the local instance is running and is fully initialized
	* **Return type**: 
		* Boolean

.. _is_running_4:


:ref:`is_running <is_running_4>`
	* **Summary**: Check if the local instance is running
	* **Return type**: 
		* Boolean

.. _start_4:


:ref:`start <start_4>`
	* **Summary**: Start the instance

.. _stop_4:


:ref:`stop <stop_4>`
	* **Summary**: Stop the instance


Sequencer
~~~~~~~~~

.. _sequencer.disable_member_1:


:ref:`sequencer.disable_member <sequencer.disable_member_1>`
	* **Summary**: Disable the provided member at the Sequencer that will allow any unread data for them to be removed
	* **Arguments**: 
		* ``member``: `com.digitalasset.canton.topology.Member <../../canton/scaladoc/com/digitalasset/canton/topology/Member.html>`_
	* **Description**: This will prevent any client for the given member to reconnect the Sequencer and allow any unread/unacknowledged data they have to be removed. This should only be used if the domain operation is confident the member will never need to reconnect as there is no way to re-enable the member. To view members using the sequencer run `sequencer.status()`."

.. _sequencer.help_1:


:ref:`sequencer.help <sequencer.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _sequencer.pruning.clear_schedule_1:


:ref:`sequencer.pruning.clear_schedule <sequencer.pruning.clear_schedule_1>`
	* **Summary**: Deactivate automatic pruning.

.. _sequencer.pruning.force_prune_1:


:ref:`sequencer.pruning.force_prune <sequencer.pruning.force_prune_1>`
	* **Summary**: Force remove data from the Sequencer including data that may have not been read by offline clients
	* **Arguments**: 
		* ``dryRun``: Boolean
	* **Return type**: 
		* String
	* **Description**: Will force pruning up until the default retention period by potentially disabling clients that have not yet read data we would like to remove. Disabling these clients will prevent them from ever reconnecting to the Domain so should only be used if the Domain operator is confident they can be permanently ignored. Run with `dryRun = true` to review a description of which clients will be disabled first. Run with `dryRun = false` to disable these clients and perform a forced pruning. 

.. _sequencer.pruning.force_prune_at_1:


:ref:`sequencer.pruning.force_prune_at <sequencer.pruning.force_prune_at_1>`
	* **Summary**: Force removing data from the Sequencer including data that may have not been read by offline clients up until the specified time
	* **Arguments**: 
		* ``timestamp``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
		* ``dryRun``: Boolean
	* **Return type**: 
		* String
	* **Description**: Similar to the above `force_prune` command but allows specifying the exact time at which to prune

.. _sequencer.pruning.force_prune_with_retention_period_1:


:ref:`sequencer.pruning.force_prune_with_retention_period <sequencer.pruning.force_prune_with_retention_period_1>`
	* **Summary**: Force removing data from the Sequencer including data that may have not been read by offline clients up until a custom retention period
	* **Arguments**: 
		* ``retentionPeriod``: scala.concurrent.duration.FiniteDuration
		* ``dryRun``: Boolean
	* **Return type**: 
		* String
	* **Description**: Similar to the above `force_prune` command but allows specifying a custom retention period

.. _sequencer.pruning.get_schedule_1:


:ref:`sequencer.pruning.get_schedule <sequencer.pruning.get_schedule_1>`
	* **Summary**: Inspect the automatic pruning schedule.
	* **Return type**: 
		* `Option[com.digitalasset.canton.admin.api.client.data.PruningSchedule] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PruningSchedule.html>`_
	* **Description**: The schedule consists of a "cron" expression and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period. Returns `None` if no schedule has been configured via `set_schedule` or if `clear_schedule` has been invoked.   

.. _sequencer.pruning.help_1:


:ref:`sequencer.pruning.help <sequencer.pruning.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _sequencer.pruning.locate_pruning_timestamp_1:


:ref:`sequencer.pruning.locate_pruning_timestamp <sequencer.pruning.locate_pruning_timestamp_1>`
	* **Summary**: Obtain a timestamp at or near the beginning of sequencer state
	* **Arguments**: 
		* ``index``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Option[com.digitalasset.canton.data.CantonTimestamp] <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Description**: This command provides insight into the current state of sequencer pruning when called with the default value of `index` 1. When pruning the sequencer manually via `prune_at` and with the intent to prune in batches, specify a value such as 1000 to obtain a pruning timestamp that corresponds to the "end" of the batch.

.. _sequencer.pruning.prune_1:


:ref:`sequencer.pruning.prune <sequencer.pruning.prune_1>`
	* **Summary**: Remove unnecessary data from the Sequencer up until the default retention point
	* **Return type**: 
		* String
	* **Description**: Removes unnecessary data from the Sequencer that is earlier than the default retention period. The default retention period is set in the configuration of the canton processing running this command under `parameters.retention-period-defaults.sequencer`. This pruning command requires that data is read and acknowledged by clients before considering it safe to remove. If no data is being removed it could indicate that clients are not reading or acknowledging data in a timely fashion (typically due to nodes going offline for long periods). You have the option of disabling the members running on these nodes to allow removal of this data, however this will mean that they will be unable to reconnect to the domain in the future. To do this run `force_prune(dryRun = true)` to return a description of which members would be disabled in order to prune the Sequencer. If you are happy to disable the described clients then run `force_prune(dryRun = false)` to permanently remove their unread data. Once offline clients have been disabled you can continue to run `prune` normally. 

.. _sequencer.pruning.prune_at_1:


:ref:`sequencer.pruning.prune_at <sequencer.pruning.prune_at_1>`
	* **Summary**: Remove data that has been read up until the specified time
	* **Arguments**: 
		* ``timestamp``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Return type**: 
		* String
	* **Description**: Similar to the above `prune` command but allows specifying the exact time at which to prune. The command will fail if a client has not yet read and acknowledged some data up to the specified time.

.. _sequencer.pruning.prune_with_retention_period_1:


:ref:`sequencer.pruning.prune_with_retention_period <sequencer.pruning.prune_with_retention_period_1>`
	* **Summary**: Remove data that has been read up until a custom retention period
	* **Arguments**: 
		* ``retentionPeriod``: scala.concurrent.duration.FiniteDuration
	* **Return type**: 
		* String
	* **Description**: Similar to the above `prune` command but allows specifying a custom retention period

.. _sequencer.pruning.set_cron_1:


:ref:`sequencer.pruning.set_cron <sequencer.pruning.set_cron_1>`
	* **Summary**: Modify the cron used by automatic pruning.
	* **Arguments**: 
		* ``cron``: String
	* **Description**: The schedule is specified in cron format and refers to pruning start times in the GMT time zone. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _sequencer.pruning.set_max_duration_1:


:ref:`sequencer.pruning.set_max_duration <sequencer.pruning.set_max_duration_1>`
	* **Summary**: Modify the maximum duration used by automatic pruning.
	* **Arguments**: 
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `maxDuration` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _sequencer.pruning.set_retention_1:


:ref:`sequencer.pruning.set_retention <sequencer.pruning.set_retention_1>`
	* **Summary**: Update the pruning retention used by automatic pruning.
	* **Arguments**: 
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `retention` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this update, pruning is actively running, a best effort is made to pause pruning and restart with the newly specified retention. This allows for the case that the new retention mandates retaining more data than previously.   

.. _sequencer.pruning.set_schedule_1:


:ref:`sequencer.pruning.set_schedule <sequencer.pruning.set_schedule_1>`
	* **Summary**: Activate automatic pruning according to the specified schedule.
	* **Arguments**: 
		* ``cron``: String
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The schedule is specified in cron format and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period.   

.. _sequencer.pruning.status_1:


:ref:`sequencer.pruning.status <sequencer.pruning.status_1>`
	* **Summary**: Status of the sequencer and its connected clients
	* **Return type**: 
		* `com.digitalasset.canton.domain.sequencing.sequencer.SequencerPruningStatus <../../canton/scaladoc/com/digitalasset/canton/domain/sequencing/sequencer/SequencerPruningStatus.html>`_
	* **Description**: Provides a detailed breakdown of information required for pruning: - the current time according to this sequencer instance - domain members that the sequencer supports - for each member when they were registered and whether they are enabled - a list of clients for each member, their last acknowledgement, and whether they are enabled 


Health
~~~~~~

.. _health.active_4:


:ref:`health.active <health.active_4>`
	* **Summary**: Check if the node is running and is the active instance (mediator, participant)
	* **Return type**: 
		* Boolean

.. _health.dump_5:


:ref:`health.dump <health.dump_5>`
	* **Summary**: Creates a zip file containing diagnostic information about the canton process running this node
	* **Arguments**: 
		* ``outputFile``: better.files.File
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``chunkSize``: Option[Int]
	* **Return type**: 
		* String

.. _health.has_identity_1:


:ref:`health.has_identity <health.has_identity_1>`
	* **Summary**: Returns true if the node has an identity
	* **Return type**: 
		* Boolean

.. _health.help_5:


:ref:`health.help <health.help_5>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _health.initialized_4:


:ref:`health.initialized <health.initialized_4>`
	* **Summary**: Returns true if node has been initialized.
	* **Return type**: 
		* Boolean

.. _health.last_error_trace_4:


:ref:`health.last_error_trace <health.last_error_trace_4>`
	* **Summary**: Show all messages logged with the given traceId in a recent interval
	* **Arguments**: 
		* ``traceId``: String
	* **Return type**: 
		* Seq[String]
	* **Description**: Returns a list of buffered log messages associated to a given trace-id. Usually, the trace-id is taken from last_errors()

.. _health.last_errors_4:


:ref:`health.last_errors <health.last_errors_4>`
	* **Summary**: Show the last errors logged
	* **Return type**: 
		* Map[String,String]
	* **Description**: Returns a map with the trace-id as key and the most recent error messages as value. Requires that --log-last-errors is enabled (and not turned off).

.. _health.running_4:


:ref:`health.running <health.running_4>`
	* **Summary**: Check if the node is running
	* **Return type**: 
		* Boolean

.. _health.set_log_level_4:


:ref:`health.set_log_level <health.set_log_level_4>`
	* **Summary**: Change the log level of the process
	* **Arguments**: 
		* ``level``: ch.qos.logback.classic.Level
	* **Description**: If the default logback configuration is used, this will change the log level of the process.

.. _health.status_4:


:ref:`health.status <health.status_4>`
	* **Summary**: Get human (and machine) readable status info
	* **Return type**: 
		* com.digitalasset.canton.admin.api.client.data.NodeStatus[S]

.. _health.wait_for_identity_4:


:ref:`health.wait_for_identity <health.wait_for_identity_4>`
	* **Summary**: Wait for the node to have an identity
	* **Description**: This is specifically useful for the Domain Manager which needs its identity to be ready for bootstrapping, but for which we can't rely on wait_for_initialized() because it will be initialized only after being bootstrapped.

.. _health.wait_for_initialized_4:


:ref:`health.wait_for_initialized <health.wait_for_initialized_4>`
	* **Summary**: Wait for the node to be initialized

.. _health.wait_for_running_4:


:ref:`health.wait_for_running <health.wait_for_running_4>`
	* **Summary**: Wait for the node to be running


Database
~~~~~~~~

.. _db.help_4:


:ref:`db.help <db.help_4>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _db.migrate_4:


:ref:`db.migrate <db.migrate_4>`
	* **Summary**: Migrates the instance's database if using a database storage
	* **Description**: When instances reside on different nodes, their database migration can be run in parallel to save time. Please not that the migration commands must however must be run on each node individually, because remote migration through `participants.remote...` is not supported. 

.. _db.repair_migration_4:


:ref:`db.repair_migration <db.repair_migration_4>`
	* **Summary**: Only use when advised - repairs the database migration of the instance's database
	* **Arguments**: 
		* ``force``: Boolean
	* **Description**: In some rare cases, we change already applied database migration files in a new release and the repair command resets the checksums we use to ensure that in general already applied migration files have not been changed. You should only use `db.repair_migration` when advised and otherwise use it at your own risk - in the worst case running it may lead to data corruption when an incompatible database migration (one that should be rejected because the already applied database migration files have changed) is subsequently falsely applied. 


Mediator Administration Commands
--------------------------------

.. _clear_cache_3:


:ref:`clear_cache (Testing) <clear_cache_3>`
	* **Summary**: Clear locally cached variables
	* **Description**: Some commands cache values on the client side. Use this command to explicitly clear the caches of these values.

.. _config_3:


:ref:`config <config_3>`
	* **Summary**: Returns the mediator configuration
	* **Return type**: 
		* `com.digitalasset.canton.domain.mediator.MediatorNodeConfig <../../canton/scaladoc/com/digitalasset/canton/domain/mediator/MediatorNodeConfig.html>`_

.. _help_4:


:ref:`help <help_4>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _id_3:


:ref:`id <id_3>`
	* **Summary**: Yields the mediator id of this mediator. Throws an exception, if the id has not yet been allocated (e.g., the mediator has not yet been initialised).
	* **Return type**: 
		* `com.digitalasset.canton.topology.MediatorId <../../canton/scaladoc/com/digitalasset/canton/topology/MediatorId.html>`_

.. _is_initialized_3:


:ref:`is_initialized <is_initialized_3>`
	* **Summary**: Check if the local instance is running and is fully initialized
	* **Return type**: 
		* Boolean

.. _is_running_3:


:ref:`is_running <is_running_3>`
	* **Summary**: Check if the local instance is running
	* **Return type**: 
		* Boolean

.. _start_3:


:ref:`start <start_3>`
	* **Summary**: Start the instance

.. _stop_3:


:ref:`stop <stop_3>`
	* **Summary**: Stop the instance


Mediator
~~~~~~~~

.. _mediator.clear_schedule_1:


:ref:`mediator.clear_schedule <mediator.clear_schedule_1>`
	* **Summary**: Deactivate automatic pruning.

.. _mediator.get_schedule_1:


:ref:`mediator.get_schedule <mediator.get_schedule_1>`
	* **Summary**: Inspect the automatic pruning schedule.
	* **Return type**: 
		* `Option[com.digitalasset.canton.admin.api.client.data.PruningSchedule] <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/PruningSchedule.html>`_
	* **Description**: The schedule consists of a "cron" expression and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period. Returns `None` if no schedule has been configured via `set_schedule` or if `clear_schedule` has been invoked.   

.. _mediator.help_1:


:ref:`mediator.help <mediator.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _mediator.initialize:


:ref:`mediator.initialize <mediator.initialize>`
	* **Summary**: Initialize a mediator
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``mediatorId``: `com.digitalasset.canton.topology.MediatorId <../../canton/scaladoc/com/digitalasset/canton/topology/MediatorId.html>`_
		* ``domainParameters``: `com.digitalasset.canton.admin.api.client.data.StaticDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/StaticDomainParameters.html>`_
		* ``sequencerConnection``: `com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
		* ``topologySnapshot``: Option[com.digitalasset.canton.topology.store.StoredTopologyTransactions[com.digitalasset.canton.topology.transaction.TopologyChangeOp.Positive]]
		* ``signingKeyFingerprint``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_

.. _mediator.initialize_1:


:ref:`mediator.initialize <mediator.initialize_1>`
	* **Summary**: Initialize a mediator
	* **Arguments**: 
		* ``domainId``: `com.digitalasset.canton.topology.DomainId <../../canton/scaladoc/com/digitalasset/canton/topology/DomainId.html>`_
		* ``mediatorId``: `com.digitalasset.canton.topology.MediatorId <../../canton/scaladoc/com/digitalasset/canton/topology/MediatorId.html>`_
		* ``domainParameters``: `com.digitalasset.canton.admin.api.client.data.StaticDomainParameters <../../canton/scaladoc/com/digitalasset/canton/admin/api/client/data/StaticDomainParameters.html>`_
		* ``sequencerConnections``: `com.digitalasset.canton.sequencing.SequencerConnections <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
		* ``topologySnapshot``: Option[com.digitalasset.canton.topology.store.StoredTopologyTransactions[com.digitalasset.canton.topology.transaction.TopologyChangeOp.Positive]]
		* ``signingKeyFingerprint``: `Option[com.digitalasset.canton.crypto.Fingerprint] <../../canton/scaladoc/com/digitalasset/canton/crypto/Fingerprint.html>`_
	* **Return type**: 
		* `com.digitalasset.canton.crypto.PublicKey <../../canton/scaladoc/com/digitalasset/canton/crypto/PublicKey.html>`_

.. _mediator.locate_pruning_timestamp_1:


:ref:`mediator.locate_pruning_timestamp <mediator.locate_pruning_timestamp_1>`
	* **Summary**: Obtain a timestamp at or near the beginning of mediator state
	* **Arguments**: 
		* ``index``: `com.digitalasset.canton.config.RequireTypes.PositiveInt <../../canton/scaladoc/com/digitalasset/canton/config/RequireTypes$$PositiveInt$.html>`_
	* **Return type**: 
		* `Option[com.digitalasset.canton.data.CantonTimestamp] <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_
	* **Description**: This command provides insight into the current state of mediator pruning when called with the default value of `index` 1. When pruning the mediator manually via `prune_at` and with the intent to prune in batches, specify a value such as 1000 to obtain a pruning timestamp that corresponds to the "end" of the batch.

.. _mediator.prune_1:


:ref:`mediator.prune <mediator.prune_1>`
	* **Summary**: Prune the mediator of unnecessary data while keeping data for the default retention period
	* **Description**: Removes unnecessary data from the Mediator that is earlier than the default retention period. The default retention period is set in the configuration of the canton node running this command under `parameters.retention-period-defaults.mediator`.

.. _mediator.prune_at_1:


:ref:`mediator.prune_at <mediator.prune_at_1>`
	* **Summary**: Prune the mediator of unnecessary data up to and including the given timestamp
	* **Arguments**: 
		* ``timestamp``: `com.digitalasset.canton.data.CantonTimestamp <../../canton/scaladoc/com/digitalasset/canton/data/CantonTimestamp.html>`_

.. _mediator.prune_with_retention_period_1:


:ref:`mediator.prune_with_retention_period <mediator.prune_with_retention_period_1>`
	* **Summary**: Prune the mediator of unnecessary data while keeping data for the provided retention period
	* **Arguments**: 
		* ``retentionPeriod``: scala.concurrent.duration.FiniteDuration

.. _mediator.set_cron_1:


:ref:`mediator.set_cron <mediator.set_cron_1>`
	* **Summary**: Modify the cron used by automatic pruning.
	* **Arguments**: 
		* ``cron``: String
	* **Description**: The schedule is specified in cron format and refers to pruning start times in the GMT time zone. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _mediator.set_max_duration_1:


:ref:`mediator.set_max_duration <mediator.set_max_duration_1>`
	* **Summary**: Modify the maximum duration used by automatic pruning.
	* **Arguments**: 
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `maxDuration` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this modification, pruning is actively running, a best effort is made to pause pruning and restart according to the new schedule. This allows for the case that the new schedule no longer allows pruning at the current time.   

.. _mediator.set_retention_1:


:ref:`mediator.set_retention <mediator.set_retention_1>`
	* **Summary**: Update the pruning retention used by automatic pruning.
	* **Arguments**: 
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The `retention` is specified as a positive duration and has at most per-second granularity. This call returns an error if no schedule has been configured via `set_schedule` or if automatic pruning has been disabled via `clear_schedule`. Additionally if at the time of this update, pruning is actively running, a best effort is made to pause pruning and restart with the newly specified retention. This allows for the case that the new retention mandates retaining more data than previously.   

.. _mediator.set_schedule_1:


:ref:`mediator.set_schedule <mediator.set_schedule_1>`
	* **Summary**: Activate automatic pruning according to the specified schedule.
	* **Arguments**: 
		* ``cron``: String
		* ``maxDuration``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
		* ``retention``: `com.digitalasset.canton.config.PositiveDurationSeconds <../../canton/scaladoc/com/digitalasset/canton/config/PositiveDurationSeconds.html>`_
	* **Description**: The schedule is specified in cron format and "max_duration" and "retention" durations. The cron string indicates the points in time at which pruning should begin in the GMT time zone, and the maximum duration indicates how long from the start time pruning is allowed to run as long as pruning has not finished pruning up to the specified retention period.   


Health
~~~~~~

.. _health.active_3:


:ref:`health.active <health.active_3>`
	* **Summary**: Check if the node is running and is the active instance (mediator, participant)
	* **Return type**: 
		* Boolean

.. _health.dump_4:


:ref:`health.dump <health.dump_4>`
	* **Summary**: Creates a zip file containing diagnostic information about the canton process running this node
	* **Arguments**: 
		* ``outputFile``: better.files.File
		* ``timeout``: `com.digitalasset.canton.config.NonNegativeDuration <../../canton/scaladoc/com/digitalasset/canton/config/NonNegativeDuration.html>`_
		* ``chunkSize``: Option[Int]
	* **Return type**: 
		* String

.. _health.has_identity:


:ref:`health.has_identity <health.has_identity>`
	* **Summary**: Returns true if the node has an identity
	* **Return type**: 
		* Boolean

.. _health.help_4:


:ref:`health.help <health.help_4>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _health.initialized_3:


:ref:`health.initialized <health.initialized_3>`
	* **Summary**: Returns true if node has been initialized.
	* **Return type**: 
		* Boolean

.. _health.last_error_trace_3:


:ref:`health.last_error_trace <health.last_error_trace_3>`
	* **Summary**: Show all messages logged with the given traceId in a recent interval
	* **Arguments**: 
		* ``traceId``: String
	* **Return type**: 
		* Seq[String]
	* **Description**: Returns a list of buffered log messages associated to a given trace-id. Usually, the trace-id is taken from last_errors()

.. _health.last_errors_3:


:ref:`health.last_errors <health.last_errors_3>`
	* **Summary**: Show the last errors logged
	* **Return type**: 
		* Map[String,String]
	* **Description**: Returns a map with the trace-id as key and the most recent error messages as value. Requires that --log-last-errors is enabled (and not turned off).

.. _health.running_3:


:ref:`health.running <health.running_3>`
	* **Summary**: Check if the node is running
	* **Return type**: 
		* Boolean

.. _health.set_log_level_3:


:ref:`health.set_log_level <health.set_log_level_3>`
	* **Summary**: Change the log level of the process
	* **Arguments**: 
		* ``level``: ch.qos.logback.classic.Level
	* **Description**: If the default logback configuration is used, this will change the log level of the process.

.. _health.status_3:


:ref:`health.status <health.status_3>`
	* **Summary**: Get human (and machine) readable status info
	* **Return type**: 
		* com.digitalasset.canton.admin.api.client.data.NodeStatus[S]

.. _health.wait_for_identity_3:


:ref:`health.wait_for_identity <health.wait_for_identity_3>`
	* **Summary**: Wait for the node to have an identity
	* **Description**: This is specifically useful for the Domain Manager which needs its identity to be ready for bootstrapping, but for which we can't rely on wait_for_initialized() because it will be initialized only after being bootstrapped.

.. _health.wait_for_initialized_3:


:ref:`health.wait_for_initialized <health.wait_for_initialized_3>`
	* **Summary**: Wait for the node to be initialized

.. _health.wait_for_running_3:


:ref:`health.wait_for_running <health.wait_for_running_3>`
	* **Summary**: Wait for the node to be running


Database
~~~~~~~~

.. _db.help_3:


:ref:`db.help <db.help_3>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _db.migrate_3:


:ref:`db.migrate <db.migrate_3>`
	* **Summary**: Migrates the instance's database if using a database storage
	* **Description**: When instances reside on different nodes, their database migration can be run in parallel to save time. Please not that the migration commands must however must be run on each node individually, because remote migration through `participants.remote...` is not supported. 

.. _db.repair_migration_3:


:ref:`db.repair_migration <db.repair_migration_3>`
	* **Summary**: Only use when advised - repairs the database migration of the instance's database
	* **Arguments**: 
		* ``force``: Boolean
	* **Description**: In some rare cases, we change already applied database migration files in a new release and the repair command resets the checksums we use to ensure that in general already applied migration files have not been changed. You should only use `db.repair_migration` when advised and otherwise use it at your own risk - in the worst case running it may lead to data corruption when an incompatible database migration (one that should be rejected because the already applied database migration files have changed) is subsequently falsely applied. 


Sequencer Connection
~~~~~~~~~~~~~~~~~~~~

.. _sequencer_connection.get_1:


:ref:`sequencer_connection.get <sequencer_connection.get_1>`
	* **Summary**: Get Sequencer Connection
	* **Return type**: 
		* `Option[com.digitalasset.canton.sequencing.SequencerConnections] <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
	* **Description**: Use this command to get the currently configured sequencer connection details for this sequencer client. If this node has not yet been initialized, this will return None.

.. _sequencer_connection.help_1:


:ref:`sequencer_connection.help <sequencer_connection.help_1>`
	* **Summary**: Help for specific commands (use help() or help("method") for more information)
	* **Arguments**: 
		* ``methodName``: String

.. _sequencer_connection.modify_1:


:ref:`sequencer_connection.modify <sequencer_connection.modify_1>`
	* **Summary**: Modify Default Sequencer Connection
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.sequencing.SequencerConnection => com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
	* **Description**: Modify sequencer connection details for this sequencer client node, by passing a modifier function that operates on the existing default connection. 

.. _sequencer_connection.modify_connections_1:


:ref:`sequencer_connection.modify_connections <sequencer_connection.modify_connections_1>`
	* **Summary**: Modify Sequencer Connections
	* **Arguments**: 
		* ``modifier``: `com.digitalasset.canton.sequencing.SequencerConnections => com.digitalasset.canton.sequencing.SequencerConnections <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
	* **Description**: Modify sequencer connection details for this sequencer client node, by passing a modifier function that operates on the existing connection configuration. 

.. _sequencer_connection.set_2:


:ref:`sequencer_connection.set <sequencer_connection.set_2>`
	* **Summary**: Set Sequencer Connection
	* **Arguments**: 
		* ``connection``: `com.digitalasset.canton.sequencing.SequencerConnection <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnection.html>`_
	* **Description**: Set new sequencer connection details for this sequencer client node. This will replace any pre-configured connection details. This command will only work after the node has been initialized.

.. _sequencer_connection.set_3:


:ref:`sequencer_connection.set <sequencer_connection.set_3>`
	* **Summary**: Set Sequencer Connection
	* **Arguments**: 
		* ``connections``: `com.digitalasset.canton.sequencing.SequencerConnections <../../canton/scaladoc/com/digitalasset/canton/sequencing/SequencerConnections.html>`_
	* **Description**: Set new sequencer connection details for this sequencer client node. This will replace any pre-configured connection details. This command will only work after the node has been initialized.

