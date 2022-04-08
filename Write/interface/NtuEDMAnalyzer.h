#ifndef NtuAnalysis_Write_NtuEDMAnalyzer_h
#define NtuAnalysis_Write_NtuEDMAnalyzer_h

#define UTIL_USE FULL

#include "NtuAnalysis/Common/interface/NtuEventHeader.h"
#include "NtuAnalysis/Common/interface/NtuAnalyzerUtil.h"
#include "NtuAnalysis/Write/interface/NtuEDConsumer.h"
#include "NtuTool/Common/interface/TreeWrapper.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"

#include <string>
#include <vector>
#include <map>
class TFile;

#define GET_PARAMETER( X, D ) getParameter( #X, X, D, true )
#define GET_UNTRACKED( X, D ) getParameter( #X, X, D, false )

class NtuEDMAnalyzer: public virtual NtuEventHeader,
                      public virtual NtuAnalyzerUtil,
                      public virtual TreeWrapper {

 protected:

  NtuEDMAnalyzer( const edm::ParameterSet& ps );
  ~NtuEDMAnalyzer() override;

  template <class T>
  void getParameter( const std::string& key, T& val,
                     const std::string& def, bool tracked ) {
    setUserParameter( key, def );
    T tmp;
    getUserParameter( key, tmp );
    val = ( parameterSet->exists( key ) ?
            ( tracked ? 
              parameterSet->getParameter<T>( key ) :
              parameterSet->getUntrackedParameter<T>( key ) ) : tmp );
    setUserParameter( key, val );
    return;
  }

  virtual void beginJob() override;
  virtual void beginRun();
  virtual bool analyzeEDM( const edm::EventBase& ev,
                           int ientry, int event_file );
  virtual void read( const edm::EventBase& ev );
  virtual void endRun();
  virtual void endJob() override;

  template <class Consumer, class Obj>
  static void consume( NtuEDConsumer<Consumer>* c,
                       NtuEDToken<Obj>& token,
                       const std::string& label ) {
    if ( label == "" ) return;
    edm::InputTag tag( label );
    if ( c != 0 ) c->template consume<Obj>( token, tag );
    return;
  }
  template <class Consumer, class Obj>
  static void consume( NtuEDConsumer<Consumer>* c,
                       NtuEDToken<Obj>& token,
                       const edm::InputTag tag ) {
    if ( c != 0 ) c->template consume<Obj>( token, tag );
    return;
  }
  template <class Consumer, class Obj, class Rec>
  static void esConsume( NtuEDConsumer<Consumer>* c,
                         NtuESToken<Obj,Rec>& token ) {
    if ( c != 0 ) c->template esConsume<Obj,Rec>( token );
    return;
  }
  template <class Consumer, class Obj, class Rec>
  static void esConsume( NtuEDConsumer<Consumer>* c,
                         NtuESToken<Obj,Rec>& token,
                         const std::string& label ) {
    if ( c != 0 ) c->template esConsume<Obj,Rec>( token,
                              edm::ESInputTag( "", label ) );
    return;
  }
  template <class Consumer, class Obj, class Rec>
  static void esConsume( NtuEDConsumer<Consumer>* c,
                         NtuESToken<Obj,Rec>& token,
                         const edm::ESInputTag tag ) {
    if ( c != 0 ) c->template esConsume<Obj,Rec>( token, tag );
    return;
  }

  template <class T>
  class ObjectConsumer {
   public:
    ObjectConsumer( NtuEDMAnalyzer* a, NtuEDConsumer<T>* c ): 
     analyzer( a ),
     consumer( c ) {}
    template <class Obj>
    void consume( NtuEDToken<Obj>& nt,
                  const std::string& label ) {
      analyzer->template consume<T,Obj>( consumer, nt, label );
      return;
    }
    template <class Obj>
    void consume( NtuEDToken<Obj>& nt,
                  const edm::InputTag tag ) {
      analyzer->template consume<T,Obj>( consumer, nt, tag );
      return;
    }
    template<class Obj,class Rec>
    void esConsume( NtuESToken<Obj,Rec>& nt ) {
      analyzer->template esConsume<T,Obj,Rec>( consumer, nt );
      return;
    }
    template<class Obj,class Rec>
    void esConsume( NtuESToken<Obj,Rec>& nt,
                    const std::string& label ) {
      analyzer->template esConsume<T,Obj,Rec>( consumer, nt,
                                               edm::ESInputTag( "", label ) );
      return;
    }
    template<class Obj,class Rec>
    void esConsume( NtuESToken<Obj,Rec>& nt,
                    const edm::ESInputTag& tag ) {
     analyzer->template esConsume<T,Obj,Rec>( consumer, nt, tag );
      return;
    }
   private:
    NtuEDMAnalyzer* analyzer;
    NtuEDConsumer<T>* consumer;
  };
  template <class T>
  ObjectConsumer<T>& getConsumer( NtuEDConsumer<T>* c ) {
    static ObjectConsumer<T>* ptr = new ObjectConsumer<T>( this, c );
    return *ptr;
  }

 private:

  // dummy copy constructor and assignment
  NtuEDMAnalyzer           ( const NtuEDMAnalyzer& c ) = delete;
  NtuEDMAnalyzer& operator=( const NtuEDMAnalyzer& c ) = delete;

};

#endif // NtuAnalysis_Write_NtuEDMAnalyzer_h
