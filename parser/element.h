#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <list>
#include <map>
#include <string>

#include "published.h"

namespace GMAD {

  enum class ElementType;

  struct Parameters;
 
  /**
   * @brief Element class
   * 
   * @author I. Agapov
   */

  struct Element : public Published<Element>{
    ElementType type; ///< element enum
    std::string name;

    double l; ///< length in metres
    double ks; ///< solenoid
    double k0; ///< dipole
    double k1; ///< quadrupole
    double k2; ///< sextupole
    double k3; ///< octupole
    double k4; ///< decapole
    double angle; ///< bending angle

    ///@{ beampipe information, new aperture model
    double beampipeThickness;
    double aper1;
    double aper2;
    double aper3;
    double aper4;
    std::string apertureType;
    std::string beampipeMaterial;
    std::string vacuumMaterial;
    ///@}
  
    // magnet geometry
    std::string magnetGeometryType;
    std::string outerMaterial;
    double outerDiameter;

    double tilt; ///< tilt
    double xsize, ysize; ///< collimator aperture or laser spotsize for laser
    double xsizeOut, ysizeOut; ///< collimator aperture or laser spotsize for laser
    double r; ///< radius, i.e cylindrical sampler
    double B; ///< magnetic field
    double phiAngleIn; ///< incoming bending angle for element
    double phiAngleOut; ///< outgoing bending angle for element
    double offsetX; ///< offset X
    double offsetY; ///< offset Y
    double tscint; ///<thickness of scintillating part of screen
    double twindow; ///<thickness of window
    double bmapZOffset; ///< offset of the field map magnet field
    double xdir;
    double ydir;
    double zdir;
    double waveLength; ///< for laser wire and 3d transforms
    double gradient; ///< for rf cavities
    double phi, theta, psi; ///< for 3d transforms
    int numberWedges; ///< for degrader
    double wedgeLength; ///< for degrader
    double degraderHeight; ///< for degrader
    double materialThickness; ///< for degrader
    double degraderOffset; ///< for degrader

    std::list<double> knl; ///< multipole expansion coefficients
    std::list<double> ksl; ///< skew multipole expansion

    ///@{List of beam loss monitor locations
    std::list<double> blmLocZ;
    std::list<double> blmLocTheta;
    ///@}
  
    ///@{ temporary string for bias setting
    std::string bias;
    std::string biasMaterial;
    std::string biasVacuum;
    ///@}
    /// physics biasing list for the material
    std::list<std::string> biasMaterialList;
    /// physics biasing list for the vacuum
    std::list<std::string> biasVacuumList;
 
    int precisionRegion; ///<which precision physics region the element is in (0 = none)
    std::string region; ///< region with range cuts
    
    ///@{ material properties
    double A; ///< g*mol^-1
    double Z; 
    double density; ///< g*cm-3 
    double temper; ///< kelvin
    double pressure; ///< atm
    std::string state; ///< "solid", "liquid", or "gas"
    std::string symbol;
    std::list<std::string> components;
    std::list<double> componentsFractions;
    std::list<int> componentsWeights;
    ///@}
  
    std::string geometryFile;
    std::string bmapFile;
    std::string material;
    std::string windowmaterial;
    std::string scintmaterial;
    std::string airmaterial;
    std::string spec;  ///< arbitrary specification to pass to beamline builder
  
    /// in case the element is a list itself (line)
    std::list <Element> *lst;

    /// print method
    void print(int &ident)const;

    /// flush method
    void flush();

    /// property lookup by name (slow method)
    /// only for properties with type int/double!
    double property_lookup(std::string property_name)const;

    ///@{ set method from Parameters structure
    void set(const Parameters& params);
    void set(const Parameters& params,std::string nameIn, ElementType typeIn);
    ///@}
  
    /// constructor
    Element();

  private:
    /// publish members so these can be looked up from parser
    void PublishMembers();
    /// map that translates between alternative parser names for members, could be made static
    std::map<std::string,std::string> alternativeNames;

  protected:
    /// returns 'official' member name for property
    std::string getPublishedName(std::string name)const;
  };
}
 
#endif
