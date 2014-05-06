import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
import os

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
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

process.options = cms.untracked.PSet(
# after crash
SkipEvent = cms.untracked.vstring('ProductNotFound')	
)

# Input Source
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring(),
#                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
                            )
mylist = FileUtils.loadListFromFile ('filelist.txt')
for fname in mylist:
 process.source.fileNames.append('file:%s' % (fname))
# process.source.fileNames.append('%s' % (fname))


# histogram output
process.TFileService = cms.Service("TFileService",
                                  fileName = cms.string("pPbHist.root"))

process.demo = cms.EDAnalyzer('DataAnalysis',
   srcTrack = cms.untracked.InputTag("selectTracks"),
   vzcutmax = cms.untracked.double(15.0),
   vzcutmin = cms.untracked.double(-0.1),
   etaMin = cms.untracked.double(-2.4),
   etaMax = cms.untracked.double(2.4),
   ptMin = cms.untracked.double(0.3),
   ptMax = cms.untracked.double(3.0),
   d0cut = cms.untracked.double(3.0),
   dzcut = cms.untracked.double(10.0),
   chi2cut = cms.untracked.double(40.0),
   jetptcut = cms.untracked.double(100.0),
   minMult = cms.untracked.int32(185),
   maxMult = cms.untracked.int32(220)
)

#process.p = cms.Path(process.PAcollisionEventSelection * process.demo)
#process.p = cms.Path(process.pACentrality * process.demo)
process.p = cms.Path(process.hltHM * process.demo)
#process.p = cms.Path(process.hltHM * process.pACentrality * process.demo)
#process.p = cms.Path(process.PAcollisionEventSelection * process.pACentrality * process.demo)
#process.p = cms.Path(process.hltZeroBiasSingleTrack * process.PAcollisionEventSelection * process.pACentrality * process.demo)

