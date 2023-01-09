.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-instrument-generic-instrument-67364:

Module Daml.Finance.Instrument.Generic.Instrument
=================================================

Templates
---------

.. _type-daml-finance-instrument-generic-instrument-instrument-96015:

**template** `Instrument <type-daml-finance-instrument-generic-instrument-instrument-96015_>`_

  An instrument representing a generic payoff, modelled using the Contingent Claims library\.
  The responsibility for processing lifecycle events as well as elections is delegated to the
  issuer, who is hence responsible for providing the correct ``Observable``\\s\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - depository
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The instrument depository\.
     * - issuer
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The instrument issuer\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - The identifier with corresponding version\.
     * - version
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The instrument's version\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - A human readable description of the instrument\.
     * - claims
       - :ref:`C <type-daml-finance-interface-claims-types-c-53263>`
       - The claim tree\.
     * - acquisitionTime
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - The claim's acquisition time\. This usually corresponds to the start date of the contract\.
     * - observers
       - :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`
       - Observers\.
     * - lastEventTimestamp
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` **for** `Instrument <type-daml-finance-instrument-generic-instrument-instrument-96015_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>` **for** `Instrument <type-daml-finance-instrument-generic-instrument-instrument-96015_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-instrument-generic-instrument-i-26565>` **for** `Instrument <type-daml-finance-instrument-generic-instrument-instrument-96015_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` **for** `Instrument <type-daml-finance-instrument-generic-instrument-instrument-96015_>`_

Data Types
----------

.. _type-daml-finance-instrument-generic-instrument-t-12893:

**type** `T <type-daml-finance-instrument-generic-instrument-t-12893_>`_
  \= `Instrument <type-daml-finance-instrument-generic-instrument-instrument-96015_>`_

  Type synonym for ``Instrument``\.
