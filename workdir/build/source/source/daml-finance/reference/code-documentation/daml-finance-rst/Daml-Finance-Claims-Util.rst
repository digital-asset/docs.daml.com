.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-claims-util-5254:

Module Daml.Finance.Claims.Util
===============================

Functions
---------

.. _function-daml-finance-claims-util-iszero-74676:

`isZero <function-daml-finance-claims-util-iszero-74676_>`_
  \: `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_

  Checks if all input claims are zero\.

.. _function-daml-finance-claims-util-iszerotick-63488:

`isZero' <function-daml-finance-claims-util-iszerotick-63488_>`_
  \: \[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\] \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_

  Checks if all input claims are zero\.

.. _function-daml-finance-claims-util-totime-68962:

`toTime <function-daml-finance-claims-util-totime-68962_>`_
  \: (t \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_) \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ x a o

  Maps the time parameter in a ``Claim`` to ``Time``\. As ``Time`` is generally understood to express
  UTC time, we recommend mapping to UTC time\.
