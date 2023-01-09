..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

Manage Dars and Packages
========================

A package is a unit of compiled Daml code corresponding to one Daml project. A DAR is a collection of packages including
a main package and all other packages from the dependencies of this Daml project.

Uploading DARs
--------------

To use a Daml application on a participant, you need to upload it to your participant node. The application always
comes packaged as one or more DARs that need to be uploaded in the order of their dependency. There are two ways to
upload DARs to a Canton node: either via the `Ledger Api <https://docs.daml.com/app-dev/grpc/proto-docs.html#com-daml-ledger-api-v1-packageservice>`__,
or through Canton :ref:`console command <dars.upload>`:

.. code-block:: none

    @ participant2.dars.upload("dars/CantonExamples.dar")
    res1: String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"

Inspecting DARs and Packages
----------------------------

You can get a list of uploaded DARs using:

.. code-block:: none

    @ participant2.dars.list()
    res2: Seq[com.digitalasset.canton.participant.admin.v0.DarDescription] = Vector(
      DarDescription(
        hash = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91",
        name = "CantonExamples"
      ),
      DarDescription(
        hash = "12209d103cff460f77634ed44086a1ecbe9d9f965aa0fdcd318d472731fb9c33a701",
        name = "AdminWorkflowsWithVacuuming"
      )
    )

Please note that the package "AdminWorkflows" is a package that ships with Canton. It contains the Daml templates
used by the ``participant.health.ping`` command.

In order to inspect the contents of the DAR, you need to grab the hash identifying it:

.. code-block:: none

    @ val dars = participant2.dars.list(filterName = "CantonExamples")
    dars : Seq[com.digitalasset.canton.participant.admin.v0.DarDescription] = Vector(
      DarDescription(
        hash = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91",
        name = "CantonExamples"
      )
    )
.. code-block:: none

    @ val hash = dars.head.hash
    hash : String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"

Using that hash, you can inspect the contents of the DAR using:

.. code-block:: none

    @ val darContent = participant2.dars.list_contents(hash)
    darContent : DarMetadata = DarMetadata(
      name = "CantonExamples",
      main = "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6",
      packages = Vector(
        "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6",
        "94f7c83923aa273fb90b907f57385ae951ca1195fb35806275cbd03e9e4faab6",
        "cb0552debf219cc909f51cbb5c3b41e9981d39f8f645b1f35e2ef5be2e0b858a",
        "3f4deaf145a15cdcfa762c058005e2edb9baa75bb7f95a4f8f6f937378e86415",
    ..

You can also directly look at the packages, using:

.. code-block:: none

    @ participant2.packages.list()
    res6: Seq[com.digitalasset.canton.participant.admin.v0.PackageDescription] = Vector(
      PackageDescription(
        packageId = "802458dc13bf773c756bf6bc1f0996623b558fece6a3d483bb87cfacb21f992f",
        sourceDescription = "CantonExamples"
      ),
      PackageDescription(
        packageId = "86828b9843465f419db1ef8a8ee741d1eef645df02375ebf509cdc8c3ddd16cb",
        sourceDescription = "CantonExamples"
    ..

Please note that a DAR can include packages that are already included in other DARs. In particular the Daml standard library
are shipped with every DAR. Therefore, the ``sourceDescription`` will always contain only one textual reference to a DAR.

You can also inspect the content of a package, using:

.. code-block:: none

    @ participant2.packages.list_contents(darContent.main)
    res7: Seq[com.digitalasset.canton.participant.admin.v0.ModuleDescription] = Vector(
      ModuleDescription(name = "CantonExamples"),
      ModuleDescription(name = "ContractKeys"),
      ModuleDescription(name = "SafePaint"),
      ModuleDescription(name = "LockIou"),
      ModuleDescription(name = "Iou"),
      ModuleDescription(name = "Divulgence"),
      ModuleDescription(name = "Paint"),
    ..

.. _package_vetting:

Understanding Package Vetting
-----------------------------

Every participant operator uploads DARs individually to their participant node. There is no global DAR repository
anywhere and participants do not have access to each others DAR repositories. Therefore, for two participants to
synchronise on a transaction that uses packages contained in a certain DAR, we need both participant operators to
have uploaded the same DAR before the transaction was submitted.

If one of the involved participants doesn't know about a certain DAR, then the transaction will bounce with an error
PACKAGE_NO_VETTED_BY_RECIPIENTS.

This error goes back to the fact that both participants not only upload the DAR, but also publicly declare towards
their peers that they are ready to receive transactions referring to certain packages. This declaration happens
automatically when you upload a DAR. The package vettings can be inspected using (preview):

.. code-block:: none

    @ participant2.topology.vetted_packages.list()
    res8: Seq[ListVettedPackagesResult] = Vector(
      ListVettedPackagesResult(
        context = BaseResult(
          domain = "Authorized",
          validFrom = 2023-01-03T23:24:55.911889Z,
          validUntil = None,
          operation = Add,
          serialized = <ByteString@60efbca4 size=2582 contents="\n\223\024\n\301\021\n\274\021\n\271\021\022 vpbp4nXJfMhhM4TXBhQ6a9FeheY5JnTJJ...">,
    ..

Vetting is necessary, as otherwise, a malicious participant might send a transaction referring to package a receiver
does not have, which would make it impossible for the receiver to process the transaction, leading to a ledger fork.
As transactions are valid only if all involved participants have vetted the used packages, this attack cannot happen.

Removing Packages and DARs
--------------------------

.. note::

    Note that package and DAR removal is under active development. The behaviour described in this documentation may
    change in the future. Package and DAR removal is a preview feature and should not be used in production.

Canton supports removal of both packages and DARs that are no longer in use. Removing unused packages and DARs has the following advantages:

- Freeing up storage

- Preventing accidental use of the old package / DAR

- Reducing the number of packages / DARs that are trusted and may potentially have to be audited



Certain conditions must to be met in order to remove packages or DARs. These conditions are designed to prevent removal of packages or DARs that are currently in use.
The rest of this page describes the requirements.

Removing DARs
~~~~~~~~~~~~~

The following checks are performed before a DAR can be removed:

- The main package of the DAR must be unused -- there should be no active contract from this package

- All package dependencies of the DAR should either be unused or contained in another of the participant node's uploaded DARs. Canton uses this restriction to ensure that the package dependencies of the DAR don't become "stranded" if they're in use.

- The main package of the dar should not be vetted. If it is vetted, Canton will try to automatically revoke the vetting for the main package of the DAR, but this automatic vetting revocation will only succeed if the main package vetting originates from a standard ``dars.upload``. Even if the automatic revocation fails, you can always manually revoke the package vetting.

The following tutorial shows how to remove a DAR with the Canton console. The first step is to upload a DAR so that
we have one to removed. Additionally, store the packages that are present before the DAR is uploaded, as these can be
used to double-check that DAR removal reverts to a clean state.

.. code-block:: none

    @ val packagesBefore = participant1.packages.list().map(_.packageId).toSet
    packagesBefore : Set[String] = HashSet(
      "86828b9843465f419db1ef8a8ee741d1eef645df02375ebf509cdc8c3ddd16cb",
      "5921708ce82f4255deb1b26d2c05358b548720938a5a325718dc69f381ba47ff",
      "cc348d369011362a5190fe96dd1f0dfbc697fdfd10e382b9e9666f0da05961b7",
      "4776964ad90aa11ec8e82abc3e5d989bc63e94f84b185e1dd9895b7e5d97ad7e",
      "6839a6d3d430c569b2425e9391717b44ca324b88ba621d597778811b2d05031d",
      "99a2705ed38c1c26cbb8fe7acf36bbf626668e167a33335de932599219e0a235",
      "e22bce619ae24ca3b8e6519281cb5a33b64b3190cc763248b4c3f9ad5087a92c",
      "d58cf9939847921b2aab78eaa7b427dc4c649d25e6bee3c749ace4c3f52f5c97",
      "802458dc13bf773c756bf6bc1f0996623b558fece6a3d483bb87cfacb21f992f",
    ..
.. code-block:: none

    @ val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    darHash : String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"

If the DAR hash is unknown, it can be found using ``dars.list``:

.. code-block:: none

    @ val darHash_ = participant1.dars.list().filter(_.name == "CantonExamples").head.hash
    darHash_ : String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"
    

The DAR can then be removed with the following command:

.. code-block:: none

    @ participant1.dars.remove(darHash)
    

Note that, right now, DAR removal will only remove the main packages associated with the DAR:

.. code-block:: none

    @ val packageIds = participant1.packages.list().filter(_.sourceDescription == "CantonExamples").map(_.packageId)
    packageIds : Seq[String] = Vector(
      "802458dc13bf773c756bf6bc1f0996623b558fece6a3d483bb87cfacb21f992f",
      "86828b9843465f419db1ef8a8ee741d1eef645df02375ebf509cdc8c3ddd16cb",
      "cc348d369011362a5190fe96dd1f0dfbc697fdfd10e382b9e9666f0da05961b7",
      "e491352788e56ca4603acc411ffe1a49fefd76ed8b163af86cf5ee5f4c38645b",
      "cb0552debf219cc909f51cbb5c3b41e9981d39f8f645b1f35e2ef5be2e0b858a",
      "38e6274601b21d7202bb995bc5ec147decda5a01b68d57dda422425038772af7",
      "99a2705ed38c1c26cbb8fe7acf36bbf626668e167a33335de932599219e0a235",
      "f20de1e4e37b92280264c08bf15eca0be0bc5babd7a7b5e574997f154c00cb78",
      "8a7806365bbd98d88b4c13832ebfa305f6abaeaf32cfa2b7dd25c4fa489b79fb",
    ..

It's possible to remove each of these manually, using package removal. There is a complication here that packages needed
for admin workflows (e.g. the Ping command) cannot be removed, so these are skipped.

.. code-block:: none

    @ packageIds.filter(id => ! packagesBefore.contains(id)).foreach(id => participant1.packages.remove(id))
    

The following command verifies that all the packages have been removed.

.. code-block:: none

    @ val packages = participant1.packages.list().map(_.packageId).toSet
    packages : Set[String] = HashSet(
      "86828b9843465f419db1ef8a8ee741d1eef645df02375ebf509cdc8c3ddd16cb",
      "5921708ce82f4255deb1b26d2c05358b548720938a5a325718dc69f381ba47ff",
      "cc348d369011362a5190fe96dd1f0dfbc697fdfd10e382b9e9666f0da05961b7",
      "4776964ad90aa11ec8e82abc3e5d989bc63e94f84b185e1dd9895b7e5d97ad7e",
      "6839a6d3d430c569b2425e9391717b44ca324b88ba621d597778811b2d05031d",
      "99a2705ed38c1c26cbb8fe7acf36bbf626668e167a33335de932599219e0a235",
      "e22bce619ae24ca3b8e6519281cb5a33b64b3190cc763248b4c3f9ad5087a92c",
      "d58cf9939847921b2aab78eaa7b427dc4c649d25e6bee3c749ace4c3f52f5c97",
      "802458dc13bf773c756bf6bc1f0996623b558fece6a3d483bb87cfacb21f992f",
    ..
.. code-block:: none

    @ assert(packages == packagesBefore)
    

The following sections explain what happens when the DAR removal operation goes wrong, for various reasons.

Main package of the DAR is in use
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The first step to illustrate this is to upload a DAR and create a contract using the main package of the DAR:

.. code-block:: none

    @ val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    darHash : String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"
.. code-block:: none

    @ val packageId = participant1.packages.find("Iou").head.packageId
    packageId : String = "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6"
.. code-block:: none

    @ participant1.domains.connect_local(mydomain)
    
.. code-block:: none

    @ val createIouCmd = ledger_api_utils.create(packageId,"Iou","Iou",Map("payer" -> participant1.adminParty,"owner" -> participant1.adminParty,"amount" -> Map("value" -> 100.0, "currency" -> "EUR"),"viewers" -> List()))
    ..
.. code-block:: none

    @ participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))
    res21: com.daml.ledger.api.v1.transaction.TransactionTree = TransactionTree(
      transactionId = "122081bd571a286ae939088bee661d40a2259d79f3a525b5e299172959425989036e",
      commandId = "bbb4fa69-233c-4c7f-b399-f17f3f06c3dc",
      workflowId = "",
      effectiveAt = Some(
    ..

Now that a contract exists using the main package of the DAR, a subsequent DAR removal operation will fail:

.. code-block:: none

    @ participant1.dars.remove(darHash)
    ERROR com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition$$anon$3 - Request failed for participant1.
      GrpcRequestRefusedByServer: FAILED_PRECONDITION/PACKAGE_OR_DAR_REMOVAL_ERROR(9,ece01a48): The DAR DarDescriptor(SHA-256:bb85d262c864...,CantonExamples) cannot be removed because its main package bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6 is in-use by contract ContractId(00780d035c23b6a6d1e54be3d2680fe17fe1bdf389e0a3acda47eefea34942defdca0112208360d53d53e891dbdc7c04b167752b351292ed05649de532097a1cc22fcc83b9)
    on domain mydomain::1220874c4161....
      Request: RemoveDar(1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91)
      CorrelationId: ece01a481e0a8c5c0ab7c74bdb5983cb
      Context: Map(participant -> participant1, test -> PackageDarManagementDocumentationIntegrationTest, pkg -> bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6)
      Command ParticipantAdministration$dars$.remove invoked from cmd10000056.sc:1

In order to remove the DAR, we must archive this contract. Note that the contract ID for this contract can also be found in the error message above.

.. code-block:: none

    @ val iou = participant1.ledger_api.acs.find_generic(participant1.adminParty, _.templateId == "Iou.Iou")
    iou : com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent = WrappedCreatedEvent(
      event = CreatedEvent(
        eventId = "#122081bd571a286ae939088bee661d40a2259d79f3a525b5e299172959425989036e:0",
        contractId = "00780d035c23b6a6d1e54be3d2680fe17fe1bdf389e0a3acda47eefea34942defdca0112208360d53d53e891dbdc7c04b167752b351292ed05649de532097a1cc22fcc83b9",
        templateId = Some(
          value = Identifier(
            packageId = "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6",
            moduleName = "Iou",
            entityName = "Iou"
          )
    ..
.. code-block:: none

    @ val archiveIouCmd = ledger_api_utils.exercise("Archive", Map.empty, iou.event)
    ..
.. code-block:: none

    @ participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(archiveIouCmd))
    res24: com.daml.ledger.api.v1.transaction.TransactionTree = TransactionTree(
      transactionId = "1220e6ef3f5fa8dc272b813c094ed98ff3ce5d235b832bd1572168398cb031506911",
      commandId = "687bf2ca-b81a-4572-9b68-f85d9dc17684",
      workflowId = "",
      effectiveAt = Some(
    ..

The DAR removal operation will now succeed.

.. code-block:: none

    @ participant1.dars.remove(darHash)
    

Main package of the DAR can't be automatically removed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Similarly, DAR removal may fail because the DAR can't be automatically removed. To illustrate this, upload the DAR
without automatic vetting and subsequently vet all the packages manually.

.. code-block:: none

    @ val darHash = participant1.dars.upload("dars/CantonExamples.dar", vetAllPackages = false)
    darHash : String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"
.. code-block:: none

    @ import com.daml.lf.data.Ref.IdString.PackageId
    
.. code-block:: none

    @ val packageIds = participant1.packages.list().filter(_.sourceDescription == "CantonExamples").map(_.packageId).map(PackageId.assertFromString)
    packageIds : Seq[PackageId] = Vector(
      "802458dc13bf773c756bf6bc1f0996623b558fece6a3d483bb87cfacb21f992f",
      "86828b9843465f419db1ef8a8ee741d1eef645df02375ebf509cdc8c3ddd16cb",
    ..
.. code-block:: none

    @ participant1.topology.vetted_packages.authorize(TopologyChangeOp.Add, participant1.id, packageIds)
    res29: com.google.protobuf.ByteString = <ByteString@671a0178 size=2384 contents="\n\315\022\n\373\017\n\366\017\n\363\017\022 phIa8QCPFGVNd08AxXX9QB232mX9WUvUJ...">

The DAR removal operation will now fail:

.. code-block:: none

    @ participant1.dars.remove(darHash)
    ERROR com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition$$anon$3 - Request failed for participant1.
      GrpcRequestRefusedByServer: FAILED_PRECONDITION/PACKAGE_OR_DAR_REMOVAL_ERROR(9,d15d1021): An error was encountered whilst trying to unvet the DAR DarDescriptor(SHA-256:bb85d262c864...,CantonExamples) with main package bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6 for DAR removal. Details: IdentityManagerParentError(Mapping(VettedPackages(
      participant = participant1::1220974fbb27...,
      packages = Seq(
        bee3603d6b10...,
        94f7c83923aa...,
        cb0552debf21...,
        3f4deaf145a1...,
        86828b984346...,
        f20de1e4e37b...,
        76bf0fd12bd9...,
        38e6274601b2...,
        d58cf...
      Request: RemoveDar(1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91)
      CorrelationId: d15d1021c20257667fd2d593e3b53eec
      Context: Map(participant -> participant1, test -> PackageDarManagementDocumentationIntegrationTest)
      Command ParticipantAdministration$dars$.remove invoked from cmd10000076.sc:1

The DAR can be successfully removed after manually revoking the vetting for the main package:

.. code-block:: none

    @ participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove, participant1.id, packageIds, force = true)
    res30: com.google.protobuf.ByteString = <ByteString@4d6022b6 size=2386 contents="\n\317\022\n\375\017\n\370\017\n\365\017\b\001\022 phIa8QCPFGVNd08AxXX9QB232mX9WUv...">
.. code-block:: none

    @ participant1.dars.remove(darHash)
    

Note that a ``force`` flag is needed used to revoke the package vetting; throughout this tutorial ``force`` will be used whenever a package vetting is being removed.
See :ref:`topology.vetted_packages.authorize <topology.vetted_packages.authorize>` for more detail.


Removing Packages
~~~~~~~~~~~~~~~~~

Canton also supports removing individual packages, giving the user more fine-grained control over the system.
Packages can be removed if the package satisfies the following two requirements:

- The package must be unused. This means that there shouldn't be an active contract corresponding to the package.

- The package must not be vetted. This means there shouldn't be an active vetting transaction corresponding to the package.

The following tutorial shows how to remove a package using the Canton console. The first step is to upload and identify the
package ID for the package to be removed.

.. code-block:: none

    @ val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    darHash : String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"
.. code-block:: none

    @ val packageId = participant1.packages.find("Iou").head.packageId
    packageId : String = "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6"

Package removal will initially fail as, by default, uploading the DAR will add a vetting transaction for the package:

.. code-block:: none

    @ participant1.packages.remove(packageId)
    ERROR com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition$$anon$3 - Request failed for participant1.
      GrpcRequestRefusedByServer: FAILED_PRECONDITION/PACKAGE_OR_DAR_REMOVAL_ERROR(9,c9d79ea5): Package bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6 is currently vetted and available to use.
      Request: RemovePackage(bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6,false)
      CorrelationId: c9d79ea51d1c6b196eb637b8b21bb7eb
      Context: Map(participant -> participant1, test -> PackageDarManagementDocumentationIntegrationTest)
      Command ParticipantAdministration$packages$.remove invoked from cmd10000087.sc:1

The vetting transaction must be manually revoked:

.. code-block:: none

    @ val packageIds = participant1.topology.vetted_packages.list().map(_.item.packageIds).filter(_.contains(packageId)).head
    packageIds : Seq[com.digitalasset.canton.package.LfPackageId] = Vector(
      "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6",
      "94f7c83923aa273fb90b907f57385ae951ca1195fb35806275cbd03e9e4faab6",
    ..
.. code-block:: none

    @ participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove, participant1.id, packageIds, force = true)
    res35: com.google.protobuf.ByteString = <ByteString@4ba2ec31 size=2386 contents="\n\317\022\n\375\017\n\370\017\n\365\017\b\001\022 u1Dvcc3ykQ2MYHx7dKHyuJXDQySrH2a...">

And then the package can be removed:

.. code-block:: none

    @ participant1.packages.remove(packageId)
    


Package is in use
^^^^^^^^^^^^^^^^^

The operations above will fail if the package is in use. To illustrate this, first re-upload the package (uploading the associated DAR will work):

.. code-block:: none

    @ val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    darHash : String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"

Then create a contract using the package:

.. code-block:: none

    @ val createIouCmd = ledger_api_utils.create(packageId,"Iou","Iou",Map("payer" -> participant1.adminParty,"owner" -> participant1.adminParty,"amount" -> Map("value" -> 100.0, "currency" -> "EUR"),"viewers" -> List()))
    createIouCmd : com.daml.ledger.api.v1.commands.Command = Command(
      command = Create(
        value = CreateCommand(
          templateId = Some(
            value = Identifier(
    ..
.. code-block:: none

    @ participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))
    res39: com.daml.ledger.api.v1.transaction.TransactionTree = TransactionTree(
      transactionId = "1220a2e4c01eb578ca962ce751b88f28cb4cca70e3b3e9d7f1ad36462a35d1d6973c",
      commandId = "7fdcb95d-3fc3-432a-a64c-ca318d0f4058",
      workflowId = "",
      effectiveAt = Some(
        value = Timestamp(
          seconds = 1672788308L,
          nanos = 456319000,
          unknownFields = UnknownFieldSet(fields = Map())
        )
    ..

In this situation, the package cannot be removed:

.. code-block:: none

    @ participant1.packages.remove(packageId)
    ERROR com.digitalasset.canton.integration.EnterpriseEnvironmentDefinition$$anon$3 - Request failed for participant1.
      GrpcRequestRefusedByServer: FAILED_PRECONDITION/PACKAGE_OR_DAR_REMOVAL_ERROR(9,3b461985): Package bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6 is currently in-use by contract ContractId(0026c4099d64b799c0591299fbca0e6a31d62b8ae263a57d16c9a889e5031de694ca011220a47323f97d09b072868cf59fb7dbae015d8c4920cfe54e3ed6c316197d32c7c2) on domain mydomain::1220874c4161.... It may also be in-use by other contracts.
      Request: RemovePackage(bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6,false)
      CorrelationId: 3b461985a573ee4d37fbe2a740498a36
      Context: HashMap(participant -> participant1, test -> PackageDarManagementDocumentationIntegrationTest, domain -> mydomain::1220874c4161..., pkg -> bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6, contract -> ContractId(0026c4099d64b799c0591299fbca0e6a31d62b8ae263a57d16c9a889e5031de694ca011220a47323f97d09b072868cf59fb7dbae015d8c4920cfe54e3ed6c316197d32c7c2))
      Command ParticipantAdministration$packages$.remove invoked from cmd10000103.sc:1

To remove the package, first archive the contract:

.. code-block:: none

    @ val iou = participant1.ledger_api.acs.find_generic(participant1.adminParty, _.templateId == "Iou.Iou")
    iou : com.digitalasset.canton.admin.api.client.commands.LedgerApiTypeWrappers.WrappedCreatedEvent = WrappedCreatedEvent(
      event = CreatedEvent(
        eventId = "#1220a2e4c01eb578ca962ce751b88f28cb4cca70e3b3e9d7f1ad36462a35d1d6973c:0",
        contractId = "0026c4099d64b799c0591299fbca0e6a31d62b8ae263a57d16c9a889e5031de694ca011220a47323f97d09b072868cf59fb7dbae015d8c4920cfe54e3ed6c316197d32c7c2",
        templateId = Some(
          value = Identifier(
            packageId = "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6",
            moduleName = "Iou",
            entityName = "Iou"
          )
    ..
.. code-block:: none

    @ val archiveIouCmd = ledger_api_utils.exercise("Archive", Map.empty, iou.event)
    archiveIouCmd : com.daml.ledger.api.v1.commands.Command = Command(
      command = Exercise(
        value = ExerciseCommand(
          templateId = Some(
            value = Identifier(
              packageId = "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6",
              moduleName = "Iou",
              entityName = "Iou"
            )
          ),
    ..
.. code-block:: none

    @ participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(archiveIouCmd))
    res42: com.daml.ledger.api.v1.transaction.TransactionTree = TransactionTree(
      transactionId = "1220a7f982f6530dcd29a26819c8c8bdda27d00732851d37b5fc67bbcba8e7c75fca",
      commandId = "685b5b16-7899-4fef-a92c-4202996bf9ed",
      workflowId = "",
      effectiveAt = Some(
        value = Timestamp(
          seconds = 1672788308L,
          nanos = 923844000,
          unknownFields = UnknownFieldSet(fields = Map())
        )
      ),
      offset = "00000000000000000c",
    ..

Then revoke the package vetting transaction:

.. code-block:: none

    @ val packageIds = participant1.topology.vetted_packages.list().map(_.item.packageIds).filter(_.contains(packageId)).head
    packageIds : Seq[com.digitalasset.canton.package.LfPackageId] = Vector(
      "bee3603d6b10e694cd6c12f6b4c923b6b2f3edd42b9ce189c5cce5d00889fac6",
      "94f7c83923aa273fb90b907f57385ae951ca1195fb35806275cbd03e9e4faab6",
    ..
.. code-block:: none

    @ participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove, participant1.id, packageIds, force = true)
    res44: com.google.protobuf.ByteString = <ByteString@26fa5f4a size=2386 contents="\n\317\022\n\375\017\n\370\017\n\365\017\b\001\022 O0jHhJpCuBEpdjxbeNQ2k3eTUyqboUR...">

The package removal operation should now succeed.

.. code-block:: none

    @ participant1.packages.remove(packageId)
    

Force-removing packages
^^^^^^^^^^^^^^^^^^^^^^^

Packages can also be forcibly removed, even if the conditions above are not satisfied. This is done by setting the
``force`` flag to ``true``.

To experiment with this, first re-upload the DAR so the package becomes available again:

.. code-block:: none

    @ participant1.dars.upload("dars/CantonExamples.dar")
    res46: String = "1220bb85d262c8647209f6157fddce79d4074a3e346ad864437c970366544e104f91"

Then force-remove the package:

.. code-block:: none

    @ participant1.packages.remove(packageId, force = true)
    

Please note, this is a dangerous operation. Forced removal of packages should be avoided whenever possible.
