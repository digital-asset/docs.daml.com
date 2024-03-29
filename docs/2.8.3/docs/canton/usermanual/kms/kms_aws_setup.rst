..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _kms_aws_setup:

Configure Amazon Web Services (AWS) KMS
=======================================

Like other Canton capabilities, AWS KMS configuration is enabled within a Canton
node's configuration file. A KMS for AWS is configured as follows:

.. _kms_aws_config:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/encrypted-store-enabled-tagged.conf
   :language: none
   :start-after: user-manual-entry-begin: AwsKmsConfig
   :end-before: user-manual-entry-end: AwsKmsConfig

- ``type`` specifies which KMS to use.
- ``region`` specifies which region the AWS KMS is bound to.
- ``multi-region-key`` flag enables the replication of keys generated by the AWS KMS. With replication turned on, the operator can replicate a key from one region to another (Note: replication of a key is not done automatically by Canton) and change the region configured in Canton at a later point in time without any other key rotation required. **The standard single-region approach is applicable for most scenarios**.
- ``audit-logging`` flag enables logging of every call made to the AWS KMS.

Configure AWS Credentials and Permissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The authorized actions (i.e. IAM permissions) for the AWS KMS depend on the mode of operation you are running, either:
(a) :ref:`an encrypted private key storage using envelope encryption <encrypted_private_key_storage_permissions_aws>`; or
(b) :ref:`externally storing and using keys directly from AWS KMS <external_key_storage_permissions_aws>`.
A complete list is given in those sections.

To make the API calls to the AWS KMS, Canton uses the `standard AWS credential access
<https://docs.aws.amazon.com/general/latest/gr/aws-sec-cred-types.html>`_. For example, the standard
environment variables of `AWS_ACCESS_KEY_ID` and `AWS_SECRET_ACCESS_KEY` can
be used. Alternatively, you can specify an AWS profile file (e.g. use a temporary access
profile credentials - `sts`).

The protection and rotation of
the credentials for AWS are the responsibility of the node operator.

Auditability
^^^^^^^^^^^^

AWS provides tools to monitor KMS keys. For AWS to set automatic external logging, refer to the
`AWS official documentation <https://docs.aws.amazon.com/kms/latest/developerguide/monitoring-overview.html>`_.
This includes instructions on how to set AWS Cloud Trail or Cloud Watch Alarms
to keep track of usage of KMS keys or of performed crypto operations.
Canton logs errors resulting from the use of KMS keys.

Logging
^^^^^^^

For further auditability, Canton can be configured to log every call made to the AWS KMS.
To enable this feature, set the ``audit-logging`` field of the KMS configuration to ``true``.
By default, when using a file-based logging configuration, such logs are written into the main Canton log file.
To write them to a dedicated log file, set the ``KMS_LOG_FILE_NAME`` environment variable or ``--kms-log-file-name`` CLI
flag to the path of the file.
These and other parameters can be configured using environment variables or CLI flags:

.. list-table:: KMS logging configuration
   :widths: 20 20 40 20
   :header-rows: 1

   * - Environment variable
     - CLI Flag
     - Purpose
     - Default
   * - KMS_LOG_FILE_NAME
     - --kms-log-file-name
     - Path to a dedicated KMS log file
     - not set
   * - KMS_LOG_IMMEDIATE_FLUSH
     - --kms-log-immediate-flush
     - When true, logs will be immediately flushed to the KMS log file
     - true
   * - KMS_LOG_FILE_ROLLING_PATTERN
     - --kms-log-file-rolling-pattern
     - Pattern to use when using the rolling file strategy to roll KMS log files
     - yyyy-MM-dd
   * - KMS_LOG_FILE_HISTORY
     - --kms-log-file-history
     - Maximum number of KMS log files to keep when using the rolling file strategy
     - 0 (i.e. no limit)

Sample of an AWS KMS audit log:

.. code-block:: none

    2023-09-12 15:44:54,426 [env-execution-context-27] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Sending request [06cc259e220da647]: DecryptRequest(CiphertextBlob=** Ciphertext placeholder **, KeyId=91c48ce4-ec80-44c1-a219-fdd07f12f002, EncryptionAlgorithm=RSAES_OAEP_SHA_256) to https://kms.us-east-1.amazonaws.com/
    2023-09-12 15:44:54,538 [aws-java-sdk-NettyEventLoop-1-15] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Received response [06cc259e220da647]: [Aws-Id: 1836823c-bb8a-44bf-883d-f33d696bf84f] - DecryptResponse(Plaintext=** Redacted plaintext placeholder **, KeyId=arn:aws:kms:us-east-1:724647588434:key/91c48ce4-ec80-44c1-a219-fdd07f12f002, EncryptionAlgorithm=RSAES_OAEP_SHA_256)
    2023-09-12 15:44:54,441 [env-execution-context-138] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Sending request [e28450df3a98ea23]: SignRequest(KeyId=f23b5b37-b4e8-494d-b2bc-1fca12308c99, Message=** Sign message text placeholder **, MessageType=RAW, SigningAlgorithm=ECDSA_SHA_256) to https://kms.us-east-1.amazonaws.com/
    2023-09-12 15:44:54,554 [aws-java-sdk-NettyEventLoop-1-2] INFO  c.d.c.c.k.a.a.AwsRequestResponseLogger:participant=participant1 tid:40d47592f1bd50f37e6804fbdff404dd - Received response [e28450df3a98ea23]: [Aws-Id: 7085bcf3-1a36-4048-a38b-014b441afa11] - SignResponse(KeyId=arn:aws:kms:us-east-1:724647588434:key/f23b5b37-b4e8-494d-b2bc-1fca12308c99, Signature=** Signature message text placeholder **, SigningAlgorithm=ECDSA_SHA_256)

Note that sensitive data is removed before logging.
The general log format is as follows:

``tid:<canton_trace_id> - Sending request [<canton_kms_request_id>]: <request details>``
``tid:<canton_trace_id> - Received response [<canton_kms_request_id>]: [Aws-Id: <aws_request_id>] - <response details>``