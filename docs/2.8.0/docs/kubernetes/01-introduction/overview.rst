.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy on Kubernetes
####################

Audience
********

This content targets individuals with the following skills and experience:

* Basic hands-on experience with deploying and managing applications running on `Kubernetes <https://kubernetes.io/>`_.
* Deploying applications packaged as `Helm charts <https://helm.sh/>`_.
* Strong understanding of operational concepts of the chosen cloud provider, particularly monitoring and observability.
* Basic know-how of deployment and configuration of the chosen cloud provider's components to adhere to tight security requirements. This includes setting up an IDP provider (Auth0, Azure AD, and so on), and a certificate issuer (such as GCP CA Service, AWS Private CA).

Content covered
***************

This section describes the objectives and target deployment for this guide.

Objectives
==========

* Describe the required cloud resources and how to configure them.
* Describe how to set up your Kubernetes cluster.
* Walk through the steps required for deploying all Daml Enterprise components on a Kubernetes cluster using Helm, Helmfile, or Argo CD.
* Provide automation to provision cloud resources through `Terraform code <https://www.terraform.io/>`_.

.. _target-deployment:

Target deployment
=================

This document targets the following Daml Enterprise deployment on a Kubernetes cluster.

.. note::
   The goal is a highly available, production-ready deployment. Such a deployment may have associated costs, depending on your cloud provider. If you need a solution for local development only, follow the `Getting Started with Daml <https://docs.daml.com/getting-started/index.html>`_ guide instead.

.. image:: ../images/k8s-deployment.png
   :alt: Target Deployment

For an overview of the Daml Enterprise architecture, see `Introduction to Canton <https://docs.daml.com/canton/about.html>`_.

* `Canton domain <https://docs.daml.com/canton/architecture/overview.html#domain-entities>`_\: These services make up the *domain entities* of a Daml Enterprise deployment. Except for the *sequencers*, all achieve high availability via active-passive clustering.

* `Canton participant <https://docs.daml.com/concepts/glossary.html#participant-node>`_\: This service provides access to the Daml Ledger for Daml applications. You can achieve high availability through active-passive clustering.

* `HTTP JSON API service <https://docs.daml.com/json-api/index.html>`_\: This service exposes a JSON API for interacting with a *participant*\ , allowing application writers to use a simpler version of the `Ledger API <https://docs.daml.com/app-dev/ledger-api.html>`_. You can achieve high availability through active-active clustering.

You can find all of the Helm charts referenced by the target deployment architecture in the `Daml Enterprise Helm charts repository <https://github.com/digital-asset/daml-helm-charts/tree/main>`_.

Prerequisites
*************

For detailed prerequisites, see these sections:

* :doc:`Provision cloud resources <../02-provision-cloud-resources/00-intro>`
* :doc:`Deploy dependencies <../03-deploy-dependencies/00-intro>`
* :doc:`Deploy Daml Enterprise <../04-deploy-daml-enterprise/00-intro>`

.. note::
   This guide assumes you are running on Linux or macOS.
