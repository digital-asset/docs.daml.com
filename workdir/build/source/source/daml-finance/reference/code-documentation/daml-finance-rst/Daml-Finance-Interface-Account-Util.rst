.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-account-util-56106:

Module Daml.Finance.Interface.Account.Util
==========================================

Functions
---------

.. _function-daml-finance-interface-account-util-fetchaccount-54577:

`fetchAccount <function-daml-finance-interface-account-util-fetchaccount-54577_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>` \=\> t \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ :ref:`I <type-daml-finance-interface-account-account-i-54958>`

  Fetch the account of a holding\.

.. _function-daml-finance-interface-account-util-getaccount-10955:

`getAccount <function-daml-finance-interface-account-util-getaccount-10955_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>` \=\> t \-\> :ref:`AccountKey <type-daml-finance-interface-types-common-types-accountkey-41482>`

  Get the account key of a holding\.

.. _function-daml-finance-interface-account-util-getcustodian-11392:

`getCustodian <function-daml-finance-interface-account-util-getcustodian-11392_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>` \=\> t \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  Get the custodian of a holding\.

.. _function-daml-finance-interface-account-util-getowner-32361:

`getOwner <function-daml-finance-interface-account-util-getowner-32361_>`_
  \: `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t :ref:`I <type-daml-finance-interface-holding-base-i-67605>` \=\> t \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_

  Get the owner of a holding\.
