#!/bin/sh

if [ -z ${CMSSW_BASE} ] ; then
  echo "CMSSW_BASE not defined; run \"cmsenv\" before"
  exit
fi

rm -rf ${CMSSW_BASE}/src/TMPAnalysis/EDM

