.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _ops-ref_index:

System Requirements
===================

Unless otherwise stated, all Daml runtime components require the following:

1. For development, one of:
  * x86-compatible systems running a modern Linux or Windows operating system
  * ARM-based Macintosh systems running MacOS 11 or above
  * Deprecated: Intel-based Macintosh systems 
2. For production deployment, an x86-compatible system running a modern Linux
   operating system
3. Java 11 or later
4. An RDBMS system, *either*:

  * PostgreSQL 11.17-15 (12+ recommended)

    *or*

  * Oracle Database 19.11 or later

5. JDBC drivers compatible with your RDBMS

In terms of hardware requirements for development, a simple Daml application
can run with a laptop using 2 GB of memory and a couple of CPU cores.
However, :ref:`a much larger environment <hardware-resources>`  is recommended for testing or production
use.

Please note that the deprecated Intel-based MacIntosh binaries are produced on a best effort basis.  At some future point, a lack of Intel Mac machines may preclude building Intel binaries which will result in Intel-based MacIntosh support changing to unsupported and unavailable.

Feature/Component System Requirements
-------------------------------------

`The JavaScript client libraries <../app-dev/bindings-ts/index.html>`_ are tested on Node 14.18.3 with TypeScript compiler 4.5.4. For best results, use these or later versions.
