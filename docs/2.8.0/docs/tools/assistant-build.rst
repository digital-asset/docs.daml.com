.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _assistant-manual-building-dars:

Build Daml Projects
###################

Build a project
*******************

To compile your Daml source code into a Daml archive (a ``.dar`` file), run::

  daml build

You can control the build by changing your project's ``daml.yaml``:

``sdk-version``
  The SDK version to use for building the project.

``name``
  The name of the project.

``source``
  The path to the source code.

The generated ``.dar`` file is created in ``.daml/dist/${name}.dar`` by default. To override the default location, pass the ``-o`` argument to ``daml build``::

  daml build -o path/to/darfile.dar


Build multiple packages
***********************

*New multi-package build content goes here!*
