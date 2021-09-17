#ifndef NtuAnalysis_Common_NtuEventHeader_h
#define NtuAnalysis_Common_NtuEventHeader_h

class TBranch;

class NtuEventHeader {

 protected:

  NtuEventHeader() { b_runNumber   =
                     b_lumiSection =
                     b_eventNumber = nullptr; }
  virtual ~NtuEventHeader() {}

  // header
  unsigned int runNumber;
  unsigned int lumiSection;
  unsigned int eventNumber;

  TBranch* b_runNumber;
  TBranch* b_lumiSection;
  TBranch* b_eventNumber;

 private:

  // dummy copy constructor and assignment
  NtuEventHeader           ( const NtuEventHeader& ) = delete;
  NtuEventHeader& operator=( const NtuEventHeader& ) = delete;

};

#endif // NtuAnalysis_Common_NtuEventHeader_h

