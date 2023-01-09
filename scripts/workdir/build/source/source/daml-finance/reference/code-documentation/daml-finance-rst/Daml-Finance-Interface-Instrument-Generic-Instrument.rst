.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-generic-instrument-53275:

Module Daml.Finance.Interface.Instrument.Generic.Instrument
===========================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-generic-instrument-instrument-11652:

**interface** `Instrument <type-daml-finance-interface-instrument-generic-instrument-instrument-11652_>`_

  Interface for generic instruments utilizing Contingent Claims\.

  + **Choice Archive**

    (no fields)

  + **Choice GetView**

    Retrieves the interface view\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party retrieving the view\.

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to base ``Instrument`` interface\.

  + **Method asClaim \:** :ref:`I <type-daml-finance-interface-claims-claim-i-15462>`

    Conversion to claim interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-generic-instrument-hasimplementation-62633:

**class** `Implementation <type-daml-finance-interface-instrument-generic-instrument-implementation-39381_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-generic-instrument-hasimplementation-62633_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-generic-instrument-i-26565:

**type** `I <type-daml-finance-interface-instrument-generic-instrument-i-26565_>`_
  \= `Instrument <type-daml-finance-interface-instrument-generic-instrument-instrument-11652_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-generic-instrument-implementation-39381:

**type** `Implementation <type-daml-finance-interface-instrument-generic-instrument-implementation-39381_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-instrument-generic-instrument-i-26565_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-claims-claim-implementation-40844>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-generic-instrument-v-37458:

**type** `V <type-daml-finance-interface-instrument-generic-instrument-v-37458_>`_
  \= `View <type-daml-finance-interface-instrument-generic-instrument-view-27278_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-generic-instrument-instrument-11652_>`_ `V <type-daml-finance-interface-instrument-generic-instrument-v-37458_>`_

.. _type-daml-finance-interface-instrument-generic-instrument-view-27278:

**data** `View <type-daml-finance-interface-instrument-generic-instrument-view-27278_>`_

  .. _constr-daml-finance-interface-instrument-generic-instrument-view-99577:

  `View <constr-daml-finance-interface-instrument-generic-instrument-view-99577_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - instrument
         - :ref:`InstrumentKey <type-daml-finance-interface-types-common-types-instrumentkey-12301>`
         - The instrument's key\.
       * - claims
         - :ref:`C <type-daml-finance-interface-claims-types-c-53263>`
         - The claim tree\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-generic-instrument-view-27278_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-generic-instrument-view-27278_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-generic-instrument-asbaseinstrument-71285:

`asBaseInstrument <function-daml-finance-interface-instrument-generic-instrument-asbaseinstrument-71285_>`_
  \: `Instrument <type-daml-finance-interface-instrument-generic-instrument-instrument-11652_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

.. _function-daml-finance-interface-instrument-generic-instrument-asclaim-51398:

`asClaim <function-daml-finance-interface-instrument-generic-instrument-asclaim-51398_>`_
  \: `Instrument <type-daml-finance-interface-instrument-generic-instrument-instrument-11652_>`_ \-\> :ref:`I <type-daml-finance-interface-claims-claim-i-15462>`
