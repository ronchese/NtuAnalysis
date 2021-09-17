#ifndef NtuAnalysis_Common_NtuData_h
#define NtuAnalysis_Common_NtuData_h

#include "NtuAnalysis/Common/interface/NtuUtil.h"
#include "NtuAnalysis/Common/interface/NtuEventHeader.h"

#include <string>
#include <vector>

template <class T>
class NtuTypeInterface {
 public:
  const char* numberType() { return ""; }
};

template <>
class NtuTypeInterface<float> {
 public:
  const char* numberType() { return "F"; }
};

template <>
class NtuTypeInterface<double> {
 public:
  const char* numberType() { return "D"; }
};

template <class T>
class NtuData: public NtuUtil<T>,
               public NtuTypeInterface<T>,
               public virtual NtuEventHeader {

 public:

  typedef T number;
  ~NtuData() override {}

 protected:

  NtuData() {}
  const char* typedName( const std::string& name ) {
    static std::string s;
    s = name + "/" + this->numberType();
    return s.c_str();
  }

 private:

  // dummy copy constructor and assignment
  NtuData           ( const NtuData& ) = delete;
  NtuData& operator=( const NtuData& ) = delete;

};

#endif // NtuAnalysis_Common_NtuData_h

