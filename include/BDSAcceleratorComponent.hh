//  
//   BDSIM, (C) 2001-2006 
//   
//   version 0.3
//  
//
//
//
//
//   Generic accelerator component class
//
//
//   History
//
//     24 Nov 2006 by Agapov,  v.0.3
//     x  x   2002 by Blair
//
//




#ifndef __BDSACCELERATORCOMPONENT_H
#define __BDSACCELERATORCOMPONENT_H

#include "BDSGlobalConstants.hh" 

#include <cstring>
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"
//#include "BDSBeamPipe.hh"
#include "BDSEnergyCounterSD.hh"

#include "G4MagneticField.hh"
#include "G4Mag_EqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4FieldManager.hh"
#include "G4UserLimits.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"
#include "G4CSGSolid.hh"
#include "G4Tubs.hh"

#include <vector> 

//using namespace std;

class BDSAcceleratorComponent 
{
public:
  //destructor
  virtual ~BDSAcceleratorComponent ();

  //name
  const G4String GetName () const;
  void SetName(G4String aName);

  //type 
  const G4String GetType () const;
  void SetType(G4String aType);

  G4int GetPrecisionRegion() const; //0 = no precision region, 1 = precision region 1, 2 = precision region 2.
  void SetPrecisionRegion(G4int aPrecisionRegion);
  

  //
  //    Geometry features    
  //

  void BuildTunnel();
  void BuildBLMs();
  void BuildGate();

  // angle - for bends etc.
  G4double GetAngle ();

  // geometry length of the component.
  void SetLength(G4double aLength); 
  virtual G4double GetLength ();
  virtual G4double GetZLength ();
  virtual G4double GetXLength ();
  virtual G4double GetYLength ();
  virtual G4double GetArcLength ();

  G4double GetPhiAngleIn (); //polar angle in
  G4double GetPhiAngleOut (); //polar angle out

  G4double GetPhi (); //polar angle with respect to original frame
  void SetPhi (G4double val);

  G4double GetTheta (); //azimuthal angle with respect to original frame
  void SetTheta(G4double val);

  G4double GetPsi (); //azimuthal angle with respect to original frame
  void SetPsi(G4double val);

  G4double GetXOffset();  // frame offset 
  G4double GetYOffset();
  G4double GetZOffset();

  G4double GetTunnelRadius();
  G4double GetTunnelOffsetX();
  
  G4double GetAperX();
  G4double GetAperY();

  G4double GetK1();
  G4double GetK2();
  G4double GetK3();

  //Set is only for Outline readout purposes - doesn't change magnet strengths
  void SetK1(G4double K1);
  void SetK2(G4double K2);
  void SetK3(G4double K3);

  G4RotationMatrix* GetRotation();
  G4ThreeVector GetPosition();
  void SetPosition(G4ThreeVector);
  
  G4double GetTilt();  // component tilt 
  
  
  


  G4LogicalVolume* GetMarkerLogicalVolume() const;

  G4LogicalVolume* GetTunnelLogicalVolume() const;
  
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

  void SetMultipleSensitiveVolumes(G4LogicalVolume* aLogVol);

  std::vector<G4LogicalVolume*> GetMultipleSensitiveVolumes();

  void SetGFlashVolumes(G4LogicalVolume* aLogVol);

  std::vector<G4LogicalVolume*> GetGFlashVolumes();

  void SetMultiplePhysicalVolumes(G4VPhysicalVolume* aPhysVol);

  std::vector<G4VPhysicalVolume*> GetMultiplePhysicalVolumes();

  void SetInnerMostLogicalVolume(G4LogicalVolume* aLogVol);
  
  G4LogicalVolume* GetInnerMostLogicalVolume() const;
  
  G4UserLimits* GetInnerBPUserLimits();
  G4UserLimits* GetUserLimits();

  G4double GetZLower();
  G4double GetZUpper();
  void SetZLower(G4double aZLower);
  void SetZUpper(G4double aZUpper);
  void AddSynchEnergyLoss(G4double SynchEnergyLoss);
  G4double GetSynchEnergyLoss();
  
  BDSAcceleratorComponent();
  void BuildOuterFieldManager();

  // in case a mapped field is provided creates a field mesh in global coordinates
  virtual void PrepareField(G4VPhysicalVolume *referenceVolume); 
  virtual void SynchRescale(G4double factor); 

  // in case a component requires specific alignment (e.g. SQL/BDSElement)
  virtual void AlignComponent(G4ThreeVector& TargetPos, 
			      G4RotationMatrix *TargetRot,
			      G4RotationMatrix& globalRotation,
			      G4ThreeVector& rtot,
			      G4ThreeVector& rlast,
			      G4ThreeVector& localX,
			      G4ThreeVector& localY,
			      G4ThreeVector& localZ); 

  
  // get parameter value from the specification string

  G4double getParameterValue(G4String spec, G4String name) const;
  G4String getParameterValueString(G4String spec, G4String name) const;

  // constructor
  BDSAcceleratorComponent (
			  G4String& aName, 
			  G4double aLength,
			  G4double aBpRadius,
			  G4double aXAper,
			  G4double aYAper,
                          G4VisAttributes* aVisAtt,
                          std::list<G4double> blmLocZ, std::list<G4double> blmLocTheta,
                          G4String aTunnelMaterial = "",
			  G4String aMaterial = "",
			  G4double phi=0.,  // polar angle (used in hor. bends)
                          //G4double theta=0.,
			  G4double XOffset=0.,
			  G4double YOffset=0.,
			  G4double ZOffset=0.,
			  G4double tunnelRadius=0.,
			  G4double tunnelOffsetX=BDSGlobalConstants::Instance()->GetTunnelOffsetX(),
                          G4String aTunnelCavityMaterial = "Air",
			  G4int aPrecisionRegion=0
);

  BDSAcceleratorComponent (
			  G4String& aName, 
			  G4double aLength,
			  G4double aBpRadius,
			  G4double aXAper,
			  G4double aYAper,
                          G4VisAttributes* aVisAtt,
                          G4String aTunnelMaterial = "",
			  G4String aMaterial = "",
			  G4double phi=0.,  // polar angle (used in hor. bends)
			  G4double XOffset=0.,
			  G4double YOffset=0.,
			  G4double ZOffset=0.,
			  G4double tunnelRadius=0.,
			  G4double tunnelOffsetX=BDSGlobalConstants::Instance()->GetTunnelOffsetX(),
			  G4String aTunnelCavityMaterial = "Air",
			  G4int aPrecisionRegion=0);



  G4VisAttributes* GetVisAttributes()const;
  G4LogicalVolume* itsOuterLogicalVolume;
  G4LogicalVolume* itsMarkerLogicalVolume;
  G4LogicalVolume* itsTunnelLogicalVolume;
  G4LogicalVolume* itsTunnelFloorLogicalVolume;


protected:

  //Calculate dimensions used for the marker volume etc.
  void CalculateLengths();


  //Values related to BLM placement and geometry
  G4double itsBlmLocationR;
  G4double itsBlmRadius;

  G4String itsName;
  G4double itsLength;
  G4double itsXLength;
  G4double itsYLength;
  G4double itsOuterR;
  G4double itsBpRadius;
  G4double itsXAper;
  G4double itsYAper;
  G4double itsAngle;
  G4String itsMaterial;
  G4VisAttributes* itsVisAttributes;
  std::list<G4double> itsBlmLocZ;
  std::list<G4double> itsBlmLocTheta;
  G4String itsTunnelMaterial;
  //Tunnel geom
  G4double itsXOffset;
  G4double itsYOffset;
  G4double itsZOffset;
  G4double itsTunnelRadius;
  G4double itsTunnelOffsetX;  

  G4String itsType;

  G4double itsTilt;

  G4double itsPhiAngleIn;
  G4double itsPhiAngleOut;
  
  G4double itsMagScaleFactor;
  G4double itsPhi;
  G4double itsTheta;
  G4double itsPsi;
  G4double itsK1, itsK2, itsK3;
  G4RotationMatrix* itsRotation;
  G4ThreeVector itsPosition;
  //  BDSBeamPipe* itsBeamPipe;
  G4Mag_EqRhs* itsOuterEqRhs;
  G4MagIntegratorStepper*  itsOuterStepper;
  G4UserLimits* itsOuterUserLimits;
  G4UserLimits* itsMarkerUserLimits;
  G4UserLimits* itsInnerBeampipeUserLimits;
  G4LogicalVolume* itsInnerMostLogicalVolume;

  G4String itsTunnelCavityMaterial;
  G4int itsPrecisionRegion;

  //Marker solid
  G4VSolid* itsMarkerSolidVolume;

  //Solid shapes used in building tunnel
  G4VSolid* itsTunnelSolid;
  G4VSolid* itsSoilSolid;
  G4VSolid* itsInnerTunnelSolid;
  G4VSolid *itsTunnelCavity;
  G4VSolid *itsLargerTunnelCavity;
  G4VSolid *itsTunnelFloor;
  G4VSolid* itsLargerInnerTunnelSolid; 
  G4VSolid *itsTunnelMinusCavity;
  G4CSGSolid* itsTunnelSizedBlock;

  //BLM logical volumes
  G4LogicalVolume* itsBLMLogicalVolume;
  G4LogicalVolume* itsBlmCaseLogicalVolume;
  //BLM physical volumes
  std::vector<G4VPhysicalVolume*> itsBLMPhysiComp;
  //Tunnel logical volumes
  G4LogicalVolume* itsSoilTunnelLogicalVolume;
  G4LogicalVolume* itsTunnelCavityLogicalVolume;
  G4LogicalVolume*  itsTunnelMinusCavityLogicalVolume;
  //Tunnel physical volumes
  G4VPhysicalVolume* itsTunnelPhysiInner;
  G4VPhysicalVolume* itsTunnelPhysiComp;
  G4VPhysicalVolume* itsTunnelFloorPhysiComp;
  G4VPhysicalVolume* itsTunnelPhysiCompSoil;
  //Tunnel user limits
  G4UserLimits* itsTunnelUserLimits;
  G4UserLimits* itsSoilTunnelUserLimits;
  G4UserLimits* itsInnerTunnelUserLimits;






private:
  /// constructor initialisation
  void ConstructorInit();

  G4RotationMatrix* nullRotationMatrix;
  G4RotationMatrix* tunnelRot;
  G4RotationMatrix* gateRot;
  G4Material* gateMaterial;
  G4VisAttributes* VisAtt;
  G4VisAttributes* VisAtt1;
  G4VisAttributes* VisAtt2;
  G4VisAttributes* VisAtt3;
  G4VisAttributes* VisAtt4;
  G4VisAttributes* VisAtt5;
  G4Tubs* itsBLMSolid;
  G4Tubs* itsBlmOuterSolid;
  G4double itsSPos;
  G4int itsCopyNumber;
  BDSEnergyCounterSD* itsBDSEnergyCounter;
  G4int itsCollectionID;
  G4LogicalVolume* itsSensitiveVolume;
  std::vector<G4LogicalVolume*> itsMultipleSensitiveVolumes;
  std::vector<G4LogicalVolume*> itsGFlashVolumes;
  //A vector containing the physical volumes in the accelerator component- to be used for geometric importance sampling etc.
  std::vector<G4VPhysicalVolume*> itsMultiplePhysicalVolumes;
  G4double itsZLower;
  G4double itsZUpper;
  G4double itsSynchEnergyLoss;

};

// Class BDSAcceleratorComponent 



inline BDSAcceleratorComponent::BDSAcceleratorComponent (
			G4String& aName,G4double aLength, 
			G4double aBpRadius,G4double aXAper,G4double aYAper, 
			G4VisAttributes* aVisAtt,
                        G4String aTunnelMaterial,
                        G4String aMaterial,G4double angle,
			G4double XOffset, G4double YOffset,G4double ZOffset, G4double tunnelRadius, G4double tunnelOffsetX,G4String aTunnelCavityMaterial, G4int aPrecisionRegion):
  itsName(aName),itsLength(aLength),itsBpRadius(aBpRadius),
  itsXAper(aXAper),itsYAper(aYAper),itsAngle(angle),
  itsMaterial(aMaterial),itsVisAttributes(aVisAtt),itsTunnelMaterial(aTunnelMaterial),
  itsXOffset(XOffset),itsYOffset(YOffset), itsZOffset(ZOffset), itsTunnelRadius(tunnelRadius), itsTunnelOffsetX(tunnelOffsetX),itsTunnelCavityMaterial(aTunnelCavityMaterial), itsPrecisionRegion(aPrecisionRegion)
{
  ConstructorInit();
}

inline BDSAcceleratorComponent::BDSAcceleratorComponent (
			G4String& aName,G4double aLength, 
			G4double aBpRadius,G4double aXAper,G4double aYAper, 
			G4VisAttributes* aVisAtt,
			std::list<G4double> blmLocZ, std::list<G4double> blmLocTheta,
                        G4String aTunnelMaterial,
                        G4String aMaterial,G4double angle,
			G4double XOffset, G4double YOffset,G4double ZOffset, G4double tunnelRadius, G4double tunnelOffsetX, G4String aTunnelCavityMaterial, G4int aPrecisionRegion):
  itsName(aName),itsLength(aLength),itsBpRadius(aBpRadius),
  itsXAper(aXAper),itsYAper(aYAper),itsAngle(angle),
  itsMaterial(aMaterial),itsVisAttributes(aVisAtt), itsBlmLocZ(blmLocZ), itsBlmLocTheta(blmLocTheta),
  itsTunnelMaterial(aTunnelMaterial),
  itsXOffset(XOffset),itsYOffset(YOffset), itsZOffset(ZOffset), itsTunnelRadius(tunnelRadius), itsTunnelOffsetX(tunnelOffsetX), itsTunnelCavityMaterial(aTunnelCavityMaterial), itsPrecisionRegion(aPrecisionRegion)
{
  if (itsBlmLocZ.size() != itsBlmLocTheta.size()){
    G4cerr << "BDSAcceleratorComponent: error, lists blmLocZ and blmLocTheta are of unequal size" << G4endl;
    G4cerr << "blmLocZ.size() = " << blmLocZ.size() << G4endl;
    G4cerr << "blmLocTheta.size() = " << blmLocTheta.size() << G4endl;
    exit(1);
  }
  ConstructorInit();
}

inline void BDSAcceleratorComponent::ConstructorInit(){
  itsInnerBeampipeUserLimits =new G4UserLimits();
  itsPhi = 0;
  itsTheta = 0;
  itsPsi = 0;
  itsTilt = 0;
  itsOuterR=0;
  itsMagScaleFactor = 1;
  itsBlmLocationR=0;
  if (itsTunnelRadius<=BDSGlobalConstants::Instance()->GetLengthSafety()){
    itsTunnelRadius=BDSGlobalConstants::Instance()->GetTunnelRadius();
  }
  CalculateLengths();
  itsOuterLogicalVolume=NULL;
  itsMarkerLogicalVolume=NULL;
  itsTunnelLogicalVolume=NULL;
  itsTunnelFloorLogicalVolume=NULL;
  itsRotation=NULL;
  itsOuterStepper=NULL;
  itsOuterUserLimits=NULL;
  itsMarkerUserLimits=NULL;
  itsInnerBeampipeUserLimits=NULL;
  itsInnerMostLogicalVolume=NULL;
  itsMarkerSolidVolume=NULL;
  itsTunnelSolid=NULL;
  itsSoilSolid=NULL;
  itsInnerTunnelSolid=NULL;
  itsTunnelCavity=NULL;
  itsLargerTunnelCavity=NULL;
  itsTunnelFloor=NULL;
  itsLargerInnerTunnelSolid=NULL;
  itsTunnelMinusCavity=NULL;
  itsTunnelSizedBlock=NULL;
  itsBLMLogicalVolume=NULL;
  itsBlmCaseLogicalVolume=NULL;
  itsSoilTunnelLogicalVolume=NULL;
  itsTunnelCavityLogicalVolume=NULL;
  itsTunnelMinusCavityLogicalVolume=NULL;
  itsTunnelPhysiInner=NULL;
  itsTunnelPhysiComp=NULL;
  itsTunnelFloorPhysiComp=NULL;
  itsTunnelPhysiCompSoil=NULL;
  itsTunnelUserLimits=NULL;
  itsSoilTunnelUserLimits=NULL;
  itsInnerTunnelUserLimits=NULL;

  nullRotationMatrix=NULL;
  tunnelRot=NULL;
  gateRot=NULL;
  gateMaterial=NULL;
  VisAtt=NULL;
  VisAtt1=NULL;
  VisAtt2=NULL;
  VisAtt3=NULL;
  VisAtt4=NULL;
  VisAtt5=NULL;
  itsBLMSolid=NULL;
  itsBlmOuterSolid=NULL;
  itsBDSEnergyCounter=NULL;
  itsSensitiveVolume=NULL;  
}

inline G4double BDSAcceleratorComponent::GetLength ()
{return itsLength;}

inline G4double BDSAcceleratorComponent::GetXLength ()
{return itsXLength;}

inline G4double BDSAcceleratorComponent::GetYLength ()
{return itsYLength;}

inline G4double BDSAcceleratorComponent::GetArcLength ()
{return itsLength;}

inline G4double BDSAcceleratorComponent::GetZLength ()
{return itsLength;}

inline G4double BDSAcceleratorComponent::GetAngle ()
{return itsAngle;}

inline G4double BDSAcceleratorComponent::GetPhiAngleIn ()
{return itsPhiAngleIn;}

inline G4double BDSAcceleratorComponent::GetPhiAngleOut ()
{return itsPhiAngleOut;}

inline G4double BDSAcceleratorComponent::GetPhi ()
{return itsPhi;}

inline void BDSAcceleratorComponent::SetPhi (G4double val)
{itsPhi = val;}

inline G4double BDSAcceleratorComponent::GetTheta ()
{return itsTheta;}

inline void BDSAcceleratorComponent::SetTheta (G4double val)
{itsTheta = val;}

inline G4double BDSAcceleratorComponent::GetPsi ()
{return itsPsi;}

inline void BDSAcceleratorComponent::SetPsi (G4double val)
{itsPsi = val;}

inline G4double BDSAcceleratorComponent::GetAperX()
{
  if(itsXAper==0) // i.e. it has not been set
    return itsBpRadius;
  else return itsXAper;
}

inline G4double BDSAcceleratorComponent::GetAperY()
{
  if(itsYAper==0) // i.e. it has not been set
    return itsBpRadius;
  else return itsYAper;
}

inline G4double BDSAcceleratorComponent::GetK1()
{ return itsK1; }

inline G4double BDSAcceleratorComponent::GetK2()
{ return itsK2; }

inline G4double BDSAcceleratorComponent::GetK3()
{ return itsK3; }

inline void BDSAcceleratorComponent::SetK1(G4double K1)
{ itsK1 = K1; }

inline void BDSAcceleratorComponent::SetK2(G4double K2)
{ itsK2 = K2; }

inline void BDSAcceleratorComponent::SetK3(G4double K3)
{ itsK3 = K3; }

inline G4RotationMatrix* BDSAcceleratorComponent::GetRotation()
{ return itsRotation;}

inline G4ThreeVector BDSAcceleratorComponent::GetPosition()
{ return itsPosition;}

inline void BDSAcceleratorComponent::SetPosition(G4ThreeVector pos)
{ itsPosition = pos;}

inline const G4String BDSAcceleratorComponent::GetName () const
{return itsName;}

inline void BDSAcceleratorComponent::SetName (G4String aName)
{itsName=aName;}

inline const G4String BDSAcceleratorComponent::GetType () const
{return itsType;}

inline void BDSAcceleratorComponent::SetType (G4String aType)
{itsType=aType;}

inline G4int BDSAcceleratorComponent::GetPrecisionRegion () const
{return itsPrecisionRegion;}

inline void BDSAcceleratorComponent::SetPrecisionRegion (G4int aPrecisionRegion)
{itsPrecisionRegion=aPrecisionRegion;}

inline G4LogicalVolume* BDSAcceleratorComponent::GetMarkerLogicalVolume() const
{return itsMarkerLogicalVolume;}

inline G4LogicalVolume* BDSAcceleratorComponent::GetTunnelLogicalVolume() const
{return itsTunnelLogicalVolume;}

inline G4LogicalVolume* BDSAcceleratorComponent::GetInnerMostLogicalVolume() const
{return itsInnerMostLogicalVolume;}

inline void BDSAcceleratorComponent::
SetInnerMostLogicalVolume(G4LogicalVolume* aLogVol)
{itsInnerMostLogicalVolume = aLogVol;}

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

inline void BDSAcceleratorComponent::SetMultipleSensitiveVolumes(G4LogicalVolume* aLogVol)
{ itsMultipleSensitiveVolumes.push_back(aLogVol);}

inline void BDSAcceleratorComponent::SetGFlashVolumes(G4LogicalVolume* aLogVol)
{ itsGFlashVolumes.push_back(aLogVol);}

inline  std::vector<G4LogicalVolume*> BDSAcceleratorComponent::GetMultipleSensitiveVolumes()
{return itsMultipleSensitiveVolumes;}

inline  std::vector<G4LogicalVolume*> BDSAcceleratorComponent::GetGFlashVolumes()
{return itsGFlashVolumes;}

inline void BDSAcceleratorComponent::SetMultiplePhysicalVolumes(G4VPhysicalVolume* aPhysVol)
{ itsMultiplePhysicalVolumes.push_back(aPhysVol);}

inline  std::vector<G4VPhysicalVolume*> BDSAcceleratorComponent::GetMultiplePhysicalVolumes()
{return itsMultiplePhysicalVolumes;}

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

inline  G4UserLimits* BDSAcceleratorComponent::GetUserLimits(){
  return GetInnerBPUserLimits();
}

inline  G4UserLimits* BDSAcceleratorComponent::GetInnerBPUserLimits()
  {return itsInnerBeampipeUserLimits;}

inline  G4double BDSAcceleratorComponent::GetXOffset()
{return itsXOffset;}

inline G4double BDSAcceleratorComponent::GetYOffset() 
{return itsYOffset;}

inline G4double BDSAcceleratorComponent::GetZOffset()
{return itsZOffset;}

inline G4double BDSAcceleratorComponent::GetTunnelRadius()
{return itsTunnelRadius;}

inline G4double BDSAcceleratorComponent::GetTunnelOffsetX()
{return itsTunnelOffsetX;}

inline G4double BDSAcceleratorComponent::GetTilt()
{return itsTilt;}


inline  G4double BDSAcceleratorComponent::getParameterValue(G4String spec, G4String name) const
{
  G4double value = 0;

  std::string delimiters = "&";
  std::string param = name + "=";

  int pos = spec.find(param);
  if( pos >= 0 )
    {
      
      int pos2 = spec.find("&",pos);
      int pos3 = spec.length();
      int tend = pos2 < 0 ? pos3 : pos2; 
      int llen = tend - pos - param.length();
      
      std::string val = spec.substr(pos + param.length(), llen);
      
      value = atof(val.c_str());

  }

  return value;

}

inline  G4String BDSAcceleratorComponent::getParameterValueString(G4String spec, G4String name) const
{
  G4String value = "";

  std::string delimiters = "&";
  std::string param = name + "=";

  int pos = spec.find(param);
  if( pos >= 0 )
    {
      
      int pos2 = spec.find("&",pos);
      int pos3 = spec.length();
      int tend = pos2 < 0 ? pos3 : pos2; 
      int llen = tend - pos - param.length();
      
      value = spec.substr(pos + param.length(), llen);
  }

  return value;

}

#endif
