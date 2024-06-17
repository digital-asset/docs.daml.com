..
   Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
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

- Participants can be upgraded independently of each other and of applications and sync domains within a major release version.
- Sync domain drivers can be upgraded independently of applications and connected participants within a major release version.
- Major versions of anything are supported for a minimum of 12 months from the release of the next major release version.

As a result, applications written today can keep running unchanged for a minimum of 12 months while upgrading participants and sync domains within a major release version.
See also the `versioning <https://docs.daml.com/support/releases.html#support-duration>`__ as well as `portability, compatibility and support duration guarantees <https://docs.daml.com/support/compatibility.html>`__ that hold for any Daml application.

For Canton participant and synchronization domain operators
-----------------------------------------------------------

In addition to the Canton release version, the Canton protocol version is the most important version for participant and sync domain operators. It used to have 3 digits, but
starting protocol version `4` it's represented by one digit.

.. _protocol_version:

Canton protocol version
~~~~~~~~~~~~~~~~~~~~~~~
The Canton protocol determines how different Canton components interact with each other. We version it using the Canton protocol version (protocol version for short) and conceptually, two Canton components can interact (are interoperable) if they support the same protocol version.
For example, a participant can connect to a sync domain if it supports the protocol version that is spoken on the sync domain, and a mediator can become the mediator for a sync domain, if it supports the protocol version required by the sync domain.
If two Canton components have the same major release version, they also share at least one protocol version and can thus interact with each other.

A Canton component advertises the protocol versions it supports and always supports all previous protocol versions of the same major release line.
That is, a participant or driver supporting a certain protocol version can transact with all other participants or drivers supporting a lower or equal protocol version but may not be able to transact with participants or drivers supporting a higher Canton protocol if they are configured to use a more recent version of the protocol.
For example, a release of a participant supporting protocol version `3` will be able to connect to all sync domains configured to use protocol version <= `3`. It won't be able to connect to a sync domain configured to use protocol version > `3`.
As a result, minor and patch version upgrades of Canton components can be done independently without any loss of interoperability.

To see the protocol versions a Canton component supports (e.g., `2` and `3`), run

.. code-block:: bash

    canton --version

(where ``canton`` is an alias for the path pointing to the Canton release binary ``bin/canton``).

The list of supported protocol versions for each minor version is the following:

.. _release-version-to-protocol-version-table:

(*) The protocol version marked with `*` is the preview protocol version. To use a preview protocol version, follow the  :ref:`documentation <how-do-i-enable-preview-features>`.

.. include:: /canton/includes/generated/versioning.rst.inc

Features and protocol versions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Some Canton features are only available on sync domains running specific protocol versions.
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
A Canton driver or sync domain operator is `able to configure <https://docs.daml.com/__VERSION__/canton/scaladoc/com/digitalasset/canton/domain/config/DomainParametersConfig.html>`__ the protocol version spoken on the sync domain (e.g. `3`). If the sync domain operator sets the protocol version spoken on a sync domain too high, they may exclude participants that do not support this protocol version yet.

For example, if the sync domain operator sets the protocol version on a sync domain to 3, participants that only support protocol version 2 aren't able to connect to the sync domain.
They would be able to connect and transact on the sync domain if the protocol version set on the sync domain is set to 2 or lower.
Note that if the participant and sync domain come from the same major release line, the sync domain will also support using
protocol version 2. Thus, the sync domain could be configured such that the participant could connect to it

Minimum protocol version
~~~~~~~~~~~~~~~~~~~~~~~~
Similar to how a sync domain operator is able to configure the protocol version spoken on a sync domain, a participant operator `is able to configure <https://docs.daml.com/__VERSION__/canton/scaladoc/com/digitalasset/canton/participant/config/ParticipantProtocolConfig.html>`__ a minimum protocol version for a participant.
Configuring a minimum protocol version guarantees that a participant will only connect to a synchronzer that uses at least this protocol version or a newer one.
This is especially desirable to ensure that a participant only connects to sync domains that have certain security patches applied or that support particular protocol features.

Support and bug fixes
~~~~~~~~~~~~~~~~~~~~~
Canton protocol major versions are supported for a minimum of 12 months from the release of the next major version.
Within a major version, only the latest minor version receives security and bug fixes.

