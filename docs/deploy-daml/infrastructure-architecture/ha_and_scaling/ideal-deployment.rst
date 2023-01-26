.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Ideal Deployment
################

The figure below puts all of the pieces together as described above with the single-endpoint load balancer option. Although this setup may look complex, each service is independent and deployed separately. 

The figure below uses client-side load balancing for the domain owner’s sequencer access. Separate sequencer nodes are shown for the distributed application user’s connectivity.


The figures that have been shown in this section have maximized the independence between components by showing them as running on independent hosts but, for actual deployment some simplification and cost reduction is possible.  For example, combining components to run on the same host is a decision that reduces complexity and cost. But this can impact the availability where one component can impact another component (e.g., one component uses 100% of the CPU which starves the other components).  Of course, different instances of a service should be run on different hosts to avoid a single point of failure at the infrastructure level.  Again, the business goals should drive the HA requirements and how things are deployed.
