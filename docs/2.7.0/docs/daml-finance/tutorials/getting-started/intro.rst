.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Getting Started
###############

Quickstart
**********

This section explains how some key concepts of Daml Finance work in practice. It combines a step by
step description of different workflows with supporting code.

To follow the tutorials, you can install the ``quickstart-finance`` project via the Daml assistant
by executing the following commands -

On Unix-based systems execute:

.. code-block:: shell

   daml new quickstart-finance --template=quickstart-finance
   cd quickstart-finance
   ./get-dependencies.sh
   daml studio

On Windows-based systems execute:

.. code-block:: shell

   daml new quickstart-finance --template=quickstart-finance
   cd quickstart-finance
   get-dependencies.bat
   daml studio

Reference App
*************

In addition to Daml Finance, there is also a separate ``Daml Finance Reference App``. It showcases
several of the Daml Finance capabilities in a web-based graphical user interface.

If you are interested in trying out the app locally, you can clone the
corresponding repo and follow the installation instructions on the
`Daml Finance Reference App GitHub page <https://github.com/digital-asset/daml-finance-app>`_.

Next Steps
**********

The following tutorials are available:

* :doc:`Holding <holding>`: describes the basics of holdings and how they relate to instruments.
* :doc:`Transfer <transfer>`: describes accounts, cash instrument, deposits, and transfers.
* :doc:`Settlement <settlement>`: explains how to execute multiple asset movements atomically.
* :doc:`Lifecycling <lifecycling>`: describes how lifecycle rules and events can be used to evolve
  instruments over time.
