.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-lifecycle-rule-util-40465:

Module Daml.Finance.Lifecycle.Rule.Util
=======================================

Data Types
----------

.. _type-daml-finance-lifecycle-rule-util-pending-87645:

**data** `Pending <type-daml-finance-lifecycle-rule-util-pending-87645_>`_

  Type used to record pending payments\.

  .. _constr-daml-finance-lifecycle-rule-util-pending-35372:

  `Pending <constr-daml-finance-lifecycle-rule-util-pending-35372_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         -
       * - amount
         - `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `Pending <type-daml-finance-lifecycle-rule-util-pending-87645_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `Pending <type-daml-finance-lifecycle-rule-util-pending-87645_>`_

Functions
---------

.. _function-daml-finance-lifecycle-rule-util-mergeconsumedandproduced-75314:

`mergeConsumedAndProduced <function-daml-finance-lifecycle-rule-util-mergeconsumedandproduced-75314_>`_
  \: \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\] \-\> \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\] \-\> \[`Pending <type-daml-finance-lifecycle-rule-util-pending-87645_>`_\]

  Merge consumed and produced instruments into a list of pending settlements\.
  This will only reproduce instrument and quantity, not tag or time\.

.. _function-daml-finance-lifecycle-rule-util-splitpending-19834:

`splitPending <function-daml-finance-lifecycle-rule-util-splitpending-19834_>`_
  \: \[`Pending <type-daml-finance-lifecycle-rule-util-pending-87645_>`_\] \-\> (\[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\], \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\])

  Map pending settlements into corresponding instrument quantities and split them into consumed
  and produced\. Pending items with an amount of ``0.0`` are discarded\.

.. _function-daml-finance-lifecycle-rule-util-net-8465:

`net <function-daml-finance-lifecycle-rule-util-net-8465_>`_
  \: \[`Pending <type-daml-finance-lifecycle-rule-util-pending-87645_>`_\] \-\> \[`Pending <type-daml-finance-lifecycle-rule-util-pending-87645_>`_\]

  Net pending payments on the same instrument (regardless of tags)\.
