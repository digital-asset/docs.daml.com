.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy Dependencies
###################

You can skip these steps if you are using :doc:`Helmfile to deploy <../04-deploy-daml-enterprise/02-helmfile-deployment/00-intro>`.

Objectives
**********

This section of the guide focuses on deploying components onto a Kubernetes cluster that are needed for running Daml Enterprise:

* Set up certificate management for your cluster.
* Ensure caching of container images for faster pod startups on all Kubernetes nodes (optional).

Prerequisites
*************

* Running Kubernetes cluster (1.24+) in which you have access to

  * create and manage namespaces, and
  * manage resources including *Custom Resource Definitions*.

* Following command-line tools installed:

  * `kubectl <https://kubernetes.io/docs/tasks/tools/#kubectl>`_
  * `helm <https://helm.sh/docs/intro/install/>`_

Next Steps
**********

* Complete the :doc:`Deploy cert-manager <01-deploy-cert-manager>` and :doc:`Create Certificate Issuers <02-create-certificate-issuers>` sections.
* Then you may continue with :doc:`Deploy Daml Enterprise <../04-deploy-daml-enterprise/00-intro>`.
