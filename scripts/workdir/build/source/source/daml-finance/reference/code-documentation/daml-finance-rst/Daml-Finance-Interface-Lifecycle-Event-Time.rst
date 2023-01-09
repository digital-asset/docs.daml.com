.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-lifecycle-event-time-4252:

Module Daml.Finance.Interface.Lifecycle.Event.Time
==================================================

Interfaces
----------

.. _type-daml-finance-interface-lifecycle-event-time-event-90457:

**interface** `Event <type-daml-finance-interface-lifecycle-event-time-event-90457_>`_

  Event interface for events that signal the passing of (business) time\.

  + **Choice Archive**

    (no fields)

  + **Choice GetView**

    Retrieves the event view\. The event's time can be retrieved from the generic ``Event``
    interface\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party retrieving the view\.

  + **Method advance \:** Advance \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Time <type-daml-finance-interface-data-reference-time-time-91391>`, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Event <type-daml-finance-interface-lifecycle-event-time-event-90457_>`_)

    Implementation of the ``Advance`` choice\.

  + **Method rewind \:** Rewind \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ (`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ :ref:`Time <type-daml-finance-interface-data-reference-time-time-91391>`, `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ `Event <type-daml-finance-interface-lifecycle-event-time-event-90457_>`_)

    Implementation of the ``Rewind`` choice\.

  + **Method asEvent \:** :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`

    Conversion to base ``Event`` interface\.

Typeclasses
-----------

.. _class-daml-finance-interface-lifecycle-event-time-hasimplementation-72442:

**class** `Implementation <type-daml-finance-interface-lifecycle-event-time-implementation-714_>`_ t \=\> `HasImplementation <class-daml-finance-interface-lifecycle-event-time-hasimplementation-72442_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-lifecycle-event-time-i-23752:

**type** `I <type-daml-finance-interface-lifecycle-event-time-i-23752_>`_
  \= `Event <type-daml-finance-interface-lifecycle-event-time-event-90457_>`_

  Type synonym for ``Event``\.

.. _type-daml-finance-interface-lifecycle-event-time-implementation-714:

**type** `Implementation <type-daml-finance-interface-lifecycle-event-time-implementation-714_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `Event <type-daml-finance-interface-lifecycle-event-time-event-90457_>`_, :ref:`Implementation <type-daml-finance-interface-lifecycle-event-implementation-22192>` t)

  Type constraint for requiring templates to implement ``Event``\.

.. _type-daml-finance-interface-lifecycle-event-time-v-38799:

**type** `V <type-daml-finance-interface-lifecycle-event-time-v-38799_>`_
  \= `View <type-daml-finance-interface-lifecycle-event-time-view-37477_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Event <type-daml-finance-interface-lifecycle-event-time-event-90457_>`_ `V <type-daml-finance-interface-lifecycle-event-time-v-38799_>`_

.. _type-daml-finance-interface-lifecycle-event-time-view-37477:

**data** `View <type-daml-finance-interface-lifecycle-event-time-view-37477_>`_

  View for ``Event``\.

  .. _constr-daml-finance-interface-lifecycle-event-time-view-37344:

  `View <constr-daml-finance-interface-lifecycle-event-time-view-37344_>`_

    (no fields)

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-lifecycle-event-time-view-37477_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-lifecycle-event-time-view-37477_>`_

Functions
---------

.. _function-daml-finance-interface-lifecycle-event-time-asevent-45179:

`asEvent <function-daml-finance-interface-lifecycle-event-time-asevent-45179_>`_
  \: `Event <type-daml-finance-interface-lifecycle-event-time-event-90457_>`_ \-\> :ref:`I <type-daml-finance-interface-lifecycle-event-i-17082>`
