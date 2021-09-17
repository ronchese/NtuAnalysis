#include "TMPAnalysis/EDM/interface/TMPEDMToNtuple.h"
#include "NtuAnalysis/Write/interface/NtuNANOWriteSteering.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

class TMPNANONtuplizer: public NtuNANOWriteSteering<TMPEDMToNtuple> {

 public:

  explicit TMPNANONtuplizer( const edm::ParameterSet& ps ):
    NtuNANOWriteSteering<TMPEDMToNtuple>( ps ) {
  }

};


//define this as a plug-in
DEFINE_FWK_MODULE( TMPNANONtuplizer );
