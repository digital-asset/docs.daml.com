.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Introduction
============

:doc:`Daml </index>` is a smart :doc:`contract </concepts/glossary>` language tailored for permissioned blockchains on the `Canton Network <https://www.canton.network/>`_. It enables the development of complex :doc:`multi-party </daml/patterns/multiparty-agreement>` applications.

This tutorial is for developers or architects to explore a :doc:`Daml application </app-dev/app-arch>`. It first focuses on how to install a quick-start, single domain Daml application `daml-app-template <https://github.com/DACH-NY/daml-app-template/tree/main>`_. It then walks you through the development lifecycle by extending the application with a new feature through the entire technology stack. It explains how to start up a `Daml development <https://docs.daml.com/daml/intro/0_Intro.html>`_ environment, implement backend and frontend code, and develop Daml choices as part of contract management. Detailed, step-by-step instructions build a functional Daml application and prepare you to develop more complex projects. If you are new to Daml development, begin with the :doc:`Getting Started </getting-started/index>` document.

Prerequisites
-------------

Completing this tutorial requires:

* Docker
* `direnv <https://direnv.net/>`_
* Nix
* WSL, Windows Subsystem for Linux. (Windows users only)
* Digital Asset Enterprise credentials
* Artifactory credentials from Digital Asset

.. important::
   This quick start uses some features that are only available with an :doc:`Enterprise license </canton/usermanual/downloading>`.

.. important::
   If you cannot clone a Git repository, please email `support@digitalasset.com <support@digitalasset.com>`_ for access to a compressed file that has the contents of this repository. Simply uncompress that file.