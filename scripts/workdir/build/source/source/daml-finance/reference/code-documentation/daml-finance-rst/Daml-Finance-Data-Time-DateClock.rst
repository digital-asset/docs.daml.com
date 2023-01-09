.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-data-time-dateclock-65212:

Module Daml.Finance.Data.Time.DateClock
=======================================

Templates
---------

.. _type-daml-finance-data-time-dateclock-dateclock-90915:

**template** `DateClock <type-daml-finance-data-time-dateclock-dateclock-90915_>`_

  A ``DateClock`` is a template used to keep track of the current date\.
  It implements the ``Time`` rule interface to be able to advance and rewind business time\. It also
  implements the ``TimeObservable`` interface\. Specifically, each date ``D`` is mapped to
  ``D 00:00:00 UTC``\. If your use\-case involves working across multiple time zones, you may need to
  define multiple ``DateClock`` templates with specific time conversions\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - The clock's providers\.
     * - date
       - :ref:`Unit <type-daml-finance-data-time-dateclock-types-unit-52065>`
       - The clock's date\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - The clock's identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - The clock's description\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-data-reference-time-i-30870>` **for** `DateClock <type-daml-finance-data-time-dateclock-dateclock-90915_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-observable-timeobservable-i-39421>` **for** `DateClock <type-daml-finance-data-time-dateclock-dateclock-90915_>`_

Data Types
----------

.. _type-daml-finance-data-time-dateclock-t-81049:

**type** `T <type-daml-finance-data-time-dateclock-t-81049_>`_
  \= `DateClock <type-daml-finance-data-time-dateclock-dateclock-90915_>`_

  Type synonym for ``DateClock``\.
