// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.security.kms

import com.digitalasset.canton.console.{
  DomainManagerNodeReference,
  LocalInstanceReferenceCommon,
  LocalMediatorReferenceCommon,
  LocalParticipantReferenceCommon,
  LocalSequencerNodeReferenceCommon,
  ParticipantReference,
}
import com.digitalasset.canton.crypto.KeyPurpose
import com.digitalasset.canton.crypto.admin.grpc.PrivateKeyMetadata
import com.digitalasset.canton.integration.tests.security.kms.aws.AwsKmsCryptoIntegrationTestBase
import com.digitalasset.canton.integration.tests.security.kms.gcp.GcpKmsCryptoIntegrationTestBase
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}

trait RotateKmsKeyIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with KmsCryptoIntegrationTestBase {

  protected val newKmsKeyIdsMap: Map[String, String]

  "be able to rotate private keys with other existing pre-generated KMS keys" in { implicit env =>
    import env.*

    def getSigningKeyForNode(node: LocalInstanceReferenceCommon): PrivateKeyMetadata = {
      // This is used to filter the signing keys, excluding namespace and encryption keys.
      val filterSigningKeys =
        if (
          node.instanceType == ParticipantReference.InstanceType ||
          node.instanceType == DomainManagerNodeReference.InstanceType
        )
          (key: PrivateKeyMetadata) =>
            key.purpose == KeyPurpose.Signing && key.publicKey.fingerprint != node.id.uid.namespace.fingerprint
        else (key: PrivateKeyMetadata) => key.purpose == KeyPurpose.Signing

      node.keys.secret
        .list()
        .find(key => filterSigningKeys(key))
        .valueOrFail("Could not find signing keys")
    }

    val signingKeyParticipant1 = getSigningKeyForNode(participant1).publicKey
    val keyFingerprint = signingKeyParticipant1.fingerprint.unwrap
    val newKmsKeyId = newKmsKeyIdsMap(participant1.name)

    // user-manual-entry-begin: RotateKmsNodeKey
    val newSigningKeyParticipant = participant1.keys.secret
      .rotate_kms_node_key(
        keyFingerprint,
        newKmsKeyId,
        "kms_key_rotated",
      )
    // user-manual-entry-end: RotateKmsNodeKey

    protectedNodes.foreach { nodeName =>
      val node = env.n(nodeName)
      val signingKey =
        if (nodeName == "participant1") signingKeyParticipant1
        else getSigningKeyForNode(node).publicKey

      // If the node is a mediator or sequencer, we must use the modified functions
      // that include the domain manager reference to ensure proper key rotation.
      val newSigningKey = node match {
        case mediator: LocalMediatorReferenceCommon =>
          mediator.keys.secret.rotate_kms_node_key(
            signingKey.fingerprint.unwrap,
            newKmsKeyIdsMap(mediator.name),
            domainManager1,
            "kms_key_rotated",
          )
        case sequencer: LocalSequencerNodeReferenceCommon =>
          sequencer.keys.secret.rotate_kms_node_key(
            signingKey.fingerprint.unwrap,
            newKmsKeyIdsMap(sequencer.name),
            domainManager1,
            "kms_key_rotated",
          )
        // The rotation for participant1 has already been done above in the `RotateKmsNodeKey` code snippet.
        case participant: LocalParticipantReferenceCommon
            if participant.name.contains("participant1") =>
          newSigningKeyParticipant
        case node =>
          node.keys.secret.rotate_kms_node_key(
            signingKey.fingerprint.unwrap,
            newKmsKeyIdsMap(node.name),
            "kms_key_rotated",
          )
      }

      node.topology.synchronisation.await_idle()

      val storedKey = node.keys.secret
        .list(filterFingerprint = newSigningKey.fingerprint.unwrap)
        .lastOption
        .valueOrFail("Could not find key")

      signingKey should not be newSigningKey
      newSigningKey shouldBe storedKey.publicKey
      storedKey.name shouldBe Some("kms_key_rotated")
    }

    assertPingSucceeds(participant1, participant2)
  }

  setupPlugins(withAutoInit = false, None)
}

class RotateAwsKmsKeyIntegrationTest
    extends RotateKmsKeyIntegrationTest
    with AwsKmsCryptoIntegrationTestBase {
  override protected val newKmsKeyIdsMap: Map[String, String] =
    Map(
      "participant1" -> "alias/canton-kms-test-authentication-key-participant1",
      "participant2" -> "alias/canton-kms-test-authentication-key-participant2",
      "domainManager1" -> "alias/canton-kms-test-authentication-key-domainManager",
      "mediator1" -> "alias/canton-kms-test-authentication-key-mediator",
      "sequencer1" -> "alias/canton-kms-test-authentication-key-sequencer",
    )

  override protected lazy val additionalProtectedNodes: Set[String] =
    Set("domainManager1", "mediator1", "sequencer1", "participant2")
}

class RotateGcpKmsKeyIntegrationTest
    extends RotateKmsKeyIntegrationTest
    with GcpKmsCryptoIntegrationTestBase {
  override protected val newKmsKeyIdsMap: Map[String, String] =
    Map(
      "participant1" -> "canton-kms-test-authentication-key-participant1",
      "participant2" -> "canton-kms-test-authentication-key-participant2",
      "domainManager1" -> "canton-kms-test-authentication-key-domainManager",
      "mediator1" -> "canton-kms-test-authentication-key-mediator",
      "sequencer1" -> "canton-kms-test-authentication-key-sequencer",
    )

  override protected lazy val additionalProtectedNodes: Set[String] =
    Set("domainManager1", "mediator1", "sequencer1", "participant2")
}
