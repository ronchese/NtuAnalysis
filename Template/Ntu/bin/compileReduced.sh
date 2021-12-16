#!/bin/sh

cd `dirname $0`/..
export TMP_PACK_DIR=`/bin/pwd`
cd ../..
export TMP_ROOT_DIR=`/bin/pwd`
echo $TMP_PACK_DIR
echo $TMP_ROOT_DIR

export SA_STRING="==="`printenv | awk -F= '($1=="SCRAM_ARCH") {print $2}'`"==="
if [ ${SA_STRING} = "======" ]; then
  export NTU_TOOL_LIB="-L "${NTU_TOOL_DIR}"/lib -lNtupleTool"
else
  export NTU_TOOL_LIB="-L "${NTU_TOOL_DIR}"/lib/"${SCRAM_ARCH}" -lNtupleTool_"${CMSSW_VERSION}
fi

export TMP_EXE_FILE=${TMP_PACK_DIR}/bin/tmpReducedAnalyze
rm -f ${TMP_EXE_FILE}

c++ -Wall `root-config --cflags`              \
-I ${TMP_ROOT_DIR} -I ${NTU_TOOL_DIR}/include \
-o ${TMP_EXE_FILE}                            \
${TMP_PACK_DIR}/bin/reducedAnalyze.cc         \
${NTU_TOOL_LIB}                               \
`root-config --glibs`

echo ${TMP_EXE_FILE}
