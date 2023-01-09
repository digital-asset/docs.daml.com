.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-claims-types-95967:

Module Daml.Finance.Interface.Claims.Types
==========================================

Data Types
----------

.. _type-daml-finance-interface-claims-types-c-53263:

**type** `C <type-daml-finance-interface-claims-types-c-53263_>`_
  \= :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ `Deliverable <type-daml-finance-interface-claims-types-deliverable-19293_>`_ `Observable <type-daml-finance-interface-claims-types-observable-47872_>`_

  The specialized claim type\.

.. _type-daml-finance-interface-claims-types-deliverable-19293:

**type** `Deliverable <type-daml-finance-interface-claims-types-deliverable-19293_>`_
  \= :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`

  Type used to reference assets in the claim tree\.

.. _type-daml-finance-interface-claims-types-observable-47872:

**type** `Observable <type-daml-finance-interface-claims-types-observable-47872_>`_
  \= `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

  Type used to reference observables in the claim tree\.

.. _type-daml-finance-interface-claims-types-pending-95419:

**data** `Pending <type-daml-finance-interface-claims-types-pending-95419_>`_

  Type used to record pending payments\.

  .. _constr-daml-finance-interface-claims-types-pending-66756:

  `Pending <constr-daml-finance-interface-claims-types-pending-66756_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - t
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         -
       * - tag
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - instrument
         - `Deliverable <type-daml-finance-interface-claims-types-deliverable-19293_>`_
         -
       * - amount
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Pending <type-daml-finance-interface-claims-types-pending-95419_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Pending <type-daml-finance-interface-claims-types-pending-95419_>`_

.. _type-daml-finance-interface-claims-types-taggedclaim-15494:

**data** `TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494_>`_

  A claim and a textual tag\.

  .. _constr-daml-finance-interface-claims-types-taggedclaim-33377:

  `TaggedClaim <constr-daml-finance-interface-claims-types-taggedclaim-33377_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - claim
         - `C <type-daml-finance-interface-claims-types-c-53263_>`_
         -
       * - tag
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494_>`_

  **instance** HasMethod :ref:`Claim <type-daml-finance-interface-claims-claim-claim-8835>` \"getClaims\" (GetClaims \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494_>`_\])
