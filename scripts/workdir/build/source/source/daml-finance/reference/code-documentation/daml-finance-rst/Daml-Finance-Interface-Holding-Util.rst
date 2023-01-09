.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-holding-util-81618:

Module Daml.Finance.Interface.Holding.Util
==========================================

Functions
---------

.. _function-daml-finance-interface-holding-util-getinstrument-91004:

`getInstrument <function-daml-finance-interface-holding-util-getinstrument-91004_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>` \=\> t \-\> :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`

  Get the key of a holding\.

.. _function-daml-finance-interface-holding-util-getamount-28935:

`getAmount <function-daml-finance-interface-holding-util-getamount-28935_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>` \=\> t \-\> `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  Get the amount of a holding\.

.. _function-daml-finance-interface-holding-util-disclose-55140:

`disclose <function-daml-finance-interface-holding-util-disclose-55140_>`_
  \: (`HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ h, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ h :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`) \=\> (`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`) \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>` \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ h \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ h)

  Disclose a holding\.

.. _function-daml-finance-interface-holding-util-undisclose-86607:

`undisclose <function-daml-finance-interface-holding-util-undisclose-86607_>`_
  \: (`HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ h, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ h :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`) \=\> (`Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_, :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`) \-\> :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>` \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ h \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ h))

  Undisclose a holding\.
