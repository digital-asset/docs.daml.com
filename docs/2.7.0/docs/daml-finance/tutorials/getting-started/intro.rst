.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Getting Started
###############

This section explains how some key concepts of Daml Finance work in practice. It combines a step by
step description of different workflows with supporting Daml code.

The following tutorials are available:

* :doc:`Holding <holding>`: describes the core asset model used in Daml Finance.
* :doc:`Transfer <transfer>`: shows how to transfer ownership of a holding.
* :doc:`Settlement <settlement>`: explains how to execute multiple asset movements atomically.
* :doc:`Lifecycling <lifecycling>`: describes how lifecycle rules and events can be used to evolve
  instruments over time.

Each tutorial builds on top of the previous ones, so they should ideally be followed in order.

Download the code for the tutorials
***********************************

As a prerequisite, make sure that the :doc:`Daml SDK <../../../getting-started/installation>`
is installed on your machine.

Open a terminal and run:

.. code-block:: shell

   daml new quickstart-finance --template quickstart-finance

This creates a new folder with contents from our template. Navigate to the folder and then run the
following to download the required ``daml-finance`` packages:

.. code-block:: shell

   ./get-dependencies.sh

or, if you are using Windows

.. code-block:: shell

   ./get-dependencies.bat

Finally, you can start Daml Studio to inspect the code and run the project's scripts:

.. code-block:: shell

   daml studio
