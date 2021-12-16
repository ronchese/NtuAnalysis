# NtuAnalysis

This package is to be used in conjunction with [NtuTool](https://github.com/ronchese/NtuTool).

## Installation

### Installing in CMSSW environment

```
cd ${CMSSW_BASE}/src
git clone git@github.com:ronchese/NtuTool.git
git clone git@github.com:ronchese/NtuAnalysis.git
scram b
```

### Installing with Docker

If you don't have docker installed already, instructions are [here](https://docs.docker.com/install/).

For a more recent CMSSW release like CMSSW_9_4_4, run a docker image:

`
docker run --name bph -it clelange/cmssw:9_4_4 /bin/bash
`

where we use the already-made CMSSW_9_4_4 release from [dockerhub](https://hub.docker.com/r/clelange/cmssw/tags)

Note: as described [here](https://github.com/clelange/cmssw-docker/) this will install a stand-alone CMSSW image so it will be
at least a few GBs and may take a while (but only has to be done once).

Once done, you should see the commmand prompt (`docker run -i` means run interactively):

`
cmsbld@3eebec38509d ~/CMSSW_9_4_4/src $
`

Then fetch the code:

```
git clone https://github.com/ronchese/NtuTool.git
git clone https://github.com/ronchese/NtuAnalysis.git
```

and compile

`
scram b
`