.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Patterns
########

This page some common patterns used in the Daml Finance library.

.. _getview:

View the data of a contract
---------------------------

There are different ways to access the data of a contract, for example the terms of an instrument:

#. :ref:`fetch <daml-ref-fetch>` the contract using its contract ID. This requires the submitting
   party to be a stakeholder of the contract.
#. ``GetView``: by calling this choice on the interface, for example on a
   :ref:`callable bond <type-daml-finance-interface-instrument-bond-callable-instrument-instrument-70770>`,
   a party can get the view of a contract, without necessarily being a stakeholder of the contract.
   This can be useful in situations where someone needs access to reference data, but should not be
   a stakeholder of the contract. Specifically, if *publicParty* is an observer of an instrumentCid,
   a party would only require readAs rights of *publicParty* in order to exercise ``GetView``. In
   the Daml Finance library, this choice has been implemented not only for instruments but also for
   other types of contracts, e.g.
   :ref:`Holdings <module-daml-finance-interface-holding-fungible-63712>` and lifecycle related
   contracts like
   :ref:`Rule <module-daml-finance-interface-lifecycle-rule-lifecycle-50431>` and
   :ref:`Effect <module-daml-finance-interface-lifecycle-effect-16050>`.
