.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-contingentclaims-core-observation-86605:

Module ContingentClaims.Core.Observation
========================================

Data Types
----------

.. _type-contingentclaims-core-observation-observation-91686:

**data** `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o

  Concrete implementation of ``Observable``, which can be serialized\.
  Conceptually it is helpful to think of this as the type ``t -> x``, or ``t -> Update x``\.

  .. _constr-contingentclaims-core-observation-const-78712:

  `Const <constr-contingentclaims-core-observation-const-78712_>`_

    A numerical constant, e\.g\. ``10.0``\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - value
         - x
         -

  .. _constr-contingentclaims-core-observation-observe-30391:

  `Observe <constr-contingentclaims-core-observation-observe-30391_>`_

    A named parameter, e\.g\. \"LIBOR 3M\"\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - key
         - o
         -

  .. _constr-contingentclaims-core-observation-add-59682:

  `Add <constr-contingentclaims-core-observation-add-59682_>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o, `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

    Sum of two observations\.

  .. _constr-contingentclaims-core-observation-neg-45561:

  `Neg <constr-contingentclaims-core-observation-neg-45561_>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

    Opposite of an observation\.

  .. _constr-contingentclaims-core-observation-mul-74041:

  `Mul <constr-contingentclaims-core-observation-mul-74041_>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o, `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

    Product of two observations\.

  .. _constr-contingentclaims-core-observation-div-40950:

  `Div <constr-contingentclaims-core-observation-div-40950_>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o, `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

    Division of two observations\.

  **instance** Corecursive (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o) (ObservationF t x o)

  **instance** Recursive (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o) (ObservationF t x o)

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x)

  **instance** (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ x, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ o) \=\> `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

  **instance** `Additive <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-additive-25881>`_ x \=\> `Additive <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-additive-25881>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

  **instance** `Multiplicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-multiplicative-10593>`_ x \=\> `Divisible <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-divisible-86689>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

  **instance** `Multiplicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-multiplicative-10593>`_ x \=\> `Multiplicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-multiplicative-10593>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

  **instance** (`Additive <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-additive-25881>`_ x, `Multiplicative <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-multiplicative-10593>`_ x) \=\> `Number <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-number-53664>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

  **instance** (`Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ t, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ x, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ o) \=\> `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ (`Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o)

.. _type-contingentclaims-core-observation-t-68930:

**type** `T <type-contingentclaims-core-observation-t-68930_>`_
  \= `Observation <type-contingentclaims-core-observation-observation-91686_>`_

  Type synonym for ``Observation``\.

Functions
---------

.. _function-contingentclaims-core-observation-pure-11509:

`pure <function-contingentclaims-core-observation-pure-11509_>`_
  \: x \-\> `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o

  Smart constructor for ``Const``\. Lifts a constant to an observation\.

.. _function-contingentclaims-core-observation-observe-80216:

`observe <function-contingentclaims-core-observation-observe-80216_>`_
  \: o \-\> `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o

  Smart constructor for ``Observe``\. Looks up the value of ``o``\.

.. _function-contingentclaims-core-observation-eval-5121:

`eval <function-contingentclaims-core-observation-eval-5121_>`_
  \: (`Number <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-number-53664>`_ x, `Divisible <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-divisible-86689>`_ x, `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ m) \=\> (o \-\> t \-\> m x) \-\> `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x o \-\> t \-\> m x

  Reify the ``Observation`` into an observation function\.
  This function is used to convert an abstract observation, e\.g\. ``LIBOR 3M + 0.005`` to the actual
  observation function ``t -> m x``\. The function is only total when the first argument is too
  (typically it will fail on ``t`` \> today)\.

.. _function-contingentclaims-core-observation-mapparams-29594:

`mapParams <function-contingentclaims-core-observation-mapparams-29594_>`_
  \: (t \-\> i) \-\> (o \-\> o') \-\> (x \-\> x') \-\> `Observation <type-contingentclaims-core-observation-observation-91686_>`_ i x o \-\> `Observation <type-contingentclaims-core-observation-observation-91686_>`_ t x' o'

  The functor map operation *and* also map any parameters to keys\.
  For example, could map the param \"spot\" to an ISIN code \"GB123456789\"\.
  Also contra\-maps time parameter, i\.e\. from relative time values to absolute ones\.

  @ mapParams identity \= bimap
