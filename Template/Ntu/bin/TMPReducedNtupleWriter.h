#ifndef TMPReducedNtupleWriter_h
#define TMPReducedNtupleWriter_h

#include "TMPReducedNtupleData.h"
#include "NtuTool/Common/interface/TreeWriter.h"
#include "TFile.h"
#include <string>

class TMPReducedNtupleWriter: public TMPReducedNtupleData, public TreeWriter {

 public:

  TMPReducedNtupleWriter() {
  }
  virtual ~TMPReducedNtupleWriter() {
  }

  void open( const std::string& name, const std::string mode = "CREATE" ) {
    TDirectory* current = gDirectory;
    file = new TFile( name.c_str(), mode.c_str() );
    initTree();
    initWrite( file );
    current->cd();
    return;
  }
 
  void close() {
    TreeWriter::close();
    file->Close();
  }

 private:

  TFile* file;

  TMPReducedNtupleWriter           ( const TMPReducedNtupleWriter& a ) = delete;
  TMPReducedNtupleWriter& operator=( const TMPReducedNtupleWriter& a ) = delete;

};

#endif

