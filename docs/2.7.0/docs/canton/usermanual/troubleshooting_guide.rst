..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _troubleshooting_guide:

Troubleshooting Guide
=====================

Introduction
------------

Distributed systems can fail in many ways and finding the cause of an error is not straight forward. This guide here captures the common steps our engineers take when trying to troubleshoot issues found during development or support.

Enable Information Gathering
----------------------------

The following switches / steps should be taken in order to improve analyzing errors. Without these, you might not be able to diagnose “harder” issues.

* **Create Health Dumps**

     Ensure that you are able to create :ref:`Health Dumps <creating_dumps>`. You need to share these health dumps during any support request. The health dumps provide a lot of diagnostic information that we need to troubleshoot issues.

* **Turn on Debug Logging**

     Turn on debug logging by starting the process with::

          ./bin/canton -v  
     
     or even::

          ./bin/canton –debug

     The ``-v`` flag will turn on debug logging of all ``com.digitalasset.canton`` loggers, whereas ``--debug`` will turn on debug logging of all libraries too. Please also see :ref:`Logging <logging>`.

* **Turn on Detailed API Logging**

     You might want to turn on :ref:`detailed api logging <detailed_logging>`. This will write all incoming commands and the outgoing data into the log file and it will allow you to inspect the details of a command that leads to failures. Beware that if your commands contain sensitive data, this data will then be written to the log file.

* **Turn on metrics collection**

     See `Canton Metrics <canton-metrics>`. If you don’t have a metrics system, you can report metrics to CSV files and JMX beans by configuring::

       metrics.report-jvm-metrics = true

       canton.monitoring.metrics.reporters = [{ 
         type = csv
         directory = “metrics”
         interval = 5s
         filters = [{
           contains = "canton.updates-published"
         }, {
           contains = "sequencer-client.event-handle"
         }, {
           contains = "sequencer.processed"
         }, {
           contains = "executor.queued"
         }, {
           contains = "executor.running"
         }, {
           contains = "executor.waittime"
         }, {
           contains = "jvm.memory_usage.heap"
         }, {
           contains = "jvm.memory_usage.non-heap"
         }, {
           contains = "jvm.thread_states"         
         }]
       }, {
         type = jmx
       }]

     This will periodically write selected metrics to CSV files (one file per metric). It will also expose all available metrics as JMX beans; therefore, you can use VisualVM to look at metric values.

     The CSV reporter needs to have a ``filters`` parameter, because otherwise Canton will report all available metrics, which would substantially slow-down Canton. The JMX reporter does not need a ``filters`` parameter, because JMX beans only get evaluated when you actually look at them using VisualVM. So the JMX reporter is great for exploring different metrics initially. The CSV reporter is preferable, if you want to record metrics without human intervention.

* **Turn on database query cost monitoring**

     Enable ``canton.monitoring.log-query-cost.every = 60s``. This will capture query cost statistics and might help diagnose latency / indexing issues with your database, as 
     explained in :ref:`How to Diagnose Slow Database Queries <how_to_diagnose_slow_db_queries>`.

* **Turn on slow futures supervision**

     Enable ``canton.monitoring.log-slow-futures = yes`` which will track some operations and alert if they are taking too long (disabled by default to reduce the overhead).

* **Do not disable deadlock detection (enabled by default)**

     Deadlock detection (``canton.monitoring.deadlock-detection``) will periodically test if the JVM executes new tasks in a timely manner. It will log the following warning, if this is not the case: `Task runner <name> is stuck or overloaded for 5s"`. Failure of this check may indicate that the CPU is overloaded, the execution context is too small. Usually the check resolves itself with a subsequent log message: `Task runner <name> is just overloaded, but operating correctly. Task got executed in the meantime`. If this message does not appear, all available threads are blocked for some reason. Their stack-traces will be logged additionally. However, all threads being blocked are not common. They should not happen. Therefore, normally this check just indicates that your system is overloaded.

* **Configure delay logging**

     Delay logging (``canton.monitoring.delay-logging-threshold``, default ``20s``) will log a warning, if a node falls behind with processing messages from the sequencer. Such a warning indicates that the node is overloaded. As a rule of thumb, configure the maximum latency, i.e., the maximum time it should take Canton to process a command.

* **Do not disable trace context propagation (enabled by default)**

     Every request will receive a unique trace id. The trace id is included in log messages referring to that request. If trace context propagation is enabled (``canton.monitoring.tracing.propagation = enabled``), different nodes will use the same trace id for a request. This makes it easier for you to identify log messages across different nodes that refer to the same request.

Key Knowledge
-------------

* **Canton Transaction Processing Steps**

     Canton transaction processing has the following key steps involved. When we debug, we obviously try to find out which of the steps fails / is slow / faulty. This can help you to narrow down the component and the issue. As all the message exchange happens via the sequencer, you effectively observe whether the information came into the node and where the action that the node was supposed to take was taken by responding with a message to the sequencer (or emitting a command result on the ledger api). The phases are:

          * Phase 1: Submitting participant prepares the confirmation request based on the “Daml command input”. The confirmation request is sent to the sequencer, addressing the mediator and the validating participants.

          * Phase 2: The mediator receives the request from the sequencer, registers the transaction and starts to wait for confirmations.
          
          * Phase 3: The validating participants receive the confirmation request from the sequencer and perform their validations. The two main checks that happen here are: validation (is the transaction correct and properly authorized?) & conflict detection (are all contracts that are spent or fetched in the transaction still active?). 
          
          * Phase 4: The confirming participants, a subset of the validating participants, send their verdict on each sub-transaction they are privy via the sequencer to the mediator. The verdict can be ``LocalApprove`` or some rejection reason.
          
          * Phase 5: The mediator receives the mediator responses (approvals and rejections) from the participants via the sequencer and validates them. If the mediator receives enough responses for the given transaction, it will compute the “Verdict”, which is the final decision on the transaction.
          
          * Phase 6: The mediator sends its verdict to all validating participants of a transaction via the sequencer.
          
          * Phase 7: The participants receive the mediator verdict and register it to the record order publisher. While the validation can happen in parallel, the record publisher will ensure that the transactions are emitted in order.
     
     For each phase a log line that should appear at the beginning and one that appears at the end of the phase.

* **Internal Errors**

     If internal consistency checks fail and indicate a possible bug in Canton, Canton will include the term ``internal error`` into the log message. Please contact support, if you see an internal error.

* **Canton Error Codes**

     All non-internal warnings and errors are :ref:`logged consistently <machine_readable_information>` (or at least we aspire to do).The error code information listed in the documentation should contain all information you need in order to understand and possibly resolve the issue.

Log Files
---------

* **Canton Trace Ids**

     All Canton log statements contain a :ref:`trace-id <tracing>`. This tracing is turned on by default and the ``trace-id`` is passed between the distributed processes::

          c.d.c.p.p.s.InFlightSubmissionTracker:participant=participant1 
          tid:d5df95972a95b5ff00cb5cc3346c545f - NOT_SEQUENCED_TIMEOUT(2,d5df9597): 
          Transaction was not sequenced within the pre-defined max sequencing time and has 
          therefore timed out err-context:{location=SubmissionTrackingData.scala:175, 
          timestamp=2022-10-19T17:45:56.393151Z} 

     In above example, we see the trace id twice: ``tid:d5df95972a95b5ff00cb5cc3346c545f`` and ``NOT_SEQUENCED_TIMEOUT(2,d5df9597)``. By filtering according to the ``trace-id``, you can find almost all log statements that relate to a particular command. Unfortunately, the ledger-api server does not yet log the ``trace-id``. Therefore, sometimes, we also need to find out the command id of a transaction. You can do that by grepping for the “rosetta stone”, which is one particular log line that contains both strings::

          2022-10-19 17:45:20,630 [⋮] DEBUG 
          c.d.c.p.s.CantonSyncService:SimplestPingIntegrationTestInMemory/participant=participant1 
          tid:d5df95972a95b5ff00cb5cc3346c545f - Received submit-transaction
          5ec48477-b440-4175-a1f8-d8373d5108ef-ping-5838bf58-5e1d-4ccc-869b-0607bed42fc7 

     The first string is again the trace id and the second one is the command id. Ideally, you then subsequently filter for command-id and trace-id.

* **Extract the Context of a Log Message**

     The log lines often also contain the “context” of the component. Examples: 

     * This log line tells us which component of which participant (participant1) of which domain connection (da) has been emitting this log line. It also includes the trace id of the underlying request::
          
          2022-10-04 15:55:50,077 [⋮] DEBUG 
          c.d.c.p.p.TransactionProcessingSteps:participant=participant1/domain=da 
          tid:461cae6245cfaadc87c2481a17d7e1bb - Preparing batch for transaction 
          submission

     * During tests, the log line includes the name of the test. In this case, it is ``SimplestPingIntegrationTestInMemory``::

          :: 2022-10-04 15:55:50,077 [⋮] DEBUG c.d.c.p.p.TransactionProcessingSteps:SimplestPingIntegrationTestInMemory/
          participant=participant1/domain=da tid:461cae6245cfaadc87c2481a17d7e1bb 
          - Preparing batch for transaction submission


     * Some classes use a different format for logging the context. This time, the context comes after the log message::
     
          2022-11-02 11:13:27,017 [⋮] INFO  c.d.p.i.p.ParallelIndexerSubscription - Storing 
          Accept transaction 1220cea6b84e95a707025b866ffe7c36c0406759ef1494726d434b079b7d950dab15
          , context: {test: "AuthorizationIntegrationTestDefault", participant: "participant1", 
          offset: "00000000000000000e", update: {submissionTime: "1970-01-01T00:00:00Z", 
          recordTime: "1970-01-01T00:00:00.000433Z", completion: {actAs : 
          ["participant1::1220565a4c91e7218b71d9f8f48fb7913680caeef6182aa0136427c08344e7528a34"]
          , commandId : "94b7354f-9c6d-42bb-affe-441631e24a10-ack-d73e5645-286c-4853-bb5d-dfb40f62f94f", 
          submissionId: "17f795ef-511b-418b-9375-17b40af5d059", deduplicationPeriod : {offset: 
          "000000000000000001"}, applicationId : "admin-ping"}, workflowId: "admin-ping", 
          transactionId: "1220cea6b84e95a707025b866ffe7c36c0406759ef1494726d434b079b7d950dab15"
          , ledgerTime: "1970-01-01T00:00:00Z"}}
     

* **Compare with a Happy Path Successful Logging Trace**

     Many components will log something and it is impossible to document every micro-step that happens (as this is also subject to change). But it makes sense to compare a failure trace with a successful transaction trace. To get such a trace, you start up a canton “simple topology” example setup and run a simple::

          participant1.health.ping(participant2)

     You then open the log file and filter for the command processing of that ping (search for "Starting ping"). This will give you a “clean happy path trace”. You can then subsequently compare your failure trace to the happy-path trace and look for the differences, i.e. where did the steps start to take a different path etc.

* **Use the API Request Logger to Locate the Component**

     One key logging component is the ``ApiRequestLogger``. This component is injected into the GRPC library and will log every incoming and outgoing request / message. Therefore, we can easily observe when a transaction left a node and when it arrived at a subsequent node. If api logging is turned on, the api request logger will print the full detail of all the GRPC messages into the log files.

Using LNAV to View Log Files
----------------------------

* **Setup and Use LNAV**

     Setup lnav for viewing logs as described in :ref:`viewing logs<lnav>`. It will require a few minutes to get used to it, but the payoff of this investment is great and comes fast. **In particular get familiar with loading multiple files, filtering, searching and jumping to errors**.

* **Open Multiple Log Files in one LNAV Session**

     Generally, when you start reading log files, then open the log files of all involved nodes in a single lnav session (if the files are small enough): ``lnav participant1.log domain.log participant2.log``

* **Split Log Files if they are too big**

     If your log files are too big the unix utility ``split`` can be used to split the file into chunks. 

* **Uncompress GZ Log files for faster reading**

     Normally, log files are compressed when you get them. Lnav works much better and faster if you pass uncompressed files on the command line.

* **Easily Navigate to the First Logged Error**

     Then hit ``g`` to go to the beginning of the file and subsequently ``w`` or ``e`` to get to the first warning or error. Usually, the first error gives you the hint on what is going on.

* **Look at All Warnings and Errors**

     Canton’s error reporting has been designed to log a warning/error whenever it detects that something is not working as it should. Therefore, any problem will likely show up in the log file. On the flip side, Canton may log a huge number of warnings/errors, in particular if a node or the database goes down.
     If the first warning or error does not completely explain the situation, it is important to look at all such messages. Use the following recipe:

          #. Set the minimum log level to WARN to display only warnings and errors (``:set-min-log-level warn``).
          
          #. Look at the first message. Mark the message (pressing ``m``) so you can later get back to the message.
          
          #. Define an out-filter to hide the first message and all similar messages.
          
          #. Repeat steps (2) and (3) until you have filtered out all messages.
          
          #. Disable all out-filters. You can now press u and U to step through all marked warning and error messages.

* **Filter Irrelevant Items**

     One useful strategy when working with logs is to continuously remove lines that are not relevant, adding “filter-out” until only the relevant log messages remain.

* **Show Gap In Logging Times**

     Once you start filtering for a particular command trace, you might want to hit “shift-t”. This will show you the delta time between the first log line and the subsequent one. Usually, you just need to find the “gap”. This will tell you immediately where something got stuck / slow / timed out:

          * open the log files of all components
          
          * search for the first error / warn (i.e. hit ``w`` or ``e``)
          
          * pick the trace-id (as described above) and filter for it
          
          * hit ``shift-t`` and find the gap.

Setup Issues
------------

* Connect to each node and check the status: *<node>* ``.health.status``

* Are the nodes up and running?

* Are the nodes :ref:`connected to a sequencer <sequencer_connections>`? Errors that often happen here are:

     * public-apis / ledger-api addresses are not set to ``0.0.0.0`` and are still binding to ``localhost`` (default value for security reasons).
     
     * you are using TLS on the server side, but on the client side you have defined the URL as ``http://``.
     
     * the chosen port is not correct.

* If you are running into TLS connectivity issues, turn on “--debug” and check the detailed netty logs for hints. These libraries tend to log necessary information only on debug level. You can also increase the debugging information level by starting canton with `-Djavax.net.debug=all`.

* Try to confirm that your setup works by running a ping::

     participant1.health.ping(participant2)

Timeout Errors
--------------

Any transaction that is submitted to Canton will either be successfully worked off (accepted or rejected), or eventually timeout. If a transaction hits a timeout, the application will be informed by an appropriate completion event on the Ledger API about the rejection reasons. We can hit the following timeouts in Canton (you can get further timeouts from the `command service <https://docs.daml.com/app-dev/services.html#command-service>`_):

     * ``NOT_SEQUENCED_TIMEOUT``
     * ``LOCAL_VERDICT_TIMEOUT``
     * ``MEDIATOR_SAYS_TX_TIMED_OUT``
     * ``LOCAL_VERDICT_LEDGER_TIME_OUT_OF_BOUND``
     * ``LOCAL_VERDICT_SUBMISSION_TIME_OUT_OF_BOUND``

Such a timeout usually means that some component is either:

     * offline - resolve by checking that all nodes are healthy (``health.status()``) and are connected with each other.
     
     * overloaded - resolve by tuning according to our :ref:`performance configuration guide <performance_configuration>`.

     * unable to complete the transaction processing within the given time (i.e. transactions are too big) - resolve by increasing the timeouts as described in our :ref:`performance configuration guide <performance_configuration>`.

* **Use a ping to determine if your system is broken or just slow / overloaded / contentious**

     Many issues only surface under high load. Therefore, it often makes sense to diagnose timeout issues using a::

          participant1.health.ping(...) 

     while the system is idle. If the ping works, then you have likely a throughput / performance / contention issue and you should use one of the other guides to continue debugging.
     
     If the ping doesn't work and never did before, you should check the setup troubleshooting guide.

     If previously, transaction processing worked and now stopped working, while all nodes are up and running, and reporting to be healthy, you should raise an issue with support. 

     By turning on diagnostics information collection as explained above, you can then figure out which step of transaction processing failed by comparing the trace in the logs to the Phase 1-7 explanation, isolating out which component did not respond.

Auth Errors
-----------

For security reasons, Canton removes all details from auth errors. On the client side, you usually only see 
``PERMISSION_DENIED/An error occurred. Please contact the operator and inquire about the request <no-correlation-id>``, so you need to inspect server logs to debug auth errors.

To use an auth-enabled ledger api, the caller needs to attach an access token to the gRPC request. These tokens are attached in the ``Authorization`` HTTP header. To see headers attached to incoming and outgoing requests, you need to set the log level to ``TRACE``. ``ApiRequestLogger`` will then output log lines containing ``received headers`` or ``sending response headers``.

Filter-in expressions for lnav:

     * com.digitalasset.canton.ledger.api.auth.Authorizer
     * c.d.l.a.a.i.AuthorizationInterceptor
     * c.d.c.n.g.ApiRequestLogger

Common patterns from the canton log:

     * ``PERMISSION_DENIED(7,0): Could not resolve is_deactivated status for user``

          You are using a token for a user that is not (yet) allocated. The log line contains the name of the user that needs to be allocated.

     * ``PERMISSION_DENIED(7,0): Claims are only valid for applicationId``

          You are using a wrong application Id when submitting commands. The log line contains the expected application ID. Note that the application ID must be equal to the daml user name when using ledger API access tokens.

     * ``UNAUTHENTICATED(6,0): The command is missing a (valid) JWT token``

          You did not attach a token to the request, or the token could not be decoded. Use `JWT.IO <https://jwt.io/#debugger-io>`_ to verify that the token string is a valid JWT.

     * ``PERMISSION_DENIED(7,0): Claims do not authorize to act as party``

          The log line contains the name of the missing claim, but not the actual claims. When using tokens based on user names (`Audience Based Tokens <https://docs.daml.com/app-dev/authorization.html#audience-based-tokens>`_ and `Scope Based Tokens <https://docs.daml.com/app-dev/authorization.html#scope-based-tokens>`_), consult the user management service to see whether you need to grant more rights to the user. When using tokens based on party names (`Custom Claims Access Tokens <https://docs.daml.com/app-dev/authorization.html#custom-daml-claims-access-tokens>`_), debug the token in `JWT.IO <https://jwt.io/#debugger-io>`_.

Performance Issues
------------------

How to obtain a performant system is :ref:`extensively documented <performance_configuration>`.

If you have followed that documentation, we can assume that:

     * Your database pools are sufficiently sized: check metric ``db-storage.queue``.
     
     * You have set the right settings with respect to:

          * number of threads (check cpu usage)
          * number of database connections (connection pool size) (``max-connections`` in storage)
          * high-throughput sequencer settings (``sequencer.writer.type = high-throughput``)
     
     * The database server is using SSDs and not spinning disks, and the latency to the database is low.
     
     * You are not using one of the slow “DLT layers” such as Fabric or Besu that are simply limited in their throughput (``sequencer.type = database``).
     
     * You have enough spare CPU capacity (cpu usage is not at 100%).
     
     * You don't have other systems competing for resources.
     
     * The max inflight transaction resource limits on the participant (``participant1.resources.set_resource_limits``) have been set carefully. The resource limits are low enough so that an application cannot overload Canton. The resource limits are high enough such that applications can submit commands at the desired target rate.
     
     * You are able to load the system fully. I.e. the load generator that you apply is submitting faster than the system can handle (i.e. you throttle using, for example, max 1000 pending commands, the latency grows linearly with num pending commands).

If you have done all that, you might have reached the limit of what the Canton version you are using can do. The next step is then to find out which component is creating the bottleneck. Generally, it is either one of the nodes or the database.

How to Measure Database Performance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To get a first impression of database performance, enable the following metrics:

     * Metrics containing ``executor.waittime``. These metrics show the time (in millis) a db command needs to wait until Canton sends it to the db. High values indicate that the db is a bottleneck.
     
     * Metrics containing ``executor.queued``. These metrics show the number of db commands waiting in a queue for being sent to the db. High values indicate that the db is a bottleneck.
     
     * Metrics containing ``executor.running``. These metrics show the number of tasks currently being executed by the db. Very high values indicate that Canton is overloading the db. Very low values indicate that Canton is not fully loading the db. The number of db connections can be configured via ``canton.<path-to-my-node>.storage.parameters.max-connections``.

.. _how_to_diagnose_slow_db_queries:

How to Diagnose Slow Database Queries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If database metrics indicate that the database is a bottleneck you may want to obtain more detailed information on query performance. For that, you need to enable query cost monitoring (``canton.monitoring.log-query-cost.every = 60s``). Once you have done that, Canton will log every 60 seconds a report on query statistics::

     2022-08-16 07:12:35,528 [slick-diexec_domain-4-7] INFO  c.d.c.r.DbStorage:domain=diexec_domain - Here is our list of the 15 most expensive database queries for canton.db-storage.general.executor:
     count=    598 mean=  13.61 ms total=  8.1 s com.digitalasset.canton.domain.sequencing.sequencer.store.DbSequencerStore.saveWatermark(DbSequencerStore.scala:593)
     count=    598 mean=   8.82 ms total=  5.3 s com.digitalasset.canton.domain.sequencing.sequencer.store.DbSequencerStore.fetchWatermark(DbSequencerStore.scala:621)
     count=      1 mean=  29.48 ms total=  0.0 s com.digitalasset.canton.domain.sequencing.authentication.DbMemberAuthenticationStore.expireNoncesAndTokens(MemberAuthenticationStore.scala:234)
     count=      2 mean=   9.37 ms total=  0.0 s com.digitalasset.canton.topology.store.db.DbTopologyStore.$anonfun$queryForTransactions$2(DbTopologyStore.scala:387)
     count=      1 mean=  18.52 ms total=  0.0 s 

The information in here can be very useful:

     * ``count`` means how often has this query run in the last period.
     * ``mean`` means what was the average execution time of that query
     * ``total`` = ``count`` * ``mean``
     * ``saveWatermark(DbSequencerStore.scala:593)`` is really the query with the place in the source code that is being run

Please note that the “execution time” of the query does not include “queuing time” in the connection pool. The time is really the time it took from sending to the JDBC driver to getting the result back.

Now, you do the following analysis:

     * if you have for example ``max-connections = 4`` and you log once a minute, if the total time of the queries approaches 240s, then you are obviously using up all db connections that are available. 

     * if a single query runs for ``60s``, then that query might be a sequential bottleneck, as it has been running for 60s out of the 60s interval.

     * the mean time should also tell you roughly the db latency, as there are some cheap read queries that should run *< 1ms*. If these queries take a long time, then you know that the database has high latencies or is overloaded.

How to find the Bottleneck
~~~~~~~~~~~~~~~~~~~~~~~~~~

In some situations, you would like to understand which component is causing a particular bottleneck. You can do that using the following technique. 

Theory
^^^^^^

In a model system with several computing stages:

     *Input -> Stage1 -> Stage2 -> Stage3 -> Stage4 -> Stage5 -> Output*

The maximum throughput of the system is given by the minimum of the maximum throughputs of all stages. Let's assume that the max throughput is limited by Stage3 that has 100 tx/s.

Now, if you have an input source that will throttle its submission based on the number of “open requests”, then we know that the average latency of each transaction is going to be

	*latency  = num-open-requests / max-throughput*

The latency will grow linearly with the number of open requests. Now, as we previously defined that 
	
     *throughput(Stage 3) < throughput (all other Stages)*

We know that the open requests will be starting to pile up in front of Stage 3, because all other stages are processing every transaction much faster.

Therefore, if we run the system under full load with N pending requests, such that the observed latency is large compared to the “zero load latency” of the system, then the bottleneck is trivially observable from the trace of a command: there will be a gap in the trace of a command, where the transaction is not being processed for (*observed latency - zero load latency*). That gap is the sequential bottleneck.

Practical
^^^^^^^^^

#. Find out what the zero load latency of your system is by running a simple ping over an idle system. A ping does three end-to-end Daml transactions, so your zero load latency is just a third of the observed ping latency.

#. Run the system under full load again, including debug logging. You should be able to load the system such that the observed latency is at least an order of magnitude larger than the zero load latency.

#. Open the log files and pick a transaction in the middle of your test run:

     * Look for “TransactionAccepted” somewhere in the log file and pick the trace-id
     * Filter for the trace-id and find the command-id. Add the command-id to the filter
     * Hit Shift-T to see the time differences.
     * Find the gaps

To increase confidence, repeat this assessment on a few more transactions.

Contention
----------

Why do you get contention
~~~~~~~~~~~~~~~~~~~~~~~~~

This section here explains you how to deal with situations where many commands are failing with errors such as:

     * ``LOCAL_VERDICT_LOCKED_CONTRACTS``
     * ``LOCAL_VERDICT_LOCKED_KEYS``
     * ``LOCAL_VERDICT_INCONSISTENT_KEY``
     * ``LOCAL_VERDICT_INACTIVE_CONTRACTS``
     * ``LOCAL_VERDICT_DUPLICATE_KEY``
     * ``CONTRACT_NOT_FOUND``
     * ``DUPLICATE_CONTRACT_KEY``

Canton is not just a distributed system, but a distributed **racy** system where different independent actors may race for contracts or other resources. As a simple example: if you have an offer contract that can be accepted by a buyer and revoked by the seller, then the decision of the buyer to accept can race with a decision of the seller to revoke the offer. 

Now, a distributed decision system with individual actors can be **accidentally racy** or **intentionally racy**. Let's explain the difference between the two:

     * **Intentionally racy**: You are putting out an offer for anyone interested on a first-come first serve basis. People might race for it and that is intended.

     * **Accidentally racy**: You turn off the traffic lights at a crossing. Suddenly, access to the shared resource (the crossing) is not managed anymore such that everyone rushes into it, blocking the entire box, making it impossible for anyone to move, leading to a complete traffic break-down.

If the system and model is intentionally racy, there is nothing you can do about the rejections. They must be there as they are the result of resolving the race for resources. But often, you will find the situation that the model is accidentally racy, which can be fixed by changing the model slightly. In many cases, contention arises due to contract-keys being fetched and updated. The issue is then that the transaction is built in phase 1, looking at the contract key state at that time. The validation / conflict detection happens then in phase 3. If any other transaction changed that particular key in the time between phase 1 and phase 3, the transaction will fail. 

Whether you get ``INACTIVE_CONTRACTS``, ``LOCKED_CONTRACT`` or ``CONTRACT_NOT_FOUND`` just depends on timing of the competing transaction. ``LOCKED`` means: there is a transaction about to change this resource, but we have not yet received the final verdict on it.

How To Change Your Model To Avoid Undesired Contention
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Now, you can resolve such accidental raciness by “introducing order” into the race. As an example, you let individuals submit “request contracts” and you add one delegated party that receives these requests and orders and performs their application to a shared resource (through delegation). As an example, if you have an AccountIdGenerator::

	template AccountIdGenerator
		next : Integer
		…
	where 
		choice NextAccount : (ContractId AccountId, ContractId AccountIdGenerator)
		do
			a <- create this with next = next + 1
			b <- create AccountId with accountId = next
			return (a,b)

This ``AccountIdGenerator`` contract will be very racy. However, you can just add a::

	template GetAccountIdRequest
		
and then have a single application consume these requests and generate ids. That single application knows whether it has already spent the existing ``AccountIdGenerator`` contract. Of course, it would make sense to support a list of requests in the choice ``NextAccount`` such that many AccountIds are created at once, as otherwise, the throughput of account allocation would be limited.

This is just a simple example, but should be sufficient to illustrate the issue and the solution idea.

How To Find Contention
~~~~~~~~~~~~~~~~~~~~~~

In a distributed application, where different systems such as Triggers, Nanobots, Ingestion Application etc submit transactions, it is often not easy to understand where the contention is coming from. Here is a recipe that can be used on the Canton level:

     #. Ensure that you have turned on Detailed API Logging with Debug logs.
     
     #. Run your system / tests until you have collected enough information / rejections.
     
     #. Open the log files and search for one of the rejections, i.e. search for ``LOCKED``.
     
     #. Filter by the trace-id of this rejection. Determine the command-id using the “rosetta stone” log entry. Add the command-id to the filter.
     
     #. Now, find the ApiRequestLogger log entry of the CommandSubmissionService. This log entry contains the entire command that the application has submitted (if you turned on the detailed api logging). I.e. the “exercise choice” that caused the contention.
     
     #. Then, go back to the rejection (i.e. the one with ``LOCKED``). This rejection will contain a ``ResourceInfo``, referring to the key / contract that caused the rejection. The ResourceInfo will contain the key that caused the failure.

Using the above recipe, you determine the choice and which key in that particular choice created the problem. This should be sufficient to find the problematic parts in the model.

Use Bisection to Narrow Down the Root Cause
-------------------------------------------

In this section an alternative approach is outlined that could help you if the guidelines in the previous sections were insufficient to resolve the problem. To apply that approach, you do not need a deep understanding of Canton. It is not only suitable to investigate problems inside of Canton, it also helps to discover problems coming from the environment.

The approach is best explained with an example. Suppose you have developed a Canton deployment and successfully tested it on your local machine. After moving it to the distributed test environment, it is showing some problems. So you have two Canton deployments, a local one and distributed one, one of them works correctly, the other one is broken.

You notice the following differences between the two deployments:

     * The local deployment runs all nodes in a single process. The distributed deployment runs nodes in different processes.
     * The local deployment runs all nodes on the same machine. The distributed deployment runs nodes on different machines.
     * Only the distributed deployment has TLS enabled.
     * Only the distributed deployment has high-availability enabled.
     * The distributed deployment runs in a docker container (e.g. by using a cloud environment). The local deployment does not use docker.

To better understand which of the differences is causing the problem, you setup a new deployment that has **only half of the differences**. That could mean, you setup a new deployment with the following characteristics:

     * It runs nodes in **different processes** (like the distributed deployment)
     * It runs nodes on the same machine (like the test deployment).
     * It has TLS **enabled**.
     * It has high availability disabled.
     * It does not use docker.

For the sake of reference, let's call it "Deployment 3". Now you rerun the test. If the test succeeds (as for the local deployment), you know that the problem in the distributed deployment is caused by the network, by high-availability, or by docker. If the test fails (as for the distributed deployment), you know that the problem is caused by running several processes, by using TLS or by both. For the sake of the illustration, let's assume the test succeeds.

To further narrow down the root cause, you setup yet another deployment that is “in the middle” between "Deployment 3" (which was successful) and the distributed deployment (which was failing). That could mean:

     * It runs nodes in different processes.
     * It runs nodes on **different** machines (like the distributed deployment).
     * It has TLS enabled.
     * It has high availability disabled.
     * It does not use docker.

Let's call it "Deployment 4". Again, you rerun the test. If the test succeeds, you know that the problem in the distributed deployment is caused by high-availability or by docker. If the test fails, you know that the problem is caused by some combination of running nodes in different processes, on different machines and having TLS enabled. Let's assume that the test fails.

To further narrow down the root cause, try to set up the simplest possible deployment that still has the problem. That could mean:

     * You simplify your test, e.g., **run a ping** instead of a complex workflow. It runs **only two nodes** (because you are aiming for a minimal example).
     * The two nodes run **in different processes on different machines** (because that seemed to be the root cause).
     * TLS is **disabled** (because that seemed not to trigger the problem).
     * High availability is disabled.
     * It does not use docker.

Let's call it “Deployment 5”. If the test fails on "Deployment 5", you have a minimal example to reproduce the problem. You know that the problem is caused by running two nodes on different machines. The problem is independent of your DAML workflow, occurs already with two nodes and without enabling TLS. If the test succeeds on "Deployment 5", you have not yet understood the root cause. In that case, you need to do yet another iteration with a deployment “in the middle” between "Deployment 4" and "Deployment 5".

The following guidelines are helpful to make this approach successful:

     * Try to keep the list of differences between successful and failing deployment **as complete as possible**. If the root cause is not on your list, you can't find it. Differences can come from configuration, DAML models, ledger applications, deployment (in process, network, docker, kubernetes, ...), hardware, operating system.
     
     * Always **aim at the middle** between the successful and failing deployment to learn the most with every new deployment you create and test. That is the fastest path to the root cause.
     
     * **Don't make assumptions up front** of which difference may or may not cause the problem. For example, if you are making the assumption that the problem is not caused by TLS, you may save one iteration, if you are right. But you will take a long detour, if you are wrong.
     
     * Do not assume that the problem is caused by a single difference between the two deployments. It could very well be that a **combination of differences** is needed to **reproduce the problem**.
