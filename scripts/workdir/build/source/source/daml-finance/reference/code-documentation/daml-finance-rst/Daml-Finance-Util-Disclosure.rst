.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-util-disclosure-73352:

Module Daml.Finance.Util.Disclosure
===================================

This module contains default implementations for the methods of the ``Disclosure`` interface\.
These are used across multiple templates in the library\.

Functions
---------

.. _function-daml-finance-util-disclosure-setobserversimpl-12973:

`setObserversImpl <function-daml-finance-util-disclosure-setobserversimpl-12973_>`_
  \: (`HasCreate <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hascreate-45738>`_ t, `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"observers\" t :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`, `HasFromInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasfrominterface-43863>`_ t :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ i, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ i :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t i) \=\> t \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (:ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>` \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ i \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`)) \-\> SetObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`)

  Default implementation for ``setObservers``\.
  The ``refUpdate`` argument is used to update the corresponding contract ``Reference`` and
  can be set to ``None`` if your template does not have an accompanying ``Reference`` contract\.

.. _function-daml-finance-util-disclosure-addobserversimpl-14106:

`addObserversImpl <function-daml-finance-util-disclosure-addobserversimpl-14106_>`_
  \: (`HasCreate <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hascreate-45738>`_ t, `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"observers\" t :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`, `HasFromInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasfrominterface-43863>`_ t :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ i, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ i :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t i) \=\> t \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (:ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>` \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ i \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`)) \-\> AddObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`)

  Default implementation for ``addObservers``\.
  The ``refUpdate`` argument is used to update the corresponding contract ``Reference`` and
  can be set to ``None`` if your template does not have an accompanying ``Reference`` contract\.

.. _function-daml-finance-util-disclosure-removeobserversimpl-85752:

`removeObserversImpl <function-daml-finance-util-disclosure-removeobserversimpl-85752_>`_
  \: (`HasCreate <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-template-functions-hascreate-45738>`_ t, `HasField <https://docs.daml.com/daml/stdlib/DA-Record.html#class-da-internal-record-hasfield-52839>`_ \"observers\" t :ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>`, `HasFromInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasfrominterface-43863>`_ t :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasInterfaceTypeRep <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hasinterfacetyperep-84221>`_ i, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ i :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`, `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t i) \=\> t \-\> `Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (:ref:`PartiesMap <type-daml-finance-interface-types-common-types-partiesmap-10862>` \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ i \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`)) \-\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>` \-\> RemoveObservers \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`Optional <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-prelude-optional-37153>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-util-disclosure-i-26993>`))

  Default implementation for ``removeObservers``\.
  The ``refUpdate`` argument is used to update the corresponding contract ``Reference`` and
  can be set to ``None`` if your template does not have an accompanying ``Reference`` contract\.
