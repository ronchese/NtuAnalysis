#ifndef TMPAnalysis_Ntu_TMPAnalyzer_h
#define TMPAnalysis_Ntu_TMPAnalyzer_h

#include "TH1.h"
#include "TMPAnalyzerUtil.h"

class TMPAnalyzer: public virtual TMPAnalyzerUtil {

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
  void save() override; // save the histograms on a ROOT file

  bool verbose;

 protected:

  double ptCut;

 private:

  TH1D* hptmumax;
  TH1D* hptmu2nd;
  TH1D* hptmu;

  // dummy copy constructor and assignment
  TMPAnalyzer           ( const TMPAnalyzer& ) = delete;
  TMPAnalyzer& operator=( const TMPAnalyzer& ) = delete;

};


#endif // TMPAnalysis_Ntu_TMPAnalyzer_h

