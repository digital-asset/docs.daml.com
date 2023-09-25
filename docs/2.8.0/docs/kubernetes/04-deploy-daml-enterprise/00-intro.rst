.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy Daml Enterprise
######################

Daml Enterprise is a set of components that are required to run Daml applications in production (see our :doc:`Target Deployment <../01-introduction/overview>`).

There are many ways to create and manage Kubernetes objects. This section of the guide focuses on deploying Daml Enterprise to Kubernetes using popular tools. Choose one option and proceed.

* :doc:`Using Helm <01-helm-deployment/01-helm-deployment-preparation>`
* :doc:`Using Helmfile (recommended) <02-helmfile-deployment/00-intro>`
* :doc:`Using Argo CD <03-argocd-deployment/01-argocd-deployment>`

.. note::
   Throughout the following pages, unless stated otherwise, we assume that the working directory is the root of this guide's repository. We also assume you have completed the previous steps successfully.
