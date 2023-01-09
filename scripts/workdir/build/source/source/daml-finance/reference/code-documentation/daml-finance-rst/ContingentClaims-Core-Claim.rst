.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-contingentclaims-core-claim-90861:

Module ContingentClaims.Core.Claim
==================================

Data Types
----------

.. _type-contingentclaims-core-claim-t-59182:

**type** `T <type-contingentclaims-core-claim-t-59182_>`_
  \= :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>`

  Type synonym for ``Claim``\.

Functions
---------

.. _function-contingentclaims-core-claim-zero-85177:

`zero <function-contingentclaims-core-claim-zero-85177_>`_
  \: :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``Zero``\.

.. _function-contingentclaims-core-claim-one-13168:

`one <function-contingentclaims-core-claim-one-13168_>`_
  \: a \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``One``\.

.. _function-contingentclaims-core-claim-give-6964:

`give <function-contingentclaims-core-claim-give-6964_>`_
  \: :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``Give``\.

.. _function-contingentclaims-core-claim-and-76019:

`and <function-contingentclaims-core-claim-and-76019_>`_
  \: :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``And``\. Because of the explicit representation of the first two arguments
  of an ``And``, it can be cumbersome to write ``And c c' []``\. With this constructor, you can write
  ``c \\``and\\`` c'`` instead\. Flattens nested ``And``s and applies additive monoid identity eagerly\.
  Note this is an ``O(n)`` operation\. For a more efficient alternative, consider ``mconcat``\.

.. _function-contingentclaims-core-claim-or-94966:

`or <function-contingentclaims-core-claim-or-94966_>`_
  \: :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``Or``\. Because of the explicit representation of the first two arguments
  of an ``Or``, it can be cumbersome to write ``Or c c' []``\. With this constructor, you can write
  ``c \\``or\\`` c'`` instead\. Flattens nested ``Or``s\. Unlike ``and``, this does not apply a monoid
  identity\. Note this is an ``O(n)`` operation\.

.. _function-contingentclaims-core-claim-cond-73191:

`cond <function-contingentclaims-core-claim-cond-73191_>`_
  \: :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``Cond``\.

.. _function-contingentclaims-core-claim-scale-79608:

`scale <function-contingentclaims-core-claim-scale-79608_>`_
  \: :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``Scale``\.

.. _function-contingentclaims-core-claim-when-17123:

`when <function-contingentclaims-core-claim-when-17123_>`_
  \: :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``When``\.

.. _function-contingentclaims-core-claim-anytime-6525:

`anytime <function-contingentclaims-core-claim-anytime-6525_>`_
  \: :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``Anytime``\.

.. _function-contingentclaims-core-claim-until-84890:

`until <function-contingentclaims-core-claim-until-84890_>`_
  \: :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x a o

  Smart constructor for ``Until``\.

.. _function-contingentclaims-core-claim-mapparams-60286:

`mapParams <function-contingentclaims-core-claim-mapparams-60286_>`_
  \: (t \-\> i) \-\> (i \-\> t) \-\> (a \-\> a') \-\> (o \-\> o') \-\> (x \-\> x') \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` i x a o \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t x' a' o'

  Replace parameters in an ``Claim`` with actual values\.

.. _function-contingentclaims-core-claim-at-6466:

`at <function-contingentclaims-core-claim-at-6466_>`_
  \: t \-\> :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x o

  Smart constructor for ``TimeGte``\.
  This boolean predicate is ``True`` for time ≥ t, ``False`` otherwise\.

.. _function-contingentclaims-core-claim-upto-71491:

`upTo <function-contingentclaims-core-claim-upto-71491_>`_
  \: t \-\> :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x a

  Observable that is true for time ≤ t\.
  This boolean predicate is ``True`` for time ≤ t, ``False`` otherwise\.

.. _function-contingentclaims-core-claim-lteq-74380:

`(<=) <function-contingentclaims-core-claim-lteq-74380_>`_
  \: :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o \-\> :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x o

  Smart constructor for ``Lte``\.
  ``import Prelude hiding ((<=))`` in order to use this\.

.. _function-contingentclaims-core-claim-compare-73069:

`compare <function-contingentclaims-core-claim-compare-73069_>`_
  \: (`Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ t, `Ord <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-ord-6395>`_ x, `Number <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-number-53664>`_ x, `Divisible <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-num-divisible-86689>`_ x, `Action <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-action-68790>`_ m) \=\> (o \-\> t \-\> m x) \-\> :ref:`Inequality <type-contingentclaims-core-internal-claim-inequality-16052>` t x o \-\> t \-\> m `Bool <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-bool-66265>`_

  Reify the ``Inequality`` into an observation function\.
  This function is used to convert an abstract inequalityvation, e\.g\. ``S ≤ 50.0`` to the actual
  observation function ``t -> m Bool``\. The function is only total when the first argument is too
  (typically it will fail on ``t`` \> today)\.
