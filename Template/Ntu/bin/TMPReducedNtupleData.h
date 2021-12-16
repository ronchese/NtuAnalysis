#ifndef TMPReducedNtupleData_h
#define TMPReducedNtupleData_h

#include "NtuTool/Common/interface/TreeWrapper.h"

class TMPReducedNtupleData: public virtual TreeWrapper {

 public:

  TMPReducedNtupleData() {
  }
  virtual ~TMPReducedNtupleData() {
  }

  void initTree() {
    treeName = "TMPreducedTree";
    setBranch( "idMuon", &idMuon, "idMuon/I", &b_idMuon );
    setBranch( "idJet" , &idJet ,  "idJet/I", &b_idJet  );
    setBranch( "angle" , &angle ,  "angle/F", &b_angle  );
  }

  int   idMuon;
  int   idJet;
  float angle;
  TBranch* b_idMuon;
  TBranch* b_idJet;
  TBranch* b_angle;

 private:

  TMPReducedNtupleData           ( const TMPReducedNtupleData& a ) = delete;
  TMPReducedNtupleData& operator=( const TMPReducedNtupleData& a ) = delete;

};

#endif

