/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file Merlin\AcceleratorModel\AdvancedModel\AcceleratorModel.cpp
 * last modified 11/07/00 21:35:17
 */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * MERLIN C++ class library for 
 * Charge Particle Accelerator Simulations
 * Copyright (c) 1999 by N.J.Walker.  ALL RIGHTS RESERVED. 
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * No representations about the suitability of this software for
 * any purpose is made. It is provided "as is" without express
 * or implied warranty.
 */

#include <iterator>
#include <cassert>
#include <algorithm>

// deleters
#include "myDeleters.hh"
// AcceleratorModel
#include "myAcceleratorModel.hh"
#include "myAcceleratorComponent.hh"

// ModelElement
//#include "AcceleratorModel/ModelElement.h"
// ComponentFrame
//#include "AcceleratorModel/ComplexGeometry/ComponentFrame.h"
// SequenceFrame
//#include "AcceleratorModel/ComplexGeometry/SequenceFrame.h"
// TComponentFrame
//#include "AcceleratorModel/ComplexGeometry/TComponentFrame.h"


using namespace std;

namespace {

	struct MatchName {
		myStringPattern pattern;
		MatchName(const string& pat) : pattern(pat) {}
		bool operator()(const myAcceleratorComponent* frm) {
			return pattern(frm->GetName());
		}
	};

}


// Parameterized Class myAcceleratorModel::Beamline::TRK 


// Class myAcceleratorModel::Beamline 

// Class myAcceleratorModel::BadRange 

// Class myAcceleratorModel 

// gab:
//myAcceleratorModel::myAcceleratorModel ()
//  : globalFrame(new SequenceFrame("GLOBAL",SequenceFrame::originAtEntrance))
//{}

myAcceleratorModel::~myAcceleratorModel ()
{
	std::for_each(elements.begin(),elements.end(),
                          deleter<myAcceleratorComponent>());
}

myAcceleratorModel::Beamline myAcceleratorModel::GetBeamline ()
{
	BeamlineIterator i = lattice.end();
	advance(i,-1);
	return Beamline(lattice.begin(),i);
}

myAcceleratorModel::Beamline myAcceleratorModel::GetBeamline (Index n1, Index n2) throw (BadRange)
{
	if(n1<0 || n2>=lattice.size())
		throw BadRange();

	BeamlineIterator i1 = lattice.begin();
	BeamlineIterator i2 = lattice.begin();
	advance(i1,n1);
	advance(i2,n2);
	return Beamline(i1,i2);
}

myAcceleratorModel::Beamline myAcceleratorModel::GetBeamline (const string& pat1, const string& pat2, int n1, int n2) throw (BadRange)
{
	assert(n1>=1 && n2>=1);
		
	myStringPattern p1(pat1),p2(pat2);
	BeamlineIterator i1,i2;
	int nn1(0),nn2(0);

	for(BeamlineIterator i = lattice.begin(); i!=lattice.end() && (nn1!=n1 || nn2!=n2); i++) {
	  //		string id = ((*i)->GetComponent()).GetQualifiedName();
		string id = (*i)->GetName();
		if(nn1<n1 && p1(id) && ++nn1 == n1)
			i1=i;
		if(nn2<n2 && p2(id) && ++nn2 == n2)
			i2=i;
	}

	if(i==lattice.end() || i1==i2)
		throw BadRange();

	return Beamline(i1,i2);
}

myAcceleratorModel::Beamline myAcceleratorModel::GetReversedBeamline ()
{
	BeamlineIterator i = lattice.end();
	advance(i,-1);
	return Beamline(i,lattice.begin());
}


/* gab: >>>
int myAcceleratorModel::ExtractComponents (const string& pat, 
vector<myAcceleratorComponent*>& results)
{
	vector<myAcceleratorComponent*> tmp;
	tmp.reserve(16);
	if(pat=="*") // copy everything!
		copy(lattice.begin(),lattice.end(),back_inserter(tmp));
	else
		copy_if(lattice.begin(),lattice.end(),back_inserter(tmp),
MatchName(pat));

	results.swap(tmp);
	return results.size();
}

int myAcceleratorModel::ExtractModelElements (const string& pat, 
vector<myAcceleratorComponent*>& results)
{
	vector<myAcceleratorComponent*> tmp;
	tmp.reserve(16);
	if(pat=="*") // copy everything!
		copy(elements.begin(),elements.end(),back_inserter(tmp));
	else
		copy_if(elements.begin(),elements.end(),back_inserter(tmp),MatchName(pat));

	results.swap(tmp);
	return results.size();
}

 gab: <<< */
