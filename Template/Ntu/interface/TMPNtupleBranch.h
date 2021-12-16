#ifndef TMPAnalysis_Ntu_TMPNtupleBranch_h
#define TMPAnalysis_Ntu_TMPNtupleBranch_h

#include "NtuAnalysis/Common/interface/NtuEventBranch.h"
#include "TMPAnalysis/Ntu/interface/TMPNtupleData.h"
#include <string>
#include <vector>

class TBranch;

template <class T>
class TMPNtupleBranch: public virtual TMPNtupleData, public virtual T,
                      public NtuEventBranch<T> {

 public:

  TMPNtupleBranch();
  virtual ~TMPNtupleBranch();

  void initTree();

 protected:

  // List of branches

  // muons
  void setBranches_muons();
  TBranch* b_nMuons;
  TBranch* b_muoPt;
  TBranch* b_muoEta;
  TBranch* b_muoPhi;
  TBranch* b_muoPx;
  TBranch* b_muoPy;
  TBranch* b_muoPz;
  TBranch* b_pSum;

  // jets
  void setBranches_jets();
  TBranch* b_nJets;
  TBranch* b_jetPt;
  TBranch* b_jetPhi;
  TBranch* b_jetEta;

 private:

  // dummy copy constructor and assignment
  TMPNtupleBranch           ( const TMPNtupleBranch& td ) = delete;
  TMPNtupleBranch& operator=( const TMPNtupleBranch& td ) = delete;

};

#include "TMPNtupleBranch.hpp"

#endif // TMPAnalysis_Ntu_TMPNtupleBranch_h

