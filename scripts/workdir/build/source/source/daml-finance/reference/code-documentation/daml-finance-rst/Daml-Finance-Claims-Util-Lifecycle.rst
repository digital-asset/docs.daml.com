.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-claims-util-lifecycle-9534:

Module Daml.Finance.Claims.Util.Lifecycle
=========================================

Functions
---------

.. _function-daml-finance-claims-util-lifecycle-timeevent-31130:

`timeEvent <function-daml-finance-claims-util-lifecycle-timeevent-31130_>`_
  \: `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ \-\> Event

  Constructor for a time event\.

.. _function-daml-finance-claims-util-lifecycle-electionevent-57428:

`electionEvent <function-daml-finance-claims-util-lifecycle-electionevent-57428_>`_
  \: `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ \-\> `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_ \-\> :ref:`C <type-daml-finance-interface-claims-types-c-53263>` \-\> Event

  Constructor for an election event\.

.. _function-daml-finance-claims-util-lifecycle-lifecycleclaims-92142:

`lifecycleClaims <function-daml-finance-claims-util-lifecycle-lifecycleclaims-92142_>`_
  \: \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>`\] \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ \-\> \[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\] \-\> \[Event\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (\[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\], \[:ref:`Pending <type-daml-finance-interface-claims-types-pending-95419>`\])

  Lifecycle a set of claims at specified events\.

.. _function-daml-finance-claims-util-lifecycle-netontag-33462:

`netOnTag <function-daml-finance-claims-util-lifecycle-netontag-33462_>`_
  \: \[:ref:`Pending <type-daml-finance-interface-claims-types-pending-95419>`\] \-\> \[:ref:`Pending <type-daml-finance-interface-claims-types-pending-95419>`\]

  Net pending payments on the same instrument, which also have the same tag\.

.. _function-daml-finance-claims-util-lifecycle-lifecycle-85331:

`lifecycle <function-daml-finance-claims-util-lifecycle-lifecycle-85331_>`_
  \: `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092>`\] \-\> :ref:`I <type-daml-finance-interface-claims-claim-i-15462>` \-\> \[Event\] \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (\[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\], \[:ref:`Pending <type-daml-finance-interface-claims-types-pending-95419>`\])

  Lifecycle a claim instrument at specified events\.

.. _function-daml-finance-claims-util-lifecycle-splitpending-12793:

`splitPending <function-daml-finance-claims-util-lifecycle-splitpending-12793_>`_
  \: \[:ref:`Pending <type-daml-finance-interface-claims-types-pending-95419>`\] \-\> (\[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\], \[:ref:`InstrumentQuantity <type-daml-finance-interface-types-common-types-instrumentquantity-3096>`\])

  Map pending settlements into corresponding instrument quantities and split them into consumed
  and produced\. Pending items with an amount of ``0.0`` are discarded\.
