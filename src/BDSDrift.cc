#include "BDSAcceleratorComponent.hh"
#include "BDSDrift.hh"
#include "BDSBeamPipe.hh"
#include "BDSBeamPipeFactory.hh"
#include "BDSBeamPipeInfo.hh"

#include "globals.hh" // geant4 globals / types

BDSDrift::BDSDrift(G4String         name, 
		   G4double         length,
		   BDSBeamPipeInfo* beamPipeInfo,
		   G4int            precisionRegion):
  BDSAcceleratorComponent(name, length, 0, "drift", precisionRegion, beamPipeInfo)
{;}

BDSDrift::~BDSDrift()
{;}

void BDSDrift::Build()
{
  BDSBeamPipeFactory* factory = BDSBeamPipeFactory::Instance();
  BDSBeamPipe* pipe = factory->CreateBeamPipe(name,
					      chordLength,
					      beamPipeInfo);

  RegisterDaughter(pipe);
  
  // make the beam pipe container, this object's container
  containerLogicalVolume = pipe->GetContainerLogicalVolume();
  containerSolid         = pipe->GetContainerSolid();

  SetAcceleratorVacuumLogicalVolume(pipe->GetVacuumLogicalVolume());

  // update extents
  InheritExtents(pipe);
}
