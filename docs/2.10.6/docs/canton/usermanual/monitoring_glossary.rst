..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _monitoring_glossary:

Glossary
========

cAdvisor
~~~~~~~~
Container Advisor (cAdvisor) provides an overview of CPU, memory, disk, and network utilization for each of the Docker containers. It works by querying the `Docker Engine API <https://docs.docker.com/engine/api/>`_ to get these statistics for each container. This lets you avoid layering the containers with a utility to perform these functions.

`https://github.com/google/cadvisor <https://github.com/google/cadvisor>`_

Docker Log Driver
~~~~~~~~~~~~~~~~~
Docker containers can be configured with a log driver that allows log output to be exported from the Docker container. Using log drivers to export logging information makes running another process on the Docker container for this unnecessary.

`https://docs.docker.com/config/containers/logging/configure/ <https://docs.docker.com/config/containers/logging/configure/>`_

Docker Plugins
~~~~~~~~~~~~~~
A Docker plugin is a way to extend Docker (for example, by adding a log driver).

`https://docs.docker.com/engine/extend/ <https://docs.docker.com/engine/extend/>`_

ECS
~~~
The Elastic Common Schema (ECS) defines a naming convention for fields used in Elasticsearch. For example, use `@timestamp` for timestamp.

`https://www.elastic.co/guide/en/ecs/current/ecs-field-reference.html <https://www.elastic.co/guide/en/ecs/current/ecs-field-reference.html>`_

Elasticsearch
~~~~~~~~~~~~~
Elasticsearch is a technology that allows JSON documents to be stored, indexed, and searched in near real time. It can be configured as a cluster with built-in resiliency.

`https://www.elastic.co/guide/en/elasticsearch/reference/8.5/index.html <https://www.elastic.co/guide/en/elasticsearch/reference/8.5/index.html>`_

ELK
~~~
The ELK stack is an established way to enable capturing, indexing, and displaying log data.

`https://www.elastic.co/what-is/elk-stack <https://www.elastic.co/what-is/elk-stack>`_

GELF
~~~~
The Graylog extended logging format (GELF) improves on syslog logging by providing structured messages that are not size-limited. GELF is one of the built-in logging drivers supported by Docker. The message format is compressed JSON.

`https://docs.graylog.org/docs/gelf <https://docs.graylog.org/docs/gelf>`_

.. _Grafana Documentation:

Grafana
~~~~~~~
Grafana provides a web UI that allows the construction of dashboards showing metric data. This data can be queried against a Prometheus metric store.

`https://grafana.com/grafana/ <https://grafana.com/grafana/>`_

Graylog
~~~~~~~
Unlike Elasticsearch, Graylog is not a general-purpose indexing, analytics, and search tool. It is designed specifically for log data. This provides a simpler, more focused option with better defaults for logging. 

`https://www.graylog.org/about/ <https://www.graylog.org/about/>`_

Logstash
~~~~~~~~
Logstash is a service that allows a series of pipelines to be configured that read, filter, and manipulate data before writing it out. It has support for a multitude of input, filter, and output types. The GELF input reader and Elasticsearch output writer are of particular interest.

`https://www.elastic.co/guide/en/logstash/current/introduction.html <https://www.elastic.co/guide/en/logstash/current/introduction.html>`_

Loki
~~~~
Loki is a log aggregation system designed to store and query logs from all your applications and infrastructure. It displays log information inside Grafana, allowing a single UI to be used for both metric data and logs.

`https://grafana.com/oss/loki/ <https://grafana.com/oss/loki/>`_

Loki Log Driver
~~~~~~~~~~~~~~~
The Loki log driver is a Loki client that allows log information to be shipped from a Docker log file, similar to other log drivers. The message format is gRPC protobuf.

`https://grafana.com/docs/loki/latest/clients/docker-driver/ <https://grafana.com/docs/loki/latest/clients/docker-driver/>`_

MinIO
~~~~~
AWS S3 Compatible Storage (used by Loki).

`https://min.io/product/s3-compatibility <https://min.io/product/s3-compatibility>`_

OpenTelemetry
~~~~~~~~~~~~~
OpenTelemetry is an organization that works to standardize observability (an umbrella term that includes logging, metrics, and tracing).

`https://opentelemetry.io/ <https://opentelemetry.io/>`_

Prometheus
~~~~~~~~~~
Prometheus can be configured to scrape metric data from many endpoints. This metric data can then be queried by metric visualization tools such as Grafana.

`https://prometheus.io/ <https://prometheus.io/>`_

Syslog
~~~~~~
Syslog is a standard for logging messages that has been around since the 1980s. Syslog is one of the built-in logging drivers supported by Docker.

`https://en.wikipedia.org/wiki/Syslog <https://en.wikipedia.org/wiki/Syslog>`_