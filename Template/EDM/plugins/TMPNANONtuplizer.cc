#include "TMPAnalysis/EDM/interface/TMPEDMToNtuple.h"
#include "NtuAnalysis/Write/interface/NtuNANOWriteSteering.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

class TMPNANONtuplizer: public NtuNANOWriteSteering<TMPEDMToNtuple> {

 public:

  explicit TMPNANONtuplizer( const edm::ParameterSet& ps ):
    NtuNANOWriteSteering<TMPEDMToNtuple>( ps ) {
  }
  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions ) {
    edm::ParameterSetDescription pSetDesc;
    pSetDesc.addUntracked<std::string>( "histName", "his.root" );
    pSetDesc.addUntracked<bool       >(  "verbose", true );
    TMPEDMToNtuple::fillDescriptions( descriptions, pSetDesc );
    descriptions.add( "process.tmpNtuTable", pSetDesc );
  }

};


//define this as a plug-in
DEFINE_FWK_MODULE( TMPNANONtuplizer );
