/* BDSIM code.    Version beta
   Author: Grahame I. Agapov, Royal Holloway, Univ. of London.

*/
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSCollimator.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"               
#include "G4SubtractionSolid.hh"
#include "G4UserLimits.hh"
#include "G4TransportationManager.hh"

#include "G4SDManager.hh"
#include "G4UserLimits.hh"
#include "parser/gmad.h"
#include <map>

//============================================================
typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
extern LogVolMap* LogVol;

extern BDSMaterials* theMaterials;
//============================================================

BDSCollimator::BDSCollimator (G4String aName,G4double aLength,G4double bpRad,
			      G4double xAper,G4double yAper, G4int type,
			      G4Material *CollimatorMaterial, G4double outR, 
                              std::list<G4double> blmLocZ, std::list<G4double> blmLocTheta,
                              G4String aTunnelMaterial):
  BDSAcceleratorComponent(aName,
			  aLength,bpRad,xAper,yAper,
			  SetVisAttributes(), blmLocZ, blmLocTheta, aTunnelMaterial),
  itsCollimatorMaterial(CollimatorMaterial), itsOuterR(outR)
{
  if(type==_RCOL) itsType="rcol";
  if(type==_ECOL) itsType="ecol";

  if(itsOuterR==0) itsOuterR = BDSGlobals->GetComponentBoxSize()/2;

  if ( (*LogVolCount)[itsName]==0)
    {
  G4double xLength, yLength;
  G4double totalTunnelRadius = BDSGlobals->GetTunnelRadius()+BDSGlobals->GetTunnelThickness()+BDSGlobals->GetTunnelSoilThickness()+std::max(BDSGlobals->GetTunnelOffsetX(),BDSGlobals->GetTunnelOffsetY());
  
  xLength = yLength = std::max(itsOuterR,BDSGlobals->GetComponentBoxSize()/2);
  xLength = yLength = std::max(xLength,totalTunnelRadius);

  itsMarkerLogicalVolume=new G4LogicalVolume
    (new G4Box( itsName+"_solid",
                xLength,
		yLength,
		(itsLength+BDSGlobals->GetLengthSafety())/2), //z half length 
     theMaterials->GetMaterial("vacuum"),
     itsName+"_log");

      if(BDSGlobals->GetBuildTunnel()){
        BuildTunnel();
      }
      BuildInnerCollimator();
      BuildBLMs();

      itsSolidLogVol->SetVisAttributes(SetVisAttributes());

      // visual attributes
      G4VisAttributes* VisAtt1 =
        new G4VisAttributes(G4Colour(0., 0., 0.));
      VisAtt1->SetForceSolid(true);
      itsInnerLogVol->SetVisAttributes(VisAtt1);

      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;
    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume=(*LogVol)[itsName];
    }  
}

void BDSCollimator::BuildBLMs(){
  itsBlmLocationR=itsOuterR*2;
  BDSAcceleratorComponent::BuildBLMs();
}

G4VisAttributes* BDSCollimator::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0.3,0.4,0.2));
  itsVisAttributes->SetForceSolid(true);
  return itsVisAttributes;
}

void BDSCollimator::BuildInnerCollimator()
{

  // zero aperture --> no aperture

  if(itsXAper <= 0) itsXAper = BDSGlobals->GetComponentBoxSize()/2;
  if(itsYAper <= 0) itsYAper = BDSGlobals->GetComponentBoxSize()/2;

  itsSolidLogVol=
    new G4LogicalVolume(new G4Box(itsName+"_solid",
				  itsOuterR,
				  itsOuterR,				  
				  itsLength/2),
                        itsCollimatorMaterial,
			itsName+"_solid");

  if(itsType == "rcol")
    {
      itsInnerLogVol=
	new G4LogicalVolume(new G4Box(itsName+"_inner",
				      itsXAper,
				      itsYAper,
				      itsLength/2),
			    theMaterials->GetMaterial("Vacuum"),
			    itsName+"_inner");
    }
  
  if(itsType == "ecol")
    {
      itsInnerLogVol=
	new G4LogicalVolume(new G4EllipticalTube(itsName+"_inner",
				      itsXAper,
				      itsYAper,
				      itsLength/2),
			    theMaterials->GetMaterial("Vacuum"),
			    itsName+"_inner");
    }

  G4ThreeVector nullThreeVector = G4ThreeVector(0,0,0);
  G4RotationMatrix *nullRotationMatrix = new G4RotationMatrix();  

  itsPhysiComp2 = 
    new G4PVPlacement(
		      nullRotationMatrix,  // no rotation
		      nullThreeVector,     // its position
		      itsInnerLogVol,      // its logical volume
		      itsName+"_combined", // its name
		      itsSolidLogVol,      // its mother  volume
		      false,		   // no boolean operation
		      0);		   // copy number 


  if(BDSGlobals->GetSensitiveComponents()){
    SetSensitiveVolume(itsSolidLogVol);
  }

  itsSolidLogVol->
    SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,
				       BDSGlobals-> GetThresholdCutCharged()));
  
  itsPhysiComp = 
    new G4PVPlacement(
		      nullRotationMatrix,   // no rotation
		      nullThreeVector,        // its position
		      itsSolidLogVol,    // its logical volume
		      itsName+"_solid",	     // its name
		      itsMarkerLogicalVolume, // its mother  volume
		      false,		     // no boolean operation
		      0);		     // copy number  
  SetMultiplePhysicalVolumes(itsPhysiComp);
  SetMultiplePhysicalVolumes(itsPhysiComp2);
}


BDSCollimator::~BDSCollimator()
{
  if(itsVisAttributes) delete itsVisAttributes;
  if(itsUserLimits) delete itsUserLimits;
  if(itsInnerTunnelUserLimits) delete itsInnerTunnelUserLimits;
  if(itsTunnelUserLimits) delete itsTunnelUserLimits;
  if(itsSoilTunnelUserLimits) delete itsSoilTunnelUserLimits;

  if(itsMarkerLogicalVolume)delete itsMarkerLogicalVolume;
  if(itsSolidLogVol)delete itsSolidLogVol;
  if(itsInnerLogVol)delete itsInnerLogVol;

  if(itsPhysiComp) delete itsPhysiComp;
  if(itsPhysiComp2) delete itsPhysiComp2;

  if(itsSoilTube) delete itsSoilTube;
  if(itsTunnelTube) delete itsTunnelTube;
  if(itsInnerTunnelTube) delete itsInnerTunnelTube;
  if(itsInnerTunnelLogicalVolume) delete itsInnerTunnelLogicalVolume;
  if(itsSoilTunnelLogicalVolume) delete itsSoilTunnelLogicalVolume;
}
