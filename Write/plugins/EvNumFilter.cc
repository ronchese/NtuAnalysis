#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "NtuAnalysis/Common/interface/NtuEventSelect.h"
#include "NtuTool/EDM/interface/EDFilterWrapper.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

// system include files
#include <iostream>
#include <fstream>

//
// class declaration
//

class EvNumFilter: public EDFilterWrapper,
                   public NtuEventSelect {

 public:

  explicit EvNumFilter( const edm::ParameterSet& ps ):
   eventList( "evtlist" ),
   listType ( "" ) {
    if ( ps.exists( "eventList" ) )
                     eventList = ps.getParameter<std::string>( "eventList" );
    if ( ps.exists( "listType"  ) )
                     listType  = ps.getParameter<std::string>( "listType"  );
    skipList = ( read( eventList ) && ( listType == "skip" ) );
  }
  ~EvNumFilter() override {}

  void beginJob() override {}
  void endJob() override {}

 private:

  // dummy copy constructor and assignment
  EvNumFilter           ( const EvNumFilter& c ) = delete;
  EvNumFilter& operator=( const EvNumFilter& c ) = delete;

  std::string eventList;
  std::string listType;
  bool skipList;

  bool filter( edm::Event& ev, const edm::EventSetup& es ) override {
    unsigned int runNumber   = ev.id().run();
    unsigned int eventNumber = ev.id().event();
    return ( skipList != find( runNumber, eventNumber ) );
  }

};

//define this as a plug-in
DEFINE_FWK_MODULE( EvNumFilter );
