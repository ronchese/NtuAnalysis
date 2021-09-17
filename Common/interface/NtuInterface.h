#ifndef NtuAnalysis_Common_NtuInterface_h
#define NtuAnalysis_Common_NtuInterface_h

#include "NtuAnalysis/Common/interface/NtuAnalyzerUtil.h"

#define FULL 2
#define BARE 3

#  if UTIL_USE == FULL

// use all the functionalities provided by NtuTool
#include "NtuTool/Common/interface/TreeWrapper.h"
typedef TreeWrapper WrapperBase;

#elif UTIL_USE == BARE

// get the bare ntuple definition, with no usage of other utilities
// in addition to the analysis specific ones
// "NtuLightReader" simply forward calls directly to ROOT with no 
// additional operation
#include "NtuAnalysis/Common/interface/NtuLightReader.h"
typedef NtuLightReader WrapperBase;

#else
#error use -D UTIL_USE=FULL or -D UTIL_USE=BARE
#endif

#include <iostream>
#include <string>

template <class T>
class NtuInterface: public virtual NtuAnalyzerUtil,
                    public virtual T {

 public:

  NtuInterface() {}
  ~NtuInterface() override {}

#  if UTIL_USE == FULL
 protected:
#endif

  void beginJob() override {
    std::string evl = this->getUserParameter( "eventList" );
    bool flag = read( evl );
    skipList = ( flag && ( this->getUserParameter( "listType" ) == "skip" ) );
    return;
  }

  bool lightAnalyze( int entry, int event_file ) {
    bool acceptEv = this->analyze( entry, event_file, this->analyzedEvts++ );
    if ( acceptEv ) this->acceptedEvts++;
    return acceptEv;
  }

  virtual bool getEntry( int ientry ) {
    if ( currentEvBase != nullptr ) return false;
    if ( currentEvent  != nullptr ) return false;
    getHeader( ientry );
    if ( skipList == find( runNumber, eventNumber ) ) return false;
    if ( !preSelect( ientry ) ) return false;
    this->currentTree()->GetEntry( ientry );
    return true;
  }

  virtual void getEntry( TBranch** branch, int ientry ) {
    if ( currentEvBase != nullptr ) return;
    if ( currentEvent  != nullptr ) return;
    (*branch)->GetEntry( ientry );
    this->process( branch, ientry );
  }

  virtual bool preSelect( int ientry ) {
    return true;
  }

#  if UTIL_USE == BARE
 protected:
#endif

  void dumpEvent( std::ostream& os,
                  const std::string& label = std::string( "" ),
                  bool endLine = true ) {
    os << "run: " << runNumber << " , event: " << eventNumber;
    if ( label.size() ) os << " " << label;
    if ( endLine ) os << std::endl;
    return;
  }

 private:

  // dummy copy constructor and assignment
  NtuInterface           ( const NtuInterface& ) = delete;
  NtuInterface& operator=( const NtuInterface& ) = delete;

};


#endif // NtuAnalysis_Common_NtuInterface_h

