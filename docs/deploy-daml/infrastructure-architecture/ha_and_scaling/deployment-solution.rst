.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

From: https://docs.google.com/document/d/1FILaPsWD11yeYTK5v3yDPas58rLKRLzW_KL6np1Q8gM/edit#heading=h.nfdb974gwzpw
!!! NOTE: pics in this section from here: https://lucid.app/lucidchart/d3a7916c-acaa-419d-b7ef-9fcaaa040447/edit?invitationId=inv_b7a43920-f4af-4da9-88fc-5985f8083c95&page=0_0#



Deployment Solution
###################

https://docs.daml.com/canton/architecture/ha/domain.html -> in this section, subsection Domain, edited.
https://docs.daml.com/canton/architecture/ha/participant.html -> in this section, subsection Participant Node, edited.


The figure below demonstrates the simplest, multi-party deployment possible. It is a logical view where each box has multiple internal components in a HA production configuration. The section High Availability and Horizontal Scaling will expand each of these logical boxes to show how they are configured for production.  Please note that the term ‘node’ may refer to a logical box with multiple components or as a single JVM process with the context determining how to interpret node.

An overview of these components is:
Ledger client: The client that uses the ledger API which is the client entry point to execute business logic. 
Participant: Exposes the public ledger API. It will execute the Daml business logic of the distributed application based on an API request or as part of the Canton transaction consensus protocol.
Mediator: Acts as a transaction manager for the Canton consensus protocol. Ensures either all of the parts of a transaction succeed or there is no change.
Domain manager: Used to manage the domain using topology transactions to update the topology or to make public keys available.
Sequencer: Exposes the Canton API so that all clients see events as totally ordered using a guaranteed, multicast communication mechanism. It has a backend component that is hidden from its clients. Depending on the backend component, either a SQL domain or blockchain domain is supported.
The reader is referred to the public documentation for more information.


The distributed application provider deploys several components: the domain (domain manager, mediator, and sequencer) and their own participant node(s). 

The distributed application user only has to deploy a participant node and connect that node (from their own private network) to the private network of the domain via communication with a sequencer.

A typical Daml deployment has additional components which are shown in the figure below:

A HTTP JSON API server which supplements the gRPC API endpoints of the participant node by providing an HTTP REST (HTTP JSON API) endpoint. It also has an internal cache so that it can be more responsive to queries.
A Trigger service that listens to the ledger event stream and triggers business logic based on ledger events.
OAuth2 middleware that supports refresh of the Trigger services JWT token. This component manages the background requests for a (re)fresh token for the Trigger services.
The Identity Provider (IDP) is the authentication entity that provides the JWT token and is mentioned here for completeness. The IDP is outside of the Daml solution but nevertheless a necessary component. Different organizations may use different IDPs for their participant nodes.

We expect the domain owner to have additional business logic in both their participant node and trigger service nodes that manages the distributed application. 



