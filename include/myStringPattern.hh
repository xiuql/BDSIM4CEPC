/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file utility\StringPattern.h
 * last modified 05/09/00  12:30:39
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

#ifndef myStringPattern_h
#define myStringPattern_h 1

//#include "merlin_config.h"

#include <string>
#include <vector>
#include <utility>
#include <iostream>

using std::string;
using std::ostream;

//	A simple string pattern which represents a reduced set
//	of the standard UNIX regular expression syntax.
//	Currently supported is the single wild-card '*', which
//	matches any number (including zero) of any character.

class myStringPattern 
{
  public:
      //	Constructor taking the string pattern.
      myStringPattern (const std::string& s);


      //	Match operation. Returns true if the pattern matched the
      //	string.
      bool Match (const std::string& s) const;

      //	Operator form of match().
      bool operator () (const std::string& s) const;

      //	Outputs to os the original pattern.
      friend ostream& operator << (ostream& os, const myStringPattern& pattern);

      operator string () const;

      bool operator < (const myStringPattern& rhs) const;

      bool operator == (const myStringPattern& rhs) const;

    // Data Members for Class Attributes

      //	The wildcard character (default ='*').
      static char wcchar;

  protected:
  private:
    // Data Members for Class Attributes

      //	A vector of literal strings. The pattern is split into
      //	literals by the presence of a '*' character.

      std::vector<string> patterns;
      //	Used to indicate if the first/last character of the
      //	string pattern were wildcards.

      std::pair<bool,bool> wcterm;
      //	Set to true if this pattern is a simple literal string
      //	(no wild cards).

      bool isLiteral;

      std::string str;

  private:  

};

// Class myStringPattern 


inline bool myStringPattern::operator () (const std::string& s) const
{
	return Match(s);
}

inline myStringPattern::operator string () const
{
	return str;
}

inline bool myStringPattern::operator < (const myStringPattern& rhs) const
{
	return str<rhs.str;
}

inline bool myStringPattern::operator == (const myStringPattern& rhs) const
{
	return str==rhs.str;
}

// Utility function for splitting a single string into a list of delimited strings.
// The return pair indicates if the first and last characters of str are dchar.
std::pair<bool,bool> DelimitString(const string& str, char dchar, std::vector<string>& result);


#endif
