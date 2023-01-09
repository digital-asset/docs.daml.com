..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _monitoring:

Monitoring
==========

.. _logging:

Logging
-------
Canton uses `Logback <https://logback.qos.ch>`__ as the logging library. All Canton logs derive from the logger ``com.digitalasset.canton``.
By default, Canton will write a log to the file ``log/canton.log`` using the ``INFO``
log-level and will also log WARN and ERROR to stdout.

How Canton produces log files can be configured extensively on the command line using the following options:

- ``-v`` (or ``--verbose``) is a short option to set the canton log level to ``DEBUG``. This is likely the most common log option you will use.
- ``--debug`` sets all log levels, except stdout which is set to ``INFO``, to ``DEBUG``. Note that ``DEBUG`` logs of external libraries can be very noisy.
- ``--log-level-root=<level>`` configures the log-level of the root logger. This changes the log level of Canton and of external libraries, but not of stdout.
- ``--log-level-canton=<level>`` configures the log-level of only the Canton logger.
- ``--log-level-stdout=<level>`` configures the log-level of stdout. This will usually be the text displayed in the Canton console.
- ``--log-file-name=log/canton.log`` configures the location of the log file.
- ``--log-file-appender=flat|rolling|off`` configures if and how logging to a file should be done. The rolling appender will roll the files according to the defined date-time pattern.
- ``--log-file-rolling-history=12`` configures the number of historical files to keep when using the rolling appender.
- ``--log-file-rolling-pattern=YYYY-mm-dd`` configures the rolling file suffix (and therefore the frequency) of how files should be rolled.
- ``--log-truncate`` configures whether the log file should be truncated on startup.
- ``--log-profile=container`` provides a default set of logging settings for a particular setup. Right now, we only support the ``container`` profile which logs to STDOUT and turns of flat file logging to avoid storage leaks due to log files within a container.
- ``--log-immediate-flush=false`` turns off immediate flushing of the log output to the log file.

Please note that if you use ``--log-profile``, the order of the command line arguments matters. The profile settings can be overridden on the command line by placing adjustments after the profile has been selected.

Canton supports the normal log4j logging levels: ``TRACE, DEBUG, INFO, WARN, ERROR``.

For further customization, a custom `logback configuration <https://logback.qos.ch/manual/configuration.html>`__ can be provided using ``JAVA_OPTS``.

.. code-block:: bash

    JAVA_OPTS="-Dlogback.configurationFile=./path-to-file.xml" ./bin/canton --config ...


If you use a custom log-file, the command line arguments for logging will not have any effect, except ``--log-level-canton`` and ``--log-level-root`` which can still be used to adjust the log level of the root loggers.

.. _lnav:

Viewing Logs
~~~~~~~~~~~~

We strongly recommend the use of a log file viewer such as `lnav <https://lnav.org/>`__ to view Canton logs and resolve issues.
Among other features, lnav has automatic syntax highlighting, convenient filtering for specific log messages, and allows viewing log files of different Canton components in a single view.
This makes viewing logs and resolving issues a lot more efficient than simply using standard UNIX tools such as less or grep.

In particular, we have found the following features especially useful when using ``lnav``:

- viewing log files of different Canton components in `a single view <https://lnav.org/features#single-log-view>`__ merged according to timestamps (``lnav <log1> <log2> ...``).
- `filtering <https://docs.lnav.org/en/latest/usage.html#filtering>`__ specific log messages in (``:filter-in <regex>``) or out (``:filter-out <regex>``). When filtering messages, e.g. with a given trace-id, in, a transaction can be traced across different components, especially when using the single-view-feature described above.
- `searching <https://docs.lnav.org/en/latest/usage.html#searching>`__ for specific log messages (``/<regex>``) and jumping in-between them (``n`` and ``N``).
- automatic syntax highlighting of parts of log messages (e.g. timestamps) and log messages themselves (e.g. ``WARN`` log messages are yellow).
- `jumping <https://docs.lnav.org/en/latest/usage.html#searching>`__ in-between error (``e`` and ``E``) and warn messages (``w`` and ``W``).
- selectively activating and deactivating different filters and files (``TAB`` and `` `` to activate/deactivate a filter).
- marking lines (``m``) and jumping back-and-forth between marked lines (``u`` and ``U``).
- jumping back-and-forth between lines that have the same :ref:`trace-id <tracing>` (``o`` and ``O``).

The `custom lnav log format file <https://docs.lnav.org/en/latest/formats.html>`__ for Canton logs ``canton.lnav.json`` is bundled in any Canton release. It can be installed with ``lnav -i canton.lnav.json``.
JSON based log files (which need to use the file suffix ``.clog``) can be viewed using the ``canton-json.lnav.json`` format file.

.. _detailed_logging:

Detailed Logging
~~~~~~~~~~~~~~~~

By default, logging will omit details in order to not write sensitive data into log files. For debug or
educational purposes, you can turn on additional logging using the following configuration switches:

.. code-block:: none

    canton.monitoring.logging {
        event-details = true
        api {
            message-payloads = true
            max-method-length = 1000
            max-message-lines = 10000
            max-string-length = 10000
            max-metadata-size = 10000
        }
    }


In particular, this will turn on payload logging in the ``ApiRequestLogger``, which records every GRPC API invocation,
and will turn on detailed logging of the ``SequencerClient`` and for the transaction trees. Please note that all
additional events will be logged at DEBUG level.

.. _tracing:

Tracing
-------

For further debuggability, Canton provides a trace-id which allows to trace the processing
of requests through the system. The trace-id is exposed to logback through the
*mapping diagnostic context* and can be included in the logback output pattern using ``%mdc{trace-id}``.

The trace-id propagation is enabled by setting the ``canton.monitoring.tracing.propagation = enabled``
configuration option, which is already enabled by default.

It is also possible to configure the service where traces and spans are reported to, for observing distributed traces.
Refer to :ref:`Traces <traces>` below to see what it looks like.

Currently Jaeger and Zipkin are supported. For example, Jaeger reporting can be configure as follows:

::

    monitoring.tracing.tracer.exporter {
      type = jaeger
      address = ... // default: "localhost"
      port = ... // default: 14250
    }

The configuration above will connect to a running Jaeger server to report tracing information.

It is possible to easily run Jaeger in a Docker container as follows:

::

    docker run --rm -it --name jaeger\
      -p 16686:16686 \
      -p 14250:14250 \
      jaegertracing/all-in-one:1.22.0

If you prefer not to use Docker, it is also possible to download the binary for your specific OS at `Download Jaeger <https://www.jaegertracing.io/download/#binaries>`_. Unzip the file and then simply run the binary titled `jaeger-all-in-one` (no need for providing any arguments to it).
By default Jagger will expose port `16686` for its UI which can be seen in a browser window, and port `14250` to which Canton will report trace information. Please make sure to properly expose these ports.

Please make sure that all Canton nodes in the network report to the same Jagger server in order to have an accurate view of the full traces, and that the Jaeger server is reachable by all Canton nodes.

Sampling
~~~~~~~~

It is also possible to change how often spans are sampled (i.e. reported to the configured exporter).
By default it will always report (``monitoring.tracing.tracer.sampler.type = always-on``).
It can also be configured to never report (``monitoring.tracing.tracer.sampler.type = always-off``, although not super useful).
And it can also be configured so that a specific fraction of spans are reported like below:

::

    monitoring.tracing.tracer.sampler = {
      type = trace-id-ratio
      ratio = 0.5
    }

There is one last property of sampling that can be optionally changed. By default we have parent-based sampling on (``monitoring.tracing.tracer.sampler.parent-based = true``)
which means that a span is sampled iff its parent is sampled (the root span will follow the configured sampling strategy).
This way, there will never be incomplete traces, so either the full trace is sampled or not.
If this property is changed, all spans will follow the configured sampling strategy ignoring whether the parent is sampled or not.

Known Limitations
~~~~~~~~~~~~~~~~~

Not every trace created which can currently be observed in logs are reported to the configured trace collector service.
Traces originated at console commands or that are part of the transaction protocol are largely well reported, while other kinds of traces
are being added to the set of reported traces as the need arise.

.. todo::
    The limitation mentioned below is to be addressed as part of the below tickets:
    `#10633 <https://github.com/DACH-NY/canton/issues/10633>`_
    `#14256 <https://github.com/digital-asset/daml/issues/14256>`_

Also, even the transaction protocol trace has a know limitation which is that once some command is submitted (and its trace fully reported),
if there are any resulting daml events which are subsequently processed as a result, a new trace is created as currently the ledger api does not
propagate any trace context info from command submission to transaction subscription. This can be observed for example by the fact that
if a participant creates a ``Ping`` contract, it is possible to see the full transaction processing trace of the ``Ping`` command being submitted, but then
the participant which processes the ``Ping`` by exercising ``Respond`` and creating the ``Pong`` contract will then create a separate trace instead of continuing to use the same one.

Note that this is different than if a single Daml transaction results in multiple actions at the same time (multiple contracts being archived and created).
In that case a single trace would encompass the whole process, since it is happening as part of a single transaction as opposed to as a result of
some external process reacting to Daml events.

.. _traces:

Traces
~~~~~~

Each span represents a single operation within a trace. A trace is a directed acyclic graph (DAG) of spans, where the edges between spans are defined as parent/child relationships (definitions taken from `Opentelemetry's glossary <https://opentelemetry.io/docs/concepts/glossary/>`_).

Canton currently reports several different kinds of traces. For example, every Canton console command that interacts with the admin api starts a trace whose initial span last for the whole duration of the command, including the GRPC call to the specific admin api endpoint.

.. figure:: ./images/ping-trace.jpg
   :align: center
   :width: 100%

One important trace is the trace of Daml command submission. This trace is illustrated above as part of performing a Canton ping using the console, which contains 18 spans.
Note that this is what it looks like as of October 2022, and it may have changed slightly.
The current tracing focuses largely on the message exchange via the sequencer, without digging deep into the message handlers and further processing of transactions. We will close those gaps in the future.
The ping illustrated here is started by ``participant1`` and has ``participant2`` as the target.

Notice that in some cases spans may start later than the end of their parent, due to their processing happening asynchronously.
That is, at a later point, as opposed to during the processing of the predecessor.
This typically happens when the new operation gets placed on a queue to be handled later, which immediately frees the parent span and ends it.
It is made clear below the moments when this happens.

The initial span (span 1) covers the duration of the whole ping operation, with a GRPC request made by the console which is handled by the GrpcPingService (span 2) in the participant node which also lasts for the whole duration of the ping operation.

For context, the Canton ping consists of 3 different Daml commands:

1. ``participant1``’s admin party creates the ``Ping`` contract
2. ``participant2``’s admin party exercises the ``Respond`` consuming choice on the contract, which results in the creation of a ``Pong`` contract.
3. ``participant1``’s admin party exercises the ``Ack`` consuming choice on it.

.. todo::
    `#10633 <https://github.com/DACH-NY/canton/issues/10633>`_

Starting at span 3 in the example trace we see the submission of the first of the three Daml commands (the creation of the ``Ping`` contract).
Due to a limitation explained in the next section, the other 2 Daml command submissions do not get linked to this whole trace. It is possible to find them separately.
In any case span 2 will only complete once the 3 Daml commands are completed.

At span 3 the participant node itself is on the client side of the ledger-api, but in other use cases it could also be an application integrated with the participant.
This span lasts for the duration of this GRPC call, which gets received on the server side (span 4) and gets handled by the ``CantonSyncService`` (span 5).
At this point the request is received and acknowledged, but not fully processed. It is processed asynchronously later on, which means that spans 3 to 5 will complete before the request is actually handled.

Currently missing from the trace, which accounts for some of the gap between spans 5 and 6, is the domain routing where the participant decides which domain to use for the
command submission, and the preparation of the initial set of messages to be sent. At span 6 we see the start of the Canton transaction protocol. Here ``participant1`` sends a request to ``sequencer1`` for it to sequence the initial set of confirmation requests messages as part of phase 1 of the transaction protocol.

The transaction protocol has 7 phases. An in-detail document about them will be made available soon, currently a simple description can be found at :ref:`transaction processing <canton-overview-tx-processing>`.

At span 7 we see ``sequencer1`` receive the request and register it. Receipt of the messages is not part of this span, as that happens asynchronously at a later point.

At span 18, as part of phase 2, ``mediator1`` receives an informee message and all it needs to do is validate and register it. As it doesn't need to respond, span 18 has no children.

As part of phase 3, ``participant2`` receives a message (which we can see at span 8) and ``participant1`` also receives a message (which we can see at span 9).
Both participants asynchronously validate the messages. ``participant2`` does not need to respond since it is only an observer, that's why span 8 has no children.
``participant1`` however will respond, which is visible at span 10 where it is again making a call to the ``sequencer1``, which receives it at span 11.

At span 12, ``participant1`` receives a successful send response message that signals that his message to the mediator was successfully sequenced.
This is happening as part of phase 4, where confirmation responses are sent to the mediator. We can see the mediator receive it at span 13, and will then proceed to validate the message (phase 5).

At this point, as we can see in spans 14 and 15, ``mediator1`` (now at phase 6) asks ``sequencer1`` to send the transaction result messages to the participants.

To end this round of the transaction protocol, ``participant1`` and ``participant2`` receive their messages at spans 16 and 17 respectively. The messages are asynchronously validated and their projections of the virtual shared ledger are updated (phase 7).

As mentioned, there are 2 other transaction submission which are unlinked from this ping trace but are part of the operation. It is also possible to find them.
The second one starts at a span titled ``admin-ping.processTransaction`` which is created by ``participant2``, and the third one has the same name but is initiated by ``participant1``.

.. _status-commands:

Status
------

Each Canton node exposes rich status information. Running

.. code-block:: bash

    <node>.health.status

will return a status object which can be one of

- ``Failure`` - if the status of the node cannot be determined, including an error message why it failed
- ``NotInitialized`` - if the node is not yet initialized
- ``Success[NodeStatus]`` - if the status could be determined including the detailed status.

Depending on the node type, the ``NodeStatus`` will differ. A participant node will respond with a message containing

- ``Participant id:`` - the participant id of the node
- ``Uptime:`` - the uptime of this node
- ``Ports:`` - the ports on which the participant node exposes the Ledger and the Admin API.
- ``Connected domains:`` - list of domains the participant is currently connected to properly
- ``Unhealthy domains:`` - list of domains the participant is trying to be connected to but where the connection is not ready for command submission.
- ``Active:`` - true if this instance is the active replica (can be false in case of the passive instance of a high-availability deployment)


A domain node or a sequencer node will respond with a message containing

- ``Domain id:`` - the unique identifier of the domain
- ``Uptime:`` - the uptime of this node
- ``Ports:`` - the ports on which the domain node exposes the Public and the Admin API
- ``Connected Participants:`` - the list of connected participants
- ``Sequencer:`` - a boolean flag indicating if the embedded sequencer writer is operational


A domain topology manager or a mediator node will return

- ``Node uid:`` - the unique identifier of the node
- ``Uptime:`` - the uptime of this node
- ``Ports:`` - the ports on which the node hosts its APIs.
- ``Active:``  - true if this instance is the active replica (can be false in case of the passive instance of a high-availability deployment)

.. _creating_dumps:

Health Dumps
------------

In order to provide efficient support, we need as much information as possible. For this purpose, Canton implements
an information gathering facility that will gather key essential system information for our support staff.
Therefore, if you encounter an error where you need our help, please ensure the following:

- Start Canton in interactive mode, with the ``-v`` option to enable debug logging: ``./bin/canton -v -c <myconfig>``.
  This will provide you with a console prompt.
- Reproduce the error by following the steps that previously caused the error. Write down these steps so they can be
  provided to support staff.
- After you observe the error, type ``health.dump()`` into the Canton console to generate the ZIP file.

This will create a dump file (``.zip``) that stores the following information:

- The configuration you are using, with all sensitive data stripped from it (no passwords).
- An extract of the logfile. We don't log overly sensitive data into log files.
- A current snapshot on Canton metrics.
- A stacktrace for each running thread.

Please provide the gathered information together with the exact list of steps you did that lead
to the issue to your support contact. Providing complete information is very important to us in order to help you
troubleshoot your issues.

Remote Health Dumps
~~~~~~~~~~~~~~~~~~~

When running a console configured to access remote nodes, the ``health.dump()`` command will gather health
data from the remote nodes and package them in the resulting zip files. There is no special action required.
It is also possible to obtain the health data of a specific node by targeting it when running the command.

For instance:

``remoteParticipant1.health.dump()``

When packaging large amounts of data, it can be useful to increase the default timeout of the dump command:

``health.dump(timeout = 2.minutes)``

.. _health-check:

Health Check
------------

The ``canton`` process can optionally expose an HTTP endpoint indicating if the process believes it is healthy.
This is intended for use in uptime checks and liveness probes.
If enabled, the ``/health`` endpoint will respond to a ``GET`` http request with a 200 HTTP status code if healthy or 500 if unhealthy (with a plain text description of why it is unhealthy).

To enable this health endpoint add a ``monitoring`` section to the canton configuration.
As this health check is for the whole process, it is added directly to the ``canton`` configuration rather than for a specific node.

::

  canton {
    monitoring.health {
     server {
        port = 7000
     }

     check {
       type = ping
       participant = participant1
       interval = 30s
     }
  }

This health check will have ``participant1`` "ledger ping" itself every 30 seconds. The process will be considered healthy if the ping is successful.

.. _canton-metrics:

Metrics
-------

Canton uses `dropwizard's metrics <https://metrics.dropwizard.io/>`__ library to report metrics. The metrics library
supports a variety of reporting backends. JMX based reporting (only for testing purposes) can be enabled using

::

    canton.monitoring.metrics.reporters = [{ type = jmx }]

Additionally, metrics can be written to a file

::

    canton.monitoring.metrics.reporters = [{
      type = jmx
    }, {
      type = csv
      directory = "metrics"
      interval = 5s // default
      filters = [{
        contains = "canton"
      }]
    }]

or reported via Graphite (to Grafana) using

::

    canton.monitoring.metrics.reporters = [{
      type = graphite
      address = "localhost" // default
      port = 2003
      prefix.type = hostname // default
      interval = 30s // default
      filters = [{
        contains = "canton"
      }]
    }]

or reported via Prometheus (to Grafana) using

::

    canton.monitoring.metrics.reporters = [{
      type = prometheus
      address = "localhost" // default
      port = 9000 // default
    }]


When using the ``graphite`` or ``csv`` reporters, Canton will periodically evaluate all metrics matching the given filters.
It is therefore advisable to filter for only those metrics that are relevant to you.

In addition to Canton metrics, the process can also report Daml metrics (of the ledger api server). Optionally,
JVM metrics can be included using

::

    canton.monitoring.metrics.report-jvm-metrics = yes // default no

Common gRPC Metrics
~~~~~~~~~~~~~~~~~~~
If a Prometheus metrics reporter is configured, we expose
`these common metrics <https://docs.daml.com/ops/common-metrics.html>`__ for all gRPC endpoints
(i.e., helping you to measure `the four golden signals <https://sre.google/sre-book/monitoring-distributed-systems/#xref_monitoring_golden-signals>`__).

Participant Metrics
~~~~~~~~~~~~~~~~~~~

canton.<domain>.conflict-detection.sequencer-counter-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of conflict detection sequencer counter queue
	* **Description**: The task scheduler will work off tasks according to the timestamp order, scheduling the tasks whenever a new timestamp has been observed. This metric exposes the number of un-processed sequencer messages that will trigger a timestamp advancement.
	* **Type**: Counter

canton.<domain>.conflict-detection.task-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of conflict detection task queue
	* **Description**: The task scheduler will schedule tasks to run at a given timestamp. This metric exposes the number of tasks that are waiting in the task queue for the right time to pass. A huge number does not necessarily indicate a bottleneck; it could also mean that a huge number of tasks have not yet arrived at their execution time.
	* **Type**: Gauge

canton.<domain>.dirty-requests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of conflict detection task queue
	* **Description**: The task scheduler will schedule tasks to run at a given timestamp. This metric exposes the number of tasks that are waiting in the task queue for the right time to pass. A huge number does not necessarily indicate a bottleneck; it could also mean that a huge number of tasks have not yet arrived at their execution time.
	* **Type**: Counter

canton.<domain>.protocol-messages.confirmation-request-creation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Time to create a confirmation request
	* **Description**: The time that the transaction protocol processor needs to create a confirmation request.
	* **Type**: Timer

canton.<domain>.protocol-messages.confirmation-request-size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Confirmation request size
	* **Description**: Records the histogram of the sizes of (transaction) confirmation requests.
	* **Type**: Histogram

canton.<domain>.protocol-messages.transaction-message-receipt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Time to parse a transaction message
	* **Description**: The time that the transaction protocol processor needs to parse and decrypt an incoming confirmation request.
	* **Type**: Timer

canton.<domain>.request-tracker.sequencer-counter-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of record order publisher sequencer counter queue
	* **Description**: Same as for conflict-detection, but measuring the sequencer counter queues for the publishing to the ledger api server according to record time.
	* **Type**: Counter

canton.<domain>.request-tracker.task-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of record order publisher task queue
	* **Description**: The task scheduler will schedule tasks to run at a given timestamp. This metric exposes the number of tasks that are waiting in the task queue for the right time to pass.
	* **Type**: Gauge

canton.<domain>.sequencer-client.application-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of sequentially handling the event application logic
	* **Description**: All events are received sequentially. This handler records the the rate and time it takes the application (participant or domain) to handle the events.
	* **Type**: Timer

canton.<domain>.sequencer-client.delay
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The delay on the event processing
	* **Description**: Every message received from the sequencer carries a timestamp that was assigned by the sequencer when it sequenced the message. This timestamp is called the sequencing timestamp. The component receiving the message on the participant, mediator or topology manager side, is the sequencer client. Upon receiving the message, the sequencer client compares the time difference between the sequencing time and the computers local clock and exposes this difference as the given metric. The difference will include the clock-skew and the processing latency between assigning the timestamp on the sequencer and receiving the message by the recipient. If the difference is large compared to the usual latencies and if clock skew can be ruled out, then it means that the node is still trying to catch up with events that were sequenced by the sequencer a while ago. This can happen after having been offline for a while or if the node is too slow to keep up with the messaging load.
	* **Type**: Gauge

canton.<domain>.sequencer-client.event-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of entire event handling
	* **Description**: Most event handling cost should come from the application-handle. This timer measures the full time (which should just be marginally more than the application handle.
	* **Type**: Timer

canton.<domain>.sequencer-client.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The load on the event subscription
	* **Description**: The event subscription processor is a sequential process. The load is a factor between 0 and 1 describing how much of an existing interval has been spent in the event handler.
	* **Type**: Gauge

canton.<domain>.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter

canton.<domain>.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter

canton.<domain>.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter

canton.<domain>.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer

canton.<domain>.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer

canton.commitments.compute
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Time spent on commitment computations.
	* **Description**: Participant nodes compute bilateral commitments at regular intervals. This metric exposes the time spent on each computation. If the time to compute the metrics starts to exceed the commitment intervals, this likely indicates a problem.
	* **Type**: Timer

canton.db-storage.<service>.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Counter
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer
	* **Instances**: locks, write, general

canton.db-storage.<storage>
^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring duration and rate of accessing the given storage
	* **Description**: Covers both read from and writes to the storage.
	* **Type**: Timer

canton.db-storage.<storage>.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The load on the given storage
	* **Description**: The load is a factor between 0 and 1 describing how much of an existing interval has been spent reading from or writing to the storage.
	* **Type**: Gauge

canton.db-storage.alerts.multi-domain-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the multi-domain event log
	* **Description**: Failed writes to the multi domain event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter

canton.db-storage.alerts.single-dimension-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the event log
	* **Description**: Failed writes to the single dimension event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter

canton.dirty_requests
^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of requests being validated.
	* **Description**: Number of requests that are currently being validated. This also covers requests submitted by other participants. 
	* **Type**: Gauge

canton.max_dirty_requests
^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Configured maximum number of requests currently being validated.
	* **Description**: Configuration for the maximum number of requests that are currently being validated. This also covers requests submitted by other participants. A negative value means no configuration value was provided and no limit is enforced. 
	* **Type**: Gauge

canton.prune
^^^^^^^^^^^^
	* **Summary**: Duration of prune operations.
	* **Description**: This timer exposes the duration of pruning requests from the Canton portion of the ledger.
	* **Type**: Timer

canton.updates-published
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of updates published through the read service to the indexer
	* **Description**: When an update is published through the read service, it has already been committed to the ledger. The indexer will subsequently store the update in a form that allows for querying the ledger efficiently.
	* **Type**: Meter

daml.commands.delayed_submissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the delayed Daml commands.
	* **Description**: The number of Daml commands that have been delayed internally because they have been evaluated to require the ledger time further in the future than the expected latency.
	* **Type**: Meter

daml.commands.failed_command_interpretations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of Daml commands that failed in interpretation.
	* **Description**: The number of Daml commands that have been rejected by the interpreter (e.g. badly authorized action).
	* **Type**: Meter

daml.commands.input_buffer_capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The capacity of the Daml commands queue.
	* **Description**: The maximum number of elements that can be kept in the queue of Daml commands in the Command Service.
	* **Type**: Counter

daml.commands.input_buffer_delay
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The queuing delay for the Daml command queue.
	* **Description**: The queuing delay for the pending Daml commands in the Command Service.
	* **Type**: Timer

daml.commands.input_buffer_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the currently pending Daml commands.
	* **Description**: The number of the currently pending Daml Commands in the Command Service.
	* **Type**: Counter

daml.commands.max_in_flight_capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The maximum number of Daml commands that can await completion.
	* **Description**: The maximum number of Daml commands that can await completion in the Command Service.
	* **Type**: Counter

daml.commands.max_in_flight_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the Daml commands awaiting completion.
	* **Description**: The number of the currently Daml commands awaiting completion in the Command Service.
	* **Type**: Counter

daml.commands.submissions
^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to fully process a Daml command.
	* **Description**: The time to validate and interpret a command before it is handed over to the synchronization services to be finalized (either committed or rejected).
	* **Type**: Timer

daml.commands.submissions_running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the Daml commands that are currently being handled by the ledger api server.
	* **Description**: The number of the Daml commands that are currently being handled by the ledger api server (including validation, interpretation, and handing the transaction over to the synchronization services).
	* **Type**: Counter

daml.commands.valid_submissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The total number of the valid Daml commands.
	* **Description**: The total number of the Daml commands that have passed validation and were sent to interpretation in this ledger api server process.
	* **Type**: Meter

daml.commands.validation
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to validate a Daml command.
	* **Description**: The time to validate a submitted Daml command before is fed to the interpreter.
	* **Type**: Timer

daml.execution.cache.<state_cache>.evicted_weight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sum of weights of cache entries evicted.
	* **Description**: The total weight of the entries evicted from the cache.
	* **Type**: Counter
	* **Instances**: contract_state, key_state

daml.execution.cache.<state_cache>.evictions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the evicted cache entries.
	* **Description**: When an entry is evicted from the cache, the counter is incremented.
	* **Type**: Counter
	* **Instances**: contract_state, key_state

daml.execution.cache.<state_cache>.hits
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache hits.
	* **Description**: When a cache lookup encounters an existing cache entry, the counter is incremented.
	* **Type**: Counter
	* **Instances**: contract_state, key_state

daml.execution.cache.<state_cache>.misses
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache misses.
	* **Description**: When a cache lookup first encounters a missing cache entry, the counter is incremented.
	* **Type**: Counter
	* **Instances**: contract_state, key_state

daml.execution.cache.contract_state.register_update
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent to update the cache.
	* **Description**: The total time spent in sequential update steps of the contract state caches updating logic. This metric is created with debugging purposes in mind.
	* **Type**: Timer

daml.execution.cache.key_state.register_update
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent to update the cache.
	* **Description**: The total time spent in sequential update steps of the contract state caches updating logic. This metric is created with debugging purposes in mind.
	* **Type**: Timer

daml.execution.cache.read_through_not_found
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache read-throughs resulting in not found contracts.
	* **Description**: On cache misses, a read-through query is performed against the Index database. When the contract is not found (as result of this query), this counter is incrmented.
	* **Type**: Counter

daml.execution.cache.resolve_divulgence_lookup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of lookups trying to resolve divulged contracts on active contracts cache hits.
	* **Description**: Divulged contracts are not cached in the contract state caches. On active contract cache hits, where stakeholders are not within the submission readers, a contract activeness lookup is performed against the Index database. On such lookups, this counter is incremented.
	* **Type**: Counter

daml.execution.cache.resolve_full_lookup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of lookups trying to resolve divulged contracts on archived contracts cache hits.
	* **Description**: Divulged contracts are not cached in the contract state caches. On archived contract cache hits, where stakeholders are not within the submission readers, a full contract activeness lookup (including fetching contract arguments) is performed against the Index database. On such lookups, this counter is incremented.
	* **Type**: Counter

daml.execution.engine
^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent executing a Daml command.
	* **Description**: The time spent by the Daml engine executing a Daml command (excluding fetching data).
	* **Type**: Timer

daml.execution.engine_running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of Daml commands currently being executed.
	* **Description**: The number of the commands that are currently being executed by the Daml engine (excluding fetching data).
	* **Type**: Counter

daml.execution.get_lf_package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to fetch individual Daml code packages during interpretation.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple Daml packages. This metric exposes the time needed to fetch the packages that are necessary for interpretation.
	* **Type**: Timer

daml.execution.lookup_active_contract
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to lookup individual active contracts during interpretation.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple active contracts. This metric exposes the time to lookup individual active contracts.
	* **Type**: Timer

daml.execution.lookup_active_contract_count_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the active contracts looked up per Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple active contracts. This metric exposes the number of active contracts that must be looked up to process a Daml command.
	* **Type**: Histogram

daml.execution.lookup_active_contract_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The compound time to lookup all active contracts in a single Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple active contracts. This metric exposes the compound time to lookup all the active contracts in a single Daml command.
	* **Type**: Timer

daml.execution.lookup_contract_key
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to lookup individual contract keys during interpretation.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple contract keys. This metric exposes the time needed to lookup individual contract keys.
	* **Type**: Timer

daml.execution.lookup_contract_key_count_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of contract keys looked up per Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple contract keys. This metric exposes the number of contract keys that must be looked up to process a Daml command.
	* **Type**: Histogram

daml.execution.lookup_contract_key_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The compound time to lookup all contract keys in a single Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple contract keys. This metric exposes the compound time needed to lookup all the contract keys in a single Daml command.
	* **Type**: Timer

daml.execution.retry
^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the interpretation retries.
	* **Description**: The total number of interpretation retries attempted due to mismatching ledger effective time in this ledger api server process.
	* **Type**: Meter

daml.execution.total
^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The overall time spent interpreting a Daml command.
	* **Description**: The time spent interpreting a Daml command in the ledger api server (includes executing Daml and fetching data).
	* **Type**: Timer

daml.execution.total_running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of Daml commands currently being interpreted.
	* **Description**: The number of the commands that are currently being interpreted (includes executing Daml code and fetching data).
	* **Type**: Counter

daml.identity_provider_config_store.<operation>.commit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to perform the SQL query commit.
	* **Description**: This metric measures the time it takes to commit an SQL transaction relating to the <operation>. It roughly corresponds to calling `commit()` on a DB connection.
	* **Type**: Timer
	* **Instances**: list_identity_provider_configs, update_identity_provider_config, delete_identity_provider_config, get_identity_provider_config, create_identity_provider_config

daml.identity_provider_config_store.<operation>.compression
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to decompress the SQL query result.
	* **Description**: Some index database queries that target contracts involve a decompression step. For such queries this metric represents the time it takes to decompress contract arguments retrieved from the database.
	* **Type**: Timer
	* **Instances**: list_identity_provider_configs, update_identity_provider_config, delete_identity_provider_config, get_identity_provider_config, create_identity_provider_config

daml.identity_provider_config_store.<operation>.exec
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query and read the result.
	* **Description**: This metric encompasses the time measured by `query` and `commit` metrics. Additionally it includes the time needed to obtain the DB connection, optionally roll it back and close the connection at the end.
	* **Type**: Timer
	* **Instances**: list_identity_provider_configs, update_identity_provider_config, delete_identity_provider_config, get_identity_provider_config, create_identity_provider_config

daml.identity_provider_config_store.<operation>.query
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query.
	* **Description**: This metric measures the time it takes to execute a block of code (on a decidated executor) related to the <operation> that can issue multiple SQL statements such that all run in a single DB transaction (either commtted or aborted).
	* **Type**: Timer
	* **Instances**: list_identity_provider_configs, update_identity_provider_config, delete_identity_provider_config, get_identity_provider_config, create_identity_provider_config

daml.identity_provider_config_store.<operation>.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Instances**: list_identity_provider_configs, update_identity_provider_config, delete_identity_provider_config, get_identity_provider_config, create_identity_provider_config

daml.identity_provider_config_store.<operation>.wait
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to acquire a connection to the database.
	* **Description**: SQL statements are run in a dedicated executor. This metric measures the time it takes between creating the SQL statement corresponding to the <operation> and the point when it starts running on the dedicated executor.
	* **Type**: Timer
	* **Instances**: list_identity_provider_configs, update_identity_provider_config, delete_identity_provider_config, get_identity_provider_config, create_identity_provider_config

daml.identity_provider_config_store.cache_by_issuer.evicted_weight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sum of weights of cache entries evicted.
	* **Description**: The total weight of the entries evicted from the cache.
	* **Type**: Counter

daml.identity_provider_config_store.cache_by_issuer.evictions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the evicted cache entries.
	* **Description**: When an entry is evicted from the cache, the counter is incremented.
	* **Type**: Counter

daml.identity_provider_config_store.cache_by_issuer.hits
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache hits.
	* **Description**: When a cache lookup encounters an existing cache entry, the counter is incremented.
	* **Type**: Counter

daml.identity_provider_config_store.cache_by_issuer.misses
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache misses.
	* **Description**: When a cache lookup first encounters a missing cache entry, the counter is incremented.
	* **Type**: Counter

daml.index.active_contracts_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for active contracts requests.
	* **Description**: An Akka stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting active contracts that transactions satisfying a given predicate.
	* **Type**: Counter

daml.index.completions_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for completions requests.
	* **Description**: An Akka stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting the completed commands in a specific period of time.
	* **Type**: Counter

daml.index.db.<operation>.commit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to perform the SQL query commit.
	* **Description**: This metric measures the time it takes to commit an SQL transaction relating to the <operation>. It roughly corresponds to calling `commit()` on a DB connection.
	* **Type**: Timer
	* **Instances**: initialize_metering_aggregator, metering_aggregator, load_string_interning_entries, get_acs_event_sequential_id_range, get_event_sequential_id_range, get_active_contract_batch, get_active_contract_ids, get_active_contracts, lookup_transaction_tree_by_id, get_transaction_trees, lookup_flat_transaction_by_id, get_flat_transactions, get_nonconsuming_event_payloads_for_tree_transactions, get_consuming_event_payloads_for_tree_transactions, get_create_event_payloads_for_tree_transactions, get_nonconsuming_event_ids_for_informee_for_tree_transactions, get_consuming_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_consuming_event_ids_for_stakeholder_for_tree_transactions, get_create_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_create_event_ids_for_stakeholder_for_tree_transactions, get_consuming_event_payloads_for_flat_transactions, get_create_event_payloads_for_flat_transactions, get_consuming_event_ids_for_flat_transactions, get_create_event_ids_for_flat_transactions, lookup_contract_by_key, lookup_active_contract, prune, load_package_entries, store_package_entry, load_archive, load_packages, load_all_parties, load_parties, store_rejection, store_ledger_entry, load_party_entries, store_party_entry, store_configuration_entry, load_configuration_entries, lookup_configuration, initialize_ledger_parameters, get_ledger_end, get_participant_id, get_ledger_id, get_completions, all

daml.index.db.<operation>.compression
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to decompress the SQL query result.
	* **Description**: Some index database queries that target contracts involve a decompression step. For such queries this metric represents the time it takes to decompress contract arguments retrieved from the database.
	* **Type**: Timer
	* **Instances**: initialize_metering_aggregator, metering_aggregator, load_string_interning_entries, get_acs_event_sequential_id_range, get_event_sequential_id_range, get_active_contract_batch, get_active_contract_ids, get_active_contracts, lookup_transaction_tree_by_id, get_transaction_trees, lookup_flat_transaction_by_id, get_flat_transactions, get_nonconsuming_event_payloads_for_tree_transactions, get_consuming_event_payloads_for_tree_transactions, get_create_event_payloads_for_tree_transactions, get_nonconsuming_event_ids_for_informee_for_tree_transactions, get_consuming_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_consuming_event_ids_for_stakeholder_for_tree_transactions, get_create_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_create_event_ids_for_stakeholder_for_tree_transactions, get_consuming_event_payloads_for_flat_transactions, get_create_event_payloads_for_flat_transactions, get_consuming_event_ids_for_flat_transactions, get_create_event_ids_for_flat_transactions, lookup_contract_by_key, lookup_active_contract, prune, load_package_entries, store_package_entry, load_archive, load_packages, load_all_parties, load_parties, store_rejection, store_ledger_entry, load_party_entries, store_party_entry, store_configuration_entry, load_configuration_entries, lookup_configuration, initialize_ledger_parameters, get_ledger_end, get_participant_id, get_ledger_id, get_completions, all

daml.index.db.<operation>.exec
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query and read the result.
	* **Description**: This metric encompasses the time measured by `query` and `commit` metrics. Additionally it includes the time needed to obtain the DB connection, optionally roll it back and close the connection at the end.
	* **Type**: Timer
	* **Instances**: initialize_metering_aggregator, metering_aggregator, load_string_interning_entries, get_acs_event_sequential_id_range, get_event_sequential_id_range, get_active_contract_batch, get_active_contract_ids, get_active_contracts, lookup_transaction_tree_by_id, get_transaction_trees, lookup_flat_transaction_by_id, get_flat_transactions, get_nonconsuming_event_payloads_for_tree_transactions, get_consuming_event_payloads_for_tree_transactions, get_create_event_payloads_for_tree_transactions, get_nonconsuming_event_ids_for_informee_for_tree_transactions, get_consuming_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_consuming_event_ids_for_stakeholder_for_tree_transactions, get_create_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_create_event_ids_for_stakeholder_for_tree_transactions, get_consuming_event_payloads_for_flat_transactions, get_create_event_payloads_for_flat_transactions, get_consuming_event_ids_for_flat_transactions, get_create_event_ids_for_flat_transactions, lookup_contract_by_key, lookup_active_contract, prune, load_package_entries, store_package_entry, load_archive, load_packages, load_all_parties, load_parties, store_rejection, store_ledger_entry, load_party_entries, store_party_entry, store_configuration_entry, load_configuration_entries, lookup_configuration, initialize_ledger_parameters, get_ledger_end, get_participant_id, get_ledger_id, get_completions, all

daml.index.db.<operation>.query
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query.
	* **Description**: This metric measures the time it takes to execute a block of code (on a decidated executor) related to the <operation> that can issue multiple SQL statements such that all run in a single DB transaction (either commtted or aborted).
	* **Type**: Timer
	* **Instances**: initialize_metering_aggregator, metering_aggregator, load_string_interning_entries, get_acs_event_sequential_id_range, get_event_sequential_id_range, get_active_contract_batch, get_active_contract_ids, get_active_contracts, lookup_transaction_tree_by_id, get_transaction_trees, lookup_flat_transaction_by_id, get_flat_transactions, get_nonconsuming_event_payloads_for_tree_transactions, get_consuming_event_payloads_for_tree_transactions, get_create_event_payloads_for_tree_transactions, get_nonconsuming_event_ids_for_informee_for_tree_transactions, get_consuming_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_consuming_event_ids_for_stakeholder_for_tree_transactions, get_create_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_create_event_ids_for_stakeholder_for_tree_transactions, get_consuming_event_payloads_for_flat_transactions, get_create_event_payloads_for_flat_transactions, get_consuming_event_ids_for_flat_transactions, get_create_event_ids_for_flat_transactions, lookup_contract_by_key, lookup_active_contract, prune, load_package_entries, store_package_entry, load_archive, load_packages, load_all_parties, load_parties, store_rejection, store_ledger_entry, load_party_entries, store_party_entry, store_configuration_entry, load_configuration_entries, lookup_configuration, initialize_ledger_parameters, get_ledger_end, get_participant_id, get_ledger_id, get_completions, all

daml.index.db.<operation>.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Instances**: initialize_metering_aggregator, metering_aggregator, load_string_interning_entries, get_acs_event_sequential_id_range, get_event_sequential_id_range, get_active_contract_batch, get_active_contract_ids, get_active_contracts, lookup_transaction_tree_by_id, get_transaction_trees, lookup_flat_transaction_by_id, get_flat_transactions, get_nonconsuming_event_payloads_for_tree_transactions, get_consuming_event_payloads_for_tree_transactions, get_create_event_payloads_for_tree_transactions, get_nonconsuming_event_ids_for_informee_for_tree_transactions, get_consuming_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_consuming_event_ids_for_stakeholder_for_tree_transactions, get_create_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_create_event_ids_for_stakeholder_for_tree_transactions, get_consuming_event_payloads_for_flat_transactions, get_create_event_payloads_for_flat_transactions, get_consuming_event_ids_for_flat_transactions, get_create_event_ids_for_flat_transactions, lookup_contract_by_key, lookup_active_contract, prune, load_package_entries, store_package_entry, load_archive, load_packages, load_all_parties, load_parties, store_rejection, store_ledger_entry, load_party_entries, store_party_entry, store_configuration_entry, load_configuration_entries, lookup_configuration, initialize_ledger_parameters, get_ledger_end, get_participant_id, get_ledger_id, get_completions, all

daml.index.db.<operation>.wait
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to acquire a connection to the database.
	* **Description**: SQL statements are run in a dedicated executor. This metric measures the time it takes between creating the SQL statement corresponding to the <operation> and the point when it starts running on the dedicated executor.
	* **Type**: Timer
	* **Instances**: initialize_metering_aggregator, metering_aggregator, load_string_interning_entries, get_acs_event_sequential_id_range, get_event_sequential_id_range, get_active_contract_batch, get_active_contract_ids, get_active_contracts, lookup_transaction_tree_by_id, get_transaction_trees, lookup_flat_transaction_by_id, get_flat_transactions, get_nonconsuming_event_payloads_for_tree_transactions, get_consuming_event_payloads_for_tree_transactions, get_create_event_payloads_for_tree_transactions, get_nonconsuming_event_ids_for_informee_for_tree_transactions, get_consuming_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_consuming_event_ids_for_stakeholder_for_tree_transactions, get_create_event_ids_for_nonstakeholderinformee_for_tree_transactions, get_create_event_ids_for_stakeholder_for_tree_transactions, get_consuming_event_payloads_for_flat_transactions, get_create_event_payloads_for_flat_transactions, get_consuming_event_ids_for_flat_transactions, get_create_event_ids_for_flat_transactions, lookup_contract_by_key, lookup_active_contract, prune, load_package_entries, store_package_entry, load_archive, load_packages, load_all_parties, load_parties, store_rejection, store_ledger_entry, load_party_entries, store_party_entry, store_configuration_entry, load_configuration_entries, lookup_configuration, initialize_ledger_parameters, get_ledger_end, get_participant_id, get_ledger_id, get_completions, all

daml.index.db.compression.create_argument_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed arguments of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed arguments of a create event.
	* **Type**: Histogram

daml.index.db.compression.create_argument_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed argument of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of decompressed arguments of a create event.
	* **Type**: Histogram

daml.index.db.compression.create_key_value_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed key value of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed key value of a create event.
	* **Type**: Histogram

daml.index.db.compression.create_key_value_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed key value of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of decompressed key value of a create event.
	* **Type**: Histogram

daml.index.db.compression.exercise_argument_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed argument of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed arguments of an exercise event.
	* **Type**: Histogram

daml.index.db.compression.exercise_argument_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed argument of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of decompressed arguments of an exercise event.
	* **Type**: Histogram

daml.index.db.compression.exercise_result_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed result of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed result of an exercise event.
	* **Type**: Histogram

daml.index.db.compression.exercise_result_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed result of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed result of an exercise event.
	* **Type**: Histogram

daml.index.db.lookup_active_contract
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent fetching a contract using its id.
	* **Description**: This metric exposes the time spent fetching a contract using its id from the index db. It is then used by the Daml interpreter when evaluating a command into a transaction.
	* **Type**: Timer

daml.index.db.lookup_key
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent looking up a contract using its key.
	* **Description**: This metric exposes the time spent looking up a contract using its key in the index db. It is then used by the Daml interpreter when evaluating a command into a transaction.
	* **Type**: Timer

daml.index.db.threadpool.connection.<server_role>.completed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks completed in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Meter

daml.index.db.threadpool.connection.<server_role>.duration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The duration of a task is running in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Timer

daml.index.db.threadpool.connection.<server_role>.idle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time that a task is idle in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Timer

daml.index.db.threadpool.connection.<server_role>.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks running in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Counter

daml.index.db.threadpool.connection.<server_role>.submitted
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks submitted to an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Meter

daml.index.db.translation.get_lf_package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to deserialize and decode a Daml-LF archive.
	* **Description**: A Daml archive before it can be used in the interpretation needs to be deserialized and decoded, in other words converted into the in-memory representation. This metric represents time necessary to do that.
	* **Type**: Timer

daml.index.flat_transactions_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for flat transactions requests.
	* **Description**: An Akka stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting flat transactions in a specific period of time that satisfy a given predicate.
	* **Type**: Counter

daml.index.ledger_end_sequential_id
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sequential id of the current ledger end kept in memory.
	* **Description**: The ledger end's sequential id is a monotonically increasing integer value representing the sequential id ascribed to the most recent ledger event ingested by the index db. Please note, that only a subset of all ledger events are ingested and given a sequential id. These are: creates, consuming exercises, non-consuming exercises and divulgence events. This value can be treated as a counter of all such events visible to a given participant. This metric exposes the latest ledger end's sequential id registered in the in-memory data set.
	* **Type**: Gauge

daml.index.lf_value.compute_interface_view
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to compute an interface view while serving transaction streams.
	* **Description**: Transaction API allows clients to request events by interface-id. When an event matches the interface - an interface view is computed, which adds to the latency. This metric represents the time for each such computation.
	* **Type**: Timer

daml.index.package_metadata.decode_archive
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to decode a package archive to extract metadata information.
	* **Description**: This metric represents the time spent scanning each uploaded package for new interfaces and corresponding templates.
	* **Type**: Timer

daml.index.package_metadata.view_init
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to initialize package metadata view.
	* **Description**: As the mapping between interfaces and templates is not persistent - it is computed for each Indexer restart by loading all packages which were ever uploaded and scanning them to extract metadata information.
	* **Type**: Timer

daml.index.transaction_trees_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for transaction trees requests.
	* **Description**: An Akka stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting transaction trees.
	* **Type**: Counter

daml.indexer.current_record_time_lag
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The lag between the record time of a transaction and the wall-clock time registered at the ingestion phase to the index db (in milliseconds).
	* **Description**: Depending on the systemic clock skew between different machines, this value can be negative.
	* **Type**: Gauge

daml.indexer.last_received_offset
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: A string value representing the last ledger offset ingested by the index db.
	* **Description**: It is only available on metrics backends that support strings. In particular, it is not available in Prometheus.
	* **Type**: Gauge

daml.indexer.last_received_record_time
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time of the last event ingested by the index db (in milliseconds since EPOCH).
	* **Description**: The last received record time is a monotonically increasing integer value that represents the record time of the last event ingested by the index db. It is measured in milliseconds since the EPOCH time.
	* **Type**: Gauge

daml.indexer.ledger_end_sequential_id
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sequential id of the current ledger end kept in the database.
	* **Description**: The ledger end's sequential id is a monotonically increasing integer value representing the sequential id ascribed to the most recent ledger event ingested by the index db. Please note, that only a subset of all ledger events are ingested and given a sequential id. These are: creates, consuming exercises, non-consuming exercises and divulgence events. This value can be treated as a counter of all such events visible to a given participant. This metric exposes the latest ledger end's sequential id registered in the database.
	* **Type**: Gauge

daml.indexer.metered_events
^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of events that will be metered
	* **Description**: Represents the number of events that will be included in the metering report. This is an estimate of the total number and not a substitute for the metering report.
	* **Type**: Meter

daml.lapi.<service_method>
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent serving a ledger api grpc request.
	* **Description**: The time spent servicing a particular type of ledger api grpc request. Unary methods report the time to serve the request, streaming methods measure the time to return the first response.
	* **Type**: Timer

daml.lapi.return_status.<gRPC_status_code>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of ledger api grpc responses with this code.
	* **Description**: This group of metrics counts the total number gRPC status codes returned by the ledger api.
	* **Type**: Counter

daml.lapi.streams.acs_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the active contracts sent by the ledger api.
	* **Description**: The total number of active contracts sent over the ledger api streams to all clients.
	* **Type**: Counter

daml.lapi.streams.active
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the actice streams served by the ledger api.
	* **Description**: The number of ledger api streams currently being served to all clients.
	* **Type**: Counter

daml.lapi.streams.completions_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the command completions sent by the ledger api.
	* **Description**: The total number of completions sent over the ledger api streams to all clients.
	* **Type**: Counter

daml.lapi.streams.transaction_trees_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the transaction trees sent over the ledger api.
	* **Description**: The total number of the transaction trees sent over the ledger api streams to all clients.
	* **Type**: Counter

daml.lapi.streams.transactions_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the flat transactions sent over the ledger api.
	* **Description**: The total number of the flat transaction sent over the ledger api streams to all clients.
	* **Type**: Counter

daml.lapi.threadpool.<threadpool>.completed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks completed in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Meter

daml.lapi.threadpool.<threadpool>.duration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The duration of a task is running in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Timer

daml.lapi.threadpool.<threadpool>.idle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time that a task is idle in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Timer

daml.lapi.threadpool.<threadpool>.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks running in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Counter

daml.lapi.threadpool.<threadpool>.submitted
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks submitted to an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Meter

daml.parallel_indexer.<stage>.commit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to perform the SQL query commit.
	* **Description**: This metric measures the time it takes to commit an SQL transaction relating to the <operation>. It roughly corresponds to calling `commit()` on a DB connection.
	* **Type**: Timer
	* **Instances**: tail_ingestion, ingestion, initialization

daml.parallel_indexer.<stage>.compression
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to decompress the SQL query result.
	* **Description**: Some index database queries that target contracts involve a decompression step. For such queries this metric represents the time it takes to decompress contract arguments retrieved from the database.
	* **Type**: Timer
	* **Instances**: tail_ingestion, ingestion, initialization

daml.parallel_indexer.<stage>.exec
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query and read the result.
	* **Description**: This metric encompasses the time measured by `query` and `commit` metrics. Additionally it includes the time needed to obtain the DB connection, optionally roll it back and close the connection at the end.
	* **Type**: Timer
	* **Instances**: tail_ingestion, ingestion, initialization

daml.parallel_indexer.<stage>.executor.completed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks completed in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Meter
	* **Instances**: batching, inputmapping

daml.parallel_indexer.<stage>.executor.duration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The duration of a task is running in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Timer
	* **Instances**: batching, inputmapping

daml.parallel_indexer.<stage>.executor.idle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time that a task is idle in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Timer
	* **Instances**: batching, inputmapping

daml.parallel_indexer.<stage>.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks running in an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Counter
	* **Instances**: batching, inputmapping

daml.parallel_indexer.<stage>.executor.submitted
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks submitted to an instrumented executor.
	* **Description**: Thread pools within the ledger api server are instrumented using the dropwizard's InstrumentedExecutorService: https://www.javadoc.io/doc/io.dropwizard.metrics/metrics-core/latest/com/codahale/metrics/InstrumentedExecutorService.html
	* **Type**: Meter
	* **Instances**: batching, inputmapping

daml.parallel_indexer.<stage>.query
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query.
	* **Description**: This metric measures the time it takes to execute a block of code (on a decidated executor) related to the <operation> that can issue multiple SQL statements such that all run in a single DB transaction (either commtted or aborted).
	* **Type**: Timer
	* **Instances**: tail_ingestion, ingestion, initialization

daml.parallel_indexer.<stage>.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Instances**: tail_ingestion, ingestion, initialization

daml.parallel_indexer.<stage>.wait
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to acquire a connection to the database.
	* **Description**: SQL statements are run in a dedicated executor. This metric measures the time it takes between creating the SQL statement corresponding to the <operation> and the point when it starts running on the dedicated executor.
	* **Type**: Timer
	* **Instances**: tail_ingestion, ingestion, initialization

daml.parallel_indexer.input_buffer_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of elements in the queue in front of the indexer.
	* **Description**: The indexer has a queue in order to absorb the back pressure and facilitate batch formation during the database ingestion.
	* **Type**: Counter

daml.parallel_indexer.inputmapping.batch_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The batch sizes in the indexer.
	* **Description**: The number of state updates contained in a batch used in the indexer for database submission.
	* **Type**: Histogram

daml.parallel_indexer.output_batched_buffer_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the queue between the indexer and the in-memory state updating flow.
	* **Description**: This counter counts batches of updates passed to the in-memory flow. Batches are dynamically-sized based on amount of backpressure exerted by the downstream stages of the flow.
	* **Type**: Counter

daml.parallel_indexer.seqmapping.duration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The duration of the seq-mapping stage.
	* **Description**: The time that a batch of updates spends in the seq-mapping stage of the indexer.
	* **Type**: Timer

daml.parallel_indexer.updates
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the state updates persisted to the database.
	* **Description**: The number of the state updates persisted to the database. There are updates such as accepted transactions, configuration changes, package uloads, party allocations, rejections, etc.
	* **Type**: Counter

daml.party_record_store.<operation>.commit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to perform the SQL query commit.
	* **Description**: This metric measures the time it takes to commit an SQL transaction relating to the <operation>. It roughly corresponds to calling `commit()` on a DB connection.
	* **Type**: Timer
	* **Instances**: update_party_record, create_party_record, get_party_record

daml.party_record_store.<operation>.compression
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to decompress the SQL query result.
	* **Description**: Some index database queries that target contracts involve a decompression step. For such queries this metric represents the time it takes to decompress contract arguments retrieved from the database.
	* **Type**: Timer
	* **Instances**: update_party_record, create_party_record, get_party_record

daml.party_record_store.<operation>.exec
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query and read the result.
	* **Description**: This metric encompasses the time measured by `query` and `commit` metrics. Additionally it includes the time needed to obtain the DB connection, optionally roll it back and close the connection at the end.
	* **Type**: Timer
	* **Instances**: update_party_record, create_party_record, get_party_record

daml.party_record_store.<operation>.query
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query.
	* **Description**: This metric measures the time it takes to execute a block of code (on a decidated executor) related to the <operation> that can issue multiple SQL statements such that all run in a single DB transaction (either commtted or aborted).
	* **Type**: Timer
	* **Instances**: update_party_record, create_party_record, get_party_record

daml.party_record_store.<operation>.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Instances**: update_party_record, create_party_record, get_party_record

daml.party_record_store.<operation>.wait
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to acquire a connection to the database.
	* **Description**: SQL statements are run in a dedicated executor. This metric measures the time it takes between creating the SQL statement corresponding to the <operation> and the point when it starts running on the dedicated executor.
	* **Type**: Timer
	* **Instances**: update_party_record, create_party_record, get_party_record

daml.services.index.<operation>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to execute an index service operation.
	* **Description**: The index service is an internal component responsible for access to the index db data. Its operations are invoked whenever a client request received over the ledger api requires access to the index db. This metric captures time statistics of such operations.
	* **Type**: Timer
	* **Instances**: get_transaction_metering, prune, configuration_entries, lookup_configuration, party_entries, list_known_parties, get_parties, get_participant_id, lookup_maximum_ledger_time, lookup_contract_key, lookup_contract_state_without_divulgence, lookup_active_contract, get_active_contracts, get_transaction_tree_by_id, get_transaction_by_id, transaction_trees, transactions, get_completions_limited, get_completions, current_ledger_end, get_ledger_configuration, package_entries, get_lf_archive, list_lf_packages

daml.services.index.in_memory_fan_out_buffer.prune
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to remove all elements from the in-memory fan-out buffer.
	* **Description**: It is possible to remove the oldest entries of the in-memory fan out buffer. This metric exposes the time needed to prune the buffer.
	* **Type**: Timer

daml.services.index.in_memory_fan_out_buffer.push
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to add a new event into the buffer.
	* **Description**: The in-memory fan-out buffer is a buffer that stores the last ingested maxBufferSize accepted and rejected submission updates as TransactionLogUpdate. It allows bypassing IndexDB persistence fetches for recent updates for flat and transaction tree streams, command completion streams and by-event-id and by-transaction-id flat and transaction tree lookups. This metric exposes the time spent on adding a new event into the buffer.
	* **Type**: Timer

daml.services.index.in_memory_fan_out_buffer.size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the in-memory fan-out buffer.
	* **Description**: The actual size of the in-memory fan-out buffer. This metric is mostly targeted for debugging purposes.
	* **Type**: Histogram

daml.services.read.<operation>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to execute a read service operation.
	* **Description**: The read service is an internal interface for reading the events from the synchronization interfaces. The metrics expose the time needed to execute each operation.
	* **Type**: Timer
	* **Instances**: state_updates, get_ledger_initial_conditions

daml.services.write.<operation>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to execute a write service operation.
	* **Description**: The write service is an internal interface for changing the state through the synchronization services. The methods in this interface are all methods that are supported uniformly across all ledger implementations. This metric exposes the time needed to execute each operation.
	* **Type**: Timer
	* **Instances**: prune, submit_configuration, allocate_party, upload_packages, submit_transaction_running, submit_transaction

daml.services.write.submit_transaction.count
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of submitted transactions by the write service.
	* **Description**: The write service is an internal interface for changing the state through the synchronization services. The methods in this interface are all methods that are supported uniformly across all ledger implementations. This metric exposes the total number of the sumbitted transactions.
	* **Type**: Timer

daml.user_management.<operation>.commit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to perform the SQL query commit.
	* **Description**: This metric measures the time it takes to commit an SQL transaction relating to the <operation>. It roughly corresponds to calling `commit()` on a DB connection.
	* **Type**: Timer
	* **Instances**: list_users, revoke_rights, grant_rights, update_user, delete_user, create_user, get_user_info

daml.user_management.<operation>.compression
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to decompress the SQL query result.
	* **Description**: Some index database queries that target contracts involve a decompression step. For such queries this metric represents the time it takes to decompress contract arguments retrieved from the database.
	* **Type**: Timer
	* **Instances**: list_users, revoke_rights, grant_rights, update_user, delete_user, create_user, get_user_info

daml.user_management.<operation>.exec
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query and read the result.
	* **Description**: This metric encompasses the time measured by `query` and `commit` metrics. Additionally it includes the time needed to obtain the DB connection, optionally roll it back and close the connection at the end.
	* **Type**: Timer
	* **Instances**: list_users, revoke_rights, grant_rights, update_user, delete_user, create_user, get_user_info

daml.user_management.<operation>.query
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query.
	* **Description**: This metric measures the time it takes to execute a block of code (on a decidated executor) related to the <operation> that can issue multiple SQL statements such that all run in a single DB transaction (either commtted or aborted).
	* **Type**: Timer
	* **Instances**: list_users, revoke_rights, grant_rights, update_user, delete_user, create_user, get_user_info

daml.user_management.<operation>.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Instances**: list_users, revoke_rights, grant_rights, update_user, delete_user, create_user, get_user_info

daml.user_management.<operation>.wait
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to acquire a connection to the database.
	* **Description**: SQL statements are run in a dedicated executor. This metric measures the time it takes between creating the SQL statement corresponding to the <operation> and the point when it starts running on the dedicated executor.
	* **Type**: Timer
	* **Instances**: list_users, revoke_rights, grant_rights, update_user, delete_user, create_user, get_user_info

daml.user_management.cache.evicted_weight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sum of weights of cache entries evicted.
	* **Description**: The total weight of the entries evicted from the cache.
	* **Type**: Counter

daml.user_management.cache.evictions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the evicted cache entries.
	* **Description**: When an entry is evicted from the cache, the counter is incremented.
	* **Type**: Counter

daml.user_management.cache.hits
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache hits.
	* **Description**: When a cache lookup encounters an existing cache entry, the counter is incremented.
	* **Type**: Counter

daml.user_management.cache.misses
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache misses.
	* **Description**: When a cache lookup first encounters a missing cache entry, the counter is incremented.
	* **Type**: Counter

test.db.commit
^^^^^^^^^^^^^^
	* **Summary**: The time needed to perform the SQL query commit.
	* **Description**: This metric measures the time it takes to commit an SQL transaction relating to the <operation>. It roughly corresponds to calling `commit()` on a DB connection.
	* **Type**: Timer

test.db.compression
^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to decompress the SQL query result.
	* **Description**: Some index database queries that target contracts involve a decompression step. For such queries this metric represents the time it takes to decompress contract arguments retrieved from the database.
	* **Type**: Timer

test.db.exec
^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query and read the result.
	* **Description**: This metric encompasses the time measured by `query` and `commit` metrics. Additionally it includes the time needed to obtain the DB connection, optionally roll it back and close the connection at the end.
	* **Type**: Timer

test.db.query
^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query.
	* **Description**: This metric measures the time it takes to execute a block of code (on a decidated executor) related to the <operation> that can issue multiple SQL statements such that all run in a single DB transaction (either commtted or aborted).
	* **Type**: Timer

test.db.translation
^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer

test.db.wait
^^^^^^^^^^^^
	* **Summary**: The time needed to acquire a connection to the database.
	* **Description**: SQL statements are run in a dedicated executor. This metric measures the time it takes between creating the SQL statement corresponding to the <operation> and the point when it starts running on the dedicated executor.
	* **Type**: Timer


Domain Metrics
~~~~~~~~~~~~~~

canton.<component>.sequencer-client.application-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of sequentially handling the event application logic
	* **Description**: All events are received sequentially. This handler records the the rate and time it takes the application (participant or domain) to handle the events.
	* **Type**: Timer
	* **Instances**: topology-manager, mediator, sequencer

canton.<component>.sequencer-client.delay
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The delay on the event processing
	* **Description**: Every message received from the sequencer carries a timestamp that was assigned by the sequencer when it sequenced the message. This timestamp is called the sequencing timestamp. The component receiving the message on the participant, mediator or topology manager side, is the sequencer client. Upon receiving the message, the sequencer client compares the time difference between the sequencing time and the computers local clock and exposes this difference as the given metric. The difference will include the clock-skew and the processing latency between assigning the timestamp on the sequencer and receiving the message by the recipient. If the difference is large compared to the usual latencies and if clock skew can be ruled out, then it means that the node is still trying to catch up with events that were sequenced by the sequencer a while ago. This can happen after having been offline for a while or if the node is too slow to keep up with the messaging load.
	* **Type**: Gauge
	* **Instances**: topology-manager, mediator, sequencer

canton.<component>.sequencer-client.event-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of entire event handling
	* **Description**: Most event handling cost should come from the application-handle. This timer measures the full time (which should just be marginally more than the application handle.
	* **Type**: Timer
	* **Instances**: topology-manager, mediator, sequencer

canton.<component>.sequencer-client.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The load on the event subscription
	* **Description**: The event subscription processor is a sequential process. The load is a factor between 0 and 1 describing how much of an existing interval has been spent in the event handler.
	* **Type**: Gauge
	* **Instances**: topology-manager, mediator, sequencer

canton.db-storage.<service>.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Counter
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer
	* **Instances**: locks, write, general

canton.db-storage.<storage>
^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring duration and rate of accessing the given storage
	* **Description**: Covers both read from and writes to the storage.
	* **Type**: Timer

canton.db-storage.<storage>.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The load on the given storage
	* **Description**: The load is a factor between 0 and 1 describing how much of an existing interval has been spent reading from or writing to the storage.
	* **Type**: Gauge

canton.db-storage.alerts.multi-domain-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the multi-domain event log
	* **Description**: Failed writes to the multi domain event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter

canton.db-storage.alerts.single-dimension-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the event log
	* **Description**: Failed writes to the single dimension event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter

canton.mediator.outstanding-requests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of currently outstanding requests
	* **Description**: This metric provides the number of currently open requests registered with the mediator.
	* **Type**: Gauge

canton.mediator.requests
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of totally processed requests
	* **Description**: This metric provides the number of totally processed requests since the system has been started.
	* **Type**: Meter

canton.mediator.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter

canton.mediator.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter

canton.mediator.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter

canton.mediator.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer

canton.mediator.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer

canton.sequencer.db-storage.<storage>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring duration and rate of accessing the given storage
	* **Description**: Covers both read from and writes to the storage.
	* **Type**: Timer

canton.sequencer.db-storage.<storage>.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The load on the given storage
	* **Description**: The load is a factor between 0 and 1 describing how much of an existing interval has been spent reading from or writing to the storage.
	* **Type**: Gauge

canton.sequencer.db-storage.alerts.multi-domain-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the multi-domain event log
	* **Description**: Failed writes to the multi domain event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter

canton.sequencer.db-storage.alerts.single-dimension-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the event log
	* **Description**: Failed writes to the single dimension event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter

canton.sequencer.db-storage.general.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter

canton.sequencer.db-storage.general.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Counter

canton.sequencer.db-storage.general.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer

canton.sequencer.db-storage.locks.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter

canton.sequencer.db-storage.locks.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Counter

canton.sequencer.db-storage.locks.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer

canton.sequencer.db-storage.write.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter

canton.sequencer.db-storage.write.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Counter

canton.sequencer.db-storage.write.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer

canton.sequencer.processed
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of messages processed by the sequencer
	* **Description**: This metric measures the number of successfully validated messages processed by the sequencer since the start of this process.
	* **Type**: Meter

canton.sequencer.processed-bytes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of message bytes processed by the sequencer
	* **Description**: This metric measures the total number of message bytes processed by the sequencer.
	* **Type**: Meter

canton.sequencer.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter

canton.sequencer.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter

canton.sequencer.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter

canton.sequencer.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer

canton.sequencer.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer

canton.sequencer.subscriptions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of active sequencer subscriptions
	* **Description**: This metric indicates the number of active subscriptions currently open and actively served subscriptions at the sequencer.
	* **Type**: Gauge

canton.sequencer.time-requests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of time requests received by the sequencer
	* **Description**: When a Participant needs to know the domain time it will make a request for a time proof to be sequenced. It would be normal to see a small number of these being sequenced, however if this number becomes a significant portion of the total requests to the sequencer it could indicate that the strategy for requesting times may need to be revised to deal with different clock skews and latencies between the sequencer and participants.
	* **Type**: Meter

canton.topology-manager.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter

canton.topology-manager.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter

canton.topology-manager.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter

canton.topology-manager.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer

canton.topology-manager.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer


