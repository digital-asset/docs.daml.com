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

.. snippet:: package_dar_removal
    .. success:: participant2.dars.upload("dars/CantonExamples.dar")

Inspecting DARs and Packages
----------------------------

You can get a list of uploaded DARs using:

.. snippet:: package_dar_removal
    .. success:: participant2.dars.list()

Please note that the package "AdminWorkflows" is a package that ships with Canton. It contains the Daml templates
used by the ``participant.health.ping`` command.

In order to inspect the contents of the DAR, you need to grab the hash identifying it:

.. snippet:: package_dar_removal
    .. success:: val dars = participant2.dars.list(filterName = "CantonExamples")
    .. success:: val hash = dars.head.hash

Using that hash, you can inspect the contents of the DAR using:

.. snippet:: package_dar_removal
    .. success(output=8):: val darContent = participant2.dars.list_contents(hash)

You can also directly look at the packages, using:

.. snippet:: package_dar_removal
    .. success(output=8):: participant2.packages.list()

Please note that a DAR can include packages that are already included in other DARs. In particular the Daml standard library
are shipped with every DAR. Therefore, the ``sourceDescription`` will always contain only one textual reference to a DAR.

You can also inspect the content of a package, using:

.. snippet:: package_dar_removal
    .. success(output=8):: participant2.packages.list_contents(darContent.main)

.. _package_vetting:

Understanding Package Vetting
-----------------------------

Every participant operator uploads DARs individually to their participant node. There is no global DAR repository
anywhere and participants do not have access to each others DAR repositories. Therefore, for two participants to
synchronise on a transaction that uses packages contained in a certain DAR, we need both participant operators to
have uploaded the same DAR before the transaction was submitted.

If one of the involved participants doesn't know about a certain DAR, then the transaction will bounce with an error
``NO_DOMAIN_FOR_SUBMISSION`` (with additional metadata listing which package has not been vetted on which participant).

This error goes back to the fact that both participants not only upload the DAR, but also publicly declare towards
their peers that they are ready to receive transactions referring to certain packages. This declaration happens
automatically when you upload a DAR. The package vettings can be inspected using (preview):

.. snippet:: package_dar_removal
    .. success(output=8):: participant2.topology.vetted_packages.list()

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
we have one to remove. Additionally, store the packages that are present before the DAR is uploaded, as these can be
used to double-check that DAR removal reverts to a clean state.

.. snippet:: package_dar_removal
    .. success(output=10):: val packagesBefore = participant1.packages.list().map(_.packageId).toSet
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar")

If the DAR hash is unknown, it can be found using ``dars.list``:

.. snippet:: package_dar_removal
    .. success:: val darHash_ = participant1.dars.list().filter(_.name == "CantonExamples").head.hash
    .. assert:: darHash == darHash_

The DAR can then be removed with the following command:

.. snippet:: package_dar_removal
    .. success:: participant1.dars.remove(darHash)

Note that, right now, DAR removal will only remove the main packages associated with the DAR:

.. snippet:: package_dar_removal
    .. success(output=10):: val packageIds = participant1.packages.list().filter(_.sourceDescription == "CantonExamples").map(_.packageId)

It's possible to remove each of these manually, using package removal. There is a complication here that packages needed
for admin workflows (e.g. the Ping command) cannot be removed, so these are skipped.

.. snippet:: package_dar_removal
    .. success(output=5):: packageIds.filter(id => ! packagesBefore.contains(id)).foreach(id => participant1.packages.remove(id))

The following command verifies that all the packages have been removed.

.. snippet:: package_dar_removal
    .. success(output=10):: val packages = participant1.packages.list().map(_.packageId).toSet
    .. success:: assert(packages == packagesBefore)

The following sections explain what happens when the DAR removal operation goes wrong, for various reasons.

Main package of the DAR is in use
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The first step to illustrate this is to upload a DAR and create a contract using the main package of the DAR:

.. snippet:: package_dar_removal
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    .. success:: val packageId = participant1.packages.find("Iou").head.packageId
    .. success:: participant1.domains.connect_local(mydomain)
    .. success(output=0):: val createIouCmd = ledger_api_utils.create(packageId,"Iou","Iou",Map("payer" -> participant1.adminParty,"owner" -> participant1.adminParty,"amount" -> Map("value" -> 100.0, "currency" -> "EUR"),"viewers" -> List()))
    .. success(output=5):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

Now that a contract exists using the main package of the DAR, a subsequent DAR removal operation will fail:

.. snippet:: package_dar_removal
    .. failure:: participant1.dars.remove(darHash)

In order to remove the DAR, we must archive this contract. Note that the contract ID for this contract can also be found in the error message above.

.. snippet:: package_dar_removal
    .. success(output=10):: val iou = participant1.ledger_api.acs.find_generic(participant1.adminParty, _.templateId.isModuleEntity("Iou", "Iou"))
    .. success(output=0):: val archiveIouCmd = ledger_api_utils.exercise("Archive", Map.empty, iou.event)
    .. success(output=5):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(archiveIouCmd))

The DAR removal operation will now succeed.

.. snippet:: package_dar_removal
    .. success:: participant1.dars.remove(darHash)

Main package of the DAR can't be automatically removed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Similarly, DAR removal may fail because the DAR can't be automatically removed. To illustrate this, upload the DAR
without automatic vetting and subsequently vet all the packages manually.

.. snippet:: package_dar_removal
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar", vetAllPackages = false)
    .. success:: import com.daml.lf.data.Ref.IdString.PackageId
    .. success(output=3):: val packageIds = participant1.packages.list().filter(_.sourceDescription == "CantonExamples").map(_.packageId).map(PackageId.assertFromString)
    .. success:: participant1.topology.vetted_packages.authorize(TopologyChangeOp.Add, participant1.id, packageIds)

The DAR removal operation will now fail:

.. snippet:: package_dar_removal
    .. failure:: participant1.dars.remove(darHash)

The DAR can be successfully removed after manually revoking the vetting for the main package:

.. snippet:: package_dar_removal
    .. success(output=5):: participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove, participant1.id, packageIds, force = true)
    .. success:: participant1.dars.remove(darHash)

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

.. snippet:: package_dar_removal
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    .. success:: val packageId = participant1.packages.find("Iou").head.packageId

Package removal will initially fail as, by default, uploading the DAR will add a vetting transaction for the package:

.. snippet:: package_dar_removal
    .. failure:: participant1.packages.remove(packageId)

The vetting transaction must be manually revoked:

.. snippet:: package_dar_removal
    .. success(output=3):: val packageIds = participant1.topology.vetted_packages.list().map(_.item.packageIds).filter(_.contains(packageId)).head
    .. success(output=5):: participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove, participant1.id, packageIds, force = true)

And then the package can be removed:

.. snippet:: package_dar_removal
    .. success:: participant1.packages.remove(packageId)


Package is in use
^^^^^^^^^^^^^^^^^

The operations above will fail if the package is in use. To illustrate this, first re-upload the package (uploading the associated DAR will work):

.. snippet:: package_dar_removal
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar")

Then create a contract using the package:

.. snippet:: package_dar_removal
    .. success(output=5):: val createIouCmd = ledger_api_utils.create(packageId,"Iou","Iou",Map("payer" -> participant1.adminParty,"owner" -> participant1.adminParty,"amount" -> Map("value" -> 100.0, "currency" -> "EUR"),"viewers" -> List()))
    .. success(output=10):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

In this situation, the package cannot be removed:

.. snippet:: package_dar_removal
    .. failure:: participant1.packages.remove(packageId)

To remove the package, first archive the contract:

.. snippet:: package_dar_removal
    .. success(output=10):: val iou = participant1.ledger_api.acs.find_generic(participant1.adminParty, _.templateId.isModuleEntity("Iou", "Iou"))
    .. success(output=10):: val archiveIouCmd = ledger_api_utils.exercise("Archive", Map.empty, iou.event)
    .. success(output=12):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(archiveIouCmd))

Then revoke the package vetting transaction:

.. snippet:: package_dar_removal
    .. success(output=3):: val packageIds = participant1.topology.vetted_packages.list().map(_.item.packageIds).filter(_.contains(packageId)).head
    .. success:: participant1.topology.vetted_packages.authorize(TopologyChangeOp.Remove, participant1.id, packageIds, force = true)

The package removal operation should now succeed.

.. snippet:: package_dar_removal
    .. success:: participant1.packages.remove(packageId)

Force-removing packages
^^^^^^^^^^^^^^^^^^^^^^^

Packages can also be forcibly removed, even if the conditions above are not satisfied. This is done by setting the
``force`` flag to ``true``.

To experiment with this, first re-upload the DAR so the package becomes available again:

.. snippet:: package_dar_removal
    .. success:: participant1.dars.upload("dars/CantonExamples.dar")

Then force-remove the package:

.. snippet:: package_dar_removal
    .. success:: participant1.packages.remove(packageId, force = true)

Please note, this is a dangerous operation. Forced removal of packages should be avoided whenever possible.
