import FWCore.ParameterSet.Config as cms

process = cms.Process("tmpAnalysis")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.load('PhysicsTools.NanoAOD.nano_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

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

# Path and EndPath definitions
# the EDProducer must have a name "process.tmpNtuTable" to be written to the
# output, otherwise its name must be appended to the outputCommands
process.tmpNtuTable = cms.EDProducer('TMPNANONtuplizer',

    ## mandatory
    ## histogram file name
    histName = cms.untracked.string('test_his.root'),

    ## optional
### A list of events can be given, having the format of a text file with
### run and event number pairs: 
###     - only events listed in the file will be accepted, by default;
###     - when setting listType to "skip" all events will be accepted
###       but the listed ones, that will be skipped.
### Discarded events will be passed to following modules but no processing
### will be done and the ntuple structure will not be filled.
### Contrarily to the other examples, producing "traditional" flat ntuples
### or EDM ntuples, an EDFilter cannot be used: apparently the NANOAOD 
### producer requires the processing of all events.
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
### modules, only for event selected by SimpleNtuEDMModule::fill function.
### Unluckily this is implemented in a largely suboptimal way, using
### a "static bool" flag: it's incompatible with multithread running and
### doesn't comply with CMSSW rules.
### A better solution will be implemented a.s.a.p.
process.tmpFilter = cms.EDFilter('EDMNtupleFilter')
process.p = cms.Path(
                     process.tmpNtuTable
#                   * process.tmpFilter
)

# Output definition
process.out = cms.OutputModule("NanoAODOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('NANOAOD'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:test_nnn.root'),
    outputCommands = process.NANOAODEventContent.outputCommands
)
### appending to the outputCommands is not necessary for producers
### named "process.tmpNtuTable:

process.e = cms.EndPath(process.out)
