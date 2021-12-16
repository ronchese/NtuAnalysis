#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "TMPAnalyzerUtil.h"

TMPAnalyzerUtil::TMPAnalyzerUtil() {

  // User parameters are set as names associated to a string,
  // see TMPAnalyzer.cc for more details.
  setUserParameter( "use_muons", "true"  );
  setUserParameter( "use_jets" , "false" );

}


TMPAnalyzerUtil::~TMPAnalyzerUtil() {
}


void TMPAnalyzerUtil::setupNtuple() {

  // User parameters are retrieved by using their names;
  // see TMPAnalyzer.cc for more details.
  getUserParameter( "use_muons", use_muons );
  getUserParameter( "use_jets" , use_jets  );

  // The function "initTree()" is defined in TMPNtupleBranch ,
  // it uses the boolean flags to choose which TTree branches are
  // actually written/read to/from the ntuple file.
  initTree();

  return;

}


void TMPAnalyzerUtil::beginJob() {

  NtuInterface< TMPNtupleBranch<WrapperBase> >::beginJob();

  return;

}


// Optional: pre-selection, with minimal data process 
// before full ntuple entry reading
bool TMPAnalyzerUtil::preSelect( int ientry ) {
  // get number of muons
  if ( use_muons ) // get nMuons from ntuple only if the block is active
  getEntry( &b_nMuons, ientry );
  std::cout << nMuons  << " muons" << std::endl;
  // skip events with no muons
  if ( !nMuons ) return false;
  return true;
}
