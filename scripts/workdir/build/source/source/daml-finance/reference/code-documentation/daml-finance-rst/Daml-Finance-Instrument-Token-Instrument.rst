.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-token-instrument-10682:

Module Daml.Finance.Instrument.Token.Instrument
===============================================

Templates
---------

.. _type-daml-finance-instrument-token-instrument-instrument-62305:

**template** `Instrument <type-daml-finance-instrument-token-instrument-instrument-62305_>`_

  Implementation of an Instrument which does not define any lifecycling logic\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - depository
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The instrument's depository\.
     * - issuer
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The instrument's issuer\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - The intrument's versioned identifier\.
     * - version
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A textual instrument version\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A description of the instrument\.
     * - validAsOf
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - Timestamp as of which the instrument is valid\. This usually coincides with the timestamp of the event that creates the instrument\. It usually does not coincide with ledger time\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-token-instrument-instrument-62305_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-token-instrument-i-72687>` **for** `Instrument <type-daml-finance-instrument-token-instrument-instrument-62305_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-token-instrument-instrument-62305_>`_

Data Types
----------

.. _type-daml-finance-instrument-token-instrument-t-51655:

**type** `T <type-daml-finance-instrument-token-instrument-t-51655_>`_
  \= `Instrument <type-daml-finance-instrument-token-instrument-instrument-62305_>`_

  Type synonym for ``Instrument``\.
