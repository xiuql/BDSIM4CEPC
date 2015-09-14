.. _appendix2_geometry:

===========================
Appendix 2 - Geometry Input
===========================

The element with user-defined physical geometry (see also :ref:`element`) is defined by::
  
  <element_name> : element, geometry=format:filename, attributes
  
where `format` must be set to `gmad`_, `mokka`_, `gdml`_ or `lcdd`_ and `filename` must point to a file that contains the geometry descriptions. For example::
  
  colli : element, geometry="gmad:colli.geo"

gmad
----

ggmad is a simple format used as G4geometry wrapper. It can be used for specifying more or less simple geometries like collimators. Example::

  Cons {
  x0=0,
  y0=0,
  z0=375,
  rmin1=100,
  rmax1=500,
  rmin2=5,
  rmax2=500,
  z=125,
  material=Graphite,
  phi0=0,
  dphi=360,
  temperature=1
  }

A file can contain several objects which will be placed sequentially into the volume.

.. note:: The user has to make sure that there is no overlap between them.
  
Available shapes are:

Box
^^^

========== ========================
parameter  description
x0         x origin
y0         y origin
z0         z origin
x          x size
y          y size
z          z size
phi        Euler angle for rotation
theta      Euler angle for rotation
psi        Euler angle for rotation
material   Material name
========== ========================

Cons
^^^^

========== =========================
parameter  description
x0         x origin
y0         y origin
z0         z origin
rmin1      inner radius at start
rmax1      outer radius at start
rmin2      inner radius at end
rmax2      outer radius at end
z          z size
phi        Euler angle for rotation
theta      Euler angle for rotation
psi        Euler angle for rotation
phi0       angle for start of sector
dphi       angle swept by sector
material   Material name
========== =========================

Tubs
^^^^

========== =========================
parameter  description
x0         x origin
y0         y origin
z0         z origin
rmin       inner radius
rmax       outer radius
z          z size
phi        Euler angle for rotation
theta      Euler angle for rotation
psi        Euler angle for rotation
material   Material name
========== =========================

Trd
^^^

========== ============================
parameter  description
x0         x origin
y0         y origin
z0         z origin
x1         half length at wider side
x2         half length at narrower side
y1         half length at wider side
y2         half length at narrower side
z          z size
phi        Euler angle for rotation
theta      Euler angle for rotation
psi        Euler angle for rotation
material   Material name
========== ============================



Mokka
-----

As well as using the GMAD format to describe user-defined physical geometry it is also possible to use a Mokka style format. This format is currently in the form of a dumped MySQL database format. Note that throughout any of the Mokka files, a `#` may be used to represent a commented line. There are three key stages, which are detailed in the following sections, that are required to setting up the Mokka geometry:

* `Describing the geometry`_
* `Creating a geometry list`_
* `Defining a Mokka Element`_

Describing the geometry
^^^^^^^^^^^^^^^^^^^^^^^

An object must be described by creating a MySQL file containing commands that would typically be used for uploading/creating a database and a corresponding new table into a MySQL database. BDSIM supports only a few such commands - specifically the CREATE TABLE and INSERT INTO commands. When writing a table to describe a solid there are some parameters that are common to all solid types (such as NAME and MATERIAL) and some that are more specific (such as those relating to radii for cone objects). A full list of the standard and specific table parameters, as well as some basic examples, are given below with each solid type. All files containing geometry descriptions must have the following database creation commands at the top of the file::

  DROP DATABASE IF EXISTS DATABASE_NAME;
  CREATE DATABASE DATABASE_NAME;
  USE DATABASE_NAME;

A table must be created to allow for the insertion of the geometry descriptions. A table is created using the following, MySQL compliant, commands::

  CREATE TABLE TABLE-NAME_GEOMETRY-TYPE (
  TABLE-PARAMETER VARIABLE-TYPE,
  TABLE-PARAMETER VARIABLE-TYPE,
  TABLE-PARAMETER VARIABLE-TYPE
  );

Once a table has been created values must be entered into it in order to define the solids and position them. The insertion command must appear after the table creation and must the MySQL compliant table insertion command::

  INSERT INTO TABLE-NAME_GEOMETRY-TYPE VALUES(value1, value2, "char-value", ...);

The values must be inserted in the same order as their corresponding parameter types are described in the table creation. Note that ALL length types must be specified in mm and that ALL angles must be in radians.

An example of two simple boxes with no visual attributes set is shown below. The first box is a simple vacuum cube whilst the second is an iron box with length x = 10mm, length y = 150mm, length z = 50mm, positioned at x=1m, y=0, z=0.5m and with zero rotation::

  CREATE TABLE mytable_BOX (
  NAME VARCHAR(32),
  MATERIAL VARCHAR(32),
  LENGTHX DOUBLE(10,3),
  LENGTHY DOUBLE(10,3),
  LENGTHZ DOUBLE(10,3),
  POSX DOUBLE(10,3),
  POSY DOUBLE(10,3),
  POSZ DOUBLE(10,3),
  ROTPSI DOUBLE(10,3),
  ROTTHETA DOUBLE(10,3),
  ROTPHI DOUBLE(10,3)
  );

  INSERT INTO mytable_BOX VALUES("a_box","vacuum", 50.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  INSERT INTO mytable_BOX VALUES("another_box","iron", 10.0, 150.0, 50.0, 1000.0, 0.0, 500.0, 0.0, 0.0, 0.0);

Further examples of the Mokka geometry implementation can be found in the examples/features/geometry/Mokka/General directory. See the common table parameters and solid type sections below for more information on the table parameters available for use.

Common Table Parameters
_______________________

The following is a list of table parameters that are common to all solid types either as an optional or mandatory parameter:

* | NAME
  | Variable type: VARCHAR(32)
  | Optional parameter
  | If supplied, then the Geant4 LogicalVolume associated with the solid will be labelled with this name. The default is set to be the table’s name plus an automatically assigned volume number.
* | MATERIAL
  | Variable type: VARCHAR(32)
  | Optional parameter
  | If supplied, then the volume will be created with this material type - note that the material must be given as a character string inside double quotation marks(“). The default material is set as Vacuum.
* | PARENTNAME
  | Variable type: VARCHAR(32)
  | Optional parameter
  | If supplied, then the volume will be placed as a daughter volume to the object with ID equal to PARENTNAME. The default parent is set to be the Component Volume. Note that if PARENTID is set to the Component Volume then POSZ will be defined with respect to the start of the object. Else POSZ will be defined with respect to the center of the parent object.
* | INHERITSTYLE
  | Variable type: VARCHAR(32)
  | Optional parameter to be used with PARENTNAME.
  | If set to “SUBTRACT“ then the instead of placing the volume within the parent volume as an inherited object, it will be subtracted from the parent volume in a Boolean solid operation. The default for this value is set to ““ - which sets to the usual mother/daughter volume inheritance.
* | ALIGNIN
  | Variable type: INTEGER(11)
  | Optional parameter
  | If set to 1 then the placement of components will be rotated and translated such that the incoming beamline will pass through the z-axis of this object. The default is set to 0.
* | ALIGNOUT
  | Variable type: INTEGER(11)
  | Optional parameter
  | If set to 1 then the placement of the next beamline component will be rotated and translated such that the outgoing beamline will pass through the z-axis of this object. The default is set to 0.
* | SETSENSITIVE
  | Variable type: INTEGER(11)
  | Optional parameter
  | If set to 1 then the object will be set up to register energy depositions made within it and to also record the z-position at which this deposition occurs. This information will be saved in the ELoss Histogram if using ROOT output. The default is set to 0.
* | MAGTYPE
  | Variable type: VARCHAR(32)
  | Optional parameter
  | If supplied, then the object will be set up to produce the appropriate magnetic field using the supplied K1 or K2 table parameter values . Three magnet types are available - “QUAD”, “SEXT” and “OCT”. The default is set to no magnet type. Note that if MAGTYPE is set to a value whilst K1/K2/K3 are not set, then no magnetic field will be implemented.
* | K1
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set to a value other than zero, in conjunction with MAGTYPE set to “QUAD” then a quadrupole field with this K1 value will be set up within the object. Default is set to zero.
* | K2
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set to a value other than zero, in conjunction with MAGTYPE set to “SEXT” then a sextupole field with this K2 value will be set up within the object. Default is set to zero.
* | K3
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set to a value other than zero, in conjunction with MAGTYPE set to “OCT” then a sextupole field with this K3 value will be set up within the object. Default is set to zero.
* | POSX, POSY, POSZ
  | Variable type: DOUBLE(10,3)
  | Required parameters
  | They are form the position in mm used to place the object in the component volume. POSX and POSY are defined with respect to the center of the component volume and with respect to the component volume’s rotation. POSZ is defined with respect to the start of the component volume. Note that if the object is being placed inside another volume using PARENTNAME then the position will refers to the center of the parent object.
* | ROTPSI, ROTTHETA, ROTPHI
  | Variable type: DOUBLE(10,3)
  | Optional parameters
  | They are the Euler angles in radians used to rotate the object before it is placed. The default is set to zero for each angle.
* | RED, BLUE, GREEN
  | Variable type: DOUBLE(10,3)
  | Optional parameters
  | They are the RGB colour components assigned to the object and should be a value between 0 and 1. The default is set to zero for each colour.
* | VISATT
  | Variable type: VARCHAR(32)
  | Optional parameter
  | This is the visual state setting for the object. Setting this to “W” results in a wireframe displayment of the object. “S” produces a shaded solid and “I” leaves the object invisible. The default is set to be solid.
* | FIELDX, FIELDY, FIELDZ
  | Variable type: DOUBLE(10,3)
  | Optional parameters
  | They can be used to apply a uniform field to any volume, with default units of Tesla. Note that if there is a solenoid field present throughout the entire element then this uniform field will act in addition to the solenoid field.

'Box' Solid Types
_________________

Append _BOX to the table name in order to make use of the G4Box solid type. The following table parameters are specific to the box solid:

* | LENGTHX, LENGTHY, LENGTHZ
  | Variable type: DOUBLE(10,3)
  | Required parameters
  | There values will be used to specify the box’s dimensions.

’Trapezoid’ Solid Types
_______________________

Append _TRAP to the table name in order to make use of the G4Trd solid type - which is defined as a trapezoid with the X and Y dimensions varying along z functions. The following table parameters are specific to the trapezoid solid:

* | LENGTHXPLUS
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the x-extent of the box’s dimensions at the surface positioned at +dz.
* | LENGTHXPMINUS
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the x-extent of the box’s dimensions at the surface positioned at -dz.
* | LENGTHYPLUS
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the y-extent of the box’s dimensions at the surface positioned at +dz.
* | LENGTHYPMINUS
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the y-extent of the box’s dimensions at the surface positioned at -dz.
* | LENGTHZ
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the z-extent of the box’s dimensions.

’Cone’ Solid Types
__________________

Append _CONE to the table name in order to make use of the G4Cons solid type. The following table parameters are specific to the cone solid:

* | LENGTH
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the z-extent of the cone’s dimensions.
* | RINNERSTART
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the inner radius of the start of the cone. The default value is zero.
* | RINNEREND
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the inner radius of the end of the cone. The default value is zero.
* | ROUTERSTART
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the outer radius of the start of the cone.
* | ROUTEREND
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the outer radius of the end of the cone.
* | STARTPHI
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the starting angle of the cone. The default value is zero.
* | DELTAPHI
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the delta angle of the cone. The default value is 2*PI.

’Torus’ Solid Types
___________________

Append _TORUS to the table name in order to make use of the G4Torus solid type. The following table parameters are specific to the torus solid:

* | RINNER
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the inner radius of the torus tube. The default value is zero.
* | ROUTER
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the outer radius of the torus tube.
* | RSWEPT
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the swept radius of the torus. It is defined as being the distance from the center of the torus ring to the center of the torus tube. For this reason this value should not be set to less than ROUTER.
* | STARTPHI
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the starting angle of the torus. The default value is zero.
* | DELTAPHI
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the delta swept angle of the torus. The default value is 2*PI.

’Polycone’ Solid Types
______________________

Append _POLYCONE to the table name in order to make use of the G4Polycone solid type. The following table parameters are specific to the polycone solid:

* | NZPLANES
  | Variable type: INTEGER(11)
  | Required parameter
  | This value will be used to specify the number of z-planes to be used in the polycone. This value must be set to greater than 1.
* | PLANEPOS1, PLANEPOS2, ..., PLANEPOSN
  | Variable type: DOUBLE(10,3)
  | Required parameters
  | These values will be used to specify the z-position of the corresponding z-plane of the polycone. There should be as many PLANEPOS parameters set as the number of z-planes. For example, 3 z-planes will require that PLANEPOS1, PLANEPOS2, and PLANEPOS3 are all set up.
* | RINNER1, RINNER2, ..., RINNERN
  | Variable type: DOUBLE(10,3)
  | Required parameters
  | These values will be used to specify the inner radius of the corresponding z-plane of the polycone. There should be as many RINNER parameters set as the number of z-planes. For example, 3 z-planes will require that RINNER1, RINNER2, and RINNER3 are all set up.
* | ROUTER1, ROUTER2, ..., ROUTERN
  | Variable type: DOUBLE(10,3)
  | Required parameters
  | These values will be used to specify the outer radius of the corresponding z-plane of the polycone. There should be as many ROUTER parameters set as the number of z-planes. For example, 3 z-planes will require that ROUTER1, ROUTER2, and ROUTER3 are all set up.
* | STARTPHI
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the starting angle of the polycone. The default value is zero.
* | DELTAPHI
  | Variable type: DOUBLE(10,3)
  | Optional parameter
  | If set then this value will be used to specify the delta angle of the polycone. The default value is 2*PI.

’Elliptical Cone’ Solid Types
_____________________________

Append _ELLIPTICALCONE to the table name in order to make use of the G4Ellipticalcone solid type. The following table parameters are specific to the elliptical cone solid:

* | XSEMIAXIS
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the Semiaxis in X.
* | YSEMIAXIS
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the Semiaxis in Y.
* | LENGTHZ
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the height of the elliptical cone.
* | ZCUT
  | Variable type: DOUBLE(10,3)
  | Required parameter
  | This value will be used to specify the upper cut plane level.

Note that the above parameters are used to define an elliptical cone with the following parametric equations (in the usual Geant4 way)::

  x = XSEMIAXIS * (LENGTHZ - u) / u * Cos(v)
  Y = YSEMIAXIS * (LENGTHZ - u) / u * Sin(v)
  z = u

where v is between 0 and 2*PI and u between 0 and h respectively.

Creating a geometry list
^^^^^^^^^^^^^^^^^^^^^^^^

A geometry list is a simple file consisting of a list of file names that contain geometry descriptions. This is the file that should be passed to the GMAD file when defining the Mokka element. An example of a geometry list containing ’boxes.sql’ and ’cones.sql’ would be::

  # ’#’ symbols can be used for commenting out an entire line
  /directory/boxes.sql
  /directory/cones.sql

Defining a Mokka element
^^^^^^^^^^^^^^^^^^^^^^^^

The Mokka element can be defined by the following command::

  collimator : element, geometry=mokka:coll_geomlist.sql

GDML
----

GDML (Geometry Description Markup Language) is an XML schema for detector description. To use Geant4 and BDSIM needs to be built with GDML usage on (default true). For more information we refer to the GDML `website <http://gdml.web.cern.ch/GDML/>`_ and `manual <http://gdml.web.cern.ch/GDML/doc/GDMLmanual.pdf>`_.

LCDD
----

The LCDD (Linear Collider Detector Description) is based on `GDML`_. The syntax and usage is described in this `SLAC paper <http://www.slac.stanford.edu/cgi-wrap/getdoc/slac-pub-12350.pdf>`_.
