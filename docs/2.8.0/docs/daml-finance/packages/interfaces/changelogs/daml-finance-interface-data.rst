.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Data - Changelog
#######################################

- Update of SDK version and dependencies.

- Added new day-count conventions: Act365NL, Basis30365, and Basis30E2360.

Version 3.1.0
*************

- Update of SDK version and dependencies.

- Added `I` as type synonym for each `Factory` in the package (the `F` type synonyms are to be
  deprecated).

Version 3.0.0
*************

- Update of SDK version and dependencies.

- Remove implementation of `Remove` choice from factory templates.

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the
`asDisclosure`, `asNumericObservable`, and `asTimeObservable` methods were removed).

Version 2.0.0
*************

- Changed the signature of `advance` and `rewind` in the `Reference.Time` interface.

- Dependencies update.
