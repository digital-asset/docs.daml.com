.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Deploy All-In-One Application
#############################

Objectives
**********

* All-in-one deployment of a Canton Domain, Canton Participant and Daml HTTP JSON API service.

Steps
*****

1. Set Up Repo for Argo CD
==========================

2. Customize Argo CD Application
================================

Branch out from the ``main`` branch and customize the Argo CD application:

.. code-block:: bash

   git checkout -b <branch-name>

The Argo CD application file :download:`daml-enterprise.yaml` can be customized before applying. The file contains comments and examples on how to customize the application.

.. code-block:: bash

   git add .
   git commit -m "Added application changes to the repository"
   git push

3. Apply Parent Application
===========================

.. code-block:: bash

   kubectl -n argocd apply -f src/argocd/apps/daml-enterprise.yaml

The Helm chart hierarchy should be now created and can be synced on the `Argo CD UI <http://localhost:8080>`_.

The applications should be synced in the following order:

#. Canton Participant
#. Canton Domain
#. Daml HTTP JSON API service
