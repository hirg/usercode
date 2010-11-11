import FWCore.ParameterSet.Config as cms

from DQM.Physics.bphysicsOniaDQM_cfi import *
#from DQM.Physics.ewkDQM_cfi import *
#from DQM.Physics.ewkMuDQM_cfi import *
#from DQM.Physics.ewkElecDQM_cfi import *
#from DQM.Physics.ewkMuLumiMonitorDQM_cfi import *
#from DQM.Physics.qcdPhotonsDQM_cfi import *
#from DQM.Physics.qcdHighPtDQM_cfi import *
#from DQM.Physics.topDiLeptonOfflineDQM_cfi import *
#from DQM.Physics.topSingleLeptonDQM_cfi import *
#from DQM.Physics.ewkMuLumiMonitorDQM_cfi import *
#from DQM.Physics.ewkTauDQM_cfi import *
#from DQM.Physics.susyDQM_cfi import *
#from DQM.Physics.qcdUeDQM_cfi import *
#from DQM.Physics.HiggsDQM_cfi import *
#from JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff import *

#from DQM.Physics.hICentralityDQM_cfi import *
from DQM.Physics.hITrackRatioDQM_cfi import *
from DQM.Physics.hISpectraDQM_cfi import *
from DQM.Physics.hIFlowDQM_cfi import *
from DQM.Physics.hIPhotonDQM_cfi import *
from DQM.Physics.hICorrelationDQM_cfi import *


dqmPhysics = cms.Sequence( bphysicsOniaDQM
			*hITrackRatioDQM
			*hISpectraDQM
			*hIFlowDQM
			*hIPhotonDQM
			*hICorrelationDQM )
#			*hICentralityDQM

#			  *ewkDQM
#                         *ewkMuDQM
#                         *ewkElecDQM
#                         *ewkMuLumiMonitorDQM
#			  *qcdPhotonsDQM
#                         *qcdHighPtDQM
#                         *topDiLeptonOfflineDQM
#                         *topSingleLeptonDQM
#                         *ewkTauDQM
#                         *susyDQM
#			  *QcdUeDQM
#                         *HiggsDQM
#			 )

