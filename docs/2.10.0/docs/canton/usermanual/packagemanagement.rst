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
is shipped with every DAR. Therefore, the ``sourceDescription`` will always contain only one textual reference to a DAR.

You can also inspect the content of a package, using:

.. snippet:: package_dar_vetting
    .. success(output=8):: participant2.packages.list_contents(darContent.main)

.. _package_vetting:

Understanding Package Vetting
-----------------------------

Every participant operator uploads DARs individually to their participant node. There is no global DAR repository
anywhere and participants do not have access to each others DAR repositories. Instead, participants publicly declare towards their peers
that they are ready to receive transactions referring to certain packages.
This is done by Canton package state topology transactions which can be seen by all the participants connected to a specific sync domain.
Therefore, for two participants to synchronize on a transaction that uses packages contained in a certain DAR, both participant operators
must upload and vet the same DAR and its contained packages before the transaction is submitted.

If the DAR has not been uploaded to one of the involved participants or it has not been vetted, then transaction submissions are rejected with a
``NO_DOMAIN_FOR_SUBMISSION`` error (with additional metadata listing which package has not been vetted on which participant).

.. note::
    The unit of Daml code for which a Canton participant can issue topology transactions is the Daml package.
    However, in practice, to ensure that transactions can be successfully submitted using any package of a specific DAR,
    the Canton vetting APIs act at the DAR level (i.e. for all of a DAR's packages, transactionally).
    The APIs in question are the console commands: ``participant.dars.vetting.enable`` and ``participant.dars.vetting.disable`` as well
    as the Admin API calls: ``PackageService.vetDar`` and ``PackageService.unvetDar``.

Vetting happens automatically when you upload a DAR, although it can be disabled by a request flag.

.. snippet:: package_dar_vetting
    .. success:: participant2.dars.upload("dars/CantonExamples.dar", vetAllPackages = false)

The packages contained in a DAR can also be vetted explicitly when the DAR upload operation was performed without vetting

.. snippet:: package_dar_vetting
    .. success:: participant2.dars.vetting.enable(hash)

Transactions are valid only if all involved participants have vetted the used packages. This helps prohibiting attacks
from malicious participants, who could send a transaction referring to a package the receiver does not have.
Such a transaction would be impossible for the receiver to process, leading to a ledger fork.

DAR vetting lifecycle
~~~~~~~~~~~~~~~~~~~~~

As mentioned above, a participant can start accepting transactions that reference packages in a DAR after it has been uploaded and vetted.

First, upload a DAR and create a contract referencing a template from the main package of the DAR:

.. snippet:: package_dar_vetting
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    .. success:: val mainPackageId = participant1.packages.find("Iou").head.packageId
    .. success:: participant1.domains.connect_local(mydomain)
    .. success(output=0):: val createIouCmd = ledger_api_utils.create(mainPackageId,"Iou","Iou",Map("payer" -> participant1.adminParty,"owner" -> participant1.adminParty,"amount" -> Map("value" -> 100.0, "currency" -> "EUR"),"viewers" -> List()))
    .. success(output=5):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty ), Seq(createIouCmd))

You can unvet a DAR, effectively preventing its use in Daml transactions.

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(darHash)

.. note::
    Unvetting a DAR is a supported and safe operation on participants running protocol version 7 and above.
    Usage of this operation in production environments is not advised on previous protocol versions.

Any subsequent commands attempting to create or exercise choices on contracts for the referenced package IDs are rejected.

.. snippet:: package_dar_vetting
    .. failure:: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

If the decision to support the DAR changes, it can be re-vetted:

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.enable(darHash)
    .. success(output=5):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

.. _multi_vetted_package:

What if a package is vetted multiple times?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can't unvet a DAR whose main package is referenced as part of a distinct vetted DAR.
For example, if you upload a DAR that depends on the "CantonExamples" DAR and try to unvet the latter, the operation fails

.. snippet:: package_dar_vetting
    .. success:: val examplesDependencyDarHash = participant1.dars.upload("dars/CantonExamplesDependency.dar")
    .. failure:: participant1.dars.vetting.disable(darHash)

Instead, you should first unvet the "CantonExamplesDependency" DAR, which contains as package dependencies
the main package of the "CantonExamples",

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(examplesDependencyDarHash)

then you can safely unvet the "CantonExamples" DAR as well.

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(darHash)

Advanced vetting concepts
~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::
    This section concentrates on lower-level details of package topology state and commands.
    For most use cases, the high-level vetting APIs mentioned above are sufficient.
    Using lower-level topology APIs can lead to inconsistencies in the participant's topology state;
    it should be used only by experts.

Package topology states
^^^^^^^^^^^^^^^^^^^^^^^

With respect to a participant, a package can be in one of the following states:

- **Not found** on the participant: The package does not exist in the local participant stores and cannot be referenced in any request to the participant node.

- **Unknown**: The package may exist in the local participant stores, but it has no associated topology transaction issued by the participant node (i.e. it is unknown topology-wise). A package pertaining to a DAR uploaded with the vetting flag off is unknown.

- **Check-only**: The package appears in a `CheckOnlyPackages` topology transaction and it allows a participant to announce that a collection of Daml packages is known, but it can only be used to validate preexisting contracts on the ledger, not for executing new Daml transactions. This concept has been introduced in protocol version 7 to support :ref:`Smart contract upgrades <smart-contract-upgrades>`.

- **Vetted**: A package in this state appears at least in a `VettedPackages` topology transaction and allows the participant to accept new transactions that reference it in Daml action nodes. This state is unchanged from the previous protocol versions.

For a DAR that is unknown (topology-wise), the vetting operations (``participant.dars.vetting.enable(darHash)`` or ``PackageService.vetDar``) results in a `VettedPackages` topology transaction referencing all the packages in the DAR.

To illustrate the point, please vet the example DAR again:

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.enable(darHash)

Now, check that the DAR's main package-id appears in a `VettedPackages` topology transaction:

.. snippet:: package_dar_vetting
    .. success(output=1):: participant1.topology.vetted_packages.list().exists(_.item.packageIds.contains(mainPackageId))
    .. assert:: RES

.. note::
    When a DAR is vetted, if it exists, the `CheckOnlyPackages` topology transaction is eventually removed,
    as a `VettedPackages` topology transaction already implies that the referenced packages can be used for validating the
    preexisting ledger contracts. This operation is asynchronous and does not block the vetting API call.

Now, unvet the DAR:

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.disable(darHash)

And you can observe that the package ID appears only in a `CheckOnlyPackages` topology transaction:

.. snippet:: package_dar_vetting
    .. success(output=1):: participant1.topology.vetted_packages.list().exists(_.item.packageIds.contains(mainPackageId))
    .. assert:: !RES
    .. success(output=1):: participant1.topology.check_only_packages.list().exists(_.item.packageIds.contains(mainPackageId))
    .. assert:: RES

Commands toggling between the two vetting states effectively issue two topology operations:

- **On vetting enable**: A `VettedPackages` topology transaction addition and the removal of the corresponding `CheckOnlyPackages` topology transaction

- **On vetting disable**: A `CheckOnlyPackages` topology transaction addition and the removal of the `VettedPackages` topology transaction

Forcefully unvetting a package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In some cases, you might want to circumvent the high-level vetting APIs
and directly issue or revoke package topology transactions.
One such example is when a package is referenced in multiple topology transactions (e.g. the package is contained in multiple vetted DARs uploaded on the participant)
and it cannot be automatically unvetted (as exemplified in the :ref:`multi_vetted_package`).

To build the example, re-enable vetting for both the `CantonExamples` and the `CantonExamplesDependency` DARs.

.. snippet:: package_dar_vetting
    .. success:: participant1.dars.vetting.enable(examplesDependencyDarHash)
    .. success:: participant1.dars.vetting.enable(darHash)

To mark the main package of the `CantonExamples` DAR as check-only, remove it from all the
`VettedPackages` topology transactions it appears in using the low-level topology management API.

First, identify the topology transactions containing the package to remove:

.. snippet:: package_dar_vetting
    .. success(output=16):: val txsContainingMainPackage = participant1.topology.vetted_packages.list(filterStore = "Authorized", filterParticipant = participant1.id.filterString).filter(_.item.packageIds.contains(mainPackageId))

Then, replace the `VettedPackages` transactions with ones that do not refer to the main package.

.. snippet:: package_dar_vetting
    .. success:: import com.digitalasset.canton.LfPackageId
    .. success:: txsContainingMainPackage.foreach { tx => participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove,participant1.id,tx.item.packageIds,force = true); participant1.topology.vetted_packages.authorize(TopologyChangeOp.Add,participant1.id,tx.item.packageIds.filterNot(_ == mainPackageId),force = true)}

Ensure that the package becomes check-only by issuing a dedicated `CheckOnlyPackages` topology transaction.

.. snippet:: package_dar_vetting
    .. success(output=0):: participant1.topology.check_only_packages.authorize(TopologyChangeOp.Add, participant1.id, Seq(LfPackageId.assertFromString(mainPackageId)), force = true)
