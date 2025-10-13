// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.security

import com.digitalasset.canton.config.{EnterpriseCryptoConfig, EnterpriseCryptoProvider}
import com.digitalasset.canton.console.CommandExecutionFailedException
import com.digitalasset.canton.crypto.{
  CryptoKeyPair,
  EncryptionKeyPair,
  EncryptionPublicKey,
  PrivateKey,
  PublicKey,
  SigningKeyPair,
  SigningPublicKey,
  TestFingerprint,
}
import com.digitalasset.canton.integration.tests.{
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.integration.{ConfigTransforms, EnterpriseEnvironmentDefinition}
import com.digitalasset.canton.logging.SuppressionRule
import com.digitalasset.canton.participant.admin.PingService
import com.digitalasset.canton.topology.transaction.TopologyChangeOp
import com.digitalasset.canton.topology.{Identifier, PartyId}
import org.slf4j.event.Level

import scala.concurrent.duration.*

class TinkCryptoIntegrationTest
    extends CryptoIntegrationTest(EnterpriseCryptoConfig(provider = EnterpriseCryptoProvider.Tink))
    with ReconnectDomainAutoInitIntegrationTest

class JceCryptoIntegrationTest
    extends CryptoIntegrationTest(EnterpriseCryptoConfig(provider = EnterpriseCryptoProvider.Jce))
    with ReconnectDomainAutoInitIntegrationTest

/** @param nodeToConnectAlias used in the ping test when verifying connectivity to the domain. When we have a
  *                           distributed domain this should take name of the sequencer that we are connecting to.
  */
abstract class CryptoIntegrationTest(
    cryptoConfig: EnterpriseCryptoConfig,
    nodeToConnectAlias: String = "da",
) extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment {

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.singleDomain
      .addConfigTransforms(
        ConfigTransforms.setCrypto(cryptoConfig),
        ConfigTransforms.adjustUck(enabled = false),
      )
      .withSetup { implicit env =>
        import env.*
        participant1.domains.connect_local(da)
        participant2.domains.connect_local(da)
      }

  s"With crypto provider ${cryptoConfig.provider}" should {

    "make a ping" in { implicit env =>
      import env.*

      eventually() {
        assert(
          participant1.domains
            .list_connected()
            .map(_.domainAlias.unwrap)
            .contains(nodeToConnectAlias)
        )
        assert(
          participant2.domains
            .list_connected()
            .map(_.domainAlias.unwrap)
            .contains(nodeToConnectAlias)
        )
      }

      loggerFactory.suppress(
        SuppressionRule.forLogger[PingService] && SuppressionRule.Level(Level.WARN)
      ) {
        eventually() {
          assertPingSucceeds(participant1, participant2)
        }
      }

      eventually() { // wait for ping to be cleaned up
        participant1.testing.acs_search(
          nodeToConnectAlias,
          filterTemplate = "^PingPong",
        ) shouldBe empty
      }
    }

    // exporting private keys is not allowed when using a KMS provider
    if (cryptoConfig.provider != EnterpriseCryptoProvider.Kms) {
      "export and import private keys pair offline" in { implicit env =>
        import env.*
        // architecture-handbook-entry-begin: ExportKeyForOfflineStorage
        // fingerprint of namespace giving key
        val participantId = participant1.id
        val namespace = participantId.uid.namespace.fingerprint

        // create new key
        val name = "new-identity-key"
        val fingerprint = participant1.keys.secret.generate_signing_key(name = name).fingerprint

        // create an intermediate certificate authority through a namespace delegation
        // we do this by adding a new namespace delegation for the newly generated key
        // and we sign this using the root namespace key
        participant1.topology.namespace_delegations.authorize(
          TopologyChangeOp.Add,
          namespace,
          fingerprint,
          signedBy = Some(namespace),
        )

        // export namespace key to file for offline storage, in this example, it's a temporary file
        better.files.File.usingTemporaryFile("namespace", ".key") { privateKeyFile =>
          participant1.keys.secret.download_to(namespace, privateKeyFile.toString)

          // delete namespace key (very dangerous ...)
          participant1.keys.secret.delete(namespace, force = true)

          // architecture-handbook-entry-end: ExportKeyForOfflineStorage

          // key should not be present anymore on p1
          participant1.keys.secret.list(namespace.unwrap) shouldBe empty

          // show that we can still add new parties using the new delegate key
          participant1.topology.party_to_participant_mappings.authorize(
            TopologyChangeOp.Add,
            PartyId(participantId.uid.copy(id = Identifier.tryCreate("NewParty"))),
            participantId,
            signedBy = Some(fingerprint),
          )

          // ensure party pops up on the domains
          eventually() {
            participant1.parties.list(filterParty = "NewParty") should not be empty
          }

          val other = participant1 // using other for the manual ...
          // architecture-handbook-entry-begin: ImportFromOfflineStorage
          // import it back wherever needed
          other.keys.secret.upload(privateKeyFile.toString, Some("newly-imported-identity-key"))
          // architecture-handbook-entry-end: ImportFromOfflineStorage

          participant1.keys.secret.list(namespace.unwrap) should not be empty
        }
      }

      "fail to import a crypto key pair when the public key fingerprint is not correctly generated" in {
        implicit env =>
          import env.*

          val invalidFingerprint = TestFingerprint.generateFingerprint("mock")

          val signingPublicKey = participant1.crypto.privateCrypto.generateSigningKey().futureValue
          val wrongSigningPublicKey =
            SigningPublicKey.idUnsafe.replace(invalidFingerprint)(signingPublicKey)
          val wrongSigningKeyPair =
            SigningKeyPair
              .wrongSigningKeyPairWithPublicKeyUnsafe(wrongSigningPublicKey)
              .asInstanceOf[CryptoKeyPair[PublicKey, PrivateKey]]

          val encryptionPublicKey = participant1.crypto.generateEncryptionKey().futureValue
          val wrongEncryptionPublicKey =
            EncryptionPublicKey.idUnsafe.replace(invalidFingerprint)(encryptionPublicKey)
          val wrongEncryptionKeyPair =
            EncryptionKeyPair
              .wrongEncryptionKeyPairWithPublicKeyUnsafe(wrongEncryptionPublicKey)
              .asInstanceOf[CryptoKeyPair[PublicKey, PrivateKey]]

          forAll(
            Set(
              (signingPublicKey, wrongSigningKeyPair),
              (encryptionPublicKey, wrongEncryptionKeyPair),
            )
          ) { case (publicKey, wrongKeyPair) =>
            // upload should fail during key deserialization because of fingerprint mismatch
            assertThrowsAndLogsCommandFailures(
              participant1.keys.secret
                .upload(
                  wrongKeyPair.toByteString(testedProtocolVersion),
                  Some("newly-imported-identity-key"),
                ),
              _.commandFailureMessage should (include(
                "Failed to parse crypto key pair: CryptoDeserializationError(DefaultDeserializationError("
              ) and include(
                s"Failed to deserialize ${wrongKeyPair.publicKey.format} public key: " +
                  s"KeyParseAndValidateError(The regenerated fingerprint ${publicKey.fingerprint} does not match " +
                  s"the fingerprint of the object: $invalidFingerprint)"
              )),
            )
          }

      }

      "export and import private key pairs offline to a different participant" in { implicit env =>
        import env.*

        val participantId = participant1.id
        val namespace = participantId.uid.namespace.fingerprint

        better.files.File.usingTemporaryFile("namespace", ".key") { keyPairFile =>
          participant1.keys.secret.download_to(namespace, keyPairFile.toString)

          participant2.keys.secret.list(namespace.unwrap) shouldBe empty
          participant2.keys.secret.upload(keyPairFile.toString, Some("newly-imported-identity-key"))
          participant2.keys.secret.list(namespace.unwrap) should not be empty
        }
      }
    }

  }
}

/** Test that participants are able to automatically reconnect to a domain after it has restarted with a new ID/Alias.
  * This requires auto-init to be active, otherwise a manual connection of the participants would have to take place.
  */
sealed trait ReconnectDomainAutoInitIntegrationTest {
  self: EnterpriseIntegrationTest =>

  "be able to connect to a reset domain with a new alias" in { implicit env =>
    import env.*
    eventually() {
      val (domainStatus, participantStatus) = health.status().tupled
      domainStatus(da.name).connectedParticipants should contain.allOf(
        participantStatus(participant1.name).id,
        participantStatus(participant2.name).id,
      )
      participantStatus(participant1.name).connectedDomains should contain(
        domainStatus(da.name).id -> true
      )
      participantStatus(participant2.name).connectedDomains should contain(
        domainStatus(da.name).id -> true
      )
    }

    loggerFactory.suppressWarningsAndErrors {
      logger.info(s"stopping domain da")
      da.stop()

      // when domain starts again, it will have a different id and the participants will get disconnected with a warning
      logger.info(s"starting domain da")
      da.start()

      // after domain reset, participants get automatically disconnected
      eventually(10.seconds) {
        val (domainStatus, participantStatus) = health.status().tupled
        domainStatus(da.name).connectedParticipants shouldBe empty
        participantStatus(participant1.name).connectedDomains shouldBe empty
        participantStatus(participant2.name).connectedDomains shouldBe empty
      }
    }
    // connecting to the reset domain with the same alias is not possible, since the domain now has a new identity
    loggerFactory.suppressWarningsErrorsExceptions[CommandExecutionFailedException](
      participant1.domains.reconnect("da")
    )
    loggerFactory.suppressWarningsErrorsExceptions[CommandExecutionFailedException](
      participant2.domains.reconnect("da")
    )

    // connect with a new alias and it all should work
    participant1.domains.connect_local(da, manualConnect = false, Some("da_newalias"))
    participant2.domains.connect_local(da, manualConnect = false, Some("da_newalias"))

    eventually() {
      val (domainStatus, participantStatus) = health.status().tupled
      domainStatus(da.name).connectedParticipants should contain.allOf(
        participantStatus(participant1.name).id,
        participantStatus(participant2.name).id,
      )
      participantStatus(participant1.name).connectedDomains should contain(
        domainStatus(da.name).id -> true
      )
      participantStatus(participant2.name).connectedDomains should contain(
        domainStatus(da.name).id -> true
      )

      // we need to wait until participant1 observed both participants, as otherwise below ping will fail
      participant1.parties
        .list(
          filterParticipant = participantStatus(participant2.name).id.filterString,
          filterDomain = domainStatus(da.name).id.filterString,
        ) should have length 1
    }

    logger.info(s"participant1 pings participant2")
    assertPingSucceeds(participant1, participant2)
  }

}
