.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml Finance Documentation
##########################

Welcome to the Daml Finance documentation. This page provides an overview of the documentation
content as well as suggested starting points. Use the left-hand menu to explore the various
sections, or the search bar above for quick navigation. If you are missing content from the
documentation, have feedback on the library, or need any help using it, do not hesitate to
`open an issue <https://github.com/digital-asset/daml-finance/issues>`_ on the repository.

Content
*******

* :doc:`Overview <overview/intro>`: description of the purpose of the library, its high-level
  architecture, as well as targeted use cases
* :doc:`Concepts <concepts/index>`: explanation of the main concepts used throughout the library,
  and how they fit together
* :doc:`Instruments <instruments/intro>`: description of the instruments that are
  included in Daml Finance and can be used out of the box
* :doc:`Packages <packages/index>`: documentation for each individual package and its contained
  modules
* :doc:`Tutorials <tutorials/getting-started/intro>`: step-by-step implementation guides across
  different use cases
* :doc:`Reference <reference/glossary>`: glossary as well as code-level documentation for each
  package

Starting Points
***************

The following is a suggested learning path to get productive quickly:

#. :doc:`Get started <tutorials/getting-started/intro>` quickly
#. Read up on the :doc:`background, purpose, and intended usage <overview/intro>` of the library
#. Understand the :doc:`fundamental concepts <concepts/index>` in depth
#. Learn how to
   :doc:`use the instrument packages to model different financial instruments <instruments/intro>`
#. Explore the :ref:`Daml Finance Demo Application <daml-finance-demo-app>`
#. Ask questions in the `Forum <https://discuss.daml.com/tag/daml-finance>`_ or read existing
   discussions

.. _releases:

Packages
********

How to Download
===============

Daml Finance is distributed as a set of packages. There are two main ways how to download Daml
Finance:

- New users are recommended to follow the
  :doc:`Getting started <tutorials/getting-started/intro>` tutorial, which also contains a
  ``get-dependencies`` script that downloads the Daml Finance packages. This allows you to learn
  Daml Finance at the same time.
- Advanced users can download Daml Finance directly from the
  `Releases section of the repo <https://github.com/digital-asset/daml-finance/releases>`_, either
  the individual packages that your application needs or a bundle containing all packages.

Current Release
===============

.. Add the next version of the SDK here (by uncommenting the next line):
.. Daml SDK 2.9.0

This section details the list of released and deprecated packages. For each package, we provide
status information according to the
`Daml Ecosystem convention <https://docs.daml.com/support/status-definitions.html>`_. In addition,
we have a section to highlight and explain the major updates and enhancements introduced since our
last release.

**Important Note**: The current Daml Finance release requires the use of Daml SDK v2.5 or later.

Major Updates
-------------

.. Add rationale and motivation for breaking changes here.

Stable Packages
---------------

+-------------------------------------------+---------+--------+
| Package                                   | Version | Status |
+===========================================+=========+========+
| ContingentClaims.Core                     | 2.0.1   | Stable |
+-------------------------------------------+---------+--------+
| ContingentClaims.Lifecycle                | 2.0.1   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Account                      | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Claims                       | 2.1.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Data                         | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Holding                      | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Bond              | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Generic           | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Token             | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Account            | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Claims             | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Data               | 3.1.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Holding            | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Base    | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Bond    | 2.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Generic | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Token   | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Types   | 1.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Lifecycle          | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Settlement         | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Types.Common       | 2.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Types.Date         | 2.1.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Interface.Util               | 2.1.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Lifecycle                    | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Settlement                   | 3.0.0   | Stable |
+-------------------------------------------+---------+--------+
| Daml.Finance.Util                         | 3.1.0   | Stable |
+-------------------------------------------+---------+--------+

Early Access Packages
---------------------

+-----------------------------------------------------+---------+--------+
| Package                                             | Version | Status |
+=====================================================+=========+========+
| ContingentClaims.Valuation                          | 0.2.2   | Labs   |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Equity                      | 0.4.0   | Alpha  |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Option                      | 0.3.0   | Alpha  |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.StructuredProduct           | 0.1.0   | Alpha  |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Swap                        | 0.4.0   | Alpha  |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Equity            | 0.4.0   | Alpha  |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Option            | 0.3.0   | Alpha  |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.StructuredProduct | 0.1.0   | Alpha  |
+-----------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Swap              | 0.4.0   | Alpha  |
+-----------------------------------------------------+---------+--------+

Deprecated Packages
-------------------

+--------------------------------------------+--------------------+--------+
| Package                                    | Version            | Status |
+============================================+====================+========+
| ContingentClaims.Core                      | 1.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| ContingentClaims.Lifecycle                 | 1.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Account                       | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Claims                        | 1.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Data                          | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Holding                       | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Instrument.Generic            | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Instrument.Token              | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Account             | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Claims              | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Data                | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Holding             | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Instrument.Base     | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Instrument.Generic  | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Instrument.Token    | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Lifecycle           | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Settlement          | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Util                | 1.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Lifecycle                     | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Settlement                    | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
| Daml.Finance.Util                          | 2.*                | Depr.  |
+--------------------------------------------+--------------------+--------+
