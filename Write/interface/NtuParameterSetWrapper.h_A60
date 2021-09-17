#ifndef NtuAnalysis_Write_NtuParameterSetWrapper_h
#define NtuAnalysis_Write_NtuParameterSetWrapper_h
/** \class PDNtuParameterSetWrapper
 *
 *  Description: 
 *
 *
 *  $Date: 2019-05-28 14:55:56 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "FWCore/PythonParameterSet/interface/MakePyBind11ParameterSets.h"

//---------------
// C++ Headers --
//---------------


//              ---------------------
//              -- Class Interface --
//              ---------------------

class NtuParameterSetWrapper {

 public:

  /** Operations
   */
  static std::unique_ptr<edm::ParameterSet> readPSetsFrom(
                                            const std::string& fileOrString ) {
    return edm::cmspybind11::readPSetsFrom( fileOrString );
  }

};

//#include "PDAnalysis/EDM/interface/PDNtuParameterSetWrapper.hpp"

#endif // NtuAnalysis_Write_NtuParameterSetWrapper_h


