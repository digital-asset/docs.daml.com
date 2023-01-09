.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-swap-fpml-instrument-17241:

Module Daml.Finance.Instrument.Swap.Fpml.Instrument
===================================================

Templates
---------

.. _type-daml-finance-instrument-swap-fpml-instrument-instrument-3170:

**template** `Instrument <type-daml-finance-instrument-swap-fpml-instrument-instrument-3170_>`_

  This template models a swap specified by FpML swapStream modules\.
  It can contain one or several legs of different types\: fix or floating rates

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - depository
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The depository of the instrument\.
     * - issuer
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The issuer of the instrument\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - An identifier of the instrument\.
     * - version
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The instrument's version\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A description of the instrument\.
     * - swapStreams
       - \[:ref:`SwapStream <type-daml-finance-interface-instrument-swap-fpml-fpmltypes-swapstream-38811>`\]
       - Each element describes a stream of swap payments, for example a regular fixed or floating rate\.
     * - issuerPartyRef
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Used to the identify which counterparty is the issuer in the swapStream\.
     * - calendarDataProvider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The reference data provider to use for the holiday calendar\.
     * - currencies
       - \[:ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`\]
       - The currencies of the different swap legs, one for each swapStream\. For example, if one leg pays in USD this should be a USD cash instrument\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - The observers of the instrument\.
     * - lastEventTimestamp
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` **for** `Instrument <type-daml-finance-instrument-swap-fpml-instrument-instrument-3170_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-dynamic-instrument-i-39105>` **for** `Instrument <type-daml-finance-instrument-swap-fpml-instrument-instrument-3170_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-swap-fpml-instrument-instrument-3170_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-swap-fpml-instrument-i-71302>` **for** `Instrument <type-daml-finance-instrument-swap-fpml-instrument-instrument-3170_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-swap-fpml-instrument-instrument-3170_>`_

Data Types
----------

.. _type-daml-finance-instrument-swap-fpml-instrument-t-37762:

**type** `T <type-daml-finance-instrument-swap-fpml-instrument-t-37762_>`_
  \= `Instrument <type-daml-finance-instrument-swap-fpml-instrument-instrument-3170_>`_

  Type synonym for ``Instrument``\.
