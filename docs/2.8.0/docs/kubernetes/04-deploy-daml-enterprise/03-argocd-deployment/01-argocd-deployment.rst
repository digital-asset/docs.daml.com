.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Argo CD Deployment of Daml Enterprise
#####################################

Objectives
**********

* Set up access to Daml Enterprise Helm charts.
* Prepare Kubernetes environment.
* Install Daml Enterprise components as an Argo CD application.

Prerequisites
*************

* Access to the Daml Enterprise Artifactory (``digitalasset-docker.jfrog.io/canton-enterprise``) repository.
* Running `Argo CD server <https://argo-cd.readthedocs.io/en/stable/getting_started/#1-install-argo-cd>`_.
* Argo CD CLI authenticated into the Argo CD server.
* Running Kubernetes cluster (1.24+) in which you have access to

  * create and manage namespaces, and
  * manage resources including *Custom Resource Definitions*.

* Access to PostgreSQL database (versions from 11 to 14 are supported).
* Following command-line tools installed:

  * `kubectl <https://kubernetes.io/docs/tasks/tools/#kubectl>`_
  * `helm <https://helm.sh/docs/intro/install/>`_
  * `Argo CD CLI <https://argo-cd.readthedocs.io/en/stable/cli_installation/>`_

Introduction
************

This section of the guide walks you through the steps of installing Daml Enterprise on a Kubernetes cluster using `Argo CD <https://argo-cd.readthedocs.io/en/stable/>`_\ , the declarative GitOps continuous delivery tool for Kubernetes.

.. note::
   For more information on Argo CD, please refer to the `Argo CD getting started guide <https://argo-cd.readthedocs.io/en/stable/getting_started/>`_.

Prepare Kubernetes Environment
******************************

1. Install Traefik ingress controller
=====================================
#. 
   Add the Traefik Helm repository:

   .. code-block:: bash

      helm repo add traefik https://traefik.github.io/charts

#. 
   Confirm Helm chart availability

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

#. 
   Install Traefik (from the root directory of this repository):

   .. code-block:: bash

      helm -n traefik install traefik --create-namespace traefik/traefik --set disableValidation=true -f src/helm/values/traefik.yaml

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
     traefik-894c9975c-z6mst   1/1     Running   0          60s

2. Install Argo CD
==================

#. Add the Argo Helm repository:

.. code-block:: bash

   helm repo add argo https://argoproj.github.io/argo-helm

#. Install Argo CD using the following command:

.. code-block:: bash

   helm -n argocd install argocd -f src/helm/values/argocd.yaml argo/argo-cd --create-namespace

#. Load the admin password into a variable:

.. code-block:: bash

   ARGOCD_PASSWORD=$(kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data['password']}" | base64 -d)

#. Export the port-forward Argo CD CLI options:

.. code-block:: bash

   ARGOCD_OPTS='--insecure --plaintext --port-forward --port-forward-namespace argocd'

#. Login with the Argo CD CLI:

.. code-block:: bash

   argocd login server --username admin --password="${ARGOCD_PASSWORD}"

#. Since the cluster is private we need to port forward the service to access the UI:

.. code-block:: bash

   kubectl -n argocd port-forward service/argocd-server 8080:80

For as long as the command is being ran, Argo CD will be available in the `browser <http://localhost:8080/>`_.

We can login to Argo CD using the user ``admin`` and the password we retrieved in step 2.

3. Install image puller as Argo CD application (optional)
=========================================================

The following steps guide you through the installation of the kubernetes-image-puller Helm chart as an Argo CD application.

Please note that the parameters section overrides any value in the values.yaml file if set.

#. 
   Apply the application file:

   .. code-block:: bash

      kubectl -n argocd apply -f src/argocd/apps/kubernetes-image-puller.yaml

#. 
   Sync the application in the Argo CD UI, alternatively you can use the CLI:

.. code-block:: bash

   argocd app sync kubernetes-image-puller

Next Steps
**********

You may now proceed to :doc:`deploying Daml Enterprise components as an Argo CD application <./02-all-in-one-argocd-deployment>`.
