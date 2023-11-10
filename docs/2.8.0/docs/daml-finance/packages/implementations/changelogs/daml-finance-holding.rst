.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Holding - Changelog
################################

Version 2.0.0
*************

- Update of SDK version and dependencies

- Remove implementation of `Remove` choice from factory templates

- Added default `splitImpl` and `mergeImpl` for `Fungible` to `Util.daml`

- Generalized the `acquireImpl` and `releaseImpl` to not rely on an attribute called "lock"

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the
  `asDisclosure`, `asBase`, and `asTransferable` implementations were removed)

- The `Transfer` choice of the `Transferable` interface now includes the new owner as a choice
  observer

- Implementation of `Lockable` does not allow an empty `lockers` set

Version 1.0.2
*************

- Dependencies update

Version 1.0.1
*************

- Fix bug in the implementation of `Fungible.Merge`

- Improve error message when acquiring a lock
