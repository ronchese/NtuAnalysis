#ifndef NtuAnalysis_Write_NtuEDConsumer_h
#define NtuAnalysis_Write_NtuEDConsumer_h
/** \class NtuEDConsumer
 *
 *  Description: 
 *    common interface to forward calls to EDConsumerBase
 *
 *  $Date: 2016-04-15 17:47:56 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/EDConsumerBase.h"
#include "FWCore/Framework/interface/ESConsumesCollector.h"

//---------------
// C++ Headers --
//---------------
#include <string>

//              ---------------------
//              -- Class Interface --
//              ---------------------

template <class Obj>
class NtuEDToken {
 public:
  typedef typename edm::EDGetTokenT<Obj> type;
  static bool get( const edm::EventBase* ev,
                   NtuEDToken<Obj>& t,
                   edm::Handle<Obj>& obj ) {
    const edm::Event* ep = dynamic_cast<const edm::Event*>( ev );
    if ( ep == nullptr ) return false;
    return ep->getByToken( t.token, obj );
  }
  bool get( const edm::EventBase* ev,
            edm::Handle<Obj>& obj ) const {
    const edm::Event* ep = dynamic_cast<const edm::Event*>( ev );
    if ( ep == nullptr ) return false;
    return ep->getByToken( token, obj );
  }
  type token;
};


template<class Obj,class Rec>
class NtuESToken {
 public:
  typedef typename edm::ESGetToken<Obj,Rec> type;
  bool get( const edm::EventSetup* es,
            edm::ESHandle<Obj>& obj ) const {
    obj = es->get<Rec>().getHandle( token );
    return obj.isValid();
  }
  type token;
};


template <class T>
class NtuEDConsumer: public virtual T {

 public:

  /** Constructor
   */
  NtuEDConsumer() {}

  /** Destructor
   */
  ~NtuEDConsumer() override {}

  /** Operations
   */
  /// forward call to EDConsumerBase
  template <class Obj>
  void consume( NtuEDToken<Obj>& tw,
                const edm::InputTag& tag ) {
    tw.token = this->template consumes<Obj>( tag );
    return;
  }
  template<class Obj,class Rec>
  void esConsume( NtuESToken<Obj,Rec>& tw ) {
    tw.token = this->template esConsumes<Obj,Rec>();
    return;
  }
  template<class Obj,class Rec>
  void esConsume( NtuESToken<Obj,Rec>& tw,
                  const std::string& label ) {
    tw.token = this->template esConsumes<Obj,Rec>( edm::ESInputTag( "",
                                                                    label ) );
    return;
  }
  template<class Obj,class Rec>
  void esConsume( NtuESToken<Obj,Rec>& tw,
                  const edm::ESInputTag& tag ) {
    tw.token = this->template esConsumes<Obj,Rec>( tag );
    return;
  }

 private:

  // private copy and assigment constructors
  NtuEDConsumer           ( const NtuEDConsumer& x ) = delete;
  NtuEDConsumer& operator=( const NtuEDConsumer& x ) = delete;

};

#endif // NtuAnalysis_Write_NtuEDConsumer_h


