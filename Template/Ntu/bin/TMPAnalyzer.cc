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

// Code lines to skim ntuple and/or produce a reduced ntuple are
// activated/deactivated by the preprocessor
// macros "SKIM_NTUPLE" and "REDUCE_NTUPLE" respectively;
// they're set in the header file.
// Macros are used just to flag the relevant code lines, 
// normally the code would not make use of the preprocessor for this.

#if REDUCE_NTUPLE != 0
#include "TMPReducedNtupleWriter.h" // reduced ntuple
#endif

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

#if SKIM_NTUPLE != 0
  dropBranch( "jet*" ); // drop some branch from the skimmed ntuple,
                        // if required, a limited support for wild characters
                        // is provided
  initWSkim( new TFile( "skim.root", "RECREATE" ) ); // open a file for 
                                                     // the skimmed ntuple
#endif

#if REDUCE_NTUPLE != 0
  rWriter = new TMPReducedNtupleWriter;           // create reduced ntuple
  rWriter->open( "reducedNtu.root", "RECREATE" ); // open file
                                                  // for reduced ntuple
#endif

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
// The macro "UTIL_USE" is automatically set in other source files,
// according to the environment where this class is being used.
#  if UTIL_USE == FULL
  // The whole ntuple content can be automatically reset at zero,
  // and std::vectors are cleared, by calling the "autoReset()" function.
  // This option is not available when not using the full utility.
  autoReset();
#elif UTIL_USE == BARE
  // If ntu content is to be reset or cleared, that should be done manually
  // when not using the full utility, i.e. when using this class as a 
  // simple ROOT macro.
  // This can be skipped, anyway, if there is not a specific reason to 
  // reset or clear all data before overwriting them with the ntuple content.
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
  float mupt;
  float mueta;
  float muphi;
  float ptmumax = -1.0;
  float ptmu2nd = -1.0;
  float angleMin = 4.0;
  unsigned int iJet;
  int mJet = -1;
  int mMuon = -1;
  for ( iMuon = 0; iMuon < nMuons; ++iMuon ) {
    cout << "muon " << iMuon << '/' << nMuons << " : "
         << muoPt ->at( iMuon ) << ' '
         << muoEta->at( iMuon ) << ' '
         << muoPhi->at( iMuon ) << " / "
         << muoPx      [iMuon]  << ' '
         << muoPy      [iMuon]  << ' '
         << muoPz      [iMuon]  << endl;
    mupt  = muoPt ->at( iMuon );
    mueta = muoEta->at( iMuon );
    muphi = muoPhi->at( iMuon );
    hptmu->Fill( mupt );
    if( mupt > ptmu2nd ) {
      if( mupt > ptmumax ) {
        ptmu2nd = ptmumax;
        ptmumax = mupt;
      }
      else {
        ptmu2nd = mupt;
      }
    }
    for ( iJet = 0; iJet < nJets; ++iJet ) {
      // Angle between muon and jet: the "angleSphe" function is declared
      // in NtuAnalysis/Common/interface/NtuUtil.h , but ROOT functions
      // could be used as well
      float angleMuJ = angleSphe( mupt, mueta, muphi,
                                  jetPt ->at( iJet ),
                                  jetEta->at( iJet ),
                                  jetPhi->at( iJet ) );
      if ( angleMuJ < angleMin ) {
	mMuon = iMuon;
        mJet  = iJet;
        angleMin = angleMuJ;
      }
    }
  }
  std::cout << "min. angle: "   << angleMin
            << " between muon " << mMuon
            << " and jet "      << mJet << endl;
  hptmumax->Fill( ptmumax );
  hptmu2nd->Fill( ptmu2nd );	
  cout << "sum: "
       << pSum[0] << ' '
       << pSum[1] << ' '
       << pSum[2] << std::endl;

#if REDUCE_NTUPLE != 0
  // set reduced ntuple data
  rWriter->idMuon = mMuon;
  rWriter->idJet  = mJet;
  rWriter->angle  = angleMin;
  // fill reduced ntuple
  rWriter->fill();
#endif

  flag = ptmumax > ptCut;

#if SKIM_NTUPLE != 0
  // additional instruction to skim the ntuple
  if ( flag ) fillSkim(); // keep this event or not according with the 
                          // results of the analysis done so far; 
                          // here the same logical value returned by the
                          // function is used, so that the number of selected
                          // entries given at the end of job corresponds to
                          // to the number of entries in the skimmed ntuple,
                          // but different choices can be done as well
#endif

  return flag;

}


void TMPAnalyzer::endJob() {

#if SKIM_NTUPLE != 0
  closeSkim(); // close the skimmed ntuple file
#endif

#if REDUCE_NTUPLE != 0
  rWriter->close(); // close file for reduced ntuple
#endif

  return;

}


// The following function is optional and it's aimed at saving histograms
// when data processing is finished.
// Actually it's needed only when not using the full utility, otherwise
// the function could simply be removed, relying on the default behaviour.
void TMPAnalyzer::save() {
// The macro "UTIL_USE" is automatically set in other source files,
// according to the environment where this class is being used.
#  if UTIL_USE == FULL
  // All histos are automatically saved by calling the "autoSave()" function,
  // see the "book()" function for more informations.
  // This option is not available when not using the full utility, i.e. when
  // using this class as a simple ROOT macro;
  // on the contrary it's the default when the full utility i used, 
  // so in that case the whole function could be simply removed.
  autoSave();
#elif UTIL_USE == BARE
  // When not using the full utility, i.e. when using this class as a
  // simple ROOT macro, histograms are to be saved explicitly.
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

