..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _identity_management_user_manual:

Identity Management
===================
On-ledger identity management focuses on the distributed aspect of identities across Canton system entities, while
user identity management focuses on individual participants managing access of their users to their ledger APIs.

Canton comes with a built in identity management system used to manage on-ledger identities. The technical details
are explained in the :ref:`architecture section <identity-manager-1>`, while this write up here is meant to give a high
level explanation.

The identity management system is self-contained and built without a trusted central entity or pre-defined root
certificate such that anyone can connect with anyone, without the need of some central approval and without the
danger of losing self-sovereignty.

Introduction
------------
What is a Canton Identity?
~~~~~~~~~~~~~~~~~~~~~~~~~~
When two system entities such as a participant, domain topology manager, mediator or sequencer communicate
with each other, they will use asymmetric cryptography to encrypt messages and sign message contents
such that only the recipient can decrypt the content, verify the authenticity of the message, or prove its origin.
Therefore, we need a method to uniquely identify the system entities and a way to associate encryption and signing keys
with them.

On top of that, Canton uses the contract language Daml, which represents contract ownership and rights
through `parties <https://docs.daml.com/concepts/glossary.html#party>`_. But parties are not primary members
of the Canton synchronisation protocol. They are represented by participants and therefore we need to
uniquely identify parties and relate them to participants, such that a participant can represent several
parties (and in Canton, a party can be represented by several participants).

Unique Identifier
~~~~~~~~~~~~~~~~~
A Canton identity is built out of two components: a random string ``X`` and a fingerprint of a public key ``N``.
This combination, ``(X,N)``, is called a *unique identifier* and is assumed to be globally unique by design.
This unique identifier is used in Canton to refer to particular parties, participants or domain entities.
A system entity (such as a party) is described by the combination of role (party, participant, mediator, sequencer,
domain topology manager) and its unique identifier.

The system entities require knowledge about the keys which will be used for encryption and signing by the
respective other entities.
This knowledge is distributed and therefore, the system entities require a way to verify that a certain
association of an entity with a key is correct and valid. This is the purpose of the fingerprint
of a public key in the unique identifier, which is referred to as *Namespace*. And the secret key of the
corresponding namespace acts as the *root of trust* for that particular namespace, as explained later.

.. _identity-transactions:

Topology Transactions
~~~~~~~~~~~~~~~~~~~~~
In order to remain flexible and be able to change keys and cryptographic algorithms, we don't identify the
entities using a single static key, but we need a way to dynamically associate participants or domain entities
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
signature of the serialised topology transaction. This authorization can be either direct, if it is signed
by the secret key of the namespace, or indirect, if it is signed by a delegated key. In order
to delegate the signing right to another key, there are other topology transactions of type *NamespaceDelegation* or
*IdentifierDelegation* that allow one to do that. A :ref:`namespace delegation <namespace-delegation>` delegates
entire namespaces to a certain key, such as saying the key identifier through the fingerprint *AABBCCDDEE...* is now
allowed to authorize topology transactions within the namespace of the key *VVWWXXYYZZ...*. An
:ref:`identifier delegation <identifier-delegation>` delegates authority over a certain identifier to a key,
which means that the delegation key can only authorize topology transactions that act on a specific identifier and not
the entire namespace.

Now, signing of topology transactions happens in a ``TopologyManager``. Canton has many topology managers. In fact, every
participant node and every domain have topology managers with exactly the same functional capabilities, just different
impact. They can create new keys, new namespaces and the identity of new participants, parties and even domains. And
they can export these topology transactions such that they can be imported at another topology manager. This allows to
manage Canton identities in quite a wide range of ways. A participant can operate their own topology manager which
allows them individually to manage their parties. Or they can associate themselves with another topology manager and let them
manage the parties that they represent or keys they use. Or something in between, depending on the introduced
delegations and associations.

The difference between the domain topology manager and the participant topology manager is that the domain topology
manager establishes the valid topology state in a particular domain by distributing topology transactions in a way that
every domain member ends up with the same topology state. However, the domain topology manager is just a gate keeper of
the domain that decides who is let in and who not on that particular domain, but the actual topology statements originate from
various sources. As such, the domain topology manager can only block the distribution, but cannot fake topology
transactions.

The participant topology manager only manages an isolated topology state. However, there is a dispatcher attached to
this particular topology manager that attempts to register locally registered identities with remote domains, by sending
them to the domain topology managers, who then decide on whether they want to include them or not.

The careful reader will have noted that the described identity system indeed does not have a single root of trust or
decision maker on who is part of the overall system or not. But also that the topology state for the distributed
synchronisation varies from domain to domain, allowing very flexible topologies and setups.

Legal Identities
~~~~~~~~~~~~~~~~
In Canton, we separate a system identity from the legal identity. While the above mechanism allows to
establish a common, verified and authorized knowledge of system entities, it doesn't guarantee that a
certain unique identifier really corresponds to a particular legal identity. Even more so, while the
unique identifier remains stable, a legal identity might change, for example in the case of a merger of
two companies. Therefore, Canton provides an administrative command which allows to associate a randomized
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
3. A new party to participant mapping is authorized on the Admin Api: ``participant.topology.party_to_participant_mappings.authorize(...)``
4. The ``ParticipantTopologyManager`` gets invoked by the GRPC request, creating a new ``SignedTopologyTransaction`` and
   tests whether the authorization can be added to the local topology state. If it can, the new topology transaction
   is added to the store.
5. The ``ParticipantTopologyDispatcher`` picks up the new transaction and requests the addition on all domains via the
   ``RegisterTopologyTransactionRequest`` message sent to the topology manager through the sequencer.
6. A domain receives this request and processes it according to the policy (open or permissioned). The default setting
   is open.
7. If approved, the request service attempts to add the new topology transaction to the ``DomainTopologyManager``.
8. The ``DomainTopologyManager`` checks whether the new topology transaction can be added to the domain topology state. If
   yes, it gets written to the local topology store.
9. The ``DomainTopologyDispatcher`` picks up the new transaction and sends it to all participants (and back to itself)
   through the sequencer.
10. The sequencer timestamps the transaction and embeds it into the transaction stream.
11. The participants receive the transaction, verify the integrity and correctness against the topology state and add it
    to the state with the timestamp of the sequencer, such that everyone has a synchronous topology state.

Note that the ``participant.parties.enable`` macro only works if the participant controls their namespace themselves, either
directly by having the namespace key or through delegation (via ``NamespaceDelegation``).

.. TODO(i9579): adjust documentation in step 6 for closed domains

Participant Onboarding
~~~~~~~~~~~~~~~~~~~~~~
Key to support topological flexibility is that participants can easily be added to new domains. Therefore, the
on-boarding of new participants to domains needs to be secure but convenient. Looking at the console command, we note
that in most examples, we are using the ``connect`` command to connect a participant to a domain. The connect command
just wraps a set of admin-api commands:

.. code-block:: scala

          val certificates = OptionUtil.emptyStringAsNone(certificatesPath).map { path =>
            BinaryFileUtil.readByteStringFromFile(path) match {
              case Left(err) => throw new IllegalArgumentException(s"failed to load ${path}: ${err}")
              case Right(bs) => bs
            }
          }
          DomainConnectionConfig.grpc(
            domainAlias,
            connection,
            manualConnect,
            domainId,
            certificates,
            priority,
            initialRetryDelay,
            maxRetryDelay,
            timeTrackerConfig,
          )


.. code-block:: scala

            // register the domain configuration
            register(config.copy(manualConnect = true))
            if (!config.manualConnect) {
              // fetch and confirm domain agreement
              config.sequencerConnection match {
                case _: GrpcSequencerConnection =>
                  confirm_agreement(config.domain.unwrap)
                case _ => ()
              }
              reconnect(config.domain.unwrap, retry = false).discard
              // now update the domain settings to auto-connect
              modify(config.domain.unwrap, _.copy(manualConnect = false))
            }


We note that from a user perspective, all that needs to happen by default is to provide the connection information and
accepting the terms of service (if required by the domain) to set up a new domain connection. There is no separate
on-boarding step performed, no giant certificate signing exercise happens, everything is set up during the
first connection attempt. However, quite a few steps happen behind the scenes. Therefore, we briefly
summarise the process here step by step:

1. The administrator of an existing participant needs to invoke the ``domains.register`` command to add a new domain.
   The mandatory arguments are a domain *alias* (used internally to refer to a particular connection) and the
   sequencer connection URL (http or https) including an optional port *http[s]://hostname[:port]/path*.
   Optional are a certificates path for a custom TLS certificate chain (otherwise the default jre root certificates
   are used) and the *domain id* of a domain. The *domain id* is the unique identifier of the domain that can
   be defined to prevent man-in-the-middle attacks (very similar to an ssh key fingerprint).

2. The participant opens a GRPC channel to the ``SequencerConnectService``.

3. The participant contacts the ``SequencerConnectService`` and checks if using the domain requires signing
   specific terms of services. If required, the terms of service are displayed to the user and an approval is
   locally stored at the participant for later. If approved, the participant attempts to connect to the sequencer.

4. The participant verifies that the remote domain is running a protocol version compatible with the participant's
   version using the ``SequencerConnectService.handshake``. If the participant runs an incompatible protocol version, the connection
   will fail.

5. The participant will download and verify the domain id from the domain. The :ref:`domain id <bootstrapping-idm>`
   can be used to verify the correct authorization of the topology transactions of the domain entities.
   If the domain id has been provided previously during the ``domains.register`` call (or in a previous session), the two
   ids will be compared. If they are not equal, the connection will fail. If the domain id was not provided during the
   ``domains.register`` call, the participant will use and store the one downloaded. We assume here that the domain id is
   obtained by the participant through a secure channel such that it is sure to be talking to the right domain.
   Therefore, this secure channel can be either something happening outside of Canton or can be provided by TLS during
   the first time we contact a domain.

6. The participant downloads the *static domain parameters*, which are the parameters used for the transaction protocol
   on the particular domain, such as the cryptographic keys supported on this domain.

7. The participant connects to the sequencer initially as an unauthenticated member. Such members can only send
   transactions to the domain topology manager. The participant then sends an initial set of topology transactions
   required to identify the participant and define the keys used by the participant to the ``DomainTopologyManagerRequestService``.
   The request service inspects the validity of the transactions and decides based on the configured domain on-boarding
   policy. The currently supported policies are ``open`` (default) and ``permissioned``.
   While ``open`` is convenient for permissionless systems and for development, it will accept any new participant and any topology transaction.
   The ``permissioned`` policy will accept the participant's onboarding transactions only if the participant has been
   added to the allow-list beforehand.

8. The request service forwards the transactions to the domain topology manager, who attempts to add it to
   the state (and thus trigger the distribution to the other members on a domain).
   The result of the onboarding request is sent to the unauthenticated member who disconnects upon receiving
   the response.

9. If the onboarding request is approved, the participant now attempts to connect to the sequencer as the actual
   participant.

10. Once the participant is properly enabled on the domain and its signing key is known, the participant can subscribe
    to the ``SequencerService`` with its identity. In order to do that and in order to verify the authorisation of any
    action on the ``SequencerService``, the participant requires to obtain an authorization token from the domain.
    For this purpose, the participant requests a ``Challenge`` from the domain. The domain will provide it with a ``nonce``
    and the fingerprint of the key to be used for authentication. The participant signs this nonce
    (together with the domain id) using the corresponding private key.
    The reason for the fingerprint is simple: the participant needs to sign the token using the participants signing key
    as defined by the domain topology state. However, as the participant will learn the true domain topology state only
    by reading from the ``SequencerService``, it cannot know what the key is. Therefore, the domain discloses this part
    of the domain topology state as part of the authorisation challenge.

11. Using the created authentication token, the participant starts to use the *SequencerService*. On the domain side,
    the domain verifies the authenticity and validity of the token by verifying that the token is the expected one and
    is signed by the participant's signing key. The token is used to authenticate every GRPC invocation and needs
    to be renewed regularly.

12. The participant sets up the ``ParticipantTopologyDispatcher``, which is the process that tries to push all topology transactions
    created at the participant node's topology manager to the domain topology manager. If the participant is using its
    topology manager to manage its identity on its own, these transactions contain all the information about the
    registered parties or supported packages.

13. As mentioned above, the first set of messages received by the participant through the sequencer will contain the
    domain topology state, which includes the signing keys of the domain entities. These messages are signed by the
    sequencer and topology manager and are self-consistent. If the participants know the domain id, they can verify that
    they are talking to the expected domain and that the keys of the domain entities have been authorized by the owner of the
    key governing the domain id.

14. Once the initial topology transactions have been read, the participant is ready to process transactions and send
    commands.

15. When a participant is (re-)enabled, the domain topology dispatcher analyses the set of topology transactions the
    participant has missed before. It sends these transactions to the participant via the sequencer, before publicly
    enabling the participant. Therefore, when the participant starts to read messages from the sequencer, the
    initially received messages will be the topology state of the domain.

Default Initialization
~~~~~~~~~~~~~~~~~~~~~~
The default initialization behaviour of participant and domain nodes is to run their own topology manager. This provides
a convenient, automatic way to configure the nodes and make them usable without manual intervention, but it can be
turned off by setting the ``auto-init = false`` configuration option **before** the first startup.

During the auto initialization, the following steps will happen:

1. On the domain, we generate four signing keys: one for the namespace and one each for the sequencer, mediator and
   topology manager. On the participant, we generate three keys: a namespace key, a signing key and an encryption key.

2. Using the fingerprint of the namespace, we generate the participant identity. For understandability, we use
   the node name used in the configuration file. This will change into a random identifier for privacy reasons.
   Once we've generated it, we set it using the ``set_id`` admin-api call.

3. We create a root certificate as ``NamespaceDelegation`` using the namespace key, signing with the namespace key.

4. Then, we create an ``OwnerToKeyMapping`` for the participant or domain entities.

The `init.identity` object can be set to control the behavior of the auto initialization. For instance,
it is possible to control the identifier name that will be given to the node during the initialization.
There are 3 possible configurations:

1. Use the node name as the node identifier

.. code-block:: none

    canton.participants.participant1.init.identity.node-identifier.type = config


2. Explicitly set a name

.. code-block:: none

    canton.participants.participant1.init.identity.node-identifier.type = explicit
    canton.participants.participant1.init.identity.node-identifier.name = MyName


3. Generate a random name

.. code-block:: none

    canton.participants.participant1.init.identity.node-identifier.type = random


Identity Setup Guide
~~~~~~~~~~~~~~~~~~~~
As explained, Canton nodes auto-initialise themselves by default, running their own topology managers. This is
convenient for development and prototyping. Actual deployments require more care and therefore, this section should
serve as a brief guideline.

Canton topology managers have one crucial task they must not fail at: do not lose access to or control of the
root of trust (namespace keys). Any other key problem can somehow be recovered by revoking an old key
and issuing a new owner to key association. Therefore, it is advisable that participants and parties are associated
with a namespace managed by a topology manager that has sufficient operational setups to guarantee the security and
integrity of the namespace.

Therefore, a participant or domain can

1. Run their own topology manager with their identity namespace key as part of the participant node.

2. Run their own topology manager on a detached computer in a self-built setup that exports topology transactions and
   transports them to the respective node (i.e. via burned CD roms).

3. Ask a trusted topology manager to issue a set of identifiers within the trusted topology manager's namespace
   as delegations and import the delegations to the local participant topology manager.

4. Let a trusted topology manager manage all the topology state on-behalf.

Obviously, there are more combinations and options possible, but these options here describe some common options
with different security and recoverability options.

In order to reduce the risk of losing namespace keys, additional keys can be created and allowed to operate on a
certain namespace. In fact, we recommend doing this and avoid storing the root key on a live node.

User Identity Management
------------------------
So far we have covered how on-ledger identities are managed.

Every participant also needs to manage access to their local Ledger API and be able to give applications
permission to read or write to that API on behalf of parties.
While an on-ledger identity is represented as a party, an application on the Ledger API is represented and managed as a user.
A ledger API server manages applications' identities through:

- authentication: recognizing which user an application corresponds to (essentially by matching an application name with a user name)
- authorization: knowing which rights an authenticated user has and restricting their Ledger API access according to those rights

Authentication is based on JWT and covered in the `application development / authorization section <https://docs.daml.com/app-dev/authorization.html>`_
of the manual; the related Ledger API authorization configuration is covered in the :ref:`Ledger API JWT configuration section <ledger-api-jwt-configuration>`.

Authorization is managed by the Ledger API's User Management Service.
In essence, a user is a mapping from a user name to a set of parties with read or write permissions.
In more detail a user consists of:

- a user id (also called user name)
- an active/deactivated status (can be used to temporarily ban a user from accessing the Ledger API)
- an optional primary party (indicates which party to use by default when submitting a Ledger API command requests as this user)
- a set of user rights (describes whether a user has access to the admin portion of the Ledger API and what parties this user can act or read as)
- a set of custom annotations (string based key-value pairs, stored locally on the Ledger API server, that can be used to attach extra information to this party, e.g. how it relates to some business entity)

All these properties except the user id can be modified.
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

.. code-block:: none

    @ val (alice, bob, eve) = (participant1.parties.enable("alice"), participant1.parties.enable("bob"), participant1.parties.enable("eve"))
    (alice, bob, eve) : (PartyId, PartyId, PartyId) = (alice::1220a40b326d..., bob::1220a40b326d..., eve::1220a40b326d...)

Create
^^^^^^

Next, create a user called ``myuser`` with act-as ``alice`` and read-as ``bob`` permissions and active user status. This user's primary party is ``alice``. The user is not an administrator
and has some custom annotations.

.. code-block:: none

    @ val user = participant1.ledger_api.users.create(id = "myuser", actAs = Set(alice.toLf), readAs = Set(bob.toLf), primaryParty = Some(alice.toLf), participantAdmin = false, isActive = true, annotations = Map("foo" -> "bar", "description" -> "This is a description"))
    user : User = User(
      id = "myuser",
      primaryParty = Some(
        value = "alice::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"
      ),
      isActive = true,
      annotations = Map("foo" -> "bar", "description" -> "This is a description")
    )
    

There are some restrictions for what constitutes a valid annotation key. In contrast, the only constraint for annotation values is that they must not be empty.
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

.. code-block:: none

    @ val updatedUser = participant1.ledger_api.users.update(id = user.id, modifier = user => { user.copy(primaryParty = None, annotations = user.annotations.updated("description", "This is a new description").removed("foo").updated("baz", "bar")) })
    updatedUser : User = User(
      id = "myuser",
      primaryParty = None,
      isActive = true,
      annotations = Map("baz" -> "bar", "description" -> "This is a new description")
    )
    
    

Inspect
^^^^^^^

You can fetch the current state of the user as follows:

.. code-block:: none

    @ participant1.ledger_api.users.get(user.id)
    res4: User = User(
      id = "myuser",
      primaryParty = None,
      isActive = true,
      annotations = Map("baz" -> "bar", "description" -> "This is a new description")
    )


You can query what rights a user has:

.. code-block:: none

    @ participant1.ledger_api.users.rights.list(user.id)
    res5: UserRights = UserRights(
      actAs = Set("alice::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"),
      readAs = Set("bob::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"),
      participantAdmin = false,
      identityProviderAdmin = false
    )

You can grant more rights.
The returned value contains only newly granted rights; it does not contain rights the user already had even if you attempted to grant them again (like the read-as ``alice`` right in this example):

.. code-block:: none

    @ participant1.ledger_api.users.rights.grant(id = user.id, actAs = Set(alice.toLf, bob.toLf), readAs = Set(eve.toLf), participantAdmin = true)
    res6: UserRights = UserRights(
      actAs = Set("bob::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"),
      readAs = Set("eve::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"),
      participantAdmin = true,
      identityProviderAdmin = false
    )

You can revoke rights from the user.
Again, the returned value contains only rights that were actually removed:

.. code-block:: none

    @ participant1.ledger_api.users.rights.revoke(id = user.id, actAs = Set(bob.toLf), readAs = Set(alice.toLf), participantAdmin = true)
    res7: UserRights = UserRights(
      actAs = Set("bob::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"),
      readAs = Set(),
      participantAdmin = true,
      identityProviderAdmin = false
    )

Now that you have granted and revoked some rights, you can fetch all of the user's rights again and see what they are:

.. code-block:: none

    @ participant1.ledger_api.users.rights.list(user.id)
    res8: UserRights = UserRights(
      actAs = Set("alice::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"),
      readAs = Set(
        "bob::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3",
        "eve::1220a40b326dd3864088599706ef56333f9f0306608567a3d1e445e0a65ef0399ff3"
      ),
      participantAdmin = false,
      identityProviderAdmin = false
    )

Also, multiple users can be fetched at the same time.
In order to do that, first create another user called ``myotheruser`` and then list all the users whose user name starts with ``my``:

.. code-block:: none

    @ participant1.ledger_api.users.create(id = "myotheruser")
    res9: User = User(id = "myotheruser", primaryParty = None, isActive = true, annotations = Map())
.. code-block:: none

    @ participant1.ledger_api.users.list(filterUser = "my")
    res10: UsersPage = UsersPage(
      users = Vector(
        User(id = "myotheruser", primaryParty = None, isActive = true, annotations = Map()),
        User(
          id = "myuser",
          primaryParty = None,
          isActive = true,
          annotations = Map("baz" -> "bar", "description" -> "This is a new description")
        )
      ),
      nextPageToken = ""
    )


Decommission
^^^^^^^^^^^^^^

You can delete a user by its id:

.. code-block:: none

    @ participant1.ledger_api.users.delete("myotheruser")
    

You can confirm it has been removed by e.g. listing it:

.. code-block:: none

    @ participant1.ledger_api.users.list("myotheruser")
    res12: UsersPage = UsersPage(users = Vector(), nextPageToken = "")

If you want to prevent a user from accessing the ledger API it may be better to deactivate it rather than deleting it. A deleted user can be recreated as if it never existed in the first place, while a deactivated user must be explicitly reactivated to be able to access the ledger API again.

.. code-block:: none

    @ participant1.ledger_api.users.update("myuser", user => user.copy(isActive = false))
    res13: User = User(
      id = "myuser",
      primaryParty = None,
      isActive = false,
      annotations = Map("baz" -> "bar", "description" -> "This is a new description")
    )

.. _canton-add-party-to-a-participant:

Adding a new Party to a Participant
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The simplest operation is adding a new party to a participant. For this, we add it normally at the topology manager
of the participant, which in the default case is part of the participant node. There is a simple macro to enable the
party on a given participant if the participant is running their own topology manager:

.. code-block:: scala

          val name = "Gottlieb"
          participant1.parties.enable(name)


This will create a new party in the namespace of the participants topology manager.

And there is the corresponding disable macro:

.. code-block:: scala

          participant1.parties.disable(name)


The macros themselves just use ``topology.party_to_participant_mappings.authorize`` to create the new party, but add some convenience such
as automatically determining the parameters for the ``authorize`` call.

.. note::
    Please note that the ``participant.parties.enable`` macro will add the parties to the same namespace as the participant is in.
    It only works if the participant has authority over that namespace either by possessing the root or a delegated key.

.. enterprise-only::

.. _offline-party-migration:

Migrate Party to Another Participant Node
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Parties are only weakly tied to participant nodes. They can be allocated in their own namespace and then
be delegated to a given participant. For simplicity and convenience, the participant creates new parties
in their own namespace by default.

The weak coupling of parties to participants allows you to migrate parties together with their active contract set from
one participant node to another. Note, the process below works only for parties that are hosted on a single node.
Also, if the party is not fully controlled by the source participant node, you need to prepare the topology state
change appropriately, disabling the party on the source node and delegating the party to the target node.

Starting with a party Alice being allocated on participant1:

    
.. code-block:: none

    @ val alice = participant1.parties.enable("Alice")
    alice : PartyId = Alice::122092a796fa...
    

To migrate Alice to participant2, we follow a four-step process. First, we need
to obtain the target participant id. In this example, we read it from the participant id:

.. code-block:: none

    @ val targetParticipantId = participant2.id
    targetParticipantId : ParticipantId = PAR::participant2::122008ff13b6...

Next, we deactivate the party on the origin participant and store the party's active contract set in a file by
using the repair macros which are part of the enterprise edition:

.. code-block:: none

    @ repair.party_migration.step1_hold_and_store_acs(alice, participant1, targetParticipantId, "alice.acs.gz")
    res3: Map[DomainId, Long] = Map()
    

The last argument is the name of a file which the active contract set is stored as base64 encoded strings,
ordered by domain-id and contract-id. This file then needs to be transferred offline to the target
participant. Additionally, the repair macro will disable the party on the first participant.
This is important in order to avoid breaking the consistency of the exported active contract set.

The target participant must then be disconnected from the domain before it can import data:

.. code-block:: none

    @ participant2.domains.disconnect("mydomain")
    

Once the domain is disconnected, invoke the import command:

.. code-block:: none

    @ repair.party_migration.step2_import_acs(participant2, "alice.acs.gz")
    

When importing is finished, reconnect to the domain using:

.. code-block:: none

    @ participant2.domains.reconnect("mydomain")
    res6: Boolean = true
    

The last step on the target participant enables the party:

.. code-block:: none

    @ repair.party_migration.step3_enable_on_target(alice, participant2)
    
    

Finally, purge the active contract set on the origin participant:

.. code-block:: none

    @ participant1.domains.disconnect("mydomain")
    
.. code-block:: none

    @ repair.party_migration.step4_clean_up_source(alice, participant1, "alice.acs.gz")
    
    
    

The above commands require interactive access to the participants and are supported as an alpha implementation. They
work for parties that were allocated using standard methods on a single participant node.
Otherwise, a few more manual steps are required to properly prepare the topology state before exporting and
importing the topology state.

.. _canton-party-on-two-nodes:

Party on Two Nodes
~~~~~~~~~~~~~~~~~~

Note: this is an alpha feature only and is not supported in production.

Assuming we have party ``("Alice", N1)`` which we want to host on two participants: ``("participant1", N1)`` and
``("participant2", N2)``. In this case, we have the party "Alice" in namespace ``N1``, whereas the participant2 is in
namespace ``N2``. In order to set this up, we need to appropriately authorize the participants to act on behalf of the
party and we need to correctly copy the active contract set.

Starting with a party being allocated on participant1:

    
.. code-block:: none

    @ val alice = participant1.parties.enable("Alice")
    alice : PartyId = Alice::122083ba3cd3...
    
    

To add this party to participant2, participant2 must first agree to host the party. This
is done by authorizing the ``RequestSide.To`` of the party to participant mapping on the target participant:

.. code-block:: none

    @ participant2.topology.party_to_participant_mappings.authorize(TopologyChangeOp.Add, alice, participant2.id, RequestSide.To, ParticipantPermission.Submission)
    res2: com.google.protobuf.ByteString = <ByteString@18b7d2ca size=556 contents="\n\251\004\n\327\001\n\322\001\n\317\001\022 uCDexF6g8WxzWkbnpyua98b77NKEUEL22...">
    
    

You can restrict the permission of the node by setting the appropriate ``ParticipantPermission`` in the
authorization call to either ``Observation`` or ``Confirmation`` instead of the default ``Submission``. This allows
setups where a party is hosted with ``Submission`` permissions on one node and ``Confirmation`` on another to increase the
liveness of the system.

.. note::

    The distinction between ``Submission`` and ``Confirmation`` is only enforced in the participant node.
    A malicious participant node with ``Confirmation`` permission for a certain party can submit transactions in the name of
    the party. This is due to Canton's high level of privacy where validators do not know the identity of the
    submitting participant. Therefore, a party who delegates ``Confirmation`` permissions to a participant
    should trust the participant sufficiently.

Before we continue, we need to ensure that the target participant is now disconnected from the affected domains, in order to
avoid the target participant receiving transactions for the new party prior to the complete transfer of the
active contract store. Therefore, we disconnect the participant from all domains:

.. code-block:: none

    @ participant2.domains.disconnect_all()
    

This is currently the reason why this feature is only supported as alpha: we can not guarantee that a user does not
damage their system by accident due to forgetting to disconnect from the domain.

Next, add the ``RequestSide.From`` transaction such that the party is activated on the target participant:

.. code-block:: none

    @ participant1.topology.party_to_participant_mappings.authorize(TopologyChangeOp.Add, alice, participant2.id, RequestSide.From, ParticipantPermission.Submission)
    res4: com.google.protobuf.ByteString = <ByteString@618c846f size=556 contents="\n\251\004\n\327\001\n\322\001\n\317\001\022 GKSJFugL9uXPWOK0tgydrdZPonjlF58O2...">

Check that the party is now hosted by two participants:

.. code-block:: none

    @ participant1.parties.list("Alice")
    res5: Seq[ListPartiesResult] = Vector(
      ListPartiesResult(
        party = Alice::122083ba3cd3...,
        participants = Vector(
          ParticipantDomains(
            participant = PAR::participant1::122083ba3cd3...,
            domains = Vector(
              DomainPermission(domain = mydomain::12202cb513a4..., permission = Submission)
            )
          ),
          ParticipantDomains(
            participant = PAR::participant2::122009a4c288...,
            domains = Vector(
              DomainPermission(domain = mydomain::12202cb513a4..., permission = Submission)
            )
          )
        )
      )
    )
    

In the next step, you store the active contract set of the party into a file. If there is no traffic on the participant
node and you can be sure that nothing has changed for the party, you can just straight use the ``repair.download``
command. Otherwise, you must find the timestamp when the party was activated. One way to find that timestamp is by
looking at the topology store of that particular domain connection:

.. code-block:: none

    @ val timestamp = participant1.topology.party_to_participant_mappings.list(filterStore="mydomain", filterParty="Alice").map(_.context.validFrom).max
    timestamp : Instant = 2023-01-03T23:27:35.948285Z

Take the ``max`` of the two timestamps which corresponds to the ``RequestSide.From`` topology transaction that you
added above. Use this timestamp now to export the state using:

.. code-block:: none

    @ participant1.repair.download(Set(alice), "alice.acs.gz", filterDomainId="mydomain", timestamp = Some(timestamp))
    res7: Map[DomainId, Long] = Map(mydomain::12202cb513a4... -> 1L)

Note that you need to do this for every domain separately with the correct timestamp of the activation of the party.
In our example, there is only one domain.

Subsequently, the active contract set is imported on the target participant:

.. code-block:: none

    @ repair.party_migration.step2_import_acs(participant2, "alice.acs.gz")
    

Once the entire active contract store has been imported, the target participant can reconnect to the domain:

.. code-block:: none

    @ participant2.domains.reconnect_all()
    
    

Now, both participant host the party and can act on behalf of it.

    

Manually Initializing a Node
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
There are situations where a node should not be automatically initialized, but where we prefer to control
each step of the initialization. For example, when a node in the setup does
not control its own identity, or when we do not want to store the identity key on the node for security
reasons.

In the following, we demonstrate the basic steps how to initialise a node:

.. _manually-init-domain:

Domain Initialization
^^^^^^^^^^^^^^^^^^^^^
The following steps describe how to manually initialize a domain node:

.. code-block:: scala

    
            // first, let's create a signing key that is going to control our identity
            val identityKey = mydomain.keys.secret.generate_signing_key(name = "default")
    
            // use the fingerprint of this key for our identity
            val namespace = identityKey.fingerprint
    
            // initialise the identity of this domain
            val uid = mydomain.topology.init_id(identifier = "mydomain", fingerprint = namespace)
    
            // create the root certificate for this namespace
            mydomain.topology.namespace_delegations.authorize(
              ops = TopologyChangeOp.Add,
              namespace = namespace,
              authorizedKey = namespace,
              isRootDelegation = true,
            )
    
            // set the initial dynamic domain parameters for the domain
            mydomain.topology.domain_parameters_changes
              .authorize(
                domainId = DomainId(uid),
                newParameters =
                  ConsoleDynamicDomainParameters.defaultValues(protocolVersion = testedProtocolVersion),
                protocolVersion = testedProtocolVersion,
              )
    
            val mediatorId = MediatorId(uid)
            Seq[KeyOwner](DomainTopologyManagerId(uid), SequencerId(uid), mediatorId).foreach {
              keyOwner =>
                // in this case, we are using an embedded domain. therefore, we initialise all domain
                // entities at once. in a distributed setup, the process needs to be invoked on
                // the separate entities, and therefore requires a bit more coordination.
                // however, the steps remain the same.
    
                // first, create a signing key for this entity
                val signingKey = mydomain.keys.secret.generate_signing_key(
                  name = keyOwner.code.threeLetterId.unwrap + "-signing-key"
                )
    
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
    


.. _manually-init-participant:

Participant Initialization
^^^^^^^^^^^^^^^^^^^^^^^^^^
The following steps describe how to manually initialize a participant node:

.. code-block:: scala

    
            // first, let's create a signing key that is going to control our identity
            val identityKey =
              participant1.keys.secret.generate_signing_key(name = "my-identity")
            // use the fingerprint of this key for our identity
            val namespace = identityKey.fingerprint
    
            // create the root certificate (self-signed)
            participant1.topology.namespace_delegations.authorize(
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
            participant1.topology.init_id(identifier = "manualInit", fingerprint = namespace)
    
            // create signing and encryption keys
            val enc = participant1.keys.secret.generate_encryption_key()
            val sig = participant1.keys.secret.generate_signing_key()
    
            // assign new keys to this participant
            Seq(enc, sig).foreach { key =>
              participant1.topology.owner_to_key_mappings.authorize(
                ops = TopologyChangeOp.Add,
                keyOwner = participant1.id,
                key = key.fingerprint,
                purpose = key.purpose,
              )
            }
    



