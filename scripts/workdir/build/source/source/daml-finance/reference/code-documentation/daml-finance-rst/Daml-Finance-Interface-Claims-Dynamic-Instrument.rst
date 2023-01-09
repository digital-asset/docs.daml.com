.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-claims-dynamic-instrument-83951:

Module Daml.Finance.Interface.Claims.Dynamic.Instrument
=======================================================

Interfaces
----------

.. _type-daml-finance-interface-claims-dynamic-instrument-instrument-14064:

**interface** `Instrument <type-daml-finance-interface-claims-dynamic-instrument-instrument-14064_>`_

  Interface implemented by instruments that create Contingent Claims trees on\-the\-fly
  (ie\., the tree is not stored on disk as part of a contract, but created and processed in\-memory)\.

  + **Choice Archive**

    (no fields)

  + **Choice CreateNewVersion**

    Create a new version of an instrument, using a new lastEventTimestamp\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - version
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         - The new version of the instrument\.
       * - lastEventTimestamp
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - The new lastEventTimestamp of the instrument\.

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

  + **Method createNewVersion \:** CreateNewVersion \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Instrument <type-daml-finance-interface-claims-dynamic-instrument-instrument-14064_>`_)

Typeclasses
-----------

.. _class-daml-finance-interface-claims-dynamic-instrument-hasimplementation-12325:

**class** `Implementation <type-daml-finance-interface-claims-dynamic-instrument-implementation-46465_>`_ t \=\> `HasImplementation <class-daml-finance-interface-claims-dynamic-instrument-hasimplementation-12325_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-claims-dynamic-instrument-i-39105:

**type** `I <type-daml-finance-interface-claims-dynamic-instrument-i-39105_>`_
  \= `Instrument <type-daml-finance-interface-claims-dynamic-instrument-instrument-14064_>`_

  Type synonym for ``Instrument``\.

.. _type-daml-finance-interface-claims-dynamic-instrument-implementation-46465:

**type** `Implementation <type-daml-finance-interface-claims-dynamic-instrument-implementation-46465_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-claims-dynamic-instrument-i-39105_>`_

  Type constraint for requiring templates to implement ``Instrument``\.

.. _type-daml-finance-interface-claims-dynamic-instrument-v-6678:

**type** `V <type-daml-finance-interface-claims-dynamic-instrument-v-6678_>`_
  \= `View <type-daml-finance-interface-claims-dynamic-instrument-view-84322_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Instrument <type-daml-finance-interface-claims-dynamic-instrument-instrument-14064_>`_ `V <type-daml-finance-interface-claims-dynamic-instrument-v-6678_>`_

.. _type-daml-finance-interface-claims-dynamic-instrument-view-84322:

**data** `View <type-daml-finance-interface-claims-dynamic-instrument-view-84322_>`_

  View for ``Instrument``\.

  .. _constr-daml-finance-interface-claims-dynamic-instrument-view-66709:

  `View <constr-daml-finance-interface-claims-dynamic-instrument-view-66709_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lifecycler
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party performing the lifecycling\.
       * - lastEventTimestamp
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - (Market) time of the last recorded lifecycle event\. If no event has occurred yet, the time of creation should be used\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-claims-dynamic-instrument-view-84322_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-claims-dynamic-instrument-view-84322_>`_

Functions
---------

.. _function-daml-finance-interface-claims-dynamic-instrument-createnewversion-35255:

`createNewVersion <function-daml-finance-interface-claims-dynamic-instrument-createnewversion-35255_>`_
  \: `Instrument <type-daml-finance-interface-claims-dynamic-instrument-instrument-14064_>`_ \-\> CreateNewVersion \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Instrument <type-daml-finance-interface-claims-dynamic-instrument-instrument-14064_>`_)
