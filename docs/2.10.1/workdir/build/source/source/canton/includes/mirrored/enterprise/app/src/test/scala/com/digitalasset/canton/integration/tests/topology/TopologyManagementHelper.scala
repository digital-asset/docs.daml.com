// Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates.
// Proprietary code. All rights reserved.

package com.digitalasset.canton.integration.tests.topology

import com.digitalasset.canton.BaseTest
import com.digitalasset.canton.console.LocalParticipantReference
import com.digitalasset.canton.crypto.KeyPurpose
import com.digitalasset.canton.integration.tests.EnterpriseTestConsoleEnvironment
import com.digitalasset.canton.topology.*
import com.digitalasset.canton.topology.transaction.{RequestSide, TopologyChangeOp}
import org.scalatest.Assertion

trait TopologyManagementHelper { this: BaseTest =>

  protected case class TopologyKmsKeys(
      namespaceKeyId: Option[String],
      signingKeyId: Option[String],
      encryptionKeyId: Option[String],
  )

  /** Manually generates the necessary keys for a simple distributed domain. Optionally we can
    * register pre-generated KMS keys.
    */
  def manuallyInitDistDomain(
      useKms: Boolean = false,
      kmsKeysDomainManagerO: Option[TopologyKmsKeys] = None,
      kmsKeysSequencerO: Option[TopologyKmsKeys] = None,
      kmsKeysMediatorO: Option[TopologyKmsKeys] = None,
  )(implicit env: EnterpriseTestConsoleEnvironment): Unit = {
    import env.*
    val mydomain_manager = domainManager1
    val mysequencer = sequencer1
    val mymediator = mediator1

    val (namespaceKmsKeyIdDomainManager, signingKmsKeyIdDomainManager) =
      if (useKms) {
        val topologyKeys =
          kmsKeysDomainManagerO.valueOrFail("kmsKeysDomainManagerO must be set if useKms is true")

        topologyKeys.namespaceKeyId
          .valueOrFail(s"domain manager [${mydomain_manager.name}] expects a namespace key id") ->
          topologyKeys.signingKeyId
            .valueOrFail(s"domain manager [${mydomain_manager.name}] expects a signing key id")
      } else "" -> ""

    val signingKmsKeyIdSequencer =
      if (useKms) {
        val topologyKeys =
          kmsKeysSequencerO.valueOrFail("kmsKeysSequencerO must be set if useKms is true")
        topologyKeys.signingKeyId
          .valueOrFail(s"sequencer [${mysequencer.name}] expects a signing key id")
      } else ""

    val signingKmsKeyIdMediator =
      if (useKms) {
        val topologyKeys =
          kmsKeysMediatorO.valueOrFail("kmsKeysMediatorO must be set if useKms is true")
        topologyKeys.signingKeyId
          .valueOrFail(s"sequencer [${mymediator.name}] expects a signing key id")
      } else ""

    // architecture-handbook-entry-begin: ManualInitDistributedDomain

    // create namespace key for the domain manager
    val namespaceKey = if (useKms) {
      mydomain_manager.keys.secret.register_kms_signing_key(
        namespaceKmsKeyIdDomainManager,
        name = mydomain_manager.name + "-namespace",
      )
    } else {
      mydomain_manager.keys.secret
        .generate_signing_key(name = mydomain_manager.name + "-namespace")
    }

    // use the fingerprint of namespace key for our identity
    val namespace = namespaceKey.fingerprint

    // initialise the identity of this domain
    val uid =
      mydomain_manager.topology.init_id(identifier = mydomain_manager.name, fingerprint = namespace)

    // create the root certificate for this namespace
    mydomain_manager.topology.namespace_delegations.authorize(
      ops = TopologyChangeOp.Add,
      namespace = namespace,
      authorizedKey = namespace,
      isRootDelegation = true,
    )

    val protocolVersion = mydomain_manager.config.init.domainParameters.initialProtocolVersion

    // set the initial dynamic domain parameters for the domain
    mydomain_manager.topology.domain_parameters_changes
      .authorize(
        domainId = DomainId(uid),
        newParameters = com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters
          .defaultValues(protocolVersion),
        protocolVersion = protocolVersion,
      )

    // create signing key for the domain manager
    val signingKeyDomainManager =
      if (useKms)
        mydomain_manager.keys.secret.register_kms_signing_key(
          signingKmsKeyIdDomainManager,
          name = mydomain_manager.name + "-signing",
        )
      else
        mydomain_manager.keys.secret
          .generate_signing_key(name = mydomain_manager.name + "-signing")

    // create a topology transaction linking the domain manager to its signing key
    mydomain_manager.topology.owner_to_key_mappings.authorize(
      ops = TopologyChangeOp.Add,
      keyOwner = DomainTopologyManagerId(uid),
      key = signingKeyDomainManager.fingerprint,
      purpose = KeyPurpose.Signing,
    )
    // architecture-handbook-entry-end: ManualInitDistributedDomain

    // this step is mandatory if we want to use KMS with previously generated keys otherwise it can be
    // skipped because `setup.bootstrap_domain()` will generate keys if no keys exist
    if (useKms) {
      mysequencer.keys.secret.register_kms_signing_key(
        signingKmsKeyIdSequencer,
        name = mysequencer.name + "-signing",
      )
      mymediator.keys.secret.register_kms_signing_key(
        signingKmsKeyIdMediator,
        name = mymediator.name + "-signing",
      )
    } else {
      mysequencer.keys.secret.generate_signing_key(name = mysequencer.name + "-signing")
      mymediator.keys.secret.generate_signing_key(name = mymediator.name + "-signing")
    }

    // initialize the remaining external nodes
    mydomain_manager.setup.bootstrap_domain(sequencers.all, Seq(mediator1))
    mydomain_manager.health.wait_for_initialized()

  }

  def manuallyInitEmbeddedDomain(
      useKms: Boolean = false,
      identityKmsKey: Option[String] = None,
      signingKmsKey: Option[String] = None,
  )(implicit env: EnterpriseTestConsoleEnvironment): Assertion = {
    import env.*
    val mydomain = da

    val (identityKmsKeyId, signingKmsKeyId) =
      if (useKms)
        identityKmsKey.valueOrFail("identityKmsKey must be set if useKms is true") ->
          signingKmsKey.valueOrFail("signingKmsKey must be set if useKms is true")
      else
        "" -> ""

    // architecture-handbook-entry-begin: ManualInitDomain

    // first, let's create a signing key that is going to control our identity
    val identityKey =
      if (useKms) {
        mydomain.keys.secret.register_kms_signing_key(
          kmsKeyId = identityKmsKeyId,
          name = mydomain.name + "-namespace",
        )
      } else {
        mydomain.keys.secret.generate_signing_key(name = mydomain.name + "-namespace")
      }

    // create a signing key for this entity
    val signingKey =
      if (useKms) {
        mydomain.keys.secret.register_kms_signing_key(
          kmsKeyId = signingKmsKeyId,
          name = mydomain.name + "-signing",
        )
      } else {
        mydomain.keys.secret.generate_signing_key(name = mydomain.name + "-signing")
      }

    val namespace = identityKey.fingerprint

    // initialise the identity of this domain
    val uid = mydomain.topology.init_id(identifier = mydomain.name, fingerprint = namespace)

    // create the root certificate for this namespace
    mydomain.topology.namespace_delegations.authorize(
      ops = TopologyChangeOp.Add,
      namespace = namespace,
      authorizedKey = namespace,
      isRootDelegation = true,
    )

    val protocolVersion = mydomain.config.init.domainParameters.initialProtocolVersion

    // set the initial dynamic domain parameters for the domain
    mydomain.topology.domain_parameters_changes
      .authorize(
        domainId = DomainId(uid),
        newParameters = com.digitalasset.canton.admin.api.client.data.DynamicDomainParameters
          .defaultValues(protocolVersion),
        protocolVersion = protocolVersion,
      )

    val mediatorId = MediatorId(uid)
    Seq[Member](DomainTopologyManagerId(uid), SequencerId(uid), mediatorId).foreach { keyOwner =>
      // in this case, we are using an embedded domain. therefore, we initialise all domain
      // entities at once. in a distributed setup, the process needs to be invoked on
      // the separate entities, and therefore requires a bit more coordination.
      // however, the steps remain the same.

      // then, create a topology transaction linking the entity to the signing key
      mydomain.topology.owner_to_key_mappings.authorize(
        ops = TopologyChangeOp.Add,
        keyOwner = keyOwner,
        key = signingKey.fingerprint,
        purpose = KeyPurpose.Signing,
      )
    }

    // Register the mediator
    mydomain.topology.mediator_domain_states.authorize(
      ops = TopologyChangeOp.Add,
      domain = mydomain.id,
      mediator = mediatorId,
      side = RequestSide.Both,
    )

    // architecture-handbook-entry-end: ManualInitDomain

    logger.debug("wait until domain is healthy")
    eventually() {
      da.health.initialized() shouldBe true
      da.is_initialized shouldBe true
    }
  }

  def manuallyInitParticipant(
      participant: LocalParticipantReference,
      useKms: Boolean = false,
      kmsKeysO: Option[TopologyKmsKeys] = None,
  ): Unit = {

    val ((namespaceKmsKeyId, signingKmsKeyId), encryptionKmsKeyId) = if (useKms) {
      val kmsKeys = kmsKeysO.valueOrFail("kmsKeysO must be set if useKms is true")
      kmsKeys.namespaceKeyId
        .valueOrFail(s"participant [${participant.name}] expects a namespace key id") ->
        kmsKeys.signingKeyId
          .valueOrFail(s"participant [${participant.name}] expects a signing key id") ->
        kmsKeys.encryptionKeyId
          .valueOrFail(s"participant [${participant.name}] expects an encryption key id")
    } else "" -> "" -> ""

    // architecture-handbook-entry-begin: ManualInitKeys
    /* Create or register three keys:
     * 1. a signing key that is going to control our identity;
     * 2. a signing key;
     * 3. an encryption key to encrypt transactions;
     */
    val ((identityKey, signingKey), encryptionKey) = if (useKms) {
      // user-manual-entry-begin: ManualRegisterKmsKeys
      participant.keys.secret
        .register_kms_signing_key(namespaceKmsKeyId, name = participant.name + "-namespace") ->
        participant.keys.secret
          .register_kms_signing_key(signingKmsKeyId, name = participant.name + "-signing") ->
        participant.keys.secret
          .register_kms_encryption_key(encryptionKmsKeyId, name = participant.name + "-encryption")
      // user-manual-entry-end: ManualRegisterKmsKeys
    } else {
      participant.keys.secret.generate_signing_key(name = participant.name + "-namespace") ->
        participant.keys.secret.generate_signing_key(name = participant.name + "-signing") ->
        participant.keys.secret.generate_encryption_key(name = participant.name + "-encryption")
    }
    // architecture-handbook-entry-end: ManualInitKeys

    // architecture-handbook-entry-begin: ManualInitParticipant

    // use the fingerprint of this key for our identity
    val namespace = identityKey.fingerprint

    // create the root certificate (self-signed)
    participant.topology.namespace_delegations.authorize(
      ops = TopologyChangeOp.Add,
      namespace = namespace,
      authorizedKey = namespace,
      isRootDelegation = true,
    )

    // initialise the id: this needs to happen AFTER we created the namespace delegation
    // (on participants; for the domain, it's the other way around ... sorry for that)
    // if we initialize the identity before we added the root certificate, then the system will
    // complain about not being able to vet the admin workflow packages automatically.
    // that would not be tragic, but would require a manual vetting step.
    // in production, use a "random" identifier. for testing and development, use something
    // helpful so you don't have to grep for hashes in your log files.
    participant.topology.init_id(
      identifier = Identifier.tryCreate("manualInit"),
      fingerprint = namespace,
    )

    // assign new keys to this participant
    Seq(encryptionKey, signingKey).foreach { key =>
      participant.topology.owner_to_key_mappings.authorize(
        ops = TopologyChangeOp.Add,
        keyOwner = participant.id,
        key = key.fingerprint,
        purpose = key.purpose,
      )
    }

    // architecture-handbook-entry-end: ManualInitParticipant

  }
}
