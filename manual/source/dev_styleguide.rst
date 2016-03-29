Style Guide
***********

This section describes the agreed style and conventions used when editing
and writing source code in BDSIM.

C++
===

General
-------

* All variables shall be namespaced and not global
* The asterix is attached to the object not the variable name

::

   BDSClassName* anInstance;
   

Naming
------

* Underscores are to be avoided as hard to type and read
* HEADERGUARDS_H are like this
* Classes start with "BDS"
* Classes use UpperCamelCaseForNaming
* Member functions use UpperCamelCase as well
* Member variables have no prefix (such as :code:`_variable` or :code:`m_variable`)
* Member variables use lowerCamelCase

  
Indentation & Spacing
---------------------

* Two spaces per level of indentation
* Tabs should not be used
* Spaces should be between operators


Braces
------

* Explicit braces should always be used, even for one line if statements

::

   if (a > 4)
     {G4cout << a << G4endl;}

* Braces should be on a new line - makes scope easier to determine

::

   if (a > 4)
     {
       G4cout << a << G4endl;
       G4cout << "This is a test" << G4endl;
     }

* The above style is preferred (indented block), but the following is also fine

::

   if (a > 4)
     {
     G4cout << a << G4endl;
     G4cout << "This is a test" << G4endl;
     }
   
  

In-Code Documentation
---------------------

* Every single class should have doxygen documentation in the header
* Obviously comments are strongly encouraged, as well as notes in this documentation
* Avoid documenting the purpose of functions (ie outside the function) in the source code - document the header


Python
======

The Python modules are developed with the intention that they be used and discovered
interactively in ipython, therefore, the naming convention described should make
tab completion easy to understand and docstrings allow the use of the :code:`?` for
help on any class or object.

General
-------

* Docstrings must be provided for all modules, classes and functions
* General packages such as numpy should be imported in a hidden fashion by renaming

::

   import numpy as _np



Naming
------

* Classes use UpperCamelCaseForNaming
* Member functions use UpperCamelCase as well
* Member variables have no prefix (such as :code:`_variable` or :code:`m_variable`)
* Member variables use lowerCamelCase
