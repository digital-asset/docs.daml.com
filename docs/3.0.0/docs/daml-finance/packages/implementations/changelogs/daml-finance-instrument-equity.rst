.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Instrument.Equity - Changelog
##########################################

Version 0.3.0
*************

- Update of SDK version and dependencies

- The `Create` choice on the instrument factory returns the corresponding interface (rather than the
  base instrument interface)

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the
  `asDisclosure` and `asBaseInstrument` implementations were removed)

- Rename `DeclareDividend` to `DeclareDistribution`

Version 0.2.1
*************

- Dependencies update
