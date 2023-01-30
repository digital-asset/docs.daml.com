.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Implementing HA
###############

This section walks through each logical component that was displayed in the prior use cases and illustrates its highly available deployment. 

For clarity the diagrams following these conventions:
Individual instances or processes or containers are in solid black boxes. 
Where needed, databases are identified as shared and highly available by adding the “HA” in the disk figure.
Distinguishing between a single instance and the HA variant is done by using the term ‘service’ to designate the HA variant. There is also a blue dashed line around the components that make up that HA service.  The word ‘service’ is chosen because it looks like a single endpoint which is highly available, like a managed service in the cloud.
For simplicity, a blue dashed box with a name is shorthand for the HA variant of that component. 
Health signals are a dashed red line that point to the instance that is a recipient of that signal.
Communication channels that are passive but become active upon failover are shown in a dashed green line.
So, in the figure below, the Middle service blue box encompasses all the components that make up that service.   Middle instances are the black box with the solid line.   The blue box “Another” is short form for a service called “Another.”   There is a load balancer that is between the Middle and Bottom services.

Each component of the Daml solution can scale out in a horizontal manner, using a stateless or  stateful horizontal scaling pattern. For example, the Bottom service has instances that are independent and considered stateless, so stateless horizontal scaling is achieved by adding another Bottom instance.  Adding that Bottom instance also increases the availability because there are more redundant instances. The Middle service is stateful since they are not independent with a shared local database between the two Middle instances and the HA model is active-passive.  So, a different pattern is used to scale the stateful Middle service which is to replicate the entire Middle service:  add two Middle instances connected by a Middle Posgres HA database.   

As a production system becomes busier, it is necessary to scale up the components. Vertical scaling is the easiest way to handle more load but there are limits to the benefits of vertical scaling. Vertical scaling is not discussed since this is a well known technique. Instead, the focus here is on horizontal scaling where backup/redundant components are deployed to different availability zones as part of the HA configuration.


HTTP JSON API and Participant Node Services
The HTTP JSON API and participant services need to be considered together since there are some state dependencies between the two. In particular, users and related parties are configured on a participant node so they will be handled by a particular participant service. This means that the HTTP JSON API service that is connected to a participant service will also serve those same users and parties. 

The description above is true if there is only a single participant service (and corresponding HTTP JSON API service) that all the client requests will go to that service.  However, if there is more than one participant service (e.g., horizontal scaling) then it is the application’s responsibility to understand which participant service to send a request to (and the corresponding HTTP JSON API service), based on the user(s) or parties of the request.  Another way to describe this is that users and parties are sharded across the participant and HTTP JSON API services; the application is responsible for targeting the right instance.

As shown below, a HTTP JSON API service is an endpoint that has four components. Each HTTP JSON API instance emits a health signal that the load balancer uses to direct traffic. The HTTP JSON API’s database acts as a cache that is local to the instance so it does not need to be HA since the cache can be reconstructed at any time. 



CALLOUT!! NOTE: The HTTP JSON API server does not support mTLS from client applications at this time.  This can be handled by the proxy load balancer in front of it which may be simpler.


The participant service and the HTTP JSON API service have some differences. A single participant service can have several HTTP JSON API servers fronting it. However, a HTTP JSON API server should not be connected to multiple participant services but only a single participant service. Also, the HTTP JSON API component operates in an active-active mode while participant nodes operate in an active-passive mode.  mTLS is supported between the load balancer and participant node.


The HTTP JSON API server and participant node have a state dependency (called the offset) so they must be deployed together.  Also, command deduplication doesn't work across participant services.   There are also the shared users and parties for both. This deployment is shown below. 


Horizontal scaling is accomplished by sharding application users and parties across a joint HTTP JSON API and participant service, and adding another HTTP JSON API and participant stack, as shown below.


Sequencer Service
The sequencer service operates in active-active mode which means that all sequencer instances can accept and process Canton protocol API requests. This has benefits for both scaling and availability. 

Deploying a sequencer depends on business requirements which may impact deployment configurations such as load balancing configurations and whether the domain is fully or only partially decentralized.

Sequencer service load balancing options

The sequencer service has several clients: participant, mediator, and domain manager. mTLS between its clients (e.g.,  participant) is currently unavailable. The two available load balancing options are shown in the diagram below. 

The first option, shown on the left, fronts the sequencer service with a load balancer that all sequencer clients use. This option simplifies configuration and connectivity but adds the complexity of configuring the load balancer. 



The other option, shown on the right, is where a gRPC java client library provides a round-robin selection mechanism for load balancing that, provided there are multiple sequencer connections, automatically round-robins through them and includes the ones that are healthy. This setup requires the distributed application provider and distributed application users to maintain the configuration information of all the available sequencers in the sequencer client.  The sequencer client continuously monitors the health of each sequencer endpoint when selecting a possible node in round-robin fashion. See the documentation here and here for more information.

The SQL domain and blockchain domain differences related to the sequencer are discussed next. This will also be used to highlight the differences between the ‘single endpoint’ Vs ‘client side’ load balancing options.

Blockchain domains

A blockchain domain has a fully decentralized data path and is used when there is no trust between the distributed application providers and users.  Whereas the sequencer queried the postgreSQL backend directly in a SQL domain, this cannot be done in a blockchain domain.  Instead, a local database to the sequencer is added to speed up queries, etc.  Then the blockchain is used by the sequencer backend to provide a guaranteed ordered multicast of events.

The figure below shows a HyperLedger Fabric blockchain example of this. Notice that each sequencer has an independent local cache running on a PostgreSQL database. This local cache ensures efficiency because the sequencer avoids having to scan the entire blockchain when it starts up or reconnects after a temporary interruption. It also reduces the performance load on the blockchain.

This figure also has a load balancer fronting the sequencer nodes but client side load balancing would also work. There are several benefits to using a load balancer:

Clients have a single endpoint that consolidates the health signals, thus simplifying setup and troubleshooting.
Adding a sequencer does not require updating the configuration information in each client.
Additional security.

Since sequencer nodes are always active, horizontal scaling for a blockchain sequencer service is achieved by adding a new sequencer along with its associated local cache database and enabling it for client use.




SQL domains

The SQL domain is only partially decentralized and is used when the sequencer’s backend data is stored in a single postgreSQL database that is managed by a centralized distributed application provider. This means that a SQL domain requires participant users to have some trust in the application provider.

A sequencer needs no local cache because it directly queries the backend database with no performance penalty. 

Since sequencer nodes are always active, horizontal scaling for the SQL domain sequencer service is achieved by adding a new sequencer and enabling the clients to use it.
Mediator Service
The mediator service has no client-facing ingest. It also has no load balancing proxy or health endpoints. Instead, it uses client side load balancing based on the gRPC infrastructure. It is like the participant node in that it has a PostgreSQLdatabase in a HA configuration. The mediator components, however, act in an active-passive configuration. 

Horizontal scaling is achieved by adding another mediator service.


Domain Manager Service
The domain manager service also has no client-facing ingest point. Like the mediator services, the domain manager is in an active-passive configuration. There is, however, only a single domain manager service per domain. This means that there is no horizontal load balancing model for the domain manager. This is feasible because the domain manager is not in the transaction processing path path and so it manages topology transactions which are orders of magnitude less frequent than the Daml transactions that the mediators manage. 

For HA support the domain manager uses PostgreSQL in a HA configuration. HA support for the domain manager was added in v2.5.0.


Trigger Service
The trigger service includes the OAuth 2.0 middleware and trigger service nodes. As shown below, it does not operate in an HA configuration that supports a single failure. Instead, it requires a monitoring system to detect if the trigger service node or OAuth 2.0 middleware is unhealthy and mitigate any issues by: (1)  restarting the failed item or (2) stopping the unhealthy instance and then starting another instance. A shared PostgreSQL database is needed for the trigger service node. As shown the OAuth 2.0 middleware connects to an OAuth provider.



Horizontal scaling is achieved by deploying additional trigger service nodes. For example, in the figure below, there are two pairs of trigger service nodes (the pink trigger service nodes and the green trigger service nodes) which use the same OAuth 2.0 middleware node that is connected to a single OAuth provider. It must be emphasized that running the same trigger rule on multiple live trigger service instances is not allowed. For example the pink rules are running in a single live trigger service node, just like the green rules are running in a single live trigger service node. Please remember that the box with the dashed lines indicate that the node is started when the active node is identified as unhealthy.


Each trigger service node is limited to a single OAuth provider; it is unable to support queries against multiple OAuth providers. For example, the pink trigger and green trigger service in the figure above can not query against both a Google OAuth provider and an Apple OAuth provider - each trigger service would need to be configured to use exactly one of these providers. 

If access to more than a single OAuth provider is needed, then different pairs of trigger service nodes and OAuth 2.0 middleware server are configured. This is shown below. Please note running the same trigger rule on multiple live trigger service instances is not allowed in this configuration either..

