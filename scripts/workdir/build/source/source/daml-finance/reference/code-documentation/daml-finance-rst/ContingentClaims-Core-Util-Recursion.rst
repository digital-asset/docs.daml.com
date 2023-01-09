.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-contingentclaims-core-util-recursion-31812:

Module ContingentClaims.Core.Util.Recursion
===========================================

This module collects a set of utilities used to execute recursion schemes\.
The morphisms ending in 'M' are monadic variants, allowing to interleave, e\.g\., ``Update`` or
``Script``\. ``cataM`` after Tim Williams' talk, https\://www\.youtube\.com/watch?v\=Zw9KeP3OzpU\.

Functions
---------

.. _function-contingentclaims-core-util-recursion-param-75158:

`paraM <function-contingentclaims-core-util-recursion-param-75158_>`_
  \: (Monad m, `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ f, Recursive b f) \=\> (f (b, a) \-\> m a) \-\> b \-\> m a

  Monadic paramorphism\.

.. _function-contingentclaims-core-util-recursion-anam-90153:

`anaM <function-contingentclaims-core-util-recursion-anam-90153_>`_
  \: (Monad m, `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ f, Corecursive b f) \=\> (a \-\> m (f a)) \-\> a \-\> m b

  Monadic anamorphism\.

.. _function-contingentclaims-core-util-recursion-apom-58905:

`apoM <function-contingentclaims-core-util-recursion-apom-58905_>`_
  \: (Monad m, `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ f, Corecursive b f) \=\> (a \-\> m (f (`Either <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-types-either-56020>`_ b a))) \-\> a \-\> m b

  Monadic apomorphism\.

.. _function-contingentclaims-core-util-recursion-futum-18818:

`futuM <function-contingentclaims-core-util-recursion-futum-18818_>`_
  \: (Monad m, `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ f, Corecursive b f) \=\> (a \-\> m (f (Free f a))) \-\> a \-\> m b

  Monadic futumorphism\.

.. _function-contingentclaims-core-util-recursion-apocatam-53978:

`apoCataM <function-contingentclaims-core-util-recursion-apocatam-53978_>`_
  \: (Monad m, `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ f, Corecursive b f) \=\> (f b \-\> b) \-\> (a \-\> m (f (`Either <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-types-either-56020>`_ b a))) \-\> a \-\> m b

  Monadic lazy unfold (apoM) followed by a fold (cata)\.
  This Specialised lazy re\-fold is used by ``lifecycle``\.

.. _function-contingentclaims-core-util-recursion-hylom-87030:

`hyloM <function-contingentclaims-core-util-recursion-hylom-87030_>`_
  \: (`Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ f, Monad n) \=\> (f b \-\> b) \-\> (a \-\> n (f a)) \-\> a \-\> n b

  A modified ``hylo`` (refold), whith an interleaved monad effect (typically ``Update``)\.

.. _function-contingentclaims-core-util-recursion-ghylom-76190:

`ghyloM <function-contingentclaims-core-util-recursion-ghylom-76190_>`_
  \: (Comonad w, `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ f, Monad m, `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ m, Monad n) \=\> (f (w c) \-\> w (f c)) \-\> (m (f d) \-\> f (m d)) \-\> (f (w b) \-\> b) \-\> (a \-\> n (f (m a))) \-\> a \-\> n b

  Generalised hylomorphism (with monadic unfold)\.

.. _function-contingentclaims-core-util-recursion-funzip-33244:

`funzip <function-contingentclaims-core-util-recursion-funzip-33244_>`_
  \: `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ f \=\> f (a, b) \-\> (f a, f b)

  Functor unzip\.

.. _function-contingentclaims-core-util-recursion-synthesize-62588:

`synthesize <function-contingentclaims-core-util-recursion-synthesize-62588_>`_
  \: (`Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ f, Recursive b f) \=\> (f attr \-\> attr) \-\> b \-\> Cofree f attr

  Annotate a recursive type bottom\-up\.

.. _function-contingentclaims-core-util-recursion-inherit-44382:

`inherit <function-contingentclaims-core-util-recursion-inherit-44382_>`_
  \: (`Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ f, Corecursive b f, Recursive b f) \=\> (b \-\> attr \-\> attr) \-\> attr \-\> b \-\> Cofree f attr

  Annotate a recursive type top\-down\.
