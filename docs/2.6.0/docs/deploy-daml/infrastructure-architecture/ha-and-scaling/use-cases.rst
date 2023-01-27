.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Use Cases
#########

The following use cases are organized by persona. Out-of-band use cases, useful for deployments, are also included. 
Distributed Application Provider
The distributed application provider is also the domain owner and the domain administrator. Their deployment activities come first since all other activities require a domain.
Deploy a domain
The distributed application provider deploys the following components: 

The domain manager. 
Mediator. 
Sequencer. 
The HA configured PostgreSQL managed service that is the sequencer’s backend. 

!!!! NOTE: 
The domain manager, mediator, and sequencer all have internal databases that are not shown here and should also be HA configured. 
Also not shown, a bastion host (e.g. Azure bastion host) can be configured for accessing the domain components. This provides an additional layer of security by limiting the means of access to the domain. Additional Production Access Controls may be needed.



The Virtual Network Gateway is shown because the distributed application provider may choose to isolate the domain from their participant node as a security measure. If this additional isolation is not required then the Virtual Network Gateway is not needed either. A different type of networking component may be more appropriate here – consider it a placeholder for a cloud implementation, HAProxy, NGINX, etc. 

The figure below shows the participant node and its ledger client.



As mentioned, the distributed domain owner can add additional components which interact with the participant node. They will likely want to deploy these components shortly after deploying the participant node. 

Connecting a new participant node 

We expect the domain to run in permissioned mode with allow-listing enabled so that only participant nodes whose identities have been registered with the domain manager.  This involves a data exchange between the distributed application provider and the distributed application user. 

The distributed application provider communicates specific information to a new distributed application user so that the user’s participant node can join the application’s domain. This out of band exchange is described in the figure below where Bob is the application provider and Alice is the new application user. 

The sequence of steps is as follows:

Alice deploys a participant node.
Alice extracts the participant node’s unique identifier into a string. The id includes the display name for the participant plus a hash of the public identity signing key.
Alice makes her participant ID known to Bob through an out of band mechanism, such as email for example.
Bob runs a console command which adds Alice’s participant ID to the domain allowlist and configures the appropriate node’s permissions. An example command which gives default permissions is shown below:

domainManager1.participants.set_state(participantIdFromString, ParticipantPermission.Submission, TrustLevel.Ordinary)

Bob passes Alice the following information which allows her to connect to the domain:

One, or more, sequencer endpoints - https url.
Certificate root public cert, if it’s not a publicly signed CA.

Alice picks a unique name for the Domain that is local to her participant.  This will be used in the connection command.
Alice enters the information into the connection command connect_multi and connects to Bob’s domain.
participantAlise.domains.connect_multi("AliceDomainName", Seq(sequencer1, sequencer2))

Prepare domain infrastructure for adding new participant nodes

A distributed application provider expands the use of their application by allowing more participant nodes to join their domain. A sequencer node is the gateway to the domain for all participant nodes so an important policy to define is when to add a new sequencer. 

As shown below, a domain may start with a sequencer node and then add more sequencer nodes as required. 

There are two options for adding a new participant node. 

Deploy a sequencer node for each participant node to introduce more isolation between the events each participant sees.  For example, Coke may want to avoid any cross-contamination of events with Pepsi, and vice-versa, so they want their own sequencers.  The Coke sequencer will see all the Coke and Pepsi messages through the shared database (essentially the sequencer backend is a broadcast) but Coke’s sequencer node provides a multicast to Coke’s participant node with only Coke’s events.  Similar for Pepsi and Pepsi’s events.  
Avoid the additional isolation and focus on high resource utilization of the sequencer by having several participant nodes use the same sequencer; i.e. a single sequencer handles multiple distributed application users. This option produces a lighter load on the joint HA PostgreSQL database.


Distributed Application User

The distributed application user deploys their own participant node and connects to the public sequencer endpoint of the distributed application provider. There is similarity here with the distributed application provider, which is no surprise given the underlying distributed ledger technology. However, the distributed application user’s DAR files (i.e. business logic) may be a subset of what is deployed by the distributed application provider.

This simple situation can be extended.  For example, the distributed application user may be interested in several distributed applications and connect their participant node to the related domains.  They would also deploy multiple DARs for the different applications’ business logic.  They may also write their own extensions that include additional DARs.  These extensions do not impact the use cases described here.



The simple configuration shown above, like the domain owner, can expand into a more capable deployment such as shown below by adding the HTTP JSON API server, trigger services, and OAuth2 middleware. 

Upload the distributed application DAR files

This is documented in https://docs.daml.com/deploy/generic_ledger.html


Site Reliability Engineer (SRE)
Monitoring is the primary use case for the SRE which is required on both the domain and participant nodes, although the scope is slightly different. 

Monitoring normally consists in the following:

Export logs.
Expose metrics via Prometheus endpoint. 
Parse out trace IDs from the log files.
Keep logs for audit.

This is covered in the public monitoring documentation.

