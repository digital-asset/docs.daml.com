.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-util-common-41560:

Module Daml.Finance.Util.Common
===============================

Functions
---------

.. _function-daml-finance-util-common-groupby-55701:

`groupBy <function-daml-finance-util-common-groupby-55701_>`_
  \: `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ k \=\> (a \-\> k) \-\> \[a\] \-\> `Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ k \[a\]

  Like ``List.groupOn``, but returns the output in a ``Map``\.

.. _function-daml-finance-util-common-mapwithindex-16736:

`mapWithIndex <function-daml-finance-util-common-mapwithindex-16736_>`_
  \: (a \-\> `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_ \-\> b) \-\> \[a\] \-\> \[b\]

  Like ``map``, but the mapping function includes the zero\-based index of the item\.

.. _function-daml-finance-util-common-notnull-49691:

`notNull <function-daml-finance-util-common-notnull-49691_>`_
  \: \[a\] \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_

  Checks if the input list is not empty\.

.. _function-daml-finance-util-common-sortandgroupon-1467:

`sortAndGroupOn <function-daml-finance-util-common-sortandgroupon-1467_>`_
  \: `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ k \=\> (a \-\> k) \-\> \[a\] \-\> \[\[a\]\]

  Like ``List.groupOn``, but sorts the list first\.
