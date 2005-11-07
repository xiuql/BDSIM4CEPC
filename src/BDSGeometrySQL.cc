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

#include "BDSSamplerSD.hh"
#include "G4SDManager.hh"

#include <vector>
#include <map>
#include <cstdlib>
#include "G4ClassicalRK4.hh"
#include <string>

using namespace std;

extern BDSMaterials* theMaterials;
extern G4RotationMatrix* RotY90;

BDSGeometrySQL::BDSGeometrySQL(G4String DBfile)
{
  ifs.open(DBfile.c_str());
  if(!ifs) G4Exception("Unable to load SQL database file: " + DBfile);
}

BDSGeometrySQL::~BDSGeometrySQL()
{;}

void BDSGeometrySQL::Construct(G4LogicalVolume *marker)
{
  itsMarkerVol = marker;
  G4String file;
  char buffer[255];
  while (ifs>>file)
    {
      if(file.contains("#")) ifs.getline(buffer,255); // This is a comment line
      else BuildSQLObjects(file);
    }
}

void BDSGeometrySQL::BuildSQLObjects(G4String file)
{

  BDSMySQLWrapper sql(file);
  itsSQLTable=sql.ConstructTable();

  for (G4int i=0; i<itsSQLTable.size(); i++)
    {

      G4String TableName = itsSQLTable[i]->GetName();
      G4int pos = TableName.find("_");
      G4String ObjectType = TableName.substr(pos+1,TableName.length() - pos);

      if(ObjectType=="cone" || ObjectType=="CONE" || ObjectType=="Cone")
	BuildCone(itsSQLTable[i]);
      else if(ObjectType=="box" || ObjectType=="BOX" || ObjectType=="Box")
	BuildBox(itsSQLTable[i]);
    }

}

void BDSGeometrySQL::BuildCone(BDSMySQLTable* aSQLTable)
{
  G4double PosX=0.;
  G4double PosY=0.;
  G4double PosZ=0.;
  G4double length=10.*mm;
  G4double rStart=10.*mm;
  G4double rEnd=10.*mm;
  G4double VisRed=0.;
  G4double VisGreen=0.;
  G4double VisBlue=0.;
  G4String VisType="w";
  G4String Material="Vacuum";
  G4String TableName = aSQLTable->GetName();
  G4String Name;

  for(G4int k=0; k<aSQLTable->GetVariable("Length")->GetNVariables(); k++)
    {
      Name = TableName+BDSGlobals->StringFromInt(k);

      if(aSQLTable->GetVariable("PosX")!=NULL)
	PosX = aSQLTable->GetVariable("PosX")->GetDblValue(k);
      if(aSQLTable->GetVariable("PosY")!=NULL)
	PosY = aSQLTable->GetVariable("PosY")->GetDblValue(k);
      if(aSQLTable->GetVariable("PosZ")!=NULL)
	PosZ = aSQLTable->GetVariable("PosZ")->GetDblValue(k);
      if(aSQLTable->GetVariable("Red")!=NULL)
	VisRed = aSQLTable->GetVariable("Red")->GetDblValue(k);
      if(aSQLTable->GetVariable("Blue")!=NULL)
	VisBlue = aSQLTable->GetVariable("Blue")->GetDblValue(k);
      if(aSQLTable->GetVariable("Green")!=NULL)
	VisGreen = aSQLTable->GetVariable("Green")->GetDblValue(k);
      if(aSQLTable->GetVariable("VisAtt")!=NULL)
	VisType = aSQLTable->GetVariable("VisAtt")->GetStrValue(k);
      if(aSQLTable->GetVariable("Length")!=NULL)
	length = aSQLTable->GetVariable("Length")->GetDblValue(k);
      if(aSQLTable->GetVariable("rStart")!=NULL)
	rStart = aSQLTable->GetVariable("rStart")->GetDblValue(k);
      if(aSQLTable->GetVariable("rEnd")!=NULL)
	rEnd = aSQLTable->GetVariable("rEnd")->GetDblValue(k);
      if(aSQLTable->GetVariable("Material")!=NULL)
	Material = aSQLTable->GetVariable("Material")->GetStrValue(k);
      if(aSQLTable->GetVariable("Name")!=NULL)
	Name = aSQLTable->GetVariable("Name")->GetStrValue(k);


      G4Cons* aCone = new G4Cons(Name+"_OuterCone",
				 0.0,
				 rStart,
				 0.0,
				 rEnd,
				 length/2,
				 0,
				 twopi*radian);
      
      G4LogicalVolume* aConeVol = 
	new G4LogicalVolume(aCone,
			    theMaterials->GetMaterial(Material),
			    Name+"_Outer_LogVol");
      
      G4ThreeVector PlacementPoint(PosX,PosY,PosZ);

      new G4PVPlacement(NULL,
			PlacementPoint,
			aConeVol,
			Name+"_PhysiComp",
			itsMarkerVol,
			false,
			0);

      G4UserLimits* ConeUserLimits = new G4UserLimits();
      ConeUserLimits->SetMaxAllowedStep(length);
      aConeVol->SetUserLimits(ConeUserLimits);

      G4VisAttributes* VisAtt = 
	new G4VisAttributes(G4Colour(VisRed, VisGreen, VisBlue));
      switch (VisType(0))
	{
	case 'w': VisAtt->SetForceWireframe(true); break;
	case 'i': VisAtt->SetVisibility(false); break;
	case 's': VisAtt->SetForceSolid(true); break;
	}
      aConeVol->SetVisAttributes(VisAtt);
    }
}

void BDSGeometrySQL::BuildBox(BDSMySQLTable* aSQLTable)
{
  G4double PosX=0.;
  G4double PosY=0.;
  G4double PosZ=0.;
  G4double lengthX=10.*mm;
  G4double lengthY=10.*mm;
  G4double lengthZ=10.*mm;
  G4double VisRed=0.;
  G4double VisGreen=0.;
  G4double VisBlue=0.;
  G4String VisType="w";
  G4String Material="Vacuum";
  G4String TableName = aSQLTable->GetName();
  G4String Name;

  for(G4int k=0; k<aSQLTable->GetVariable("LengthX")->GetNVariables(); k++)
    {
      Name = TableName+BDSGlobals->StringFromInt(k);

      if(aSQLTable->GetVariable("PosX")!=NULL)
	PosX = aSQLTable->GetVariable("PosX")->GetDblValue(k);
      if(aSQLTable->GetVariable("PosY")!=NULL)
	PosY = aSQLTable->GetVariable("PosY")->GetDblValue(k);
      if(aSQLTable->GetVariable("PosZ")!=NULL)
	PosZ = aSQLTable->GetVariable("PosZ")->GetDblValue(k);
      if(aSQLTable->GetVariable("Red")!=NULL)
	VisRed = aSQLTable->GetVariable("Red")->GetDblValue(k);
      if(aSQLTable->GetVariable("Blue")!=NULL)
	VisBlue = aSQLTable->GetVariable("Blue")->GetDblValue(k);
      if(aSQLTable->GetVariable("Green")!=NULL)
	VisGreen = aSQLTable->GetVariable("Green")->GetDblValue(k);
      if(aSQLTable->GetVariable("VisAtt")!=NULL)
	VisType = aSQLTable->GetVariable("VisAtt")->GetStrValue(k);
      if(aSQLTable->GetVariable("LengthX")!=NULL)
	lengthX = aSQLTable->GetVariable("LengthX")->GetDblValue(k);
      if(aSQLTable->GetVariable("LengthY")!=NULL)
	lengthY = aSQLTable->GetVariable("LengthY")->GetDblValue(k);
      if(aSQLTable->GetVariable("LengthZ")!=NULL)
	lengthZ = aSQLTable->GetVariable("LengthZ")->GetDblValue(k);
      if(aSQLTable->GetVariable("Material")!=NULL)
	Material = aSQLTable->GetVariable("Material")->GetStrValue(k);
      if(aSQLTable->GetVariable("Name")!=NULL)
	Name = aSQLTable->GetVariable("Name")->GetStrValue(k);


      G4Box* aBox = new G4Box(Name+"_OuterBox",
			      lengthX/2,
			      lengthY/2,
			      lengthZ/2);
      
      G4LogicalVolume* aBoxVol = 
	new G4LogicalVolume(aBox,
			    theMaterials->GetMaterial(Material),
			    Name+"_Outer_LogVol");
      
      G4ThreeVector PlacementPoint(PosX,PosY,PosZ);

      new G4PVPlacement(NULL,
			PlacementPoint,
			aBoxVol,
			Name+"_PhysiComp",
			itsMarkerVol,
			false,
			0);

      G4UserLimits* BoxUserLimits = new G4UserLimits();
      BoxUserLimits->SetMaxAllowedStep(lengthZ);
      aBoxVol->SetUserLimits(BoxUserLimits);

      G4VisAttributes* VisAtt = 
	new G4VisAttributes(G4Colour(VisRed, VisGreen, VisBlue));
      switch (VisType(0))
	{
	case 'w': VisAtt->SetForceWireframe(true); break;
	case 'i': VisAtt->SetVisibility(false); break;
	case 's': VisAtt->SetForceSolid(true); break;
	}
      aBoxVol->SetVisAttributes(VisAtt);
    }
}
