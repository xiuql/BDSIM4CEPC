#ifndef _BDS_TRAJECTORY_POINT_HH__
#define _BDS_TRAJECTORY_POINT_HH__

#include "G4TrajectoryPoint.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"

class BDSTrajectoryPoint: public G4TrajectoryPoint{
public:
  BDSTrajectoryPoint();
  BDSTrajectoryPoint(const G4Track* aTrack);
  ~BDSTrajectoryPoint();

  inline void *operator new(size_t);
  inline void operator delete(void *aTrajectoryPoint);
  inline int operator==(const BDSTrajectoryPoint& right) const
  {return (this==&right);};

  inline G4bool isScatteringProcess(){return _isScatteringProcess;}
  inline G4int GetTrackID(){return _trackID;}
  void printData();
  inline G4ThreeVector GetVertexPosition(){return _vertexPosition;}

  
private:
  G4bool _isScatteringProcess;
  const G4VProcess* _currentProcess;
  G4int _trackID;
  G4ThreeVector _vertexPosition;
};

extern G4Allocator<BDSTrajectoryPoint> bdsTrajectoryPointAllocator;

inline void* BDSTrajectoryPoint::operator new(size_t)
{
  void *aTrajectoryPoint;
  aTrajectoryPoint = (void *) bdsTrajectoryPointAllocator.MallocSingle();
  return aTrajectoryPoint;
}

inline void BDSTrajectoryPoint::operator delete(void *aTrajectoryPoint)
{
  bdsTrajectoryPointAllocator.FreeSingle((BDSTrajectoryPoint *) aTrajectoryPoint);
}



#endif
