import FWCore.ParameterSet.Config as cms

process = cms.PSet()

### define here a list of (MINI)AOD files
filename = open('edm_files.list', 'r')
filelist = cms.vstring( filename.readlines() )

process.fwliteInput = cms.PSet(
    fileNames   = filelist,               ## mandatory
    maxEvents   = cms.int32(1000),        ## optional, use maxEvents<=0
                                          ##           to read all events
    outputEvery = cms.uint32(10),         ## optional (usage not clear...)
)
    
process.tmpAnalyzer = cms.PSet(

    ## mandatory
    ## ntuple file name: giving an empty string the ntuple structure is 
    ## filled but it's not written to the ROOT file
    ntuName = cms.untracked.string('test_ntu.root'),
    ## histogram file name
    histName = cms.untracked.string('test_his.root'),

    ## optional
### A list of events can be given, having the format of a text file
### with run and event number pairs: 
###     - only events listed in the file will be accepted, by default;
###     - when setting listType to "skip" all events will be accepted
###       but the listed ones, that will be skipped.
#    eventList = cms.string('evtlist'),
#    listType = cms.string('keep'),
##    listType = cms.string('skip'),

    verbose = cms.untracked.bool(True),

### If labelMuons is not set the "muons" block will not be activated and the
### corresponding branch(es) will not be included in the ntuple,
### if labelMuons is set as 'RANDOM', muons will be generated
### with random momenta in place of reading from input
### (mandatory when reading from an empty source)
#    labelMuons        = cms.string('calibratedPatMuonsPFlow'),
    labelMuons        = cms.string('RANDOM'),
#    labelMuons        = cms.string(''),

### If labelJets is not set the "jets" block will not be activated and the
### corresponding branch(es) will not be included in the ntuple,
### if labelJets is set as 'RANDOM', jets will be generated
### with random momenta in place of reading from input
### (mandatory when reading from an empty source)
#    labelJets         = cms.string('selectedPatJetsLooseIDUserDataPFlow'),
    labelJets         = cms.string('RANDOM'),
#    labelJets         = cms.string(''),

    ## select events with at least a muon with pT > 10 GeV
    ## (if missing a default ptCut=20GeV will be used, see TMPAnalyzer)
    ptCut = cms.double( 10.0 )

)


