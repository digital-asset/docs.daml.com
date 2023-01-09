.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-data-time-dateclockupdate-48859:

Module Daml.Finance.Data.Time.DateClockUpdate
=============================================

Templates
---------

.. _type-daml-finance-data-time-dateclockupdate-dateclockupdateevent-5430:

**template** `DateClockUpdateEvent <type-daml-finance-data-time-dateclockupdate-dateclockupdateevent-5430_>`_

  Event signalling the update of a ``DateClock``\. It can trigger the execution of lifecycle rules
  for some instruments\.

  .. list-table::
     :widths: 15 10 30
     :header-rows: 1

     * - Field
       - Type
       - Description
     * - providers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - Providers of the event\.
     * - date
       - `Date <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-date-32253>`_
       - The updated clock data\.
     * - eventTime
       - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
       - The event time\.
     * - id
       - :ref:`Id <type-daml-finance-interface-types-common-types-id-31223>`
       - Event identifier\.
     * - description
       - `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_
       - Event description\.
     * - observers
       - :ref:`Parties <type-daml-finance-interface-types-common-types-parties-94211>`
       - The clock's observers\.

  + **Choice Archive**

    (no fields)

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>` **for** `DateClockUpdateEvent <type-daml-finance-data-time-dateclockupdate-dateclockupdateevent-5430_>`_

  + **interface instance** :ref:`I <type-daml-finance-interface-lifecycle-event-time-i-23752>` **for** `DateClockUpdateEvent <type-daml-finance-data-time-dateclockupdate-dateclockupdateevent-5430_>`_

Data Types
----------

.. _type-daml-finance-data-time-dateclockupdate-t-61716:

**type** `T <type-daml-finance-data-time-dateclockupdate-t-61716_>`_
  \= `DateClockUpdateEvent <type-daml-finance-data-time-dateclockupdate-dateclockupdateevent-5430_>`_

  Type synonym for ``DateClockUpdateEvent``\.
