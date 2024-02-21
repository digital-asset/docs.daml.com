.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _ha_arch:

HA and Horizontal Scaling
#########################

Introduction
************

This section describes how to deploy a complete Daml solution in an HA configuration with horizontal scaling characteristics. 

The distributed solution uses Daml v2.x Enterprise with Canton services, HTTP JSON API server, Trigger services, and OAuth 2.0 middleware components. In this document we primarily discuss a SQL synchronizer that uses PostgreSQL as the synchronization mechanism for the sequencer backend. We also describe a blockchain syncrhonizer. 

Information in this section is useful for the following:

* Production deployment planning.
* Understanding HA architectures.
* Understanding Daml application scalability.
* Building Kubernetes deployments.
* HA/scalability deployments in the cloud or on-premises.

Target audience
===============

1. A distributed application provider who runs a synchronizer and their own participant service.
2. Distributed application users who run a participant service.
3. Infrastructure operators or site reliability engineers (SREs).

.. IMPORTANT::
    A distributed application build engineer persona acts as a combination of all three target audiences as they need to validate that the distributed application works as part of the CI/CD activity. 