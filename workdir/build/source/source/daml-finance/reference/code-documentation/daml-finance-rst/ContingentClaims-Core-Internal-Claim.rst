.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-contingentclaims-core-internal-claim-23633:

Module ContingentClaims.Core.Internal.Claim
===========================================

Data Types
----------

.. _type-contingentclaims-core-internal-claim-claim-35538:

**data** `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o

  Core data type used to model cashflows of instruments\.
  Check out the
  Daml Finance documentation(https://digital-asset.github.io/daml-finance/concepts/contingent-claims.html)
  for a detailed explanation\.
  In the reference paper from Peyton\-Jones this is called 'Contract'\.
  We renamed it to avoid ambiguity\.

  * ``t`` and ``x`` respectively correspond to the ``Observation`` input type and the resulting output
    type\. An observation is a function from ``t`` to ``x``\. A common choice is to use ``Time`` and
    ``Decimal``, respectively\.
  * ``a`` is the representation of an asset, e\.g\. a ``Text`` ISIN code\.
  * ``o`` is the representation of an observable, e\.g\. a ``Text``\.

  You should build the ``Claim`` using the smart constructors (e\.g\. ``zero``, ``and``) instead of using
  the data constructors directly (``Zero``, ``And``)\.

  .. _constr-contingentclaims-core-internal-claim-zero-91734:

  `Zero <constr-contingentclaims-core-internal-claim-zero-91734_>`_

    Represents an absence of claims\. Monoid ``And`` identity\.

  .. _constr-contingentclaims-core-internal-claim-one-74385:

  `One <constr-contingentclaims-core-internal-claim-one-74385_>`_ a

    The bearer acquires one unit of ``a``  *immediately*\.

  .. _constr-contingentclaims-core-internal-claim-give-57619:

  `Give <constr-contingentclaims-core-internal-claim-give-57619_>`_ (`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o)

    The obligations of the bearer and issuer are reversed\.

  .. _constr-contingentclaims-core-internal-claim-and-71042:

  `And <constr-contingentclaims-core-internal-claim-and-71042_>`_

    Used to combine multiple rights together\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - fst
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -
       * - snd
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -
       * - tail
         - \[`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o\]
         -

  .. _constr-contingentclaims-core-internal-claim-or-76817:

  `Or <constr-contingentclaims-core-internal-claim-or-76817_>`_

    Gives the bearer the right to choose between several claims\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - fst
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -
       * - snd
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -
       * - tail
         - \[`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o\]
         -

  .. _constr-contingentclaims-core-internal-claim-cond-87672:

  `Cond <constr-contingentclaims-core-internal-claim-cond-87672_>`_

    Gives the bearer the right to the first claim if ``predicate`` is true, else the second
    claim\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - predicate
         - `Inequality <type-contingentclaims-core-internal-claim-inequality-16052_>`_ t x o
         -
       * - success
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -
       * - failure
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -

  .. _constr-contingentclaims-core-internal-claim-scale-17585:

  `Scale <constr-contingentclaims-core-internal-claim-scale-17585_>`_

    Multiplies the ``claim`` by ``k`` (which can be non\-deterministic)\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - k
         - :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o
         -
       * - claim
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -

  .. _constr-contingentclaims-core-internal-claim-when-91024:

  `When <constr-contingentclaims-core-internal-claim-when-91024_>`_

    Defers the acquisition of ``claim`` until *the first instant* that ``predicate`` is true\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - predicate
         - `Inequality <type-contingentclaims-core-internal-claim-inequality-16052_>`_ t x o
         -
       * - claim
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -

  .. _constr-contingentclaims-core-internal-claim-anytime-28688:

  `Anytime <constr-contingentclaims-core-internal-claim-anytime-28688_>`_

    Like ``When``, but valid any time the predicate is true (not just infinium)\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - predicate
         - `Inequality <type-contingentclaims-core-internal-claim-inequality-16052_>`_ t x o
         -
       * - claim
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -

  .. _constr-contingentclaims-core-internal-claim-until-25523:

  `Until <constr-contingentclaims-core-internal-claim-until-25523_>`_

    Expires said claim on the *first instant* that ``predicate`` is true\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - predicate
         - `Inequality <type-contingentclaims-core-internal-claim-inequality-16052_>`_ t x o
         -
       * - claim
         - `Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o
         -

  **instance** Corecursive (`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o) (ClaimF t x a o)

  **instance** Recursive (`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o) (ClaimF t x a o)

  **instance** (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ a, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ x, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ o, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ t) \=\> `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ (`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o)

  **instance** (`Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ t, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ x, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ a, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ o) \=\> `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ (`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o)

  **instance** `Monoid <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-monoid-6742>`_ (`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o)

  **instance** `Semigroup <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-semigroup-78998>`_ (`Claim <type-contingentclaims-core-internal-claim-claim-35538_>`_ t x a o)

.. _type-contingentclaims-core-internal-claim-inequality-16052:

**data** `Inequality <type-contingentclaims-core-internal-claim-inequality-16052_>`_ t x o

  Data type for boolean predicates supported by the library\.
  A boolean predicate is a generic function with signature ``t -> x -> Bool``\. However, a lmited set
  of predicates is currently supported\.

  .. _constr-contingentclaims-core-internal-claim-timegte-91610:

  `TimeGte <constr-contingentclaims-core-internal-claim-timegte-91610_>`_ t

    ``True`` when ``time ≥ t``, ``False`` otherwise\.

  .. _constr-contingentclaims-core-internal-claim-timelte-19581:

  `TimeLte <constr-contingentclaims-core-internal-claim-timelte-19581_>`_ t

    ``True`` when ``time ≤ t``, ``False`` otherwise\.

  .. _constr-contingentclaims-core-internal-claim-lte-19296:

  `Lte <constr-contingentclaims-core-internal-claim-lte-19296_>`_ (:ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o, :ref:`Observation <type-contingentclaims-core-observation-observation-91686>` t x o)

    ``True`` when ``o(t, x) ≤ o'(t, x)``, ``False`` otherwise
    for a pair of observations ``o``, ``o'``\.

  **instance** (`Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ t, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ x, `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ o) \=\> `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ (`Inequality <type-contingentclaims-core-internal-claim-inequality-16052_>`_ t x o)

  **instance** (`Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ t, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ x, `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ o) \=\> `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ (`Inequality <type-contingentclaims-core-internal-claim-inequality-16052_>`_ t x o)
