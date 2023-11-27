.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy Daml Enterprise
######################

Daml Enterprise is a set of components required to run Daml applications in production (see the :doc:`Deploy on Kubernetes <../01-introduction/overview>`) section.

There are many ways to create and manage Kubernetes objects. This section focuses on deploying Daml Enterprise to Kubernetes using popular tools. Choose one option and proceed.

* :doc:`Using Helm <01-helm-deployment/01-helm-deployment-preparation>`
* :doc:`Using Helmfile (recommended) <02-helmfile-deployment/00-intro>`
* :doc:`Using Argo CD <03-argocd-deployment/01-argocd-deployment>`

If you deploy components independently, follow this sequence:

#. Canton participant
#. Canton domain (bootstraps both the domain itself and its participant)
#. Daml HTTP JSON API service (requires a functional Ledger API)

.. note::
   The following sections assume that the working directory is the root of your clone of the `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/tree/main/>`_, unless stated otherwise. Be sure that you completed the previous steps successfully.
