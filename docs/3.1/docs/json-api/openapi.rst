
JSON API V2 Openapi definition
#####################

Below there is copy of openapi specification.

When the canton is started with http api enabled the same specification is available under http://YOUSERVER_HOST:PORT/docs/openapi

Sources below can be copied to `Editor swagger IO <https://editor-next.swagger.io>`_

The editor will show a nice preview of the specification and generate some example inputs and outputs to try.


The specification below only covers classic http endpoints - for a streaming endpoints (websockets) please navigate to :doc:`asyncapi`

Properties of type: `{}` (any JSON) are DAML record fields as defined in the Daml template and formatted according to :doc:`lf-value-specification`.

.. literalinclude:: openapi/openapi.yaml
  :language: yaml