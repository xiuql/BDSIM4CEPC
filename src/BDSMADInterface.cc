/** BDSIM code.    Version 1.0
 *   @Author: Grahame A. Blair, Royal Holloway, Univ. of London.
 *  Last modified 24.7.2002
 *  @Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// This code was modifed by G.Blair from an original Merlin
// routine of N.Walker:

/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file Merlin\MADInterface\MADInterface.cpp
 * last modified 11/07/00 20:43:06
 */
/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * MERLIN C++ class library for 
 * Charge Particle Accelerator Simulations
 * Copyright (c) 1999 by N.J.Walker.  ALL RIGHTS RESERVED. 
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * No representations about the suitability of this software for
 * any purpose is made. It is provided "as is" without express
 * or implied warranty.
 */
#include "BDSGlobalConstants.hh" // must be first in include list

#include <cstdlib>
#include "BDSSectorBend.hh"
#include "BDSQuadrupole.hh"
#include "BDSDrift.hh"
#include "BDSSkewSextupole.hh"
#include "BDSSextupole.hh"
#include "BDSOctupole.hh"
#include "BDSDecapole.hh"
#include "BDSKiller.hh"
#include "BDSSampler.hh"
#include "BDSSpoiler.hh"
#include "BDSAbsorber.hh"
#include "BDSLaserWire.hh"
#include "BDSLWCalorimeter.hh"


#include "BDSMaterials.hh"

#include "BDSMADInterface.hh"

using namespace std;


#include"globals.hh"

#include<string>
#include<stack>

extern BDSMaterials* theMaterials;

extern G4Material* SpoilerMaterial;
extern G4double NumSpoilerRadLen;

//--------------------------
// process options
// BDSLaserWire* TheBDSLaserWire;
//--------------------------


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

void StripHeader(istream& is)
{
  // Need to read the first 13 lines from the optics file
  char buffer[256];
  for(int i=0; i<13; i++)
    is.getline(buffer,256);
}

inline G4String StripQuotes(const G4String& text)
{
  return text.substr(1,text.length()-2);
}


// Class MADInterface 

BDSMADInterface::BDSMADInterface (const G4String& madFileName,G4double P0)
  : ifs(madFileName.c_str()),log(&G4cout)
  // brho is the radius of curvature * B-field
{
  brho=
    sqrt(pow(P0,2)- pow(electron_mass_c2,2))/(0.299792458 * (GeV/(tesla*m)));
  assert(ifs);

  //  if(BDSGlobals->GetSynchRadOn())
  //{
  //      synch_file.open("synch_factors.dat");
  //}
  synch_factor=1.;
  E_Synch=BDSGlobals->GetAcceleratorType()->GetBeamTotalEnergy();


  G4cout<<"MAD Optics Filename="<<madFileName<<G4endl;
}

BDSBeamline BDSMADInterface::ConstructModel ()
{
  //  ofstream madlog("construction.log");
  
  ctor = new BDSBeamline;
  G4double z=0.0;

  // reset the stream pointer
  ifs.seekg(0);
  StripHeader(ifs);
  
  while(ifs) z+=ReadComponent();
  return *ctor;
}

BDSMADInterface::~BDSMADInterface()
{
  if(ctor) delete ctor;
}

G4double BDSMADInterface::ReadComponent ()
{
#define  _READ(value) if(!(ifs>>value)) return 0;

  G4String name,type,aptype;
  G4double len,s,angle,k1,k2,k3,k4,tilt;
  
  BDSGlobals->GetAcceleratorType()->GetBeamTotalEnergy();

  _READ(name);
  _READ(type);
  _READ(s);
  _READ(len);
  _READ(angle);
  _READ(k1);
  _READ(k2);
  _READ(k3);
  _READ(k4);
  _READ(tilt);
  _READ(aptype);

  if(len<0)G4Exception("BDSMADInterface: Negative length component!");

  //  G4cout<<name<<" "<<type<<" "<<s<<" "<<len<<" "<<angle<<" "<<k1<<" "<<
  //   k2<<" "<<k3<<" "<<k4<<" "<<tilt<<" "<<aptype<<G4endl;
	
  name=StripQuotes(name);

  type=StripQuotes(type);
  aptype=StripQuotes(aptype);


  // gab:
  if(len<=0&&aptype=="~")return 0;

  // input units are SI:
  angle*=radian;
  s*=m;
  len*=m;

  // needed for ATF deck:
  if(type=="SBEND"&&(angle==0))type="DRIFT";

  //  if(type=="SBEND")type="DRIFT";

  //if(type=="QUADRUPOLE")type="DRIFT";
  if(type=="SKEWQUAD")type="DRIFT";
  //if(type=="SEXTUPOLE")type="DRIFT";
  //if(type=="SKEWSEXT")type="DRIFT";
  //if(type=="OCTUPOLE")type="DRIFT";

  //  if(type=="MULTIPOLE")type="DECAPOLE";
  // tmp !! this must be changed once the nlc decapole lengths are known.
  
  if(type=="MULTIPOLE")return 0;

  if( (type=="HKICKER"||type=="VKICKER") && (len > 0 )  ) type = "DRIFT";

  //  G4cout<<type<<" name="<<name<<" s="<<s/m<<"typ="<<aptype<<G4endl;
  //  G4cout<<type<<" len ="<<len<<" angle="<<angle<<"k1="<<k1<<G4endl;

  if(BDSGlobals->GetSynchRadOn()&& BDSGlobals->GetSynchRescale())
    {
      G4double deltaE;
      //synch_file>>deltaE;
      //      synch_factor-=deltaE*GeV/
      // rather than use the file, calculate theoretical value for sbends:
      // Synch energy loss:

      if(angle!=0)
	{
	  G4double R=abs(len/angle);
	  deltaE=(0.0884627*pow(E_Synch/GeV,4)/(R/m))*abs(angle)/(2*pi)*MeV;
	  G4cout<<"deltaE="<<deltaE/GeV<<G4endl;
	  E_Synch-=deltaE;
	  synch_factor=(E_Synch+0.5*deltaE)/ // 0.5 factor for average loss
	    BDSGlobals->GetAcceleratorType()->GetBeamTotalEnergy();
	  G4cout<<" synch_factor="<<synch_factor <<G4endl;
	}	  
    }


  G4double xAper=0,yAper=0, bpRad=BDSGlobals->GetBeampipeRadius();
  G4double LCBeampipeThickness=BDSGlobals->GetBeampipeThickness();


  // Inner radius of outer iron structure:
  G4double FeRad=bpRad;

  if(aptype!="~")
    {
      if(aptype.substr(0,1)=="D")
	{
	  FeRad=atof((aptype.substr(1,aptype.length()-1)).c_str())*mm/2
	    +BDSGlobals->GetBeampipeThickness();
	  bpRad=FeRad;
	    // if(FeRad<bpRad)
	    // bpRad=FeRad+BDSGlobals->GetBeampipeThickness();
	}         
      else if(aptype.substr(0,1)=="H")
	{
	  FeRad=atof((aptype.substr(1,aptype.length()-1)).c_str())*mm/2
	    +BDSGlobals->GetBeampipeThickness();
	  //if(FeRad<bpRad)bpRad=FeRad+BDSGlobals->GetBeampipeThickness();
	  bpRad=FeRad;
	}   
      else
	{
	  int iY=aptype.find("Y");
	  xAper=atof(aptype.substr(1,iY-1).c_str()) * mm;
	  yAper=atof(aptype.substr(iY+1,aptype.length()-1).c_str()) * mm;
	  // need to divide by two because the apertures quoted in
	  
	  // the optics file are the total length (equivalent to
	  // the diameter for circular apertures)
	  xAper/=2.;
	  yAper/=2.;
	  G4double rMin=sqrt(pow(xAper,2)+pow(yAper,2))+LCBeampipeThickness;
	  if(rMin>=bpRad)bpRad=rMin;
	}
    }


  /*
  // Determine the length actually containing magnetic field for the
  // model of sector bends employed here:
  G4double sFld=len;
  // determine how many straight beampipes are required so that
  // max offset of central orbit from centre of beampipe is 1 mm:
  G4int nSegments=int(abs(angle/2)/acos(1.-1.*mm*abs(angle)/len));
  if(nSegments<1) nSegments = 1;
  G4double bField=0.;
  if(angle!=0)
    {
      G4double dSegments=double(nSegments);
      G4double SegAng=abs(angle)/dSegments;
      G4double SegLen=(len/dSegments)*sin(SegAng)/SegAng;
      G4double FldL = SegLen - 2.*bpRad*tan(SegAng/2);
      sFld=FldL*SegAng/sin(SegAng);
      bField= brho*SegAng/sFld*synch_factor;
    }

  */
  G4double bField= brho*angle/len*synch_factor;

  G4double bPrime=brho*k1/len/m*synch_factor;;
  // minus sign needed to conform to Machine conventions
  // ie need a pi rotation about z  - only affects even-order poles
  G4double bDoublePrime=brho*k2/len/(m*m)*synch_factor;;
  G4double bTriplePrime=brho*k3/len/(m*m*m)*synch_factor;;
  G4double bQuadPrime  =brho*k4/len/(m*m*m*m)*synch_factor;;


  //if( (type=="MARKER")&&(aptype!="~") )
  //  {
  //    type="SPOILER";
  //    //      len= NumSpoilerRadLen *SpoilerMaterial->GetRadlen();
  //  }

  if( (name=="ENGYSP")||(name=="ESPOI")||(name=="XYSPOI")||
      (name=="COLX")||(name=="COLY")||
      (name=="XSP1")||(name=="XSP2")||(name=="XSP3")||(name=="XSP4")||
      (name=="YSP1")||(name=="YSP2")||(name=="YSP3")||(name=="YSP4"))
      type="SPOILER";

  if( (name=="ENGYAB")||
      (name=="XAB1")||(name=="XAB2")||(name=="XAB3")||(name=="XAB4")||
      (name=="YAB1")||(name=="YAB2")||(name=="YAB3")||(name=="YAB4")||
      (name=="PC") )
      type="ABSORBER";


  if( (type=="DRIFT")&&( (xAper!=0)||(yAper!=0)) ) {type="ABSORBER";}
  if( (type=="ABSORBER")&&( (xAper==0)&&(yAper==0)) ) {type="DRIFT";}

  // tmp:
  //if((type=="ABSORBER")||(type=="SPOILER"))type="DRIFT";

  //G4cout<<"type="<<type<<G4endl;




  if(type=="DRIFT"){
    //G4cout<<"adding drift "<<name<<" len="<<len<<" bpRad="<<bpRad<<endl;
    ctor->push_back(new BDSDrift(name,len,bpRad));
  }

  else if(type=="QUADRUPOLE")
    ctor->push_back(new BDSQuadrupole(name,len,bpRad,FeRad,bPrime));
  //  else if(type=="SKEWQUAD") 
  //ctor->push_back(new BDSSkewQuadrupole(name,len,bPrime));
  else if(type=="SBEND")
    ctor->push_back(new BDSSectorBend(name,len,bpRad,FeRad,bField,angle));
  //    ctor->push_back(new BDSSectorBend(name,len,bpRad,FeRad,
  //			      bField,angle,nSegments));
  else if(type=="SEXTUPOLE") 
    ctor->push_back( new BDSSextupole(name,len,bpRad,FeRad,bDoublePrime));
  else if(type=="SKEWSEXT") 
    ctor->push_back(new BDSSkewSextupole(name,len,bpRad,FeRad,bDoublePrime));
  else if(type=="OCTUPOLE") 
    ctor->push_back(new BDSOctupole(name,len,bpRad,FeRad,bTriplePrime));
  else if(type=="DECAPOLE") 
    ctor->push_back(new BDSDecapole(name,len,bpRad,FeRad,bQuadPrime));
  else if(type=="SAMPLER")
    {
      ctor->push_back(new BDSSampler(name,len));
      G4cout<<"adding sampler "<<name<<" len="<<len<<endl;
    }
  else if(type=="KILLER")
    ctor->push_back(new BDSKiller(name,len));
  
  else if(type=="SPOILER")
    {
      G4cout<<"adding spoiler "<<name<<" len="<<len<<" bpRad="<<bpRad<<
	"  xAper="<<xAper<<"  yAper="<<yAper<<endl;
      ctor->push_back(new BDSSpoiler(name,len,bpRad,xAper,yAper,
				     SpoilerMaterial));
    }
  else if(type=="ABSORBER")
    ctor->push_back(new BDSAbsorber(name,len,bpRad,xAper,yAper,
				    theMaterials->LCCopper));
  else if(type=="LASERWIRE")
    {
      BDSLaserWire* TheBDSLaserWire=
	new BDSLaserWire(name,len,BDSGlobals->GetLaserwireWavelength(),
			 BDSGlobals->GetLaserwireDir());
      ctor->push_back(TheBDSLaserWire);
    }
  else if(type=="LWCAL")
    {
      ctor->push_back(new BDSLWCalorimeter(name,len,bpRad));
    }
  else if(len!=0)
    {
      G4cout<<" WARNING :  Component: "<<name<< " of unknown type "<<type<<G4endl;;
      //G4Exception(" MADInterface:Unknown beamline component");
    }
  return len;

}
}
