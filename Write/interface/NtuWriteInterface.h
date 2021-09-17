#ifndef NtuAnalysis_Write_NtuWriteInterface_h
#define NtuAnalysis_Write_NtuWriteInterface_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "NtuAnalysis/Write/interface/NtuEDConsumer.h"
#include "NtuTool/Common/interface/TreeWriter.h"

template <class T>
class NtuWriteInterface: public T,
                         public TreeWriter {

 public:

  template <class C>
  NtuWriteInterface( const edm::ParameterSet& ps, NtuEDConsumer<C>* cb );
  ~NtuWriteInterface() override;

  virtual void beginJob() override;

  virtual void openNtuple( const std::string& ntuName );

  bool analyzeEDM( const edm::EventBase& ev,
                   int ientry, int event_file ) override;

  virtual void writeNtuple();
  virtual void closeNtuple();

  virtual void endJob() override;

 private:

  // dummy copy constructor and assignment
  NtuWriteInterface           ( const NtuWriteInterface& c ) = delete;
  NtuWriteInterface& operator=( const NtuWriteInterface& c ) = delete;

  std::string ntuName;
  TFile* file;

  bool dumpNtuple;

};

#include "NtuAnalysis/Write/interface/NtuWriteInterface.hpp"

#endif // NtuAnalysis_Write_NtuWriteInterface_h
