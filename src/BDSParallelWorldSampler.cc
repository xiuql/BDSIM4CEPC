#include "BDSAcceleratorModel.hh"
#include "BDSBeamline.hh"
#include "BDSBeamlineElement.hh"
#include "BDSDebug.hh"
#include "BDSGlobalConstants.hh"
#include "BDSParallelWorldSampler.hh"
#include "BDSSampler.hh"
#include "BDSSamplerCylinder.hh"
#include "BDSSamplerPlane.hh"
#include "BDSSamplerRegistry.hh"
#include "BDSSamplerSD.hh"
#include "BDSSamplerType.hh"

#include "globals.hh" // geant4 types / globals
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4Transform3D.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserParallelWorld.hh"

#include <vector>


BDSParallelWorldSampler::BDSParallelWorldSampler():
  G4VUserParallelWorld("SamplerWorld"),
  samplerWorldVis(nullptr)
{;}

BDSParallelWorldSampler::~BDSParallelWorldSampler()
{
  for (auto placement : placements)
    {delete placement;}
  for (auto sampler : samplers)
    {delete sampler;}
  delete samplerWorldVis;
}

void BDSParallelWorldSampler::Construct()
{
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << G4endl;
#endif
  G4VPhysicalVolume* samplerWorld   = GetWorld();
  G4LogicalVolume*   samplerWorldLV = samplerWorld->GetLogicalVolume();

  samplerWorldVis = new G4VisAttributes(*(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr()));
  samplerWorldVis->SetForceWireframe(true);//just wireframe so we can see inside it
  samplerWorldLV->SetVisAttributes(samplerWorldVis);
  
  const G4double samplerR    = 0.5*BDSGlobalConstants::Instance()->GetSamplerDiameter();
  BDSBeamline* beamline      = BDSAcceleratorModel::Instance()->GetFlatBeamline();
  const G4bool checkOverlaps = BDSGlobalConstants::Instance()->GetCheckOverlaps();

  // Construct the one sampler typically used for a general sampler
  BDSSamplerPlane* generalPlane = new BDSSamplerPlane("Plane_sampler", samplerR);
  samplers.push_back(generalPlane); // register it

  // For each element in the beamline construct and place the appropriate type
  // of sampler if required. Info encoded in BDSBeamlineElement instance
  for (auto element : *beamline)
    {
      if (element->GetSamplerType() == BDSSamplerType::none)
	{continue;}
      // esle must be a valid sampler
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << "Sampler type: " << element->GetSamplerType() << G4endl;
#endif
      G4String name     = element->GetName();
      G4Transform3D* pt = element->GetSamplerPlacementTransform();
      G4double sEnd     = element->GetSPositionEnd();
      
      BDSSampler* sampler = nullptr;
      switch (element->GetSamplerType().underlying())
	{
	case BDSSamplerType::plane:
	  {sampler = generalPlane; break;}
	case BDSSamplerType::cylinder:
	  {
	    G4double length = element->GetAcceleratorComponent()->GetChordLength();
	    sampler = new BDSSamplerCylinder(name,
					     length,
					     samplerR);
	    samplers.push_back(sampler); // register it - memory management
	    break;
	  }
	default:
	  continue; // leave as nullptr - shouldn't occur due to if at top
	}
      
      if (sampler)
	{
#ifdef BDSDEBUG
	  G4cout << "Translation: " << pt->getTranslation() << G4endl;
	  G4cout << "Rotation:    " << pt->getRotation()    << G4endl;
#endif
	  G4int samplerID = BDSSamplerRegistry::Instance()->RegisterSampler(name,
									    sampler,
									    *pt,
									    sEnd);
	  
	  // record placements for cleaning up at destruction.
	  G4PVPlacement* pl = new G4PVPlacement(*pt,              // placement transform
						sampler->GetContainerLogicalVolume(), // logical volume
						name + "_pv",     // name of placement
						samplerWorldLV,   // mother volume
						false,            // no boolean operation
						samplerID,        // copy number
						checkOverlaps);
	  
	  placements.push_back(pl);
	}
    }
  
  // now build arbitrary user specified samplers - ie those for detectors
  // TBC
}
