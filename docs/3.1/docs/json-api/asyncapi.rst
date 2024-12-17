
JSON API V2 Asyncapi definition
######################

This section contains a copy of the asyncapi/openapi specification.

If the canton is started with the http api enabled, this specification is available under http://YOUSERVER_HOST:PORT/docs/asyncapi

Sources below can be copied to `Editor swagger IO <https://editor-next.swagger.io>`_

The editor will show a nice preview of the specification and generate some example inputs and outputs to try.

The specification below covers streaming (websockets) endpoints - for regular endpoints (http) please navigate to :doc:`openapi`

Properties of type: `{}` (any JSON) are DAML record fields as defined in the Daml template and formatted according to :doc:`lf-value-specification`.

.. literalinclude:: openapi/asyncapi.yaml
  :language: yaml