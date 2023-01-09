.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-holding-util-87323:

Module Daml.Finance.Holding.Util
================================

Functions
---------

.. _function-daml-finance-holding-util-transferimpl-88690:

`transferImpl <function-daml-finance-holding-util-transferimpl-88690_>`_
  \: :ref:`I <type-daml-finance-interface-holding-transferable-i-13335>` \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-transferable-i-13335>` \-\> Transfer \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-transferable-i-13335>`)

  Default implementation of transfer for the Transferable interface\.

.. _function-daml-finance-holding-util-acquireimpl-34800:

`acquireImpl <function-daml-finance-holding-util-acquireimpl-34800_>`_
  \: (`HasCreate <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hascreate-45738>`_ t, `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"lock\" t (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Lock <type-daml-finance-interface-holding-base-lock-32912>`), `HasFromInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasfrominterface-43863>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>`, `HasSignatory <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hassignatory-17507>`_ t) \=\> t \-\> Acquire \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`)

  Default implementation of ``acquire`` from the Base interface\.

.. _function-daml-finance-holding-util-releaseimpl-24083:

`releaseImpl <function-daml-finance-holding-util-releaseimpl-24083_>`_
  \: (`HasCreate <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hascreate-45738>`_ t, `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"lock\" t (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ :ref:`Lock <type-daml-finance-interface-holding-base-lock-32912>`), `HasFromInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasfrominterface-43863>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>`) \=\> t \-\> Release \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-holding-base-i-67605>`)

  Default implementation of release from the Base interface\.
