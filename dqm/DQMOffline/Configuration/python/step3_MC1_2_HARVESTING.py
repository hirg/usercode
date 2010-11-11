# Auto generated configuration file
# using: 
# Revision: 1.232.2.6 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step3_MC1_2 -s HARVESTING:dqmHarvesting --harvesting AtRunEnd --conditions auto:mc --geometry Ideal --filein file:step2_MC1_2_RAW2DIGI_RECO_DQM.root --mc --no_exec --scenario HeavyIons
import FWCore.ParameterSet.Config as cms

process = cms.Process('HARVESTING')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryIdeal_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.EDMtoMEAtRunEnd_cff')
process.load('Configuration.StandardSequences.HarvestingHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.232.2.6 $'),
    annotation = cms.untracked.string('step3_MC1_2 nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:step2_MC1_2_RAW2DIGI_RECO_DQM.root'),
    processingMode = cms.untracked.string('RunsAndLumis')
)

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    fileMode = cms.untracked.string('FULLMERGE')
)

# Output definition

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_39Y_V3::All'

# Path and EndPath definitions
process.edmtome_step = cms.Path(process.EDMtoME)

process.validationHarvestingHI = cms.Path(process.postValidationHI)

process.dqmHarvesting = cms.Path(process.DQMOfflineHeavyIons_SecondStep*process.DQMOfflineHeavyIons_Certification)

process.validationHarvesting = cms.Path(process.postValidationHI)

process.dqmHarvestingPOG = cms.Path(process.DQMOfflineHeavyIons_SecondStep_PrePOG)

process.dqmsave_step = cms.Path(process.DQMSaver)


# remove crashing clients from POG
#process.dqmHarvesting.remove(process.photonOfflineDQMClient)
#process.dqmHarvesting.remove(process.triggerOfflineDQMClient)
#process.dqmHarvesting.remove(process.hltOfflineDQMClient)
#process.dqmHarvesting.remove(process.bTagCollectorSequence)

process.dqmHarvesting.remove(process.jetMETDQMOfflineClient)
process.dqmHarvesting.remove(process.dataCertificationJetMET)


process.dqmSaver.dirName = "/afs/cern.ch/user/t/tuos/scratch0/"
#process.dqmSaver.workflow = '/Hydjet/CMSSW_3_7_0/job_0'
process.dqmSaver.workflow = '/Hydjet/CMSSW_3_9_2/25evts'


# Schedule definition
process.schedule = cms.Schedule(process.edmtome_step,process.dqmHarvesting,process.dqmsave_step)
