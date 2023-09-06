.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Helmfile Deployment of Daml Enterprise
######################################

Prerequisites
*************

* CLI tools:

  * `Kubernetes command-line tool <https://kubernetes.io/docs/tasks/tools/>`_ [\ ``1.25+``\ ]
  * `Helm installation <https://helm.sh/docs/intro/install/>`_ [\ ``3.9+``\ ]
  * `Helmfile <https://helmfile.readthedocs.io/>`_ [\ ``0.150+``\ ]

* Access to your AKS cluster

Automated Deployment
********************

* Switch ``kubectl`` context and open an SSH tunnel to the private Kubernetes API:

  .. code-block:: bash

     cd src/terraform/
     ./bootstraps/merge-kubeconfig.sh
     make kubectl-proxy
     `

* Open a new terminal at the root of this repository

* Deploy everything with Helmfile:

  .. code-block:: bash

     cd src/helmfile/
     helmfile apply --skip-diff-on-install

Manual Deployment
*****************

You can go to `src/helmfile/ <https://github.com/DACH-NY/0-to-k8-canton-doc-temp-space/tree/main/src/helmfile>`_ and inspect `helmfile.yaml <https://github.com/DACH-NY/0-to-k8-canton-doc-temp-space/blob/main/src/helmfile/helmfile.yaml>`_ and its `values <https://github.com/DACH-NY/0-to-k8-canton-doc-temp-space/tree/main/src/helmfile/values>`_.
