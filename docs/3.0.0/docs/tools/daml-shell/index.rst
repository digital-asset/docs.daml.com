.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Daml Shell User Guide
#####################

Getting Started
===============

Prerequisites
-------------

Daml Shell connects to the PostgreSQL database of a Participant Query
Store (PQS). Please refer to the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__ for
setup instructions.

Running Daml Shell
------------------

Daml Shell can be run from a ``jar`` artifact or from a ``Docker`` image
(`tag
list <https://hub.docker.com/repository/docker/digitalasset/daml-shell/tags?ordering=last_updated>`__).

.. code:: sh

   docker run -it --net host docker.io/digitalasset/daml-shell:<version-tag> # change --net host if desired

Commands
--------

The easiest way to discover commands is to type the ``help`` command
while Daml Shell is running.

You can recurse into commands by typing
``help <command> <sub-command> ...``. Auto-completion at the bottom of
the screen will suggest possible command options.

.. figure:: images/001-help-output.gif?raw=true
   :alt: Help

   Help

::

   > help
   NAME
       help - Display usage instructions

   SYNOPSIS
       help [<command>]

   DESCRIPTION
       CLI to interact with a Scribe database.
       
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
         * net-changes - net contract counts
         * set - configure application settings
         * transaction - transaction details

FAQ
===

   **Why do I not see any archived contracts?**

This is likely because PQS has been configured to seed the database from
the ACS, which does not include historical offsets, archived contracts,
or exercised choices.

To see pre-existing archived contracts, the database needs to be seeded
from the ``Transaction Stream`` or ``Transaction Tree Stream``.

Solution: Set ``--pipeline-ledger-start`` to ``Genesis`` when running
PQS for the first time (refer to the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__ or
``--help`` output).

   **Why do I not see any choices?**

Choices are only visible on the Ledger API’s
``Transaction Tree Stream``. Set ``--pipeline-datasource`` to
``TransactionTreeStream`` when running PQS (refer to the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__ or
``--help`` output).

   **Why do I still not see any choices?**

See ``Why do I not see any archived contracts`` above.

   **Why do I not see any interface views?**

Interfaces are only visible on the Ledger API’s ``Transaction Stream``
or ACS (not the ``Transaction Tree Stream``).

Set ``--pipeline-datasource`` to ``TransactionStream`` when running PQS
(refer to the `PQS
documentation <https://docs.daml.com/query/pqs-user-guide.html>`__ or
``--help`` output).

   **Why do all contracts show the same ledger offset?**

See ``Why do I not see any archived contracts`` above.# Configuration

Daml Shell can be configured via CLI arguments, environment variables,
through a configuration file, or interactively using the ``set``
command.

Command line arguments
----------------------

To see available command line options, run Daml Shell with the
``--help`` flag:

.. code:: sh

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

Configuration file
------------------

These configuration parameters can also be set in a reusable
configuration file in HOCON (a JSON superset) using the flag
``--config <filename>``.

Example file content:

.. code:: hocon

   # file: application.conf
   oldest = "start"
   latest = "end"
   identifier-hash-length = 20
   wildcard-char = "…"
   identifier-trim-location = "trailing"
   full-identifiers = false
   disable-color = false

Interactively
-------------

Settings can be configured interactively using the ``set`` command.
Example:

::

   > set identifier-hash-length full 
   Disabled identifier shortening

Type ``help set`` or ``help set <setting>`` to find out more about
specific settings.# Usage

This document describes some basic usage examples.

Setup
~~~~~

Please refer to the `Getting Started <001-getting-started.md>`__ guide.

Connecting
~~~~~~~~~~

We connect by entering the JDBC URL of our PQS postgres database. For
example:

::

   > connect jdbc:postgresql://localhost/postgres?user=postgres&password=postgres

The status bar shows the connected status, the session offset range, and
the datastore offset range.

.. figure:: images/003-connect.gif?raw=true
   :alt: Connect

   Connect

Offsets
~~~~~~~

By default, offsets have leading zeroes removed. To see all identifiers
in full, including contract ID hashes, you can run
``set identifier-hash-length full``, or set a custom length limit for
hashes by running, for example, ``set identifier-hash-length 15``.

Depending on the ledger implementation, offsets may be in hexadecimal
format.

The available offset range from the data-store is given in the
``Datastore range`` status field. The offset range for Daml Shell to use
to display payload counts and summaries is given by the
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
   +3 PingPong:Cash [89a08f0324025f1…]
   -3 PingPong:CashTransferProposal [89a08f0324025f1…]
   +3 PingPong:IAsset [89a08f0324025f1…]
   -3 PingPong:IAssetTransferProposal [89a08f0324025f1…]

.. figure:: images/003-offset-commands.gif?raw=true
   :alt: Connect

   Connect

Summary information
~~~~~~~~~~~~~~~~~~~

Commands such as ``active``, ``archives``, ``creates``, and
``exercises`` can be used without argument to see payload counts by
fully qualified identifier names. You can run ``help <command>`` to find
out what each of them does.

::

   > active
   ┌─────────────────────────────────────────┬───────────┬───────┐
   │ Identifier                              │ Type      │ Count │
   ╞═════════════════════════════════════════╪═══════════╪═══════╡
   │ PingPong:Cash [89a08f0324025f1…]        │ Template  │     6 │
   ├─────────────────────────────────────────┼───────────┼───────┤
   │ PingPong:IAsset [89a08f0324025f1…]      │ Interface │     6 │
   ├─────────────────────────────────────────┼───────────┼───────┤
   │ PingPong:IBounceable [89a08f0324025f1…] │ Interface │     2 │
   ├─────────────────────────────────────────┼───────────┼───────┤
   │ PingPong:Ping [89a08f0324025f1…]        │ Template  │     2 │
   └─────────────────────────────────────────┴───────────┴───────┘

.. figure:: images/003-summary-commands.gif?raw=true
   :alt: Summary commands

   Summary Commands

Payloads by fully qualified name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Adding a fully qualified name (FQN) after any of the ``active``,
``archives``, ``creates``, or ``exercises`` commands will list all
applicable payloads for that FQN.

The package ID can be included in the FQN, in which case only payloads
from that particular package will be returned, e.g.

::

   > active 89a08f0324025f1254f09edc0195ca24459c6302e88d2b9f636d2be5a615d1f1:PingPong:Ping

or the package ID can be omitted, in which case payloads from all
package IDs are returned, as long as they have the same name.

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

The auto-completion provides both variants, FQN with and without package
IDs.

Contract lookup
~~~~~~~~~~~~~~~

Contracts can be looked up by contract ID. Interface views will also be
displayed, if any.

The contract ID can be copied with the wildcard character (here “…”)
included. The wildcard character will be expanded to any matching ID.

::

   > contract 0093dce322a08c8…
   ╓──────────────╥────────────────────────────────────────────────────────────────────────────────────╖
   ║ Identifier   ║ PingPong:Ping [89a08f0324025f1…]                                                   ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Type         ║ Template                                                                           ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Created at   ║ a                                                                                  ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Archived at  ║ <active>                                                                           ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Contract ID  ║ 0093dce322a08c8…                                                                   ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Event ID     ║ #122099ed6675f2e…:1                                                                ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Contract Key ║                                                                                    ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────╢
   ║ Payload      ║ label: one copy updated                                                            ║
   ║              ║ owner: Alice::12209038d324bf70625c580267d5957cb4c4c03bb7bce294713b48151a4a088afd3b ║
   ╙──────────────╨────────────────────────────────────────────────────────────────────────────────────╜

   ╓──────────────╥─────────────────────────────────────────╖
   ║ Identifier   ║ PingPong:IBounceable [89a08f0324025f1…] ║
   ╟──────────────╫─────────────────────────────────────────╢
   ║ Type         ║ Interface                               ║
   ╟──────────────╫─────────────────────────────────────────╢
   ║ Created at   ║ a                                       ║
   ╟──────────────╫─────────────────────────────────────────╢
   ║ Archived at  ║ <active>                                ║
   ╟──────────────╫─────────────────────────────────────────╢
   ║ Contract ID  ║ 0093dce322a08c8…                        ║
   ╟──────────────╫─────────────────────────────────────────╢
   ║ Event ID     ║ #122099ed6675f2e…:1                     ║
   ╟──────────────╫─────────────────────────────────────────╢
   ║ Contract Key ║                                         ║
   ╟──────────────╫─────────────────────────────────────────╢
   ║ Payload      ║ ilabel: view one copy updated           ║
   ╙──────────────╨─────────────────────────────────────────╜

You can also compare two contracts in a ``diff``-style output format
using the ``compare-contracts <id1> <id2>`` command.

.. figure:: images/003-compare-contracts.gif?raw=true
   :alt: compare-contracts

   compare-contracts

Transaction lookup
~~~~~~~~~~~~~~~~~~

Transactions can be looked up either by transaction ID or by offset,
i.e., by running ``transaction <transaction-id>`` or
``transaction at <offset>`` respectively. Note the “``at``” when looking
up by offset.

The current transaction, at the head of the session offset range, can be
displayed by just running ``transaction``.

The ``transaction`` command will show which contracts were created,
which ones were archived, and what choices were exercised. It will also
display the event ID for each of those events, as well as contract IDs
and package IDs!

.. figure:: images/003-transactions.gif?raw=true
   :alt: compare-contracts

   compare-contracts

Exercise lookup
~~~~~~~~~~~~~~~

Exercised choices can be looked up in the same manner as contracts,
except that exercises are looked up by their event ID rather than by a
contract ID. The commands for summaries and lookups mirror the
functionality available for contracts.

For example, exercise counts by FQN can be looked up like this:

::

   > exercises 
   ┌───────────────────────────────────────────────────────────────┬───────────────┬───────┐
   │ Identifier                                                    │ Type          │ Count │
   ╞═══════════════════════════════════════════════════════════════╪═══════════════╪═══════╡
   │ PingPong:AcceptIAssetTransferProposal [89a08f0324025f1254f0…] │ Consuming     │     6 │
   ├───────────────────────────────────────────────────────────────┼───────────────┼───────┤
   │ PingPong:ChangeLabel [89a08f0324025f1254f0…]                  │ Consuming     │     1 │
   ├───────────────────────────────────────────────────────────────┼───────────────┼───────┤
   │ PingPong:Copy [89a08f0324025f1254f0…]                         │ Non-consuming │     1 │
   └───────────────────────────────────────────────────────────────┴───────────────┴───────┘

Exercises for a specific choice can be looked up like this:

::

   > exercises PingPong:AcceptIAssetTransferProposal 
   ┌────────┬───────────────────────┬──────────┬────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
   │ Offset │ Contract ID           │ Argument │ Result                                                                                                                                     │
   ╞════════╪═══════════════════════╪══════════╪════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╡
   │ 11     │ 005b18f0298576b2bf7d… │          │ 004af1af7f4c64f57b5eb52c95dcc686174d8939c0d3870f5b5f648acf16ec1774ca02122000ddecd621a6c304a9354c1cd6b6726e9815aed0fb9391395cac33ae2c846955 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 11     │ 003c2ae213b3149463f2… │          │ 002ad4f09e7b5e6d8f11fecb57f5da2be7ab8bce01adf86eabda86b79d3266e738ca0212201dd16c97b501db848761792e824cbd80a3e6767e4191b140287ba7ed32d2d807 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 11     │ 0022e9065ca19b435611… │          │ 0027d45f1732d8a044eb370eb5d19e27c913de4a6e5fd7026cef165dff71534481ca02122072decfd063e0508af764eb0e0e171125a2bb62abf9b877fc33f4bea39ce289e2 │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 12     │ 00bc1500e6c781559ad1… │          │ 00a8753f0ccbc503ab393dae99d7ca982b15f1429b61739c03dad299d123f21e5aca02122090c1f0e10da810f4ee1a961a91701863dd22f9f360f676725540929069cee17e │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 12     │ 001495835b90270f9699… │          │ 00ea78410739637ad2460e65ddf9382d2eef8d9a33a2ce38f912eaba065a342ebbca021220f5ffe34193c016a242a41735bf9670cf585a61e7423766bedbb15e92c6ea83be │
   ├────────┼───────────────────────┼──────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
   │ 12     │ 00844b2f4a2fb8ff73fe… │          │ 00bc875c5ee7cc6adb11a48a2cb4272e4374affa94f23cb8a7b358946f3bd5c4b4ca0212209cb5521de33a5a2d931e0b97a312753d772e55529bc086e0fb75376123131b6f │
   └────────┴───────────────────────┴──────────┴────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘

Individual exercises can be looked up by event ID:

::

   > exercise #12206159b8de32b97edb…:0
   ╓──────────────╥────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╖
   ║ Event ID     ║ #12206159b8de32b97edb…:0                                                                                                                   ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Choice       ║ PingPong:AcceptIAssetTransferProposal [89a08f0324025f1254f0…]                                                                              ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Template FQN ║ PingPong:CashTransferProposal [89a08f0324025f1254f0…]                                                                                      ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Contract ID  ║ 00bc1500e6c781559ad1…                                                                                                                      ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Offset       ║ 12                                                                                                                                         ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Consuming    ║ true                                                                                                                                       ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Witnesses    ║ Bank::12204b77186b76c16e1c…, Bob::12204b77186b76c16e1c…                                                                                    ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Parent       ║                                                                                                                                            ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Argument     ║                                                                                                                                            ║
   ╟──────────────╫────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
   ║ Result       ║ 00a8753f0ccbc503ab393dae99d7ca982b15f1429b61739c03dad299d123f21e5aca02122090c1f0e10da810f4ee1a961a91701863dd22f9f360f676725540929069cee17e ║
   ╙──────────────╨────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╜

Setting offset bounds
~~~~~~~~~~~~~~~~~~~~~

The output of ``creates [<fqn>]`` and ``archives [<fqn>]`` can be
bounded by ``set oldest`` (for the lower bound) and ``set latest`` (for
the upper bound). ``go`` is an alias for ``set latest``.

.. figure:: images/003-bounded-lookup.gif?raw=true
   :alt: bounded lookup

   bounded lookup

Finding transactions that created/archived a contract
=====================================================

Once you know the offsets that a contract was created at, for example by
using the ``archives`` command, you can look up the relevant
transactions using the ``transaction at <offset>`` command.

.. figure:: images/003-from-contract-to-transactions.gif?raw=true
   :alt: event transaction

   event transactions
