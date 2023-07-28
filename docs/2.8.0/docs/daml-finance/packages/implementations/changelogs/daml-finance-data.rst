.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Data - Changelog
#############################

Version 2.0.0
*************

- Update of SDK version and dependencies

- Remove implementation of `Remove` choice from factory templates

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the `asDisclosure`,
  `asNumericObservable`, `asTimeObservable`, and `asEvent` implementations were removed)

- Removed `key` from `DateClock`.

Version 1.0.1
*************

- Fixed a bug in the `DateClock` implementation to avoid key violations

- Dependencies update
