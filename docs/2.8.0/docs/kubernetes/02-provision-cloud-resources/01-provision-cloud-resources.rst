.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Provisioning Cloud Resources with Terraform
###########################################

.. note::
  If you plan on using GitOps via
  :doc:`Argo CD to deploy Daml Enterprise <../04-deploy-daml-enterprise/03-argocd-deployment/01-argocd-deployment>`
  to Kubernetes, you will need to fork `this GitHub repository <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints>`_. If you plan to follow other options like
  :doc:`Helm <../04-deploy-daml-enterprise/01-helm-deployment/01-helm-deployment-preparation>`
  or :doc:`Helmfile <../04-deploy-daml-enterprise/02-helmfile-deployment/00-intro>` (recommended),
  you can just directly clone `this repository <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`_.

.. note::
   All the resources created are private, nothing is being exposed over the public internet.

Objectives
**********

This section of the guide focuses on the following objectives:

* Configure access to your cloud account and `configure Terraform <https://www.terraform.io/>`_.
* Initialize databases and configure Kubernetes secrets.
* Copy Daml Enterprise container images into a private container registry.

The following diagram provides an overview of the target state that the Terraform configuration is aiming to achieve. For details, please consult the `Terraform configuration files <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/tree/main/azure/terraform>`_ and the :ref:`default IPv4 addressing plan <default-addressing-plan>`.

.. tabs::
  .. tab:: Azure
    .. image:: ../images/azure.png
      :alt: Azure Infrastructure Overview

  .. tab:: AWS
    .. image:: ../images/aws.png
      :alt: AWS Infrastructure Overview

Prerequisites
*************

* Credentials to access `Digital Asset's Artifactory <https://digitalasset.jfrog.io/>`_ and pull Daml Enterprise container images
* GitHub account with access to the `accompanying resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`_
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
   All the below steps assume that you have cloned the `accompanying resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`_,
   and your working directory is ``azure/terraform`` or ``aws/terraform``, depending on your cloud provider of choice.

Create SSH Key for Accessing Bastion
====================================

You need to provide an existing SSH key pair to access the proxy (aka bastion) that will be created, you can create a new one using this command:

.. code-block:: sh

   ssh-keygen -m PEM -t rsa -b 4096 -f /path/to/ssh/key -C 'bastion@zero.k8s'

.. note::
  For increased security, it is recommended to provide a passphrase for the created SSH key.

Set Up Your Cloud Account
=========================

.. tabs::
  .. tab:: Azure

    Log in to Azure and select the target subscription (if you have multiple ones):

    .. code-block:: bash

      az login
      az account list
      az account set --subscription <subscription_id>
  
  .. tab:: AWS
    Sign in to AWS and select the target subscription (if you have multiple ones):

    .. code-block:: bash

      aws sso login --profile <your_profile>
      TODO

Configure Terraform
===================

.. tabs::
  .. tab:: Azure
    To configure Terraform for your Azure subscription, follow the below steps:

    * You need to provide an existing Azure resource group, you can create a new one using this command:

      .. code-block:: bash

        az group create --name <resource_group_name> --location <location>

    * Create your own backend configuration

    * Copy and customize the variables file `sample.tfvars <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/azure/terraform/sample.tfvars>`_, use the resource group you just created, you can use the file name ``terraform.tfvars`` to avoid passing argument ``--var-file=/path/to/file.tfvars`` each run.

  .. tab:: AWS
    To configure Terraform for your AWS subscription, follow the below steps:

    * Create your own backend configuration

    * Copy and customize the variables file `sample.tfvars <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/aws/terraform/sample.tfvars>`_, you can use the file name ``terraform.tfvars`` to avoid passing argument ``--var-file=/path/to/file.tfvars`` each run.

.. note::
   There are multiple ways to `configure the backend <https://developer.hashicorp.com/terraform/language/settings/backends/configuration>`_ and manage different environments (development, staging, production, etc.) within the same repository, you should pick the appropriate solution for your needs! For local testing the `default backend <https://developer.hashicorp.com/terraform/language/settings/backends/configuration#default-backend>`_ suffices.

To learn more about Terraform, consult the `official Terraform documentation <https://developer.hashicorp.com/terraform/tutorials>`_.

Initialize Terraform and Preview Execution Plan
===============================================

To initialize Terraform and the directory containing Terraform configuration files:

.. code-block:: sh

   terraform init
   terraform plan

The last command displays the Terraform execution plan, which indicates the changes that Terraform intends to make to your cloud subscription.

Apply Changes Proposed in the Execution Plan
============================================

To apply the proposed changes in the execution plan, use the below command:

.. code-block:: bash

   terraform apply

.. note::
   It takes 15 to 20 minutes to create a Kubernetes cluster on your first Terraform apply.

Access to Kubernetes API
========================

There are different ways to configure access to the Kubernetes API using the CLI. Choose one option and proceed.

a) Using a kubectl configuration context (recommended)
------------------------------------------------------

* Open new terminal to make an SSH tunnel (available on ``localhost:44443``\ ):

  .. code-block:: bash

     make kubectl-proxy

* Merge and switch to the new ``kubectl`` configuration (aka ``kubeconfig``\ ) to your Kubernetes cluster using the SSH tunnel:

  .. code-block:: bash

     ./bootstraps/merge-kubeconfig.sh

* Run commands ``kubectl``\ , ``helm``\ , ``helmfile``\ , etc. as usual

b) Targeting the kubectl configuration file
-------------------------------------------

* Open new terminal to make an SSH tunnel (available on ``localhost:44443``\ ):

  .. code-block:: bash

     make kubectl-proxy

* Set Kubernetes CLI configuration file (lost if you use a new/different terminal)

  .. code-block:: bash

     export KUBECONFIG="$(pwd)/outputs/kube/ssh.config"

* Run commands ``kubectl``\ , ``helm``\ , ``helmfile``\ , etc. as usual

Access to PostgreSQL
====================

To enable accessing to the provisioned PostgreSQL server:

* Open a new terminal to make an SSH tunnel (available on ``localhost:5432``\ )

  .. code-block:: bash

     make psql-proxy

* To connect to the PostgreSQL server using admin credentials:

  .. code-block:: bash

     make psql

Set up PostgreSQL & Kubernetes secrets
======================================

To complete the PostgreSQL server setup required for deploying Daml Enterprise components, creating roles/database, storing passwords into Key Vault, and creating Kubernetes secrets:

.. code-block:: bash

   ./bootstraps/postgresql.sh

Copy Container Images to the Private Registry
=============================================

Set environment variables to access Digital Asset's container image registry at ``digitalasset-docker.jfrog.io``:

.. code-block:: bash

  export ARTIFACTORY_USER='<your_user>'
  export ARTIFACTORY_API_KEY='<your_api_key>'

To copy container images from Digital Asset's Artifactory to the private container registry, run the following:

.. code-block:: bash

   ./bootstraps/clone-images.sh 2.7.1

Next Steps
**********

Now you should have all cloud resources provisioned and set up, so you may proceed to :doc:`Deploy Dependencies <../03-deploy-dependencies/00-intro>`.

Deployment Details
******************

Interacting with deployment
===========================

To help you interact with the deployment, we have added a ``Makefile`` under ``azure/terraform`` and ``aws/terraform``. You may list all the supported commands available by invoking ``make help`` or simply ``make``.

Access to bastion/proxy
=======================

To connect to the bastion VM provisioned using SSH:

.. code-block:: sh

   make bastion

.. note::
   Only the public IP of the machine used to run Terraform apply is allowed to connect by default, you can provide a static array of public IPs with Terraform variable ``admin_public_ips``.

.. _default-addressing-plan:

Default Private IPv4 Addressing Plan
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
          - CIDR
          - Start
          - End
          - Available IPs
