#include "TMPAnalysis/EDM/interface/TMPEDMToNtuple.h"
#include "NtuAnalysis/Write/interface/NtuEDMWriteSteering.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

class TMPEDMNtuplizer: public NtuEDMWriteSteering<TMPEDMToNtuple> {

 public:

  explicit TMPEDMNtuplizer( const edm::ParameterSet& ps ):
    NtuEDMWriteSteering<TMPEDMToNtuple>( ps ) {
  }
  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions ) {
    edm::ParameterSetDescription pSetDesc;
    pSetDesc.addUntracked<std::string>( "histName", "his.root" );
    pSetDesc.addUntracked<bool       >(  "verbose", true );
    TMPEDMToNtuple::fillDescriptions( descriptions, pSetDesc );
    descriptions.add( "process.tmpEDMAnalyzer", pSetDesc );
  }

};


//define this as a plug-in
DEFINE_FWK_MODULE( TMPEDMNtuplizer );
