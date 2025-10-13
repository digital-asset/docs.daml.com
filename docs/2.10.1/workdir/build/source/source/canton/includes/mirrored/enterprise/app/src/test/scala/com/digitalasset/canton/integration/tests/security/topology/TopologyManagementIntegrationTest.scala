// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.security.topology

import com.daml.test.evidence.scalatest.AccessTestScenario
import com.daml.test.evidence.scalatest.ScalaTestSupport.Implicits.*
import com.daml.test.evidence.tag.Security.SecurityTest.Property.*
import com.daml.test.evidence.tag.Security.{Attack, SecurityTest, SecurityTestSuite}
import com.digitalasset.canton.DomainAlias
import com.digitalasset.canton.ProtoDeserializationError.ProtoDeserializationFailure
import com.digitalasset.canton.admin.api.client.data.ListOwnerToKeyMappingResult
import com.digitalasset.canton.console.commands.DomainChoice
import com.digitalasset.canton.console.{
  CommandFailure,
  InstanceReference,
  LocalParticipantReference,
  ParticipantReference,
}
import com.digitalasset.canton.crypto.*
import com.digitalasset.canton.crypto.admin.grpc.PrivateKeyMetadata
import com.digitalasset.canton.data.CantonTimestamp
import com.digitalasset.canton.domain.topology.DomainTopologyManagerError
import com.digitalasset.canton.integration.*
import com.digitalasset.canton.integration.plugins.UsePostgres
import com.digitalasset.canton.integration.tests.{
  EnterpriseHasCycleUtils,
  EnterpriseIntegrationTest,
  SharedEnterpriseEnvironment,
}
import com.digitalasset.canton.logging.LogEntry
import com.digitalasset.canton.participant.admin.workflows.java.pingpong
import com.digitalasset.canton.participant.topology.ParticipantTopologyManagerError
import com.digitalasset.canton.topology.*
import com.digitalasset.canton.topology.store.TimeQuery
import com.digitalasset.canton.topology.transaction.*
import com.google.protobuf.ByteString

import scala.concurrent.duration.*
import scala.concurrent.{Await, ExecutionContext, Future, blocking}
import scala.jdk.CollectionConverters.*

trait TopologyManagementIntegrationTest
    extends EnterpriseIntegrationTest
    with SharedEnterpriseEnvironment
    with EnterpriseHasCycleUtils
    with SecurityTestSuite
    with AccessTestScenario {

  // TODO(test-coverage): disable participant / roll keys while the affected nodes are busy

  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.singleDomain withSetup { implicit env =>
      import env.*
      participant1.domains.connect_local(da)
      participant2.domains.connect_local(da)
    }

  "A Canton operator" can {
    "reconnect a participant to a domain twice" in { implicit env =>
      import env.*

      // making sure that attempting to connect when already connected will not leave things in a bad state
      participant1.domains.reconnect("da")
      participant2.domains.reconnect("da")
      participant1.domains.reconnect("da")

    }

    "issue new certificates through the domain admin api" in { implicit env =>
      import env.*

      utils.synchronize_topology()
      // create a new intermediate CA on the domain
      val intermediateCAKey = da.keys.secret.generate_signing_key("intermediate-ca")
      val nd = da.topology.namespace_delegations.list(filterStore = da.id.filterString)
      val daKey =
        da.keys.secret
          .list(filterName = "da-namespace")
          .headOption
          .getOrElse(fail("Cannot get default signing key for da"))
          .publicKey
          .fingerprint

      da.topology.namespace_delegations.authorize(
        TopologyChangeOp.Add,
        daKey,
        intermediateCAKey.fingerprint,
      )

      eventually() {
        val nd3 = da.topology.namespace_delegations.list(filterStore = da.id.filterString)
        assertResult(1, nd3.map(_.item))(nd3.length - nd.length)
      }

      // let the mediator key be the identifier delegation for participant1, using the intermediate CA
      val identifierCAKey = da.keys.secret.generate_signing_key("identifier-ca")
      val daId = da.id

      val idt = da.topology.identifier_delegations.list()
      da.topology.identifier_delegations.authorize(
        TopologyChangeOp.Add,
        daId.unwrap,
        identifierCAKey.fingerprint,
        Some(intermediateCAKey.fingerprint),
      )
      eventually() { () =>
        val idt2 = da.topology.identifier_delegations.list(
          da.id.filterString,
          timeQuery = TimeQuery.Range(
            Some(CantonTimestamp.MinValue),
            Some(CantonTimestamp.MaxValue),
          ),
          operation = Some(TopologyChangeOp.Add),
        )
        assert(idt.length + 1 == idt2.length)
      }
    }

    "allocate new parties" taggedAs_ { scenario =>
      SecurityTest(
        property = Authorization,
        asset = "ledger api",
        happyCase = scenario,
      )
    } in { implicit env =>
      import env.*

      val p1Id = participant1.id

      // add new party
      val newParty = PartyId(p1Id.uid.copy(id = Identifier.tryCreate("Donald")))
      participant1.topology.party_to_participant_mappings.authorize(
        TopologyChangeOp.Add,
        newParty,
        p1Id,
        signedBy = Some(p1Id.uid.namespace.fingerprint),
      )

      eventually() {
        val pr1 = da.topology.party_to_participant_mappings
          .list(filterParty = "Donald", filterStore = "Authorized")
        val pr2 = da.topology.party_to_participant_mappings.list(
          filterParty = "Donald",
          filterStore = da.id.filterString,
          filterParticipant = p1Id.filterString,
          filterRequestSide = Some(RequestSide.Both),
          filterPermission = Some(ParticipantPermission.Submission),
        )
        assertResult(1, pr1)(pr1.length)
        assertResult(pr1.length)(pr2.length)
      }

      def checkPartyExists(
          participant: LocalParticipantReference,
          name: String,
          exists: Boolean = true,
      ): Unit =
        eventually() {
          val plist1 = participant.parties.list(name)
          if (exists) {
            plist1 should have length 1
            plist1.map(_.party.toProtoPrimitive) contains name
          } else {
            plist1 shouldBe empty
          }
        }

      checkPartyExists(participant1, newParty.toProtoPrimitive)

      participant1.ledger_api.parties.allocate("someone", "this is someone")
      checkPartyExists(participant1, "someone")

      // check party management macros
      // architecture-handbook-entry-begin: EnableParty
      val name = "Gottlieb"
      participant1.parties.enable(name)
      // architecture-handbook-entry-end: EnableParty

      checkPartyExists(participant1, name)
      // architecture-handbook-entry-begin: DisableParty
      participant1.parties.disable(name)
      // architecture-handbook-entry-end: DisableParty
      checkPartyExists(participant1, name, exists = false)
    }

    "permission a party on two nodes" taggedAs_ { action =>
      SecurityTest(
        property = Authorization,
        asset = "ledger api",
        happyCase = action,
      )
    } in { implicit env =>
      import env.*

      // enable party on participant1 (will invoke topology.party_to_participant_mappings.authorize) under the hood
      val partyId = participant1.parties.enable("Jesper")
      val p2id = participant2.id

      // authorize mapping of Jesper to P2 on the topology manager of Jesper
      participant1.topology.party_to_participant_mappings.authorize(
        ops = TopologyChangeOp.Add,
        party = partyId, // party unique identifier
        participant = p2id, // participant unique identifier
        side =
          RequestSide.From, // request side is From if signed by the party idm, To if signed by the participant idm.
        permission =
          ParticipantPermission.Submission, // optional argument defaulting to `Submission`.
      )
      // authorize mapping of Jesper to P2 on the topology manager of P2
      participant2.topology.party_to_participant_mappings.authorize(
        ops = TopologyChangeOp.Add,
        party = partyId,
        participant = p2id,
        side = RequestSide.To,
        permission = ParticipantPermission.Submission,
      )

      eventually() {
        Seq(participant1, participant2).foreach { p =>
          p.parties
            .list("Jesper")
            .flatMap(_.participants.filter(_.domains.nonEmpty).map(_.participant))
            .toSet shouldBe Set(participant1.id, participant2.id)
        }
      }
      clue("running cycle after permissioning party on two nodes") {
        runCycle(partyId, participant1, participant2)
      }
    }

    "inspect the participant state" in { implicit env =>
      import env.*

      participant1.topology.participant_domain_states
        .list(
          filterStore = "da",
          timeQuery = TimeQuery
            .Range(from = Some(CantonTimestamp.MinValue), until = Some(CantonTimestamp.MaxValue)),
          filterParticipant = "participant1",
        )
        .map(x => (x.item.side, x.item.permission)) shouldBe Seq[
        (RequestSide, ParticipantPermission)
      ](
        (RequestSide.From, ParticipantPermission.Submission),
        (RequestSide.To, ParticipantPermission.Submission),
      )

    }

    "disable and re-enable a participant safely" taggedAs SecurityTest(
      property = Availability,
      asset = "domain node",
      Attack(
        actor = "a malicious participant",
        threat = "runs a denial of service attack on a domain",
        mitigation = "disable the participant",
      ),
    ) in { implicit env =>
      import env.*

      def disableP1() =
        loggerFactory.suppressWarnings {
          da.participants.set_state(participant1.id, ParticipantPermission.Disabled)
          eventually() {
            participant1.domains.list_connected() shouldBe empty
          }
        }

      def reconnectP1() = {
        eventually() {
          da.participants.active(participant1.id) shouldBe true
        }
        participant1.domains.reconnect("da")
        eventually() {
          participant1.domains.list_connected().map(_.domainAlias) shouldBe List(
            DomainAlias.tryCreate("da")
          )
        }
      }

      // verify that p1 is currently connected
      assertResult(List(DomainAlias.tryCreate("da")))(
        participant1.domains.list_connected().map(_.domainAlias)
      )
      clue("disable p1 first") {
        disableP1()
      }
      clue("re-enable p1 first") {
        da.participants.set_state(participant1.id, ParticipantPermission.Submission)
      }
      clue("reconnect p1 first") {
        reconnectP1()
      }
      clue("wait until active") {
        eventually() {
          participant1.domains.active("da")
        }
      }
      clue("can ping") {
        eventually() {
          loggerFactory.suppressWarnings {
            participant1.health.maybe_ping(participant1.id) shouldBe defined
          }
        }
      }
      // disable again and first re-connect with observation before getting to submission
      disableP1()
      da.participants.set_state(participant1.id, ParticipantPermission.Observation)
      reconnectP1()
      da.participants.set_state(participant1.id, ParticipantPermission.Submission)
      eventually() {
        loggerFactory.suppressWarnings {
          participant1.health.maybe_ping(participant1.id) shouldBe defined
        }
      }
    }

    "not import same transaction twice" in { implicit env =>
      import env.*

      val tx = participant1.topology.party_to_participant_mappings.authorize(
        TopologyChangeOp.Add,
        PartyId(participant1.uid.copy(id = Identifier.tryCreate("Watslav"))),
        participant1.id,
        RequestSide.Both,
        ParticipantPermission.Submission,
      )
      assertThrowsAndLogsCommandFailures(
        participant1.topology.load_transaction(tx),
        _.shouldBeCantonErrorCode(TopologyManagerError.DuplicateTransaction),
      )

    }

    "not add the same party twice" in { implicit env =>
      import env.*

      def add() = participant1.topology.party_to_participant_mappings.authorize(
        TopologyChangeOp.Add,
        PartyId(participant1.uid.copy(id = Identifier.tryCreate("Boris"))),
        participant1.id,
        RequestSide.Both,
        ParticipantPermission.Submission,
      )

      // add once
      val tx = add()
      // add twice
      assertThrowsAndLogsCommandFailures(
        add(),
        _.shouldBeCantonErrorCode(TopologyManagerError.MappingAlreadyExists),
      )
      // also fail importing
      assertThrowsAndLogsCommandFailures(
        participant1.topology.load_transaction(tx),
        _.shouldBeCantonErrorCode(TopologyManagerError.DuplicateTransaction),
      )
      // also fails when adding party twice
      assertThrowsAndLogsCommandFailures(
        participant1.parties.enable("Boris"),
        _.shouldBeCantonErrorCode(TopologyManagerError.MappingAlreadyExists),
      )

      // disable user to avoid conflicts with future tests
      participant1.parties.disable("Boris")
    }

    "not disable party if active contracts" in { implicit env =>
      import env.*

      val Vlad = participant1.parties.enable("Vlad", waitForDomain = DomainChoice.All)
      createCycleContract(participant1, Vlad, "Disable-Party-Active-Contracts")
      val coid = participant1.ledger_api.javaapi.acs.await(pingpong.Cycle.COMPANION)(Vlad)

      def remove() =
        participant1.topology.party_to_participant_mappings.authorize(
          TopologyChangeOp.Remove,
          PartyId(Vlad.uid),
          participant1.id,
          RequestSide.Both,
          ParticipantPermission.Submission,
        )

      // try to remove
      assertThrowsAndLogsCommandFailures(
        remove(),
        _.shouldBeCantonErrorCode(
          ParticipantTopologyManagerError.DisablePartyWithActiveContractsRequiresForce
        ),
      )

      // archive contract
      val cycleEx = coid.id.exerciseVoid().commands.asScala.toSeq
      participant1.ledger_api.javaapi.commands.submit(
        Seq(Vlad),
        cycleEx,
      )

      // try to remove again
      remove()
      eventually() {
        participant1.topology.party_to_participant_mappings.list(
          filterParty = "Vlad",
          filterParticipant = participant1.id.filterString,
          filterRequestSide = Some(RequestSide.Both),
          filterPermission = Some(ParticipantPermission.Submission),
        ) shouldBe empty
      }
    }

    "disable party with active contract with force" in { implicit env =>
      import env.*

      val Rick = participant1.parties.enable("Rick", waitForDomain = DomainChoice.All)
      createCycleContract(participant1, Rick, "Disable-Party-Active-Contracts-Force")
      participant1.ledger_api.javaapi.acs.await(pingpong.Cycle.COMPANION)(Rick)

      // remove with force
      participant1.topology.party_to_participant_mappings.authorize(
        TopologyChangeOp.Remove,
        PartyId(Rick.uid),
        participant1.id,
        RequestSide.Both,
        ParticipantPermission.Submission,
        force = true,
      )

      eventually() {
        participant1.topology.party_to_participant_mappings.list(
          filterParty = "Rick",
          filterParticipant = participant1.id.filterString,
          filterRequestSide = Some(RequestSide.Both),
          filterPermission = Some(ParticipantPermission.Submission),
        ) shouldBe empty
      }
    }

    "add the same party twice if authorized with different keys" taggedAs_ { action =>
      SecurityTest(
        property = Authorization,
        asset = "ledger api",
        happyCase = action,
      )
    } in { implicit env =>
      import env.*

      def add(signingKey: Option[Fingerprint]) =
        participant1.topology.party_to_participant_mappings.authorize(
          TopologyChangeOp.Add,
          PartyId(participant1.uid.copy(id = Identifier.tryCreate("Jeremias"))),
          participant1.id,
          RequestSide.Both,
          ParticipantPermission.Submission,
          signingKey,
        )
      // vanilla add
      add(None)
      eventually() {
        participant1.parties.list("Jeremias") should not be empty
      }
      // add new namespace delegation
      val key1 = participant1.keys.secret.generate_signing_key("test cert")
      participant1.topology.namespace_delegations.authorize(
        TopologyChangeOp.Add,
        participant1.uid.namespace.fingerprint,
        key1.fingerprint,
        isRootDelegation = false,
      )
      // add previous statement again but signed with a different key
      add(Some(key1.fingerprint))

    }

    def genTx(
        participant: LocalParticipantReference,
        tx: TopologyStateUpdate[AddRemoveChangeOp],
        key: SigningPublicKey,
    )(implicit ec: ExecutionContext): SignedTopologyTransaction[AddRemoveChangeOp] = {
      val crypto = participant.underlying
        .map(_.sync.syncCrypto.crypto)
        .getOrElse(sys.error("where is my crypto?"))
      SignedTopologyTransaction
        .create(
          tx,
          key,
          crypto.pureCrypto,
          crypto.privateCrypto,
          testedProtocolVersion,
        )
        .value
        .futureValue
        .getOrElse(sys.error("failed to create tx"))
    }

    "not remove a non-existent transaction" in { implicit env =>
      import env.*

      val key1 = participant1.keys.secret.generate_signing_key("test-key1")
      val tx = genTx(
        participant1,
        TopologyStateUpdate(
          TopologyChangeOp.Remove,
          TopologyStateUpdateElement(
            TopologyElementId.generate(),
            IdentifierDelegation(participant1.uid, key1),
          ),
          testedProtocolVersion,
        ),
        key1,
      )
      assertThrowsAndLogsCommandFailures(
        participant1.topology.load_transaction(tx.getCryptographicEvidence),
        _.shouldBeCantonErrorCode(TopologyManagerError.NoCorrespondingActiveTxToRevoke),
      )

    }

    def unauthorizedTxTest(reason: String) = SecurityTest(
      property = Authorization,
      asset = "topology manager",
      attack = Attack(
        actor = "an admin api user",
        threat = s"register an unauthorized topology transaction ($reason)",
        mitigation = "reject transaction",
      ),
    )

    "not add an unauthorized transaction" taggedAs unauthorizedTxTest("unauthorizedKey") in {
      implicit env =>
        import env.*

        val key = participant1.keys.secret.generate_signing_key("unauthorized-sequencer")
        val tx = genTx(
          participant1,
          TopologyStateUpdate(
            TopologyChangeOp.Add,
            TopologyStateUpdateElement(
              TopologyElementId.generate(),
              OwnerToKeyMapping(SequencerId(da.id.unwrap), key),
            ),
            testedProtocolVersion,
          ),
          key,
        )
        loggerFactory.assertThrowsAndLogs[CommandFailure](
          da.topology.load_transaction(tx.getCryptographicEvidence),
          _.shouldBeCantonErrorCode(TopologyManagerError.UnauthorizedTransaction),
          _.shouldBeCantonErrorCode(TopologyManagerError.UnauthorizedTransaction),
          _.commandFailureMessage should include(
            s"INVALID_ARGUMENT/${LogEntry.SECURITY_SENSITIVE_MESSAGE_ON_API}"
          ),
        )
    }

    "not add a topology transaction without a signing key" taggedAs unauthorizedTxTest(
      "missing key"
    ) in { implicit env =>
      import env.*

      assertThrowsAndLogsCommandFailures(
        participant1.topology.party_to_participant_mappings.authorize(
          TopologyChangeOp.Add,
          PartyId(participant2.uid.copy(id = Identifier.tryCreate("NothingToSignWith"))),
          participant2.id,
          RequestSide.Both,
          ParticipantPermission.Submission,
        ),
        _.shouldBeCantonErrorCode(TopologyManagerError.NoAppropriateSigningKeyInStore),
      )
    }

    "not add a topology transaction if the signing key is not in the store" taggedAs unauthorizedTxTest(
      "key not in store"
    ) in { implicit env =>
      import env.*

      val p2Key = participant2.keys.secret.generate_signing_key("some-secret-key")

      def add() = participant1.topology.party_to_participant_mappings.authorize(
        TopologyChangeOp.Add,
        PartyId(participant2.uid.copy(id = Identifier.tryCreate("NothingToSignWith"))),
        participant2.id,
        RequestSide.Both,
        ParticipantPermission.Submission,
        Some(p2Key.fingerprint),
      )

      assertThrowsAndLogsCommandFailures(
        add(),
        _.shouldBeCantonErrorCode(TopologyManagerError.PublicKeyNotInStore),
      )

      participant1.keys.public
        .upload(p2Key.toByteString(testedProtocolVersion), Some("p2-some-key"))
      assertThrowsAndLogsCommandFailures(
        add(),
        _.shouldBeCantonErrorCode(TopologyManagerError.SecretKeyNotInStore),
      )

    }

    "not add a topology transaction if the signature is invalid" taggedAs unauthorizedTxTest(
      "invalid signature"
    ) in { implicit env =>
      import env.*

      val key1 = participant1.keys.secret.generate_signing_key()
      val sig = participant1.keys.secret
        .list(filterFingerprint = participant1.uid.namespace.fingerprint.unwrap)
        .collectFirst { case PrivateKeyMetadata(x: SigningPublicKeyWithName, _) =>
          x.publicKey
        }
        .getOrElse(sys.error("where is my namespace key?"))

      def create() = genTx(
        participant1,
        TopologyStateUpdate(
          TopologyChangeOp.Add,
          TopologyStateUpdateElement(
            TopologyElementId.generate(),
            IdentifierDelegation(participant1.uid, key1),
          ),
          testedProtocolVersion,
        ),
        sig,
      )

      val tx1 = create()
      val tx2 = create()
      // steal the sig of tx2 and add it to tx1
      val fakeTx = tx1.update(signature = tx2.signature)
      // can not add it
      loggerFactory.assertThrowsAndLogs[CommandFailure](
        participant1.topology.load_transaction(fakeTx.getCryptographicEvidence),
        _.shouldBeCantonErrorCode(TopologyManagerError.InvalidSignatureError),
        _.commandFailureMessage should include(
          s"INVALID_ARGUMENT/${LogEntry.SECURITY_SENSITIVE_MESSAGE_ON_API}"
        ),
      )
      // but i can add the valid one
      participant1.topology.load_transaction(tx1.getCryptographicEvidence)

    }

    "not add owner to key mappings for alien domain entities" taggedAs unauthorizedTxTest(
      "alien domain entity"
    ) in { implicit env =>
      import env.*

      def mkNs(ref: InstanceReference) = {
        val key1 = ref.keys.secret.generate_signing_key("fake-domain-entities")
        val fakeUid = UniqueIdentifier(Identifier.tryCreate("fake"), Namespace(key1.fingerprint))
        ref.topology.namespace_delegations.authorize(
          TopologyChangeOp.Add,
          key1.fingerprint,
          key1.fingerprint,
          isRootDelegation = true,
        )
        (key1, fakeUid)
      }

      def auth(ref: InstanceReference, fakeUid: UniqueIdentifier, key: SigningPublicKey) =
        ref.topology.owner_to_key_mappings.authorize(
          TopologyChangeOp.Add,
          SequencerId(fakeUid),
          key.fingerprint,
          KeyPurpose.Signing,
        )

      val (key1, uid1) = mkNs(da)
      // domain will reject
      assertThrowsAndLogsCommandFailures(
        auth(da, uid1, key1),
        _.shouldBeCantonErrorCode(DomainTopologyManagerError.AlienDomainEntities),
      )

      // participant should be happy
      val (key2, uid2) = mkNs(participant1)

      // will succeed, but
      auth(participant1, uid2, key2)

      // we need to flush the idm system, therefore, we'll add another namespace update
      val (key3, _) = mkNs(participant1)
      eventually() {
        da.topology.namespace_delegations
          .list()
          .find(_.item.target.fingerprint == key3.fingerprint) should not be empty
      }

      // now, we can assert that the domain has not registered the alien domain entities (it was not even
      // forwarded to the remote domain)
      val seqId2 = SequencerId(uid2)
      da.topology.owner_to_key_mappings
        .list(
          filterKeyOwnerUid = seqId2.filterString,
          filterKeyOwnerType = Some(seqId2.code),
        ) shouldBe empty

    }

    "not enable participant without keys" taggedAs SecurityTest(
      property = SecureConfiguration,
      asset = "participant node",
      attack = Attack(
        actor = "a domain operator",
        threat = "enables a participant without signing/encryption keys",
        mitigation = "refuse to enable",
      ),
    ) in { implicit env =>
      import env.*

      val signingKey = da.keys.secret.generate_signing_key("some other")
      val encryptionKey = da.keys.secret.generate_encryption_key("some other")
      val pid = ParticipantId(da.id.unwrap.copy(id = Identifier.tryCreate("other")))
      da.topology.participant_domain_states.authorize(
        TopologyChangeOp.Add,
        da.id,
        pid,
        RequestSide.To,
      )

      def enable() = {
        da.participants.active(pid) shouldBe false
        da.topology.participant_domain_states.authorize(
          TopologyChangeOp.Add,
          da.id,
          pid,
          RequestSide.From,
        )
      }

      clue("not initialised without any key") {
        assertThrowsAndLogsCommandFailures(
          enable(),
          _.shouldBeCantonErrorCode(DomainTopologyManagerError.ParticipantNotInitialized),
        )
      }

      da.topology.owner_to_key_mappings.authorize(
        TopologyChangeOp.Add,
        pid,
        signingKey.fingerprint,
        KeyPurpose.Signing,
      )

      clue("signing key is not enough") {
        assertThrowsAndLogsCommandFailures(
          enable(),
          _.shouldBeCantonErrorCode(DomainTopologyManagerError.ParticipantNotInitialized),
        )
      }

      da.topology.owner_to_key_mappings.authorize(
        TopologyChangeOp.Add,
        pid,
        encryptionKey.fingerprint,
        KeyPurpose.Encryption,
      )

      enable()

    }

    "export and import secret keys" in { implicit env =>
      import env.*

      val key1P = participant1.keys.secret.generate_signing_key("export")
      val keyPair1 = participant1.keys.secret.download(key1P.fingerprint, testedProtocolVersion)

      clue("can import keys") {
        participant2.keys.secret.upload(keyPair1, Some("IMPORTED"))
      }

      participant2.keys.secret.list(key1P.fingerprint.unwrap) should not be empty
    }

    "not upload overly long stuff" taggedAs SecurityTest(
      property = Availability,
      asset = "topology manager",
      attack = Attack(
        actor = "a Canton operator",
        threat = "upload an excessively long topology transaction",
        mitigation = "gracefully reject the transaction",
      ),
    ) in { implicit env =>
      import env.*
      val crap = ByteString.copyFrom((1 to 6000000).map(x => x.toByte).toArray)
      assertThrowsAndLogsCommandFailures(
        participant1.topology.load_transaction(crap),
        _.shouldBeCantonErrorCode(ProtoDeserializationFailure),
      )

    }

    "fix broken auth chains" taggedAs SecurityTest(
      property = Availability,
      asset = "topology manager",
      attack = Attack(
        actor = "a Canton operator",
        threat = "breaks an auth chain",
        mitigation = "repair the auth chain",
      ),
    ) in { implicit env =>
      import env.*

      val key1 = participant1.keys.secret.generate_signing_key()
      val partyId = PartyId(participant1.uid.copy(id = Identifier.tryCreate("cascading")))

      def authorizeNs(op: TopologyChangeOp) =
        participant1.topology.namespace_delegations.authorize(
          op,
          participant1.uid.namespace.fingerprint,
          key1.fingerprint,
          isRootDelegation = false,
        )

      authorizeNs(TopologyChangeOp.Add)
      participant1.topology.party_to_participant_mappings.authorize(
        TopologyChangeOp.Add,
        partyId,
        participant1,
        RequestSide.Both,
        ParticipantPermission.Submission,
        Some(key1.fingerprint),
      )

      def getMappings() =
        da.parties.list(filterParty = partyId.filterString).filter(_.participants.nonEmpty)

      // should appear
      eventually() {
        getMappings() should not be empty
      }
      // cascading revoke
      clue("cascading removal") {
        authorizeNs(TopologyChangeOp.Remove)
      }
      // should disappear
      eventually() {
        getMappings() shouldBe empty
      }
      // cascading re-enable
      authorizeNs(TopologyChangeOp.Add)
      eventually() {
        getMappings() should not be empty
      }
    }

    "query namespace delegations" in { implicit env =>
      import env.*

      val key1 = participant1.keys.secret.generate_signing_key("ns-test1")
      val key2 = participant1.keys.secret.generate_signing_key("ns-test2")

      val preTimestamp = environment.clock.now

      Seq(key1, key2).map(key =>
        participant1.topology.namespace_delegations.authorize(
          TopologyChangeOp.Add,
          key.fingerprint,
          key.fingerprint,
          isRootDelegation = true,
          signedBy = Some(key.fingerprint),
        )
      )

      eventually() {
        // we should see both
        val all = participant1.topology.namespace_delegations
          .list(da.id.filterString)
          .map(_.item.namespace.fingerprint)
        forAll(Seq(key1, key2)) { key =>
          all should contain(key.fingerprint)
        }
        // filtering should work
        participant1.topology.namespace_delegations
          .list(da.id.filterString, filterNamespace = key1.fingerprint.unwrap)
          .map(_.item.namespace.fingerprint) shouldBe Seq(key1.fingerprint)

      }

      val timestamp = env.environment.clock.now

      // remove
      Seq(key1, key2).map(key =>
        participant1.topology.namespace_delegations.authorize(
          TopologyChangeOp.Remove,
          key.fingerprint,
          key.fingerprint,
          isRootDelegation = true,
          signedBy = Some(key.fingerprint),
        )
      )

      eventually() {
        val known = participant1.topology.namespace_delegations
          .list(da.id.filterString, useStateStore = true)
          .map(_.item.namespace.fingerprint)
        forAll(Seq(key1.fingerprint, key2.fingerprint)) { fp =>
          known should not contain (fp)
        }
      }

      // querying for snapshots should work
      val sp = participant1.topology.namespace_delegations
        .list(
          da.id.filterString,
          timeQuery = TimeQuery.Snapshot(timestamp),
          filterNamespace = key1.fingerprint.unwrap,
        )
        .map(_.item.namespace.fingerprint)
      sp shouldBe Seq(key1.fingerprint)

      // add and remove txs should be found
      val fnd = participant1.topology.namespace_delegations
        .list(
          da.id.filterString,
          useStateStore = false,
          timeQuery = TimeQuery.Range(Some(preTimestamp), Some(environment.clock.now)),
          filterNamespace = key1.fingerprint.unwrap,
        )
        .map { rr =>
          (rr.context.operation, rr.item.namespace.fingerprint)
        }
      fnd.toSet shouldBe Set(
        (TopologyChangeOp.Add, key1.fingerprint),
        (TopologyChangeOp.Remove, key1.fingerprint),
      )

      // finding removals should work as well
      val fnd2 = participant1.topology.namespace_delegations
        .list(
          da.id.filterString,
          useStateStore = false,
          timeQuery = TimeQuery.Range(Some(preTimestamp), Some(environment.clock.now)),
          operation = Some(TopologyChangeOp.Remove),
          filterNamespace = key1.fingerprint.unwrap,
        )
        .map { rr =>
          (rr.context.operation, rr.item.namespace.fingerprint)
        }
      fnd2 shouldBe Seq((TopologyChangeOp.Remove, key1.fingerprint))

    }

    "query identifier delegations" in { implicit env =>
      import env.*

      val key = participant1.keys.secret.generate_signing_key()
      participant1.topology.identifier_delegations.authorize(
        TopologyChangeOp.Add,
        participant1.uid,
        key.fingerprint,
      )
      eventually() {
        participant1.topology.identifier_delegations
          .list(
            filterUid = participant1.filterString
          )
          .map(_.item.target) should contain(key)
      }
    }

    "query owner to key mappings" in { implicit env =>
      import env.*

      val key = participant1.keys.secret.generate_signing_key()
      participant1.topology.owner_to_key_mappings.authorize(
        TopologyChangeOp.Add,
        participant1.id,
        key.fingerprint,
        KeyPurpose.Signing,
      )

      eventually() {
        participant1.topology.owner_to_key_mappings.list(
          filterKeyOwnerUid = participant1.filterString,
          filterKeyOwnerType = Some(SequencerId.Code),
        ) shouldBe empty
        participant1.topology.owner_to_key_mappings
          .list(
            filterKeyOwnerUid = participant1.filterString,
            filterKeyOwnerType = Some(ParticipantId.Code),
            filterKeyPurpose = Some(KeyPurpose.Encryption),
          )
          .map(_.item.key.fingerprint) should not contain (key.fingerprint)

        val items = participant1.topology.owner_to_key_mappings
          .list(
            filterKeyOwnerUid = participant1.filterString,
            filterKeyOwnerType = Some(ParticipantId.Code),
            filterKeyPurpose = Some(KeyPurpose.Signing),
          )
          .map(_.item.key.fingerprint)
        items should contain(key.fingerprint)
      }
    }

    "query party to participant mappings" in { implicit env =>
      import env.*

      participant1.topology.party_to_participant_mappings.authorize(
        TopologyChangeOp.Add,
        PartyId(participant1.uid.copy(id = Identifier.tryCreate("Bertram"))),
        participant1.id,
      )

      eventually() {
        participant1.topology.party_to_participant_mappings.list(
          filterParty = "Bertram",
          filterParticipant = participant1.id.filterString,
          filterRequestSide = Some(RequestSide.Both),
          filterPermission = Some(ParticipantPermission.Submission),
        ) should not be empty
        participant1.topology.party_to_participant_mappings.list(
          filterParty = "Bertram",
          filterParticipant = participant2.id.filterString,
        ) shouldBe empty
        participant1.topology.party_to_participant_mappings.list(
          filterParty = "Bertram",
          filterRequestSide = Some(RequestSide.From),
        ) shouldBe empty
        participant1.topology.party_to_participant_mappings.list(
          filterParty = "Bertram",
          filterPermission = Some(ParticipantPermission.Observation),
        ) shouldBe empty
      }

    }

    "issue topology transactions concurrently" in { implicit env =>
      import env.*

      val partiesF = (1 to 100).map { idx =>
        Future {
          blocking {
            val partyId = PartyId(participant1.uid.copy(id = Identifier.tryCreate(s"party$idx")))
            participant1.topology.party_to_participant_mappings.authorize(
              TopologyChangeOp.Add,
              partyId,
              participant1.id,
            )
            partyId
          }
        }
      }
      val parties = Await.result(Future.sequence(partiesF), 300.seconds).map(_.uid.id.unwrap).toSet
      eventually(timeUntilSuccess = 60.seconds) {
        val registered =
          participant1.topology.party_to_participant_mappings
            .list("da")
            .map(_.item.party.uid.id.unwrap)
            .toSet
        (parties -- registered) shouldBe empty
      }

    }

    "not use keys that do not exist locally" taggedAs SecurityTest(
      property = Privacy,
      asset = "topology manager",
      attack = Attack(
        actor = "a Canton operator",
        threat = "use a key of a different node",
        mitigation = "ensure that a node can only use its own keys",
      ),
    ) in { implicit env =>
      import env.*

      // we can ping back and forth
      participant1.health.maybe_ping(participant2) shouldBe defined

      // create key unknown to p2
      val key = participant1.keys.secret.generate_encryption_key("test-export")
      participant2.keys.public.upload(key.toByteString(testedProtocolVersion), Some("test-import"))

      // create idm certificate for p1 namespace for p2 (so we can test force=false) command failures
      val key2 = participant2.keys.secret.generate_signing_key("some signing key")
      participant1.keys.public.upload(key2.toByteString(testedProtocolVersion), Some("p2-signing"))
      val nsds = participant1.topology.namespace_delegations
        .list(filterStore = "Authorized")
        .map(_.context.serialized)
      nsds.foreach(participant2.topology.load_transaction)
      val nsd = participant1.topology.namespace_delegations
        .authorize(
          TopologyChangeOp.Add,
          participant1.id.uid.namespace.fingerprint,
          key2.fingerprint,
        )
      participant2.topology.load_transaction(nsd)

      // create another encryption key that does not exist on p1
      val keyEnc = participant2.keys.secret.generate_encryption_key("encryption-for-p1")

      // test that we can not authorize an unknown key for the given participant
      loggerFactory.assertThrowsAndLogs[CommandFailure](
        participant2.topology.owner_to_key_mappings.authorize(
          TopologyChangeOp.Add,
          participant2.id,
          key.fingerprint,
          key.purpose,
          force = false,
        ),
        // client failure
        _.shouldBeCantonErrorCode(
          ParticipantTopologyManagerError.DangerousKeyUseCommandRequiresForce
        ),
      )

      // test that we can not authorize for another participant without force
      loggerFactory.assertThrowsAndLogs[CommandFailure](
        participant2.topology.owner_to_key_mappings.authorize(
          TopologyChangeOp.Add,
          participant1.id,
          keyEnc.fingerprint,
          keyEnc.purpose,
          force = false,
        ),
        // client failure
        _.shouldBeCantonErrorCode(
          ParticipantTopologyManagerError.DangerousKeyUseCommandRequiresForce
        ),
      )

      // remove any encryption key p1 might have
      participant1.topology.owner_to_key_mappings
        .list(
          filterStore = "Authorized",
          filterKeyOwnerUid = participant1.filterString,
          filterKeyPurpose = Some(KeyPurpose.Encryption),
        )
        .map(_.item.key)
        .foreach { key =>
          participant1.topology.owner_to_key_mappings.authorize(
            TopologyChangeOp.Remove,
            participant1,
            key.fingerprint,
            key.purpose,
            force = true,
          )
        }
      // test that we get alerted if someone assigns a key that we do not have
      loggerFactory.assertLogs(
        {
          participant2.topology.owner_to_key_mappings.authorize(
            TopologyChangeOp.Add,
            participant1.id,
            keyEnc.fingerprint,
            keyEnc.purpose,
            force = true,
          )

          def syncOnKeys(p: ParticipantReference) = eventually() {
            val myKeys = p.topology.owner_to_key_mappings
              .list(
                filterStore = da.id.filterString,
                filterKeyOwnerUid = participant1.id.filterString,
              )
              .map(_.item.key.fingerprint)
            myKeys should contain(keyEnc.fingerprint)
          }

          syncOnKeys(participant1)
          // sync on keys so that p2 has seen the change before submitting a ping ...
          syncOnKeys(participant2)
        },
        // MissingKeyAlerter will let us know if there is an issue
        _.errorMessage should include("but this key is not present"),
      )

      // Note: if I run a ping now, I will break P1 (would need to ignore the poison pill)
      // See IgnoreSequencedEventsIntegrationTest
      // Not ignoring events right here, because this test has a running acs commitment processor and that may cause flakes.
      // participant2.health.maybe_ping(participant1) shouldBe empty

      // now, add the encryption key
      val privateKey = participant2.keys.secret.download(keyEnc.fingerprint, testedProtocolVersion)
      participant1.keys.secret.upload(privateKey, None)

      // and ping should pass
      participant2.health.ping(participant1)

    }

    "needs force to remove the last key" in { implicit env =>
      import env.*

      def remove(force: Boolean, current: ListOwnerToKeyMappingResult) =
        participant1.topology.owner_to_key_mappings.authorize(
          TopologyChangeOp.Remove,
          participant1.id,
          current.item.key.fingerprint,
          KeyPurpose.Signing,
          force = force,
        )

      def all: Seq[ListOwnerToKeyMappingResult] = participant1.topology.owner_to_key_mappings
        .list(
          filterStore = "Authorized",
          filterKeyOwnerUid = participant1.id.filterString,
          filterKeyPurpose = Some(KeyPurpose.Signing),
        )

      all.drop(1).toList.map(current => remove(force = false, current))

      eventually() {
        all.size == 1
      }

      val current = all.headOption
        .getOrElse(sys.error("can not get current key"))

      // bails if i don't force it
      assertThrowsAndLogsCommandFailures(
        remove(force = false, current),
        _.shouldBeCantonErrorCode(TopologyManagerError.RemovingLastKeyMustBeForced),
      )
      remove(force = true, current)

      eventually() {
        participant1.topology.owner_to_key_mappings
          .list(filterKeyOwnerUid = participant1.id.filterString)
          .filter(_.item.key.fingerprint == current.item.key.fingerprint) shouldBe empty
      }
    }
  }
}

//class TopologyManagementIntegrationTestDefault extends TopologyManagementIntegrationTest //TODO(i9565): beware -- in-memory integration tests can be flaky due to a known issue

class TopologyManagementIntegrationTestPostgres extends TopologyManagementIntegrationTest {
  registerPlugin(new UsePostgres(loggerFactory))
}

//class TopologyManagementIntegrationTestOracle extends TopologyManagementIntegrationTest {
//  registerPlugin(new UseOracle(loggerFactory))
//}
