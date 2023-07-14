.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Lifecycling tutorials
#####################

This section explains how to lifecycle instruments in Daml Finance. Each tutorial combines a step by
step description of different workflows with supporting code.

Tutorial code
*************

To follow the tutorials, you can install the ``finance-lifecycling`` project via the Daml assistant
by executing the following commands -

On Unix-based systems execute:

.. code-block:: shell

   daml new finance-lifecycling --template=finance-lifecycling
   cd finance-lifecycling
   ./get-dependencies.sh
   daml studio

On Windows-based systems execute:

.. code-block:: shell

   daml new finance-lifecycling --template=finance-lifecycling
   cd finance-lifecycling
   get-dependencies.bat
   daml studio

Note: this will only work once Daml SDK v2.7 has been released.

Next Steps
**********

The following tutorials are available:

* The :doc:`Time-based lifecycling <fixed-rate-bond>` tutorial uses a fixed rate bond as an example
  to demonstrate time-based lifecycling.
* The :doc:`Observations <floating-rate-bond>` tutorial uses a floating rate bond as a sample
  instrument to show how Observations work. This applies to instruments that depend on the price of
  an underlying asset.
* The :doc:`Election-based lifecycling <callable-bond>` tutorial uses a callable bond to
  explain how to create and process elections. This applies to instruments that require an
  active choice by one of the stakeholders
