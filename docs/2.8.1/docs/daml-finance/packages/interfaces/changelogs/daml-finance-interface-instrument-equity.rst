.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Instrument.Equity - Changelog
####################################################

Version 0.4.0
*************

- Update of SDK version and dependencies.

- The `InstrumentKey` is extended by the `HoldingStandard` field.

- The `Remove` choice was removed from the `Factory` (it is newly part of the `Base` instrument
  interface).

- Renamed the `F` type synonym to `I`.

Version 0.3.0
*************

- Update of SDK version and dependencies.

- The `Create` choice on the instrument factory returns the corresponding interface (rather than the
  base instrument interface).

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the
  `asDisclosure` and `asBaseInstrument` methods were removed).

- Rename `DeclareDividend` to `DeclareDistribution`.
