#include "TMPAnalysis/EDM/interface/TMPEDMToNtuple.h"
#include "NtuAnalysis/Write/interface/NtuWriteSteering.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

class TMPNtuplizer: public NtuWriteSteering<TMPEDMToNtuple> {

 public:

  explicit TMPNtuplizer( const edm::ParameterSet& ps ):
    NtuWriteSteering<TMPEDMToNtuple>( ps ) {
  }
  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions ) {
    edm::ParameterSetDescription pSetDesc;
    pSetDesc.addUntracked<std::string>(  "ntuName", "ntu.root" );
    pSetDesc.addUntracked<std::string>( "histName", "his.root" );
    pSetDesc.addUntracked<bool       >(  "verbose", true );
    TMPEDMToNtuple::fillDescriptions( descriptions, pSetDesc );
    descriptions.add( "process.tmpAnalyzer", pSetDesc );
  }

};


//define this as a plug-in
DEFINE_FWK_MODULE( TMPNtuplizer );
