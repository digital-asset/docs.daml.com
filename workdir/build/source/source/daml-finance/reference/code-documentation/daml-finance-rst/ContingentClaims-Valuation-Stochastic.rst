.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-contingentclaims-valuation-stochastic-37844:

Module ContingentClaims.Valuation.Stochastic
============================================

Typeclasses
-----------

.. _class-contingentclaims-valuation-stochastic-isidentifier-12300:

**class** `IsIdentifier <class-contingentclaims-valuation-stochastic-isidentifier-12300_>`_ t **where**

  .. _function-contingentclaims-valuation-stochastic-localvar-55150:

  `localVar <function-contingentclaims-valuation-stochastic-localvar-55150_>`_
    \: `Int <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-int-37261>`_ \-\> t

    Produce a local identifier of type ``t``, subindexed by ``i``\.

Data Types
----------

.. _type-contingentclaims-valuation-stochastic-expr-34143:

**data** `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t

  Represents an expression of t\-adapted stochastic processes\.

  .. _constr-contingentclaims-valuation-stochastic-const-74883:

  `Const <constr-contingentclaims-valuation-stochastic-const-74883_>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_


  .. _constr-contingentclaims-valuation-stochastic-ident-27600:

  `Ident <constr-contingentclaims-valuation-stochastic-ident-27600_>`_ t


  .. _constr-contingentclaims-valuation-stochastic-proc-88863:

  `Proc <constr-contingentclaims-valuation-stochastic-proc-88863_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - name
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - process
         - `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t
         -
       * - filtration
         - t
         -

  .. _constr-contingentclaims-valuation-stochastic-sup-52916:

  `Sup <constr-contingentclaims-valuation-stochastic-sup-52916_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lowerBound
         - t
         -
       * - tau
         - t
         -
       * - rv
         - `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t
         -

  .. _constr-contingentclaims-valuation-stochastic-sum-54737:

  `Sum <constr-contingentclaims-valuation-stochastic-sum-54737_>`_ \[`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t\]


  .. _constr-contingentclaims-valuation-stochastic-neg-38822:

  `Neg <constr-contingentclaims-valuation-stochastic-neg-38822_>`_ (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t)


  .. _constr-contingentclaims-valuation-stochastic-mul-94150:

  `Mul <constr-contingentclaims-valuation-stochastic-mul-94150_>`_ (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t, `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t)


  .. _constr-contingentclaims-valuation-stochastic-pow-80002:

  `Pow <constr-contingentclaims-valuation-stochastic-pow-80002_>`_ (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t, `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t)


  .. _constr-contingentclaims-valuation-stochastic-i-18527:

  `I <constr-contingentclaims-valuation-stochastic-i-18527_>`_ (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t, `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t)


  .. _constr-contingentclaims-valuation-stochastic-e-66387:

  `E <constr-contingentclaims-valuation-stochastic-e-66387_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - rv
         - `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t
         -
       * - filtration
         - t
         -

  **instance** :ref:`ToXml <class-contingentclaims-valuation-mathml-toxml-10440>` t \=\> :ref:`ToXml <class-contingentclaims-valuation-mathml-toxml-10440>` (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t)

  **instance** Corecursive (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t) (`ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t)

  **instance** Recursive (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t) (`ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t)

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ t \=\> `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t)

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ t \=\> `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t)

.. _type-contingentclaims-valuation-stochastic-exprf-78496:

**data** `ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t x

  Base functor for ``Expr``\. Note that this is ADT is re\-used in a couple of places, e\.g\.,
  ``Process``, where however not every choice is legal and will lead to a partial evaluator\.

  .. _constr-contingentclaims-valuation-stochastic-constf-13072:

  `ConstF <constr-contingentclaims-valuation-stochastic-constf-13072_>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_


  .. _constr-contingentclaims-valuation-stochastic-identf-75709:

  `IdentF <constr-contingentclaims-valuation-stochastic-identf-75709_>`_ t


  .. _constr-contingentclaims-valuation-stochastic-procf-8736:

  `ProcF <constr-contingentclaims-valuation-stochastic-procf-8736_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - name
         - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
         -
       * - process
         - `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t
         -
       * - filtration
         - t
         -

  .. _constr-contingentclaims-valuation-stochastic-supf-72237:

  `SupF <constr-contingentclaims-valuation-stochastic-supf-72237_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lowerBound
         - t
         -
       * - tau
         - t
         -
       * - rv
         - x
         -

  .. _constr-contingentclaims-valuation-stochastic-sumf-36426:

  `SumF <constr-contingentclaims-valuation-stochastic-sumf-36426_>`_ \[x\]


  .. _constr-contingentclaims-valuation-stochastic-negf-88723:

  `NegF <constr-contingentclaims-valuation-stochastic-negf-88723_>`_ x


  .. _constr-contingentclaims-valuation-stochastic-mulf-20435:

  `MulF <constr-contingentclaims-valuation-stochastic-mulf-20435_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lhs
         - x
         -
       * - rhs
         - x
         -

  .. _constr-contingentclaims-valuation-stochastic-powf-60695:

  `PowF <constr-contingentclaims-valuation-stochastic-powf-60695_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lhs
         - x
         -
       * - rhs
         - x
         -

  .. _constr-contingentclaims-valuation-stochastic-if-9970:

  `I_F <constr-contingentclaims-valuation-stochastic-if-9970_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - lhs
         - x
         -
       * - rhs
         - x
         -

  .. _constr-contingentclaims-valuation-stochastic-ef-22806:

  `E_F <constr-contingentclaims-valuation-stochastic-ef-22806_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - rv
         - x
         -
       * - filtration
         - t
         -

  **instance** Corecursive (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t) (`ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t)

  **instance** Recursive (`Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t) (`ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t)

  **instance** `Functor <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-base-functor-31205>`_ (`ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t)

  **instance** `Foldable <https://docs.daml.com/daml/stdlib/DA-Foldable.html#class-da-foldable-foldable-25994>`_ (`ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t)

  **instance** `Traversable <https://docs.daml.com/daml/stdlib/DA-Traversable.html#class-da-traversable-traversable-18144>`_ (`ExprF <type-contingentclaims-valuation-stochastic-exprf-78496_>`_ t)

.. _type-contingentclaims-valuation-stochastic-process-42020:

**data** `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t

  A stochastic processes\. Currently this represents a Geometric Browniam Motion, i\.e\.,
  dX / X \= α dt \+ β dW\. Eventually, we wish to support other processes such as Levy\.

  .. _constr-contingentclaims-valuation-stochastic-process-5639:

  `Process <constr-contingentclaims-valuation-stochastic-process-5639_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - dt
         - `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t
         -
       * - dW
         - `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t
         -

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ t \=\> `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ (`Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t)

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ t \=\> `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ (`Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t)

Functions
---------

.. _function-contingentclaims-valuation-stochastic-riskless-25180:

`riskless <function-contingentclaims-valuation-stochastic-riskless-25180_>`_
  \: t \-\> `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t

  Helper function to create a riskless process ``dS = r dt``\.

.. _function-contingentclaims-valuation-stochastic-gbm-84999:

`gbm <function-contingentclaims-valuation-stochastic-gbm-84999_>`_
  \: t \-\> t \-\> `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t

  Helper function to create a geometric BM ``dS = μ dt + σ dW``\.

.. _function-contingentclaims-valuation-stochastic-fapf-7751:

`fapf <function-contingentclaims-valuation-stochastic-fapf-7751_>`_
  \: (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ a, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ a, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ o, `IsIdentifier <class-contingentclaims-valuation-stochastic-isidentifier-12300_>`_ t) \=\> a \-\> (a \-\> `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t) \-\> (a \-\> a \-\> `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t) \-\> (o \-\> `Process <type-contingentclaims-valuation-stochastic-process-42020_>`_ t) \-\> t \-\> :ref:`Claim <type-contingentclaims-core-internal-claim-claim-35538>` t `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_ a o \-\> `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t

  Converts a ``Claim`` into the Fundamental Asset Pricing Formula\. The ϵ expressions are defined as
  E1\-E10 in the Eber/Peyton\-Jones paper\. If you squint you can almost see they correspond
  one\-to\-one to the formulae in our whitepaper\. This is still an experimental feature\.

.. _function-contingentclaims-valuation-stochastic-simplify-57423:

`simplify <function-contingentclaims-valuation-stochastic-simplify-57423_>`_
  \: `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t \-\> `Expr <type-contingentclaims-valuation-stochastic-expr-34143_>`_ t

  This is meant to be a function that algebraically simplifies the FAPF by

  1. using simple identities and ring laws
  2. change of numeraire technique\.
     This is still an experimental feature\.
