.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy dependencies
###################

If you are using :doc:`Helmfile to deploy <../04-deploy-daml-enterprise/02-helmfile-deployment/00-intro>`, you can skip the following steps.

Objectives
**********

This section covers deploying the components onto a Kubernetes cluster that are needed to run Daml Enterprise:

* Set up certificate management for your cluster.
* Ensure caching of container images for faster Pod startups on all Kubernetes nodes (optional).

Prerequisites
*************

* A running Kubernetes cluster (1.24+) in which you have access to the following:

  * Create and manage namespaces
  * Manage resources, including Custom Resource Definitions

* The following command-line tools installed:

  * `kubectl <https://kubernetes.io/docs/tasks/tools/#kubectl>`_
  * `Helm <https://helm.sh/docs/intro/install/>`_

Next steps
**********

* Complete the :doc:`Deploy cert-manager <01-deploy-cert-manager>` and :doc:`Create certificate issuers <02-create-certificate-issuers>` sections.
* Then continue with the :doc:`Deploy Daml Enterprise <../04-deploy-daml-enterprise/00-intro>` section.
