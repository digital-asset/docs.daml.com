.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-da-bignumeric-85314:

DA.BigNumeric
=============

This module exposes operations for working with the ``BigNumeric`` type\.

Functions
---------

.. _function-da-bignumeric-scale-86425:

`scale <function-da-bignumeric-scale-86425_>`_
  \: :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`Int <type-ghc-types-int-37261>`

  Calculate the scale of a ``BigNumeric`` number\. The ``BigNumeric`` number is
  represented as ``n * 10^-s`` where ``n`` is an integer with no trailing zeros,
  and ``s`` is the scale\.

  Thus, the scale represents the number of nonzero digits after the decimal point\.
  Note that the scale can be negative if the ``BigNumeric`` represents an integer
  with trailing zeros\. In that case, it represents the number of trailing zeros
  (negated)\.

  The scale ranges between 2\^15 and \-2\^15 \+ 1\.
  The scale of ``0`` is ``0`` by convention\.

  .. code-block:: daml

    >>> scale 1.1
    1


  .. code-block:: daml

    >>> scale (shiftLeft (2^14) 1.0)
    -2^14

.. _function-da-bignumeric-precision-71155:

`precision <function-da-bignumeric-precision-71155_>`_
  \: :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`Int <type-ghc-types-int-37261>`

  Calculate the precision of a ``BigNumeric`` number\. The ``BigNumeric`` number is
  represented as ``n * 10^-s`` where ``n`` is an integer with no trailing zeros,
  and ``s`` is the scale\. The precision is the number of digits in ``n``\.

  Thus, the precision represents the number of significant digits in the ``BigNumeric``\.

  The precision ranges between 0 and 2\^16 \- 1\.

  .. code-block:: daml

    >>> precision 1.10
    2

.. _function-da-bignumeric-div-13956:

`div <function-da-bignumeric-div-13956_>`_
  \: :ref:`Int <type-ghc-types-int-37261>` \-\> :ref:`RoundingMode <type-ghc-types-roundingmode-50660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>`

  Calculate a division of ``BigNumeric`` numbers\. The value of ``div n r a b``
  is the division of ``a`` by ``b``, rounded to ``n`` decimal places (i\.e\. scale),
  according to the rounding mode ``r``\.

  This will fail when dividing by ``0``, and when using the ``RoundingUnnecessary``
  mode for a number that cannot be represented exactly with at most ``n`` decimal
  places\.

.. _function-da-bignumeric-round-91787:

`round <function-da-bignumeric-round-91787_>`_
  \: :ref:`Int <type-ghc-types-int-37261>` \-\> :ref:`RoundingMode <type-ghc-types-roundingmode-50660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>`

  Round a ``BigNumeric`` number\. The value of ``round n r a`` is the value
  of ``a`` rounded to ``n`` decimal places (i\.e\. scale), according to the rounding
  mode ``r``\.

  This will fail when using the ``RoundingUnnecessary`` mode for a number that cannot
  be represented exactly with at most ``n`` decimal places\.

.. _function-da-bignumeric-shiftright-72144:

`shiftRight <function-da-bignumeric-shiftright-72144_>`_
  \: :ref:`Int <type-ghc-types-int-37261>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>`

  Shift a ``BigNumeric`` number to the right by a power of 10\. The value
  ``shiftRight n a`` is the value of ``a`` times ``10^(-n)``\.

  This will fail if the resulting ``BigNumeric`` is out of bounds\.

  .. code-block:: daml

    >>> shiftRight 2 32.0
    0.32

.. _function-da-bignumeric-shiftleft-59824:

`shiftLeft <function-da-bignumeric-shiftleft-59824_>`_
  \: :ref:`Int <type-ghc-types-int-37261>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>`

  Shift a ``BigNumeric`` number to the left by a power of 10\. The value
  ``shiftLeft n a`` is the value of ``a`` times ``10^n``\.

  This will fail if the resulting ``BigNumeric`` is out of bounds\.

  .. code-block:: daml

    >>> shiftLeft 2 32.0
    3200.0

.. _function-da-bignumeric-roundtonumeric-55442:

`roundToNumeric <function-da-bignumeric-roundtonumeric-55442_>`_
  \: :ref:`NumericScale <class-ghc-classes-numericscale-83720>` n \=\> :ref:`RoundingMode <type-ghc-types-roundingmode-50660>` \-\> :ref:`BigNumeric <type-ghc-types-bignumeric-26660>` \-\> :ref:`Numeric <type-ghc-types-numeric-891>` n

  Round a ``BigNumeric`` and cast it to a ``Numeric``\. This function uses the
  scale of the resulting numeric to determine the scale of the rounding\.

  This will fail when using the ``RoundingUnnecessary`` mode if the ``BigNumeric``
  cannot be represented exactly in the requested ``Numeric n``\.

  .. code-block:: daml

    >>> (roundToNumeric RoundingHalfUp 1.23456789 : Numeric 5)
    1.23457
