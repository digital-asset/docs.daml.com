..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _example_monitoring_setup:

Example Monitoring Setup
========================

This section gives an example of how canton can be run inside a connected network of docker containers. We then go on to show how network activity can be monitored. See the `Glossary`_ for an explaination of the terms used and the `Monitoring Choices`_ section on the reasoning behind the example monitoring setup. 

Container Setup
---------------

Here we go through the details of how `Docker Compose <https://docs.docker.com/compose/>`_ can be configured to spin up the docker container network shown below.
Please see the `compose` documentation for detailed information concerning the structure of the configuration files.

One feature of `compose` is that it allows the overall configuration to be provided across a number of files.
Below we look at each of the configuration files in turn and then show how we can bring them all together in a running network.

.. image:: ./images/basic-canton-setup.svg
   :align: center
   :width: 100%


Intended Use
~~~~~~~~~~~~

The purpose of of this example is to demonstrate how monitoring information can be exposed from canton, aggregated and observed. It is not suitable for production use as is without alterations. In particular note the warnings below.

 .. warning::

   Ports are exposed from the docker network that are not necessary to support the UI. This may be to allow low level interaction with the underlying service via a REST interface or similar. In a production system the only ports that should be exposed are those required for the operation of the system

 .. warning:: 

   Some of the services used in the demo, for example Postgres and Elasiticsearch persist data to disk. For the demo the volumes used for this persisted data are internal to the docker container. This means that when the docker network is torn down all data is cleaned up along with the containers. In a production system these volumes would be mounted onto permanent storage.

 .. warning:: 

   Passwords are stored in plaintext in configuration files. In a production system passwords should be extracted from a secure keystore at runtime.

 .. warning:: 

   Network connections are not secured. In a production system connections between services should be TLS enabled with a certificate authority (CA) provided.

 .. warning:: 

   The memory use of the containers is only suitable for light demonstration loads. In a production setup containers need to be given sufficient memory based on memory profiling.

 .. warning:: 

   The versions of the docker images used in the example was current at the time of publishing. In a production system only the latest patched versions should be used.


Network Configuration
~~~~~~~~~~~~~~~~~~~~~
This compose file defines the network that will be used to connect all the running containers.

.. code-block:: yaml
   :caption: etc/network-docker-compose.yml

    
    # Create with `docker network create monitoring`
    
    version: "3.8"
    
    networks:
      default:
        name: monitoring
        external: true
    


Postgres Setup
~~~~~~~~~~~~~~
We only use a single postgres container but create databases for the domain along with canton and index databases for each participant.
We do this by mounting `postgres-init.sql` into the postgres initialized directory. Note that in a production environment passwords
must not be inlined inside config.

.. code-block:: yaml
   :caption: etc/postgres-docker-compose.yml

    
    services:
      postgres:
        image: postgres:11.18-bullseye
        hostname: postgres
        container_name: postgres
        environment:
          - POSTGRES_USER=pguser
          - POSTGRES_PASSWORD=pgpass
        volumes:
          - ../etc/postgres-init.sql:/docker-entrypoint-initdb.d/init.sql
        expose:
          - "5432"
        ports:
          - "5432:5432"    
        healthcheck:
          test: "pg_isready -U postgres"
          interval: 5s
          timeout: 5s
          retries: 5


.. code-block:: sql
   :caption: etc/postgres-init.sql

    
    create database canton1db;
    create database index1db;
    
    create database domain0db;
    
    create database canton2db;
    create database index2db;
    
    


Domain Setup
~~~~~~~~~~~~
We run the domain with the `--log-profile container` that writes plain text to standard out at debug level.

.. code-block:: yaml
   :caption: etc/domain0-docker-compose.yml

    
    services:
      domain0:
        image: digitalasset/canton-open-source:2.4.2
        container_name: domain0
        hostname: domain0
        volumes:
          - ./domain0.conf:/canton/etc/domain0.conf
        command: daemon --log-profile container --config etc/domain0.conf
        expose:
          - "10018"
          - "10019"
          - "10020"
        ports:
          - "10018:10018"    
          - "10019:10019"    
          - "10020:10020"    
    
    


.. code-block:: none
   :caption: etc/domain0.conf

    
    canton {
      domains {
        domain0 {
          storage {
            type = postgres
            config {
              dataSourceClass = "org.postgresql.ds.PGSimpleDataSource"
              properties = {
                databaseName = "domain0db"
                serverName = "postgres"
                portNumber = "5432"
                user = pguser
                password = pgpass
              }
            }
          }
          public-api {
            port = 10018
            address = "0.0.0.0"
          }
          admin-api {
            port = 10019
            address = "0.0.0.0"
          }
        }
      }
      monitoring.metrics.reporters = [{
        type = prometheus
        address = "0.0.0.0"
        port = 10020
      }]
    }
    


Participant Setup
~~~~~~~~~~~~~~~~~
Ths particpant container has two files mapped into it on conainer creation, the `.conf` gives details of the domain and database locations.
A HTTP metrics endpoint is exposed that returns metrics in the 
`Prometheus Text Based Format <https://github.com/prometheus/docs/blob/main/content/docs/instrumenting/exposition_formats.md#text-based-format>`_
By default participants do not connect to remote domains so to make this happen a bootstrap script is provided.

.. code-block:: yaml
   :caption: etc/participant1-docker-compose.yml

    
    services:
      participant1:
        image: digitalasset/canton-open-source:2.4.2
        container_name: participant1
        hostname: participant1
        volumes:
          - ./participant1.conf:/canton/etc/participant1.conf
          - ./participant1.bootstrap:/canton/etc/participant1.bootstrap
        command: daemon --log-profile container --config etc/participant1.conf --bootstrap etc/participant1.bootstrap
        expose:
          - "10011"
          - "10012"
          - "10013"
        ports:
          - "10011:10011"    
          - "10012:10012"    
          - "10013:10013"    
    
    


.. code-block:: scala
   :caption: etc/participant1.bootstrap

    participant1.domains.connect(domain0.defaultDomainConnection)

.. code-block:: none
   :caption: etc/participant1.conf

    canton {
      participants {
        participant1 {
          storage {
            type = postgres
            config {
            dataSourceClass = "org.postgresql.ds.PGSimpleDataSource"
              properties = {
                databaseName = "canton1db"
                serverName = "postgres"
                portNumber = "5432"
                user = pguser
                password = pgpass
              }
            }
            ledger-api-jdbc-url = "jdbc:postgresql://postgres:5432/index1db?user=pguser&password=pgpass"
          }
          ledger-api {
            port = 10011
            address = "0.0.0.0"
          }
          admin-api {
            port = 10012
            address = "0.0.0.0" 
          } 
        }
      }
      monitoring.metrics.reporters = [{
        type = prometheus
        address = "0.0.0.0"
        port = 10013
      }]
      remote-domains.domain0 {
        public-api {
          address="domain0"
          port = 10018
        } 
        admin-api {
          address = "domain0"
          port = 10019
        }
      } 
    }
    
    


The setup for participant2 is identical apart from the name and ports which are changed

.. code-block:: yaml
   :caption: etc/participant2-docker-compose.yml

    
    services:
      participant2:
        image: digitalasset/canton-open-source:2.4.2
        container_name: participant2
        hostname: participant2
        volumes:
          - ./participant2.conf:/canton/etc/participant2.conf
          - ./participant2.bootstrap:/canton/etc/participant2.bootstrap
        command: daemon --log-profile container --config etc/participant2.conf --bootstrap etc/participant2.bootstrap
        expose:
          - "10021"
          - "10022"
          - "10023"
        ports:
          - "10021:10021"    
          - "10022:10022"    
          - "10023:10023"    
    
    


.. code-block:: scala
   :caption: etc/participant2.bootstrap

    participant1.domains.connect(domain0.defaultDomainConnection)

.. code-block:: none
   :caption: etc/participant2.conf

    canton {
      participants {
        participant1 {
          storage {
            type = postgres
            config {
            dataSourceClass = "org.postgresql.ds.PGSimpleDataSource"
              properties = {
                databaseName = "canton1db"
                serverName = "postgres"
                portNumber = "5432"
                user = pguser
                password = pgpass
              }
            }
            ledger-api-jdbc-url = "jdbc:postgresql://postgres:5432/index1db?user=pguser&password=pgpass"
          }
          ledger-api {
            port = 10011
            address = "0.0.0.0"
          }
          admin-api {
            port = 10012
            address = "0.0.0.0" 
          } 
        }
      }
      monitoring.metrics.reporters = [{
        type = prometheus
        address = "0.0.0.0"
        port = 10013
      }]
      remote-domains.domain0 {
        public-api {
          address="domain0"
          port = 10018
        } 
        admin-api {
          address = "domain0"
          port = 10019
        }
      } 
    }
    
    


Logstash
~~~~~~~~

Docker containers have the ability to specifify a log driver that allows the automatic exporting of log information from the container to an aggregating service. We have chosen to export log information in `GELF`_ with Logstash being used as the aggregation point for all GELF streams. Logstash can be used to feed a number of downstream logging data stores including Elasiticsearch, Loki and Graylog.

.. code-block:: none
   :caption: etc/logstash-docker-compose.yml

    
    services:
      logstash:
        image: docker.elastic.co/logstash/logstash:8.5.1
        hostname: logstash
        container_name: logstash
        expose:
          - 12201/udp
        volumes:
          - ./pipeline.yml:/usr/share/logstash/config/pipeline.yml
          - ./logstash.yml:/usr/share/logstash/config/logstash.yml
          - ./logstash.conf:/usr/share/logstash/pipeline/logstash.conf
        ports:
          - "12201:12201/udp"


Logstash reads the `pipeline.yml` to discover the locations of all pipelines.

.. code-block:: none
   :caption: etc/pipeline.yml

    
    - pipeline.id: main
      path.config: "/usr/share/logstash/pipeline/logstash.conf"


The configured pipeline reads GELF formatted input and outputs it to an Elasticsearch index prefixed with `logs-` and postfixed with the date.

.. code-block:: none
   :caption: etc/logstash.conf

    
    # Main logstash pipeline
    
    input { 
      gelf {
        use_udp => true
        use_tcp => false
        port => 12201   
      }
    } 
    
    filter {}
    
    output { 
    
      elasticsearch { 
        hosts => ["http://elasticsearch:9200"] 
        index => "logs-%{+YYYY.MM.dd}"
      }
    
    }


The default logstash settings are used with the http port bound to all host IP addresses.

.. code-block:: none
   :caption: etc/logstash.yml

    
    # For full set of descriptions see
    # https://www.elastic.co/guide/en/logstash/current/logstash-settings-file.html
    
    http.host: "0.0.0.0"


Elasticsearch
~~~~~~~~~~~~~

Elasiticsearch supports running in a clustered configuration with built-in resiliency. For demonstration purposes we only run a single Elasticsearch node. 

.. code-block:: none
   :caption: etc/elasticsearch-docker-compose.yml

    
    services:
      elasticsearch:
        image: docker.elastic.co/elasticsearch/elasticsearch:8.5.2
        container_name: elasticsearch
        environment:
          ELASTIC_PASSWORD: elastic
          node.name: elasticsearch
          cluster.name: elasticsearch
          cluster.initial_master_nodes: elasticsearch
          xpack.security.enabled: false
          bootstrap.memory_lock: true
        ulimits:
          memlock:
            soft: -1
            hard: -1
        expose:
          - 9200
        ports:
          - 9200:9200
        healthcheck:
          test: "curl -s -I http://localhost:9200 | grep 'HTTP/1.1 200 OK'"
          interval: 10s
          timeout: 10s
          retries: 10
    



Kibana
~~~~~~

Kibana is used to provide a UI that allows the Elasiticsearch log index to be searched.

.. code-block:: none
   :caption: etc/kibana-docker-compose.yml

    
    services:
      kibana:
        image: docker.elastic.co/kibana/kibana:8.5.2
        container_name: kibana
        expose:
          - 5601
        ports:
          - 5601:5601
        environment:
          - SERVERNAME=kibana
          - ELASTICSEARCH_HOSTS=http://elasticsearch:9200
        healthcheck:
          test: "curl -s -I http://localhost:5601 | grep 'HTTP/1.1 302 Found'"
          interval: 10s
          timeout: 10s
          retries: 10      
    


A data view needs to be manually configured to allow log viewing. See `Kibana Log Monitoring`_ for instructions on how to do this.

Prometheus
~~~~~~~~~~

Prometheus is configured with `prometheus.yml` that gives the endpoints from which metric data should be scraped. 
By default port `9090` can be used to query the stored metric data.

.. code-block:: none
   :caption: etc/prometheus-docker-compose.yml

    
    services:
      prometheus:
        image: prom/prometheus:v2.40.6
        container_name: prometheus
        hostname: prometheus
        volumes:
          - ./prometheus.yml:/etc/prometheus/prometheus.yml
        ports:
          - 9090:9090
    
    


.. code-block:: none
   :caption: etc/prometheus.yml

    
    global:
      scrape_interval: 15s
      scrape_timeout: 10s
      evaluation_interval: 1m
    
    scrape_configs:
      - job_name: canton
        static_configs:
          - targets:
            - domain0:10020
            - participant1:10013
            - participant2:10023


Grafana
~~~~~~~

Grafana is provided with: 

* The connection details for the prometheus metric store
* The username and password required to use the web UI
* The location of any externally provided dashboards
* The actual dashboards.

Note that the `Metric Count` dashboard referenced in the docker-compose.yml (`grafana-message-count-dashboard.json`) is not inlined below as this is not hand configured but built via the web UI and then exported (so contains a lot of unnecessary details). 
See `Grafana Metric Monitoring`_ for instructions of how to log into Grafana and display the dashboard.

.. code-block:: none
   :caption: etc/grafana-docker-compose.yml

    
    services:
      grafana:
        image: grafana/grafana:9.3.1-ubuntu
        container_name: grafana
        hostname: grafana
        volumes:
          - ./grafana.ini:/etc/grafana/grafana.ini
          - ./grafana-datasources.yml:/etc/grafana/provisioning/datasources/default.yml
          - ./grafana-dashboards.yml:/etc/grafana/provisioning/dashboards/default.yml
          - ./grafana-message-count-dashboard.json:/var/lib/grafana/dashboards/grafana-message-count-dashboard.json
        ports:
          - 3000:3000


.. code-block:: none
   :caption: etc/grafana.ini

    instance_name = "docker-compose"
    
    [security]
    admin_user = "grafana"
    admin_password = "grafana"
    
    [unified_alerting]
    enabled = false
    
    [alerting]
    enabled = false
    
    [plugins]
    plugin_admin_enabled = true


.. code-block:: none
   :caption: etc/grafana-datasources.yml

    ---
    apiVersion: 1
    
    datasources:
    - name: prometheus
      type: prometheus
      access: proxy
      orgId: 1
      uid: prometheus
      url: http://prometheus:9090
      isDefault: true
      version: 1
      editable: false


.. code-block:: none
   :caption: etc/grafana-dashboards.yml

    ---
    apiVersion: 1
    
    providers:
      - name: local
        orgId: 1
        folder: ''
        folderUid: default
        type: file
        disableDeletion: true
        updateIntervalSeconds: 30
        allowUiUpdates: true
        options:
          path: /var/lib/grafana/dashboards
          foldersFromFilesStructure: true


Dependencies
~~~~~~~~~~~~

There are startup dependencies between the docker containers, for example the domain needs to be running before the particpant, and in turn, the datbase needs to run before the domain.

The `yaml` anchor `x-logging` enabled GELF container logging and is duplicated across the containers where we want to capture logging output. One thing to note is that the host address used is that of the host machine, not a network address (on OSX).

.. code-block:: yaml
   :caption: etc/dependency-docker-compose.yml

    
    x-logging: &logging
      driver: gelf
      options:
        # Should be able to use "udp://logstash:12201"
        gelf-address: "udp://host.docker.internal:12201"
    
    services:  
    
      logstash:
        depends_on:
          elasticsearch:
            condition: service_healthy
    
      postgres:
        logging: 
          <<: *logging
        depends_on:
          logstash:
            condition: service_started
    
      domain0:
        logging: 
          <<: *logging
        depends_on:
          postgres:
            condition: service_healthy
          logstash:
            condition: service_started
    
      participant1:
        logging: 
          <<: *logging
        depends_on:
          domain0:
            condition: service_started
          logstash:
            condition: service_started
    
      participant2:
        logging: 
          <<: *logging
        depends_on:
          domain0:
            condition: service_started
          logstash:
            condition: service_started
    
      kibana:
        depends_on:
          elasticsearch:
            condition: service_healthy
    
      grafana:
        depends_on:
          prometheus:
            condition: service_started



Docker Images
~~~~~~~~~~~~~

The docker images used above need to be pulled down prior to starting the network.

* digitalasset/canton-open-source:2.4.2
* docker.elastic.co/elasticsearch/elasticsearch:8.5.2
* docker.elastic.co/kibana/kibana:8.5.2
* docker.elastic.co/logstash/logstash:8.5.1
* grafana/grafana:9.3.1-ubuntu
* postgres:11.18-bullseye
* prom/prometheus:v2.40.6


Running Docker Compose
~~~~~~~~~~~~~~~~~~~~~~

Running `docker compose` with all the compose files shown above makes for quite a long command line. For this reason a helper script, `dc.sh` is used.

It is recommended that the docker is provided with a minimum of **12GB** of memory. To verify docker is not running short of memory run `docker stats` and ensure the total `MEM%` is not too high.

.. code-block:: bash
   :caption: dc.sh

    #!/bin/bash
    
    if [ $# -eq 0 ];then
        echo "Usage: $0 <docker compose command>"
        echo "Use '$0 up --force-recreate --renew-anon-volumes' to re-create network"    
        exit 1
    fi
    
    set -x
    
    docker compose \
        -p monitoring \
        -f etc/network-docker-compose.yml \
        -f etc/elasticsearch-docker-compose.yml \
        -f etc/logstash-docker-compose.yml \
        -f etc/postgres-docker-compose.yml \
        -f etc/domain0-docker-compose.yml \
        -f etc/participant1-docker-compose.yml \
        -f etc/participant2-docker-compose.yml \
        -f etc/kibana-docker-compose.yml \
        -f etc/prometheus-docker-compose.yml \
        -f etc/grafana-docker-compose.yml \
        -f etc/dependency-docker-compose.yml \
        $*
    


**Useful commands**

.. code-block:: bash

     ./dc.sh up -d       # Spins up the network and runs it in the background

     ./dc.sh ps          # Shows the running containers

     ./dc.sh stop        # Stops the containers

     ./dc.sh start       # Starts the containers

     ./dc.sh down        # Stops and tears down the network, removing any created containers

Connecting to Nodes
-------------------

To interact with the running network a the canton console can be used with a remote configuration. For example

.. code-block:: bash

     bin/canton -c etc/remote-participant1.conf

Remote configurations
~~~~~~~~~~~~~~~~~~~~~

.. code-block:: none
   :caption: etc/remote-domain0.conf

    
    canton.remote-domains.domain0 {
      admin-api {
        address="0.0.0.0"
        port="10019"
      }
      public-api {
        address="0.0.0.0"
        port="10018"
      }
    }
    


.. code-block:: none
   :caption: etc/remote-participant1.conf

    canton {
      
      features.enable-testing-commands = yes  // Needed for ledger-api
    
      remote-participants.participant1 {
        ledger-api {
          address="0.0.0.0"
          port="10011"
        }
        admin-api {
          address="0.0.0.0"
          port="10012"
        }
      }
    } 


.. code-block:: none
   :caption: etc/remote-participant2.conf

    canton {
      
      features.enable-testing-commands = yes  // Needed for ledger-api
    
      remote-participants.participant2 {
        ledger-api {
          address="0.0.0.0"
          port="10021"
        }
        admin-api {
          address="0.0.0.0"
          port="10022"
        }
      }
    
    }  


Getting Started
~~~~~~~~~~~~~~~
Using the scripts above it is possible to follow the examples provided in 
the getting the :ref:`Getting Started <canton-getting-started>` guide.

Kibana Log Monitoring
---------------------

When the Kibana is started for the first time a data view needs to be set up to allow the viewing of log data:

   - Navigate to http://localhost:5601/
   - Click 'Explore on my own'
   - From the menu select Analytics -> Discover
   - Click 'Create data view'
   - Save a data view with the following properties:

      * Name: `Logs`
      * Index pattern: `logs-*`
      * Timestamp field: `@timestamp`

You should now have a UI similar to the one shown below.

.. image:: ./images/kibana.png
   :align: center
   :width: 100%

Kibana has a fairly intuitive interface that allows:

   - A view to be created based on selected fields
   - Log messages to be viewed by logging timestamp
   - Filtering by field value
   - Text searching
   - Querying using either `KSQL` or `Lucene` query languages.

For more details see the Kibana documentation. Note that querying based on plain text for a wide time window is likely to result in poor UI performance. See `Logging Improvements`_ for ideas about how this can be improved.

Grafana Metric Monitoring
-------------------------

When the Kibana is started for the first time a data view needs to be set up to allow the viewing of log data:

   - Navigate to http://localhost:3000/login
   - Enter the username/password: `grafana/grafana`
   - In the left hand border select the search icon that has the popup text `Search dashboards`
   - Entering `Message Counts` in the search field should cause a dashboard of the same name to be shown in the results.
   - Select the dashboards. If no activity has happened on the system it will report `No data`.

A simple ping message can be used to create some activity. This can be done by starting a canton console remotely connected to `participant1` and then issuing the command:

   `participant1.health.ping(participant1)`

Once there has been some system activity you should see message count metrics similar to that shown below:

.. image:: ./images/grafana.png
   :align: center
   :width: 100%

See the `Grafana Documentation`_ about how configure dashboards.  For information about which metrics are available see the Metrics documentation in the Monitoring section of this user manual.

Monitoring Choices
------------------
This section documents the reasoning behind the technology used in the example monitoring setup.

Use Docker Log Drivers
~~~~~~~~~~~~~~~~~~~~~~
**Reasons:**

- Most docker containers can be configured to log all debug output to stdout
- Containers can be run as supplied
- No additional dockerfile layers need to be added to install/start log scrapers
- No need to worry about local file naming / log rotation etc

Use GELF Docker Log Driver
~~~~~~~~~~~~~~~~~~~~~~~~~~
**Reasons:**

- It is shipped with docker (so arguably mature)
- Has decodable JSON payload
- Does not have size limitations of syslog
- A UDP listener can be used to debug problems

Use Logstash
~~~~~~~~~~~~
**Reasons:**

- It is a lightweight way to bridge the GELF output provided by the containers into Elasticsearch.
- Simple conceptual model (pipelines consiting of input/filter/output plugins).
- Large ecosystem of input/filter and output plugins.
- It externalizes the logic for mapping container logging output to a structures/ECS format.
- Can be run with `stdin`/`stdout` input/outut plugins for use with testing.
- Can be used to feed Elasiticsearch, Loki or Graylog.
- Has suppport for the Elastic Common Schema (ECS) were this to be needed.

Use Elasticsearch/Kibana
~~~~~~~~~~~~~~~~~~~~~~~~
**Reasons:**

- Using Logstash with Elasticsearch and Kibana, the `ELK`_ stack, is a mature way set up a logging infrastructure. 
- Good defaults for these products allow a basic setup to be started with close to zero configuration.
- The ELK setup acts as a good baseline if comparing to other options such as `Loki`_ or `Graylog`_.

Use Prometheus/Grafana
~~~~~~~~~~~~~~~~~~~~~~
**Reasons:**

- Prometheus defines and uses the `OpenTelemetry`_ reference file format.
- Exposing metrics via an HTTP endpoint allows easy direct inspection of metric values.
- The Prometheus approach of pulling metrics from underlying system means that the running containers to not need infrastructure to store and push metric data.
- Grafana works very well with Prometheus.


Logging Improvements
--------------------
This version of the example only has the logging structure provided via GELF. It is possible to do better than this by:

  - Extracting data from the underlying containers as a JSON stream 
  - Mapping fields in this JSON data onto the `ECS`_ such that the same name is used for commonly used field values (e.g. log level).
  - Configuring Elasticsearch with a schema that allows certain fields to be quickly filtered (e.g. log level).

Glossary
--------

Docker Log Driver
~~~~~~~~~~~~~~~~~
Docker containers can be configured with a log driver that allows log output to be exported out of the docker container. Using log drivers to export logging information means that it is not necessary to run another process on the docker container to do this.

https://docs.docker.com/config/containers/logging/configure/

Syslog
~~~~~~
Syslog is a standard for logging messages that has been around since the 1980s. Syslog is one of the built-in logging drivers supported by docker.

https://en.wikipedia.org/wiki/Syslog

GELF
~~~~
The Graylog extended logging format (GELF) improves on syslog logging by providing structured messages that are not size limited. GELF is one of the built-in logging drivers supported by docker. The message format is compressed JSON.

https://docs.graylog.org/docs/gelf

Docker Plugins
~~~~~~~~~~~~~~
A docker plugin is a way to extend docker, for example by adding an log driver.

https://docs.docker.com/engine/extend/

Loki Log Driver
~~~~~~~~~~~~~~~
The loki log driver is a Loki client that allows log information to be shipped from a docker log file similar to other log drivers. The message format is gRPC protobuf.

https://grafana.com/docs/loki/latest/clients/docker-driver/

Logstash
~~~~~~~~
Logstash is a service that allows a series of pipelines to be configured that read input, filter and manipulate it before writing it out. It has support for a multitude of different input, filter and output types. The GELF input reader and Elasticsearch output writer are of particular interest.

https://www.elastic.co/guide/en/logstash/current/introduction.html

Elasticsearch
~~~~~~~~~~~~~
Elasticsearch is a technology that allows JSON documents to be stored, indexed and searched in near real-time. It can be configured as a cluster with built-in resiliency.

https://www.elastic.co/guide/en/elasticsearch/reference/8.5/index.html

ECS
~~~
The Elastic Common Schema (ECS) defines a naming convention for fields used in Elasticsearch. For example @timestamp should be used for timestamp.

https://www.elastic.co/guide/en/ecs/current/ecs-field-reference.html

MinIO
~~~~~
AWS S3 Compatible Storage (used by Loki).

https://min.io/product/s3-compatibility

ELK
~~~
The ELK stack is an esablished way to enable to capture, indexing and display of log data.

https://www.elastic.co/what-is/elk-stack

Graylog
~~~~~~~
Unlike Elasticsearch Graylog is not a general purpose indexing, analytics and search tool but one that is designed specificially for log data. Doing this allows a simpler more focused proposition with better default for logging. 

https://www.graylog.org/about/

Loki
~~~~
Loki is a log aggregation system designed to store and query logs from all your applications and infrastructure. It displays log information inside Grafana allowing a single UI to be used for both metric data and logs.

https://grafana.com/oss/loki/

Prometheus
~~~~~~~~~~
Prometheus can be configured to scrape metric data from a number of endpoints. This metric data can then be queried by metric visulization tools such as Grafana

https://prometheus.io/


.. _Grafana Documentation:

Grafana
~~~~~~~
Grafana provides a web UI that allows the contruction of dashboards showing metric data. This data can be queried against a Prometheus metric store.

https://grafana.com/grafana/

OpenTelemetry
~~~~~~~~~~~~~
OpenTelemetry is an organisation that works to standardize observability (an umbrella term that includes logging, metrics and tracing).

https://opentelemetry.io/


