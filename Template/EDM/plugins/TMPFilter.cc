#include "TMPAnalysis/EDM/interface/TMPEDMToNtuple.h"
#include "NtuAnalysis/Write/interface/NtuFilter.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

class TMPFilter: public NtuFilter<TMPEDMToNtuple> {

 public:

  explicit TMPFilter( const edm::ParameterSet& ps ):
    NtuFilter<TMPEDMToNtuple>( ps ) {
  }
  static void fillDescriptions( edm::ConfigurationDescriptions& descriptions ) {
    edm::ParameterSetDescription pSetDesc;
    pSetDesc.addUntracked<std::string>(  "ntuName", "ntu.root" );
    pSetDesc.addUntracked<std::string>( "histName", "his.root" );
    pSetDesc.addUntracked<bool       >(  "verbose", true );
    TMPEDMToNtuple::fillDescriptions( descriptions, pSetDesc );
    descriptions.add( "process.bphvtxFilter", pSetDesc );
  }

};


//define this as a plug-in
DEFINE_FWK_MODULE( TMPFilter );
