.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-observable-numericobservable-67288:

Module Daml.Finance.Interface.Lifecycle.Observable.NumericObservable
====================================================================

This module defines an interface for a ``NumericObservable``, which is used to inspect
time\-dependent numerical values\.

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-observable-numericobservable-numericobservable-88407:

**interface** `NumericObservable <type-daml-finance-interface-lifecycle-observable-numericobservable-numericobservable-88407_>`_

  An interface to inspect some (time\-dependent) numerical values (e\.g\. a stock price or an
  interest rate fixing) required when processing a lifecycle rule\.

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

  + **Choice Observe**

    Observe the ``Observable``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actors
         - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
         - Parties calling this 'Observe' choice\.
       * - t
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - Time at which the value is observed\.

  + **Method observe \:** `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

    Implementation of the ``Observe`` choice\.

Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-observable-numericobservable-hasimplementation-21654:

**class** `Implementation <type-daml-finance-interface-lifecycle-observable-numericobservable-implementation-26558_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-observable-numericobservable-hasimplementation-21654_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092:

**type** `I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092_>`_
  \= `NumericObservable <type-daml-finance-interface-lifecycle-observable-numericobservable-numericobservable-88407_>`_

  Type synonym for ``Observable``\.

  **instance** HasMethod :ref:`Observation <type-daml-finance-interface-data-numeric-observation-observation-2365>` \"asNumericObservable\" `I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092_>`_

.. _type-daml-finance-interface-lifecycle-observable-numericobservable-implementation-26558:

**type** `Implementation <type-daml-finance-interface-lifecycle-observable-numericobservable-implementation-26558_>`_ t
  \= `HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-lifecycle-observable-numericobservable-i-22092_>`_

  Type constraint for requiring templates to implement ``NumericObservable``\.

.. _type-daml-finance-interface-lifecycle-observable-numericobservable-v-2379:

**type** `V <type-daml-finance-interface-lifecycle-observable-numericobservable-v-2379_>`_
  \= `View <type-daml-finance-interface-lifecycle-observable-numericobservable-view-1969_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `NumericObservable <type-daml-finance-interface-lifecycle-observable-numericobservable-numericobservable-88407_>`_ `V <type-daml-finance-interface-lifecycle-observable-numericobservable-v-2379_>`_

.. _type-daml-finance-interface-lifecycle-observable-numericobservable-view-1969:

**data** `View <type-daml-finance-interface-lifecycle-observable-numericobservable-view-1969_>`_

  View for ``Observable``\.

  .. _constr-daml-finance-interface-lifecycle-observable-numericobservable-view-68636:

  `View <constr-daml-finance-interface-lifecycle-observable-numericobservable-view-68636_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - provider
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - Party providing the observations\.
       * - id
         - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
         - Textual reference to the observable\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-observable-numericobservable-view-1969_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-observable-numericobservable-view-1969_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-observable-numericobservable-observe-12235:

`observe <function-daml-finance-interface-lifecycle-observable-numericobservable-observe-12235_>`_
  \: `NumericObservable <type-daml-finance-interface-lifecycle-observable-numericobservable-numericobservable-88407_>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_
