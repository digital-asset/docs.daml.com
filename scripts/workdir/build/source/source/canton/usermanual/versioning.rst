..
     Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates
..
    
..
     Proprietary code. All rights reserved.

.. _canton_versioning:

Versioning
==========

Canton release version
----------------------

The Canton release version (release version for short) is the primary version assigned to a `Canton release <https://github.com/digital-asset/daml/releases>`__.
It is semantically versioned, i.e., breaking changes to a public API will always lead to a major version increase of the release version.
The public APIs encompassed by the release version are the following:

- Ledger API server (for participants)
- Error code format (machine-readable parts, see also :ref:`the error code documentation <error_codes>`)
- Canton configuration file format
- Command line arguments
- Internal storage (data continuity between non-major upgrades)
- Canton protocol version

As a result, Canton components are always safely upgradeable with respect to these APIs. In particular, the inclusion of the Canton protocol version as a Public API guarantees that any two Canton components of the same release version can interact with each other and can be independently upgraded within a major version without any loss of interoperability (see also :ref:`the documentation on the Canton protocol version <protocol_version>`).

For application developers and operators
----------------------------------------
Applications using Canton have the following guarantees:

- Participants can be upgraded independently of each other and of applications and domains within a major release version.
- Domain drivers can be upgraded independently of applications and connected participants within a major release version.
- Major versions of anything are supported for a minimum of 12 months from the release of the next major release version.

As a result, applications written today can keep running unchanged for a minimum of 12 months while upgrading participants and domains within a major release version.
See also the `versioning <https://docs.daml.com/support/releases.html#support-duration>`__ as well as `portability, compatibility and support duration guarantees <https://docs.daml.com/support/compatibility.html>`__ that hold for any Daml application.

For Canton participant and domain operators
-------------------------------------------

In addition to the Canton release version, the Canton protocol version is the most important version for participant and domain operators. It used to have 3 digits, but
starting protocol version `4` it's represented by one digit.

.. _protocol_version:

Canton protocol version
~~~~~~~~~~~~~~~~~~~~~~~
The Canton protocol determines how different Canton components interact with each other. We version it using the Canton protocol version (protocol version for short) and conceptually, two Canton components can interact (are interoperable) if they support the same protocol version.
For example, a participant can connect to a domain if it supports the protocol version that is spoken on the domain, and a mediator can become the mediator for a domain, if it supports the protocol version required by the domain.
If two Canton components have the same major release version, they also share at least one protocol version and can thus interact with each other.

A Canton component advertises the protocol versions it supports and always supports all previous protocol versions of the same major release line.
That is, a participant or driver supporting a certain protocol version, is able to transact with all other participants or drivers supporting a lower or equal protocol version but may not be able to transact with participants or drivers supporting a higher Canton protocol if they are configured to use a more recent version of the protocol.
For example, a release of a participant supporting protocol version `3` will be able to connect to all domains configured to use protocol version <= `3`. It won't be able to connect to a domain configured to use protocol version > `3`.
As a result, minor and patch version upgrades of Canton components can be done independently without any loss of interoperability.

To see the protocol versions a Canton component supports (e.g., `2` and `3`), run

.. code-block:: bash

    canton --version

(where ``canton`` is an alias for the path pointing to the Canton release binary ``bin/canton``).

The list of supported protocol versions for each minor version is the following:

.. _release-version-to-protocol-version-table:

.. list-table::
   :widths: 10 15
   :header-rows: 1
   :align: center

   * - Release
     - Protocol versions
   * - 2.0
     - 2
   * - 2.1
     - 2
   * - 2.2
     - 2
   * - 2.3
     - 2, 3
   * - 2.4
     - 2, 3
   * - 2.5
     - 2, 3, 4
   * - 2.6
     - 2, 3, 4

Features and protocol versions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Some Canton features are only available on domains running specific protocol versions.
The following table indicates the protocol versions required to use some features.

.. list-table::
   :widths: 10 15
   :header-rows: 1
   :align: center

   * - Protocol version
     - Feature
   * - 4 and above
     - `Interfaces <https://docs.daml.com/daml/reference/interfaces.html>`__

Configuring the protocol version
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A Canton driver or domain operator is `able to configure <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/domain/config/DomainParametersConfig.html>`__ the protocol version spoken on the domain (e.g. `3`). If the domain operator sets the protocol version spoken on a domain too high, they may exclude participants that don't support this protocol version yet.

For example, if the domain operator sets the protocol version on a domain to 3, participants that only support protocol version 2 aren't able to connect to the domain.
They would be able to connect and transact on the domain, if the protocol version set on the domain is set to 2 or lower.
Note that if the participant and domain come from the same major release line, the domain will also support using
protocol version 2. Thus, the domain could be configured such that the participant could connect to it

Minimum protocol version
~~~~~~~~~~~~~~~~~~~~~~~~
Similar to how a domain operator is able to configure the protocol version spoken on a domain, a participant operator `is able to configure <https://docs.daml.com/2.6.0/canton/scaladoc/com/digitalasset/canton/participant/config/ParticipantNodeParameters.html>`__ a minimum protocol version for a participant.
Configuring a minimum protocol version guarantees that a participant will only connect to domain that use at least this protocol version or a newer one.
This is especially desirable to ensure that a participant only connects to domains that have certain security patches applied or that support particular protocol features.


.. _ethereum_contract_version:

Ethereum contract version
~~~~~~~~~~~~~~~~~~~~~~~~~
The Ethereum contract version is a 3-digit version tracking the revisions of the `Sequencer.sol contract in the Enterprise Besu
driver <https://www.canton.io/docs/dev/user-manual/architecture/domains/ethereum.html#ethereum-architecture>`__.

A single Canton release may support deploying multiple revisions of the `Sequencer.sol` smart contract for
backwards-compatibility with older releases.

Concretely, the relationship between release version and supported Ethereum contract version is as follows:

.. list-table::
   :widths: 10 15
   :header-rows: 1
   :align: center

   * - Release
     - Ethereum contract versions
   * - 2.0
     - 1.0.0
   * - 2.1
     - 1.0.0
   * - 2.2
     - 1.0.0
   * - 2.3
     - 1.0.0, 1.0.1
   * - 2.4
     - 1.0.0, 1.0.1
   * - 2.5
     - 1.0.0, 1.0.1
   * - 2.6
     - 1.0.0, 1.0.1

Support and bug fixes
~~~~~~~~~~~~~~~~~~~~~
Canton protocol major versions are supported for a minimum of 12 months from the release of the next major version.
Within a major version, only the latest minor version receives security and bug fixes.

