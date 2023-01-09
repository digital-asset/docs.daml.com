.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-observable-timeobservable-45971:

Module Daml.Finance.Interface.Lifecycle.Observable.TimeObservable
=================================================================

This module defines an interface for a ``TimeObservable``, which is implemented by templates
exposing time information\.

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-observable-timeobservable-timeobservable-48407:

**interface** `TimeObservable <type-daml-finance-interface-lifecycle-observable-timeobservable-timeobservable-48407_>`_

  An interface to inspect a time value\.

  + **Choice Archive**

    (no fields)

  + **Choice GetTime**

    Retrieves the current time\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - The party retrieving the current time\.

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

  + **Method getTime \:** `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_

    Implementation of the ``GetTime`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-observable-timeobservable-hasimplementation-69873:

**class** `Implementation <type-daml-finance-interface-lifecycle-observable-timeobservable-implementation-4157_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-observable-timeobservable-hasimplementation-69873_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421:

**type** `I <type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421_>`_
  \= `TimeObservable <type-daml-finance-interface-lifecycle-observable-timeobservable-timeobservable-48407_>`_

  Type synonym for ``TimeObservable``\.

  **instance** HasMethod :ref:`Time <type-daml-finance-interface-data-reference-time-time-91391>` \"asTimeObservable\" `I <type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421_>`_

.. _type-daml-finance-interface-lifecycle-observable-timeobservable-implementation-4157:

**type** `Implementation <type-daml-finance-interface-lifecycle-observable-timeobservable-implementation-4157_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421_>`_

  Type constraint for requiring interface implementations for ``TimeObservable``\.

.. _type-daml-finance-interface-lifecycle-observable-timeobservable-v-41754:

**type** `V <type-daml-finance-interface-lifecycle-observable-timeobservable-v-41754_>`_
  \= `View <type-daml-finance-interface-lifecycle-observable-timeobservable-view-64502_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `TimeObservable <type-daml-finance-interface-lifecycle-observable-timeobservable-timeobservable-48407_>`_ `V <type-daml-finance-interface-lifecycle-observable-timeobservable-v-41754_>`_

.. _type-daml-finance-interface-lifecycle-observable-timeobservable-view-64502:

**data** `View <type-daml-finance-interface-lifecycle-observable-timeobservable-view-64502_>`_

  View for ``TimeObservable``\.

  .. _constr-daml-finance-interface-lifecycle-observable-timeobservable-view-38537:

  `View <constr-daml-finance-interface-lifecycle-observable-timeobservable-view-38537_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - providers
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties providing the observation\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Textual reference to the observable\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-observable-timeobservable-view-64502_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-observable-timeobservable-view-64502_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-observable-timeobservable-gettime-97157:

`getTime <function-daml-finance-interface-lifecycle-observable-timeobservable-gettime-97157_>`_
  \: `TimeObservable <type-daml-finance-interface-lifecycle-observable-timeobservable-timeobservable-48407_>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
