.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy Argo CD applications
#############################

Steps
*****

1. Set up the repo for Argo CD
==============================

Set the environment variable ``ARGO_OPTS``:

.. code-block:: bash

  export ARGOCD_OPTS='--insecure --plaintext --port-forward --port-forward-namespace argocd'

Fork the `Daml Enterprise Deployment Resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/tree/main/>`__ and add it to the Argo CD repositories:

.. code-block:: bash

  argocd repo add https://github.com/<github-handle>/daml-enterprise-deployment-blueprints.git \
    --username '<github-handle>' --password '<github-classic-api-token>'

.. note::
  You must provide your GitHub username and password because the repository is private. The username is your GitHub handle, and the password is your personal access token generated from GitHub. The `GitHub Docs <https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens>`_ describe how to generate one. The token should have the ``repo`` scope. Be sure to enable SSO in the list of tokens after the token is generated and copied.

2. Customize the Argo CD application
====================================

.. tabs::
  .. tab:: Azure
    Create a new branch starting from ``main``:

    .. code-block:: bash
      git checkout -b <new-branch-name>
    * Customize the `Argo CD application YAML file <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/azure/argocd/daml-enterprise.yaml>`__ with your forked
      GitHub repository URL and target revision (new branch name).

    * Commit changes to your new branch:

    .. code-block:: bash
      git add .
      git commit -m "Commit changes for Argo CD"
      git push
  .. tab:: AWS
    Create a new branch starting from ``main``:

    .. code-block:: bash
      git checkout -b <new-branch-name>
    * Customize the `Argo CD application YAML file <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/aws/argocd/daml-enterprise.yaml>`__ with your forked
      GitHub repository URL and target revision (new branch name).

    * Commit changes to your new branch:

    .. code-block:: bash
      git add .
      git commit -m "Commit changes for Argo CD"
      git push

3. Apply the parent application
===============================

.. tabs::
  .. tab:: Azure
    .. code-block:: bash
      kubectl -n argocd apply -f azure/argocd/daml-enterprise.yaml
  .. tab:: AWS
    .. code-block:: bash
      kubectl -n argocd apply -f aws/argocd/daml-enterprise.yaml

At this point, you should have four applications automatically synced. You can check the state in the `Argo CD UI <http://localhost:8080>`_. Access is described in the :doc:`Argo CD deployment of Daml Enterprise <./01-argocd-deployment>` section.
