/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file AcceleratorModel\StdComponent\TemplateComponents.h
 * last modified 22/04/99 13:32:11
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

#ifndef TemplateComponents_h
#define TemplateComponents_h 1

//#include "merlin_config.h"


// AcceleratorComponent
#include "AcceleratorModel/myAcceleratorComponent.h"

template <class G>
class TAccCompG : public myAcceleratorComponent  
{
  public:
    typedef G geom_type;

  public:
      TAccCompG (const string& id, G* geom, EMFieldRegion* field = 0);
      TAccCompG (const TAccCompG<G>& rhs);


      TAccCompG<G>& operator = (const TAccCompG<G>& rhs);

      G& GetGeometry ();

      const G& GetGeometry () const;

  protected:
  private:
  private:  
};

template <class G, class F>
class TAccCompGF : public TAccCompG<G>  //## Inherits: <unnamed>%371EF9D2010E
{
  public:

    typedef F field_type;

  public:
      TAccCompGF (const string& id, G* geom, F* field);

      TAccCompGF (const TAccCompGF<G,F>& rhs);


      TAccCompGF<G,F>& operator = (const TAccCompGF<G,F>& rhs);

      F& GetField ();

      const F& GetField () const;

  protected:
  private:
  private:  
};

// Parameterized Class TAccCompG 

template <class G>
inline TAccCompG<G>::TAccCompG (const string& id, G* geom, EMFieldRegion* field)
  : AcceleratorComponent(id,geom,field){}

template <class G>
inline G& TAccCompG<G>::GetGeometry ()
{
	return static_cast<G&>(*itsGeometry);
}

template <class G>
inline const G& TAccCompG<G>::GetGeometry () const
{
	return static_cast<const G&>(*itsGeometry);
}

// Parameterized Class TAccCompGF 

template <class G, class F>
inline TAccCompGF<G,F>::TAccCompGF (const string& id, G* geom, F* field)
  : TAccCompG<G>(id,geom,field){}

template <class G, class F>
inline F& TAccCompGF<G,F>::GetField ()
{
	return static_cast<F&>(*itsField);
}

template <class G, class F>
inline const F& TAccCompGF<G,F>::GetField () const
{
	return static_cast<const F&>(*itsField);
}

// Parameterized Class TAccCompG 

template <class G>
TAccCompG<G>::TAccCompG (const TAccCompG<G>& rhs)
  : AcceleratorComponent(rhs.GetName(),new G(rhs.GetGeometry()),0){}

template <class G>
TAccCompG<G>& TAccCompG<G>::operator = (const TAccCompG<G>& rhs)
{
	if(this!=&rhs) {
		SetName(rhs.GetName());
		GetGeometry() = rhs.GetGeometry();
	}
	return *this;
}

// Parameterized Class TAccCompGF 

template <class G, class F>
TAccCompGF<G,F>::TAccCompGF (const TAccCompGF<G,F>& rhs)
  : TAccCompG<G>(rhs.GetName(),new G(rhs.GetGeometry()), new F(rhs.GetField()))
{}

template <class G, class F>
TAccCompGF<G,F>& TAccCompGF<G,F>::operator = (const TAccCompGF<G,F>& rhs)
{
	if(this!=&rhs) {
		TAccCompG<G>::operator=(rhs);
		GetField() = rhs.GetField();
	}
	return *this;
}

#endif
