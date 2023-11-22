.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

How to achieve high availability for Daml Enterprise on Kubernetes
##################################################################

Target deployment
*****************

As a reminder, this guide targets the following Daml Enterprise deployment:

.. image:: ../images/k8s-deployment.png
   :alt: Target Deployment

For details, see :doc:`Deploy on Kubernetes <../01-introduction/overview>`.

Components
**********

Canton participant
==================

The Canton participant component is normally deployed in an active-passive cluster to achieve high availability. However, in a Kubernetes environment, this is not necessary. Kubernetes ensures that the requested number of ready Pods are running. You don't need to have a standby (non-ready) replica.

Here is the approach followed:

-  The active Pod is selected based on the health check. The application doesn't report ready until it can access the DB lock.
-  You deploy a single replica of the Pod. Note the following points:

   -  If you increase the replica count to more than one, there is only
      one Pod available and serving traffic at any time because
      the DB lock may be held by a single Pod.
   -  If the application crashes, Kubernetes restarts the Pod. Upon
      restart, the application likely loses the DB lock. This
      results in no traffic directed to this Pod.
   -  To ensure fast Pod restarts, make sure all the Kubernetes nodes
      and workers have already pulled the relevant container images. This is
      achieved through the `Kubernetes Image
      Puller <https://github.com/che-incubator/kubernetes-image-puller>`_.

Note that this approach may result in slight downtime while the Pod
is being restarted.

Canton domain: Topology Manager, Mediator
=========================================

You normally achieve high availability through active-passive clustering for the Topology Manager and Mediator components. See the previous section for details on why this is not necessary in a Kubernetes environment. The same principles apply to these components.

Canton Domain: Sequencer
========================

You achieve high availability through active-active clustering for the Sequencer components. Note the following:

-  Deploy two replicas by default.
-  Set `stickiness <https://kubernetes.io/docs/concepts/services-networking/service/#session-stickiness>`_ based on the client IP (through `sessionAffinity <https://kubernetes.io/docs/reference/networking/virtual-ips/#session-affinity>`_; it expires in one hour).

HTTP JSON API server
====================

You achieve high availability through active-active clustering for the HTTP JSON API server component. Note the following:

-  Deploy two replicas by default.
-  There is no `session stickiness <https://kubernetes.io/docs/concepts/services-networking/service/#session-stickiness>`_.
-  It uses ``/livez`` and ``/readyz`` probes (see the `HTTP JSON API Service documentation <https://docs.daml.com/json-api/index.html#healthcheck-endpoints>`_).

References
**********

Here are selected Kubernetes resource types and concepts that are relevant to
achieve high availability:

-  `Service method <https://kubernetes.io/docs/concepts/services-networking/service/>`_

   -  Sends workload only to Pods that are ready.

-  `Deployment <https://kubernetes.io/docs/concepts/workloads/controllers/deployment/>`_
   >
   `ReplicaSet <https://kubernetes.io/docs/concepts/workloads/controllers/replicaset/>`_
   > `Pods <https://kubernetes.io/docs/concepts/workloads/pods/>`_

   -  Tells the Scheduler to try to reach the number of ready Pods you request.

-  `DaemonSet <https://kubernetes.io/docs/concepts/workloads/controllers/daemonset/>`_

   -  Ensures that a copy of a certain Pod runs on all nodes.

-  `Health
   probes <https://kubernetes.io/docs/tasks/configure-pod-container/configure-liveness-readiness-startup-probes/#configure-probes>`_

   -  Allows Kubernetes to determine which Pods may serve traffic or need to be restarted.
