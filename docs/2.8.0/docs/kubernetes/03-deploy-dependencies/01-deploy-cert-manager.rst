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

This guide installs `cert-manager <https://cert-manager.io/docs/>`_ on a Kubernetes cluster. It is a Kubernetes add-on to help manage certificates. Canton uses the add-on to generate and renew certificates for the various components.

Prerequisites
*************

* Kubernetes 1.24+
* `Helm <https://helm.sh/docs/intro/install/>`_ and `kubectl <https://kubernetes.io/docs/tasks/tools/#kubectl>`_ installed locally
* Access to the Kubernetes cluster with the necessary permissions to install Kubernetes
  resources, including custom resource definitions and namespaces

Install cert-manager with Helm
******************************

Add the Jetstack Helm repository
================================

For access to the cert-manager Helm charts, add the ``jetstack.io`` Helm chart repository to your Helm client environment and update your local cache:

.. code-block:: bash

   helm repo add jetstack https://charts.jetstack.io

Inspect the available Helm charts in the Jetstack Helm repository:

.. code-block:: bash

   helm search repo jetstack

.. note::
   Note that Jetstack is the only supported source of cert-manager charts. Other mirrors or copies are unofficial and could represent a security risk. For more information, see the `cert-manager documentation <https://cert-manager.io/docs/installation/helm/>`_.

Install Helm chart for cert-manager
===================================

Installing the Helm charts creates the Kubernetes resources required to run cert-manager and cert-manager-csi-driver.

Install the cert-manager Helm chart, including the custom resource definitions (CRDs)
into the cert-manager namespace:

.. code-block:: bash

   helm -n cert-manager install cert-manager jetstack/cert-manager \
     --set installCRDs=true --create-namespace

Install Helm Chart for cert-manager-csi-driver
==============================================

The following command is required for cert-manager to expose Daml Enterprise services through the `Kubernetes Container Storage Interface <https://kubernetes-csi.github.io/docs/introduction.html>`_\ :

.. code-block:: bash

   helm -n cert-manager install cert-manager-csi-driver \
     jetstack/cert-manager-csi-driver

Verify the installations
========================

Verify that the cert-manager Pods are running with this command:

.. code-block:: bash

   kubectl -n cert-manager get pods

Verify that the CSI driver has been installed by running this command:

.. code-block:: bash

   helm list -aA

Alternatively, cert-manager Helm charts can be pulled using the ``helm pull`` command. This downloads the Helm charts to your local machine. You can then install the Helm charts using the ``helm install`` command after the value files are created.
