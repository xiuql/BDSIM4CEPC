/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file Merlin\AcceleratorModel\ComplexGeometry\ComponentFrame.cpp
 * last modified 07/12/00 12:49:48
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


// myComponentFrame
#include "myComponentFrame.hh"

// Class myComponentFrame::CachedT 


// Class myComponentFrame 

bool myComponentFrame::cacheTransforms = false;

myComponentFrame::~myComponentFrame ()
{
	if(cached_t)
		delete cached_t;
}


const myComponentFrame& myComponentFrame::operator = (const myComponentFrame& rhs)
{
	if(this!=&rhs) {
		if(cached_t) {
			delete cached_t;
			cached_t=0;
		}
		SetName(rhs.GetName());
		theComponent=rhs.theComponent;
	}
	return *this;
}

// gab: >>>
/*
Transform3D myComponentFrame::GetTransform (double s1, double s2) const throw (BeyondExtent)
{
	return theComponent->GetGeometry()->GetTransform(s1,s2);
}

Transform3D myComponentFrame::GetTotalTransform () const
{
	return theComponent->GetGeometry()->GetTotalTransform();
}
// gab: <<<
*/


AcceleratorGeometry::Extent myComponentFrame::GetLocalExtent () const
{
	return theComponent->GetGeometry()->GetLocalExtent();
}

double myComponentFrame::GetLength () const
{
	return theComponent->GetGeometry()->GetLength();
}

void myComponentFrame::ReplaceSubFrame (LatticeFrame& oldf, LatticeFrame& newf)
{
	assert(false);
}

bool myComponentFrame::HasSubFrames () const
{
	return false;
}

bool myComponentFrame::IsEntrSubFrame (const LatticeFrame& aSubFrame) const
{
	return false;
}

bool myComponentFrame::IsExitSubFrame (const LatticeFrame& aSubFrame) const
{
	return false;
}

bool myComponentFrame::IsSubFrame (const LatticeFrame& aFrame) const
{
	return false;
}

void myComponentFrame::Invalidate () const
{
	if(cached_t) {
		delete cached_t;
		cached_t=0;
	}
}

// gab: >>>
/*
Transform3D myComponentFrame::GetEntrTransform () const
{
	if(cacheTransforms) {
		UpdateCachedT();
		return cached_t->in_T;
	}
	else
		return LatticeFrame::GetEntrTransform();
}

Transform3D myComponentFrame::GetExitTransform () const
{
	if(cacheTransforms) {
		UpdateCachedT();
		return cached_t->out_T;
	}
	else
		return LatticeFrame::GetExitTransform();
}
// gab: <<<
*/

ModelElement* myComponentFrame::Copy () const
{
	return new myComponentFrame(*this);
}

const string& myComponentFrame::GetType () const
{
	_TYPESTR(myComponentFrame);
}


// gab: >>>
/*
//	equivalent to GetTransform(0.0,GetLocalExtent().first).
Transform3D myComponentFrame::GetOriginToEntrTransform () const
{
	return theComponent->GetGeometry()->GetOriginToEntrTransform();
}

//	equivalent to: GetTransform(0,GetLocalExtent().second);
Transform3D myComponentFrame::GetOriginToExitTransform () const
{
	return theComponent->GetGeometry()->GetOriginToExitTransform();
}

// gab: <<<
/*

void myComponentFrame::UpdateCachedT () const
{
	if(cached_t==0) { // need to update
		cached_t=new CachedT;
// gab:
//		cached_t->in_T = LatticeFrame::GetEntrTransform();
//		cached_t->out_T = LatticeFrame::GetExitTransform();
	}  
}

