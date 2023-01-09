.. Copyright (c) 2022 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _module-daml-trigger-assert-86642:

Daml.Trigger.Assert
===================

Data Types
----------

.. _type-daml-trigger-assert-acsbuilder-13690:

**data** `ACSBuilder <type-daml-trigger-assert-acsbuilder-13690_>`_

  Used to construct an 'ACS' for 'testRule'\.

  **instance** `Monoid <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-monoid-6742>`_ `ACSBuilder <type-daml-trigger-assert-acsbuilder-13690_>`_

  **instance** `Semigroup <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-prelude-semigroup-78998>`_ `ACSBuilder <type-daml-trigger-assert-acsbuilder-13690_>`_

Functions
---------

.. _function-daml-trigger-assert-toacs-87773:

`toACS <function-daml-trigger-assert-toacs-87773_>`_
  \: `Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t \=\> `ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t \-\> `ACSBuilder <type-daml-trigger-assert-acsbuilder-13690_>`_

  Include the given contract in the 'ACS'\. Note that the ``ContractId``
  must point to an active contract\.

.. _function-daml-trigger-assert-testrule-46106:

`testRule <function-daml-trigger-assert-testrule-46106_>`_
  \: :ref:`Trigger <type-daml-trigger-trigger-91122>` s \-\> `Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_ \-\> \[`Party <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-party-57932>`_\] \-\> `ACSBuilder <type-daml-trigger-assert-acsbuilder-13690_>`_ \-\> `Map <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-map-90052>`_ :ref:`CommandId <type-daml-trigger-lowlevel-commandid-51507>` \[:ref:`Command <type-daml-trigger-lowlevel-command-96878>`\] \-\> s \-\> Script (s, \[:ref:`Commands <type-daml-trigger-lowlevel-commands-84262>`\])

  Execute a trigger's rule once in a scenario\.

.. _function-daml-trigger-assert-flattencommands-11861:

`flattenCommands <function-daml-trigger-assert-flattencommands-11861_>`_
  \: \[:ref:`Commands <type-daml-trigger-lowlevel-commands-84262>`\] \-\> \[:ref:`Command <type-daml-trigger-lowlevel-command-96878>`\]

  Drop 'CommandId's and extract all 'Command's\.

.. _function-daml-trigger-assert-assertcreatecmd-38375:

`assertCreateCmd <function-daml-trigger-assert-assertcreatecmd-38375_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `CanAbort <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-canabort-29060>`_ m) \=\> \[:ref:`Command <type-daml-trigger-lowlevel-command-96878>`\] \-\> (t \-\> `Either <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-types-either-56020>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ ()) \-\> m ()

  Check that at least one command is a create command whose payload fulfills the given assertions\.

.. _function-daml-trigger-assert-assertexercisecmd-57703:

`assertExerciseCmd <function-daml-trigger-assert-assertexercisecmd-57703_>`_
  \: (`Template <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-template-31804>`_ t, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r, `CanAbort <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-canabort-29060>`_ m) \=\> \[:ref:`Command <type-daml-trigger-lowlevel-command-96878>`\] \-\> ((`ContractId <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-lf-contractid-95282>`_ t, c) \-\> `Either <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-types-either-56020>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ ()) \-\> m ()

  Check that at least one command is an exercise command whose contract id and choice argument fulfill the given assertions\.

.. _function-daml-trigger-assert-assertexercisebykeycmd-14954:

`assertExerciseByKeyCmd <function-daml-trigger-assert-assertexercisebykeycmd-14954_>`_
  \: (`TemplateKey <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-templatekey-95200>`_ t k, `Choice <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-internal-template-functions-choice-82157>`_ t c r, `CanAbort <https://docs.daml.com/daml/stdlib/Prelude.html#class-da-internal-lf-canabort-29060>`_ m) \=\> \[:ref:`Command <type-daml-trigger-lowlevel-command-96878>`\] \-\> ((k, c) \-\> `Either <https://docs.daml.com/daml/stdlib/Prelude.html#type-da-types-either-56020>`_ `Text <https://docs.daml.com/daml/stdlib/Prelude.html#type-ghc-types-text-51952>`_ ()) \-\> m ()

  Check that at least one command is an exercise by key command whose key and choice argument fulfill the given assertions\.

