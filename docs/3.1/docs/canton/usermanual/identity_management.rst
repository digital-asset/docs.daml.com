..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _identity_management_user_manual:

Identity Management
===================
On-ledger identity management focuses on the distributed aspect of identities across Canton system entities, while
user identity management focuses on individual participants managing access of their users to their ledger APIs.

Canton comes with a built-in identity management system used to manage on-ledger identities. The technical details
are explained in the :ref:`architecture section <identity-manager-1>`, while this write-up here is meant to give a high
level explanation.

The identity management system is self-contained and built without a trusted central entity or pre-defined root
certificate such that anyone can connect with anyone, without the need for some central approval and without the
danger of losing self-sovereignty.

Introduction
------------
What is a Canton Identity?
~~~~~~~~~~~~~~~~~~~~~~~~~~
When two system entities such as a participant, sync domain topology manager, mediator or sequencer communicate
with each other, they will use asymmetric cryptography to encrypt messages and sign message contents
such that only the recipient can decrypt the content, verify the authenticity of the message, or prove its origin.
Therefore, we need a method to uniquely identify the system entities and a way to associate encryption and signing keys
with them.

On top of that, Canton uses the contract language Daml, which represents contract ownership and rights
through `parties <https://docs.daml.com/concepts/glossary.html#party>`_. But parties are not primary members
of the Canton synchronization protocol. They are represented by participants and therefore we need to
uniquely identify parties and relate them to participants, such that a participant can represent several
parties (and in Canton, a party can be represented by several participants).

Unique Identifier
~~~~~~~~~~~~~~~~~
A Canton identity is built out of two components: a random string ``X`` and a fingerprint of a public key ``N``.
This combination, ``(X,N)``, is called a *unique identifier* and is assumed to be globally unique by design.
This unique identifier is used in Canton to refer to particular parties, participants, or sync domain entities.
A system entity (such as a party) is described by the combination of role (party, participant, mediator, sequencer,
sync domain topology manager) and its unique identifier.

The system entities require knowledge about the keys that are used for encryption and signing by the
respective other entities.
This knowledge is distributed and therefore, the system entities require a way to verify that a certain
association of an entity with a key is correct and valid. This is the purpose of the fingerprint
of a public key in the unique identifier, which is referred to as *Namespace*. The secret key of the
corresponding namespace acts as the *root of trust* for that particular namespace, as explained later.

.. _identity-transactions:

Topology Transactions
~~~~~~~~~~~~~~~~~~~~~
In order to remain flexible and be able to change keys and cryptographic algorithms, we don't identify the
entities using a single static key, but we need a way to dynamically associate participants or sync domain entities
with keys and parties with participants. We do this through topology transactions.

A topology transaction establishes a certain association of a unique identifier with either a key or a relationship
with another identifier. There are several different types of topology transactions. The most general one is the
``OwnerToKeyMapping``, which as the name says, :ref:`associates a key with a unique identifier <owner-to-key-mapping>`.
Such a topology transaction will inform all other system entities that a certain system entity is using a specific
key for a specific purpose, such as participant *Alice* of namespace *12345..* is using the key identified through
the fingerprint *AABBCCDDEE..* to sign messages.

Now, this poses two questions: who authorizes these transactions, and who distributes them?

For the authorization, we need to look at the second part of the unique identifier, the *Namespace*. A
topology transaction that refers to a particular unique identifier operates on that namespace and we require
that such a topology transaction is authorized by the corresponding secret key through a cryptographic
signature of the serialized topology transaction. This authorization can be either direct, if it is signed
by the secret key of the namespace, or indirect, if it is signed by a delegated key. To delegate the signing right to another key, there are other topology transactions of type *NamespaceDelegation* or
*IdentifierDelegation* that allow one to do that. A :ref:`namespace delegation <namespace-delegation>` delegates
entire namespaces to a certain key, such as saying the key identifier through the fingerprint *AABBCCDDEE...* is now
allowed to authorize topology transactions within the namespace of the key *VVWWXXYYZZ...*. An
:ref:`identifier delegation <identifier-delegation>` delegates authority over a certain identifier to a key,
which means that the delegation key can only authorize topology transactions that act on a specific identifier and not
the entire namespace.

Signing of topology transactions happens in a ``TopologyManager``. Canton has many topology managers. Every
participant node and every sync domain have topology managers with exactly the same functional capabilities, just different
impacts. They can create new keys, new namespaces, and the identity of new participants, parties, and sync domains. And
they can export these topology transactions such that they can be imported by another topology manager. This allows you to
manage Canton identities in quite a wide range of ways. A participant can operate their own topology manager which
allows them individually to manage their parties. Or they can associate themselves with another topology manager and let them
manage the parties that they represent or keys they use. Or something in between, depending on the introduced
delegations and associations.

The difference between the sync domain topology manager and the participant topology manager is that the sync domain topology
manager establishes the valid topology state in a particular sync domain by distributing topology transactions in a way that
every sync domain member ends up with the same topology state. However, the sync domain topology manager is just a gatekeeper of
the sync domain that decides who is let in and who is not on that particular sync domain, but the actual topology statements originate from
various sources. As such, the sync domain topology manager can only block the distribution, but cannot fake topology
transactions.

The participant topology manager only manages an isolated topology state. However, there is a dispatcher attached to
this particular topology manager that attempts to register locally registered identities with remote sync domains, by sending
them to the sync domain topology managers, who then decide on whether they want to include them or not.

The careful reader will have noted that the described identity system indeed does not have a single root of trust or
decision maker on who is part of the overall system or not. But also that the topology state for the distributed
synchronization varies from sync domain to sync domain, allowing very flexible topologies and setups.

Legal Identities
~~~~~~~~~~~~~~~~
In Canton, we separate a system identity from the legal identity. While the above mechanism allows to
establish a common, verified and authorized knowledge of system entities, it doesn't guarantee that a
certain unique identifier really corresponds to a particular legal identity. Even more so, while the
unique identifier remains stable, a legal identity might change, for example in the case of a merger of
two companies. Therefore, Canton provides an administrative command which allows one to associate a randomized
system identity with a human readable *display name* using the ``participant.parties.set_display_name`` command.

..  note::
    A party display name is private to the participant. If such names should be shared among participants,
    we recommend to build a corresponding Daml workflow and some automation logic, listening to the
    results of the Daml workflow and updating the display name accordingly.

Life of a Party
~~~~~~~~~~~~~~~
In the tutorials, we use the ``participant.parties.enable("name")`` function to setup a party on a participant.
To understand the identity management system in Canton, it helps to look at the steps under the hood of how a new party
is added:

1. The ``participant.parties.enable`` function determines the unique identifier of the participant: ``participant.id``.
2. The party name is built as ``name::<namespace>``, where the ``namespace`` is the one of the participant.
3. A new party-to-participant mapping is authorized on the Admin API: ``participant.topology.party_to_participant_mappings.authorize(...)``
4. The ``ParticipantTopologyManager`` gets invoked by the GRPC request, creating a new ``SignedTopologyTransaction`` and
   tests whether the authorization can be added to the local topology state. If it can, the new topology transaction
   is added to the store.
5. The ``ParticipantTopologyDispatcher`` picks up the new transaction and requests the addition on all sync domains via the
   ``RegisterTopologyTransactionRequest`` message sent to the topology manager through the sequencer.
6. A sync domain receives this request and processes it according to the policy (open or permissioned). The default setting
   is open.
7. If approved, the request service attempts to add the new topology transaction to the ``DomainTopologyManager``.
8. The ``DomainTopologyManager`` checks whether the new topology transaction can be added to the sync domain topology state. If
   yes, it gets written to the local topology store.
9. The ``DomainTopologyDispatcher`` picks up the new transaction and sends it to all participants (and back to itself)
   through the sequencer.
10. The sequencer timestamps the transaction and embeds it into the transaction stream.
11. The participants receive the transaction, verify the integrity and correctness against the topology state and add it
    to the state with the timestamp of the sequencer, such that everyone has a synchronous topology state.

Note that the ``participant.parties.enable`` macro only works if the participant controls their namespace themselves, either
directly by having the namespace key or through delegation (via ``NamespaceDelegation``).

.. TODO(i9579): adjust documentation in step 6 for closed sync domains

Participant Onboarding
~~~~~~~~~~~~~~~~~~~~~~
Key to supporting topological flexibility is that participants can easily be added to new synchronizers. Therefore, the
on-boarding of new participants to sync domains needs to be secure but convenient. Looking at the console command, we note
that in most examples, we are using the ``connect`` command to connect a participant to a sync domain. The connect command
just wraps a set of admin-api commands:

.. literalinclude:: /canton/includes/mirrored/community/app-base/src/main/scala/com/digitalasset/canton/console/commands/ParticipantAdministration.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: OnboardParticipantToConfig
   :end-before: architecture-handbook-entry-end: OnboardParticipantToConfig
   :dedent:

.. literalinclude:: /canton/includes/mirrored/community/app-base/src/main/scala/com/digitalasset/canton/console/commands/ParticipantAdministration.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: OnboardParticipantConnect
   :end-before: architecture-handbook-entry-end: OnboardParticipantConnect
   :dedent:

We note that from a user perspective, all that needs to happen by default is to provide the connection information and
accept the terms of service (if required by the sync domain) to set up a new sync domain connection. There is no separate
onboarding step performed, no giant certificate signing exercise happens, everything is set up during the
first connection attempt. However, quite a few steps happen behind the scenes. Therefore, we briefly
summarise the process here step by step:

1. The administrator of an existing participant needs to invoke the ``domains.register`` command to add a new sync domain.
   The mandatory arguments are a sync domain *alias* (used internally to refer to a particular connection) and the
   sequencer connection URL (http or https) including an optional port *http[s]://hostname[:port]/path*.
   Optional are a certificates path for a custom TLS certificate chain (otherwise the default jre root certificates
   are used) and the *sync domain ID* of a sync domain. The *sync domain ID* is the unique identifier of the sync domain that can
   be defined to prevent man-in-the-middle attacks (very similar to an SSH key fingerprint).

2. The participant opens a GRPC channel to the ``SequencerConnectService``.

3. The participant contacts the ``SequencerConnectService`` and checks if using the sync domain requires signing
   specific terms of services. If required, the terms of service are displayed to the user and an approval is
   locally stored at the participant for later. If approved, the participant attempts to connect to the sequencer.

4. The participant verifies that the remote sync domain is running a protocol version compatible with the participant's
   version using the ``SequencerConnectService.handshake``. If the participant runs an incompatible protocol version, the connection
   will fail.

5. The participant downloads and verifies the sync domain ID from the sync domain. The :ref:`sync domain ID <bootstrapping-idm>`
   can be used to verify the correct authorization of the topology transactions of the sync domain entities.
   If the sync domain ID has been provided previously during the ``domains.register`` call (or in a previous session), the two
   IDs are compared. If they are not equal, the connection fails. If the sync domain ID was not provided during the
   ``domains.register`` call, the participant uses and stores the one downloaded. We assume here that the sync domain ID is
   obtained by the participant through a secure channel such that it is sure to be talking to the right sync domain.
   Therefore, this secure channel can be either something happening outside of Canton or can be provided by TLS during
   the first time we contact a sync domain.

6. The participant downloads the *static sync domain parameters*, which are the parameters used for the transaction protocol
   on the particular sync domain, such as the cryptographic keys supported by this sync domain.

7. The participant connects to the sequencer initially as an unauthenticated member. Such members can only send
   transactions to the sync domain topology manager. The participant then sends an initial set of topology transactions
   required to identify the participant and define the keys used by the participant to the ``DomainTopologyManagerRequestService``.
   The request service inspects the validity of the transactions and decides based on the configured sync domain on-boarding
   policy. The currently supported policies are ``open`` (default) and ``permissioned``.
   While ``open`` is convenient for permissionless systems and for development, it will accept any new participant and any topology transaction.
   The ``permissioned`` policy will accept the participant's onboarding transactions only if the participant has been
   added to the allow-list beforehand.

8. The request service forwards the transactions to the sync domain topology manager, which attempts to add them to
   the state (and thus trigger the distribution to the other members on a sync domain).
   The result of the onboarding request is sent to the unauthenticated member who disconnects upon receiving
   the response.

9. If the onboarding request is approved, the participant now attempts to connect to the sequencer as the actual
   participant.

10. Once the participant is properly enabled on the sync domain and its signing key is known, the participant can subscribe
    to the ``SequencerService`` with its identity. To do that and to verify the authorization of any
    action on the ``SequencerService``, the participant must obtain an authorization token from the sync domain.
    For this purpose, the participant requests a ``Challenge`` from the sync domain. The sync domain will provide it with a ``nonce``
    and the fingerprint of the key to be used for authentication. The participant signs this nonce
    (together with the sync domain ID) using the corresponding private key.
    The reason for the fingerprint is simple: the participant needs to sign the token using the participant's signing key
    as defined by the sync domain topology state. However, as the participant will learn the true sync domain topology state only
    by reading from the ``SequencerService``, it cannot know what the key is. Therefore, the sync domain discloses this part
    of the sync domain topology state as part of the authorization challenge.

11. Using the created authentication token, the participant starts to use the *SequencerService*. On the sync domain side,
    the sync domain verifies the authenticity and validity of the token by verifying that the token is the expected one and
    is signed by the participant's signing key. The token is used to authenticate every GRPC invocation and needs
    to be renewed regularly.

12. The participant sets up the ``ParticipantTopologyDispatcher``, which is the process that tries to push all topology transactions
    created at the participant node's topology manager to the sync domain topology manager. If the participant is using its
    topology manager to manage its identity on its own, these transactions contain all the information about the
    registered parties or supported packages.

13. As mentioned above, the first set of messages received by the participant through the sequencer contains the
    sync domain topology state, which includes the signing keys of the sync domain entities. These messages are signed by the
    sequencer and topology manager and are self-consistent. If the participants know the sync domain ID, they can verify that
    they are talking to the expected sync domain and that the keys of the sync domain entities have been authorized by the owner of the
    key governing the sync domain ID.

14. Once the initial topology transactions have been read, the participant is ready to process transactions and send
    commands.

15. When a participant is (re-)enabled, the sync domain topology dispatcher analyses the set of topology transactions the
    participant has missed before. It sends these transactions to the participant via the sequencer, before publicly
    enabling the participant. Therefore, when the participant starts to read messages from the sequencer, the
    initially received messages will be the topology state of the sync domain.

Default Initialization
~~~~~~~~~~~~~~~~~~~~~~
The default initialization behavior of participant nodes and sync domains is to run their own topology manager. This provides
a convenient, automatic way to configure the nodes and make them usable without manual intervention, but it can be
turned off by setting the ``auto-init = false`` configuration option **before** the first startup.

During the auto initialization, the following steps occur:

1. On the sync domain, we generate four signing keys: one for the namespace and one each for the sequencer, mediator and
   topology manager. On the participant, we generate three keys: a namespace key, a signing key and an encryption key.

2. Using the fingerprint of the namespace, we generate the participant identity. For understandability, we use
   the node name used in the configuration file. This will change into a random identifier for privacy reasons.
   Once we've generated it, we set it using the ``set_id`` admin-api call.

3. We create a root certificate as ``NamespaceDelegation`` using the namespace key, signing with the namespace key.

4. Then, we create an ``OwnerToKeyMapping`` for the participant or sync domain entities.

The `init.identity` object can be set to control the behavior of the auto initialization. For instance,
it is possible to control the identifier name that will be given to the node during the initialization.
There are 3 possible configurations:

1. Use the node name as the node identifier

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/config-node-identifier.conf

2. Explicitly set a name

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/explicit-node-identifier.conf

3. Generate a random name

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/resources/random-node-identifier.conf

Identity Setup Guide
~~~~~~~~~~~~~~~~~~~~
As explained, Canton nodes auto-initialize by default, running their own topology managers. This is
convenient for development and prototyping. Actual deployments require more care and therefore, this section should
serve as a brief guideline.

Canton topology managers have one crucial task they must not fail at: do not lose access to or control of the
root of trust (namespace keys). Any other key problem can somehow be recovered by revoking an old key
and issuing a new owner to key association. Therefore, it is advisable that participants and parties are associated
with a namespace managed by a topology manager that has sufficient operational setups to guarantee the security and
integrity of the namespace.

Therefore, a participant or sync domain can

1. Run their own topology manager with their identity namespace key as part of the participant node.

2. Run their own topology manager on a detached computer in a self-built setup that exports topology transactions and
   transports them to the respective node (i.e. via burned CD roms).

3. Ask a trusted topology manager to issue a set of identifiers within the trusted topology manager's namespace
   as delegations and import the delegations to the local participant topology manager.

4. Let a trusted topology manager manage all the topology state on-behalf.

Obviously, there are more combinations and options possible, but these options here describe some common options
with different security and recoverability options.

To reduce the risk of losing namespace keys, additional keys can be created and allowed to operate on a
certain namespace. In fact, we recommend doing this and avoiding storing the root key on a live node.

User Identity Management
------------------------
So far we have covered how on-ledger identities are managed.

Every participant also needs to manage access to their local Ledger API and be able to give applications
permission to read or write to that API on behalf of parties.
While an on-ledger identity is represented as a party, an application on the Ledger API is represented and managed as a user.
A ledger API server manages applications' identities through:

- authentication: recognizing which user an application corresponds to (essentially by matching an application name with a user name)
- authorization: knowing which rights an authenticated user has and restricting their Ledger API access according to those rights

Authentication is based on JWT and covered in the `application development/authorization section <https://docs.daml.com/app-dev/authorization.html>`_
of the manual; the related Ledger API authorization configuration is covered in the :ref:`Ledger API JWT configuration section <ledger-api-jwt-configuration>`.

Authorization is managed by the Ledger API's User Management Service.
In essence, a user is a mapping from a user name to a set of parties with read or write permissions.
In more detail a user consists of:

- a user ID (also called user name)
- an active/deactivated status (can be used to temporarily ban a user from accessing the Ledger API)
- an optional primary party (indicates which party to use by default when submitting a Ledger API command request as this user)
- a set of user rights (describes whether a user has access to the admin portion of the Ledger API and what parties this user can act or read as)
- a set of custom annotations (string-based key-value pairs, stored locally on the Ledger API server, that can be used to attach extra information to this party, e.g. how it relates to some business entity)

All these properties except the user ID can be modified.
To learn more about annotations refer to the `Ledger API Reference documentation <https://docs.daml.com/app-dev/grpc/proto-docs.html#objectmeta>`_ .
For an overview of the ledger API's UserManagementService, see this `section  <https://docs.daml.com/app-dev/services.html#user-management-service>`_.

You can manage users through the :ref:`Canton console user management commands <ledger_api.users.list>`, an alpha feature.
See the cookbook below for some concrete examples of how to manage users.

Cookbook
--------

Manage Users
~~~~~~~~~~~~~~~~~~~~~~

In this section, we present how you can manage participant users using the Canton console commands.
First, we create three parties that we'll use in subsequent examples:

.. snippet:: user_management
    .. assert:: { participant1.domains.connect_local(mydomain); true }
    .. success:: val Seq(alice, bob, eve) = Seq("alice", "bob", "eve").map(p => participant1.parties.enable(name = p, waitForDomain = DomainChoice.All))

Create
^^^^^^

Next, create a user called ``myuser`` with act-as ``alice`` and read-as ``bob`` permissions and active user status. This user's primary party is ``alice``. The user is not an administrator
and has some custom annotations.

.. snippet:: user_management
    .. success:: val user = participant1.ledger_api.users.create(id = "myuser", actAs = Set(alice), readAs = Set(bob), primaryParty = Some(alice), participantAdmin = false, isActive = true, annotations = Map("foo" -> "bar", "description" -> "This is a description"))
    .. assert:: user.id == "myuser"

There are some restrictions on what constitutes a valid annotation key. In contrast, the only constraint for annotation values is that they must not be empty.
To learn more about annotations refer to the `Ledger API Reference documentation <https://docs.daml.com/app-dev/grpc/proto-docs.html#objectmeta>`_.

Update
^^^^^^

You can update a user's primary party, active/deactivated status and annotations.
(You can also change what rights a user has, but using a different method presented further below.)

In the following snippet, you change the user's primary party to be unassigned,
leave the active/deactivated status intact,
and update the annotations.
In the annotations, you change the value of the ``description`` key, remove the ``foo`` key and add the new ``baz`` key.
The return value contains the updated state of the user:

.. snippet:: user_management
    .. success:: val updatedUser = participant1.ledger_api.users.update(id = user.id, modifier = user => { user.copy(primaryParty = None, annotations = user.annotations.updated("description", "This is a new description").removed("foo").updated("baz", "bar")) })
    .. assert:: updatedUser.id == "myuser"
    .. assert:: updatedUser.annotations == Map("description" -> "This is a new description", "baz" -> "bar")

You can also update the user's identity provider ID.
In the following snippets, you change the user's identity provider ID to the newly created one.
Note that originally the user belonged to the default identity provider whose id is represented as the empty string ```""```.

.. snippet:: user_management
    .. success:: participant1.ledger_api.identity_provider_config.create("idp-id1", isDeactivated = false, jwksUrl = "http://someurl", issuer = "issuer1", audience = None)
    .. success:: participant1.ledger_api.users.update_idp("myuser", sourceIdentityProviderId="", targetIdentityProviderId="idp-id1")
    .. success:: participant1.ledger_api.users.get("myuser", identityProviderId="idp-id1")

You can change the user's identity provider ID back to the default one:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.update_idp("myuser", sourceIdentityProviderId="idp-id1", targetIdentityProviderId="")
    .. success:: participant1.ledger_api.users.get("myuser", identityProviderId="")

Inspect
^^^^^^^

You can fetch the current state of the user as follows:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.get(user.id)


You can query what rights a user has:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.rights.list(user.id)

You can grant more rights.
The returned value contains only newly granted rights; it does not contain rights the user already had even if you attempted to grant them again (like the read-as ``alice`` right in this example):

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.rights.grant(id = user.id, actAs = Set(alice, bob), readAs = Set(eve), participantAdmin = true)

You can revoke rights from the user.
Again, the returned value contains only rights that were actually removed:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.rights.revoke(id = user.id, actAs = Set(bob), readAs = Set(alice), participantAdmin = true)

Now that you have granted and revoked some rights, you can fetch all of the user's rights again and see what they are:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.rights.list(user.id)

Also, multiple users can be fetched at the same time.
To do that, first create another user called ``myotheruser`` and then list all the users whose user name starts with ``my``:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.create(id = "myotheruser")
    .. success:: participant1.ledger_api.users.list(filterUser = "my")


Decommission
^^^^^^^^^^^^^^

You can delete a user by its ID:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.delete("myotheruser")

You can confirm it has been removed by e.g. listing it:

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.list("myotheruser")

If you want to prevent a user from accessing the ledger API it may be better to deactivate it rather than deleting it. A deleted user can be recreated as if it never existed in the first place, while a deactivated user must be explicitly reactivated to be able to access the ledger API again.

.. snippet:: user_management
    .. success:: participant1.ledger_api.users.update("myuser", user => user.copy(isActive = false))

.. _canton-add-party-to-a-participant:


Configure a default Participant Admin
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Fresh participant nodes come with a default participant admin user called ``participant_admin``, which
can be used to bootstrap other users.
You might prefer to have an admin user with a different user ID ready on a participant startup.
For such situations, you can specify an additional participant admin user with the user ID of your choice.

.. note:: If a user with the specified ID already exists, then no additional user will be created,
          even if the preexisting user was not an admin user.

.. code-block:: none
   :caption: additional-admin.conf

   canton.participants.myparticipant.ledger-api.user-management-service.additional-admin-user-id = "my-admin-id"


Adding a new Party to a Participant
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The simplest operation is adding a new party to a participant. For this, we add it normally at the topology manager
of the participant, which in the default case is part of the participant node. There is a simple macro to enable the
party on a given participant if the participant is running their own topology manager:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/TopologyManagementIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: EnableParty
   :end-before: architecture-handbook-entry-end: EnableParty
   :dedent:

This will create a new party in the namespace of the participant's topology manager.

And there is the corresponding disable macro:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/security/topology/TopologyManagementIntegrationTest.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: DisableParty
   :end-before: architecture-handbook-entry-end: DisableParty
   :dedent:

The macros themselves just use ``topology.party_to_participant_mappings.authorize`` to create the new party, but add some convenience such
as automatically determining the parameters for the ``authorize`` call.

.. note::
    Please note that the ``participant.parties.enable`` macro will add the parties to the same namespace as the participant is in.
    It only works if the participant has authority over that namespace either by possessing the root or a delegated key.

.. _separate-party-migration:

Client Controlled Party
~~~~~~~~~~~~~~~~~~~~~~~

Parties are only weakly tied to participant nodes. They can be allocated in their own namespace and then
delegated to a given participant. For simplicity and convenience, the participant creates new parties
in its own namespace by default, but there are situations where this is not desired.

A common scenario is that you first host the party on behalf of your client, but subsequently hand over
the party to the client's node. With the default party allocation, you would still control the party of the client.

To avoid this, you need your client to create a new party on their own and export a party delegation
to you. This party delegation can then be imported into your topology state, which will then allow you
to act on behalf of the party.

For this process, we use a participant node which won't be connected to any sync domain. We don't need the full
node, but just the topology manager. First, we need to find out the participant ID of the hosting node:

.. snippet:: client_controlled_party
    .. hidden:: participant2.domains.connect_local(mydomain)
    .. hidden:: val client = participant1
    .. hidden:: val hosting = participant2
    .. success:: hosting.id.toProtoPrimitive

This identifier needs to be communicated to the client and can be imported using ``ParticipantId.tryFromProtoPrimitive``.
The client then creates first a new key (they could use the default key created):

.. snippet:: client_controlled_party
    .. success:: val secret = client.keys.secret.generate_signing_key("my-party-key")

and an appropriate root certificate for this key:

.. snippet:: client_controlled_party
    .. success:: val rootCert = client.topology.namespace_delegations.authorize(TopologyChangeOp.Add,secret.fingerprint,secret.fingerprint,isRootDelegation = true)

This root certificate needs to be exported into a file:

.. snippet:: client_controlled_party
    .. success:: import com.digitalasset.canton.util.BinaryFileUtil
    .. success:: BinaryFileUtil.writeByteStringToFile("rootCert.bin", rootCert)

Define the party ID of the party you want to create:

.. snippet:: client_controlled_party
    .. success:: val partyId = PartyId("Client", secret.fingerprint)

Create and export the party to participant delegation:

.. snippet:: client_controlled_party
    .. hidden:: val hostingNodeId = participant2.id
    .. success:: val partyDelegation = client.topology.party_to_participant_mappings.authorize(TopologyChangeOp.Add, partyId, hostingNodeId, RequestSide.From)
    .. success:: BinaryFileUtil.writeByteStringToFile("partyDelegation.bin", partyDelegation)

The client now shares the ``rootCert.bin`` and ``partyDelegation.bin`` files with the hosting node. The hosting
node imports them into their topology state:

.. snippet:: client_controlled_party
    .. success:: hosting.topology.load_transaction(BinaryFileUtil.tryReadByteStringFromFile("rootCert.bin"))
    .. success:: hosting.topology.load_transaction(BinaryFileUtil.tryReadByteStringFromFile("partyDelegation.bin"))

Finally, the hosting node needs to issue the corresponding topology transaction to enable the party on its node:

.. snippet:: client_controlled_party
    .. success:: hosting.topology.party_to_participant_mappings.authorize(TopologyChangeOp.Add, partyId, hosting.id, RequestSide.To)
    .. hidden:: utils.synchronize_topology()
    .. assert:: hosting.parties.hosted("Client").nonEmpty

An alternative method would be to issue an identifier delegation certificate to a key controlled by the hosting node.
In this case, the party wouldn't be delegated to a specific participant. Instead, the unique identifier would be delegated to a
specific key, which would then in turn be able to delegate the party to a participant.

.. _offline-party-migration:

Replicate Party to Another Participant Node
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. enterprise-only::

.. note::
    - The improved macros are available in Daml Enterprise 2.x as of release 2.8.1.
    - In 2.x, party migration has limitations. Please read the documentation carefully.
    - The macros work with protocol version 4 or later.
    - The involved participants must be entirely quiet during the migration. Therefore, the migration can only happen during a maintenance window of the sync domain where the rate is set to 0.
    - The target participant must not know about any contract involving the party prior to the migration.

The weak coupling of parties to participants allows you to migrate parties together with their active contract set from
one participant node to another. The process described below uses a specific set of commands that have to be executed in the right order with some care.

We assume that there are three participants: The ``sourceParticipant`` from which the existing contract set will be copied,
a ``targetParticipant`` to which the contract set will be copied, and a ``controllingParticipant`` that owns the party.
In some cases, the controlling participant will be the same as the source participant, but this is not required.

.. note::

    Please note that the entire system needs to be totally quiet for this process to succeed. You
    currently cannot migrate a party under load on 2.x. If you migrate a party on a system that processes
    transactions, the processing data will eventually become corrupt, breaking your node. The macros
    will refuse to run if the system is not idle. Therefore, follow the steps below carefully.

First, turn off transaction processing on the sync domain by setting the rate to 0 and wait for all timeouts to have
elapsed (mediator & participant reaction timeout):

.. snippet:: party_migration
    .. success:: mydomain.service.set_max_rate_per_participant(0)
    .. hidden:: mydomain.service.update_dynamic_domain_parameters(_.update(participantResponseTimeout = 1.seconds, mediatorReactionTimeout = 1.seconds))
    .. hidden:: participant1.parties.enable("Alice")
    .. hidden:: participants.all.domains.connect_local(mydomain)
    .. hidden:: val sourceParticipant = participant1
    .. hidden:: val controllingParticipant = participant1
    .. hidden:: val targetParticipant = participant2

This is necessary as otherwise the contract set might change, or there might be inflight transactions and locked
contracts which would confuse the newly onboarded participant.

Assuming there is a party named ``Alice`` permissioned on the ``sourceParticipant``, you first download
the active contract set of the party:

.. snippet:: party_migration
    .. hidden:: participant1.topology.synchronisation.await_idle()
    .. success:: val alice = sourceParticipant.parties.find("Alice")
    .. hidden:: com.digitalasset.canton.concurrent.Threading.sleep(2000)
    .. success:: repair.party_migration.step1_store_acs(sourceParticipant, Set(alice), partiesOffboarding = true, "alice.acs.gz")

This will store all the contracts in the file. If the file ends with ".gz", then the content will be compressed.
After transferring the file to the target participant, you first need to disconnect the target participant from the
sync domain, because the repair service cannot run with an active sync domain connection:

.. snippet:: party_migration
    .. success:: targetParticipant.domains.disconnect_all()

Once disconnected, import the contracts using the next repair macro:

.. snippet:: party_migration
    .. success:: repair.party_migration.step2_import_acs(targetParticipant, Set(alice), "alice.acs.gz")

Although this step has imported the contracts, the party is still not enabled on the target participant. For a
party to be delegated to a participant, both the owner of the party and the participant need to issue the
required topology transactions. If the controlling participant is connected to the sync domain, you run the next
step:

.. snippet:: party_migration
    .. hidden:: val targetParticipantId = targetParticipant.id
    .. hidden:: targetParticipant.domains.reconnect_all()
    .. success:: repair.party_migration.step3_delegate_party_to_target_node(controllingParticipant, Set(alice), targetParticipantId)
    .. hidden:: utils.synchronize_topology()

This will issue the party to participant topology transaction of type ``From``. The ``To`` transaction must be
issued on the ``targetParticipant``, using the fourth step. The participant must be connected to the sync domain for this step:

.. snippet:: party_migration
    .. success:: targetParticipant.domains.reconnect_all()
    .. success:: repair.party_migration.step4_enable_party_on_target(targetParticipant, Set(alice))

After this step, the party is enabled on the target participant and the active contract set has been migrated,
but the party is now hosted by both ``sourceParticipant`` and ``targetParticipant``.

If you want to remove the party from the source participant, continue with the next step before resetting
the sync domain rate back to its original value. First, unregister the party from the source participant:

.. snippet:: party_migration
    .. success:: repair.party_migration.step5_remove_party_delegation_from_source(controllingParticipant, Set(alice), sourceParticipant)

Then, disconnect the source participant from the sync domain:

.. snippet:: party_migration
    .. success:: sourceParticipant.domains.disconnect_all()

Finally, remove the active contracts of ``Alice`` from the source participant:

.. snippet:: party_migration
    .. success:: repair.party_migration.step6_cleanup_source(sourceParticipant, "alice.acs.gz", Set(alice))

Thereafter, reconnect to the sync domain and re-enable transaction processing on the sync domain:

.. snippet:: party_migration
    .. success:: sourceParticipant.domains.reconnect_all()
    .. success:: mydomain.service.set_max_rate_per_participant(10000)
    .. hidden:: mydomain.service.update_dynamic_domain_parameters(_.update(participantResponseTimeout = 30.seconds, mediatorReactionTimeout = 30.seconds))
    .. assert:: participant1.health.maybe_ping(participant2).nonEmpty

.. _canton-party-on-multiple-nodes-expert mode:

Party on Multiple Nodes
~~~~~~~~~~~~~~~~~~~~~~~

.. note::
        The below section is used to demonstrate the capabilities of Canton or to be helpful in special setups.
        Please use the repair macros as explained above to migrate parties between nodes. The below section
        contains commands that can break your system if used incorrectly.

Assuming we have party ``("Alice", N1)`` which we want to host on two participants: ``("participant1", N1)`` and
``("participant2", N2)``. In this case, we have the party "Alice" in namespace ``N1``, whereas the participant2 is in
namespace ``N2``. In order to set this up, we need to appropriately authorize the participants to act on behalf of the
party. In this example, we assume that the party is added to both nodes at the same time before any contract is
created. If you want to migrate an existing party, :ref:`follow the guide above <offline-party-migration>`.

To make sure that we don't accidentally create a contract that is observed by one node and not
the others, set the sync domain rate to 0, which will ensure that no contracts can be created on the sync domain during
this maintenance period:

.. snippet:: party_on_two_nodes
    .. success:: mydomain.service.set_max_rate_per_participant(0)

Starting with a party allocated on participant1:

.. snippet:: party_on_two_nodes
    .. hidden:: participants.all.domains.connect_local(mydomain)
    .. success:: val alice = participant1.parties.enable("Alice")
    .. hidden:: utils.synchronize_topology()

To add this party to participant2, participant2 must first agree to host the party. This is done by authorizing
the ``RequestSide.To`` of the party to participant mapping on the target participant:

.. snippet:: party_on_two_nodes
    .. success:: participant2.topology.party_to_participant_mappings.authorize(TopologyChangeOp.Add, alice, participant2.id, RequestSide.To, ParticipantPermission.Submission)
    .. hidden:: utils.synchronize_topology()

The permission of the node can be restricted by setting the appropriate ``ParticipantPermission`` in the
authorization call to either ``Observation`` or ``Confirmation`` instead of the default ``Submission``. This allows
setups where a party is hosted with ``Submission`` permissions on one node and ``Confirmation`` on another to increase
the liveness of the party.

.. note::

    The distinction between ``Submission`` and ``Confirmation`` is only enforced in the participant node.
    A malicious participant node with ``Confirmation`` permission for a certain party can submit transactions in the name of
    the party. This is due to Canton's high level of privacy where validators do not know the identity of the
    submitting participant. Therefore, a party who delegates ``Confirmation`` permissions to a participant
    should trust the participant sufficiently.

Next, add the ``RequestSide.From`` transaction such that the party is activated on the target participant:

.. snippet:: party_on_two_nodes
    .. success:: participant1.topology.party_to_participant_mappings.authorize(TopologyChangeOp.Add, alice, participant2.id, RequestSide.From, ParticipantPermission.Submission)

Check that the party is now hosted by two participants:

.. snippet:: party_on_two_nodes
    .. success:: participant1.parties.list("Alice")
    .. assert:: participant1.parties.list("Alice").flatMap(_.participants.map(_.participant)).contains(participant2.id)

Finally, the transaction processing on the sync domain can be re-enabled again:

.. snippet:: party_on_two_nodes
    .. success:: mydomain.service.set_max_rate_per_participant(100)
    .. hidden:: import scala.jdk.CollectionConverters._
    .. hidden:: import com.digitalasset.canton.participant.admin.workflows.java.pingpong.Cycle
    .. hidden:: participant1.ledger_api.javaapi.commands.submit_flat(Seq(alice), new Cycle("hello", alice.toProtoPrimitive).create.commands.asScala.toSeq)

Both participants will now see the same contracts, and depending on the permissions, be able to submit on behalf of
the party. Each hosting participant will be included in the transaction, which means that there is an upper limit
on where this feature is useful. If you need to share contract data with many participants, you should consider
using explicit disclosure and sharing contract data out of band.

.. _manually_initializing_node:

Manually Initializing a Node
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
There are situations where a node should not be automatically initialized, but where you should control
each step of the initialization. For example, this might be the case when a node in the setup does
not control its own identity, when you do not want to store the identity key on the node for security
reasons, or when you want to set our own keys (e.g. when keys are externally stored in a Key Management Service - KMS).

The following demonstrates the basic steps on how to initialize a node:

Keys Initialization
^^^^^^^^^^^^^^^^^^^

The following steps describe how to manually generate the necessary Canton keys (e.g. for a participant):

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/topology/TopologyManagementHelper.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: ManualInitKeys
   :end-before: architecture-handbook-entry-end: ManualInitKeys
   :dedent:

.. note::
   Be aware that in some particular use cases, you might want to register keys rather than generate new ones (for instance
   when you have pre-generated KMS keys that you want to use). Please refer to
   :ref:`External Key Storage with a Key Management Service (KMS) <external_key_storage>` for more details.

.. _manually-init-domain:

Synchronization Domain Initialization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The following steps describe how to manually initialize a sync domain node:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/topology/TopologyManagementHelper.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: ManualInitDomain
   :end-before: architecture-handbook-entry-end: ManualInitDomain
   :dedent:

.. _manually-init-participant:

Participant Initialization
^^^^^^^^^^^^^^^^^^^^^^^^^^
The following steps describe how to manually initialize a participant node:

.. literalinclude:: /canton/includes/mirrored/enterprise/app/src/test/scala/com/digitalasset/canton/integration/tests/topology/TopologyManagementHelper.scala
   :language: scala
   :start-after: architecture-handbook-entry-begin: ManualInitParticipant
   :end-before: architecture-handbook-entry-end: ManualInitParticipant
   :dedent:
