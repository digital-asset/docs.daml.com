.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Claims
###################

This package contains utility functions that facilitate building and working with
:doc:`Contingent Claims <../../concepts/contingent-claims>` based instruments. It includes the
following modules:

- :ref:`Lifecycle.Rule <module-daml-finance-claims-lifecycle-rule-53980>`:
  Rule to process a lifecycle event for instruments that are modelled using
  :doc:`On-the-Fly claims <../../tutorials/advanced-topics/instrument-modeling/contingent-claims-on-ledger-vs-on-the-fly>`
- :ref:`Util <module-daml-finance-claims-util-5254>`:
  Contains utility functions for claims, e.g., checking the content of a claim and converting the
  claim time
- :ref:`Util.Lifecycle <module-daml-finance-claims-util-lifecycle-9534>`:
  Defines different types of events and how to lifecycle them
- :ref:`Util.Builders <module-daml-finance-claims-util-builders-48637>`:
  Utility functions related to creating :doc:`Contingent Claims <../../concepts/contingent-claims>`,
  e.g. for bonds/swaps
- :ref:`Util.Date <module-daml-finance-claims-util-date-40505>`:
  Utility functions related to dates and schedule periods, which are used to define claims.

Changelog
*********
