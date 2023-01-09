.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-equity-instrument-69265:

Module Daml.Finance.Instrument.Equity.Instrument
================================================

Templates
---------

.. _type-daml-finance-instrument-equity-instrument-instrument-90430:

**template** `Instrument <type-daml-finance-instrument-equity-instrument-instrument-90430_>`_

  An Instrument representing a common stock\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - issuer
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Issuer\.
     * - depository
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Depository\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - A textual identifier\.
     * - version
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The instrument's version\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A description of the instrument\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.
     * - validAsOf
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - Timestamp as of which the instrument is valid\. This usually coincides with the timestamp of the event that creates the instrument\. It usually does not coincide with ledger time\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-equity-instrument-instrument-90430_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-equity-instrument-i-74160>` **for** `Instrument <type-daml-finance-instrument-equity-instrument-instrument-90430_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-equity-instrument-instrument-90430_>`_

Data Types
----------

.. _type-daml-finance-instrument-equity-instrument-t-62422:

**type** `T <type-daml-finance-instrument-equity-instrument-t-62422_>`_
  \= `Instrument <type-daml-finance-instrument-equity-instrument-instrument-90430_>`_

  Type synonym for ``Instrument``\.
