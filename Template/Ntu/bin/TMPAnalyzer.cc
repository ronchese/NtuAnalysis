// TMPAnalyzer class to process a ntuple entry and return a true/false flag:
//     - when writing the ntuple the flag is used to actually write
//       the entry on the ROOT file, for traditional flat ntuples, or 
//       put the informations inside the Event for EDM ntuples or NANOAOD;
//     - when reading the ntuple the value is used just to count events;
//     - the value can be used to skim the ntuple.
//
// Another TMPAnalyzerUtil class is also provided, for the following purposes:
//     - use configuration parameters to choose which blocks are actually 
//       to be read, see the corresponding code files for an example;
//     - provide any utility function tightly bound to the ntuple format,
//       e.g. to navigate through indices, compute complex quantites from
//       basic ones and so on.

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "TMPAnalyzer.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
//#include "TCanvas.h"
#include "Math/LorentzVector.h"

using namespace std;

TMPAnalyzer::TMPAnalyzer() {

  cout << "new TMPAnalyzer" << endl;

  // User parameters are set as names associated to a string:
  //     - numeric values are converted internally as strings;
  //     - default values can be set in the analyzer class constructor,
  //       values can be given as strings, also for numerical values;
  //     - default values can be set also in the TMPAnalyzerUtil constructor,
  //       the ones in TMPAnalyzer constructor override the ones in 
  //       TMPAnalyzerUtil .

  setUserParameter( "verbose", "f" );
  setUserParameter( "ptCut", 20.0 );

}


TMPAnalyzer::~TMPAnalyzer() {
}



void TMPAnalyzer::beginJob() {

  TMPAnalyzerUtil::beginJob();

  // User parameters are retrieved as strings by using their names;
  // numeric parameters ( int, float or whatever ) can be directly set
  // by passing the corresponding variable, e.g.:
  //   getUserParameter( "name", x );
  // or secifying the type as a template parameter, e.g.
  //   i = getUserParameter<int>( "name" );

  getUserParameter( "verbose", verbose );
  getUserParameter( "ptCut"  , ptCut   );
// alternatively:
//  verbose = getUserParameter<bool> ( "verbose" );
//  ptCut   = getUserParameter<float>( "ptCut"   );

  return;

}


void TMPAnalyzer::book() {

  // Histo is automatically marked for saving on file by putting
  // "autoSavedObject" in front of the its creation.
  // This option is uneffective when not using the full utility.

  autoSavedObject =
  hptmumax        = new TH1D( "hptmumax", "ptmumax" ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu2nd        = new TH1D( "hptmu2nd", "ptmu 2nd",  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu           = new TH1D( "hptmu"   , "ptmu"    ,  50, 0.0, 100.0 );

  return;

}


void TMPAnalyzer::reset() {
#  if UTIL_USE == FULL
  // The whole ntuple content can be automatically reset at zero,
  // and std::vectors are cleared, by calling the "autoReset()" function.
  // This option is not available when not using the full utility.
  autoReset();
#elif UTIL_USE == BARE
  // If ntu content is to be reset or cleared, that should be done manually
  // when not using the full utility.
  nMuons = 0;
  muoPt ->clear();
  muoEta->clear();
  muoPhi->clear();
#endif
  return;
}


bool TMPAnalyzer::analyze( int entry, int event_file, int event_tot ) {

  if ( verbose ) {
    cout << " +++++++++++++++++++++++++++ " << endl;
    cout << "entry: "
         << entry << " " << event_file << " " << event_tot << endl;
    cout << "run: " <<   runNumber << " , "
         << "evt: " << eventNumber << endl;
  }
  else {
//    if ( !( event_file % 10000 ) || !( event_tot % 10000 ) )
    if ( !( event_tot % 10000 ) && event_tot )
      cout << event_file << " " << event_tot << endl;
  }

  // flag to be set "true" or "false" for events accepted or rejected
  bool flag;

  flag = true;

  unsigned int iMuon;
  float ptmu;
  float ptmumax = -1.0;
  float ptmu2nd = -1.0;
  for ( iMuon = 0; iMuon < nMuons; ++iMuon ) {
    cout << "muon " << iMuon << '/' << nMuons << " : "
         << muoPt ->at( iMuon ) << ' '
         << muoEta->at( iMuon ) << ' '
         << muoPhi->at( iMuon ) << " / "
         << muoPx      [iMuon]  << ' '
         << muoPy      [iMuon]  << ' '
         << muoPz      [iMuon]  << endl;
    ptmu = muoPt->at( iMuon );
    hptmu->Fill( ptmu );
    if( ptmu > ptmu2nd ) {
      if( ptmu > ptmumax ) {
        ptmu2nd = ptmumax;
        ptmumax = ptmu;
      }
      else {
        ptmu2nd = ptmu;
      }
    }
  }
  hptmumax->Fill( ptmumax );
  hptmu2nd->Fill( ptmu2nd );	
  cout << "sum: "
       << pSum[0] << ' '
       << pSum[1] << ' '
       << pSum[2] << std::endl;

  flag = ptmumax > ptCut;

  return flag;

}


void TMPAnalyzer::endJob() {
  return;
}


void TMPAnalyzer::save() {
#  if UTIL_USE == FULL
  // All histos are automatically saved by calling the "autoSave()" function,
  // see the "book()" function for more informations.
  // This option is not available when not using the full utility.
  autoSave();
#elif UTIL_USE == BARE
  // When not using the full utility histos are to be saved explicitly
  hptmumax->Write();
  hptmu2nd->Write();
  hptmu   ->Write();
#endif
  return;
}

/*
// The following function is optional and it's aimed at making some plots
// when data processing is finished.
// If implemented, the Gpad library must be added to the
//   TMPAnalysis/Ntu/BuildFile.xml
// with the instruction
// <flags LDFLAGS="-lGpad"/>
// or
// <lib   name="Gpad"/>
// DO NOT leave here an empty function, or a function without any ROOT object
// drawing, otherwise the execution could get stuck in some situations.
void TMPAnalyzer::plot() {
  TCanvas* can = new TCanvas( "muoPt", "muoPt", 800, 600 );
  can->cd();
  can->Divide( 1, 2 );
  can->cd( 1 );
  hptmumax->Draw();
  can->cd( 2 );
  hptmu2nd->Draw();
  can->Print( "muoPt.pdf" );
  return;
}
*/

