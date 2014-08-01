import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )
process.MessageLogger.cerr.FwkReport.reportEvery = 200

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'GR_E_V33A::All'
process.GlobalTag.globaltag = 'GR_P_V41::All'

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHM = process.hltHighLevel.clone()
process.hltHM.HLTPaths = [
               "HLT_PAPixelTracks_Multiplicity100_v*",  #120-150
               "HLT_PAPixelTracks_Multiplicity130_v*",  #150-185
               "HLT_PAPixelTracks_Multiplicity160_v*"  #185-220
#               "HLT_PAPixelTracks_Multiplicity190_v*"  #220-260
#               "HLT_PAPixelTracks_Multiplicity220_v*"   #260-300
              ]
process.hltHM.andOr = cms.bool(True)
process.hltHM.throw = cms.bool(False)

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
  centralityVariable = cms.string("HFtowersPlusTrunc"),
  nonDefaultGlauberModel = cms.string(""),
  centralitySrc = cms.InputTag("pACentrality")
  )

process.source = cms.Source("PoolSource",
#                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(
'file:/lio/lfs/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_v12/331639eac1650e369e7dacf443369878/pPb_HM_63_1_YBl.root'
    ))

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("histogram_test.root"))

process.demo = cms.EDAnalyzer('TrackOfflineExample'
)

process.p = cms.Path(process.hltHM * process.demo)

