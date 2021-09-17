#include "TMPAnalysis/EDM/interface/TMPEDMToNtuple.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include <iostream>
#include <sstream>
#include <map>

using pat::Muon;
using pat::Jet;

using namespace std;

void TMPEDMToNtuple::build( const edm::ParameterSet& ps ) {

  cout << "TMPEDMToNtuple::TMPEDMToNtuple" << endl;

  // GET_PARAMETER( X, D ) and GET_UNTRACKED( X, D )
  // are preprocessor macros, equivalent to:
  //     - look in the edm::ParameterSet for a parameter with label "X",
  //       tracked or untracked respectively and use it to set variable X,
  //       otherwise use the default value D;
  //     - set a local user parameter with the same label and value.
  // The same can be achieved calling the function getParameter:
  // getParameter<T>( "X", X, D,  true ); // for   tracked parameters
  // getParameter<T>( "X", X, D, false ); // for untracked parameters
  // The reason for using macros is to avoid the repetition of X and
  // let the preprocessor duplicate/stringify it.

  GET_UNTRACKED( verbose, "false" );

  // get label of muons collection and
  // switch on muon blocklet if not null
  GET_PARAMETER( labelMuons, "" );
  use_muons = ( labelMuons != "" );
  setUserParameter( "use_muons", use_muons ? "t" : "f" );

  // get label of jets collection and
  // switch on muon blocklet if not null
  GET_PARAMETER( labelJets , "" );
  use_jets = ( labelJets != "" );
  setUserParameter( "use_jets", use_jets ? "t" : "f" );

  // get ptCut and set the corresponding user parameter,
  // of course the default value given here is from the edm::ParameterSet
  // point of view, it has no relation with the default values set in
  // TMPAnalyzer and TMPAnalyzerUtil constructors
  GET_PARAMETER( ptCut, "15.0" );

  // The function "setupNtuple()" is defined in TMPAnalyzerUtil ,
  // it retrieves the "use_..." boolean flags and choose which TTree branches
  // are actually written to the ntuple file.
  setupNtuple();

}


TMPEDMToNtuple::~TMPEDMToNtuple() {
}


void TMPEDMToNtuple::beginJob() {

  TMPAnalyzer::beginJob();
  NtuEDMAnalyzer::beginJob();

  return;

}


void TMPEDMToNtuple::beginRun() {
  return;
}


void TMPEDMToNtuple::read( const edm::EventBase& ev ) {

  nMuons      = 0;
  nJets       = 0;
  if ( use_muons ) fillMuons();
  if ( use_jets  ) fillJets ();

  return;

}


void TMPEDMToNtuple::endRun() {
  return;
}


void TMPEDMToNtuple::endJob() {
  TMPAnalyzer::endJob();
  NtuEDMAnalyzer::endJob();
  return;
}


void TMPEDMToNtuple::fillMuons() {

  float pt;
  float eta;
  float phi;
  float xs = 0.0;
  float ys = 0.0;
  float zs = 0.0;

  if ( labelMuons == "RANDOM" ) {

    // set seed
    static bool seed = true;
    if ( seed ) {
      srandom( 1 );
      seed = false;
    }

    // generate random momenta
    float pm = 1.0e+30;
    while ( ( pt = -50.0 * log ( random() * 1.0 / RAND_MAX ) ) < pm ) {
      if ( ( pt < 5.0 ) && !nMuons ) break;
      muoPt ->push_back( pm = pt );
      eta = random() * 5.0        / RAND_MAX - 2.5;
      phi = random() * 2.0 * M_PI / RAND_MAX - M_PI;
      muoEta->push_back( eta );
      muoPhi->push_back( phi );
      float px;
      float py;
      float pz;
      // this function is defined in NtuAnalysis/Commin/interface/NtuUtil.h
      convSpheCart( pt, eta, phi, px, py, pz );
      xs += px;
      ys += py;
      zs += pz;
      muoPx[nMuons] = px;
      muoPy[nMuons] = py;
      muoPz[nMuons] = pz;
      ++nMuons;
    }

  }

  else {

    // get muons through an interface to access data by label or by token
    // according to CMSSW version
    gt_muons.get( currentEvBase, muons );
    bool vMuons = muons.isValid();

    // store muons info
    int iObj;
    int nObj = ( vMuons ? muons->size() : 0 );
    muoPt ->resize( nObj );
    muoEta->resize( nObj );
    muoPhi->resize( nObj );
    if ( !vMuons ) {
      cout << "invalid muons: " << getUserParameter( "labelMuons" ) << endl;
      return;
    }

    vector<const Muon*> muonPtr;
    muonPtr.resize( nObj );
    for ( iObj = 0; iObj < nObj; ++iObj ) muonPtr[iObj] =
                                       &( muons->at( iObj ) );

    CompareByPt<Muon> muoComp; // defined in TMPEDMToNtuple.h
    sort( muonPtr.begin(), muonPtr.end(), muoComp );

    nMuons = nObj;
    muoPt ->resize( nMuons );
    muoEta->resize( nMuons );
    muoPhi->resize( nMuons );
    for ( iObj = 0; iObj < nObj; ++iObj ) {
      const Muon& muon = *muonPtr[iObj];
      muoPt ->at( iObj ) = pt  = muon.pt ();
      muoEta->at( iObj ) = eta = muon.eta();
      muoPhi->at( iObj ) = phi = muon.phi();
      float px;
      float py;
      float pz;
      convSpheCart( pt, eta, phi, px, py, pz );
      xs += px;
      ys += py;
      zs += pz;
      muoPx[iObj] = px;
      muoPy[iObj] = py;
      muoPz[iObj] = pz;
    }

  }

  pSum[0] = xs;
  pSum[1] = ys;
  pSum[2] = zs;

  return;

}


void TMPEDMToNtuple::fillJets() {

  // get muons through an interface to access data by label or by token
  // according to CMSSW version
  gt_jets.get( currentEvBase, jets );
  bool vJets = jets.isValid();

  // store jets info

  int iObj;
  int nObj = ( vJets ? jets->size() : 0 );
  jetPt  ->resize( 0 );
  if ( !vJets ) {
    cout << "invalid jets" << getUserParameter( "labelJets" ) << endl;
    return;
  }

  vector<const Jet*> jetPtr;
  jetPtr.resize( nObj );
  for ( iObj = 0; iObj < nObj; ++iObj ) jetPtr[iObj] = &( jets->at( iObj ) );

  CompareByPt<Jet> jetComp;
  sort( jetPtr.begin(), jetPtr.end(), jetComp );

  nJets = nObj;
  jetPt->resize( nJets );
  for ( iObj = 0; iObj < nObj; ++iObj ) {
    const Jet& jet = *jetPtr[iObj];
    jetPt->at( iObj ) = jet.pt();
  }

  return;

}


