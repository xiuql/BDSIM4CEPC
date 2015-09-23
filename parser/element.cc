#include "element.h"
#include "elementtype.h"
#include "parameters.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace GMAD;

namespace GMAD {
  extern std::string current_line;
}

namespace {
  // helper method
  void print(std::list<struct Element> l, int ident=0)
  {
    if(ident == 0) std::cout << "using line " << current_line << std::endl;
  
    for(std::list<struct Element>::iterator it=l.begin();it!=l.end();it++)
      {
	(*it).print(ident);
      }
  }
}

Element::Element():lst(nullptr) {
  flush();
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

  // new aperture model
  beampipeThickness = 0;
  aper1 = 0;
  aper2 = 0;
  aper3 = 0;
  aper4 = 0;
  apertureType = "";
  beampipeMaterial = "";

  // magnet geometry
  magnetGeometryType  = "";
  outerMaterial = "";
  outerDiameter = 0;
  
  tilt = 0;
  xsize = 0;
  ysize = 0;
  r = 0;
  B = 0;
  phiAngleIn = 0;
  phiAngleOut = 0;
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

  knl.erase(knl.begin(),knl.end());
  ksl.erase(ksl.begin(),ksl.end());
  blmLocZ.erase(blmLocZ.begin(), blmLocZ.end());
  blmLocTheta.erase(blmLocTheta.begin(), blmLocTheta.end());

  bias = "";
  
  precisionRegion = 0;

  A = 0;
  Z = 0;
  density = 0;      //g*cm-3
  temper = 300;     //kelvin
  pressure = 0;     //atm
  state = "solid";  //allowed values: "solid", "liquid", "gas"
  symbol = "";

  components.erase(components.begin(),components.end());
  componentsFractions.erase(componentsFractions.begin(),componentsFractions.end());
  componentsWeights.erase(componentsWeights.begin(),componentsWeights.end());

  geometryFile ="";
  bmapFile = "";
  material="";  
  windowmaterial = "vacuum";
  scintmaterial = "";
  airmaterial="";
  spec = "";
}

double Element::property_lookup(std::string property_name)const{
  if(property_name == "l") return l;
  if(property_name == "bmapZOffset") return bmapZOffset;
  if(property_name == "B") return B;
  if(property_name == "ks") return ks;
  if(property_name == "k0") return k0;
  if(property_name == "k1") return k1;
  if(property_name == "k2") return k2;
  if(property_name == "k3") return k3;
  if(property_name == "k4") return k4;
  if(property_name == "angle") return angle;
  if(property_name == "phiAngleIn") return phiAngleIn;
  if(property_name == "phiAngleOut") return phiAngleOut;
  if(property_name == "beampipeThickness") return beampipeThickness;
  if(property_name == "aper") return aper1;
  if(property_name == "aper1") return aper1;
  if(property_name == "aper2") return aper2;
  if(property_name == "aper3") return aper3;
  if(property_name == "aper4") return aper4;
  if(property_name == "outerDiameter") return outerDiameter;
  if(property_name == "boxSize") return outerDiameter;
  if(property_name == "outR") return 0.5*outerDiameter;
  if(property_name == "xsize") return xsize;
  if(property_name == "ysize") return ysize;
  if(property_name == "xdir") return xdir;
  if(property_name == "ydir") return ydir;
  if(property_name == "zdir") return zdir;
  if(property_name == "phi") return phi;
  if(property_name == "psi") return psi;
  if(property_name == "theta") return theta;
  if(property_name == "waveLength") return waveLength;
  if(property_name == "tilt") return tilt;
  if(property_name == "offsetX") return offsetX;
  if(property_name == "offsetY") return offsetY;
  if(property_name == "gradient") return gradient;

  if(property_name == "A") return A;
  if(property_name == "Z") return Z;
  if(property_name == "density") return density;
  if(property_name == "T") return temper;
  if(property_name == "P") return pressure;

  std::cerr << "element.cc> Error: unknown property \"" << property_name << "\" (only works on numerical properties)" << std::endl; 
  exit(1);
  //what about property_lookup for attributes of type string, like material?
}

void Element::set(const struct Parameters& params,std::string nameIn, ElementType typeIn, std::list<struct Element> *lstIn)
{
  type = typeIn;
  // common parameters for all elements
  name = nameIn;
  switch(type) {

  case ElementType::_LINE:
  case ElementType::_REV_LINE:
    lst = lstIn;
    break;
  default:
    break;
  }
  
  set(params);
}

void Element::set(const struct Parameters& params)
{
  // checks on setting of parameters needs to be done to allow for extension of already set Elements
  if(params.lset) l = params.l;

  //new aperture model
  if(params.aper1set) aper1 = params.aper1;
  if(params.aper2set) aper2 = params.aper2;
  if(params.aper3set) aper3 = params.aper3;
  if(params.aper4set) aper4 = params.aper4;
  if(params.apertureTypeset) apertureType = params.apertureType;
  if(params.beampipeMaterialset) beampipeMaterial = params.beampipeMaterial;

  //magnet geometry
  if(params.outerDiameterset) outerDiameter = params.outerDiameter;
  if(params.outerMaterialset) outerMaterial = params.outerMaterial;
  if(params.magnetGeometryTypeset) magnetGeometryType = params.magnetGeometryType;
  
  if(params.xsizeset) xsize = params.xsize;
  if(params.ysizeset) ysize = params.ysize;
  if(params.materialset) material = params.material;  
  if(params.precisionRegionset) precisionRegion = params.precisionRegion;

  if(params.offsetXset) offsetX = params.offsetX;
  if(params.offsetYset) offsetY = params.offsetY;
  // end of common parameters

  // specific parameters

  // for transform3ds, lasers and for tracker
  if(params.xdirset) xdir = params.xdir;
  if(params.ydirset) ydir = params.ydir;
  if(params.zdirset) zdir = params.zdir;

  if(params.biasset) bias = params.bias;
  
  // BLM
  if(params.blmLocZset)
    blmLocZ = params.blmLocZ;
  if(params.blmLocThetaset)
    blmLocTheta = params.blmLocTheta;

  // Drift
  if(params.phiAngleInset)
    phiAngleIn = params.phiAngleIn;
  if(params.phiAngleOutset)
    phiAngleOut = params.phiAngleOut;

  // Drift, Drift
  if(params.beampipeThicknessset)
    beampipeThickness = params.beampipeThickness;
  // RF
  if(params.gradientset)
    gradient = params.gradient;
  // SBend, RBend, (Awake)Screen
  if(params.angle)
    angle = params.angle;
  // SBend, RBend, HKick, VKick, Quad
  if(params.k1set)
    k1 = params.k1;
  // SBend, RBend, HKick, VKick, Solenoid, MuSpoiler
  if(params.Bset)
    B = params.B;
  // SBend, RBend, HKick, VKick, Quad, Sext, Oct, Mult
  if(params.tiltset) tilt = params.tilt;
  // Quad
  if(params.specset) spec = params.spec;
  // Sext
  if(params.k2set && type==ElementType::_SEXTUPOLE) k2 = params.k2;
  // Octupole
  if(params.k3set && type==ElementType::_OCTUPOLE) k3 = params.k3;
  // Decapole
  if(params.k4set && type==ElementType::_DECAPOLE) k4 = params.k4;
  
  // Multipole
  if(params.knlset)
    knl = params.knl;
  if(params.kslset)
    ksl = params.ksl;
  // Solenoid
  if(params.ksset) ks = params.ks;
  // Laser
  if(params.waveLengthset) waveLength = params.waveLength;
  // Element, Tunnel
  if(params.geometryFileset) geometryFile = params.geometryFile;
  // Element
  if(params.bmapFileset) bmapFile = params.bmapFile;
  if(params.bmapZOffsetset)
    bmapZOffset = params.bmapZOffset;
  // Transform3D
  if(params.thetaset) theta = params.theta;
  if(params.phiset)   phi = params.phi;
  if(params.psiset)   psi = params.psi;
  // (Awake) Screen
  if(params.tscintset) tscint = params.tscint;
  if(params.scintmaterialset) scintmaterial = params.scintmaterial;
  // Screen
  if(params.airmaterialset) airmaterial = params.airmaterial;
  // AwakeScreen
  if(params.twindowset) twindow = params.twindow;
  if(params.windowmaterialset) windowmaterial = params.windowmaterial;

  // overwriting of other parameters or specific printing
  switch(type) {

  case ElementType::_MATERIAL:
    if(params.Aset) A = params.A;
    if(params.Zset) Z = params.Z;
    if(params.densityset) density = params.density;
    if(params.temperset) temper = params.temper;
    if(params.pressureset) pressure = params.pressure;
    if(params.stateset) state = params.state;
    if(params.componentsset) components = params.components;
    if(params.componentsWeightsset) componentsWeights = params.componentsWeights;
    if(params.componentsFractionsset) componentsFractions = params.componentsFractions;
    break;
    
  case ElementType::_ATOM:
    if(params.Aset) A = params.A;
    if(params.Zset) Z = params.Z;
    if(params.symbolset) symbol = params.symbol;
    break;
    
  case ElementType::_AWAKESCREEN:
    std::cout << "scintmaterial: " << scintmaterial << " " <<  params.scintmaterial << std::endl;
    std::cout << "windowmaterial: " << windowmaterial << " " <<  params.windowmaterial << std::endl;
    break;

  default:
    break;
  }
}
