#include "element.h"
#include "elementtype.h"
#include "parameters.h"
#include "parser.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace GMAD;

namespace {
  // helper method
  void print(std::list<Element> l, int ident=0)
  {
    if(ident == 0) std::cout << "using line " << Parser::Instance()->current_line << std::endl;
  
    for(std::list<Element>::iterator it=l.begin();it!=l.end();it++)
      {
	(*it).print(ident);
      }
  }
}

Element::Element():lst(nullptr) {
  flush();

  PublishMembers();
}

void Element::PublishMembers()
{
  publish("l",&Element::l);
  publish("bmapZOffset",&Element::bmapZOffset);
  publish("B",&Element::B);
  publish("ks",&Element::ks);
  publish("k0",&Element::k0);
  publish("k1",&Element::k1);
  publish("k2",&Element::k2);
  publish("k3",&Element::k3);
  publish("k4",&Element::k4);
  publish("angle",&Element::angle);
  publish("beampipeThickness",&Element::beampipeThickness);
  publish("aper",&Element::aper1);
  alternativeNames["aper"] = "aper1";
  publish("aperture",&Element::aper1);
  alternativeNames["aperture"] = "aper1";
  publish("aper1",&Element::aper1);
  publish("aperture1",&Element::aper1);
  alternativeNames["aperture1"] = "aper1";
  publish("aper2",&Element::aper2);
  publish("aperture2",&Element::aper2);
  alternativeNames["aperture2"] = "aper2";
  publish("aper3",&Element::aper3);
  publish("aperture3",&Element::aper3);
  alternativeNames["aperture3"] = "aper3";
  publish("aper4",&Element::aper4);
  publish("aperture4",&Element::aper4);
  alternativeNames["aperture4"] = "aper4";
  publish("outerDiameter",&Element::outerDiameter);
  //  publish("outR",2*&Element::outerDiameter);
  publish("xsize",&Element::xsize);
  publish("ysize",&Element::ysize);
  publish("xsizeOut",&Element::xsizeOut);
  publish("ysizeOut",&Element::ysizeOut);
  publish("r",&Element::r);
  publish("tilt",&Element::tilt);
  publish("e1",&Element::e1);
  publish("e2",&Element::e2);
  publish("offsetX",&Element::offsetX);
  publish("offsetY",&Element::offsetY);
  publish("x",&Element::xdir);
  alternativeNames["x"] = "xdir";
  publish("y",&Element::ydir);
  alternativeNames["y"] = "ydir";
  publish("z",&Element::zdir);
  alternativeNames["z"] = "zdir";
  publish("xdir",&Element::xdir);
  publish("ydir",&Element::ydir);
  publish("zdir",&Element::zdir);
  publish("phi",&Element::phi);
  publish("theta",&Element::theta);
  publish("psi",&Element::psi);
  publish("gradient",&Element::gradient);
  publish("precisionRegion",&Element::precisionRegion);
  publish("region",&Element::region);
  publish("A",&Element::A);
  publish("Z",&Element::Z);
  publish("density",&Element::density);
  publish("T",&Element::temper);
  publish("P",&Element::pressure);
  publish("waveLength",&Element::waveLength);
  publish("tscint",&Element::tscint);
  publish("twindow",&Element::twindow);
  publish("numberWedges",&Element::numberWedges);
  publish("wedgeLength",&Element::wedgeLength);
  publish("degraderHeight",&Element::degraderHeight);
  publish("materialThickness",&Element::materialThickness);
  publish("degraderOffset",&Element::degraderOffset);

  publish("geometry",&Element::geometryFile);
  publish("bmap",&Element::bmapFile);
  publish("outerMaterial",&Element::outerMaterial);
  publish("material",&Element::material);
  publish("apertureType",&Element::apertureType);
  publish("magnetGeometryType",&Element::magnetGeometryType);
  publish("beampipeMaterial",&Element::beampipeMaterial);
  publish("vacuumMaterial",&Element::vacuumMaterial);
  publish("scintmaterial",&Element::scintmaterial);
  publish("windowmaterial",&Element::windowmaterial);
  publish("airmaterial",&Element::airmaterial);
  publish("spec",&Element::spec);
  publish("cavityModel",&Element::cavityModel);
  publish("state",&Element::state);
  publish("symbol",&Element::symbol);
  publish("bias",&Element::bias);
  publish("biasMaterial",&Element::biasMaterial);
  publish("biasVacuum",&Element::biasVacuum);

  publish("knl",&Element::knl);
  publish("ksl",&Element::ksl);
  publish("blmLocZ",&Element::blmLocZ);
  publish("blmLocTheta",&Element::blmLocTheta);
  publish("components",&Element::components);
  publish("componentsWeights",&Element::componentsWeights);
  publish("componentsFractions",&Element::componentsFractions);
}

std::string Element::getPublishedName(std::string name)const
{
  auto it = alternativeNames.find(name);
  if (it != alternativeNames.end()) {
    return it->second;
  }
  // if not found return name
  return name;
}

bool Element::isSpecial()const {
  bool isSpecial = false;

  if (type == ElementType::_SAMPLER ||
      type == ElementType::_CSAMPLER ||
      type == ElementType::_DUMP ||
      type == ElementType::_TRANSFORM3D ||
      type == ElementType::_MARKER ||
      type == ElementType::_LINE ||
      type == ElementType::_REV_LINE ||
      type == ElementType::_MATERIAL ||
      type == ElementType::_ATOM)
    {isSpecial = true;}

  return isSpecial;
}

void Element::print(int & ident)const{
  for(int i=0;i<ident;i++)
    printf("--");

  std::cout << "->" << name << " : " << type << std::endl;

  std::list<double>::const_iterator it;
  switch(type) {
  case ElementType::_DRIFT:
  case ElementType::_SBEND:
  case ElementType::_RBEND:
  case ElementType::_QUAD:
  case ElementType::_SEXTUPOLE:
  case ElementType::_OCTUPOLE:
  case ElementType::_DECAPOLE:
    printf(", l=%.10g, k0=%.10g, k1=%.10g, k2=%.10g, k3=%.10g, k4=%.10g, angle=%.10g,tilt=%.10g ",
	   l,k0,k1,k2,k3,k4,angle,tilt);
    break;
    
  case ElementType::_SOLENOID:
    printf(", l=%.10g, ks=%.10g ", l, ks);
    break;
    
  case ElementType::_MULT:
    printf(" , knl={");
    for(it=knl.begin();it!=knl.end();++it)
      printf("%.10g, ",(*it));
    printf("},  ksl={");
    for(it=ksl.begin();it!=ksl.end();++it)
      printf("%.10g, ",(*it));
    printf("}");
    break;
    
  case ElementType::_ELEMENT:
    printf("\ngeometry file : %s\n",geometryFile.c_str());
    printf("B map file : %s\n",bmapFile.c_str());
    break;
    
  case ElementType::_SCREEN:
    break;
    
  case ElementType::_CSAMPLER:
    printf(" length=%.10g, radius=%.10g",l, r);
    break;
    
  case ElementType::_TRANSFORM3D:
    printf(" xdir=%.10g, ydir=%.10g, zdir=%.10g,  phi=%.10g, theta=%.10g,psi=%.10g",
	   xdir, ydir, zdir, phi, theta, psi);
    break;
  case ElementType::_MATERIAL:
    printf(" A=%.10g, Z=%.10g, density=%.10g,  temper=%.10g, pressure=%.10g",
	   A, Z, density, temper, pressure);
    break;
  default:
    break;
  }
  
  printf("\n");
  
  if(lst != nullptr)
    {
      ::print(*lst,++ident);
      ident--;
    }
}

void Element::flush() {
  type = ElementType::_NONE;
  name = "";
  l = 0;
  ks = 0;
  k0 = 0;
  k1 = 0;
  k2 = 0;
  k3 = 0;
  k4 = 0;
  angle = 0;
  
  // degrader
  numberWedges = 1;
  wedgeLength = 0;
  degraderHeight = 0;
  materialThickness = 0;
  degraderOffset = 0;

  // new aperture model
  beampipeThickness = 0;
  aper1 = 0;
  aper2 = 0;
  aper3 = 0;
  aper4 = 0;
  apertureType = "";
  beampipeMaterial = "";
  vacuumMaterial = "";

  // magnet geometry
  magnetGeometryType  = "";
  outerMaterial = "";
  outerDiameter = 0;
  
  tilt = 0;
  xsize = 0;
  ysize = 0;
  xsizeOut = 0;
  ysizeOut = 0;
  r = 0;
  B = 0;
  e1 = 0;
  e2 = 0;
  offsetX = 0;
  offsetY = 0;
  tscint = 0.0003;
  twindow = 0;
  bmapZOffset = 0;
  xdir = 0;
  ydir = 0;
  zdir = 0;
  waveLength = 0;
  gradient = 0;
  phi = 0;
  theta = 0;
  psi = 0;

  knl.clear();
  ksl.clear();
  blmLocZ.clear();
  blmLocTheta.clear();

  bias = ""; biasMaterial=""; biasVacuum="";
  biasMaterialList.clear();
  biasVacuumList.clear();
  
  precisionRegion = 0;
  region = "";
  
  A = 0;
  Z = 0;
  density = 0;      //g*cm-3
  temper = 300;     //kelvin
  pressure = 0;     //atm
  state = "solid";  //allowed values: "solid", "liquid", "gas"
  symbol = "";

  components.clear();
  componentsFractions.clear();
  componentsWeights.clear();

  geometryFile ="";
  bmapFile = "";
  material="";  
  windowmaterial = "vacuum";
  scintmaterial = "";
  airmaterial="";
  spec = "";
  cavityModel = "";
}

double Element::property_lookup(std::string property_name)const{
  if(property_name == "outR") return 0.5*outerDiameter;

  double value;
  try {
    value = get<double>(this,property_name);
  }
  catch (std::runtime_error) {
    std::cerr << "element.cc> Error: unknown property \"" << property_name << "\" (only works on numerical properties)" << std::endl; 
    exit(1);
  }
  return value;
}

void Element::set(const Parameters& params,std::string nameIn, ElementType typeIn)
{
  // common parameters for all elements
  type = typeIn;
  name = nameIn;
  
  set(params);
}

void Element::set(const Parameters& params)
{
  for (auto& i : params.setMap)
    {
      if(i.second == true)
	{
	  std::string property = i.first;

	  Published<Element>::set(this,(Element*)&params,property);

	  // split bias into tokens and add to both material and vacuum
	  if (property == "bias")
	    {
	      std::stringstream ss(bias);
	      std::string tok;
	      while(ss >> tok)
		{
		  biasMaterialList.push_back(tok);
		  biasVacuumList.push_back(tok);
		}
	    }
	  else if (property == "biasMaterial")
	    {
	      std::stringstream ss(biasMaterial);
	      std::string tok;
	      while(ss >> tok) {biasMaterialList.push_back(tok);}
	    }
	  else if (property == "biasVacuum")
	    {
	      std::stringstream ss(biasVacuum);
	      std::string tok;
	      while(ss >> tok) {biasVacuumList.push_back(tok);}
	    }
	}
    }
}
