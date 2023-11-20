.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy Argo CD Applications
#############################

Steps
*****

1. Set Up Repo for Argo CD
==========================

Set the environment variable `ARGO_OPTS`:

.. code-block:: bash

  export ARGOCD_OPTS='--insecure --plaintext --port-forward --port-forward-namespace argocd'

Fork the `GitHub repository for the accompanying resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/tree/main/>`_ and add it to Argo CD repositories:

.. code-block:: bash

  argocd repo add https://github.com/<github-handle>/daml-enterprise-deployment-blueprints.git \
    --username '<github-handle>' --password '<github-classic-api-token>'

.. note::
  As the repository is private, you will need to provide your GitHub username and password.
  The `username` is your GitHub handle and the `password` is your personal access token generated
  from GitHub. Here is a `guide <https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens>`_
  on how to generate one. The token should have the `repo` scope. Make sure you enable SSO
  in the list of tokens after the token is generated and copied out.

2. Customize Argo CD Application
================================

.. tabs::
  .. tab:: Azure
    Create a new branch starting from ``main``:

    .. code-block:: bash

      git checkout -b <new-branch-name>

    * Customize the `Argo CD application YAML file <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/azure/argocd/daml-enterprise.yaml>`_ with your forked
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

    * Customize the `Argo CD application YAML file <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/blob/main/aws/argocd/daml-enterprise.yaml>`_ with your forked
      GitHub repository URL and target revision (new branch name).

    * Commit changes to your new branch:

    .. code-block:: bash

      git add .
      git commit -m "Commit changes for Argo CD"
      git push


3. Apply Parent Application
===========================

.. tabs::
  .. tab:: Azure
    .. code-block:: bash

      kubectl -n argocd apply -f azure/argocd/daml-enterprise.yaml

  .. tab:: AWS
    .. code-block:: bash

      kubectl -n argocd apply -f aws/argocd/daml-enterprise.yaml

You should have four applications automatically synced, you can check the state in the `Argo CD UI <http://localhost:8080>`_.

Access is described in :doc:`the previous step <./01-argocd-deployment>`.
