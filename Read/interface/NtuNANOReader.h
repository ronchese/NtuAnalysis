#ifndef NtuAnalysis_Read_NtuNANOReader_h
#define NtuAnalysis_Read_NtuNANOReader_h

#include "NtuTool/Read/interface/NANOTreeReader.h"
#include <iostream>
#include <string>

template <class T>
class NtuNANOReader: public T, public NANOTreeReader {

 public:

  NtuNANOReader() {
  }
  ~NtuNANOReader() override {}

  void beginJob() override {
    T::setupNtuple();
    T::beginJob();
    return;
  }

  bool getEntry( int ientry ) override {
    return T::getEntry( ientry );
  };

 private:

  // dummy copy constructor and assignment
  NtuNANOReader           ( const NtuNANOReader& ) = delete;
  NtuNANOReader& operator=( const NtuNANOReader& ) = delete;

};

#endif // NtuAnalysis_Read_NtuNANOReader_h
