.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

NOTE: 
This is background material.  If you have experience, please skip this chapter.

From: https://docs.google.com/document/d/1FILaPsWD11yeYTK5v3yDPas58rLKRLzW_KL6np1Q8gM/edit#heading=h.1kgkozh4pzqh
!!! NOTE: there are some equations in this section pasted in as pics.
!!! NOTE: there is also a table posted in as a pic.

Business Goals
##############

From Wikipedia, “High availability (HA) is a characteristic of a system which aims to ensure an agreed level of operational performance, usually uptime, for a higher than normal period.”
Wikipedia continues, “There are three principles of systems design in reliability engineering which can help achieve high availability.
Elimination of single points of failure. This means adding or building redundancy into the system so that failure of a component does not mean failure of the entire system.
Reliable crossover. In redundant systems, the crossover point itself tends to become a single point of failure. Reliable systems must provide for reliable crossover.
Detection of failures as they occur. If the two principles above are observed, then a user may never see a failure – but the maintenance activity must.”


The Daml solution design honors these principles by:


Eliminating single points of failure through redundant components.
Executing reliable crossover through networking best practices in conjunction with the Canton transaction consensus protocol to eliminate partially processed requests. 
Ensuring automated failover when a single failure is detected. 


The focus of this document is the technical aspects of an HA deployment. However, the rest of this section examines how business goals drive the configuration and operational aspects of the HA deployment. Check the following sources for more information:
Multi-Region fundamental 1: Understanding the requirements.
Availability Table.
Embracing Risk.
What is an error budget—and why does it matter?
Available . . . or not? That is the question—CRE life lessons.
Defining Availability
Availability defines whether a system is able to fulfill its intended function over a period of time. It is usually defined as a certain number of 9’s to be met, such as 99.5% or 99.999%, which is the probability that the system will work as intended. The inverse of that is the percentage of time it is expected to fail, such as 0.5% or 0.001%. There are two ways that availability is specified: time based-and aggregate request availability. 
Time-based availability
The most frequent availability metric is the percentage of uptime of the system - not the components. A refinement of this is to only apply this to unplanned downtime: to the amount of time that the system is unexpectedly unavailable since well published maintenance activities will not have a business impact but unplanned downtime does have a business impact (e.g., lost revenue, reputational harm, customers using a competitor, etc.). 

The general formula is:

Some simple algebra for this simple math formula allows a calculation of how many minutes of downtime are allowed for a given period. For example, using this formula over the period of a year, we can calculate the acceptable number of minutes of downtime to reach a given number of nines of availability. For example, a system with an availability target of 99.99% can be down for up to 52.56 minutes in an entire year and stay within its availability target. The table below provides the estimated downtime for a given period. For a custom time period, use the formula from Availability Calculator.


The table helps to define an error budget which is “An error budget is the maximum amount of time that a technical system can fail without contractual consequences.” For example, a 30 day (43,200 minutes) window of time and an availability target of 99.9% (three nines), simple arithmetic shows that the system must not be down for more than 43.2 minutes over the 30 days. This 43.2 minute figure is a very concrete target to plan around, and is often referred to as the error budget. If you exceed 43.2 minutes of downtime over 30 days, you'll not meet your availability goal. An error budget becomes a KPI for the SREs.
Aggregate request availability
Rather than consider the time that a system is fully available, a finer grained metric considers the number of failed requests. An aggregate request unavailability metric (i.e., "X% of all requests failed") is more useful than focusing on outage lengths for services that may be partially available, for services whose load varies over the course of a day or week rather than remaining constant, or to monitor specific, business critical endpoints. The formula is:.

Although not all requests have equal business value, this metric is often calculated over all requests made to the system. For example, a system that serves 2.5M requests in a day with a daily availability target of 99.99% can serve up to 250 errors and still hit its target for that given day.

It should be noted that if a request is retried and succeeds then it is not considered a failed request since the end-user does not see a failure. 
The Related Metrics of RTO and RPO

Related metrics that are frequently cited are RTO and RPO:
Recovery Time Objective (RTO) — RTO is the maximum acceptable delay between the interruption of service and restoration of service. This value determines an acceptable duration for which the service is impaired. This is a slice of the error budget but for a single instance of downtime.
Recovery Point Objective (RPO) — RPO is the maximum acceptable amount of time since the last data recovery point. This determines what is considered an acceptable data loss between the latest recovery point and a service interruption. 
Financial systems often need to support an RPO of zero. Once a customer commits a request and receives a response that it succeeded, they expect that request to fully succeed. If a request receives an error response then the user does not expect it to succeed and will need to retry themselves.

As discussed here, resiliency is a related property to availability. “Resiliency is the capability to handle partial failures while continuing to execute and not crash. In modern application architectures — whether it be microservices running in containers on-premises or applications running in the cloud — failures are going to occur. For example, applications that communicate over networks (like services talking to a database or an API) are subject to transient failures. These temporary faults cause lesser amounts of downtime due to timeouts, overloaded resources, networking hiccups, and other problems that come and go and are hard to reproduce. These failures are usually self-correcting.”

Resiliency and availability are enhanced by the client application leveraging best practice patterns, such as the retry pattern. “Retries can be an effective way to handle transient failures that occur with cross-component communication in a system.” A retry pattern is often coupled with the circuit breaker pattern that effectively shuts down all retries on an operation after a set number of retries have failed. This allows the system to recover from failed retries after hitting a known limit and gives it a chance to react in another way, like falling back to a cached value or returning a message to the user to try again later.”

The key takeaway is that the Daml solution’s client application needs to add this type of resiliency to increase availability of the overall system consisting of platform and application.
High Availability Cost Trade-Offs
High availability can be costly so trade-offs are required. For illustration, if the goal is to remain running in all cases then extremely rare events, such as an asteroid strike that simultaneously wipes out all data centers in a continent, need to be taken into account. Some of these extreme events are highly improbable and may not need to be considered. This highlights that there is a trade-off between avoidance cost of an outage, the probability of a single failure (single component redundancy), and the probability of multiple simultaneous failures (multiple component, integrated redundancy). How can these trade-offs be analyzed?

Using unplanned downtime this can be calculated as: 
Error budget x Revenue lost per minute of downtime 
where the revenue lost per minute of downtime is a projected or measured statistic. Then the cost of loss of availability is easily derived. The formula can also be turned around to determine what availability is needed to attain a revenue target. Lastly, this formula can compare the cost to achieve higher availability, with associated increased revenue, with the increased investment cost. In this manner, the business goals drive the trade-offs for high availability. 
