/* Display for BDSIM code     
Author: Olivier Dadoun, Laboratoire de l'Accelerateur Lineaire (LAL-IN2P3), Orsay (France)
<mailto:> dadoun@lal.in2p3.fr, 2005
Last modified 30.09.2005
*/
#include "BDSParser.h"
#include "BDSPad.h"
#include "BDSCanvas.h"
BDSParser::BDSParser()
{
	//*-*-*-*-*-*-*-*-*-*-*Line default constructor*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	//*-*                  ========================
}

void BDSParser::LoadFile(BDSPad* _pad, char* _path)
{
	gmad_parser(_path);
	list<struct Element>::iterator it;
	Double_t s_current=0.;
	Int_t nelement=1;
	TString tempname; 
	((BDSCanvas*)gPad->GetCanvas())->EndPositionElement[nelement]=0.;
	_pad->Begin();
	for(it = beamline_list.begin();it!=beamline_list.end();it++)
	{
	if((*it).l> 1e-9)
		{
		s_current += (*it).l;
		((BDSCanvas*)gPad->GetCanvas())->EndPositionElement[nelement]=s_current;
		tempname=Form((*it).name);
		((BDSCanvas*)gPad->GetCanvas())->NameElement[nelement]=tempname;	
	//	strcpy(((BDSCanvas*)gPad->GetCanvas())->NameElement[nelement],(*it).name);
		_pad->AddBDSBox(*it,s_current);
		nelement++;
		}
	}
	((BDSCanvas*)gPad->GetCanvas())->NumberElement=nelement-1;
	cout << "total length "  << s_current << endl;	
	_pad->End();
}
