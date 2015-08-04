#include "BDSTunnelType.hh"
#include "BDSDebug.hh"
#include "globals.hh"

#include <map>

// dictionary for BDSTunnelType
template<>
std::map<BDSTunnelType, std::string>* BDSTunnelType::dictionary =
  new std::map<BDSTunnelType, std::string> ({
   {BDSTunnelType::circular,       "circular"},
   {BDSTunnelType::elliptical,     "elliptical"},
   {BDSTunnelType::square,         "square"},
   {BDSTunnelType::rectangular,    "rectangular"},
   {BDSTunnelType::rectaboveground,"rectaboveground"},
   {BDSTunnelType::ilc,            "ilc"}
});
      
BDSTunnelType BDS::DetermineTunnelType(G4String tunnelType)
{
  std::map<G4String, BDSTunnelType> types;
  types["circular"]        = BDSTunnelType::circular;
  types["elliptical"]      = BDSTunnelType::elliptical;
  types["square"]          = BDSTunnelType::square;
  types["rectangular"]     = BDSTunnelType::rectangular;
  types["ilc"]             = BDSTunnelType::ilc;
  types["rectaboveground"] = BDSTunnelType::rectaboveground;

  tunnelType.toLower();
  
  if ( types.find(tunnelType) == types.end() )
    {
      // it's not a valid key
      G4cerr << __METHOD_NAME__ << " " << tunnelType << " is not a valid tunnel type" << G4endl;
      exit(1);
    }

  BDSTunnelType returnValue = types[tunnelType];
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " determined tunnel type to be " << returnValue << G4endl;
#endif
  return returnValue;
}
