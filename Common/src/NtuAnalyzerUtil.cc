#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "NtuAnalysis/Common/interface/NtuAnalyzerUtil.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"

NtuAnalyzerUtil::NtuAnalyzerUtil() {
  currentRun     = nullptr;
  currentEvent   = nullptr;
  currentEvBase  = nullptr;
  currentEvSetup = nullptr;
}


NtuAnalyzerUtil::~NtuAnalyzerUtil() {
}


void NtuAnalyzerUtil::getHeader( int ientry ) {
  if ( this->b_runNumber   != nullptr ) this->b_runNumber  ->GetEntry( ientry );
  if ( this->b_lumiSection != nullptr ) this->b_lumiSection->GetEntry( ientry );
  if ( this->b_eventNumber != nullptr ) this->b_eventNumber->GetEntry( ientry );
  return;
}

