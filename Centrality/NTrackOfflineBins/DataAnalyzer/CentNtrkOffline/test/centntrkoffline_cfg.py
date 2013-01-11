import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(200) )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_P_V41::All'
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltZeroBiasSingleTrack = process.hltHighLevel.clone()
process.hltZeroBiasSingleTrack.HLTPaths = ["HLT_PAZeroBiasPixel_SingleTrack_v1"]

process.HeavyIonGlobalParameters = cms.PSet(
        centralityVariable = cms.string("Tracks"),
        nonDefaultGlauberModel = cms.string(""),
        centralitySrc = cms.InputTag("pACentrality")
)

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(
'file:/store/hidata/data/PARun2012/PAPhysics/RECO/PromptReco-v2/000/202/792/6689838A-33FF-E111-A07F-0030486730C6.root'
    ))

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("histogram_test.root"))

process.demo = cms.EDAnalyzer('CentNtrkOffline'
)

#process.p = cms.Path(process.pACentrality * process.demo)
#process.p = cms.Path(process.PAcollisionEventSelection * process.pACentrality * process.demo)
process.p = cms.Path(process.hltZeroBiasSingleTrack * process.PAcollisionEventSelection * process.pACentrality * process.demo)


