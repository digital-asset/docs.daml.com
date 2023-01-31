.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Understanding HA from a Business Perspective
############################################

.. NOTE::
    This section contains information for those unfamiliar with HA and how it is fundamental to operational efficiency. We look at how business goals drive the configuration and operational aspects of the HA deployment. 
    
    Those familiar with these principles may skip this page.

**Definition**
[#f1]_

    "High availability (HA) is a characteristic of a system which aims to ensure an agreed level of operational performance, usually `uptime <https://en.wikipedia.org/wiki/Uptime>`_, for a higher than normal period."

    ...

    "There are three principles of `systems design <https://en.wikipedia.org/wiki/Systems_design>`_ in `reliability engineering <https://en.wikipedia.org/wiki/Reliability_engineering>`_ which can help achieve high availability.

    1. Elimination of `single points of failure <https://en.wikipedia.org/wiki/Single_point_of_failure>`_. This means adding or building redundancy into the system so that failure of a component does not mean failure of the entire system.
    2. Reliable crossover. In `redundant systems <https://en.wikipedia.org/wiki/Redundancy_(engineering)>`_, the crossover point itself tends to become a single point of failure. Reliable systems must provide for reliable crossover.
    3. Detection of failures as they occur. If the two principles above are observed, then a user may never see a failure - but the maintenance activity must."
    
Daml solution design honors these principles by:

1. Eliminating single points of failure through redundant components.
2. Executing reliable crossover through networking best practices, in conjunction with the Canton transaction consensus protocol, to eliminate partially processed requests. 
3. Ensuring automated failover when a single failure is detected. 

**Useful Resources**

* `Multi-Region fundamental 1: Understanding the requirements <https://docs.aws.amazon.com/whitepapers/latest/aws-multi-region-fundamentals/multi-region-fundamental-1-understanding-the-requirements.html>`_.
* `Availability Table <https://sre.google/sre-book/availability-table/>`_.
* `Embracing Risk <https://sre.google/sre-book/embracing-risk/#risk-management_measuring-service-risk_aggregate-availability-equation>`_.
* `What is an error budget—and why does it matter? <https://www.atlassian.com/incident-management/kpis/error-budget#:~:text=An%20error%20budget%20is%20the,can%20fail%20without%20contractual%20consequences.>`_.
* `Available . . . or not? That is the question—CRE life lessons <https://cloud.google.com/blog/products/gcp/available-or-not-that-is-the-question-cre-life-lessons>`_.

Defining Availability
*********************

Availability defines whether a system is able to fulfill its intended function over a period of time, i.e. the system works as intended 99.5% or 99.999% of the time. 

The inverse is the percentage of time it is expected to fail, such as 0.5% or 0.001%. 

Time-based availability
=======================

The most frequent availability metric is the whole system uptime percentage - rather than the separate components. 

A refinement of this metric is *unplanned downtime*, i.e. the amount of time that the system is unexpectedly unavailable. This is because well-published maintenance activities have no business impact whereas unplanned downtime does; e.g. lost revenue, reputational harm, customers switching to a competitor, etc.

The general formula is: 

    :math:`availability = uptime / (uptime + downtime)`.

This formula calculates how many minutes of downtime are allowed in a given period. For example, a system with an availability target of 99.99% can be down for up to 52.56 minutes in an entire year and stay within its availability level. 

The table below provides the estimated downtime for a number of given availability levels. 

.. list-table:: Availablility calculator table
   :widths: 14 14 14 14 14 14 16
   :header-rows: 1

   - * Availability level
     * Downtime per year
     * Downtime per quarter
     * Downtime per month 
     * Downtime per week 
     * Downtime per day 
     * Downtime per hour
   - * 90%
     * 36.52 days
     * 9.13 days
     * 3.04 days
     * 16.80 hours
     * 2.40 hours
     * 6.00 minutes
   - * 95%
     * 18.26 days
     * 4.57 days
     * 1.52 days
     * 8.40 hours
     * 1.20 hours
     * 3.00 minutes
   - * 99%
     * 3.65 days
     * 21.91 hours
     * 7.30 hours
     * 1.68 hours
     * 14.40 minutes
     * 36.00 seconds
   - * 99.5%
     * 1.83 days
     * 10.96 hours
     * 3.65 hours
     * 50.40 minutes
     * 7.20 minutes
     * 18.00 seconds
   - * 99.9%
     * 8.77 hours
     * 2.19 hours
     * 43.83 minutes
     * 10.08 minutes
     * 1.44 minutes
     * 3.60 seconds
   - * 99.95%
     * 4.38 hours
     * 1.10 hours
     * 21.91 minutes
     * 5.04 minutes
     * 43.20 seconds
     * 1.80 seconds
   - * 99.99%
     * 52.59 minutes
     * 13.15 minutes
     * 4.38 minutes
     * 1.01 minutes
     * 8.64 seconds
     * 0.36 seconds
   - * 99.999%
     * 5.26 minutes
     * 1.31 minutes
     * 26.30 seconds
     * 6.05 seconds
     * 0.86 seconds
     * 0.04 seconds


    


For a custom availability percentage, use the `availability calculator <https://availability.sre.xyz/>`_.



The table helps to define an error budget which is “An error budget is the maximum amount of time that a technical system can fail without contractual consequences.” For example, a 30 day (43,200 minutes) window of time and an availability target of 99.9% (three nines), simple arithmetic shows that the system must not be down for more than 43.2 minutes over the 30 days. This 43.2 minute figure is a very concrete target to plan around, and is often referred to as the error budget. If you exceed 43.2 minutes of downtime over 30 days, you'll not meet your availability goal. An error budget becomes a KPI for the SREs.

Aggregate request availability
==============================

Rather than consider the time that a system is fully available, a finer grained metric considers the number of failed requests. An aggregate request unavailability metric (i.e., "X% of all requests failed") is more useful than focusing on outage lengths for services that may be partially available, for services whose load varies over the course of a day or week rather than remaining constant, or to monitor specific, business critical endpoints. The formula is:.

Although not all requests have equal business value, this metric is often calculated over all requests made to the system. For example, a system that serves 2.5M requests in a day with a daily availability target of 99.99% can serve up to 250 errors and still hit its target for that given day.

It should be noted that if a request is retried and succeeds then it is not considered a failed request since the end-user does not see a failure. 

The Related Metrics of RTO and RPO
**********************************

Related metrics that are frequently cited are RTO and RPO:
Recovery Time Objective (RTO) — RTO is the maximum acceptable delay between the interruption of service and restoration of service. This value determines an acceptable duration for which the service is impaired. This is a slice of the error budget but for a single instance of downtime.
Recovery Point Objective (RPO) — RPO is the maximum acceptable amount of time since the last data recovery point. This determines what is considered an acceptable data loss between the latest recovery point and a service interruption. 
Financial systems often need to support an RPO of zero. Once a customer commits a request and receives a response that it succeeded, they expect that request to fully succeed. If a request receives an error response then the user does not expect it to succeed and will need to retry themselves.

As discussed here, resiliency is a related property to availability. “Resiliency is the capability to handle partial failures while continuing to execute and not crash. In modern application architectures — whether it be microservices running in containers on-premises or applications running in the cloud — failures are going to occur. For example, applications that communicate over networks (like services talking to a database or an API) are subject to transient failures. These temporary faults cause lesser amounts of downtime due to timeouts, overloaded resources, networking hiccups, and other problems that come and go and are hard to reproduce. These failures are usually self-correcting.”

Resiliency and availability are enhanced by the client application leveraging best practice patterns, such as the retry pattern. “Retries can be an effective way to handle transient failures that occur with cross-component communication in a system.” A retry pattern is often coupled with the circuit breaker pattern that effectively shuts down all retries on an operation after a set number of retries have failed. This allows the system to recover from failed retries after hitting a known limit and gives it a chance to react in another way, like falling back to a cached value or returning a message to the user to try again later.”

The key takeaway is that the Daml solution’s client application needs to add this type of resiliency to increase availability of the overall system consisting of platform and application.

High Availability Cost Trade-Offs
*********************************

High availability can be costly so trade-offs are required. For illustration, if the goal is to remain running in all cases then extremely rare events, such as an asteroid strike that simultaneously wipes out all data centers in a continent, need to be taken into account. Some of these extreme events are highly improbable and may not need to be considered. This highlights that there is a trade-off between avoidance cost of an outage, the probability of a single failure (single component redundancy), and the probability of multiple simultaneous failures (multiple component, integrated redundancy). How can these trade-offs be analyzed?

Using unplanned downtime this can be calculated as: 
Error budget x Revenue lost per minute of downtime 
where the revenue lost per minute of downtime is a projected or measured statistic. Then the cost of loss of availability is easily derived. The formula can also be turned around to determine what availability is needed to attain a revenue target. Lastly, this formula can compare the cost to achieve higher availability, with associated increased revenue, with the increased investment cost. In this manner, the business goals drive the trade-offs for high availability. 

.. rubric:: Footnotes

.. [#f1] https://en.wikipedia.org/wiki/High_availability
