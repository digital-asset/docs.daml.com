
JSON API V2 Openapi definition
##############################

Below there is copy of openapi specification.

When the canton is started with http api enabled the same specification is available under http://YOUSERVER_HOST:PORT/docs/openapi

The sources below can be copied to `Editor swagger IO <https://editor-next.swagger.io>`_

The editor displays a preview of the specification and generates example inputs and outputs.

The specification covers regular http endpoints - for streaming endpoints (websockets) please navigate to :doc:`asyncapi`

Properties of type: `{}` (any JSON) are DAML record fields as defined in the Daml template and formatted according to :doc:`lf-value-specification`.

.. literalinclude:: openapi/openapi.yaml
  :language: yaml
  :lines: 1-1000

.. literalinclude:: openapi/openapi.yaml
  :language: yaml
  :lines: 1001-2000

.. literalinclude:: openapi/openapi.yaml
  :language: yaml
  :lines: 2000-