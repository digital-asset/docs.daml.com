.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml.Finance.Instrument.Option
##############################

This package contains the *implementation* of different option types, defined in the
following modules:

- :ref:`Dividend.Instrument <module-daml-finance-instrument-option-dividend-instrument-7333>`:
  Instrument implementation for dividend options
- :ref:`Dividend.Factory <module-daml-finance-instrument-option-dividend-factory-82807>`:
  Factory implementation to instantiate dividend options
- :ref:`Dividend.Election <module-daml-finance-instrument-option-dividend-election-79353>`:
  Factory implementation to create an Election for dividend options
- :ref:`EuropeanCash.Instrument <module-daml-finance-instrument-option-europeancash-instrument-22074>`:
  Instrument implementation for cash-settled European options
- :ref:`EuropeanCash.Factory <module-daml-finance-instrument-option-europeancash-factory-75778>`:
  Factory implementation to instantiate cash-settled European options
- :ref:`EuropeanPhysical.Instrument <module-daml-finance-instrument-option-europeanphysical-instrument-71708>`:
  Instrument implementation for physically settled European options
- :ref:`EuropeanPhysical.Factory <module-daml-finance-instrument-option-europeanphysical-factory-58032>`:
  Factory implementation to instantiate physically settled European options
- :ref:`Util <module-daml-finance-instrument-option-util-7008>`:
  Utility functions for options

Check out the tutorial on
:doc:`How to use the Option extension package <../../tutorials/instrument-extension-packages/option-extension>`
for a description of how to use the option extension in practice.
