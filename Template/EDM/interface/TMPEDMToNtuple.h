#ifndef TMPAnalysis_EDM_TMPEDMToNtuple_h
#define TMPAnalysis_EDM_TMPEDMToNtuple_h

// the following header files must appear in the following order, due to
// cross-dependencies through preprocessor macro definition: an ugly 
// situation, but didn't find any better solution to avoid both code 
// duplication and excessive code fragmentation in a large number of 
// source files
#include "NtuAnalysis/Write/interface/NtuEDMAnalyzer.h"
#include "NtuAnalysis/Write/interface/NtuEDConsumer.h"
#include "TMPAnalysis/Ntu/bin/TMPAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// header files for examples of getting data from EventSetup
//#include "MagneticField/Engine/interface/MagneticField.h"
//#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
//#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
//#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include <string>
#include <vector>
class TFile;

namespace pat {
  class Muon;
  class Jet;
}

class TMPEDMToNtuple: public TMPAnalyzer,
                      public NtuEDMAnalyzer {

 public:

  template <class T>
  TMPEDMToNtuple( const edm::ParameterSet& ps, NtuEDConsumer<T>* c ):
   NtuEDMAnalyzer( ps ) {
    // parse ParameterSet and bind ntuple branches to variables
    build( ps );
    // interface to allow uniform access to data in different CMSSW versions
    ObjectConsumer<T>& oc = getConsumer( c );
    oc.template consume< std::vector<pat::Muon> >( gt_muons,
                                                 labelMuons );
    oc.template consume< std::vector<pat::Jet > >( gt_jets ,
                                                 labelJets  );
    // examples of access to data from EventSetup
//    oc.template esConsume< MagneticField,
//                           IdealMagneticFieldRecord >( gt_magField );
//    oc.template esConsume< TransientTrackBuilder,
//                           TransientTrackRecord >( gt_ttB,
//                                                   "TransientTrackBuilder" );
  }
  ~TMPEDMToNtuple() override;

  virtual void beginJob();
  virtual void beginRun();
  virtual void read( const edm::EventBase& ev );
  virtual void endRun();
  virtual void endJob();

 private:

  template <class PATObject> class CompareByPt {
   public:
    bool operator()( const PATObject* l, const PATObject* r ) {
      return l->pt() > r->pt();
    }
  };

  std::string labelMuons;
  std::string labelJets;

  edm::Handle< std::vector<pat::Muon> > muons;
  edm::Handle< std::vector<pat::Jet > > jets;
  // examples of data to get from EventSetup
//  edm::ESHandle<TransientTrackBuilder>  ttB;
//  edm::ESHandle<MagneticField> magField;

  // interfaces to allow uniform access to data in different CMSSW versions
  NtuEDToken < std::vector<pat::Muon> > gt_muons;
  NtuEDToken < std::vector<pat::Jet > > gt_jets;
  // examples of tokens to get data from EventSetup
//  NtuESToken< MagneticField,
//              IdealMagneticFieldRecord > gt_magField;
//  NtuESToken< TransientTrackBuilder,
//              TransientTrackRecord >     gt_ttB;

  void build( const edm::ParameterSet& ps );

  void fillMuons();
  void fillJets();

};

#endif // TMPAnalysis_EDM_TMPEDMToNtuple_h
