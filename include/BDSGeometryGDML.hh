/* * BDSIM code.    Version 1.0
   * Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   * Last modified 24.7.2002
   * Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 


   Author of this code: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 13.04.2005
*/

#ifdef USE_XML

#ifndef BDSGeometryGDML_h
#define BDSGeometryGDML_h 1

#include "globals.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"
#include "G4VSolid.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "BDSMySQLTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"
#include "BDSSamplerSD.hh"
#include <fstream>
#include <vector>
#include <map>
#include "BDSMagFieldSQL.hh"

// Headers required for XML parsing
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>


extern BDSMaterials* theMaterials;

using namespace std;

class BDSClassicalRK4;

struct POS_REF{
  G4String name;
  G4ThreeVector value;
};

struct ROT_REF{
  G4String name;
  G4ThreeVector value;
};

struct CONST_REF{
  G4String name;
  G4double value;
};

class BDSGeometryGDML
{
public:
  BDSGeometryGDML(G4String GDMLfile);
  ~BDSGeometryGDML();

  void parseDoc();
  void parseGDML(xmlDocPtr doc, xmlNodePtr cur);
  void parseDEFINE(xmlDocPtr doc, xmlNodePtr cur);
  void parseSOLID(xmlDocPtr doc, xmlNodePtr cur);
  void parseSTRUCTURE(xmlDocPtr doc, xmlNodePtr cur);
  void parseVOLUME(xmlDocPtr doc, xmlNodePtr cur);
  void parsePHYSVOL(xmlDocPtr doc, xmlNodePtr cur, G4String volume_name);

  G4RotationMatrix* RotateComponent(G4ThreeVector rotvalues);

  void Construct(G4LogicalVolume *marker);
  vector<G4LogicalVolume*> VOL_LIST;
  G4String parseStrChar(xmlChar* value);
  G4double parseDblChar(xmlChar* value);

  G4bool stripwhitespace(G4String& str);

  // used for parsing strings for math calculations
  G4bool EvaluateExpression(const char*, G4double& result);
  G4bool EvaluateTerm(const char* term, G4int termLength, G4double& result);
  G4bool VerifyExpression(const char*);
  G4bool VerifyNumber(const char*);
  G4bool StrToFloat(const char* str, G4int start, G4int end, G4double& f);
private:

  G4String itsGDMLfile;
  G4LogicalVolume* itsMarkerVol;
  vector <struct CONST_REF> CONST_LIST;
  vector <struct POS_REF> POS_LIST;
  vector <struct ROT_REF> ROT_LIST;
  vector <G4VSolid*> SOLID_LIST;
  vector <G4LogicalVolume*> LOGVOL_LIST;

  G4double visRed, visGreen, visBlue;


protected:
};
// simple casting - needed to suppress mulitple conversion warnings from gcc 3.3 and above compiler
// second function of this method is to check for constants in value and or numerical functions and do them

inline G4String BDSGeometryGDML::parseStrChar(xmlChar* value)
{
  if(value==NULL) return "";
  G4String val = G4String((char*)value);
  //G4cout << "strVAL: "<< val << G4endl;
  return val;
}

inline G4double BDSGeometryGDML::parseDblChar(xmlChar* value)
{
  if(value==NULL) return 0.0;
  G4String val = G4String((char*)value);
  stripwhitespace(val);
  //G4cout << "dblVAL: "<< val << G4endl;
  // now check for defined constants
  for(G4int i=0; i<CONST_LIST.size(); i++)
    {
      if(val.contains(CONST_LIST[i].name))
	{
	  //check that this is the entire constant, and not part of a larger name
	  // e.g "zpos" and "zpos_world"
	  G4int endpos = val.index(CONST_LIST[i].name)+(CONST_LIST[i].name).length();
	  G4int startpos = val.index(CONST_LIST[i].name);
	  G4bool replaceStr = false;
	  if(val==CONST_LIST[i].name) replaceStr = true;
	  
	  //check after string for math operators or end of string
	  else if((val.data()[endpos] == '+' ||
		   val.data()[endpos] == '-' ||
		   val.data()[endpos] == '*' ||
		   val.data()[endpos] == '/' ||
		   endpos>=val.length())     &&
		  (val.data()[startpos-1] == '+' ||
		   val.data()[startpos-1] == '-' ||
		   val.data()[startpos-1] == '*' ||
		   val.data()[startpos-1] == '/' ||
		   startpos-1<=0))
	    replaceStr = true;
 
	  // replace all instances of constant with value

	  if(replaceStr)
	    {
	      char constval[40];
	      sprintf(constval,"%f",CONST_LIST[i].value);
	      val.replace(val.index((CONST_LIST[i].name)), (CONST_LIST[i].name).length(), constval);
	      i=0;
	    }
	}
    }
  G4double dbl_val = 0.0;

  if(VerifyExpression(val)) EvaluateExpression(val.data(),dbl_val);
  else
    {
      G4cout << "Unable to evaluate expression: " << value << G4endl;
      G4Exception("Check spellings and that constants are declared properly");
    }
    
  return dbl_val;
}

inline G4bool BDSGeometryGDML::EvaluateExpression(const char* expr, G4double& result)
{

  G4int length = strlen(expr);
  G4int end = length-1;
  double term;
  result = 0.0;
  G4int i;
  for(i = length-1; i>=0; i--)
    {
      if(expr[i]=='+')
	{
	  if(!EvaluateTerm(expr + i + 1, end-i, term))
	    return false;
	  result += term;
	  end = i-1;
	}
      else if (expr[i] == '-')
	{
	  if(!EvaluateTerm(expr + i + 1, end-i, term))
	    return false;
	  result -= term;
	  end = i-1;	  
	}
    }
  
  if (expr[0] !='+' && expr[0]!='-')
    {
      if(!EvaluateTerm(expr, end+1, term))
	return false;
      result += term;
      end = i-1;	  
    }

  return true;

}

inline G4bool BDSGeometryGDML::EvaluateTerm(const char* term, G4int termLength, G4double& result)
{
  G4int end = termLength-1;
  result = 1.0;
  G4double number;
  G4int i;
  for (i = end ; i>=0; i--)
    {
      if(term[i] == '*')
	{
	  if(!StrToFloat(term+i+1, 0, end-i, number))
	    return false;
	  result *= number;
	  end = i-1;
	}
      else if(term[i] == '/')
	{
	  if(!StrToFloat(term+i+1, 0, end-i, number))
	    return false;
	  result /= number;
	  end = i-1;
	}
    }
  if (term[0] != '*' && term[0] != '/')
    {    
      if(!StrToFloat(term, 0, end+1, number))
	return false;
      result *= number;
    }
  return true;
}

inline G4bool BDSGeometryGDML::VerifyExpression(const char* expr)
{
  G4int length = strlen(expr);
  if(length==0) return false;
  G4int i;
  for (i=0; i<length; i++)
    {
      if(expr[i] >='0' && expr[i] <= '9')
	continue;
      else
	if (expr[i] == '+' || expr[i] =='-' || expr[i] =='*' ||
	    expr[i] == '/' || expr[i] =='.' || expr[i] =='e' ||
	    expr[i] == 'E' || expr[i] =='^')
	  continue;
	else return false;
    }
  return true;
}

inline G4bool BDSGeometryGDML::VerifyNumber(const char* expr)
{
  G4int length = strlen(expr);
  if(length==0) return false;
  G4int i;
  for (i=0; i<length; i++)
    {
      if(expr[i] >='0' && expr[i] <= '9')
	continue;
      else
	if (expr[i] =='.') continue;
	else return false;
    }
  return true;
}

inline G4bool BDSGeometryGDML::StrToFloat(const char* str, G4int start, G4int end, G4double& f)
{
  if(!str) return false;
  
  G4double factor=0.1;
  G4int i,j;
  for(i=start; i<end; i++)
    {

      if(str[i]=='.' && (str[i+1]=='e' || str[i]=='E' || str[i] =='^'))
	{
	  for(j= i+2; j< end; j++)
	    if(str[j] <'0' || str[j] >'9') return false;
	  break;
	}
      else if(str[i]=='.')
	{
	  for(j= i+1; j< end; j++)
	    if(str[j] <'0' || str[j] >'9') return false;
	  break;
	}
      else if(str[i] =='^')
	{
	  for(j= i+1; j< end; j++)
	    {
	      if(str[j] == '.') continue;
	      if(str[j] <'0' || str[j] >'9') return false;
	    }
	  break;
	}
      else if(str[i]=='e'  || str[i]=='E')
	{
	  for(j= i+1; j< end; j++)
	    if(str[j] <'0' || str[j] >'9') return false;
	  break;
	}
      else if(str[i] <'0' || str[i]>'9') return false;
      factor *=10;
    }
  
  f=0.0;
  for(i=start; i<end; i++)
    {
      if(str[i]=='.') continue;

      else if(str[i]=='e'  || str[i]=='E')
	{		
	  G4double f1 = 0.0;
	  G4double f2 = 0.0;
	  StrToFloat(str,0,i,f1);
	  StrToFloat(str,i+1,end,f2);
	  f = f1*pow(10,f2);
	}
      else if(str[i]=='^')
	{
	  G4double f1 = 0.0;
	  G4double f2 = 0.0;
	  StrToFloat(str,0,i,f1);
	  StrToFloat(str,i+1,end,f2);
	  f = pow(f1,f2);
	}

      else
	{
	  f+= (G4double)(str[i] - '0')*factor;
	  factor *= 0.1;
	}
    }
  return true;

}

inline G4bool BDSGeometryGDML::stripwhitespace(G4String& str)
{
  //return false if nothing done
  if(str.length()==0) return false;

  G4String newstr;

  str_size i;
  for(i=0;i<str.length();i++)
    {
      if(str[i] != ' ')
	newstr+=str[i];
    }

  str = newstr;
  return true;
}

#endif

#endif //from use_xml
