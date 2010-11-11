import FWCore.ParameterSet.Config as cms

hICorrelationDQM = cms.EDAnalyzer("HICorrelationDQM",
#   disable all warnings
    maxNumWarnings = cms.int32(0),
)

