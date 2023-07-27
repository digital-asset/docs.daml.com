.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Settlement
##########

Quickstart
**********

This section explains how settlement processes of Daml Finance work in more detail. It combines a
step by step description of different workflows with supporting code.

To follow the tutorials, you can install the ``tutorial-settlement`` project via the Daml assistant
by executing the following commands -

On Unix-based systems execute:

.. code-block:: shell

   daml new tutorial-settlement --template=tutorial-settlement
   cd tutorial-settlement
   ./get-dependencies.sh
   daml studio

On Windows-based systems execute:

.. code-block:: shell

   daml new tutorial-settlement --template=tutorial-settlement
   cd tutorial-settlement
   get-dependencies.bat
   daml studio

Next Steps
**********

The following tutorials are available:

* The :doc:`Enhanced Transfers <transfer>` tutorial builds upon the
  basic :doc:`transfer <../getting-started/transfer>` tutorial from the getting-started section.
  Specifically, we explore how to configure the controllers that need to authorize incoming
  transfers (credits) and outgoing transfers (debits) to and from an account, respectively.
* Internal Settlement