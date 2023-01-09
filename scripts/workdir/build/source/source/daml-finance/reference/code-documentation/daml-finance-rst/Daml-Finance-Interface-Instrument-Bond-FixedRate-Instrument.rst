.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-instrument-bond-fixedrate-instrument-43896:

Module Daml.Finance.Interface.Instrument.Bond.FixedRate.Instrument
==================================================================

Interfaces
----------

.. _type-daml-finance-interface-instrument-bond-fixedrate-instrument-instrument-55963:

**interface** `Instrument <type-daml-finance-interface-instrument-bond-fixedrate-instrument-instrument-55963_>`_

  Instrument interface representing a fixed rate bond\.

  + **Choice Archive**

    (no fields)

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to ``Base Instrument`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-instrument-bond-fixedrate-instrument-hasimplementation-54686:

**class** `Implementation <type-daml-finance-interface-instrument-bond-fixedrate-instrument-implementation-2506_>`_ t \=\> `HasImplementation <class-daml-finance-interface-instrument-bond-fixedrate-instrument-hasimplementation-54686_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-instrument-bond-fixedrate-instrument-i-93672:

**type** `I <type-daml-finance-interface-instrument-bond-fixedrate-instrument-i-93672_>`_
  \= `Instrument <type-daml-finance-interface-instrument-bond-fixedrate-instrument-instrument-55963_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-instrument-bond-fixedrate-instrument-implementation-2506:

**type** `Implementation <type-daml-finance-interface-instrument-bond-fixedrate-instrument-implementation-2506_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Instrument <type-daml-finance-interface-instrument-bond-fixedrate-instrument-instrument-55963_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t, :ref:`Implementation <type-daml-finance-interface-util-disclosure-implementation-41553>` t)

  Type constraint requiring templates to implement ``Instrument`` along with the ``BaseInstrument``
  and ``Disclosure`` interfaces\.

.. _type-daml-finance-interface-instrument-bond-fixedrate-instrument-v-8719:

**type** `V <type-daml-finance-interface-instrument-bond-fixedrate-instrument-v-8719_>`_
  \= `View <type-daml-finance-interface-instrument-bond-fixedrate-instrument-view-66597_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-instrument-bond-fixedrate-instrument-instrument-55963_>`_ `V <type-daml-finance-interface-instrument-bond-fixedrate-instrument-v-8719_>`_

.. _type-daml-finance-interface-instrument-bond-fixedrate-instrument-view-66597:

**data** `View <type-daml-finance-interface-instrument-bond-fixedrate-instrument-view-66597_>`_

  View of ``Instrument``\.

  .. _constr-daml-finance-interface-instrument-bond-fixedrate-instrument-view-38280:

  `View <constr-daml-finance-interface-instrument-bond-fixedrate-instrument-view-38280_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - fixedRate
         - :ref:`FixedRate <type-daml-finance-interface-instrument-bond-fixedrate-types-fixedrate-80866>`
         - Attributes of a fixed rate bond\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-instrument-bond-fixedrate-instrument-view-66597_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-instrument-bond-fixedrate-instrument-view-66597_>`_

Functions
---------

.. _function-daml-finance-interface-instrument-bond-fixedrate-instrument-asbaseinstrument-75558:

`asBaseInstrument <function-daml-finance-interface-instrument-bond-fixedrate-instrument-asbaseinstrument-75558_>`_
  \: `Instrument <type-daml-finance-interface-instrument-bond-fixedrate-instrument-instrument-55963_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`
