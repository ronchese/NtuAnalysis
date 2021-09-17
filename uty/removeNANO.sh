#!/bin/sh

export DIR=`dirname $0`
export TOP=`dirname ${DIR}`

eval `find ${TOP} | grep -i NANO | grep -v removeNANO | awk '{print "rm "$0" ;"}'`

cat << END_OF_INPUT > ${TOP}/Read/interface/NtuNANOReader.h
#ifndef NtuAnalysis_Read_NtuNANOReader_h
#define NtuAnalysis_Read_NtuNANOReader_h
template <class T>
class NtuNANOReader: public T {
};
#endif // NtuAnalysis_Read_NtuNANOReader_h
END_OF_INPUT
