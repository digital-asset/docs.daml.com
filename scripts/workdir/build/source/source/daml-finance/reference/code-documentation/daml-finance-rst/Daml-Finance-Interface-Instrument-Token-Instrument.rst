.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-token-instrument-24425:

Module Daml.Finance.Interface.Instrument.Token.Instrument
=========================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-token-instrument-instrument-4350:

**interface** `Instrument <type-daml-finance-interface-instrument-token-instrument-instrument-4350_>`_

  Interface for simple token instruments which do not define any lifecycling logic\.

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

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-token-instrument-hasimplementation-31027:

**class** `Implementation <type-daml-finance-interface-instrument-token-instrument-implementation-32731_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-token-instrument-hasimplementation-31027_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-token-instrument-i-72687:

**type** `I <type-daml-finance-interface-instrument-token-instrument-i-72687_>`_
  \= `Instrument <type-daml-finance-interface-instrument-token-instrument-instrument-4350_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-token-instrument-implementation-32731:

**type** `Implementation <type-daml-finance-interface-instrument-token-instrument-implementation-32731_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-instrument-token-instrument-i-72687_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t)

  Type constraint requiring templates to implement ``Instrument`` along with ``BaseInstrument`` and
  ``Disclosure``\.

.. _type-daml-finance-interface-instrument-token-instrument-v-57640:

**type** `V <type-daml-finance-interface-instrument-token-instrument-v-57640_>`_
  \= `View <type-daml-finance-interface-instrument-token-instrument-view-23204_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-token-instrument-instrument-4350_>`_ `V <type-daml-finance-interface-instrument-token-instrument-v-57640_>`_

.. _type-daml-finance-interface-instrument-token-instrument-view-23204:

**data** `View <type-daml-finance-interface-instrument-token-instrument-view-23204_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-token-instrument-view-32199:

  `View <constr-daml-finance-interface-instrument-token-instrument-view-32199_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - token
         - :ref:`Token <type-daml-finance-interface-instrument-token-types-token-10344>`
         - Attributes of a token\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-token-instrument-view-23204_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-token-instrument-view-23204_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-token-instrument-asbaseinstrument-89863:

`asBaseInstrument <function-daml-finance-interface-instrument-token-instrument-asbaseinstrument-89863_>`_
  \: `Instrument <type-daml-finance-interface-instrument-token-instrument-instrument-4350_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
