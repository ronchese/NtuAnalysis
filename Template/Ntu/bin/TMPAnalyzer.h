#ifndef TMPAnalysis_Ntu_TMPAnalyzer_h
#define TMPAnalysis_Ntu_TMPAnalyzer_h

#include "TH1.h"
#include "TMPAnalyzerUtil.h"

// Activate/deactivate lines to skim ntuple:
// a macro is used just to flag the relevant code lines, 
// normally the code would not make use of the preprocessor.

// Do not do the ntuple skim
#define SKIM_NTUPLE 0
// Do the ntuple skim
//#define SKIM_NTUPLE 1

#if SKIM_NTUPLE != 0
#include "NtuTool/Common/interface/TreeFilter.h"
#include "TFile.h"
#endif

// Activate/deactivate lines to produce a reduced ntuple:
// a macro is used just to flag the relevant code lines, 
// normally the code would not make use of the preprocessor.

// Do not produce a reduced ntuple
#define REDUCE_NTUPLE 0
// Produce a reduced ntuple
//#define REDUCE_NTUPLE 1

#if REDUCE_NTUPLE != 0
class TMPReducedNtupleWriter;
#endif

class TMPAnalyzer: public virtual TMPAnalyzerUtil
#if SKIM_NTUPLE != 0
                 , public virtual TreeFilter // additional header file
                                             // to skim ntuples
#endif
 {

 public:

  TMPAnalyzer();
  ~TMPAnalyzer() override;

  // function called before starting the analysis
  void beginJob() override;

  // functions to book the histograms
  void book() override;

  // functions called for each event
  // function to reset class content before reading from file
  void reset() override;
  // function to do event-by-event analysis,
  // return value "true" for accepted events, see .cc for more info
  bool analyze( int entry, int event_file, int event_tot ) override;

  // function called at the end of the analysis
  void endJob() override;

  // functions called at the end of the event loop
  using WrapperBase::plot; // needed for the following declaration
//  void plot() override; // plot histograms on the screen (optional, see .cc)
  using WrapperBase::save;
  void save() override; // save histograms on a ROOT file (optional, see .cc)

  bool verbose;

 protected:

  double ptCut;

#if REDUCE_NTUPLE != 0
  TMPReducedNtupleWriter* rWriter;
#endif

 private:

  TH1D* hptmumax;
  TH1D* hptmu2nd;
  TH1D* hptmu;

  // dummy copy constructor and assignment
  TMPAnalyzer           ( const TMPAnalyzer& ) = delete;
  TMPAnalyzer& operator=( const TMPAnalyzer& ) = delete;

};


#endif // TMPAnalysis_Ntu_TMPAnalyzer_h

