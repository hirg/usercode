/*
 *  See header file for a description of this class.
 *
 *  $Date: 2010/09/01 15:35:00 $
 *  $Revision: 1.0 $
 *  \author Shengquan Tuo - Vanderbilt
 */

#include "DQM/Physics/src/HIPhotonDQM.h"


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include <vector>

#include <string>
#include <cmath>




#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Framework/interface/LuminosityBlockPrincipal.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <string>


#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"
//#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/SimpleVector.h"
#include "Math/Vector3D.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
//#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/DetId/interface/DetId.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

/// EgammaCoreTools
#include "RecoEcal/EgammaCoreTools/interface/PositionCalc.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalEtaPhiRegion.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

// Geometry
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/CaloTopology/interface/CaloSubdetectorTopology.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloTopology/interface/EcalEndcapTopology.h"
#include "Geometry/CaloTopology/interface/EcalBarrelTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"



#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Track/interface/CoreSimTrack.h"
#include "SimDataFormats/EncodedEventId/interface/EncodedEventId.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/UpdatablePSimHit.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"



#include <iostream>


  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace math;
  using namespace HepMC;

HIPhotonDQM::HIPhotonDQM(const edm::ParameterSet& iConfig)//:
  //  centLabel_(iConfig.getUntrackedParameter<edm::InputTag>("hiCentrality"))
{

}

HIPhotonDQM::~HIPhotonDQM() { 
  

}


void HIPhotonDQM::beginJob() {
 
  theDbe = Service<DQMStore>().operator->();

  //Book MEs
 
  theDbe->setCurrentFolder("Physics/HIPhoton");  

  //book histograms for multiplicity distribution
  MEcontainer_["dndphi"] = theDbe->book1D("dndphi", "dN/dPhi of SuperCluster ", 80, -4, 4); // in Barrel
  MEcontainer_["dndeta"] = theDbe->book1D("dndeta", "dN/dEta of SuperCluster ", 80, -4, 4); // in Barrel
  MEcontainer_["esumeb"] = theDbe->book1D("esumeb", "Total Energy of Ecal Barrel Clusters", 500, 0, 500);

} 

void HIPhotonDQM::endJob(void) {

}


void HIPhotonDQM::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  Handle<reco::PhotonCollection> photonCollection; 
  iEvent.getByLabel("photons",photonCollection);
  if ( !photonCollection.isValid()) {
    cout<< "Error! Can't get the product "<< "photonCollection_ "<< endl;
    //validPhotons=false;
  }
 for( reco::PhotonCollection::const_iterator  iPho = photonCollection->begin(); iPho != photonCollection->end(); iPho++) {

   //if ( fabs((*iPho).superCluster()->eta()) <  1.479 ){
  MEcontainer_["dndphi"]->Fill((*iPho).superCluster()->phi());
  MEcontainer_["dndeta"]->Fill((*iPho).superCluster()->eta());
  // }
  //cout<<"Eta = "<<(*iPho).superCluster()->eta()<<", Phi = "<<(*iPho).superCluster()->phi()<<endl;
 }

     double etEBSum=0;
     Handle<BasicClusterCollection> clusters;
     iEvent.getByLabel("hybridSuperClusters","hybridBarrelBasicClusters", clusters);
     for( size_t i = 0; i<clusters->size(); ++ i){
	const BasicCluster & cluster = (*clusters)[ i ];
	double tg = cluster.position().rho()/cluster.position().r();
        double et = cluster.energy()*tg;
	etEBSum += et;
     }

     MEcontainer_["esumeb"]->Fill(etEBSum);
     //cout<<"etEBSum = "<<etEBSum<<endl;


}













