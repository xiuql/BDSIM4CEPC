/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file Merlin\AcceleratorModel\AdvancedModel\AcceleratorModel.h
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

#ifndef myAcceleratorModel_h
#define myAcceleratorModel_h 1


//#include "merlin_config.h"


#include <algorithm>
#include <set>
#include <vector>
#include <string>

// StringPattern
#include "myStringPattern.hh"

//class myModelElement;
//class myComponentFrame;

class myAcceleratorComponent;

// gab:
//class SequenceFrame;
template <class T> class TmyAcceleratorComponent;

using std::string;
using std::set;
using std::vector;

class myAcceleratorModel 
{
  private:
    //	Used to store and access all the ModelElement objects
    //	associated (contained) by an AcceleratorModel. Primary
    //	functions are fast keyed access to ModelElements, and
    //	memory management.

    typedef set<myAcceleratorComponent*> ElementRepository;

  public:
    //	A sequence of myAcceleratorComponent objects representing the
    //	complete accelerator lattice.

        typedef std::vector<myAcceleratorComponent*> FlatLattice;

    //	Iterator definitions.
     typedef FlatLattice::iterator BeamlineIterator;
     typedef FlatLattice::const_iterator ConstBeamlineIterator;

    //	Represents the complete or  contiguous sub-section of
    //	the accelerator lattice.

    class Beamline 
    {
      protected:
        template <class T>
        class TRK 
        {
          public:
              explicit TRK (T& aT)
                : _t(aT)
              { }


              void operator () (myAcceleratorComponent* frame)
              {
                _t(frame);
              }

            // Data Members for Class Attributes

              T& _t;

          protected:
          private:
          private:  
        };

      public:
          Beamline (BeamlineIterator fst, BeamlineIterator lst)
			: first(fst),last(lst)
          { }

          //	Returns true if the beamline is reversed.
          bool IsReversed ()
          {
			  return first>last;
          }

          //	Template function that iterates the functor object tobj
          //	over the Beamline. Returns a reference to tobj on exit.
          template<class T> T& Track (T& tobj)
          {
			  // We make use of the TRK wrapper, to avoid the call to tobj's
			  // copy constructor
			  std::for_each(begin(),end(),TRK<T>(tobj));
			  return tobj;
			  // return std::for_each(begin(),end(),tobj);
          }
          //	Standard library type iterator accessors.
          BeamlineIterator begin ()
          {
			  return first;
          }

          ConstBeamlineIterator begin () const
          {
			  return first;
          }

          BeamlineIterator end ()
          {
			  return last+1;
          }

          ConstBeamlineIterator end () const
          {
			  return last+1;
          }

          //	Returns a reference to the first myComponentFrame.
          myAcceleratorComponent& First ()
          {
			  return **first;
          }

          const myAcceleratorComponent& First () const
          {
			  return **first;
          }

          //	Returns a reference to the last myComponentFrame.
          myAcceleratorComponent& Last ()
          {
			  return **last;
          }

          const myAcceleratorComponent& Last () const
          {
			  return **last;
          }

      protected:
      private:
        // Data Members for Class Attributes

          BeamlineIterator first;
          BeamlineIterator last;

      private:  
    };

    class BadRange 
    {
      public:
      protected:
      private:
      private:  
    };

    typedef size_t Index;

  public:
      //	Constructor.
      myAcceleratorModel ();

      ~myAcceleratorModel ();


      //	Returns the entire beamline of the model.
      myAcceleratorModel::Beamline GetBeamline ();

      //	Returns the beamline from elements n1 to n2.
      myAcceleratorModel::Beamline GetBeamline (Index n1, Index n2) throw (BadRange);

      //	Returns a Beamline from the n1-th occurrence of the
      //	component whose qualified name  matches the pattern
      //	pat1, to the n2-th occurrence of the component matching
      //	patl2. Throws BadRange if no section is found.
      myAcceleratorModel::Beamline GetBeamline (const string& pat1, const string& pat2, int n1 = 1, int n2 = 1) throw (BadRange);

      //	Returns the reversed complete beamline of the model.
      myAcceleratorModel::Beamline GetReversedBeamline ();

      //	Returns in results all myComponentFrame objects whose name
      //	matches the string pattern pat. Returns the length of
      //	results on exit. Note that the previous contents of
      //	results is overwritten. Components are returned in
      //	Beamline order.
      int ExtractComponents (const string& pat, vector<myAcceleratorComponent*>& results);

      //	Returns in results all myModelElement objects whose name
      //	matches the string pattern pat. Returns the length of
      //	results on exit. Note that the previous contents of
      //	results is overwritten. The order results is undefined.
      int ExtractmyModelElements (const string& pat, vector<myAcceleratorComponent*>& results);

      //	template function returning TmyComponentFrame objects
      //	corresponding to AcceleratorComponents of type T.
      //	pattern is optional string pattern which can be used to
      //	match only those components with a specific
      //	(unqualified) name. Components are returned in Beamline
      //	order.
      template<class T> int ExtractTypedComponents (vector<TmyAcceleratorComponent<T>*>& results, const string& pattern = "*")
      {

		  vector<TmyAcceleratorComponent<T>*> temp;
		  myStringPattern p(pattern);
		  temp.reserve(10);
		  for(BeamlineIterator i = lattice.begin(); i!=lattice.end(); i++) {
			TmyAcceleratorComponent<T>* cf = dynamic_cast<TmyAcceleratorComponent<T>*>(*i);
			if(cf && p(cf->GetName()))
				temp.push_back(cf);
		  }
		  results.swap(temp);
		  return results.size();
      }

  /* gab: >>>
      //	template function returning myModelElements of type T.
      //	pattern is optional string pattern which can be used to
      //	match only those components with a specific
      //	(unqualified) name. Order is undefined.
      template<class T> int ExtractTypedElements (T& results, const string& pattern = "*")
      {
		  T temp;
		  myStringPattern p(pattern);
		  for(ElementRepository::iterator i = elements.begin(); i!=elements.end(); i++) {
			  T::value_type mi = dynamic_cast<T::value_type>(*i);
			if(mi && p(mi->GetName()))
				temp.push_back(mi);
		  }
		  results.swap(temp);
		  return results.size();
      }

      gab: <<<*/

  protected:
  private:
    // Data Members for Associations

      //	The root object in the nested frame hierachy. Note that
      //	this myModelElement is not stored in the repository.
  // gab:
  //      SequenceFrame* globalFrame;
      FlatLattice lattice;

      ElementRepository elements;

  private:  
  //    friend class myAcceleratorModelConstructor;
};


#endif
