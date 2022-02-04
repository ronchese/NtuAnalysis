#!/bin/sh

if [ -z ${CMSSW_BASE} ] ; then
  echo "CMSSW_BASE not defined; run \"cmsenv\" before"
  exit
fi

cat << END_OF_INPUT > ${CMSSW_BASE}/src/TMPAnalysis/Ntu/bin/TMPAnalyzerUtil.h
#ifndef TMPAnalysis_Ntu_TMPAnalyzerUtil_h
#define TMPAnalysis_Ntu_TMPAnalyzerUtil_h
#include "TMPAnalysis/Ntu/interface/TMPNtupleBranch.h"
#include "NtuAnalysis/Common/interface/NtuInterface.h"
class TMPAnalyzerUtil: public NtuInterface< TMPNtupleBranch<WrapperBase> > {
 public:
  TMPAnalyzerUtil() {}
  ~TMPAnalyzerUtil() override {}
 protected:
  void setupNtuple() {
     initTree();
  }
  void beginJob() override {
    NtuInterface< TMPNtupleBranch<WrapperBase> >::beginJob();
  }
 private:
  // dummy copy constructor and assignment
  TMPAnalyzerUtil           ( const TMPAnalyzerUtil& ) = delete;
  TMPAnalyzerUtil& operator=( const TMPAnalyzerUtil& ) = delete;
};
#endif // TMPAnalysis_Ntu_TMPAnalyzerUtil_h
END_OF_INPUT

cat << END_OF_INPUT > ${CMSSW_BASE}/src/TMPAnalysis/Ntu/bin/TMPAnalyzer.h
#ifndef TMPAnalysis_Ntu_TMPAnalyzer_h
#define TMPAnalysis_Ntu_TMPAnalyzer_h
#include "TMPAnalyzerUtil.h"
#include <iostream>
class TMPAnalyzer: public virtual TMPAnalyzerUtil {
 public:
  TMPAnalyzer() {
    std::cout << "new TMPAnalyzer" << std::endl;
    setUserParameter( "verbose", "f" );
  }
  ~TMPAnalyzer() override {}
  void beginJob() override {
    TMPAnalyzerUtil::beginJob();
    getUserParameter( "verbose", verbose );
  }
  void reset() override {
#  if UTIL_USE == FULL
    autoReset();
#endif
  }
  bool analyze( int entry, int event_file, int event_tot ) override {
    if ( verbose ) {
      std::cout << " +++++++++++++++++++++++++++ " << std::endl;
      std::cout << "entry: "
                << entry << " " << event_file << " " << event_tot << std::endl;
      std::cout << "run: " <<   runNumber << " , "
                << "evt: " << eventNumber << std::endl;
    }
    else {
      if ( !( event_tot % 10000 ) && event_tot )
        std::cout << event_file << " " << event_tot << std::endl;
    }
    return true;
  }
  bool verbose;
 private:
  TMPAnalyzer           ( const TMPAnalyzer& ) = delete;
  TMPAnalyzer& operator=( const TMPAnalyzer& ) = delete;
};
#endif // TMPAnalysis_Ntu_TMPAnalyzer_h
END_OF_INPUT

cat << END_OF_INPUT > ${CMSSW_BASE}/src/TMPAnalysis/Ntu/bin/TMPAnalyzerUtil.cc
#include "TMPAnalysis/Ntu/bin/TMPAnalyzerUtil.h"
END_OF_INPUT

cat << END_OF_INPUT > ${CMSSW_BASE}/src/TMPAnalysis/Ntu/bin/TMPAnalyzer.cc
#include "TMPAnalysis/Ntu/bin/TMPAnalyzer.h"
END_OF_INPUT

rm -f TMPAnalysis/Ntu/bin/TMPReducedNtuple*
rm -f TMPAnalysis/Ntu/bin/reducedAnalyze.cc

export BUILDFILETMP="TMPAnalysis/Ntu/bin/BuildFile_"`date +%s`
grep -v reducedAnalyze TMPAnalysis/Ntu/bin/BuildFile.xml > ${BUILDFILETMP}
rm TMPAnalysis/Ntu/bin/BuildFile.xml
mv ${BUILDFILETMP} TMPAnalysis/Ntu/bin/BuildFile.xml

