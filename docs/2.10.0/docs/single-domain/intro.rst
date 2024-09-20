.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Introduction
============

`Daml <https://docs.daml.com>`_ is a smart `contract <https://docs.daml.com/concepts/glossary.html#contract>`_ language tailored for permissioned blockchains on the `Canton Network <https://www.canton.network/>`_. It enables the development of complex `multi-party <https://docs.daml.com/daml/patterns/multiparty-agreement.html>`_ applications.

This tutorial is for developers or architects to explore a `Daml application <https://docs.daml.com/app-dev/app-arch.html>`_. It first focuses on how to install a quick-start, single domain Daml application `daml-app-template <https://github.com/DACH-NY/daml-app-template/tree/main>`_. It then walks you through the development lifecycle by extending the application with a new feature through the entire technology stack. It explains how to start up a `Daml development <https://docs.daml.com/daml/intro/0_Intro.html>`_ environment, implement backend and frontend code, and develop Daml choices as part of contract management. Detailed, step-by-step instructions build a functional Daml application and prepare you to develop more complex projects. If you are new to Daml development, begin with the `Getting Started <https://docs.daml.com/getting-started/index.html>`_ document.

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
   This quick start uses some features that are only available with an `Enterprise license <https://docs.daml.com/canton/usermanual/downloading.html>`_.

.. important::
   If you cannot clone a Git repository, please email `support@digitalasset.com <support@digitalasset.com>`_ for access to a compressed file that has the contents of this repository. Simply uncompress that file.