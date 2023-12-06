.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Provision cloud resources with Terraform
########################################

.. note::
  If you plan to use GitOps via
  :doc:`Argo CD to deploy Daml Enterprise <../04-deploy-daml-enterprise/03-argocd-deployment/01-argocd-deployment>`
  to Kubernetes, you must fork the `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints>`__. If you plan to follow other options like
  :doc:`Helm <../04-deploy-daml-enterprise/01-helm-deployment/01-helm-deployment-preparation>`
  or :doc:`Helmfile <../04-deploy-daml-enterprise/02-helmfile-deployment/00-intro>` (recommended),
  you can directly clone the `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`__.

.. note::
   All the resources created are private. Nothing is exposed over the public Internet.

Objectives
**********

This section covers the following objectives:

* Configure access to your cloud account and `configure Terraform <https://www.terraform.io/>`_.
* Create resources in your Azure subscription required for deploying Daml Enterprise.
* Initialize databases and configure Kubernetes secrets.
* Copy Daml Enterprise container images into a private container registry.

The following diagram provides an overview of the target state for the Terraform configuration. For details, consult the `Terraform configuration files <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/tree/main/azure/terraform>`_ and the :ref:`default IPv4 addressing plan <default-addressing-plan>`.

.. tabs::
  .. tab:: Azure
    .. image:: ../images/azure.png
      :alt: Azure Infrastructure Overview

  .. tab:: AWS
    .. image:: ../images/aws.png
      :alt: AWS Infrastructure Overview

Prerequisites
*************

* Credentials to access the `Digital Asset Artifactory <https://digitalasset.jfrog.io/>`_ and pull Daml Enterprise container images
* GitHub account with access to the `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`__
* `jq <https://jqlang.github.io/jq/download/>`_ [\ ``1.5+``\ ]
* CLI client for your cloud provider of choice:

  * `Azure CLI <https://learn.microsoft.com/en-us/cli/azure/install-azure-cli>`_ [latest]
  * `AWS CLI <https://aws.amazon.com/cli/>`_ [latest]
* `Terraform <https://developer.hashicorp.com/terraform/downloads>`_ [\ ``1.4+``\ ]
* `regctl <https://github.com/regclient/regclient/blob/main/docs/install.md>`_ [\ ``0.4+``\ ]
* `PostgreSQL interactive terminal <https://www.postgresql.org/download/>`_ [\ ``14+``\ ]
* `Kubernetes command-line tool <https://kubernetes.io/docs/tasks/tools/>`_ [\ ``1.25+``\ ]
* `Helm <https://helm.sh/docs/intro/install/>`_ [\ ``3.9+``\ ]
* `Helmfile (optional) <https://helmfile.readthedocs.io/>`_ [\ ``0.150+``\ ]

Steps
*****

.. note::
   The following steps assume that you have cloned `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`__,
   and that your working directory is ``azure/terraform`` or ``aws/terraform``, depending on your cloud provider of choice.

Create SSH key to access bastion
================================

You must provide an existing SSH key pair to access the proxy (also called bastion) to be created. You can create a new one using this command:

.. code-block:: sh

   ssh-keygen -m PEM -t rsa -b 4096 -f /path/to/ssh/key -C 'bastion@zero.k8s'

.. note::
  For increased security, provide a passphrase for the created SSH key.

Set up your cloud account
=========================

.. tabs::
  .. tab:: Azure

    Log in to Azure and select the target subscription (if you have multiple ones):

    .. code-block:: bash

      az login
      az account list
      az account set --subscription <subscription_id>

  .. tab:: AWS
    Sign in to AWS with the account you would like to use.
    You may do this in multiple ways — for example, using SSO:

    .. code-block:: bash

      aws sso login --profile <your_profile>

Configure Terraform
===================

.. tabs::
  .. tab:: Azure
    To configure Terraform for your Azure subscription, follow these steps:

    * Provide an existing Azure resource group. You can create a new one with this command:

      .. code-block:: bash

        az group create --name <resource_group_name> --location <location>

    * Create your own backend configuration

    * Copy and customize the variables file `sample.tfvars <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/azure/terraform/sample.tfvars>`__. Use the resource group you just created. You can use the file name ``terraform.tfvars`` to avoid passing the argument ``--var-file=/path/to/file.tfvars`` on each run.

  .. tab:: AWS
    To configure Terraform for your AWS account, follow these steps:

    * Create your own backend configuration

    * Copy and customize the variables file `sample.tfvars <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/aws/terraform/sample.tfvars>`__. You can use the file name ``terraform.tfvars`` to avoid passing the argument ``--var-file=/path/to/file.tfvars`` on each run.

.. note::
   There are multiple ways to `configure the backend <https://developer.hashicorp.com/terraform/language/settings/backends/configuration>`_ and manage different environments (development, staging, production, and so on) within the same repository. Select the appropriate solution for your needs. For local testing, use the `Terraform default backend <https://developer.hashicorp.com/terraform/language/settings/backends/configuration#default-backend>`_.

To learn more about Terraform, consult the `Terraform documentation <https://developer.hashicorp.com/terraform/tutorials>`_.

Initialize Terraform and preview the execution plan
===================================================

To initialize Terraform and the directory containing Terraform configuration files, run this command:

.. code-block:: sh

   terraform init
   terraform plan

The last command displays the Terraform execution plan, which indicates the changes that Terraform intends to make to your cloud subscription.

Apply changes proposed in the execution plan
============================================

To apply the proposed changes in the execution plan, use this command:

.. code-block:: bash

   terraform apply

.. note::
   It initially takes 15 to 20 minutes to create a Kubernetes cluster.

Access to Kubernetes API
========================

There are different ways to configure access to the Kubernetes API using the CLI. Choose one option and proceed.

a) Using a kubectl configuration context (recommended)
------------------------------------------------------

* Open a new terminal to make an SSH tunnel (available on ``localhost:44443``\ ):

  .. code-block:: bash

     make kubectl-proxy

* Merge and switch to the new ``kubectl`` configuration (also called ``kubeconfig``\ ) to your Kubernetes cluster using the SSH tunnel:

  .. code-block:: bash

     ./bootstraps/merge-kubeconfig.sh

* Run commands such as ``kubectl``\ , ``helm``\ , and ``helmfile``\  as usual.

b) Target the kubectl configuration file
----------------------------------------

* Open a new terminal to make an SSH tunnel (available on ``localhost:44443``\ ):

  .. code-block:: bash

     make kubectl-proxy

* Set the  Kubernetes CLI configuration file (this is lost if you use a new or different terminal):

  .. code-block:: bash

     export KUBECONFIG="$(pwd)/outputs/kube/ssh.config"

* Run commands such as ``kubectl``\ , ``helm``\ , and ``helmfile``\ as usual.

Access to PostgreSQL
====================

To enable access to the provisioned PostgreSQL server:

* Open a new terminal to make an SSH tunnel (available on ``localhost:5432``\ )

  .. code-block:: bash

     make psql-proxy

* Connect to the PostgreSQL server using admin credentials:

  .. code-block:: bash

     make psql

Set up PostgreSQL & Kubernetes secrets
======================================

Complete the PostgreSQL server setup that is required for deploying Daml Enterprise components, creating roles/database, storing passwords into Key Vault, and creating Kubernetes secrets:

.. code-block:: bash

   ./bootstraps/postgresql.sh

Copy container images to private container registry
===================================================

Set environment variables to access the Digital Asset container image registry at ``digitalasset-docker.jfrog.io``:

.. code-block:: bash

  export ARTIFACTORY_USER='<your_user>'
  export ARTIFACTORY_API_KEY='<your_api_key>'

Copy container images from the Digital Asset Artifactory to the private container registry:

.. code-block:: bash

   ./bootstraps/clone-images.sh 2.7.1

Next steps
**********

At this point, all cloud resources should be provisioned and set up. Continue with the :doc:`Deploy dependencies <../03-deploy-dependencies/00-intro>` section.

Deployment details
******************

Interact with the deployment
============================

To interact with the deployment, use the ``Makefile`` under ``azure/terraform`` or ``aws/terraform``. To list all the supported commands, invoke ``make help`` or ``make``.

Access to bastion/proxy
=======================

Connect to the bastion VM provisioned using SSH:

.. code-block:: sh

   make bastion

.. note::
   Only the public IP of the machine used to run Terraform can connect by default. You can provide a static array of public IPs with the Terraform variable ``admin_public_ips``.

.. _default-addressing-plan:

Default private IPv4 addressing plan
====================================

.. tabs::
  .. tab:: Azure
    .. list-table::
      :header-rows: 1

      * - Name
        - CIDR
        - Start
        - End
        - Available IPs
      * - Virtual network
        - ``10.0.0.0/16``
        - ``10.0.0.0``
        - ``10.0.255.255``
        - ``65536``
      * - Public subnet
        - ``10.0.0.0/19``
        - ``10.0.0.0``
        - ``10.0.31.255``
        - ``8192``
      * - Private subnet
        - ``10.0.32.0/19``
        - ``10.0.32.0``
        - ``10.0.63.255``
        - ``8191``
      * - AKS internal load balancer
        - ``10.0.63.1/32``
        - ``10.0.63.1``
        - ``10.0.63.1``
        - ``1``
      * - AKS pods
        - ``10.0.64.0/19``
        - ``10.0.64.0``
        - ``10.0.95.255``
        - ``8192``
      * - AKS services
        - ``10.0.96.0/22``
        - ``10.0.96.0``
        - ``10.0.99.255``
        - ``1024``
      * - AKS ingresses
        - ``10.0.100.0/22``
        - ``10.0.100.0``
        - ``10.0.103.255``
        - ``1024``
      * - Database subnet
        - ``10.0.104.0/24``
        - ``10.0.104.0``
        - ``10.0.104.255``
        - ``256``
      * - Space (1)
        - ``10.0.105.0/17``
        - ``10.0.105.0``
        - ``10.0.127.255``
        - ``5888``
      * - Space (2)
        - ``10.0.128.0/17``
        - ``10.0.128.0``
        - ``10.0.255.255``
        - ``32768``

  .. tab:: AWS
    .. list-table::
      :header-rows: 1

      * - Name
        - IPv4 CIDR
        - Start
        - End
        - Available IPv4s
        - IPv6 CIDR
      * - Virtual network
        - ``10.0.0.0/16``
        - ``10.0.0.0``
        - ``10.0.255.255``
        - ``65536``
        - ``2a05:d016:a5b:c400::/56``
      * - Public subnet (1)
        - ``10.0.0.0/22``
        - ``10.0.0.0``
        - ``10.0.3.255``
        - ``1024``
        - ``2a05:d016:a5b:c400::/64``
      * - Public subnet (2)
        - ``10.0.4.0/22``
        - ``10.0.4.0``
        - ``10.0.7.255``
        - ``1024``
        - ``2a05:d016:a5b:c401::/64``
      * - Public subnet (3)
        - ``10.0.8.0/22``
        - ``10.0.8.0``
        - ``10.0.11.255``
        - ``1024``
        - ``2a05:d016:a5b:c402::/64``
      * - Private subnet (1)
        - ``10.0.12.0/22``
        - ``10.0.12.0``
        - ``10.0.15.255``
        - ``1024``
        - ``2a05:d016:a5b:c403::/64``
      * - Private subnet (2)
        - ``10.0.16.0/22``
        - ``10.0.16.0``
        - ``10.0.19.255``
        - ``1024``
        - ``2a05:d016:a5b:c404::/64``
      * - Private subnet (3)
        - ``10.0.20.0/22``
        - ``10.0.20.0``
        - ``10.0.23.255``
        - ``1024``
        - ``2a05:d016:a5b:c405::/64``
      * - Intra subnet (1)
        - ``10.0.24.0/19``
        - ``10.0.24.0``
        - ``10.0.27.255``
        - ``1024``
        - ``2a05:d016:a5b:c406::/64``
      * - Intra subnet (2)
        - ``10.0.28.0/19``
        - ``10.0.28.0``
        - ``10.0.31.255``
        - ``1024``
        - ``2a05:d016:a5b:c407::/64``
      * - Intra subnet (3)
        - ``10.0.32.0/19``
        - ``10.0.32.0``
        - ``10.0.35.255``
        - ``1024``
        - ``2a05:d016:a5b:c408::/64``
