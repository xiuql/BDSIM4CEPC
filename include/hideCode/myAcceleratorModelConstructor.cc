/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file myAcceleratorModelConstructor.cc
 * last modified 26/06/00 16:28:02
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

//#include "merlin_config.h"
#include <cassert>
#include <map>
#include <iomanip>

// Drift
#include "myDrift.hh"
// myAcceleratorModelConstructor
#include "myAcceleratorModelConstructor.hh"
// SequenceFrame
//#include "AcceleratorModel/ComplexGeometry/SequenceFrame.h"

namespace {

	struct ModelStats {

		map<string,int>& s;

		ModelStats(map<string,int>& stats) :s(stats) {}

		void operator()(const ModelElement* element)
		{
			s[element->GetType()]++;
		}
	};
};


// Class myAcceleratorModelConstructor 

myAcceleratorModelConstructor::myAcceleratorModelConstructor ()
  : currentModel(0)
{}

myAcceleratorModelConstructor::~myAcceleratorModelConstructor ()
{
	if(currentModel) 
		delete currentModel;
}

void myAcceleratorModelConstructor::NewModel ()
{
	if(currentModel) {
		delete currentModel;
		while(!frameStack.empty())
			frameStack.pop();
	}
	currentModel = new myAcceleratorModel();
	// gab:
	//	frameStack.push(currentModel->globalFrame);
}

myAcceleratorModel* myAcceleratorModelConstructor::GetModel ()
{
	frameStack.pop();
	assert(currentModel && frameStack.empty());

	currentModel->globalFrame->ConsolidateConstruction();

	myAcceleratorModel* t=currentModel;
	currentModel=0;
	return t;
}

/* gab >>>
void AcceleratorModelConstructor::NewFrame (SequenceFrame& aFrame)
{
	assert(currentModel);
	(*currentModel).elements.insert(&aFrame);
	frameStack.push(&aFrame);
}

void AcceleratorModelConstructor::EndFrame (SequenceFrame& aFrame)
{
	SequenceFrame* cf = frameStack.top();
	assert(&aFrame == cf);
	frameStack.pop();
	(frameStack.top())->AppendFrame(*cf);
}

void AcceleratorModelConstructor::AppendDrift (double d)
{
	Drift* newd = new Drift("UNNAMED",d);
	AppendComponentFrame(new TComponentFrame<Drift>(*newd));
}

/* gab >>>
void AcceleratorModelConstructor::ReportStatistics (std::ostream& os) const
{
	using std::map;

	os<<"Arc length of beamline:     "<<currentModel->globalFrame->GetLength()<<" meter"<<endl;
	os<<"Total number of components: "<<(*currentModel).lattice.size()<<endl;
	os<<"Total numner of elements:   "<<(*currentModel).elements.size()<<endl;
	os<<endl;
	os<<"Model Element statistics\n";
	os<<"------------------------\n\n";

	map<string,int> stats;
	for_each((*currentModel).elements.begin(),(*currentModel).elements.end(),ModelStats(stats));
	for(map<string,int>::iterator si=stats.begin(); si!=stats.end(); si++) {
		string atype = (*si).first;
		int count = (*si).second;
		os<<setw(20)<<left<<atype.c_str();
		os<<setw(4)<<count<<endl;
	}
	os<<endl;
}
<<< gab */

void AcceleratorModelConstructor::AppendComponentFrame (ComponentFrame* cf)
{
	assert(currentModel);
	(*currentModel).elements.insert(cf);
	(*currentModel).elements.insert(&(cf->GetComponent()));
	(*currentModel).lattice.push_back(cf);
	(frameStack.top())->AppendFrame(*cf);
}

