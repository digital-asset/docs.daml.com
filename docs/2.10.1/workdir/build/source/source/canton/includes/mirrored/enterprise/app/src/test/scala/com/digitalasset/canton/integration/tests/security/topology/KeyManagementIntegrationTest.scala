// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.security.topology

import cats.syntax.option.*
import com.daml.test.evidence.scalatest.AccessTestScenario
import com.daml.test.evidence.scalatest.ScalaTestSupport.Implicits.*
import com.daml.test.evidence.tag.Security.SecurityTest.Property.*
import com.daml.test.evidence.tag.Security.{Attack, SecurityTest, SecurityTestSuite}
import com.digitalasset.canton.console.{InstanceReference, LocalInstanceReference}
import com.digitalasset.canton.crypto.*
import com.digitalasset.canton.integration.plugins.UsePostgres
import com.digitalasset.canton.integration.tests.{
  EnterpriseHasCycleUtils,
  EnterpriseIntegrationTest,
  EnterpriseTestConsoleEnvironment,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.integration.{ConfigTransforms, *}
import com.digitalasset.canton.topology.*
import com.digitalasset.canton.topology.store.TopologyStoreId.AuthorizedStore
import com.digitalasset.canton.topology.transaction.TopologyChangeOp
import org.scalatest.Assertion

trait KeyManagementIntegrationTestHelper
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment {

  protected def rotateNodeKeysTest(asset: String): SecurityTest = SecurityTest(
    property = Authenticity,
    asset = asset,
    Attack(
      actor = "a network participant",
      threat = s"impersonates a $asset with compromised signing keys",
      mitigation = "rotate the keys",
    ),
  )

  protected def rotateNamespaceKeysTest(asset: String): SecurityTest = SecurityTest(
    property = Authenticity,
    asset = s"$asset namespace",
    Attack(
      actor = "a network participant",
      threat =
        s"impersonates any entity under the namespace by authorizing topology transactions with the compromised namespace signing keys",
      mitigation = "rotate a namespace intermediate keys",
    ),
  )

  protected def setupNamespaceIntermediateKey(
      identityManager: InstanceReference,
      rootKey: PublicKey,
  ): PublicKey = {

    val namespaceDelegations =
      identityManager.topology.namespace_delegations.list(
        filterStore = AuthorizedStore.filterName,
        filterNamespace = identityManager.id.uid.namespace.toProtoPrimitive,
      )

    // architecture-handbook-entry-begin: CreateNamespaceIntermediateKey

    // create a new namespace intermediate key
    val intermediateKey = identityManager.keys.secret.generate_signing_key()

    // Create a namespace delegation for the intermediate key with the namespace root key
    identityManager.topology.namespace_delegations.authorize(
      TopologyChangeOp.Add,
      rootKey.fingerprint,
      intermediateKey.fingerprint,
    )

    // architecture-handbook-entry-end: CreateNamespaceIntermediateKey

    // Check that the new namespace delegations appears
    eventually() {
      val updatedNamespaceDelegations = identityManager.topology.namespace_delegations.list(
        filterStore = AuthorizedStore.filterName,
        filterNamespace = identityManager.id.uid.namespace.toProtoPrimitive,
      )
      assertResult(1, updatedNamespaceDelegations)(
        updatedNamespaceDelegations.length - namespaceDelegations.length
      )
    }

    intermediateKey
  }

  protected def setupIdentifierDelegation(
      node: InstanceReference,
      identityManager: InstanceReference,
  ): PublicKey = {
    // Create a new signing key and assign it as an identifier delegation for the uid
    val identifierKey = node.keys.secret.generate_signing_key()

    if (node != identityManager)
      // TODO(i10563) Change the serialization of crypto keys in console commands
      identityManager.keys.public.upload(identifierKey.toByteString(testedProtocolVersion), None)

    identityManager.topology.identifier_delegations.authorize(
      TopologyChangeOp.Add,
      node.id.uid,
      identifierKey.fingerprint,
    )

    identifierKey
  }

  protected def rotateIntermediateNamespaceKeyAndPing(
      identityManager: InstanceReference,
      node: InstanceReference,
      kmsRotationKeyIdO: Option[String],
      setupIntermediateKey: (InstanceReference, PublicKey) => PublicKey =
        setupNamespaceIntermediateKey,
  )(implicit env: EnterpriseTestConsoleEnvironment): Assertion = {
    import env.*

    assertPingSucceeds(participant2, participant1)

    // Create a namespace intermediate key for the participant namespace
    val rootKey =
      identityManager.keys.secret
        .list(filterName = s"${identityManager.name}-namespace")
        .headOption
        .getOrElse(fail("Cannot get namespace signing"))
        .publicKey

    val intermediateKey = setupIntermediateKey(identityManager, rootKey)

    // To test the namespace key rotation, we assign a new node key to a node authorized with the new intermediate key
    // and remove the previous node key that was authorized by the previous intermediate key.

    // Find the current signing key
    val currentSigningKey = identityManager.topology.owner_to_key_mappings
      .list(
        filterStore = AuthorizedStore.filterName,
        filterKeyOwnerUid = node.id.filterString,
      )
      .find(x => x.item.owner == node.id && x.item.key.purpose == KeyPurpose.Signing)
      .map(_.item.key)
      .getOrElse(sys.error(s"No signing key found for $node"))

    val newSigningKey = kmsRotationKeyIdO match {
      case Some(kmsKeyId) =>
        node.keys.secret.register_kms_signing_key(kmsKeyId, s"$node-signing-new")
      case None => node.keys.secret.generate_signing_key(s"$node-signing-new")
    }

    if (identityManager != node)
      identityManager.keys.public
        .upload(newSigningKey.toByteString(testedProtocolVersion), Some(s"$node-signing-new"))

    val owner = node.id match {
      case domainId: DomainId => DomainTopologyManagerId(domainId)
      case owner: KeyOwner => owner
      case unknown =>
        fail(s"Unknown key owner: $unknown")
    }

    // Authorize the new key with the intermediate namespace key
    identityManager.topology.owner_to_key_mappings.authorize(
      TopologyChangeOp.Add,
      owner,
      newSigningKey.fingerprint,
      KeyPurpose.Signing,
      intermediateKey.fingerprint.some,
    )

    // Remove the previous signing key authorized by the namespace root key, now only a signing key authorized by the namespace intermediate key exists
    identityManager.topology.owner_to_key_mappings.authorize(
      TopologyChangeOp.Remove,
      owner,
      currentSigningKey.fingerprint,
      currentSigningKey.purpose,
    )

    // Create a new namespace intermediate key
    val newIntermediateKey = setupIntermediateKey(identityManager, rootKey)

    // architecture-handbook-entry-begin: RotateNamespaceIntermediateKey

    // Renew all active topology transactions that have been authorized by the previous intermediate key with the new intermediate key
    identityManager.topology.all.renew(intermediateKey.fingerprint, newIntermediateKey.fingerprint)

    // Remove the previous intermediate key
    identityManager.topology.namespace_delegations.authorize(
      TopologyChangeOp.Remove,
      rootKey.fingerprint,
      intermediateKey.fingerprint,
    )

    // architecture-handbook-entry-end: RotateNamespaceIntermediateKey

    // check that only the root key and the new key is listed
    eventually() {
      val delegations = identityManager.topology.namespace_delegations
        .list(
          filterStore = AuthorizedStore.filterName,
          filterNamespace = rootKey.id.toProtoPrimitive,
        )
      val delegatedKeys = delegations.map(_.targetKey)

      delegatedKeys shouldNot contain(intermediateKey.fingerprint)
      delegatedKeys shouldBe Seq(rootKey.fingerprint, newIntermediateKey.fingerprint)
    }

    // We should still be able to ping with the participant1 signing key authorized by the newIntermediateKey
    assertPingSucceeds(participant2, participant1)
  }

  protected def rotateNodeKeyAndPing(
      node: InstanceReference,
      identityManager: InstanceReference,
      newKeyName: String,
      purpose: KeyPurpose = KeyPurpose.Signing,
  )(implicit
      env: EnterpriseTestConsoleEnvironment
  ): Assertion = {
    import env.*

    assertPingSucceeds(participant2, participant1)

    // Get the key owner id from the node id
    val owner = node.id match {
      case domainId: DomainId => DomainTopologyManagerId(domainId)
      case owner: KeyOwner => owner
      case unknown =>
        fail(s"Unknown key owner: $unknown")
    }

    // Find the current key in the identity manager's store
    val currentKey = identityManager.topology.owner_to_key_mappings
      .list(filterStore = AuthorizedStore.filterName, filterKeyOwnerUid = owner.filterString)
      .find(x => x.item.owner == owner && x.item.key.purpose == purpose)
      .map(_.item.key)
      .getOrElse(sys.error(s"No key found for owner $owner of purpose $purpose"))

    // Generate a new key on the node
    val newKey = purpose match {
      case KeyPurpose.Signing => node.keys.secret.generate_signing_key(newKeyName)
      case KeyPurpose.Encryption => node.keys.secret.generate_encryption_key(newKeyName)
    }

    // Import the generated public key into the identity manager if node and identity manager are separate nodes
    if (identityManager != node) {
      identityManager.keys.public
        .upload(newKey.toByteString(testedProtocolVersion), Some(newKeyName))
    }

    // Rotate the key for the node through the identity manager
    identityManager.topology.owner_to_key_mappings.rotate_key(
      node,
      owner,
      currentKey,
      newKey,
    )

    // check that only new key is listed
    eventually() {
      val inspect = identityManager.keys.public
        .list_by_owner(owner)
        .flatMap(_.keys(purpose).map(_.fingerprint))
      assertResult(Seq(newKey.fingerprint))(inspect)
    }

    // check that ping still works
    assertPingSucceeds(participant2, participant1)
  }
}

/** Tests the management (specifically rotation) of various cryptographic keys. */
trait KeyManagementIntegrationTest
    extends KeyManagementIntegrationTestHelper
    with EnterpriseHasCycleUtils
    with SecurityTestSuite
    with AccessTestScenario
    with KeyManagementTestHelper {

  // TODO(test-coverage): disable participant / roll keys while the affected nodes are busy

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.distributedSingleDomain
      .addConfigTransforms(
        ConfigTransforms.enableRemoteDomainManagers("domainManager1", "remoteManager1")
      )
      .withSetup { implicit env =>
        import env.*

        domainManager1.setup.bootstrap_domain(Seq(sequencer1), Seq(mediator1))

        Seq[LocalInstanceReference](domainManager1, sequencer1, mediator1).foreach { n =>
          n.health.wait_for_initialized()
        }

        participant1.domains.connect_local(sequencer1)
        participant2.domains.connect_local(sequencer1)
      }

  "A Canton operator" can {

    "rotate mediator signing key" taggedAs rotateNodeKeysTest("mediator node") in { implicit env =>
      import env.*
      rotateNodeKeyAndPing(mediator1, domainManager1, "mediator1-signing-rotated")
    }

    "rotate sequencer signing key" taggedAs rotateNodeKeysTest("sequencer node") in {
      implicit env =>
        import env.*
        rotateNodeKeyAndPing(
          sequencer1,
          domainManager1,
          "sequencer1-signing-rotated",
        )
    }

    "rotate domain topology manager signing key" taggedAs rotateNodeKeysTest(
      "domain topology manager"
    ) in { implicit env =>
      import env.*
      rotateNodeKeyAndPing(domainManager1, domainManager1, "domainManager1-signing-rotated")
    }

    "rotate participant signing keys" taggedAs rotateNodeKeysTest("participant node") in {
      implicit env =>
        import env.*
        rotateNodeKeyAndPing(participant1, participant1, "participant1-signing-rotated")
    }

    "rotate participant encryption keys" taggedAs rotateNodeKeysTest("participant node") in {
      implicit env =>
        import env.*
        rotateNodeKeyAndPing(
          participant1,
          participant1,
          "participant1-encryption-rotated",
          purpose = KeyPurpose.Encryption,
        )
    }

    "create participant namespace intermediate key and rotate the key" taggedAs rotateNamespaceKeysTest(
      "participant"
    ) in { implicit env =>
      import env.*
      rotateIntermediateNamespaceKeyAndPing(participant1, participant1, None)
    }

    "create domain namespace intermediate key and rotate the key" taggedAs rotateNamespaceKeysTest(
      "domain"
    ) in { implicit env =>
      import env.*

      rotateIntermediateNamespaceKeyAndPing(domainManager1, sequencer1, None)
    }

    "rotate key of an identifier delegation" in { implicit env =>
      import env.*

      val identityManager = participant1
      val node = participant1

      assertPingSucceeds(participant2, participant1)

      val identifierKey = setupIdentifierDelegation(node, identityManager)

      val currentNodeKey = identityManager.topology.owner_to_key_mappings
        .list(filterStore = AuthorizedStore.filterName, filterKeyOwnerUid = node.filterString)
        .find(x => x.item.owner == node.id && x.item.key.purpose == KeyPurpose.Signing)
        .map(_.item.key)
        .getOrElse(sys.error(s"No key found for owner $node"))

      // Create a new signing key for the node
      val newNodeKey = node.keys.secret.generate_signing_key()
      if (node != identityManager)
        identityManager.keys.public.upload(newNodeKey.toByteString(testedProtocolVersion), None)

      identityManager.topology.owner_to_key_mappings.authorize(
        TopologyChangeOp.Add,
        node.id,
        newNodeKey.fingerprint,
        newNodeKey.purpose,
        identifierKey.fingerprint.some,
      )

      // Remove the previous node key, now only the key authorized by the identifier delegation remains
      identityManager.topology.owner_to_key_mappings.authorize(
        TopologyChangeOp.Remove,
        node.id,
        currentNodeKey.fingerprint,
        currentNodeKey.purpose,
      )

      // Create a new identifier delegation, renew the existing topology transactions, then remove the previous identifier delegation
      val newIdentifierKey = setupIdentifierDelegation(node, identityManager)

      identityManager.topology.all.renew(identifierKey.fingerprint, newIdentifierKey.fingerprint)

      identityManager.topology.identifier_delegations.authorize(
        TopologyChangeOp.Remove,
        node.id.uid,
        identifierKey.fingerprint,
      )

      assertPingSucceeds(participant2, participant1)
    }

    "fail to renew a key if permissions of the new key are insufficient" in { implicit env =>
      import env.*

      val identityManager = domainManager1
      val node = mediator1

      val rootKey =
        identityManager.keys.secret
          .list(filterName = s"${identityManager.name}-namespace")
          .headOption
          .getOrElse(fail("Cannot get namespace signing"))
          .publicKey

      val namespaceIntermediateKey = setupNamespaceIntermediateKey(identityManager, rootKey)
      val identifierKey = setupIdentifierDelegation(node, identityManager)

      // Should fail because the identifier key won't be able to sign for the entire namespace as the namespace intermediate key
      assertThrows[IllegalArgumentException] {
        identityManager.topology.all
          .renew(namespaceIntermediateKey.fingerprint, identifierKey.fingerprint)
      }
    }

    "download and upload private keys locally" in { implicit env =>
      import env.*

      val privateKeyMetadata = domainManager1.keys.secret.list().head
      val privateKeyId = privateKeyMetadata.id
      val privateKeyNew = domainManager1.keys.secret.download(privateKeyId)

      val keyPair =
        CryptoKeyPair.fromByteString(privateKeyNew).valueOrFail("parsing of crypto key pair")

      // The old format was just the protobuf message serialized to bytestring
      val privateKeyOld = keyPair.toProtoCryptoKeyPairV0.toByteString

      // Delete the secret key before re-uploading
      // user-manual-entry-begin: DeletePrivateKey
      domainManager1.keys.secret.delete(privateKeyId, force = true)
      // user-manual-entry-end: DeletePrivateKey
      domainManager1.keys.secret.list(filterFingerprint = privateKeyId.unwrap) should have size (0)

      domainManager1.keys.secret.upload(privateKeyOld, privateKeyMetadata.name.map(_.unwrap))

      domainManager1.keys.secret.list(filterFingerprint = privateKeyId.unwrap) should have size (1)
    }

    "download and upload private keys remotely" in { implicit env =>
      import env.*

      val remoteDomainManager1 = rdm("remoteManager1")

      val privateKeyMetadata = remoteDomainManager1.keys.secret.list().head
      val privateKeyId = privateKeyMetadata.id
      val privateKey = remoteDomainManager1.keys.secret.download(privateKeyId)

      // Delete the secret key before re-uploading
      remoteDomainManager1.keys.secret.delete(privateKeyId, force = true)
      remoteDomainManager1.keys.secret
        .list(filterFingerprint = privateKeyId.unwrap) should have size (0)

      remoteDomainManager1.keys.secret.upload(privateKey, privateKeyMetadata.name.map(_.unwrap))

      remoteDomainManager1.keys.secret
        .list(filterFingerprint = privateKeyId.unwrap) should have size (1)
    }

    "rotate a node's keys using the rotate_node_key macro" in { implicit env =>
      import env.*

      val currentKeys = participant1.keys.secret.list()
      val p2Key =
        // user-manual-entry-begin: ListPublicKeys
        participant2.keys.secret
          .list()
          // user-manual-entry-end: ListPublicKeys
          .find(_.publicKey.fingerprint != participant2.id.uid.namespace.fingerprint)
          .valueOrFail("could not find a valid key to rotate")

      // Rotate a participant's keys
      // user-manual-entry-begin: RotateNodeKeys
      participant1.keys.secret.rotate_node_keys()
      // user-manual-entry-end: RotateNodeKeys

      // user-manual-entry-begin: RotateNodeKey
      val p2KeyNew = participant2.keys.secret.rotate_node_key(
        p2Key.publicKey.fingerprint.unwrap,
        "key_rotated",
      )
      // user-manual-entry-end: RotateNodeKey
      participant2.topology.synchronisation.await_idle()

      val (p2StoredPubKey, p2StoredPubKeyName) = participant2.keys.secret
        .list()
        .map(key => (key.publicKey, key.name))
        .find { case (pubKey, _) => pubKey.fingerprint == p2KeyNew.fingerprint }
        .valueOrFail("cannot find new key")

      p2StoredPubKey shouldBe p2KeyNew
      p2StoredPubKeyName shouldBe Some("key_rotated")

      p2KeyNew should not be p2Key.publicKey

      participant1.topology.synchronisation.await_idle()
      val newKeys = participant1.keys.secret.list()
      currentKeys should not equal newKeys

      rotateAndTest(domainManager1, domainManager1)
      rotateAndTest(sequencer1, domainManager1)
      rotateAndTest(mediator1, domainManager1)

      // Rotate the domain keys again (and use snippet for documentation)
      // user-manual-entry-begin: RotateNodeKeys2
      domainManager1.keys.secret.rotate_node_keys()
      sequencer1.keys.secret.rotate_node_keys(domainManager1)
      mediator1.keys.secret.rotate_node_keys(domainManager1)
      // user-manual-entry-end: RotateNodeKeys2

      domainManager1.topology.synchronisation.await_idle()

      participant1.health.ping(participant2)

      // trying to rotate a key on a sequencer node without a domain manager reference must fail
      assertThrows[IllegalArgumentException](sequencer1.keys.secret.rotate_node_keys())
    }
  }
}

class KeyManagementIntegrationTestPostgres extends KeyManagementIntegrationTest {
  registerPlugin(new UsePostgres(loggerFactory))
}

// takes 10 min on oracle
//class KeyManagementIntegrationTestOracle extends KeyManagementIntegrationTest {
//  registerPlugin(new UseOracle(loggerFactory))
//}
