..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _administration_apis:

Canton Administration APIs
==========================

Canton provides a :ref:`console <canton_console>` as a builtin mode for administrative interaction. However, under the
hood, all administrative console actions are effected using the administration gRPC API. Therefore, it is also
possible to write your own administration application and connect it to the administration gRPC endpoints of both
types of nodes, participant and domain.

There are three categories of admin-apis: participant, domain and identity.

Participant Admin APIs
----------------------
The participant exposes the following admin-api services:

Package Service
~~~~~~~~~~~~~~~
The package service is used to manage the installed packages.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.participant.admin.v0;
    
    import "google/protobuf/empty.proto";
    
    service PackageService {
    
        // List all Daml-LF archives on the participant node - return their hashes
        rpc ListPackages(ListPackagesRequest) returns (ListPackagesResponse);
    
        // Lists all the modules in package on the participant node
        rpc ListPackageContents (ListPackageContentsRequest) returns (ListPackageContentsResponse);
    
        // List all DARs on the participant node - return their hashes and filenames
        rpc ListDars(ListDarsRequest) returns (ListDarsResponse);
    
        // List content of a Dar
        rpc ListDarContents(ListDarContentsRequest) returns (ListDarContentsResponse);
    
        // Upload a DAR file and all packages inside to the participant node
        rpc UploadDar (UploadDarRequest) returns (UploadDarResponse);
    
        // Remove a package that is not vetted
        rpc RemovePackage (RemovePackageRequest) returns (RemovePackageResponse);
    
        // Remove a DAR that is not needed
        rpc RemoveDar (RemoveDarRequest) returns (RemoveDarResponse);
    
        // Obtain a DAR file by hash -- for inspection & download
        rpc GetDar(GetDarRequest) returns (GetDarResponse);
    
        // Share a DAR with another participant
        rpc Share(ShareRequest) returns (google.protobuf.Empty);
    
        // List requests this participant has made to share DARs with another participant
        rpc ListShareRequests(google.protobuf.Empty) returns (ListShareRequestsResponse);
    
        // List offers to share a DAR that this participant has received
        rpc ListShareOffers(google.protobuf.Empty) returns (ListShareOffersResponse);
    
        // Accept a DAR sharing offer (this will install the DAR into the participant)
        rpc AcceptShareOffer(AcceptShareOfferRequest) returns (google.protobuf.Empty);
    
        // Reject a DAR sharing offer
        rpc RejectShareOffer(RejectShareOfferRequest) returns (google.protobuf.Empty);
    
        // Add party to our DAR distribution whitelist
        rpc WhitelistAdd(WhitelistChangeRequest) returns (google.protobuf.Empty);
    
        // Remove party from our DAR distribution whitelist
        rpc WhitelistRemove(WhitelistChangeRequest) returns (google.protobuf.Empty);
    
        // List all parties currently on the whitelist
        rpc WhitelistList(google.protobuf.Empty) returns (WhitelistListResponse);
    }
    
    message ListPackageContentsRequest {
        string package_id = 1;
    }
    
    message ListPackageContentsResponse {
        repeated ModuleDescription modules = 1;
    }
    
    message ListDarContentsRequest {
        string dar_id = 1;
    }
    
    message ListDarContentsResponse {
        string description = 1;
        string main = 2;
        repeated string packages = 3;
        repeated string dependencies = 4;
    }
    
    message RemovePackageRequest {
        string package_id = 1;
        bool force = 2;
    }
    
    message RemovePackageResponse {
        google.protobuf.Empty success = 1;
    }
    
    message RemoveDarRequest {
        string dar_hash = 1;
    }
    
    message RemoveDarResponse {
        google.protobuf.Empty success = 1;
    }
    
    message ModuleDescription {
        string name = 1;
    }
    
    message ListPackagesRequest {
        int32 limit = 1;
    }
    
    message ListPackagesResponse {
        repeated PackageDescription package_descriptions = 1;
    }
    
    message ListDarsRequest {
        int32 limit = 1;
    }
    
    message ListDarsResponse {
        repeated DarDescription dars = 1;
    }
    
    message DarDescription {
        string hash = 1;
        string name = 2;
    }
    
    message UploadDarRequest {
        bytes data = 1;
        string filename = 2;
        // if set to true, we'll register the vetting topology transactions with the idm
        bool vet_all_packages = 3;
        // if set to true, we'll wait until the vetting transaction has been observed by this participant on all connected domains
        bool synchronize_vetting = 4;
    }
    
    message UploadDarResponse {
        oneof value {
            Success success = 1;
            Failure failure = 2;
        }
        message Success {
            string hash = 1;
        }
        message Failure {
            string reason = 1;
        }
    }
    
    message GetDarRequest {
        string hash = 1;
    }
    
    message GetDarResponse {
        bytes data = 1;
        string name = 2;
    }
    
    message PackageDescription {
        string package_id = 1;
        string source_description = 3;
    }
    
    message ShareRequest {
        string dar_hash = 1;
        string recipient_id = 2;
    }
    
    message ListShareRequestsResponse {
        repeated Item share_requests = 1;
    
        message Item {
            string id = 1;
            string dar_hash = 2;
            string recipient_id = 3;
            string name = 4;
        }
    }
    
    message ListShareOffersResponse {
        repeated Item share_offers = 1;
    
        message Item {
            string id = 1;
            string dar_hash = 2;
            string owner_id = 3;
            string name = 4;
        }
    }
    
    message AcceptShareOfferRequest {
        string id = 1;
    }
    
    message RejectShareOfferRequest {
        string id = 1;
        // informational message explaining why we decided to reject the DAR
        // can be empty
        string reason = 2;
    }
    
    message WhitelistChangeRequest {
        string party_id = 1;
    }
    
    message WhitelistListResponse {
        repeated string party_ids = 1;
    }


Participant Status Service
~~~~~~~~~~~~~~~~~~~~~~~~~~
.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.health.admin.v0;
    import "google/protobuf/empty.proto";
    import "google/protobuf/duration.proto";
    import "google/protobuf/wrappers.proto";
    
    service StatusService {
        rpc Status(google.protobuf.Empty) returns (NodeStatus);
        // Streams back a zip file as byte chunks, containing a health dump of the full canton process (including other nodes)
        rpc HealthDump(HealthDumpRequest) returns (stream HealthDumpChunk);
    }
    
    message TopologyQueueStatus {
        // how many topology changes are currently queued at the manager
        uint32 manager = 1;
        // how many topology changes are currently queued at the dispatcher
        uint32 dispatcher = 2;
        // how many topology changes are currently waiting to become effective (across all connected domains in the case of participants)
        uint32 clients = 3;
    }
    
    message NodeStatus {
        message Status {
            string id = 1;
            google.protobuf.Duration uptime = 2;
            map<string, int32> ports = 3;
            bytes extra = 4; // contains extra information depending on the node type
            bool active = 5; // Indicate if the node is active, usually true unless it's a replicated node that is passive
            TopologyQueueStatus topology_queues = 6; // indicates the state of the topology queues (manager / dispatcher only where they exist)
        }
    
        message NotInitialized {
            bool active = 1; // Indicate if the node is active, usually true unless it's a replicated node that is passive
        }
    
        oneof response {
            NotInitialized not_initialized = 1; // node is running but has not been initialized yet
            Status success = 2; // successful response from a running and initialized node
        }
    }
    
    message HealthDumpRequest {
        // Size of the byte chunks to stream back.
        // Defaults to 2MB (half of the default gRPC max message size)
        google.protobuf.UInt32Value chunkSize = 1;
    }
    
    message HealthDumpChunk {
        bytes chunk = 1; // A chunk of of the health dump file
    }
    
    
    
    // domain node specific extra status info
    message DomainStatusInfo {
        repeated string connected_participants = 1;
        // optional - only set if a sequencer is being run by the domain
        SequencerHealthStatus sequencer = 2;
    }
    
    // participant node specific extra status info
    message ParticipantStatusInfo {
        message ConnectedDomain {
            string domain = 1;
            bool healthy = 2;
        }
        repeated ConnectedDomain connected_domains = 1;
        // Indicate if the participant node is active
        // True if the participant node is replicated and is the active replica, or true if not replicated
        bool active = 2;
    }
    
    message SequencerNodeStatus {
        repeated string connected_participants = 1;
        // required - status of the sequencer component it is running
        SequencerHealthStatus sequencer = 2;
        string domain_id = 3;
    }
    
    // status of the sequencer component
    message SequencerHealthStatus {
        // is the sequencer component active - can vary by implementation for what this means
        bool active = 1;
        // optionally set details on how sequencer is healthy/unhealthy
        google.protobuf.StringValue details = 2;
    }
    
    message MediatorNodeStatus {
        string domain_id = 1;
    }

Ping Pong Service
~~~~~~~~~~~~~~~~~
Canton uses a default simple ping-pong workflow to smoke-test a deployment.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.participant.admin.v0;
    
    service PingService {
        rpc ping(PingRequest) returns (PingResponse);
    }
    
    message PingRequest {
    
        repeated string target_parties = 1;
        repeated string validators = 2;
        uint64 timeout_milliseconds = 3;
        uint64 levels = 4;
        uint64 grace_period_milliseconds = 5;
        string workflow_id = 6; // optional
        string id = 7; // optional UUID to be used for ping test
    
    }
    
    message PingSuccess {
        uint64 ping_time = 1;
        string responder = 2;
    }
    
    message PingFailure {
    }
    
    message PingResponse {
        oneof response {
            PingSuccess success = 1;
            PingFailure failure = 2;
        }
    
    }


Domain Connectivity Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.participant.admin.v0;
    
    import "google/protobuf/duration.proto";
    import "com/digitalasset/canton/time/admin/v0/time_tracker_config.proto";
    import "com/digitalasset/canton/protocol/v0/sequencing.proto";
    
    /**
     * Domain connectivity service for adding and connecting to domains
     *
     * The domain connectivity service allows to register to new domains and control the
     * participants domain connections.
     */
    service DomainConnectivityService {
        // reconnect to domains
        rpc ReconnectDomains(ReconnectDomainsRequest) returns (ReconnectDomainsResponse);
        // configure a new domain connection
        rpc RegisterDomain(RegisterDomainRequest) returns (RegisterDomainResponse);
        // reconfigure a domain connection
        rpc ModifyDomain(ModifyDomainRequest) returns (ModifyDomainResponse);
        // connect to a configured domain
        rpc ConnectDomain(ConnectDomainRequest) returns (ConnectDomainResponse);
        // disconnect from a configured domain
        rpc DisconnectDomain(DisconnectDomainRequest) returns (DisconnectDomainResponse);
        // list connected domains
        rpc ListConnectedDomains(ListConnectedDomainsRequest) returns (ListConnectedDomainsResponse);
        // list configured domains
        rpc ListConfiguredDomains(ListConfiguredDomainsRequest) returns (ListConfiguredDomainsResponse);
        // Get the service agreement for the domain
        rpc GetAgreement(GetAgreementRequest) returns (GetAgreementResponse);
        // Accept the agreement of the domain
        rpc AcceptAgreement(AcceptAgreementRequest) returns (AcceptAgreementResponse);
        // Get the domain id of the given domain alias
        rpc GetDomainId(GetDomainIdRequest) returns (GetDomainIdResponse);
    }
    
    message DomainConnectionConfig {
        // participant local identifier of the target domain
        string domain_alias = 1;
        // connection information to sequencer
        com.digitalasset.canton.protocol.v0.SequencerConnection sequencerConnection = 2;
        // if false, then domain needs to be manually connected to (default false)
        bool manual_connect = 3;
        // optional domainId (if TLS isn't to be trusted)
        string domain_id = 4;
        // optional. Influences whether the participant submits to this domain, if several domains are eligible
        int32 priority = 5;
        // initial delay before an attempt to reconnect to the sequencer
        google.protobuf.Duration initialRetryDelay = 6;
        // maximum delay before an attempt to reconnect to the sequencer
        google.protobuf.Duration maxRetryDelay = 7;
        // configuration for how time is tracked and requested on this domain
        com.digitalasset.canton.time.admin.v0.DomainTimeTrackerConfig timeTracker = 8;
    }
    
    message ReconnectDomainsRequest {
        /* if set to true, the connection attempt will succeed even if one of the connection attempts failed */
        bool ignore_failures = 1;
    
    }
    message ReconnectDomainsResponse {
    
    }
    
    /** Register and optionally auto-connect to a new domain */
    message RegisterDomainRequest {
        DomainConnectionConfig add = 1;
    }
    
    message RegisterDomainResponse {
    
    }
    
    message ModifyDomainRequest {
        DomainConnectionConfig modify = 1;
    }
    
    message ModifyDomainResponse {
    
    }
    
    message ListConfiguredDomainsRequest {
    
    }
    
    message ListConfiguredDomainsResponse {
        message Result {
            DomainConnectionConfig config = 1;
            bool connected = 2;
        }
        repeated Result results = 1;
    }
    
    message ConnectDomainRequest {
        string domain_alias = 1;
        /* if retry is set to true, we will keep on retrying if the domain is unavailable */
        bool retry = 2;
    }
    
    message ConnectDomainResponse {
        /* true if the domain is connected, false if the domain is offline, exception on any other error */
        bool connected_successfully = 1;
    }
    
    message DisconnectDomainRequest {
        string domain_alias = 1;
    }
    
    message DisconnectDomainResponse {
    }
    
    message ListConnectedDomainsRequest {
    }
    
    message ListConnectedDomainsResponse {
        message Result {
            string domain_alias = 1;
            string domain_id = 2;
            bool healthy = 3;
        }
        repeated Result connected_domains = 1;
    }
    
    message GetAgreementRequest {
        string domain_alias = 1;
    }
    
    message GetAgreementResponse {
        string domain_id = 1;
        Agreement agreement = 2;
        bool accepted = 3;
    }
    
    message Agreement {
        string id = 1;
        string text = 2;
    }
    
    message AcceptAgreementRequest {
        string domain_alias = 1;
        string agreement_id = 2;
    }
    
    message AcceptAgreementResponse {
    }
    
    message GetDomainIdRequest {
        string domain_alias = 1;
    }
    
    message GetDomainIdResponse {
        string domain_id = 2;
    }


Party Name Management Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.participant.admin.v0;
    
    /**
      * Local participant service allowing to set the display name for a party
      *
      * The display name is a local property to the participant. The participant is encouraged to perform
      * a Daml based KYC process and add some automation which will update the display names based
      * on the desired update rules.
      *
      * As such, this function here just offers the bare functionality to perform this.
      */
    service PartyNameManagementService {
        rpc setPartyDisplayName(SetPartyDisplayNameRequest) returns (SetPartyDisplayNameResponse);
    }
    
    message SetPartyDisplayNameRequest {
        string party_id = 1;
        string display_name = 2;
    }
    
    message SetPartyDisplayNameResponse {
    
    }

Inspection Service
~~~~~~~~~~~~~~~~~~
.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.participant.admin.v0;
    
    import "google/protobuf/timestamp.proto";
    
    /**
     * Inspection Service
     *
     * Supports inspecting the Participant for details about its ledger.
     * This contains only a subset of the ParticipantInspection commands that can run over the admin-api instead of requiring
     * direct access to the participant node instance.
     */
    service InspectionService {
        // Lookup the domain where a contract is currently active.
        // Supports querying many contracts at once.
        rpc LookupContractDomain(LookupContractDomain.Request) returns (LookupContractDomain.Response);
        // Lookup the domain that the transaction was committed over. Can fail with NOT_FOUND if no domain was found.
        rpc LookupTransactionDomain(LookupTransactionDomain.Request) returns (LookupTransactionDomain.Response);
        // Look up the ledger offset corresponding to the timestamp, specifically the largest offset such that no later
        // offset corresponds to a later timestamp than the specified one.
        rpc LookupOffsetByTime(LookupOffsetByTime.Request) returns (LookupOffsetByTime.Response);
        // Look up the ledger offset by an index, e.g. 1 returns the first offset, 2 the second, etc.
        rpc LookupOffsetByIndex(LookupOffsetByIndex.Request) returns (LookupOffsetByIndex.Response);
    }
    
    message LookupContractDomain {
        message Request {
            // set of contract ids to lookup their active domain aliases.
            repeated string contract_id = 1;
        }
    
        message Response {
            // map of contract id to domain alias.
            // if a request contract id from the request is missing from this map it indicates that the contract was not
            // active on any current domain.
            map<string, string> results = 1;
        }
    }
    
    message LookupTransactionDomain {
        message Request {
            // the transaction to look up
            string transaction_id = 1;
        }
    
        message Response {
            // the domain that the transaction was committed over
            string domain_id = 1;
        }
    }
    
    message LookupOffsetByTime {
        message Request {
            // the timestamp to look up the offset for
            google.protobuf.Timestamp timestamp = 1;
        }
    
        message Response {
            // the absolute offset as a string corresponding to the specified timestamp.
            // empty string if no such offset exists.
            string offset = 1;
        }
    }
    
    message LookupOffsetByIndex {
        message Request {
            // the index to look up the offset for, needs to be 1 or larger
            int64 index = 1;
        }
    
        message Response {
            // the absolute offset as a string corresponding to the specified index.
            // empty string if no such offset exists.
            string offset = 1;
        }
    }


Transfer Service
~~~~~~~~~~~~~~~~
.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.participant.admin.v0;
    
    import "google/protobuf/timestamp.proto";
    import "com/digitalasset/canton/protocol/v0/participant_transfer.proto";
    
    // Supports transferring contracts from one domain to another
    service TransferService {
        // transfer out a contract
        rpc TransferOut (AdminTransferOutRequest) returns (AdminTransferOutResponse);
    
        // transfer-in a contract
        rpc TransferIn (AdminTransferInRequest) returns (AdminTransferInResponse);
    
        // return the in-flight transfers on a given participant for a given target domain
        rpc TransferSearch (AdminTransferSearchQuery) returns (AdminTransferSearchResponse);
    }
    
    message AdminTransferOutRequest {
        string submitting_party = 1;
        string contract_id = 2;
        string origin_domain = 3;
        string target_domain = 4;
    }
    
    message AdminTransferOutResponse {
        com.digitalasset.canton.protocol.v0.TransferId transfer_id = 1;
    }
    
    message AdminTransferInRequest {
        string submitting_party_id = 1;
        string target_domain = 2;
        com.digitalasset.canton.protocol.v0.TransferId transfer_id = 3;
    }
    
    message AdminTransferInResponse {
    
    }
    
    message AdminTransferSearchQuery {
        string search_domain = 1;
        string filter_origin_domain = 2; // exact match if non-empty
        google.protobuf.Timestamp filter_timestamp = 3; // optional; exact match if set
        string filter_submitting_party = 4;
        int64 limit = 5;
    }
    
    message AdminTransferSearchResponse {
        repeated TransferSearchResult results = 1;
    
        message TransferSearchResult {
            string contract_id = 1;
            com.digitalasset.canton.protocol.v0.TransferId transfer_id = 2;
            string origin_domain = 3;
            string target_domain = 4;
            string submitting_party = 5;
            bool ready_for_transfer_in = 6;
        }
    }


Pruning Service
~~~~~~~~~~~~~~~~
.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.participant.admin.v0;
    
    import "com/digitalasset/canton/pruning/admin/v0/pruning.proto";
    
    // Canton-internal pruning service that prunes only canton state, but leaves the ledger-api
    // state unpruned.
    service PruningService {
    
        // Prune the participant specifying the offset before and at which ledger transactions
        // should be removed. Only returns when the potentially long-running prune request ends
        // successfully or with one of the following errors:
        // - ``INVALID_ARGUMENT``: if the payload, particularly the offset is malformed or missing
        // - ``INTERNAL``: if the participant has encountered a failure and has potentially
        //   applied pruning partially. Such cases warrant verifying the participant health before
        //   retrying the prune with the same (or a larger, valid) offset. Successful retries
        //   after such errors ensure that different components reach a consistent pruning state.
        // - ``FAILED_PRECONDITION``: if the participant is not yet able to prune at the specified
        //   offset or if pruning is invoked on a participant running the Community Edition.
        rpc Prune (PruneRequest) returns (PruneResponse);
    
        // Enable automatic pruning using the specified schedule parameters
        // The following errors may occur on the SetSchedule or Update commands:
        // - ``INVALID_ARGUMENT``: if a parameter is missing or an invalid cron expression
        //   or duration.
        // - ``FAILED_PRECONDITION``: if automatic background pruning has not been enabled
        //   or if invoked on a participant running the Community Edition.
        rpc SetSchedule(com.digitalasset.canton.pruning.admin.v0.SetSchedule.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetSchedule.Response);
    
        // Modify individual pruning schedule parameters.
        // - ``INVALID_ARGUMENT``: if the payload is malformed or no schedule is configured
        rpc SetCron(com.digitalasset.canton.pruning.admin.v0.SetCron.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetCron.Response);
        rpc SetMaxDuration(com.digitalasset.canton.pruning.admin.v0.SetMaxDuration.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetMaxDuration.Response);
        rpc SetRetention(com.digitalasset.canton.pruning.admin.v0.SetRetention.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetRetention.Response);
    
        // Disable automatic pruning and remove the persisted schedule configuration.
        rpc ClearSchedule(com.digitalasset.canton.pruning.admin.v0.ClearSchedule.Request) returns (com.digitalasset.canton.pruning.admin.v0.ClearSchedule.Response);
    
        // Retrieve the automatic pruning configuration.
        rpc GetSchedule(com.digitalasset.canton.pruning.admin.v0.GetSchedule.Request) returns (com.digitalasset.canton.pruning.admin.v0.GetSchedule.Response);
    
    }
    
    message PruneRequest {
        // Inclusive offset up to which the ledger is to be pruned.
        string prune_up_to = 1;
    }
    
    message PruneResponse {
        // Empty for now, but may contain fields in the future
    }


Domain Admin APIs
-----------------
The domain exposes the following admin-api services:

Domain Status Service
~~~~~~~~~~~~~~~~~~~~~

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.health.admin.v0;
    import "google/protobuf/empty.proto";
    import "google/protobuf/duration.proto";
    import "google/protobuf/wrappers.proto";
    
    service StatusService {
        rpc Status(google.protobuf.Empty) returns (NodeStatus);
        // Streams back a zip file as byte chunks, containing a health dump of the full canton process (including other nodes)
        rpc HealthDump(HealthDumpRequest) returns (stream HealthDumpChunk);
    }
    
    message TopologyQueueStatus {
        // how many topology changes are currently queued at the manager
        uint32 manager = 1;
        // how many topology changes are currently queued at the dispatcher
        uint32 dispatcher = 2;
        // how many topology changes are currently waiting to become effective (across all connected domains in the case of participants)
        uint32 clients = 3;
    }
    
    message NodeStatus {
        message Status {
            string id = 1;
            google.protobuf.Duration uptime = 2;
            map<string, int32> ports = 3;
            bytes extra = 4; // contains extra information depending on the node type
            bool active = 5; // Indicate if the node is active, usually true unless it's a replicated node that is passive
            TopologyQueueStatus topology_queues = 6; // indicates the state of the topology queues (manager / dispatcher only where they exist)
        }
    
        message NotInitialized {
            bool active = 1; // Indicate if the node is active, usually true unless it's a replicated node that is passive
        }
    
        oneof response {
            NotInitialized not_initialized = 1; // node is running but has not been initialized yet
            Status success = 2; // successful response from a running and initialized node
        }
    }
    
    message HealthDumpRequest {
        // Size of the byte chunks to stream back.
        // Defaults to 2MB (half of the default gRPC max message size)
        google.protobuf.UInt32Value chunkSize = 1;
    }
    
    message HealthDumpChunk {
        bytes chunk = 1; // A chunk of of the health dump file
    }
    
    
    
    // domain node specific extra status info
    message DomainStatusInfo {
        repeated string connected_participants = 1;
        // optional - only set if a sequencer is being run by the domain
        SequencerHealthStatus sequencer = 2;
    }
    
    // participant node specific extra status info
    message ParticipantStatusInfo {
        message ConnectedDomain {
            string domain = 1;
            bool healthy = 2;
        }
        repeated ConnectedDomain connected_domains = 1;
        // Indicate if the participant node is active
        // True if the participant node is replicated and is the active replica, or true if not replicated
        bool active = 2;
    }
    
    message SequencerNodeStatus {
        repeated string connected_participants = 1;
        // required - status of the sequencer component it is running
        SequencerHealthStatus sequencer = 2;
        string domain_id = 3;
    }
    
    // status of the sequencer component
    message SequencerHealthStatus {
        // is the sequencer component active - can vary by implementation for what this means
        bool active = 1;
        // optionally set details on how sequencer is healthy/unhealthy
        google.protobuf.StringValue details = 2;
    }
    
    message MediatorNodeStatus {
        string domain_id = 1;
    }

Identity Admin APIs
-------------------
Both, domain and participant nodes expose the following services:

Vault Management Service
~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.crypto.admin.v0;
    
    import "com/digitalasset/canton/crypto/v0/crypto.proto";
    import "google/protobuf/empty.proto";
    
    /**
     * Vault service providing programmatic access to locally stored keys and certificates
     *
     * We have two key-stores: a private key store where we are storing our pairs of
     * public and private keys and a public key store where we are storing other
     * public keys that we learned.
     *
     * We learn public key stores in different ways: either by importing them or
     * by picking them up from internal sources (such as identity management updates).
     *
     * The only purpose of the public key store (where we import foreign keys) is convenience for
     * identity management such that when we add identity management transactions, we can refer to
     * fingerprints in commands while building them rather than having to attach public-key files.
     *
     * In addition, we also provide access to the locally stored certificates which are used
     * either by the HTTP/1.1 sequencer client or for legal identity claims.
     */
    service VaultService {
    
        /**
         * List public keys according to request filter for which we have a private key in our key vault.
         *
         * The request includes a filter for fingerprints which can be used for lookups.
         *
         * @param ListMyKeysRequest: request with optional fingerprint filter
         * @return: all serialized keys and metadata that have the fingerprint filter as a substring in their fingerprint
         */
        rpc ListMyKeys(ListKeysRequest) returns (ListMyKeysResponse);
    
        /**
         * Generates a new public / private key pair for signing.
         *
         * Stores the private key in the vault, and returns the public key
         */
        rpc GenerateSigningKey(GenerateSigningKeyRequest) returns (GenerateSigningKeyResponse);
    
        /**
         * Generates a new public / private key pair for hybrid encryption.
         *
         * Stores the private key in the vault, and returns the public key
         */
        rpc GenerateEncryptionKey(GenerateEncryptionKeyRequest) returns (GenerateEncryptionKeyResponse);
    
        /**
         * Import a public key into the registry in order to provide that Fingerprint -> PublicKey lookups
         *
         * @param: ImportPublicKeyRequest serialized public key to be imported
         * @return: fingerprint and serialized public key of imported public key
         */
        rpc ImportPublicKey(ImportPublicKeyRequest) returns (ImportPublicKeyResponse);
    
        /**
         * Lists all public keys matching the supplied filter which are internally cached
         *
         * Any public key returned here can be referenced in topology transaction building
         * by fingerprint.
         */
        rpc ListPublicKeys(ListKeysRequest) returns (ListKeysResponse);
    
        /**
         * Import a X509 certificate into the local vault.
         */
        rpc ImportCertificate(ImportCertificateRequest) returns (ImportCertificateResponse);
    
        /**
         * Create a new, self-signed certificate with CN=unique_identifier
         */
        rpc GenerateCertificate(GenerateCertificateRequest) returns (GenerateCertificateResponse);
    
        /**
         * List certificates stored in the local vault
         */
        rpc ListCertificates(ListCertificateRequest) returns (ListCertificateResponse);
    
        /**
         * Changes the wrapper key that is used to encrypt private keys when stored
         */
        rpc RotateWrapperKey(RotateWrapperKeyRequest) returns (google.protobuf.Empty);
    
    
        rpc GetWrapperKeyId(GetWrapperKeyIdRequest) returns (GetWrapperKeyIdResponse);
    }
    
    message GenerateCertificateRequest {
        // unique identifier to be used for CN
        string unique_identifier = 1;
        // the private key fingerprint to use for this certificate
        string certificate_key = 2;
        // optional additional X500 names
        string additional_subject = 3;
        // the additional subject names to be added to this certificate
        repeated string subject_alternative_names = 4;
    }
    
    message GenerateCertificateResponse {
        // the certificate in PEM format
        string x509_cert = 1;
    }
    
    message ListCertificateRequest {
        string filterUid = 1;
    }
    
    message ListCertificateResponse {
        message Result {
            string x509_cert = 1;
        }
        repeated Result results = 1;
    }
    
    message ImportCertificateRequest {
        // X509 certificate as PEM
        string x509_cert = 1;
    }
    
    message ImportCertificateResponse {
        string certificate_id = 1;
    }
    
    
    message ImportPublicKeyRequest {
        // import a crypto.PublicKey protobuf serialized key
        bytes public_key = 1;
        // an optional name that should be stored along side the key
        string name = 2;
    }
    
    message ImportPublicKeyResponse {
        // fingerprint of imported key
        string fingerprint = 1;
    }
    
    message ListKeysRequest {
        // the substring that needs to match a given fingerprint
        string filter_fingerprint = 1;
        // the substring to filter the name
        string filter_name = 2;
        // filter on public key purpose
        repeated com.digitalasset.canton.crypto.v0.KeyPurpose filter_purpose = 3;
    }
    
    message PrivateKeyMetadata {
        com.digitalasset.canton.crypto.v0.PublicKeyWithName public_key_with_name = 1;
    
        // If set the private key is stored encrypted by the wrapper key
        string wrapper_key_id = 2;
    }
    
    
    message ListMyKeysResponse {
        repeated PrivateKeyMetadata private_keys_metadata = 1;
    }
    
    message ListKeysResponse {
        repeated com.digitalasset.canton.crypto.v0.PublicKeyWithName public_keys = 1;
    }
    
    message GenerateSigningKeyRequest {
        com.digitalasset.canton.crypto.v0.SigningKeyScheme key_scheme = 1;
    
        // optional descriptive name for the key
        string name = 2;
    }
    
    message GenerateSigningKeyResponse {
        com.digitalasset.canton.crypto.v0.SigningPublicKey public_key = 1;
    }
    
    message GenerateEncryptionKeyRequest {
        com.digitalasset.canton.crypto.v0.EncryptionKeyScheme key_scheme = 1;
    
        // optional descriptive name for the key
        string name = 2;
    }
    
    message GenerateEncryptionKeyResponse {
        com.digitalasset.canton.crypto.v0.EncryptionPublicKey public_key = 1;
    }
    
    message RotateWrapperKeyRequest {
        string new_wrapper_key_id = 1;
    }
    
    message GetWrapperKeyIdRequest {
    }
    
    message GetWrapperKeyIdResponse {
        string wrapper_key_id = 1;
    }


Initialization Service
~~~~~~~~~~~~~~~~~~~~~~
The one time initialization service, used to setup the identity of a node.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.topology.admin.v0;
    
    import "google/protobuf/empty.proto";
    import "google/protobuf/timestamp.proto";
    
    /**
     * The node initialization service
     */
    service InitializationService {
    
        /**
         * Initialize the node with the unique identifier (can and must be done once)
         *
         * When a domain or participant instance starts for the first time, we need to bind it
         * to a globally unique stable identifier before we can continue with the
         * initialization procedure.
         *
         * This method is only used once during initialization.
         */
        rpc InitId(InitIdRequest) returns (InitIdResponse);
    
    
        /**
         * Returns the id of the node (or empty if not initialized)
         */
        rpc GetId(google.protobuf.Empty) returns (GetIdResponse);
    
    
        /**
         * Returns the current time of the node (used for testing with static time)
         */
        rpc CurrentTime(google.protobuf.Empty) returns (google.protobuf.Timestamp);
    
    }
    
    message InitIdRequest {
        string identifier = 1;
        string fingerprint = 2;
        // optional - instance id, if supplied value is empty then one will be generated
        string instance = 3;
    }
    
    message InitIdResponse {
        string unique_identifier = 1;
        string instance = 2;
    }
    
    message GetIdResponse {
        bool initialized = 1;
        string unique_identifier = 2;
        string instance = 3;
    }

Topology Aggregation Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Aggregated view of the sequenced domain topology state.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.topology.admin.v0;
    
    import "google/protobuf/timestamp.proto";
    import "com/digitalasset/canton/crypto/v0/crypto.proto";
    import "com/digitalasset/canton/protocol/v0/topology.proto";
    
    /**
     * Topology information aggregation service
     *
     * This service allows deep inspection into the aggregated topology state.
     * The services runs both on the domain and on the participant and uses the same
     * data. The service provides GRPC access to the information aggregated by the identity providing
     * service client.
     */
    service TopologyAggregationService {
    
        /**
          * Obtain information about a certain set of active parties matching a given filter criterion.
          *
          * The request allows to filter per (domain, party, asOf) where the domain and party argument are
          * used in order to filter the result list using the `startsWith` method on the respective resulting string.
          *
          * As such, if you just need to do a lookup, then define a precise filter. Given the uniqueness of the
          * identifiers (and the fact that the identifiers contain key fingerprints), we should only ever get a single
          * result back if we are doing a precise lookup.
          *
          * The response is a sequence of tuples (party, domain, participant, privilege, trust-level).
          * The response is restricted to active parties and their active participants.
          */
        rpc ListParties (ListPartiesRequest) returns (ListPartiesResponse);
    
        /**
          * Obtain key owner information matching a given filter criterion.
          *
          * Key owners in the system are different types of entities: Participant, Mediator, Domain Topology Manager and
          * Sequencer. The present method allows to define a filter to search for a key owner
          * using filters on (asOf, domain, ownerType, owner)
          *
          * The response is a sequence of (domain, ownerType, owner, keys) where keys is a sequence of
          * (fingerprint, bytes, key purpose). As such, we can use this method to export currently used signing or encryption
          * public keys.
          *
          * This method is quite general, as depending on the arguments, very different results can be obtained.
          *
          * Using OwnerType = 'Participant' allows to query for all participants.
          * Using OwnerType = 'Sequencer' allows to query for all sequencers defined.
          */
        rpc ListKeyOwners (ListKeyOwnersRequest) returns (ListKeyOwnersResponse);
    }
    
    message ListPartiesRequest {
        google.protobuf.Timestamp as_of = 1;
        int32 limit = 2;
        string filter_domain = 3;
        string filter_party = 4;
        string filter_participant = 5;
    }
    
    message ListPartiesResponse {
        message Result {
            string party = 1;
            message ParticipantDomains {
                message DomainPermissions {
                    string domain = 1;
                    com.digitalasset.canton.protocol.v0.ParticipantPermission permission = 2;
                }
                string participant = 1;
                /**
                  * permissions of this participant for this party on a per domain basis
                  *
                  * for records that only exist in the authorized store, this list will be empty.
                  */
                repeated DomainPermissions domains = 2;
            }
            repeated ParticipantDomains participants = 2;
        }
        repeated Result results = 2;
    }
    
    message ListKeyOwnersRequest {
        google.protobuf.Timestamp as_of = 1;
        int32 limit = 2;
        string filter_domain = 3;
        string filter_key_owner_type = 4;
        string filter_key_owner_uid = 5;
    }
    
    message ListKeyOwnersResponse {
        message Result {
            string domain = 1;
            string key_owner = 2;
            repeated com.digitalasset.canton.crypto.v0.SigningPublicKey signing_keys = 3;
            repeated com.digitalasset.canton.crypto.v0.EncryptionPublicKey encryption_keys = 4;
        }
        repeated Result results = 1;
    }


Topology Manager Read Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Raw access to the underlying topology transactions.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.topology.admin.v0;
    
    import "com/digitalasset/canton/crypto/v0/crypto.proto";
    import "com/digitalasset/canton/protocol/v0/topology.proto";
    import "com/digitalasset/canton/topology/admin/v0/topology_ext.proto";
    import "com/digitalasset/canton/protocol/v0/sequencing.proto";
    import "com/digitalasset/canton/protocol/v1/sequencing.proto";
    import "google/protobuf/timestamp.proto";
    import "google/protobuf/empty.proto";
    import "google/protobuf/wrappers.proto";
    
    // domain + idm + participant
    service TopologyManagerReadService {
    
        rpc ListAvailableStores(ListAvailableStoresRequest) returns (ListAvailableStoresResult);
        rpc ListPartyToParticipant(ListPartyToParticipantRequest) returns (ListPartyToParticipantResult);
        rpc ListOwnerToKeyMapping(ListOwnerToKeyMappingRequest) returns (ListOwnerToKeyMappingResult);
        rpc ListNamespaceDelegation(ListNamespaceDelegationRequest) returns (ListNamespaceDelegationResult);
        rpc ListIdentifierDelegation(ListIdentifierDelegationRequest) returns (ListIdentifierDelegationResult);
        rpc ListSignedLegalIdentityClaim(ListSignedLegalIdentityClaimRequest) returns (ListSignedLegalIdentityClaimResult);
        rpc ListParticipantDomainState(ListParticipantDomainStateRequest) returns (ListParticipantDomainStateResult);
        rpc ListMediatorDomainState(ListMediatorDomainStateRequest) returns (ListMediatorDomainStateResult);
        rpc ListVettedPackages(ListVettedPackagesRequest) returns (ListVettedPackagesResult);
        rpc ListDomainParametersChanges(ListDomainParametersChangesRequest) returns (ListDomainParametersChangesResult);
        rpc ListAll(ListAllRequest) returns (ListAllResponse);
    
    
    }
    
    message ListNamespaceDelegationRequest {
        BaseQuery base_query = 1;
        string filter_namespace = 2;
    }
    
    message ListNamespaceDelegationResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.NamespaceDelegation item = 2;
            string target_key_fingerprint = 3;
        }
        repeated Result results = 1;
    }
    
    message ListIdentifierDelegationRequest {
        BaseQuery base_query = 1;
        string filter_uid = 2;
    }
    
    message ListIdentifierDelegationResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.IdentifierDelegation item = 2;
            string target_key_fingerprint = 3;
        }
        repeated Result results = 1;
    }
    
    message BaseQuery {
        string filter_store = 1;
        bool use_state_store = 2;
        com.digitalasset.canton.protocol.v0.TopologyChangeOp operation = 3;
        /** if true, then we'll filter the results according to above defined operation */
        bool filter_operation = 4;
        message TimeRange {
            google.protobuf.Timestamp from = 2;
            google.protobuf.Timestamp until = 3;
        }
        oneof time_query {
            google.protobuf.Timestamp snapshot = 5;
            google.protobuf.Empty head_state = 6;
            TimeRange range = 7;
        }
        string filter_signed_key = 8;
        google.protobuf.StringValue protocol_version = 9;
    }
    
    message BaseResult {
        string store = 1;
        // TODO(i9014) reorder once we break the admin api
        google.protobuf.Timestamp sequenced = 7;
        google.protobuf.Timestamp valid_from = 2;
        google.protobuf.Timestamp valid_until = 3;
        com.digitalasset.canton.protocol.v0.TopologyChangeOp operation = 4;
        bytes serialized = 5;
        string signed_by_fingerprint = 6;
    }
    
    message ListPartyToParticipantResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.PartyToParticipant item = 2;
        }
        repeated Result results = 2;
    }
    
    message ListPartyToParticipantRequest {
        BaseQuery base_query = 1;
        string filter_party = 2;
        string filter_participant = 3;
        message FilterRequestSide {
            com.digitalasset.canton.protocol.v0.RequestSide value = 1;
        }
        FilterRequestSide filter_request_side = 4;
        message FilterPermission {
            com.digitalasset.canton.protocol.v0.ParticipantPermission value = 1;
        }
        FilterPermission filter_permission = 5;
    }
    
    message ListOwnerToKeyMappingRequest {
        BaseQuery base_query = 1;
        string filter_key_owner_type = 2;
        string filter_key_owner_uid = 3;
        message FilterKeyPurpose {
            com.digitalasset.canton.crypto.v0.KeyPurpose value = 1;
        }
        FilterKeyPurpose filter_key_purpose = 4;
    }
    
    message ListOwnerToKeyMappingResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.OwnerToKeyMapping item = 2;
            string key_fingerprint = 3;
        }
        repeated Result results = 1;
    }
    
    message ListSignedLegalIdentityClaimRequest {
        BaseQuery base_query = 1;
        string filter_uid = 2;
    }
    
    message ListSignedLegalIdentityClaimResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.SignedLegalIdentityClaim item = 2;
        }
        repeated Result results = 1;
    }
    
    message ListVettedPackagesRequest {
        BaseQuery base_query = 1;
        string filter_participant = 2;
    }
    
    message ListVettedPackagesResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.VettedPackages item = 2;
        }
        repeated Result results = 1;
    }
    
    message ListDomainParametersChangesRequest {
        BaseQuery base_query = 1;
    }
    
    message ListDomainParametersChangesResult {
        message Result {
            BaseResult context = 1;
            oneof parameters {
              com.digitalasset.canton.protocol.v0.DynamicDomainParameters v0 = 2;
              com.digitalasset.canton.protocol.v1.DynamicDomainParameters v1 = 3;
            }
        }
    
        repeated Result results = 1;
    }
    
    message ListAvailableStoresRequest {
    
    }
    message ListAvailableStoresResult {
        repeated string store_ids = 1;
    }
    
    message ListParticipantDomainStateRequest {
        BaseQuery base_query = 1;
        string filter_domain = 2;
        string filter_participant = 3;
    }
    
    message ListParticipantDomainStateResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.ParticipantState item = 2;
        }
        repeated Result results = 1;
    }
    
    message ListMediatorDomainStateRequest {
        BaseQuery base_query = 1;
        string filter_domain = 2;
        string filter_mediator = 3;
    }
    
    message ListMediatorDomainStateResult {
        message Result {
            BaseResult context = 1;
            com.digitalasset.canton.protocol.v0.MediatorDomainState item = 2;
        }
        repeated Result results = 1;
    }
    
    
    message ListAllRequest {
        BaseQuery base_query = 1;
    }
    
    message ListAllResponse {
        com.digitalasset.canton.protocol.v0.TopologyTransactions result = 1;
    }


Topology Manager Write Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.topology.admin.v0;
    
    import "com/digitalasset/canton/crypto/v0/crypto.proto";
    import "com/digitalasset/canton/protocol/v0/topology.proto";
    import "com/digitalasset/canton/protocol/v0/sequencing.proto";
    import "com/digitalasset/canton/protocol/v1/sequencing.proto";
    
    /**
     * Write operations on the local topology manager.
     *
     * Both, participant and domain run a local topology manager exposing the same write interface.
     */
    service TopologyManagerWriteService {
    
        /**
         * Authorizes a party to participant mapping change (add/remove) on the node local topology manager.
         */
        rpc AuthorizePartyToParticipant(PartyToParticipantAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Authorizes an owner to key mapping change (add/remove) on the local topology manager
         */
        rpc AuthorizeOwnerToKeyMapping(OwnerToKeyMappingAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Authorizes a namespace delegation (root or intermediate CA) (add/remove) on the local topology manager
         */
        rpc AuthorizeNamespaceDelegation(NamespaceDelegationAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Authorizes a new identifier delegation (identifier certificate) (add/remove) on the local topology manager
         */
        rpc AuthorizeIdentifierDelegation(IdentifierDelegationAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Authorizes a new package vetting transaction
         */
        rpc AuthorizeVettedPackages(VettedPackagesAuthorization) returns (AuthorizationSuccess);
    
        /** Authorizes a change of parameters for the domain */
        rpc AuthorizeDomainParametersChange(DomainParametersChangeAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Authorizes a new signed legal identity
         */
        rpc AuthorizeSignedLegalIdentityClaim(SignedLegalIdentityClaimAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Authorizes a participant domain state
         */
        rpc AuthorizeParticipantDomainState(ParticipantDomainStateAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Authorizes a mediator domain state
         */
        rpc AuthorizeMediatorDomainState(MediatorDomainStateAuthorization) returns (AuthorizationSuccess);
    
        /**
         * Adds a signed topology transaction to the Authorized store
         */
        rpc AddSignedTopologyTransaction(SignedTopologyTransactionAddition) returns (AdditionSuccess);
    
        /**
         * Generates a legal identity claim
         */
        rpc GenerateSignedLegalIdentityClaim(SignedLegalIdentityClaimGeneration) returns (com.digitalasset.canton.protocol.v0.SignedLegalIdentityClaim);
    
    }
    
    message AuthorizationSuccess {
        bytes serialized = 1;
    }
    
    message AdditionSuccess {
    
    }
    
    message SignedTopologyTransactionAddition {
        bytes serialized = 1;
    }
    
    message AuthorizationData {
    
        /** Add / Remove / Replace */
        com.digitalasset.canton.protocol.v0.TopologyChangeOp change = 1;
    
        /**
         * Fingerprint of the key signing the authorization
         *
         * The signing key is used to identify a particular `NamespaceDelegation` or `IdentifierDelegation` certificate,
         * which is used to justify the given authorization.
         */
        string signed_by = 2;
    
        /** if true, the authorization will also replace the existing (makes only sense for adds) */
        bool replace_existing = 3;
    
        /** Force change even if dangerous */
        bool force_change = 4;
    
    }
    
    message NamespaceDelegationAuthorization {
        AuthorizationData authorization = 1;
    
        // The namespace for which the authorization is issued.
        string namespace = 2;
    
        /**
         * The fingerprint of the signing key which will be authorized to issue topology transactions for this namespace.
         *
         * The key needs to be present in the local key registry either by being locally
         * generated or by having been previously imported.
         */
        string fingerprint_of_authorized_key = 3;
    
        /**
         * Flag indicating whether authorization is a root key delegation
         */
        bool is_root_delegation = 4;
    }
    
    message IdentifierDelegationAuthorization {
        AuthorizationData authorization = 1;
        string identifier = 2;
    
        /**
         * The fingerprint of the signing key which will be authorized to issue topology transaction for this particular identifier.
         *
         * As with `NamespaceDelegation`s, the key needs to be present locally.
         */
        string fingerprint_of_authorized_key = 3;
    }
    
    message PartyToParticipantAuthorization {
        AuthorizationData authorization = 1;
        /**
         * The request side of this transaction
         *
         * A party to participant mapping can map a party from one namespace on a participant from another namespace.
         * Such a mapping needs to be authorized by both namespace keys. If the namespace is the same, we use
         * RequestSide.Both and collapse into a single transaction. Otherwise, `From` needs to be signed by a namespace key
         * of the party and `To` needs to be signed by a namespace key of the participant.
         */
        com.digitalasset.canton.protocol.v0.RequestSide side = 2;
    
        // The unique identifier of the party
        string party = 3;
        // The unique identifier of the participant
        string participant = 4;
        // The permission of the participant that will allow him to act on behalf of the party.
        com.digitalasset.canton.protocol.v0.ParticipantPermission permission = 5;
    }
    
    message OwnerToKeyMappingAuthorization {
    
        AuthorizationData authorization = 1;
    
        /**
         * The key owner
         *
         * An entity in Canton is described by his role and his unique identifier. As such, the same unique identifier
         * can be used for a mediator, sequencer, domain topology manager or even participant. Therefore, we expect
         * here the protoPrimitive of a key owner which is in effect its type as a three letter code separated
         * from the unique identifier.
         */
        string key_owner = 2;
    
    
        /**
         * The fingerprint of the key that will be authorized
         *
         * The key needs to be present in the local key registry (can be imported via KeyService)
         */
        string fingerprint_of_key = 3;
    
        /**
         * Purpose of the key
         */
        com.digitalasset.canton.crypto.v0.KeyPurpose key_purpose = 4;
    
    }
    
    message SignedLegalIdentityClaimAuthorization {
        AuthorizationData authorization = 1;
        com.digitalasset.canton.protocol.v0.SignedLegalIdentityClaim claim = 2;
    }
    
    message SignedLegalIdentityClaimGeneration {
        message X509CertificateClaim {
            string unique_identifier = 1;
            string certificate_id = 2;
        }
        oneof request {
            // Serialized LegalIdentityClaim
            bytes legal_identity_claim = 1;
            X509CertificateClaim certificate = 2;
        }
    }
    
    
    message ParticipantDomainStateAuthorization {
        AuthorizationData authorization = 1;
        /** which side (domain or participant) is attempting to issue the authorization */
        com.digitalasset.canton.protocol.v0.RequestSide side = 2;
        /** domain this authorization refers to */
        string domain = 3;
        /** participant that should be authorized */
        string participant = 4;
        /** permission that should be used (lower of From / To) */
        com.digitalasset.canton.protocol.v0.ParticipantPermission permission = 5;
        /** trust level that should be used (ignored for side from, defaults to Ordinary) */
        com.digitalasset.canton.protocol.v0.TrustLevel trust_level = 6;
    }
    
    message MediatorDomainStateAuthorization {
        AuthorizationData authorization = 1;
        /** which side (domain or mediator) is attempting to issue the authorization */
        com.digitalasset.canton.protocol.v0.RequestSide side = 2;
        /** domain this authorization refers to */
        string domain = 3;
        /** mediator that should be authorized */
        string mediator = 4;
    }
    
    message VettedPackagesAuthorization {
        AuthorizationData authorization = 1;
        string participant = 2;
        repeated string package_ids = 3;
    }
    
    message DomainParametersChangeAuthorization {
        AuthorizationData authorization = 1;
        /** domain this authorization refers to */
        string domain = 2;
        /** new parameters for the domain */
        oneof parameters {
            com.digitalasset.canton.protocol.v0.DynamicDomainParameters parameters_v0 = 3;
            com.digitalasset.canton.protocol.v1.DynamicDomainParameters parameters_v1 = 4;
        }
    }
    


Mediator Admin APIs
-------------------
Standalone Mediator nodes (enterprise version only) expose the following services:

Mediator Initialization Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Service to initialize an external Mediator to participate in confirming transaction results.
Only expected to be called by the Domain node to allow the Mediator to connect to the domain Sequencer.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.domain.admin.v0;
    
    import "com/digitalasset/canton/crypto/v0/crypto.proto";
    import "com/digitalasset/canton/protocol/v0/sequencing.proto";
    import "com/digitalasset/canton/topology/admin/v0/topology_ext.proto";
    
    service MediatorInitializationService {
    
      // Initialize a Mediator service
      // If the Mediator is uninitialized it should initialize itself with the provided configuration
      // If the Mediator is already initialized then verify the request is for the domain we're running against,
      // if correct then just return the current key otherwise fail.
      rpc Initialize (InitializeMediatorRequest) returns (InitializeMediatorResponse);
    
    }
    
    message InitializeMediatorRequest {
      // the domain identifier
      string domain_id = 1;
      // the mediator identifier
      string mediator_id = 2;
      // topology state required for startup
      com.digitalasset.canton.protocol.v0.TopologyTransactions current_identity_state = 3;
      // parameters for the domain (includes the protocol version which needs to match the protocol version the domain
      // manager is running)
      com.digitalasset.canton.protocol.v0.StaticDomainParameters domain_parameters = 4;
      // how should the member connect to the domain sequencer
      com.digitalasset.canton.protocol.v0.SequencerConnection sequencer_connection = 5;
    }
    
    message InitializeMediatorResponse {
      oneof value {
        Success success = 1;
        Failure failure = 2;
      }
    
      message Success {
        // Current signing key
        com.digitalasset.canton.crypto.v0.SigningPublicKey mediator_key = 1;
      }
    
      message Failure {
        // Reason that can be logged
        string reason = 1;
      }
    }


Enterprise Mediator Administration Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. enterprise-only::

Exposes details about the mediator operation such as its leadership status when many mediator instances are running in
a single domain to provide high availability.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.domain.admin.v0;
    
    import "google/protobuf/timestamp.proto";
    import "google/protobuf/empty.proto";
    
    import "com/digitalasset/canton/pruning/admin/v0/pruning.proto";
    
    // administration service for mediator instances
    service EnterpriseMediatorAdministrationService {
    
      // Remove unnecessary data from the Mediator
      rpc Prune (MediatorPruningRequest) returns (google.protobuf.Empty);
    
    
      // Enable automatic pruning using the specified schedule parameters
      // The following errors may occur on the SetSchedule or Update commands:
      // - ``INVALID_ARGUMENT``: if a parameter is missing or an invalid cron expression
      //   or duration.
      // - ``FAILED_PRECONDITION``: if automatic background pruning has not been enabled
      //   or if invoked on a participant running the Community Edition.
      rpc SetSchedule(com.digitalasset.canton.pruning.admin.v0.SetSchedule.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetSchedule.Response);
    
      // Modify individual pruning schedule parameters.
      // - ``INVALID_ARGUMENT``: if the payload is malformed or no schedule is configured
      rpc SetCron(com.digitalasset.canton.pruning.admin.v0.SetCron.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetCron.Response);
      rpc SetMaxDuration(com.digitalasset.canton.pruning.admin.v0.SetMaxDuration.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetMaxDuration.Response);
      rpc SetRetention(com.digitalasset.canton.pruning.admin.v0.SetRetention.Request) returns (com.digitalasset.canton.pruning.admin.v0.SetRetention.Response);
    
      // Disable automatic pruning and remove the persisted schedule configuration.
      rpc ClearSchedule(com.digitalasset.canton.pruning.admin.v0.ClearSchedule.Request) returns (com.digitalasset.canton.pruning.admin.v0.ClearSchedule.Response);
    
      // Retrieve the automatic pruning configuration.
      rpc GetSchedule(com.digitalasset.canton.pruning.admin.v0.GetSchedule.Request) returns (com.digitalasset.canton.pruning.admin.v0.GetSchedule.Response);
    
      // Retrieve pruning timestamp at or near the "beginning" of events.
      rpc LocatePruningTimestamp(com.digitalasset.canton.pruning.admin.v0.LocatePruningTimestamp.Request) returns (com.digitalasset.canton.pruning.admin.v0.LocatePruningTimestamp.Response);
    }
    
    message MediatorPruningRequest {
      // timestamp to prune for
      google.protobuf.Timestamp timestamp = 1;
    }


Sequencer Admin APIs
--------------------
Standalone Sequencer nodes (enterprise version only) expose the following services:

Sequencer Administration Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. enterprise-only::

Exposes status information of the Sequencer.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.domain.admin.v0;
    
    import "google/protobuf/empty.proto";
    import "google/protobuf/timestamp.proto";
    
    // administration service for sequencer instances
    service SequencerAdministrationService {
    
      // fetch the current status of the sequencer
      rpc PruningStatus (google.protobuf.Empty) returns (SequencerPruningStatus);
    
    }
    
    message SequencerMemberStatus {
      string member = 1;
      google.protobuf.Timestamp registered_at = 2;
      google.protobuf.Timestamp last_acknowledged = 3;
      bool enabled = 4;
    }
    
    message SequencerPruningStatus {
      // current time according to the sequencer
      google.protobuf.Timestamp now = 1;
      // the earliest event we are currently storing
      google.protobuf.Timestamp earliest_event_timestamp = 2;
      // details of each member registered on the sequencer
      repeated SequencerMemberStatus members = 3;
    }

Enterprise Sequencer Administration Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Exposes enterprise features of the Sequencer, such as pruning and the ability to disable clients.

.. code-block:: none

    // Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
    // SPDX-License-Identifier: Apache-2.0
    
    syntax = "proto3";
    
    package com.digitalasset.canton.domain.admin.v0;
    
    import "google/protobuf/empty.proto";
    import "google/protobuf/timestamp.proto";
    import "com/digitalasset/canton/domain/admin/v0/sequencer_initialization_snapshot.proto";
    
    // administration service for enterprise feature supporting sequencer instances
    service EnterpriseSequencerAdministrationService {
    
      // Remove data from the Sequencer
      rpc Prune (Pruning.Request) returns (Pruning.Response);
    
      // fetch a snapshot of the sequencer state based on the given timestamp
      rpc Snapshot(Snapshot.Request) returns (Snapshot.Response);
    
      // Disable members at the sequencer. Will prevent existing and new instances from connecting, and permit removing their data.
      rpc DisableMember(DisableMemberRequest) returns (google.protobuf.Empty);
    
      rpc AuthorizeLedgerIdentity(LedgerIdentity.AuthorizeRequest) returns (LedgerIdentity.AuthorizeResponse);
    }
    
    message EthereumAccount {
      string address = 1;
    }
    
    message LedgerIdentity {
      oneof identifier {
        EthereumAccount ethereum_account = 1;
      }
    
      message AuthorizeRequest {
        LedgerIdentity identify = 1;
      }
      message AuthorizeResponse {
        oneof value {
          Success success = 1;
          Failure failure = 2;
        }
      }
      message Success {}
      message Failure {
        string reason = 1;
      }
    }
    
    message Pruning {
      message Request {
        google.protobuf.Timestamp timestamp = 1;
      }
    
      message Response {
        // description of what was removed
        string details = 1;
      }
    }
    
    message Snapshot {
      message Request {
        google.protobuf.Timestamp timestamp = 1;
      }
      message Response {
        oneof value {
          Success success = 1;
          Failure failure = 2;
        }
      }
      message Success {
        com.digitalasset.canton.domain.admin.v0.SequencerSnapshot state = 1;
      }
      message Failure {
        string reason = 1;
      }
    }
    
    message DisableMemberRequest {
      string member = 1;
    }

