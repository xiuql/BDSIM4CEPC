/* BDSIM code.    Version 1.0
   Author: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 02.12.2004
   Copyright (c) 2004 by J.C.Carter.  ALL RIGHTS RESERVED. 
*/
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSInteractionPointLeft.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"

#include "BDSAcceleratorComponent.hh"


#include <map>

//============================================================

typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
extern LogVolMap* LogVol;

extern BDSMaterials* theMaterials;
extern G4RotationMatrix* RotY90;

//============================================================

BDSInteractionPointLeft::BDSInteractionPointLeft(G4String& aName,G4double aLength,
					 G4double bpRad):
  BDSAcceleratorComponent(
			  aName,
			  aLength,bpRad,0,0,
			  SetVisAttributes())
{
  BuildIPLogicalVolume();
  BuildBeamCal();
  BuildLumiCal();
  BuildQuadFront();
}

void BDSInteractionPointLeft::BuildIPLogicalVolume()
{
  // Build the logical volume for the IP components to be placed within.

  if(!(*LogVolCount)[itsName])
    {
      G4double TransSize;
      if(BDSGlobals->GetAcceleratorType()->GetType()=="atf")
	TransSize = BDSGlobals->GetComponentBoxSize();
      else
	TransSize = 2. *BDSGlobals->GetTunnelRadius();

      itsMarkerLogicalVolume = 
	new G4LogicalVolume(new G4Box(itsName+"Left_solid",
				      TransSize,
				      TransSize,
				      itsLength/2),
			    theMaterials->LCVacuum,
			    itsName);

      (*LogVolCount)[itsName] = 1;
      (*LogVol)[itsName] = itsMarkerLogicalVolume;

      itsOuterUserLimits = new G4UserLimits();
      itsOuterUserLimits->SetMaxAllowedStep(itsLength);
      itsMarkerLogicalVolume->SetUserLimits(itsOuterUserLimits);
    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume = (*LogVol)[itsName];
    }
}

void BDSInteractionPointLeft::BuildBeamCal()
{
  // Build the BeamCal component. Size is not changable outside of this code
  G4double OuterBeamCalRadius = 0.120*m; // These radius figures are guessed
  G4double InnerBeamCalRadius = 0.030*m; // the given slide diagram

  G4double BeamCalUpperDist = 3.850*m;
  G4double BeamCalLowerDist = 3.650*m;
  G4double BeamCalLength = BeamCalUpperDist - BeamCalLowerDist;
  G4double BeamCalZMidPoint = BeamCalLowerDist + BeamCalLength/2 - itsLength/2;

  itsOuterBeamCalTube = new G4Tubs(itsName+"Left_BeamCal_OuterTube",
				   0.,
				   OuterBeamCalRadius,
				   BeamCalLength/2,
				   0,
				   twopi*radian);

  itsInnerBeamCalTube = new G4Tubs(itsName+"Left_BeamCal_InnerTube",
				   0.,
				   InnerBeamCalRadius,
				   BeamCalLength/2,
				   0,
				   twopi*radian);
  
  itsOuterBeamCalLogicalVolume = new G4LogicalVolume(itsOuterBeamCalTube,
						     theMaterials->LCTungsten,
						     itsName+"Left_OuterBeamCal_Logical");

  itsInnerBeamCalLogicalVolume = new G4LogicalVolume(itsInnerBeamCalTube,
						     theMaterials->LCVacuum,
						     itsName+"Left_InnnerBeamCal_Logical");

  G4VPhysicalVolume* PhysiInner = new G4PVPlacement(0,
						   G4ThreeVector(0.,0.,0.),
						   itsInnerBeamCalLogicalVolume,
						   itsName+"Left_InnerBeamCal",
						   itsOuterBeamCalLogicalVolume,
						   false,
						   0);

  G4RotationMatrix* Rot = NULL;
  if(itsAngle!=0) Rot = RotY90;

  G4VPhysicalVolume* PhysiComp = new G4PVPlacement(Rot,
						  G4ThreeVector(0.,0.,BeamCalZMidPoint),
						  itsOuterBeamCalLogicalVolume,
						  itsName+"Left_BeamCal",
						  itsMarkerLogicalVolume,
						  false,
						  0);

  itsOuterBeamCalUserLimits =
     new G4UserLimits("OuterBeamCal Cuts",DBL_MAX,DBL_MAX,DBL_MAX,
		      BDSGlobals->GetThresholdCutCharged());
   
   itsInnerBeamCalUserLimits =
     new G4UserLimits("InnerBeamCal Cuts",DBL_MAX,DBL_MAX,DBL_MAX,
		      BDSGlobals->GetThresholdCutCharged());
   
   itsOuterBeamCalUserLimits->SetMaxAllowedStep(BeamCalLength);
   
   itsOuterBeamCalLogicalVolume->SetUserLimits(itsOuterBeamCalUserLimits);
   
   itsInnerBeamCalUserLimits->SetMaxAllowedStep(BeamCalLength);
   
   itsInnerBeamCalLogicalVolume->SetUserLimits(itsInnerBeamCalUserLimits);

}

void BDSInteractionPointLeft::BuildLumiCal()
{
  // Build the LumiCal component. Size is not changable outside of this code

  G4double OuterLumiCalRadius = 0.280*m; // These radius figures are guessed
  G4double InnerLumiCalRadius = 0.080*m; // from the given slide diagram

  G4double LumiCalUpperDist = 3.250*m;
  G4double LumiCalLowerDist = 3.050*m;
  G4double LumiCalLength = LumiCalUpperDist - LumiCalLowerDist;
  G4double LumiCalZMidPoint = LumiCalLowerDist + LumiCalLength/2 - itsLength/2;
  
  itsOuterLumiCalTube = new G4Tubs(itsName+"Left_LumiCal_OuterTube",
				   0.,
				   OuterLumiCalRadius,
				   LumiCalLength/2,
				   0,
				   twopi*radian);

  itsInnerLumiCalTube = new G4Tubs(itsName+"Left_LumiCal_InnerTube",
				   0.,
				   InnerLumiCalRadius,
				   LumiCalLength/2,
				   0,
				   twopi*radian);
  
  itsOuterLumiCalLogicalVolume = new G4LogicalVolume(itsOuterLumiCalTube,
						     theMaterials->LCTungsten,
						     itsName+"Left_OuterLumiCal_Logical");

  itsInnerLumiCalLogicalVolume = new G4LogicalVolume(itsInnerLumiCalTube,
						     theMaterials->LCVacuum,
						     itsName+"Left_InnnerLumiCal_Logical");

  G4VPhysicalVolume* PhysiInner = new G4PVPlacement(0,
						   G4ThreeVector(0.,0.,0.),
						   itsInnerLumiCalLogicalVolume,
						   itsName+"Left_InnerLumiCal",
						   itsOuterLumiCalLogicalVolume,
						   false,
						   0);

  G4RotationMatrix* Rot = NULL;
  if(itsAngle!=0) Rot = RotY90;

  G4VPhysicalVolume* PhysiComp = new G4PVPlacement(Rot,
						  G4ThreeVector(0.,0.,LumiCalZMidPoint),
						  itsOuterLumiCalLogicalVolume,
						  itsName+"Left_LumiCal",
						  itsMarkerLogicalVolume,
						  false,
						  0);

  itsOuterLumiCalUserLimits =
     new G4UserLimits("OuterLumiCal Cuts",DBL_MAX,DBL_MAX,DBL_MAX,
		      BDSGlobals->GetThresholdCutCharged());
   
   itsInnerLumiCalUserLimits =
     new G4UserLimits("InnerLumiCal Cuts",DBL_MAX,DBL_MAX,DBL_MAX,
		      BDSGlobals->GetThresholdCutCharged());
   
   itsOuterLumiCalUserLimits->SetMaxAllowedStep(LumiCalLength);
   
   itsOuterLumiCalLogicalVolume->SetUserLimits(itsOuterLumiCalUserLimits);
   
   itsInnerLumiCalUserLimits->SetMaxAllowedStep(LumiCalLength);
   
   itsInnerLumiCalLogicalVolume->SetUserLimits(itsInnerLumiCalUserLimits);

}

void BDSInteractionPointLeft::BuildQuadFront()
{
  // Build the Quad Front component. Size is not changable outside of this code
  
  G4double OuterQuadFrontRadius = 0.170*m; // These radius figures are guessed
  G4double InnerQuadFrontRadius = 0.040*m; // from the given slide diagram

  G4double QuadFrontUpperDist = 4.050*m;
  G4double QuadFrontLowerDist = 3.950*m;
  G4double QuadFrontLength = QuadFrontUpperDist - QuadFrontLowerDist;
  G4double QuadFrontZMidPoint = QuadFrontLowerDist + QuadFrontLength/2 - itsLength/2;
  
  itsOuterQuadFrontTube = new G4Tubs(itsName+"Left_QuadFront_OuterTube",
				     0.,
				     OuterQuadFrontRadius,
				     QuadFrontLength/2,
				     0,
				     twopi*radian);
  
  itsInnerQuadFrontTube = new G4Tubs(itsName+"Left_QuadFront_InnerTube",
				     0.,
				     InnerQuadFrontRadius,
				     QuadFrontLength/2,
				     0,
				     twopi*radian);
  
  itsOuterQuadFrontLogicalVolume = new G4LogicalVolume(itsOuterQuadFrontTube,
						       theMaterials->LCTungsten,
						       itsName+"Left_OuterQuadFront_Logical");
  
  itsInnerQuadFrontLogicalVolume = new G4LogicalVolume(itsInnerQuadFrontTube,
						       theMaterials->LCVacuum,
						       itsName+"Left_InnnerQuadFront_Logical");
  
  G4VPhysicalVolume* PhysiInner = new G4PVPlacement(0,
						   G4ThreeVector(0.,0.,0.),
						   itsInnerQuadFrontLogicalVolume,
						   itsName+"Left_InnerQuadFront",
						   itsOuterQuadFrontLogicalVolume,
						   false,
						   0);
  
  G4RotationMatrix* Rot = NULL;
  if(itsAngle!=0) Rot = RotY90;
  
  G4VPhysicalVolume* PhysiComp = new G4PVPlacement(Rot,
						  G4ThreeVector(0.,0.,QuadFrontZMidPoint),
						  itsOuterQuadFrontLogicalVolume,
						  itsName+"Left_QuadFront",
						  itsMarkerLogicalVolume,
						  false,
						  0);
  
  itsOuterQuadFrontUserLimits =
    new G4UserLimits("OuterQuadFront Cuts",DBL_MAX,DBL_MAX,DBL_MAX,
		     BDSGlobals->GetThresholdCutCharged());
  
  itsInnerQuadFrontUserLimits =
    new G4UserLimits("InnerQuadFront Cuts",DBL_MAX,DBL_MAX,DBL_MAX,
		     BDSGlobals->GetThresholdCutCharged());
  
  itsOuterQuadFrontUserLimits->SetMaxAllowedStep(QuadFrontLength);
  
  itsOuterQuadFrontLogicalVolume->SetUserLimits(itsOuterQuadFrontUserLimits);
  
  itsInnerQuadFrontUserLimits->SetMaxAllowedStep(QuadFrontLength);
  
  itsInnerQuadFrontLogicalVolume->SetUserLimits(itsInnerQuadFrontUserLimits);
  
}

G4VisAttributes* BDSInteractionPointLeft::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0.5,0.5,1));
  return itsVisAttributes;
}


BDSInteractionPointLeft::~BDSInteractionPointLeft()
{
  delete itsOuterBeamCalTube;
  delete itsInnerBeamCalTube;
  
  delete itsOuterLumiCalTube;
  delete itsInnerLumiCalTube;
  
  delete itsOuterQuadFrontTube;
  delete itsInnerQuadFrontTube;

  delete itsVisAttributes;
 
}
