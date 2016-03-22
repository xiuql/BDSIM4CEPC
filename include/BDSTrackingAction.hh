#ifndef BDSTRACKINGACTION_H
#define BDSTRACKINGACTION_H

#include "globals.hh" // geant4 types / globals
#include "G4Track.hh"
#include "G4UserTrackingAction.hh"

/**
 * @brief Action to decide whether or not to store trajectory information.
 *
 */

class BDSTrackingAction: public G4UserTrackingAction
{
public:
  BDSTrackingAction();
  BDSTrackingAction(G4bool batchMode);
  
  virtual ~BDSTrackingAction(){;}
   
  virtual void PreUserTrackingAction(const G4Track* track);

private:
  /// Whether we're using the visualiser - in which case always store
  /// trajectories for visualisation.
  G4bool interactive;
};

#endif
