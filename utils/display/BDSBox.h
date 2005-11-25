/* Display for BDSIM code     
Author: Olivier Dadoun, Laboratoire de l'Accelerateur Lineaire (LAL-IN2P3), Orsay (France)
<mailto:> dadoun@lal.in2p3.fr, 2005
Last modified 30.09.2005
*/
#ifndef __BDSBox__
#define __BDSBox__

#ifndef ROOT_TBox
#include "TBox.h"
#endif

#include "BDSParser.h"

#include "parser/gmad.h"

class BDSBox : public TBox
{
public:
	BDSBox(Element _item, Double_t _y1, Double_t _y2);	

	void Update(BDSPad* pad, Double_t xmin, Double_t xmax);
	Double_t GetBDSX1() {return s-item.l;}
   Double_t GetBDSX2() {return s;}
	TString  GetBDSBoxName(){return Form(item.name);}
	short GetBDSType(){return item.type;}
	Double_t GetBDSLen(){return item.l;}
	Float_t GetBDSAngle(){return item.angle;}
	Float_t GetBDSK0(){return item.k0;}
	Float_t GetBDSK1(){return item.k1;}
	Float_t GetBDSK2(){return item.k2;}
	Float_t GetBDSK3(){return item.k3;}
	Float_t GetBDSTilt(){return item.tilt;}
	Double_t SetBDSX2(Double_t S){s=S;}
	
private:
	Element item;
	Double_t s;

public:
	ClassDef(BDSBox,1)
};
#endif
