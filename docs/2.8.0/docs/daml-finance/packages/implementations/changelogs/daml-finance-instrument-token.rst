.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Instrument.Token - Changelog
#########################################

Version 3.0.0
*************

- Update of SDK version and dependencies.

- Added a `HoldingStandard` field to the implementation.

- The `Remove` implementation was removed from the `Factory` (it is newly part of the `Base`
  instrument interface).

- Renamed the `F` type synonym to `T`.

Version 2.0.0
*************

- Update of SDK version and dependencies.

- The `Create` choice on the instrument factory returns the corresponding interface (rather than the
  base instrument interface).

- Make use of the `requires` keyword to enforce the interface hierarchy (in the particular
  `asDisclosure` and `asBaseInstrument` implementations were removed).

Version 1.0.1
*************

- Dependencies update.
