.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-contingentclaims-valuation-mathml-30102:

Module ContingentClaims.Valuation.MathML
========================================

Typeclasses
-----------

.. _class-contingentclaims-valuation-mathml-toxml-10440:

**class** `ToXml <class-contingentclaims-valuation-mathml-toxml-10440_>`_ a **where**

  Renders an ``Expr`` into MathML presentation format\.

  .. _function-contingentclaims-valuation-mathml-presentation-97680:

  `presentation <function-contingentclaims-valuation-mathml-presentation-97680_>`_
    \: a \-\> Xml

  **instance** `ToXml <class-contingentclaims-valuation-mathml-toxml-10440_>`_ t \=\> `ToXml <class-contingentclaims-valuation-mathml-toxml-10440_>`_ (:ref:`Expr <type-contingentclaims-valuation-stochastic-expr-34143>` t)

  **instance** `ToXml <class-contingentclaims-valuation-mathml-toxml-10440_>`_ `Decimal <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-decimal-18135>`_

  **instance** `ToXml <class-contingentclaims-valuation-mathml-toxml-10440_>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_

  **instance** `ToXml <class-contingentclaims-valuation-mathml-toxml-10440_>`_ `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
