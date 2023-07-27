.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Instrument.Swap - Changelog
##################################################

Version 0.3.0
*************

- Update of SDK version and dependencies

- The `Create` choice on the instrument factories returns the corresponding interface (rather than the base instrument interface)

- Added `GetView` choice to all instrument interfaces

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the `asDisclosure` and
  `asBaseInstrument` methods were removed)

Version 0.2.1
*************

- Updates to data types related to interest rate compounding and payment lag

- Updates to data types related to Term period
