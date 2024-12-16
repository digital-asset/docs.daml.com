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

Daml SDK 2.9.4

This section details the list of released and deprecated packages, with status information provided
for each package according to the
`Daml Ecosystem convention <https://docs.daml.com/support/status-definitions.html>`_. Additionally,
a section is included to highlight and explain the major updates and enhancements introduced since
the last release.

**Important Note**: The current Daml Finance release requires the use of Daml SDK v2.5 or later.

Major Updates
-------------

The main driver for this release has been to optimize the library for useability, maintainability,
and upgradability. Along with code changes, new documentation and tutorials have been added to
streamline the learning process for new users.

This section outlines the major changes and reasons behind them. The technical changelog for each
package can be found as a sub-page under :doc:`Packages <packages/index>`.

Enhanced Upgradeability, Extensibility, and Interoperability
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The core asset model (``Account``, ``Holding``, and ``Instrument`` interfaces) has been enhanced to
streamline upgrade processes, enhance extensibility, and improve interoperability:

#. The ``Account`` now links to its ``Daml.Finance.Interface.Holding.V4.Factory`` by key, a
   ``HoldingFactoryKey``, instead of a ``ContractId``. This facilitates the upgrading of a
   ``HoldingFactory`` without the need to modify existing ``Account`` contract instances. It also
   enables a "lazy" upgrade approach for holdings, as detailed the
   :doc:`Holding Upgrade Tutorial <./tutorials/upgrade/holding>`.

#. In anticipation of the need for standardization when implementing composed workflows across
   applications, the notion of a ``HoldingStandard`` was introduced (as part of the
   ``InstrumenKey``). It categorizes holdings into four distinct classes, each defined by the
   combination of holding interfaces (``Transferable``, ``Fungible``, and ``Holding``) they
   implement. This new standard has guided the renaming and structuring of holding implementations.
   The ``Fungible`` interface no longer requires the ``Transferable`` interface. However, both
   ``Transferable`` and ``Fungible`` continue to require the implementation of the ``Holding``
   interface (renamed from ``Base`` following customer feedback). Moreover, the settlement process
   has been refined to require only a matching ``HoldingStandard``, allowing for implementation
   variations.

#. A unified ``HoldingFactory`` capable of creating holdings for any specified ``HoldingStandard``
   has been adopted. In particular, this enables multiple holdings (of various ``HoldingStandards``)
   to be credited to the same account.

Foreseeing future integration with Daml 3.0 and the Canton Network
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to ease future transitions to Daml 3.0 and the Canton Network, there is a shift to
single-maintainer contract keys:

#. The `issuer : Party` of the ``InstrumentKey`` is now the single maintainer for the ``Instrument``
   key.

#. For ``Batch`` and ``Instruction``, the `requestors : Parties` field has been divided into a
   single-maintainer `instructor : Party` for the ``Instruction`` key, alongside additional
   signatories `consenters : Parties`. Corresponding changes have been made to the ``Batch`` and
   ``Instruction`` views. In the ``Daml.Finance.Lifecycle.V4.Rule.Claim`` implementation,
   `providers : Parties` has been replaced with a single `provider : Party` (to facilitate assigning
   the `provider` as a settlement `instructor : Party`).

#. The LedgerTime key has been completely removed, as it was redundant.

Streamlining Interface Archival
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Previously, our factory contracts featured a ``Remove`` choice for archiving interface instances.
With Daml now supporting direct archival of interface instances, these choices have been removed. To
facilitate the simultaneous archival of ``Account``, ``Instrument``, and ``HoldingFactory``
interfaces with their related ``Reference`` contract instance, a ``Remove`` choice has been added to
the ``Account``, base ``Instrument``, and ``HoldingFactory`` interfaces.

New Interface Lockable
~~~~~~~~~~~~~~~~~~~~~~

The locking mechanism has been separated from the base ``Holding`` interface into a new ``Lockable``
interface (which the ``Holding`` now requires). That makes ``Lockable`` available for broader use;
while the ``Account`` also implements ``Lockable`` allowing to freeze an account, it’s not required.

Additionally, the implementations of ``Transfer``, ``Split``, ``Merge``, and ``Debit`` have been
adjusted to require unlocking before they can be used when in the locked state.

New Instruments
~~~~~~~~~~~~~~~

The library's functionality has been broadened by introducing new financial instruments,
such as structured products and multi-underlying asset swap instruments (both early access).

Usability Improvements
~~~~~~~~~~~~~~~~~~~~~~

Finally, a large number (around 50 tickets) of smaller improvements addressing customer feedback
were made. These improvements range from the consistency of naming conventions (for example, the type
synonym ``F`` for factories has been renamed to ``T`` for factory templates and ``I`` for factory
interfaces) in the library to didactical improvements in our docs and tutorials.

Additional Changes
~~~~~~~~~~~~~~~~~~

The ``Calculate`` choice in the ``Effect`` interface now accepts a quantity as an argument instead
of a ``ContractId Holding``. This change enhances privacy by minimizing unnecessary data exposure.


Stable Packages
---------------

+----------------------------------------------+---------+--------+
| Package                                      | Version | Status |
+==============================================+=========+========+
| ContingentClaims.Core.V3                     | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| ContingentClaims.Lifecycle.V3                | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Account.V4                      | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Claims.V3                       | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Data.V4                         | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Holding.V4                      | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Bond.V3              | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Generic.V4           | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Token.V4             | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Account.V4            | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Claims.V4             | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Data.V4               | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Holding.V4            | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Base.V4    | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Bond.V3    | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Generic.V4 | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Token.V4   | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Types.V2   | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Lifecycle.V4          | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Settlement.V4         | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Types.Common.V3       | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Types.Date.V3         | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Interface.Util.V3               | 3.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Lifecycle.V4                    | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Settlement.V4                   | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+
| Daml.Finance.Util.V4                         | 4.0.0   | Stable |
+----------------------------------------------+---------+--------+

Early Access Packages
---------------------

+--------------------------------------------------------+---------+--------+
| Package                                                | Version | Status |
+========================================================+=========+========+
| ContingentClaims.Valuation.V1                          | 1.0.0   | Labs   |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Equity.V1                      | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Option.V1                      | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.StructuredProduct.V1           | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Instrument.Swap.V1                        | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Equity.V1            | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Option.V1            | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.StructuredProduct.V1 | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+
| Daml.Finance.Interface.Instrument.Swap.V1              | 1.0.0   | Alpha  |
+--------------------------------------------------------+---------+--------+

Deprecated Packages
-------------------

+-----------------------------------------------+--------------------+--------+
| Package                                       | Version            | Status |
+===============================================+====================+========+
| ContingentClaims.Core                         | 2.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| ContingentClaims.Lifecycle                    | 2.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Account                          | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Claims                           | 2.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Data                             | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Holding                          | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Instrument.Generic               | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Instrument.Token                 | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Account                | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Claims                 | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Data                   | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Holding                | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Instrument.Base        | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Instrument.Generic     | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Instrument.Token       | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Lifecycle              | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Settlement             | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Interface.Util                   | 2.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Lifecycle                        | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Settlement                       | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+
| Daml.Finance.Util                             | 3.*                | Depr.  |
+-----------------------------------------------+--------------------+--------+

