.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Instrument.Generic - Changelog
#####################################################

Version 2.0.0
*************

- Update of SDK version and dependencies

- The `Create` choice on the instrument factory returns the corresponding interface (rather than the base instrument interface)

- Move the `Election` module to the `Lifecycle` package. Also, refactor the `Election` to identify the elected sub-tree by a textual tag rather than the actual sub-tree

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the `asDisclosure`,
  `asBaseInstrument`, and `asClaim` methods were removed)