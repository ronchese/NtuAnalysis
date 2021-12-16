#include "NtuTool/Read/interface/NANOHandler.h"
#include <iostream>

template <class T>
TMPNtupleBranch<T>::TMPNtupleBranch() {
  T::treeName = "TMPtree";
}


template <class T>
TMPNtupleBranch<T>::~TMPNtupleBranch() {
}


template <class T>
void TMPNtupleBranch<T>::initTree() {

  std::cout << "TMPNtupleBranch<T>::initTree()" << std::endl;

  // define branches
  // use local function "setBranch" (defined in the utility)
  // in place of ROOT "Branch" & "SetBranchAddress"

  setBranches_muons();
  setBranches_jets ();

  return;

}


template <class T>
void TMPNtupleBranch<T>::setBranches_muons() {
  // muons
  if ( !use_muons ) {
    nMuons = 0;
    return;
  }
  int size = 8192; // ROOT container size
  // The function "setBranch" takes the same arguments as TTree::Branch .
  // Specific instructions to write/read in nanoAOD format:
  //     - std::vectors and/or arrays sharing the same size should be put 
  //       in the same table; this can be obtained concatenating the calls
  //       to "setBranch";
  //     - the size is the first variable in the table, an "unsigned int"
  //       should be used for that and care must be taken that it's
  //       actually equal to the std::vector size;
  //     - if size is missing it's automatically added;
  //     - the table name can be added after the first call, if missing a
  //       default will be used;
  //     - the table size is necessary to reserve temporary arrays used
  //       when reading std::vectors, that in NANOAOD are anyway stored
  //       as native arrays, and the value should be larger than the biggest
  //       array/vector actually stored in the ntuple, if missing it's set
  //       at 10000 by default; in this example the initial value
  //       of nMuons is set at 20 in TMPNtupleData.cc, so it's used in
  //       place of hardcoding "20".
  // When writing/reading other ntuple formats different than NANOAOD,
  //    i.e. traditional flat ntuple or EDM ntuples, the calls to "setInfo"
  //    are simply ignored.
  this->setBranch( "nMuons"            , &  nMuons,
                   "nMuons/i"          , &b_nMuons )
      ->setInfo( NANOHandler::nanoTableName, "muons"       )
      ->setInfo( NANOHandler::nanoTableSize, nMuons        )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon number" )
      ->setBranch( "muoPt"             , &  muoPt ,
                   size, 99            , &b_muoPt  )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon p_t"    )
      ->setBranch( "muoEta"            , &  muoEta,
                   size, 99            , &b_muoEta )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon eta"    )
      ->setBranch( "muoPhi"            , &  muoPhi,
                   size, 99            , &b_muoPhi )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon phi"    )
      ->setBranch( "muoPx"             ,    muoPx ,
                   "muoPx[nMuons]/F"   , &b_muoPx  )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon p_x"    )
      ->setBranch( "muoPy"             ,    muoPy ,
                   "muoPy[nMuons]/F"   , &b_muoPy  )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon p_y"    )
      ->setBranch( "muoPz"             ,    muoPz ,
                   "muoPz[nMuons]/F"   , &b_muoPz  )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon p_z"    );
  // Muon momentum sum: no name is given for the table, so the name of 
  // the first branch is used
  this->setBranch( "pSum"              ,    pSum  ,
                   typedName("pSum[3]"), &b_pSum   )
      ->setInfo( NANOHandler::nanoBranchDoc, "muon momentum sum" );
  return;
}


template <class T>
void TMPNtupleBranch<T>::setBranches_jets() {
  // jets
  if ( !use_jets ) {
    nJets = 0;
    return;
  }
  int size = 8192; // ROOT container size
  // No calls to "setInfo", default behaviour when writing NANOAOD:
  //     - a different table will be created for each branch;
  //     - the size of jetPt,jetEta,jetPhi is stored regardless of "nJets"
  //       (i.e. there's a data duplication, left just for example)
  this->setBranch( "nJets"          , &  nJets          ,
                   "nJets/i"        , &b_nJets           );
  this->setBranch( "jetPt"          , &  jetPt          ,
                   size, 99         , &b_jetPt           );
  this->setBranch( "jetEta"         , &  jetEta         ,
                   size, 99         , &b_jetEta          );
  this->setBranch( "jetPhi"         , &  jetPhi         ,
                   size, 99         , &b_jetPhi          );
  return;
}

