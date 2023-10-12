.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy Daml Enterprise
######################

Daml Enterprise is a set of components that are required to run Daml applications in production (see our :doc:`Target Deployment <../01-introduction/overview>`).

There are many ways to create and manage Kubernetes objects. This section of the guide focuses on deploying Daml Enterprise to Kubernetes using popular tools. Choose one option and proceed.

* :doc:`Using Helm <01-helm-deployment/01-helm-deployment-preparation>`
* :doc:`Using Helmfile (recommended) <02-helmfile-deployment/00-intro>`
* :doc:`Using Argo CD <03-argocd-deployment/01-argocd-deployment>`

If you deploy components independently, the following order should be followed:
#. Canton Participant
#. Canton Domain (bootstraps both the domain itself and its participant)
#. Daml HTTP JSON API service (requires a functional Ledger API)

.. note::
   Throughout the following pages, unless stated otherwise, we assume that the working directory is the root of your clone of the `accompanying resources' repository <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/tree/main/>`_. We also assume you have completed the previous steps successfully.
