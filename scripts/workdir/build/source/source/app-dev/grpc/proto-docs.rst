Ledger API Reference
####################


.. _com/daml/ledger/api/v1/active_contracts_service.proto:

com/daml/ledger/api/v1/active_contracts_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.GetActiveContractsRequest:

GetActiveContractsRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetActiveContractsRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.GetActiveContractsRequest.filter: 

       filter
     - :ref:`TransactionFilter <com.daml.ledger.api.v1.TransactionFilter>`
     - 
     - Templates to include in the served snapshot, per party. Required
   * - .. _com.daml.ledger.api.v1.GetActiveContractsRequest.verbose: 

       verbose
     - :ref:`bool <bool>`
     - 
     - If enabled, values served over the API will contain more information than strictly necessary to interpret the data. In particular, setting the verbose flag to true triggers the ledger to include labels for record fields. Optional
   * - .. _com.daml.ledger.api.v1.GetActiveContractsRequest.active_at_offset: 

       active_at_offset
     - :ref:`string <string>`
     - 
     - The offset at which the snapshot of the active contracts will be computed. Must be no greater than the current ledger end offset. Must be greater than or equal to the last pruning offset. If not set the current ledger end offset will be used. Optional
   



.. _com.daml.ledger.api.v1.GetActiveContractsResponse:

GetActiveContractsResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetActiveContractsResponse.offset: 

       offset
     - :ref:`string <string>`
     - 
     - Included only in the last message. The client should start consuming the transactions endpoint with this offset. The format of this field is described in ``ledger_offset.proto``.
   * - .. _com.daml.ledger.api.v1.GetActiveContractsResponse.workflow_id: 

       workflow_id
     - :ref:`string <string>`
     - 
     - The workflow that created the contracts. Must be a valid LedgerString (as described in ``value.proto``).
   * - .. _com.daml.ledger.api.v1.GetActiveContractsResponse.active_contracts: 

       active_contracts
     - :ref:`CreatedEvent <com.daml.ledger.api.v1.CreatedEvent>`
     - repeated
     - The list of contracts that were introduced by the workflow with ``workflow_id`` at the offset. Must be a valid LedgerString (as described in ``value.proto``).
   






.. _com.daml.ledger.api.v1.ActiveContractsService:

ActiveContractsService
===================================================================================================

Allows clients to initialize themselves according to a fairly recent state of the ledger without reading through all transactions that were committed since the ledger's creation.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetActiveContracts
     - :ref:`GetActiveContractsRequest <com.daml.ledger.api.v1.GetActiveContractsRequest>`
     - :ref:`GetActiveContractsResponse <com.daml.ledger.api.v1.GetActiveContractsResponse>`
     - Returns a stream of the snapshot of the active contracts at a ledger offset. If there are no active contracts, the stream returns a single response message with the offset at which the snapshot has been taken. Clients SHOULD use the offset in the last GetActiveContractsResponse message to continue streaming transactions with the transaction service. Clients SHOULD NOT assume that the set of active contracts they receive reflects the state at the ledger end.
   



.. _com/daml/ledger/api/v1/admin/config_management_service.proto:

com/daml/ledger/api/v1/admin/config_management_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.GetTimeModelRequest:

GetTimeModelRequest
===================================================================================================





.. _com.daml.ledger.api.v1.admin.GetTimeModelResponse:

GetTimeModelResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetTimeModelResponse.configuration_generation: 

       configuration_generation
     - :ref:`int64 <int64>`
     - 
     - The current configuration generation. The generation is a monotonically increasing integer that is incremented on each change. Used when setting the time model.
   * - .. _com.daml.ledger.api.v1.admin.GetTimeModelResponse.time_model: 

       time_model
     - :ref:`TimeModel <com.daml.ledger.api.v1.admin.TimeModel>`
     - 
     - The current ledger time model.
   



.. _com.daml.ledger.api.v1.admin.SetTimeModelRequest:

SetTimeModelRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.SetTimeModelRequest.submission_id: 

       submission_id
     - :ref:`string <string>`
     - 
     - Submission identifier used for tracking the request and to reject duplicate submissions. Required.
   * - .. _com.daml.ledger.api.v1.admin.SetTimeModelRequest.maximum_record_time: 

       maximum_record_time
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - Deadline for the configuration change after which the change is rejected.
   * - .. _com.daml.ledger.api.v1.admin.SetTimeModelRequest.configuration_generation: 

       configuration_generation
     - :ref:`int64 <int64>`
     - 
     - The current configuration generation which we're submitting the change against. This is used to perform a compare-and-swap of the configuration to safeguard against concurrent modifications. Required.
   * - .. _com.daml.ledger.api.v1.admin.SetTimeModelRequest.new_time_model: 

       new_time_model
     - :ref:`TimeModel <com.daml.ledger.api.v1.admin.TimeModel>`
     - 
     - The new time model that replaces the current one. Required.
   



.. _com.daml.ledger.api.v1.admin.SetTimeModelResponse:

SetTimeModelResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.SetTimeModelResponse.configuration_generation: 

       configuration_generation
     - :ref:`int64 <int64>`
     - 
     - The configuration generation of the committed time model.
   



.. _com.daml.ledger.api.v1.admin.TimeModel:

TimeModel
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.TimeModel.avg_transaction_latency: 

       avg_transaction_latency
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - The expected average latency of a transaction, i.e., the average time from submitting the transaction to a [[WriteService]] and the transaction being assigned a record time. Required.
   * - .. _com.daml.ledger.api.v1.admin.TimeModel.min_skew: 

       min_skew
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - The minimimum skew between ledger time and record time: lt_TX >= rt_TX - minSkew Required.
   * - .. _com.daml.ledger.api.v1.admin.TimeModel.max_skew: 

       max_skew
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - The maximum skew between ledger time and record time: lt_TX <= rt_TX + maxSkew Required.
   






.. _com.daml.ledger.api.v1.admin.ConfigManagementService:

ConfigManagementService
===================================================================================================

Status: experimental interface, will change before it is deemed production
ready

The ledger configuration management service provides methods for the ledger administrator
to change the current ledger configuration. The services provides methods to modify
different aspects of the configuration.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetTimeModel
     - :ref:`GetTimeModelRequest <com.daml.ledger.api.v1.admin.GetTimeModelRequest>`
     - :ref:`GetTimeModelResponse <com.daml.ledger.api.v1.admin.GetTimeModelResponse>`
     - Return the currently active time model and the current configuration generation.
   * - SetTimeModel
     - :ref:`SetTimeModelRequest <com.daml.ledger.api.v1.admin.SetTimeModelRequest>`
     - :ref:`SetTimeModelResponse <com.daml.ledger.api.v1.admin.SetTimeModelResponse>`
     - Set the ledger time model.
   



.. _com/daml/ledger/api/v1/admin/identity_provider_config_service.proto:

com/daml/ledger/api/v1/admin/identity_provider_config_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.CreateIdentityProviderConfigRequest:

CreateIdentityProviderConfigRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.CreateIdentityProviderConfigRequest.identity_provider_config: 

       identity_provider_config
     - :ref:`IdentityProviderConfig <com.daml.ledger.api.v1.admin.IdentityProviderConfig>`
     - 
     - Required
   



.. _com.daml.ledger.api.v1.admin.CreateIdentityProviderConfigResponse:

CreateIdentityProviderConfigResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.CreateIdentityProviderConfigResponse.identity_provider_config: 

       identity_provider_config
     - :ref:`IdentityProviderConfig <com.daml.ledger.api.v1.admin.IdentityProviderConfig>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.admin.DeleteIdentityProviderConfigRequest:

DeleteIdentityProviderConfigRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.DeleteIdentityProviderConfigRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The identity provider config to delete. Required
   



.. _com.daml.ledger.api.v1.admin.DeleteIdentityProviderConfigResponse:

DeleteIdentityProviderConfigResponse
===================================================================================================

Does not (yet) contain any data.



.. _com.daml.ledger.api.v1.admin.GetIdentityProviderConfigRequest:

GetIdentityProviderConfigRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetIdentityProviderConfigRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - Required
   



.. _com.daml.ledger.api.v1.admin.GetIdentityProviderConfigResponse:

GetIdentityProviderConfigResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetIdentityProviderConfigResponse.identity_provider_config: 

       identity_provider_config
     - :ref:`IdentityProviderConfig <com.daml.ledger.api.v1.admin.IdentityProviderConfig>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.admin.IdentityProviderConfig:

IdentityProviderConfig
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.IdentityProviderConfig.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The identity provider identifier Must be a valid LedgerString (as describe in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.admin.IdentityProviderConfig.is_deactivated: 

       is_deactivated
     - :ref:`bool <bool>`
     - 
     - When set, the callers using JWT tokens issued by this identity provider are denied all access to the Ledger API. Optional, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.IdentityProviderConfig.issuer: 

       issuer
     - :ref:`string <string>`
     - 
     - Specifies the issuer of the JWT token. The issuer value is a case sensitive URL using the https scheme that contains scheme, host, and optionally, port number and path components and no query or fragment components. Required Modifiable
   * - .. _com.daml.ledger.api.v1.admin.IdentityProviderConfig.jwks_url: 

       jwks_url
     - :ref:`string <string>`
     - 
     - The JWKS (JSON Web Key Set) URL. The Ledger API uses JWKs (JSON Web Keys) from the provided URL to verify that the JWT has been signed with the loaded JWK. Only RS256 (RSA Signature with SHA-256) signing algorithm is supported. Required Modifiable
   



.. _com.daml.ledger.api.v1.admin.ListIdentityProviderConfigsRequest:

ListIdentityProviderConfigsRequest
===================================================================================================

Pagination is not required as the resulting data set is small enough to be returned in a single call



.. _com.daml.ledger.api.v1.admin.ListIdentityProviderConfigsResponse:

ListIdentityProviderConfigsResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListIdentityProviderConfigsResponse.identity_provider_configs: 

       identity_provider_configs
     - :ref:`IdentityProviderConfig <com.daml.ledger.api.v1.admin.IdentityProviderConfig>`
     - repeated
     - 
   



.. _com.daml.ledger.api.v1.admin.UpdateIdentityProviderConfigRequest:

UpdateIdentityProviderConfigRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.UpdateIdentityProviderConfigRequest.identity_provider_config: 

       identity_provider_config
     - :ref:`IdentityProviderConfig <com.daml.ledger.api.v1.admin.IdentityProviderConfig>`
     - 
     - The identity provider config to update. Required, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.UpdateIdentityProviderConfigRequest.update_mask: 

       update_mask
     -  `google.protobuf.FieldMask <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.FieldMask>`__
     - 
     - An update mask specifies how and which properties of the ``IdentityProviderConfig`` message are to be updated. An update mask consists of a set of update paths. A valid update path points to a field or a subfield relative to the ``IdentityProviderConfig`` message. A valid update mask must: (1) contain at least one update path, (2) contain only valid update paths. Fields that can be updated are marked as ``Modifiable``. For additional information see the documentation for standard protobuf3's ``google.protobuf.FieldMask``. Required
   



.. _com.daml.ledger.api.v1.admin.UpdateIdentityProviderConfigResponse:

UpdateIdentityProviderConfigResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.UpdateIdentityProviderConfigResponse.identity_provider_config: 

       identity_provider_config
     - :ref:`IdentityProviderConfig <com.daml.ledger.api.v1.admin.IdentityProviderConfig>`
     - 
     - Updated identity provider config
   






.. _com.daml.ledger.api.v1.admin.IdentityProviderConfigService:

IdentityProviderConfigService
===================================================================================================

Identity Provider Config Service makes it possible for participant node administrators
to setup and manage additional identity providers at runtime.

This allows using access tokens from identity providers unknown at deployment time. When an identity
provider is configured, independent IDP administrators can manage their own set of parties and users.
Such parties and users have a matching `identity_provider_id` defined and are inaccessible to
administrators from other identity providers. A user will only be authenticated if the corresponding JWT
token is issued by the appropriate identity provider.
Users and parties without `identity_provider_id` defined are assumed to be using the default identity provider,
which is configured statically at the participant node's deployment time.

The Ledger API uses the "iss" claim of a JWT token to match the token to a specific IDP. If there is no match,
the default IDP is assumed.

The fields of request messages (and sub-messages) are marked either as ``Optional`` or ``Required``:
(1) ``Optional`` denoting the client may leave the field unset when sending a request.
(2) ``Required`` denoting the client must set the field to a non-default value when sending a request.

An identity provider config resource is described by the ``IdentityProviderConfig`` message,
An identity provider config resource, once it has been created, can be modified.
In order to update the properties represented by the ``IdentityProviderConfig`` message use the ``UpdateIdentityProviderConfig`` RPC.
The only fields that can be modified are those marked as ``Modifiable``.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - CreateIdentityProviderConfig
     - :ref:`CreateIdentityProviderConfigRequest <com.daml.ledger.api.v1.admin.CreateIdentityProviderConfigRequest>`
     - :ref:`CreateIdentityProviderConfigResponse <com.daml.ledger.api.v1.admin.CreateIdentityProviderConfigResponse>`
     - Create a new identity provider configuration. The request will fail if the maximum allowed number of separate configurations is reached.
   * - GetIdentityProviderConfig
     - :ref:`GetIdentityProviderConfigRequest <com.daml.ledger.api.v1.admin.GetIdentityProviderConfigRequest>`
     - :ref:`GetIdentityProviderConfigResponse <com.daml.ledger.api.v1.admin.GetIdentityProviderConfigResponse>`
     - Get the identity provider configuration data by id.
   * - UpdateIdentityProviderConfig
     - :ref:`UpdateIdentityProviderConfigRequest <com.daml.ledger.api.v1.admin.UpdateIdentityProviderConfigRequest>`
     - :ref:`UpdateIdentityProviderConfigResponse <com.daml.ledger.api.v1.admin.UpdateIdentityProviderConfigResponse>`
     - Update selected modifiable attribute of an identity provider config resource described by the ``IdentityProviderConfig`` message.
   * - ListIdentityProviderConfigs
     - :ref:`ListIdentityProviderConfigsRequest <com.daml.ledger.api.v1.admin.ListIdentityProviderConfigsRequest>`
     - :ref:`ListIdentityProviderConfigsResponse <com.daml.ledger.api.v1.admin.ListIdentityProviderConfigsResponse>`
     - List all existing identity provider configurations.
   * - DeleteIdentityProviderConfig
     - :ref:`DeleteIdentityProviderConfigRequest <com.daml.ledger.api.v1.admin.DeleteIdentityProviderConfigRequest>`
     - :ref:`DeleteIdentityProviderConfigResponse <com.daml.ledger.api.v1.admin.DeleteIdentityProviderConfigResponse>`
     - Delete an existing identity provider configuration.
   



.. _com/daml/ledger/api/v1/admin/metering_report_service.proto:

com/daml/ledger/api/v1/admin/metering_report_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.GetMeteringReportRequest:

GetMeteringReportRequest
===================================================================================================

Authorized if and only if the authenticated user is a participant admin.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetMeteringReportRequest.from: 

       from
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - The from timestamp (inclusive). Required.
   * - .. _com.daml.ledger.api.v1.admin.GetMeteringReportRequest.to: 

       to
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - The to timestamp (exclusive). If not provided, the server will default to its current time.
   * - .. _com.daml.ledger.api.v1.admin.GetMeteringReportRequest.application_id: 

       application_id
     - :ref:`string <string>`
     - 
     - If set to a non-empty value, then the report will only be generated for that application. Optional.
   



.. _com.daml.ledger.api.v1.admin.GetMeteringReportResponse:

GetMeteringReportResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetMeteringReportResponse.request: 

       request
     - :ref:`GetMeteringReportRequest <com.daml.ledger.api.v1.admin.GetMeteringReportRequest>`
     - 
     - The actual request that was executed.
   * - .. _com.daml.ledger.api.v1.admin.GetMeteringReportResponse.report_generation_time: 

       report_generation_time
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - The time at which the report was computed.
   * - .. _com.daml.ledger.api.v1.admin.GetMeteringReportResponse.metering_report_json: 

       metering_report_json
     -  `google.protobuf.Struct <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Struct>`__
     - 
     - The metering report json. For a JSON Schema definition of the JSon see: https://github.com/digital-asset/daml/blob/main/ledger-api/grpc-definitions/metering-report-schema.json
   






.. _com.daml.ledger.api.v1.admin.MeteringReportService:

MeteringReportService
===================================================================================================

Experimental API to retrieve metering reports.

Metering reports aim to provide the information necessary for billing participant
and application operators.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetMeteringReport
     - :ref:`GetMeteringReportRequest <com.daml.ledger.api.v1.admin.GetMeteringReportRequest>`
     - :ref:`GetMeteringReportResponse <com.daml.ledger.api.v1.admin.GetMeteringReportResponse>`
     - Retrieve a metering report.
   



.. _com/daml/ledger/api/v1/admin/object_meta.proto:

com/daml/ledger/api/v1/admin/object_meta.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.ObjectMeta:

ObjectMeta
===================================================================================================

Represents metadata corresponding to a participant resource (e.g. a participant user or participant local information about a party).

Based on ``ObjectMeta`` meta used in Kubernetes API.
See https://github.com/kubernetes/apimachinery/blob/master/pkg/apis/meta/v1/generated.proto#L640

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ObjectMeta.resource_version: 

       resource_version
     - :ref:`string <string>`
     - 
     - An opaque, non-empty value, populated by a participant server which represents the internal version of the resource this ``ObjectMeta`` message is attached to. The participant server will change it to a unique value each time the corresponding resource is updated. You must not rely on the format of resource version. The participant server might change it without notice. You can obtain the newest resource version value by issuing a read request. You may use it for concurrent change detection by passing it back unmodified in an update request. The participant server will then compare the passed value with the value maintained by the system to determine if any other updates took place since you had read the resource version. Upon a successful update you are guaranteed that no other update took place during your read-modify-write sequence. However, if another update took place during your read-modify-write sequence then your update will fail with an appropriate error. Concurrent change control is optional. It will be applied only if you include a resource version in an update request. When creating a new instance of a resource you must leave the resource version empty. Its value will be populated by the participant server upon successful resource creation. Optional
   * - .. _com.daml.ledger.api.v1.admin.ObjectMeta.annotations: 

       annotations
     - :ref:`ObjectMeta.AnnotationsEntry <com.daml.ledger.api.v1.admin.ObjectMeta.AnnotationsEntry>`
     - repeated
     - A set of modifiable key-value pairs that can be used to represent arbitrary, client-specific metadata. Constraints: 1. The total size over all keys and values cannot exceed 256kb in UTF-8 encoding. 2. Keys are composed of an optional prefix segment and a required name segment such that: - key prefix, when present, must be a valid DNS subdomain with at most 253 characters, followed by a '/' (forward slash) character, - name segment must have at most 63 characters that are either alphanumeric ([a-z0-9A-Z]), or a '.' (dot), '-' (dash) or '_' (underscore); and it must start and end with an alphanumeric character. 2. Values can be any non-empty strings. Keys with empty prefix are reserved for end-users. Properties set by external tools or internally by the participant server must use non-empty key prefixes. Duplicate keys are disallowed by the semantics of the protobuf3 maps. See: https://developers.google.com/protocol-buffers/docs/proto3#maps Annotations may be a part of a modifiable resource. Use the resource's update RPC to update its annotations. In order to add a new annotation or update an existing one using an update RPC, provide the desired annotation in the update request. In order to remove an annotation using an update RPC, provide the target annotation's key but set its value to the empty string in the update request. Optional Modifiable
   



.. _com.daml.ledger.api.v1.admin.ObjectMeta.AnnotationsEntry:

ObjectMeta.AnnotationsEntry
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ObjectMeta.AnnotationsEntry.key: 

       key
     - :ref:`string <string>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.admin.ObjectMeta.AnnotationsEntry.value: 

       value
     - :ref:`string <string>`
     - 
     - 
   








.. _com/daml/ledger/api/v1/admin/package_management_service.proto:

com/daml/ledger/api/v1/admin/package_management_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.ListKnownPackagesRequest:

ListKnownPackagesRequest
===================================================================================================





.. _com.daml.ledger.api.v1.admin.ListKnownPackagesResponse:

ListKnownPackagesResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListKnownPackagesResponse.package_details: 

       package_details
     - :ref:`PackageDetails <com.daml.ledger.api.v1.admin.PackageDetails>`
     - repeated
     - The details of all Daml-LF packages known to backing participant. Required
   



.. _com.daml.ledger.api.v1.admin.PackageDetails:

PackageDetails
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.PackageDetails.package_id: 

       package_id
     - :ref:`string <string>`
     - 
     - The identity of the Daml-LF package. Must be a valid PackageIdString (as describe in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.admin.PackageDetails.package_size: 

       package_size
     - :ref:`uint64 <uint64>`
     - 
     - Size of the package in bytes. The size of the package is given by the size of the ``daml_lf`` ArchivePayload. See further details in ``daml_lf.proto``. Required
   * - .. _com.daml.ledger.api.v1.admin.PackageDetails.known_since: 

       known_since
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - Indicates since when the package is known to the backing participant. Required
   * - .. _com.daml.ledger.api.v1.admin.PackageDetails.source_description: 

       source_description
     - :ref:`string <string>`
     - 
     - Description provided by the backing participant describing where it got the package from. Optional
   



.. _com.daml.ledger.api.v1.admin.UploadDarFileRequest:

UploadDarFileRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.UploadDarFileRequest.dar_file: 

       dar_file
     - :ref:`bytes <bytes>`
     - 
     - Contains a Daml archive DAR file, which in turn is a jar like zipped container for ``daml_lf`` archives. See further details in ``daml_lf.proto``. Required
   * - .. _com.daml.ledger.api.v1.admin.UploadDarFileRequest.submission_id: 

       submission_id
     - :ref:`string <string>`
     - 
     - Unique submission identifier. Optional, defaults to a random identifier.
   



.. _com.daml.ledger.api.v1.admin.UploadDarFileResponse:

UploadDarFileResponse
===================================================================================================

An empty message that is received when the upload operation succeeded.






.. _com.daml.ledger.api.v1.admin.PackageManagementService:

PackageManagementService
===================================================================================================

Status: experimental interface, will change before it is deemed production
ready

Query the Daml-LF packages supported by the ledger participant and upload
DAR files. We use 'backing participant' to refer to this specific participant
in the methods of this API.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - ListKnownPackages
     - :ref:`ListKnownPackagesRequest <com.daml.ledger.api.v1.admin.ListKnownPackagesRequest>`
     - :ref:`ListKnownPackagesResponse <com.daml.ledger.api.v1.admin.ListKnownPackagesResponse>`
     - Returns the details of all Daml-LF packages known to the backing participant.
   * - UploadDarFile
     - :ref:`UploadDarFileRequest <com.daml.ledger.api.v1.admin.UploadDarFileRequest>`
     - :ref:`UploadDarFileResponse <com.daml.ledger.api.v1.admin.UploadDarFileResponse>`
     - Upload a DAR file to the backing participant. Depending on the ledger implementation this might also make the package available on the whole ledger. This call might not be supported by some ledger implementations. Canton could be an example, where uploading a DAR is not sufficient to render it usable, it must be activated first. This call may: - Succeed, if the package was successfully uploaded, or if the same package was already uploaded before. - Respond with a gRPC error
   



.. _com/daml/ledger/api/v1/admin/participant_pruning_service.proto:

com/daml/ledger/api/v1/admin/participant_pruning_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.PruneRequest:

PruneRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.PruneRequest.prune_up_to: 

       prune_up_to
     - :ref:`string <string>`
     - 
     - Inclusive offset up to which the ledger is to be pruned. By default the following data is pruned: 1. All normal and divulged contracts that have been archived before `prune_up_to`. 2. All transaction events and completions before `prune_up_to`
   * - .. _com.daml.ledger.api.v1.admin.PruneRequest.submission_id: 

       submission_id
     - :ref:`string <string>`
     - 
     - Unique submission identifier. Optional, defaults to a random identifier, used for logging.
   * - .. _com.daml.ledger.api.v1.admin.PruneRequest.prune_all_divulged_contracts: 

       prune_all_divulged_contracts
     - :ref:`bool <bool>`
     - 
     - Prune all immediately and retroactively divulged contracts created before `prune_up_to` independent of whether they were archived before `prune_up_to`. Useful to avoid leaking storage on participant nodes that can see a divulged contract but not its archival.

Application developers SHOULD write their Daml applications such that they do not rely on divulged contracts; i.e., no warnings from using divulged contracts as inputs to transactions are emitted.

Participant node operators SHOULD set the `prune_all_divulged_contracts` flag to avoid leaking storage due to accumulating unarchived divulged contracts PROVIDED that: 1. no application using this participant node relies on divulgence OR 2. divulged contracts on which applications rely have been re-divulged after the `prune_up_to` offset.
   



.. _com.daml.ledger.api.v1.admin.PruneResponse:

PruneResponse
===================================================================================================

Empty for now, but may contain fields in the future






.. _com.daml.ledger.api.v1.admin.ParticipantPruningService:

ParticipantPruningService
===================================================================================================

Prunes/truncates the "oldest" transactions from the participant (the participant Ledger Api Server plus any other
participant-local state) by removing a portion of the ledger in such a way that the set of future, allowed
commands are not affected.

This enables:
1. keeping the "inactive" portion of the ledger to a manageable size and
2. removing inactive state to honor the right to be forgotten.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - Prune
     - :ref:`PruneRequest <com.daml.ledger.api.v1.admin.PruneRequest>`
     - :ref:`PruneResponse <com.daml.ledger.api.v1.admin.PruneResponse>`
     - Prune the ledger specifying the offset before and at which ledger transactions should be removed. Only returns when the potentially long-running prune request ends successfully or with an error.
   



.. _com/daml/ledger/api/v1/admin/party_management_service.proto:

com/daml/ledger/api/v1/admin/party_management_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.AllocatePartyRequest:

AllocatePartyRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.AllocatePartyRequest.party_id_hint: 

       party_id_hint
     - :ref:`string <string>`
     - 
     - A hint to the participant which party ID to allocate. It can be ignored. Must be a valid PartyIdString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.admin.AllocatePartyRequest.display_name: 

       display_name
     - :ref:`string <string>`
     - 
     - Human-readable name of the party to be added to the participant. It doesn't have to be unique. Use of this field is discouraged. Use ``local_metadata`` instead. Optional
   * - .. _com.daml.ledger.api.v1.admin.AllocatePartyRequest.local_metadata: 

       local_metadata
     - :ref:`ObjectMeta <com.daml.ledger.api.v1.admin.ObjectMeta>`
     - 
     - Participant-local metadata to be stored in the ``PartyDetails`` of this newly allocated party. Optional
   * - .. _com.daml.ledger.api.v1.admin.AllocatePartyRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the party is managed by the default identity provider or party is not hosted by the participant.
   



.. _com.daml.ledger.api.v1.admin.AllocatePartyResponse:

AllocatePartyResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.AllocatePartyResponse.party_details: 

       party_details
     - :ref:`PartyDetails <com.daml.ledger.api.v1.admin.PartyDetails>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.admin.GetParticipantIdRequest:

GetParticipantIdRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin)``



.. _com.daml.ledger.api.v1.admin.GetParticipantIdResponse:

GetParticipantIdResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetParticipantIdResponse.participant_id: 

       participant_id
     - :ref:`string <string>`
     - 
     - Identifier of the participant, which SHOULD be globally unique. Must be a valid LedgerString (as describe in ``value.proto``).
   



.. _com.daml.ledger.api.v1.admin.GetPartiesRequest:

GetPartiesRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetPartiesRequest.parties: 

       parties
     - :ref:`string <string>`
     - repeated
     - The stable, unique identifier of the Daml parties. Must be valid PartyIdStrings (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.admin.GetPartiesRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` whose parties should be retrieved. Optional, if not set, assume the party is managed by the default identity provider or party is not hosted by the participant.
   



.. _com.daml.ledger.api.v1.admin.GetPartiesResponse:

GetPartiesResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetPartiesResponse.party_details: 

       party_details
     - :ref:`PartyDetails <com.daml.ledger.api.v1.admin.PartyDetails>`
     - repeated
     - The details of the requested Daml parties by the participant, if known. The party details may not be in the same order as requested. Required
   



.. _com.daml.ledger.api.v1.admin.ListKnownPartiesRequest:

ListKnownPartiesRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListKnownPartiesRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` whose parties should be retrieved. Optional, if not set, assume the party is managed by the default identity provider or party is not hosted by the participant.
   



.. _com.daml.ledger.api.v1.admin.ListKnownPartiesResponse:

ListKnownPartiesResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListKnownPartiesResponse.party_details: 

       party_details
     - :ref:`PartyDetails <com.daml.ledger.api.v1.admin.PartyDetails>`
     - repeated
     - The details of all Daml parties known by the participant. Required
   



.. _com.daml.ledger.api.v1.admin.PartyDetails:

PartyDetails
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.PartyDetails.party: 

       party
     - :ref:`string <string>`
     - 
     - The stable unique identifier of a Daml party. Must be a valid PartyIdString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.admin.PartyDetails.display_name: 

       display_name
     - :ref:`string <string>`
     - 
     - Human readable name associated with the party at allocation time. Caution, it might not be unique. Use of this field is discouraged. Use the `local_metadata` field instead. Optional
   * - .. _com.daml.ledger.api.v1.admin.PartyDetails.is_local: 

       is_local
     - :ref:`bool <bool>`
     - 
     - true if party is hosted by the participant. Optional
   * - .. _com.daml.ledger.api.v1.admin.PartyDetails.local_metadata: 

       local_metadata
     - :ref:`ObjectMeta <com.daml.ledger.api.v1.admin.ObjectMeta>`
     - 
     - Participant-local metadata of this party. Optional, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.PartyDetails.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the party is managed by the default identity provider or party is not hosted by the participant.
   



.. _com.daml.ledger.api.v1.admin.UpdatePartyDetailsRequest:

UpdatePartyDetailsRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(party_details.identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.UpdatePartyDetailsRequest.party_details: 

       party_details
     - :ref:`PartyDetails <com.daml.ledger.api.v1.admin.PartyDetails>`
     - 
     - Party to be updated Required, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.UpdatePartyDetailsRequest.update_mask: 

       update_mask
     -  `google.protobuf.FieldMask <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.FieldMask>`__
     - 
     - An update mask specifies how and which properties of the ``PartyDetails`` message are to be updated. An update mask consists of a set of update paths. A valid update path points to a field or a subfield relative to the ``PartyDetails`` message. A valid update mask must: (1) contain at least one update path, (2) contain only valid update paths. Fields that can be updated are marked as ``Modifiable``. An update path can also point to non-``Modifiable`` fields such as 'party' and 'local_metadata.resource_version' because they are used: (1) to identify the party details resource subject to the update, (2) for concurrent change control. An update path can also point to non-``Modifiable`` fields such as 'is_local' and 'display_name' as long as the values provided in the update request match the server values. Examples of update paths: 'local_metadata.annotations', 'local_metadata'. For additional information see the documentation for standard protobuf3's ``google.protobuf.FieldMask``. For similar Ledger API see ``com.daml.ledger.api.v1.admin.UpdateUserRequest``. Required
   



.. _com.daml.ledger.api.v1.admin.UpdatePartyDetailsResponse:

UpdatePartyDetailsResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.UpdatePartyDetailsResponse.party_details: 

       party_details
     - :ref:`PartyDetails <com.daml.ledger.api.v1.admin.PartyDetails>`
     - 
     - Updated party details
   






.. _com.daml.ledger.api.v1.admin.PartyManagementService:

PartyManagementService
===================================================================================================

This service allows inspecting the party management state of the ledger known to the participant
and managing the participant-local party metadata.

The authorization rules for its RPCs are specified on the ``<RpcName>Request``
messages as boolean expressions over these facts:
(1) ``HasRight(r)`` denoting whether the authenticated user has right ``r`` and
(2) ``IsAuthenticatedIdentityProviderAdmin(idp)`` denoting whether ``idp`` is equal to the ``identity_provider_id``
of the authenticated user and the user has an IdentityProviderAdmin right.

The fields of request messages (and sub-messages) are marked either as ``Optional`` or ``Required``:
(1) ``Optional`` denoting the client may leave the field unset when sending a request.
(2) ``Required`` denoting the client must set the field to a non-default value when sending a request.

A party details resource is described by the ``PartyDetails`` message,
A party details resource, once it has been created, can be modified using the ``UpdatePartyDetails`` RPC.
The only fields that can be modified are those marked as ``Modifiable``.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetParticipantId
     - :ref:`GetParticipantIdRequest <com.daml.ledger.api.v1.admin.GetParticipantIdRequest>`
     - :ref:`GetParticipantIdResponse <com.daml.ledger.api.v1.admin.GetParticipantIdResponse>`
     - Return the identifier of the participant. All horizontally scaled replicas should return the same id. daml-on-kv-ledger: returns an identifier supplied on command line at launch time canton: returns globally unique identifier of the participant
   * - GetParties
     - :ref:`GetPartiesRequest <com.daml.ledger.api.v1.admin.GetPartiesRequest>`
     - :ref:`GetPartiesResponse <com.daml.ledger.api.v1.admin.GetPartiesResponse>`
     - Get the party details of the given parties. Only known parties will be returned in the list.
   * - ListKnownParties
     - :ref:`ListKnownPartiesRequest <com.daml.ledger.api.v1.admin.ListKnownPartiesRequest>`
     - :ref:`ListKnownPartiesResponse <com.daml.ledger.api.v1.admin.ListKnownPartiesResponse>`
     - List the parties known by the participant. The list returned contains parties whose ledger access is facilitated by the participant and the ones maintained elsewhere.
   * - AllocateParty
     - :ref:`AllocatePartyRequest <com.daml.ledger.api.v1.admin.AllocatePartyRequest>`
     - :ref:`AllocatePartyResponse <com.daml.ledger.api.v1.admin.AllocatePartyResponse>`
     - Allocates a new party on a ledger and adds it to the set managed by the participant. Caller specifies a party identifier suggestion, the actual identifier allocated might be different and is implementation specific. Caller can specify party metadata that is stored locally on the participant. This call may: - Succeed, in which case the actual allocated identifier is visible in the response. - Respond with a gRPC error daml-on-kv-ledger: suggestion's uniqueness is checked by the validators in the consensus layer and call rejected if the identifier is already present. canton: completely different globally unique identifier is allocated. Behind the scenes calls to an internal protocol are made. As that protocol is richer than the surface protocol, the arguments take implicit values The party identifier suggestion must be a valid party name. Party names are required to be non-empty US-ASCII strings built from letters, digits, space, colon, minus and underscore limited to 255 chars
   * - UpdatePartyDetails
     - :ref:`UpdatePartyDetailsRequest <com.daml.ledger.api.v1.admin.UpdatePartyDetailsRequest>`
     - :ref:`UpdatePartyDetailsResponse <com.daml.ledger.api.v1.admin.UpdatePartyDetailsResponse>`
     - Update selected modifiable participant-local attributes of a party details resource. Can update the participant's local information for local parties.
   



.. _com/daml/ledger/api/v1/admin/user_management_service.proto:

com/daml/ledger/api/v1/admin/user_management_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.admin.CreateUserRequest:

CreateUserRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(user.identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.CreateUserRequest.user: 

       user
     - :ref:`User <com.daml.ledger.api.v1.admin.User>`
     - 
     - The user to create. Required
   * - .. _com.daml.ledger.api.v1.admin.CreateUserRequest.rights: 

       rights
     - :ref:`Right <com.daml.ledger.api.v1.admin.Right>`
     - repeated
     - The rights to be assigned to the user upon creation, which SHOULD include appropriate rights for the ``user.primary_party``. Optional
   



.. _com.daml.ledger.api.v1.admin.CreateUserResponse:

CreateUserResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.CreateUserResponse.user: 

       user
     - :ref:`User <com.daml.ledger.api.v1.admin.User>`
     - 
     - Created user.
   



.. _com.daml.ledger.api.v1.admin.DeleteUserRequest:

DeleteUserRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.DeleteUserRequest.user_id: 

       user_id
     - :ref:`string <string>`
     - 
     - The user to delete. Required
   * - .. _com.daml.ledger.api.v1.admin.DeleteUserRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the user is managed by the default identity provider.
   



.. _com.daml.ledger.api.v1.admin.DeleteUserResponse:

DeleteUserResponse
===================================================================================================

Does not (yet) contain any data.



.. _com.daml.ledger.api.v1.admin.GetUserRequest:

GetUserRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id) OR IsAuthenticatedUser(user_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetUserRequest.user_id: 

       user_id
     - :ref:`string <string>`
     - 
     - The user whose data to retrieve. If set to empty string (the default), then the data for the authenticated user will be retrieved. Optional
   * - .. _com.daml.ledger.api.v1.admin.GetUserRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the user is managed by the default identity provider.
   



.. _com.daml.ledger.api.v1.admin.GetUserResponse:

GetUserResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GetUserResponse.user: 

       user
     - :ref:`User <com.daml.ledger.api.v1.admin.User>`
     - 
     - Retrieved user.
   



.. _com.daml.ledger.api.v1.admin.GrantUserRightsRequest:

GrantUserRightsRequest
===================================================================================================

Add the rights to the set of rights granted to the user.

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GrantUserRightsRequest.user_id: 

       user_id
     - :ref:`string <string>`
     - 
     - The user to whom to grant rights. Required
   * - .. _com.daml.ledger.api.v1.admin.GrantUserRightsRequest.rights: 

       rights
     - :ref:`Right <com.daml.ledger.api.v1.admin.Right>`
     - repeated
     - The rights to grant. Optional
   * - .. _com.daml.ledger.api.v1.admin.GrantUserRightsRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the user is managed by the default identity provider.
   



.. _com.daml.ledger.api.v1.admin.GrantUserRightsResponse:

GrantUserRightsResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.GrantUserRightsResponse.newly_granted_rights: 

       newly_granted_rights
     - :ref:`Right <com.daml.ledger.api.v1.admin.Right>`
     - repeated
     - The rights that were newly granted by the request.
   



.. _com.daml.ledger.api.v1.admin.ListUserRightsRequest:

ListUserRightsRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id) OR IsAuthenticatedUser(user_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListUserRightsRequest.user_id: 

       user_id
     - :ref:`string <string>`
     - 
     - The user for which to list the rights. If set to empty string (the default), then the rights for the authenticated user will be listed. Required
   * - .. _com.daml.ledger.api.v1.admin.ListUserRightsRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the user is managed by the default identity provider.
   



.. _com.daml.ledger.api.v1.admin.ListUserRightsResponse:

ListUserRightsResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListUserRightsResponse.rights: 

       rights
     - :ref:`Right <com.daml.ledger.api.v1.admin.Right>`
     - repeated
     - All rights of the user.
   



.. _com.daml.ledger.api.v1.admin.ListUsersRequest:

ListUsersRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListUsersRequest.page_token: 

       page_token
     - :ref:`string <string>`
     - 
     - Pagination token to determine the specific page to fetch. Leave empty to fetch the first page. Optional
   * - .. _com.daml.ledger.api.v1.admin.ListUsersRequest.page_size: 

       page_size
     - :ref:`int32 <int32>`
     - 
     - Maximum number of results to be returned by the server. The server will return no more than that many results, but it might return fewer. If 0, the server will decide the number of results to be returned. Optional
   * - .. _com.daml.ledger.api.v1.admin.ListUsersRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the user is managed by the default identity provider.
   



.. _com.daml.ledger.api.v1.admin.ListUsersResponse:

ListUsersResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.ListUsersResponse.users: 

       users
     - :ref:`User <com.daml.ledger.api.v1.admin.User>`
     - repeated
     - A subset of users of the participant node that fit into this page.
   * - .. _com.daml.ledger.api.v1.admin.ListUsersResponse.next_page_token: 

       next_page_token
     - :ref:`string <string>`
     - 
     - Pagination token to retrieve the next page. Empty, if there are no further results.
   



.. _com.daml.ledger.api.v1.admin.RevokeUserRightsRequest:

RevokeUserRightsRequest
===================================================================================================

Remove the rights from the set of rights granted to the user.

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.RevokeUserRightsRequest.user_id: 

       user_id
     - :ref:`string <string>`
     - 
     - The user from whom to revoke rights. Required
   * - .. _com.daml.ledger.api.v1.admin.RevokeUserRightsRequest.rights: 

       rights
     - :ref:`Right <com.daml.ledger.api.v1.admin.Right>`
     - repeated
     - The rights to revoke. Optional
   * - .. _com.daml.ledger.api.v1.admin.RevokeUserRightsRequest.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the ``Identity Provider`` Optional, if not set, assume the user is managed by the default identity provider.
   



.. _com.daml.ledger.api.v1.admin.RevokeUserRightsResponse:

RevokeUserRightsResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.RevokeUserRightsResponse.newly_revoked_rights: 

       newly_revoked_rights
     - :ref:`Right <com.daml.ledger.api.v1.admin.Right>`
     - repeated
     - The rights that were actually revoked by the request.
   



.. _com.daml.ledger.api.v1.admin.Right:

Right
===================================================================================================

A right granted to a user.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.Right.participant_admin: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ kind.participant_admin
     - :ref:`Right.ParticipantAdmin <com.daml.ledger.api.v1.admin.Right.ParticipantAdmin>`
     - 
     - The user can administer the participant node.
   * - .. _com.daml.ledger.api.v1.admin.Right.can_act_as: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ kind.can_act_as
     - :ref:`Right.CanActAs <com.daml.ledger.api.v1.admin.Right.CanActAs>`
     - 
     - The user can act as a specific party.
   * - .. _com.daml.ledger.api.v1.admin.Right.can_read_as: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ kind.can_read_as
     - :ref:`Right.CanReadAs <com.daml.ledger.api.v1.admin.Right.CanReadAs>`
     - 
     - The user can read ledger data visible to a specific party.
   * - .. _com.daml.ledger.api.v1.admin.Right.identity_provider_admin: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ kind.identity_provider_admin
     - :ref:`Right.IdentityProviderAdmin <com.daml.ledger.api.v1.admin.Right.IdentityProviderAdmin>`
     - 
     - The user can administer users and parties assigned to the same identity provider as the one of the user.
   



.. _com.daml.ledger.api.v1.admin.Right.CanActAs:

Right.CanActAs
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.Right.CanActAs.party: 

       party
     - :ref:`string <string>`
     - 
     - The right to authorize commands for this party.
   



.. _com.daml.ledger.api.v1.admin.Right.CanReadAs:

Right.CanReadAs
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.Right.CanReadAs.party: 

       party
     - :ref:`string <string>`
     - 
     - The right to read ledger data visible to this party.
   



.. _com.daml.ledger.api.v1.admin.Right.IdentityProviderAdmin:

Right.IdentityProviderAdmin
===================================================================================================

The right to administer the identity provider that the user is assigned to.
It means, being able to manage users and parties that are also assigned
to the same identity provider.



.. _com.daml.ledger.api.v1.admin.Right.ParticipantAdmin:

Right.ParticipantAdmin
===================================================================================================

The right to administer the participant node.



.. _com.daml.ledger.api.v1.admin.UpdateUserRequest:

UpdateUserRequest
===================================================================================================

Required authorization: ``HasRight(ParticipantAdmin) OR IsAuthenticatedIdentityProviderAdmin(user.identity_provider_id)``

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.UpdateUserRequest.user: 

       user
     - :ref:`User <com.daml.ledger.api.v1.admin.User>`
     - 
     - The user to update. Required, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.UpdateUserRequest.update_mask: 

       update_mask
     -  `google.protobuf.FieldMask <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.FieldMask>`__
     - 
     - An update mask specifies how and which properties of the ``User`` message are to be updated. An update mask consists of a set of update paths. A valid update path points to a field or a subfield relative to the ``User`` message. A valid update mask must: (1) contain at least one update path, (2) contain only valid update paths. Fields that can be updated are marked as ``Modifiable``. An update path can also point to a non-``Modifiable`` fields such as 'id' and 'metadata.resource_version' because they are used: (1) to identify the user resource subject to the update, (2) for concurrent change control. Examples of valid update paths: 'primary_party', 'metadata', 'metadata.annotations'. For additional information see the documentation for standard protobuf3's ``google.protobuf.FieldMask``. For similar Ledger API see ``com.daml.ledger.api.v1.admin.UpdatePartyDetailsRequest``. Required
   



.. _com.daml.ledger.api.v1.admin.UpdateUserResponse:

UpdateUserResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.UpdateUserResponse.user: 

       user
     - :ref:`User <com.daml.ledger.api.v1.admin.User>`
     - 
     - Updated user
   



.. _com.daml.ledger.api.v1.admin.User:

User
===================================================================================================

Users are used to dynamically manage the rights given to Daml applications.
They are stored and managed per participant node.

Read the :doc:`Authorization documentation </app-dev/authorization>` to learn more.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.admin.User.id: 

       id
     - :ref:`string <string>`
     - 
     - The user identifier, which must be a non-empty string of at most 128 characters that are either alphanumeric ASCII characters or one of the symbols "@^$.!`-#+'~_|:". Required
   * - .. _com.daml.ledger.api.v1.admin.User.primary_party: 

       primary_party
     - :ref:`string <string>`
     - 
     - The primary party as which this user reads and acts by default on the ledger *provided* it has the corresponding ``CanReadAs(primary_party)`` or ``CanActAs(primary_party)`` rights. Ledger API clients SHOULD set this field to a non-empty value for all users to enable the users to act on the ledger using their own Daml party. Users for participant administrators MAY have an associated primary party. Optional, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.User.is_deactivated: 

       is_deactivated
     - :ref:`bool <bool>`
     - 
     - When set, then the user is denied all access to the Ledger API. Otherwise, the user has access to the Ledger API as per the user's rights. Optional, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.User.metadata: 

       metadata
     - :ref:`ObjectMeta <com.daml.ledger.api.v1.admin.ObjectMeta>`
     - 
     - The metadata of this user. Note that the ``metadata.resource_version`` tracks changes to the properties described by the ``User`` message and not the user's rights. Optional, Modifiable
   * - .. _com.daml.ledger.api.v1.admin.User.identity_provider_id: 

       identity_provider_id
     - :ref:`string <string>`
     - 
     - The id of the identity provider configured by ``Identity Provider Config`` Optional, if not set, assume the user is managed by the default identity provider.
   






.. _com.daml.ledger.api.v1.admin.UserManagementService:

UserManagementService
===================================================================================================

Service to manage users and their rights for interacting with the Ledger API
served by a participant node.

The authorization rules for its RPCs are specified on the ``<RpcName>Request``
messages as boolean expressions over these facts:
(1) ``HasRight(r)`` denoting whether the authenticated user has right ``r`` and
(2) ``IsAuthenticatedUser(uid)`` denoting whether ``uid`` is the empty string or equal to the id of the authenticated user.
(3) ``IsAuthenticatedIdentityProviderAdmin(idp)`` denoting whether ``idp`` is equal to the ``identity_provider_id``
of the authenticated user and the user has an IdentityProviderAdmin right.
If `user_id` is set to the empty string (the default), then the data for the authenticated user will be retrieved.
If `identity_provider_id` is set to the empty string, the default identity provider will be assumed.

The fields of request messages (and sub-messages) are marked either as ``Optional`` or ``Required``:
(1) ``Optional`` denoting the client may leave the field unset when sending a request.
(2) ``Required`` denoting the client must set the field to a non-default value when sending a request.

A user resource consists of:
(1) a set of properties represented by the ``User`` message,
(2) a set of user rights, where each right is represented by the ``Right`` message.

A user resource, once it has been created, can be modified.
In order to update the properties represented by the ``User`` message use the ``UpdateUser`` RPC. The only fields that can be modified are those marked as ``Modifiable``.
In order to grant or revoke user rights use ``GrantRights' and ``RevokeRights`` RPCs.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - CreateUser
     - :ref:`CreateUserRequest <com.daml.ledger.api.v1.admin.CreateUserRequest>`
     - :ref:`CreateUserResponse <com.daml.ledger.api.v1.admin.CreateUserResponse>`
     - Create a new user.
   * - GetUser
     - :ref:`GetUserRequest <com.daml.ledger.api.v1.admin.GetUserRequest>`
     - :ref:`GetUserResponse <com.daml.ledger.api.v1.admin.GetUserResponse>`
     - Get the user data of a specific user or the authenticated user.
   * - UpdateUser
     - :ref:`UpdateUserRequest <com.daml.ledger.api.v1.admin.UpdateUserRequest>`
     - :ref:`UpdateUserResponse <com.daml.ledger.api.v1.admin.UpdateUserResponse>`
     - Update selected modifiable attribute of a user resource described by the ``User`` message.
   * - DeleteUser
     - :ref:`DeleteUserRequest <com.daml.ledger.api.v1.admin.DeleteUserRequest>`
     - :ref:`DeleteUserResponse <com.daml.ledger.api.v1.admin.DeleteUserResponse>`
     - Delete an existing user and all its rights.
   * - ListUsers
     - :ref:`ListUsersRequest <com.daml.ledger.api.v1.admin.ListUsersRequest>`
     - :ref:`ListUsersResponse <com.daml.ledger.api.v1.admin.ListUsersResponse>`
     - List all existing users.
   * - GrantUserRights
     - :ref:`GrantUserRightsRequest <com.daml.ledger.api.v1.admin.GrantUserRightsRequest>`
     - :ref:`GrantUserRightsResponse <com.daml.ledger.api.v1.admin.GrantUserRightsResponse>`
     - Grant rights to a user. Granting rights does not affect the resource version of the corresponding user.
   * - RevokeUserRights
     - :ref:`RevokeUserRightsRequest <com.daml.ledger.api.v1.admin.RevokeUserRightsRequest>`
     - :ref:`RevokeUserRightsResponse <com.daml.ledger.api.v1.admin.RevokeUserRightsResponse>`
     - Revoke rights from a user. Revoking rights does not affect the resource version of the corresponding user.
   * - ListUserRights
     - :ref:`ListUserRightsRequest <com.daml.ledger.api.v1.admin.ListUserRightsRequest>`
     - :ref:`ListUserRightsResponse <com.daml.ledger.api.v1.admin.ListUserRightsResponse>`
     - List the set of all rights granted to a user.
   



.. _com/daml/ledger/api/v1/command_completion_service.proto:

com/daml/ledger/api/v1/command_completion_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.Checkpoint:

Checkpoint
===================================================================================================

Checkpoints may be used to:

* detect time out of commands.
* provide an offset which can be used to restart consumption.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Checkpoint.record_time: 

       record_time
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - All commands with a maximum record time below this value MUST be considered lost if their completion has not arrived before this checkpoint. Required
   * - .. _com.daml.ledger.api.v1.Checkpoint.offset: 

       offset
     - :ref:`LedgerOffset <com.daml.ledger.api.v1.LedgerOffset>`
     - 
     - May be used in a subsequent CompletionStreamRequest to resume the consumption of this stream at a later time. Required
   



.. _com.daml.ledger.api.v1.CompletionEndRequest:

CompletionEndRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CompletionEndRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   



.. _com.daml.ledger.api.v1.CompletionEndResponse:

CompletionEndResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CompletionEndResponse.offset: 

       offset
     - :ref:`LedgerOffset <com.daml.ledger.api.v1.LedgerOffset>`
     - 
     - This offset can be used in a CompletionStreamRequest message. Required
   



.. _com.daml.ledger.api.v1.CompletionStreamRequest:

CompletionStreamRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CompletionStreamRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger id reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.CompletionStreamRequest.application_id: 

       application_id
     - :ref:`string <string>`
     - 
     - Only completions of commands submitted with the same application_id will be visible in the stream. Must be a valid ApplicationIdString (as described in ``value.proto``). Required unless authentication is used with a user token or a custom token specifying an application-id. In that case, the token's user-id, respectively application-id, will be used for the request's application_id.
   * - .. _com.daml.ledger.api.v1.CompletionStreamRequest.parties: 

       parties
     - :ref:`string <string>`
     - repeated
     - Non-empty list of parties whose data should be included. Only completions of commands for which at least one of the ``act_as`` parties is in the given set of parties will be visible in the stream. Must be a valid PartyIdString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.CompletionStreamRequest.offset: 

       offset
     - :ref:`LedgerOffset <com.daml.ledger.api.v1.LedgerOffset>`
     - 
     - This field indicates the minimum offset for completions. This can be used to resume an earlier completion stream. This offset is exclusive: the response will only contain commands whose offset is strictly greater than this. Optional, if not set the ledger uses the current ledger end offset instead.
   



.. _com.daml.ledger.api.v1.CompletionStreamResponse:

CompletionStreamResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CompletionStreamResponse.checkpoint: 

       checkpoint
     - :ref:`Checkpoint <com.daml.ledger.api.v1.Checkpoint>`
     - 
     - This checkpoint may be used to restart consumption. The checkpoint is after any completions in this response. Optional
   * - .. _com.daml.ledger.api.v1.CompletionStreamResponse.completions: 

       completions
     - :ref:`Completion <com.daml.ledger.api.v1.Completion>`
     - repeated
     - If set, one or more completions.
   






.. _com.daml.ledger.api.v1.CommandCompletionService:

CommandCompletionService
===================================================================================================

Allows clients to observe the status of their submissions.
Commands may be submitted via the Command Submission Service.
The on-ledger effects of their submissions are disclosed by the Transaction Service.

Commands may fail in 2 distinct manners:

1. Failure communicated synchronously in the gRPC error of the submission.
2. Failure communicated asynchronously in a Completion, see ``completion.proto``.

Note that not only successfully submitted commands MAY produce a completion event. For example, the participant MAY
choose to produce a completion event for a rejection of a duplicate command.

Clients that do not receive a successful completion about their submission MUST NOT assume that it was successful.
Clients SHOULD subscribe to the CompletionStream before starting to submit commands to prevent race conditions.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - CompletionStream
     - :ref:`CompletionStreamRequest <com.daml.ledger.api.v1.CompletionStreamRequest>`
     - :ref:`CompletionStreamResponse <com.daml.ledger.api.v1.CompletionStreamResponse>`
     - Subscribe to command completion events.
   * - CompletionEnd
     - :ref:`CompletionEndRequest <com.daml.ledger.api.v1.CompletionEndRequest>`
     - :ref:`CompletionEndResponse <com.daml.ledger.api.v1.CompletionEndResponse>`
     - Returns the offset after the latest completion.
   



.. _com/daml/ledger/api/v1/command_service.proto:

com/daml/ledger/api/v1/command_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionIdResponse:

SubmitAndWaitForTransactionIdResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionIdResponse.transaction_id: 

       transaction_id
     - :ref:`string <string>`
     - 
     - The id of the transaction that resulted from the submitted command. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionIdResponse.completion_offset: 

       completion_offset
     - :ref:`string <string>`
     - 
     - The format of this field is described in ``ledger_offset.proto``. Optional
   



.. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionResponse:

SubmitAndWaitForTransactionResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionResponse.transaction: 

       transaction
     - :ref:`Transaction <com.daml.ledger.api.v1.Transaction>`
     - 
     - The flat transaction that resulted from the submitted command. Required
   * - .. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionResponse.completion_offset: 

       completion_offset
     - :ref:`string <string>`
     - 
     - The format of this field is described in ``ledger_offset.proto``. Optional
   



.. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionTreeResponse:

SubmitAndWaitForTransactionTreeResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionTreeResponse.transaction: 

       transaction
     - :ref:`TransactionTree <com.daml.ledger.api.v1.TransactionTree>`
     - 
     - The transaction tree that resulted from the submitted command. Required
   * - .. _com.daml.ledger.api.v1.SubmitAndWaitForTransactionTreeResponse.completion_offset: 

       completion_offset
     - :ref:`string <string>`
     - 
     - The format of this field is described in ``ledger_offset.proto``. Optional
   



.. _com.daml.ledger.api.v1.SubmitAndWaitRequest:

SubmitAndWaitRequest
===================================================================================================

These commands are atomic, and will become transactions.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.SubmitAndWaitRequest.commands: 

       commands
     - :ref:`Commands <com.daml.ledger.api.v1.Commands>`
     - 
     - The commands to be submitted. Required
   






.. _com.daml.ledger.api.v1.CommandService:

CommandService
===================================================================================================

Command Service is able to correlate submitted commands with completion data, identify timeouts, and return contextual
information with each tracking result. This supports the implementation of stateless clients.

Note that submitted commands generally produce completion events as well, even in case a command gets rejected.
For example, the participant MAY choose to produce a completion event for a rejection of a duplicate command.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - SubmitAndWait
     - :ref:`SubmitAndWaitRequest <com.daml.ledger.api.v1.SubmitAndWaitRequest>`
     -  `.google.protobuf.Empty <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Empty>`__
     - Submits a single composite command and waits for its result. Propagates the gRPC error of failed submissions including Daml interpretation errors.
   * - SubmitAndWaitForTransactionId
     - :ref:`SubmitAndWaitRequest <com.daml.ledger.api.v1.SubmitAndWaitRequest>`
     - :ref:`SubmitAndWaitForTransactionIdResponse <com.daml.ledger.api.v1.SubmitAndWaitForTransactionIdResponse>`
     - Submits a single composite command, waits for its result, and returns the transaction id. Propagates the gRPC error of failed submissions including Daml interpretation errors.
   * - SubmitAndWaitForTransaction
     - :ref:`SubmitAndWaitRequest <com.daml.ledger.api.v1.SubmitAndWaitRequest>`
     - :ref:`SubmitAndWaitForTransactionResponse <com.daml.ledger.api.v1.SubmitAndWaitForTransactionResponse>`
     - Submits a single composite command, waits for its result, and returns the transaction. Propagates the gRPC error of failed submissions including Daml interpretation errors.
   * - SubmitAndWaitForTransactionTree
     - :ref:`SubmitAndWaitRequest <com.daml.ledger.api.v1.SubmitAndWaitRequest>`
     - :ref:`SubmitAndWaitForTransactionTreeResponse <com.daml.ledger.api.v1.SubmitAndWaitForTransactionTreeResponse>`
     - Submits a single composite command, waits for its result, and returns the transaction tree. Propagates the gRPC error of failed submissions including Daml interpretation errors.
   



.. _com/daml/ledger/api/v1/command_submission_service.proto:

com/daml/ledger/api/v1/command_submission_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.SubmitRequest:

SubmitRequest
===================================================================================================

The submitted commands will be processed atomically in a single transaction. Moreover, each ``Command`` in ``commands`` will be executed in the order specified by the request.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.SubmitRequest.commands: 

       commands
     - :ref:`Commands <com.daml.ledger.api.v1.Commands>`
     - 
     - The commands to be submitted in a single transaction. Required
   






.. _com.daml.ledger.api.v1.CommandSubmissionService:

CommandSubmissionService
===================================================================================================

Allows clients to attempt advancing the ledger's state by submitting commands.
The final states of their submissions are disclosed by the Command Completion Service.
The on-ledger effects of their submissions are disclosed by the Transaction Service.

Commands may fail in 2 distinct manners:

1. Failure communicated synchronously in the gRPC error of the submission.
2. Failure communicated asynchronously in a Completion, see ``completion.proto``.

Note that not only successfully submitted commands MAY produce a completion event. For example, the participant MAY
choose to produce a completion event for a rejection of a duplicate command.

Clients that do not receive a successful completion about their submission MUST NOT assume that it was successful.
Clients SHOULD subscribe to the CompletionStream before starting to submit commands to prevent race conditions.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - Submit
     - :ref:`SubmitRequest <com.daml.ledger.api.v1.SubmitRequest>`
     -  `.google.protobuf.Empty <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Empty>`__
     - Submit a single composite command.
   



.. _com/daml/ledger/api/v1/commands.proto:

com/daml/ledger/api/v1/commands.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.Command:

Command
===================================================================================================

A command can either create a new contract or exercise a choice on an existing contract.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Command.create: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ command.create
     - :ref:`CreateCommand <com.daml.ledger.api.v1.CreateCommand>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Command.exercise: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ command.exercise
     - :ref:`ExerciseCommand <com.daml.ledger.api.v1.ExerciseCommand>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Command.exerciseByKey: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ command.exerciseByKey
     - :ref:`ExerciseByKeyCommand <com.daml.ledger.api.v1.ExerciseByKeyCommand>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Command.createAndExercise: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ command.createAndExercise
     - :ref:`CreateAndExerciseCommand <com.daml.ledger.api.v1.CreateAndExerciseCommand>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.Commands:

Commands
===================================================================================================

A composite command that groups multiple commands together.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Commands.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.Commands.workflow_id: 

       workflow_id
     - :ref:`string <string>`
     - 
     - Identifier of the on-ledger workflow that this command is a part of. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.Commands.application_id: 

       application_id
     - :ref:`string <string>`
     - 
     - Uniquely identifies the application or participant user that issued the command. Must be a valid ApplicationIdString (as described in ``value.proto``). Required unless authentication is used with a user token or a custom token specifying an application-id. In that case, the token's user-id, respectively application-id, will be used for the request's application_id.
   * - .. _com.daml.ledger.api.v1.Commands.command_id: 

       command_id
     - :ref:`string <string>`
     - 
     - Uniquely identifies the command. The triple (application_id, party + act_as, command_id) constitutes the change ID for the intended ledger change, where party + act_as is interpreted as a set of party names. The change ID can be used for matching the intended ledger changes with all their completions. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.Commands.party: 

       party
     - :ref:`string <string>`
     - 
     - Party on whose behalf the command should be executed. If ledger API authorization is enabled, then the authorization metadata must authorize the sender of the request to act on behalf of the given party. Must be a valid PartyIdString (as described in ``value.proto``). Deprecated in favor of the ``act_as`` field. If both are set, then the effective list of parties on whose behalf the command should be executed is the union of all parties listed in ``party`` and ``act_as``. Optional
   * - .. _com.daml.ledger.api.v1.Commands.commands: 

       commands
     - :ref:`Command <com.daml.ledger.api.v1.Command>`
     - repeated
     - Individual elements of this atomic command. Must be non-empty. Required
   * - .. _com.daml.ledger.api.v1.Commands.deduplication_time: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ deduplication_period.deduplication_time
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - Specifies the length of the deduplication period. Same semantics apply as for `deduplication_duration`. Must be non-negative. Must not exceed the maximum deduplication time (see ``ledger_configuration_service.proto``).
   * - .. _com.daml.ledger.api.v1.Commands.deduplication_duration: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ deduplication_period.deduplication_duration
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - Specifies the length of the deduplication period. It is interpreted relative to the local clock at some point during the submission's processing. Must be non-negative. Must not exceed the maximum deduplication time (see ``ledger_configuration_service.proto``).
   * - .. _com.daml.ledger.api.v1.Commands.deduplication_offset: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ deduplication_period.deduplication_offset
     - :ref:`string <string>`
     - 
     - Specifies the start of the deduplication period by a completion stream offset (exclusive). Must be a valid LedgerString (as described in ``ledger_offset.proto``).
   * - .. _com.daml.ledger.api.v1.Commands.min_ledger_time_abs: 

       min_ledger_time_abs
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - Lower bound for the ledger time assigned to the resulting transaction. Note: The ledger time of a transaction is assigned as part of command interpretation. Use this property if you expect that command interpretation will take a considerate amount of time, such that by the time the resulting transaction is sequenced, its assigned ledger time is not valid anymore. Must not be set at the same time as min_ledger_time_rel. Optional
   * - .. _com.daml.ledger.api.v1.Commands.min_ledger_time_rel: 

       min_ledger_time_rel
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - Same as min_ledger_time_abs, but specified as a duration, starting from the time the command is received by the server. Must not be set at the same time as min_ledger_time_abs. Optional
   * - .. _com.daml.ledger.api.v1.Commands.act_as: 

       act_as
     - :ref:`string <string>`
     - repeated
     - Set of parties on whose behalf the command should be executed. If ledger API authorization is enabled, then the authorization metadata must authorize the sender of the request to act on behalf of each of the given parties. This field supersedes the ``party`` field. The effective set of parties on whose behalf the command should be executed is the union of all parties listed in ``party`` and ``act_as``, which must be non-empty. Each element must be a valid PartyIdString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.Commands.read_as: 

       read_as
     - :ref:`string <string>`
     - repeated
     - Set of parties on whose behalf (in addition to all parties listed in ``act_as``) contracts can be retrieved. This affects Daml operations such as ``fetch``, ``fetchByKey``, ``lookupByKey``, ``exercise``, and ``exerciseByKey``. Note: A participant node of a Daml network can host multiple parties. Each contract present on the participant node is only visible to a subset of these parties. A command can only use contracts that are visible to at least one of the parties in ``act_as`` or ``read_as``. This visibility check is independent from the Daml authorization rules for fetch operations. If ledger API authorization is enabled, then the authorization metadata must authorize the sender of the request to read contract data on behalf of each of the given parties. Optional
   * - .. _com.daml.ledger.api.v1.Commands.submission_id: 

       submission_id
     - :ref:`string <string>`
     - 
     - A unique identifier to distinguish completions for different submissions with the same change ID. Typically a random UUID. Applications are expected to use a different UUID for each retry of a submission with the same change ID. Must be a valid LedgerString (as described in ``value.proto``).

If omitted, the participant or the committer may set a value of their choice. Optional
   * - .. _com.daml.ledger.api.v1.Commands.disclosed_contracts: 

       disclosed_contracts
     - :ref:`DisclosedContract <com.daml.ledger.api.v1.DisclosedContract>`
     - repeated
     - Additional contracts used to resolve contract & contract key lookups. Optional
   



.. _com.daml.ledger.api.v1.CreateAndExerciseCommand:

CreateAndExerciseCommand
===================================================================================================

Create a contract and exercise a choice on it in the same transaction.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CreateAndExerciseCommand.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template of the contract the client wants to create. Required
   * - .. _com.daml.ledger.api.v1.CreateAndExerciseCommand.create_arguments: 

       create_arguments
     - :ref:`Record <com.daml.ledger.api.v1.Record>`
     - 
     - The arguments required for creating a contract from this template. Required
   * - .. _com.daml.ledger.api.v1.CreateAndExerciseCommand.choice: 

       choice
     - :ref:`string <string>`
     - 
     - The name of the choice the client wants to exercise. Must be a valid NameString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.CreateAndExerciseCommand.choice_argument: 

       choice_argument
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The argument for this choice. Required
   



.. _com.daml.ledger.api.v1.CreateCommand:

CreateCommand
===================================================================================================

Create a new contract instance based on a template.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CreateCommand.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template of contract the client wants to create. Required
   * - .. _com.daml.ledger.api.v1.CreateCommand.create_arguments: 

       create_arguments
     - :ref:`Record <com.daml.ledger.api.v1.Record>`
     - 
     - The arguments required for creating a contract from this template. Required
   



.. _com.daml.ledger.api.v1.DisclosedContract:

DisclosedContract
===================================================================================================

An additional contract that is used to resolve
contract & contract key lookups.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.DisclosedContract.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template id of the contract. Required
   * - .. _com.daml.ledger.api.v1.DisclosedContract.contract_id: 

       contract_id
     - :ref:`string <string>`
     - 
     - The contract id Required
   * - .. _com.daml.ledger.api.v1.DisclosedContract.create_arguments: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ arguments.create_arguments
     - :ref:`Record <com.daml.ledger.api.v1.Record>`
     - 
     - The contract arguments as typed Record
   * - .. _com.daml.ledger.api.v1.DisclosedContract.create_arguments_blob: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ arguments.create_arguments_blob
     -  `google.protobuf.Any <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Any>`__
     - 
     - The contract arguments specified using an opaque blob extracted from the ``create_arguments_blob`` field of a ``com.daml.ledger.api.v1.CreatedEvent``.
   * - .. _com.daml.ledger.api.v1.DisclosedContract.metadata: 

       metadata
     - :ref:`ContractMetadata <com.daml.ledger.api.v1.ContractMetadata>`
     - 
     - The contract metadata from the create event. Required
   



.. _com.daml.ledger.api.v1.ExerciseByKeyCommand:

ExerciseByKeyCommand
===================================================================================================

Exercise a choice on an existing contract specified by its key.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExerciseByKeyCommand.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template of contract the client wants to exercise. Required
   * - .. _com.daml.ledger.api.v1.ExerciseByKeyCommand.contract_key: 

       contract_key
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The key of the contract the client wants to exercise upon. Required
   * - .. _com.daml.ledger.api.v1.ExerciseByKeyCommand.choice: 

       choice
     - :ref:`string <string>`
     - 
     - The name of the choice the client wants to exercise. Must be a valid NameString (as described in ``value.proto``) Required
   * - .. _com.daml.ledger.api.v1.ExerciseByKeyCommand.choice_argument: 

       choice_argument
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The argument for this choice. Required
   



.. _com.daml.ledger.api.v1.ExerciseCommand:

ExerciseCommand
===================================================================================================

Exercise a choice on an existing contract.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExerciseCommand.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template of contract the client wants to exercise. Required
   * - .. _com.daml.ledger.api.v1.ExerciseCommand.contract_id: 

       contract_id
     - :ref:`string <string>`
     - 
     - The ID of the contract the client wants to exercise upon. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ExerciseCommand.choice: 

       choice
     - :ref:`string <string>`
     - 
     - The name of the choice the client wants to exercise. Must be a valid NameString (as described in ``value.proto``) Required
   * - .. _com.daml.ledger.api.v1.ExerciseCommand.choice_argument: 

       choice_argument
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The argument for this choice. Required
   








.. _com/daml/ledger/api/v1/completion.proto:

com/daml/ledger/api/v1/completion.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.Completion:

Completion
===================================================================================================

A completion represents the status of a submitted command on the ledger: it can be successful or failed.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Completion.command_id: 

       command_id
     - :ref:`string <string>`
     - 
     - The ID of the succeeded or failed command. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.Completion.status: 

       status
     -  `google.rpc.Status <https://cloud.google.com/tasks/docs/reference/rpc/google.rpc#google.rpc.Status>`__
     - 
     - Identifies the exact type of the error. It uses the same format of conveying error details as it is used for the RPC responses of the APIs. Optional
   * - .. _com.daml.ledger.api.v1.Completion.transaction_id: 

       transaction_id
     - :ref:`string <string>`
     - 
     - The transaction_id of the transaction that resulted from the command with command_id. Only set for successfully executed commands. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.Completion.application_id: 

       application_id
     - :ref:`string <string>`
     - 
     - The application-id or user-id that was used for the submission, as described in ``commands.proto``. Must be a valid ApplicationIdString (as described in ``value.proto``). Optional for historic completions where this data is not available.
   * - .. _com.daml.ledger.api.v1.Completion.act_as: 

       act_as
     - :ref:`string <string>`
     - repeated
     - The set of parties on whose behalf the commands were executed. Contains the union of ``party`` and ``act_as`` from ``commands.proto``. The order of the parties need not be the same as in the submission. Each element must be a valid PartyIdString (as described in ``value.proto``). Optional for historic completions where this data is not available.
   * - .. _com.daml.ledger.api.v1.Completion.submission_id: 

       submission_id
     - :ref:`string <string>`
     - 
     - The submission ID this completion refers to, as described in ``commands.proto``. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.Completion.deduplication_offset: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ deduplication_period.deduplication_offset
     - :ref:`string <string>`
     - 
     - Specifies the start of the deduplication period by a completion stream offset (exclusive).

Must be a valid LedgerString (as described in ``value.proto``).
   * - .. _com.daml.ledger.api.v1.Completion.deduplication_duration: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ deduplication_period.deduplication_duration
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - Specifies the length of the deduplication period. It is measured in record time of completions.

Must be non-negative.
   








.. _com/daml/ledger/api/v1/contract_metadata.proto:

com/daml/ledger/api/v1/contract_metadata.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.ContractMetadata:

ContractMetadata
===================================================================================================

Contract-related metadata used in DisclosedContract (that can be included in command submission)
or forwarded as part of the CreateEvent in Active Contract Set or Transaction streams.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ContractMetadata.created_at: 

       created_at
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - Ledger effective time of the transaction that created the contract. Required
   * - .. _com.daml.ledger.api.v1.ContractMetadata.contract_key_hash: 

       contract_key_hash
     - :ref:`bytes <bytes>`
     - 
     - Hash of the contract key if defined. Optional
   * - .. _com.daml.ledger.api.v1.ContractMetadata.driver_metadata: 

       driver_metadata
     - :ref:`bytes <bytes>`
     - 
     - Driver-specific metadata. This is opaque and cannot be decoded. Optional
   








.. _com/daml/ledger/api/v1/event.proto:

com/daml/ledger/api/v1/event.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.ArchivedEvent:

ArchivedEvent
===================================================================================================

Records that a contract has been archived, and choices may no longer be exercised on it.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ArchivedEvent.event_id: 

       event_id
     - :ref:`string <string>`
     - 
     - The ID of this particular event. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ArchivedEvent.contract_id: 

       contract_id
     - :ref:`string <string>`
     - 
     - The ID of the archived contract. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ArchivedEvent.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template of the archived contract. Required
   * - .. _com.daml.ledger.api.v1.ArchivedEvent.witness_parties: 

       witness_parties
     - :ref:`string <string>`
     - repeated
     - The parties that are notified of this event. For an ``ArchivedEvent``, these are the intersection of the stakeholders of the contract in question and the parties specified in the ``TransactionFilter``. The stakeholders are the union of the signatories and the observers of the contract. Each one of its elements must be a valid PartyIdString (as described in ``value.proto``). Required
   



.. _com.daml.ledger.api.v1.CreatedEvent:

CreatedEvent
===================================================================================================

Records that a contract has been created, and choices may now be exercised on it.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CreatedEvent.event_id: 

       event_id
     - :ref:`string <string>`
     - 
     - The ID of this particular event. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.CreatedEvent.contract_id: 

       contract_id
     - :ref:`string <string>`
     - 
     - The ID of the created contract. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.CreatedEvent.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template of the created contract. Required
   * - .. _com.daml.ledger.api.v1.CreatedEvent.contract_key: 

       contract_key
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The key of the created contract. This will be set if and only if ``create_arguments`` is set and ``template_id`` defines a contract key. Optional
   * - .. _com.daml.ledger.api.v1.CreatedEvent.create_arguments: 

       create_arguments
     - :ref:`Record <com.daml.ledger.api.v1.Record>`
     - 
     - The arguments that have been used to create the contract. Set either: - if there was a party, which is in the ``witness_parties`` of this event, and for which an ``InclusiveFilters`` exists with the ``template_id`` of this event among the ``template_ids``, - or if there was a party, which is in the ``witness_parties`` of this event, and for which a wildcard filter exists (``Filters`` without ``InclusiveFilters``, or with an ``InclusiveFilters`` with empty ``template_ids`` and empty ``interface_filters``). Optional
   * - .. _com.daml.ledger.api.v1.CreatedEvent.create_arguments_blob: 

       create_arguments_blob
     -  `google.protobuf.Any <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Any>`__
     - 
     - Opaque representation of contract payload intended for forwarding to an API server as a contract disclosed as part of a command submission. Optional
   * - .. _com.daml.ledger.api.v1.CreatedEvent.interface_views: 

       interface_views
     - :ref:`InterfaceView <com.daml.ledger.api.v1.InterfaceView>`
     - repeated
     - Interface views specified in the transaction filter. Includes an ``InterfaceView`` for each interface for which there is a ``InterfaceFilter`` with - its party in the ``witness_parties`` of this event, - and which is implemented by the template of this event, - and which has ``include_interface_view`` set. Optional
   * - .. _com.daml.ledger.api.v1.CreatedEvent.witness_parties: 

       witness_parties
     - :ref:`string <string>`
     - repeated
     - The parties that are notified of this event. When a ``CreatedEvent`` is returned as part of a transaction tree, this will include all the parties specified in the ``TransactionFilter`` that are informees of the event. If served as part of a flat transaction those will be limited to all parties specified in the ``TransactionFilter`` that are stakeholders of the contract (i.e. either signatories or observers). Required
   * - .. _com.daml.ledger.api.v1.CreatedEvent.signatories: 

       signatories
     - :ref:`string <string>`
     - repeated
     - The signatories for this contract as specified by the template. Required
   * - .. _com.daml.ledger.api.v1.CreatedEvent.observers: 

       observers
     - :ref:`string <string>`
     - repeated
     - The observers for this contract as specified explicitly by the template or implicitly as choice controllers. This field never contains parties that are signatories. Required
   * - .. _com.daml.ledger.api.v1.CreatedEvent.agreement_text: 

       agreement_text
     -  `google.protobuf.StringValue <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.StringValue>`__
     - 
     - The agreement text of the contract. We use StringValue to properly reflect optionality on the wire for backwards compatibility. This is necessary since the empty string is an acceptable (and in fact the default) agreement text, but also the default string in protobuf. This means a newer client works with an older sandbox seamlessly. Optional
   * - .. _com.daml.ledger.api.v1.CreatedEvent.metadata: 

       metadata
     - :ref:`ContractMetadata <com.daml.ledger.api.v1.ContractMetadata>`
     - 
     - Metadata of the contract. Required for contracts created after the introduction of explicit disclosure. Optional
   



.. _com.daml.ledger.api.v1.Event:

Event
===================================================================================================

An event in the flat transaction stream can either be the creation
or the archiving of a contract.

In the transaction service the events are restricted to the events
visible for the parties specified in the transaction filter. Each
event message type below contains a ``witness_parties`` field which
indicates the subset of the requested parties that can see the event
in question. In the flat transaction stream you'll only receive events
that have witnesses.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Event.created: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ event.created
     - :ref:`CreatedEvent <com.daml.ledger.api.v1.CreatedEvent>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Event.archived: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ event.archived
     - :ref:`ArchivedEvent <com.daml.ledger.api.v1.ArchivedEvent>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.ExercisedEvent:

ExercisedEvent
===================================================================================================

Records that a choice has been exercised on a target contract.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.event_id: 

       event_id
     - :ref:`string <string>`
     - 
     - The ID of this particular event. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.contract_id: 

       contract_id
     - :ref:`string <string>`
     - 
     - The ID of the target contract. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.template_id: 

       template_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The template of the target contract. Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.interface_id: 

       interface_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The interface where the choice is defined, if inherited. Optional
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.choice: 

       choice
     - :ref:`string <string>`
     - 
     - The choice that was exercised on the target contract. Must be a valid NameString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.choice_argument: 

       choice_argument
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The argument of the exercised choice. Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.acting_parties: 

       acting_parties
     - :ref:`string <string>`
     - repeated
     - The parties that exercised the choice. Each element must be a valid PartyIdString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.consuming: 

       consuming
     - :ref:`bool <bool>`
     - 
     - If true, the target contract may no longer be exercised. Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.witness_parties: 

       witness_parties
     - :ref:`string <string>`
     - repeated
     - The parties that are notified of this event. The witnesses of an exercise node will depend on whether the exercise was consuming or not. If consuming, the witnesses are the union of the stakeholders and the actors. If not consuming, the witnesses are the union of the signatories and the actors. Note that the actors might not necessarily be observers and thus signatories. This is the case when the controllers of a choice are specified using "flexible controllers", using the ``choice ... controller`` syntax, and said controllers are not explicitly marked as observers. Each element must be a valid PartyIdString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.child_event_ids: 

       child_event_ids
     - :ref:`string <string>`
     - repeated
     - References to further events in the same transaction that appeared as a result of this ``ExercisedEvent``. It contains only the immediate children of this event, not all members of the subtree rooted at this node. The order of the children is the same as the event order in the transaction. Each element must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.ExercisedEvent.exercise_result: 

       exercise_result
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The result of exercising the choice. Required
   



.. _com.daml.ledger.api.v1.InterfaceView:

InterfaceView
===================================================================================================

View of a create event matched by an interface filter.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.InterfaceView.interface_id: 

       interface_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The interface implemented by the matched event. Required
   * - .. _com.daml.ledger.api.v1.InterfaceView.view_status: 

       view_status
     -  `google.rpc.Status <https://cloud.google.com/tasks/docs/reference/rpc/google.rpc#google.rpc.Status>`__
     - 
     - Whether the view was successfully computed, and if not, the reason for the error. The error is reported using the same rules for error codes and messages as the errors returned for API requests. Required
   * - .. _com.daml.ledger.api.v1.InterfaceView.view_value: 

       view_value
     - :ref:`Record <com.daml.ledger.api.v1.Record>`
     - 
     - The value of the interface's view method on this event. Set if it was requested in the ``InterfaceFilter`` and it could be sucessfully computed. Optional
   








.. _com/daml/ledger/api/v1/experimental_features.proto:

com/daml/ledger/api/v1/experimental_features.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.AcsActiveAtOffsetFeature:

AcsActiveAtOffsetFeature
===================================================================================================

Whether the Ledger API supports requesting ACS at an offset

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.AcsActiveAtOffsetFeature.supported: 

       supported
     - :ref:`bool <bool>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.CommandDeduplicationFeatures:

CommandDeduplicationFeatures
===================================================================================================

Feature descriptors for command deduplication intended to be used for adapting Ledger API tests.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationFeatures.deduplication_period_support: 

       deduplication_period_support
     - :ref:`CommandDeduplicationPeriodSupport <com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationFeatures.deduplication_type: 

       deduplication_type
     - :ref:`CommandDeduplicationType <com.daml.ledger.api.v1.CommandDeduplicationType>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationFeatures.max_deduplication_duration_enforced: 

       max_deduplication_duration_enforced
     - :ref:`bool <bool>`
     - 
     - The ledger will reject any requests which specify a deduplication period which exceeds the specified max deduplication duration. This is also enforced for ledgers that convert deduplication periods specified as offsets to durations.
   



.. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport:

CommandDeduplicationPeriodSupport
===================================================================================================

Feature descriptor specifying how deduplication periods can be specified and how they are handled by the participant
node.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.offset_support: 

       offset_support
     - :ref:`CommandDeduplicationPeriodSupport.OffsetSupport <com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.OffsetSupport>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.duration_support: 

       duration_support
     - :ref:`CommandDeduplicationPeriodSupport.DurationSupport <com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.DurationSupport>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.ExperimentalCommitterEventLog:

ExperimentalCommitterEventLog
===================================================================================================

How the committer stores events.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalCommitterEventLog.event_log_type: 

       event_log_type
     - :ref:`ExperimentalCommitterEventLog.CommitterEventLogType <com.daml.ledger.api.v1.ExperimentalCommitterEventLog.CommitterEventLogType>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.ExperimentalContractIds:

ExperimentalContractIds
===================================================================================================

See `daml-lf/spec/contract-id.rst` for more information on contract ID formats.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalContractIds.v1: 

       v1
     - :ref:`ExperimentalContractIds.ContractIdV1Support <com.daml.ledger.api.v1.ExperimentalContractIds.ContractIdV1Support>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.ExperimentalExplicitDisclosure:

ExperimentalExplicitDisclosure
===================================================================================================

Enables the use of explicitly disclosed contracts for command submission

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalExplicitDisclosure.supported: 

       supported
     - :ref:`bool <bool>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.ExperimentalFeatures:

ExperimentalFeatures
===================================================================================================

See the feature message definitions for descriptions.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.self_service_error_codes: 

       self_service_error_codes
     - :ref:`ExperimentalSelfServiceErrorCodes <com.daml.ledger.api.v1.ExperimentalSelfServiceErrorCodes>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.static_time: 

       static_time
     - :ref:`ExperimentalStaticTime <com.daml.ledger.api.v1.ExperimentalStaticTime>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.command_deduplication: 

       command_deduplication
     - :ref:`CommandDeduplicationFeatures <com.daml.ledger.api.v1.CommandDeduplicationFeatures>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.optional_ledger_id: 

       optional_ledger_id
     - :ref:`ExperimentalOptionalLedgerId <com.daml.ledger.api.v1.ExperimentalOptionalLedgerId>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.contract_ids: 

       contract_ids
     - :ref:`ExperimentalContractIds <com.daml.ledger.api.v1.ExperimentalContractIds>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.committer_event_log: 

       committer_event_log
     - :ref:`ExperimentalCommitterEventLog <com.daml.ledger.api.v1.ExperimentalCommitterEventLog>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.explicit_disclosure: 

       explicit_disclosure
     - :ref:`ExperimentalExplicitDisclosure <com.daml.ledger.api.v1.ExperimentalExplicitDisclosure>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.user_and_party_local_metadata_extensions: 

       user_and_party_local_metadata_extensions
     - :ref:`ExperimentalUserAndPartyLocalMetadataExtensions <com.daml.ledger.api.v1.ExperimentalUserAndPartyLocalMetadataExtensions>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.ExperimentalFeatures.acs_active_at_offset: 

       acs_active_at_offset
     - :ref:`AcsActiveAtOffsetFeature <com.daml.ledger.api.v1.AcsActiveAtOffsetFeature>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.ExperimentalOptionalLedgerId:

ExperimentalOptionalLedgerId
===================================================================================================

Ledger API does not require ledgerId to be set in the requests.



.. _com.daml.ledger.api.v1.ExperimentalSelfServiceErrorCodes:

ExperimentalSelfServiceErrorCodes
===================================================================================================

GRPC self-service error codes are returned by the Ledger API.



.. _com.daml.ledger.api.v1.ExperimentalStaticTime:

ExperimentalStaticTime
===================================================================================================

Ledger is in the static time mode and exposes a time service.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalStaticTime.supported: 

       supported
     - :ref:`bool <bool>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.ExperimentalUserAndPartyLocalMetadataExtensions:

ExperimentalUserAndPartyLocalMetadataExtensions
===================================================================================================

Whether the Ledger API supports:
- is_deactivated user property,
- metadata with annotations and resource version for users and parties,
- update calls for users and parties.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalUserAndPartyLocalMetadataExtensions.supported: 

       supported
     - :ref:`bool <bool>`
     - 
     - 
   




.. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.DurationSupport:

CommandDeduplicationPeriodSupport.DurationSupport
===================================================================================================

How the participant node supports deduplication periods specified as durations.

.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.DurationSupport.DURATION_NATIVE_SUPPORT:

       DURATION_NATIVE_SUPPORT
     - 0
     - 
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.DurationSupport.DURATION_CONVERT_TO_OFFSET:

       DURATION_CONVERT_TO_OFFSET
     - 1
     - 
   


.. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.OffsetSupport:

CommandDeduplicationPeriodSupport.OffsetSupport
===================================================================================================

How the participant node supports deduplication periods specified using offsets.

.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.OffsetSupport.OFFSET_NOT_SUPPORTED:

       OFFSET_NOT_SUPPORTED
     - 0
     - 
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.OffsetSupport.OFFSET_NATIVE_SUPPORT:

       OFFSET_NATIVE_SUPPORT
     - 1
     - 
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationPeriodSupport.OffsetSupport.OFFSET_CONVERT_TO_DURATION:

       OFFSET_CONVERT_TO_DURATION
     - 2
     - 
   


.. _com.daml.ledger.api.v1.CommandDeduplicationType:

CommandDeduplicationType
===================================================================================================

How the participant node reports duplicate command submissions.

.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationType.ASYNC_ONLY:

       ASYNC_ONLY
     - 0
     - Duplicate commands are exclusively reported asynchronously via completions.
   * - .. _com.daml.ledger.api.v1.CommandDeduplicationType.ASYNC_AND_CONCURRENT_SYNC:

       ASYNC_AND_CONCURRENT_SYNC
     - 1
     - Commands that are duplicates of concurrently submitted commands are reported synchronously via a gRPC error on the command submission, while all other duplicate commands are reported asynchronously via completions.
   


.. _com.daml.ledger.api.v1.ExperimentalCommitterEventLog.CommitterEventLogType:

ExperimentalCommitterEventLog.CommitterEventLogType
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalCommitterEventLog.CommitterEventLogType.CENTRALIZED:

       CENTRALIZED
     - 0
     - Default. There is a single log.
   * - .. _com.daml.ledger.api.v1.ExperimentalCommitterEventLog.CommitterEventLogType.DISTRIBUTED:

       DISTRIBUTED
     - 1
     - There is more than one event log. Usually, when the committer itself is distributed. Or there are per-participant event logs. It may result in transaction IDs being different for the same transaction across participants, for example.
   


.. _com.daml.ledger.api.v1.ExperimentalContractIds.ContractIdV1Support:

ExperimentalContractIds.ContractIdV1Support
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.ExperimentalContractIds.ContractIdV1Support.SUFFIXED:

       SUFFIXED
     - 0
     - Contract IDs must be suffixed. Distributed ledger implementations must reject non-suffixed contract IDs.
   * - .. _com.daml.ledger.api.v1.ExperimentalContractIds.ContractIdV1Support.NON_SUFFIXED:

       NON_SUFFIXED
     - 1
     - Contract IDs do not need to be suffixed. This can be useful for shorter contract IDs in centralized committer implementations. Suffixed contract IDs must also be supported.
   






.. _com/daml/ledger/api/v1/ledger_configuration_service.proto:

com/daml/ledger/api/v1/ledger_configuration_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.GetLedgerConfigurationRequest:

GetLedgerConfigurationRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetLedgerConfigurationRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   



.. _com.daml.ledger.api.v1.GetLedgerConfigurationResponse:

GetLedgerConfigurationResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetLedgerConfigurationResponse.ledger_configuration: 

       ledger_configuration
     - :ref:`LedgerConfiguration <com.daml.ledger.api.v1.LedgerConfiguration>`
     - 
     - The latest ledger configuration.
   



.. _com.daml.ledger.api.v1.LedgerConfiguration:

LedgerConfiguration
===================================================================================================

LedgerConfiguration contains parameters of the ledger instance that may be useful to clients.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.LedgerConfiguration.max_deduplication_duration: 

       max_deduplication_duration
     -  `google.protobuf.Duration <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Duration>`__
     - 
     - If a command submission specifies a deduplication period of length up to ``max_deduplication_duration``, the submission SHOULD not be rejected with ``FAILED_PRECONDITION`` because the deduplication period starts too early. The deduplication period is measured on a local clock of the participant or Daml ledger, and therefore subject to clock skews and clock drifts. Command submissions with longer periods MAY get accepted though.
   






.. _com.daml.ledger.api.v1.LedgerConfigurationService:

LedgerConfigurationService
===================================================================================================

LedgerConfigurationService allows clients to subscribe to changes of the ledger configuration.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetLedgerConfiguration
     - :ref:`GetLedgerConfigurationRequest <com.daml.ledger.api.v1.GetLedgerConfigurationRequest>`
     - :ref:`GetLedgerConfigurationResponse <com.daml.ledger.api.v1.GetLedgerConfigurationResponse>`
     - Returns the latest configuration as the first response, and publishes configuration updates in the same stream.
   



.. _com/daml/ledger/api/v1/ledger_identity_service.proto:

com/daml/ledger/api/v1/ledger_identity_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.GetLedgerIdentityRequest:

GetLedgerIdentityRequest
===================================================================================================





.. _com.daml.ledger.api.v1.GetLedgerIdentityResponse:

GetLedgerIdentityResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetLedgerIdentityResponse.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - The ID of the ledger exposed by the server. Must be a valid LedgerString (as described in ``value.proto``). Optional
   






.. _com.daml.ledger.api.v1.LedgerIdentityService:

LedgerIdentityService
===================================================================================================

DEPRECATED: This service is now deprecated and ledger identity string is optional for all Ledger API requests.

Allows clients to verify that the server they are communicating with exposes the ledger they wish to operate on.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetLedgerIdentity
     - :ref:`GetLedgerIdentityRequest <com.daml.ledger.api.v1.GetLedgerIdentityRequest>`
     - :ref:`GetLedgerIdentityResponse <com.daml.ledger.api.v1.GetLedgerIdentityResponse>`
     - Clients may call this RPC to return the identifier of the ledger they are connected to.
   



.. _com/daml/ledger/api/v1/ledger_offset.proto:

com/daml/ledger/api/v1/ledger_offset.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.LedgerOffset:

LedgerOffset
===================================================================================================

Describes a specific point on the ledger.

The Ledger API endpoints that take offsets allow to specify portions
of the ledger that are relevant for the client to read.

Offsets returned by the Ledger API can be used as-is (e.g.
to keep track of processed transactions and provide a restart
point to use in case of need).

The format of absolute offsets is opaque to the client: no
client-side transformation of an offset is guaranteed
to return a meaningful offset.

The server implementation ensures internally that offsets
are lexicographically comparable.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.LedgerOffset.absolute: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ value.absolute
     - :ref:`string <string>`
     - 
     - The format of this string is specific to the ledger and opaque to the client.
   * - .. _com.daml.ledger.api.v1.LedgerOffset.boundary: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ value.boundary
     - :ref:`LedgerOffset.LedgerBoundary <com.daml.ledger.api.v1.LedgerOffset.LedgerBoundary>`
     - 
     - 
   




.. _com.daml.ledger.api.v1.LedgerOffset.LedgerBoundary:

LedgerOffset.LedgerBoundary
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.LedgerOffset.LedgerBoundary.LEDGER_BEGIN:

       LEDGER_BEGIN
     - 0
     - Refers to the first transaction.
   * - .. _com.daml.ledger.api.v1.LedgerOffset.LedgerBoundary.LEDGER_END:

       LEDGER_END
     - 1
     - Refers to the currently last transaction, which is a moving target.
   






.. _com/daml/ledger/api/v1/package_service.proto:

com/daml/ledger/api/v1/package_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.GetPackageRequest:

GetPackageRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetPackageRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.GetPackageRequest.package_id: 

       package_id
     - :ref:`string <string>`
     - 
     - The ID of the requested package. Must be a valid PackageIdString (as described in ``value.proto``). Required
   



.. _com.daml.ledger.api.v1.GetPackageResponse:

GetPackageResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetPackageResponse.hash_function: 

       hash_function
     - :ref:`HashFunction <com.daml.ledger.api.v1.HashFunction>`
     - 
     - The hash function we use to calculate the hash. Required
   * - .. _com.daml.ledger.api.v1.GetPackageResponse.archive_payload: 

       archive_payload
     - :ref:`bytes <bytes>`
     - 
     - Contains a ``daml_lf`` ArchivePayload. See further details in ``daml_lf.proto``. Required
   * - .. _com.daml.ledger.api.v1.GetPackageResponse.hash: 

       hash
     - :ref:`string <string>`
     - 
     - The hash of the archive payload, can also used as a ``package_id``. Must be a valid PackageIdString (as described in ``value.proto``). Required
   



.. _com.daml.ledger.api.v1.GetPackageStatusRequest:

GetPackageStatusRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetPackageStatusRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.GetPackageStatusRequest.package_id: 

       package_id
     - :ref:`string <string>`
     - 
     - The ID of the requested package. Must be a valid PackageIdString (as described in ``value.proto``). Required
   



.. _com.daml.ledger.api.v1.GetPackageStatusResponse:

GetPackageStatusResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetPackageStatusResponse.package_status: 

       package_status
     - :ref:`PackageStatus <com.daml.ledger.api.v1.PackageStatus>`
     - 
     - The status of the package.
   



.. _com.daml.ledger.api.v1.ListPackagesRequest:

ListPackagesRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ListPackagesRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   



.. _com.daml.ledger.api.v1.ListPackagesResponse:

ListPackagesResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.ListPackagesResponse.package_ids: 

       package_ids
     - :ref:`string <string>`
     - repeated
     - The IDs of all Daml-LF packages supported by the server. Each element must be a valid PackageIdString (as described in ``value.proto``). Required
   




.. _com.daml.ledger.api.v1.HashFunction:

HashFunction
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.HashFunction.SHA256:

       SHA256
     - 0
     - 
   


.. _com.daml.ledger.api.v1.PackageStatus:

PackageStatus
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Name
     - Number
     - Description
   * - .. _com.daml.ledger.api.v1.PackageStatus.UNKNOWN:

       UNKNOWN
     - 0
     - The server is not aware of such a package.
   * - .. _com.daml.ledger.api.v1.PackageStatus.REGISTERED:

       REGISTERED
     - 1
     - The server is able to execute Daml commands operating on this package.
   




.. _com.daml.ledger.api.v1.PackageService:

PackageService
===================================================================================================

Allows clients to query the Daml-LF packages that are supported by the server.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - ListPackages
     - :ref:`ListPackagesRequest <com.daml.ledger.api.v1.ListPackagesRequest>`
     - :ref:`ListPackagesResponse <com.daml.ledger.api.v1.ListPackagesResponse>`
     - Returns the identifiers of all supported packages.
   * - GetPackage
     - :ref:`GetPackageRequest <com.daml.ledger.api.v1.GetPackageRequest>`
     - :ref:`GetPackageResponse <com.daml.ledger.api.v1.GetPackageResponse>`
     - Returns the contents of a single package.
   * - GetPackageStatus
     - :ref:`GetPackageStatusRequest <com.daml.ledger.api.v1.GetPackageStatusRequest>`
     - :ref:`GetPackageStatusResponse <com.daml.ledger.api.v1.GetPackageStatusResponse>`
     - Returns the status of a single package.
   



.. _com/daml/ledger/api/v1/testing/time_service.proto:

com/daml/ledger/api/v1/testing/time_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.testing.GetTimeRequest:

GetTimeRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.testing.GetTimeRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as describe in ``value.proto``). Optional
   



.. _com.daml.ledger.api.v1.testing.GetTimeResponse:

GetTimeResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.testing.GetTimeResponse.current_time: 

       current_time
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - The current time according to the ledger server.
   



.. _com.daml.ledger.api.v1.testing.SetTimeRequest:

SetTimeRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.testing.SetTimeRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as describe in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.testing.SetTimeRequest.current_time: 

       current_time
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - MUST precisely match the current time as it's known to the ledger server.
   * - .. _com.daml.ledger.api.v1.testing.SetTimeRequest.new_time: 

       new_time
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - The time the client wants to set on the ledger. MUST be a point int time after ``current_time``.
   






.. _com.daml.ledger.api.v1.testing.TimeService:

TimeService
===================================================================================================

Optional service, exposed for testing static time scenarios.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetTime
     - :ref:`GetTimeRequest <com.daml.ledger.api.v1.testing.GetTimeRequest>`
     - :ref:`GetTimeResponse <com.daml.ledger.api.v1.testing.GetTimeResponse>`
     - Returns a stream of time updates. Always returns at least one response, where the first one is the current time. Subsequent responses are emitted whenever the ledger server's time is updated.
   * - SetTime
     - :ref:`SetTimeRequest <com.daml.ledger.api.v1.testing.SetTimeRequest>`
     -  `.google.protobuf.Empty <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Empty>`__
     - Allows clients to change the ledger's clock in an atomic get-and-set operation.
   



.. _com/daml/ledger/api/v1/transaction.proto:

com/daml/ledger/api/v1/transaction.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.Transaction:

Transaction
===================================================================================================

Filtered view of an on-ledger transaction's create and archive events.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Transaction.transaction_id: 

       transaction_id
     - :ref:`string <string>`
     - 
     - Assigned by the server. Useful for correlating logs. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.Transaction.command_id: 

       command_id
     - :ref:`string <string>`
     - 
     - The ID of the command which resulted in this transaction. Missing for everyone except the submitting party. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.Transaction.workflow_id: 

       workflow_id
     - :ref:`string <string>`
     - 
     - The workflow ID used in command submission. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.Transaction.effective_at: 

       effective_at
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - Ledger effective time. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.Transaction.events: 

       events
     - :ref:`Event <com.daml.ledger.api.v1.Event>`
     - repeated
     - The collection of events. Only contains ``CreatedEvent`` or ``ArchivedEvent``. Required
   * - .. _com.daml.ledger.api.v1.Transaction.offset: 

       offset
     - :ref:`string <string>`
     - 
     - The absolute offset. The format of this field is described in ``ledger_offset.proto``. Required
   



.. _com.daml.ledger.api.v1.TransactionTree:

TransactionTree
===================================================================================================

Complete view of an on-ledger transaction.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.TransactionTree.transaction_id: 

       transaction_id
     - :ref:`string <string>`
     - 
     - Assigned by the server. Useful for correlating logs. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.TransactionTree.command_id: 

       command_id
     - :ref:`string <string>`
     - 
     - The ID of the command which resulted in this transaction. Missing for everyone except the submitting party. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.TransactionTree.workflow_id: 

       workflow_id
     - :ref:`string <string>`
     - 
     - The workflow ID used in command submission. Only set if the ``workflow_id`` for the command was set. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.TransactionTree.effective_at: 

       effective_at
     -  `google.protobuf.Timestamp <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Timestamp>`__
     - 
     - Ledger effective time. Required
   * - .. _com.daml.ledger.api.v1.TransactionTree.offset: 

       offset
     - :ref:`string <string>`
     - 
     - The absolute offset. The format of this field is described in ``ledger_offset.proto``. Required
   * - .. _com.daml.ledger.api.v1.TransactionTree.events_by_id: 

       events_by_id
     - :ref:`TransactionTree.EventsByIdEntry <com.daml.ledger.api.v1.TransactionTree.EventsByIdEntry>`
     - repeated
     - Changes to the ledger that were caused by this transaction. Nodes of the transaction tree. Each key be a valid LedgerString (as describe in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.TransactionTree.root_event_ids: 

       root_event_ids
     - :ref:`string <string>`
     - repeated
     - Roots of the transaction tree. Each element must be a valid LedgerString (as describe in ``value.proto``). The elements are in the same order as the commands in the corresponding Commands object that triggered this transaction. Required
   



.. _com.daml.ledger.api.v1.TransactionTree.EventsByIdEntry:

TransactionTree.EventsByIdEntry
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.TransactionTree.EventsByIdEntry.key: 

       key
     - :ref:`string <string>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.TransactionTree.EventsByIdEntry.value: 

       value
     - :ref:`TreeEvent <com.daml.ledger.api.v1.TreeEvent>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.TreeEvent:

TreeEvent
===================================================================================================

Each tree event message type below contains a ``witness_parties`` field which
indicates the subset of the requested parties that can see the event
in question.

Note that transaction trees might contain events with
_no_ witness parties, which were included simply because they were
children of events which have witnesses.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.TreeEvent.created: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ kind.created
     - :ref:`CreatedEvent <com.daml.ledger.api.v1.CreatedEvent>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.TreeEvent.exercised: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ kind.exercised
     - :ref:`ExercisedEvent <com.daml.ledger.api.v1.ExercisedEvent>`
     - 
     - 
   








.. _com/daml/ledger/api/v1/transaction_filter.proto:

com/daml/ledger/api/v1/transaction_filter.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.Filters:

Filters
===================================================================================================

The union of a set of contract filters, or a wildcard.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Filters.inclusive: 

       inclusive
     - :ref:`InclusiveFilters <com.daml.ledger.api.v1.InclusiveFilters>`
     - 
     - If set, then contracts matching any of the ``InclusiveFilters`` match this filter. If not set, or if ``InclusiveFilters`` has empty ``template_ids`` and empty ``interface_filters``: any contract matches this filter. Optional
   



.. _com.daml.ledger.api.v1.InclusiveFilters:

InclusiveFilters
===================================================================================================

A filter that matches all contracts that are either an instance of one of
the ``template_ids`` or that match one of the ``interface_filters``.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.InclusiveFilters.template_ids: 

       template_ids
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - repeated
     - A collection of templates for which the payload will be included in the ``create_arguments`` of a matching ``CreatedEvent``. SHOULD NOT contain duplicates. All ``template_ids`` needs to be valid: corresponding template should be defined in one of the available packages at the time of the query. Optional
   * - .. _com.daml.ledger.api.v1.InclusiveFilters.interface_filters: 

       interface_filters
     - :ref:`InterfaceFilter <com.daml.ledger.api.v1.InterfaceFilter>`
     - repeated
     - Include an ``InterfaceView`` for every ``InterfaceFilter`` matching a contract. The ``InterfaceFilter``s MUST use unique ``interface_id``s. All ``interface_id`` needs to be valid: corresponding interface should be defined in one of the available packages at the time of the query. Optional
   



.. _com.daml.ledger.api.v1.InterfaceFilter:

InterfaceFilter
===================================================================================================

This filter matches contracts that implement a specific interface.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.InterfaceFilter.interface_id: 

       interface_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - The interface that a matching contract must implement. Required
   * - .. _com.daml.ledger.api.v1.InterfaceFilter.include_interface_view: 

       include_interface_view
     - :ref:`bool <bool>`
     - 
     - Whether to include the interface view on the contract in the returned ``CreateEvent``. Use this to access contract data in a uniform manner in your API client. Optional
   * - .. _com.daml.ledger.api.v1.InterfaceFilter.include_create_arguments_blob: 

       include_create_arguments_blob
     - :ref:`bool <bool>`
     - 
     - Whether to include a ``create_arguments_blob`` in the returned ``CreateEvent``. Use this to access the complete contract data in your API client for submitting it as a disclosed contract with future commands. Optional
   



.. _com.daml.ledger.api.v1.TransactionFilter:

TransactionFilter
===================================================================================================

A filter both for filtering create and archive events as well as for
filtering transaction trees.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.TransactionFilter.filters_by_party: 

       filters_by_party
     - :ref:`TransactionFilter.FiltersByPartyEntry <com.daml.ledger.api.v1.TransactionFilter.FiltersByPartyEntry>`
     - repeated
     - Each key must be a valid PartyIdString (as described in ``value.proto``). The interpretation of the filter depends on the stream being filtered: (1) For **transaction tree streams** only party filters with wildcards are allowed, and all subtrees whose root has one of the listed parties as an informee are returned. (2) For **transaction and active-contract-set streams** create and archive events are returned for all contracts whose stakeholders include at least one of the listed parties and match the per-party filter. Required
   



.. _com.daml.ledger.api.v1.TransactionFilter.FiltersByPartyEntry:

TransactionFilter.FiltersByPartyEntry
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.TransactionFilter.FiltersByPartyEntry.key: 

       key
     - :ref:`string <string>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.TransactionFilter.FiltersByPartyEntry.value: 

       value
     - :ref:`Filters <com.daml.ledger.api.v1.Filters>`
     - 
     - 
   








.. _com/daml/ledger/api/v1/transaction_service.proto:

com/daml/ledger/api/v1/transaction_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.GetFlatTransactionResponse:

GetFlatTransactionResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetFlatTransactionResponse.transaction: 

       transaction
     - :ref:`Transaction <com.daml.ledger.api.v1.Transaction>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.GetLedgerEndRequest:

GetLedgerEndRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetLedgerEndRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as describe in ``value.proto``). Optional
   



.. _com.daml.ledger.api.v1.GetLedgerEndResponse:

GetLedgerEndResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetLedgerEndResponse.offset: 

       offset
     - :ref:`LedgerOffset <com.daml.ledger.api.v1.LedgerOffset>`
     - 
     - The absolute offset of the current ledger end.
   



.. _com.daml.ledger.api.v1.GetTransactionByEventIdRequest:

GetTransactionByEventIdRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetTransactionByEventIdRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.GetTransactionByEventIdRequest.event_id: 

       event_id
     - :ref:`string <string>`
     - 
     - The ID of a particular event. Must be a valid LedgerString (as described in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.GetTransactionByEventIdRequest.requesting_parties: 

       requesting_parties
     - :ref:`string <string>`
     - repeated
     - The parties whose events the client expects to see. Events that are not visible for the parties in this collection will not be present in the response. Each element must be a valid PartyIdString (as described in ``value.proto``). Required
   



.. _com.daml.ledger.api.v1.GetTransactionByIdRequest:

GetTransactionByIdRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetTransactionByIdRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as describe in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.GetTransactionByIdRequest.transaction_id: 

       transaction_id
     - :ref:`string <string>`
     - 
     - The ID of a particular transaction. Must be a valid LedgerString (as describe in ``value.proto``). Required
   * - .. _com.daml.ledger.api.v1.GetTransactionByIdRequest.requesting_parties: 

       requesting_parties
     - :ref:`string <string>`
     - repeated
     - The parties whose events the client expects to see. Events that are not visible for the parties in this collection will not be present in the response. Each element be a valid PartyIdString (as describe in ``value.proto``). Required
   



.. _com.daml.ledger.api.v1.GetTransactionResponse:

GetTransactionResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetTransactionResponse.transaction: 

       transaction
     - :ref:`TransactionTree <com.daml.ledger.api.v1.TransactionTree>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.GetTransactionTreesResponse:

GetTransactionTreesResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetTransactionTreesResponse.transactions: 

       transactions
     - :ref:`TransactionTree <com.daml.ledger.api.v1.TransactionTree>`
     - repeated
     - The list of transaction trees that matches the filter in ``GetTransactionsRequest`` for the ``GetTransactionTrees`` method.
   



.. _com.daml.ledger.api.v1.GetTransactionsRequest:

GetTransactionsRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetTransactionsRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   * - .. _com.daml.ledger.api.v1.GetTransactionsRequest.begin: 

       begin
     - :ref:`LedgerOffset <com.daml.ledger.api.v1.LedgerOffset>`
     - 
     - Beginning of the requested ledger section. This offset is exclusive: the response will only contain transactions whose offset is strictly greater than this. Required
   * - .. _com.daml.ledger.api.v1.GetTransactionsRequest.end: 

       end
     - :ref:`LedgerOffset <com.daml.ledger.api.v1.LedgerOffset>`
     - 
     - End of the requested ledger section. This offset is inclusive: the response will only contain transactions whose offset is less than or equal to this. Optional, if not set, the stream will not terminate.
   * - .. _com.daml.ledger.api.v1.GetTransactionsRequest.filter: 

       filter
     - :ref:`TransactionFilter <com.daml.ledger.api.v1.TransactionFilter>`
     - 
     - Requesting parties with template filters. Template filters must be empty for GetTransactionTrees requests. Required
   * - .. _com.daml.ledger.api.v1.GetTransactionsRequest.verbose: 

       verbose
     - :ref:`bool <bool>`
     - 
     - If enabled, values served over the API will contain more information than strictly necessary to interpret the data. In particular, setting the verbose flag to true triggers the ledger to include labels for record fields. Optional
   



.. _com.daml.ledger.api.v1.GetTransactionsResponse:

GetTransactionsResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetTransactionsResponse.transactions: 

       transactions
     - :ref:`Transaction <com.daml.ledger.api.v1.Transaction>`
     - repeated
     - The list of transactions that matches the filter in GetTransactionsRequest for the GetTransactions method.
   






.. _com.daml.ledger.api.v1.TransactionService:

TransactionService
===================================================================================================

Allows clients to read transactions from the ledger.

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetTransactions
     - :ref:`GetTransactionsRequest <com.daml.ledger.api.v1.GetTransactionsRequest>`
     - :ref:`GetTransactionsResponse <com.daml.ledger.api.v1.GetTransactionsResponse>`
     - Read the ledger's filtered transaction stream for a set of parties. Lists only creates and archives, but not other events. Omits all events on transient contracts, i.e., contracts that were both created and archived in the same transaction.
   * - GetTransactionTrees
     - :ref:`GetTransactionsRequest <com.daml.ledger.api.v1.GetTransactionsRequest>`
     - :ref:`GetTransactionTreesResponse <com.daml.ledger.api.v1.GetTransactionTreesResponse>`
     - Read the ledger's complete transaction tree stream for a set of parties. The stream can be filtered only by parties, but not templates (template filter must be empty).
   * - GetTransactionByEventId
     - :ref:`GetTransactionByEventIdRequest <com.daml.ledger.api.v1.GetTransactionByEventIdRequest>`
     - :ref:`GetTransactionResponse <com.daml.ledger.api.v1.GetTransactionResponse>`
     - Lookup a transaction tree by the ID of an event that appears within it. For looking up a transaction instead of a transaction tree, please see GetFlatTransactionByEventId
   * - GetTransactionById
     - :ref:`GetTransactionByIdRequest <com.daml.ledger.api.v1.GetTransactionByIdRequest>`
     - :ref:`GetTransactionResponse <com.daml.ledger.api.v1.GetTransactionResponse>`
     - Lookup a transaction tree by its ID. For looking up a transaction instead of a transaction tree, please see GetFlatTransactionById
   * - GetFlatTransactionByEventId
     - :ref:`GetTransactionByEventIdRequest <com.daml.ledger.api.v1.GetTransactionByEventIdRequest>`
     - :ref:`GetFlatTransactionResponse <com.daml.ledger.api.v1.GetFlatTransactionResponse>`
     - Lookup a transaction by the ID of an event that appears within it.
   * - GetFlatTransactionById
     - :ref:`GetTransactionByIdRequest <com.daml.ledger.api.v1.GetTransactionByIdRequest>`
     - :ref:`GetFlatTransactionResponse <com.daml.ledger.api.v1.GetFlatTransactionResponse>`
     - Lookup a transaction by its ID.
   * - GetLedgerEnd
     - :ref:`GetLedgerEndRequest <com.daml.ledger.api.v1.GetLedgerEndRequest>`
     - :ref:`GetLedgerEndResponse <com.daml.ledger.api.v1.GetLedgerEndResponse>`
     - Get the current ledger end. Subscriptions started with the returned offset will serve transactions created after this RPC was called.
   



.. _com/daml/ledger/api/v1/value.proto:

com/daml/ledger/api/v1/value.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.Enum:

Enum
===================================================================================================

A value with finite set of alternative representations.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Enum.enum_id: 

       enum_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - Omitted from the transaction stream when verbose streaming is not enabled. Optional when submitting commands.
   * - .. _com.daml.ledger.api.v1.Enum.constructor: 

       constructor
     - :ref:`string <string>`
     - 
     - Determines which of the Variant's alternatives is encoded in this message. Must be a valid NameString. Required
   



.. _com.daml.ledger.api.v1.GenMap:

GenMap
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GenMap.entries: 

       entries
     - :ref:`GenMap.Entry <com.daml.ledger.api.v1.GenMap.Entry>`
     - repeated
     - 
   



.. _com.daml.ledger.api.v1.GenMap.Entry:

GenMap.Entry
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GenMap.Entry.key: 

       key
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.GenMap.Entry.value: 

       value
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.Identifier:

Identifier
===================================================================================================

Unique identifier of an entity.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Identifier.package_id: 

       package_id
     - :ref:`string <string>`
     - 
     - The identifier of the Daml package that contains the entity. Must be a valid PackageIdString. Required
   * - .. _com.daml.ledger.api.v1.Identifier.module_name: 

       module_name
     - :ref:`string <string>`
     - 
     - The dot-separated module name of the identifier. Required
   * - .. _com.daml.ledger.api.v1.Identifier.entity_name: 

       entity_name
     - :ref:`string <string>`
     - 
     - The dot-separated name of the entity (e.g. record, template, ...) within the module. Required
   



.. _com.daml.ledger.api.v1.List:

List
===================================================================================================

A homogenous collection of values.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.List.elements: 

       elements
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - repeated
     - The elements must all be of the same concrete value type. Optional
   



.. _com.daml.ledger.api.v1.Map:

Map
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Map.entries: 

       entries
     - :ref:`Map.Entry <com.daml.ledger.api.v1.Map.Entry>`
     - repeated
     - 
   



.. _com.daml.ledger.api.v1.Map.Entry:

Map.Entry
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Map.Entry.key: 

       key
     - :ref:`string <string>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Map.Entry.value: 

       value
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - 
   



.. _com.daml.ledger.api.v1.Optional:

Optional
===================================================================================================

Corresponds to Java's Optional type, Scala's Option, and Haskell's Maybe.
The reason why we need to wrap this in an additional ``message`` is that we
need to be able to encode the ``None`` case in the ``Value`` oneof.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Optional.value: 

       value
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - optional
   



.. _com.daml.ledger.api.v1.Record:

Record
===================================================================================================

Contains nested values.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Record.record_id: 

       record_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - Omitted from the transaction stream when verbose streaming is not enabled. Optional when submitting commands.
   * - .. _com.daml.ledger.api.v1.Record.fields: 

       fields
     - :ref:`RecordField <com.daml.ledger.api.v1.RecordField>`
     - repeated
     - The nested values of the record. Required
   



.. _com.daml.ledger.api.v1.RecordField:

RecordField
===================================================================================================

A named nested value within a record.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.RecordField.label: 

       label
     - :ref:`string <string>`
     - 
     - When reading a transaction stream, it's omitted if verbose streaming is not enabled. When submitting a commmand, it's optional: - if all keys within a single record are present, the order in which fields appear does not matter. however, each key must appear exactly once. - if any of the keys within a single record are omitted, the order of fields MUST match the order of declaration in the Daml template. Must be a valid NameString
   * - .. _com.daml.ledger.api.v1.RecordField.value: 

       value
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - A nested value of a record. Required
   



.. _com.daml.ledger.api.v1.Value:

Value
===================================================================================================

Encodes values that the ledger accepts as command arguments and emits as contract arguments.

The values encoding use different classes of non-empty strings as identifiers. Those classes are
defined as follows:
- NameStrings are strings with length <= 1000 that match the regexp ``[A-Za-z\$_][A-Za-z0-9\$_]*``.
- PackageIdStrings are strings with length <= 64 that match the regexp ``[A-Za-z0-9\-_ ]+``.
- PartyIdStrings are strings with length <= 256 that match the regexp ``[A-Za-z0-9:\-_ ]+``.
- LedgerStrings are strings with length <= 256 that match the regexp ``[A-Za-z0-9#:\-_/ ]+``.
- ApplicationIdStrings are strings with length <= 256 that match the regexp ``[A-Za-z0-9#:\-_/ @\|]+``.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Value.record: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.record
     - :ref:`Record <com.daml.ledger.api.v1.Record>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Value.variant: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.variant
     - :ref:`Variant <com.daml.ledger.api.v1.Variant>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Value.contract_id: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.contract_id
     - :ref:`string <string>`
     - 
     - Identifier of an on-ledger contract. Commands which reference an unknown or already archived contract ID will fail. Must be a valid LedgerString.
   * - .. _com.daml.ledger.api.v1.Value.list: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.list
     - :ref:`List <com.daml.ledger.api.v1.List>`
     - 
     - Represents a homogeneous list of values.
   * - .. _com.daml.ledger.api.v1.Value.int64: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.int64
     - :ref:`sint64 <sint64>`
     - 
     - 
   * - .. _com.daml.ledger.api.v1.Value.numeric: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.numeric
     - :ref:`string <string>`
     - 
     - A Numeric, that is a decimal value with precision 38 (at most 38 significant digits) and a scale between 0 and 37 (significant digits on the right of the decimal point). The field has to match the regex [+-]?\d{1,38}(.\d{0,37})? and should be representable by a Numeric without loss of precision.
   * - .. _com.daml.ledger.api.v1.Value.text: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.text
     - :ref:`string <string>`
     - 
     - A string.
   * - .. _com.daml.ledger.api.v1.Value.timestamp: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.timestamp
     - :ref:`sfixed64 <sfixed64>`
     - 
     - Microseconds since the UNIX epoch. Can go backwards. Fixed since the vast majority of values will be greater than 2^28, since currently the number of microseconds since the epoch is greater than that. Range: 0001-01-01T00:00:00Z to 9999-12-31T23:59:59.999999Z, so that we can convert to/from https://www.ietf.org/rfc/rfc3339.txt
   * - .. _com.daml.ledger.api.v1.Value.party: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.party
     - :ref:`string <string>`
     - 
     - An agent operating on the ledger. Must be a valid PartyIdString.
   * - .. _com.daml.ledger.api.v1.Value.bool: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.bool
     - :ref:`bool <bool>`
     - 
     - True or false.
   * - .. _com.daml.ledger.api.v1.Value.unit: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.unit
     -  `google.protobuf.Empty <https://developers.google.com/protocol-buffers/docs/reference/google.protobuf#google.protobuf.Empty>`__
     - 
     - This value is used for example for choices that don't take any arguments.
   * - .. _com.daml.ledger.api.v1.Value.date: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.date
     - :ref:`int32 <int32>`
     - 
     - Days since the unix epoch. Can go backwards. Limited from 0001-01-01 to 9999-12-31, also to be compatible with https://www.ietf.org/rfc/rfc3339.txt
   * - .. _com.daml.ledger.api.v1.Value.optional: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.optional
     - :ref:`Optional <com.daml.ledger.api.v1.Optional>`
     - 
     - The Optional type, None or Some
   * - .. _com.daml.ledger.api.v1.Value.map: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.map
     - :ref:`Map <com.daml.ledger.api.v1.Map>`
     - 
     - The Map type
   * - .. _com.daml.ledger.api.v1.Value.enum: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.enum
     - :ref:`Enum <com.daml.ledger.api.v1.Enum>`
     - 
     - The Enum type
   * - .. _com.daml.ledger.api.v1.Value.gen_map: 

       `oneof <https://developers.google.com/protocol-buffers/docs/proto3#oneof>`_ Sum.gen_map
     - :ref:`GenMap <com.daml.ledger.api.v1.GenMap>`
     - 
     - The GenMap type
   



.. _com.daml.ledger.api.v1.Variant:

Variant
===================================================================================================

A value with alternative representations.

.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.Variant.variant_id: 

       variant_id
     - :ref:`Identifier <com.daml.ledger.api.v1.Identifier>`
     - 
     - Omitted from the transaction stream when verbose streaming is not enabled. Optional when submitting commands.
   * - .. _com.daml.ledger.api.v1.Variant.constructor: 

       constructor
     - :ref:`string <string>`
     - 
     - Determines which of the Variant's alternatives is encoded in this message. Must be a valid NameString. Required
   * - .. _com.daml.ledger.api.v1.Variant.value: 

       value
     - :ref:`Value <com.daml.ledger.api.v1.Value>`
     - 
     - The value encoded within the Variant. Required
   








.. _com/daml/ledger/api/v1/version_service.proto:

com/daml/ledger/api/v1/version_service.proto
***************************************************************************************************



.. _com.daml.ledger.api.v1.FeaturesDescriptor:

FeaturesDescriptor
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.FeaturesDescriptor.user_management: 

       user_management
     - :ref:`UserManagementFeature <com.daml.ledger.api.v1.UserManagementFeature>`
     - 
     - If set, then the Ledger API server supports user management. It is recommended that clients query this field to gracefully adjust their behavior for ledgers that do not support user management.
   * - .. _com.daml.ledger.api.v1.FeaturesDescriptor.experimental: 

       experimental
     - :ref:`ExperimentalFeatures <com.daml.ledger.api.v1.ExperimentalFeatures>`
     - 
     - Features under development or features that are used for ledger implementation testing purposes only.

Daml applications SHOULD not depend on these in production.
   



.. _com.daml.ledger.api.v1.GetLedgerApiVersionRequest:

GetLedgerApiVersionRequest
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetLedgerApiVersionRequest.ledger_id: 

       ledger_id
     - :ref:`string <string>`
     - 
     - Must correspond to the ledger ID reported by the Ledger Identification Service. Must be a valid LedgerString (as described in ``value.proto``). Optional
   



.. _com.daml.ledger.api.v1.GetLedgerApiVersionResponse:

GetLedgerApiVersionResponse
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.GetLedgerApiVersionResponse.version: 

       version
     - :ref:`string <string>`
     - 
     - The version of the ledger API.
   * - .. _com.daml.ledger.api.v1.GetLedgerApiVersionResponse.features: 

       features
     - :ref:`FeaturesDescriptor <com.daml.ledger.api.v1.FeaturesDescriptor>`
     - 
     - The features supported by this Ledger API endpoint.

Daml applications CAN use the feature descriptor on top of version constraints on the Ledger API version to determine whether a given Ledger API endpoint supports the features required to run the application.

See the feature descriptions themselves for the relation between Ledger API versions and feature presence.
   



.. _com.daml.ledger.api.v1.UserManagementFeature:

UserManagementFeature
===================================================================================================



.. list-table::
   :header-rows: 1

   * - Field
     - Type
     - Label
     - Description
   * - .. _com.daml.ledger.api.v1.UserManagementFeature.supported: 

       supported
     - :ref:`bool <bool>`
     - 
     - Whether the Ledger API server provides the user management service.
   * - .. _com.daml.ledger.api.v1.UserManagementFeature.max_rights_per_user: 

       max_rights_per_user
     - :ref:`int32 <int32>`
     - 
     - The maximum number of rights that can be assigned to a single user. Servers MUST support at least 100 rights per user. A value of 0 means that the server enforces no rights per user limit.
   * - .. _com.daml.ledger.api.v1.UserManagementFeature.max_users_page_size: 

       max_users_page_size
     - :ref:`int32 <int32>`
     - 
     - The maximum number of users the server can return in a single response (page). Servers MUST support at least a 100 users per page. A value of 0 means that the server enforces no page size limit.
   






.. _com.daml.ledger.api.v1.VersionService:

VersionService
===================================================================================================

Allows clients to retrieve information about the ledger API version

.. list-table::
   :header-rows: 1

   * - Method name
     - Request type
     - Response type
     - Description
   * - GetLedgerApiVersion
     - :ref:`GetLedgerApiVersionRequest <com.daml.ledger.api.v1.GetLedgerApiVersionRequest>`
     - :ref:`GetLedgerApiVersionResponse <com.daml.ledger.api.v1.GetLedgerApiVersionResponse>`
     - Read the Ledger API version
   



.. _scalarvaluetypes:

Scalar Value Types
***************************************************************************************************

.. list-table::
   :header-rows: 1

   * - .proto type
     - Notes
     - C++ type
     - Java type
     - Python type
   * - .. _double: 

       double
     - 
     - double
     - double
     - float
   * - .. _float: 

       float
     - 
     - float
     - float
     - float
   * - .. _int32: 

       int32
     - Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint32 instead.
     - int32
     - int
     - int
   * - .. _int64: 

       int64
     - Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint64 instead.
     - int64
     - long
     - int/long
   * - .. _uint32: 

       uint32
     - Uses variable-length encoding.
     - uint32
     - int
     - int/long
   * - .. _uint64: 

       uint64
     - Uses variable-length encoding.
     - uint64
     - long
     - int/long
   * - .. _sint32: 

       sint32
     - Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int32s.
     - int32
     - int
     - int
   * - .. _sint64: 

       sint64
     - Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int64s.
     - int64
     - long
     - int/long
   * - .. _fixed32: 

       fixed32
     - Always four bytes. More efficient than uint32 if values are often greater than 2^28.
     - uint32
     - int
     - int
   * - .. _fixed64: 

       fixed64
     - Always eight bytes. More efficient than uint64 if values are often greater than 2^56.
     - uint64
     - long
     - int/long
   * - .. _sfixed32: 

       sfixed32
     - Always four bytes.
     - int32
     - int
     - int
   * - .. _sfixed64: 

       sfixed64
     - Always eight bytes.
     - int64
     - long
     - int/long
   * - .. _bool: 

       bool
     - 
     - bool
     - boolean
     - boolean
   * - .. _string: 

       string
     - A string must always contain UTF-8 encoded or 7-bit ASCII text.
     - string
     - String
     - str/unicode
   * - .. _bytes: 

       bytes
     - May contain any arbitrary sequence of bytes.
     - string
     - ByteString
     - str
   
