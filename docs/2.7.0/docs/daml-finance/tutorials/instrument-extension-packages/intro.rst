.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Instrument Extensions Packages
##############################

This section explains how to use some of the Daml Finance instrument packages to model an array of
financial instruments. Each tutorial combines a step by step description of different workflows
with supporting code.

Tutorial code
*************

To follow the tutorials, you can install the ``finance-instruments`` project via the Daml assistant
by executing the following commands -

On Unix-based systems execute:

.. code-block:: shell

   daml new finance-instruments --template=finance-instruments
   cd finance-instruments
   ./get-dependencies.sh
   daml studio

On Windows-based systems execute:

.. code-block:: shell

   daml new finance-instruments --template=finance-instruments
   cd finance-instruments
   get-dependencies.bat
   daml studio

Note: this will only work once Daml SDK v2.7 has been released.

Next Steps
**********

The following tutorials are available:

* The :doc:`Bond Extension <bond-extension>` tutorial introduces the different types of bonds
  supported in Daml Finance out of the box.
* The :doc:`Equity Extension <equity-extension>` tutorial describes how to model the equity related
  lifecycle events like dividends, stock splits and mergers.
* The :doc:`Swap Extension <swap-extension>` tutorial describes how to use the different types of
  swaps in Daml Finance.
* The :doc:`Option Extension <option-extension>` tutorial describes the different types of option
  instruments in Daml Finance.

If you want to learn how to model custom payoffs, you can skip to the next section and have a look at the :doc:`Generic Instrument <../payoff-modeling/generic-extension>` tutorial.
