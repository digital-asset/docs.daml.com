.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-settlement-hierarchy-15826:

Module Daml.Finance.Settlement.Hierarchy
========================================

Data Types
----------

.. _type-daml-finance-settlement-hierarchy-hierarchy-68950:

**data** `Hierarchy <type-daml-finance-settlement-hierarchy-hierarchy-68950_>`_

  Data type that describes a hierarchical account structure among multiple parties for holdings
  on an instrument\.

  .. _constr-daml-finance-settlement-hierarchy-hierarchy-13149:

  `Hierarchy <constr-daml-finance-settlement-hierarchy-hierarchy-13149_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - rootCustodian
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Root custodian of the instrument\.
       * - pathsToRootCustodian
         - \[\[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\]\]
         - Paths from \"leaf\" owners to the root custodian of the instrument\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Hierarchy <type-daml-finance-settlement-hierarchy-hierarchy-68950_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Hierarchy <type-daml-finance-settlement-hierarchy-hierarchy-68950_>`_

Functions
---------

.. _function-daml-finance-settlement-hierarchy-unfoldstep-82948:

`unfoldStep <function-daml-finance-settlement-hierarchy-unfoldstep-82948_>`_
  \: `Hierarchy <type-daml-finance-settlement-hierarchy-hierarchy-68950_>`_ \-\> :ref:`Step <type-daml-finance-interface-settlement-types-step-78661>` \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ \[:ref:`RoutedStep <type-daml-finance-interface-settlement-types-routedstep-10086>`\]
