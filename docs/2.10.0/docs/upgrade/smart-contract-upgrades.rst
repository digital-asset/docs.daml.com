.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _smart-contract-upgrades:

Smart Contract Upgrade
######################

.. .. toctree::
   :hidden:

Theory of Operation
===================

What is Smart Contract Upgrade (SCU)?
-------------------------------------

Smart Contract Upgrade (SCU) allows Daml models (packages in DAR files) to be
updated on Canton transparently, provided some guidelines in making the
changes are followed. For example, you can fix an application bug by uploading
the DAR of the fixed package. This feature requires the minimum versions of LF
1.17 and Canton Protocol version 7. This section provides an overview of
the SCU feature, while :ref:`The Smart Contract Upgrade Model in Depth
<upgrade-model-reference>` is a concise, technical description of the feature.

 
Smart Contract Upgrade (SCU) is a feature for Daml
packages which enable authors to publish new versions of their templates
while maintaining compatibility with prior versions, without any
downtime for package users and existing contracts.

Package authors previously upgraded their packages by either:

-  | Providing a Daml workflow for upgrading contracts to the new version,
     and tell users of the old version to use the workflow to upgrade
     their old templates to the new versions.
   | This requires communication with all package users, splits package users
     across the two versions during the migration, and may incur
     significant network cost. This approach is described
     :ref:`here <upgrade-overview>`.

-  | Uploading the new version of their application code to their participant,
     temporarily stopping workflows relating to the old version, and manually
     upgrading every old template on the participant to the new version by
     directly manipulating Canton’s databases. This method is error-prone and
     requires some downtime for the participant.

Now, with SCU, any contract from the old package is automatically interpreted
as the new version as soon as it is used in a new workflow that requires
it. This feature is well-suited for developing and rolling out incremental
template changes. There are guidelines to ensure upgrade compatibility
between DAR files. The compatibility is checked at compile time, DAR
upload time, and runtime. This is to ensure data backwards upgrade
compatibility and forwards compatibility (subject to the guidelines
being followed) so that DARs can be safely upgraded to new versions. It
also prevents unexpected data loss at clients if a runtime downgrade
occurs (e.g., a client is using template version 1.0.0 while the
participant node has the newer version 1.1.0).

A general guideline for SCU is that additive application changes are allowed
but items cannot be removed. A summary of the allowed changes in templates
are:

-  A template can add new ``Optional`` fields at the end of the list of fields;

-  A ``record`` datatype can add new optional fields at the end of the list of
   fields, and a ``variant`` or ``enum`` datatype can add new constructors at
   the end;

-  The ``ensure`` predicate can be changed and it is reevaluated at interpretation;

-  A choice signature can be changed by adding ``Optional`` parameters at the end;

-  The controller of a choice can be changed;

-  The observer of a choice can be changed

-  The body of a choice can be changed;

-  A new choice can be added to a template;

-  The implementation of an interface instance can be changed;

The following table summarizes the changes supported by SCU. Consult the
sections below for additional information. For application updates
that are not covered by SCU, consult the :ref:`Automating the Upgrade Process
<upgrade-automation>` section, which describes an upgrade tool for
migrating contracts from an old version to a new version.

.. csv-table::
  :file: upgrade-scopes.csv
  :widths: 20, 20, 15, 45
  :header-rows: 1

In this way, package authors can publish new package versions that
improve contract functionality without requiring any
error-prone migrations, without downtime, without requiring any
additional network traffic, and without any extensive communication with
downstream users.

The JSON API server is compatible with the smart contract upgrade
feature by:

-  Supporting package names for commands and queries;

-  Allowing use of an optional ``packageIdSelectionPreference`` field to
   specify a preferred package ID to use;

-  Requiring either a package id or package name to be present to disambiguate
   the partially-qualified form of template/interface IDs.

Previously JSON API had supported partially qualified template IDs,
(i.e. simply ``<module>:<entity>``) as an interactive convenience which
fails if there is more than one package with matching template names.
Since this format was not supported for production use and does not work
with SCU, it is now unavailable.

The Java and TypeScript codegen allow the use of package name and
package ID (if needed).

PQS supports for this feature.  PQS now supports the highly sought after feature of using package-name
(specified in ``daml.yaml``) instead of the more cumbersome package-id. When specifying a
template/interface/choice name, simply substitute any package-id with the
package-name (eg. now ``register:DA.Register:Token``) instead of the old
``deadbeefpackageidhex:DA.Register:Token`` format. This applies to template
filters and SQL queries (eg. via the ``active()`` function). These functions will
always return all versions of a given identifier. Qualified name can be:

- fully qualified, e.g. ``<package-name>:<module-path>:<template-name>``

- partially qualified, e.g. ``<module-path>:<template-name>``

Qualified names cannot be ambiguous.

The PQS Read API now returns the package-name, package-id, and package-version
for each contract instance, making it easy for users to determine and inspect
different versions over time. To reconstruct the old experience (should you
need to) of querying one specific version, use a filter predicate in
the SQL.

.. code-block:: sql

    SELECT * 
      FROM active('mypackage:My.App:MyTemplate') 
      WHERE package_id = 'deadbeefpackageidhex'


Requirements
------------

Note that SCU is only available when the criteria below are met:

-  Canton 2.10.x or above

-  Daml LF Version 1.17 or above

-  Canton Protocol Version 7 or above

There are instructions below on how to configure this setup. The
sections below, unless explicitly stated otherwise, assume that this is
the case.

To prevent unexpected behavior, this feature enforces a unique package name and version for each DAR being
uploaded to a participant node.
This closes a loophole where the participant node allowed multiple DARs with
the same package name and version. For backward compatibility, this
restriction only applies for packages compiled with LF >= 1.17. If LF <
1.15 is used, there can be several packages with the same name and
version but this should be corrected; duplicate package names and versions are no longer supported.

Smart Contract Upgrade Basics
-----------------------------

To upgrade a package the package author modifies their existing
package to add new functionality, such as new fields and choices. When
the new package is uploaded to a participant with the old version, 
the participant ensures that every modification to the model in the
new version is a valid upgrade of the previous version.

To be able to automatically upgrade a contract or datatype, SCU
restricts the kinds of changes that a new package version can introduce
over its prior version.

For example, the simplest kind of data transformation that SCU supports
is adding a field to a template.

Given the following first version of a template:

.. code:: daml

  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
    where
      signatory issuer
      observer owner

You can add a new field for currency:

.. code:: daml

  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
      -- New field:
      currency: Optional String
    where
      signatory issuer
      observer owner

With SCU, any new template fields must be optional - templates from the
old version are automatically upgraded to new versions by setting the
new field to ``None``. This optional field requirement extends to all
records in your package. Conversely, newer contracts with this field set
to ``None`` can be automatically downgraded to previous versions of the
template in workflows that have not yet been updated.

Automatic Data Upgrades and Downgrades
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When extending data in a Daml model, SCU requires the old model to be
representable in the new model. For extending a record, we can
only add nullable (``Optional``) fields, so that old data can be represented
by setting these fields to ``None``. Similar constraints hold for
Variants and Enums, which only allow adding constructors, with some
other restrictions covered in `Continuing to Write Your Upgrades <#continuing-to-write-your-upgrades>`__. This
approach is inspired by
`Protobuf <https://protobuf.dev/programming-guides/proto3/#updating>`__
and Typescript's ability to ignore `excess
fields <https://www.typescriptlang.org/docs/handbook/2/objects.html#excess-property-checks>`__
via ``as``.

Automatic data upgrades occur in the following places:

**Submissions to the Ledger API**

When you submit a command, and provide only a package-name instead of a package-id,
Canton will automatically upgrade (or downgrade) the payloads you give to the most
recent version of the package that is uploaded on the participant. It
will also use the most recent implementation of any choices you exercise
directly through the Ledger API, by automatically upgrading/downgrading the choice argument.
Choice result upgrading/downgrading is handled by Consuming Clients, as discussed later in this section.
This behavior can be influenced by `package preference <#dynamic-package-resolution-in-ledger-api-queries>`__.

**Updates in a choice body**

When Fetching a contract, the contract payload will be automatically upgraded/downgraded to match
the version expected by the calling choice body, as compiled into the DAR.
When Exercising a choice on a contract, the contract payload will be upgraded/downgraded
to match the version of the choice expected by the calling choice body. This means
that in a choice body, an exercised choice argument or return type is never upgraded/downgraded.

**Consuming Clients (such as Daml Script, ts/java codegen)**

When clients query the Ledger API for contracts, the returned event
payload format matches the template originally used for generating the
event (creating a contract/exercising a choice). It is the
responsibility of these clients to upgrade/downgrade the payloads they
receive to match what is expected downstream. The same applies to choice
results. Daml Script, as well as ts/java codegen, does this for you to 
match the Ledger API response to the package versions they were run/built from.

Upgrading Across the Stack
--------------------------

These are all the components that interact with SCU,
and how you as a user should be aware that they interacts.

Canton
~~~~~~

When considering the Canton ledger nodes, only the Canton participant
node is aware of smart contract upgrading. The Canton domain nodes are
only concerned with the protocol version which must be at least 7 to allow connected participants to use upgradable Daml packages.

Below, we provide a brief overview of the interactions with the
participant node that have been adapted for supporting the smart
contract upgrading feature starting with Canton 2.10:

-  DAR upload requests go through an additional validation stage to
   check the contained new packages for upgrade-compatibility with
   other packages previously uploaded on the participant.

-  Ledger API command submissions can be automatically or explicitly
   up/downgraded if multiple upgrade-supported (language version >= 1.17) packages exist for the same package-name.

-  Ledger API streaming queries are adapted to support fetching events
   more generically, by package-name.

Code Generation
~~~~~~~~~~~~~~~

The Java and TypeScript CodeGen have been updated to perform upgrades on
retrieved contracts, and now use package-names over package-ids for
commands to the participant.

JSON API Server
~~~~~~~~~~~~~~~

To match the changes to the Ledger API, the JSON API similarly supports
package-name queries and command submission.

PQS & Daml Shell
~~~~~~~~~~~~~~~~

As of 2.9, PQS only supports querying contracts via package-name, 
dropping support for direct pacakge-id queries. See
`Limitations <#limitations>`__ for more information and a work-around.

Daml Shell builds on top of PQS, so inherits this behavior.

Daml Script
~~~~~~~~~~~

Support for SCU is available in the opt-in beta version of Daml Script.

This version acts as a drop-in replacement for the previous
Daml Script, and enables support for upgrades on all queries and
command submissions.

We also expose functions for more advanced interactions with
upgrades, as well as to revert to the previous submission behavior.

Daml Compiler
~~~~~~~~~~~~~

The Daml compiler supports the ``upgrades:`` configuration field - every
time ``daml build`` is invoked, it validates the current package for
upgrade compatibility against the package specified in the ``upgrades:``
field.

Validation emits custom error messages for common upgrading mistakes,
and warns the package author when upgrading a package in a potentially
unsafe way. Note however that this validation cannot be complete, as
upgrade validity depends on a participant’s package store. The
participant’s DAR upload checks have the final say on upgrade validity.

Limitations
-----------

To allow SCU to minimize downtime, and multiple versions
of a package to be active at once, we limit the types of
transformations that can be performed on live data. Following are some
data transformations that cannot be made using SCU upgrades:

-  Renaming, removal, or rearrangement of fields in a template

-  Conversion of records to variants and vice versa

-  Moving templates/datatypes to other modules

-  Upgrading interface and exception definitions

These restrictions are required to give a simple model of runtime
upgrades, avoiding ambiguity and non-obvious side effects. If you
require any of these types of changes, you may need to consider a
redeployment with downtime, using any of the tools listed in 
`What is Smart Contract Upgrade <#what-are-zero-downtime-smart-contract-upgrades>`__.

In this version of SCU, the following functionality has not yet
been implemented, but may be implemented in future releases.

-  Retroactive interface instances are not compatible with SCU upgrades.
   We do not expect to ever add this compatibility, as SCU supersedes retroactive
   interface instances

-  Daml Script does not support SCU, you must use Daml Script Beta.

-  Contract keys in upgradable packages can only include types defined
   within the same package, or types from the Daml Standard Library.

-  Upgrade compatibility checks currently run on all data types, even those which are
   not `serializable <https://github.com/digital-asset/daml/blob/main-2.x/sdk/daml-lf/spec/daml-lf-1.rst#serializable-types>`__.
   This check will be loosened in a future version.

The Programming Model by Example
================================

Writing Your First Smart Contract Upgrade
-----------------------------------------

Setup
~~~~~

We continue with the example introduced in `Smart Contract Upgrade Basics <#smart-contract-upgrade-basics>`__. Begin by defining the first (old) version
of our package:

.. code:: bash

  > mkdir -p v1/my-pkg
  > cd v1/my-pkg
  > daml init
  > daml version
  SDK versions:
    2.10.0  (project SDK version from daml.yaml)

Running ``daml version`` should print a line showing that 2.10.0 or higher is the "project SDK version from daml.yaml".

Add ``daml-script-beta`` to the list of dependencies in ``v1/my-pkg/daml.yaml``,
as well as ``--target=1.17`` to the ``build-options``:

.. code:: yaml
  
  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml-script-beta
  build-options:
  - --target=1.17

Then create ``v1/my-pkg/daml/Main.daml``:

.. code:: daml

  module Main where

  import Daml.Script

  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
    where
      signatory issuer
      observer owner
      key issuer : Party
      maintainer key


Running daml build should successfully produce a DAR in
``v1/my-pkg/.daml/dist/my-pkg-1.0.0.dar``:

.. code:: bash

  > daml build
  Running single package build of my-pkg as no multi-package.yaml was found.
  ...
  Compiling my-pkg to a DAR.
  ...
  Created .daml/dist/my-pkg-1.0.0.dar

Now you can create the second (new) version of this package, which
upgrades the first version. Navigate back to the root directory and copy
the v1 package into a v2 directory.

.. code:: bash

  > cd ../..
  > cp -r v1 v2
  > cd v2/my-pkg

Edit the ``daml.yaml`` to update the package version, and add the ``upgrades:``
field pointing to v1:

.. code:: yaml

  version: 1.1.0
  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml-script-beta
  upgrades: ../../v1/my-pkg/.daml/dist/my-pkg-1.0.0.dar
  build-options:
  - --target=1.17

Any changes you make to v2 are now validated as correct upgrades
over v1.


Adding a New Field
~~~~~~~~~~~~~~~~~~

Begin by adding a new ``currency`` field to ``v2/my-pkg/daml/Main.daml``:

.. code:: daml

  ...
  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
      currency: Text -- New field
    where
  ...

Run ``daml build``. An error is emitted:

.. code:: bash

  > daml build
  ...
  error type checking template Main.IOU :
    The upgraded template IOU has added new fields, but those fields are not Optional.
  ERROR: Creation of DAR file failed.

Any new fields added to a template must be optional - old contracts
from the previous version are automatically upgraded by setting new
fields to ``None``.

Fix the ``currency`` field to be optional, and re-run ``daml build``:

.. code:: daml

  ...
      currency: Optional Text -- New field
  ...

.. code:: bash

  > daml build
  ...
  Created .daml/dist/my-pkg-1.0.0.dar

The build may produce warnings about expression changes - this is
covered in the `Continuing to Write Your
Upgrades <#continuing-to-write-your-upgrades>`__ section.

Seeing Upgraded Fields in Contracts
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using the Daml Sandbox, we can see our old contracts automatically
upgrade.

Add a script to make and get IOUs to ``v1/my-pkg/daml/Main.daml``:

.. code:: daml

  module Main where

  import Daml.Script
  ...
  mkIOU : Script Party
  mkIOU = do
    alice <- allocateParty "alice"
    alice `submit` createCmd (IOU alice alice 1)
    pure alice

  getIOU : Party -> Script (Optional (ContractId IOU, IOU))
  getIOU key = queryContractKey @IOU key key

Open ``v2/my-pkg/daml/Main.daml`` and add scripts to make IOUs with and
without a currency field, and a script to get any IOU:

.. code:: daml

  module Main where

  import Daml.Script
  ...
  mkIOU : Script Party
  mkIOU = do
    alice <- allocateParty "alice"
    alice `submit` createCmd (IOU alice alice 1 (Some "USD"))
    pure alice

  mkIOUWithoutCurrency : Script Party
  mkIOUWithoutCurrency = do
    alice <- allocateParty "alice"
    alice `submit` createCmd (IOU alice alice 1 None)
    pure alice

  getIOU : Party -> Script (Optional (ContractId IOU, IOU))
  getIOU key = queryContractKey @IOU key key

Start a new terminal, run ``daml sandbox`` to start a simple ledger in which
to test upgrades.

.. code:: bash

  > daml sandbox
  Starting Canton sandbox.
  Listening at port 6865
  Canton sandbox is ready.

Start another terminal, separately from the terminal in which the
sandbox is running. From inside ``v1/my-pkg``, upload and run the ``mkIOU``
script and place the resulting party for Alice into an output file
``alice-v1``:

.. code:: bash

  > cd v1/my-pkg
  > daml ledger upload-dar --port 6865
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:mkIOU \
      --output-file alice-v1
  ...

From inside ``v2/my-pkg``, upload and run the ``getIOU`` script, passing in the
``alice-v1`` file as the script’s input:

.. code:: bash

  > cd ../../v2/my-pkg
  > daml ledger upload-dar --port 6865
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.1.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file ../../v1/my-pkg/alice-v1
  ...
  {
    "_1": "...",
    "_2": {
    "issuer": "party-...",
    "owner": "party-...",
    "value": 1,
    "currency": null
    }
  }
  ...

The returned contract has a field ``currency`` which is set to ``null``. When
running the ``getIOU`` script from v1, this field does not appear.

.. code:: bash

  > cd ../../v1/my-pkg
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file alice-v1
  ...
  {
    "_1": "...",
    "_2": {
    "issuer": "party-...",
    "owner": "party-...",
    "value": 1
    }
  }
  ...

Downgrading Contracts
~~~~~~~~~~~~~~~~~~~~~

New contracts cannot be downgraded if they have a value in their
Optional fields. Create a new v2 IOU contract from the ``v2/my-pkg``
directory, with ``USD`` as currency:

.. code:: bash

  > # Create a new v2 IOU contract, with USD as currency
  > cd ../../v2/my-pkg
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.1.0.dar \
      --script-name Main:mkIOU \
      --output-file alice-v2
  ...

Query it from a v1 script in the ``v1/my-pkg`` directory:

.. code:: bash

  > # Query from v1 package
  > cd ../../v1/my-pkg
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file ../../v2/my-pkg/alice-v2
  ...
  Exception in thread "main" com.daml.lf.engine.script.Script$FailedCmd: Command QueryContractKey failed: Failed to translate create argument:
  ...
  An optional contract field with a value of Some may not be dropped during downgrading.

The error states that the optional field may not be dropped during
downgrading.

Contracts created in a workflow from a v2 package may be used if the
optional, upgraded fields are set to ``None``. For example, create an IOU
with the currency field set to ``None`` using ``mkIOUWithoutCurrency``:

.. code:: bash

  > # Create a new v2 IOU contract, without USD as currency
  > cd ../../v2/my-pkg
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.1.0.dar \
      --script-name Main:mkIOUWithoutCurrency \
      --output-file alice-v2
  ...

And then query it from v1:

.. code:: bash

  > # Query from v1 package
  > cd ../../v1/my-pkg
  > daml script \
  	--ledger-host localhost --ledger-port 6865 \
  	--dar .daml/dist/my-pkg-1.0.0.dar \
  	--script-name Main:getIOU \
  	--output-file /dev/stdout \
  	--input-file ../../v2/my-pkg/alice-v2
  ...
    "issuer": "party-...",
  	"owner": "party-...",
  	"value": 1
  ...

In this case, the query from v1 succeeded because all upgraded fields
are set to ``None``.

Adding a Choice
~~~~~~~~~~~~~~~

SCU also allows package authors to add new choices - add the
example choice ``Double`` to ``v2/my-pkg/daml/Main.daml``, which archives
the current contract and produces a new one with twice the value.

.. code:: daml

  ...
      maintainer key
      choice Double : ContractId IOU
          controller issuer
          do create this with value = value * 2
  ...

Along with a script to call it.

.. code:: daml

  import DA.Optional (fromSome)

  ...

  doubleIOU : Party -> Script IOU
  doubleIOU alice = do
    oIOU <- getIOU alice
    case oIOU of
      Some (cid, _) -> do
        newCid <- alice `submit` exerciseCmd cid Double
        fromSome <$> queryContractId alice newCid
      None -> fail "Failed to find IOU"

Compiled changes are checked against the previous version and pass:

.. code:: bash

  > daml build
  ...
  Compiling my-pkg to a DAR.
  ...
  Created .daml/dist/my-pkg-1.1.0.dar
  ...

Restart the sandbox and re-upload both v1 and v2:

.. code:: bash

  > cd v1/my-deps
  > daml ledger upload-dar --port 6865
  > # Make a new IOU
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:mkIOU \
      --output-file alice-v1
  ...
  > cd ../../v2/my-deps
  > daml ledger upload-dar --port 6865
  ...
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.1.0.dar \
      --script-name Main:doubleIOU \
      --output-file /dev/stdout \
      --input-file ../../v1/my-pkg/alice-v1
  ...
  	"issuer": "party-...",
  	"owner": "party-...",
  	"value": 2,
  	"currency": null
  ...

Contracts made in v1 can now be exercised with choices introduced in
v2.

Exercising a v1 choice on a v2 contract is also possible if upgraded
fields are set to ``None``, but this requires a different script function -
replace the use of ``exerciseCmd`` with ``exerciseExactCmd`` in the body of
``doubleIOU`` in v1, and restart your sandbox.

.. code:: bash

  > # Replace exerciseCmd with exerciseExactCmd in v1
  > # Do it using your editor, or use `sed`
  > sed -i -E 's/exerciseCmd/exerciseExactCmd/g' \
      v1/my-pkg/daml/Main.daml

Once you’ve restarted your sandbox, create an IOU without a currency in
V2 via ``mkIOUWithoutCurrency``, then run ``doubleIOU`` on it from V1:

.. code:: bash

  > # Create a new v2 IOU contract, without USD as currency
  > cd v2/my-pkg
  > daml ledger upload-dar --port 6865
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.1.0.dar \
      --script-name Main:mkIOUWithoutCurrency \
      --output-file alice-v2
  > cd ../../v1/my-pkg
  > daml ledger upload-dar --port 6865
  > daml script \
  	--ledger-host localhost --ledger-port 6865 \
  	--dar .daml/dist/my-pkg-1.0.0.dar \
  	--script-name Main:doubleIOU \
  	--output-file /dev/stdout \
  	--input-file ../../v2/my-pkg/alice-v2
  ...
  	"issuer": "party-...",
  	"owner": "party-...",
  	"value": 2
  ...

Existing choices can also be upgraded, as covered in
`Continuing to Write Your Upgrades <#continuing-to-write-your-upgrades>`__.

Deploying Your First Upgrade
----------------------------

Configuring Canton to Support Smart Upgrading
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When using the feature one must
temporarily configure Canton nodes to :ref:`enable beta version support <how-do-i-enable-beta-features>`.

Using Smart Contract Upgrading Enabled Packages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once you have finished development of your smart contract app, use the
mentioned upgrade-enabled options in daml.yaml to compile and generate
the related DAR. This can be uploaded using the existing gRPC endpoints
without modifications and is immediately available for use.

.. note::

  In 2.10, once a DAR is successfully uploaded, it cannot be
  safely removed from the participant node. Participant operators must
  then ensure that uploaded functionality does not break the intended
  upgrade lineage as newly uploaded DARs affect the upgrading line (i.e.
  all subsequent uploads must be compatible with this one as well).

.. note::

  Upgrade-supported packages stored on the participant must
  lead to unique package-id -> (package-name, package-version) relationships
  since runtime package-name -> package-id
  resolution must be deterministic (see `Ledger API <#ledger-api>`__). For this
  reason, once a LF 1.17+ DAR has been uploaded with its main package
  having a specific package-name/package-version, this relationship cannot
  be overridden. Hence, uploading a DAR with different content for the
  same name/version as an existing DAR on the participant leads to a
  rejection with error code KNOWN_DAR_VERSION.

Validate the DAR Against a Running Participant Node
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Starting with 2.9 you can validate your DAR against the current
participant node state without uploading it to the participant via the
``PackageManagementService.validateDar`` Ledger API endpoint. This allows
participant node operators to first check the DAR before uploading it.

This operation is also available via the Canton Admin API and Console:

.. code::

  participant.dars.validate("dars/CantonExamples.dar")

Upgrading and Package Vetting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Upgradable packages are also subject to :ref:`package vetting
restrictions <package_vetting>`:
in to be able to use a package in Daml transactions with smart
contract upgrading, it must be vetted by all participants informed about
the transaction. This applies to both the packages used for creating
the contracts and the target packages.

**Note:** Package vetting is enabled by default on DAR upload
operations.

Continuing to Write Your Upgrades
---------------------------------

SCU allows package authors to change many more aspects of their packages
- fields can be extended in templates, choices, and data type
definitions. Choice bodies can be changed, and other expressions such as
key definitions and signatory lists can be changed with caveats.

.. _setup-1:

Setup
~~~~~

Continue the package defined in the `Writing Your First
Upgrade <#writing-your-first-upgrade>`__ section above, but overwrite
the v1 and v2 IOU modules. The v1 IOU module should be overwritten as follows:

.. code:: daml

  module Main where
  
  import Daml.Script
  
  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
    where
      signatory issuer
      observer owner
      key issuer : Party
      maintainer key
  
  mkIOU : Script Party
  mkIOU = do
    alice <- allocateParty "alice"
    alice `submit` createCmd (IOU alice alice 1)
    pure alice
  
  getIOU : Party -> Script (Optional (ContractId IOU, IOU))
  getIOU key = queryContractKey @IOU key key

The v2 IOU module should be overwritten to look like the following:

.. code:: daml

  module Main where
  
  import Daml.Script
  import DA.Optional (fromOptional)
  
  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
      currency: Optional Text
    where
      signatory issuer
      observer owner
      key issuer : Party
      maintainer key
  
  mkIOU : Script Party
  mkIOU = do
    alice <- allocateParty "alice"
    alice `submit` createCmd (IOU alice alice 1 (Some "USD"))
    pure alice
  
  mkIOUWithoutCurrency : Script Party
  mkIOUWithoutCurrency = do
    alice <- allocateParty "alice"
    alice `submit` createCmd (IOU alice alice 1 None)
    pure alice
  
  getIOU : Party -> Script (Optional (ContractId IOU, IOU))
  getIOU key = queryContractKey @IOU key key

All other files should remain the same.

Changing Choices
~~~~~~~~~~~~~~~~

Add the following choice, ``Duplicate``, to both v1 and v2 versions of IOU:

.. code:: daml

      data DuplicateResult = DuplicateResult with
        newCid : ContractId IOU

      choice Duplicate : DuplicateResult
        controller issuer
        do
          cid <- create this with value = value * 2
          return DuplicateResult with newCid = cid

Running ``daml build`` should succeed without errors.

.. code:: bash

  > cd v1/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.0.0.dar
  > cd ../../v2/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.1.0.dar

Next, upgrade the ``Duplicate`` choice by adding an optional field ``amount``,
and changing the behavior of the choice to default to a multiple of 3. Also
upgrade the ``DuplicateResult`` data type to include the old value.
Replace the definitions of the ``DuplicateResult`` data type and of the
``Duplicate`` choice in v2 only:

.. code:: daml

  ...
  -- Add import to top of module
  import DA.Optional (fromOptional)
  ...
  -- Replace DuplicateResult definition
  data DuplicateResult = DuplicateResult with
    newCid : ContractId IOU
    oldValue : Optional Int -- New optional oldValue field
  ...
     -- Replace Duplicate choice implementation
     choice Duplicate : DuplicateResult
       with
         amount : Optional Int -- New optional amount
       controller issuer
       do
         let amt = fromOptional 3 amount
         cid <- create this with value = value * amt
         return DuplicateResult with
           newCid = cid
           oldValue = Some value
  ...

Add a script called ``duplicateIOU`` in V1:

.. code:: daml

  ...
  duplicateIOU : Party -> Script (Optional (ContractId IOU, IOU))
  duplicateIOU key = do
    mbIOU <- getIOU key
    case mbIOU of
      None -> pure None
      Some (iouCid, _) -> do
        res <- key `submit` exerciseExactCmd iouCid Duplicate
        mbNewIOU <- queryContractId key res.newCid
        case mbNewIOU of
          Some newIOU -> pure (Some (newCid, newIOU))
          None -> pure None

A similar script called ``duplicateIOU`` should be added in V2, supplying an
``amount`` field:

.. code:: daml

  ...
  duplicateIOU : Party -> Script (Optional (ContractId IOU, Int, IOU))
  duplicateIOU key = do
    mbIOU <- getIOU key
    case mbIOU of
      None -> pure None
      Some (iouCid, _) -> do
        res <- key `submit` exerciseExactCmd iouCid Duplicate { amount = Some 4 }
        case res.oldValue of
          None -> pure None -- This should never happen
          Some oldValue -> 
            mbNewIOU <- queryContractId key res.newCid
            case mbNewIOU of
              Some newIOU -> pure (Some (newCid, oldValue, newIOU))
              None -> pure None

Running the v1 ``duplicateIOU`` script with ``exerciseExactCmd`` always runs
the v1 implementation for the ``Duplicate`` choice, and likewise for v2.

Modifying Signatory Definitions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Other definitions can be changed, but warnings are emitted to remind the
developer that the changes can be unsafe and need to be made with care
to preserve necessary invariants.

Signatories and observers are one expression that can be changed.
Importantly, SCU assumes that the new definition does not alter the
computed values of the signatories, observers, and key for existing contracts.
Otherwise, dynamic contract upgrades will fail at runtime.

For example, add a new field of "outside observers" to the v2 IOU
template, and add them to the observer definition.

.. code:: daml

  ...
      -- Add a new outsideObservers field
      outsideObservers: Optional [Party]
    where
      signatory issuer
      -- Add outsideObservers to the observer definition
      observer owner, fromOptional [] outsideObservers
  ...

The new observer definition allows v2 contracts and beyond to add
new observers via the outsideObservers field. However, any existing
contracts default to ``None`` for the ``outsideObservers`` field, so all
existing contracts have the same observer list as before: the
single owner.

In the case where a contract's signatories or observers change during an upgrade/downgrade,
the upgrade, and thus full transaction, fails at runtime.

Modifying Key Expressions
~~~~~~~~~~~~~~~~~~~~~~~~~

Similarly, key expressions can be changed as long as they evaluate to
the same value for existing contracts. This means that the type of the key
cannot change.

For example, v2 can add a new field "alternative key" to the v2 IOU
template, and use it instead of the default key when present.

.. code:: daml

  ...
      -- Add a new alternativeKey field
      alternativeKey: Optional Party
    where
      key fromOptional issuer alternativeKey
  ...

All old contracts will default to using the ``issuer``, and new contracts
will use the ``alternativeKey`` field.
Note also that key expressions in upgrabable packages cannot include types
from other packages, with the exception of the Daml Standard Library.
See `Limitations <#limitatiions>`__ for more information.

Upgrading Enums
~~~~~~~~~~~~~~~

Variants and enums can be extended using SCU, either by adding
fields to an existing constructor, or by adding a new constructor to the
end of the list.

Redefine the IOU package, overwriting the v1 and v2 sections similarly
to the previous section. Overwrite the IOU package in both V1 and V2
with the following:

.. code:: daml

  module Main where
  
  import Daml.Script
  
  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
      currency: Currency
    where
      signatory issuer
      observer owner
      key issuer : Party
      maintainer key
  
  data Currency
    = USD
    | GBP
    deriving (Show, Eq, Ord)
  
  mkIOU : Script Party
  mkIOU = do
    alice <- allocateParty "alice"
    alice `submit` createCmd (IOU alice alice 1 USD)
    pure alice
  
  getIOU : Party -> Script (Optional (ContractId IOU, IOU))
  getIOU key = queryContractKey @IOU key key

Instead of using ``Text`` for the currency field, here we use an enum
data-type ``Currency`` with two constructors: ``USD`` and ``GBP``.

Running ``daml build`` should succeed with no errors:

.. code:: bash

  > cd v1/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.0.0.dar
  > cd ../../v2/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.1.0.dar

When you want to extend our contract to support new currencies, you can
add new entries to the end of our ``Currency`` enum.

.. code:: daml

  ...
  data Currency
    = USD
    | GBP
    | CHF -- Add a new currency type
    deriving (Show, Eq, Ord)
  ...

Upgrades of extended enums from an old version to a new version always succeed. In the case of IOUs, a v1 IOU can always be interpreted
as a v2 IOU because the constructors for its ``currency`` field are a subset
of those in a v2 contract.

For example, create an IOU with USD via v1’s ``mkIOU`` script, and query it
via v2’s ``getIOU`` script:

.. code:: bash

  > cd v1/my-pkg
  > daml script
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:mkIOU \
      --output-file alice-v1
  ...
  > cd ../../v2/my-pkg
  > daml script
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.1.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file ../../v1/my-pkg/alice-v1
  ...
      "issuer": "party-...",
      "owner": "party-...",
      "value": 1,
      "currency": "USD"
  ...

Only constructors that are defined in both
v1 and v2 can be downgraded from v2 to v1. Any constructor that does not
exist in the v1 package fails to downgrade with a runtime error. In
the case of our ``IOU``, any ``CHF`` fails to downgrade, so any v2 contracts
with a ``CHF`` currency cannot be used in v1 workflows.

For example, create a contract with ``CHF`` as its ``currency`` field via v2’s
``mkIOU`` script. Attempting to query it via v1’s ``getIOU`` script fails
with a lookup error for the CHF variant.

.. code:: bash

  > cd v2/my-pkg
  > daml script
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.1.0.dar \
      --script-name Main:mkIOU \
      --output-file alice-v2
  ...
  > cd ../../v1/my-pkg
  > daml script
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file ../../v2/my-pkg/alice-v2
  ...
  Failed to translate create argument: Lookup(NotFound(DataVariantConstructor(c1543a5c2b7ff03650162e68e03e469d1ecf9f546565d3809cdec2e0255ed902:Main:Currency,CHF),DataEnumConstructor(c1543a5c2b7ff03650162e68e03e469d1ecf9f546565d3809cdec2e0255ed902:Main:Currency,CHF)))
  ...

Upgrading Variants
~~~~~~~~~~~~~~~~~~

Variants, also known as algebraic data types, are very similar to enums
except that they also contain structured data.

For example, the following variant has two constructors, each with
unique fields. Overwrite both v1 and v2 modules with the following
source:

.. code:: daml

  module Main where
  
  data Shape
    = Circle
    | Polygon { sides : Int }

You can extend this variant in two ways. You can add a new constructor,
similarly to enums. Modify the v2 module to add a new ``Line`` constructor
with a ``len`` field:

.. code:: daml

  module Main where
  
  data Shape
    = Circle
    | Polygon { sides : Int }
    | Line { len : Numeric 10 } -- New line constructor

As before, building should succeed.

.. code:: bash

  > cd v1/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.0.0.dar
  > cd ../../v2/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.1.0.dar

You can also add a new field to a constructor, similarly to templates -
for example, add a ``sideLen`` field to the ``Polygon`` constructor, to specify
the lengths of the sides of the polygon.

.. code:: daml

  data Shape
    = Circle
    | Polygon
        { sides : Int
        , sideLen : Numeric 10 -- New field
        }
    | Line { len : Numeric 10 }

Building this fails because the new ``sideLen`` field is non-optional.

.. code:: bash

  > cd v2/my-pkg
  > daml build
  ...
  error type checking data type Main.Shape:
    The upgraded variant constructor Polygon from variant Shape has added a field.
  ERROR: Creation of DAR file failed.

Making the new ``sideLen`` field optional fixes the error:

.. code:: daml

  ...
        , sideLen : Optional (Numeric 10) -- New field
  ...

.. code:: bash

  > cd v2/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.1.0.dar

Limitations in Upgrading Variants
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Upgrading variants has some limitations - because the ``Circle``
constructor has been defined without a field in curly braces, it cannot be
upgraded with new fields.

.. code:: daml

  ...
    -- Add a field where no fields existed
    = Circle { radius : Optional (Numeric 10) }
  ...

.. code:: bash

  > cd v2/my-pkg
  > daml build
  ...
  error type checking data type Main.Shape:
    The upgraded data type Shape has changed the type of a variant.
  ERROR: Creation of DAR file failed.

The same applies to variants with unnamed fields. If the v1 definition
of the ``Line`` constructor were as follows, it would also not be able to
upgrade:

.. code:: daml

  ...
    | Line (Numeric 10)

In general, in order to enable future upgrades, it is strongly
recommended that all constructors use named fields, and that all
constructors have at least one field. If a constructor has no fields in
an initial v1 package, one can assign a dummy field.

For example, the correct way to write the v1 ``Circle`` constructor would be
as follows:

.. code:: daml

  ...
    = Circle { dummy : () }
  ...

The subsequent v2 upgrade would succeed:

.. code:: daml

  ...
    = Circle { dummy : (), radius : Optional (Numeric 10) }
  ...

Nested Datatypes
~~~~~~~~~~~~~~~~

If a data type, choice, or template has a field which refers to another
data type, the larger data type can be upgraded if the field’s data
type is upgradeable.

For example, given the data type ``A`` with a field referring to data type
``B``,

.. code:: daml

  data A = A { b : B }
  data B = B { field : Text }

If modifications made to ``B`` are valid for SCU, then ``A`` is also valid.

Dependencies
~~~~~~~~~~~~

Package authors may upgrade the dependencies of a package as well as the
package itself. A new version of a package may add new dependencies, and
must have all the (non-:ref:`utility-package <upgrades-utility-package>`)
dependencies of the old version. Each of these existing dependency
must either be unchanged from the old dar, or an upgrade of its previous
version.

For example, given a dependencies folder, containing v1 and v2
of two dependency packages ``depA`` and ``depB``

.. code:: bash

  > ls ./dependencies
  depA-1.0.0.dar
  depA-1.1.0.dar
  depB-1.0.0.dar
  depB-1.1.0.dar

Change v1 of the IOU package so that it depends on ``depA-1.0.0`` and
``depB-1.1.0``. Its ``v1/my-pkg/daml.yaml`` would look something like this:

.. code:: yaml

  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml3-script
  - ../../dependencies/depA-1.0.0.dar
  - ../../dependencies/depB-1.1.0.dar
  ...

A package with a newer version may upgrade any dependency to a newer
version (or keep the version the same). For example, v2 of the IOU
package may keep its dependencies the same, or it may upgrade ``depA`` to
``1.1.0``:

.. code:: yaml

  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml3-script
  - ../../dependencies/depA-1.1.0.dar
  - ../../dependencies/depB-1.1.0.dar
  ...

Downgrading a dependency is not permitted. For example, IOU may not
downgrade ``depB`` to version ``1.0.0``. The following ``daml.yaml`` would be
invalid:

.. code:: yaml

  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml3-script
  - ../../dependencies/depA-1.0.0.dar
  - ../../dependencies/depB-1.0.0.dar
  ...

At the moment, ``daml build`` does not check for valid dependencies - checks
are instead performed at upload time to a participant.

.. code:: bash

  > cd v1/my-pkg
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  DAR upload succeeded.
  > cd ../../v2/my-pkg
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.1.0.dar to localhost:6865
  upload-dar did not succeed: DAR_NOT_VALID_UPGRADE(...): The DAR contains a package which claims to upgrade another package, but basic checks indicate the package is not a valid upgrade
  ...

Upgrading Interface Instances
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SCU also supports changing Interface instances. First, create a
new package directory ``my-iface``, with ``my-iface/daml.yaml`` and
module ``my-iface/daml/MyIface.daml``:

.. code:: yaml

  sdk-version: 0.0.0
  name: my-iface
  version: 1.0.0
  source: daml/MyIface.daml
  parties:
  - Alice
  - Bob
  dependencies:
  - daml-prim
  - daml-stdlib
  build-options:
  - --target=1.17

.. code:: daml

  module MyIface where
  
  data HasValueView = HasValueView { hasValueView : Int }
  
  interface HasValue where
    viewtype HasValueView
    getValue : Int

And build the module:

.. code:: bash

  > cd my-iface
  > daml build
  ...
  Created .daml/dist/my-iface-1.0.0.dar

Add references to the newly created DAR in both ``v1/my-pkg/daml.yaml`` and
``v2/my-pkg/daml.yaml``:

.. code:: yaml

  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml3-script
  - ../../my-iface/.daml/dist/my-iface-1.0.0.dar
  ...

Overwrite both ``v1/my-pkg/daml/Main.daml`` and ``v2/my-pkg/daml/Main.daml``
with the following:

.. code:: daml

  module Main where
  
  import Daml.Script
  import MyIface
  
  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
    where
      signatory issuer
      observer owner
      key issuer : Party
      maintainer key

      interface instance HasValue for IOU where
        view = HasValueView value
        getValue = value

Interface instances can be changed by an upgrade. For example, v2 can
change the definition of ``getValue`` in the ``HasValue`` instance.

Add a ``quantity`` field to the v2 IOU package, and amend the definition of
``getValue`` to use it:

.. code:: daml

  ...
  import DA.Optional (fromOptional)
  
  template IOU
    with
      issuer: Party
      owner: Party
      value: Int
      quantity: Optional Int -- new quantity field
    where
  ...
      interface instance HasValue for IOU where
        view = HasValueView (value * fromOptional 1 quantity)
        -- Use quantity field to calculate value
        getValue = value * fromOptional 1 quantity

Shut down and relaunch the Daml sandbox, then build and upload the two
DARs. They should both succeed again:

.. code:: bash

  > cd v1/my-pkg
  > daml build
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  DAR upload succeeded.
  > cd ../../v2/my-pkg
  > daml build
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.1.0.dar to localhost:6865
  DAR upload succeeded.

Packages with new versions cannot remove an instance that is already
there. For example, the v2 IOU template cannot remove its instance of
``HasValue``. Comment out the interface instance for ``HasValue`` from
``v2/my-pkg/daml/Main.daml`` completely, then restart the sandbox and try to
reupload the two versions:

.. code:: bash

  > cd v1/my-pkg
  > daml build
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  DAR upload succeeded.
  > cd ../../v2/my-pkg
  > daml build
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-2.0.0.dar to localhost:6865
  upload-dar did not succeed: ... Implementation of interface ...:MyIface:HasValue by template IOU appears in package that is being upgraded, but does not appear in this package.

Packages with new versions cannot add an interface instance to an existing
template either. For example, restore the instance deleted in the previous step
and remove the ``HasValue`` interface from ``v2/my-pkg/daml/Main.daml`` instead.
Then restart the sandbox and try to reupload the two versions.

.. code:: bash

  > cd v1/my-pkg
  > daml build
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  DAR upload succeeded.
  > cd ../../v2/my-pkg
  > daml build
  > daml ledger upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-2.0.0.dar to localhost:6865
  upload-dar did not succeed: ... Implementation of ...:MyIface:HasValue by template IOU appears in this package, but does not appear in package that is being upgraded.

Similarly to choices, scripts may invoke interface implementations from
their own version using ``exerciseExactCmd``.

Upgrading Interfaces
~~~~~~~~~~~~~~~~~~~~

Interface instances may be upgraded, but interface definitions cannot be
upgraded. If an interface definition is present in v1 of a package, it must be
removed from all subsequent versions of that package.

Because interfaces definitions may not be defined in subsequent versions, any
package that uses an interface definition from a dependency package can never
upgrade that dependency to a new version.

For this reason, it is strongly recommend that interfaces always be defined
in their own packages separately from templates.

Best Practices
--------------

To ensure that future upgrades and DAR lifecycling go smoothly, we
recommend the following practices:

Separate Interfaces/Exceptions from Templates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Interface and exception definitions are not upgradable. As such, if you attempt
to redefine an interface or exception in version 2 of a package, even if it is
unchanged, the package does not type check. Removing an interface from the
version 2 package also causes issues, especially if the interface has
choices.

Instead, move interface and exception definitions out into a separate package
from the start, such that subsequent versions of your package with templates all
depend on the same version of the package with interfaces/exceptions. The SCU
type checker warns about this, but you should see this warning as an error - it
is very strongly recommended that you do not compile interfaces or exceptions in
a package alongside templates.

Remove Retroactive Instances
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SCU eliminates the need for retroactive instances and is not
compatible with them. To ensure package selection for interface choices
acts correctly, retroactive interface instances should be moved to newer
versions of templates, such that changes to the instance warrants a new
version of the template.

Explicit Template Versions
~~~~~~~~~~~~~~~~~~~~~~~~~~

If you need package version specific behavior that cannot just depend on
the presence or absence of new fields, then one workaround would be to
tag your contracts in their payload with an explicit version field.
This allows for less fragile behavior in the event of
"partial upgrades" (where a user may only upgrade part of the payload of
a package, intentionally), and allows you to model rollbacks as upgrades
in a principled manner.

Avoid Contract Metadata Changes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The signatories, observers, contract key and ensure clauses of a
contract should be fixed at runtime for a given contract. Changing their
definitions in your Daml code triggers a warning from the SCU
typechecker, and is discouraged. Note that for contract keys, the type
cannot change at all, only its value. Should you need to change these
values, be aware that if their runtime value changes in any way, the
upgrade, and thus the full transaction, fails. Contracts in this
state can then only be used by explicitly choosing the older version of
the contract in your transaction.

Migration
---------

SCU is only supported on LF1.17, which in turn is only supported on
Canton Protocol Version 7. This means that existing deployed contracts require migration and redeployment to utilize this feature.

First you must migrate your Daml model to be compatible with
upgrades; see `Best Practices <#best-practices>`__ for what to
change here. Pay particular attention to the case of interfaces and
exceptions, as failure to do so could lead to packages which are
incompatible with SCU and require the use of a separate tool (and
downtime).

Next, you need to be aware of the new package-name scoping rules, and
ensure that your package set does not violate this. In short, LF1.17 packages
with the same package-name are unified under SCU, so you should ensure that
all of your packages that aren't intended to be direct upgrades of each-other
have unique package-names.
Note also that within a given package-name, only one package for each version
can exist.
LF1.15 packages are not subject to this restriction, and can exist alongside LF1.17
packages.

Once you have your new DARs, you need to upgrade your Canton and
protocol version together, since 2.10 introduces a new protocol version.
The steps to achieve this are given in the :ref:`Canton Upgrading
manual <one_step_migration>`.

Finally, you can migrate your live data from your previous DARs to the
new LF1.17 DARs, using one of the existing downtime upgrade techniques
listed :ref:`here <upgrades-index>`.

The Upgrade Model in Depth - Reference
--------------------------------------

You can find the in-depth upgrading model, which can be used as a reference
for valid upgrades, :ref:`here <upgrade-model-reference>`.

Components
==========

Ledger API
----------

Until the introduction of SCU, templates in requests on the Ledger API
could only be referenced by the template-id, with the template fully
qualified name of format ``<package-id>:<module-name>:<template-name>``.

With SCU, we introduce a more generic template reference of the format
``#<package-name>:<module-name>:<template-name>``. This format is only a
Ledger API concept and is meant to suggest to the Ledger API to perform
a dynamic runtime resolution of packages in the Daml engine when
generating the Daml transaction before command interpretation. This
dynamic resolution is based on the existing upgradable (LF >= 1.17)
package-ids pertaining to a specific ``package-name`` and is possible on the
write path (command submission) and read path (Ledger API queries) as
presented below.

.. _dynamic-package-resolution-in-command-submission:

Dynamic Package Resolution in Command Submission
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Dynamic package resolution can happen in two cases during command
submission:

-  For command submissions that use the package-name selector
   (``#<package-name>``) in the command’s templateId field (e.g. in a
   create command :ref:`here <com.daml.ledger.api.v1.CreateCommand>`)

-  For command submissions leading to Daml transactions that contain
   actions exercised on interfaces. In this situation there may be
   many versions of a template that implement the interface being
   exercised.

In these situations the following rules are followed to resolve the
package-name to a package-id:

-  By default, the participant resolves a package-name to the package-id
   pertaining to the highest package version uploaded

-  The command submitter can override the above-mentioned default
   participant resolution by pinning package-ids in the Command’s
   :ref:`package_id_selection_preference <com.daml.ledger.api.v1.Commands.package_id_selection_preference>`.
   More specifically, this field is a list of package-ids that must
   be explicitly used when resolving package-name *ambiguities* in
   either command template-id or interface resolution.

   - See :ref:`here <daml-script-package-preference>` for how to provide this in Daml-Script

   -  **Note:** The Command’s
      :ref:`package_id_selection_preference <com.daml.ledger.api.v1.Commands.package_id_selection_preference>`
      must not lead to ambiguous resolutions for package-names,
      meaning that it must not contain two package-ids pointing to
      packages with the same package-name, as otherwise the submission will fail with
      an ``INVALID_ARGUMENT`` error

Dynamic Package Resolution in Ledger API Queries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When subscribing for
:ref:`transaction <transaction-trees>`
or :ref:`active contract streams <active-contract-service>`,
users can now use the ``#<package-name>`` selector in the template-id format
to specify that they’re interested in fetching events for all templates
pertaining to the specified package-name. This template selection set is
dynamic and it widens with each uploaded template/package.

**Note:** The by-package-name query mechanism described here does not
apply to events sourced from non-upgradable templates (coming from
packages with LF < 1.17)

Example
^^^^^^^

Given the following packages with LF 1.17 existing on the participant
node:

-  Package AppV1

   -  package-name: ``app1``

   -  package-version: ``1.0.0``

   -  template-ids: ``pkgId1:mod:T``

-  Package AppV2

   -  package-name: ``app1``

   -  package-version: ``1.1.0``

   -  template-ids: ``pkgId2:mod:T``

If a transaction query is created with a templateId specified as
``#app1:mod:T``, then the events stream will include events from both
template-ids: ``pkgId1:mod:T`` and ``pkgId2:mod:T``

Codegen
-------

For packages that support SCU (i.e. LF1.17), generated code uses
package-names in place of package-ids in template IDs. Retrieved data
from the ledger is subject to the upgrade transformations described
in previous sections.

Concretely, this is implemented as follows:

Java
~~~~

The classes that are generated for each template and interface contain a
``TEMPLATE_ID`` field, which, for upgradable packages, now use a
package name rather than a package ID. To help you determine
the package ID of these packages, we have added a new ``PACKAGE_ID`` field to all
such classes. Upgradable packages also cause ``PACKAGE_NAME`` and
``PACKAGE_VERSION`` fields to be present.

TypeScript
~~~~~~~~~~

The ``templateId`` field on generated template classes has been updated to
use the package-name as the package qualifier for upgrade compatible
packages. This is used for command submission and queries. However,
note that the package qualifier given back in queries contains the
package-id, rather than the package-name. Generated modules now also
give the package "reference", which is the package-name for upgrade-compatible packages; for other packages it is the package-id.

To perform package-id qualified commands/queries in an upgrade
compatible package, a copy of the template object can be created using
the following:

.. code:: typescript

  const MyTemplateWithPackageId = { 
    ...pkg.Mod.MyTemplate,
    templateId: `${pkg.packageId}:Mod:MyTemplate`,
  }

.. _json-api-server-1:

JSON API Server
----------------

Template IDs may still be used with a package ID, however,
for packages built as LF 1.17 or greater, the package may also be
identified by name. That is to say, for upgradable packages a template ID can have
the form ``#<package-name>:<module-name>:<template-name>``, and this is
resolved to corresponding templates from all packages which share this
name, and are built at 1.17 or above. For packages built at LF 1.15,
the templates are not identifiable via a package name, and a
package ID must be used.

Note: template IDs in query results always use a package ID. This
allows us to distinguish the source of a particular contract. This means
that if you use a template with a package name in the request, you can
no longer expect the template IDs in the result to exactly match the
input template ID.

Package ID selection preference: preferences apply to JSON API where you
can specify your preferred selection of package versions.

PQS
---

To match the package-name changes to the Ledger API, PQS has changed how packages
are selected for queries. All queries that take a Daml identity in the form 
``<package-id>:<module-name>:<template-name>`` now take a package-name in place 
of package-id. Note that this differs from the Ledger API in that the `#` prefix
is not required for PQS, as PQS has dropped direct package-id queries.
Queries for package-names will return all versions of a given contract, alongside the
package-version and package-id for each contract.

.. note::
  If you still need to perform a query with an explicit package-id, you can either use
  a previous version of PQS, or add the following filter predicate to your query:
  ``SELECT \* FROM active('my_package:My.App:MyTemplate') WHERE package_id = 'my_package_id'``

Given that PQS uses a document-oriented model for ledger content
(JSONB), extensions to contract payloads are handled simply by returning
the additional data in the blob.

Daml Shell
----------

Daml Shell builds on PQS by providing a shell interface to inspect the
ledger using package-name to view all versions of contracts, in an
integrated way.

Daml-Script
-----------

Daml 2.10 introduces a new version of Daml Script, which can be used by
depending on ``daml-script-beta`` in your ``daml.yaml``, as you will have seen
in `Writing your first upgrade <#writing-your-first-upgrade>`__. This version of Daml Script
supports upgrades over the Ledger API.

All commands and queries in this version of Daml Script now use
upgrades/downgrades automatically, to ensure that the correct versions
of choices are exercises, and correct payloads are returned.

The following additional functionality is available for more advanced
uses of SCU.

**Exact commands**

Each of the four submission commands now has an "exact" variant, of the
forms ``createExactCmd``, ``exerciseExactCmd``, ``exerciseByKeyExactCmd`` and
``createAndExerciseExactCmd``. These commands force the participant to
use the exact version of the package that your script uses, this is most
useful when you want to be absolutely certain of the choice code you are
calling. Note that exact and non-exact commands can be mixed in the same
submission.

.. _daml-script-package-preference:

**Package Preference**

A submission can specify a `package preference <#dynamic-package-resolution-in-ledger-api-queries>`__,
as a list of package IDs, as follows.

.. code:: daml

  (actAs alice <> packagePreference [myPackageId]) `submitWithOptions` createCmd ...

Note here the use of ``submitWithOptions : SubmitOptions -> Commands a -> Script a``.
We build ``SubmitOptions`` by combining the ``actAs`` and ``packagePreference`` functions with ``<>``.

The full list of builders for ``SubmitOptions`` is as follows:

.. code:: daml

  -- `p` can be `Party`, `[Party]`, etc.
  actAs : IsParties p => p -> SubmiOptions
  readAs : IsParties p => p -> SubmitOptions

  disclose : Disclosure -> SubmitOptions
  discloseMany : [Disclosure] -> SubmitOptions

  newtype PackageId = PackageId Text
  packagePreference : [PackageId] -> SubmitOptions

A ``PackageId`` can be hard-coded in your script, which will need to updated whenever the given package changes. Otherwise,
it can be provided using the ``--input-file`` flag of the ``daml script`` command line tool.

Following is an example on reading the package ID from a dar and passing it to a script.

.. code:: bash

  # Path to the dar you want to pass as package preference. We will extract the package-id of its
  # main package
  PACKAGE_DAR=path/to/main/dar.dar
  # Path to the dar containing your daml-script, for which you want to pass the package-id
  SCRIPT_DAR=path/to/script/dar.dar
  daml damlc inspect-dar ${PACKAGE_DAR} --json | jq '.main_package_id' > ./package-id-script-input.json
  # replace --ide-ledger with --ledger-host and --ledger-port for deployed Canton
  daml script --dar ${SCRIPT_DAR} --script-name Main:main --ide-ledger --input-file ./package-id-script-input.json

Following this, your script would look like

.. code:: daml

  module Main where

  import Daml.Script

  main : Text -> Script ()
  main rawPkgId = do
    let pkgId = PackageId rawPkgId
    alice <- allocateParty "alice"
    -- Commands emitted for brevity
    (actAs alice <> packagePreference [pkgId]) `submitWithOptions` createCmd ...

Daml Studio support
-------------------

Daml Studio runs a reference model of Canton called the IDE Ledger. This
ledger has been updated to support the relevant parts of the Smart Contract
Upgrades feature.

Testing
=======

Upgrade Validity Checking
-------------------------

We recommend that as a further check for the validity of your upgraded
package, you perform a dry-run upload of your package to a testing environment,
using the ``--dry-run`` flag of the ``daml ledger upload-dar`` command.
This runs the upgrade type-checking, but does not persist your package to the ledger.

For workflows involving multiple DARs, we recommend more robust testing by
running a Canton sandbox with the same version and environment as your
in-production participant and uploading all the old and new packages that
constitute your Daml app.

Daml Script Testing
-------------------

Daml Script has been used for demonstrative purposes in this document, however
usually the complexities of live upgrades comes with your workflows, not the data
transformations themselves. You can use Daml Script (with Canton) to test some
isolated simple cases, but for thorough tests of you system using SCU, you should
prefer full workflow testing, as below.

Workflow Testing
----------------

While testing your workflows is application-specific, we still
recommend at least one test for your core workflows that follows this pattern:

1. Start your app using version 2.0 of your DAR, but only upload version 1.0.
2. Initialize the app and start one instance of every core workflow.
3. Upload version 2.0 of your DAR.
4. Switch your backends to start using version 2.0, ideally this should be a flag.
5. Validate that the core workflows are in the same state and advance them to check that they are not stuck.
