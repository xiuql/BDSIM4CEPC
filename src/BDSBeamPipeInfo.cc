#include "BDSBeamPipeInfo.hh"
#include "BDSBeamPipeType.hh"
#include "BDSDebug.hh"
#include "BDSMaterials.hh"
#include "BDSUtilities.hh"

#include "globals.hh" // geant4 types / globals
#include "G4Material.hh"


BDSBeamPipeInfo::BDSBeamPipeInfo(BDSBeamPipeType beamPipeTypeIn,
				 G4double        aper1In,
				 G4double        aper2In,
				 G4double        aper3In,
				 G4double        aper4In,
				 G4Material*     vacuumMaterialIn,
				 G4double        beamPipeThicknessIn,
				 G4Material*     beamPipeMaterialIn,
				 G4double        angleInIn,
				 G4double        angleOutIn):
  beamPipeType(beamPipeTypeIn),
  aper1(aper1In), aper2(aper2In), aper3(aper3In), aper4(aper4In),
  vacuumMaterial(vacuumMaterialIn),
  beamPipeThickness(beamPipeThicknessIn),
  beamPipeMaterial(beamPipeMaterialIn),
  angleIn(angleInIn),
  angleOut(angleOutIn)
{
  CheckApertureInfo();
}

BDSBeamPipeInfo::BDSBeamPipeInfo(G4String beamPipeTypeIn,
				 G4double aper1In,
				 G4double aper2In,
				 G4double aper3In,
				 G4double aper4In,
				 G4String vacuumMaterialIn,
				 G4double beamPipeThicknessIn,
				 G4String beamPipeMaterialIn,
				 G4double angleInIn,
				 G4double angleOutIn):
  aper1(aper1In), aper2(aper2In), aper3(aper3In), aper4(aper4In),
  beamPipeThickness(beamPipeThicknessIn),
  angleIn(angleInIn),
  angleOut(angleOutIn)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "vacuum material: " << vacuumMaterialIn << G4endl;
#endif
  beamPipeType     = BDS::DetermineBeamPipeType(beamPipeTypeIn);
  vacuumMaterial   = BDSMaterials::Instance()->GetMaterial(vacuumMaterialIn);
  beamPipeMaterial = BDSMaterials::Instance()->GetMaterial(beamPipeMaterialIn);
  CheckApertureInfo();
}
  
BDSBeamPipeInfo::BDSBeamPipeInfo(BDSBeamPipeInfo* defaultInfo,
				 G4String         beamPipeTypeIn,
				 G4double         aper1In,
				 G4double         aper2In,
				 G4double         aper3In,
				 G4double         aper4In,
				 G4String         vacuumMaterialIn,
				 G4double         beamPipeThicknessIn,
				 G4String         beamPipeMaterialIn,
				 G4double         angleInIn,
				 G4double         angleOutIn):
  angleIn(angleInIn),
  angleOut(angleOutIn)
{
  if (beamPipeTypeIn == "")
    {beamPipeType = defaultInfo->beamPipeType;}
  else 
    {beamPipeType = BDS::DetermineBeamPipeType(beamPipeTypeIn);}

  if (!BDS::IsFinite(aper1In))
    {aper1 = defaultInfo->aper1;}
  else
    {aper1 = aper1In;}
  if (!BDS::IsFinite(aper2In))
    {aper2 = defaultInfo->aper2;}
  else
    {aper2 = aper2In;}
  if (!BDS::IsFinite(aper3In))
    {aper3 = defaultInfo->aper3;}
  else
    {aper3 = aper3In;}
  if (!BDS::IsFinite(aper4In))
    {aper4 = defaultInfo->aper4;}
  else
    {aper4 = aper4In;}
  if (!BDS::IsFinite(beamPipeThicknessIn))
    {beamPipeThickness = defaultInfo->beamPipeThickness;}
  else
    {beamPipeThickness = beamPipeThicknessIn;}
  
  if (vacuumMaterialIn == "")
    {vacuumMaterial = defaultInfo->vacuumMaterial;}
  else
    {vacuumMaterial = BDSMaterials::Instance()->GetMaterial(vacuumMaterialIn);}
  if (beamPipeMaterialIn == "")
    {beamPipeMaterial = defaultInfo->beamPipeMaterial;}
  else
    {beamPipeMaterial = BDSMaterials::Instance()->GetMaterial(beamPipeMaterialIn);}
  
  CheckApertureInfo();
}
  
void BDSBeamPipeInfo::CheckApertureInfo()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  switch (beamPipeType.underlying())
    {
    case BDSBeamPipeType::circular:
      InfoOKForCircular();    break;
    case BDSBeamPipeType::elliptical:
      InfoOKForElliptical();  break;
    case BDSBeamPipeType::rectangular:
      InfoOKForRectangular(); break;
    case BDSBeamPipeType::lhc:
      InfoOKForLHC();         break;
    case BDSBeamPipeType::lhcdetailed:
      InfoOKForLHCDetailed(); break;
    case BDSBeamPipeType::rectellipse:
      InfoOKForRectEllipse(); break;
    case BDSBeamPipeType::racetrack:
      InfoOKForRaceTrack();   break;
    case BDSBeamPipeType::octagonal:
      InfoOKForOctagonal();   break;
    default:
      InfoOKForCircular();
    }
}

void BDSBeamPipeInfo::CheckRequiredParametersSet(G4bool setAper1,
						 G4bool setAper2,
						 G4bool setAper3,
						 G4bool setAper4)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
  G4cout << "aper1: " << aper1 << " check it? " << setAper1 << G4endl;
  G4cout << "aper2: " << aper2 << " check it? " << setAper2 << G4endl;
  G4cout << "aper3: " << aper3 << " check it? " << setAper3 << G4endl;
  G4cout << "aper4: " << aper4 << " check it? " << setAper4 << G4endl;
#endif
  G4bool shouldExit = false;
  if (setAper1)
    {
      if (!BDS::IsFinite(aper1))
	{G4cerr << "\"aper1\" not set, but required to be" << G4endl; shouldExit = true;}
    }

  if (setAper2)
    {
      if (!BDS::IsFinite(aper2))
	{G4cerr << "\"aper2\" not set, but required to be" << G4endl; shouldExit = true;}
    }

  if (setAper3)
    {
      if (!BDS::IsFinite(aper3))
	{G4cerr << "\"aper3\" not set, but required to be" << G4endl; shouldExit = true;}
    }

  if (setAper4)
    {
      if (!BDS::IsFinite(aper4))
	{G4cerr << "\"aper4\" not set, but required to be" << G4endl; shouldExit = true;}
    }

  if (shouldExit)
    {exit(1);}
}

void BDSBeamPipeInfo::InfoOKForCircular()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CheckRequiredParametersSet(true, false, false, false);
}

void BDSBeamPipeInfo::InfoOKForElliptical()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CheckRequiredParametersSet(true, true, false, false);
}

void BDSBeamPipeInfo::InfoOKForRectangular()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CheckRequiredParametersSet(true, true, false, false);
}

void BDSBeamPipeInfo::InfoOKForLHC()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CheckRequiredParametersSet(true, true, true, false);

  if ((aper3 > aper1) and (aper2 < aper3))
    {
      G4cerr << __METHOD_NAME__ << "WARNING - \"aper3\" > \"aper1\" (or \"beamPipeRadius\") for lhc aperture model - will not produce desired shape" << G4endl;
      exit(1);
    }

  if ((aper3 > aper2) and (aper1 < aper3))
    {
      G4cerr << __METHOD_NAME__ << "WARNING - \"aper3\" > \"aper2\" (or \"beamPipeRadius\") for lhc aperture model - will not produce desired shape" << G4endl;
      exit(1);
    }
}

void BDSBeamPipeInfo::InfoOKForLHCDetailed()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  InfoOKForLHC();
}

void BDSBeamPipeInfo::InfoOKForRectEllipse()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CheckRequiredParametersSet(true, true, true, true);

  // TBC
  
  /*
  //treat rectangle as point coordinates.  If this point is inside ellipse,
  //rectangle is too small -> error should just use elliptical aperture
  G4double test = sqrt((aper1/aper3)*(aper1/aper3) + (aper2/aper4)*(aper2/aper4));
  if (test < 1)
    {
      //rectangle too small
      G4cerr << __METHOD_NAME__ << "WARNING - combination of \"aper1\" and \"aper2\" too small"
	     << " rectangle is entirely inside ellipse - simply use elliptical aperture" << G4endl;
      exit(1);
    }
  */
  //check if ellipse is b
  //if ((aper1 > aper3) and (aper2 > aper4))
  //  {;}
}

void BDSBeamPipeInfo::InfoOKForRaceTrack()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CheckRequiredParametersSet(true, true, true, false);
}

void BDSBeamPipeInfo::InfoOKForOctagonal()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CheckRequiredParametersSet(true, true, true, true);

  if (aper3 >= aper1)
    {G4cerr << "aper3 is >= aper1 - invalid for an octagonal aperture"; exit(1);}
  if (aper4 >= aper2)
    {G4cerr << "aper4 is >= aper2 - invalid for an octagonal aperture"; exit(1);}
}

