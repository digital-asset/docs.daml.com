// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests

import com.digitalasset.canton.SequencerAlias
import com.digitalasset.canton.console.CommandFailure
import com.digitalasset.canton.console.commands.DomainChoice
import com.digitalasset.canton.integration.IntegrationTestUtilities.*
import com.digitalasset.canton.integration.*
import com.digitalasset.canton.integration.plugins.UsePostgres
import com.digitalasset.canton.participant.domain.{DomainConnectionConfig, DomainRegistryError}
import com.digitalasset.canton.participant.sync.LedgerSyncEvent
import com.digitalasset.canton.sequencing.{GrpcSequencerConnection, SequencerConnections}
import com.digitalasset.canton.topology.*
import com.digitalasset.canton.topology.transaction.{ParticipantPermission, TrustLevel}
import com.google.protobuf.ByteString

import scala.concurrent.duration.*

trait MultiDomainIntegrationTests
    extends EnterpriseIntegrationTest
    with IsolatedEnterpriseEnvironments
    with EnterpriseHasCycleUtils {
  override lazy val environmentDefinition: EnterpriseEnvironmentDefinition =
    EnterpriseEnvironmentDefinition.multiDomain

  private val expectedPingTransactionCount =
    IntegrationTestUtilities.expectedGrabbedCountsForBong(0).acceptedTransactionCount

  "run domain connectivity commands" in { implicit env =>
    import env.*
    {
      val (domainStatus, participantStatus) = health.status().tupled
      assertResult(domainStatus.size)(2)
      assertResult(participantStatus.size)(4)
    }

    val p2Id = participant2.id

    assertResult(List())(participant2.domains.list_registered())

    eventually() {
      acme.health.initialized() shouldBe true
    }

    participant2.domains.connect_local(acme, manualConnect = true)

    val hostname = "localhost"
    val port = acme.config.publicApi.port.unwrap
    val certs = acme.config.publicApi.tls.map(_.certChainFile.unwrap.getPath).value

    // architecture-handbook-entry-begin: TlsConnect
    participant3.domains.connect(
      domainAlias = "acme",
      connection = s"https://$hostname:$port",
      certificatesPath = certs, // path to certificate chain file (.pem) of server
    )
    // architecture-handbook-entry-end: TlsConnect

    // self ping should work (and warm-up the system)
    eventually() {
      assertPingSucceeds(participant3, participant3)
    }

    assertResult(1)(participant2.domains.list_registered().length)
    assertResult(0)(participant2.domains.list_connected().length)

    // Ping should not work before connected to the same domain
    loggerFactory.suppressWarningsAndErrors {
      participant3.health.maybe_ping(participant2.id, 500.millis) should not be defined
    }

    // Ping should work after connected to the same domain
    participant2.domains.reconnect("acme")
    eventually() {
      assertResult(1)(participant2.domains.list_connected().length)
    }
    eventually() {
      participant3.parties.list(filterParty = p2Id.adminParty.filterString) should not be empty
    }
    assertPingSucceeds(participant3, participant2)

    // wait for pong contract to be archived by participant3 (such that we don't get a "GRPC disconnect error
    // printed to the log)
    eventually() {
      participant3.testing.pcs_search(
        "acme",
        filterTemplate = "PingPong:Pong",
        activeSet = true,
      ) shouldBe empty
      participant3.testing.pcs_search("acme", filterTemplate = "PingPong:Pong") should not be empty
    }

    participant2.domains.disconnect("acme")
    eventually() {
      assertResult(0)(participant2.domains.list_connected().length)
    }
    loggerFactory.suppressWarningsAndErrors {
      eventually() {
        participant3.health.maybe_ping(participant2.id, 500.millis) should not be defined
      }
    }
    participant3.testing.pcs_search(
      "acme",
      filterTemplate = "NOTHING",
      filterId = "VERYUNLIKELY",
    ) shouldBe empty
    val tests = Map(
      "Ping" -> true,
      "ingPong:Ping" -> true,
      "ingPong:Pin" -> true,
      "RADEBRECHT" -> false,
      "^PingPong:Ping" -> true,
      "^PingPong:Pin" -> true,
      "^ingPong" -> false,
      "!ingPong:Ping" -> false,
      "!PingPong:Ping" -> true,
      "!PingPong:Pin" -> false,
    )
    tests.foreach { kv =>
      val tst = participant3.testing.pcs_search("acme", filterTemplate = kv._1)
      assert(tst.nonEmpty == kv._2, kv._1)
    }

    participant3.domains.disconnect("acme")
    assertResult(0)(participant3.domains.list_connected().length)
    participant3.domains.reconnect("acme")
    assertResult(1)(participant3.domains.list_connected().length)

    participant2.domains.reconnect("acme")
    assertResult(1)(participant2.domains.list_connected().length)

    assertPingSucceeds(participant3, participant2)

    eventually() {
      participant3.testing.pcs_search(
        "acme",
        filterTemplate = "PingPong:Pong",
        activeSet = true,
      ) shouldBe empty
      participant3.testing.pcs_search("acme", filterTemplate = "PingPong:Pong") should not be empty
    }

    eventually() {
      val (domainStatus, participantStatus) = health.status().tupled
      domainStatus(acme.name).connectedParticipants should contain(
        participantStatus(participant2.name).id
      )
      participantStatus(participant2.name).connectedDomains should contain(
        domainStatus(acme.name).id -> true
      )
    }

    loggerFactory.suppressWarningsAndErrors {
      acme.participants.set_state(p2Id, ParticipantPermission.Disabled, TrustLevel.Ordinary)

      eventually() {
        val (domainStatus, participantStatus) = health.status().tupled
        domainStatus(acme.name).connectedParticipants should not contain participantStatus(
          participant2.name
        ).id
        participantStatus(participant2.name).connectedDomains should not contain (domainStatus(
          acme.name
        ).id -> true)
      }
    }
  }

  "run a simple workflow" in { implicit env =>
    import env.*

    val p1Id = participant1.id

    participant1.domains.connect_local(da)
    participant2.domains.connect_local(da)
    participant1.domains.connect_local(acme)
    participant3.domains.connect_local(acme)

    participant1.parties.enable("Alice")
    participant1.parties.enable("Alice2")
    participant1.parties.enable("Bank", waitForDomain = DomainChoice.All)
    participant2.parties.enable("Painter")
    participant2.parties.enable("Carol", waitForDomain = DomainChoice.All)

    val hash = participants.all.dars.upload(CantonExamplesPath).values.headOption.value
    participant1.dars.download(hash, "./enterprise/app/target/")
    participant2.dars.upload(CantonExamplesPath)

    val packagesP1 = participant1.packages.list()
    packagesP1 should not be empty

    participant1.ledger_api.packages.upload_dar(CantonTestsPath)
    val newPackagesP1 = participant1.packages.list()
    newPackagesP1.size should be > packagesP1.size

    val packageId0 = packagesP1.headOption.getOrElse(fail("No packages on participant1")).packageId
    participant1.packages.list_contents(packageId0) should not be empty

    participant1.dars.list() should not be empty

    val p1UnrelatedEvents = participant1.testing
      .event_search()
      .map { case (_, tsEvent) => tsEvent.event }
      .collect { case ev: LedgerSyncEvent.TransactionAccepted => ev }
      .length

    // verify participants can ping each other
    assertPingSucceeds(participant1, participant2)
    assertPingSucceeds(participant3, participant1)
    assertPingSucceeds(participant1, participant1)

    // check that event_search works across domains
    val p1Txs =
      participant1.testing
        .event_search()
        .map { case (_, tsEvent) => tsEvent.event }
        .collect { case ev: LedgerSyncEvent.TransactionAccepted => ev }
    p1Txs.length shouldBe 9 + p1UnrelatedEvents

    // send bong (concurrent ping)
    participant1.testing.bong(Set(participant1.id, participant2.id))

    // change participant state (trust level Ordinary -> Vip)
    da.participants.set_state(p1Id, ParticipantPermission.Submission, TrustLevel.Vip)

    // list parties on domains
    eventually() {
      da.parties.list(filterParty = "Alice") should have length (2)
      acme.parties.list(
        filterParty = "Alice",
        asOf = Some(java.time.Instant.now),
      ) should have length (2)
      // list parties on participant
      val participantParties = participant1.parties.list("Alice")
      participantParties should have length (2)
      participantParties.flatMap(_.participants).flatMap(_.domains) should have length (4)
    }

    // list participants
    val domainParticipants = da.keys.public.list_owners(
      filterKeyOwnerUid = "",
      filterKeyOwnerType = Some(ParticipantId.Code),
      filterDomain = "",
      Some(java.time.Instant.now),
    )
    val participantParticipants = participant2.keys.public.list_owners(
      filterKeyOwnerUid = "participant",
      filterKeyOwnerType = Some(ParticipantId.Code),
      filterDomain = "da",
      None,
    )
    domainParticipants.size shouldBe participantParticipants.size

    // create new key
    val genKey = participant1.keys.secret.generate_signing_key("new-participant1")
    val fingerprint = genKey.fingerprint.unwrap

    // download new key from participant
    val newKey =
      participant1.keys.secret.list(fingerprint).headOption.value.publicKey

    // upload key to domain
    da.keys.public.upload(newKey.toByteString(testedProtocolVersion), None)

    // download key again from domain
    da.keys.public.list(fingerprint).size shouldBe 1

    // run ledger-api commands
    participant1.ledger_api.transactions.end()

    // test create and exercise
    eventually() {
      participant1.testing.acs_search(domainAlias = "da", filterTemplate = "Pong") shouldBe empty
    }

    runCycle(p1Id.adminParty, participant1, participant1)

    stopAll()

  }

  "select a domain for ping" in { implicit env =>
    import env.*

    participant1.domains.connect_local(da)
    participant2.domains.connect_local(da)
    participant1.domains.connect_local(acme)
    participant2.domains.connect_local(acme)

    val p1InitialCounts = grabCounts(da, participant1)
    val p2InitialCounts = grabCounts(da, participant2)

    assertPingSucceeds(participant1, participant2, workflowId = "da")

    eventually() {
      val p1Counts = grabCounts(da, participant1)
      val p2Counts = grabCounts(da, participant2)
      assertResult(expectedPingTransactionCount)(
        p1Counts.acceptedTransactionCount - p1InitialCounts.acceptedTransactionCount
      )
      assertResult(p1Counts.plus(p2InitialCounts))(p2Counts.plus(p1InitialCounts))
    }

    assertPingSucceeds(participant1, participant2, workflowId = "acme")

    eventually() {
      val p1Counts = grabCounts(acme, participant1)
      val p2Counts = grabCounts(acme, participant2)
      assertResult(expectedPingTransactionCount)(
        p1Counts.acceptedTransactionCount - p1InitialCounts.acceptedTransactionCount
      )
      assertResult(p1Counts.plus(p2InitialCounts))(p2Counts.plus(p1InitialCounts))
    }
  }

  "choose the domain for a ping deterministically" in { implicit env =>
    import env.*

    // Domains have equal priority, so the alphabetically first domain `acme` should always be chosen
    val expectedDomain = List(acme, da).minByOption(x => x.id.toProtoPrimitive).value

    participant1.domains.connect_local(da)
    participant2.domains.connect_local(da)
    participant1.domains.connect_local(acme)
    participant2.domains.connect_local(acme)

    val p1InitialCounts = grabCounts(expectedDomain, participant1)
    val p2InitialCounts = grabCounts(expectedDomain, participant2)

    assertPingSucceeds(participant1, participant2)

    eventually() {
      val p1Counts = grabCounts(expectedDomain, participant1)
      val p2Counts = grabCounts(expectedDomain, participant2)
      assertResult(expectedPingTransactionCount)(
        p1Counts.acceptedTransactionCount - p1InitialCounts.acceptedTransactionCount
      )
      assertResult(p1Counts.plus(p2InitialCounts))(p2Counts.plus(p1InitialCounts))
    }
  }

  "restart and deal with stopped domains" in { implicit env =>
    import env.*

    participant1.domains.connect_local(da)
    participant1.domains.connect_local(acme)

    withClue("Stopping participant and domain") {
      participant1.stop()
      acme.stop()
    }

    withClue("Restarting participant1") {
      participant1.start()
      // try a manual connect
      assertThrowsAndLogsCommandFailures(
        participant1.domains.reconnect("acme", retry = false),
        _.commandFailureMessage should include(
          DomainRegistryError.ConnectionErrors.DomainIsNotAvailable.id
        ),
      )
    }

    // try a reconnect
    loggerFactory.assertThrowsAndLogs[CommandFailure](
      participant1.domains.reconnect_all(ignoreFailures = false),
      _.commandFailureMessage should include(
        DomainRegistryError.ConnectionErrors.DomainIsNotAvailable.id
      ),
    )

    // set domain to autoConnect = off such that acme is excluded from domains.reconnect()
    participant1.domains.modify("acme", _.copy(manualConnect = true))

    participant1.domains.reconnect_all()
    // shouldn't matter if i call it again
    participant1.domains.reconnect_all()

    participant1.health.maybe_ping(participant1.id) shouldBe defined

  }

  "connecting a single participant terminates only when the connected domain is active" in {
    implicit env =>
      import env.*

      participant1.domains.connect_local(da)
      participant1.domains.active(da.name) shouldBe true

      participant2.domains.register(
        DomainConnectionConfig(
          da.name,
          SequencerConnections.single(da.sequencerConnection),
        )
      )
      participant2.domains.active(da.name) shouldBe true
      participant2.domains.disconnect(da.name)
      participant2.domains.active(da.name) shouldBe false

      participant2.domains.reconnect_all()
      participant2.domains.active(da.name) shouldBe true

      participant3.domains.register(
        DomainConnectionConfig(
          da.name,
          SequencerConnections.single(da.sequencerConnection),
          manualConnect = true,
        )
      )
      participant3.domains.active(da.name) shouldBe false
      participant3.domains.reconnect(da.name)
      participant3.domains.active(da.name) shouldBe true
  }

  "connecting multiple participants terminates only when the connected domain is active" in {
    implicit env =>
      import env.*

      Seq(participant1, participant2).domains.connect_local(da)
      Seq(participant1, participant2).foreach(_.domains.active(da.name) shouldBe true)

      Seq(participant3, participant4).domains
        .register(
          DomainConnectionConfig(
            da.name,
            SequencerConnections.single(da.sequencerConnection),
          )
        )
      Seq(participant3, participant4).foreach(_.domains.active(da.name) shouldBe true)
      Seq(participant3, participant4).domains.disconnect(da.name)
      Seq(participant3, participant4).foreach(_.domains.active(da.name) shouldBe false)
      Seq(participant3, participant4).domains.reconnect_all()
      Seq(participant3, participant4).foreach(_.domains.active(da.name) shouldBe true)

      val acmeCertificate = acme.sequencerConnection match {
        case grpc: GrpcSequencerConnection =>
          grpc.customTrustCertificates.getOrElse(ByteString.EMPTY)
        case _ => fail()
      }
      Seq(participant1, participant2).domains
        .register(
          DomainConnectionConfig(
            acme.name,
            SequencerConnections.single(acme.sequencerConnection),
            manualConnect = true,
          )
            .withCertificates(SequencerAlias.Default, acmeCertificate)
        )
      Seq(participant1, participant2).foreach(_.domains.active(acme.name) shouldBe false)
      Seq(participant1, participant2).domains.reconnect(acme.name)
      Seq(participant1, participant2).foreach(_.domains.active(acme.name) shouldBe true)
  }
}

//class MultiDomainIntegrationTestsDefault extends MultiDomainIntegrationTests

class MultiDomainIntegrationTestsPostgres extends MultiDomainIntegrationTests {
  registerPlugin(new UsePostgres(loggerFactory))
}

//class MultiDomainIntegrationTestsOracle extends MultiDomainIntegrationTests {
//  registerPlugin(new UseOracle(loggerFactory))
//}
