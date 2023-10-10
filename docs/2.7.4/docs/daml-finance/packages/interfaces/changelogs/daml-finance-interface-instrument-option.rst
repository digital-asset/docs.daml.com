.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Instrument.Option - Changelog
####################################################

Version 0.2.0
*************

- Update of SDK version and dependencies

- The `Create` choice on the instrument factories returns the corresponding interface (rather than the base instrument interface)

- Add instruments physically-settled European options, dividend options, barrier options

- Renamed cash-settled European options to `EuropeanCash`

- Added `GetView` choice to all instrument interfaces

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the `asDisclosure`,
  `asBaseInstrument`, and `asEvent` methods were removed)
