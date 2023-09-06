.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy cert-manager
###################

Objectives
**********

* Prepare your Kubernetes environment for installing cert-manager.
* Install cert-manager components using Helm.

Introduction
************

This guide aims to help installing `cert-manager <https://cert-manager.io/docs/>`_ on a Kubernetes cluster. cert-manager is a Kubernetes add-on that helps managing certificates. It is used by Canton to generate and renew certificates for the various components.

Prerequisites
*************

* Kubernetes 1.24+
* `Helm <https://helm.sh/docs/intro/install/>`_ and `Kubectl <https://kubernetes.io/docs/tasks/tools/#kubectl>`_ are installed locally
* Access to the Kubernetes cluster with necessary permissions to install Kubernetes
  resources including Custom Resource Definitions and create Namespaces

Installing cert-manager with Helm
*********************************

Add the Jetstack Helm Repository
================================

In order to have access to the cert-manager Helm charts, add the ``jetstack.io`` Helm chart repository to your ``helm`` client environment and update your local cache:

.. code-block:: bash

   helm repo add jetstack https://charts.jetstack.io

Let's inspect the available Helm charts in the jetstack Helm repository:

.. code-block:: bash

   helm search repo jetstack

.. note::
   Note that jetstack is the only supported source of cert-manager charts — other mirrors or copies are unofficial and could represent security risk. For more information see the relevant `cert-manager documentation <https://cert-manager.io/docs/installation/helm/>`_.

Install Helm Chart for cert-manager
===================================

Installing the Helm charts will create the Kubernetes resources required to run cert-manager and cert-manager-csi-driver.

Install the cert-manager Helm chart, including the *Custom Resource Definitions* (CRDs)
into the ``cert-manager`` namespace:

.. code-block:: bash

   helm -n cert-manager install cert-manager jetstack/cert-manager \
     --set installCRDs=true --create-namespace

Install Helm Chart for cert-manager-csi-driver
==============================================

This is required for enabling certificates to be exposed by cert-manager to Daml Enterprise services via the `Kubernetes Container Storage Interface <https://kubernetes-csi.github.io/docs/introduction.html>`_\ :

.. code-block:: bash

   helm -n cert-manager install cert-manager-csi-driver \
     jetstack/cert-manager-csi-driver

Verify the installations
------------------------

Verify that the cert-manager pods are running by running the following command:

.. code-block:: bash

   kubectl -n cert-manager get pods

Verify that the CSI driver has been installed by running the following command:

.. code-block:: bash

   helm list -aA

Alternatively, cert-manager Helm charts can also be pulled using the ``helm pull`` command. This will download the Helm charts to your local machine. The Helm charts can then be installed using the ``helm install`` command after the value files have been created.
