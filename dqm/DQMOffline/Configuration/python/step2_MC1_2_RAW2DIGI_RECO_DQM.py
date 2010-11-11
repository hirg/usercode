# Auto generated configuration file
# using: 
# Revision: 1.232.2.6 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step2_MC1_2 -s RAW2DIGI,RECO,DQM -n 3 --scenario HeavyIons --filein /store/relval/CMSSW_3_5_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_3XY_V21-v1/0014/6C5E7E7C-8713-DF11-A49F-001731EF61B4.root --eventcontent RECO --conditions auto:mc --geometry Ideal --mc --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryIdeal_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('DQMOffline.Configuration.DQMOfflineHeavyIonsMC_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.232.2.6 $'),
    annotation = cms.untracked.string('step2_MC1_2 nevts:3'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(30)
)

# Input source
process.source = cms.Source("PoolSource",
    #fileNames = cms.untracked.vstring('/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v2/000/150/589/6A3B6478-5AEC-DF11-BE1A-000423D996C8.root')
#    fileNames = cms.untracked.vstring('/store/relval/CMSSW_3_5_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_3XY_V21-v1/0014/6C5E7E7C-8713-DF11-A49F-001731EF61B4.root')
#    fileNames = cms.untracked.vstring('/store/himc/Fall10/Hydjet_Quenched_MinBias_2760GeV/GEN-SIM-RAW/Pyquen_UnquenchedDiJet_Pt50_MC_38Y_V12-v2/0011/FE882E72-88E1-DF11-BD71-00151796C040.root')
fileNames = cms.untracked.vstring('/store/relval/CMSSW_3_9_0/RelValHydjetQ_MinBias_2760GeV/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_39Y_V2-v1/0050/06C3C829-26D8-DF11-848E-002618943958.root')
)

process.options = cms.untracked.PSet(

)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('step2_MC1_2_RAW2DIGI_RECO_DQM.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_39Y_V3::All'

process.MonitorTrackResiduals.Tracks              = 'hiGlobalPrimTracks'
process.MonitorTrackResiduals.trajectoryInput     = 'hiGlobalPrimTracks'
process.SiPixelTrackResidualSource.TrackCandidateProducer = 'hiPrimTrackCandidates'
process.SiPixelTrackResidualSource.trajectoryInput  = 'hiGlobalPrimTracks'
process.SiStripMonitorTrack.TrackProducer = 'hiGlobalPrimTracks'
process.SiPixelHitEfficiencySource.trajectoryInput = 'hiGlobalPrimTracks'
process.hiPixel3PrimTracks.OrderedHitsFactoryPSet.GeneratorPSet.maxTriplets = cms.uint32(10000000) # or bigger if necessary


# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)

process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)

process.dqmoffline_step = cms.Path(process.DQMOfflineHeavyIons)

process.endjob_step = cms.Path(process.endOfProcess)

process.RECOoutput_step = cms.EndPath(process.RECOoutput)


# remove crashing POG modules (this modules crash on the first reconstruction step)       
#process.dqmoffline_step.remove(process.egammaDQMOffline)
#process.dqmoffline_step.remove(process.triggerOfflineDQMSource)
#process.dqmoffline_step.remove(process.pvMonitor)
#process.dqmoffline_step.remove(process.bTagPlots)
#process.dqmoffline_step.remove(process.dqmPhysics)
#process.dqmoffline_step.remove(process.jetMETDQMOfflineSource)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.dqmoffline_step,process.endjob_step,process.RECOoutput_step)
