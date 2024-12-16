.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Util.V3 - Changelog
##########################################

Version 2.1.0
*************

- Update of SDK version and dependencies.

- Added a `Lockable` module containing the interface for locking (the `Acquire` and `Release`
  choices used to be part of the base `Holding` interface).

- Created a module `InterfaceKey` with utility functions for keyed interfaces.

Version 2.0.0
*************

- Update of SDK version and dependencies.

- Remove `mapWithIndex` utility function.

- Remove the `HasImplementation` type class definition.
