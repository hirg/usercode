import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_920.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_921.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_922.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_924.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_925.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_926.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_927.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_928.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_929.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_93.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_930.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_932.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_94.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_940.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_941.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_942.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_943.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_944.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_945.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_946.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_948.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_949.root',
'file:/mnt/hadoop/cms/store/user/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_95.root'
    ))

process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'STARTHI53_V9::All'
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltZeroBiasSingleTrack = process.hltHighLevel.clone()
process.hltZeroBiasSingleTrack.HLTPaths = ["HLT_PAZeroBiasPixel_SingleTrack_v1"]

process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("Tracks"),
	nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
	centralitySrc = cms.InputTag("pACentrality")
)

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("histogram_test.root"))

process.demo = cms.EDAnalyzer('CentNtrkOffline'
)

#process.p = cms.Path(process.pACentrality * process.demo)
process.p = cms.Path(process.PAcollisionEventSelection * process.pACentrality * process.demo)
#process.p = cms.Path(process.hltZeroBiasSingleTrack * process.PAcollisionEventSelection * process.pACentrality * process.demo)

