#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSGeometrySQL.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "BDSMySQLWrapper.hh"
#include "BDSMaterials.hh"
#include "BDSSamplerSD.hh"
#include "G4SDManager.hh"
#include "BDSSamplerSD.hh"
#include "BDSOutput.hh"
#include <vector>
#include <map>
#include <cstdlib>
#include "G4ClassicalRK4.hh"
#include <string>

using namespace std;

extern BDSMaterials* theMaterials;
extern G4RotationMatrix* RotY90;
extern BDSOutput bdsOutput;
extern BDSSamplerSD* BDSSamplerSensDet;
extern BDSGlobalConstants* BDSGlobals;

BDSGeometrySQL::BDSGeometrySQL(G4String DBfile, G4double markerlength)
{
  itsMarkerLength = markerlength;
  ifs.open(DBfile.c_str());
  if(!ifs) G4Exception("Unable to load SQL database file: " + DBfile);
  align_in_volume = NULL;  //default alignment (does nothing)
  align_out_volume = NULL;  //default alignment (does nothing)
}

BDSGeometrySQL::~BDSGeometrySQL()
{;}

void BDSGeometrySQL::Construct(G4LogicalVolume *marker)
{
  itsMarkerVol = marker;
  G4String file;
  char buffer[1000];
  while (ifs>>file)
    {
      if(file.contains("#")) ifs.getline(buffer,1000); // This is a comment line
      else BuildSQLObjects(file);
    }
  
  // Now that all solids are built - place them.
  
}

void BDSGeometrySQL::BuildSQLObjects(G4String file)
{

  BDSMySQLWrapper sql(file);
  itsSQLTable=sql.ConstructTable();

  for (G4int i=0; i<(G4int)itsSQLTable.size(); i++)
    {

      G4String TableName = itsSQLTable[i]->GetName();
      G4int pos = TableName.find("_");
      G4String ObjectType = TableName.substr(pos+1,TableName.length() - pos);
      G4String::caseCompare cmpmode = G4String::ignoreCase;
      if(ObjectType.compareTo("CONE",cmpmode)==0) BuildCone(itsSQLTable[i]);
      else if(ObjectType.compareTo("BOX",cmpmode)==0) BuildBox(itsSQLTable[i]);
      else if(ObjectType.compareTo("SAMPLER",cmpmode)==0) BuildSampler(itsSQLTable[i]);
    }

}

void BDSGeometrySQL::BuildCone(BDSMySQLTable* aSQLTable)
{
  G4LogicalVolume** VOL_LIST = NULL;
  
  G4int NVariables = aSQLTable->GetVariable("LENGTH")->GetNVariables();

  VOL_LIST = new G4LogicalVolume*[NVariables];
  VOL_LIST[0] = itsMarkerVol;
  for( int i=1; i<NVariables; i++) VOL_LIST[i] = NULL;
  G4double length;
  G4double rInnerStart;
  G4double rInnerEnd;
  G4double rOuterStart;
  G4double rOuterEnd;
  G4double VisRed; 
  G4double VisGreen;
  G4double VisBlue;
  G4int ID;
  G4String VisType;
  G4String Material;
  G4String TableName = aSQLTable->GetName();
  G4String Name;

  for(G4int k=0; k<NVariables; k++)
    {
      //Defaults
      length = rOuterStart = rOuterEnd = 10.*mm;
      rInnerStart = rInnerEnd = 0.0;
      VisRed = VisGreen = VisBlue = 0.;
      ID = k+1;
      VisType = "W";
      Material = "VACUUM";

      if(aSQLTable->GetVariable("ID")!=NULL)
	ID = aSQLTable->GetVariable("ID")->GetIntValue(k);
      if(aSQLTable->GetVariable("RED")!=NULL)
	VisRed = aSQLTable->GetVariable("RED")->GetDblValue(k);
      if(aSQLTable->GetVariable("BLUE")!=NULL)
	VisBlue = aSQLTable->GetVariable("BLUE")->GetDblValue(k);
      if(aSQLTable->GetVariable("GREEN")!=NULL)
	VisGreen = aSQLTable->GetVariable("GREEN")->GetDblValue(k);
      if(aSQLTable->GetVariable("VISATT")!=NULL)
	VisType = aSQLTable->GetVariable("VISATT")->GetStrValue(k);
      if(aSQLTable->GetVariable("LENGTH")!=NULL)
	length = aSQLTable->GetVariable("LENGTH")->GetDblValue(k);
      if(aSQLTable->GetVariable("RINNERSTART")!=NULL)
	rInnerStart = aSQLTable->GetVariable("RINNERSTART")->GetDblValue(k);
      if(aSQLTable->GetVariable("RINNEREND")!=NULL)
	rInnerEnd = aSQLTable->GetVariable("RINNEREND")->GetDblValue(k);
      if(aSQLTable->GetVariable("ROUTERSTART")!=NULL)
	rOuterStart = aSQLTable->GetVariable("ROUTERSTART")->GetDblValue(k);
      if(aSQLTable->GetVariable("ROUTEREND")!=NULL)
	rOuterEnd = aSQLTable->GetVariable("ROUTEREND")->GetDblValue(k);
      if(aSQLTable->GetVariable("MATERIAL")!=NULL)
	Material = aSQLTable->GetVariable("MATERIAL")->GetStrValue(k);
      if(aSQLTable->GetVariable("NAME")!=NULL)
	Name = aSQLTable->GetVariable("NAME")->GetStrValue(k);

      if(Name=="") Name = TableName+BDSGlobals->StringFromInt(k);

      G4Cons* aCone = new G4Cons(Name+"_Cone",
				 rInnerStart,
				 rOuterStart,
				 rInnerEnd,
				 rOuterEnd,
				 length/2,
				 0,
				 twopi*radian);

      G4LogicalVolume* aConeVol = 
	new G4LogicalVolume(aCone,
			    theMaterials->GetMaterial(Material),
			    Name+"_LogVol");
      
      G4UserLimits* ConeUserLimits = new G4UserLimits();
      ConeUserLimits->SetMaxAllowedStep(length);
      aConeVol->SetUserLimits(ConeUserLimits);
      G4VisAttributes* VisAtt = 
	new G4VisAttributes(G4Colour(VisRed, VisGreen, VisBlue));
      switch (VisType(0))
	{
	case 'W': VisAtt->SetForceWireframe(true); break;
	case 'I': VisAtt->SetVisibility(false); break;
	case 'S': VisAtt->SetForceSolid(true); break;
	case 'w': VisAtt->SetForceWireframe(true); break;
	case 'i': VisAtt->SetVisibility(false); break;
	case 's': VisAtt->SetForceSolid(true); break;
	}
      aConeVol->SetVisAttributes(VisAtt);
      if(ID<1 || ID>k+1){
	G4cout << Name << " has invalid ID assigned:  " << ID << G4endl;
	G4cerr << "Stopping BDSIM in BDSGeometrySQL::BuildCone " << G4endl;
      }
      else VOL_LIST[ID] = aConeVol;
    }

  PlaceComponents(aSQLTable, VOL_LIST);
  delete [] VOL_LIST;
  VOL_LIST = NULL;
}

void BDSGeometrySQL::BuildBox(BDSMySQLTable* aSQLTable)
{
  G4LogicalVolume** VOL_LIST = NULL;
  
  G4int NVariables = aSQLTable->GetVariable("LENGTHX")->GetNVariables();

  VOL_LIST = new G4LogicalVolume*[NVariables];
  VOL_LIST[0] = itsMarkerVol;
  for( int i=1; i<NVariables; i++) VOL_LIST[i] = NULL;
  G4int ID;
  G4double lengthX;
  G4double lengthY;
  G4double lengthZ;
  G4double VisRed;
  G4double VisGreen;
  G4double VisBlue;
  G4String VisType;
  G4String Material;
  G4String TableName = aSQLTable->GetName();

  G4String Name;

  for(G4int k=0; k<NVariables; k++)
    {
      lengthX = lengthY = lengthZ = 10.*mm;
      VisRed = VisGreen = VisBlue = 0.;
      VisType = "W";
      Material = "VACUUM";
      ID = k+1;

      if(aSQLTable->GetVariable("ID")!=NULL)
	ID = aSQLTable->GetVariable("ID")->GetIntValue(k);
      if(aSQLTable->GetVariable("RED")!=NULL)
	VisRed = aSQLTable->GetVariable("RED")->GetDblValue(k);
      if(aSQLTable->GetVariable("BLUE")!=NULL)
	VisBlue = aSQLTable->GetVariable("BLUE")->GetDblValue(k);
      if(aSQLTable->GetVariable("GREEN")!=NULL)
	VisGreen = aSQLTable->GetVariable("GREEN")->GetDblValue(k);
      if(aSQLTable->GetVariable("VISATT")!=NULL)
	VisType = aSQLTable->GetVariable("VISATT")->GetStrValue(k);
      if(aSQLTable->GetVariable("LENGTHX")!=NULL)
	lengthX = aSQLTable->GetVariable("LENGTHX")->GetDblValue(k);
      if(aSQLTable->GetVariable("LENGTHY")!=NULL)
	lengthY = aSQLTable->GetVariable("LENGTHY")->GetDblValue(k);
      if(aSQLTable->GetVariable("LENGTHZ")!=NULL)
	lengthZ = aSQLTable->GetVariable("LENGTHZ")->GetDblValue(k);
      if(aSQLTable->GetVariable("MATERIAL")!=NULL)
	Material = aSQLTable->GetVariable("MATERIAL")->GetStrValue(k);
      if(aSQLTable->GetVariable("NAME")!=NULL)
	Name = aSQLTable->GetVariable("NAME")->GetStrValue(k);

      if(Name=="") Name = TableName+BDSGlobals->StringFromInt(k);

      G4Box* aBox = new G4Box(Name+"_Box",
			      lengthX/2,
			      lengthY/2,
			      lengthZ/2);
      
      G4LogicalVolume* aBoxVol = 
	new G4LogicalVolume(aBox,
			    theMaterials->GetMaterial(Material),
			    Name+"_LogVol");
      
      G4UserLimits* BoxUserLimits = new G4UserLimits();
      BoxUserLimits->SetMaxAllowedStep(lengthZ);
      aBoxVol->SetUserLimits(BoxUserLimits);
      G4VisAttributes* VisAtt = 
	new G4VisAttributes(G4Colour(VisRed, VisGreen, VisBlue));
      switch (VisType(0))
	{
	case 'W': VisAtt->SetForceWireframe(true); break;
	case 'I': VisAtt->SetVisibility(false); break;
	case 'S': VisAtt->SetForceSolid(true); break;
	case 'w': VisAtt->SetForceWireframe(true); break;
	case 'i': VisAtt->SetVisibility(false); break;
	case 's': VisAtt->SetForceSolid(true); break;
	}
      aBoxVol->SetVisAttributes(VisAtt);
      if(ID<1 || ID>k+1){
	G4cout << Name << " has invalid ID assigned:  " << ID << G4endl;
	G4cerr << "Stopping BDSIM in BDSGeometrySQL::BuildBox " << G4endl;
      }
      else VOL_LIST[ID] = aBoxVol;
    }

  PlaceComponents(aSQLTable, VOL_LIST);
  delete [] VOL_LIST;
  VOL_LIST = NULL;
}

void BDSGeometrySQL::BuildSampler(BDSMySQLTable* aSQLTable)
{
  G4LogicalVolume** VOL_LIST = NULL;
  
  G4int NVariables = aSQLTable->GetVariable("LENGTH")->GetNVariables();

  VOL_LIST = new G4LogicalVolume*[NVariables];
  VOL_LIST[0] = itsMarkerVol;
  for( int i=1; i<NVariables; i++) VOL_LIST[i] = NULL;
  G4double length;
  G4double rInnerStart;
  G4double rInnerEnd;
  G4double rOuterStart;
  G4double rOuterEnd;
  G4double VisRed; 
  G4double VisGreen;
  G4double VisBlue;
  G4int ID;
  G4String VisType;
  G4String Material;
  G4String TableName = aSQLTable->GetName();
  G4String Name;

  for(G4int k=0; k<NVariables; k++)
    {
      //Defaults
      length = rOuterStart = rOuterEnd = 10.*mm;
      rInnerStart = rInnerEnd = 0.0;
      VisRed = VisGreen = VisBlue = 0.;
      ID = k+1;
      VisType = "W";
      Material = "VACUUM";

      if(aSQLTable->GetVariable("ID")!=NULL)
	ID = aSQLTable->GetVariable("ID")->GetIntValue(k);
      if(aSQLTable->GetVariable("RED")!=NULL)
	VisRed = aSQLTable->GetVariable("RED")->GetDblValue(k);
      if(aSQLTable->GetVariable("BLUE")!=NULL)
	VisBlue = aSQLTable->GetVariable("BLUE")->GetDblValue(k);
      if(aSQLTable->GetVariable("GREEN")!=NULL)
	VisGreen = aSQLTable->GetVariable("GREEN")->GetDblValue(k);
      if(aSQLTable->GetVariable("VISATT")!=NULL)
	VisType = aSQLTable->GetVariable("VISATT")->GetStrValue(k);
      if(aSQLTable->GetVariable("LENGTH")!=NULL)
	length = aSQLTable->GetVariable("LENGTH")->GetDblValue(k);
      if(aSQLTable->GetVariable("RINNERSTART")!=NULL)
	rInnerStart = aSQLTable->GetVariable("RINNERSTART")->GetDblValue(k);
      if(aSQLTable->GetVariable("RINNEREND")!=NULL)
	rInnerEnd = aSQLTable->GetVariable("RINNEREND")->GetDblValue(k);
      if(aSQLTable->GetVariable("ROUTERSTART")!=NULL)
	rOuterStart = aSQLTable->GetVariable("ROUTERSTART")->GetDblValue(k);
      if(aSQLTable->GetVariable("ROUTEREND")!=NULL)
	rOuterEnd = aSQLTable->GetVariable("ROUTEREND")->GetDblValue(k);
      if(aSQLTable->GetVariable("MATERIAL")!=NULL)
	Material = aSQLTable->GetVariable("MATERIAL")->GetStrValue(k);
      if(aSQLTable->GetVariable("NAME")!=NULL)
	{
	  Name = aSQLTable->GetVariable("NAME")->GetStrValue(k);
	  aSQLTable->GetVariable("NAME")->SetStrValue(k,Name+"_SQL");
	  Name = aSQLTable->GetVariable("NAME")->GetStrValue(k);
	}
      if(Name=="_SQL") Name = TableName+BDSGlobals->StringFromInt(k)+"_SQL";
     
      G4Cons* aSampler = new G4Cons(Name+"_samp",
				    rInnerStart,
				    rOuterStart,
				    rInnerEnd,
				    rOuterEnd,
				    length/2,
				    0,
				    twopi*radian);

      G4LogicalVolume* aSamplerVol = 
	new G4LogicalVolume(aSampler,
			    theMaterials->GetMaterial(Material),
			    Name+"_LogVol");
      
      G4UserLimits* SamplerUserLimits = new G4UserLimits();
      SamplerUserLimits->SetMaxAllowedStep(length);
      aSamplerVol->SetUserLimits(SamplerUserLimits);
      G4VisAttributes* VisAtt = 
	new G4VisAttributes(G4Colour(VisRed, VisGreen, VisBlue));
      switch (VisType(0))
	{
	case 'W': VisAtt->SetForceWireframe(true); break;
	case 'I': VisAtt->SetVisibility(false); break;
	case 'S': VisAtt->SetForceSolid(true); break;
	case 'w': VisAtt->SetForceWireframe(true); break;
	case 'i': VisAtt->SetVisibility(false); break;
	case 's': VisAtt->SetForceSolid(true); break;
	}
      aSamplerVol->SetVisAttributes(VisAtt);

      G4SDManager* SDMan = G4SDManager::GetSDMpointer();
      if(bdsOutput.nSamplers==0){
	BDSSamplerSensDet = new BDSSamplerSD(Name, "plane");
	SDMan->AddNewDetector(BDSSamplerSensDet);
      }
      aSamplerVol->SetSensitiveDetector(BDSSamplerSensDet);
      bdsOutput.nSamplers++;
      bdsOutput.SampName.push_back(Name + "_PhysiComp_1");
      if(ID<1 || ID>k+1){
	G4cout << Name << " has invalid ID assigned:  " << ID << G4endl;
	G4cerr << "Stopping BDSIM in BDSGeometrySQL::BuildSampler " << G4endl;
      }
      else VOL_LIST[ID] = aSamplerVol;
    }

  PlaceComponents(aSQLTable, VOL_LIST);
  delete [] VOL_LIST;
  VOL_LIST = NULL;
}

G4RotationMatrix* BDSGeometrySQL::RotateComponent(G4double psi,G4double phi,G4double theta)
{
  G4RotationMatrix *rotateComponent = new G4RotationMatrix;
  if(psi==0 && phi==0 && theta==0) return rotateComponent;

  G4RotationMatrix LocalRotation;
  G4ThreeVector localX = G4ThreeVector(1.,0.,0.);
  G4ThreeVector localY = G4ThreeVector(0.,1.,0.);
  G4ThreeVector localZ = G4ThreeVector(0.,0.,1.);
  
  LocalRotation.rotate(psi,localZ);
  localX.rotate(psi,localZ);
  localY.rotate(psi,localZ);
  
  
  LocalRotation.rotate(phi,localY);
  localX.rotate(phi,localY);
  localZ.rotate(phi,localY);
  
  
  LocalRotation.rotate(theta,localX);
  localY.rotate(theta,localX);
  localZ.rotate(theta,localX);
  
  rotateComponent->transform(LocalRotation);
  rotateComponent->invert();
  
  return rotateComponent;
}


void BDSGeometrySQL::PlaceComponents(BDSMySQLTable* aSQLTable, G4LogicalVolume** VOL_LIST)
{
  G4double PosX;
  G4double PosY;
  G4double PosZ;
  G4double RotPsi;
  G4double RotTheta;
  G4double RotPhi;
  G4double K1,K2,K3,K4;
  G4int ID, PARENTID;
  G4String Name;
  G4String MagType;
  G4String TableName = aSQLTable->GetName();
  G4int NVariables = aSQLTable->GetVariable("POSX")->GetNVariables();
  G4int align_in;
  G4int align_out;

  for(G4int k=0; k<NVariables; k++) // Now run through and place according to
    { 
      //Defaults
      PosX = PosY = PosZ = 0.;
      RotPsi = RotTheta = RotPhi = 0.;
      K1 = K2 = K3 = K4 = 0.;
      ID = k+1;
      PARENTID = 0;
      align_in=0;
      align_out=0;
      MagType = "";
      if(aSQLTable->GetVariable("ID")!=NULL)
	ID = aSQLTable->GetVariable("ID")->GetIntValue(k);
      if(aSQLTable->GetVariable("PARENTID")!=NULL)
	PARENTID = aSQLTable->GetVariable("PARENTID")->GetIntValue(k);
      if(aSQLTable->GetVariable("POSX")!=NULL)
	PosX = aSQLTable->GetVariable("POSX")->GetDblValue(k);
      if(aSQLTable->GetVariable("POSY")!=NULL)
	PosY = aSQLTable->GetVariable("POSY")->GetDblValue(k);
      if(aSQLTable->GetVariable("POSZ")!=NULL)
	PosZ = aSQLTable->GetVariable("POSZ")->GetDblValue(k);
      if(aSQLTable->GetVariable("ROTPSI")!=NULL)
	RotPsi = aSQLTable->GetVariable("ROTPSI")->GetDblValue(k);
      if(aSQLTable->GetVariable("ROTTHETA")!=NULL)
	RotTheta = aSQLTable->GetVariable("ROTTHETA")->GetDblValue(k);
      if(aSQLTable->GetVariable("ROTPHI")!=NULL)
	RotPhi = aSQLTable->GetVariable("ROTPHI")->GetDblValue(k);
      if(aSQLTable->GetVariable("K1")!=NULL)
	K1 = aSQLTable->GetVariable("K1")->GetDblValue(k);
      if(aSQLTable->GetVariable("K2")!=NULL)
	K2 = aSQLTable->GetVariable("K2")->GetDblValue(k);
      if(aSQLTable->GetVariable("K3")!=NULL)
	K3 = aSQLTable->GetVariable("K3")->GetDblValue(k);
      if(aSQLTable->GetVariable("K4")!=NULL)
	K4 = aSQLTable->GetVariable("K4")->GetDblValue(k);
      if(aSQLTable->GetVariable("MAGTYPE")!=NULL)
	MagType = aSQLTable->GetVariable("MAGTYPE")->GetStrValue(k);
      if(aSQLTable->GetVariable("ALIGNIN")!=NULL)
	align_in = aSQLTable->GetVariable("ALIGNIN")->GetIntValue(k);
      if(aSQLTable->GetVariable("ALIGNOUT")!=NULL)
	align_out = aSQLTable->GetVariable("ALIGNOUT")->GetIntValue(k);
      if(aSQLTable->GetVariable("NAME")!=NULL)
	Name = aSQLTable->GetVariable("NAME")->GetStrValue(k);
      if(Name=="_SQL") Name = TableName+BDSGlobals->StringFromInt(k) + "_SQL";
      if(Name=="") Name = TableName+BDSGlobals->StringFromInt(k);

      if(PARENTID==0) PosZ-=itsMarkerLength/2; //Move definition of PosZ to front of element

      G4ThreeVector PlacementPoint(PosX,PosY,PosZ);
      
      G4VPhysicalVolume* PhysiComp = 
	new G4PVPlacement(RotateComponent(RotPsi,RotPhi,RotTheta),
			  PlacementPoint,
			  VOL_LIST[ID],
			  Name+"_PhysiComp",
			  VOL_LIST[PARENTID],
			  false,
			  0);

      if(align_in)
	{
	  // Make sure program stops and informs user if more than one alignment vol.
	  if(align_in_volume!=NULL)
	    {
	      G4cerr<<"\nBDSGeometrySQL.cc:486: Trying to align in-beam to SQL volume to " << PhysiComp->GetName() << " but alignment already set to " << align_in_volume->GetName() << G4endl;
	      G4Exception("Aborting Program");

	    }

	  else
	    align_in_volume=PhysiComp;

	}

      if(align_out)
	{
	  if(align_out_volume!=NULL)
	    {
	      G4cerr<<"\nBDSGeometrySQL.cc:486: Trying to align out-beam to SQL volume to " << PhysiComp->GetName() << " but alignment already set to " << align_out_volume->GetName() << G4endl;
	      G4Exception("Aborting Program");

	    }

	  else
	    align_out_volume=PhysiComp;
	}

      G4String::caseCompare cmpmode = G4String::ignoreCase;
      G4double P0 = BDSGlobals->GetBeamTotalEnergy();
      G4double brho=
	sqrt(pow(P0,2)- pow(electron_mass_c2,2))/(0.299792458 * (GeV/(tesla*m)));
      if(MagType.compareTo("QUAD",cmpmode)==0)
	{
	  QuadBgrad.push_back(brho * K1 * tesla / m);
	  Quadvol.push_back(PhysiComp->GetName());
	}

      if(MagType.compareTo("SEXT",cmpmode)==0)
	{
	  SextBgrad.push_back(brho * K2 * tesla / (m*m));
	  Sextvol.push_back(PhysiComp->GetName());
	}
  }
}
