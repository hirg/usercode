import FWCore.ParameterSet.Config as cms

hIFlowDQM = cms.EDAnalyzer("HIFlowDQM",
#   disable all warnings
    maxNumWarnings = cms.int32(0),
)

