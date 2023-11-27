.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Argo CD deployment of Daml Enterprise
#####################################

Objectives
**********

* Set up access to the Daml Enterprise Helm charts.
* Prepare the Kubernetes environment.
* Install the Daml Enterprise components as Argo CD applications.

Prerequisites
*************

* Access to the Daml Enterprise Artifactory repository (``digitalasset-docker.jfrog.io/canton-enterprise``)
* A running `Argo CD server <https://argo-cd.readthedocs.io/en/stable/getting_started/#1-install-argo-cd>`_
* Argo CD CLI authenticated into the Argo CD server
* A running Kubernetes cluster (1.24+) in which you have access to:

  * Create and manage namespaces
  * Manage resources including Custom Resource Definitions

* Access to a PostgreSQL database (versions from 11 to 14 are supported)
* The following command-line tools installed:

  * `kubectl <https://kubernetes.io/docs/tasks/tools/#kubectl>`_
  * `Helm <https://helm.sh/docs/intro/install/>`_
  * `Argo CD CLI <https://argo-cd.readthedocs.io/en/stable/cli_installation/>`_

Introduction
************

This section walks through the steps to install Daml Enterprise on a Kubernetes cluster using `Argo CD <https://argo-cd.readthedocs.io/en/stable/>`_\ , the declarative GitOps continuous delivery tool for Kubernetes.

If you want to use GitOps, you must fork the `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`__ to commit the changes in ``manifests/configurations/values`` to deploy Kubernetes resources. You must grant Argo CD access to this forked repository and reference it with a revision (branch, SHA1 or tag) within the application's configuration.

.. note::
   For more information on Argo CD, refer to the `Argo CD getting started guide <https://argo-cd.readthedocs.io/en/stable/getting_started/>`_.

Prepare the Kubernetes environment
**********************************

1. Install Argo CD
==================

#.
  Add the Argo Helm repository:

  .. code-block:: bash

    helm repo add argo https://argoproj.github.io/argo-helm

#.
  Install Argo CD using the following command:

  .. code-block:: bash

    helm -n argocd install argocd -f azure/helm/values/argocd.yaml argo/argo-cd --create-namespace

#.
  Load the admin password into a variable:

  .. code-block:: bash

    ARGOCD_PASSWORD=$(kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data['password']}" | base64 -d)

#.
  Export the ``port-forward`` Argo CD CLI options:

  .. code-block:: bash

    ARGOCD_OPTS='--insecure --plaintext --port-forward --port-forward-namespace argocd'

#.
  Login with the Argo CD CLI:

  .. code-block:: bash

    argocd login server --username admin --password="${ARGOCD_PASSWORD}"

#.
  The cluster is private, so you must port forward the service to access the UI:

  .. code-block:: bash

    kubectl -n argocd port-forward service/argocd-server 8080:80

While the command is in process, Argo CD is available in the `browser <http://localhost:8080/>`_.

You can log in to Argo CD using the user ``admin`` and the password you retrieved in step 2.

2. Install the image puller as an Argo CD application (optional)
=================================================================

The following steps guide you to install the ``kubernetes-image-puller`` Helm chart as an Argo CD application.

Note that the parameters section overrides any value in the ``values.yaml`` file, if set.

#. 
   Apply the application file:

   .. code-block:: bash

      kubectl -n argocd apply -f azure/argocd/apps/kubernetes-image-puller.yaml

#. 
   Sync the application in the Argo CD UI. Alternatively, you can use the CLI:

.. code-block:: bash

   argocd app sync kubernetes-image-puller

.. note::
  Make sure to set the environment variable ``ARGO_OPTS`` before running Argo CD CLI commands.
  Refer to the `section in the Argo CD Getting Started guide <https://argo-cd.readthedocs.io/en/stable/getting_started/#4-login-using-the-cli>`_.

Next steps
**********

Continue with the :doc:`Deploy Argo CD applications <./02-all-in-one-argocd-deployment>` section.
