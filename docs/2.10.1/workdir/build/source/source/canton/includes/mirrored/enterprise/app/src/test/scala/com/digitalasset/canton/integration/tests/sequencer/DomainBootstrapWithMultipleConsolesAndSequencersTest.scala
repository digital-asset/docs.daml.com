// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.sequencer

import better.files.File
import com.digitalasset.canton.admin.api.client.data.StaticDomainParameters
import com.digitalasset.canton.crypto.SigningPublicKey
import com.digitalasset.canton.domain.sequencing.sequencer.SequencerSnapshot
import com.digitalasset.canton.integration.tests.DomainBootstrapWithSeparateConsolesTest
import com.digitalasset.canton.topology.SequencerId
import com.digitalasset.canton.topology.store.StoredTopologyTransactions
import com.digitalasset.canton.topology.transaction.TopologyChangeOp

import scala.concurrent.duration.DurationInt

trait DomainBootstrapWithMultipleConsolesAndSequencersTest
    extends DomainBootstrapWithSeparateConsolesTest {

  "Nodes in separate consoles after bootstrapping" should {
    "be able to onboard a second sequencer also on a separate console" in { implicit env =>
      import env.*
      val secondSequencer = env.sequencers.local(1)

      val domainId = domainManager1.id
      val sequencerId = SequencerId(domainId)

      // the process below is equivalent to calling domainManager1.setup.onboard_new_sequencer(sequencer, secondSequencer)
      // this is not supported by the DB sequencer, that's why it's not part of the base DomainBootstrapWithSeparateConsolesTest
      for {
        pFile <- File.temporaryFile("params-file", ".proto")
        f1 <- File.temporaryFile("file1", ".proto")
        f2 <- File.temporaryFile("file2", ".proto")
      } yield {
        val paramsFile = pFile.canonicalPath
        val file1 = f1.canonicalPath
        val file2 = f2.canonicalPath

        // user-manual-entry-begin: DynamicallyOnboardSequencerWithSeparateConsoles

        // Second sequencer's console: write signing key to file
        {
          secondSequencer.keys.secret
            .generate_signing_key(s"${secondSequencer.name}-signing")
            .writeToFile(file1)
        }

        // Domain manager's console: write domain params and current topology
        {
          domainManager1.service.get_static_domain_parameters.writeToFile(paramsFile)

          val sequencerSigningKey = SigningPublicKey.tryReadFromFile(file1)

          domainManager1.setup.helper.authorizeKey(
            sequencerSigningKey,
            s"${secondSequencer.name}-signing",
            sequencerId,
          )

          domainManager1.setup.helper.waitForKeyAuthorizationToBeSequenced(
            sequencerId,
            sequencerSigningKey,
          )

          domainManager1.topology.all
            .list(domainId.filterString)
            .collectOfType[TopologyChangeOp.Positive]
            .writeToFile(file1)
        }

        // Initial sequencer's console: read topology and write snapshot to file
        {
          val topologySnapshotPositive =
            StoredTopologyTransactions
              .tryReadFromFile(file1)
              .collectOfType[TopologyChangeOp.Positive]

          val sequencingTimestamp = topologySnapshotPositive.lastChangeTimestamp.getOrElse(
            sys.error("topology snapshot is empty")
          )

          sequencer.sequencer.snapshot(sequencingTimestamp).writeToFile(file2)
        }

        // Second sequencer's console: read topology, snapshot and domain params
        {
          val topologySnapshotPositive =
            StoredTopologyTransactions
              .tryReadFromFile(file1)
              .collectOfType[TopologyChangeOp.Positive]

          val state = SequencerSnapshot.tryReadFromFileUnsafe(file2)

          val domainParameters = StaticDomainParameters.tryReadFromFile(paramsFile)

          secondSequencer.initialization
            .initialize_from_snapshot(
              domainId,
              topologySnapshotPositive,
              state,
              domainParameters,
            )
            .publicKey

          secondSequencer.health.initialized() shouldBe true

        }

        // user-manual-entry-end: DynamicallyOnboardSequencerWithSeparateConsoles
      }

      participant2.domains.connect_local(secondSequencer)
      participant1.health.ping(participant2, timeout = 30.seconds)
    }
  }
}
