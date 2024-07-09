.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _upgrade_model_reference:

The Upgrade Model in Depth - Reference
======================================

This section describes in detail what rules govern package validation upon
upload and how contracts, choice arguments and choice results are upgraded or
downgraded at runtime. These topics are for a large part covered in the
sections above. This section acts as a thorough reference.

Static Checks
-------------

Upgrade static checks are performed once alongside other validity checks
when a DAR is uploaded to a participant. DARs deemed invalid for
upgrades are rejected.

DAR upgrade checks are broken down into package-level checks, which are in turn
broken down into module, template and data type-level checks.

Packages
~~~~~~~~

**Definition:** A *utility package* is a package with no template
definition, no interface definition, and only
non-`serializable <https://github.com/digital-asset/daml/blob/main-2.x/sdk/daml-lf/spec/daml-lf-1.rst#serializable-types>`__
data type definitions. A utility package typically consists of
helper functions and constants, but no type definitions.

In the following validity check, packages whose LF version does not support upgrades
(1.15 and earlier) and utility packages are ignored. 

A DAR is checked against previously uploaded DARs for upgrade validity on upload
to a participant. Specifically, for every package with
:ref:`name<assistant-manual-build-a-project>` *p* and
:ref:`version<assistant-manual-build-a-project>` *v* present in the uploaded
DAR:

1. The participant looks up versions *v_prev* and *v_next* of *p* in its package
   database, such that *v_prev* is the greatest version of
   *p* smaller than *v*, and *v_next* is the smallest version of *p*
   greater than *v*. Note that they may not always exist.

   .. image:: ./images/upgrade-static-checks-order.svg

2. The participant checks that version *v* of *p* is a valid upgrade of
   version *v_prev* of p, if it exists.
3. The participant checks that version *v_next* of *p* is a valid
   upgrade of version *v* of *p*, if it exists.

Therefore "being a valid upgrade" for a DAR is context
dependent: it depends on what packages are already uploaded on the
participant. It also *modular*: checks are performed at the package level. That
is, a new version of a package is rejected as soon as it contains some
element which doesn't properly upgrade its counterpart in the old
package, even if some other elements do. Similarly, 
all packages in a DAR must be pass the check for the DAR to be accepted. If one
of the packages fails the check, the entire DAR is rejected.  


Modules
~~~~~~~

The modules of the upgrading package must form a superset of the modules
of the upgraded package. In other words, it is valid to add new modules
but deleting a module leads to a validation error.

**Examples**

In the file tree below, package v2 is a potentially valid upgrade of
package v1, assuming ``v2/A.daml`` is a valid upgrade of ``v1/A.daml``.

.. code::

  ├── v1
  │   ├── daml
  │   │   └── A.daml
  │   └── daml.yaml
  └── v2
      ├── daml
      │   ├── A.daml
      │   └── B.daml
      └── daml.yaml


In the file tree below, package v2 cannot possibly be a valid upgrade of
v1 because it doesn't define module ``B``.

.. code::

  ├── v1
  │   ├── daml
  │   │   ├── A.daml
  │   │   └── B.daml
  │   └── daml.yaml
  └── v2
      ├── daml
      │   └── A.daml
      └── daml.yaml

Templates
~~~~~~~~~~

The templates of the upgrading package must form a superset of the
templates of the upgraded package. In other words, it is valid to add
new templates but deleting a template leads to a validation error.

.. _examples-1:

**Examples**

Below, the module on the right is a valid upgrade of the module on the
left. But the module on the left is **not** a valid upgrade of the
module on the right because it lacks a definition for template ``T2``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

          module M where
          
          template T1      
            with           
              p : Party    
            where          
              signatory p  
    
     - .. code-block:: daml

          module M where   
          
            template T1
              with
                p : Party
              where
                signatory p
          
            template T2
              with
                p : Party
              where
                signatory p
    
Template Parameters
~~~~~~~~~~~~~~~~~~~

An upgrading template may add new optional parameters at the end of the
parameter sequence of the upgraded template. The types of the parameters
that the upgrading template has in common with the upgraded template
must be pairwise valid upgrades of the original types.

Deleting a parameter leads to a validation error.

Adding a parameter in the middle of the parameter sequence leads to a
validation error.

As a special case of the two points above, renaming a parameter leads to
a validation error.

Adding a non-optional parameter at the end of the parameter leads to a
validation error.

.. _examples-2:

**Examples**

Below, the template on the right is a valid upgrade of the template on
the left. It adds an optional parameter ``x1`` at the end of the parameter
sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml
 
             template T
                 with
                   p : Party
                 where
                   signatory p

     - .. code-block:: daml
 
          template T
              with
                p : Party
                x1 : Optional Int
              where
                signatory p
 
Below, the template on the right is **not** a valid upgrade of the
template on the left because it adds a new parameter ``x1`` before ``p`` instead
of adding it at the end of the parameter sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            template T
              with
                p : Party
              where
                signatory p

     - .. code-block:: daml

            template T
              with
                x1 : Optional Int
                p : Party
              where
                signatory p

Below, the template on the right is **not** a valid upgrade of the
template on the left because it drops parameter ``x1``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            template T
              with
                p : Party
                x1 : Int
              where
                signatory p

     - .. code-block:: daml

            template T
              with
                p : Party
              where
                signatory p

Below, the template on the right is **not** a valid upgrade of the
template on the left because it changes the type of ``x1`` from ``Int`` to ``Text``.
``Text`` is not a valid upgrade of ``Int``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            template T
              with
                p : Party
                x1 : Int
              where
                signatory p

     - .. code-block:: daml

            template T
              with
                p : Party
                x1 : Text
              where
                signatory p
        
Template Keys
~~~~~~~~~~~~~

An upgrading template cannot modify the key of the upgraded template in
any way.

Adding a key leads to a validation error.

Removing a key leads to a validation error.

Changing the type of a key leads to a validation error.

For Daml 2.9, key types can only use definitions from the current package or 
from the Daml standard library. 

.. _examples-3:

**Examples**

Below, the template on the right is **not** a valid upgrade of the
template on the left because it adds a key.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            template T
              with
                p : Party
                k : Text
              where
                signatory p

     - .. code-block:: daml

            template T
              with
                p : Party
                k : Text
              where
                signatory p
                key (p, k): (Party, Text)
                maintainer (fst key)
        
Below, the template on the right is **not** a valid upgrade of the
template on the left because it deletes its key.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            template T
              with
                p : Party
                k : Text
              where
                signatory p
                key (p, k): (Party, Text)
                maintainer (fst key)

     - .. code-block:: daml

            template T
              with
                p : Party
                k : Text
              where
                signatory p
        
Below, the template on the right is **not** a valid upgrade of the
template on the left because it changes the type of its key.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            template T
              with
                p : Party
                k : Text
              where
                signatory p
                key (p, k): (Party, Text)
                maintainer (fst key)

     - .. code-block:: daml

            template T
              with
                p : Party
                k : Text
              where
                signatory p
                key (p, 2): (Party, Int)
                maintainer (fst key)

Template Choices
~~~~~~~~~~~~~~~~

The choices of an upgrading template must form a superset of the choices
of the upgraded template. In other words, it is valid to add new choices
but deleting a choice leads to a validation error.

.. _examples-4:

**Examples**

Below, the template on the right is a valid upgrade of the template on
the left. It adds a choice ``C`` to the previous version of the template.
But the template on the left is **not** a valid upgrade of the template
on the right as it deletes a choice.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            template T
              with
                p : Party
              where
                signatory p

     - .. code-block:: daml

            template T
              with
                p : Party
              where
                signatory p

                choice C : ()
                  controller p
                  do
                    return ()

Template Choices - Parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As with template parameters, an upgrading choice may add new optional
parameters at the end of the parameter sequence of the upgraded choice.
The types of the parameters that the upgrading choice has in common with
the upgraded choice must be pairwise valid upgrades of the original
types.

Deleting a parameter leads to a validation error.

Adding a parameter in the middle of the parameter sequence leads to a
validation error.

As a special case of the two points above, renaming a parameter leads to
a validation error.

Adding a non-optional parameter at the end of the parameter sequence leads to a
validation error.

**Example**

Below, the choice on the right is a valid upgrade of the choice on the
left. It adds an optional parameter ``x2`` at the end of the parameter
sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            choice C : ()
              with
                x1 : Int
              controller p
              do 
                return ()

     - .. code-block:: daml

            choice C : ()
              with
                x1 : Int
                x2 : Optional Text
              controller p
              do 
                return ()

Below, the choice on the right is **not** a valid upgrade of the choice
on the left because it adds a new parameter ``x2`` before ``x1`` instead of
adding it at the end of the parameter sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            choice C : ()
              with
                x1 : Int
              controller p
              do 
                return ()

     - .. code-block:: daml

            choice C : ()
              with
                x2 : Optional Text
                x1 : Int
              controller p
              do 
                return ()

Below, the choice on the right is **not** a valid upgrade of the choice
on the left because it adds a new field ``x2`` before ``x1`` instead of adding
it at the end of the parameter sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            choice C : ()
              with
                x1 : Int
              controller p
              do 
                return ()

     - .. code-block:: daml

            choice C : ()
              with
                x2 : Optional Text
                x1 : Int
              controller p
              do 
                return ()

Below, the choice on the right is **not** a valid upgrade of the choice
on the left because it drops parameter ``x1``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            choice C : ()
              with
                x1 : Int
              controller p
              do 
                return ()

     - .. code-block:: daml

            choice C : ()
              with
              controller p
              do 
                return ()

Below, the choice on the right is **not** a valid upgrade of the choice
on the left because it changes the type of ``x1`` from ``Int`` to ``Text``. ``Text`` is
not a valid upgrade of ``Int``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            choice C : ()
              with
                x1 : Int
              controller p
              do 
                return ()

     - .. code-block:: daml

            choice C : ()
              with
              controller p
              do 
                return ()

Template Choices - Return Type
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The return type of an upgrading choice must be a valid upgrade of the
return type of the upgraded choice.

Changing the return type of a choice for a non-valid upgrade leads to a
validation error.

.. _examples-5:

**Examples**

Below, the choice on the right is **not** a valid upgrade of the choice
on the left because it changes its return type from ``()`` to ``Int``. ``Int`` is
not a valid upgrade of ``()``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            choice C : ()
              controller p
              do
                return ()

     - .. code-block:: daml

            choice C : Int
              controller p
              do
                return 1

Data Types
~~~~~~~~~~

The serializable data types of the upgrading module must form a superset
of the serializable data types of the upgraded package. In other words,
it is valid to add new data types but deleting a data type leads to a
validation error.

Changing the variety of a serializable data type leads to a validation
error. For instance, one cannot change a record type into a variant
type.

Non-serializable data types are inexistent from the point of view of the
upgrade validity check. Turning a non-serializable data type into a
serializable one amounts to adding a new data type, which is valid.
Turning a serializable data type into a non-serializable one amounts to
deleting this data type, which is invalid.

.. _examples-6:

**Examples**

Below, the module on the right is a valid upgrade of the module on the
left. It defines an additional serializable data type ``B``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module M where

           data A = A

     - .. code-block:: daml

            module M where
  
            data A = A
            data B = B

Below, the module on the right is a valid upgrade of the module on the
left. It turns the non-serializable type ``A`` into a serializable one. The
non-serializable type is invisible to the upgrade validity check so this
amounts to adding a new data type to the module on the right.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module M where

            data A = A
              with 
                x : Int -> Int

     - .. code-block:: daml

            module M where

            data A = A
              with

Below, the module on the right is **not** a valid upgrade of the module
on the left because it changes the variety of ``A`` from record type to
variant type.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module M where

            data A = A
              with

     - .. code-block:: daml

            module M where

            data A = A | B

Below, the module on the right is **not** a valid upgrade of the module
on the left because it drops the serializable data type ``A``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module M where
     
            data A = A
     
     - .. code-block:: daml

            module M where
     
Below, the module on the right is **not** a valid upgrade of the module
on the left because although it adds an optional field to the record
type ``A``, it also turns ``A`` into a non-serializable type, which amounts to
deleting ``A`` from the point of view of the upgrade validity check.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module M where

            data A = A
              with

     - .. code-block:: daml

            module M where

            data A = A 
              with 
                x : Optional (Int -> Int)

Data Types - Records
~~~~~~~~~~~~~~~~~~~~

An upgrading record may add new optional fields at the end of the field
sequence of the upgraded record. The types of the fields that the
upgrading record has in common with the upgraded record must be pairwise
valid upgrades of the original types.

Deleting a field leads to a validation error.

Adding a field in the middle of the field sequence leads to a validation
error.

As a special case of the two points above, renaming a field leads to a
validation error.

Adding a non-optional field at the end of the field sequence leads to a
validation error.

.. _examples-7:

**Examples**

Below, the record on the right is a valid upgrade of the module on the
left. It adds an optional field ``x2`` at the end of the field sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

          data T = T with
            x1 : Int

     - .. code-block:: daml

          data T = T with
           x1 : Int
           x2 : Optional Text

Below, the record on the right is **not** a valid upgrade of the record
on the left because it adds a new field ``x2`` before ``x1`` instead of adding
it at the end of the field sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

          data T = T with
            x1 : Int

     - .. code-block:: daml

          data T = T with
            x2 : Optional Text
            x1 : Int
  
Below, the record on the right is **not** a valid upgrade of the record
on the left because it drops field ``x2``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

           data T = T with
             x1 : Int
             x2 : Text
     
     - .. code-block:: daml

           data T = T with
             x1 : Int

Below, the record on the right is **not** a valid upgrade of the record
on the left because it changes the type of ``x1`` from ``Int`` to ``Text``. 
``Text`` is not a valid upgrade of ``Int``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

           data T = T with
             x1 : Int

     - .. code-block:: daml

           data T = T with
             x1 : Text

Data Types - Variants
~~~~~~~~~~~~~~~~~~~~~

An upgrading variant may add new constructors at the end of the
constructor sequence of the upgraded variant. The argument types  
of the constructors that the upgrading variant has in common with the  
upgraded variant must be pairwise valid upgrades of the original types.  

Adding a constructor in the middle of the constructor sequence leads to
a validation error.

Changing the order or the name of the constructor sequence leads to a validation
error.

Removing a constructor leads to a validation error.

.. _examples-8:

**Examples**

Below, the variant on the right is a valid upgrade of the variant on the
left. It adds a new constructor ``C`` at the end of the constructor
sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: haskell

            data T =
              A Int | B Text

     - .. code-block:: haskell

            data T = 
              A Int | B Text | C Bool

Below, the variant on the right is **not** a valid upgrade of the
variant on the left because it adds a new constructor ``C`` before ``B`` instead
of adding it at the end of the constructor sequence.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: haskell

            data T =
              A Int | B Text

     - .. code-block:: haskell

            data T = 
              A Int | C Bool | B Text

Below, the variant on the right is **not** a valid upgrade of the
variant on the left because it changes the order of its constructors.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: haskell

            data T =
              A Int | B Text

     - .. code-block:: haskell

            data T = 
              B Text | A Int

Below, the variant on the right is **not** a valid upgrade of the
variant on the left because it drops constructor ``B````.``

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: haskell

            data T =
              A Int | B Text

     - .. code-block:: haskell

            data T = 
              A Int

Below, the variant on the right is **not** a valid upgrade of the
variant on the left because it changes the type of ``B``'s argument from
``Text`` to ``Bool``. ``Bool`` is not a valid upgrade of ``Text``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: haskell

            data T =
              A Int | B Text

     - .. code-block:: haskell

            data T = 
              A Int | B Bool

Data Types - Enums
~~~~~~~~~~~~~~~~~~

For the purpose of upgrade validation, enums can be treated as a special
case of variants. The rules of `the section on
variants <#data-types---variants>`__ apply, only without constructor
arguments.

Data Types - Type References
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A type reference is an identifier that resolves to a type. For instance,
consider the following module definitions, from two different packages:

.. code:: daml

  -- In package q
  module Dep where

  data U = U with x : Int
  type A = U

.. code:: daml

  -- In package p
  module M where
  import qualified Dep

  data T = T with x : Dep.A

In the definition of ``T``, ``Dep.A`` is a type reference that resolves to the
type with qualified name ``Dep.U`` in package ``q``.

A reference *r2* to a data type upgrades a reference *r1* to a data type
if and only if:

-  *r2* resolves to a type *t2* with qualified name *q2* in package *p2;*
-  *r1* resolves to a type *t1* with qualified name *q1* in package *p1;*
-  The qualified names *q2* and *q1* are the same;
-  If the LF versions of both *p1* and *p2* support upgrades then
      package *p2* is a valid upgrade of package *p1*, else *p2* and
      *p1* are the exact same package.

It is worth noting that even when *t2* upgrades *t1*, *r2* only upgrades
*r1* provided that package *p2* is a valid upgrade of package *p1* as a
whole.

.. _examples-9:

**Examples**

In these examples we assume the existence of packages ``q-1.0.0`` and
``q-2.0.0`` with LF version 1.16, and that the latter is a valid upgrade of
the former.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - In ``q-1.0.0``:
     - In ``q-2.0.0``:

   * - .. code-block:: daml

            module Dep where
     
            data U = C1
            data V = V
     
     - .. code-block:: daml
     
            module Dep where
     
            data U = C1 | C2
            data V = V
     
Then below, the module on the right is a valid upgrade of the module on
the left.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module Main where
     
            -- imported from q-1.0.0
            import qualified Dep
     
            data T = T Dep.U
     
     - .. code-block:: daml

            module Main where
     
            -- imported from q-2.0.0
            import qualified Dep
     
            data T = T Dep.U
     
However below, the module on the right is **not** a valid upgrade of the
module on the left because ``Dep.V`` on the right belongs to package ``q-1.0.0``
which is not a valid upgrade of package ``p-2.0.0``, even though the two
definitions of ``V`` are the same.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module Main where
     
            -- imported from q-2.0.0
            import qualified Dep
     
            data T = T Dep.V

     - .. code-block:: daml

            module Main where
     
            -- imported from q-1.0.0
            import qualified Dep
     
            data T = T Dep.V

Suppose now that q-1.0.0 and q-2.0.0 are both compiled to LF version
1.15 (which does not support upgrades). Then below, the module on the
right is **not** a valid upgrade of the module on the left because the
references to U on each side resolve to packages with different IDs.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            module Main where
     
            -- imported from q-1.0.0
            import qualified Dep
     
            data T = T Dep.U
     
     - .. code-block:: daml

            module Main where
     
            -- imported from q-2.0.0
            import qualified Dep
     
            data T = T Dep.U

Data Types - Parameterized Data Types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Parameterized data types are considered serializable. That is, parameterized
data types in an upgrading package are compared against their previous version.

The upgrade validation for parameterized data types follows the same
rules as non-parameterized data types, but also compares type variables.
The type variable comparison is currently limited to a pure syntactic
equality check, meaning that a type variable only upgrades a type
variable of the same name.

.. _example-1:

**Example**

Below, the parameterized data type on the right is a valid upgrade of
the parameterized data type on the left. As is valid with any record
type, it adds an optional field.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            data Tree a = 
              Tree with 
                label : a
                children : [Tree a]

     - .. code-block:: daml

            data Tree a = 
              Tree with 
                label : a
                children : [Tree a]
                cachedSize : Optional Int

Below, the parameterized data type on the right is **not** a valid
upgrade of the parameterized data type on the left. It renames the type
variable ``a`` into ``b`` which is currently not supported.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            data Tree b = 
              Tree with 
                label : b
                children : [Tree b]

     - .. code-block:: daml

            data Tree b = 
              Tree with 
                label : b
                children : [Tree b]

Interfaces
~~~~~~~~~~

Interfaces definitions cannot be upgraded. We strongly discourage
uploading a package that contains both interface and template
definitions, as these templates cannot benefit from smart contract upgrades
in the future. Instead, we recommend declaring interfaces in a
package of their own that defines no template.

Data Transformation: Runtime Semantics
--------------------------------------

Whenever a contract is fetched or one of its choices is exercised, it is
retrieved from the ledger and transformed into a value that fits the target
template type. Then, its metadata (signatories, observers, key, maintainers) is
recomputed using the code of the target temmpate and compared against the
existing metadata: it is not allowed to change. The ensure clause of the 
contract is also re-evaluated: it must evaluate to ``True``.

In addition, when a choice is exercised, its arguments are transformed into
values that fit the type of the parameters of the choice in the target package.
The result of the exercise is then possibly transformed back to some other
target type by the client (e.g. the generated java client code).

Below, we detail the rules governing target types, then explain how
transformations are performed, and finally detail the rules of metadata
re-computation.

Target Types
~~~~~~~~~~~~

In a top-level fetch or exercise triggered by a Ledger API command, the
target template type is determined by the rules of package preference
detailed in the `Ledger API <#_swcg5hoxdia8>`__ section. Once a given
version of a template has been selected, the target type of its
parameters as well as the target type of the contracts retrieved in its
choices is determined by their static type.

.. _example-1-1:

**Example 1**

Assume a package ``p`` with two versions. The upgrading version adds an
optional text field.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - In ``p-1.0.0``:
     - In ``p-2.0.0``:

   * - .. code-block:: daml

            template T 
              with
                p : Party
              where
                signatory p

     - .. code-block:: daml

            template T 
              with
                p : Party
                t : Optional Text
              where
                signatory p

Also assume a ledger that contains a contract of type ``T`` written by
``p-1.0.0``, and another contract of written by ``p-2.0.0``.

+------------+---------------+-----------------------------------------+
| Contract   | Type          | Contract                                |
| ID         |               |                                         |
+============+===============+=========================================+
| ``1234``   | ``p-1.0.0:T`` | ``T { p = 'Alice' }``                   |
+------------+---------------+-----------------------------------------+
| ``5678``   | ``p-2.0.0:T`` | ``T { p = 'Bob', t = Some "Hello" }``   |
+------------+---------------+-----------------------------------------+

Then

-  Fetching contract ``1234`` with package preference ``p-1.0.0`` retrieves the
   contract and leaves it unchanged, returning ``T { p = 'Alice' }``.
-  Fetching contract ``1234`` with package preference ``p-2.0.0`` retrieves the
   contract and successfully transforms it to the target template
   type, returning ``T { p = 'Alice', t = None }``.
-  Fetching contract ``5678`` with package preference ``p-1.0.0`` retrieves the
   contract and fails to downgrade it to the target template type,
   returning an error.
-  Fetching contract ``5678`` with package preference ``p-2.0.0`` retrieves the
   contract and leaves it unchanged, returning ``T { p = 'Bob', t =
   Some "Hello" }``.

**Example 2**

Now, assume two versions of a package called dep, defining a template U
and its upgrade.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - In ``dep-1.0.0``:
     - In ``dep-2.0.0``:

   * - .. code-block:: daml

            module Dep where

            template U
              with
                p : Party
              where
                signatory p

     - .. code-block:: daml

            module Dep where

            template U
              with
                p : Party
                t : Optional Text
              where
                signatory p

Assume then some package ``q`` which depends on version ``1.0.0`` of ``dep``.

.. code:: yaml

  [...]
  name: q
  version: 1.0.0
  data-dependencies:
  - dep-1.0.0.dar

Package ``q`` defines a template ``S`` with a choice that fetches a contract of
type ``U``.

.. code:: daml

  import qualified Dep

  template S
    with
      p : Party
    where
      signatory p

      choice GetU : Dep.U 
        with
          cid : ContractId Dep.U
        where
          controller p
          do fetch cid

Finally assume a ledger that contains a contract of type ``S`` written by ``q``
and a contract of type ``U`` written by ``dep-2.0.0``.

+-------------+------------------+------------------------------------+
| Contract ID | Type             | Contract                           |
+=============+==================+====================================+
| ``4321``    | ``q:T``          | ``T { p = 'Alice' }``              |
+-------------+------------------+------------------------------------+
| ``8765``    | ``dep-2.0.0:U``  | ``U { p = 'Bob', t = None }``      |
+-------------+------------------+------------------------------------+

When exercising choice ``GetU 8765`` on contract ``4321`` with package
preference ``dep-2.0.0``, we trigger a fetch of contract ``5678``. Because
package ``q`` depends on version ``1.0.0`` of ``dep``, the target type for ``U``
is the one defined in package ``dep-1.0.0``. Contract ``5678`` is thus
downgraded to ``U { p = 'Bob'}`` upon retrieval. Note that the command
preference for version ``2.0.0`` of package ``dep`` bears no incidence here.

**Example 3**

Assume now a package ``r`` with two versions. They define a template with a
choice, and version ``2.0.0`` adds an optional field to the parameters of the
choice. The return type of the choice is also upgraded.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - In ``r-1.0.0``:
     - In ``r-2.0.0``:

   * - .. code-block:: daml

            module M where

            data Ret = Ret with

            template V
              with
                p : Party
              where
                signatory p

                choice C : Ret
                  with 
                    i : Int
                  controller p
                  do return Ret

     - .. code-block:: daml

            module M where

            data Ret = Ret with
              j : Optional Int

            template V
              with
                 p : Party
               where
                 signatory p

                 choice C : Ret
                   with 
                     i : Int
                     j : Optional Int
                   controller p
                   do return Ret with j = j
 
Also assume a ledger that contains a contract of type ``V`` written by
``r-1.0.0``.

+------------+---------------+-----------------------------------------+
| Contract   | Type          | Contract                                |
| ID         |               |                                         |
+============+===============+=========================================+
| ``9101``   | ``r-1.0.0:V`` | ``V { p = 'Alice' }``                   |
+------------+---------------+-----------------------------------------+

Then:

- Exercising ``C with i=1`` on contract ``9101`` with package preference ``r-2.0.0`` 
  will execute the code of ``C`` as defined in ``r-2.0.0``. The parameter 
  sequence ``i=1`` is thus transformed into the parameter sequence ``i=1, j=None`` to
  match its parameter types. The exercise then returns the value ``Ret with j=None``.
  It is up to the client code (e.g. the caller of the ledger API) to transform this
  to a value that fits the return type it expects. For instance, a client which
  only knows about version ``1.0.0`` of package ``r`` would expect a value of type
  ``Ret`` and would thus transform the value ``Ret with j=None`` back to ``Ret``.
- Exercising ``C with i=1`` on contract ``9101`` with package preference ``r-1.0.0``
  will execute the code of ``C`` as defined in ``r-1.0.0``. The parameter sequence
  requires therefore no transformation. The exercise returns the value ``Ret``.
- Exercising ``C with i=1 j=Some 2`` on contract ``9101`` with package preference ``r-2.0.0``
  will execute the code of ``C`` as defined in ``r-2.0.0``. Again, the parameter sequence
  no transformation. The exercise returns the value ``Ret with j=Some 2``.
- Exercising ``C with i=1 j=Some 2`` on contract ``9101`` with package preference ``r-1.0.0``
  will fail with a runtime error as the parameter sequence ``i=1 j=Some 2`` cannot be
  downgraded to the parameter sequence of ``C`` as defined in ``r-1.0.0``.


Transformation Rules
~~~~~~~~~~~~~~~~~~~~

Once the target type has been determined, the data transformation rules
themselves follow the `upgrading rules of
protocol
buffers <https://protobuf.dev/programming-guides/proto3/#updating>`__.

Records and Parameters
^^^^^^^^^^^^^^^^^^^^^^

Given a record type and its upgrade, referred to respectively as ``T-v1``
and ``T-v2`` in the following,

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

           data T = T with
             x1 : T1
             ...
             xn : Tn
     
     - .. code-block:: daml

           data T = T with
             x1 : T1'
             ...
             xn : Tn'
             y1 : Optional U1
             ...
             ym : Optional Um

-  A ``T-v1`` value ``T { x1 = v1, ..., xn = vn }`` is upgraded to a ``T-v2`` value by
   setting the additional fields to None and upgrading ``v1...vn``
   recursively. The transformation results in a value ``T { x1 = v1',
   ..., xn = vn', y1 = None, ..., ym = None }``, where ``v1'... vn'`` is the
   result of upgrading ``v1...vn`` to ``T1' ... Tn'``.
-  A ``T-v2`` value of the shape
   ``T { x1 = v1, ..., xn = vn, y1 = None, ..., ym = None }`` is downgraded to a ``T-v1``
   value by dropping additional fields and downgrading ``v1...vn`` recursively. 
   The transformation results in a value
   ``T { x1 = v1', ..., xn = vn' }`` where ``v1'... vn'`` is the result of
   downgrading ``v1 ... vn`` to ``T1 ... Tn``.
-  Attempting to downgrade a ``T-v2`` value where at least one ``yi`` is a 
   ``Some _`` results in a runtime error.

The same transformation rules apply to template parameters and choice
parameters.

Variants and Enums
^^^^^^^^^^^^^^^^^^

Given a variant type and its upgrade, referred to respectively as ``V-v1``
and ``V-v2`` in the following,

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

            data V =
              = C1 T1
              | ...
              | Cn Tn

     - .. code-block:: daml

            data V =
              = C1 T1'
              | ...
              | Cn Tn'
              | D1 U1
              | ...
              | Dm Um

-  A ``V-v1`` value ``Ci vi`` is upgraded to a ``V-v2`` value by upgrading ``vi``
   recursively. The transformation results in a value ``Ci vi'`` where
   ``vi'`` is the result of upgrading ``vi`` to ``Ti'``.
-  A ``V-v2`` value ``Ci vi`` is downgraded to a ``V-v1`` value by downgrading ``vi``
   recursively. The transformation results in a value ``Ci vi'`` where
   ``vi'`` is the result of downgrading ``vi`` to ``Ti``.
-  Attempting to downgrade a ``V-v2`` value of the form ``Dj vj`` results in a
   runtime error.

The same transformation rules apply to enum types, constructor arguments
aside.

Other Types
^^^^^^^^^^^

Types that aren't records or variants are "pass-through" for the upgrade
and downgrade transformations:

-  Values of scalar types are trivially transformed to themselves.
-  The payload of an Optional is recursively transformed.
-  The elements of Lists are recursively transformed.
-  The keys and values of Maps are recursively transformed.

Metadata
~~~~~~~~
For a given contract, metadata is every information outside of the contract
parameters that is stored on the ledger for this contract. Namely:

- The contract ID;
- The contract signatories;
- The contract observers;
- The contract key;
- The maintainers of the contract key.

This information is not allowed to change between two versions of a contract.
Upon retrieval and after conversion, the metadata of a contract is recomputed
using the code of the target template. It is a runtime error if the recomputed
metadata does not match that of the original contract.

**Examples**

Below the template on the right is a valid upgrade of the template on the left.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * -  In ``p-1.0.0``:
     -  In ``p-2.0.0``:

   * - .. code-block:: daml 

           template T 
             with
               sig : Party
             where
               signatory sig

     - .. code-block:: daml

           template T 
             with
               sig : Party
               additionalSig : Optional Party
             where
               signatory sig, fromOptional [] additionalSig
     
Assume a ledger that contains a contract of type ``T`` written by
``p-1.0.0``.

+------------+---------------+-----------------------------------------+
| Contract   | Type          | Contract                                |
| ID         |               |                                         |
+============+===============+=========================================+
| ``1234``   | ``p-1.0.0:T`` | ``T { sig = ['Alice'] }``               |
+------------+---------------+-----------------------------------------+

Fetching contract ``1234`` with package preference ``p-2.0.0`` retrieves the
contract and successfully transforms it into a value of type ``p-2.0.0:T``: ``T
{ sig = 'Alice', additionalSig = None }``. The signatories of this transformed
contract are then computed using the expression ``sig, fromOptional []
additionalSig``, which evaluate to the list ``['Alice']``. This list is then
compared to signatories of the original contract stored on the ledger:
``['Alice']``. They match and thus the upgrade is valid.

On the other hand, below, the template on the right is **not** a valid upgrade
of the template on the left.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * -  In ``p-1.0.0``:
     -  In ``p-2.0.0``:

   * - .. code-block:: daml

          template T 
            with
              sig : Party
            where
              signatory sig
  
     -  .. code-block:: daml

           template T 
             with
               sig : Party
             where
               signatory sig, sig
    
Assume the same leger as above. Fetching contract ``1234`` with package
preference ``p-2.0.0`` retrieves the the contract and again successfully
transforms it into the value ``T { sig = 'Alice', additionalSig = None }``. The
signatories of this transformed contract are then computed using the expression
``sig, sig``, which evaluate to the list ``['Alice', 'Alice']``. This list is
then compared to signatories of the original contract stored on the ledger:
``['Alice']``. They do not match and thus the upgrade is rejected at runtime.

Ensure Clause
~~~~~~~~~~~~~

Upon retrieval and after conversion, the ensure clause of a contract is
recomputed using the code of the target template. It is a runtime error if the
recomputed ensure clause evaluates to ``False``.

** Example ***

Below, the template on the right is **not** a valid upgrade of the template on
the left because its ensure clause will evaluate to ``False`` for contracts that
have been written using the template on the left with ``n = 0``.

.. list-table::
   :widths: 50 50
   :width: 100%
   :class: diff-block

   * - .. code-block:: daml

          template T 
            with
              sig : Party
              n : Int
            where
              signatory sig
              ensure n >= 0
  
     -  .. code-block:: daml

           template T 
             with
               sig : Party
               n : Int
             where
               signatory sig
               ensure n > 0
