.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

High Availability Deployment and Scaling
########################################

This section details a complete Daml solution deployed in a High Availability (HA) configuration. We also look at the horizontal scaling characteristics of the same solution. 

.. note::
    **Definition**: HA is the elimination of single points of failure ensuring applications continue to operate when a component they depend on, such as a server, fails. 

The information in this section assists engineers with the following:

* Production deployment planning.
* Understanding HA architectures.
* Understanding Daml application scalability.
* Building Kubernetes deployments.
* HA/scalability deployments in the cloud or on-premises.

The solution described herein is a Daml v2.x Enterprise distributed application that includes Canton services, HTTP JSON API server, Trigger services, and OAuth 2.0 middleware components. The example is a SQL domain that uses PostgreSQL as the synchronization mechanism for the sequencers' backend. 


