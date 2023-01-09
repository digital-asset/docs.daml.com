.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-da-numeric-17471:

DA.Numeric
==========

Functions
---------

.. _function-da-numeric-mul-81896:

`mul <function-da-numeric-mul-81896_>`_
  \: :ref:`NumericScale <class-ghc-classes-numericscale-83720>` n3 \=\> :ref:`Numeric <type-ghc-types-numeric-891>` n1 \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n2 \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n3

  Multiply two numerics\. Both inputs and the output may have
  different scales, unlike ``(*)`` which forces all numeric scales
  to be the same\. Raises an error on overflow, rounds to chosen
  scale otherwise\.

.. _function-da-numeric-div-56407:

`div <function-da-numeric-div-56407_>`_
  \: :ref:`NumericScale <class-ghc-classes-numericscale-83720>` n3 \=\> :ref:`Numeric <type-ghc-types-numeric-891>` n1 \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n2 \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n3

  Divide two numerics\. Both inputs and the output may have
  different scales, unlike ``(/)`` which forces all numeric scales
  to be the same\. Raises an error on overflow, rounds to chosen
  scale otherwise\.

.. _function-da-numeric-cast-54256:

`cast <function-da-numeric-cast-54256_>`_
  \: :ref:`NumericScale <class-ghc-classes-numericscale-83720>` n2 \=\> :ref:`Numeric <type-ghc-types-numeric-891>` n1 \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n2

  Cast a Numeric\. Raises an error on overflow or loss of precision\.

.. _function-da-numeric-castandround-59941:

`castAndRound <function-da-numeric-castandround-59941_>`_
  \: :ref:`NumericScale <class-ghc-classes-numericscale-83720>` n2 \=\> :ref:`Numeric <type-ghc-types-numeric-891>` n1 \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n2

  Cast a Numeric\. Raises an error on overflow, rounds to chosen
  scale otherwise\.

.. _function-da-numeric-shift-13796:

`shift <function-da-numeric-shift-13796_>`_
  \: :ref:`NumericScale <class-ghc-classes-numericscale-83720>` n2 \=\> :ref:`Numeric <type-ghc-types-numeric-891>` n1 \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n2

  Move the decimal point left or right by multiplying the numeric
  value by 10\^(n1 \- n2)\. Does not overflow or underflow\.

.. _function-da-numeric-pi-88702:

`pi <function-da-numeric-pi-88702_>`_
  \: :ref:`NumericScale <class-ghc-classes-numericscale-83720>` n \=\> :ref:`Numeric <type-ghc-types-numeric-891>` n

  The number pi\.
