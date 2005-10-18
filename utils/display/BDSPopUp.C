/* Display for BDSIM code     
Author: Olivier Dadoun, Laboratoire de l'Accelerateur Lineaire (LAL-IN2P3), Orsay (France)
<mailto:> dadoun@lal.in2p3.fr, 2005
Last modified 30.09.2005
*/
#ifndef ROOT_TText
#include "TText.h"
#endif

#include "BDSPopUp.h"
ClassImp(BDSPopUp) 

BDSPopUp::BDSPopUp(TString name, short type,Float_t len, Float_t s,
					   Float_t k0, Float_t k1, Float_t k2, Float_t k3, Float_t angle)
: TCanvas("echo_canvas","Optics Specs.",960,10,330,200)
{
	TString temp;
	TString string_type;
	
	TText *t0 = new TText(0.02,0.9,"Opticals Elements specs.");
	temp= "Name: " + name;

	switch (type) {
		case 4 : string_type = "Quadrupole";
			break;
		case 3 : string_type = "Sbend";
			break;
		default :  string_type = "Other type ...";
	}
	
	temp = temp + " Type :" + string_type;
	TText *t1 = new TText(0.02,0.7,temp);
	temp=Form("@ %f m with a length of %f m",s,len);
	TText *t2 = new TText(0.02,0.6,temp);
	temp=Form("k1=%f, k2=%f",k0,k1);
	TText *t3 = new TText(0.02,0.4,temp);
	temp=Form("k3=%f, k4=%f",k2,k3);
	TText *t4 = new TText(0.02,0.3,temp);
	temp=Form("angle=%f",angle);
	
	t0->SetTextColor(2);
	t0->SetTextAlign(12);
	t0->SetTextSize(0.11);
	t1->SetTextAlign(12);
	t1->SetTextSize(0.09);
	t2->SetTextAlign(12);
	t2->SetTextSize(0.09);
	t3->SetTextAlign(12);
	t3->SetTextSize(0.09);
	t4->SetTextAlign(12);
	t4->SetTextSize(0.09);	
	
	t0->Draw();
	t1->Draw();
	t2->Draw();
	t3->Draw();
	t4->Draw();
}
