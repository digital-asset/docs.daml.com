.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _ops-ref_index:

System Requirements
===================

Unless otherwise stated, all Daml runtime components require the following:

1. For development, an x86-compatible system running a modern Linux, Windows,
   or MacOS operating system
2. For production deployment, an x86-compatible system running a modern Linux
   operating system
3. Java 11 or later
4. An RDBMS system, *either*:

  * PostgreSQL 11.17-15 (12+ recommended)

    *or*

  * Oracle Database 19.11 or later

5. JDBC drivers compatible with your RDBMS

Daml is tested using the following specific dependencies in default installations:

1. Operating Systems:

  a. Ubuntu 20.04 for development; Ubuntu 20.04 and Debian 11 are also tested for production use
  b. Windows Server 2016
  c. MacOS 10.15 Catalina

2. `Eclipse Adoptium <https://adoptium.net>`_ version 11 for Java
3. PostgreSQL 11.17-15
4. Oracle Database 19.11

In terms of hardware requirements, minimal deployments running simple Daml applications
are regularly tested with as little as 2 GB of memory and access to a single, shared vCPU.

Feature/Component System Requirements
-------------------------------------

`The JavaScript client libraries <../app-dev/bindings-ts/index.html>`_ are tested on Node 14.18.3 with TypeScript compiler 4.5.4. For best results, use these or later versions.
