.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Install ``daml-http-json`` chart
################################

Steps
*****

1. Parameterize the Helm chart
==============================
.. note::
   The Terraform scripts parameterize the Helm values. For a standalone Helm deployment without Terraform, you must customize the value file manually (see example below).

.. tabs::
  .. tab:: Azure
    Example `http-json.yaml <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/azure/helm/values/http-json.yaml>`__:

    .. code-block:: yaml

      ---
      image:
        registry: "<container_image_registry_hostname>"
      storage:
        host: "<postgresql_server_hostname>"
        database: "myjson"
        user: "myjson"
        existingSecret:
          name: "myjson-postgresql"
          key: "myjson"
      ledgerAPI:
        host: "participant1-canton-participant.canton.svc.cluster.local"
      certManager:
        issuerGroup: certmanager.step.sm
        issuerKind: StepClusterIssuer
      tls:
        enabled: true
        certManager:
          issuerName: canton-tls-issuer
  .. tab:: AWS
    Example `http-json.yaml <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/aws/helmfile/values/http-json.yaml>`__:

    .. code-block:: yaml

      ---
      image:
        registry: "<container_image_registry_hostname>"
      storage:
        database: "myjson"
        user: "myjson"
        existingSecret:
          name: "myjson-postgresql"
          key: "myjson"
      ledgerAPI:
        host: "participant1-canton-participant.canton.svc.cluster.local"
      tls:
        enabled: true
        certManager:
          issuerName: "aws-privateca-issuer"

After you create the override file, you must edit the values to match your environment.

.. note::
   To learn about the supported attributes for ``daml-http-json``, see the `daml-http-json documentation <https://artifacthub.io/packages/helm/digital-asset/daml-http-json#parameters>`_.

2. Install the chart
====================

.. note::
  Depending on your cloud provider of choice, make sure the current directory is the ``azure/terraform`` or ``aws/terraform`` folder of your clone of the `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`__.

After the values are configured, install the chart:

.. code-block:: bash

   helm -n canton install httpjson digital-asset/daml-http-json -f helm/values/http-json.yaml

Expected output:

.. code-block:: bash

   NAME: myjson
   LAST DEPLOYED: Wed Aug 16 16:27:15 2023
   NAMESPACE: canton
   STATUS: deployed
   REVISION: 1
   TEST SUITE: None
   NOTES:
   HTTP JSON API 2.7.1 has been deployed successfully!

   More information on how to configure the HTTP JSON API service can be found in our documentation:

   https://docs.daml.com/json-api/

3. Check deployment status
==========================

You can check the status of the deployment using the following command:

.. code-block:: bash

   kubectl -n canton get pods

Expected output:

.. code-block:: bash

   NAME                                                READY   STATUS      RESTARTS   AGE
   mydomain-canton-domain-bootstrap-dcbsr              0/1     Completed   0          15m
   mydomain-canton-domain-console-6b86bf5d4f-djfj8     1/1     Running     0          15m
   mydomain-canton-domain-manager-59f8b9688d-kdgbk     1/1     Running     0          15m
   mydomain-canton-domain-mediator-75f7665845-kxt49    1/1     Running     0          15m
   mydomain-canton-domain-sequencer-5768f45457-bl4pb   1/1     Running     0          15m
   mydomain-canton-domain-sequencer-5768f45457-zkxf9   1/1     Running     0          15m
   myjson-daml-http-json-59f79746d4-b5jvc              1/1     Running     0          15m
   participant1-canton-participant-647b99cb8b-dbzrw    1/1     Running     0          15m
