import FWCore.ParameterSet.Config as cms

# DQM monitor module for BPhysics: onia resonances
bphysicsOniaDQM = cms.EDAnalyzer("BPhysicsOniaDQM",
                              MuonCollection = cms.InputTag("muons"),
                              vertex = cms.InputTag("hiSelectedVertex"),
)


