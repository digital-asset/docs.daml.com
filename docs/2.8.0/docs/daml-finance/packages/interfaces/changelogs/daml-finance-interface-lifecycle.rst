.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Lifecycle - Changelog
############################################

Version 3.0.0
*************

- Update of SDK version and dependencies.

- Renamed the `F` type synonym to `I`.

- Changed the `Calculate` choice of the `Effect.I` to take a quantity as argument instead of a
  `ContractId Holding` (in order to not leak information about the holding to the effect provider).

Version 2.0.0
*************

- Update of SDK version and dependencies.

- Remove implementation of `Remove` choice from factory interfaces.

- Move the `Election` module from the `Generic` to the `Lifecycle` package.

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the
  `asDisclosure` and `asEvent` methods were removed).
