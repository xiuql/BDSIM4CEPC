#ifndef BDSBunchFactory_h
#define BDSBunchFactory_h

#include "BDSOutputFormat.hh"

class BDSOutputBase;

/**
 * @brief factory class for BDSOutput
 * 
 * @author Jochem Snuverink <Jochem.Snuverink@rhul.ac.uk>
 */

class BDSOutputFactory {

public:
  /// factory method
  static BDSOutputBase* createOutput(BDSOutputFormat format);
};

#endif
