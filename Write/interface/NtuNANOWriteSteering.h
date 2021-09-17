
#ifndef NtuAnalysis_Write_NtuNANOWriteSteering_h
#define NtuAnalysis_Write_NtuNANOWriteSteering_h

#include "NtuAnalysis/Common/interface/NtuAnalyzerUtil.h"

#include "NtuTool/EDM/interface/NANOTreeWriter.h"

#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "NtuAnalysis/Write/interface/NtuEDConsumer.h"
#include "NtuTool/EDM/interface/EDProducerWrapper.h"

#include <string>
#include <iostream>
#include <fstream>

//
// class declaration
//

template <class T>
class NtuNANOWriteSteering: public NANOTreeWriter,
                            public NtuEDConsumer<EDProducerWrapper>,
                            public T,
                            public virtual NtuAnalyzerUtil {

 public:

  explicit NtuNANOWriteSteering( const edm::ParameterSet& ps );
  ~NtuNANOWriteSteering() override;

  void beginJob() override;
  void endJob() override;

 private:

  // dummy copy constructor and assignment
  NtuNANOWriteSteering           ( const NtuNANOWriteSteering& c ) = delete;
  NtuNANOWriteSteering& operator=( const NtuNANOWriteSteering& c ) = delete;

  int analyzedFile;
  std::string histName;

  void beginRun( const edm::Run  & run, const edm::EventSetup& es ) override;
  void endRun(   const edm::Run  & run, const edm::EventSetup& es ) override;
  bool fill(     const edm::Event&  ev, const edm::EventSetup& es ) override;

};

#include "NtuAnalysis/Write/interface/NtuNANOWriteSteering.hpp"

#endif // NtuAnalysis_Write_NtuNANOWriteSteering_h
