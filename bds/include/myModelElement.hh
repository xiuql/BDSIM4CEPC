/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file AcceleratorModel\myModelElement.h
 * last modified 10/06/99 21:06:05
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


#ifndef myModelElement_h
#define myModelElement_h 1

//#include "merlin_config.h"

#include <string>

using std::string;


//	Root class for all elements/components which are used to
//	construct an AcceleratorModel. All myModelElement objects
//	are characterised by a type string and an identifier
//	(name). The type string identifies the type of element
//	(class), while the name is specific to an instance of
//	that element type.

class myModelElement 
{
  public:
      //	Constructor taking the name of the element.
      explicit myModelElement (const string& aName);

      //	Constructor taking the name of the element.
      myModelElement ();

      virtual ~myModelElement ();

      //	Return the name of the element.
      virtual const string& GetName () const;

      //	Return the type string for the element.
      virtual const string& GetType () const = 0;

      //	Return the qualified name of the component. The
      //	qualified name has the form typestr.namestr.
      string GetQualifiedName () const;

      //	Virtual constructor.
      virtual myModelElement* Copy () const = 0;

      //	Set the name of the component.
      void SetName (const string& name);

  protected:

      //	Initialise the myModelElement with the specified name.
      void Init (const string& aName);

    // Data Members for Class Attributes

      string id;

  private:
  private:  
};

// Class myModelElement 

inline myModelElement::myModelElement (const string& aName)
  : id(aName)
{}

inline myModelElement::myModelElement ()
{}

inline myModelElement::~myModelElement ()
{
	// nothing to do
}



inline const string& myModelElement::GetName () const
{
	return id;
}

inline string myModelElement::GetQualifiedName () const
{
	return GetType()+'.'+GetName();
}

inline void myModelElement::SetName (const string& name)
{
	id=name;
}

inline void myModelElement::Init (const string& aName)
{
	id=aName;
}

// Class myModelElement 


// utility macros:
// GetType() implementation
#define _TYPESTR(s) static const string typestr(#s); return typestr;


#endif
