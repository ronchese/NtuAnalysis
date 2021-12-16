#ifndef TMPReducedNtupleReader_h
#define TMPReducedNtupleReader_h

#include "TMPReducedNtupleData.h"
#include "NtuTool/Common/interface/TreeReader.h"
#include "TFile.h"
#include "TH1.h"
#include <string>
#include <iostream>

class TMPReducedNtupleReader: public TMPReducedNtupleData, public TreeReader {

 public:

  TMPReducedNtupleReader() {}
  virtual ~TMPReducedNtupleReader() {}

  virtual void beginJob() {
    initTree();
  }

  virtual void book() {
    autoSavedObject =
      hAngle = new TH1F( "hAngle", "hAngle", 32, 0.0, 3.2 );
  }
  virtual bool analyze( int entry, int event_file, int event_tot ) {
    // In this example there's just the filling of an histogram,
    // more complicated analyses can be implemented, of course
    hAngle->Fill( angle );
    return true;
  }
  virtual void endJob() {}

 private:

  TH1F* hAngle;

  TMPReducedNtupleReader           ( const TMPReducedNtupleReader& a ) = delete;
  TMPReducedNtupleReader& operator=( const TMPReducedNtupleReader& a ) = delete;

};

#endif

