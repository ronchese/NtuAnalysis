import FWCore.ParameterSet.Config as cms

process = cms.Process("tmpAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

# Quiet Mode or event dump
#process.MessageLogger.cerr.threshold = 'ERROR'
process.MessageLogger.cerr.threshold = 'WARNING'
#process.MessageLogger.cerr.FwkReport.reportEvery = 10000

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

### define here a list of (MINI)AOD files
#filename = open('edm_files.list', 'r')
#fileList = cms.untracked.vstring( filename.readlines() )

#process.source = cms.Source ("PoolSource", fileNames=fileList)

### an empty source is used here for testing purposes
process.source = cms.Source("EmptySource",
    numberEventsInRun   = cms.untracked.uint32(10)
)

### An EDFilter is available to select events using a list having the format of
### a text file with run and event number pairs: 
###     - only events listed in the file will be accepted, by default;
###     - when setting listType to "skip" all events will be accepted
###       but the listed ones, that will be skipped.
#process.evNumFilter = cms.EDFilter('EvNumFilter',
#    eventList = cms.string('evList'),
#    listType = cms.string('keep')
##    listType = cms.string('skip')
#)

### Analyze and write an EDM ntuple.
### This is an EDProducer: events will be processed, the ntuple content will
### be added to the edm::Event if selected (see TMPAnalyzer), passed to the
### following module, if any, and finally events will be written to the output
### (see the OutputModule); an explicit filter to select events according to 
### the process result can be added (see the EDMNtupleFilter module).
process.tmpAnalyzer = cms.EDProducer('TMPEDMNtuplizer',

    ## mandatory
    ## histogram file name
    histName = cms.untracked.string('test_his.root'),

    ## optional
### Independently on the EDFilter above, a list of events can be given, with
### the same format as in the filter above; discarded events will be passed
### to following modules but no processing will be done, the ntuple structure
### will not be filled and nothing will be added to the Event.
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
    ## (if missing a default ptCut=15GeV will be used, see TMPEDMToNtuple.cc)
    ptCut = cms.double( 10.0 )

)

### A filter can be included in the path, to pass the event to following
### modules, or the output, only for event selected by TMPAnalyzer::analyze
### function.
### Unluckily this is implemented in a suboptimal way, using a "static bool"
### flag: it's incompatible with multithread running and doesn't comply 
### with CMSSW rules. A better solution will be implemented a.s.a.p.
process.tmpFilter = cms.EDFilter('EDMNtupleFilter')
process.p = cms.Path(
#                     process.evNumFilter *
                     process.tmpAnalyzer
#                   * process.tmpFilter
)

# Output definition
process.out = cms.OutputModule(
    "PoolOutputModule",
    outputCommands = cms.untracked.vstring(
      "drop *",
      "keep *_tmpAnalyzer_*_*"      
    ),
    fileName = cms.untracked.string('test_edm.root'),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    )
)


process.e = cms.EndPath(process.out)

