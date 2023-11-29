.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Lifecycle - Changelog
############################################

Version 2.0.0
*************

- Update of SDK version and dependencies

- Remove implementation of `Remove` choice from factory interfaces

- Move the `Election` module from the `Generic` to the `Lifecycle` package

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the `asDisclosure` and `asEvent` methods were removed)
