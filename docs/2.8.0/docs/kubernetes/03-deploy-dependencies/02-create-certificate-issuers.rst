.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Create Certificate Issuers
##########################

Objectives
**********

* Configure a `Smallstep <https://smallstep.com/>`_ ``cert-manager`` compatible certificate issuer.
* Deploy Smallstep components to a Kubernetes cluster with Helm.
* Set TLS configuration when deploying Daml Enterprise components with Helm.

For more details on the ``cert-manager`` integration available for Smallstep see `here <https://smallstep.com/docs/step-ca/integrations/#kubernetes>`_.

Prerequisites
*************

* `Docker <https://www.docker.com/products/docker-desktop/>`_
* `Helm installed <https://helm.sh/docs/intro/install/>`_
* `jq <https://github.com/jqlang/jq>`_

Configure Smallstep
*******************

The scripts for Smallstep setup are pre-generated during Terraform deployment.
All the below commands assume the current directory is the ``azure/terraform`` folder of your clone of the `accompanying resources <https://github.com/DACH-NY/daml-enterprise-deployment-blueprints/>`.

.. code-block:: bash

   cd azure/terraform/

.. note::
   The following sections contain slightly different terminal commands for Linux and Mac —
   ensure you pick the one for your OS. To illustrate the contents of these generated files, we will have them printed out with ``cat`` before
   showing you an example output below.

Generate ``step-certificates`` configuration
============================================

  *Linux command*

.. code-block:: bash

     ./outputs/smallstep/linux_create_config.sh

  The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/linux_create_config.sh
     docker run --rm \
       --user ${UID} \
       -v "/home/ubuntu/dev/daml-enterprise-k8s-deployment-guide/02-provision-cloud-resources/iac/outputs/smallstep/passwords":/home/step/passwords \
       -v "/home/ubuntu/dev/daml-enterprise-k8s-deployment-guide/02-provision-cloud-resources/iac/outputs/smallstep/config":/home/step/config \
       -v "/home/ubuntu/dev/daml-enterprise-k8s-deployment-guide/02-provision-cloud-resources/iac/outputs/smallstep/certs":/home/step/certs \
       -v "/home/ubuntu/dev/daml-enterprise-k8s-deployment-guide/02-provision-cloud-resources/iac/outputs/smallstep/secrets":/home/step/secrets \
       cr.step.sm/smallstep/step-ca-bootstrap:latest \
       step ca init \
       --name "smallstep-canton" \
       --dns "smallstep-canton-step-certificates.smallstep.svc.cluster.local" \
       --address ":9000" \
       --provisioner "canton-tls" \
       --with-ca-url "https://smallstep-canton-step-certificates.smallstep.svc.cluster.local" \
       --password-file "/home/step/passwords/ca.txt" \
       --provisioner-password-file "/home/step/passwords/provisioner.txt"

     $ ./outputs/smallstep/linux_create_config.sh

     Generating root certificate... done!
     Generating intermediate certificate... done!

     ✔ Root certificate: /home/step/certs/root_ca.crt
     ✔ Root private key: /home/step/secrets/root_ca_key
     ✔ Root fingerprint: 4f182ac049c29774b3ae95e6bb1976092f15ad1335ebccfe8f3d637dcc8e596b
     ✔ Intermediate certificate: /home/step/certs/intermediate_ca.crt
     ✔ Intermediate private key: /home/step/secrets/intermediate_ca_key
     ✔ Database folder: /home/step/db
     ✔ Default configuration: /home/step/config/defaults.json
     ✔ Certificate Authority configuration: /home/step/config/ca.json

     Your PKI is ready to go. To generate certificates for individual services see 'step help ca'.

     FEEDBACK 😍 🍻
       The step utility is not instrumented for usage statistics. It does not phone
       home. But your feedback is extremely valuable. Any information you can provide
       regarding how you’re using `step` helps. Please send us a sentence or two,
       good or bad at feedback@smallstep.com or join GitHub Discussions
       https://github.com/smallstep/certificates/discussions and our Discord 
       https://u.step.sm/discord.

  *Mac command*

.. code-block:: bash

     ./outputs/smallstep/macos_create_config.sh

  The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/macos_create_config.sh
     docker run --rm \
       -v "./passwords":/home/step/passwords \
       -v "./config":/home/step/config \
       -v "./certs":/home/step/certs \
       -v "./secrets":/home/step/secrets \
       cr.step.sm/smallstep/step-ca-bootstrap:latest \
       step ca init \
       --name "smallstep-canton" \
       --dns "smallstep-canton-step-certificates.smallstep.svc.cluster.local" \
       --address ":9000" \
       --provisioner "canton-tls" \
       --with-ca-url "https://smallstep-canton-step-certificates.smallstep.svc.cluster.local" \
       --password-file "/home/step/passwords/ca.txt" \
       --provisioner-password-file "/home/step/passwords/provisioner.txt"

     $ ./outputs/smallstep/macos_create_config.sh

     Generating root certificate... done!
     Generating intermediate certificate... done!

     ✔ Root certificate: /home/step/certs/root_ca.crt
     ✔ Root private key: /home/step/secrets/root_ca_key
     ✔ Root fingerprint: 4f182ac049c29774b3ae95e6bb1976092f15ad1335ebccfe8f3d637dcc8e596b
     ✔ Intermediate certificate: /home/step/certs/intermediate_ca.crt
     ✔ Intermediate private key: /home/step/secrets/intermediate_ca_key
     ✔ Database folder: /home/step/db
     ✔ Default configuration: /home/step/config/defaults.json
     ✔ Certificate Authority configuration: /home/step/config/ca.json

     Your PKI is ready to go. To generate certificates for individual services see 'step help ca'.

     FEEDBACK 😍 🍻
       The step utility is not instrumented for usage statistics. It does not phone
       home. But your feedback is extremely valuable. Any information you can provide
       regarding how you’re using `step` helps. Please send us a sentence or two,
       good or bad at feedback@smallstep.com or join GitHub Discussions
       https://github.com/smallstep/certificates/discussions and our Discord 
       https://u.step.sm/discord.

Increase maximal generated certificate duration
===============================================

 As certificates may only be rotated by a full restart for Daml Enterprise, we set maximal generated certificate duration to 10 years:

  *Linux command*

.. code-block:: bash

     ./outputs/smallstep/linux_certificate_duration.sh

  The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/linux_certificate_duration.sh
     docker run --rm \
       --user ${UID} \
       -v "/home/ubuntu/dev/daml-enterprise-k8s-deployment-guide/02-provision-cloud-resources/iac/outputs/smallstep/config":/home/step/config \
       cr.step.sm/smallstep/step-ca-bootstrap:latest \
       step ca provisioner \
         update canton-tls \
         --x509-max-dur=88000h

     $ ./outputs/smallstep/linux_certificate_duration.sh
     ✔ CA Configuration: /home/step/config/ca.json

     Success! Your `step-ca` config has been updated. To pick up the new configuration SIGHUP (kill -1 <pid>) or restart the step-ca process.

  *Mac command*

.. code-block:: bash

     ./outputs/smallstep/macos_certificate_duration.sh

  The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/macos_certificate_duration.sh
     docker run --rm \
       -v "./config":/home/step/config \
       cr.step.sm/smallstep/step-ca-bootstrap:latest \
       step ca provisioner \
         update canton-tls \
         --x509-max-dur=88000h

     $ ./outputs/smallstep/macos_certificate_duration.sh
     ✔ CA Configuration: /home/step/config/ca.json

     Success! Your `step-ca` config has been updated. To pick up the new configuration SIGHUP (kill -1 <pid>) or restart the step-ca process.

Configure Kubernetes cluster
============================

Add the configurations and secrets to the Kubernetes cluster with the following command:

.. code-block:: bash

   ./outputs/smallstep/create_secrets.sh

The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/create_secrets.sh
     kubectl create namespace "smallstep"

     kubectl -n "smallstep" \
       create configmap "smallstep-canton-step-certificates-config" \
       --from-file "./outputs/smallstep/config"

     kubectl -n "smallstep" \
       create configmap "smallstep-canton-step-certificates-certs" \
       --from-file "./outputs/smallstep/certs"

     kubectl -n "smallstep" \
       create secret generic "smallstep-canton-step-certificates-secrets" \
       --from-file "./outputs/smallstep/secrets/intermediate_ca_key"

     kubectl -n "smallstep" \
       create secret generic "smallstep-canton-step-certificates-ca-password" \
       --from-file "password=./outputs/smallstep/passwords/ca.txt"

     kubectl -n "smallstep" \
       create secret generic "smallstep-canton-step-certificates-provisioner-password"\
       --from-file "password=./outputs/smallstep/passwords/provisioner.txt"

     $ ./outputs/smallstep/create_secrets.sh
     namespace/smallstep created
     configmap/smallstep-canton-step-certificates-config created
     configmap/smallstep-canton-step-certificates-certs created
     secret/smallstep-canton-step-certificates-secrets created
     secret/smallstep-canton-step-certificates-ca-password created
     secret/smallstep-canton-step-certificates-provisioner-password created

Deploy Smallstep ``cert-manager`` Issuer
****************************************

Set up Helm repository for Smallstep
====================================

To be able to pull the official Smallstep Helm charts, add the smallstep repository:

.. code-block:: bash

     helm repo add smallstep https://smallstep.github.io/helm-charts

After running the above command you should see:

.. code-block:: bash

     "smallstep" has been added to your repositories

Deploy ``step-certificates`` with Helm
======================================

The chart is configured using ``outputs/smallstep/step_certificates_values.yaml``\ :

.. code-block:: bash

     $ cat ./outputs/smallstep/step_certificates_values.yaml
     existingSecrets:
       enabled: true
       ca: true

     bootstrap:
       secrets: false
       enabled: false
       configmaps: false

     inject:
       enabled: false

To install ``step-certificates``\ , execute the below command:

.. code-block:: bash

     ./outputs/smallstep/helm_install_step_certificate.sh

The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/helm_install_step_certificate.sh
     helm -n smallstep install \
       smallstep-canton smallstep/step-certificates \
       --version 1.23.2+5 \
       -f step_certificates_values.yaml \
       --wait-for-jobs --wait

     $ ./outputs/smallstep/helm_install_step_certificate.sh
     NAME: smallstep-canton
     LAST DEPLOYED: Mon Jul 31 08:49:16 2023
     NAMESPACE: smallstep
     STATUS: deployed
     REVISION: 1
     NOTES:
     Thanks for installing Step CA.

     1. Get the PKI and Provisioner secrets running these commands:
       kubectl get -n smallstep -o jsonpath='{.data.password}' secret/smallstep-canton-step-certificates-ca-password | base64 --decode
       kubectl get -n smallstep -o jsonpath='{.data.password}' secret/smallstep-canton-step-certificates-provisioner-password | base64 --decode

Deploy ``step-issuer`` with Helm
================================

To install ``step-issuer``\ , execute the below command:

.. code-block:: bash

     ./outputs/smallstep/helm_install_step_issuer.sh

The default configuration is used:

.. code-block:: bash

     $ cat ./outputs/smallstep/helm_install_step_issuer.sh
     helm -n smallstep install \
       smallstep-canton-issuer smallstep/step-issuer \
       --version 0.7.0 \
       --wait-for-jobs --wait

     $ ./outputs/smallstep/helm_install_step_issuer.sh
     NAME: smallstep-canton-issuer
     LAST DEPLOYED: Mon Jul 31 08:52:06 2023
     NAMESPACE: smallstep
     STATUS: deployed
     REVISION: 1
     TEST SUITE: None
     NOTES:
     ⚙️  Thanks for installing step-issuer.

     step-issuer is ideal for issuing certificates
     from your own private Certificate Authority (CA).

     To start issuing certificates, you will need:

     👉 A cert-manager installation
     👉 A step-ca Certificate Authority (CA) or a Smallstep Certificate Manager authority
     👉 A StepIssuer resource that links step-issuer to your CA

     To continue, follow the instructions here:

     https://u.step.sm/step-issuer

Create Certificate Issuers
**************************

Create the Kubernetes resource description
==========================================

.. code-block:: bash

     ./outputs/smallstep/create_step_cluster_issuer_config.sh

  The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/create_step_cluster_issuer_config.sh
     cat > canton-tls-issuer.yaml <<EOF
     apiVersion: certmanager.step.sm/v1beta1
     kind: StepClusterIssuer
     metadata:
       name: canton-tls-issuer
       namespace: smallstep
     spec:
       # The CA URL:
       url: https://smallstep-canton-step-certificates.smallstep.svc.cluster.local
       # The base64 encoded version of the CA root certificate in PEM format:
       caBundle: $(base64 -i "./certs/root_ca.crt" | tr -d '\n')
       # The provisioner name, kid, and a reference to the provisioner password secret:
       provisioner:
         name: canton-tls
         kid: $(jq ".authority.provisioners[0].key.kid" "./config/ca.json")
         passwordRef:
           namespace: smallstep
           name: smallstep-canton-step-certificates-provisioner-password
           key: password
     EOF

     $ ./outputs/smallstep/create_step_cluster_issuer_config.sh

Deploy the certificate issuer
=============================

.. code-block:: bash

     ./outputs/smallstep/create_step_cluster_issuer.sh

  The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/create_step_cluster_issuer.sh
     kubectl apply -f ./canton-tls-issuer.yaml

     $ ./outputs/smallstep/create_step_cluster_issuer.sh
     stepclusterissuer.certmanager.step.sm/canton-tls-issuer configured

Check that the certificate issuer is ready
==========================================

.. code-block:: bash

     ./outputs/smallstep/check_step_cluster_issuer.sh

  The output should be similar to the following:

.. code-block:: bash

     $ cat ./outputs/smallstep/check_step_cluster_issuer.sh
     kubectl get -n smallstep StepClusterIssuer canton-tls-issuer -o yaml

     $ ./outputs/smallstep/check_step_cluster_issuer.sh
     apiVersion: certmanager.step.sm/v1beta1
     kind: StepClusterIssuer
     [...] 
     status:
       conditions:
       - lastTransitionTime: "2023-07-31T08:57:17Z"
         message: StepClusterIssuer verified and ready to sign certificates
         reason: Verified
         status: "True"
         type: Ready

For troubleshooting problems with certificate issuance, see `cert-manager's documentation <https://cert-manager.io/docs/troubleshooting/>`_.

Securing Smallstep Certificate Issuer
*************************************

Smallstep provides a more complete documentation about `production configuration <https://smallstep.com/docs/step-ca/certificate-authority-server-production/>`_.

For this deployment, the important points are:

* securing the root CA private key
* securing the passwords
