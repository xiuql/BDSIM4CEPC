#include "BDSMagnetOuterFactoryPolesSquare.hh"

#include "BDSGlobalConstants.hh"
#include "BDSMaterials.hh"
#include "BDSMagnetColours.hh"
#include "BDSSDManager.hh"

#include "globals.hh"

#include "G4Box.hh"
#include "G4EllipticalTube.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4VSolid.hh"

#include <vector>
#include <cmath>

BDSMagnetOuterFactoryPolesSquare* BDSMagnetOuterFactoryPolesSquare::_instance = 0;

BDSMagnetOuterFactoryPolesSquare* BDSMagnetOuterFactoryPolesSquare::Instance()
{
  if (_instance == 0)
    {_instance = new BDSMagnetOuterFactoryPolesSquare();}
  return _instance;
}

BDSMagnetOuterFactoryPolesSquare::~BDSMagnetOuterFactoryPolesSquare()
{
  _instance = 0;
}

void BDSMagnetOuterFactoryPolesSquare::CreatePoleSolid(G4String     name,
						       G4double     length,
						       G4int        order)
{
  G4int nPoles = 2*order;
  
  // full circle is divided into segments for each pole
  G4double segmentAngleWidth = CLHEP::twopi / (G4double)nPoles;
  G4double poleAngle = segmentAngleWidth * poleAngularFraction;

  // compose pole of an annulus of a certain angle plus
  // an ellipsoid at the inner side. make the union of the
  // two to give a typical pole shape - curved inner surface
  // with increasing width outwards
  
  // make some % of pole length curved ellipsoidal surface

  G4double  croppingBoxRadius = yokeStartRadius - lengthSafety;
  G4VSolid* croppingBoxSolid = new G4Box(name + "_pole_intersection_solid", // name
					 croppingBoxRadius,                 // x half width
					 croppingBoxRadius,                 // y half width
					 length);                           // z length
  // z length long for unambiguous intersection
  
  G4double poleLength          = poleFinishRadius - poleStartRadius - 2*lengthSafety;
  G4double ellipsoidHeight     = poleTipFraction*poleLength;
  //G4double annulusHeight       = poleLength - ellipsoidHeight;
  G4double ellipsoidCentre     = poleStartRadius + ellipsoidHeight*0.5;
  
  // work out the chord length
  G4double ellipsoidWidth      = 2*(poleStartRadius + 0.5*ellipsoidHeight) * tan(poleAngle*0.5);
  
  G4double annulusStartRadius  = ellipsoidCentre / cos(poleAngle*0.5); //so edges line up with ellipsoid edges
  G4double annulusFinishRadius = poleFinishRadius*2; // long for unambiguous intersection with yoke

  G4VSolid* poleTip = new G4EllipticalTube(name + "_pole_tip_solid",   // name
					       ellipsoidHeight*0.5,        // x half width
					       ellipsoidWidth*0.5,         // y half width
					       length*0.5 - lengthSafety); // z half width

  G4VSolid* poleAnnulus = new G4Tubs(name + "_pole_annulus_solid", // name
				     annulusStartRadius,           // start radius
				     annulusFinishRadius,          // finish radius
				     length*0.5 - lengthSafety,    // z half length
				     -poleAngle*0.5,               // start angle
				     poleAngle);                   // sweep angle
  
  // note annulus is defined from centre of rotation
  G4ThreeVector ellipsoidTranslation(poleStartRadius + ellipsoidHeight*0.5, 0, 0);
  // the centre of the union solid will be that of the 1st solid - the annulus - ie 0,0,0
  G4VSolid* aSinglePoleSolid = new G4UnionSolid(name + "_pole_solid", // name
						poleAnnulus,          // solid 1
						poleTip,              // solid 2
						0,                    // rotation matrix
						ellipsoidTranslation);// translation of poleTip
  
  // create different poles to fit inside square yoke
  G4RotationMatrix* iPoleRM;
  for (G4int i = 0; i < nPoles; ++i)
    {
      iPoleRM = new G4RotationMatrix();
      G4double segmentAngle = CLHEP::twopi/nPoles; // angle per pole
      G4double rotationAngle = (0.5-i)*segmentAngle + CLHEP::pi*0.5;
      iPoleRM->rotateZ(rotationAngle); 
      // crop the singlepolesolid with the cropping box so it'll fit inside the outer square yoke
      G4IntersectionSolid* aSolid = new G4IntersectionSolid(name + "_pole_solid", // name
								aSinglePoleSolid,
								croppingBoxSolid,     // solid 2 - the one to be shifted
								iPoleRM,              // rotation matrix
								(G4ThreeVector)0);    // translation vector
					  
								
      poleSolids.push_back(aSolid);
      
      poleRotations.push_back(iPoleRM);
    }
}

void BDSMagnetOuterFactoryPolesSquare::CreateYokeAndContainerSolid(G4String      name,
								   G4double      length,
								   G4int         /*order*/)
{
  // square yoke - have to do subtraction between two solid boxes
  G4VSolid* yokeOuter = new G4Box(name + "_yoke_outer_solid", // name
				  yokeFinishRadius,           // x half width
				  yokeFinishRadius,           // y half width
				  length*0.5 - lengthSafety); // z half length

  G4VSolid* yokeInner = new G4Box(name + "_yoke_inner_solid", // name
				  yokeStartRadius,            // x half width
				  yokeStartRadius,            // y half width
				  length);                    // z half length
  // inner length is 2x as long for unambiguous subtraction

  yokeSolid = new G4SubtractionSolid(name + "_yoke_solid",    // name
				     yokeOuter,
				     yokeInner);

  // note container must have hole in it for the beampipe to fit in!
  // poled geometry doesn't fit tightly to beampipe so can alays use a circular aperture

  G4VSolid* containerOuter = new G4Box(name + "_container_outer_solid", // name
				       yokeFinishRadius*0.5,            // x half width
				       yokeFinishRadius*0.5,            // y half width
				       length*0.5);                     // x half width

  G4VSolid* containerInner = new G4Tubs(name + "_container_inner_solid", // name
					0,                               // inner radius
					poleStartRadius,                 // finish radius
					length,                          // z half length
					0,                               // start angle
					CLHEP::twopi);                   // sweep angle
  // length of inner is long for unambiguous subtraction

  containerSolid = new G4SubtractionSolid(name + "_container_solid", // name
					  containerOuter,
					  containerInner);
}

void BDSMagnetOuterFactoryPolesSquare::CreateLogicalVolumes(G4String    name,
							    G4double    length,
							    G4int       order,
							    G4Material* outerMaterial)
{
  // VISUAL ATTRIBUTES
  // set visual attributes
  G4Colour* magnetColour = BDSMagnetColours::Instance()->GetMagnetColour(order);
  G4VisAttributes* outerVisAttr = new G4VisAttributes(*magnetColour);
  outerVisAttr->SetVisibility(true);
  outerVisAttr->SetForceSolid(true);
  outerVisAttr->SetForceLineSegmentsPerCircle(50);

  for (G4int n = 0; n < 2*order; ++n)
    {
      G4LogicalVolume* thisPole = new G4LogicalVolume(poleSolids[n],
						      outerMaterial,
						      name + "_pole_lv");
      thisPole->SetVisAttributes(outerVisAttr);
      thisPole->SetSensitiveDetector(BDSSDManager::Instance()->GetEnergyCounterOnAxisSD());
      poleLVs.push_back(thisPole);
    }

  // yoke
  yokeLV   = new G4LogicalVolume(yokeSolid,
				 outerMaterial,
				 name + "_yoke_lv");
  yokeLV->SetVisAttributes(outerVisAttr);
  yokeLV->SetSensitiveDetector(BDSSDManager::Instance()->GetEnergyCounterOnAxisSD());

  // container
  G4Material* emptyMaterial = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetEmptyMaterial());
  containerLV = new G4LogicalVolume(containerSolid,
				    emptyMaterial,
				    name + "_container_lv");
#ifdef BDSDEBUG
  containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr());
#else
  containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
#endif

  // USER LIMITS
  // set user limits based on bdsim user specified parameters
#ifndef NOUSERLIMITS
  G4UserLimits* outerUserLimits = new G4UserLimits("outer_cuts");
  G4double maxStepFactor = 0.5; // fraction of length for maximum step size
  outerUserLimits->SetMaxAllowedStep( length * maxStepFactor );
  outerUserLimits->SetUserMinEkine(BDSGlobalConstants::Instance()->GetThresholdCutCharged());
  outerUserLimits->SetUserMaxTime(BDSGlobalConstants::Instance()->GetMaxTime());
  //attach cuts to volumes
  yokeLV->SetUserLimits(outerUserLimits);
  containerLV->SetUserLimits(outerUserLimits);
  std::vector<G4LogicalVolume*>::iterator j;
  for(j = poleLVs.begin(); j != poleLVs.end(); ++j)
    {
      (*j)->SetUserLimits(outerUserLimits);
    }
#endif
}

void BDSMagnetOuterFactoryPolesSquare::PlaceComponents(G4String name,
						       G4int    order)
{
  // PLACEMENT
  // place the components inside the container
  // note we don't need the pointer for placements - it's registered upon construction with g4
  new G4PVPlacement((G4RotationMatrix*)0,         // no rotation
		    (G4ThreeVector)0,             // position
		    yokeLV,                       // lv to be placed
		    name + "_yoke_pv",            // name
		    containerLV,                  // mother lv to be placed in
		    false,                        // no boolean operation
		    0,                            // copy number
		    BDSGlobalConstants::Instance()->GetCheckOverlaps() // whether to check overlaps
		    );
  
  // pole placement
  G4double nPoles = 2*order;
  for (G4int n = 0; n < 2*order; ++n)
    {
      G4RotationMatrix* rm = new G4RotationMatrix();
      G4double segmentAngle = CLHEP::twopi/nPoles; // angle per pole
      G4double rotationAngle = (0.5-n)*segmentAngle + CLHEP::pi*0.5;
      rm->rotateZ(-rotationAngle); 
      // only need to test the end of one iterator as both should be the same length
      new G4PVPlacement(rm,                 // rotation
			(G4ThreeVector)0,   // position
			poleLVs[n],         // logical volume
			name + "_pole_pv",  // name      
			containerLV,        // mother lv to be placed in
			false,              // no boolean operation
			n,                  // copy number
			BDSGlobalConstants::Instance()->GetCheckOverlaps()); // check overlaps
      //name + "_pole_" + printf("_%d_pv", n), // name
      }
}

void BDSMagnetOuterFactoryPolesSquare::CleanUp()
{
  poleRotations.clear();
  poleSolids.clear();
  poleLVs.clear();
}
  
