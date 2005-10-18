/* Display for BDSIM code     
Author: Olivier Dadoun, Laboratoire de l'Accelerateur Lineaire (LAL-IN2P3), Orsay (France)
<mailto:> dadoun@lal.in2p3.fr, 2005
Last modified 30.09.2005
*/
#include "BDSParser.h"
#include "BDSPad.h"
BDSParser::BDSParser()
{
	//*-*-*-*-*-*-*-*-*-*-*Line default constructor*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	//*-*                  ========================
}

void BDSParser::LoadFile(BDSPad* _pad, char* _path)
{
	FILE* f = fopen(_path,"r");
	gmad_parser(_path);
	list<struct Element>::iterator it;
	Double_t s_current=0.;
	
	_pad->Begin();
	for(it = beamline_list.begin();it!=beamline_list.end();it++)
	{
	s_current += (*it).l;
	_pad->AddBDSBox(*it,s_current);
	}
	cout << "total length "  << s_current << endl;	
	_pad->End();
	fclose(f);
}
