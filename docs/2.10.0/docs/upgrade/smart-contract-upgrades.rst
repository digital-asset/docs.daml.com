.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Zero Downtime Smart Contract Upgrades
#####################################

.. .. toctree::
   :hidden:

Theory of Operation
===================

What are Zero Downtime Smart Contract Upgrades?
-----------------------------------------------

Zero-Downtime Smart Contract Upgrades (SCU) are a feature for Daml
packages which enable authors to publish new versions of their templates
while maintaining compatibility with prior versions, without any
downtime for package users and existing contracts.

Without this feature, package authors can upgrade their packages using broadly
one of two approaches:

-  | Provide a Daml workflow for upgrading contracts to the new version,
     and tell users of the old version to use the workflow to upgrade
     their old templates to the new versions.
   | This requires communication with all package users, splits package
     users across the two versions during the migration, and may incur
     significant network cost. This approach is described
     :ref:`here <upgrade-overview>`.

-  | Publish the new version to their participant, temporarily stop
     workflows relating to the old version, and manually upgrade every
     old template on the participant to the new version by directly
     manipulating Canton’s databases.
   | This is error prone and requires some downtime for the participant.

With SCU, any contract from the old package is automatically interpreted
as the new version as soon as it is used in a new workflow that requires
it.

In this way, package authors can publish new package versions that
improve contracts’ functionality without requiring any
error prone migrations, without downtime, without requiring any
additional network traffic, and without any extensive communication with
downstream users.

Requirements
------------

Note that SCU is only available when the criteria below are met:

-  Canton 2.9.x or above

-  Daml LF Version 1.16 or above

-  Canton Protocol Version 6 or above

There are instructions below on how to configure this setup. The
sections below, unless explicitly stated otherwise, assume that this is
the case.

How Does it Work
----------------

When upgrading a package, the package author modifies their existing
package to add new functionality, such as new fields and choices. When
the new package is uploaded to a participant with the old version, 
the participant ensures that the every modification to the model in the
new version is a valid upgrade of the previous version.

In order to be able to automatically upgrade a contract or datatype, SCU
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

We can add a new field for currency:

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

Automatic Data Upgrades
~~~~~~~~~~~~~~~~~~~~~~~

When extending data in a daml model, SCU requires the old model be
representable in the new model. I.e., for extending a record, we can
only add nullable (``Optional``) fields, so that old data can be represented
by setting these fields to ``None``. This mentality is continued for
Variants and Enums, which only allow adding constructors, with some
other restrictions covered in `Continuing to Write Your Upgrades <#continuing-to-write-your-upgrades>`__. This
approach is inspired by
`Protobuf <https://protobuf.dev/programming-guides/proto3/#updating>`__
and Typescript's ability to ignore `excess
fields <https://www.typescriptlang.org/docs/handbook/2/objects.html#excess-property-checks>`__
via ``as``.

Following is a list of places where automatic data upgrades occur:

**Submissions to the Ledger API**

When you submit a command, and do not explicitly specify a package-id to
use, Canton will automatically upgrade the payloads you give to the most
recent version of the package that is uploaded on the participant. It
will also use the most recent implementation of any choices you exercise
directly through the Ledger API. This behavior can be influenced by
package preference, which will be covered later.

**Fetches/Creates**

Within choices, the package-ids of the payloads we expect for fetches
and creates are given by the version of the package we depend on. SCU
will upgrade (or downgrade) the payloads given/stored in the ledger to
match these versions when used in a choice body.

**Exercises**

Similarly to fetches, the version of the choice implementation that is
called from a choice body is determined by the package that the choice’s
package depends on. SCU will automatically upgrade/downgrade the payload
stored in the ledger to match that of the choice it is calling.

**Consuming clients (such as daml-script, ts/java codegen)**

When clients query the Ledger API for contracts, the returned event
payload format matches the template originally used for generating the
event (creating a contract/exercising a choice). It is the
responsibility of these clients to upgrade/downgrade the payloads they
receive to match what is expected downstream. Daml-script, as well as
ts/java codegen, will do this for you to match the payload to the
package versions they were run/built from.

Upgrading Across the Stack
--------------------------

These are all the components that interact with upgrades as a feature,
and this is how you as a user should be aware it interacts.

Canton
~~~~~~

When considering the Canton ledger nodes, only the Canton participant
node is aware of smart contract upgrading. The Canton domain nodes are
only concerned with the protocol version which must be minimally 6 for
allowing connected participants to use upgradable Daml packages.

Below, we provide a brief overview of the interactions with the
participant node that have been adapted for supporting the smart
contract upgrading feature starting with Canton 2.9:

-  DAR upload requests go through an additional validation stage to
   check the contained new packages for upgrade-compatibility with
   other packages previously uploaded on the participant.

-  Ledger API command submissions can be automatically or explicitly
   up/downgraded if multiple upgrade-compatible packages exist.

-  Ledger API streaming queries are adapted to support fetching events
   more generically, by package-name.

Code Generation
~~~~~~~~~~~~~~~

The Java and TypeScript CodeGen have been updated to perform upgrades on
retrieved contracts, and will now use package-names over package-ids for
commands to the participant.

JSON API Server
~~~~~~~~~~~~~~~

To match the changes to the Ledger API, the JSON API similarly supports
package-name queries and command submission.

PQS & Daml Shell
~~~~~~~~~~~~~~~~

PQS now only supports querying contracts via package-name, see
`Limitations <#limitations>` for package-id queries.

Daml Shell builds on top of PQS, so inherits this behavior.

Daml Script
~~~~~~~~~~~

We’ve added a new opt-in version of daml-script which, among other
improvements, adds support for Upgrades.

This new version acts as a drop in replacement for the previous
daml-script, and will enable support for upgrades on all queries and
command submissions.

We also expose new functions for more advanced interactions with
upgrades, as well as to revert to previous submission behavior.

Daml Compiler
~~~~~~~~~~~~~

The Daml compiler supports the new ``upgrades:`` configuration field - every
time ``daml build`` is invoked, it will validate the current package for
upgrade compatibility against the package specified in the ``upgrades:``
field.

Validation emits custom error messages for common upgrading mistakes,
and warns the package author when upgrading a package in a potentially
unsafe way. Note however that this validation cannot be complete, as
upgrade validity depends on a participant’s package store. The
participant’s DAR upload checks have the final say on upgrade validity.

Daml Studio
~~~~~~~~~~~

Basic Upgrades support has also been added to Daml Studio’s “Script
Results” tab, allowing you to test your upgrades quickly and easily
within VSCode. There are some limitations here which are listed in 
`Daml Studio support <#daml-studio-support>` below.

Limitations
-----------

In order to enable zero downtime upgrades, alongside multi-versioned
packages running concurrently, we’ve limited the types of
transformations that can be performed on live data. Following are some
data transformations that cannot be made using SCU upgrades.

-  Renaming, removal or rearrangement of fields in a template

-  Conversion of records to variants, and vice versa

-  Moving templates/datatypes to other modules

-  Upgrading interface and exception definitions

These restrictions are required to give a simple model of runtime
upgrades, avoiding ambiguity and non-obvious side effects. If you
require any of these types of changes, you may need to consider a
redeployment with downtime, using any of the tools listed in 
`What are Zero Downtime Smart Contract Upgrades <#what-are-zero-downtime-smart-contract-upgrades>`__.

In this beta version of SCU, the following functionality has not yet
been implemented, but may be implemented in future releases.

-  Retroactive interface instances are not compatible with SCU upgrades.

-  Daml Script does not support SCU, Daml Script Beta must be used.

-  The ``upgrades:`` field in the ``daml.yaml`` is not yet integrated into
   Multi-Package, and therefore will not be automatically built as a
   dependency (or when running ``daml build --all``, unless explicitly
   listed in ``multi-package.yaml``)

-  Contract keys in upgradable packages can only include types defined
   within the same package, or in ``daml-stdlib`` or ``daml-prim``, for hashing reasons.
   This restriction is intended to be loosened in a later version.

-  Upgrade compatibility checks currently run on all data types, even those which are
   not `serializable <https://github.com/digital-asset/daml/blob/main-2.x/sdk/daml-lf/spec/daml-lf-1.rst#serializable-types>`__.
   This check will be loosened in a future version.

Local developer experience
==========================

Writing your first upgrade
--------------------------

Setup
~~~~~

We continue with the example introduced in `How Does It
Work <#how-does-it-work>`__. Begin by defining the first (old) version
of our package:

.. code:: bash

  > mkdir -p v1/my-pkg
  > cd v1/my-pkg
  > daml init

Add ``daml-script-beta`` to the list of dependencies in ``v1/my-pkg/daml.yaml``,
as well as ``--target=1.16`` to the ``build-options``:

.. code:: yaml
  
  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml-script-beta
  build-options:
  - --target=1.16

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

Now we create the second (new) version of our package, which will
upgrade the first version. Navigate back to the root directory and copy
the v1 package into a v2 directory.

.. code:: bash

  > cd ../..
  > cp -r v1 v2
  > cd v2/my-pkg

Edit the ``daml.yaml`` to update the package version, and add the ``upgrades:``
field pointing to v1:

.. code:: yaml

  version: 2.0.0
  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml-script-beta
  upgrades: ../../v1/my-pkg/.daml/dist/my-pkg-1.0.0.dar
  build-options:
  - --target=1.16

Now any changes we make to v2 will be validated as a correct upgrade
over v1.

First Changes
~~~~~~~~~~~~~

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

Run ``daml build``, an error will be emitted:

.. code:: bash

  > daml build
  ...
  error type checking template Main.IOU :
    The upgraded template IOU has added new fields, but those fields are not Optional.
  ERROR: Creation of DAR file failed.

Any new fields we add to a template must be optional - old contracts
from the previous version will automatically be upgraded by setting new
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

The build may produce warnings about expression changes - this will be
covered in the `Continuing to Write Your
Upgrades <#continuing-to-write-your-upgrades>`__ section.

Seeing Upgraded Fields in Contracts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
      --output-file alice-v1 \
      --enable-contract-upgrading
  Slf4jLogger started
  Running CoordinatedShutdown with reason [ActorSystemTerminateReason]

.. note::
  All invocations of daml script using ZDT require the ``--enable-contract-upgrading`` flag.

From inside ``v2/my-pkg``, upload and run the ``getIOU`` script, passing in the
``alice-v1`` file as the script’s input:

.. code:: bash

  > cd ../../v2/my-pkg
  > daml ledger upload-dar --port 6865
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-2.0.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file ../../v1/my-pkg/alice-v1 \
      --enable-contract-upgrading
  Slf4jLogger started
  {
    "_1": "...",
    "_2": {
    "issuer": "party-...",
    "owner": "party-...",
    "value": 1,
    "currency": null
    }
  }
  Running CoordinatedShutdown with reason [ActorSystemTerminateReason]

The returned contract has a field ``currency`` which is set to ``null``. When
running the ``getIOU`` script from v1, this field does not appear.

.. code:: bash

  > cd ../../v1/my-pkg
  > daml script \
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file alice-v1 \
      --enable-contract-upgrading
  Slf4jLogger started
  {
    "_1": "...",
    "_2": {
    "issuer": "party-...",
    "owner": "party-...",
    "value": 1
    }
  }
  Running CoordinatedShutdown with reason [ActorSystemTerminateReason]

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
      --dar .daml/dist/my-pkg-2.0.0.dar \
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
      --input-file ../../v2/my-pkg/alice-v2 \
      --enable-contract-upgrading
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
      --dar .daml/dist/my-pkg-2.0.0.dar \
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
  	--input-file ../../v2/my-pkg/alice-v2 \
  	--enable-contract-upgrading
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
example choice ``Double`` to ``v2/my-pkg/daml/Main.daml``, which will archive
the current contract and produce a new one with twice the value.

.. code:: daml

  ...
      maintainer key
      choice Double : ContractId IOU
          controller issuer
          do create this with value = value * 2
  ...

Compiled changes will be checked against the previous version and pass:

.. code:: bash

  > daml build
  ...
  2024-06-27 15:32:49.17 [INFO]  [build]
  Compiling my-pkg to a DAR.
  
  2024-06-27 15:32:49.54 [INFO]  [build]
  Created .daml/dist/my-pkg-2.0.0.dar
  ...

Restart the sandbox and reupload the both v1 and v2 using the Daml
sandbox:

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
      --dar .daml/dist/my-pkg-2.0.0.dar \
      --script-name Main:doubleIOU \
      --output-file /dev/stdout \
      --input-file ../../v1/my-pkg/alice-v1 \
      --enable-contract-upgrading
  ...
  	"issuer": "party-...",
  	"owner": "party-...",
  	"value": 2,
  	"currency": null
  ...

Contracts made in v1 can still be exercised with choices introduced in
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
      --dar .daml/dist/my-pkg-2.0.0.dar \
      --script-name Main:mkIOUWithoutCurrency \
      --output-file alice-v2
  > cd ../../v1/my-pkg
  > daml ledger upload-dar --port 6865
  > daml script \
  	--ledger-host localhost --ledger-port 6865 \
  	--dar .daml/dist/my-pkg-1.0.0.dar \
  	--script-name Main:doubleIOU \
  	--output-file /dev/stdout \
  	--input-file ../../v2/my-pkg/alice-v2 \
  	--enable-contract-upgrading
  ...
  	"issuer": "party-...",
  	"owner": "party-...",
  	"value": 2
  ...

Deploying your first upgrade
----------------------------

Configuring Canton to support smart upgrading
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SCU is a beta feature in Canton 2.9. When using the feature one must
configure Canton nodes to :ref:`enable beta version support <how-do-i-enable-beta-features>`.

Using smart-contract-upgrading enabled packages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once you have finished development of your smart contract app, use the
mentioned upgrade-enabled options in daml.yaml to compile and generate
the related DAR. This can be uploaded using the existing gRPC endpoints
without modifications and will be immediately available for use.

.. note::

  In 2.9, once a DAR is successfully uploaded, it cannot be
  safely removed from the participant node. Participant operators must
  then ensure that uploaded functionality does not break the intended
  upgrade lineage as newly uploaded DARs affect the upgrading line (i.e.
  all subsequent uploads must be compatible with this one as well).

.. note::

  Upgrade-compatible packages stored on the participant must
  lead to unique (in both directions) package-id <-> (package-name,
  package-version) relationships since runtime package-name -> package-id
  resolution must be deterministic (see Ledger API section). For this
  reason, once a LF 1.16+ DAR has been uploaded with its main package
  having a specific package-name/package-version, this relationship cannot
  be overridden. Hence, uploading a DAR with different content for the
  same name/version as an existing DAR on the participant will lead to a
  rejection with error code KNOWN_DAR_VERSION.

Validate the DAR against a running participant node
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Starting with 2.9, you can validate your DAR against the current
participant node state, without uploading it to the participant in case
of success. This is possible via the
``PackageManagementService.validateDar`` Ledger API endpoint and allows
participant node operators to first check the DAR before uploading it.

This operation is also available via the Canton Admin API and Console:

.. code::

  participant.dars.validate("dars/CantonExamples.dar")

Upgrading and package vetting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Upgradable packages are also subject to :ref:`package vetting
restrictions <package_vetting>`:
in order to be able to use a package in Daml transactions with smart
contract upgrading, it needs to be vetted by all participants involved
in the transaction. This applies both for the packages used for creating
the contracts and for the target packages.

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
the v1 and v2 IOU modules. The v1 IOU module should be overwritten to
look like the following:

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

      choice Duplicate : ContractId IOU
        controller issuer
        do
          create this with value = value * 2

Running ``daml build`` should succeed without errors.

.. code:: bash

  > cd v1/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-1.0.0.dar
  > cd ../../v2/my-pkg
  > daml build
  ...
  Created .daml/dist/my-pkg-2.0.0.dar

We can upgrade the ``Duplicate`` choice by adding an optional field ``amount``,
and changing the behavior of the choice to default to a multiple of 3.
Replace the definition of the ``Duplicate`` choice in the v2 implementation
of ``IOU`` only:

.. code:: daml

  ...
  -- Add import to top of module
  import DA.Optional (fromOptional)
  ...
     -- Replace Duplicate choice implementation
     choice Duplicate : ContractId IOU
       with
         amount : Optional Int -- New optional amount
       controller issuer
       do
         let amt = fromOptional 3 amount
         create this with value = value * amt
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
        newCid <- key `submit` exerciseExactCmd iouCid Duplicate
        mbNewIOU <- queryContractId key newCid
        case mbNewIOU of
          Some newIOU -> pure (Some (newCid, newIOU))
          None -> pure None

A similar script called ``duplicateIOU`` should be added in V2, supplying an
``amount`` field:

.. code:: daml

  ...
  duplicateIOU : Party -> Script (Optional (ContractId IOU, IOU))
  duplicateIOU key = do
    mbIOU <- getIOU key
    case mbIOU of
      None -> pure None
      Some (iouCid, _) -> do
        newCid <- key `submit` exerciseExactCmd iouCid Duplicate { amount = Some 4 }
        mbNewIOU <- queryContractId key newCid
        case mbNewIOU of
          Some newIOU -> pure (Some (newCid, newIOU))
          None -> pure None

Running the v1 ``duplicateIOU`` script with ``exerciseExactCmd`` will always run
the v1 implementation for the ``Duplicate`` choice, and similarly for v2.

Modifying Signatory Definitions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Other definitions can be changed, but warnings are emitted to remind the
developer that the changes can be unsafe and need to be made with care
to preserve necessary invariants.

Signatories and observers are one expression that can be changed.
Importantly, the new definition must not change the resulting list of
signatories and observers for existing contracts.

For example, add a new field of “outside observers” to the v2 IOU
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

The new observer definition will allow v2 contracts and beyond to add
new observers via the outsideObservers field. However, any existing
contracts will default to ``None`` for the ``outsideObservers`` field, so all
existing contracts will have the same observer list as before: the
single owner.

Modifying Key Expressions
~~~~~~~~~~~~~~~~~~~~~~~~~

Similarly, key expressions can be changed as long as they evaluate to
the same value for existing contracts, this means that the type of the key
cannot change.

For example, v2 can add a new field “alternative key” to the v2 IOU
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
from other packages, with the exception of `daml-stdlib` and `daml-prim`.
See `Limitations <#limitatiions>`__ for more information.

Upgrading Enums
~~~~~~~~~~~~~~~

Variants and enums can be extended under SCU, either by adding
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
  Created .daml/dist/my-pkg-2.0.0.dar

When we want to extend our contract to support new currencies, we can
add new entries to the end of our ``Currency`` enum.

.. code:: daml

  ...
  data Currency
    = USD
    | GBP
    | CHF -- Add a new currency type
    deriving (Show, Eq, Ord)
  ...

Upgrades of extended enums from an old version to new version will
always succeed. In the case of IOUs, a v1 IOU can always be interpreted
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
      --output-file alice-v1 \
      --enable-contract-upgrading
  ...
  > cd ../../v2/my-pkg
  > daml script
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-2.0.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file ../../v1/my-pkg/alice-v1 \
      --enable-contract-upgrading
  ...
      "issuer": "party-...",
      "owner": "party-...",
      "value": 1,
      "currency": "USD"
  ...

For downgrades from v2 to v1, only constructors that are defined in both
v1 and v2 can be downgraded from v2 to v1. Any constructor that doesn’t
exist in the v1 package will fail to downgrade with a runtime error. In
the case of our ``IOU``, any ``CHF`` will fail to downgrade, so any v2 contracts
with a ``CHF`` currency cannot be used in v1 workflows.

For example, create a contract with ``CHF`` as its ``currency`` field via v2’s
``mkIOU`` script. Attempting to query it via v1’s ``getIOU`` script will fail
with a lookup error for the CHF variant.

.. code:: bash

  > cd v2/my-pkg
  > daml script
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-2.0.0.dar \
      --script-name Main:mkIOU \
      --output-file alice-v2 \
      --enable-contract-upgrading
  ...
  > cd ../../v1/my-pkg
  > daml script
      --ledger-host localhost --ledger-port 6865 \
      --dar .daml/dist/my-pkg-1.0.0.dar \
      --script-name Main:getIOU \
      --output-file /dev/stdout \
      --input-file ../../v2/my-pkg/alice-v2 \
      --enable-contract-upgrading
  ...
  Failed to translate create argument: Lookup(NotFound(DataVariantConstructor(c1543a5c2b7ff03650162e68e03e469d1ecf9f546565d3809cdec2e0255ed902:Main:Currency,CHF),DataEnumConstructor(c1543a5c2b7ff03650162e68e03e469d1ecf9f546565d3809cdec2e0255ed902:Main:Currency,CHF)))
  ...

Upgrading Variants
~~~~~~~~~~~~~~~~~~

Variants, also known as algebraic data types, are very similar to enums,
except that they also contain structured data within them.

For example, the following variant has two constructors, each with
unique fields. Overwrite both v1 and v2 modules with the following
source:

.. code:: daml

  module Main where
  
  data Shape
    = Circle
    | Polygon { sides : Int }

We can extend this variant in two ways. We can add a new constructor,
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
  Created .daml/dist/my-pkg-2.0.0.dar

We can also add a new field to a constructor, similarly to templates -
for example, add a ``sideLen`` field to our ``Polygon`` constructor, to specify
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
  Created .daml/dist/my-pkg-2.0.0.dar

Limitations in Upgrading Variants
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Upgrading variants has some limitations - because we have defined the
``Circle`` constructor without a field in curly braces, it cannot be
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
data type, the larger data type will be upgradeable if the field’s data
type is upgradeable as well.

For example, given the data type ``A`` with a field referring to data type
``B``,

.. code:: daml

  data A = A { b : B }
  data B = B { field : Text }

If modifications made to ``B`` are valid for SCU, then ``A`` will also be valid.

Dependencies
~~~~~~~~~~~~

Package authors may upgrade the dependencies of a package as well as the
package itself. A new version of a package may add new dependencies, and
must have all the dependencies of the old version. Dependencies of the
old version may be upgraded, or must be identical.

For example, suppose we have a dependencies folder, containing v1 and v2
of two dependency packages ``depA`` and ``depB``

.. code:: bash

  > ls ./dependencies
  depA-1.0.0.dar
  depA-2.0.0.dar
  depB-1.0.0.dar
  depB-2.0.0.dar

Change v1 of the IOU package so that it depends on ``depA-1.0.0`` and
``depB-2.0.0``. Its ``v1/my-pkg/daml.yaml`` would look something like this:

.. code:: yaml

  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml3-script
  - ../../dependencies/depA-1.0.0.dar
  - ../../dependencies/depB-2.0.0.dar
  ...

A package with a newer version may upgrade any dependency to a newer
version (or keep the version the same). For example, v2 of our IOU
package may keep its dependencies the same, or it may upgrade ``depA`` to
``2.0.0``:

.. code:: yaml

  ...
  dependencies:
  - daml-prim
  - daml-stdlib
  - daml3-script
  - ../../dependencies/depA-2.0.0.dar
  - ../../dependencies/depB-2.0.0.dar
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
  Uploading .daml/dist/my-pkg-2.0.0.dar to localhost:6865
  upload-dar did not succeed: DAR_NOT_VALID_UPGRADE(...): The DAR contains a package which claims to upgrade another package, but basic checks indicate the package is not a valid upgrade
  ...

Upgrading Interface Instances
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ZDT upgrades also support changing Interface instances. First, create a
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
  - --target=1.16

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

Upgrades allow us to add an interface definition. For example, add an
interface instance of ``HasValue`` for ``IOU`` to package v2:

.. code:: daml

  ...
      interface instance HasValue for IOU where
        view = HasValueView value
        getValue = value

Shut down and relaunch the Daml sandbox, then build and upload the two
DARs. They should both succeed:

.. code:: bash

  > cd v1/my-pkg
  > daml build
  > daml sandbox upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  DAR upload succeeded.
  > cd ../../v2/my-pkg
  > daml build
  > daml sandbox upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-2.0.0.dar to localhost:6865
  DAR upload succeeded.

Interface instances can be changed by an upgrade. For example, v2 can
change the definition of ``getValue`` in the ``HasValue`` instance. Add the
interface instance to ``v1/my-pkg/daml/Main.daml``:

.. code:: daml

  ...
      interface instance HasValue for IOU where
        view = HasValueView value
        getValue = value

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
        view = HasValueView value
        -- Use quantity field to calculate value
        getValue = value * fromOptional 1 quantity

Shut down and relaunch the Daml sandbox, then build and upload the two
DARs. They should both succeed again:

.. code:: bash

  > cd v1/my-pkg
  > daml build
  > daml sandbox upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  DAR upload succeeded.
  > cd ../../v2/my-pkg
  > daml build
  > daml sandbox upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-2.0.0.dar to localhost:6865
  DAR upload succeeded.

Packages with new versions cannot remove an instance that is already
there. For example, the v2 IOU template cannot remove its instance of
``HasValue``. Remove the interface instance for ``HasValue`` from
``v2/my-pkg/daml/Main.daml`` completely, then restart the sandbox and try to
reupload the two versions:

.. code:: bash

  > cd v1/my-pkg
  > daml build
  > daml sandbox upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  DAR upload succeeded.
  > cd ../../v2/my-pkg
  > daml build
  > daml sandbox upload-dar --port 6865
  ...
  Uploading .daml/dist/my-pkg-1.0.0.dar to localhost:6865
  upload-dar did not succeed: KNOWN_DAR_VERSION(8,c63f3811): A DAR with the same version number has previously been uploaded.

Similarly to choices, scripts may invoke interface implementations from
their own version using ``exerciseExactCmd``.

Upgrading Interfaces
~~~~~~~~~~~~~~~~~~~~

Interface instances may be upgraded, but interfaces themselves cannot be
upgraded. If an interface is present in v1 of a package, it must be
removed from all subsequent versions of that package.

Because interfaces may not be defined in subsequent versions, any
package depending on an interface from a dependency package can never
upgrade that dependency to a new version.

For this reason, we strongly recommend that interfaces always be defined
in their own packages separately from templates.

Best Practices
--------------

To ensure your future upgrades and dar lifecycling goes smoothly, we
recommend the following practices:

Separate Interfaces/Exceptions from templates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Interface and exception definitions are not upgradable, they are fixed
for the lifetime of a package. As such, if you attempt to redefine an
interface or exception in version 2 of a package, even if unchanged, the
package will not type check. Removing the interface from the second
package will also cause issues, especially if the interface has choices.
Instead, you should move these definitions out into a separate package
from the start, such that subsequent versions of your package with
templates all depend on the same version of the package with
interfaces/exceptions. The SCU type checker will warn about this, but
you should see this warning as an error - it is very strongly
recommended that you do not compile interfaces and templates for
upgrades.

Remove retroactive instances
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SCU replaces the need for retroactive instances, and is also not
compatible with them. To ensure package selection for interface choices
acts correctly, retroactive interface instances should be moved to newer
versions of templates, such that changes to the instance warrants a new
version of the template.

Explicit template versions
~~~~~~~~~~~~~~~~~~~~~~~~~~

While in many cases, the absence of new fields can be used to infer the
version of a package, it is recommended that you tag your contracts in
their payload with an explicit version field, and rely on that to know a
payload’s version. This will allow for less fragile behavior in the
event of “partial upgrades” (where a user may only upgrade part of the
payload of a package, intentionally), and allow you to model rollbacks
as upgrades in a principled manner.

Avoid contract metadata changes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The signatories, observers, contract key and ensure clauses of a
contract should be fixed at runtime for a given contract. Changing their
definitions in your daml code will trigger a warning from the SCU
typechecker, and is discouraged. Note that for contract keys, the type
cannot change at all, only its value. Should you need to change these
values, be aware that if their runtime value changes in any way, the
upgrade will fail, and thus the full transaction. Contracts in this
state can then only be used by explicitly choosing the older version of
the contract in your transaction.

Migration
---------

SCU is only supported on LF1.16, which in turn is only supported on
Canton Protocol Version 6. This means that existing deployed contracts
will first require migration and redeployment to utilize this feature.

First, you’ll need to migrate your daml model to be compatible with
upgrades, see the section above about `Best Practices <#best-practices>`__ for what to
change here. Pay particular attention to the case on interfaces and
exceptions, and failure to do so could lead to packages which are
incompatible with SCU, and require the use of a separate tool (and
downtime).

Next, you’ll need to be aware of the new package-name scoping rules, and
ensure that your package set does not violate this. In short, packages
with the same package-name are considered to be “in the same scope”,
each version string within this scope can only be held by one package,
and contract key queries will yield contracts from all packages within
the same scope. If you have packages with the same name that you do not
want to be associated with each other via upgrades, you’ll need to
rename them. Note that this scoping rule *only* applies to packages in
LF1.16. Packages with the same name and version can exist in LF1.15, if
you intend to use both LF versions at the same time on your participant.

Once you have your new dars, you’ll need to upgrade your Canton and
protocol version together, since 2.9 introduces a new protocol version.
The steps to achieve this are given in the :ref:`Canton Upgrading
manual <one_step_migration>`.

Finally, you can migrate your live data from your previous dars to the
new LF1.16 dars, using one of the existing downtime upgrade techniques
listed in `What are Zero Downtime Smart Contract Upgrades <#what-are-zero-downtime-smart-contract-upgrades>`__.

The Upgrade Model in Depth - Reference
--------------------------------------

You can find the in-depth upgrading model, which can be used as a reference
for valid upgrades, :ref:`here <upgrade_model_reference>`.

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
generating the Daml transaction after command interpretation. This
dynamic resolution is based on the existing upgradable (LF >= 1.16)
package-ids pertaining to a specific ``package-name`` and is possible on the
write path (command submission) and read path (Ledger API queries) as
presented below.

Dynamic package resolution in command submission
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

   -  **Note:** The Command’s
      :ref:`package_id_selection_preference <com.daml.ledger.api.v1.Commands.package_id_selection_preference>`
      must not lead to ambiguous resolutions for package-names,
      meaning that it must not contain two package-ids pertaining to
      the same package-name otherwise the submission will fail with
      an ``INVALID_ARGUMENT`` error

Dynamic package resolution in Ledger API queries
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
packages with LF < 1.16)

Example
^^^^^^^

Given the following packages with LF 1.16 existing on the participant
node:

-  Package AppV1

   -  package-name: ``app1``

   -  package-version: ``1.0.0``

   -  template-ids: ``pkgId1:mod:T``

-  Package AppV2

   -  package-name: ``app1``

   -  package-version: ``2.0.0``

   -  template-ids: ``pkgId2:mod:T``

If a transaction query is created with a templateId specified as
``#app1:mod:T``, then the events stream will include events from both
template-ids: ``pkgId1:mod:T`` and ``pkgId2:mod:T``

Codegen
-------

For packages that support SCU (i.e. LF1.16), generated code will use
package-names in place of package-ids in template ids. Retrieved data
from the ledger will be subject to the upgrade transformations described
in previous sections.

Concretely, this is implemented as follows:

Java
~~~~

The classes that are generated for each template and interface contain a
``TEMPLATE_ID`` field, which, for upgradable packages, will now use a
package name, rather than a package id. In order to allow determining
the package id of these packages, we add a new ``PACKAGE_ID`` field to all
such classes. Upgradable packages will also cause ``PACKAGE_NAME`` and
``PACKAGE_VERSION`` fields to be present.

TypeScript
~~~~~~~~~~

The ``templateId`` field on generated template classes has been updated to
use the package-name as the package qualifier for upgrade compatible
packages. This will be used for command submission and queries, however
note that the package qualifier given back in queries will contain the
package-id, rather than package-name. Generated modules will now also
give the package “reference”, which will be the package-name for upgrade
compatible packages, otherwise it’ll be the package-id.

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

As before, template IDs may still be used with a package id, however,
for packages built as LF 1.16 or greater, the package may also be
identified by name, i.e. for upgradable packages, a template ID can have
the form ``#<package-name>:<module-name>:<template-name>``, and this will be
resolved to corresponding templates from all packages which share this
name, and are built at 1.16 or above. For packages built at LF 1.15 or
lower, the templates will not be identifiable via a package name, and a
package id must be used.

Note: template ids in query results will always use a package id. This
allows us to distinguish the source of a particular contract. This means
that if you use a template with a package name in the request, you can
no longer expect the template ids in the result to exactly match the
input template id.

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

Daml-Script-Beta
----------------

Daml 2.9 introduces a new version of Daml Script, which can be used by
depending on ``daml-script-beta`` in your ``daml.yaml``, as you will have seen
in `Writing your first upgrade <#writing-your-first-upgrade>`__. Only this version of Daml Script
supports upgrades over the Ledger API.

All commands and queries in this version of daml script will now use
upgrades/downgrades automatically, to ensure that the correct versions
of choices are exercises, and correct payloads are returned.

The following additional functionality is available for more advanced
uses of SCU.

**Exact commands**

Each of the 4 submission commands now have an “exact” variant, of the
forms ``createExactCmd``, ``exerciseExactCmd``, ``exerciseByKeyExactCmd`` and
``createAndExerciseExactCmd``. These commands will force the participant to
use the exact version of the package that your script uses, this is most
useful when you want to be absolutely certain of the choice code you are
calling. Note that exact and non-exact commands can be mixed in the same
submission.

Daml Studio support
-------------------

Daml Studio runs a reference model of Canton called the IDE Ledger, this
ledger has been updated to support most of the functionality of upgrades
in daml-script. The behavior that this ledger does not implement is the
following:

-  Upgrades type checking
   The Upgrades type errors you’ll get when running daml build are not
   currently shown as code intelligence in Daml Studio.

-  Contract ID verification
   This may allow some contract metadata changes to take effect that
   Canton otherwise would not.

-  Per-submission package preference
   Any submission to the IDE Ledger will mimic a Canton participants
   default package preference of the most recent package version.

Testing
=======

Upgrade validity checking
-------------------------

While the compile time upgrade checks are quite thorough, they are not
yet a perfect mirror of the checks that a participant does when a
package is uploaded. We recommend that as a final check for the validity
of your upgraded package, you can either:

-  Run a Canton sandbox (running ``daml sandbox``) and upload your old and
   new package (``daml ledger upload-dar``).

-  Run a dry-run upload of your package to a more permanent testing
   environment, using the ``--dry-run`` flag of the
   ``daml ledger upload-dar`` command, which will run the upgrade
   type-checking, but not persist your package to the ledger.

Workflow testing
----------------

While the testing of your workflows will be very application specific, we still
recommend at least one test for your core workflows that follows this pattern:

1. Start your app using version 2.0 of your DAR, but only upload version 1.0.
2. Initialize the app and start one instance of every core workflow.
3. Upload version 2.0 of your DAR.
4. Switch your backends to start using version 2.0, ideally this should be a flag.
5. Validate that the core workflows are in the same state and advance them to check that they are not stuck.