.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Lifecycle - Changelog
##################################

Version 2.0.0
*************

- Update of SDK version and dependencies

- Remove implementation of `Remove` choice from factory templates

- Move the `Election` module from the `Generic` to the `Lifecycle` package

- `Election` and `ElectionEffect` implement the `Disclosure` interface

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the
  `asDisclosure` and `asEvent` implementations were removed)

- The `Distribution` and `Replacement` lifecycle rules check that the target and procued instruments
  are active

Version 1.0.1
*************

- Dependencies update
