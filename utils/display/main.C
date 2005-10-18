/* Display for BDSIM code     
Author: Olivier Dadoun, Laboratoire de l'Accelerateur Lineaire (LAL-IN2P3), Orsay (France)
<mailto:> dadoun@lal.in2p3.fr, 2005
Last modified 30.09.2005
*/
#include "TROOT.h"
#include "TRint.h"
#include "TFile.h"
#include "TH1F.h"
#include "BDSCanvas.h"
#include "BDSPad.h"

int main(int argc, char **argv)
{
    // Create interactive interface
    TRint *theApp = new TRint("ROOT example", &argc, argv, NULL, 0);
	 
	 // Work Area 
	 BDSCanvas *b = new BDSCanvas("20mrad.gmad");
	 
	 Float_t x,xp,y,yp,z,z0,e;
	 TFile *f = TFile::Open("20mrad.root");
	 TH1F *histo;
	 histo = (TH1F*)f->Get("h1;1"); 
	 histo->GetXaxis()->SetLimits(BDSPad::xmin_axis,BDSPad::xmax_axis);
  	 histo->Draw();
	 b->SetHisto(histo); 
    b->cd();
	 // Run interactive interface
	theApp->Run();
	
    return(0);
}
//--------------------------------------------------
