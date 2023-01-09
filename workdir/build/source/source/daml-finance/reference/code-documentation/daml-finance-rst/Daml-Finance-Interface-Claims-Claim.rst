.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-claims-claim-82866:

Module Daml.Finance.Interface.Claims.Claim
==========================================

Interfaces
----------

.. _type-daml-finance-interface-claims-claim-claim-8835:

**interface** `Claim <type-daml-finance-interface-claims-claim-claim-8835_>`_

  Interface implemented by templates that can be represented as Contingent Claims\.

  + **Choice Archive**

    (no fields)

  + **Choice GetClaims**

    Retrieves the list of claims representing the instrument\. This might involve fetching
    reference data, such as calendars, on which the actor must have visibility\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - actor
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party retrieving the claims\.

  + **Choice GetView**

    Retrieves the interface view\.

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - viewer
         - `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_
         - The party retrieving the view\.

  + **Method asBaseInstrument \:** :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

    Conversion to base ``Instrument`` interface\.

  + **Method getClaims \:** GetClaims \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\]

    The list of claims representing the instrument\.

Typeclasses
-----------

.. _class-daml-finance-interface-claims-claim-hasimplementation-88500:

**class** `Implementation <type-daml-finance-interface-claims-claim-implementation-40844_>`_ t \=\> `HasImplementation <class-daml-finance-interface-claims-claim-hasimplementation-88500_>`_ t **where**


Data Types
----------

.. _type-daml-finance-interface-claims-claim-i-15462:

**type** `I <type-daml-finance-interface-claims-claim-i-15462_>`_
  \= `Claim <type-daml-finance-interface-claims-claim-claim-8835_>`_

  Type synonym for ``Claim``\.

  **instance** HasMethod :ref:`Instrument <type-daml-finance-interface-instrument-generic-instrument-instrument-11652>` \"asClaim\" `I <type-daml-finance-interface-claims-claim-i-15462_>`_

.. _type-daml-finance-interface-claims-claim-implementation-40844:

**type** `Implementation <type-daml-finance-interface-claims-claim-implementation-40844_>`_ t
  \= (`HasToInterface <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-interface-hastointerface-68104>`_ t `I <type-daml-finance-interface-claims-claim-i-15462_>`_, :ref:`Implementation <type-daml-finance-interface-instrument-base-instrument-implementation-67110>` t)

  Type constraint for requiring templates to implement ``Claim``\.

.. _type-daml-finance-interface-claims-claim-v-8849:

**type** `V <type-daml-finance-interface-claims-claim-v-8849_>`_
  \= `View <type-daml-finance-interface-claims-claim-view-42823_>`_

  Type synonym for ``View``\.

  **instance** `HasFromAnyView <https://docs.daml.com/daml/stdlib/DA-Internal-Interface-AnyView.html#class-da-internal-interface-anyview-hasfromanyview-30108>`_ `Claim <type-daml-finance-interface-claims-claim-claim-8835_>`_ `V <type-daml-finance-interface-claims-claim-v-8849_>`_

.. _type-daml-finance-interface-claims-claim-view-42823:

**data** `View <type-daml-finance-interface-claims-claim-view-42823_>`_

  View for ``Claim``\.

  .. _constr-daml-finance-interface-claims-claim-view-92050:

  `View <constr-daml-finance-interface-claims-claim-view-92050_>`_

    .. list-table::
       :widths: 15 10 30
       :header-rows: 1

       * - Field
         - Type
         - Description
       * - acquisitionTime
         - `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_
         - The claim's acquisition time\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `View <type-daml-finance-interface-claims-claim-view-42823_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `View <type-daml-finance-interface-claims-claim-view-42823_>`_

Functions
---------

.. _function-daml-finance-interface-claims-claim-asbaseinstrument-6172:

`asBaseInstrument <function-daml-finance-interface-claims-claim-asbaseinstrument-6172_>`_
  \: `Claim <type-daml-finance-interface-claims-claim-claim-8835_>`_ \-\> :ref:`I <type-daml-finance-interface-instrument-base-instrument-i-67236>`

.. _function-daml-finance-interface-claims-claim-getclaims-52748:

`getClaims <function-daml-finance-interface-claims-claim-getclaims-52748_>`_
  \: `Claim <type-daml-finance-interface-claims-claim-claim-8835_>`_ \-\> GetClaims \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ \[:ref:`TaggedClaim <type-daml-finance-interface-claims-types-taggedclaim-15494>`\]

.. _function-daml-finance-interface-claims-claim-getclaim-12044:

`getClaim <function-daml-finance-interface-claims-claim-getclaim-12044_>`_
  \: `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> `Claim <type-daml-finance-interface-claims-claim-claim-8835_>`_ \-\> `Update <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-update-68072>`_ :ref:`C <type-daml-finance-interface-claims-types-c-53263>`

  Retrieves the single claim representing the template\. An error is thrown if there are zero or
  more than one claims\.

.. _function-daml-finance-interface-claims-claim-getacquisitiontime-55540:

`getAcquisitionTime <function-daml-finance-interface-claims-claim-getacquisitiontime-55540_>`_
  \: `Claim <type-daml-finance-interface-claims-claim-claim-8835_>`_ \-\> `Time <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-time-63886>`_

  Retrieves the claim's acquisition time\.
