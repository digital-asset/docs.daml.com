canton.<domain>.conflict-detection.sequencer-counter-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of conflict detection sequencer counter queue
	* **Description**: The task scheduler will work off tasks according to the timestamp order, scheduling the tasks whenever a new timestamp has been observed. This metric exposes the number of un-processed sequencer messages that will trigger a timestamp advancement.
	* **Type**: Counter
	* **Qualification**: Debug

canton.<domain>.conflict-detection.task-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of conflict detection task queue
	* **Description**: "This metric measures the size of the queue for conflict detection between concurrent transactions. A huge number does not necessarily indicate a bottleneck; it could also mean that a huge number of tasks have not yet arrived at their execution time.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.<domain>.protocol-messages.confirmation-request-creation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Time to create a confirmation request
	* **Description**: The time that the transaction protocol processor needs to create a confirmation request.
	* **Type**: Timer
	* **Qualification**: Debug

canton.<domain>.protocol-messages.confirmation-request-size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Confirmation request size
	* **Description**: Records the histogram of the sizes of (transaction) confirmation requests.
	* **Type**: Histogram
	* **Qualification**: Debug

canton.<domain>.protocol-messages.transaction-message-receipt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Time to parse a transaction message
	* **Description**: The time that the transaction protocol processor needs to parse and decrypt an incoming confirmation request.
	* **Type**: Timer
	* **Qualification**: Debug

canton.<domain>.request-tracker.sequencer-counter-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of record order publisher sequencer counter queue
	* **Description**: Same as for conflict-detection, but measuring the sequencer counter queues for the publishing to the ledger api server according to record time.
	* **Type**: Counter
	* **Qualification**: Debug

canton.<domain>.request-tracker.task-queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Size of record order publisher task queue
	* **Description**: The task scheduler will schedule tasks to run at a given timestamp. This metric exposes the number of tasks that are waiting in the task queue for the right time to pass.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.<domain>.sequencer-client.application-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of sequentially handling the event application logic
	* **Description**: All events are received sequentially. This handler records the the rate and time it takes the application (participant or domain) to handle the events.
	* **Type**: Timer
	* **Qualification**: Debug

canton.<domain>.sequencer-client.delay
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The delay on the event processing
	* **Description**: Every message received from the sequencer carries a timestamp that was assigned by the sequencer when it sequenced the message. This timestamp is called the sequencing timestamp. The component receiving the message on the participant, mediator or topology manager side, is the sequencer client. Upon receiving the message, the sequencer client compares the time difference between the sequencing time and the computers local clock and exposes this difference as the given metric. The difference will include the clock-skew and the processing latency between assigning the timestamp on the sequencer and receiving the message by the recipient. If the difference is large compared to the usual latencies and if clock skew can be ruled out, then it means that the node is still trying to catch up with events that were sequenced by the sequencer a while ago. This can happen after having been offline for a while or if the node is too slow to keep up with the messaging load.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.<domain>.sequencer-client.event-handle
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Timer monitoring time and rate of entire event handling
	* **Description**: Most event handling cost should come from the application-handle. This timer measures the full time (which should just be marginally more than the application handle.
	* **Type**: Timer
	* **Qualification**: Debug

canton.<domain>.sequencer-client.handler.actual-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks how many such batches are processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Indicators that the configured upper bound may be too low: This metric constantly is closed to the configured maximum, which is exposed via 'max-in-flight-event-batches', while the system's resources are under-utilized. Indicators that the configured upper bound may be too high: Out-of-memory errors crashing the JVM or frequent garbage collection cycles that slow down processing. The metric tracks how many of these batches have been sent to the application handler but have not yet been fully processed. This metric can help identify potential bottlenecks or issues with the application's processing of events and provide insights into the overall workload of the system.
	* **Type**: Counter
	* **Qualification**: Saturation

canton.<domain>.sequencer-client.handler.max-in-flight-event-batches
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Nodes process the events from the domain's sequencer in batches. This metric tracks the upper bound of such batches being processed in parallel.
	* **Description**: Incoming messages are processed by a sequencer client, which combines them into batches of size up to 'event-inbox-size' before sending them to an application handler for processing. Depending on the system's configuration, the rate at which event batches are sent to the handler may be throttled to avoid overwhelming it with too many events at once. Configured by 'maximum-in-flight-event-batches' parameter in the sequencer-client config The metric shows the configured upper limit on how many batches the application handler may process concurrently. The metric 'actual-in-flight-event-batches' tracks the actual number of currently processed batches.
	* **Type**: Gauge
	* **Qualification**: Saturation

canton.<domain>.sequencer-client.submissions.dropped
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests that did not cause an event to be sequenced
	* **Description**: Counter of send requests we did not witness a corresponding event to be sequenced by the supplied max-sequencing-time. There could be many reasons for this happening: the request may have been lost before reaching the sequencer, the sequencer may be at capacity and the the max-sequencing-time was exceeded by the time the request was processed, or the supplied max-sequencing-time may just be too small for the sequencer to be able to sequence the request.
	* **Type**: Counter
	* **Qualification**: Debug

canton.<domain>.sequencer-client.submissions.in-flight
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of sequencer send requests we have that are waiting for an outcome or timeout
	* **Description**: Incremented on every successful send to the sequencer. Decremented when the event or an error is sequenced, or when the max-sequencing-time has elapsed.
	* **Type**: Counter
	* **Qualification**: Debug

canton.<domain>.sequencer-client.submissions.overloaded
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Count of send requests which receive an overloaded response
	* **Description**: Counter that is incremented if a send request receives an overloaded response from the sequencer.
	* **Type**: Counter
	* **Qualification**: Debug

canton.<domain>.sequencer-client.submissions.sends
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of send requests to the sequencer
	* **Description**: Provides a rate and time of how long it takes for send requests to be accepted by the sequencer. Note that this is just for the request to be made and not for the requested event to actually be sequenced. 
	* **Type**: Timer
	* **Qualification**: Debug

canton.<domain>.sequencer-client.submissions.sequencing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Rate and timings of sequencing requests
	* **Description**: This timer is started when a submission is made to the sequencer and then completed when a corresponding event is witnessed from the sequencer, so will encompass the entire duration for the sequencer to sequence the request. If the request does not result in an event no timing will be recorded. 
	* **Type**: Timer
	* **Qualification**: Debug

canton.<domain>.traffic-control.event-above-traffic-limit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Event was not delivered because of traffic limit exceeded
	* **Description**: An event was not delivered because of insufficient traffic credit.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.<domain>.traffic-control.event-delivered
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Event was delivered
	* **Description**: An event was not delivered.
	* **Type**: Meter
	* **Qualification**: Traffic

canton.<domain>.traffic-control.extra-traffic-credit-available
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Current amount of extra traffic remaining
	* **Description**: Gets updated with every event received.
	* **Type**: Gauge
	* **Qualification**: Traffic

canton.<domain>.traffic-control.traffic-state-topology-transaction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Records a new top up on the participant
	* **Description**: Records top up events and the new extra traffic limit associated.
	* **Type**: Gauge
	* **Qualification**: Traffic

canton.commitments.catchup-mode-enabled
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Times the catch up mode has been activated.
	* **Description**: Participant nodes compute bilateral commitments at regular intervals. This metric exposes how often catch-up mode has been activated. Catch-up mode is triggered according to catch-up config and happens if the participant lags behind on computation.
	* **Type**: Meter
	* **Qualification**: Debug

canton.commitments.compute
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Time spent on commitment computations.
	* **Description**: Participant nodes compute bilateral commitments at regular intervals. This metric exposes the time spent on each computation. If the time to compute the metrics starts to exceed the commitment intervals, this likely indicates a problem.
	* **Type**: Timer
	* **Qualification**: Debug

canton.commitments.sequencing-time
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Time spent in microseconds between commitment and sequencing.
	* **Description**: Participant nodes compute bilateral commitments at regular intervals. After a commitment has been computed it is send for sequencing. This measures the time between the end of a commitment interval and when the commitment has been sequenced. A high value indicates that the participant is lagging behind in processing messages and computing commitments or the sequencer is slow in sequencing the commitment messages.
	* **Type**: Gauge
	* **Qualification**: Debug

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

canton.dirty_requests*
^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of requests being validated.
	* **Description**: Number of requests that are currently being validated. This also covers requests submitted by other participants. 
	* **Type**: Gauge
	* **Qualification**: Debug
	* **Labels**: 
		* **participant**: The id of the participant for which the value applies.

canton.max_dirty_requests*
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Configured maximum number of requests currently being validated.
	* **Description**: Configuration for the maximum number of requests that are currently being validated. This also covers requests submitted by other participants. A negative value means no configuration value was provided and no limit is enforced. 
	* **Type**: Gauge
	* **Qualification**: Debug
	* **Labels**: 
		* **participant**: The id of the participant for which the value applies.

canton.prune
^^^^^^^^^^^^
	* **Summary**: Duration of prune operations.
	* **Description**: This timer exposes the duration of pruning requests from the Canton portion of the ledger.
	* **Type**: Timer
	* **Qualification**: Debug

canton.prune.max-event-age
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Age of oldest unpruned event.
	* **Description**: This gauge exposes the age of the oldest, unpruned event in hours as a way to quantify the pruning backlog.
	* **Type**: Gauge
	* **Qualification**: Debug

canton.updates-published
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of updates published through the read service to the indexer
	* **Description**: When an update is published through the read service, it has already been committed to the ledger. The indexer will subsequently store the update in a form that allows for querying the ledger efficiently.
	* **Type**: Meter
	* **Qualification**: Debug

daml.cache.evicted_weight*
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sum of weights of cache entries evicted.
	* **Description**: The total weight of the entries evicted from the cache.
	* **Type**: Counter
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The cache for which the metrics are registered.

daml.cache.evictions*
^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the evicted cache entries.
	* **Description**: When an entry is evicted from the cache, the counter is incremented.
	* **Type**: Counter
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The cache for which the metrics are registered.

daml.cache.hits*
^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache hits.
	* **Description**: When a cache lookup encounters an existing cache entry, the counter is incremented.
	* **Type**: Counter
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The cache for which the metrics are registered.

daml.cache.misses*
^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache misses.
	* **Description**: When a cache lookup first encounters a missing cache entry, the counter is incremented.
	* **Type**: Counter
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The cache for which the metrics are registered.

daml.commands.delayed_submissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the delayed Daml commands.
	* **Description**: The number of Daml commands that have been delayed internally because they have been evaluated to require the ledger time further in the future than the expected latency.
	* **Type**: Meter
	* **Qualification**: Debug

daml.commands.failed_command_interpretations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of Daml commands that failed in interpretation.
	* **Description**: The number of Daml commands that have been rejected by the interpreter (e.g. badly authorized action).
	* **Type**: Meter
	* **Qualification**: Debug

daml.commands.max_in_flight_capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The maximum number of Daml commands that can await completion.
	* **Description**: The maximum number of Daml commands that can await completion in the Command Service.
	* **Type**: Counter
	* **Qualification**: Debug

daml.commands.max_in_flight_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the Daml commands awaiting completion.
	* **Description**: The number of the currently Daml commands awaiting completion in the Command Service.
	* **Type**: Counter
	* **Qualification**: Debug

daml.commands.reassignment_validation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to validate a reassignment command.
	* **Description**: The time to validate a submitted Daml command before is fed to the interpreter.
	* **Type**: Timer
	* **Qualification**: Debug

daml.commands.submissions
^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to fully process a Daml command.
	* **Description**: The time to validate and interpret a command before it is handed over to the synchronization services to be finalized (either committed or rejected).
	* **Type**: Timer
	* **Qualification**: Latency

daml.commands.submissions_running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the Daml commands that are currently being handled by the ledger api server.
	* **Description**: The number of the Daml commands that are currently being handled by the ledger api server (including validation, interpretation, and handing the transaction over to the synchronization services).
	* **Type**: Counter
	* **Qualification**: Debug

daml.commands.valid_submissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The total number of the valid Daml commands.
	* **Description**: The total number of the Daml commands that have passed validation and were sent to interpretation in this ledger api server process.
	* **Type**: Meter
	* **Qualification**: Debug

daml.commands.validation
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to validate a Daml command.
	* **Description**: The time to validate a submitted Daml command before is fed to the interpreter.
	* **Type**: Timer
	* **Qualification**: Debug

daml.db.commit.duration.seconds*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to perform the SQL query commit.
	* **Description**: This metric measures the time it takes to commit an SQL transaction relating to the <operation>. It roughly corresponds to calling `commit()` on a DB connection.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The operation/pool for which the metric is registered.

daml.db.compression.duration.seconds*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to decompress the SQL query result.
	* **Description**: Some index database queries that target contracts involve a decompression step. For such queries this metric represents the time it takes to decompress contract arguments retrieved from the database.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The operation/pool for which the metric is registered.

daml.db.exec.duration.seconds*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query and read the result.
	* **Description**: This metric encompasses the time measured by `query` and `commit` metrics. Additionally it includes the time needed to obtain the DB connection, optionally roll it back and close the connection at the end.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The operation/pool for which the metric is registered.

daml.db.query.duration.seconds*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to run the SQL query.
	* **Description**: This metric measures the time it takes to execute a block of code (on a dedicated executor) related to the <operation> that can issue multiple SQL statements such that all run in a single DB transaction (either committed or aborted).
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The operation/pool for which the metric is registered.

daml.db.translation.duration.seconds*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The operation/pool for which the metric is registered.

daml.db.wait.duration.seconds*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to acquire a connection to the database.
	* **Description**: SQL statements are run in a dedicated executor. This metric measures the time it takes between creating the SQL statement corresponding to the <operation> and the point when it starts running on the dedicated executor.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The operation/pool for which the metric is registered.

daml.execution.cache.contract_state.register_update
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent to update the cache.
	* **Description**: The total time spent in sequential update steps of the contract state caches updating logic. This metric is created with debugging purposes in mind.
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.cache.key_state.register_update
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent to update the cache.
	* **Description**: The total time spent in sequential update steps of the contract state caches updating logic. This metric is created with debugging purposes in mind.
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.cache.read_through_not_found
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of cache read-throughs resulting in not found contracts.
	* **Description**: On cache misses, a read-through query is performed against the Index database. When the contract is not found (as result of this query), this counter is incrmented.
	* **Type**: Counter
	* **Qualification**: Debug

daml.execution.cache.resolve_divulgence_lookup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of lookups trying to resolve divulged contracts on active contracts cache hits.
	* **Description**: Divulged contracts are not cached in the contract state caches. On active contract cache hits, where stakeholders are not within the submission readers, a contract activeness lookup is performed against the Index database. On such lookups, this counter is incremented.
	* **Type**: Counter
	* **Qualification**: Debug

daml.execution.cache.resolve_full_lookup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of lookups trying to resolve divulged contracts on archived contracts cache hits.
	* **Description**: Divulged contracts are not cached in the contract state caches. On archived contract cache hits, where stakeholders are not within the submission readers, a full contract activeness lookup (including fetching contract arguments) is performed against the Index database. On such lookups, this counter is incremented.
	* **Type**: Counter
	* **Qualification**: Debug

daml.execution.engine
^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent executing a Daml command.
	* **Description**: The time spent by the Daml engine executing a Daml command (excluding fetching data).
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.engine_running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of Daml commands currently being executed.
	* **Description**: The number of the commands that are currently being executed by the Daml engine (excluding fetching data).
	* **Type**: Counter
	* **Qualification**: Debug

daml.execution.get_lf_package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to fetch individual Daml code packages during interpretation.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple Daml packages. This metric exposes the time needed to fetch the packages that are necessary for interpretation.
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.lookup_active_contract
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to lookup individual active contracts during interpretation.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple active contracts. This metric exposes the time to lookup individual active contracts.
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.lookup_active_contract_count_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the active contracts looked up per Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple active contracts. This metric exposes the number of active contracts that must be looked up to process a Daml command.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.execution.lookup_active_contract_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The compound time to lookup all active contracts in a single Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple active contracts. This metric exposes the compound time to lookup all the active contracts in a single Daml command.
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.lookup_contract_key
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to lookup individual contract keys during interpretation.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple contract keys. This metric exposes the time needed to lookup individual contract keys.
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.lookup_contract_key_count_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of contract keys looked up per Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple contract keys. This metric exposes the number of contract keys that must be looked up to process a Daml command.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.execution.lookup_contract_key_per_execution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The compound time to lookup all contract keys in a single Daml command.
	* **Description**: The interpretation of a command in the ledger api server might require fetching multiple contract keys. This metric exposes the compound time needed to lookup all the contract keys in a single Daml command.
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.retry
^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the interpretation retries.
	* **Description**: The total number of interpretation retries attempted due to mismatching ledger effective time in this ledger api server process.
	* **Type**: Meter
	* **Qualification**: Debug

daml.execution.total
^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The overall time spent interpreting a Daml command.
	* **Description**: The time spent interpreting a Daml command in the ledger api server (includes executing Daml and fetching data).
	* **Type**: Timer
	* **Qualification**: Debug

daml.execution.total_running
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of Daml commands currently being interpreted.
	* **Description**: The number of the commands that are currently being interpreted (includes executing Daml code and fetching data).
	* **Type**: Counter
	* **Qualification**: Debug

daml.executor.runtime.completed*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks completed in an instrumented executor.
	* **Description**: The number of tasks completed by this executor
	* **Type**: Meter
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The name of the executor service.
		* **type**: The type of the executor service. Can be `fork_join` or `thread_pool`.

daml.executor.runtime.duration*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time a task runs in an instrumented executor.
	* **Description**: A task is considered running only after it has started execution.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The name of the executor service.
		* **type**: The type of the executor service. Can be `fork_join` or `thread_pool`.

daml.executor.runtime.idle*
^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time that a task is idle in an instrumented executor.
	* **Description**: A task is considered idle if it was submitted to the executor but it has not started execution yet.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The name of the executor service.
		* **type**: The type of the executor service. Can be `fork_join` or `thread_pool`.

daml.executor.runtime.running*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks running in an instrumented executor.
	* **Description**: The number of currently running tasks.
	* **Type**: Counter
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The name of the executor service.
		* **type**: The type of the executor service. Can be `fork_join` or `thread_pool`.

daml.executor.runtime.submitted*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of tasks submitted to an instrumented executor.
	* **Description**: Number of tasks that were submitted to the executor.
	* **Type**: Meter
	* **Qualification**: Debug
	* **Labels**: 
		* **name**: The name of the executor service.
		* **type**: The type of the executor service: `fork_join` or `thread_pool`.

daml.index.active_contracts_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for active contracts requests.
	* **Description**: An Pekko stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting active contracts that transactions satisfying a given predicate.
	* **Type**: Counter
	* **Qualification**: Saturation

daml.index.completions_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for completions requests.
	* **Description**: An Pekko stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting the completed commands in a specific period of time.
	* **Type**: Counter
	* **Qualification**: Saturation

daml.index.db.active_contract_keys_lookup.batch.active_contract_lookup.batch_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The batch sizes in the lookup batch-loading Contract Service.
	* **Description**: The number of lookups contained in a batch, used in the batch-loading Contract Service.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.active_contract_keys_lookup.batch.active_contract_lookup.buffer_capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The capacity of the lookup queue.
	* **Description**: The maximum number of elements that can be kept in the queue of lookups in the batch-loading queue of the Contract Service.
	* **Type**: Counter
	* **Qualification**: Debug

daml.index.db.active_contract_keys_lookup.batch.active_contract_lookup.buffer_delay.duration.seconds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The queuing delay for the lookup queue.
	* **Description**: The queuing delay for the pending lookups in the batch-loading queue of the Contract Service.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.db.active_contract_keys_lookup.batch.active_contract_lookup.buffer_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the currently pending active contract lookups.
	* **Description**: The number of the currently pending active contract lookups in the batch-loading queue of the Contract Service.
	* **Type**: Counter
	* **Qualification**: Debug

daml.index.db.active_contract_lookup.batch.active_contract_lookup.batch_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The batch sizes in the lookup batch-loading Contract Service.
	* **Description**: The number of lookups contained in a batch, used in the batch-loading Contract Service.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.active_contract_lookup.batch.active_contract_lookup.buffer_capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The capacity of the lookup queue.
	* **Description**: The maximum number of elements that can be kept in the queue of lookups in the batch-loading queue of the Contract Service.
	* **Type**: Counter
	* **Qualification**: Debug

daml.index.db.active_contract_lookup.batch.active_contract_lookup.buffer_delay.duration.seconds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The queuing delay for the lookup queue.
	* **Description**: The queuing delay for the pending lookups in the batch-loading queue of the Contract Service.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.db.active_contract_lookup.batch.active_contract_lookup.buffer_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the currently pending active contract lookups.
	* **Description**: The number of the currently pending active contract lookups in the batch-loading queue of the Contract Service.
	* **Type**: Counter
	* **Qualification**: Debug

daml.index.db.compression.create_argument_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed arguments of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed arguments of a create event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.compression.create_argument_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed argument of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of decompressed arguments of a create event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.compression.create_key_value_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed key value of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed key value of a create event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.compression.create_key_value_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed key value of a create event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of decompressed key value of a create event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.compression.exercise_argument_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed argument of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed arguments of an exercise event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.compression.exercise_argument_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed argument of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of decompressed arguments of an exercise event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.compression.exercise_result_compressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the compressed result of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed result of an exercise event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.compression.exercise_result_uncompressed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the decompressed result of an exercise event.
	* **Description**: Event information can be compressed by the indexer before storing it in the database. This metric collects statistics about the size of compressed result of an exercise event.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.index.db.flat_transactions_stream.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.db.lookup_active_contract
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent fetching a contract using its id.
	* **Description**: This metric exposes the time spent fetching a contract using its id from the index db. It is then used by the Daml interpreter when evaluating a command into a transaction.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.db.lookup_key
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time spent looking up a contract using its key.
	* **Description**: This metric exposes the time spent looking up a contract using its key in the index db. It is then used by the Daml interpreter when evaluating a command into a transaction.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.db.reassignment_stream.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.db.translation.get_lf_package
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to deserialize and decode a Daml-LF archive.
	* **Description**: A Daml archive before it can be used in the interpretation needs to be deserialized and decoded, in other words converted into the in-memory representation. This metric represents time necessary to do that.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.db.tree_transactions_stream.translation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time needed to turn serialized Daml-LF values into in-memory objects.
	* **Description**: Some index database queries that target contracts and transactions involve a Daml-LF translation step. For such queries this metric stands for the time it takes to turn the serialized Daml-LF values into in-memory representation.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.flat_transactions_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for flat transactions requests.
	* **Description**: An Pekko stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting flat transactions in a specific period of time that satisfy a given predicate.
	* **Type**: Counter
	* **Qualification**: Saturation

daml.index.ledger_end_sequential_id
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sequential id of the current ledger end kept in memory.
	* **Description**: The ledger end's sequential id is a monotonically increasing integer value representing the sequential id ascribed to the most recent ledger event ingested by the index db. Please note, that only a subset of all ledger events are ingested and given a sequential id. These are: creates, consuming exercises, non-consuming exercises and divulgence events. This value can be treated as a counter of all such events visible to a given participant. This metric exposes the latest ledger end's sequential id registered in the in-memory data set.
	* **Type**: Gauge
	* **Qualification**: Debug

daml.index.lf_value.compute_interface_view
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to compute an interface view while serving transaction streams.
	* **Description**: Transaction API allows clients to request events by interface-id. When an event matches the interface - an interface view is computed, which adds to the latency. This metric represents the time for each such computation.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.package_metadata.decode_archive
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to decode a package archive to extract metadata information.
	* **Description**: This metric represents the time spent scanning each uploaded package for new interfaces and corresponding templates.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.package_metadata.view_init
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to initialize package metadata view.
	* **Description**: As the mapping between interfaces and templates is not persistent - it is computed for each Indexer restart by loading all packages which were ever uploaded and scanning them to extract metadata information.
	* **Type**: Timer
	* **Qualification**: Debug

daml.index.transaction_trees_buffer_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The buffer size for transaction trees requests.
	* **Description**: An Pekko stream buffer is added at the end of all streaming queries, allowing to absorb temporary downstream backpressure (e.g. when the client is slower than upstream delivery throughput). This metric gauges the size of the buffer for queries requesting transaction trees.
	* **Type**: Counter
	* **Qualification**: Saturation

daml.indexer.current_record_time_lag
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The lag between the record time of a transaction and the wall-clock time registered at the ingestion phase to the index db (in milliseconds).
	* **Description**: Depending on the systemic clock skew between different machines, this value can be negative.
	* **Type**: Gauge
	* **Qualification**: Debug

daml.indexer.events*
^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of transactions processed.
	* **Description**: Represents the total number of transaction acceptance, transaction rejection, package upload, party allocation, etc. events processed.
	* **Type**: Meter
	* **Qualification**: Debug
	* **Labels**: 
		* **participant_id**: The id of the participant.
		* **application_id**: The application generating the events.
		* **event_type**: The type of ledger event processed (transaction, package upload, party allocation, configuration change).
		* **status**: Indicates if the transaction was accepted or not. Possible values accepted|rejected.

daml.indexer.last_received_record_time
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time of the last event ingested by the index db (in milliseconds since EPOCH).
	* **Description**: The last received record time is a monotonically increasing integer value that represents the record time of the last event ingested by the index db. It is measured in milliseconds since the EPOCH time.
	* **Type**: Gauge
	* **Qualification**: Debug

daml.indexer.ledger_end_sequential_id
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The sequential id of the current ledger end kept in the database.
	* **Description**: The ledger end's sequential id is a monotonically increasing integer value representing the sequential id ascribed to the most recent ledger event ingested by the index db. Please note, that only a subset of all ledger events are ingested and given a sequential id. These are: creates, consuming exercises, non-consuming exercises and divulgence events. This value can be treated as a counter of all such events visible to a given participant. This metric exposes the latest ledger end's sequential id registered in the database.
	* **Type**: Gauge
	* **Qualification**: Debug

daml.indexer.metered_events*
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: Number of ledger events that are metered.
	* **Description**: Represents the number of events that will be included in the metering report. This is an estimate of the total number and not a substitute for the metering report.
	* **Type**: Meter
	* **Qualification**: Debug
	* **Labels**: 
		* **participant_id**: The id of the participant.
		* **application_id**: The application generating the events.

daml.lapi.streams.acs_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the active contracts sent by the ledger api.
	* **Description**: The total number of active contracts sent over the ledger api streams to all clients.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.lapi.streams.active
^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the active streams served by the ledger api.
	* **Description**: The number of ledger api streams currently being served to all clients.
	* **Type**: Gauge
	* **Qualification**: Debug

daml.lapi.streams.completions_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the command completions sent by the ledger api.
	* **Description**: The total number of completions sent over the ledger api streams to all clients.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.lapi.streams.transaction_trees_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the transaction trees sent over the ledger api.
	* **Description**: The total number of the transaction trees sent over the ledger api streams to all clients.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.lapi.streams.transactions_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the flat updates sent over the ledger api.
	* **Description**: The total number of the flat updates sent over the ledger api streams to all clients.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.lapi.streams.update_trees_sent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the update trees sent over the ledger api.
	* **Description**: The total number of the update trees sent over the ledger api streams to all clients.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.parallel_indexer.archivals
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of archive events persisted to the database.
	* **Description**: The number of archive events persisted to the database.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.parallel_indexer.creates
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of create events persisted to the database.
	* **Description**: The number of create events persisted to the database.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.parallel_indexer.input_buffer_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of elements in the queue in front of the indexer.
	* **Description**: The indexer has a queue in order to absorb the back pressure and facilitate batch formation during the database ingestion.
	* **Type**: Counter
	* **Qualification**: Saturation

daml.parallel_indexer.inputmapping.batch_size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The batch sizes in the indexer.
	* **Description**: The number of state updates contained in a batch used in the indexer for database submission.
	* **Type**: Histogram
	* **Qualification**: Debug

daml.parallel_indexer.output_batched_buffer_length
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the queue between the indexer and the in-memory state updating flow.
	* **Description**: This counter counts batches of updates passed to the in-memory flow. Batches are dynamically-sized based on amount of backpressure exerted by the downstream stages of the flow.
	* **Type**: Counter
	* **Qualification**: Debug

daml.parallel_indexer.seqmapping.duration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The duration of the seq-mapping stage.
	* **Description**: The time that a batch of updates spends in the seq-mapping stage of the indexer.
	* **Type**: Timer
	* **Qualification**: Debug

daml.parallel_indexer.updates
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of the state updates persisted to the database.
	* **Description**: The number of the state updates persisted to the database. There are updates such as accepted transactions, configuration changes, package uloads, party allocations, rejections, etc.
	* **Type**: Counter
	* **Qualification**: Traffic

daml.services.index.<operation>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to execute an index service operation.
	* **Description**: The index service is an internal component responsible for access to the index db data. Its operations are invoked whenever a client request received over the ledger api requires access to the index db. This metric captures time statistics of such operations.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Instances**: get_transaction_metering, prune, configuration_entries, lookup_configuration, party_entries, list_known_parties, get_parties, get_participant_id, lookup_maximum_ledger_time, get_events_by_contract_key, get_events_by_contract_id, lookup_contract_key, lookup_contract_state_without_divulgence, lookup_active_contract, get_active_contracts, get_transaction_tree_by_id, get_transaction_by_id, transaction_trees, transactions, get_completions_limited, get_completions, latest_pruned_offsets, current_ledger_end, get_ledger_configuration, package_entries, get_lf_archive, list_lf_packages

daml.services.index.in_memory_fan_out_buffer.prune
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to remove all elements from the in-memory fan-out buffer.
	* **Description**: It is possible to remove the oldest entries of the in-memory fan out buffer. This metric exposes the time needed to prune the buffer.
	* **Type**: Timer
	* **Qualification**: Debug

daml.services.index.in_memory_fan_out_buffer.push
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to add a new event into the buffer.
	* **Description**: The in-memory fan-out buffer is a buffer that stores the last ingested maxBufferSize accepted and rejected submission updates as TransactionLogUpdate. It allows bypassing IndexDB persistence fetches for recent updates for flat and transaction tree streams, command completion streams and by-event-id and by-transaction-id flat and transaction tree lookups. This metric exposes the time spent on adding a new event into the buffer.
	* **Type**: Timer
	* **Qualification**: Debug

daml.services.index.in_memory_fan_out_buffer.size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The size of the in-memory fan-out buffer.
	* **Description**: The actual size of the in-memory fan-out buffer. This metric is mostly targeted for debugging purposes.
	* **Type**: Histogram
	* **Qualification**: Saturation

daml.services.read.<operation>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to execute a read service operation.
	* **Description**: The read service is an internal interface for reading the events from the synchronization interfaces. The metrics expose the time needed to execute each operation.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Instances**: validate_dar, get_connected_domains, state_updates

daml.services.write.<operation>
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The time to execute a write service operation.
	* **Description**: The write service is an internal interface for changing the state through the synchronization services. The methods in this interface are all methods that are supported uniformly across all ledger implementations. This metric exposes the time needed to execute each operation.
	* **Type**: Timer
	* **Qualification**: Debug
	* **Instances**: prune, submit_configuration, allocate_party, upload_packages, submit_reassignment_running, submit_reassignment, submit_transaction_running, submit_transaction

daml.services.write.submit_transaction.count
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	* **Summary**: The number of submitted transactions by the write service.
	* **Description**: The write service is an internal interface for changing the state through the synchronization services. The methods in this interface are all methods that are supported uniformly across all ledger implementations. This metric exposes the total number of the sumbitted transactions.
	* **Type**: Timer
	* **Qualification**: Traffic
