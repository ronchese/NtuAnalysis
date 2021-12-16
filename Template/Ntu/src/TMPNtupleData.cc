#include <iostream>

using namespace std;

#include "TMPAnalysis/Ntu/interface/TMPNtupleData.h"

TMPNtupleData::TMPNtupleData() {

  // muons
  nMuons = 20; // max number of muons, used to create native arrays
  muoPt  = new vector<number>;
  muoEta = new vector<number>;
  muoPhi = new vector<number>;
  muoPx  = new number[nMuons]();
  muoPy  = new number[nMuons]();
  muoPz  = new number[nMuons]();

  pSum = new number[3];

  // jets
  nJets = 0;
  jetPt  = new vector<number>;
  jetEta = new vector<number>;
  jetPhi = new vector<number>;

}

TMPNtupleData::~TMPNtupleData() {
}


