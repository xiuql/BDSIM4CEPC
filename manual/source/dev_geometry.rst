.. _dev-geometry:

Geometry
********

In :code:`bdsim.cc`, an instance of :code:`BDSDetectorConstruction` is created and registered to the
Geant4 run manager.

They geometry is dynamically built based on information from the parser instance. BDSIM is designed to
build a model of an accelerator and as such, creates a single beam line in order, element by element.
Each element is created using a component factory (:code:`BDSComponentFactory`) to instantiate
the correct class and it is then placed in a holder (:code:`BDSBeamline`) that calculates the
the cumulative coordinates of the element in the world given the already created ones. It also keeps
track of the extent of the model. Optionally, the tunnel is built with respect to the beamline. Only
after these stages, can an appropriately sized world volume be created. Each element in the beam line
is then placed into the world volume. Ultimately, the fully constructed world volume (and therefore all
of its contents - the accelerator model) is returned to Geant4, which then handles it for the simulation.

Beam Line Calculations
======================

As well as being a vector of the beam line elements, when each :code:`BDSAcceleratorComponent`
is added to the beam line, the coordinates that it should be placed in the world that represent
that element's position in the beam line are calculated. The rotation matrices and positions for
the beginning, middle and end are stored along with the :code:`BDSAcceleratorComponent` instance
in a :code:`BDSBeamlineElement` instance. A further subtelty is that any one element can be offset or
tilted with respect to the accelerator curvlinear reference ('design') trajectory, so the originals
are stored under the name 'reference' and the final positions (incorporating tilts and offsets)
are recorded without name.

Assumptions About Geometry
--------------------------

The coordinate calculation is to a degree simplified with a few basic assumptions about how
any one component affects the reference ('design') trajectory.

* A BDSAcceleratorComponent advances the reference trajectory by a length :math:`l`.
* A BDSAcceleratorComponent may change the outgoing angle of the reference trajectory
  by angle :math:`\alpha` in the horizontal (:math:`x` - :math:`z`) plane and this is
  assumed to be a single smooth change.
* Any offset in the reference trajectory at the end of a :code:`BDSAcceleratorComponent` is due
  to the change in angle through the component.
* It is not possible for the outgoing trajectory to be offset but with zero angle - ie
  a slalom or S shape.

**A Few Important Points**

* Geant4 uses the right handed coordinate system.
* Euler angles are used to rotate frames of reference and offsets are applied first.
* :math:`l` is not used for length in the code - only :code:`chordLength` or :code:`arcLength` to be explicit.
* The chord length and arclength are supplied or calculated in :code:`BDSAcceleratorComponent`.

A schematic of the chord and arc length for a :code:`BDSAcceleratorComponent` with a finite bend
angle is shown below.

.. figure:: dev_figures/chord_arc_length.pdf
	   :width: 90%
	   :align: center

	   Schematic of chord and arc length as well as reference points and planes for
	   a :code:`BDSAcceleratorComponent` that bends by finite angle :math:`\alpha`.
	  

Component Factory
=================


Beam Pipe / Aperture Factories
==============================

Magnet Factories
================

The magnet geometry is built in factories with virtual base class :code:`BDSMagnetOuterFactoryBase`. Many
factories inherit this implementing the virtual methods (one for each magnet type) and provide various
styles of magnet geometry. In this way, a new magnet style can be added easily or a factory made that
mixes and matches others by calling other factories. All factories are singletons as there need only be
one of them - although this isn't strictly required.

Angles of Bends and Faces
-------------------------

For the sector and rectangular bends, angled faces are required (remember, each segment of geometry in
BDSIM is always a small straight section, but can have angled faces). To accommodate both normal bends
and those with pole face rotations, the angle of the input face and the angle of the output face are
specified. If no pole face rotations are specified, half the bend angle is given as the face angles.

**TBC** Definition of pole face angles (+ve, -ve) w.r.t. right-handed coordinate system and madx
angle convention.


Specific Element Details
========================

Rectangular Bend
----------------
