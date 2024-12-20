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
anywhere and participants do not have access to each others DAR repositories. Instead, participants publicly declare towards their peers
that they are ready to receive transactions referring to certain packages. This is done by vetting topology transactions which can be seen
by all the participants connected to a specific domain.
Therefore, for two participants to synchronise on a transaction that uses packages contained in a certain DAR, we need both participant operators to
have uploaded the same DAR and have its contained packages vetted before the transaction was submitted.

If one of the involved participants doesn't know about a certain DAR, then the transaction will bounce with an error
``NO_DOMAIN_FOR_SUBMISSION`` (with additional metadata listing which package has not been vetted on which participant).
This can happen if the DAR has not been uploaded to the participant node or it has not been vetted. This declaration happens
automatically when you upload a DAR, although it can be disabled by a request flag.

The package vettings can be inspected using (preview):

.. snippet:: package_dar_removal
    .. success(output=8):: participant2.topology.vetted_packages.list()

Vetting is necessary, as otherwise, a malicious participant might send a transaction referring to package a receiver
does not have, which would make it impossible for the receiver to process the transaction, leading to a ledger fork.
As transactions are valid only if all involved participants have vetted the used packages, this attack cannot happen.

DAR vetting lifecycle
~~~~~~~~~~~~~~~~~~~~~

As mentioned above, a participant can start accepting transactions that reference a DAR's packages after the DAR has been uploaded.

.. snippet:: package_dar_removal
    .. success:: val darHash = participant1.dars.upload("dars/CantonExamples.dar")
    .. success:: val packageId = participant1.packages.find("Iou").head.packageId
    .. success:: participant1.domains.connect_local(mydomain)
    .. success(output=0):: val createIouCmd = ledger_api_utils.create(packageId,"Iou","Iou",Map("payer" -> participant1.adminParty,"owner" -> participant1.adminParty,"amount" -> Map("value" -> 100.0, "currency" -> "EUR"),"viewers" -> List()))
    .. success(output=5):: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

The vetting of a DAR can be disabled, effectively preventing its use in Daml transactions.
Any subsequent commands attempting to create or exercise choices on contracts for the referenced package IDs will now be rejected.

.. snippet:: package_dar_removal
    .. success:: participant1.dars.vetting.disable(darHash)
    .. failure:: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))

If the decision to support the DAR changes, its vetting can be re-enabled:

.. snippet:: package_dar_removal
    .. success:: participant1.dars.vetting.enable(darHash)
    .. failure:: participant1.ledger_api.commands.submit(Seq(participant1.adminParty), Seq(createIouCmd))
