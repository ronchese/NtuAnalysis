#ifndef NtuAnalysis_Read_NtuProofReader_h
#define NtuAnalysis_Read_NtuProofReader_h

class NtuProofReaderInterface: public NtuAnalyzer {
 public:
  void bJ() {
    this->setupNtuple();
    this->beginJob();
    return;
  }
  bool gE( int ientry ) {
    return this->getEntry( ientry );
  };
  ClassDef(NtuProofReaderInterface,0);
};

class NtuProofReader: public NtuProofReaderInterface,
                      public TreeReader {
 protected:
  void iT( TTree* tree ) {
    cout << "initRead" << endl;
    this->initRead( tree );
  };
  ClassDef(NtuProofReader,0);
};

class NtuProofEDMReader: public NtuProofReaderInterface,
                         public EDMTreeReader {
 public:
  NtuProofEDMReader() {
    setProcessName ( processName  );
    setProducerName( producerName );
  }
 protected:
  void iT( TTree* tree ) {
    cout << "initRead" << endl;
    this->initRead( tree );
  };
  ClassDef(NtuProofEDMReader,0);
};


#endif // NtuAnalysis_Read_NtuProofReader_h

