/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file Merlin\AcceleratorModel\ComplexGeometry\myComponentFrame.h
 * last modified 07/12/00 12:49:47
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

#ifndef myComponentFrame_h
#define myComponentFrame_h 1

//#include "merlin_config.h"

// myAcceleratorComponent
#include "myAcceleratorComponent.hh"
// TransformableFrame
// gab:
//#include "AcceleratorModel/ComplexGeometry/TransformableFrame.h"

// gab:
class myComponentFrame 
//: public TransformableFrame  
{
  public:
    class CachedT 
    {
      public:
        // Data Members for Class Attributes

      // gab:
      //          Transform3D in_T;
      //          Transform3D out_T;

      protected:
      private:
      private:  
    };

  public:
      //	Constructor taking the associated myAcceleratorComponent
      //	object.
      explicit myComponentFrame (myAcceleratorComponent& ac, const string& id = "");

      //	Copy constructor.
      myComponentFrame (const myComponentFrame& rhs);

      virtual ~myComponentFrame ();


      //	Copy assignment.
      const myComponentFrame& operator = (const myComponentFrame& rhs);

      myAcceleratorComponent& GetComponent ();

      const myAcceleratorComponent& GetComponent () const;

      //	Return the three-dimensional transformation between the
      //	local frame at s1 and the local frame at s2. s1 and s2
      //	are in the local s frame, and must be within the
      //	geometry extents.
  // gab:
  //      virtual Transform3D GetTransform (double s1, double s2) const throw (BeyondExtent);

      //	Returns the total transformation, i.e. the
      //	transformation from the local entrance frame to the
      //	local exit frame.
  // gab:
  //      virtual Transform3D GetTotalTransform () const;

      //	Returns the local extent of this geometry.
  //      virtual AcceleratorGeometry::Extent GetLocalExtent () const;

      //	Returns the total arc-length of the geometry.
      virtual double GetLength () const;

      //	Should never be called for this class.
      virtual void ReplaceSubFrame (LatticeFrame& oldf, LatticeFrame& newf);

      //	Returns false.
      virtual bool HasSubFrames () const;

      //	Returns false;
      virtual bool IsEntrSubFrame (const LatticeFrame& aSubFrame) const;

      //	Returns false.
      virtual bool IsExitSubFrame (const LatticeFrame& aSubFrame) const;

      //	Returns false.
      virtual bool IsSubFrame (const LatticeFrame& aFrame) const;

      //	Causes any cached state to be invalidated. The cached
      //	state should be re-calculated if and when required.
      virtual void Invalidate () const;

      //	Returns the entrance transformation for this frame,
      //	including the effects of all nested frame boundaries at
      //	this location.
  // gab:
  // virtual Transform3D GetEntrTransform () const;

      //	Returns the exit transformation for this frame,
      //	including the effects of all nested frame boundaries at
      //	this location.
  // gab:
  //  virtual Transform3D GetExitTransform () const;

      myAcceleratorComponent* operator -> ();

      const myAcceleratorComponent* operator -> () const;

      //	Returns a copy of this myComponentFrame. Note that only
      //	the reference to the myAcceleratorComponent is copied, not
      //	the myAcceleratorComponent itself.
      virtual myModelElement* Copy () const;

      //	Return the name of the element. Returns the name of the
      //	myAcceleratorComponent if the label for this frame has not
      //	been explicitely set.
      virtual const string& GetName () const;

      //	Returns the type of the referenced myAcceleratorComponent.
      virtual const string& GetType () const;

      //	Returns the transformation from the local origin to the
      //	entrance plane.
  //gab:
  //      virtual Transform3D GetOriginToEntrTransform () const;

      //	Returns the transformation from the local origin to the
      //	exit plane.
  // gab:
  //      virtual Transform3D GetOriginToExitTransform () const;

    // Data Members for Class Attributes

      //	Set to true if entrance and exit transformations are to
      //	be cached.

      static bool cacheTransforms;


  protected:
    // Data Members for Associations

      myAcceleratorComponent* theComponent;

  private:
  private:  

      void UpdateCachedT () const;

    // Data Members for Associations
      mutable CachedT* cached_t;
};

// Class myComponentFrame::CachedT 

// Class myComponentFrame 

// gab:
//inline myComponentFrame::myComponentFrame (myAcceleratorComponent& ac, const //string& id)
//  : TransformableFrame(id),theComponent(&ac),cached_t(0)
//{}

inline myComponentFrame::myComponentFrame (const myComponentFrame& rhs)
  // gab:
  : theComponent(rhs.theComponent),cached_t(0)
  //  : TransformableFrame(rhs),theComponent(rhs.theComponent),cached_t(0)
{}


inline myAcceleratorComponent& myComponentFrame::GetComponent ()
{
	return *theComponent;
}

inline const myAcceleratorComponent& myComponentFrame::GetComponent () const
{
	return *theComponent;
}

inline myAcceleratorComponent* myComponentFrame::operator -> ()
{
	return theComponent;
}

inline const myAcceleratorComponent* myComponentFrame::operator -> () const
{
	return theComponent;
}

inline const string& myComponentFrame::GetName () const
{
  // gab:
  //	const string& id = TransformableFrame::GetName();
	return (id.length()!=0)? id : (theComponent->GetName());
}


#endif
