#ifndef TMPAnalysis_Ntu_TMPNtupleData_h
#define TMPAnalysis_Ntu_TMPNtupleData_h

#include <string>
#include <vector>

#include "NtuAnalysis/Common/interface/NtuData.h"

// the template parameter is just used to define a type "number"
// in NANOAOD some types are not supported, so they will be truncated:
//    unsigned int           ->  int
//    long long              ->  int
//    unsigned long long     ->  int
//    double                 ->  float

class TMPNtupleData: public NtuData<float> {

 public:

  TMPNtupleData();
  virtual ~TMPNtupleData();

 protected:

  // Declaration of leaf types

  // muons
  bool use_muons;
  unsigned int nMuons;
  // spherical coordinates stored as std::vector
  std::vector<number>* muoPt;
  std::vector<number>* muoEta;
  std::vector<number>* muoPhi;
  // cartesian coordinates stored as native array
  number* muoPx;
  number* muoPy;
  number* muoPz;

  number* pSum;

  // jets
  bool use_jets;
  unsigned int nJets;
  std::vector<number>* jetPt;
  std::vector<number>* jetEta;
  std::vector<number>* jetPhi;

 private:

  // dummy copy constructor and assignment
  TMPNtupleData           ( const TMPNtupleData& td ) = delete;
  TMPNtupleData& operator=( const TMPNtupleData& td ) = delete;

};

#endif // TMPAnalysis_Ntu_TMPNtupleData_h

