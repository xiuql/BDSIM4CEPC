#include "BDSDebug.hh"
#include "BDSGeometryComponent.hh"
#include "BDSTunnelFactory.hh"
#include "BDSTunnelFactoryBase.hh"
#include "BDSTunnelFactoryCircular.hh"
#include "BDSTunnelFactoryElliptical.hh"
#include "BDSTunnelFactoryRectangular.hh"
#include "BDSTunnelFactoryRectAboveGround.hh"
#include "BDSTunnelFactorySquare.hh"
#include "BDSTunnelSection.hh"
#include "BDSTunnelType.hh"

#include "globals.hh"                        // geant4 globals / types

BDSTunnelFactory* BDSTunnelFactory::_instance = 0;

BDSTunnelFactory* BDSTunnelFactory::Instance()
{
  if (_instance == 0)
    {_instance = new BDSTunnelFactory();}
  return _instance;
}

BDSTunnelFactory::BDSTunnelFactory()
{;}

BDSTunnelFactoryBase* BDSTunnelFactory::GetAppropriateFactory(BDSTunnelType tunnelType)
{
  switch(tunnelType.underlying()){
  case BDSTunnelType::circular:
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << "circular tunnel factory" << G4endl;
#endif
    return BDSTunnelFactoryCircular::Instance();
    break;
  case BDSTunnelType::elliptical:
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << "elliptical tunnel factory" << G4endl;
#endif
    return BDSTunnelFactoryElliptical::Instance();
    break;
  case BDSTunnelType::rectangular:
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << "rectangular tunnel factory" << G4endl;
#endif
    return BDSTunnelFactoryRectangular::Instance();
    break;
  case BDSTunnelType::square:
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << "square tunnel factory" << G4endl;
#endif
    return BDSTunnelFactorySquare::Instance();
    break;
  case BDSTunnelType::rectaboveground:
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << "rectangular above ground tunnel factory" << G4endl;
#endif
    return BDSTunnelFactoryRectAboveGround::Instance();
    break;
  default:
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << "unknown tunnel type \"" << tunnelType
	   << "\" - using circular tunnel factory by default" << G4endl;
#endif
    return BDSTunnelFactoryCircular::Instance();
    break;
  }
}

BDSTunnelSection* BDSTunnelFactory::CreateTunnelSection(BDSTunnelType tunnelType,
							G4String      name,
							G4double      length,
							G4double      tunnelThickness,
							G4double      tunnelSoilThickness,
							G4Material*   tunnelMaterial,
							G4Material*   tunnelSoilMaterial,
							G4bool        tunnelFloor,
							G4double      tunnelFloorOffset,
							G4double      tunnel1,
							G4double      tunnel2,
							G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  BDSTunnelFactoryBase* factory = GetAppropriateFactory(tunnelType);
  return factory->CreateTunnelSection(name, length, tunnelThickness,
				      tunnelSoilThickness, tunnelMaterial,
				      tunnelSoilMaterial, tunnelFloor,
				      tunnelFloorOffset, tunnel1, tunnel2, visible);
}

BDSTunnelSection* BDSTunnelFactory::CreateTunnelSectionAngledIn(BDSTunnelType tunnelType,
								G4String      name,
								G4double      length,
								G4double      angleIn,
								G4double      tunnelThickness,
								G4double      tunnelSoilThickness,
								G4Material*   tunnelMaterial,
								G4Material*   tunnelSoilMaterial,
								G4bool        tunnelFloor,
								G4double      tunnelFloorOffset,
								G4double      tunnel1,
								G4double      tunnel2,
								G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  BDSTunnelFactoryBase* factory = GetAppropriateFactory(tunnelType);
  return factory->CreateTunnelSectionAngledIn(name, length, angleIn, tunnelThickness,
					      tunnelSoilThickness, tunnelMaterial,
					      tunnelSoilMaterial, tunnelFloor,
					      tunnelFloorOffset, tunnel1, tunnel2, visible);
}

BDSTunnelSection* BDSTunnelFactory::CreateTunnelSectionAngledOut(BDSTunnelType tunnelType,
								 G4String      name,
								 G4double      length,
								 G4double      angleOut,
								 G4double      tunnelThickness,
								 G4double      tunnelSoilThickness,
								 G4Material*   tunnelMaterial,
								 G4Material*   tunnelSoilMaterial,
								 G4bool        tunnelFloor,
								 G4double      tunnelFloorOffset,
								 G4double      tunnel1,
								 G4double      tunnel2,
								 G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  BDSTunnelFactoryBase* factory = GetAppropriateFactory(tunnelType);
  return factory->CreateTunnelSectionAngledOut(name, length, angleOut, tunnelThickness,
					       tunnelSoilThickness, tunnelMaterial,
					       tunnelSoilMaterial, tunnelFloor,
					       tunnelFloorOffset, tunnel1, tunnel2, visible);
}

BDSTunnelSection* BDSTunnelFactory::CreateTunnelSectionAngledInOut(BDSTunnelType tunnelType,
								   G4String      name,
								   G4double      length,
								   G4double      angleIn,
								   G4double      angleOut,
								   G4double      tunnelThickness,
								   G4double      tunnelSoilThickness,
								   G4Material*   tunnelMaterial,
								   G4Material*   tunnelSoilMaterial,
								   G4bool        tunnelFloor,
								   G4double      tunnelFloorOffset,
								   G4double      tunnel1,
								   G4double      tunnel2,
								   G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  BDSTunnelFactoryBase* factory = GetAppropriateFactory(tunnelType);
  return factory->CreateTunnelSectionAngledInOut(name, length, angleIn, angleOut,
						 tunnelThickness, tunnelSoilThickness, tunnelMaterial,
						 tunnelSoilMaterial, tunnelFloor,
						 tunnelFloorOffset, tunnel1, tunnel2, visible);
}

BDSTunnelSection* BDSTunnelFactory::CreateTunnelSectionAngled(BDSTunnelType tunnelType,
							      G4String      name,
							      G4double      length,
							      G4ThreeVector inputFace,
							      G4ThreeVector outputFace,
							      G4double      tunnelThickness,
							      G4double      tunnelSoilThickness,
							      G4Material*   tunnelMaterial,
							      G4Material*   tunnelSoilMaterial,
							      G4bool        tunnelFloor,
							      G4double      tunnelFloorOffset,
							      G4double      tunnel1,
							      G4double      tunnel2,
							      G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  BDSTunnelFactoryBase* factory = GetAppropriateFactory(tunnelType);
  return factory->CreateTunnelSectionAngled(name, length, inputFace, outputFace,
					    tunnelThickness, tunnelSoilThickness, tunnelMaterial,
					    tunnelSoilMaterial, tunnelFloor,
					    tunnelFloorOffset, tunnel1, tunnel2, visible);
}
