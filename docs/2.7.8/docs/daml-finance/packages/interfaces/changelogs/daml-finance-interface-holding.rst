.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Interface.Holding - Changelog
##########################################

Version 2.0.0
*************

- Update of SDK version and dependencies

- Remove implementation of `Remove` choice from factory templates

- Removed unnecessary `ArchiveFungible` choice

- Make use of the `requires` keyword to enforce the interface hierarchy (in particular the `asDisclosure`,
  `asBase`, and `asTransferable` methods were removed)

- Fix to signature of `disclose` (removed the `actor` argument)