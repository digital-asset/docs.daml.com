.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Holding
####################

This package contains the *implementation* of holdings, including utility functions. It has the
following modules:

- :ref:`Fungible <module-daml-finance-holding-fungible-7201>`: Implementation of a holding which is
  fungible only, i.e., include split and merge functionality
- :ref:`Transferable <module-daml-finance-holding-transferable-43388>`: Implementation of a holding
  which is transferable only
- :ref:`TransferableFungible <module-daml-finance-holding-transferablefungible-77726>`:
  Implementation of a holding which is both transferable and fungible
- :ref:`BaseHolding <module-daml-finance-holding-baseholding-57062>`: Implementation of
  a holding which is neither transferable nor fungible
- :ref:`Util <module-daml-finance-holding-util-87323>`: Utility functions related to holdings, e.g.,
  to transfer or split/merge a holding

The :doc:`Asset Model <../../concepts/asset-model>` page explains the relationship between
instruments, holdings, and accounts. Also, check out the
:doc:`Transfer tutorial <../../tutorials/getting-started/transfer>` for a description of how to
create a holding on an instrument and transfer it between accounts.

Changelog
*********
