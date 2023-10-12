.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Helm Deployment of Daml Enterprise
##################################

Objectives
**********

* Set up access to Daml Enterprise Helm charts
* Prepare Kubernetes environment
* Install Daml Enterprise components with Helm

Prerequisites
*************

* CLI tools:

  * `Kubernetes command-line tool <https://kubernetes.io/docs/tasks/tools/>`_ [\ ``1.25+``\ ]
  * `Helm is installed <https://helm.sh/docs/intro/install/>`_ [\ ``3.9+``\ ]

* Access to your AKS cluster via ``kubectl``

Introduction
************

This section of the guide aims to walk through the steps of installing Daml Enterprise on a Kubernetes cluster `using Helm <https://helm.sh>`_\ , a package manager for Kubernetes. Helm charts define a set of Kubernetes resources that may be deployed together.

.. note::
   For more information on Helm, refer to the `Helm Quickstart Guide <https://helm.sh/docs/intro/quickstart/>`_.

Steps
*****

1. Adding the Digital Asset Helm chart repository
=================================================

Add the Digital Asset Helm chart repository to your local helm cache:

.. code-block:: bash

   helm repo add digital-asset https://digital-asset.github.io/daml-helm-charts/
   helm search repo digital-asset

Let's inspect the available Helm charts in the Digital Asset Helm repository:

.. code-block:: bash

   helm search repo digital-asset

Expected output:

.. code-block:: bash

   NAME                            CHART VERSION   APP VERSION     DESCRIPTION                                
   digital-asset/canton-domain      0.4.0           2.7.1           A Helm chart for Canton Domains            
   digital-asset/canton-participant 0.4.0           2.7.1           A Helm chart for Canton Participants       
   digital-asset/daml-http-json     0.4.0           2.7.1           A Helm chart for Daml HTTP JSON API service
   digital-asset/daml-trigger       0.4.0           2.7.1           A Helm chart for Daml Trigger service

2. Install Traefik ingress controller
=====================================

#. Add the Traefik Helm repository:

   .. code-block:: bash

      helm repo add traefik https://traefik.github.io/charts

#. Confirm Helm chart availability

After the previous step we should be able to search the repo for the Traefik chart:

.. code-block:: bash

     helm search repo traefik

Expected output:

.. code-block:: bash

     NAME                    CHART VERSION   APP VERSION     DESCRIPTION                                       
     traefik/traefik         23.2.0          v2.10.4         A Traefik based Kubernetes ingress controller     
     traefik/traefik-hub     1.0.6           v2.1.0          Traefik Hub Ingress Controller                    
     traefik/traefik-mesh    4.1.1           v1.4.8          Traefik Mesh - Simpler Service Mesh               
     traefik/traefikee       1.14.1          v2.10.2         Traefik Enterprise is a unified cloud-native ne...
     traefik/hub-agent       1.6.0           v1.4.2          Traefik Hub is an all-in-one global networking ...
     traefik/maesh           2.1.2           v1.3.2          Maesh - Simpler Service Mesh

#. Install Traefik:

   The following command expects that you are in the root directory of this repository.

   .. code-block:: bash

      helm -n traefik install traefik traefik/traefik --set disableValidation=true -f src/helm/values/traefik.yaml --create-namespace

Expected output:

.. code-block:: bash

     NAME: traefik
     LAST DEPLOYED: Wed Aug  2 11:08:59 2023
     NAMESPACE: traefik
     STATUS: deployed
     REVISION: 1
     TEST SUITE: None
     NOTES:
     Traefik Proxy v2.10.4 has been deployed successfully on traefik namespace !

Let us verify the traefik pods availability:

.. code-block:: bash

     kubectl -n traefik get pods

Expected output:

.. code-block:: bash

     NAME                      READY   STATUS    RESTARTS   AGE
     traefik-894c9975c-z6mst   1/1     Running   0          15m
