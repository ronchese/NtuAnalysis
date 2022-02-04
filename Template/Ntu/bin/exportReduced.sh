#!/bin/sh

cd `dirname $0`/../../..
export TMP_PATH=TMPAnalysis/Ntu
export TMP_PACK=`pwd`/tmpAnalysisReduced.tgz
rm -f ${TMP_PACK}
tar -czf ${TMP_PACK}                     \
${TMP_PATH}/bin/TMPReducedNtupleData.*   \
${TMP_PATH}/bin/TMPReducedNtupleReader.* \
${TMP_PATH}/bin/reducedAnalyze.cc        \
${TMP_PATH}/bin/compileReduced.sh        \
${TMP_PATH}/bin/exportReduced.sh
echo ${TMP_PACK}
