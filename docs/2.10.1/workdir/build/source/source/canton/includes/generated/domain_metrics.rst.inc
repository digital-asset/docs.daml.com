canton.<component>.sequencer-client.application-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of sequentially handling the event application logic
	* **Description**: All events are received sequentially. This handler records the the rate and time it takes the application (participant or domain) to handle the events.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Instances**: topology-manager, mediator, sequencer

canton.<component>.sequencer-client.delay
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The delay on the event processing
	* **Description**: Every message received from the sequencer carries a timestamp that was assigned by the sequencer when it sequenced the message. This timestamp is called the sequencing timestamp. The component receiving the message on the participant, mediator or topology manager side, is the sequencer client. Upon receiving the message, the sequencer client compares the time difference between the sequencing time and the computers local clock and exposes this difference as the given metric. The difference will include the clock-skew and the processing latency between assigning the timestamp on the sequencer and receiving the message by the recipient. If the difference is large compared to the usual latencies and if clock skew can be ruled out, then it means that the node is still trying to catch up with events that were sequenced by the sequencer a while ago. This can happen after having been offline for a while or if the node is too slow to keep up with the messaging load.
	* **Type**: Gauge
	* **Qualification**: Debug
	* **Instances**: topology-manager, mediator, sequencer

canton.<component>.sequencer-client.event-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of entire event handling
	* **Description**: Most event handling cost should come from the application-handle. This timer measures the full time (which should just be marginally more than the application handle.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Instances**: topology-manager, mediator, sequencer

canton.db-storage.<service>.executor.exectime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Execution time metric for database tasks
	* **Description**: The time a task is running on the database is measured using this metric.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Load of database pool
	* **Description**: Database queries run as tasks on an async executor. This metric shows the current number of queries running in parallel divided by the number database connections for this database connection pool.
	* **Type**: Gauge
	* **Qualification**: Debug
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter
	* **Qualification**: Debug
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Gauge
	* **Qualification**: Debug
	* **Instances**: locks, write, general

canton.db-storage.<service>.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Instances**: locks, write, general

canton.db-storage.<storage>
^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring duration and rate of accessing the given storage
	* **Description**: Covers both read from and writes to the storage.
	* **Type**: Timer
	* **Qualification**: Debug

canton.db-storage.<storage>.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The load on the given storage
	* **Description**: The load is a factor between 0 and 1 describing how much of an existing interval has been spent reading from or writing to the storage.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.db-storage.alerts.multi-domain-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the multi-domain event log
	* **Description**: Failed writes to the multi domain event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter
	* **Qualification**: Debug

canton.db-storage.alerts.single-dimension-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the event log
	* **Description**: Failed writes to the single dimension event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter
	* **Qualification**: Debug

canton.mediator.event-rejected
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Event rejected because of traffic limit exceeded
	* **Description**: This metric is being incremented every time a sequencer rejects an event because      the sender does not have enough credit.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.mediator.max-event-age
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Age of oldest unpruned mediator response.
	* **Description**: This gauge exposes the age of the oldest, unpruned mediator response in hours as a way to quantify the pruning backlog.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.mediator.outstanding-requests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of currently outstanding requests
	* **Description**: This metric provides the number of currently open requests registered with the mediator.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.mediator.requests
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of totally processed requests
	* **Description**: This metric provides the number of totally processed requests since the system has been started.
	* **Type**: Meter
	* **Qualification**: Debug

canton.mediator.sequencer-client.handler.actual-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks how many such batches are processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Indicators that the configured upper bound may be too low: This metric constantly is closed to the configured maximum, which is exposed via 'max-in-flight-event-batches', while the system's resources are under-utilized. Indicators that the configured upper bound may be too high: Out-of-memory errors crashing the JVM or frequent garbage collection cycles that slow down processing. The metric tracks how many of these batches have been sent to the application handler but have not yet been fully processed. This metric can help identify potential bottlenecks or issues with the application's processing of events and provide insights into the overall workload of the system.
	* **Type**: Counter
	* **Qualification**: Saturation

canton.mediator.sequencer-client.handler.max-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks the upper bound of such batches being processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Configured by 'maximum-in-flight-event-batches' parameter in the sequencer-client config The metric shows the configured upper limit on how many batches the application handler may process concurrently. The metric 'actual-in-flight-event-batches' tracks the actual number of currently processed batches.
	* **Type**: Gauge
	* **Qualification**: Saturation

canton.mediator.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter
	* **Qualification**: Debug

canton.mediator.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter
	* **Qualification**: Debug

canton.mediator.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter
	* **Qualification**: Debug

canton.mediator.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer
	* **Qualification**: Debug

canton.mediator.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.block.event-bytes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Event bytes processed by the sequencer, tagged by type and sender.
	* **Description**: Similar to events, except measured by bytes.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.sequencer.block.events
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Events processed by the sequencer, tagged by type and sender
	* **Description**: The sequencer forwards opaque, possibly encrypted payload. However, by looking at the recipient list, the type of message can still be inferred, and tagged appropriately, including the sender.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.sequencer.block.height
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Current block height processed
	* **Description**: The submission messages are processed in blocks, where each block has an increasing number. The metric shows the height of the last processed block by the given sequencer node.
	* **Type**: Gauge
	* **Qualification**: Traffic

canton.sequencer.db-storage.<storage>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring duration and rate of accessing the given storage
	* **Description**: Covers both read from and writes to the storage.
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.db-storage.<storage>.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The load on the given storage
	* **Description**: The load is a factor between 0 and 1 describing how much of an existing interval has been spent reading from or writing to the storage.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.db-storage.alerts.multi-domain-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the multi-domain event log
	* **Description**: Failed writes to the multi domain event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.db-storage.alerts.single-dimension-event-log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of failed writes to the event log
	* **Description**: Failed writes to the single dimension event log indicate an issue requiring user intervention. In the case of domain event logs, the corresponding domain no longer emits any subsequent events until domain recovery is initiated (e.g. by disconnecting and reconnecting the participant from the domain). In the case of the participant event log, an operation might need to be reissued. If this counter is larger than zero, check the canton log for errors for details. 
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.db-storage.general.executor.exectime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Execution time metric for database tasks
	* **Description**: The time a task is running on the database is measured using this metric.
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.db-storage.general.executor.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Load of database pool
	* **Description**: Database queries run as tasks on an async executor. This metric shows the current number of queries running in parallel divided by the number database connections for this database connection pool.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.db-storage.general.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.db-storage.general.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.db-storage.general.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.db-storage.locks.executor.exectime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Execution time metric for database tasks
	* **Description**: The time a task is running on the database is measured using this metric.
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.db-storage.locks.executor.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Load of database pool
	* **Description**: Database queries run as tasks on an async executor. This metric shows the current number of queries running in parallel divided by the number database connections for this database connection pool.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.db-storage.locks.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.db-storage.locks.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.db-storage.locks.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.db-storage.write.executor.exectime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Execution time metric for database tasks
	* **Description**: The time a task is running on the database is measured using this metric.
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.db-storage.write.executor.load
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Load of database pool
	* **Description**: Database queries run as tasks on an async executor. This metric shows the current number of queries running in parallel divided by the number database connections for this database connection pool.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.db-storage.write.executor.queued
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks waiting in queue
	* **Description**: Database access tasks get scheduled in this queue and get executed using one of the existing asynchronous sessions. A large queue indicates that the database connection is not able to deal with the large number of requests. Note that the queue has a maximum size. Tasks that do not fit into the queue will be retried, but won't show up in this metric.
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.db-storage.write.executor.running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of database access tasks currently running
	* **Description**: Database access tasks run on an async executor. This metric shows the current number of tasks running in parallel.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.db-storage.write.executor.waittime
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Scheduling time metric for database tasks
	* **Description**: Every database query is scheduled using an asynchronous executor with a queue. The time a task is waiting in this queue is monitored using this metric.
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.max-event-age
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Age of oldest unpruned sequencer event.
	* **Description**: This gauge exposes the age of the oldest, unpruned sequencer event in hours as a way to quantify the pruning backlog.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.processed
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of messages processed by the sequencer
	* **Description**: This metric measures the number of successfully validated messages processed by the sequencer since the start of this process.
	* **Type**: Meter
	* **Qualification**: Debug

canton.sequencer.processed-bytes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of message bytes processed by the sequencer
	* **Description**: This metric measures the total number of message bytes processed by the sequencer. If the message received by the sequencer contains duplicate or irrelevant fields, the contents of these fields do not contribute to this metric.
	* **Type**: Meter
	* **Qualification**: Debug

canton.sequencer.sequencer-client.handler.actual-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks how many such batches are processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Indicators that the configured upper bound may be too low: This metric constantly is closed to the configured maximum, which is exposed via 'max-in-flight-event-batches', while the system's resources are under-utilized. Indicators that the configured upper bound may be too high: Out-of-memory errors crashing the JVM or frequent garbage collection cycles that slow down processing. The metric tracks how many of these batches have been sent to the application handler but have not yet been fully processed. This metric can help identify potential bottlenecks or issues with the application's processing of events and provide insights into the overall workload of the system.
	* **Type**: Counter
	* **Qualification**: Saturation

canton.sequencer.sequencer-client.handler.max-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks the upper bound of such batches being processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Configured by 'maximum-in-flight-event-batches' parameter in the sequencer-client config The metric shows the configured upper limit on how many batches the application handler may process concurrently. The metric 'actual-in-flight-event-batches' tracks the actual number of currently processed batches.
	* **Type**: Gauge
	* **Qualification**: Saturation

canton.sequencer.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter
	* **Qualification**: Debug

canton.sequencer.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer
	* **Qualification**: Debug

canton.sequencer.subscriptions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of active sequencer subscriptions
	* **Description**: This metric indicates the number of active subscriptions currently open and actively served subscriptions at the sequencer.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.sequencer.time-requests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of time requests received by the sequencer
	* **Description**: When a Participant needs to know the domain time it will make a request for a time proof to be sequenced. It would be normal to see a small number of these being sequenced, however if this number becomes a significant portion of the total requests to the sequencer it could indicate that the strategy for requesting times may need to be revised to deal with different clock skews and latencies between the sequencer and participants.
	* **Type**: Meter
	* **Qualification**: Debug

canton.sequencer.traffic-control.event-delivered-cost
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Cost of delivered event.
	* **Description**: Cost of an event that was delivered.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.sequencer.traffic-control.event-received-size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Raw size of an event received in the sequencer.
	* **Description**: This the raw payload size of an event, on the write path. Final event cost calculation.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.sequencer.traffic-control.event-rejected-cost
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Cost of rejected event.
	* **Description**: Cost of an event that was rejected because it exceeded the sender's traffic limit.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.topology-manager.sequencer-client.handler.actual-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks how many such batches are processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Indicators that the configured upper bound may be too low: This metric constantly is closed to the configured maximum, which is exposed via 'max-in-flight-event-batches', while the system's resources are under-utilized. Indicators that the configured upper bound may be too high: Out-of-memory errors crashing the JVM or frequent garbage collection cycles that slow down processing. The metric tracks how many of these batches have been sent to the application handler but have not yet been fully processed. This metric can help identify potential bottlenecks or issues with the application's processing of events and provide insights into the overall workload of the system.
	* **Type**: Counter
	* **Qualification**: Saturation

canton.topology-manager.sequencer-client.handler.max-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks the upper bound of such batches being processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Configured by 'maximum-in-flight-event-batches' parameter in the sequencer-client config The metric shows the configured upper limit on how many batches the application handler may process concurrently. The metric 'actual-in-flight-event-batches' tracks the actual number of currently processed batches.
	* **Type**: Gauge
	* **Qualification**: Saturation

canton.topology-manager.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter
	* **Qualification**: Debug

canton.topology-manager.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter
	* **Qualification**: Debug

canton.topology-manager.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter
	* **Qualification**: Debug

canton.topology-manager.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer
	* **Qualification**: Debug

canton.topology-manager.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer
	* **Qualification**: Debug
