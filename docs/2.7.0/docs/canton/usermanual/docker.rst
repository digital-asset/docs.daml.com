..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _docker-instructions:

Running in Docker
=================

Obtaining the Docker Images
---------------------------

The Canton Open Source edition is published to the `digitalasset/canton-open-source dockerhub repository <https://hub.docker.com/r/digitalasset/canton-open-source>`_.
You can pull the Docker image using

.. code-block:: bash

    docker pull digitalasset/canton-open-source[:version]

Here, the version is optional and by default, the latest version is used. The version ``dev`` is the the current main build.
Please note that previous versions were called ``canton-community``, before we renamed the artefact to ``canton-open-source``.

If you want to use the edition included with Daml Enterprise, you can download it using

.. code-block:: bash

    docker login digitalasset-canton-enterprise-docker.jfrog.io
    docker pull digitalasset-canton-enterprise-docker.jfrog.io/digitalasset/canton-enterprise

Starting Canton
---------------

The canton executable is the default image entry point so all examples using ``bin/canton`` can simply substitute that with ``docker run digitalasset/canton``.

For example, to run our example simple topology:

.. code-block:: bash

   docker run --rm -it digitalasset/canton-open-source:latest --config examples/01-simple-topology/simple-topology.conf --bootstrap examples/01-simple-topology/simple-ping.canton

The ``--rm`` option ensures that the container is removed when the canton process exits.
The ``-it`` options start the container interactively and provide a TTY for running our console.

The default working directory of the container is ``/canton``.
This directory contains the same content as the release archive (``daml``, ``dar``, ``examples``).

By default docker will pull the ``latest`` tag containing the latest Canton release.
As docker will only automatically pull ``latest`` once, ensure you have the latest version by  periodically running ``docker pull digitalasset/canton-open-source``.

Previous releases can be run by specifying their tag ``digitalasset/canton-open-source:2.4.0``.

Configuring Logging
-------------------
The default convention with logging of containers is to have the process to log to ``stdout``. Therefore, we change the logging behaviour of Canton using appropriate :ref:`command line flags <logging>`, such as ``--log-profile=container``.

Supplying custom configuration and DARs
---------------------------------------

To expose files to the canton container you must specify a volume mapping from the host machine to the container.

For example, if you have the local directory ``my-application`` containing your custom canton configuration and DAR:

.. code-block:: bash

   docker run --rm -it \
      --volume "$PWD/my-application:/canton/my-application" \
      digitalasset/canton-open-source --config /canton/my-application/my-config.conf

DARs can be loaded using the same container local path.

Exposing the ledger-api to the host machine
-------------------------------------------

Applications using Canton will typically need access to the ledger-api to read from and write to the ledger.
Each participant binds the ledger-api to the port specified at the configuration key: ``ledger-api.port``.
For ``participant1`` in the simple topology example this is set to port 5011.

To expose the ledger-api to port 5011 on the host machine, run docker with the following options:

.. code-block:: bash

   docker run --rm -it \
      -p 5011:5011 \
      digitalasset/canton-open-source \
      -C canton.participants.participant1.ledger-api.address=0.0.0.0 \
      --config examples/01-simple-topology/simple-topology.conf \
      --bootstrap examples/01-simple-topology/simple-ping.canton

The ledger-api port for each participant will need to be mapped separately.

Running Postgres in Docker
--------------------------

Canton requires an appropriate database to persist data. For this purpose, such a database can also be run in a docker
container using the following, helpful command:

.. code-block:: bash

    docker run -d --rm --name canton-postgres --shm-size=256mb --publish 5432:5432 -e POSTGRES_USER=test-user
        -e POSTGRES_PASSWORD=test-password postgres:11 postgres -c max_connections=500

Please note that the ``--publish`` command allows us to pick the target port which we have to define in the
Canton configuration file. The ``--rm`` will delete the data store once the docker container is killed. This is
useful for short-term tests. The ``--shm-size 256mb`` is necessary as Docker will allocate only 64mb of shared memory by
default which is insufficient for the way Canton uses Postgres.

Note that you also need to create the databases yourself, which for
Postgres you can do using ``psql``

.. code-block:: bash

    PGPASSWORD=test-password psql -h localhost -U test-user << EOF
    CREATE DATABASE participant1;
    GRANT ALL ON DATABASE participant1 TO CURRENT_USER;
    EOF

The tables will be managed automatically by Canton. The ``psql`` solution works also if you run multiple nodes on one
Postgres database which all require separate databases. If you run just one node against one database, you can avoid
using ``psql`` by adding ``--POSTGRES_DB=participant1`` to above docker command.
