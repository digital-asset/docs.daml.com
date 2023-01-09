.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-settlement-routeprovider-singlecustodian-83455:

Module Daml.Finance.Settlement.RouteProvider.SingleCustodian
============================================================

Templates
---------

.. _type-daml-finance-settlement-routeprovider-singlecustodian-singlecustodian-66394:

**template** `SingleCustodian <type-daml-finance-settlement-routeprovider-singlecustodian-singlecustodian-66394_>`_

  Template which implements the ``RouteProvider`` interface\.
  It is used to transform each settlement ``Step`` into a ``RoutedStep`` using a single custodian\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - provider
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - Party providing the facility\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.
     * - custodian
       - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
       - The custodian to be used to route each ``Step``\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-settlement-routeprovider-i-46608>` **for** `SingleCustodian <type-daml-finance-settlement-routeprovider-singlecustodian-singlecustodian-66394_>`_
