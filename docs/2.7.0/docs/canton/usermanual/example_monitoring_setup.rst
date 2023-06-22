..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _example_monitoring_setup:

Example Monitoring Setup
========================

This section provides an example of how Canton can be run inside a connected network of Docker containers. The example also shows how you can monitor network activity. See the `Glossary`_ for an explanation of the terms and the `Monitoring Choices`_ section for the reasoning behind the example monitoring setup. 

Container Setup
---------------

Following are the details for how you can configure `Docker Compose <https://docs.docker.com/compose/>`_ to spin up the Docker container network shown in the diagram. See the `compose` documentation for detailed information concerning the structure of the configuration files.

One feature of `compose` is that you can provide the overall configuration across multiple files. Each configuration file is described below, followed by information on how to bring them together in a running network.

.. image:: ./images/basic-canton-setup.svg
   :align: center
   :width: 100%
   :alt: A diagram showing an example Docker network setup

Intended Use
~~~~~~~~~~~~

This example is intended to demonstrate how you can expose, aggregate, and observe monitoring information from Canton. It is not suitable for production without alterations. Note the following warnings.

 .. warning::

   Ports are exposed from the Docker network that are not necessary to support the UI. This may be to allow low-level interaction with the underlying service via a REST or similar interface. In a production system, the only ports that should be exposed are those required for the operation of the system.

 .. warning:: 

   Some of the services used in the example (for example, Postgres and Elasticsearch) persist data to disk. For this example, the volumes used for this persisted data are internal to the Docker container. This means that when the Docker network is torn down, all data is cleaned up along with the containers. In a production system, these volumes would be mounted onto permanent storage.

 .. warning:: 

   Passwords are stored in plaintext in configuration files. In a production system, passwords should be extracted from a secure keystore at runtime.

 .. warning:: 

   Network connections are not secured. In a production system, connections between services should be TLS-enabled, with a certificate authority (CA) provided.

 .. warning:: 

   The memory use of the containers is only suitable for light demonstration loads. In a production setup, containers need to be given sufficient memory based on memory profiling.

 .. warning:: 

   The versions of the Docker images used in the example may become outdated. In a production system, only the latest patched versions should be used.


Network Configuration
~~~~~~~~~~~~~~~~~~~~~
In this compose file, define the network that will be used to connect all the running containers:

.. literalinclude:: ./monitoring/etc/network-docker-compose.yml
   :language: yaml
   :caption: etc/network-docker-compose.yml

Postgres Setup
~~~~~~~~~~~~~~
Using only a single Postgres container, create databases for the domain, along with Canton and index databases for each participant. To do this, mount `postgres-init.sql` into the Postgres-initialized directory. Note that in a production environment, passwords must not be inlined inside config.

.. literalinclude:: ./monitoring/etc/postgres-docker-compose.yml
   :language: yaml
   :caption: etc/postgres-docker-compose.yml

.. literalinclude:: ./monitoring/etc/postgres-init.sql
   :language: sql
   :caption: etc/postgres-init.sql 

Domain Setup
~~~~~~~~~~~~
Run the domain with the `--log-profile container` that writes plain text to standard out at debug level.

.. literalinclude:: ./monitoring/etc/domain0-docker-compose.yml
   :language: yaml
   :caption: etc/domain0-docker-compose.yml

.. literalinclude:: ./monitoring/etc/domain0.conf
   :caption: etc/domain0.conf

Participant Setup
~~~~~~~~~~~~~~~~~
The participant container has two files mapped into it on container creation. The `.conf` file provides details of the domain and database locations. An HTTP metrics endpoint is exposed that returns metrics in the `Prometheus Text Based Format <https://github.com/prometheus/docs/blob/main/content/docs/instrumenting/exposition_formats.md#text-based-format>`_. By default, participants do not connect to remote domains, so a bootstrap script is provided to accomplish that.

.. literalinclude:: ./monitoring/etc/participant1-docker-compose.yml
   :language: yaml
   :caption: etc/participant1-docker-compose.yml

.. literalinclude:: ./monitoring/etc/participant1.bootstrap
   :language: scala
   :caption: etc/participant1.bootstrap

.. literalinclude:: ./monitoring/etc/participant1.conf
   :caption: etc/participant1.conf

The setup for participant2 is identical, except that the name and ports are changed.

.. literalinclude:: ./monitoring/etc/participant2-docker-compose.yml
   :language: yaml
   :caption: etc/participant2-docker-compose.yml

.. literalinclude:: ./monitoring/etc/participant1.bootstrap
   :language: scala
   :caption: etc/participant2.bootstrap

.. literalinclude:: ./monitoring/etc/participant1.conf
   :caption: etc/participant2.conf

Logstash
~~~~~~~~

Docker containers can specify a log driver to automatically export log information from the container to an aggregating service. The example exports log information in `GELF`_, using Logstash as the aggregation point for all GELF streams. You can use Logstash to feed many downstream logging data stores, including Elasticsearch, Loki, and Graylog.

.. literalinclude:: ./monitoring/etc/logstash-docker-compose.yml
   :caption: etc/logstash-docker-compose.yml

Logstash reads the `pipeline.yml` to discover the locations of all pipelines.

.. literalinclude:: ./monitoring/etc/pipeline.yml
   :caption: etc/pipeline.yml

The configured pipeline reads GELF-formatted input, then outputs it to an Elasticsearch index prefixed with `logs-` and postfixed with the date.

.. literalinclude:: ./monitoring/etc/logstash.conf
   :caption: etc/logstash.conf

The default Logstash settings are used, with the HTTP port bound to all host IP addresses.

.. literalinclude:: ./monitoring/etc/logstash.yml
   :caption: etc/logstash.yml

Elasticsearch
~~~~~~~~~~~~~

Elasticsearch supports running in a clustered configuration with built-in resiliency. The example runs only a single Elasticsearch node. 

.. literalinclude:: ./monitoring/etc/elasticsearch-docker-compose.yml
   :caption: etc/elasticsearch-docker-compose.yml


Kibana
~~~~~~

Kibana provides a UI that allows the Elasticsearch log index to be searched.

.. literalinclude:: ./monitoring/etc/kibana-docker-compose.yml
   :caption: etc/kibana-docker-compose.yml

You must manually configure a data view to view logs. See `Kibana Log Monitoring`_ for instructions.

cAdvisor
~~~~~~~~

cAdvisor exposes container system metrics (CPU, memory, disk, and network) to Prometheus. It also provides a UI to view these metrics.

.. literalinclude:: ./monitoring/etc/cadvisor-docker-compose.yml
   :caption: etc/cadvisor-docker-compose.yml

To view container metrics:

   1. Navigate to `http://localhost:8080/docker/ <http://localhost:8080/docker/>`_.
   2. Select a Docker container of interest.

You should now see a UI similar to the one shown.

.. image:: ./images/c-advisor.png
   :align: center
   :width: 100% 
   :alt: An example cAdvisor UI

Prometheus-formatted metrics are available by default at `http://localhost:8080/metrics <http://localhost:8080/metrics>`_.

Prometheus
~~~~~~~~~~

Configure Prometheus with `prometheus.yml` to provide the endpoints from which metric data should be scraped. By default, port `9090` can query the stored metric data.

.. literalinclude:: ./monitoring/etc/prometheus-docker-compose.yml
   :caption: etc/prometheus-docker-compose.yml

.. literalinclude:: ./monitoring/etc/prometheus.yml
   :caption: etc/prometheus.yml

Grafana
~~~~~~~

Grafana is provided with: 

* The connection details for the Prometheus metric store
* The username and password required to use the web UI
* The location of any externally provided dashboards
* The actual dashboards

Note that the `Metric Count` dashboard referenced in the docker-compose.yml file (`grafana-message-count-dashboard.json`) is not inlined below. The reason is that this is not hand-configured but built via the web UI and then exported, so it contains unnecessary details. See `Grafana Metric Monitoring`_ for instructions to log into Grafana and display the dashboard.

.. literalinclude:: ./monitoring/etc/grafana-docker-compose.yml
   :caption: etc/grafana-docker-compose.yml

.. literalinclude:: ./monitoring/etc/grafana.ini
   :caption: etc/grafana.ini

.. literalinclude:: ./monitoring/etc/grafana-datasources.yml
   :caption: etc/grafana-datasources.yml

.. literalinclude:: ./monitoring/etc/grafana-dashboards.yml
   :caption: etc/grafana-dashboards.yml

Dependencies
~~~~~~~~~~~~

There are startup dependencies between the Docker containers. For example, the domain needs to be running before the participant, and the database needs to run before the domain.

The `yaml` anchor `x-logging` enabled GELF container logging and is duplicated across the containers where you want to capture logging output. Note that the host address is the host machine, not a network address (on OSX).

.. literalinclude:: ./monitoring/etc/dependency-docker-compose.yml
   :language: yaml
   :caption: etc/dependency-docker-compose.yml

Docker Images
~~~~~~~~~~~~~

The Docker images used need to be pulled down before starting the network:

* digitalasset/canton-open-source:2.5.1
* docker.elastic.co/elasticsearch/elasticsearch:8.5.2
* docker.elastic.co/kibana/kibana:8.5.2
* docker.elastic.co/logstash/logstash:8.5.1
* gcr.io/cadvisor/cadvisor:v0.45.0
* grafana/grafana:9.3.1-ubuntu
* postgres:11.18-bullseye
* prom/prometheus:v2.40.6

Running Docker Compose
~~~~~~~~~~~~~~~~~~~~~~

Since running `docker compose` with all the compose files shown above can create a long command line, a helper script `dc.sh` is used.

It is recommended to provide the Docker with a minimum of **12GB** of memory. To verify that Docker is not running short of memory, run `docker stats` and ensure the total `MEM%` is not too high.

.. literalinclude:: ./monitoring/dc.sh
   :language: bash
   :caption: dc.sh

**Useful commands**

.. code-block:: bash

     ./dc.sh up -d       # Spins up the network and runs it in the background

     ./dc.sh ps          # Shows the running containers

     ./dc.sh stop        # Stops the containers

     ./dc.sh start       # Starts the containers

     ./dc.sh down        # Stops and tears down the network, removing any created containers

Connecting to Nodes
-------------------

To interact with the running network, a Canton console can be used with a remote configuration. For example:

.. code-block:: bash

     bin/canton -c etc/remote-participant1.conf

Remote configurations
~~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: ./monitoring/etc/remote-domain0.conf
   :caption: etc/remote-domain0.conf

.. literalinclude:: ./monitoring/etc/remote-participant1.conf
   :caption: etc/remote-participant1.conf

.. literalinclude:: ./monitoring/etc/remote-participant2.conf
   :caption: etc/remote-participant2.conf

Getting Started
~~~~~~~~~~~~~~~

Using the previous scripts, you can follow the examples provided in 
the :ref:`Getting Started <canton-getting-started>` guide.

Kibana Log Monitoring
---------------------

When Kibana is started for the first time, you must set up a data view to allow view the log data:

   1. Navigate to `http://localhost:5601/ <http://localhost:5601/>`_.
   2. Click **Explore on my own**.
   3. From the menu select **Analytics** > **Discover**.
   4. Click **Create data view**.
   5. Save a data view with the following properties:

      * Name: `Logs`
      * Index pattern: `logs-*`
      * Timestamp field: `@timestamp`

You should now see a UI similar to the one shown.

.. image:: ./images/kibana.png
   :align: center
   :width: 100%
   :alt: An example Kibana UI

In the Kibana interface, you can:

   - Create a view based on selected fields
   - View log messages by logging timestamp
   - Filter by field value
   - Search for text
   - Query using either `KSQL` or `Lucene` query languages

For more details, see the Kibana documentation. Note that querying based on plain text for a wide time window likely results in poor UI performance. See `Logging Improvements`_ for ideas to improve it.

Grafana Metric Monitoring
-------------------------

You can log into the Grafana UI and set up a dashboard. The example imports a `GrafanaLabs community dashboard <https://grafana.com/grafana/dashboards/>`_ that has graphs for cAdvisor metrics. The `cAdvisor Export dashboard <https://grafana.com/grafana/dashboards/14282-cadvisor-exporter/>`_ imported below has an ID of **14282**.

   1. Navigate to `http://localhost:3000/login <http://localhost:3000/login>`_.
   2. Enter the username/password: `grafana/grafana`.
   3. In the side border, select **Dashboards** and then **Import**.
   4. Enter the dashboard ID `14282` and click **Load**.
   5. On the screen, select **Prometheus** as the data source and click **Import**.

You should see a container system metrics dashboard similar to the one shown:

.. image:: ./images/grafana-cadvisor.png
   :align: center
   :width: 100%
   :alt: An example metrics dashboard

See the `Grafana Documentation`_ for how to configure dashboards. For information about which metrics are available, see the Metrics documentation in the Monitoring section of this user manual.

Monitoring Choices
------------------
This section documents the reasoning behind the technology used in the example monitoring setup.

Use Docker Log Drivers
~~~~~~~~~~~~~~~~~~~~~~

**Reasons:**

- Most Docker containers can be configured to log all debug output to stdout.
- Containers can be run as supplied.
- No additional dockerfile layers need to be added to install and start log scrapers.
- There is no need to worry about local file naming, log rotation, and so on.

Use GELF Docker Log Driver
~~~~~~~~~~~~~~~~~~~~~~~~~~

**Reasons:**

- It is shipped with Docker.
- It has a decodable JSON payload.
- It does not have the size limitations of syslog.
- A UDP listener can be used to debug problems.

Use Logstash
~~~~~~~~~~~~

**Reasons:**

- It is a lightweight way to bridge the GELF output provided by the containers into Elasticsearch.
- It has a simple conceptual model (pipelines consisting of input/filter/output plugins).
- It has a large ecosystem of input/filter and output plugins.
- It externalizes the logic for mapping container logging output to a structures/ECS format.
- It can be run with `stdin`/`stdout` input/output plugins for use with testing.
- It can be used to feed Elasticsearch, Loki, or Graylog.
- It has support for the Elastic Common Schema (ECS) if needed.

Use Elasticsearch/Kibana
~~~~~~~~~~~~~~~~~~~~~~~~

**Reasons:**

- Using Logstash with Elasticsearch and Kibana, the `ELK`_ stack, is a mature way to set up a logging infrastructure. 
- Good defaults for these products allow a basic setup to be started with almost zero configuration.
- The ELK setup acts as a good baseline as compared to other options such as `Loki`_ or `Graylog`_.

Use Prometheus/Grafana
~~~~~~~~~~~~~~~~~~~~~~

**Reasons:**

- Prometheus defines and uses the `OpenTelemetry`_ reference file format.
- Exposing metrics via an HTTP endpoint allows easy direct inspection of metric values.
- The Prometheus approach of pulling metrics from underlying system means that the running containers do not need infrastructure to store and push metric data.
- Grafana works very well with Prometheus.


Logging Improvements
--------------------
This version of the example only has the logging structure provided via GELF. It is possible to improve this by:

  - Extracting data from the underlying containers as a JSON stream.
  - Mapping fields in this JSON data onto the `ECS`_ so that the same name is used for commonly used field values (for example, log level).
  - Configuring Elasticsearch with a schema that allows certain fields to be quickly filtered (for example, log level).

Glossary
--------

Docker Log Driver
~~~~~~~~~~~~~~~~~
Docker containers can be configured with a log driver that allows log output to be exported out of the Docker container. Using log drivers to export logging information means that it is not necessary to run another process on the Docker container to do this.

`https://docs.docker.com/config/containers/logging/configure/ <https://docs.docker.com/config/containers/logging/configure/>`_

Syslog
~~~~~~
Syslog is a standard for logging messages that has been around since the 1980s. Syslog is one of the built-in logging drivers supported by Docker.

`https://en.wikipedia.org/wiki/Syslog <https://en.wikipedia.org/wiki/Syslog>`_

GELF
~~~~
The Graylog extended logging format (GELF) improves on syslog logging by providing structured messages that are not size-limited. GELF is one of the built-in logging drivers supported by Docker. The message format is compressed JSON.

`https://docs.graylog.org/docs/gelf <https://docs.graylog.org/docs/gelf>`_

Docker Plugins
~~~~~~~~~~~~~~
A Docker plugin is a way to extend Docker (for example, by adding a log driver).

`https://docs.docker.com/engine/extend/ <https://docs.docker.com/engine/extend/>`_

Loki Log Driver
~~~~~~~~~~~~~~~
The Loki log driver is a Loki client that allows log information to be shipped from a Docker log file, similar to other log drivers. The message format is gRPC protobuf.

`https://grafana.com/docs/loki/latest/clients/docker-driver/ <https://grafana.com/docs/loki/latest/clients/docker-driver/>`_

Logstash
~~~~~~~~
Logstash is a service that allows a series of pipelines to be configured that read, filter, and manipulate data before writing it out. It has support for a multitude of input, filter, and output types. The GELF input reader and Elasticsearch output writer are of particular interest.

`https://www.elastic.co/guide/en/logstash/current/introduction.html <https://www.elastic.co/guide/en/logstash/current/introduction.html>`_

Elasticsearch
~~~~~~~~~~~~~
Elasticsearch is a technology that allows JSON documents to be stored, indexed, and searched in near real time. It can be configured as a cluster with built-in resiliency.

`https://www.elastic.co/guide/en/elasticsearch/reference/8.5/index.html <https://www.elastic.co/guide/en/elasticsearch/reference/8.5/index.html>`_

ECS
~~~
The Elastic Common Schema (ECS) defines a naming convention for fields used in Elasticsearch. For example, use `@timestamp` for timestamp.

`https://www.elastic.co/guide/en/ecs/current/ecs-field-reference.html <https://www.elastic.co/guide/en/ecs/current/ecs-field-reference.html>`_

MinIO
~~~~~
AWS S3 Compatible Storage (used by Loki).

`https://min.io/product/s3-compatibility <https://min.io/product/s3-compatibility>`_

ELK
~~~
The ELK stack is an established way to enable capturing, indexing, and displaying log data.

`https://www.elastic.co/what-is/elk-stack <https://www.elastic.co/what-is/elk-stack>`_

Graylog
~~~~~~~
Unlike Elasticsearch, Graylog is not a general-purpose indexing, analytics, and search tool. It is designed specifically for log data. This provides a simpler, more focused option with better defaults for logging. 

`https://www.graylog.org/about/ <https://www.graylog.org/about/>`_

Loki
~~~~
Loki is a log aggregation system designed to store and query logs from all your applications and infrastructure. It displays log information inside Grafana, allowing a single UI to be used for both metric data and logs.

`https://grafana.com/oss/loki/ <https://grafana.com/oss/loki/>`_

Prometheus
~~~~~~~~~~
Prometheus can be configured to scrape metric data from many endpoints. This metric data can then be queried by metric visualization tools such as Grafana.

`https://prometheus.io/ <https://prometheus.io/>`_

.. _Grafana Documentation:

Grafana
~~~~~~~
Grafana provides a web UI that allows the construction of dashboards showing metric data. This data can be queried against a Prometheus metric store.

`https://grafana.com/grafana/ <https://grafana.com/grafana/>`_

OpenTelemetry
~~~~~~~~~~~~~
OpenTelemetry is an organization that works to standardize observability (an umbrella term that includes logging, metrics, and tracing).

`https://opentelemetry.io/ <https://opentelemetry.io/>`_

cAdvisor
~~~~~~~~
Container Advisor (cAdvisor) provides an overview of CPU, memory, disk, and network utilization for each of the Docker containers. It works by querying the `Docker Engine API <https://docs.docker.com/engine/api/>`_ to get these statistics for each container. This avoids layering the containers with a utility to perform these functions.

`https://github.com/google/cadvisor <https://github.com/google/cadvisor>`_
