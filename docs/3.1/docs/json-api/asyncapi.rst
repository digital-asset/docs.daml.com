
JSON API V2 Asyncapi definition
###############################

This section contains a copy of the asyncapi/openapi specification.

If you start Canton with the HTTP API enabled, this specification is available under http://<host>:<port>/docs/asyncapi

The sources below can be copied to `Editor swagger IO <https://editor-next.swagger.io>`_ . The editor displays a preview of the specification and generates example inputs and outputs.

The specification covers streaming (websockets) endpoints - for regular endpoints (HTTP) please see :doc:`openapi`

Properties of type: `{}` (any JSON) are DAML types as defined in the Daml template and formatted according to :doc:`lf-value-specification`.

.. literalinclude:: openapi/asyncapi.yaml
  :language: yaml