#ifndef NtuAnalysis_Common_NtuAnalyzerUtil_h
#define NtuAnalysis_Common_NtuAnalyzerUtil_h

#include "NtuAnalysis/Common/interface/NtuEventHeader.h"
#include "NtuAnalysis/Common/interface/NtuEventSelect.h"

class TBranch;
class TTree;

namespace edm {
  class ParameterSet;
  class Run;
  class Event;
  class EventBase;
  class EventSetup;
}

class NtuAnalyzerUtil: public NtuEventSelect,
                       public virtual NtuEventHeader {

 public:

  NtuAnalyzerUtil();
  ~NtuAnalyzerUtil() override;

 protected:

  const edm::ParameterSet* parameterSet ;
  const edm::Run         * currentRun;
  const edm::Event       * currentEvent;
  const edm::EventBase   * currentEvBase;
  const edm::EventSetup  * currentEvSetup;

  virtual void getHeader( int ientry );

 protected:

  // flag to use event list as skip list
  bool skipList;

  TTree** currentTPtr;

 private:

  // dummy copy constructor and assignment
  NtuAnalyzerUtil           ( const NtuAnalyzerUtil& ) = delete;
  NtuAnalyzerUtil& operator=( const NtuAnalyzerUtil& ) = delete;


};

#endif // NtuAnalysis_Common_NtuAnalyzerUtil_h

