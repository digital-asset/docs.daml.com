.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _json-api:

HTTP JSON API Service V2
#####################

This section describes the new JSON API Service that is a part of Canton 3.2. If you are looking for legacy JSON API, please navigate to :doc:`JSON API V1 </json-api/v1/index>`

The **JSON API** provides a way to interact with a ledger using http/json protocol instead of gRPC
:doc:`the Ledger API </app-dev/ledger-api>`.
The JSON API provides almost all the functionality available by the gRPC API, although the HTTP protocol imposes some minor limitations.

The full reference consists of:
    * :doc:`openapi`
    * :doc:`asyncapi`
    * :doc:`the Ledger API </app-dev/ledger-api>`

We recommend using openapi/asyncapi specification to generate a client for your technology (Java, typescript).


We welcome feedback about the JSON API on
`our issue tracker <https://github.com/digital-asset/daml/issues/new/choose>`_, or
`on our forum <https://discuss.daml.com>`_.


Prerequisites
****************

It is assumed that you know the basics of HTTP Protocol, HTTP methods, HTTP request and response headers (including authorization), JSON format, and WebSockets.

In order to test json api you need a tool such as:
 * command line ``curl``
 * postman `<https://www.postman.com>`


Some tools enable testing of WebSockets; one is, for instance: ``wscat``.

Run the JSON API
****************

Prepare canton configuration
===================

.. code-block:: none

    canton {
      participants {
        participant1 {
          storage {
            type = memory
          }
          admin-api {
            port = 14012
          }
          http-ledger-api {
             server {
                port = 8080
             }
         }
       }
      }
    }

Save config as (for instance) ``json_enabled.conf``

.. note:: in canton 3.1 and earlier `http-ledger-api` is named `http-ledger-api-experimental`.


Start canton
===================

You can run the JSON API alongside any ledger exposing the gRPC Ledger API you want. If you don't have an existing ledger, you can start canton with the config as below:

.. code-block:: shell

    bin/canton -c json_enabled.conf


#. Ensure that the canton console is started. Please refer to :doc:`Console documentation </canton/usermanual/console>`

#. Check that json api is running:

    In terminal use curl to get openapi documentation

.. code-block:: shell

    curl localhost:8080/docs/openapi

    alternatively open the web browser and navigate to address:

    `<http:://localhost:8080/docs/openapi>`_

You should see yaml file contents that starts with:

.. code-block:: none

    openapi: 3.1.0
    info:
      title: JSON Ledger API HTTP endpoints


Congratulations, You have successfully started  JSON API.


.. _start-http-service:

.. note:: Your JSON API service should never be exposed to the Internet. When running in production the JSON API should be behind a `reverse proxy, such as via NGINX <https://docs.nginx.com/nginx/admin-guide/web-server/reverse-proxy/>`_.


HTTP API Advanced configuration
===================

The full set of configurable options that can be specified via config file is listed below:

.. code-block:: none

    {
      server {
        //IP address that HTTP JSON API service listens on. Defaults to 127.0.0.1.
        address = "127.0.0.1"
        //HTTP JSON API service port number. A port number of 0 will let the system pick an ephemeral port.
        port = 7575
      }
      ledger-api {
        address = "127.0.0.1"
        port = 6865
        tls {
            enabled = "true"
            // the certificate to be used by the server
            cert-chain-file = "cert-chain.crt"
            // private key of the server
            private-key-file = "pvt-key.pem"
            // trust collection, which means that all client certificates will be verified using the trusted
            // certificates in this store. if omitted, the JVM default trust store is used.
            trust-collection-file = "root-ca.crt"
        }
      }

      metrics {
        //Start a metrics reporter. Must be one of "console", "csv:///PATH", "graphite://HOST[:PORT][/METRIC_PREFIX]", or "prometheus://HOST[:PORT]".
        reporter = "console"
        //Set metric reporting interval , examples : 1s, 30s, 1m, 1h
        reporting-interval = 30s
      }

      // DEV MODE ONLY (not recommended for production)
      // Allow connections without a reverse proxy providing HTTPS.
      allow-insecure-tokens = false
    }


.. _json-api-access-tokens:

Access Tokens
=============

Each request to the HTTP JSON API Service *must* come with an access token (``JWT``). This also includes development setups using an unsecured sandbox.
The HTTP JSON API Service *does not*
hold on to the access token, which will be only used to fulfill the request it came along with. The same token will be used
to issue the request to the Ledger API.
The only exceptions are documentation endpoints, which do not strictly require tokens.

For  a reference on the JWT Tokens we use, please read:
 :ref:`Authorization <authorization>` and
 :ref:`JWT Authorization configuration <ledger-api-jwt-configuration>` documentation.

.. note::

    While the JSON API receives the token it doesn't validate it itself. Upon receiving a token it will pass it,
    and all data contained within the request, on to the Ledger API's AuthService which will then determine if the
    token is valid and authorized.

For a ledger without authorization, e.g., the default configuration of Daml Sandbox, you can use `https://jwt.io <https://jwt.io/#debugger-io?token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwczovL2RhbWwuY29tL2xlZGdlci1hcGkiOnsibGVkZ2VySWQiOiJzYW5kYm94IiwiYXBwbGljYXRpb25JZCI6ImZvb2JhciIsImFjdEFzIjpbIkFsaWNlIl19fQ.1Y9BBFH5uVz1Nhfmx12G_ECJVcMncwm-XLaWM40EHbY>`_ (or the JWT library of your choice) to generate your
token.  You can use an arbitrary secret here. The default "header" is fine.  Under "Payload", fill in:

.. code-block:: json

    {
      "aud": [],
      "exp": null,
      "iss": null,
      "scope": "ExpectedTargetScope",
      "sub": "actAs-Alice::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c"
    }

The value after``actAs`` is specified as a list and you provide it with the party that you want to use,
such as in the example above which uses ``Alice`` for a party. ``actAs`` may include more than just one party
as the JSON API supports multi-party submissions.

The party should reference an already allocated party.
In canton console a party can be allocated using:

.. code-block:: shell

    val alice = participant1.parties.enable("Alice")
    alice.toProtoPrimitive //this will display a full party Id


Then the "Encoded" box should have your **token**, ready for passing to
the service as described in the following sections.

Alternatively, here is a token you can use for testing:

.. code-block:: json

    {
        "aud": [],
        "exp": null,
        "iss": null,
        "scope": "ExpectedTargetScope",
        "sub": "participant_admin"
    }

.. code-block:: none

    eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOltdLCJleHAiOm51bGwsImlzcyI6bnVsbCwic2NvcGUiOiJFeHBlY3RlZFRhcmdldFNjb3BlIiwic3ViIjoicGFydGljaXBhbnRfYWRtaW4ifQ.8bABNm1t718TuJXwRQOF2gXOclrL38t0uCmWkIT7Pcg


Auth via HTTP
^^^^^^^^^^^^^

Set HTTP header ``Authorization: Bearer <paste-jwt-here>``


Example header:

.. code-block:: none

    Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwczovL2RhbWwuY29tL2xlZGdlci1hcGkiOnsibGVkZ2VySWQiOiJNeUxlZGdlciIsImFwcGxpY2F0aW9uSWQiOiJIVFRQLUpTT04tQVBJLUdhdGV3YXkiLCJhY3RBcyI6WyJBbGljZSJdfX0.34zzF_fbWv7p60r5s1kKzwndvGdsJDX-W4Xhm4oVdpk

Example using ``curl``

.. code-block:: bash

    curl -X 'POST' \
        'http://localhost:8080/v2/users' \
        -H 'Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOltdLCJleHAiOm51bGwsImlzcyI6bnVsbCwic2NvcGUiOiJFeHBlY3RlZFRhcmdldFNjb3BlIiwic3ViIjoicGFydGljaXBhbnRfYWRtaW4ifQ.8bABNm1t718TuJXwRQOF2gXOclrL38t0uCmWkIT7Pcg' \
        -H 'accept: application/json' \
        -H 'Content-Type: application/json' \
        -d @body_create_user.json



Auth via WebSockets
^^^^^^^^^^^^^^^^^^^

WebSocket clients support a "subprotocols" argument (sometimes simply
called "protocols"); this is usually in a list form but occasionally in
comma-separated form.  Check the documentation for your WebSocket library of
choice for details.

For HTTP JSON requests, you must pass two subprotocols:

- ``daml.ws.auth``
- ``jwt.token.paste-jwt-here``

Example:

.. code-block:: none

    jwt.token.eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwczovL2RhbWwuY29tL2xlZGdlci1hcGkiOnsibGVkZ2VySWQiOiJNeUxlZGdlciIsImFwcGxpY2F0aW9uSWQiOiJIVFRQLUpTT04tQVBJLUdhdGV3YXkiLCJhY3RBcyI6WyJBbGljZSJdfX0.34zzF_fbWv7p60r5s1kKzwndvGdsJDX-W4Xhm4oVdpk


Example using ``wscat``:

.. code-block:: none

    wscat -c http://localhost:8080/v2/state/active-contracts \
        -s "jwt.token.eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOltdLCJleHAiOm51bGwsImlzcyI6bnVsbCwic2NvcGUiOiJFeHBlY3RlZFRhcmdldFNjb3BlL1dpdGgtRGFzaC9BbmRfVW5kZXJzY29yZSIsInN1YiI6ImFjdEFzLUFsaWNlOjoxMjIwOTllNmI3YzkyZTEyZWIwMjZmNDgzZjU5YTczZTQ4MTQ5ZGM2ZTYzMGE0ZjRmOGZiOTViOGQyNjkyMTliMzU2YyJ9.FmJoP6eK2Yg6CAmO2G0SYosMS4IOai_6HlvO1siYNUA" \
        -s "daml.ws.auth"


HTTP Status Codes
*****************

The **JSON API** reports errors using standard HTTP status codes. It divides HTTP status codes into 3 groups indicating:

1. success (200)
2. failure due to a client-side problem (400, 401, 403, 404, 409, 429)
3. failure due to a server-side problem (500, 503)

Most common HTTP status codes are:

- 200 - OK
- 400 - Bad Request (Client Error)
- 401 - Unauthorized, authentication required
- 403 - Forbidden, insufficient permissions
- 404 - Not Found
- 409 - Conflict, contract ID or key missing or duplicated
- 500 - Internal Server Error
- 503 - Service Unavailable, ledger server is not running yet or has been shut down
- 504 - Gateway Timeout, transaction failed to receive its completion within the predefined timeout


HTTP JSON API Errors
*****************

When the Ledger API returns an error code, the JSON API maps it to one of the above codes according to `the official gRPC to HTTP code mapping <https://cloud.google.com/apis/design/errors#generating_errors>`_.

If a client's HTTP GET or POST request reaches an API endpoint, the corresponding response will always contain a JSON object. Either an expected message (corresponding to endpoint) or an  ``error`` object specified as in the example below:

.. code-block:: none

    {
    "cause" : "The submitted request has invalid arguments: Cannot unassign contract `ContractId(00a7feb291fe1be6289c4d77f3a432b623083ed3f49bf8535f8571aa8bdf68b647ca10122006207a71ac6ed62dae27429b43e456dfbbc411a49d67b7e0067bef4c914c6e8a)`: source and target domains are the same",
    "code" : "INVALID_ARGUMENT",
    "context" : {
        "category" : "8",
         "definite_answer" : "false",
          "participant" : "participant1",
          "test" : "JsonV2Tests",
         "tid" : "99e67812af315256ef9a02a9fdb94646"
      },
    "correlationId" : null,
    "definiteAnswer" : null,
    "errorCategory" : 8,
    "grpcCodeValue" : 3,
    "resources" : [ ],
    "retryInfo" : null,
    "traceId" : "99e67812af315256ef9a02a9fdb94646"
    }

Where:

- ``cause`` --  a textual message containing readable error reason,
- ``code`` -- a LedgerAPI error code,
- ``context`` -- a Ledger API context of an error,
- ``traceId`` -- telemetry tracing id
- ``grpcCodeValue`` and ``errorCategory`` as defined in :ref:`error_codes`.


See The Ledger API error codes (Canton Error Codes Reference) for more details about error codes from Ledger API.


WebSockets Errors
========================================

In case of websockets an error might be delivered as frame. Each incoming frame can either be a correct response (corresponding to the endpoint definition) or an error frame in the format above.




Example of successful Response, HTTP Status: 200 OK
========================================

- Content-Type: ``application/json``
- Content:

.. code-block:: none

    {
      "partyDetails": {
        "party": "Carol:-_ a9c80151-002c-445e-9fae-3caf111e3ac4::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
        "isLocal": true,
        "localMetadata": {
          "resourceVersion": "0",
          "annotations": {}
        },
        "identityProviderId": ""
      }
    }


Create a New Contract
*********************

To create an ``Iou`` contract from the :doc:`Quickstart guide </app-dev/bindings-java/quickstart>`:

.. literalinclude:: ../app-dev/bindings-java/quickstart/template-root/daml/Iou.daml
  :language: daml
  :start-after: -- BEGIN_IOU_TEMPLATE_DATATYPE
  :end-before: -- END_IOU_TEMPLATE_DATATYPE

.. _create-request:

HTTP Request
============

- URL,  one of:
    - ``/v2/commands/submit-and-wait-for-transaction-tree``
    - ``/v2/commands/submit-and-wait-for-transaction``
    -  ``/v2/commands/submit-and-wait``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "commands" : [ {
        "CreateCommand" : {
          "template_id" : "cbed714ed61c4a30b0038ea72c9ff13de51be99aac065f61e6ae9e954375e171:Iou:Iou",
          "create_arguments" : {
            "observers" : [ ],
            "issuer" : "Alice_2820c3a4-d1bd-49ef-9b90-17b142c55d30::1220df15d08ac34527e46492a6ee48a723e3d02ed3ec20a05ebf64be47173f24407f",
            "amount" : "999.99",
            "currency" : "USD",
            "owner" : "Alice_2820c3a4-d1bd-49ef-9b90-17b142c55d30::1220df15d08ac34527e46492a6ee48a723e3d02ed3ec20a05ebf64be47173f24407f"
          }
        }
      } ],
      "workflow_id" : "",
      "application_id" : "defaultapp1",
      "command_id" : "somecommandid",
      "deduplication_period" : {
        "Empty" : { }
      },
      "min_ledger_time_abs" : null,
      "min_ledger_time_rel" : null,
      "act_as" : [ "Alice_2820c3a4-d1bd-49ef-9b90-17b142c55d30::1220df15d08ac34527e46492a6ee48a723e3d02ed3ec20a05ebf64be47173f24407f" ],
      "read_as" : [ "Alice_2820c3a4-d1bd-49ef-9b90-17b142c55d30::1220df15d08ac34527e46492a6ee48a723e3d02ed3ec20a05ebf64be47173f24407f" ],
      "submission_id" : "somesubmissionid1",
      "disclosed_contracts" : [ ],
      "domain_id" : "",
      "package_id_selection_preference" : [ ]
    }

Where:

- ``template_id`` is the contract template identifier which has the following
  two formats: ``#<package name>:<module>:<entity>`` or ``<package
  ID>:<module>:<entity>``.

  The package name format works with the smart contract upgrading feature so
  that contracts with different package IDs but the same package name can be
  used in a uniform manner. 
  
  Using the package ID format refers to a single package. 


- ``create_arguments`` field contains contract fields as defined in the Daml template and formatted according to :doc:`lf-value-specification`.
- ``commandId`` -- optional field, a unique string identifying the command.
- ``actAs`` -- a non-empty list of parties, overriding the set from the JWT user; must be a subset of the JWT user's set.
- ``readAs`` -- a list of parties, overriding the set from the JWT user; must be a subset of the JWT user's set.
- ``submissionId`` -- a string, used for :doc:`deduplicating retried requests </app-dev/command-deduplication>`.  If you do not set it, a random one will be chosen, effectively treating the request as unique and disabling deduplication.
- ``deduplicationPeriod`` -- either a ``Duration`` as above, which is how far back in time prior commands will be searched for this submission, or an ``Offset`` as follows, which is the earliest ledger offset after which to search for the submission.

.. _example_response: (in case of 1/v2/commands/submit-and-wait-for-transaction-tree)

HTTP Response
=============

 The response will differ according to endpoint URL chosen to send transaction. Example below assumes ``/v2/commands/submit-and-wait-for-transaction-tree``.

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "transaction_tree": {
        "command_id": "somecommandid",
        "domain_id": "domain1::122002d4368a8ad29623839f1c4976889124cf9f6c336b5fbf833e643f38e9e8a498",
        "effective_at": "1970-01-01T00:00:00Z",
        "events_by_id": {
          "#1220ef7fb20517c48dc07c55743ea4712968d7fe51b32c212ab268176d240b582d12:0": {
            "CreatedTreeEvent": {
              "value": {
                "contract_id": "00d814ef389459b8fa8b1b67765637c6490e92819c7aae0a0d199ced2efec7ef25ca101220640e21ca6220bcb2a476d2b5be3beddd7da1f71f4f3af3a001ef3c38522211c4",
                "contract_key": null,
                "create_argument": {
                  "amount": "999.9900000000",
                  "currency": "USD",
                  "issuer": "Alice_6c4715ab-147d-4918-acfe-fdc85a745de7::1220844878a78a09732545ce29e5b48bd4038dd936224b3c844e17d621a3065a542a",
                  "observers": [],
                  "owner": "Alice_6c4715ab-147d-4918-acfe-fdc85a745de7::1220844878a78a09732545ce29e5b48bd4038dd936224b3c844e17d621a3065a542a"
                },
                "created_at": "1970-01-01T00:00:00Z",
                "created_event_blob": "",
                "event_id": "#1220ef7fb20517c48dc07c55743ea4712968d7fe51b32c212ab268176d240b582d12:0",
                "interface_views": [],
                "observers": [],
                "package_name": "model-tests",
                "signatories": [
                  "Alice_6c4715ab-147d-4918-acfe-fdc85a745de7::1220844878a78a09732545ce29e5b48bd4038dd936224b3c844e17d621a3065a542a"
                ],
                "template_id": "cbed714ed61c4a30b0038ea72c9ff13de51be99aac065f61e6ae9e954375e171:Iou:Iou",
                "witness_parties": [
                  "Alice_6c4715ab-147d-4918-acfe-fdc85a745de7::1220844878a78a09732545ce29e5b48bd4038dd936224b3c844e17d621a3065a542a"
                ]
              }
            }
          }
        },
        "offset": 8,
        "record_time": "1970-01-01T00:00:00.000036Z",
        "root_event_ids": [
          "#1220ef7fb20517c48dc07c55743ea4712968d7fe51b32c212ab268176d240b582d12:0"
        ],
        "trace_context": {
          "traceparent": "00-16fd492d478a8e3bef67bf4ecb1f4e22-7d4374f93195fa1c-01",
          "tracestate": null
        },
        "update_id": "1220ef7fb20517c48dc07c55743ea4712968d7fe51b32c212ab268176d240b582d12",
        "workflow_id": ""
      }
    }

Where:

- ``events_by_id`` contains ledger events with details of created contract(s),



Exercise by Contract ID
***********************

The JSON command below, demonstrates how to exercise an ``Iou_Transfer`` choice on an ``Iou`` contract:

.. literalinclude:: ../app-dev/bindings-java/quickstart/template-root/daml/Iou.daml
  :language: daml
  :start-after: -- BEGIN_IOU_TEMPLATE_TRANSFER
  :end-before: -- END_IOU_TEMPLATE_TRANSFER

HTTP Request
============

- URL,  one of:
    - ``/v2/commands/submit-and-wait-for-transaction-tree``
    - ``/v2/commands/submit-and-wait-for-transaction``
    -  ``/v2/commands/submit-and-wait``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "act_as" : [ "Alice_f410fcbe-e03f-47ef-bad0-f7a8a08e7338::1220870d67dba562b868d0256cb2968dbc59a7a6bdbc4b82ee623ff96c8cda3afb9a" ],
      "application_id" : "defaultapp2",
      "command_id" : "somecommandid",
      "commands" : [ {
        "ExerciseCommand" : {
          "choice" : "Iou_Transfer",
          "choice_argument" : {
            "newOwner" : "Alice_f410fcbe-e03f-47ef-bad0-f7a8a08e7338::1220870d67dba562b868d0256cb2968dbc59a7a6bdbc4b82ee623ff96c8cda3afb9a"
          },
          "contract_id" : "00fd14e85d36ac5f1568d7276f33a1d7bf461cd77fd6042af16455a06613e8afabca101220b6a0730c7765991946af0f5d9d32be551d12ac2c7c14eb5f45ba706b05548923",
          "template_id" : "cbed714ed61c4a30b0038ea72c9ff13de51be99aac065f61e6ae9e954375e171:Iou:Iou"
        }
      } ],
      "deduplication_period" : {
        "Empty" : { }
      },
      "disclosed_contracts" : [ ],
      "domain_id" : "",
      "min_ledger_time_abs" : null,
      "min_ledger_time_rel" : null,
      "package_id_selection_preference" : [ ],
      "read_as" : [ "Alice_f410fcbe-e03f-47ef-bad0-f7a8a08e7338::1220870d67dba562b868d0256cb2968dbc59a7a6bdbc4b82ee623ff96c8cda3afb9a" ],
      "submission_id" : "somesubmissionid2",
      "workflow_id" : ""
    }

Where:

- ``templateId`` -- contract template or interface identifier, same as in :ref:`create request <create-request>`,
- ``choiceInterfaceId`` -- *optional* template or interface that defines the choice, same format as ``templateId``,
- ``contractId`` -- contract identifier, the value from the  :ref:`create response <create-response>`,
- ``choice`` -- Daml contract choice, that is being exercised,
- ``argument`` -- contract choice argument(s).

``templateId`` and ``choiceInterfaceId`` are treated as with :ref:`exercise by key <exercise-by-key-templateId-choiceInterfaceId>`.
However, because ``contractId`` is always unambiguous, you may alternatively simply specify the interface ID as the ``templateId`` argument, and ignore ``choiceInterfaceId`` entirely.
This isn't true of exercise-by-key or create-and-exercise, so we suggest treating this request as if this alternative isn't available.

.. _exercise-response: (using ``/v2/commands/submit-and-wait``)

HTTP Response
=============

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "completion_offset" : 11,
      "update_id" : "12205cec9cccf807dd95df3c0ab270bd286ef1bc9b84aa26f7ecf1180248aaa9d070"
    }

Where:

    + ``update_id``  the id of the transaction that resulted from the submitted command.
    + ``completionOffset`` is the ledger offset of the transaction containing the exercise's ledger changes.

Create and Exercise in the Same Transaction
*******************************************

This command allows creating a contract and exercising a choice on the newly created contract in the same transaction.

HTTP Request
============

- URL,  one of:
    - ``/v2/commands/submit-and-wait-for-transaction-tree``
    - ``/v2/commands/submit-and-wait-for-transaction``
    -  ``/v2/commands/submit-and-wait``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "act_as" : [ "Alice_f410fcbe-e03f-47ef-bad0-f7a8a08e7338::1220870d67dba562b868d0256cb2968dbc59a7a6bdbc4b82ee623ff96c8cda3afb9a" ],
      "application_id" : "defaultapp2",
      "command_id" : "somecommandid",
      "commands" : [ {
        "CreateAndExerciseCommand" : {
          "choice" : "Iou_Transfer",
          "create_arguments" : {
                      "observers" : [ ],
                      "issuer" : "Alice_2820c3a4-d1bd-49ef-9b90-17b142c55d30::1220df15d08ac34527e46492a6ee48a723e3d02ed3ec20a05ebf64be47173f24407f",
                      "amount" : "999.99",
                      "currency" : "USD",
                      "owner" : "Alice_2820c3a4-d1bd-49ef-9b90-17b142c55d30::1220df15d08ac34527e46492a6ee48a723e3d02ed3ec20a05ebf64be47173f24407f"
                    },
          "choice_argument" : {
            "newOwner" : "Alice_f410fcbe-e03f-47ef-bad0-f7a8a08e7338::1220870d67dba562b868d0256cb2968dbc59a7a6bdbc4b82ee623ff96c8cda3afb9a"
          },
          "template_id" : "cbed714ed61c4a30b0038ea72c9ff13de51be99aac065f61e6ae9e954375e171:Iou:Iou"
        }
      } ],
      "deduplication_period" : {
        "Empty" : { }
      },
      "disclosed_contracts" : [ ],
      "domain_id" : "",
      "min_ledger_time_abs" : null,
      "min_ledger_time_rel" : null,
      "package_id_selection_preference" : [ ],
      "read_as" : [ "Alice_f410fcbe-e03f-47ef-bad0-f7a8a08e7338::1220870d67dba562b868d0256cb2968dbc59a7a6bdbc4b82ee623ff96c8cda3afb9a" ],
      "submission_id" : "somesubmissionid2",
      "workflow_id" : ""
    }

Where:

- ``templateId`` -- the initial contract template identifier, in the same format as in the :ref:`create request <create-request>`,
- ``payload`` -- the initial contract fields as defined in the Daml template and formatted according to :doc:`lf-value-specification`,
- ``choiceInterfaceId`` -- *optional* template or interface that defines the choice, same format as ``templateId``,
- ``choice`` -- Daml contract choice, that is being exercised,
- ``argument`` -- contract choice argument(s).

``templateId`` and ``choiceInterfaceId`` are treated as with :ref:`exercise by key <exercise-by-key-templateId-choiceInterfaceId>`, with the exception that it is ``payload``, not ``key``, strictly interpreted according to ``templateId``.

HTTP Response
=============

Please note that the response below is for a consuming choice, so it contains:

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "transaction" : {
        "command_id" : "somecommandid",
        "domain_id" : "domain1::12208f22808f6fe77f8689d0d565488e34e9a3abb2eaf37270f6e5b2b2073894db9f",
        "effective_at" : "1970-01-01T00:00:00Z",
        "events" : [ {
          "CreatedEvent" : {
            "contract_id" : "00811e868ffe78638ecf14b8d69a5df6eafd8b16f13a431117ee26981cc39f40e1ca101220c15b891d2cac1287d5067594c81f60b722141204f63f2a27c3328a70467c5018",
            "contract_key" : null,
            "create_argument" : {
              "iou" : {
                "amount" : "999.9900000000",
                "currency" : "USD",
                "issuer" : "Alice_ffe0d699-2978-42d7-a315-b7faec7ba95a::1220d7b8bc76f04500216f07e1576da75db0e811ea1e01d5688140816823615a34bf",
                "observers" : [ ],
                "owner" : "Alice_ffe0d699-2978-42d7-a315-b7faec7ba95a::1220d7b8bc76f04500216f07e1576da75db0e811ea1e01d5688140816823615a34bf"
              },
              "newOwner" : "Alice_ffe0d699-2978-42d7-a315-b7faec7ba95a::1220d7b8bc76f04500216f07e1576da75db0e811ea1e01d5688140816823615a34bf"
            },
            "created_at" : "1970-01-01T00:00:00Z",
            "created_event_blob" : "",
            "event_id" : "#1220ad3e6509fa8977478aa49cf3261b376dd55b06f6409e3ec59553272c89d3616c:2",
            "interface_views" : [ ],
            "node_id" : 2,
            "observers" : [ ],
            "offset" : 12,
            "package_name" : "model-tests",
            "signatories" : [ "Alice_ffe0d699-2978-42d7-a315-b7faec7ba95a::1220d7b8bc76f04500216f07e1576da75db0e811ea1e01d5688140816823615a34bf" ],
            "template_id" : "a36cfff1da2f15da3d760c872860bf03140aa699f73b57b639fd40dfe8156cfe:Iou:IouTransfer",
            "witness_parties" : [ "Alice_ffe0d699-2978-42d7-a315-b7faec7ba95a::1220d7b8bc76f04500216f07e1576da75db0e811ea1e01d5688140816823615a34bf" ]
          }
        } ],
        "offset" : 12,
        "record_time" : "1970-01-01T00:00:00.000042Z",
        "trace_context" : {
          "traceparent" : "00-d84d23ff01031adbcf76f19525fa62fb-003327aa6c8ede2d-01",
          "tracestate" : null
        },
        "update_id" : "1220ad3e6509fa8977478aa49cf3261b376dd55b06f6409e3ec59553272c89d3616c",
        "workflow_id" : ""
      }
    }

Get All Active Contracts
************************

List all currently active contracts for all known templates.

.. note:: You can only query active contracts with the ``/v2/state/active-contracts`` endpoint. Archived contracts (those that were archived or consumed during an exercise operation) will not be shown in the results.

HTTP Websocket Request
============

- URL: ``/v2/state/active-contracts``
- Protocol: ``Websocket``
- Content:

Send a single query frame:

.. code-block:: json

    {
        "filter":
        {
            "filtersByParty":{},
            "filtersForAnyParty":
                {"cumulative":  [
                    {"identifierFilter":
                        {"WildcardFilter":
                            {"value":
                                {"includeCreatedEventBlob":true}
                                }
                            }
                        }
                    ]
                }
            },
        "verbose":false,
        "activeAtOffset":23
   }

.. note:: be careful and do enter a proper value for activeAtOffset

Example Response frames
=============

The response might look like an example below:

.. code-block:: json

    {
      "workflow_id": "",
      "contract_entry": {
        "JsActiveContract": {
          "created_event": {
            "event_id": "#1220c9f63cf562c188f3135491a4e74fe08586b2e5bdb65f026d6eb425297cb049fa:0",
            "offset": 23,
            "node_id": 0,
            "contract_id": "0060bee40875fe4502d115dc602e089b23ad5d9bddf568e9f22c85071028104d3fca1012203a7966db6486e1a12b7e63035b193fd3df7bac94c3a280860bb92ac590ca97d8",
            "template_id": "a36cfff1da2f15da3d760c872860bf03140aa699f73b57b639fd40dfe8156cfe:Iou:Iou",
            "contract_key": null,
            "create_argument": {
              "issuer": "Alice::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
              "owner": "Alice::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
              "currency": "USD",
              "amount": "999.9900000000",
              "observers": []
            },
            "created_event_blob": "CgMyLjES7wMKRQBgvuQIdf5FAtEV3GAuCJsjrV2b3fVo6fIshQcQKBBNP8oQEiA6eWbbZIbhoSt+YwNbGT/T33uslMOigIYLuSrFkMqX2BILbW9kZWwtdGVzdHMaTApAYTM2Y2ZmZjFkYTJmMTVkYTNkNzYwYzg3Mjg2MGJmMDMxNDBhYTY5OWY3M2I1N2I2MzlmZDQwZGZlODE1NmNmZRIDSW91GgNJb3UiyAFqxQEKTwpNOktBbGljZTo6MTIyMDk5ZTZiN2M5MmUxMmViMDI2ZjQ4M2Y1OWE3M2U0ODE0OWRjNmU2MzBhNGY0ZjhmYjk1YjhkMjY5MjE5YjM1NmMKTwpNOktBbGljZTo6MTIyMDk5ZTZiN2M5MmUxMmViMDI2ZjQ4M2Y1OWE3M2U0ODE0OWRjNmU2MzBhNGY0ZjhmYjk1YjhkMjY5MjE5YjM1NmMKBwoFQgNVU0QKEgoQMg45OTkuOTkwMDAwMDAwMAoECgJaACpLQWxpY2U6OjEyMjA5OWU2YjdjOTJlMTJlYjAyNmY0ODNmNTlhNzNlNDgxNDlkYzZlNjMwYTRmNGY4ZmI5NWI4ZDI2OTIxOWIzNTZjOc1refENKQYAQioKJgokCAESINYJODbmD6MBtygqr/BXycesGGKTrVwcms/ZsrN6ZTivEB4=",
            "interface_views": [],
            "witness_parties": [
              "Alice::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c"
            ],
            "signatories": [
              "Alice::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c"
            ],
            "observers": [],
            "created_at": "2024-12-12T07:48:42.844109Z",
            "package_name": "model-tests"
          },
          "domain_id": "da1::12209490832f5a44e5a76cd5c4afc4e44db3d856d3070f8236d5109e28626a48374d",
          "reassignment_counter": 0
        }
      }
    }

Fetch Parties by Identifiers
****************************

- URL: ``/v2/parties/{partyId}``
- Method: ``GET``
- Content-Type: ``application/json``
- Content:


HTTP Response
=============

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "partyDetails": [
        {
          "party": "Alice::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
          "isLocal": true,
          "localMetadata": {
            "resourceVersion": "",
            "annotations": {}
          },
          "identityProviderId": ""
        }
      ]
    }

Where

- ``identifier`` -- a stable unique identifier of a Daml party,
- ``isLocal`` -- true if party is hosted by the backing participant.

The ``result`` might contain an empty JSON array `partyDetails`.

Fetch All Known Parties
***********************

- URL: ``/v2/parties``
- Method: ``GET``
- Content: <EMPTY>

HTTP Response
=============

.. code-block:: json

    {
      "partyDetails": [
        {
          "party": "Alice::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
          "isLocal": true,
          "localMetadata": {
            "resourceVersion": "",
            "annotations": {}
          },
          "identityProviderId": ""
        },
        {
          "party": "Bob::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
          "isLocal": true,
          "localMetadata": {
            "resourceVersion": "",
            "annotations": {}
          },
          "identityProviderId": ""
        },
        {
          "party": "participant1::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
          "isLocal": true,
          "localMetadata": {
            "resourceVersion": "",
            "annotations": {}
          },
          "identityProviderId": ""
        }
      ],
      "nextPageToken": ""
    }

.. note:: `nextPageToken` is used by gRPC if there is paging enabled, in the current resource version of JSON API paging is not yet supported.


Allocate a New Party
********************

This endpoint is a JSON API proxy for the Ledger API's :ref:`AllocatePartyRequest <com.daml.ledger.api.v1.admin.AllocatePartyRequest>`. For more information about party management, please refer to :ref:`Provisioning Identifiers <provisioning-ledger-identifiers>` part of the Ledger API documentation.

HTTP Request
============

- URL: ``/v2/parties``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "identityProviderId" : "",
      "localMetadata" : null,
      "partyIdHint" : "Carol:-_ a9c80151-002c-445e-9fae-3caf111e3ac4"
    }


Please refer to :ref:`AllocateParty <com.daml.ledger.api.v1.admin.AllocatePartyRequest>` documentation for information about the meaning of the fields.


HTTP Response
=============

.. code-block:: json

    {
      "partyDetails": {
        "party": "Carol:-_ a9c80151-002c-445e-9fae-3caf111e3ac4::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
        "isLocal": true,
        "localMetadata": {
          "resourceVersion": "0",
          "annotations": {}
        },
        "identityProviderId": ""
      }
    }


Create a New User
*****************

This endpoint exposes the Ledger API's :ref:`CreateUser RPC <com.daml.ledger.api.v1.admin.createuserrequest>`.

HTTP Request
============

- URL: ``/v2/users``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

  {
    "rights" : [
      {
        "kind": {
          "CanActAs" : {
            "value": {
              "party" : "Bob::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c"
            }
          }
        }
      }
    ],
    "user" : {
      "id" : "CreatedUser1",
      "identityProviderId" : "",
      "isDeactivated" : false,
      "metadata" : null,
      "primaryParty" : ""
    }
  }


Please refer to :ref:`CreateUser RPC <com.daml.ledger.api.v1.admin.createuserrequest>` documentation for information about the meaning of the fields.

Only the userId fields in the request is required, this means that an JSON object containing only it is a valid request to create a new user.

HTTP Response
=============

.. code-block:: json

    {
      "user": {
        "id": "CreatedUser1",
        "primaryParty": "",
        "isDeactivated": false,
        "metadata": {
          "resourceVersion": "0",
          "annotations": {}
        },
        "identityProviderId": ""
      }
    }


Get Specific User Information
*****************************

This endpoint exposes the Ledger API's :ref:`GetUser RPC <com.daml.ledger.api.v1.admin.getuserrequest>`.

HTTP Request
============

- URL: ``/v2/users/{userId}``
- Method: ``GET``
- Content-Type: ``application/json``
- Content:


Please refer to :ref:`GetUser RPC <com.daml.ledger.api.v1.admin.getuserrequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "user": {
        "id": "CreatedUser1",
        "primaryParty": "",
        "isDeactivated": false,
        "metadata": {
          "resourceVersion": "0",
          "annotations": {}
        },
        "identityProviderId": ""
      }
    }

Delete Specific User
********************

This endpoint exposes the Ledger API's :ref:`DeleteUser RPC <com.daml.ledger.api.v1.admin.DeleteUserRequest>`.

HTTP Request
============

- URL: ``/v2/users/{userId}``
- Method: ``DELETE``
- Content-Type: ``application/json``
- Content:


Please refer to :ref:`DeleteUser RPC <com.daml.ledger.api.v1.admin.DeleteUserRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {}

An empty response with a status 200 confirms successful deletion.


List Users
**********

This endpoint exposes the Ledger API's :ref:`ListUsers RPC <com.daml.ledger.api.v1.admin.ListUsersRequest>`.

HTTP Request
============

- URL: ``/v2/users``
- Method: ``GET``

HTTP Response
=============

.. code-block:: json

    {
      "users": [
        {
          "id": "CreatedUser",
          "primaryParty": "",
          "isDeactivated": false,
          "metadata": {
            "resourceVersion": "0",
            "annotations": {}
          },
          "identityProviderId": ""
        },
        {
          "id": "participant_admin",
          "primaryParty": "",
          "isDeactivated": false,
          "metadata": {
            "resourceVersion": "0",
            "annotations": {}
          },
          "identityProviderId": ""
        }
      ],
      "nextPageToken": ""
    }

Grant User Rights
*****************

This endpoint exposes the Ledger API's :ref:`GrantUserRights RPC <com.daml.ledger.api.v1.admin.GrantUserRightsRequest>`.

HTTP Request
============

- URL: ``/v2/users/{userId}/rights``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "identityProviderId" : "",
      "rights" : [ {
        "kind" : {
          "ParticipantAdmin" : {
            "value" : { }
          }
        }
      } ],
      "userId" : "CreatedUser1"
    }

Please refer to :ref:`GrantUserRights RPC <com.daml.ledger.api.v1.admin.GrantUserRightsRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "newlyGrantedRights": [
        {
          "kind": {
            "ParticipantAdmin": {
              "value": {}
            }
          }
        }
      ]
    }

Returns the rights that were newly granted.

Revoke User Rights
******************

This endpoint exposes the Ledger API's :ref:`RevokeUserRights RPC <com.daml.ledger.api.v1.admin.RevokeUserRightsRequest>`.

HTTP Request
============

- URL: ``/v2/users/{userId}/rights``
- Method: ``PATCH``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "identityProviderId" : "",
      "rights" : [ {
        "kind" : {
          "ParticipantAdmin" : {
            "value" : { }
          }
        }
      } ],
      "userId" : "CreatedUser1"
    }

Please refer to :ref:`RevokeUserRights RPC <com.daml.ledger.api.v1.admin.RevokeUserRightsRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "newlyRevokedRights": [
        {
          "kind": {
            "ParticipantAdmin": {
              "value": {}
            }
          }
        }
      ]
    }

Returns the rights that were actually revoked.



List Specific User Rights
*************************

This endpoint exposes the Ledger API's :ref:`ListUserRights RPC <com.daml.ledger.api.v1.admin.ListUserRightsRequest>`.

HTTP Request
============

- URL: ``/v2/users/{userId}/rights``
- Method: ``GET``
- Content-Type: ``application/json``

Please refer to :ref:`ListUserRights RPC <com.daml.ledger.api.v1.admin.ListUserRightsRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "rights": [
        {
          "kind": {
            "CanActAs": {
              "value": {
                "party": "Bob::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c"
              }
            }
          }
        },
        {
          "kind": {
            "ParticipantAdmin": {
              "value": {}
            }
          }
        }
      ]
    }

List All DALF Packages
**********************

HTTP Request
============

- URL: ``/v2/packages``
- Method: ``GET``


HTTP Response
=============

.. code-block:: json

    {
      "packageIds": [
        "9e70a8b3510d617f8a136213f33d6a903a10ca0eeec76bb06ba55d1ed9680f69",
        "0e4a572ab1fb94744abb02243a6bbed6c78fc6e3c8d3f60c655f057692a62816",
        "5aee9b21b8e9a4c4975b5f4c4198e6e6e8469df49e2010820e792f393db870f4",
        "a1fa18133ae48cbb616c4c148e78e661666778c3087d099067c7fe1868cbb3a1",
        "a36cfff1da2f15da3d760c872860bf03140aa699f73b57b639fd40dfe8156cfe",
        "54f85ebfc7dfae18f7d70370015dcc6c6792f60135ab369c44ae52c6fc17c274"
        ]
     }

Where ``packageIds`` is the JSON array containing the package IDs of all loaded DALFs.

Download a DALF Package
***********************

HTTP Request
============

- URL: ``/v2/packages/<package ID>``
- Method: ``GET``
- Content: <EMPTY>

Note that the desired package ID is specified in the URL.

HTTP Response, status: 200 OK
=============================

- Transfer-Encoding: ``chunked``
- Content-Type: ``application/octet-stream``
- Content: <DALF bytes>

The content (body) of the HTTP response contains raw DALF package bytes, without any encoding. Note that the package ID specified in the URL is actually the SHA-256 hash of the downloaded DALF package and can be used to validate the integrity of the downloaded content.

Upload a DAR File
*****************

HTTP Request
============

- URL: ``/v2/packages``
- Method: ``POST``
- Content-Type: ``application/octet-stream``
- Content: <DAR bytes>

The content (body) of the HTTP request contains raw DAR file bytes, without any encoding.

HTTP Response, Status: 200 OK
=============================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {}



Metering Report
***************

For a description of participant metering, the parameters, and the report format see
the :doc:`Participant Metering <../ops/metering>`.

- URL: ``/v2/metering/report/<applicationId>?from=<date>``
- Method: ``GET``
- Content-Type: ``application/json``



HTTP Response
=============

- Content-Type: ``application/json``
- Content:

.. code-block:: json

     {
       "request": {
         "from": "2024-06-01T00:00:00Z",
         "to": null,
         "applicationId": "app1"
       },
       "reportGenerationTime": "2024-12-12T13:01:58.010470Z",
       "meteringReportJson": {
         "participant": "participant1::122099e6b7c92e12eb026f483f59a73e48149dc6e630a4f4f8fb95b8d269219b356c",
         "request": {
           "application": "app1",
           "from": "2024-06-01T00:00:00Z"
         },
         "applications": [
           {
             "application": "app1",
             "events": 2.0
           }
         ],
         "check": {
           "digest": "2sicz7z8cIQpSxpGUbN8rhDeI9eOX9TZnuN2JPYas4U=",
           "scheme": "canton-enterprise-2022"
         },
         "final": false
       }
     }

