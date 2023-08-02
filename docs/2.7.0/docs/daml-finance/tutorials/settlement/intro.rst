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
* The :doc:`Internal Settlement <internal>` tutorial, an extension of the
  basic :doc:`settlement <../getting-started/settlement>` getting-started tutorial, illustrates how
  holdings can be transferred within a single custodian through a settlement workflow involving
  batches and related instructions. The allocation process of such instructions involves methods for
  committing a pre-existing holding (``Pledge``), a newly created holding (``CreditReceiver``), and
  a holding received simultaneously (``PassThroughFrom``). The approval methods include taking
  delivery of a holding to an account (``TakeDelivery``), immediately nullifying the holding
  (``DebitSender``), and passing the holding through (as allocation) to another instruction
  (``PassThroughTo``).
* The :doc:`Intermediated Settlement <internal>` tutorial builds upon the
  :doc:`Internal Settlement <internal>` tutorial and, in particular, shows how to make use of a
  ``RouteProvider`` to settle instructions across account hierarchies involving more than one
  custodian.
