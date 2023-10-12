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

*If you want to use GitOps, it is mandatory to fork the `accompanying resources' GitHub repository <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`_ to be able to commit
the changes in manifests/configurations/values used to deploy Kubernetes resources.* You will need
to grant Argo CD access to this forked repository, and reference it with a revision (branch, SHA1 or tag)
within applications' configuration.

.. note::
   For more information on Argo CD, refer to the `Argo CD getting started guide <https://argo-cd.readthedocs.io/en/stable/getting_started/>`_.

Prepare Kubernetes Environment
******************************

1. Install Argo CD
==================

#. Add the Argo Helm repository:

.. code-block:: bash

   helm repo add argo https://argoproj.github.io/argo-helm

#. Install Argo CD using the following command:

.. code-block:: bash

   helm -n argocd install argocd -f azure/helm/values/argocd.yaml argo/argo-cd --create-namespace

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

2. Install image puller as Argo CD application (optional)
=========================================================

The following steps guide you through the installation of the kubernetes-image-puller Helm chart as an Argo CD application.

Note that the parameters section overrides any value in the values.yaml file if set.

#. 
   Apply the application file:

   .. code-block:: bash

      kubectl -n argocd apply -f azure/argocd/apps/kubernetes-image-puller.yaml

#. 
   Sync the application in the Argo CD UI, alternatively you can use the CLI:

.. code-block:: bash

   argocd app sync kubernetes-image-puller

.. note::
  Make sure environment variable `ARGO_OPTS` is set before running Argo CD CLI commands.
  Refer to the `relevant section <https://argo-cd.readthedocs.io/en/stable/getting_started/#4-login-using-the-cli>`_ of the Argo CD Getting Started guide.

Next Steps
**********

You may now proceed to :doc:`deploying Daml Enterprise components as Argo CD applications <./02-all-in-one-argocd-deployment>`.
