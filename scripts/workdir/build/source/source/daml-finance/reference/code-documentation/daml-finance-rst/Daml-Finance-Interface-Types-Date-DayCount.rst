.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-finance-interface-types-date-daycount-90980:

Module Daml.Finance.Interface.Types.Date.DayCount
=================================================

Data Types
----------

.. _type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281:

**data** `DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281_>`_

  An enum type to specify a day count convention used to calculate day count fractions\.
  For a detailed definition of each convention, we refer to the \"Method of Interest Computation
  Indicator\" definitions in the context of the ISO\-20022 standard\. Where useful, we provide
  disambiguation comments\.

  .. _constr-daml-finance-interface-types-date-daycount-act360-99170:

  `Act360 <constr-daml-finance-interface-types-date-daycount-act360-99170_>`_

    Actual 360\.
    In CDM it is called *DayCountFractionEnum\_ACT\_360*\. In ISO20022 it is called *A004*\.

  .. _constr-daml-finance-interface-types-date-daycount-act365fixed-71648:

  `Act365Fixed <constr-daml-finance-interface-types-date-daycount-act365fixed-71648_>`_

    Actual 365 fixed\.
    In CDM it is called *DayCountFractionEnum\_ACT\_365\_FIXED*\. In ISO20022 it is called *A005*\.

  .. _constr-daml-finance-interface-types-date-daycount-act365l-66362:

  `Act365L <constr-daml-finance-interface-types-date-daycount-act365l-66362_>`_

    Actual 365L\.
    In CDM it is called *DayCountFractionEnum\_ACT\_365L*\. In ISO20022 it is called *A009*\.

  .. _constr-daml-finance-interface-types-date-daycount-actactafb-25369:

  `ActActAFB <constr-daml-finance-interface-types-date-daycount-actactafb-25369_>`_

    Actual Actual AFB\.
    In CDM it is called *DayCountFractionEnum\_ACT\_ACT\_AFB*\. In ISO20022 it is called *A010*\.

  .. _constr-daml-finance-interface-types-date-daycount-actactisda-83034:

  `ActActISDA <constr-daml-finance-interface-types-date-daycount-actactisda-83034_>`_

    Actual Actual ISDA\.
    In CDM it is called *DayCountFractionEnum\_ACT\_ACT\_ISDA*\. In ISO20022 it is called *A008*\.

  .. _constr-daml-finance-interface-types-date-daycount-actacticma-63753:

  `ActActICMA <constr-daml-finance-interface-types-date-daycount-actacticma-63753_>`_

    Actual Actual ICMA\.
    In CDM it is called *DayCountFractionEnum\_ACT\_ACT\_ICMA* and
    *DayCountFractionEnum\_ACT\_ACT\_ISMA* (they are identical\:
    https\://www\.isda\.org/2011/01/07/act\-act\-icma/)\.
    In ISO20022 it is called *A006*\. Also called ISMA in the 1998 ISDA paper\.

  .. _constr-daml-finance-interface-types-date-daycount-basis1-33728:

  `Basis1 <constr-daml-finance-interface-types-date-daycount-basis1-33728_>`_

    1/1\.
    In CDM it is called *DayCountFractionEnum\_\_1\_1*\. Currently not included in ISO20022\.

  .. _constr-daml-finance-interface-types-date-daycount-basis30360-21031:

  `Basis30360 <constr-daml-finance-interface-types-date-daycount-basis30360-21031_>`_

    30/360\.
    In CDM it is called *DayCountFractionEnum\_\_30\_360*\. In ISO20022 it is called *A001*\.
    Also called 30/360 ISDA or American Basic rule\.

  .. _constr-daml-finance-interface-types-date-daycount-basis30360icma-65557:

  `Basis30360ICMA <constr-daml-finance-interface-types-date-daycount-basis30360icma-65557_>`_

    30/360 ICMA\.
    In CDM it is called *DayCountFractionEnum\_\_30E\_360*\. In ISO20022 it is called *A011*\.
    Also called Basic Rule\. This corresponds to \"30E/360\" of the 2006 ISDA definitions\.

  .. _constr-daml-finance-interface-types-date-daycount-basis30e360-89067:

  `Basis30E360 <constr-daml-finance-interface-types-date-daycount-basis30e360-89067_>`_

    30E/360\.
    In CDM it is called *DayCountFractionEnum\_\_30E\_360\_ISDA*\. In ISO20022 it is called *A007*\.
    Also called Eurobond basis\. This corresponds to \"30E360 (ISDA)\" of the 2006 ISDA definitions\.

  .. _constr-daml-finance-interface-types-date-daycount-basis30e3360-95253:

  `Basis30E3360 <constr-daml-finance-interface-types-date-daycount-basis30e3360-95253_>`_

    30E3/360\.
    Currently not included in CDM\. In ISO20022 it is called *A013*\. Also called Eurobond basis
    model 3\.

  **instance** `Eq <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-classes-eq-22713>`_ `DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281_>`_

  **instance** `Show <https://docs.daml.com/daml/stdlib/Prelude.html#class-ghc-show-show-65360>`_ `DayCountConventionEnum <type-daml-finance-interface-types-date-daycount-daycountconventionenum-67281_>`_
