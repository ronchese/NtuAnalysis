
#include "TFile.h"

// system include files
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

template <class T>
NtuFilter<T>::NtuFilter( const edm::ParameterSet& ps ):
  NtuWriteInterface<T>( ps, this ) {
  histName = ps.getUntrackedParameter<std::string>( "histName" );
}


template <class T>
NtuFilter<T>::~NtuFilter() {
}


template <class T>
void NtuFilter<T>::beginJob() {
  NtuWriteInterface<T>::beginJob();
  analyzedFile = 0;
  return;
}


template <class T>
void NtuFilter<T>::endJob()  {
  NtuWriteInterface<T>::endJob();
  TreeWrapper::save( histName );
  return;
}


template <class T>
void NtuFilter<T>::beginRun( const edm::Run& run,
                             const edm::EventSetup& es ) {
  currentRun     = &run;
  currentEvSetup = &es;
  NtuWriteInterface<T>::beginRun();
  return;
}


template <class T>
void NtuFilter<T>::endRun( const edm::Run& run,
                           const edm::EventSetup& es ) {
  NtuWriteInterface<T>::endRun();
  return;
}


template <class T>
bool NtuFilter<T>::filter( edm::Event& ev,
                     const edm::EventSetup& es ) {
  currentEvent   = &ev;
  currentEvSetup = &es;
  int ientry = 0;
  return NtuWriteInterface<T>::analyzeEDM( ev, ientry, analyzedFile++ );
}

