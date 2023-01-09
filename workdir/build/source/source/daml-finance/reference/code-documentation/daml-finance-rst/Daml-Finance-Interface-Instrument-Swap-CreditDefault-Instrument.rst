.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-swap-creditdefault-instrument-27480:

Module Daml.Finance.Interface.Instrument.Swap.CreditDefault.Instrument
======================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-swap-creditdefault-instrument-instrument-24051:

**interface** `Instrument <type-daml-finance-interface-instrument-swap-creditdefault-instrument-instrument-24051_>`_

  Instrument interface representing a credit default swap\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-swap-creditdefault-instrument-hasimplementation-54274:

**class** `Implementation <type-daml-finance-interface-instrument-swap-creditdefault-instrument-implementation-8482_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-swap-creditdefault-instrument-hasimplementation-54274_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-swap-creditdefault-instrument-i-36944:

**type** `I <type-daml-finance-interface-instrument-swap-creditdefault-instrument-i-36944_>`_
  \= `Instrument <type-daml-finance-interface-instrument-swap-creditdefault-instrument-instrument-24051_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-swap-creditdefault-instrument-implementation-8482:

**type** `Implementation <type-daml-finance-interface-instrument-swap-creditdefault-instrument-implementation-8482_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-swap-creditdefault-instrument-instrument-24051_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-swap-creditdefault-instrument-v-30855:

**type** `V <type-daml-finance-interface-instrument-swap-creditdefault-instrument-v-30855_>`_
  \= `View <type-daml-finance-interface-instrument-swap-creditdefault-instrument-view-10941_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-swap-creditdefault-instrument-instrument-24051_>`_ `V <type-daml-finance-interface-instrument-swap-creditdefault-instrument-v-30855_>`_

.. _type-daml-finance-interface-instrument-swap-creditdefault-instrument-view-10941:

**data** `View <type-daml-finance-interface-instrument-swap-creditdefault-instrument-view-10941_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-swap-creditdefault-instrument-view-71316:

  `View <constr-daml-finance-interface-instrument-swap-creditdefault-instrument-view-71316_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - creditDefault
         - :ref:`CreditDefault <type-daml-finance-interface-instrument-swap-creditdefault-types-creditdefault-84256>`
         - Attributes of a credit default swap\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-swap-creditdefault-instrument-view-10941_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-swap-creditdefault-instrument-view-10941_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-swap-creditdefault-instrument-asbaseinstrument-28934:

`asBaseInstrument <function-daml-finance-interface-instrument-swap-creditdefault-instrument-asbaseinstrument-28934_>`_
  \: `Instrument <type-daml-finance-interface-instrument-swap-creditdefault-instrument-instrument-24051_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
