#include "BDSAnalysisManager.hh"
#include "BDSDebug.hh"
#include "BDSHistogram.hh"
#include "globals.hh"             // geant4 globals / types

#include <vector>

BDSAnalysisManager* BDSAnalysisManager::_instance = nullptr;

BDSAnalysisManager* BDSAnalysisManager::Instance()
{
  if (_instance == nullptr)
    {
      _instance = new BDSAnalysisManager();
    }
  return _instance;
}

BDSAnalysisManager::BDSAnalysisManager(){;}

BDSAnalysisManager::~BDSAnalysisManager()
{
  //delete all the 1d histograms created
  std::vector<BDSHistogram1D*>::iterator iter, end;
  for (iter = histograms1d.begin(), end = histograms1d.end(); iter != end; ++iter)
    {
      delete (*iter);
    }
  _instance = nullptr;
}

G4int BDSAnalysisManager::Create1DHistogram(G4String name,
					    G4String title,
					    G4int    nbins,
					    G4double xmin,
					    G4double xmax,
					    G4String xlabel,
					    G4String ylabel)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__   << "Name: " << name
	 << ", Title: "       << title
	 << ", # of Bins: "   << nbins
	 << ", Lower limit: " << xmin
	 << ", Upper limit: " << xmax << G4endl;
#endif
  histograms1d.push_back(new BDSHistogram1D(xmin, xmax, nbins, name, title, xlabel, ylabel));
  return histograms1d.size();
}

G4int BDSAnalysisManager::Create1DHistogram(G4String name,
					    G4String title,
					    std::vector<double>& edges,
					    G4String xlabel,
					    G4String ylabel)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "Name: " << name
	 << ", Title: " << title << G4endl
	 << __METHOD_NAME__ << "Vector of bin edges - # of Bins: " << edges.size()
	 << ", Lower limit: " << edges.front()
	 << ", Upper limit: " << edges.back() << G4endl;
#endif
  histograms1d.push_back(new BDSHistogram1D(edges,name, title, xlabel, ylabel));
  return histograms1d.size();
}

BDSHistogram1D* BDSAnalysisManager::GetHistogram(G4int histoIndex)
{
  CheckHistogramIndex(histoIndex);
  return histograms1d[histoIndex];
}

void BDSAnalysisManager::Fill1DHistogram(G4int histoIndex, G4double value, G4double weight)
{
  CheckHistogramIndex(histoIndex);
  histograms1d[histoIndex]->Fill(value,weight);
}

G4int BDSAnalysisManager::NumberOfHistograms()const{return histograms1d.size();}

void BDSAnalysisManager::CheckHistogramIndex(G4int histoIndex)
{
  if ( ((size_t)histoIndex > histograms1d.size()) || histoIndex < 0 )
  {
    G4cerr << __METHOD_NAME__ << "invalid histogram index" << G4endl;
    exit(1);
  }
  // else void - keep going
}
