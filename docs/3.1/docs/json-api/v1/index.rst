.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _json-api-v1:

HTTP JSON API Service
#####################

The **JSON API** provides a significantly simpler way to interact with a ledger than
:doc:`the Ledger API </app-dev/ledger-api>` by providing *basic active contract set functionality*:

- creating contracts,
- exercising choices on contracts,
- querying the current active contract set, and
- retrieving all known parties.

The goal of this API is to get your distributed ledger application up and running quickly, so we have deliberately excluded
complicating concerns including, but not limited to:

- inspecting transactions,
- asynchronous submit/completion workflows,
- temporal queries (e.g. active contracts *as of a certain time*), and

For these and other features, use :doc:`the Ledger API </app-dev/ledger-api>` instead.
The HTTP JSON API service is a "proxy", after a fashion, for that API; *there is literally nothing that HTTP JSON API service can do that your own application cannot do via gRPC*.

If you are using this API from JavaScript or TypeScript, we strongly recommend using `the JavaScript bindings and code generator </app-dev/bindings-ts/index.html>`_ rather than invoking these endpoints directly.
This will both simplify access to the endpoints described here and (with TypeScript) help to provide the correct JavaScript value format for each of your contracts, choice arguments, and choice results.

As suggested by those bindings, the primary target application for the HTTP JSON API service is a web application, where user actions translate to one or a few ledger operations.
It is not intended for high-throughput, high-performance ledger automation; the Ledger API is better suited to such use cases.

We welcome feedback about the JSON API on
`our issue tracker <https://github.com/digital-asset/daml/issues/new/choose>`_, or
`on our forum <https://discuss.daml.com>`_.


Run the JSON API
****************

Start a Daml Ledger with the HTTP JSON API Service
==================================================

You can run the JSON API alongside any ledger exposing the gRPC Ledger API you want. If you don't have an existing ledger, you can start an in-memory sandbox:

.. code-block:: shell

    daml new my-project --template quickstart-java
    cd my-project
    daml build
    daml sandbox --json-api-port 8080 --wall-clock-time --dar ./.daml/dist/quickstart-0.0.1.dar

.. _start-http-service:

Configure the HTTP JSON API Service
===================================

You can configure the JSON API through the standard Canton config file:

.. code-block:: shell

    daml sandbox -c canton.conf --wall-clock-time --dar ./.daml/dist/quickstart-0.0.1.dar

where a corresponding minimal config file is

.. code-block:: none

    canton.participants.sandbox {
      http-ledger-api {
        server {
          address=localhost
          port=7575
        }
      }
    }

This starts the JSON API on port 7575.

.. note:: Your JSON API service should never be exposed to the internet. When running in production the JSON API should be behind a `reverse proxy, such as via NGINX <https://docs.nginx.com/nginx/admin-guide/web-server/reverse-proxy/>`_.

The full set of configurable options that can be specified via config file is listed below

.. code-block:: none

    canton.participants.sandbox.http-ledger-api {
      server {
        //IP address that HTTP JSON API service listens on. Defaults to 127.0.0.1.
        address = "127.0.0.1"
        //HTTP JSON API service port number. A port number of 0 will let the system pick an ephemeral port.
        port = 7575
        // A file to which the http port will be written upon start-up
        port-file = ./port-file.txt
        // A prefix of all the http json api endpoints
        path-prefix = "json/v1"
      }

      //Optional websocket configuration parameters
      websocket-config {
        //Maximum websocket session duration
        max-duration = 120m
        //Server-side heartbeat interval duration
        heartbeat-period = 5s
        //akka stream throttle-mode one of either `shaping` or `enforcing`
        mode = "shaping"
      }

      // DEV MODE ONLY (not recommended for production)
      // Allow connections without a reverse proxy providing HTTPS.
      allow-insecure-tokens = false

      // Turn on logging of http requests and responses
      debug-logging-of-http-bodies = false

      // utilize the user management database (including idp) to convert JWT tokens to parties
      // that the user is entitled to act and read as even if the authorization is not turned on.
      user-management-without-authorization = false
    }


With Query Store
----------------

Unlike the previous stand-alone JSON API, the built-in version does not have a query store. If you need persistent
storage for your JSON API client application, configure a PQS instance. For setup instructions, see the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__.

.. _json-api-access-tokens-v1:

Access Tokens
=============

Each request to the HTTP JSON API Service *must* come with an access token, regardless of whether the underlying ledger
requires it or not. This also includes development setups using an unsecured sandbox. The HTTP JSON API Service *does not*
hold on to the access token, which will be only used to fulfill the request it came along with. The same token will be used
to issue the request to the Ledger API.

The HTTP JSON API Service does not validate the token but may need to decode it to extract information that can be used
to fill in request fields for party-specific request. How this happens depends partially on the token format you are using.

Party-specific Requests
-----------------------

Party-specific requests, i.e., command submissions and queries, are subject to additional restrictions. For command
submissions the token must provide a proof that the bearer can act on behalf of at least one party (and possibly read
on behalf of any number of parties). For queries the token must provide a proof that the bearer can either act and/or
read of at least one party. This happens regardless of the used :ref:`access token format<access-token-formats>`. The
following paragraphs provide guidance as to how different token formats are used by the HTTP JSON API in this regard.

Using User Tokens
^^^^^^^^^^^^^^^^^

If the underlying ledger supports :ref:`user management <user-management-service>` (this includes Canton and the sandbox), you are
recommended to use user tokens. For command submissions, the user of the bearer should have ``actAs`` rights for at
least one party and ``readAs`` rights for any number of parties. Queries require the bearer's user to have at least
one ``actAs`` or ``readAs`` user right. The application id of the Ledger API request will be the user id.

Auth via HTTP
^^^^^^^^^^^^^

Set HTTP header ``Authorization: Bearer paste-jwt-here``

Example:

.. code-block:: none

    Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwczovL2RhbWwuY29tL2xlZGdlci1hcGkiOnsibGVkZ2VySWQiOiJNeUxlZGdlciIsImFwcGxpY2F0aW9uSWQiOiJIVFRQLUpTT04tQVBJLUdhdGV3YXkiLCJhY3RBcyI6WyJBbGljZSJdfX0.34zzF_fbWv7p60r5s1kKzwndvGdsJDX-W4Xhm4oVdpk

Auth via WebSockets
^^^^^^^^^^^^^^^^^^^

WebSocket clients support a "subprotocols" argument (sometimes simply
called "protocols"); this is usually in a list form but occasionally in
comma-separated form.  Check documentation for your WebSocket library of
choice for details.

For HTTP JSON requests, you must pass two subprotocols:

- ``daml.ws.auth``
- ``jwt.token.paste-jwt-here``

Example:

.. code-block:: none

    jwt.token.eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwczovL2RhbWwuY29tL2xlZGdlci1hcGkiOnsibGVkZ2VySWQiOiJNeUxlZGdlciIsImFwcGxpY2F0aW9uSWQiOiJIVFRQLUpTT04tQVBJLUdhdGV3YXkiLCJhY3RBcyI6WyJBbGljZSJdfX0.34zzF_fbWv7p60r5s1kKzwndvGdsJDX-W4Xhm4oVdpk

HTTP Status Codes
*****************

The **JSON API** reports errors using standard HTTP status codes. It divides HTTP status codes into 3 groups indicating:

1. success (200)
2. failure due to a client-side problem (400, 401, 403, 404, 409, 429)
3. failure due to a server-side problem (500, 503)

The **JSON API** can return one of the following HTTP status codes:

- 200 - OK
- 400 - Bad Request (Client Error)
- 401 - Unauthorized, authentication required
- 403 - Forbidden, insufficient permissions
- 404 - Not Found
- 409 - Conflict, contract ID or key missing or duplicated
- 500 - Internal Server Error
- 503 - Service Unavailable, ledger server is not running yet or has been shut down
- 504 - Gateway Timeout, transaction failed to receive its completion within the predefined timeout

When the Ledger API returns an error code, the JSON API maps it to one of the above codes according to `the official gRPC to HTTP code mapping <https://cloud.google.com/apis/design/errors#generating_errors>`_.

If a client's HTTP GET or POST request reaches an API endpoint, the corresponding response will always contain a JSON object with a ``status`` field, and either an ``errors`` or ``result`` field. It may also contain an optional ``warnings`` and/or an optional ``ledgerApiError`` :

.. code-block:: none

    {
        "status": <400 | 401 | 403 | 404 | 409 | 500 | 503 | 504>,
        "errors": <JSON array of strings>, | "result": <JSON object or array>,
        ["warnings": <JSON object> ],
        ["ledgerApiError": <JSON object> ]
    }

Where:

- ``status`` -- a JSON number which matches the HTTP response status code returned in the HTTP header,
- ``errors`` -- a JSON array of strings, each string represents one error,
- ``result`` -- a JSON object or JSON array, representing one or many results,
- ``warnings`` -- an optional field with a JSON object, representing one or many warnings.
- ``ledgerApiError`` -- an optional field with a JSON object, representing detail of an error if it was originated from Ledger API.

See the following blog post for more details about error handling best practices: `REST API Error Codes 101 <https://blog.restcase.com/rest-api-error-codes-101/>`_.

See The Ledger API error codes (Canton Error Codes Reference) for more details about error codes from Ledger API.

Successful Response, HTTP Status: 200 OK
========================================

- Content-Type: ``application/json``
- Content:

.. code-block:: none

    {
        "status": 200,
        "result": <JSON object>
    }

Successful Response with a Warning, HTTP Status: 200 OK
=======================================================

- Content-Type: ``application/json``
- Content:

.. code-block:: none

    {
        "status": 200,
        "result": <JSON object>,
        "warnings": <JSON object>
    }

.. _error-format:

Failure, HTTP Status: 400 | 401 | 404 | 500
===========================================

- Content-Type: ``application/json``
- Content:

.. code-block:: none

    {
        "status": <400 | 401 | 404 | 500>,
        "errors": <JSON array of strings>,
        ["ledgerApiError": <JSON object> ]
    }

Examples
========

**Result with JSON Object without Warnings:**

.. code-block:: none

    {"status": 200, "result": {...}}

**Result with JSON Array and Warnings:**

.. code-block:: none

    {"status": 200, "result": [...], "warnings": {"unknownTemplateIds": ["UnknownModule:UnknownEntity"]}}

**Bad Request Error:**

.. code-block:: json

    {"status": 400, "errors": ["JSON parser error: Unexpected character 'f' at input index 27 (line 1, position 28)"]}

**Bad Request Error with Warnings:**

.. code-block:: json

    {"status":400, "errors":["Cannot resolve any template ID from request"], "warnings":{"unknownTemplateIds":["XXX:YYY","AAA:BBB"]}}

**Authentication Error:**

.. code-block:: json

    {"status": 401, "errors": ["Authentication Required"]}

**Not Found Error:**

.. code-block:: json

    {"status": 404, "errors": ["HttpMethod(POST), uri: http://localhost:7575/v1/query1"]}

**Internal Server Error:**

.. code-block:: json

    {"status": 500, "errors": ["Cannot initialize Ledger API"]}

Create a New Contract
*********************

To create an ``Iou`` contract from the :doc:`Quickstart guide </app-dev/bindings-java/quickstart>`:

.. literalinclude:: ../../app-dev/bindings-java/quickstart/template-root/daml/Iou.daml
  :language: daml
  :start-after: -- BEGIN_IOU_TEMPLATE_DATATYPE
  :end-before: -- END_IOU_TEMPLATE_DATATYPE

.. _create-request-v1:

HTTP Request
============

- URL: ``/v1/create``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "templateId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:Iou",
      "payload": {
        "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
        "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
        "currency": "USD",
        "amount": "999.99",
        "observers": []
      }
    }

Where:

- ``templateId`` is the contract template identifier which has the following
  two formats: ``#<package name>:<module>:<entity>`` or ``<package
  ID>:<module>:<entity>``.

  The package name format works with the smart contract upgrading feature so
  that contracts with different package IDs but the same package name can be
  used in a uniform manner.

  Using the package ID format refers to a single package.

  Previously JSON API had supported partially qualified template IDs, (i.e.
  simply ``<module>:<entity>``) as an interactive convenience which fails if
  there is more than one package with matching template names. **Since this
  format was not supported for production use and will not work with smart
  contract upgrades, it is now unavailable.**

- ``payload`` field contains contract fields as defined in the Daml template and formatted according to :doc:`../lf-value-specification`.

.. _create-response:

HTTP Response
=============

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "status": 200,
        "result": {
            "observers": [],
            "agreementText": "",
            "payload": {
                "observers": [],
                "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                "amount": "999.99",
                "currency": "USD",
                "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
            },
            "signatories": [
                "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
            ],
            "contractId": "#124:0",
            "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou",
            "completionOffset":"0000000000000084"
        }
    }

Where:

- ``status`` field matches the HTTP response status code returned in the HTTP header,
- ``result`` field contains created contract details. Keep in mind that ``templateId`` in the **JSON API** response is always fully qualified (always contains package ID).

.. _create-request-with-meta:

Create a Contract with a Command ID
***********************************

When creating a new contract or exercising a choice you may specify an optional ``meta`` field. This allows you to control various extra settings used when submitting a command to the ledger.  Each of these ``meta`` fields is optional.

.. note:: You cannot currently use ``commandIds`` anywhere else in the JSON API, but you can use it for observing the results of its commands outside the JSON API in logs or via the Ledger API's :doc:`Command Services </app-dev/services>`

.. code-block:: json

    {
      "templateId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:IouTransfer",
      "payload": {
        "observers": [],
        "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
        "amount": "999.99",
        "currency": "USD",
        "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
      },
      "meta": {
        "commandId": "a unique ID",
        "actAs": ["Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"],
        "readAs": ["PublicParty"],
        "deduplicationPeriod": {
          "durationInMillis": 10000,
          "type": "Duration"
        },
        "submissionId": "d2f941b1-ee5c-4634-9a51-1335ce6902fa"
      }
    }

Where:

- ``commandId`` -- optional field, a unique string identifying the command.
- ``actAs`` -- a non-empty list of parties, overriding the set from the JWT user; must be a subset of the JWT user's set.
- ``readAs`` -- a list of parties, overriding the set from the JWT user; must be a subset of the JWT user's set.
- ``submissionId`` -- a string, used for :doc:`deduplicating retried requests </app-dev/command-deduplication>`.  If you do not set it, a random one will be chosen, effectively treating the request as unique and disabling deduplication.
- ``deduplicationPeriod`` -- either a ``Duration`` as above, which is how far back in time prior commands will be searched for this submission, or an ``Offset`` as follows, which is the earliest ledger offset after which to search for the submission.

.. code-block:: json

        "deduplicationPeriod": {
          "offset": "0000000000000083",
          "type": "Offset"
        }

Exercise by Contract ID
***********************

The JSON command below, demonstrates how to exercise an ``Iou_Transfer`` choice on an ``Iou`` contract:

.. literalinclude:: ../../app-dev/bindings-java/quickstart/template-root/daml/Iou.daml
  :language: daml
  :start-after: -- BEGIN_IOU_TEMPLATE_TRANSFER
  :end-before: -- END_IOU_TEMPLATE_TRANSFER

HTTP Request
============

- URL: ``/v1/exercise``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "templateId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:IouTransfer",
        "choiceInterfaceId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:IouTransferInterface",
        "contractId": "#124:0",
        "choice": "Iou_Transfer",
        "argument": {
            "newOwner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        }
    }

Where:

- ``templateId`` -- contract template or interface identifier, same as in :ref:`create request <create-request-v1>`,
- ``choiceInterfaceId`` -- *optional* template or interface that defines the choice, same format as ``templateId``,
- ``contractId`` -- contract identifier, the value from the  :ref:`create response <create-response>`,
- ``choice`` -- Daml contract choice, that is being exercised,
- ``argument`` -- contract choice argument(s).

``templateId`` and ``choiceInterfaceId`` are treated as with :ref:`exercise by key <exercise-by-key-templateId-choiceInterfaceId>`.
However, because ``contractId`` is always unambiguous, you may alternatively simply specify the interface ID as the ``templateId`` argument, and ignore ``choiceInterfaceId`` entirely.
This isn't true of exercise-by-key or create-and-exercise, so we suggest treating this request as if this alternative isn't available.

.. _exercise-response:

HTTP Response
=============

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "status": 200,
        "result": {
            "exerciseResult": "#201:1",
            "events": [
                {
                    "archived": {
                        "contractId": "#124:0",
                        "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou"
                    }
                },
                {
                    "created": {
                        "observers": [],
                        "agreementText": "",
                        "payload": {
                            "iou": {
                                "observers": [],
                                "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                                "amount": "999.99",
                                "currency": "USD",
                                "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                            },
                            "newOwner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                        },
                        "signatories": [
                            "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                        ],
                        "contractId": "#201:1",
                        "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:IouTransfer"
                    }
                }
            ],
            "completionOffset":"0000000000000083"
        }
    }

Where:

- ``status`` field matches the HTTP response status code returned in the HTTP header,

- ``result`` field contains contract choice execution details:

    + ``exerciseResult`` field contains the return value of the exercised contract choice.
    + ``events`` contains an array of contracts that were archived and created as part of the choice execution. The array may contain: **zero or many** ``{"archived": {...}}`` and **zero or many** ``{"created": {...}}`` elements. The order of the contracts is the same as on the ledger.
    + ``completionOffset`` is the ledger offset of the transaction containing the exercise's ledger changes.


Exercise by Contract Key
************************

The JSON command below, demonstrates how to exercise the ``Archive`` choice on the ``Account`` contract with a ``(Party, Text)`` :doc:`contract key </daml/reference/contract-keys>` defined like this:

.. code-block:: daml

    template Account with
        owner : Party
        number : Text
        status : AccountStatus
      where
        signatory owner
        key (owner, number) : (Party, Text)
        maintainer key._1


HTTP Request
============

- URL: ``/v1/exercise``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:Account",
        "key": {
            "_1": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
            "_2": "abc123"
        },
        "choiceInterfaceId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:AccountInterface",
        "choice": "Archive",
        "argument": {}
    }

Where:

- ``templateId`` -- contract template identifier, same as in :ref:`create request <create-request-v1>`,
- ``key`` -- contract key, formatted according to the :doc:`../lf-value-specification`,
- ``choiceInterfaceId`` -- *optional* template or interface that defines the choice, same format as ``templateId``,
- ``choice`` -- Daml contract choice, that is being exercised,
- ``argument`` -- contract choice argument(s), empty, because ``Archive`` does not take any.

.. _exercise-by-key-templateId-choiceInterfaceId:

``key`` is always searched in relation to the ``templateId``.
The ``choice``, on the other hand, is searched according to ``choiceInterfaceId``; if ``choiceInterfaceId`` is not specified, ``templateId`` is its default.
We recommend always specifying ``choiceInterfaceId`` when invoking an interface choice; however, if the set of Daml-LF packages on the participant only contains one choice with a given name associated with ``templateId``, that choice will be exercised, regardless of where it is defined.
If a template *and* one or more of the interfaces it implements declares a choice, and ``choiceInterfaceId`` is not used, the one directly defined on the choice will be exercised.
If choice selection is still ambiguous given these rules, the endpoint will fail as if the choice isn't defined.

HTTP Response
=============

Formatted similar to :ref:`Exercise by Contract ID response <exercise-response>`.

Create and Exercise in the Same Transaction
*******************************************

This command allows creating a contract and exercising a choice on the newly created contract in the same transaction.

HTTP Request
============

- URL: ``/v1/create-and-exercise``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou",
      "payload": {
        "observers": [],
        "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
        "amount": "999.99",
        "currency": "USD",
        "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
      },
      "choiceInterfaceId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:IouInterface",
      "choice": "Iou_Transfer",
      "argument": {
        "newOwner": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
      }
    }

Where:

- ``templateId`` -- the initial contract template identifier, in the same format as in the :ref:`create request <create-request-v1>`,
- ``payload`` -- the initial contract fields as defined in the Daml template and formatted according to :doc:`../lf-value-specification`,
- ``choiceInterfaceId`` -- *optional* template or interface that defines the choice, same format as ``templateId``,
- ``choice`` -- Daml contract choice, that is being exercised,
- ``argument`` -- contract choice argument(s).

``templateId`` and ``choiceInterfaceId`` are treated as with :ref:`exercise by key <exercise-by-key-templateId-choiceInterfaceId>`, with the exception that it is ``payload``, not ``key``, strictly interpreted according to ``templateId``.

HTTP Response
=============

Please note that the response below is for a consuming choice, so it contains:

- ``created`` and ``archived`` events for the initial contract (``"contractId": "#1:0"``), which was created and archived right away when a consuming choice was exercised on it,
- a ``created`` event for the contract that is the result of exercising the choice (``"contractId": "#1:2"``).

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "result": {
        "exerciseResult": "#1:2",
        "events": [
          {
            "created": {
              "observers": [],
              "agreementText": "",
              "payload": {
                "observers": [],
                "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                "amount": "999.99",
                "currency": "USD",
                "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
              },
              "signatories": [
                "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
              ],
              "contractId": "#1:0",
              "templateId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:Iou"
            }
          },
          {
            "archived": {
              "contractId": "#1:0",
              "templateId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:Iou"
            }
          },
          {
            "created": {
              "observers": [
                "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
              ],
              "agreementText": "",
              "payload": {
                "iou": {
                  "observers": [],
                  "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                  "amount": "999.99",
                  "currency": "USD",
                  "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                },
                "newOwner": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
              },
              "signatories": [
                "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
              ],
              "contractId": "#1:2",
              "templateId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:IouTransfer"
            }
          }
        ]
      },
      "status": 200
    }

Fetch Contract by Contract ID
*****************************

HTTP Request
============

- URL: ``/v1/fetch``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

application/json body:

.. code-block:: json

    {
      "contractId": "0031d4987d68ef429ce1288ef1db6f90753e455de13de32b97c5c80cb9eccc01ddca101220b49c913ec64072afcdfc220c31d0e54553fb2bdfe583ee2179be7598aff22bca",
      "templateId": "a3b788b4dc18dc060bfb82366ae6dc055b1e361d646d5cfdb1b729607e344336:Iou:IouTransfer"
    }


``readers`` may be passed as with :ref:`Query <sync-query-req>`.
``templateId`` is optional, but you are strongly advised to always pass it explicitly to minimize the data read from the Ledger API to answer the query. It can be either a template ID or an interface ID.

Contract Not Found HTTP Response
================================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "status": 200,
        "result": null
    }

Contract Found HTTP Response
============================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "status": 200,
        "result": {
            "observers": [],
            "agreementText": "",
            "payload": {
                "iou": {
                    "observers": [],
                    "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                    "amount": "999.99",
                    "currency": "USD",
                    "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                },
                "newOwner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
            },
            "signatories": [
                "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
            ],
            "contractId": "#201:1",
            "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:IouTransfer"
        }
    }

Fetch Contract by Key
*********************

Show the currently active contract that matches a given key.

The websocket endpoint `/v1/stream/fetch <#fetch-by-key-contracts-stream>`__ can
be used to search multiple keys in the same request, or in place of iteratively
invoking this endpoint to respond to changes on the ledger.

HTTP Request
============

- URL: ``/v1/fetch``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:Account",
        "key": {
            "_1": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
            "_2": "abc123"
        }
    }

``readers`` may be passed as with :ref:`Query <sync-query-req>`.

Contract Not Found HTTP Response
================================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "status": 200,
        "result": null
    }

Contract Found HTTP Response
============================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "status": 200,
        "result": {
            "observers": [],
            "agreementText": "",
            "payload": {
                "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                "number": "abc123",
                "status": {
                    "tag": "Enabled",
                    "value": "2020-01-01T00:00:01Z"
                }
            },
            "signatories": [
                "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
            ],
            "key": {
                "_1": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                "_2": "abc123"
            },
            "contractId": "#697:0",
            "templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:Account"
        }
    }


Get All Active Contracts
************************

List all currently active contracts for all known templates.

.. note:: Retrieved contracts do not get persisted into a query store database. Query store is a search index and can be used to optimize search latency. See :ref:`Start HTTP service <start-http-service>` for information on how to start JSON API service with a query store enabled.

.. note:: You can only query active contracts with the ``/v1/query`` endpoint. Archived contracts (those that were archived or consumed during an exercise operation) will not be shown in the results.

HTTP Request
============

- URL: ``/v1/query``
- Method: ``GET``
- Content: <EMPTY>

HTTP Response
=============

The response is the same as for the POST method below.

Get All Active Contracts Matching a Given Query
***********************************************

List currently active contracts that match a given query.

The websocket endpoint `/v1/stream/query <#contracts-query-stream>`__ can be
used in place of iteratively invoking this endpoint to respond to changes on the
ledger.

HTTP Request
============

- URL: ``/v1/query``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. _sync-query-req:

.. code-block:: json

    {
        "templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou"],
        "readers": ["Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"]
    }

Where:

- ``templateIds`` -- either an array of contract template identifiers in the
  same format as in the :ref:`create request <create-request-v1>`.  It can also
  an array containing a single interface identifier to search through.
  Mixing of template ID's and interface ID's, or specifying more than one
  interface ID is not allowed.
- ``readers``: *optional* non-empty list of parties to query as; must be a subset of the actAs and readAs parties in the JWT.

Empty HTTP Response
===================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "status": 200,
        "result": []
    }

Nonempty HTTP Response
======================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "result": [
            {
                "observers": [],
                "agreementText": "",
                "payload": {
                    "observers": [],
                    "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                    "amount": "999.99",
                    "currency": "USD",
                    "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                },
                "signatories": [
                    "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                ],
                "contractId": "#52:0",
                "templateId": "b10d22d6c2f2fae41b353315cf893ed66996ecb0abe4424ea6a81576918f658a:Iou:Iou"
            }
        ],
        "status": 200
    }

Where

- ``result`` contains an array of contracts, each contract formatted according to :doc:`../lf-value-specification`,
- ``status`` matches the HTTP status code returned in the HTTP header.

Nonempty HTTP Response With Unknown Template IDs Warning
========================================================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "warnings": {
            "unknownTemplateIds": ["UnknownModule:UnknownEntity"]
        },
        "result": [
            {
                "observers": [],
                "agreementText": "",
                "payload": {
                    "observers": [],
                    "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                    "amount": "999.99",
                    "currency": "USD",
                    "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                },
                "signatories": [
                    "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                ],
                "contractId": "#52:0",
                "templateId": "b10d22d6c2f2fae41b353315cf893ed66996ecb0abe4424ea6a81576918f658a:Iou:Iou"
            }
        ],
        "status": 200
    }

Fetch Parties by Identifiers
****************************

- URL: ``/v1/parties``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    ["Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d", "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d", "Dave::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"]

If an empty JSON array is passed: ``[]``, this endpoint returns BadRequest(400) error:

.. code-block:: json

    {
      "status": 400,
      "errors": [
        "JsonReaderError. Cannot read JSON: <[]>. Cause: spray.json.DeserializationException: must be a list with at least 1 element"
      ]
    }

HTTP Response
=============

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "status": 200,
      "result": [
        {
          "identifier": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
          "displayName": "Alice & Co. LLC",
          "isLocal": true
        },
        {
          "identifier": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
          "displayName": "Bob & Co. LLC",
          "isLocal": true
        },
        {
          "identifier": "Dave::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
          "isLocal": true
        }
      ]
    }

Please note that the order of the party objects in the response is not guaranteed to match the order of the passed party identifiers.

Where

- ``identifier`` -- a stable unique identifier of a Daml party,
- ``displayName`` -- optional human readable name associated with the party. Might not be unique,
- ``isLocal`` -- true if party is hosted by the backing participant.

Response With Unknown Parties Warning
=====================================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "result": [
        {
          "identifier": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
          "displayName": "Alice & Co. LLC",
          "isLocal": true
        }
      ],
      "warnings": {
        "unknownParties": ["Erin"]
      },
      "status": 200
    }

The ``result`` might be an empty JSON array if none of the requested parties is known.

Fetch All Known Parties
***********************

- URL: ``/v1/parties``
- Method: ``GET``
- Content: <EMPTY>

HTTP Response
=============

The response is the same as for the POST method above.

Allocate a New Party
********************

This endpoint is a JSON API proxy for the Ledger API's :ref:`AllocatePartyRequest <com.daml.ledger.api.v1.admin.AllocatePartyRequest>`. For more information about party management, please refer to :ref:`Provisioning Identifiers <provisioning-ledger-identifiers>` part of the Ledger API documentation.

HTTP Request
============

- URL: ``/v1/parties/allocate``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "identifierHint": "Carol",
      "displayName": "Carol & Co. LLC"
    }

Please refer to :ref:`AllocateParty <com.daml.ledger.api.v1.admin.AllocatePartyRequest>` documentation for information about the meaning of the fields.

All fields in the request are optional, this means that an empty JSON object is a valid request to allocate a new party:

.. code-block:: json

    {}

HTTP Response
=============

.. code-block:: json

    {
      "result": {
        "identifier": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
        "displayName": "Carol & Co. LLC",
        "isLocal": true
      },
      "status": 200
    }


Create a New User
*****************

This endpoint exposes the Ledger API's :ref:`CreateUser RPC <com.daml.ledger.api.v1.admin.createuserrequest>`.

HTTP Request
============

- URL: ``/v1/user/create``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "userId": "carol",
      "primaryParty": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
      "rights": [
        {
          "type": "CanActAs",
          "party": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "ParticipantAdmin"
        }
      ]
    }

Please refer to :ref:`CreateUser RPC <com.daml.ledger.api.v1.admin.createuserrequest>` documentation for information about the meaning of the fields.

Only the userId fields in the request is required, this means that an JSON object containing only it is a valid request to create a new user.

HTTP Response
=============

.. code-block:: json

    {
      "result": {},
      "status": 200
    }


Get Authenticated User Information
**********************************

This endpoint exposes the Ledger API's :ref:`GetUser RPC <com.daml.ledger.api.v1.admin.getuserrequest>`.

The user ID will always be filled out with the user specified via the currently used user token.

HTTP Request
============

- URL: ``/v1/user``
- Method: ``GET``

HTTP Response
=============

.. code-block:: json

    {
      "result": {
        "userId": "carol",
        "primaryParty": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
      },
      "status": 200
    }


Get Specific User Information
*****************************

This endpoint exposes the Ledger API's :ref:`GetUser RPC <com.daml.ledger.api.v1.admin.getuserrequest>`.

HTTP Request
============

- URL: ``/v1/user``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "userId": "carol"
    }


Please refer to :ref:`GetUser RPC <com.daml.ledger.api.v1.admin.getuserrequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "result": {
        "userId": "carol",
        "primaryParty": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
      },
      "status": 200
    }

Delete Specific User
********************

This endpoint exposes the Ledger API's :ref:`DeleteUser RPC <com.daml.ledger.api.v1.admin.DeleteUserRequest>`.

HTTP Request
============

- URL: ``/v1/user/delete``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "userId": "carol"
    }


Please refer to :ref:`DeleteUser RPC <com.daml.ledger.api.v1.admin.DeleteUserRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "result": {},
      "status": 200
    }

List Users
**********

This endpoint exposes the Ledger API's :ref:`ListUsers RPC <com.daml.ledger.api.v1.admin.ListUsersRequest>`.

HTTP Request
============

- URL: ``/v1/users``
- Method: ``GET``

HTTP Response
=============

.. code-block:: json

    {
      "result": [
        {
            "userId": "carol",
            "primaryParty": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
            "userId": "bob",
            "primaryParty": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        }
      ],
      "status": 200
    }

Grant User Rights
*****************

This endpoint exposes the Ledger API's :ref:`GrantUserRights RPC <com.daml.ledger.api.v1.admin.GrantUserRightsRequest>`.

HTTP Request
============

- URL: ``/v1/user/rights/grant``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "userId": "carol",
      "rights": [
        {
          "type": "CanActAs",
          "party": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "ParticipantAdmin"
        }
      ]
    }

Please refer to :ref:`GrantUserRights RPC <com.daml.ledger.api.v1.admin.GrantUserRightsRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "result": [
        {
          "type": "CanActAs",
          "party": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "ParticipantAdmin"
        }
      ],
      "status": 200
    }

Returns the rights that were newly granted.

Revoke User Rights
******************

This endpoint exposes the Ledger API's :ref:`RevokeUserRights RPC <com.daml.ledger.api.v1.admin.RevokeUserRightsRequest>`.

HTTP Request
============

- URL: ``/v1/user/rights/revoke``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "userId": "carol",
      "rights": [
        {
          "type": "CanActAs",
          "party": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "ParticipantAdmin"
        }
      ]
    }

Please refer to :ref:`RevokeUserRights RPC <com.daml.ledger.api.v1.admin.RevokeUserRightsRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "result": [
        {
          "type": "CanActAs",
          "party": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "ParticipantAdmin"
        }
      ],
      "status": 200
    }

Returns the rights that were actually granted.

List Authenticated User Rights
******************************

This endpoint exposes the Ledger API's :ref:`ListUserRights RPC <com.daml.ledger.api.v1.admin.ListUserRightsRequest>`.

The user ID will always be filled out with the user specified via the currently used user token.

HTTP Request
============

- URL: ``/v1/user/rights``
- Method: ``GET``

HTTP Response
=============

.. code-block:: json

    {
      "result": [
        {
          "type": "CanActAs",
          "party": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "ParticipantAdmin"
        }
      ],
      "status": 200
    }

List Specific User Rights
*************************

This endpoint exposes the Ledger API's :ref:`ListUserRights RPC <com.daml.ledger.api.v1.admin.ListUserRightsRequest>`.

HTTP Request
============

- URL: ``/v1/user/rights``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "userId": "carol"
    }

Please refer to :ref:`ListUserRights RPC <com.daml.ledger.api.v1.admin.ListUserRightsRequest>` documentation for information about the meaning of the fields.

HTTP Response
=============

.. code-block:: json

    {
      "result": [
        {
          "type": "CanActAs",
          "party": "Carol::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "CanReadAs",
          "party": "Bob::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
        },
        {
          "type": "ParticipantAdmin"
        }
      ],
      "status": 200
    }

List All DALF Packages
**********************

HTTP Request
============

- URL: ``/v1/packages``
- Method: ``GET``
- Content: <EMPTY>

HTTP Response
=============

.. code-block:: json

    {
      "result": [
        "c1f1f00558799eec139fb4f4c76f95fb52fa1837a5dd29600baa1c8ed1bdccfd",
        "733e38d36a2759688a4b2c4cec69d48e7b55ecc8dedc8067b815926c917a182a",
        "bfcd37bd6b84768e86e432f5f6c33e25d9e7724a9d42e33875ff74f6348e733f",
        "40f452260bef3f29dede136108fc08a88d5a5250310281067087da6f0baddff7",
        "8a7806365bbd98d88b4c13832ebfa305f6abaeaf32cfa2b7dd25c4fa489b79fb"
      ],
      "status": 200
    }

Where ``result`` is the JSON array containing the package IDs of all loaded DALFs.

Download a DALF Package
***********************

HTTP Request
============

- URL: ``/v1/packages/<package ID>``
- Method: ``GET``
- Content: <EMPTY>

Note that the desired package ID is specified in the URL.

HTTP Response, status: 200 OK
=============================

- Transfer-Encoding: ``chunked``
- Content-Type: ``application/octet-stream``
- Content: <DALF bytes>

The content (body) of the HTTP response contains raw DALF package bytes, without any encoding. Note that the package ID specified in the URL is actually the SHA-256 hash of the downloaded DALF package and can be used to validate the integrity of the downloaded content.

HTTP Response With Error, Any Status Different from 200 OK
==========================================================

Any status different from ``200 OK`` will be in the format specified below.

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "errors": [
            "io.grpc.StatusRuntimeException: NOT_FOUND"
        ],
        "status": 500
    }

Upload a DAR File
*****************

HTTP Request
============

- URL: ``/v1/packages``
- Method: ``POST``
- Content-Type: ``application/octet-stream``
- Content: <DAR bytes>

The content (body) of the HTTP request contains raw DAR file bytes, without any encoding.

HTTP Response, Status: 200 OK
=============================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "result": 1,
        "status": 200
    }

HTTP Response With Error
========================

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
        "errors": [
            "io.grpc.StatusRuntimeException: INVALID_ARGUMENT: Invalid argument: Invalid DAR: package-upload, content: [}]"
        ],
        "status": 500
    }

Metering Report
***************

For a description of participant metering, the parameters, and the report format see
the :doc:`Participant Metering <../../ops/metering>`.

- URL: ``/v1/metering-report``
- Method: ``POST``
- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "from": "2022-01-01",
      "to": "2022-02-01",
      "application": "some-application"
    }


HTTP Response
=============

- Content-Type: ``application/json``
- Content:

.. code-block:: json

    {
      "status": 200,
      "result": {
        "participant": "some-participant",
        "request": {
          "from": "2022-01-01T00:00:00Z",
          "to": "2022-02-01T00:00:00Z"
        },
        "final": true,
        "applications": [
          {
            "application": "some-application",
            "events": 42
          }
        ]
      }
    }


Streaming API
*************

Two subprotocols must be passed with every request, as described in
`Auth via WebSockets <#auth-via-websockets>`__.

JavaScript/Node.js example demonstrating how to establish Streaming API connection:

.. code-block:: javascript

    const wsProtocol = "daml.ws.auth";
    const tokenPrefix = "jwt.token.";
    const jwt =
      "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwczovL2RhbWwuY29tL2xlZGdlci1hcGkiOnsibGVkZ2VySWQiOiJNeUxlZGdlciIsImFwcGxpY2F0aW9uSWQiOiJIVFRQLUpTT04tQVBJLUdhdGV3YXkiLCJhY3RBcyI6WyJBbGljZSJdfX0.34zzF_fbWv7p60r5s1kKzwndvGdsJDX-W4Xhm4oVdp";
    const subprotocols = [`${tokenPrefix}${jwt}`, wsProtocol];

    const ws = new WebSocket("ws://localhost:7575/v1/stream/query", subprotocols);

    ws.addEventListener("open", function open() {
      ws.send(JSON.stringify({templateIds: ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou"]}));
    });

    ws.addEventListener("message", function incoming(data) {
      console.log(data);
    });

Please note that Streaming API does not allow multiple requests over the same WebSocket connection. The server returns an error and disconnects if second request received over the same WebSocket connection.

Error and Warning Reporting
===========================

Errors and warnings reported as part of the regular ``on-message`` flow: ``ws.addEventListener("message", ...)``.

Streaming API error messages formatted the same way as :ref:`synchronous API errors <error-format>`.

Streaming API reports only one type of warnings -- unknown template IDs, which is formatted as:

.. code-block:: none

    {"warnings":{"unknownTemplateIds":<JSON Array of template ID strings>>}}

Error and Warning Examples
--------------------------

.. code-block:: none

    {"warnings": {"unknownTemplateIds": ["UnknownModule:UnknownEntity"]}}

    {
      "errors":["JsonReaderError. Cannot read JSON: <{\"templateIds\":[]}>. Cause: spray.json.DeserializationException: search requires at least one item in 'templateIds'"],
      "status":400
    }

    {
      "errors":["Multiple requests over the same WebSocket connection are not allowed."],
      "status":400
    }

    {
      "errors":["Could not resolve any template ID from request."],
      "status":400
    }

Contracts Query Stream
======================

- URL: ``/v1/stream/query``
- Scheme: ``ws``
- Protocol: ``WebSocket``

List currently active contracts that match a given query, with
continuous updates.

Simpler use-cases that do not require continuous updates should use the simpler
`/v1/query <#get-all-active-contracts-matching-a-given-query>`__ endpoint
instead.

``application/json`` body must be sent first, formatted according to the
:doc:`search-query-language`::

    {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou"]}

Multiple queries may be specified in an array, for overlapping or
different sets of template IDs.::

    [
        {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou"]},
        {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:OtherIou:OtherIou"]},
    ]

Only one interface ID can be provided in ``templateIds``.::

    [
        {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Ifc:Ifc"]}
    ]

Mixing of template ID's and interface ID's or specifying more than one interface ID across queries is not allowed. BadRequest(400) error will be returned.::

    [
        {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou"]},
        {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Ifc:Ifc"]}
    ]


Queries have two ways to specify an offset.

An ``offset``, a string supplied by an earlier query output message, may
optionally be specified alongside each query itself::

    [
        {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:IouTransfer"]},
        {"templateIds": ["11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Iou:Iou"], "offset": "5609"}
    ]

If specified, the stream will include only contract creations and
archivals *after* the response body that included that offset.  Queries
with no offset will begin with all active contracts for that query, as
usual.

If an offset is specified *before* the queries, as a separate body, it
will be used as a default offset for all queries that do not include an
offset themselves::

    {"offset": "4307"}

For example, if this message preceded the above 3-query example, it
would be as if ``"4307"`` had been specified for the first two queries,
while ``"5609"`` would be used for the third query.

If any offset has been pruned, the websocket will immediately fail with
code 1011 and message ``internal error``.

The output is a series of JSON documents, each ``payload`` formatted
according to :doc:`../lf-value-specification`::

    {
        "events": [{
            "created": {
                "observers": [],
                "agreementText": "",
                "payload": {
                    "observers": [],
                    "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                    "amount": "999.99",
                    "currency": "USD",
                    "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                },
                "signatories": ["Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"],
                "contractId": "#1:0",
                "templateId": "eb3b150383a979d6765b8570a17dd24ae8d8b63418ee5fd20df20ad2a1c13976:Iou:Iou"
            },
            "matchedQueries": [1, 2]
        }]
    }

where ``matchedQueries`` indicates the 0-based indices into the request
list of queries that matched this contract.

Every ``events`` block following the end of contracts that existed when
the request started includes an ``offset``.  The stream is guaranteed to
send an offset immediately at the beginning of this "live" data, which
may or may not contain any ``events``; if it does not contain events and
no events were emitted before, it may be ``null`` if there was no
transaction on the ledger
or a string representing the current ledger end;
otherwise, it will be a string.  For example, you might use it to turn
off an initial "loading" indicator::

    {
        "events": [],
        "offset": "2"
    }

.. note::

    Events in the following "live" data may include ``events`` that precede
    this ``offset`` if an earlier per-query ``offset`` was specified.

    This has been done with the intent of allowing to use per-query ``offset`` s to
    efficiently use a single connection to multiplex various requests. To give an
    example of how this would work, let's say that there are two contract templates,
    ``A`` and ``B`` . Your application first queries for ``A`` s without specifying
    an offset. Then some client-side interaction requires the application to do the
    same for ``B`` s. The application can save the latest observed offset for the
    previous query, which let's say is ``42``, and issue a new request that queries
    for all ``B`` s without specifying an offset and all ``A`` s from ``42``. While
    this happens on the client, a few more ``A`` s and ``B`` s are created and the
    new request is issued once the latest offset is ``47``. The response to this
    will contain a message with all active ``B`` s, followed by the message reporting
    the offset ``47``, followed by a stream of live updates that contains new ``A`` s
    starting from ``42`` and new ``B`` s starting from ``47`` .

To keep the stream alive, you'll occasionally see messages like this,
which can be safely ignored if you do not need to capture the last seen ledger offset::

    {"events":[],"offset":"5609"}

where ``offset`` is the last seen ledger offset.

After submitting an ``Iou_Split`` exercise, which creates two contracts
and archives the one above, the same stream will eventually produce::

    {
        "events": [{
            "archived": {
                "contractId": "#1:0",
                "templateId": "eb3b150383a979d6765b8570a17dd24ae8d8b63418ee5fd20df20ad2a1c13976:Iou:Iou"
            }
        }, {
            "created": {
                "observers": [],
                "agreementText": "",
                "payload": {
                    "observers": [],
                    "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                    "amount": "42.42",
                    "currency": "USD",
                    "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                },
                "signatories": ["Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"],
                "contractId": "#2:1",
                "templateId": "eb3b150383a979d6765b8570a17dd24ae8d8b63418ee5fd20df20ad2a1c13976:Iou:Iou"
            },
            "matchedQueries": [0, 2]
        }, {
            "created": {
                "observers": [],
                "agreementText": "",
                "payload": {
                    "observers": [],
                    "issuer": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d",
                    "amount": "957.57",
                    "currency": "USD",
                    "owner": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"
                },
                "signatories": ["Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d"],
                "contractId": "#2:2",
                "templateId": "eb3b150383a979d6765b8570a17dd24ae8d8b63418ee5fd20df20ad2a1c13976:Iou:Iou"
            },
            "matchedQueries": [1, 2]
        }],
        "offset": "3"
    }

If any template IDs are found not to resolve, the first element of the stream will report them::

    {"warnings": {"unknownTemplateIds": ["UnknownModule:UnknownEntity"]}}

and the stream will continue, provided that at least one template ID
resolved properly.

Aside from ``"created"`` and ``"archived"`` elements, ``"error"``
elements may appear, which contain a string describing the error.  The
stream will continue in these cases, rather than terminating.

Some notes on behavior:

1. Each result array means "this is what would have changed if you just
   polled ``/v1/query`` iteratively."  In particular, just as
   polling search can "miss" contracts (as a create and archive can be
   paired between polls), such contracts may or may not appear in any
   result object.

2. No ``archived`` ever contains a contract ID occurring within a
   ``created`` in the same array.  So, for example, supposing you are
   keeping an internal map of active contracts keyed by contract ID, you
   can apply the ``created`` first or the ``archived`` first, forwards,
   backwards, or in random order, and be guaranteed to get the same
   results.

3. Within a given array, if an ``archived`` and ``created`` refer to
   contracts with the same template ID and :doc:`contract key </daml/reference/contract-keys>`, the
   ``archived`` is guaranteed to occur before the ``created``.

4. Except in cases of #3, within a single response array, the order of
   ``created`` and ``archived`` is undefined and does not imply that any
   element occurred "before" or "after" any other one.

5. You will almost certainly receive contract IDs in ``archived`` that
   you never received a ``created`` for.  These are contracts that
   query filtered out, but for which the server no longer is aware of
   that.  You can safely ignore these.  However, such "phantom archives"
   *are* guaranteed to represent an actual archival *on the ledger*, so
   if you are keeping a more global dataset outside the context of this
   specific search, you can use that archival information as you wish.

Fetch by Key Contracts Stream
=============================

- URL: ``/v1/stream/fetch``
- Scheme: ``ws``
- Protocol: ``WebSocket``

List currently active contracts that match one of the given ``{templateId, key}`` pairs, with continuous updates.

Simpler use-cases that search for only a single key and do not require
continuous updates should use the simpler
`/v1/fetch <#fetch-contract-by-key>`__ endpoint instead.

The ``application/json`` body must be sent first, formatted according to the following rule:

.. code-block:: none

    [
        {"templateId": "<template ID 1>", "key": <key 1>},
        {"templateId": "<template ID 2>", "key": <key 2>},
        ...
        {"templateId": "<template ID N>", "key": <key N>}
    ]

Where:

- ``templateId`` -- contract template identifier, same as in :ref:`create request <create-request-v1>`,
- ``key`` -- contract key, formatted according to the :doc:`../lf-value-specification`,

Example:

.. code-block:: json

    [
        {"templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:Account", "key": {"_1": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d", "_2": "abc123"}},
        {"templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:Account", "key": {"_1": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d", "_2": "def345"}}
    ]

The output stream has the same format as the output from the
`Contracts Query Stream`_. For every ``archived`` event
appearing on the stream there has been a matching ``created`` event
earlier in the stream, except in the case of missing
``contractIdAtOffset`` fields in the case described below.

You may supply optional ``offset`` s for the stream, as with
query streams. However, you should supply a ``contractIdAtOffset`` with each ``{templateId,
key}`` pair. A ``contractIdAtOffset`` is the contract ID currently
associated with that pair at the point of the given offset, or ``null``
if no contract ID was associated with the pair at that offset.  For
example, with the above keys, if you had one ``"abc123"`` contract but
no ``"def345"`` contract, you might specify:

.. code-block:: json

    [
        {"templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:Account", "key": {"_1": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d", "_2": "abc123"},
         "contractIdAtOffset": "#1:0"},
        {"templateId": "11c8f3ace75868d28136adc5cfc1de265a9ee5ad73fe8f2db97510e3631096a2:Account:Account", "key": {"_1": "Alice::12202f0cb99013b0f7fe09cdac189a36f8e3c999c91927093d20c7dabcc2b0c9413d", "_2": "def345"},
         "contractIdAtOffset": null}
    ]

If every ``contractIdAtOffset`` is specified, as in the example
above, you do not receive any ``archived`` events for contracts
created before the offset *unless* those contracts are identified in a
``contractIdAtOffset``.  By contrast, if any ``contractIdAtOffset`` is
missing, ``archived`` event filtering is turned off, and you receive "phantom archives" as with query streams.

Healthcheck Endpoints
*********************

The HTTP JSON API provides two healthcheck endpoints for integration
with schedulers like
`Kubernetes <https://kubernetes.io/docs/tasks/configure-pod-container/configure-liveness-readiness-startup-probes/>`_.

Liveness Check
==============

- URL: ``/livez``
- Method: ``GET``

A status code of ``200`` indicates a successful liveness check.

This is an unauthenticated endpoint intended to be used as a liveness
probe.

Readiness Check
===============

- URL: ``/readyz``
- Method: ``GET``

A status code of ``200`` indicates a successful readiness check.

This is an unauthenticated endpoint intended to be used as a readiness
probe. It validates both the ledger connection and the database
connection.
