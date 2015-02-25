//  
//   BDSIM, (C) 2001-2007
//   
//   version 0.5-dev
//  
//
//
//   Geometry construction
//
//
//   History
//     19 May 2008 by Marchioni v.0.5-dev
//     18 Mar 2008 by Malton v.0.5-dev
//      3 Oct 2007 by Malton v.0.4
//     21 Nov 2006 by Agapov v.0.3
//     28 Mar 2006 by Agapov v.0.2
//     15 Dec 2005 by Agapov beta
//

//=================================================================

#include <list>
#include <map>
#include <vector>

#include "BDSDetectorConstruction.hh"

#include "BDSExecOptions.hh"
#include "BDSGlobalConstants.hh"
#include "BDSDebug.hh"

#include "BDSSDManager.hh"

#include "G4UserLimits.hh"
#include "G4GeometryManager.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"
#include "G4PropagatorInField.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "globals.hh"
#include "G4ios.hh"

#include "G4Navigator.hh"
#include "G4UniformMagField.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Material.hh"

#include "BDSAcceleratorComponent.hh"
#include "BDSBeamline.hh"
#include "BDSEnergyCounterSD.hh"
#include "BDSLine.hh"
#include "BDSMaterials.hh"
#include "BDSTeleporter.hh"
#include "BDSTerminator.hh"
#include "BDSLogicalVolumeInfo.hh"
#include "BDSComponentFactory.hh"

#include "G4MagneticField.hh"
#include "G4VSampler.hh"
#include "G4GeometrySampler.hh"

#include "ggmad.hh"
#include "parser/element.h"
#include "parser/elementlist.h"
#include "parser/enums.h"

#ifdef BDSDEBUG
bool debug = true;
#else
bool debug = false;
#endif

//=================================================================

BDSDetectorConstruction::BDSDetectorConstruction():
  itsGeometrySampler(NULL),precisionRegion(NULL),gasRegion(NULL),
  solidWorld(NULL),logicWorld(NULL),physiWorld(NULL),
  magField(NULL),BDSUserLimits(NULL),BDSSensitiveDetector(NULL),
  theHitMaker(NULL),theParticleBounds(NULL),_globalRotation(NULL)
{  
  verbose    = BDSExecOptions::Instance()->GetVerbose();
  gflash     = BDSExecOptions::Instance()->GetGFlash();
  gflashemax = BDSExecOptions::Instance()->GetGFlashEMax();
  gflashemin = BDSExecOptions::Instance()->GetGFlashEMin();

  //initialize global rotation matrix
  _globalRotation = new G4RotationMatrix();

  if (gflash) {
    // GFlashStuff
    theParticleBounds  = new GFlashParticleBounds();              // Energy Cuts to kill particles                                                                
    theParticleBounds->SetMaxEneToParametrise(*G4Electron::ElectronDefinition(),gflashemax*CLHEP::GeV);
    theParticleBounds->SetMinEneToParametrise(*G4Electron::ElectronDefinition(),gflashemin*CLHEP::GeV);
    theParticleBounds->SetEneToKill(*G4Electron::ElectronDefinition(),BDSGlobalConstants::Instance()->GetThresholdCutCharged());
    
    theParticleBounds->SetMaxEneToParametrise(*G4Positron::PositronDefinition(),gflashemax*CLHEP::GeV);
    theParticleBounds->SetMinEneToParametrise(*G4Positron::PositronDefinition(),gflashemin*CLHEP::GeV);
    theParticleBounds->SetEneToKill(*G4Positron::PositronDefinition(),BDSGlobalConstants::Instance()->GetThresholdCutCharged());
    
    // theParticleBoundsVac  = new GFlashParticleBounds();              // Energy Cuts to kill particles                                                                
    // theParticleBoundsVac->SetMaxEneToParametrise(*G4Electron::ElectronDefinition(),0*CLHEP::GeV);
    // theParticleBoundsVac->SetMaxEneToParametrise(*G4Positron::PositronDefinition(),0*CLHEP::GeV);

#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << "theParticleBounds - min E - electron: " 
	   << theParticleBounds->GetMinEneToParametrise(*G4Electron::ElectronDefinition())/CLHEP::GeV<< " GeV" << G4endl;
    G4cout << __METHOD_NAME__ << "theParticleBounds - max E - electron: " 
	   << theParticleBounds->GetMaxEneToParametrise(*G4Electron::ElectronDefinition())/CLHEP::GeV<< G4endl;
    G4cout << __METHOD_NAME__ << "theParticleBounds - kill E - electron: " 
	   << theParticleBounds->GetEneToKill(*G4Electron::ElectronDefinition())/CLHEP::GeV<< G4endl;
    G4cout << __METHOD_NAME__ << "theParticleBounds - min E - positron: " 
	   << theParticleBounds->GetMinEneToParametrise(*G4Positron::PositronDefinition())/CLHEP::GeV<< G4endl;
    G4cout << __METHOD_NAME__ << "theParticleBounds - max E - positron: " 
	   << theParticleBounds->GetMaxEneToParametrise(*G4Positron::PositronDefinition())/CLHEP::GeV<< G4endl;
    G4cout << __METHOD_NAME__ << "theParticleBounds - kill E - positron: " 
	   << theParticleBounds->GetEneToKill(*G4Positron::PositronDefinition())/CLHEP::GeV<< G4endl;
#endif

    theHitMaker          = new GFlashHitMaker();                    // Makes the EnergieSpots 
  }
}


//=================================================================

G4VPhysicalVolume* BDSDetectorConstruction::Construct()
{
  gasRegion   = new G4Region("gasRegion");

  G4ProductionCuts* theGasProductionCuts = new G4ProductionCuts();
  theGasProductionCuts->SetProductionCut(1*CLHEP::m,G4ProductionCuts::GetIndex("gamma"));
  theGasProductionCuts->SetProductionCut(1*CLHEP::m,G4ProductionCuts::GetIndex("e-"));
  theGasProductionCuts->SetProductionCut(1*CLHEP::m,G4ProductionCuts::GetIndex("e+"));
  gasRegion->SetProductionCuts(theGasProductionCuts);
  
  if (verbose || debug) G4cout << "-->starting BDS construction \n"<<G4endl;
  //construct bds
  return ConstructBDS(beamline_list);
}

G4VPhysicalVolume* BDSDetectorConstruction::ConstructBDS(ElementList& beamline_list)
{  
  // prepare materials for this run
  BDSMaterials::Instance()->PrepareRequiredMaterials();
  
  // set global magnetic field first
  SetMagField(0.0); // necessary to set a global field; so choose zero
  
  // construct the component list
  BuildBeamline();

  // build world and calculate coordinates
  BuildWorld();

  // set default output formats for BDSDetector:
  int G4precision = G4cout.precision(15);
  
  // placement procedure
  ComponentPlacement();

#ifdef BDSDEBUG
  BDSBeamline::Instance()->print();
#endif
  
  // construct tunnel
  BuildTunnel();

  // free the parser list
  std::list<struct Element>::iterator it;
  for(it = beamline_list.begin();it!=beamline_list.end();it++) {
    delete (*it).lst;
  }
  beamline_list.clear();

  if(verbose || debug) G4cout<<"end placement, size="<<BDSBeamline::Instance()->size()<<G4endl;
  
  if(verbose || debug) G4cout<<"Detector Construction done"<<G4endl; 

#ifdef BDSDEBUG 
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
#endif

  if(verbose || debug) G4cout<<"Finished listing materials, returning physiWorld"<<G4endl; 
  
  // set precision back
  G4cout.precision(G4precision);

  return physiWorld;
}

//=================================================================
 
void BDSDetectorConstruction::SetMagField(const G4double fieldValue){
  
  G4FieldManager* fieldMgr =
    G4TransportationManager::GetTransportationManager()->GetFieldManager();
  magField = new G4UniformMagField(G4ThreeVector(0.,fieldValue,0.));  
  fieldMgr->SetDetectorField(magField);
  fieldMgr->CreateChordFinder(magField);
}

//=================================================================
BDSDetectorConstruction::~BDSDetectorConstruction()
{ 
  delete precisionRegion;
  gFlashRegion.clear();

  delete _globalRotation;

  delete theHitMaker;
  delete theParticleBounds;
  //  delete theParticleBoundsVac;
}

//=================================================================
void BDSDetectorConstruction::BuildBeamline(){
  std::list<struct Element>::iterator it;
  // Special ring machine bits
  // Add teleporter to account for slight ring offset
  // Add terminator to do ring turn counting logic
  // Both only in case of a circular machine
  // must be done before we parse the element list (for correct coordinates)
  if (BDSExecOptions::Instance()->GetCircular()) {
#ifdef BDSDEBUG
    G4cout << "Circular machine - this is the last element - creating terminator & teleporter" << G4endl;
#endif
    AddTeleporterToEndOfBeamline(&beamline_list);
    AddTerminatorToEndOfBeamline(&beamline_list);
  }

  // convert the parsed element list to list of BDS elements
  BDSComponentFactory* theComponentFactory = new BDSComponentFactory();

  if (verbose || debug) G4cout << "parsing the beamline element list..."<< G4endl;
  for(it = beamline_list.begin();it!=beamline_list.end();it++){

#ifdef BDSDEBUG
    G4cout << "BDSDetectorConstruction creating component " << (*it).name << G4endl;
#endif

    BDSAcceleratorComponent* temp = theComponentFactory->createComponent(it, beamline_list);
    if(temp){
      if (temp->GetType() == "line") {
	// dynamic cast to access methods for iteration
	BDSLine* line = dynamic_cast<BDSLine*>(temp);
	if (line) {
	  //line of components to be added individually
	  for (BDSLine::BDSLineIterator i = line->begin(); i != line->end(); ++i) {
	    BDSBeamline::Instance()->addComponent(*i);}
	}
      }
      else {
	//single component
	BDSBeamline::Instance()->addComponent(temp);
      }
    }
  }
  
  delete theComponentFactory;

#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "size of beamline element list: "<< beamline_list.size() << G4endl;
#endif
  G4cout << __METHOD_NAME__ << "size of theBeamline: "<< BDSBeamline::Instance()->size() << G4endl;

  if (BDSBeamline::Instance()->size() == 0) {
    G4cout << __METHOD_NAME__ << "beamline empty or no line selected! exiting" << G4endl;
    exit(1);
  }
}

void BDSDetectorConstruction::BuildWorld(){
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  G4ThreeVector maxpositive = BDSBeamline::Instance()->GetMaximumExtentPositive();
  G4ThreeVector maxnegative = BDSBeamline::Instance()->GetMaximumExtentNegative();
  G4ThreeVector worldR;
  for (int i = 0; i < 3; i++){
    worldR[i] = std::max(fabs(maxpositive[i]),fabs(maxnegative[i]));
  }
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " world extent positive : " << maxpositive << G4endl;
  G4cout << __METHOD_NAME__ << " world extent negative : " << maxnegative << G4endl;
  G4cout << __METHOD_NAME__ << " world half size determined to be strictly: " << worldR << G4endl;
#endif
  worldR += G4ThreeVector(5000,5000,5000); //add 5m extra in every dimension
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " with 5m margin becomes in all dimensions : " << worldR << G4endl;
#endif
  
  G4String worldName="World";
  solidWorld = new G4Box(worldName, worldR.x(), worldR.y(), worldR.z());
    
  logicWorld = new G4LogicalVolume(solidWorld,	       //its solid
				   BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetEmptyMaterial()), //its material
				   worldName);	       //its name

  // visual attributes
#ifdef BDSDEBUG
  G4VisAttributes* debugWorldVis = new G4VisAttributes(*(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr()));
  debugWorldVis->SetForceWireframe(true);//just wireframe so we can see inside it
  logicWorld->SetVisAttributes(debugWorldVis);
#else
  logicWorld->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
#endif
	
  // set limits
#ifndef NOUSERLIMITS
  G4UserLimits* WorldUserLimits = new G4UserLimits(*(BDSGlobalConstants::Instance()->GetDefaultUserLimits()));
  WorldUserLimits->SetMaxAllowedStep(worldR.z()*0.5);
  logicWorld->SetUserLimits(WorldUserLimits);
#endif

  // create regions
#ifdef BDSDEBUG
  G4cout<<"Creating regions..."<<G4endl;
#endif
  precisionRegion = new G4Region("precisionRegion");
  G4ProductionCuts* theProductionCuts = new G4ProductionCuts();
  if(BDSGlobalConstants::Instance()->GetProdCutPhotonsP()>0)
    theProductionCuts->SetProductionCut(BDSGlobalConstants::Instance()->GetProdCutPhotonsP(),G4ProductionCuts::GetIndex("gamma"));

  if(BDSGlobalConstants::Instance()->GetProdCutElectronsP()>0)
    theProductionCuts->SetProductionCut(BDSGlobalConstants::Instance()->GetProdCutElectronsP(),G4ProductionCuts::GetIndex("e-"));

  if(BDSGlobalConstants::Instance()->GetProdCutPositronsP()>0)
    theProductionCuts->SetProductionCut(BDSGlobalConstants::Instance()->GetProdCutPositronsP(),G4ProductionCuts::GetIndex("e+"));
  
  precisionRegion->SetProductionCuts(theProductionCuts);
#ifndef NOUSERLIMITS
  precisionRegion->SetUserLimits(WorldUserLimits);
#endif

  // place the world
  physiWorld = new G4PVPlacement((G4RotationMatrix*)0, // no rotation
  				 (G4ThreeVector)0,     // at (0,0,0)
                                 logicWorld,	// its logical volume
                                 worldName,	// its name
                                 NULL,		// its mother  volume
                                 false,		// no boolean operation
                                 0,             // copy number
				 BDSGlobalConstants::Instance()->GetCheckOverlaps());// overlap checking

}

void BDSDetectorConstruction::ComponentPlacement(){
  if (verbose || debug) G4cout<<"starting placement procedure "<<G4endl;
  
  // sensitive detectors
  //G4SDManager* SDman = G4SDManager::GetSDMpointer();
  //you only need a single instance of your sensitive detector class
  //attach to as many logical volumes as you want
  //note each new sensitive detector invokes a slow string compare
  //while registering with sd manager. ok if only a few SD types.
  //BDSEnergyCounterSD* ECounter    = new BDSEnergyCounterSD("base_ec");
  //SDman->AddNewDetector(ECounter);

  G4ThreeVector TargetPos;          // position of component
  G4ThreeVector rlast = G4ThreeVector(0.,0.,0.);  // edge of last element coordinates
  G4ThreeVector rtot(0.,0.,0.);     // position of component, often same as TargetPos
  G4ThreeVector localX(1.,0.,0.); 
  G4ThreeVector localY(0.,1.,0.);
  G4ThreeVector localZ(0.,0.,1.);

  for(BDSBeamline::Instance()->first();!BDSBeamline::Instance()->isDone();BDSBeamline::Instance()->next())
    {
      BDSAcceleratorComponent* thecurrentitem = BDSBeamline::Instance()->currentItem();
#ifdef BDSDEBUG
      G4cout << G4endl;
#endif
      G4double angle  = thecurrentitem->GetAngle();
      G4double theta  = thecurrentitem->GetTheta();
      G4double psi    = thecurrentitem->GetPsi();
      G4double tilt   = thecurrentitem->GetTilt();
      G4double phi    = thecurrentitem->GetPhi();
      G4double length = thecurrentitem->GetChordLength();

      if( thecurrentitem->GetType() == "transform3d")
	{
#ifdef BDSDEBUG 
          G4cout<<"transform3d : "<<phi<<" "<<theta<<" "<<psi<<G4endl;
#endif
	  rtot(0) += thecurrentitem->GetXOffset(); 
	  rtot(1) += thecurrentitem->GetYOffset(); 
	  rtot(2) += thecurrentitem->GetZOffset(); 

	  rlast(0) += thecurrentitem->GetXOffset();
	  rlast(1) += thecurrentitem->GetYOffset(); 
	  rlast(2) += thecurrentitem->GetZOffset(); 

	  _globalRotation->rotate(psi,localZ);
	  localX.rotate(psi,localZ);
	  localY.rotate(psi,localZ);

	  _globalRotation->rotate(phi,localY);
	  localX.rotate(phi,localY);
	  localZ.rotate(phi,localY);
	  
	  _globalRotation->rotate(theta,localX);
	  localY.rotate(theta,localX);
	  localZ.rotate(theta,localX);
	  	  	  
	  continue;
	}
      
      // rotation matrix for component placement
      G4RotationMatrix *rotateComponent = new G4RotationMatrix;

      // tilted bends influence reference frame, otherwise just local tilt
      if( fabs(angle) > 1e-12 )
	{
	  _globalRotation->rotate(tilt,localZ);
	  localX.rotate(tilt,localZ);
	  localY.rotate(tilt,localZ);
	}
      else 
	rotateComponent->rotateZ(tilt);
    
      // define center of bended elements from the previous coordinate frame
      G4ThreeVector zHalfAngle = localZ; 

      if( fabs(angle) > 1e-12 ) 
	{zHalfAngle.rotate(angle/2,localY);}

#ifdef BDSDEBUG
      G4cout << "zHalfAngle = " << zHalfAngle <<G4endl;
      G4cout << "localZ     = " << localZ     <<G4endl;
      G4cout << "localX     = " << localX     <<G4endl;
      G4cout << "localY     = " << localY     <<G4endl;
      G4cout << "rlast      = " << rlast      <<G4endl;
      G4cout << "rtot       = " << rtot       <<G4endl;
#endif
      
      // target position
      TargetPos = rlast + zHalfAngle *  ( length/2 + BDSGlobalConstants::Instance()->GetLengthSafety()/2 );
#ifdef BDSDEBUG 
      G4cout<<"TargetPos  = "<<TargetPos<<G4endl;
#endif

      // advance the coordinates, but not for cylindrical samplers
      //think this should be > samplerlength
      if( ( ( thecurrentitem->GetType() != "csampler") || ( length <= BDSGlobalConstants::Instance()->GetSamplerLength() ) )  && ( thecurrentitem->GetType()!="element" ))
	{
#ifdef BDSDEBUG 
          G4cout << thecurrentitem->GetType() << " "
                 << thecurrentitem->GetName() << " "
                 << G4endl;
#endif
	  rtot = rlast + zHalfAngle * length/2;
	  rlast = rtot + zHalfAngle * length/2;
	}

      // rotate to the previous reference frame
      rotateComponent->transform(*_globalRotation);
      rotateComponent->invert();

      // recompute global rotation
      // define new coordinate system local frame	  
 
      // bends transform the coordinate system
      if( thecurrentitem->GetType() == "sbend" || thecurrentitem->GetType() == "rbend") {
	_globalRotation->rotate(angle,localY);
	localX.rotate(angle,localY);
	localZ.rotate(angle,localY);
	
	_globalRotation->rotate(theta,localX);
	localY.rotate(theta,localX);
	localZ.rotate(theta,localX);
	
	// bend trapezoids defined along z-axis
	rotateComponent->rotateY(-angle/2.0);
      } else if (thecurrentitem->GetMarkerLogicalVolume()->GetSolid()->GetName().contains("trapezoid") ) {
	rotateComponent->rotateY(-CLHEP::twopi/4); //Drift trapezoids defined along z axis 
      }
      
      // zero length components not placed (transform3d)
      if(length<=0.) {
	delete rotateComponent;
	continue;
      }

      // set visualisation attributes
      G4LogicalVolume* LocalLogVol = thecurrentitem->GetMarkerLogicalVolume();
      G4String LogVolName          = LocalLogVol->GetName();
      
      // add the volume to one of the regions
      if(thecurrentitem->GetPrecisionRegion())
	{
#ifdef BDSDEBUG
	  G4cout<<"ELEMENT IS IN PRECISION REGION: "<<thecurrentitem->GetPrecisionRegion()<< G4endl;
#endif
	  LocalLogVol->SetRegion(precisionRegion);
	  precisionRegion->AddRootLogicalVolume(LocalLogVol);
	}
      
#ifdef BDSDEBUG
      G4cout<<"SETTING UP SENSITIVE VOLUMES..."<< G4endl;
#endif

      // register all logical volumes with sposition and any other information for later use
      std::vector<G4LogicalVolume*> allLVs = thecurrentitem->GetAllLogicalVolumes();
      std::vector<G4LogicalVolume*>::iterator allLVsIterator = allLVs.begin();
      for(;allLVsIterator != allLVs.end(); ++allLVsIterator)
	{
	  BDSGlobalConstants::Instance()->AddLogicalVolumeInfo(*allLVsIterator,
							       new BDSLogicalVolumeInfo((*allLVsIterator)->GetName(),
											thecurrentitem->GetSPos())
							       );
	}

      // old way of setting sensitive volumes - remains for now for components that haven't been changed
      /*
      std::vector<G4LogicalVolume*> SensVols = thecurrentitem->GetSensitiveVolumes();
      for(G4int i=0; i<(G4int)SensVols.size(); i++)
	{
	  //use already defined instance of Ecounter sd
	  //SensVols[i]->SetSensitiveDetector(ECounter);
	  SensVols[i]->SetSensitiveDetector(BDSSDManager::Instance()->GetEnergyCounterOnAxisSD());
	  //register any volume that an ECounter is attached to
	  BDSLogicalVolumeInfo* theinfo = new BDSLogicalVolumeInfo( SensVols[i]->GetName(),
								    thecurrentitem->GetSPos() );
	  BDSGlobalConstants::Instance()->AddLogicalVolumeInfo(SensVols[i],theinfo);
	  //G4cout << "sensvols["<<i<<"] - name : "<<SensVols[i]->GetName() << G4endl;
		
	  if(gflash && 
	     SensVols[i]->GetRegion() != precisionRegion && 
	     (thecurrentitem->GetType()=="element")) {//If not in the precision region....
	    //		    if(SensVols[i]->GetMaterial()->GetState()!=kStateGas){ //If the region material state is not gas, associate with a parameterisation
#ifdef BDSDEBUG
	    G4cout << "...adding " << SensVols[i]->GetName() << " to gFlashRegion" << G4endl;
#endif
	    // Initialise shower model
	    G4String rname = "gFlashRegion_" + SensVols[i]->GetName();
	    gFlashRegion.push_back(new G4Region(rname.c_str()));
	    G4String mname = "fastShowerModel" + rname;
#ifdef BDSDEBUG
	    G4cout << "...making parameterisation..." << G4endl;
#endif
	    theFastShowerModel.push_back(new BDSShowerModel(mname.c_str(),gFlashRegion.back()));
	    theParameterisation.push_back(new GFlashHomoShowerParameterisation(BDSMaterials::Instance()->GetMaterial(SensVols[i]->GetMaterial()->GetName().c_str()))); 
	    theFastShowerModel.back()->SetParameterisation(*theParameterisation.back());
	    theFastShowerModel.back()->SetParticleBounds(*theParticleBounds) ;
	    theFastShowerModel.back()->SetHitMaker(*theHitMaker);
	    if(SensVols[i]->GetMaterial()->GetState()!=kStateGas){ //If the region material state is not gas, associate with a parameterisation
	      theFastShowerModel.back()->SetFlagParamType(1);//Turn on the parameterisation for e-m showers starting in sensitive material and fitting in the current stack.
	      theFastShowerModel.back()->SetFlagParticleContainment(1);//Turn on containment
	    } else {
	      theFastShowerModel.back()->SetFlagParamType(0);//Turn on the parameterisation for e-m showers starting in sensitive material and fitting in the current stack.
	      theFastShowerModel.back()->SetFlagParticleContainment(0);//Turn on containment
		  
	    }
	    SensVols[i]->SetRegion(gFlashRegion.back());
	    gFlashRegion.back()->AddRootLogicalVolume(SensVols[i]);
	    //		    gFlashRegion.back()->SetUserLimits(new G4UserLimits(thecurrentitem->GetChordLength()/10.0));
	    //		    SensVols[i]->SetUserLimits(new G4UserLimits(thecurrentitem->GetChordLength()/10.0));
	  }		  
	}
      */
#ifdef BDSDEBUG
      G4cout<<"ALIGNING COMPONENT..."<< G4endl;
#endif	
      // Align Component - most cases does nothing. 
      // Currently only used for BDSElement	
      /*
      thecurrentitem->AlignComponent(//TargetPos,
				     rlast,
				     rotateComponent,
				     *_globalRotation,
				     rtot,
				     rlast,
				     localX,
				     localY,
				     localZ);
      */

#ifdef BDSDEBUG
      G4cout << "Placing PHYSICAL COMPONENT..."<< G4endl;
      G4cout << "BDSDetectorConstruction : rotateComponent = " << *rotateComponent << G4endl;
      G4cout << "BDSDetectorConstruction : TargetPos        = " << TargetPos << G4endl;
#endif	

      G4String LocalName=thecurrentitem->GetName()+"_phys";
      const int nCopy = thecurrentitem->GetCopyNumber();
      
      G4PVPlacement* PhysiComponentPlace = 
	new G4PVPlacement(
			  rotateComponent,  // its rotation
			  TargetPos,        // its position
			  LocalName,	      // its name
			  LocalLogVol,      // its logical volume
			  physiWorld,	      // its mother  volume
			  false,	      // no boolean operation
			  nCopy,            // copy number
			  BDSGlobalConstants::Instance()->GetCheckOverlaps());//overlap checking

      //this vector of physical volumes isn't used anywhere...
      fPhysicalVolumeVector.push_back(PhysiComponentPlace);
      std::vector<G4VPhysicalVolume*> MultiplePhysicalVolumes = thecurrentitem->GetMultiplePhysicalVolumes();
      for (unsigned int i=0;i<MultiplePhysicalVolumes.size(); i++) fPhysicalVolumeVector.push_back(MultiplePhysicalVolumes.at(i));
					    
#ifdef BDSDEBUG 
      G4cout << "Volume name: " << LocalName << G4endl;
#endif
      if(BDSGlobalConstants::Instance()->GetRefVolume()+"_phys"==LocalName && 
	 BDSGlobalConstants::Instance()->GetRefCopyNo()==nCopy){
#ifdef BDSDEBUG 
	G4cout << "Setting new transform" <<G4endl;
#endif
	G4AffineTransform tf(*_globalRotation,TargetPos-G4ThreeVector(0,0,length/2));
	BDSGlobalConstants::Instance()->SetRefTransform(tf);
      }

      //this does nothing by default - only used by BDSElement
      //looks like it could just be done in its construction rather than
      //in BDSDetectorConstruction
      thecurrentitem->PrepareField(PhysiComponentPlace);
    }
}

void BDSDetectorConstruction::BuildTunnel(){
  std::list<struct Element>::iterator it;
  for(it = beamline_list.begin();it!=beamline_list.end();it++)
    {
      if((*it).type==_TUNNEL ) {
#ifdef BDSDEBUG
	G4cout<<"BUILDING TUNNEL : "<<(*it).l<<"  "<<(*it).name<<G4endl;
#endif
	
	G4String gFormat="",  GFile="";
	G4String geometry = (*it).geometryFile;

	// get geometry format and file
	G4int pos = geometry.find(":");
	
	if(pos<0) { 
	  G4cerr<<"WARNING: invalid geometry reference format : "<<geometry<<G4endl;
	  gFormat="none";
	}
	
	else {
	  gFormat = geometry.substr(0,pos);
	  GFile = geometry.substr(pos+1,geometry.length() - pos); 
	}
	
#ifdef BDSDEBUG
	G4cout<<"placing components\n: geometry format - "<<gFormat<<G4endl<<
	  "file - "<<GFile<<G4endl;
#endif
	
	if(gFormat=="gmad") {
	 
	  GGmadDriver ggmad(GFile);
	  ggmad.Construct(logicWorld);
	  
	} else  G4cerr<<"Tunnel won't be build! "<<G4endl;
      }
    }
}
