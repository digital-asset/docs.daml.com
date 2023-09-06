.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Configure Container Image Puller (Optional)
###########################################

Objectives
**********

* Deploy & set up `Kubernetes Image Puller utility <https://github.com/che-incubator/kubernetes-image-puller>`_.

Introduction
************

This is a simple implementation of `Kubernetes Image Puller <https://github.com/che-incubator/kubernetes-image-puller>`_. The aim of this is to pre-cache the images across all nodes of a Kubernetes cluster, making failover and pod recreation faster. This is an optional step: if a pod is placed on a node which does not have its image yet, it will pull it from the designated repository as per standard behaviour.

Installation guide
******************

#. Pull the image puller Helm chart

   .. code-block:: bash

      git clone git@github.com:che-incubator/kubernetes-image-puller.git

   The Helm chart is located in the deploy/helm directory.

#. Parameterize the value file of the Kubernetes image puller Helm chart

   This is an example of a value file for the Kubernetes image puller Helm chart (see the `official documentation <https://github.com/che-incubator/kubernetes-image-puller#configuration---helm>`_ for all options):

   .. code-block:: yaml

      deploymentName: kubernetes-image-puller
      image: 
       repository: quay.io/eclipse/kubernetes-image-puller
       tag: next
      serviceAccount:
       name: kubernetes-image-puller
      configMap:
       name: kubernetes-image-puller
       images: >-
         <image>=<repository>/<image>:<tag>;
         <image>=<repository>/<image>:<tag>;
       cachingIntervalHours: 1
       cachingMemoryRequest: "10Mi"
       cachingMemoryLimit: "20Mi"
       cachingCpuRequest: ".05"
       cachingCpuLimit: ".2"
       nodeSelector: "{}"
       affinity: "{}"

   By default the image puller will pull its default image from quay.io. We can change this by setting the following to different values:

   .. code-block:: yaml

      image: 
       repository: quay.io/eclipse/kubernetes-image-puller
       tag: next

   Configure which images to be cached by the image puller. The images are configured in the configMap.images list. The format of the list is as follows:

   .. code-block:: yaml

      configMap:
       images: >
         <image>=<repository>/<image>:<tag>;

   Fill this list in the values file with the images you want to be cached by the image puller. This depends on what version of Daml Enterprise you would like to deploy to the Kubernetes cluster. For example, if you want to deploy Daml Enterprise 2.6.4, you should add the following images to the list:

   .. code-block:: yaml

      configMap:
       images: >
         canton-enterprise=<acr_hostname>/digitalasset/canton-enterprise:2.7.0;
         canton-enterprise-debug=<acr_hostname>/digitalasset/canton-enterprise:2.7.0-debug;
         http-json=<acr_hostname>/http-json:2.7.0;

#. Install the Helm chart by running the following command from the root directory of the repository:

   .. code-block:: bash

      helm -n kubernetes-image-puller install kubernetes-image-puller --create-namespace deploy/helm
