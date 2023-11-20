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

* Access to your Kubernetes cluster via ``kubectl``

Automated Deployment
********************

.. tabs::
  .. tab:: Azure
    * Switch ``kubectl`` context and open an SSH tunnel to the private Kubernetes API:

      .. code-block:: bash

         cd azure/terraform/
         ./bootstraps/merge-kubeconfig.sh
         make kubectl-proxy
         `

    * Open a new terminal at the root of this repository

    * Deploy everything with Helmfile:

      .. code-block:: bash

         cd azure/helmfile/
         helmfile apply --skip-diff-on-install

  .. tab:: AWS
    * Switch ``kubectl`` context and open an SSH tunnel to the private Kubernetes API:

      .. code-block:: bash

         cd aws/terraform/
         ./bootstraps/merge-kubeconfig.sh
         make kubectl-proxy
         `

    * Open a new terminal at the root of this repository

    * Deploy everything with Helmfile:

      .. code-block:: bash

         cd aws/helmfile/
         helmfile apply --skip-diff-on-install
