#ifndef  BDSTransportationManager_hh
#define  BDSTransportationManager_hh

#include "G4Navigator.hh"

class G4PropagatorInField;
class G4GeometryMessenger;
class G4FieldManager;

class BDSTransportationManager 
{
  public:  // with description



     ~BDSTransportationManager(); 

  protected:

     BDSTransportationManager(); 
    
  private:

     G4Navigator*            fNavigatorForTracking ;
     G4PropagatorInField*    fPropagatorInField;
     G4FieldManager*         fFieldManager;
     G4GeometryMessenger*    fGeomMessenger;

     static BDSTransportationManager*  fTransportationManager;
};

#endif 
