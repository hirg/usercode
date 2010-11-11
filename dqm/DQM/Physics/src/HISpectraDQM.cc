/*
 *  See header file for a description of this class.
 *
 *  $Date: 2010/07/07 18:31:00 $
 *  $Revision: 1.0 $
 *  \author Shengquan Tuo - Vanderbilt
 */

#include "DQM/Physics/src/HISpectraDQM.h"


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <vector>

#include <string>
#include <cmath>




#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/LuminosityBlockPrincipal.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/SimpleVector.h"
#include "Math/Vector3D.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
//#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
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
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"


  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace math;
  using namespace HepMC;

HISpectraDQM::HISpectraDQM(const edm::ParameterSet& iConfig)//:
  //  centLabel_(iConfig.getUntrackedParameter<edm::InputTag>("hiCentrality"))
{

}

HISpectraDQM::~HISpectraDQM() { 
  

}


void HISpectraDQM::beginJob() {
 
  theDbe = Service<DQMStore>().operator->();

  //Book MEs
 
  theDbe->setCurrentFolder("Physics/HISpectra");  

  //book histograms for multiplicity distribution
  MEcontainer_["Pt_dist"] = theDbe->book1D("Pt_dist", "Pt distribution;Pt", 200, 0, 12);
  MEcontainer_["Phi_dist"] = theDbe->book1D("Phi_dist", "Phi distribution;Phi", 100, -4, 4);
  MEcontainer_["Eta_dist"] = theDbe->book1D("Eta_dist", "Eta distribution;Eta", 100, -4, 4);

  //book histograms for elliptic flow
  //MEcontainer_["event"] = theDbe->book1D("event", "Event distribution", 10, 0, 10);



}

void HISpectraDQM::endJob(void) {

}


void HISpectraDQM::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel("hiSelectedTracks", tracks);

     for ( TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); track++) {

       double track_eta = track->eta();      
       double track_phi = track->phi();     
       double track_pt  = track->pt();     
       int track_charge = track->charge();

       MEcontainer_["Pt_dist"]->Fill(track_pt);
       MEcontainer_["Phi_dist"]->Fill(track_phi);
       MEcontainer_["Eta_dist"]->Fill(track_eta);


     }


  //initializing 
  ///double pt;
  ///double phi;
  ///double eta;
  /*
  double hf=0;
  int bin=0;
  int nh[11]={0};  

  const CentralityBins * cbins_ = 0;
  if(!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);
  edm::Handle<reco::Centrality> cent;
  iEvent.getByLabel(edm::InputTag("hiCentrality"),cent);
  //iEvent.getByLabel(centLabel_,cent);

  hf = cent->EtHFhitSum();
  bin = cbins_->getBin(hf);

  for(int i=0;i<10;i++){
    if(i==bin){
     for ( TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); track++) {
       nh[i]++;
       nh[10]++;
     }
    }
  }
  MEcontainer_["Cent_0_100"]->Fill(nh[10]);
  if(nh[0]!=0)   MEcontainer_["Cent_0_10"]->Fill(nh[0]);
  if(nh[1]!=0)   MEcontainer_["Cent_10_20"]->Fill(nh[1]);
  if(nh[2]!=0)   MEcontainer_["Cent_20_30"]->Fill(nh[2]);
  if(nh[3]!=0)   MEcontainer_["Cent_30_40"]->Fill(nh[3]);
  if(nh[4]!=0)   MEcontainer_["Cent_40_50"]->Fill(nh[4]);
  if(nh[5]!=0)   MEcontainer_["Cent_50_60"]->Fill(nh[5]);
  if(nh[6]!=0)   MEcontainer_["Cent_60_70"]->Fill(nh[6]);
  if(nh[7]!=0)   MEcontainer_["Cent_70_80"]->Fill(nh[7]);
  if(nh[8]!=0)   MEcontainer_["Cent_80_90"]->Fill(nh[8]);
  if(nh[9]!=0)   MEcontainer_["Cent_90_100"]->Fill(nh[9]);
  */

  //for HFhits20
  /*
     for ( TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); track++) {

       nh[0]++;
       if(bin==0||bin==1) nh[1]++;
       else if(bin==2||bin==3) nh[2]++;
       else if(bin==4||bin==5) nh[3]++;
       else if(bin==6||bin==7) nh[4]++;
       else if(bin==8||bin==9) nh[5]++;
       else if(bin==10||bin==11) nh[6]++;
       else if(bin==12||bin==14) nh[7]++;
       else if(bin==14||bin==15) nh[8]++;
       else if(bin==16||bin==17) nh[9]++;
       else  nh[10]++;

     }

  MEcontainer_["Cent 0-100%"]->Fill(nh[0]);
  MEcontainer_["Cent 0-10%"]->Fill(nh[1]);
  MEcontainer_["Cent 10-20%"]->Fill(nh[2]);
  MEcontainer_["Cent 20-30%"]->Fill(nh[3]);
  MEcontainer_["Cent 30-40%"]->Fill(nh[4]);
  MEcontainer_["Cent 40-50%"]->Fill(nh[5]);
  MEcontainer_["Cent 50-60%"]->Fill(nh[6]);
  MEcontainer_["Cent 60-70%"]->Fill(nh[7]);
  MEcontainer_["Cent 70-80%"]->Fill(nh[8]);
  MEcontainer_["Cent 80-90%"]->Fill(nh[9]);
  MEcontainer_["Cent 90-100%"]->Fill(nh[10]);

  MEcontainer_["event"]->Fill(bin);
  */
    
}













