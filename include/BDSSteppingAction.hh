#ifndef BDSSTEPPINGACTION_H
#define BDSSTEPPINGACTION_H

#include "G4UserSteppingAction.hh"
#include "G4Transform3D.hh"
#include "G4Types.hh"
#include "BDSBeamlineElement.hh"

class BDSSteppingAction : public G4UserSteppingAction
{
public:
  BDSSteppingAction();
  virtual ~BDSSteppingAction();

  virtual void UserSteppingAction(const G4Step*);

private:
  void ThresholdCutSteppingAction();
  void VerboseSteppingAction();
  void SynchrotronSteppingAction();
  void SynchrotronStatistic();
  void TerminateSteppingAction();

  const G4Step* _step;

  std::ofstream* m_foutSyn;
  std::ofstream* m_foutSynStatistic;
  std::ofstream* m_foutBeam;
  G4String m_endElementName;
  bool m_endPointFlag;
  G4double m_synchHitPosUpstream;
  G4double m_synchHitPosDownstream;
  BDSBeamlineElement* m_endElement;
};

#endif
