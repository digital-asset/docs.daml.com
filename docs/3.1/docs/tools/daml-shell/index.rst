.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. enterprise-only::

.. _daml-shell-header:

Daml Shell (``daml-shell``)
###########################

Daml Shell is a terminal-based application that enables you to inspect a
Daml ledger by connecting to a live PQS datastore. With Daml Shell, you
can examine current or historical states of the ledger by querying
ledger events, transactions, and contracts. The Daml Shell CLI includes
extensive help via the ``help`` command.

Some of the actions that Daml Shell supports are:

-  Find a specific contract and display it. For example, if you have a
   contract ID, you can use Daml Shell to inspect the corresponding
   contract using the ``contract`` command.
-  Find all events related to a transaction ID. A transaction is
   displayed as a series of ledger events (creates, archives, and
   exercises).
-  Auto-completion for identifiers such as contract IDs, fully qualified
   names, and package names.
-  List active, inactive, or all contracts for a template using a
   template FQN.
-  Apply queries and filters to commands to manage the output.
-  Use the ``compare-contracts`` command to highlight the delta between
   two contract IDs for the same template.

To bound a search, specify a minimum and maximum offset value.

Daml Shell leverages PQS as its datastore and connects using JDBC. For
more information, see
:ref:`configuration`

Getting started
***************

Prerequisites
=============

Daml Shell connects to the PostgreSQL database of a Participant Query
Store (PQS). For setup instructions, see the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__.

Running Daml Shell
==================

You can run Daml Shell from a ``jar`` artifact or from a ``Docker``
image (`tag
list <https://hub.docker.com/repository/docker/digitalasset/daml-shell/tags?ordering=last_updated>`__).

.. code-block:: sh

   docker run -it --net host digitalasset-docker.jfrog.io/daml-shell:<version-tag> # version-tag format: x.y.z

Commands
========

The easiest way to discover commands and filters is to type the ``help``
command while Daml Shell is running.

You can recurse into commands by typing
``help <command> <sub-command> [...]``. Auto-completion at the bottom of
the screen suggests possible command options.

.. image:: images/001-help-output.gif
   :alt: 001-help-output.gif

::

   > help
   NAME
       help - Display usage instructions

   SYNOPSIS
       help [<command>]

   DESCRIPTION
       CLI to interact with a PQS database.
       
       Available commands:
         * active - active contracts
         * archives - archived contracts
         * compare-contracts - compare two contracts
         * connect - connect to JDBC URL
         * contract - contract by ID
         * creates - created contracts
         * disconnect - close database connection
         * exercise - choice by event-id
         * exercises - exercised choices
         * go - upper offset bound
         * help - Display usage instructions
         * net-changes - net contract counts
         * quit - quit the shell
         * set - configure application settings
         * transaction - transaction details
       
       Available filters:
         * csv - transform table data to csv format
         * export - write output to local file
         * grep - filter output by pattern
         * head - take first n lines
         * tail - take last n lines
       
       In addition to above built-in filters, any of the available system binaries
       can be used as filters and will receive the command output as stdin

Filters
=======

You can pipe command output through one or more ``filters`` using the
``|`` (pipe) symbol. For example,
``active Foo:Bar | csv | export ~/my_foos.csv``. If the filter is not
recognized as a built-in filter, Daml Shell uses the system binary of
the same name as the filter if such a binary exists.

.. _configuration:

Configuration
*************

You can configure Daml Shell via CLI arguments, environment variables, a
configuration file, or interactively using the ``set`` command.

Command line arguments
======================

To see available command line options, run Daml Shell with the
``--help`` flag:

.. code-block:: sh

   Usage: daml-shell [options]

     -h, --help               prints this usage text
     --config <file>          HOCON config file with settings as key-value pairs
     --wildcard-char <char>   wildcard character used to abbreviate identifiers. Default: "…"
     --identifier-hash-length <length>
                              Number of characters to render for hashes inside identifiers. Default: 20
     --full-identifiers       Disable identifier shortening.
     --identifier-trim-location <leading|middle|trailing>
                              Where to trim long identifiers. Default: "trailing"
     --disable-color          Disable ANSI colored output.
     --postgres-host <host>   Postgres host to connect to. Implies --connect. Default: "localhost"
     --postgres-port <port>   Postgres port to connect to. Implies --connect. Default: 5432
     --postgres-username <username>
                              Postgres username to connect with. Implies --connect. Default: "postgres"
     --postgres-password <password>
                              Postgres password to connect with. Implies --connect. Default: none
     --postgres-database <name>
                              Postgres database to connect to. Implies --connect. Default: "postgres"
     --postgres-tls-mode <Disable|VerifyCA|VerifyFull>
                              TLS mode for Postgres connection. Implies --connect. Default: "Disable"
     --postgres-tls-cafile <path>
                              Path to the TLS CA file for Postgres connection. Implies --connect. Default: none
     --postgres-tls-cert <path>
                              Path to the TLS certificate file for Postgres connection. Implies --connect. Default: none
     --postgres-tls-key <path>
                              Path to the TLS key file for Postgres connection. Implies --connect. Default: none
     --connect                Auto-connect to the database on startup.

If you specify a ``--postgres-*`` flag, Daml Shell will automatically
connect to the database on startup.

Configuration file
==================

You can set Daml Shell parameters in a reusable configuration file in
HOCON (a JSON superset) using the flag ``--config <filename>``.

Example file content:

.. code-block:: text

   # file: application.conf
   oldest = "start"
   latest = "end"
   identifier-hash-length = 20
   wildcard-char = "…"
   identifier-trim-location = "trailing"
   full-identifiers = false
   disable-color = false
   postgres-host = "localhost"
   postgres-port = 5432
   postgres-username = "postgres"
   postgres-password = "mypassword"
   postgres-database = "postgres"
   postgres-tls-mode = "Disable"

Interactive configuration
=========================

You can configure settings interactively using the ``set`` command.
Example:

::

   > set identifier-hash-length full 
   Disabled identifier shortening

Type ``help set`` or ``help set <setting>`` to learn more about specific
settings.

Usage
*****

This section provides some basic usage examples.

Connecting
==========

Daml Shell leverages PQS as its datastore and connects using JDBC. You
can set connection parameters via configuration parameters or
interactively using a JDBC URL. For more information, see
:ref:`configuration`

To connect interactively, enter the JDBC URL of your PQS PostgreSQL
database. For example:

::

   > connect jdbc:postgresql://localhost/postgres?user=postgres&password=postgres

The status bar shows the connected status, the session offset range, and
the datastore offset range.

.. image:: images/003-connect.gif
   :alt: 003-connect.gif

Offsets
=======

By default, offsets have leading zeroes removed. To see all identifiers
in full, including contract ID hashes, run
``set identifier-hash-length full`` or set a custom length limit for
hashes by running, for example, ``set identifier-hash-length 15``.

Depending on the ledger implementation, offsets may be in hexadecimal
format.

The available offset range from the datastore is specified in the
``Datastore range`` status field. The offset range for Daml Shell to use
to display payload counts and summaries is specified in the
``Session range`` status field.

You can move to different offsets by using the ``go`` command, which is
an alias for ``set latest``. ``go -2`` (go backward two offsets),
``go +2`` (go forward two offsets), ``go forward`` (alias ``go next``),
``go back`` (alias ``go backward``), ``go start``, and ``go end`` are
all examples of valid commands.

The ``net-changes`` command summarizes the changes effected by the
transaction at the current offset. The ``net-changes`` command also
accepts a target ``offset`` argument, or two ``offset`` arguments to
compare between (see ``help net-changes``).

::

   > net-changes 
   +6 myproject:PingPong:Cash
   -6 myproject:PingPong:CashTransferProposal
   +6 myproject:PingPong:IAsset
   -6 myproject:PingPong:IAssetTransferProposal

.. image:: images/003-offset-commands.gif
   :alt: 003-offset-commands.gif

Summary information
===================

Commands such as ``active``, ``archives``, ``creates``, and
``exercises`` can be used without argument to see payload counts by
fully qualified identifier names. For details, run ``help <command>``.

::

   > active
   ┌────────────────────────────────┬───────────┬───────┐
   │ Identifier                     │ Type      │ Count │
   ╞════════════════════════════════╪═══════════╪═══════╡
   │ myproject:PingPong:Cash        │ Template  │    12 │
   ├────────────────────────────────┼───────────┼───────┤
   │ myproject:PingPong:IAsset      │ Interface │    12 │
   ├────────────────────────────────┼───────────┼───────┤
   │ myproject:PingPong:IBounceable │ Interface │   102 │
   ├────────────────────────────────┼───────────┼───────┤
   │ myproject:PingPong:Ping        │ Template  │   102 │
   └────────────────────────────────┴───────────┴───────┘

.. image:: images/003-summary-commands.gif
   :alt: 003-summary-commands.gif

Payloads by fully qualified name
================================

Specify a fully qualified name (FQN) with the command ``active``,
``archives``, ``creates``, or ``exercises`` to list all applicable
payloads for that FQN.

To return payloads from a particular package only, include the package
name in the FQN:

::

   > active myproject:PingPong:Ping

If you omit the package name, payloads from all package names are
returned, as long as they have the same name.

::

   > active PingPong:Ping
   ┌────────────┬──────────────────┬──────────────┬────────────────────────────────────────────────────────────────────────────────────┐
   │ Created at │ Contract ID      │ Contract Key │ Payload                                                                            │
   ╞════════════╪══════════════════╪══════════════╪════════════════════════════════════════════════════════════════════════════════════╡
   │ 8          │ 0022e89289bda36… │              │ label: one                                                                         │
   │            │                  │              │ owner: Alice::12209038d324bf70625c580267d5957cb4c4c03bb7bce294713b48151a4a088afd3b │
   ├────────────┼──────────────────┼──────────────┼────────────────────────────────────────────────────────────────────────────────────┤
   │ a          │ 0093dce322a08c8… │              │ label: one copy updated                                                            │
   │            │                  │              │ owner: Alice::12209038d324bf70625c580267d5957cb4c4c03bb7bce294713b48151a4a088afd3b │
   └────────────┴──────────────────┴──────────────┴────────────────────────────────────────────────────────────────────────────────────┘

The auto-completion provides both FQN variants (with and without package
name).

Filtering with ``where`` clauses
================================

To refine your queries when listing contracts, you can use ``where``
clauses to filter on specific payload fields. ``where`` clauses use a
SQL-like syntax for conditionals and are supported for the ``active``,
``creates``, ``archives``, and ``exercises`` commands.

To access nested fields, use dot notation: ``parent.child.value``

Comparison operators
--------------------

-  ``=`` Equal to
-  ``!=`` Not equal to
-  ``>`` Greater than
-  ``>=`` Greater than or equal to
-  ``<`` Less than
-  ``<=`` Less than or equal to
-  ``like`` Used for pattern matching, ``%`` serves as a wildcard
   character

Logical operators
-----------------

-  ``and``: Both conditions must be satisfied
-  ``or``: Either condition may be satisfied

You can use parentheses to group conditions and direct the order of
evaluation.

Type casting
------------

To ensure proper comparison, you can optionally cast fields to a
specific type using the ``::`` operator. The available casting types are
``numeric``, ``timestamp``, and ``text``.

Field values are sorted and compared lexicographically if no cast is
specified.

``where`` clause examples
-------------------------

Here are some examples of how to use ``where`` clauses in commands:

-  Filter by a string pattern:

   ::

      > active where owner like Alice%

   Lists contracts where the ``owner`` field starts with the string
   ``Alice``.

-  Filter by a nested numeric field:

   ::

      > active where deeply.nested.value :: numeric > 1000

   Lists contracts where the nested field ``value`` is greater than
   ``1000``.

-  Filter with exact string match (note the use of double quotes):

   ::

      > active where label = "loren ipsum"

   Lists contracts where the label field is exactly ``loren ipsum``. Use
   double quotes with values that contain whitespace characters.

-  Combine different conditions:

   ::

      > active where (owner like Bob% or value :: numeric < 100) and myfield = myvalue

   Lists contracts where the ``owner`` starts with ``Bob`` or the
   ``value`` is less than ``100``, and ``myfield`` is ``myvalue``.

.. image:: images/003-where-clause.gif
   :alt: 003-where-clause.gif

Contract lookup
===============

You can look up contracts by contract ID. Interface views are also
displayed, if any.

The contract ID can be copied with the wildcard character (here "…”)
included. The wildcard character will be expanded to any matching ID.

::

   > contract 005188b40…
   ╓──────────────╥────────────────────────────────────────────────────────────────────────────────────╖
   ║ Identifier   ║ myproject:PingPong:Ping                                                            ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Type         ║ Template                                                                           ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Created at   ║ a (not yet active)                                                                 ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Archived at  ║ <active>                                                                           ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Contract ID  ║ 005188b40f981533f8f5…                                                              ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Event ID     ║ #1220731030eb9c81d0d0…:1                                                           ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Contract Key ║                                                                                    ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Payload      ║ label: Copy of: this contract supersedes the original contact                      ║
   ║              ║ owner: Alice::1220b93eaba17d8da363ce7ef1b57d8494910ed4d7c99d2b33887f54832dbb77b5da ║
   ╙──────────────╨────────────────────────────────────────────────────────────────────────────────────╜

   ╓──────────────╥─────────────────────────────────────────────────────────────────────────╖
   ║ Identifier   ║ myproject:PingPong:IBounceable                                          ║
   ╟──────────────╫─────────────────────────────────────────────────────────────────────────╢
   ║ Type         ║ Interface                                                               ║
   ╟──────────────╫─────────────────────────────────────────────────────────────────────────╢
   ║ Created at   ║ a (not yet active)                                                      ║
   ╟──────────────╫─────────────────────────────────────────────────────────────────────────╢
   ║ Archived at  ║ <active>                                                                ║
   ╟──────────────╫─────────────────────────────────────────────────────────────────────────╢
   ║ Contract ID  ║ 005188b40f981533f8f5…                                                   ║
   ╟──────────────╫─────────────────────────────────────────────────────────────────────────╢
   ║ Event ID     ║ #1220731030eb9c81d0d0…:1                                                ║
   ╟──────────────╫─────────────────────────────────────────────────────────────────────────╢
   ║ Contract Key ║                                                                         ║
   ╟──────────────╫─────────────────────────────────────────────────────────────────────────╢
   ║ Payload      ║ ilabel: View of: Copy of: this contract supersedes the original contact ║
   ╙──────────────╨─────────────────────────────────────────────────────────────────────────╜

You can also compare two contracts in a ``diff``-style output format
using the ``compare-contracts <id1> <id2>`` command.

.. image:: images/003-compare-contracts.gif
   :alt: 003-compare-contracts.gif

Transaction lookup
==================

You can look up transactions by either transaction ID or offset, by
running ``transaction <transaction-id>`` or ``transaction at <offset>``,
respectively. Note the ``at`` syntax when looking up by offset.

To display the current transaction at the head of the session offset
range, run ``transaction``.

The ``transaction`` command shows which contracts were created, which
were archived, and what choices were exercised. It also displays the
event ID for each of those events, as well as contract IDs and package
names.

.. image:: images/003-transactions.gif
   :alt: 003-transactions.gif

Exercise lookup
===============

Exercised choices can be looked up in the same manner as contracts,
except that exercises are looked up by their event ID rather than by a
contract ID. The commands for summaries and lookups mirror the
functionality available for contracts.

For example, you can look up exercise counts by FQN:

::

   > exercises 
   ┌─────────────────────────────────────────────────┬───────────────┬───────┐
   │ Identifier                                      │ Type          │ Count │
   ╞═════════════════════════════════════════════════╪═══════════════╪═══════╡
   │ myproject:PingPong:AcceptIAssetTransferProposal │ Consuming     │    12 │
   ├─────────────────────────────────────────────────┼───────────────┼───────┤
   │ myproject:PingPong:ChangeLabel                  │ Consuming     │     1 │
   ├─────────────────────────────────────────────────┼───────────────┼───────┤
   │ myproject:PingPong:Copy                         │ Non-consuming │     1 │
   └─────────────────────────────────────────────────┴───────────────┴───────┘

You can look up exercises for a specific choice:

::

   > exercises PingPong:AcceptIAssetTransferProposal 
   ┌────────┬───────────────────────┬──────────┬────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
   │ Offset │ Contract ID           │ Argument │ Result                                                                                                                                     │
   ╞════════╪═══════════════════════╪══════════╪════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╡
   │ 7b     │ 00604362bf43678ba849… │          │ 004ddbb65e00c8210d978fa13503d877e33d3d83dccc0addea759db1063c089412ca0212205b8a98e1b219436a3a6744eb314e20539b349d61dc09f5e23d880e95b2a1c199 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7b     │ 00549232a251254b6115… │          │ 00b433b6cb4742f0040f9bab57b809dd478d6a73deeaf08ecdd3c30e2be77d98d1ca021220123f4cad1ba5121fa22e43b83ab4c80c0649f51e8a7e776e01b78bc27544cd02 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7b     │ 0063bdaacd598bf2c02f… │          │ 005e908b45701072ed4d0dcf30b9b7b6b233278208078d803edf5fd4502872ce7bca0212201bfb6b375d7fa31a4019ade973a948db52c36ba2a5a239a2d909d12e2ef12968 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7b     │ 00ed039a7747337ddb85… │          │ 005d921fd715007edbbb1b2dfffe56c7d37ba4b6698bdf1357b68749038b3817dcca021220dc08f48d759037f776289c06ae409955f4a2475b3cd0238c3fb5d74da5254e3e │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7b     │ 001207f682120f4798ce… │          │ 00dbe9c12a7ae28f8d12f334ddf9d09bea95a1d55d6a3816f5da5079c71ceb0450ca021220cee4ff410b0e4289301eedeecd82df9f1014796a68c1d4549b8bd72e18464220 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7b     │ 00d5e4f15c3d07cb0785… │          │ 00df079f466b87b61e8b5a6702e6f5b05fecba05513a5559b1b400e4c89903f277ca02122000bcac7e924d0489d144b245c16ba1c95c20a9c293e59dd9290b94df77742a92 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7c     │ 004dc3561fc426de4dad… │          │ 005e1f271e5f5d7a39e623f0774b11cc9295d59693fa53d9953aed726f40e03a81ca021220053c09a2f248902fc48c09492e7fd38c8cf25beacdb803f1ad51444af38bb51c │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7c     │ 00ae24d6c2286768a7b2… │          │ 0059352a66da47b5def7e0653f229dbbb797be70d0485792101fe9aad10f396e70ca021220343d49011f6038af41f3e99792fb318e17ce5ab3227660c932f8043aacfed2bf │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7c     │ 000f02cbb781f76c1877… │          │ 0089b90df5e7085ddb05110eccc9d684e86b96631ff74688ac3f6298cde5f92208ca021220e72fc065a90368000388e41dd8be0672a1078e3329346780e9afb353be100c31 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7c     │ 00126b6f770fb951d666… │          │ 00e9e74240297251e4f9274519ec2cd421fb647af88c13d38bba5f67c67a0f90ffca021220ce3fb55a64f86094dc5fa32e509443ce903fc7f28b2a152a732471819eb56491 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7c     │ 00ab4ff0b42c625d45c5… │          │ 001c00a896e1e66bdb1acbcdeda5f4e00d8a6131c6a86a672809d9831e857ea2e3ca02122001b6efc6e449a2116bc73e333575eaa4dfcaa69be0655ffd3f4eb5b2777960d2 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 7c     │ 0020ab2446d6cfc3f93f… │          │ 00a936fa54cc6fba294962b6fd6c639947f220ab4539c73b6c5c693522e5c5364aca021220104bc750d4800053c090d5b447a6c49d9a49911a4f654fa72c58650b3348e735 │
   └────────┴───────────────────────┴──────────┴────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘

To look up individual exercises, use the event ID:

::

   > exercise #12202cc79ccf1f116ebe…:10
   ╓──────────────╥────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╖
   ║ Event ID     ║ #12202cc79ccf1f116ebe…:10                                                                                                                  ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Choice       ║ myproject:PingPong:AcceptIAssetTransferProposal                                                                                            ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Template FQN ║ myproject:PingPong:IAssetTransferProposal                                                                                                  ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Contract ID  ║ 00d5e4f15c3d07cb0785…                                                                                                                      ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Offset       ║ 7b                                                                                                                                         ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Consuming    ║ true                                                                                                                                       ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Parent       ║                                                                                                                                            ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Argument     ║                                                                                                                                            ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Result       ║ 00df079f466b87b61e8b5a6702e6f5b05fecba05513a5559b1b400e4c89903f277ca02122000bcac7e924d0489d144b245c16ba1c95c20a9c293e59dd9290b94df77742a92 ║
   ╙──────────────╨────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╜

Transforming and exporting command output
*****************************************

You can convert tabular output to CSV by piping it through the ``csv``
filter:

::

   > active PingPong:Ping | csv

You can then write this output to a file by piping it through the
``export`` filter:

::

   > active PingPong:Ping | csv | export ~/my_pings.csv

The ``export`` filter writes any command output to the specified file.
You can use it without the ``csv`` filter.

.. image:: images/003-csv-export.gif
   :alt: 003-csv-export.gif

Setting offset bounds
=====================

The output of ``creates [<fqn>]`` and ``archives [<fqn>]`` can be
bounded by ``set oldest`` (for the lower bound) and ``set latest`` (for
the upper bound). ``go`` is an alias for ``set latest``.

.. image:: images/003-bounded-lookup.gif
   :alt: 003-bounded-lookup.gif

Finding transactions that created or archived a contract
========================================================

Once you know the offsets that a contract was created at (for example,
by using the ``archives`` command), you can look up the relevant
transactions using the ``transaction at <offset>`` command.

.. image:: images/003-from-contract-to-transactions.gif
   :alt: 003-from-contract-to-transactions.gif

FAQ
***

.. _no-archived-contracts:

Why don't I see any archived contracts?
=======================================

If you don't see any archived contracts, PQS might be configured to seed
the database from the ACS, which does not include historical offsets,
archived contracts, or exercised choices.

To see pre-existing archived contracts, seed the database from the
``Transaction Stream`` or ``Transaction Tree Stream``.

For best results, set ``--pipeline-ledger-start`` to ``Genesis`` when
running PQS for the first time (refer to the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__ or
``--help`` output).

Why don't I see any choices?
============================

Choices are only visible on the Ledger API's
``Transaction Tree Stream``. Set ``--pipeline-datasource`` to
``TransactionTreeStream`` when running PQS (refer to the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__ or
``--help`` output).

If you still don't see choices, see :ref:`no-archived-contracts`

Why don't I see any interface views?
====================================

Interfaces are only visible on the Ledger API's ``Transaction Stream``
or ACS (not the ``Transaction Tree Stream``).

Set ``--pipeline-datasource`` to ``TransactionStream`` when running PQS
(refer to the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__ or
``--help`` output).

Why do all contracts show the same ledger offset?
=================================================

See :ref:`no-archived-contracts`
