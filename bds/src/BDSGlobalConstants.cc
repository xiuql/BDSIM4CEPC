/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#include "BDSGlobalConstants.hh"

#include "G4UniformMagField.hh"

#include <cstdlib>

#include<string>
#include<stack>

/* IA: */ #include <assert.h> 

using namespace std;

G4double NumSpoilerRadLen=1.;

namespace 
{

	// stack used to match MAD LINE pairs
	// Note: we need this because we no longer preserve the 
        // complete MAD beamline
	// structure.
  stack<G4String> frameStack;

	// utility routines for reading in MAD optics file
	
 void Log(const G4String& tag, int depth, ostream& os)
{
  static const char* tab = "----|";
  while(depth--) os<<tab;
  os<<' '<<tag<<endl;
}

void BDSGlobalConstants::StripHeader(istream& is)
{
  // Need to read the first 2 lines from the cards file
  char buffer[256];
  for(int i=0; i<2; i++)
    is.getline(buffer,256);
}


BDSGlobalConstants::BDSGlobalConstants (const G4String& CardsFileName)
  : ifs(CardsFileName.c_str()),log(&cout)
{
  assert(ifs);
  //  ofstream GlobalFilelog("construction.log");
  
  // reset the stream pointer
  ifs.seekg(0);
  G4String accelerator,bunch_type;

  // defaults:
  itsEnergyOffset=0.;
  itsVerboseEventNumber=0;
  itsTrackWeightFactor=1.0;

  itsOutputNtupleFileName="sampler_output.rz";
  // end of defaults

  while(ifs) ReadCard(accelerator, bunch_type);

  itsAccelerator=  new BDSAcceleratorType(accelerator,bunch_type);

  // default value (can be renamed later)

  G4UniformMagField* magField = new G4UniformMagField(G4ThreeVector());
  itsZeroFieldManager=new G4FieldManager();
  itsZeroFieldManager->SetDetectorField(magField);
  itsZeroFieldManager->CreateChordFinder(magField);
  
}


G4int BDSGlobalConstants::ReadCard (G4String& accelerator, 
				    G4String& bunch_type)
{
  //#define  _READ(value) if(!(ifs>>value)) return 0;
#define  _READ(value) if(!(ifs>>value))return 0; else G4cout<<value<<G4endl;
  
  G4String name;
  _READ(name);
  
  if(name=="*"){// This is a comment line  
    char buffer[255];
    ifs.getline(buffer,255);
    return 0;   
  }


  if(name=="ACCELERATOR")
    {_READ(accelerator);}
  else if(name=="BUNCH_TYPE")
    {_READ(bunch_type);}
  else if(name=="READ_BUNCH_FILE")
    { _READ(itsReadBunchFile);    }
  else if(name=="EXTRACT_BUNCH_FILE")
    { _READ(itsExtractBunchFile);    }
  else if(name=="WRITE_BUNCH_FILE")
    {
      _READ(itsWriteBunchFile);
    }
  else if(name=="ENERGY_OFFSET")
    { 
      _READ(itsEnergyOffset);    
      itsEnergyOffset*=GeV;
    }
  else if(name=="BACKGROUND_SCALE_FACTOR")
    {_READ(itsBackgroundScaleFactor);}
  else if(name=="ACCELERATOR_COMPONENT_BOX_SIZE")
    {_READ(itsComponentBoxSize);
    itsComponentBoxSize*=cm;
    }
  else if(name=="MAGNET_POLE_SIZE")
    {_READ(itsMagnetPoleSize);
    itsMagnetPoleSize*=cm;
    }
  else if(name=="MAGNET_POLE_RADIUS")
    {_READ(itsMagnetPoleRadius);
    itsMagnetPoleRadius*=cm;
    }
  else if(name=="TUNNEL_RADIUS")
    {_READ(itsTunnelRadius);
    itsTunnelRadius*=m;
    }
  else if(name=="HORIZONTAL_BEAMLINE_OFFSET")
    {_READ(itsHorizontalBeamlineOffset);
    itsHorizontalBeamlineOffset*=m;
    }
  else if(name=="VERTICAL_BEAMLINE_OFFSET")
    {_READ(itsVerticalBeamlineOffset);
    itsVerticalBeamlineOffset*=m;
    }
  else if(name=="BEAMPIPE_RADIUS")
    {_READ(itsBeampipeRadius);
    itsBeampipeRadius*=cm;
    }
  else if(name=="BEAMPIPE_THICKNESS")
    {_READ(itsBeampipeThickness);
    itsBeampipeThickness*=mm;
    }
  else if(name=="THRESHOLD_CUT_CHARGED")
    {_READ(itsThresholdCutCharged);
    itsThresholdCutCharged*=GeV;
    }
  else if(name=="THRESHOLD_CUT_PHOTONS")
    {_READ(itsThresholdCutPhotons);
    itsThresholdCutPhotons*=GeV;
    }
  else if(name=="TRACK_WEIGHT_FACTOR")
    {_READ(itsTrackWeightFactor);
    }
  else if(name=="DELTA_CHORD")
    {_READ(itsDeltaChord);
    itsDeltaChord*=m;
    }
  else if(name=="CHORD_STEP_MINIMUM")
    {_READ(itsChordStepMinimum);
    itsChordStepMinimum*=m;
    }
  else if(name=="DELTA_INTERSECTION")
    {_READ(itsDeltaIntersection);
    itsDeltaIntersection*=m;
    }
  else if(name=="TURN_ON_INTERACTIONS")
    {_READ(itsTurnOnInteractions);
    }
  else if(name=="TURN_ON_SYNCHROTRON")
    {_READ(itsSynchRadOn);}
  else if(name=="RESCALE_DUE_TO_SYNCHROTRON")
    {_READ(itsSynchRescale);}
  else if(name=="TRACK_SYNCHROTRON_PHOTONS")
    {_READ(itsSynchTrackPhotons);}
  else if(name=="SYNCHROTRON_LOWEST_X")
    {_READ(itsSynchLowX);}
  else if(name=="SYNCHROTRON_LOWEST_GAMMA_ENERGY")
    {
      _READ(itsSynchLowGamE);
      itsSynchLowGamE*=MeV;
    }
  else if(name=="TURN_ON_PLANCK")
    {_READ(itsPlanckOn);}
  else if(name=="TURN_ON_BDSeBREM")
    {_READ(itsBDSeBremOn);}
  else if(name=="LASERWIRE_WAVELENGTH")
    {_READ(itsLaserwireWavelength);
    itsLaserwireWavelength*=m;
    }
  else if(name=="LASERWIRE_DIR_X")
    {G4double Dir;
    _READ(Dir);
    itsLaserwireDir.setX(Dir);
    }
  else if(name=="LASERWIRE_DIR_Y")
    {G4double Dir;
    _READ(Dir);
    itsLaserwireDir.setY(Dir);
    }
  else if(name=="LASERWIRE_DIR_Z")
    {G4double Dir;
    _READ(Dir);
    itsLaserwireDir.setZ(Dir);
    }
  else if(name=="LASERWIRE_TRACK_PHOTONS")
    {_READ(itsLaserwireTrackPhotons);}
  else if(name=="LASERWIRE_TRACK_ELECTRONS")
    {_READ(itsLaserwireTrackElectrons);}
  else if(name=="LENGTH_SAFETY")
    {
      _READ(itsLengthSafety);
      itsLengthSafety*=mm;
    }
  else if(name=="VERBOSE_STEP")
    {_READ(itsVerboseStep);}
  else if(name=="VERBOSE_EVENT_NUMBER")
    {_READ(itsVerboseEventNumber);}
  else if(name=="USE_TIMER")
    {
      _READ(itsUseTimer);
      if(itsUseTimer) itsTimer=new G4Timer();
    }
  else if(name=="USE_EM_HADRONIC")
    {
      _READ(itsUseEMHadronic);
    }
  else if(name=="USE_MUON_PAIR_PRODUCTION")
    {
      _READ(itsUseMuonPairProduction);
    }
  else if(name=="MUON_PRODUCTION_SCALE_FACTOR")
    {
      _READ(itsMuonProductionScaleFactor);
    }
  else if(name=="HADRON_INELASTIC_SCALE_FACTOR")
    {
      _READ(itsHadronInelasticScaleFactor);
    }
  else if(name=="STORE_MUON_TRAJECTORIES")
    {
      _READ(itsStoreMuonTrajectories);
    }
  else if(name=="USE_MUON_SHOWERS")
    {
      _READ(itsUseMuonShowers);
    }
  else if(name=="INCLUDE_IRON_MAG_FIELDS")
    {
      _READ(itsIncludeIronMagFields);
    }
  else if(name=="INNER_HALO_X")
    {_READ(itsInnerHaloX);}
  else if(name=="OUTER_HALO_X")
    {_READ(itsOuterHaloX);}
  else if(name=="INNER_HALO_Y")
    {_READ(itsInnerHaloY);}
  else if(name=="OUTER_HALO_Y")
    {_READ(itsOuterHaloY);}
  else if(name=="USE_HALO_RADIUS")
    {_READ(itsUseHaloRadius);}
  else if(name=="HALO_INNER_RADIUS")
    {_READ(itsHaloInnerRadius);}
  else if(name=="HALO_OUTER_RADIUS")
    {_READ(itsHaloOuterRadius);}
  else if(name=="USE_BATCH")
    {_READ(itsUseBatch);}
  else if(name=="NUMBER_TO_GENERATE")
    {_READ(itsNumberToGenerate);}
  else if(name=="RANDOM_SEED")
    {_READ(itsRandomSeed);}
  else if(name=="OUTPUT_NTUPLE_FILE_NAME")
    {_READ(itsOutputNtupleFileName);}
  else if(name=="NUMBER_OF_EVENTS_PER_NTUPLE")
    {_READ(itsNumberOfEventsPerNtuple);}
  else if(name=="LW_CAL_WIDTH")
    {_READ(itsLWCalWidth);
      itsLWCalWidth*=cm;
    }
  else if(name=="LW_CAL_OFFSET")
    {_READ(itsLWCalOffset);
      itsLWCalOffset*=cm;
    }
  else if(name=="LW_CAL_MATERIAL")
    {_READ(itsLWCalMaterial);}

  // JCC Addded for Grid Farm multiple job runs 06/07/04
  // ===========================================================
  else if(name=="GRID_FARM_JOB_USE")
    {
      G4bool GridFarmUse;
      _READ(GridFarmUse);
      if(GridFarmUse)
        {
          if(getenv("BDS_FILENAME")!=NULL)
	    {
	      itsOutputNtupleFileName = getenv("BDS_FILENAME");
	    }
          if(getenv("BDS_SEED")!=NULL) itsRandomSeed = atoi(getenv("BDS_SEED"));
        }
    }
  // ===========================================================

  else
    {
      G4cout<<" Unknown card in BDSInput.cards:"<<name<<G4endl;
      G4Exception("BDSGlobalConstants: UNRECOGNISED CARD");
    } 
  return 0;
}

BDSGlobalConstants::~BDSGlobalConstants()
{  
  delete itsAccelerator;
  if(itsTimer)delete itsTimer;
}

}
