/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSAcceleratorComponent_h
#define BDSAcceleratorComponent_h 1

#include <string>
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"
#include "BDSBeamPipe.hh"
#include "BDSEnergyCounterSD.hh"

#include "G4MagneticField.hh"
#include "G4Mag_EqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4FieldManager.hh"
#include "G4UserLimits.hh"
 
class BDSAcceleratorComponent 
{
public:
  virtual ~BDSAcceleratorComponent ();

  //	Returns the geometry length of the component.
  const G4double GetLength () const;
  void SetLength(G4double aLength);
  const G4String GetName () const;
  void SetName(G4String aName);
  const G4double GetAngle () const;
  G4LogicalVolume* GetMarkerLogicalVolume() const;
  BDSEnergyCounterSD* GetBDSEnergyCounter() const;
  void SetBDSEnergyCounter( BDSEnergyCounterSD* anBDSEnergyCounter);
  G4int GetCopyNumber() const;
  G4double GetSPos() const;
  void SetSPos(G4double spos);
  void SetCopyNumber(G4int nCopy);
  void SetBDSEnergyCounterID(G4int anID);
  G4int GetBDSEnergyCounterID();
  void SetSensitiveVolume(G4LogicalVolume* aLogVol);
  G4LogicalVolume* GetSensitiveVolume();

  G4UserLimits* GetInnerBPUserLimits();

  G4double GetZLower();
  G4double GetZUpper();
  void SetZLower(G4double aZLower);
  void SetZUpper(G4double aZUpper);
  void AddSynchEnergyLoss(G4double SynchEnergyLoss);
  G4double GetSynchEnergyLoss();
  
  BDSAcceleratorComponent();
  void BuildOuterFieldManager();

  BDSAcceleratorComponent (
			  G4String& aName, 
			  G4double aLength,
			  G4double aBpRadius,
			  G4double aXAper,
			  G4double aYAper,
			  G4VisAttributes* aVisAtt,
			  G4double angle=0.);


  G4VisAttributes* GetVisAttributes()const;
  G4LogicalVolume* itsOuterLogicalVolume;
  G4LogicalVolume* itsMarkerLogicalVolume;

protected:
  G4String itsName;
  G4double itsLength;
  G4double itsBpRadius;
  G4double itsXAper;
  G4double itsYAper;
  G4double itsAngle;
  BDSBeamPipe* itsBeamPipe;
  G4MagneticField* itsOuterMagField;
  G4Mag_EqRhs* itsOuterEqRhs;
  G4MagIntegratorStepper*  itsOuterStepper;
  G4ChordFinder* itsOuterChordFinder;
  G4FieldManager*  itsOuterFieldMgr;
  G4VisAttributes* itsVisAttributes;
  G4UserLimits* itsOuterUserLimits;
  G4UserLimits* itsMarkerUserLimits;
  G4UserLimits* itsInnerBeampipeUserLimits;


private:
  G4double itsSPos;
  G4int itsCopyNumber;
  BDSEnergyCounterSD* itsBDSEnergyCounter;
  G4int itsCollectionID;
  G4LogicalVolume* itsSensitiveVolume;
  G4double itsZLower;
  G4double itsZUpper;
  G4double itsSynchEnergyLoss;

};

// Class BDSAcceleratorComponent 

inline BDSAcceleratorComponent::
BDSAcceleratorComponent (
			G4String& aName,G4double aLength, 
			G4double aBpRadius,G4double aXAper,G4double aYAper, 
			G4VisAttributes* aVisAtt,G4double angle  ): 
  itsName(aName),itsLength(aLength),itsBpRadius(aBpRadius),
  itsXAper(aXAper),itsYAper(aYAper),
  itsVisAttributes(aVisAtt),itsAngle(angle)
{itsSensitiveVolume=NULL;
 itsInnerBeampipeUserLimits =new G4UserLimits();
};


inline const G4double BDSAcceleratorComponent::GetLength () const
{return itsLength;}

inline const G4double BDSAcceleratorComponent::GetAngle () const
{return itsAngle;}

inline const G4String BDSAcceleratorComponent::GetName () const
{return itsName;}

inline void BDSAcceleratorComponent::SetName (G4String aName)
{itsName=aName;}

inline G4LogicalVolume* BDSAcceleratorComponent::GetMarkerLogicalVolume() const
{return itsMarkerLogicalVolume;}

inline G4VisAttributes* BDSAcceleratorComponent::GetVisAttributes() const
{return itsVisAttributes;}

inline BDSEnergyCounterSD* BDSAcceleratorComponent::GetBDSEnergyCounter() const
{return itsBDSEnergyCounter;}

inline G4int BDSAcceleratorComponent::GetCopyNumber() const
{return itsCopyNumber;}

inline G4double BDSAcceleratorComponent::GetSPos() const
{return itsSPos;}

inline void BDSAcceleratorComponent::SetCopyNumber(G4int nCopy)
{itsCopyNumber=nCopy;}

inline void BDSAcceleratorComponent::SetSPos(G4double spos)
{itsSPos=spos;}

inline void 
BDSAcceleratorComponent::SetBDSEnergyCounter(BDSEnergyCounterSD* anBDSEnergyCounter)
{itsBDSEnergyCounter=anBDSEnergyCounter;}

inline void BDSAcceleratorComponent::SetBDSEnergyCounterID(G4int anID)
{itsCollectionID=anID;}

inline G4int BDSAcceleratorComponent::GetBDSEnergyCounterID()
{return itsCollectionID;}

inline  
void BDSAcceleratorComponent::SetSensitiveVolume(G4LogicalVolume* aLogVol)
{itsSensitiveVolume=aLogVol;}

inline  G4LogicalVolume* BDSAcceleratorComponent::GetSensitiveVolume()
{return itsSensitiveVolume;}

inline  G4double BDSAcceleratorComponent::GetZLower()
{return itsZLower;}

inline  G4double BDSAcceleratorComponent::GetZUpper()
{return itsZUpper;}

inline  void BDSAcceleratorComponent::SetZLower(G4double aZLower)
{itsZLower=aZLower;}

inline  void BDSAcceleratorComponent::SetZUpper(G4double aZUpper)
{itsZUpper=aZUpper;}

inline void 
BDSAcceleratorComponent::AddSynchEnergyLoss(G4double SynchEnergyLoss)
{itsSynchEnergyLoss+=SynchEnergyLoss;}

inline  G4double BDSAcceleratorComponent::GetSynchEnergyLoss()
{return itsSynchEnergyLoss;}

inline  G4UserLimits* BDSAcceleratorComponent::GetInnerBPUserLimits()
  {return itsInnerBeampipeUserLimits;}
#endif



