.. _dev-geantusage:

Geant4 User Action Classes
**************************

Geant4 provides several base classes the developer can inherit, instantiate and register with
the Geant4 run manager as a way of taking various actions defined by the developer at different
stages of the simulation. These are described at `Geant4 user actions <http://geant4.web.cern.ch/geant4/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/UserActions/OptionalActions.html>`_.
They provide actions at
each level of granularity in the simulation. The actions BDSIM takes in each of these is described
in the following sections.



G4UserRunAction
===============

A 'Run' is the largest unit of simulation in Geant4 parlance - it is a simulation where all the
geometry, fields and physics are fixed and the same throughout. It typically contains many 'Events'.

BDSRunAction::GenerateRun
-------------------------

This is not used as BDSIM does not define its own Run object and uses the G4Run one.

BDSRunAction::BeginOfRunAction
------------------------------

* This histrograms for the simulation (Run) are prepared and registered with the :code:`BDSAnalysisManager`
* The start time is printed out


BDSRunAction::EndOfRunAction
----------------------------

* The stop time is printed out
* All histograms are written to the output
* Clean up


G4UserEventAction
=================

BDSEventAction::BeginOfEventAction
----------------------------------

* Sampler hits collections are created and registered

BDSEventAction::EndOfEventAction
--------------------------------

* Primary vertex coordinates are recorded
* Sampler, Cylindrical Sampler, Energy Deposition, Tunnel Energy Deposition hits are recorded in that order
* Primary impact points and loss points are recorded
* Output is written
* Trajectories matching filtering criteria are prepared and written to output

G4UserStackingAction
====================

This allows the developer to fiddle the priority of particles (primary and secondary) based on their properties.

BDSStackingAction::ClassifyNewTrack
-----------------------------------

* All neutrinos are killed by default to save time on tracking
* If specified in :code:`GMAD::Options` stop tracks, the following secondary particles are killed

  * electrons, photons, positrons and protons/antiprotons
  
* If stop secondaries is specified, all secondaries are killed.
* Photons are counted


G4UserTrackingAction
====================

The tracking action happens after each step is completed

BDSUserTrackingAction::PreUserTrackingAction
--------------------------------------------

* the tracking manager is always told to store the trajectory

G4UserSteppingAction
====================

Only :code:`UserSteppingAction` is implemented and only to provide verbose output if required.
