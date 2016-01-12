#include "BDSDebug.hh"
#include "BDSGeometryWriter.hh"
#include "BDSUtilities.hh"

#include "globals.hh" // geant4 types / globals
#ifdef USE_GDML
#include "G4GDMLParser.hh"
#endif
#include "G4FileUtilities.hh"
#include "G4TransportationManager.hh"

class G4VPhysicalVolume;

BDSGeometryWriter::~BDSGeometryWriter(){}

BDSGeometryWriter::BDSGeometryWriter()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
}

void BDSGeometryWriter::ExportGeometry(G4String geometryType,
				       G4String geometryFileName)
{
  if (!strcmp(geometryType, "gdml"))
    {WriteToGDML(geometryFileName);}
}

void BDSGeometryWriter::WriteToGDML(G4String           outputFileName,
				    G4VPhysicalVolume* volume)
{
  if (!volume)
    {volume = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();}
  // gdml parser throws exception if file exists. Delete file in that case
  if (BDS::FileExists(outputFileName)) {
    G4FileUtilities fileUtilities;
    fileUtilities.DeleteFile(outputFileName, "");
  }
#ifdef USE_GDML
  G4GDMLParser parser;
  parser.Write(outputFileName, volume, true);
#endif
}
