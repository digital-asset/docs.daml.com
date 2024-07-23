..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _downloading:

Obtaining Canton
================

Choosing Open-Source or Enterprise Edition
------------------------------------------
The Canton distributed ledger is included with Daml Enterprise edition, or available as open source. Which role the application takes
depends on the configuration. The main administration interface of the Canton application is the embedded console, which
is part of the application.

Canton releases come in two variants: Open-Source or Enterprise. Both support the full Canton protocol, but differ in
terms of enterprise and non-functional capabilities:

.. list-table:: Differences between Enterprise and Open Source Edition
    :widths: 50,25,25
    :header-rows: 1

    * - Capability
      - Enterprise
      - Open-Source
    * - Daml Synchronisation
      - Yes
      - Yes
    * - Sub-Transaction Privacy
      - Yes
      - Yes
    * - Transaction Processing
      - Parallel (fast)
      - Sequential (slow)
    * - High Availability
      - :ref:`Yes <ha_user_manual>`
      - No
    * - `Participant Query Store <https://docs.daml.com/query/pqs-user-guide.html>`__
      - Yes
      - No
    * - High Throughput via Microservices
      - :ref:`Yes <ha_user_manual>`
      - No
    * - Resource Management
      - Yes
      - No
    * - Ledger Pruning
      - Yes
      - No
    * - `AWS KMS, GCP KMS <https://docs.daml.com/canton/usermanual/kms/kms.html>`__ 
      - Yes
      - No
    * - Postgres Backend
      - Yes
      - Yes

Please follow below instructions in order to obtain your copy of Canton.

Downloading the Open Source Edition
-----------------------------------

The Open Source release is available from `Github <https://github.com/digital-asset/daml/releases/latest>`__.


Downloading the Enterprise Edition
----------------------------------
Enterprise releases are available on request (sales@digitalasset.com) and can be downloaded from the
respective `repository <https://digitalasset.jfrog.io/artifactory/canton-enterprise/>`__, or you can use
our Canton Enterprise Docker images as described in our :ref:`Docker instructions <docker-instructions>`.
