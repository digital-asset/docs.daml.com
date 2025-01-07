..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

Manage DARs and Packages
========================

A package is a unit of compiled Daml code corresponding to one Daml project. A DAR is a collection of packages including
a main package and all other packages from the dependencies of this Daml project.

Uploading DARs
--------------

To use a Daml application on a participant, you need to upload it to your participant node. The application always
comes packaged as one or more DARs that need to be uploaded in the order of their dependency. There are two ways to
upload DARs to a Canton node: either via the `Ledger Api <https://docs.daml.com/app-dev/grpc/proto-docs.html#com-daml-ledger-api-v1-packageservice>`__,
or through Canton :ref:`console command <dars.upload>`:

.. snippet:: package_dar_vetting
    .. success:: participant2.dars.upload("dars/CantonExamples.dar")

Inspecting DARs and Packages
----------------------------

You can get a list of uploaded DARs using:

.. snippet:: package_dar_vetting
    .. success:: participant2.dars.list()

Please note that the package "AdminWorkflows" is a package that ships with Canton. It contains the Daml templates
used by the ``participant.health.ping`` command.

In order to inspect the contents of the DAR, you need to grab the hash identifying it:

.. snippet:: package_dar_vetting
    .. success:: val dars = participant2.dars.list(filterName = "CantonExamples")
    .. success:: val hash = dars.head.hash

Using that hash, you can inspect the contents of the DAR using:

.. snippet:: package_dar_vetting
    .. success(output=8):: val darContent = participant2.dars.list_contents(hash)

You can also directly look at the packages, using:

.. snippet:: package_dar_vetting
    .. success(output=8):: participant2.packages.list()

Please note that a DAR can include packages that are already included in other DARs. In particular the Daml standard library
are shipped with every DAR. Therefore, the ``sourceDescription`` will always contain only one textual reference to a DAR.

You can also inspect the content of a package, using:

.. snippet:: package_dar_vetting
    .. success(output=8):: participant2.packages.list_contents(darContent.main)

.. _package_vetting:

Understanding Package Vetting
-----------------------------

Every participant operator uploads DARs individually to their participant node. There is no global DAR repository
anywhere and participants do not have access to each others DAR repositories. Instead, participants publicly declare towards their peers
that they are ready to receive transactions referring to certain packages.
This is done by Daml package state topology transactions which can be seen by all the participants connected to a specific domain.
Therefore, for two participants to synchronise on a transaction that uses packages contained in a certain DAR, both participant operators
must upload and enable vetting for the same DAR and its contained packages before the transaction is submitted.

If one of the involved participants doesn't know about the packages of a certain DAR, then the transaction will bounce with an error
``NO_DOMAIN_FOR_SUBMISSION`` (with additional metadata listing which package has not been vetted on which participant).
This can happen if the DAR has not been uploaded to the participant node or it has not been vetted.

.. note::
    The unit of Daml code for which a Canton participant can issue topology transactions is the Daml package.
    However, in practice, for ensuring that transactions can be successfully submitted using any package of a specific DAR,
    the high-level Canton vetting APIs act on vetting at the DAR level (i.e. for all of a DAR's packages, transactionally).
    These high-level APIs are the ``participant.dars.vetting.enable`` and ``participant.dars.vetting.disable`` console commands as well
    as the ``PackageService.vetDar`` and ``PackageService.unvetDar`` Admin API calls.

Vetting happens automatically when you upload a DAR, although it can be disabled by a request flag.

.. snippet:: package_dar_vetting
    .. success:: participant2.dars.upload("dars/CantonExamples.dar", vetAllPackages = false)

Vetting can also be enabled explicitly for a DAR's packages (e.g. if the DAR upload operation was triggerred without vetting)

.. snippet:: package_dar_vetting
    .. success:: participant2.dars.vetting.enable(hash)

Vetting is necessary, as otherwise, a malicious participant might send a transaction referring to package a receiver
does not have, which would make it impossible for the receiver to process the transaction, leading to a ledger fork.
As transactions are valid only if all involved participants have vetted the used packages, this attack cannot happen.

DAR vetting lifecycle
~~~~~~~~~~~~~~~~~~~~~

As mentioned above, a participant can start accepting transactions that reference a DAR's packages after the DAR has been uploaded
and its vetting enabled.

Let's upload a DAR and create a contract referencing a template from the main package of the DAR:

.. snippet:: package_dar_vetting
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    .. success:: val mainPackageId = participant1.packages.find("Iou").head.packageId
    .. success:: participant1.domains.connect_local(mydomain)
    .. success(output=0):: val createIouCmd = ledger_api_utils.create(mainPackageId,"Iou","Iou",Map("payer" -> participant1.adminParty,"owner" -> participant1.adminParty,"amount" -> Map("value" -> 100.0, "currency" -> "EUR"),"viewers" -> List()))
    .. success(output=5):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty ), Seq(createIouCmd))

The vetting of a DAR can be disabled, effectively preventing its use in Daml transactions.

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(darHash)

.. note::
    Disabling of DAR vetting is a supported and safe operation on participants running protocol version 7 and above.
    Usage of this operation in production environments is not advised on previous protocol version.

Any subsequent commands attempting to create or exercise choices on contracts for the referenced package IDs will now be rejected.

.. snippet:: package_dar_vetting
    .. failure:: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

If the decision to support the DAR changes, its vetting can be re-enabled:

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.enable(darHash)
    .. success(output=5):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

.. _multi_vetted_package:

What if a package is vetted multiple times?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We can't disable the vetting for a DAR whose main package is referenced as part of a distinct vetted DAR.
For example, let's upload a DAR that depends on the "CantonExamples" DAR and try to disable vetting for the latter:

.. snippet:: package_dar_vetting
    .. success:: val examplesDependencyDarHash = participant1.dars.upload("dars/CantonExamplesDependency.dar")
    .. failure:: participant1.dars.vetting.disable(darHash)

Instead, if we disable the vetting for the "CantonExamplesDependency" DAR first, which contains as package dependencies
the main package of the "CantonExamples" DAR,

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(examplesDependencyDarHash)

then we can disable the vetting for the "CantonExamples" DAR as well.

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(darHash)

Advanced vetting concepts
~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::
    This section concentrates on lower-level details of package topology state and commands.
    For most use-cases, the high-level vetting APIs mentioned above should be sufficient.
    Usage of the lower-level topology APIs can lead to inconsistencies in the participant's topology state
    and is advised only by expert users.

Package topology states
^^^^^^^^^^^^^^^^^^^^^^^

With respect to a participant, a package can be in one of the following states:

- **Not found** on the participant: The package does not exist in the local participant stores and it can't be referenced in any request to the participant node.

- **Unknown**: The package may exist in the local participant stores, but it has no associated topology transaction issued by the participant node (i.e. it is unknown topology-wise). A package pertaining to a DAR that was uploaded with the vetting flag disabled is unknown.

- **Check-only**: The package appears at least in a `CheckOnlyPackages` topology transaction and it allows a participant to announce that a collection of Daml packages are known but can only be used for validating pre-existing contracts on the ledger and not for executing new Daml transactions. This concept has been introduced in protocol version 7 for supporting :ref:`Smart contract upgrades <smart-contract-upgrades>`.

- **Vetted**: A package in this state appears at least in a `VettedPackages` topology transaction and allows the participant to accept new transactions that reference it in Daml action nodes. This state includes is unchanged from the previous protocol versions.

For a DAR that is unknown (topology-wise), the vetting operations (``participant.dars.vetting.enable(darHash)`` or ``PackageService.vetDar``) issues a `VettedPackages` topology transaction referencing all the packages in the DAR.

To exemplify, let's vet the examples DAR again:

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.enable(darHash)

Now, we can check that the DAR's main package-id appears in a `VettedPackages` topology transaction:

.. snippet:: package_dar_vetting
    .. success(output=1):: participant1.topology.vetted_packages.list().exists(_.item.packageIds.contains(mainPackageId))
    .. assert:: RES

.. note::
    On enabling the vetting for a DAR, if it exists, the `CheckOnlyPackages` topology transaction is eventually removed,
    as a `VettedPackages` topology transaction already implies that the referenced packages can be used for validating the
    pre-existing ledger contracts. This operation is done asynchronously and does not block the vetting API call.

Once we disable the package's DAR vetting,

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(darHash)

the package-id will appear only in a `CheckOnlyPackages` topology transaction:

.. snippet:: package_dar_vetting
    .. success(output=1):: participant1.topology.vetted_packages.list().exists(_.item.packageIds.contains(mainPackageId))
    .. assert:: !RES
    .. success(output=1):: participant1.topology.check_only_packages.list().exists(_.item.packageIds.contains(mainPackageId))
    .. assert:: RES

Commands toggling between the two vetting enabled and disabled states effectively always issue two topology operations:

- **On vetting enable**: A `VettedPackages` topology transaction is added and corresponding `CheckOnlyPackages` topology transaction

- **On vetting disable**: A `CheckOnlyPackages` topology transaction addition and the removal of the `VettedPackages` topology transaction

Forcefully unvetting a package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In some cases, you might want to circumvent the high-level vetting APIs
and directly issue or revoke package topology transactions.
One such example is when a package is referenced in multiple topology transactions (e.g. the package is contained in multiple vetted DARs uploaded on the participant)
and it can't be automatically unvetted (as exemplified in the :ref:`multi_vetted_package`).

To build the example, let's re-enable vetting for both the `CantonExamples` the `CantonExamplesDependency` DARs.

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.enable(examplesDependencyDarHash)
    .. success:: participant1.dars.vetting.enable(darHash)

In order to mark a the main package of the `CantonExamples` DAR as check-only, we need to remove it from all the
`VettedPackages` topology transactions it appears in. We'll do so by using the low-level topology management API.

First, we need to identify the topology transactions containing the package that we need to disable:

.. snippet:: package_dar_vetting
    .. success(output=16):: val txsContainingMainPackage = participant1.topology.vetted_packages.list(filterStore = "Authorized", filterParticipant = participant1.id.filterString).filter(_.item.packageIds.contains(mainPackageId))

Then, we replace the `VettedPackages` transactions with ones not referring to the main package.

.. snippet:: package_dar_vetting
    .. success:: import com.digitalasset.canton.LfPackageId
    .. success:: txsContainingMainPackage.foreach { tx => participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove,participant1.id,tx.item.packageIds,force = true); participant1.topology.vetted_packages.authorize(TopologyChangeOp.Add,participant1.id,tx.item.packageIds.filterNot(_ == mainPackageId),force = true)}

Additionally, we make sure the package becomes check-only by issuing a dedicated `CheckOnlyPackages` topology transaction.

.. snippet:: package_dar_vetting
    .. success(output=0):: participant1.topology.check_only_packages.authorize(TopologyChangeOp.Add, participant1.id, Seq(LfPackageId.assertFromString(mainPackageId)), force = true)