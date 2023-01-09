.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-util-common-43703:

Module Daml.Finance.Interface.Util.Common
=========================================

Functions
---------

.. _function-daml-finance-interface-util-common-verify-28040:

`verify <function-daml-finance-interface-util-common-verify-28040_>`_
  \: `CanAssert <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-assert-canassert-67323>`_ m \=\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ \-\> m ()

  Verify is assertMsg with its arguments flipped\.

.. _function-daml-finance-interface-util-common-fetchinterfacebykey-89757:

`fetchInterfaceByKey <function-daml-finance-interface-util-common-fetchinterfacebykey-89757_>`_
  \: (`HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ i, `HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ i2, `HasFetchByKey <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetchbykey-54638>`_ t k, `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"cid\" t (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ i), `HasFetch <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hasfetch-52387>`_ i2) \=\> k \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ i2

  Fetch an interface by key\.

.. _function-daml-finance-interface-util-common-qty-39194:

`qty <function-daml-finance-interface-util-common-qty-39194_>`_
  \: `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>` \-\> :ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`

  Wraps an amount and an instrument key into an instrument quantity\.

.. _function-daml-finance-interface-util-common-scale-82730:

`scale <function-daml-finance-interface-util-common-scale-82730_>`_
  \: `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ \-\> :ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>` \-\> :ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`

  Scale ``quantity`` by the provided factor\.
