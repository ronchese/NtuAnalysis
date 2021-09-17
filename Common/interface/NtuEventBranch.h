#ifndef NtuAnalysis_Common_NtuEventBranch_h
#define NtuAnalysis_Common_NtuEventBranch_h

#include "NtuAnalysis/Common/interface/NtuEventHeader.h"
#include <string>
#include <vector>

template <class T>
class NtuEventBranch: public virtual NtuEventHeader, public virtual T {

 public:

  ~NtuEventBranch() override;

 protected:

  NtuEventBranch() {
    this->setBranch( "runNumber"    , &  runNumber      ,
                     "runNumber/i"  , &b_runNumber       );
    this->setBranch( "lumiSection"  , &  lumiSection    ,
                     "lumiSection/i", &b_lumiSection     );
    this->setBranch( "eventNumber"  , &  eventNumber    ,
                     "eventNumber/i", &b_eventNumber     );
  }

 private:

  // dummy copy constructor and assignment
  NtuEventBranch           ( const NtuEventBranch& td ) = delete;
  NtuEventBranch& operator=( const NtuEventBranch& td ) = delete;

};

template <class T>
NtuEventBranch<T>::~NtuEventBranch() {
}

#endif // NtuAnalysis_Common_NtuEventBranch_h

