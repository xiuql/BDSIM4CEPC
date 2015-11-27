***************
Python Packages
***************

Several python packages are provided to aid preparation and conversion
of models to a from BDSIM's gmad format and are described the following
sections.

* pybdsim - conversion and building of input as well as ASCII data analysis
* pymadx  - file loader for MADX Tfs file format
* pymad8  - file loader for MAD8 file format

Installing Python Packages
==========================

To access (import) the supplied packages from anywhere on your system,
the `utils` directory should be added to your `PYTHONPATH` environmental
variable::

  export PYTHONPATH=$PYTHONPATH:~/physics/reps/bdsim/utils

This should allow you to import the python utilities without error
from any location::

  cd ~/
  python
  
>>> import pybdsim
>>> # no errors


Documentation
=============

In the following sections is individual documentatino for each python package.
These are also available when using ipython by typing ? after any module or class.

.. toctree::
   :maxdepth: 2

   pybdsim.rst
   pymadx
   pymad8




   

