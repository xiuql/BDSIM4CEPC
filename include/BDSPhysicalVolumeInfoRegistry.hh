#ifndef BDSPHYSICALVOLUMEINFOREGISTRY
#define BDSPHYSICALVOLUMEINFOREGISTRY

/**
 * @brief A registry of physical volume info instances that
 * can be searched. This actually contains two registries - one
 * for read out geometry and one for general geometry. The reason 
 * for this is that the physical volumes of the general geometry are
 * much more numerous and would increase the search time of whole registry
 * - important as it'll be used for every single energy deposition track.
 * However, if the read out geometry is used for an element, then we need only
 * register that as all hits will occur inside the read out geometry and that
 * can be used for info lookup. This means only one registration per beamline
 * element. It is not a formal requirement that each component have a read out
 * geometry (yet) so this look up should work without it.  Adding all the physical
 * volumes of a component will lead to polluting the main register with many more
 * volumes. This can be revisited and simplified if we force / require that every
 * element has a read out volume.
 * 
 * @author Laurie Nevay <laurie.nevay@rhul.ac.uk>
 */

#include "globals.hh" // geant4 globals / types
#include "G4VPhysicalVolume.hh"

#include <iterator>
#include <map>

class BDSPhysicalVolumeInfo;

typedef std::map<G4VPhysicalVolume*, BDSPhysicalVolumeInfo*>::iterator BDSPVInfoIterator;
typedef std::map<G4VPhysicalVolume*, BDSPhysicalVolumeInfo*>::const_iterator BDSPVInfoIteratorConst;

class BDSPhysicalVolumeInfoRegistry
{
public:
  /// Singleton accessor
  static BDSPhysicalVolumeInfoRegistry* Instance();

  /// Destructor resets instance to 0 so that the class can be reinstantiated
  /// if necessary
  ~BDSPhysicalVolumeInfoRegistry();

  /// Register an instance of logical volume info with the address of the logical
  /// volume, which is used as the key to access it. Optional isReadOutVolume flag
  /// means volume info will be stored in a separate register that will be searched
  /// first to minimise search time. If not found there, the main register will be
  /// searched. Optional flag isTunnel controls whether the info is stored to a
  /// separate registry just for tunnel segments (not so many so quicker look up,
  /// and / or doesn't pollute main registry -> slower).
  void RegisterInfo(G4VPhysicalVolume*     lvPointer,
		    BDSPhysicalVolumeInfo* info,
		    G4bool                 isReadOutVolume = false,
		    G4bool                 isTunnel = false);

  /// Get the logical volume info for a particular logical volume (by address). Note,
  /// returns null pointer if none found. If isTunnel, gets only from tunnelRegistry.
  BDSPhysicalVolumeInfo* GetInfo(G4VPhysicalVolume* logicalVolume,
				 G4bool             isTunnel = false);

  /// output stream
  friend std::ostream& operator<< (std::ostream &out, BDSPhysicalVolumeInfoRegistry const &r);

private:
  /// Default constructor is private as singleton
  BDSPhysicalVolumeInfoRegistry();

  /// Check whether a physical volume is registered at all
  G4bool IsRegistered(G4VPhysicalVolume* physicalVolume);

  /// Check whether a physical volume is registered to the read out registry
  G4bool IsRegisteredToReadOutRegister(G4VPhysicalVolume* physicalVolume);

  /// Check whether a physical volume is registered ot the general backup registry
  G4bool IsRegisteredToBackupRegister(G4VPhysicalVolume* physicalVolume);

  // Check whether a physical volume is registered ot the tunel registry
  G4bool IsRegisteredToTunnelRegister(G4VPhysicalVolume* physicalVolume);

  /// @{ Search iterator
  BDSPVInfoIterator readOutSearch;
  BDSPVInfoIterator backupSearch;
  BDSPVInfoIterator tunnelSearch;
  /// @}
  
  /// The singleton instane
  static BDSPhysicalVolumeInfoRegistry* _instance;

  /// Registry is a map - note 'register' is a protected keyword.
  std::map<G4VPhysicalVolume*, BDSPhysicalVolumeInfo*> readOutRegister;
  std::map<G4VPhysicalVolume*, BDSPhysicalVolumeInfo*> backupRegister;
  std::map<G4VPhysicalVolume*, BDSPhysicalVolumeInfo*> tunnelRegister;
};






#endif
