.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

From:
https://docs.google.com/document/d/1FILaPsWD11yeYTK5v3yDPas58rLKRLzW_KL6np1Q8gM/edit#heading=h.poaj4a35nfzn

HA and Scaling
##############

Introduction

This document describes a complete Daml solution deployed as a High Availability (HA) configuration and its horizontal scaling characteristics. The solution is a Daml v2.x Enterprise distributed that includes Canton services, HTTP JSON API server, Trigger services, and OAuth 2.0 middleware components. This example largely is for a SQL domain that uses PostgreSQL as the synchronization mechanism for the sequencers’ backend. The solution does discuss a blockchain domain. 

!!!CALLOUT: We define HA as the elimination of single points of failure ensuring applications continue to operate when a component they depend on, such as a server, fails. 

This information in this document is useful for the following:

Production deployment planning.
Understanding HA architectures.
Understanding Daml application scalability.
Building Kubernetes deployments.
HA/scalability deployments in the cloud or on-premises.


Overview  

https://docs.daml.com/canton/architecture/ha/overview.html



Target Personas

The primary personas for this document are primarily involved in deployment activities. They are:

A distributed application provider who runs a domain and their own participant service.
Distributed application users who run a participant service.
Infrastructure operators or site reliability engineers (SREs).

!!! CALLOUT: A distributed application build engineer persona acts as a combination of all three of the above because they need to validate that the distributed application works as part of the CI/CD activity. 

