..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
..
   Proprietary code. All rights reserved.

.. _docker-instructions:

Work With the Docker Containers
===============================

.. note::

	Please note that the images have moved from ``digitalasset-canton-enterprise-docker.jfrog.io/digitalasset/canton-enterprise``
        to ``digitalasset-docker.jfrog.io/canton-enterprise`` as per version 2.8.0. The old images will remain, but new versions won't 
        be added to the old repository. The open source Canton Docker image is no longer available.

Obtaining the Docker Images
---------------------------

The Canton Docker images are available for the Daml Enterprise. You can download them using

.. code-block:: bash

    docker login digitalasset-docker.jfrog.io
    docker pull digitalasset-docker.jfrog.io/canton-enterprise[:version]

The version is optional, and the latest version is used by default. The version ``dev`` is the the current main build.

Starting Canton
---------------

The canton executable is the default image entry point so all examples using ``bin/canton`` can simply substitute that with ``docker run digitalasset/canton``.

For example, to run a command in interactive console mode, defining a participant on the fly:

.. code-block:: bash

   docker run --rm -it digitalasset-docker.jfrog.io/canton-enterprise:latest \
        --no-tty -C canton.participants.p.ledger-api.port=1234

The ``--rm`` option ensures that the container is removed when the canton process exits.
The ``-it`` options start the container interactively and provide access to our running console.
The ``-no-tty`` option deactivates the ``tty`` mode, as the console is not usable with that mode engaged.

By default Docker will pull the ``latest`` tag containing the latest Canton release.
As Docker will only automatically pull ``latest`` once, ensure you have the latest version by
periodically running ``docker pull digitalasset-docker.jfrog.io/canton-enterprise``.

Configuring Logging and Health Probes
-------------------------------------
The default convention with logging of containers is to have the process to log to ``stdout``. The logging behaviour of Canton can be changed, using appropriate :ref:`command line flags <logging>`, such as ``--log-profile=container``.
The Docker images include a grpc health probe ``/usr/local/bin/grpc_health_probe``, which can be used to setup health checks for Kubernetes.

Administrating the Running Node
-------------------------------
In a Docker based environment, Canton should be run in ``daemon`` mode, while a :ref:`remote console <canton_remote_console>`
can be used to interact with the node.

Exposing the Ledger API or Admin API to the host machine
--------------------------------------------------------

Applications using Canton typically need access to the Ledger or Admin API to read from and write to the ledger.
Each participant binds the Ledger API to the port specified at the configuration key: ``ledger-api.port``.
For ``participant1`` in the simple topology example this is set to port 5011.

To expose the Ledger API to port 5011 on the host machine, run Docker with the following options:

.. code-block:: bash

   docker run --rm -it \
      -p 5011:5011 \
      digitalasset-docker.jfrog.io/canton-enterprise --no-tty \
      -C canton.participants.participant1.ledger-api.address=0.0.0.0 \
      -C canton.participants.participant1.ledger-api.port=5011 \


The Ledger API port for each participant needs to be mapped separately. The same applies to the Admin API.

Supplying custom configuration and DARs
---------------------------------------

To expose files to the Canton container, you must specify a volume mapping from the host machine to the container.

For example, if you have the local directory ``my-application`` containing your custom Canton configuration and DAR:

.. code-block:: bash

   docker run --rm -it \
      --volume "$PWD/my-application:/canton/my-application" \
      digitalasset-docker.jfrog.io/canton-enterprise daemon \
      --config /canton/my-application/my-config.conf

DARs can be loaded using the same container local path or by using the remote console access.

Running Postgres in Docker
--------------------------

Canton requires an appropriate database to persist data. For this purpose, such a database can also be run in a Docker
container using the following, helpful command:

.. code-block:: bash

    docker run -d --rm --name canton-postgres --shm-size=256mb --publish 5432:5432 -e POSTGRES_USER=test-user
        -e POSTGRES_PASSWORD=test-password postgres:14.8-bullseye postgres -c max_connections=500

Please note that the ``--publish`` command allows us to pick the target port which we have to define in the
Canton configuration file. The ``--rm`` will delete the data store once the Docker container is killed. This is
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
using ``psql`` by adding ``--POSTGRES_DB=participant1`` to above Docker command.

