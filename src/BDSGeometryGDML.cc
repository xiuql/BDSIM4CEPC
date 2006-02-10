#ifdef USE_XML
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSGeometryGDML.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Torus.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
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

BDSGeometryGDML::BDSGeometryGDML(G4String GDMLfile)
{
  itsGDMLfile = GDMLfile;
  visRed = visGreen = visBlue = 0.0;

  // define some standard constants
  CONST_REF aconst;
  aconst.name="pi";
  aconst.value=pi;
  CONST_LIST.push_back(aconst);

  aconst.name="TWOPI";
  aconst.value=twopi;
  CONST_LIST.push_back(aconst);

  
  aconst.name="HALFPI";
  aconst.value=halfpi;
  CONST_LIST.push_back(aconst);

  // define units using mm and radians as =1
  
  
  aconst.name="radian";
  aconst.value=radian;
  CONST_LIST.push_back(aconst);

  aconst.name="degree";
  aconst.value=degree;
  CONST_LIST.push_back(aconst);

  
  aconst.name="mm";
  aconst.value=mm;
  CONST_LIST.push_back(aconst);

  
  aconst.name="cm";
  aconst.value=cm;
  CONST_LIST.push_back(aconst);

  
  aconst.name="m";
  aconst.value=m;
  CONST_LIST.push_back(aconst);

}

BDSGeometryGDML::~BDSGeometryGDML()
{;}

void BDSGeometryGDML::Construct(G4LogicalVolume *marker)
{
  itsMarkerVol = marker;
  parseDoc();

}

void BDSGeometryGDML::parseDoc()
{
  char* docname = itsGDMLfile.c_str();
  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlParseFile(docname);

  if (doc == NULL )
  {
  G4Exception("Document not parsed successfully");
  }

  cur = xmlDocGetRootElement(doc); //GO the first node

  if (cur == NULL)
  {
   xmlFreeDoc(doc);
   G4Exception("empty document");
  }

//test the xml format, must be start by lccdd
   if (xmlStrcmp(cur->name, (const xmlChar *) "lcdd"))
   {
   xmlFreeDoc(doc);
   G4Exception("XML document of the wrong type, root node != lcdd\nCheck your XML file ￼\n");
   }

   cur = cur->xmlChildrenNode;
   
   while (cur != NULL)
     {
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"lcdd")))
	 {
	   // Not coded yet - to be done soon as this section contains Vis/Color information
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"gdml")))
	 {
	   parseGDML(doc,cur);
	 }
       cur = cur->next;
     }

   xmlFreeDoc(doc);
   return;
}

void BDSGeometryGDML::parseGDML(xmlDocPtr doc, xmlNodePtr cur)
{
  cur = cur->xmlChildrenNode;

  while (cur != NULL)
     {
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"define")))
	 {
	   G4cout << "Importing GDML Definitions" << G4endl;
	   parseDEFINE(doc,cur);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"materials")))
	 {
	   //Not coded yet
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"solids")))
	 {
	   G4cout << "Importing GDML Solids" << G4endl;
	   parseSOLID(doc,cur);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"structure")))
	 {
	   G4cout << "Importing GDML Structures" << G4endl;
	   parseSTRUCTURE(doc,cur);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"setup")))
	 {
	   //Not coded yet
	 }
       cur = cur->next;
     }
  return;
}

void BDSGeometryGDML::parseSTRUCTURE(xmlDocPtr doc, xmlNodePtr cur)
{
  cur = cur->xmlChildrenNode;

  while (cur != NULL)
     {
       
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"volume")))
	 {
	   parseVOLUME(doc,cur);
	 }
       cur = cur->next;
     }
  
  return;
}


void BDSGeometryGDML::parseDEFINE(xmlDocPtr doc, xmlNodePtr cur)
{
  cur = cur->xmlChildrenNode;

  while (cur != NULL)
     {
       
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
	 {	
	   ROT_REF arot;
	   arot.name=(parseStrChar(xmlGetProp(cur,(const xmlChar*)"name")));
	   arot.value=G4ThreeVector(parseDblChar(xmlGetProp(cur,(const xmlChar*)"x")),
				    parseDblChar(xmlGetProp(cur,(const xmlChar*)"y")),
				    parseDblChar(xmlGetProp(cur,(const xmlChar*)"z")));

	   ROT_LIST.push_back(arot);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
	 {
	   POS_REF apos;
	   apos.name=(parseStrChar(xmlGetProp(cur,(const xmlChar*)"name")));
	   apos.value=G4ThreeVector(parseDblChar(xmlGetProp(cur,(const xmlChar*)"x")),
				    parseDblChar(xmlGetProp(cur,(const xmlChar*)"y")),
				    parseDblChar(xmlGetProp(cur,(const xmlChar*)"z")));

	   POS_LIST.push_back(apos);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"constant")))
	 {
	   CONST_REF aconst;
	   aconst.name=(parseStrChar(xmlGetProp(cur,(const xmlChar*)"name")));
	   aconst.value=parseDblChar(xmlGetProp(cur,(const xmlChar*)"value"));
	   CONST_LIST.push_back(aconst);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"expression")))
	 {
	   //Not coded yet
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"quantity")))
	 {
	   //Not coded yet
	 }
       cur = cur->next;
     }
  
  return;
}


void BDSGeometryGDML::parseSOLID(xmlDocPtr doc, xmlNodePtr cur)
{
  cur = cur->xmlChildrenNode;

  while (cur != NULL)
     {
       
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"tube")))
	 {
	   G4String name = parseStrChar(xmlGetProp(cur,(const xmlChar*)"name"));
	   G4double rmin = parseDblChar(xmlGetProp(cur,(const xmlChar*)"rmin"));
	   G4double rmax = parseDblChar(xmlGetProp(cur,(const xmlChar*)"rmax"));
	   G4double length = parseDblChar(xmlGetProp(cur,(const xmlChar*)"z"));
	   G4double dphi = parseDblChar(xmlGetProp(cur,(const xmlChar*)"deltaphi"));

	   G4double lunit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"lunit"));
	   G4double aunit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"launit"));
	   
	   if(aunit!=0) dphi*=aunit;
	   if(lunit!=0) 
	     {
	       rmin*=lunit;
	       rmax*=lunit;
	       length*=lunit;
	     }

	   SOLID_LIST.push_back(new G4Tubs(name,
					   rmin,
					   rmax,
					   length/2.0,
					   0.0,
					   dphi)
				);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"box")))
	 {
	   G4String name = parseStrChar(xmlGetProp(cur,(const xmlChar*)"name"));
	   G4double x = parseDblChar(xmlGetProp(cur,(const xmlChar*)"x")); 
	   G4double y = parseDblChar(xmlGetProp(cur,(const xmlChar*)"y")); 
	   G4double z = parseDblChar(xmlGetProp(cur,(const xmlChar*)"z")); 

	   G4double lunit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"lunit"));
	   G4double aunit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"launit"));
	   
	   if(aunit!=0) {}
	   if(lunit!=0) 
	     {
	       x*=lunit;
	       y*=lunit;
	       z*=lunit;
	     }

	   SOLID_LIST.push_back(new G4Box(name,
					  x/2.0,
					  y/2.0,
					  z/2.0)
				);
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"cone")))
	 {
	   G4Exception("Not coded cone yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"eltube")))
	 {
	   G4Exception("Not coded eltube yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"hype")))
	 {
	   G4Exception("Not coded hype yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"intersection")))
	 {
	   G4Exception("Not coded intersection yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"orb")))
	 {
	   G4Exception("Not coded orb yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"polyhedra")))
	 {
	   G4Exception("Not coded polyhedra yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"sphere")))
	 {
	   G4Exception("Not coded sphere yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"trap")))
	 {
	   G4Exception("Not coded trap yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"subtraction")))
	 {

	   G4String name = parseStrChar(xmlGetProp(cur,(const xmlChar*)"name"));
	   G4double lunit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"lunit"));
	   G4double aunit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"launit"));
	   G4String firstname, secondname;

	   G4String position_name;
	   G4double position_unit;
	   G4String position_type;
	   G4ThreeVector PlacementPoint = G4ThreeVector(0.,0.,0.);

	   G4String rotation_name;
	   G4double rotation_unit;
	   G4String rotation_type;
	   G4RotationMatrix* componentRotation = NULL;

	   G4String firstpos_name;
	   G4double firstpos_unit;
	   G4String firstpos_type;
	   G4ThreeVector FirstPlacementPoint = G4ThreeVector(0.,0.,0.);

	   G4String firstrot_name;
	   G4double firstrot_unit;
	   G4String firstrot_type;
	   G4RotationMatrix* componentFirstRot = NULL;

	   xmlNodePtr tempcur = cur->xmlChildrenNode;
	   
	   while(tempcur!=NULL)
	     {
	       if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"first")))
		 firstname = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"ref"));

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"second")))
		 secondname = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"ref"));

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"position")))
		 {
		   position_name = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"name"));	   
		   position_unit = parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"unit"));	   
		   position_type = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"type"));	   
		   PlacementPoint = G4ThreeVector(parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"x")),
						  parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"y")),
						  parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"z")));
		   if(position_unit!=0 && lunit==0) PlacementPoint*=position_unit;
		   else if(lunit!=0) PlacementPoint*=lunit;
		 }

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"positionref")))
		 {
		   G4int i;
		   for(i=0; i<(G4int)POS_LIST.size();i++)
		     {
		       if(POS_LIST[i].name==(parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"ref"))))
			 {
			   PlacementPoint = POS_LIST[i].value;
			   break;
			 }
		     }
		 }

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"rotation")))
		 {
		   rotation_name = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"name"));	   
		   rotation_unit = parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"unit"));
		   rotation_type = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"type"));
		   G4ThreeVector rotvect = G4ThreeVector(parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"x")),
							 parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"y")),
							 parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"z")));
		   if(rotation_unit!=0 && aunit==0) rotvect*=rotation_unit;
		   else if(aunit!=0) rotvect*=aunit;
		   componentRotation = RotateComponent(rotvect);
		 }

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"rotationref")))
 		 {
		   G4int i;
		   for(i=0; i<(G4int)ROT_LIST.size();i++)
		     {
		       if(ROT_LIST[i].name==(parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"ref"))))
			 {
			   componentRotation = RotateComponent(ROT_LIST[i].value);
			   break;
			 }
		     }
		 }

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"firstposition")))
		 {
		   firstpos_name = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"name"));	   
		   firstpos_unit = parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"unit"));	   
		   firstpos_type = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"type"));	   
		   FirstPlacementPoint = G4ThreeVector(parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"x")),
						  parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"y")),
						  parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"z")));
		   if(firstpos_unit!=0 && lunit==0) FirstPlacementPoint*=firstpos_unit;
		   else if(lunit!=0) FirstPlacementPoint*=lunit;
		 }

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"firstpositionref")))
		 {
		   G4int i;
		   for(i=0; i<(G4int)POS_LIST.size();i++)
		     {
		       if(POS_LIST[i].name==(parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"ref"))))
			 {
			   FirstPlacementPoint = POS_LIST[i].value;
			   break;
			 }
		     }
		 }

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"firstrotation")))
		 {
		   firstrot_name = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"name"));	   
		   firstrot_unit = parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"unit"));
		   firstrot_type = parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"type"));
		   G4ThreeVector rotvect = G4ThreeVector(parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"x")),
							 parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"y")),
							 parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"z")));
		   if(firstrot_unit!=0 && aunit==0) rotvect*=firstrot_unit;
		   else if(aunit!=0) rotvect*=aunit;
		   componentFirstRot = RotateComponent(rotvect);
		 }

	       else if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"firstrotationref")))
		 {
		   G4int i;
		   for(i=0; i<(G4int)ROT_LIST.size();i++)
		     {
		       if(ROT_LIST[i].name==(parseStrChar(xmlGetProp(tempcur,(const xmlChar*)"ref"))))
			 {
			   componentFirstRot = RotateComponent(ROT_LIST[i].value);
			   break;
			 }
		     }
		 }
		 
	       tempcur = tempcur->next;
	     }

	   G4int solidA=-1;
	   G4int i;
	   for(i=0; i<(G4int)SOLID_LIST.size(); i++)
	     {
	       if(SOLID_LIST[i]->GetName()== firstname)
		 {
		   solidA=i;
		   break;
		 }
	     }

	   G4int solidB=-1;
	   for(i=0; i<(G4int)SOLID_LIST.size(); i++)
	     {
	       if(SOLID_LIST[i]->GetName()== secondname)
		 {
		   solidB=i;
		   break;
		 }
	     }

	   if (solidA==-1 || solidB==-1) 
	     {
	       G4cout << "Failing to buld subtraction solid: " << name << G4endl;
	       G4Exception("BDSGeometryGDML:: One of Subtraction Solids not found!");
	     }
	   // cater for the 3 geant4 constructors
	   if(componentRotation==NULL && componentFirstRot==NULL &&
	      PlacementPoint==0.0 && FirstPlacementPoint==0.0)
	     {
	       SOLID_LIST.push_back(new G4SubtractionSolid(name,
							   SOLID_LIST[solidA],
							   SOLID_LIST[solidB])
				    );
	     }
	   else if(componentFirstRot==NULL && FirstPlacementPoint==0.0)
	     {
	       G4Transform3D transform((*componentRotation).invert(),PlacementPoint);
	       SOLID_LIST.push_back(new G4SubtractionSolid(name,
							   SOLID_LIST[solidA],
							   SOLID_LIST[solidB],
							   transform)
				    );

	     }
	   else G4Exception("Cant build subtraction solid properly");

	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"torus")))
	 {
	   G4Exception("Not coded torus yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"trd")))
	 {
	   G4Exception("Not coded trd yet");
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"union")))
	 {
	   G4Exception("Not coded union yet");
	 }

       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"polycone")))
	 {
	   xmlNodePtr tempcur = cur->xmlChildrenNode;

	   G4int numZPlanes = 0;
	   while(tempcur!=NULL)
	     {
	       if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"zplane")))
		 numZPlanes++;
	       tempcur = tempcur->next;
	     }

	   G4double* zPlanes = NULL;
	   G4double* rInner = NULL;
	   G4double* rOuter = NULL;
	   zPlanes = new G4double[numZPlanes];
	   rInner = new G4double[numZPlanes];
	   rOuter = new G4double[numZPlanes];

	   tempcur = cur->xmlChildrenNode;
	   G4int i=0;
	   while(tempcur!=NULL)
	     {
	       if ((!xmlStrcmp(tempcur->name, (const xmlChar *)"zplane")))
		 {
		   zPlanes[i] = parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"z"));
		   rInner[i] = parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"rmin"));
		   rOuter[i] = parseDblChar(xmlGetProp(tempcur,(const xmlChar*)"rmax"));
		   i++;
		 }
	       tempcur = tempcur->next;
	     }

	   SOLID_LIST.push_back(new G4Polycone((parseStrChar(xmlGetProp(cur,(const xmlChar*)"name"))),
					       parseDblChar(xmlGetProp(cur,(const xmlChar*)"startphi")),
					       parseDblChar(xmlGetProp(cur,(const xmlChar*)"deltaphi")),
					       numZPlanes,
					       zPlanes,
					       rInner,
					       rOuter)
				);

	   delete [] rInner;
	   rInner = NULL;
	   delete [] rOuter;
	   rOuter = NULL;
	   delete [] zPlanes;
	   zPlanes = NULL;
	 }
	   
       cur = cur->next;
     }
  
  return;
}

void BDSGeometryGDML::parseVOLUME(xmlDocPtr doc, xmlNodePtr cur)
{
  G4String volume_name = parseStrChar(xmlGetProp(cur,(const xmlChar*)"name"));
  cur = cur->xmlChildrenNode;

  G4String materialref;
  G4String solidref;
  G4String visref;
  xmlNodePtr origcur = cur;
  while (cur != NULL)
     {
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"materialref")))
	 {
	   materialref = parseStrChar(xmlGetProp(cur,(const xmlChar*)"ref"));
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"solidref")))
	 {
	   solidref = parseStrChar(xmlGetProp(cur,(const xmlChar*)"ref"));  
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"visref")))
	 {
	   visref = parseStrChar(xmlGetProp(cur,(const xmlChar*)"ref"));  
	 }
       
       cur = cur->next;
     }

  if(materialref!="" && solidref!="")
    {
      if(volume_name!="MARKER")
	{
	  G4String::caseCompare cmpmode = G4String::ignoreCase;
	  G4int ID = -1;
	  G4int i;
	  for(i=0; i<(G4int)SOLID_LIST.size(); i++)
	    {
	      G4String tempname1 = SOLID_LIST[i]->GetName();
	      if(tempname1.compareTo(solidref,cmpmode)==0)
		{
		  ID=i;
		  break;
		}
	    }
	  if(ID==-1) // couldn't find it.
	    {
	      G4cout << "Couldn't find solidref: " << solidref<<G4endl;
	      G4Exception("Quitting in BDSGeometryGDML LogVol building");
	    }
	  // TEMP 
	  materialref="iron";
	  G4LogicalVolume* alogvol = new G4LogicalVolume(SOLID_LIST[ID],
							 theMaterials->GetMaterial(materialref),
							 volume_name);
	  
	  LOGVOL_LIST.push_back(alogvol);
	  visRed+=1.0/SOLID_LIST.size();
	  //visGreen+=1.0/SOLID_LIST.size();
	  visGreen=0.5;
	  visBlue+=1.0/SOLID_LIST.size();
	  G4VisAttributes* VisAtt = 
	    new G4VisAttributes(G4Colour(visRed, visGreen, visBlue));
	  VisAtt->SetForceSolid(true);
	  alogvol->SetVisAttributes(VisAtt);
	}
      while(origcur!=NULL)
	{
	  if ((!xmlStrcmp(origcur->name, (const xmlChar *)"physvol")))
	    {
	      parsePHYSVOL(doc,origcur, volume_name);
	    }
	  origcur = origcur->next;
	}
    }
  else
    {
      G4cout << "Can't build" << volume_name << " : " << solidref << G4endl;
      G4Exception();
    }
  

  
  return;
}

void BDSGeometryGDML::parsePHYSVOL(xmlDocPtr doc, xmlNodePtr cur, G4String volume_name)
{
  cur = cur->xmlChildrenNode;

  G4String volumeref;
  G4String positionref;
  G4String rotationref;
  G4String position_name;
  G4double position_x;
  G4double position_y;
  G4double position_z;
  G4double position_unit;
  G4String position_type;
  G4String rotation_name;
  G4double rotation_x;
  G4double rotation_y;
  G4double rotation_z;
  G4double rotation_unit;
  G4String rotation_type;

  G4RotationMatrix* componentRotation = NULL;
  
  G4ThreeVector PlacementPoint;


  while (cur != NULL)
     {
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"volumeref")))
	 {
	   volumeref = parseStrChar(xmlGetProp(cur,(const xmlChar*)"ref"));
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"positionref")))
	 {
	   positionref = parseStrChar(xmlGetProp(cur,(const xmlChar*)"ref"));
	   G4int i;
	   for(i=0; i<(G4int)POS_LIST.size();i++)
	     {
	       if(POS_LIST[i].name==positionref)
		 {
		   PlacementPoint = POS_LIST[i].value;
		   break;
		 }
	     }
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
	 {
	   position_name = parseStrChar(xmlGetProp(cur,(const xmlChar*)"name"));	   
	   position_x = parseDblChar(xmlGetProp(cur,(const xmlChar*)"x"));	   
	   position_y = parseDblChar(xmlGetProp(cur,(const xmlChar*)"y"));	   
	   position_z = parseDblChar(xmlGetProp(cur,(const xmlChar*)"z"));	
	   position_unit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"unit"));	   
	   position_type = parseStrChar(xmlGetProp(cur,(const xmlChar*)"type"));	   
	   PlacementPoint = G4ThreeVector(position_x, position_y, position_z);
	   if(position_unit!=0) PlacementPoint*=position_unit;
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotationref")))
	 {
	   rotationref = parseStrChar(xmlGetProp(cur,(const xmlChar*)"ref"));
	   G4int i;
	   for(i=0; i<(G4int)ROT_LIST.size();i++)
	     {
	       if(ROT_LIST[i].name==rotationref)
		 {
		   componentRotation = RotateComponent(ROT_LIST[i].value);
		   break;
		 }
	     }
	 }
       else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
	 {
	   rotation_name = parseStrChar(xmlGetProp(cur,(const xmlChar*)"name"));	   
	   rotation_x = parseDblChar(xmlGetProp(cur,(const xmlChar*)"x"));	   
	   rotation_y = parseDblChar(xmlGetProp(cur,(const xmlChar*)"y"));	   
	   rotation_z = parseDblChar(xmlGetProp(cur,(const xmlChar*)"z"));	   
	   rotation_unit = parseDblChar(xmlGetProp(cur,(const xmlChar*)"unit"));	   
	   rotation_type = parseStrChar(xmlGetProp(cur,(const xmlChar*)"type"));	   
	   G4ThreeVector rotvect = G4ThreeVector(rotation_x, rotation_y, rotation_z);
	   if(rotation_unit!=0) rotvect*=rotation_unit;
	   componentRotation = RotateComponent(rotvect);
	 }
       cur = cur->next;
     }

  G4String::caseCompare cmpmode = G4String::ignoreCase;
  G4int ID = -1;
  G4int i;
  for(i=0; i<(G4int)LOGVOL_LIST.size(); i++)
    {
      G4String tempname = LOGVOL_LIST[i]->GetName();
      if(tempname.compareTo(volumeref,cmpmode)==0)
	{
	  ID=i;
	  break;
	}
    }
  if (ID==-1)
    {
      G4cout << "Unable to locate volume: " << volumeref << G4endl;
      G4Exception("Check volumes references");
    }
  G4int PARENTID = -1;
  for(i=0; i<(G4int)LOGVOL_LIST.size(); i++)
    {
      G4String tempname = LOGVOL_LIST[i]->GetName();
      if(tempname.compareTo(volume_name,cmpmode)==0)
	{
	  PARENTID=i;
	  break;
	}
    }
  G4LogicalVolume* parentVol = NULL;
  if (PARENTID==-1) parentVol = itsMarkerVol;
  else parentVol = LOGVOL_LIST[PARENTID];

  new G4PVPlacement(componentRotation,
		    PlacementPoint,
		    LOGVOL_LIST[ID],
		    LOGVOL_LIST[ID]->GetName()+"_PhysiComp",
		    parentVol,
		    false,
		    0);
  

  return;
}

 G4RotationMatrix* BDSGeometryGDML::RotateComponent(G4ThreeVector rotvalues)
{
  G4RotationMatrix *rotateComponent = new G4RotationMatrix;
  
  //Assuming order is rotate x, then y, then z;

  rotateComponent->rotateX(rotvalues.x());
  rotateComponent->rotateY(rotvalues.y());
  rotateComponent->rotateZ(rotvalues.z());
  
  
  return rotateComponent;
}

#endif
