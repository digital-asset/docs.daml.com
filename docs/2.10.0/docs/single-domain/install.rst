.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Step-by-Step Instructions
=========================

These step-by-step instructions guide you through the setup, customization, and deployment of a Daml application using the `daml-app-template <https://github.com/DACH-NY/daml-app-template/>`_.

Development Environment Set Up
------------------------------

**Install Docker**

1. Open terminal or PowerShell to check if you have Docker installed on your computer:

   .. code-block:: bash

      docker -v

2. If Docker is not installed, follow the download instructions for your operating system in the `Get Docker Docs <https://docs.docker.com/get-docker/>`_.

**Install** `direnv <https://direnv.net/#basic-installation>`_

1. Find the direnv `package or binary <https://direnv.net/docs/installation.html>`_ for your operating system.
2. Hook `direnv into your shell <https://direnv.net/docs/hook.html>`_.

**Install Nix**

1. Install Nix by following the `Nixos.org download instructions <https://nixos.org/download.html>`_.
2. Enable support for Nix flakes and the Nix command:

   a. Open a file editor in the terminal:

      .. code-block:: bash

         sudo vim /etc/nix/nix.conf

      *If you installed a single user version of nix, the file to edit is located at:*

      .. code-block:: bash

         sudo vim ~/.config/nix/nix.conf

   b. Add the following line to the nix.conf file:

      .. code-block:: text

         extra-experimental-features = nix-command flakes

   Helpful vim commands:

   - ``i`` - insert text
   - ``esc`` - escape insert, enter command mode
   - ``:w`` - write to disk (save)
   - ``:x`` - exit

Install the Application
-----------------------

**Clone the Repository**

1. Open your terminal and run the following command to clone the ``daml-app-template`` repository:

   .. code-block:: bash

      git clone https://github.com/DACH-NY/daml-app-template
      cd daml-app-template

   *If you use SSH with GitHub, the ``git clone`` command is:*

   .. code-block:: bash

      git clone git@github.com:DACH-NY/daml-app-template.git

2. Pull down the submodules required by the template (This step may require a few seconds):

   .. code-block:: bash

      git submodule update --init

**Configure Artifactory credentials**

1. Generate an Artifactory Identity Token with `JFROG <https://digitalasset.jfrog.io/ui/admin/artifactory/user_profile>`_:

   .. note::
      If this is your first time setting up Daml, you may need permissions from Digital Asset.
      Email `support@digitalasset.com <support@digitalasset.com>`_ and ask for Artifactory permissions.

   a. Once you have secured an authorized JFROG account, set up your user profile and identity token.
   b. Select the user profile icon in the top right corner, then select "**Edit Profile**".

      .. image:: images/jfrog-dashboard.png

   c. The user profile is displayed in the top left corner. This is most likely the email address you used to register an account. On the same screen, under "**Authentication Settings**" click the "**Generate an Identity Token**" button.

      .. image:: images/jfrog-artifactory-profile.png

   d. Enter a description to identify the token in the future, then select "**Next**."

      .. image:: images/jfrog-generate-token.png

   e. A token is generated and displayed. Copy the Reference Token. Store it in a safe place. The token cannot be retrieved after the window is closed.

      .. image:: images/jfrog-artifactory-new-token.png

2. Add the username and identity token credentials to a new file named ``.envrc.private``:

   .. code-block:: bash

      vim .envrc.private

   Replace the default values, but keep the quotation marks:

   .. code-block:: bash

      export ARTIFACTORY_USER="yourartifactoryusername"
      export ARTIFACTORY_PASSWORD="yourartifactoryidentitytoken"

   The following is an example of what the contents of the ``.envrc.private`` file may look like.
   Replace the username with your email and the password with your identity token.

   .. code-block:: bash

      export ARTIFACTORY_USER="user@domain.com"
      export ARTIFACTORY_PASSWORD="ijMDQ5ijd1MBW6fTwkZ0T"


   This information is private and should not be committed to the repository. Check that ``.envrc.private`` is included in ``.gitignore``:

   .. code-block:: bash

      cat .gitignore

3. Quit and restart the terminal for the updates to take effect.

4. Verify the username and password are properly linked:

   .. code-block:: bash

      echo $ARTIFACTORY_PASSWORD | docker login digitalasset-http-json-docker.jfrog.io -u "$ARTIFACTORY_USER" --password-stdin

   If successful, it returns "``Login Succeeded``".

   .. note::
      Start the Docker engine if the command returns:
      "Cannot connect to the Docker daemon at unix:///Users/bame/.docker/run/docker.sock. Is the docker daemon running?"

5. From the root directory, run ``direnv allow`` (This command may take several seconds to process):

   .. code-block:: bash

      direnv allow

   The output should look similar to the following. Details may differ, but you should see "``direnv: using flake_subdir``" in the output:

   .. code-block:: text

      direnv: loading ~/../daml/daml-app-template/.envrc                
      direnv: using flake_subdir
      evaluating derivation 'path:nix#devShells.aarch64-darwin.default'
      direnv: ([/opt/homebrew/bin/direnv export zsh]) is taking a while to execute. Use CTRL-C to give up.
      direnv: loading ~/../daml/daml-app-template/.envrc.vars
      direnv: loading ~/../daml/daml-app-template/.envrc.private
      direnv: export +AR +ARTIFACTORY_PASSWORD +ARTIFACTORY_USER +AS +AUTH0_DOMAIN +CC +CLASSPATH +CLOUDSDK_COMPUTE_REGION +CLOUDSDK_CORE_PROJECT +COMPOSE_FILE +CONFIG_SHELL +CXX 
      ...
      +propagatedNativeBuildInputs +shell +shellHook +stdenv +strictDeps +system ~JAVA_HOME ~PATH ~XDG_DATA_DIRS

**Install the Daml SDK**

1. From the root directory, run the following command to install the `Daml SDK <https://docs.daml.com/getting-started/installation.html>`_:

   .. code-block:: bash

      curl -sSL https://get.daml.com/ | sh -s ${DAML_SDK_RELEASE_VERSION}

   ``DAML_SDK_RELEASE_VERSION`` refers to the value in ``.envrc.vars``. Use the ``cat`` command in the terminal to find the correct release version:

   .. code-block:: bash

      cat .envrc.vars

   Find the version stored in ``export DAML_SDK_RELEASE_VERSION=``

   .. image:: images/DAML_SDK_RELEASE_VERSION.png

2. After installation, add Daml to your PATH in your shell configuration file (``.zshrc`` or ``.bashrc`` depending on your system) if it wasn't added automatically:

   a. To edit the file in the terminal or PowerShell, enter ``vim ~/.bashrc`` or ``vim ~/.zshrc``.
   b. If you don't know which shell your system runs, find the appropriate file by entering ``ls -a ~/.`` in the command prompt.
   c. In the shell configuration file, add:

      .. code-block:: bash

         export PATH=$PATH:$HOME/.daml/bin 

   d. Save and exit the file then restart the terminal to complete the update.

3. Verify installation by entering ``daml version`` in the terminal. This should return the Daml SDK version.

Build and Test
~~~~~~~~~~~~~~

Daml Finance `Dar files <https://docs.daml.com/concepts/glossary.html#dar-file-dalf-file>`_ are automatically fetched, cached, and managed by Gradle, with versioning defined within the ``app/daml/build.gradle.kts`` file.

1. Verify that the Gradle Build Tool is installed by checking the version in the project's root directory:

   .. code-block:: bash

      ./gradlew -v

   Sample output:

   .. code-block:: text

      daml-app-template ~ % ./gradlew -v

      ------------------------------------------------------------
      Gradle 8.2.1
      ------------------------------------------------------------

      Build time:   2023-07-10 12:12:35 UTC
      Revision:     a38ec64d3c4612da9083cc506a1ccb212afeecaa

      Kotlin:       1.8.20
      Groovy:       3.0.17
      Ant:          Apache Ant(TM) version 1.10.13 compiled on January 4 2023
      JVM:          17.0.3 (Azul Systems, Inc. 17.0.3+7-LTS)
      OS:           Mac OS X 13.6.1 aarch64

   If the command fails, install Gradle by following the `Gradle Build Tool installation instructions <https://gradle.org/install/>`_.

2. Build the ``daml-app-template.dar`` and ``daml-app-template-tests.dar`` files from the sources:

   .. code-block:: bash

      ./gradlew :app:daml:assemble

3. Test all of the Daml test dars in the root directory. Tests should return ``BUILD SUCCESSFUL``:

   .. code-block:: bash

      ./gradlew :app:daml:test