/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file AcceleratorModel\AdvancedModel\AcceleratorModelConstructor.h
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


#ifndef myAcceleratorModelConstructor_h
#define myAcceleratorModelConstructor_h 1

//#include "merlin_config.h"

#include <stack>

// AcceleratorModel
#include "myAcceleratorModel.hh"
// TComponentFrame
//#include "AcceleratorModel/ComplexGeometry/TComponentFrame.h"
//#include "myComponentFrame.hh"

//class SequenceFrame;

//	Responsible for constructing an AcceleratorModel object.
//	The nested frame hierachy is constructed internally
//	using a frame stack: each call to NewFrame(aFrame)
//	pushes the current frame onto the stack, and makes the
//	new frame the current frame. A subsequent call to End
//	Frame(aFrame) causes the current frame (aFrame) to be
//	popped from the stack. At any time between calls to New
//	Frame and EndFrame can AppendComponent be called.

class myAcceleratorModelConstructor 
{
  public:
      myAcceleratorModelConstructor ();

      ~myAcceleratorModelConstructor ();

      //	Initialises a new myAcceleratorModel. Must be called
      //	before any subsequent constructor calls.
      void NewModel ();

      //	Ends the current model construction and returns the
      //	model. The model must be in a valid (complete) state.
      myAcceleratorModel* GetModel ();

      //	Begin construction of a new LatticeFrame.
  // gab:
  //      void NewFrame (SequenceFrame& aFrame);
      void NewFrame (myComponentFrame& aFrame);

      //	Finish construction of the specified frame. aFrame must
      //	match the current stack frame.
  //      void EndFrame (SequenceFrame& aFrame);
      void EndFrame (myComponentFrame& aFrame);

      //	Append the specified component a distance d meters
      //	downstream of the last component.
      template<class T> void AppendComponent (T& acc, double d = 0)
      {
		if(d!=0) 
			AppendDrift(d);
		// gab:
		//     AppendComponentFrame(new TComponentFrame<T>(acc));
		AppendComponentFrame(new myComponentFrame<T>(acc));
      }

      //	Returns a reference to the current frame.
      SequenceFrame& GetCurrentFrame ()
      {
		return *(frameStack.top());
      }

      //	Returns the depth of the current frame. 0 refers to the
      //	global frame (top level).
      int GetCurrentFrameDepth () const
      {
		return frameStack.size()-1;
      }

      //	Appends a simple drift to the current model.
      void AppendDrift (double d);

      //	Prints a table to os  containing statistics on the type
      //	and number of ModelElement current contained in the
      //	model.
      void ReportStatistics (std::ostream& os) const;

  protected:
  private:
    // Data Members for Associations

      myAcceleratorModel* currentModel;

  private: 

      void AppendComponentFrame (ComponentFrame* cf);

    // Data Members for Associations

      std::stack< SequenceFrame* > frameStack;
};

#endif
