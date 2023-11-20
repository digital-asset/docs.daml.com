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

* Access to your Kubernetes cluster via ``kubectl``

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
