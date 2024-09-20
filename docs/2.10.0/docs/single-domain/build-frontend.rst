.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Build and Test the Frontend
---------------------------

1. Open a third terminal. Run the following command from the project's root directory to build the frontend:

   .. code-block:: bash

      ./gradlew :app:frontend:assemble

2. Run the tests with a mock backend:

   .. code-block:: bash

      ./gradlew :app:frontend:test

3. Run the linter to check for code quality issues:

   .. code-block:: bash

      ./gradlew :app:frontend:spotlessCheck

4. If linter issues exist, try to fix them with the following command:

   .. code-block:: bash

      ./gradlew :app:frontend:spotlessApply

5. Navigate to ``app/frontend``:

   .. code-block:: bash

      cd app/frontend

6. Start the frontend development server provided through the node package manager to see the app in action:

   .. code-block:: bash

      npm run dev

   This command creates a session on ``localhost:5173`` which connects the frontend to the user's `party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_. You can now log in locally as ``alice``.

   .. image:: images/localhost-alice-terminal.png

7. Navigate to ``localhost:5173`` in an incognito browser window and log in as ``alice``. The username must be all lowercase.

   .. image:: images/localhost-5173-ui.png
      :width: 250px

8. Create a fourth terminal instance. Run the following command from the ``frontend`` directory to connect to the ``provider``'s party:

   .. code-block:: bash

      JSON_API_PORT=4003 npm run dev

   .. image:: images/localhost-provider-terminal.png

   .. note::
      The ``provider``'s session is most likely hosted on ``localhost:5174``

9. Log in as ``provider`` using all lowercase.

   .. image:: images/localhost-5174-ui.png
      :width: 250px

.. important::
   You now have a total of four terminals. You can organize them in four windows or use the terminal's tab feature and cycle through each tab as needed.

   .. image:: images/four-terminals-template.png