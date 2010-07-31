// -*- C++ -*-
//
// Package:    DataTrans
// Class:      DataTrans
// 
/**\class DataTrans DataTrans.cc Analyzer/DataTrans/src/DataTrans.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tuo Shengquan
//         Created:  Tue Jul 27 14:50:36 EDT 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"

#include <string>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/LuminosityBlockPrincipal.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/SimpleVector.h"
#include "Math/Vector3D.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
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

#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1I.h"
#include "TNtuple.h"


#define maxnh 20000
#define maxnjet 200

  Int_t d_nh; 
  Int_t d_bin;
  Float_t d_pt[maxnh];    
  Float_t d_phi[maxnh];     
  Float_t d_eta[maxnh];

  Float_t d_npart;
  Float_t d_npartsig;
  Float_t d_ncoll;
  Float_t d_ncollsig;

  Int_t d_njet;
  Float_t d_jetpt[maxnjet];
  Float_t d_jetphi[maxnjet];
  Float_t d_jeteta[maxnjet];


typedef std::vector<TrackingParticle>                   TrackingParticleCollection;
typedef TrackingParticleRefVector::iterator               tp_iterator;

//
// class declaration
//

class DataTrans : public edm::EDAnalyzer {
   public:
      explicit DataTrans(const edm::ParameterSet&);
      ~DataTrans();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

  //void trackCM_GEN(const edm::Event&, const edm::EventSetup&);   
      void trackCM_RECO(const edm::Event&, const edm::EventSetup&); 

   TTree *evttree;
   edm::Service<TFileService> fs;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DataTrans::DataTrans(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


DataTrans::~DataTrans()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DataTrans::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;


   using namespace edm;
   using namespace std;
   using namespace reco;
   using namespace HepMC;
   cout<<" ana start, now in DataTrans::analyze()"<<endl;

   trackCM_RECO(iEvent, iSetup);



}


// ------------ method called once each job just before starting event loop  ------------
void 
DataTrans::beginJob()
{

   evttree = fs->make<TTree>("evttree","event tree");
   evttree->Branch("nh",&d_nh,"nh/I");  
   evttree->Branch("bin",&d_bin,"bin/I"); 
   evttree->Branch("npart",&d_npart,"npart/F");
   evttree->Branch("npartsig",&d_npartsig,"npartsig/F");
   evttree->Branch("ncoll",&d_ncoll,"ncoll/F");
   evttree->Branch("ncollsig",&d_ncollsig,"ncollsig/F");
   evttree->Branch("pt",&d_pt,"pt[nh]/F");  
   evttree->Branch("phi",&d_phi,"phi[nh]/F");  
   evttree->Branch("eta",&d_eta,"eta[nh]/F");

   evttree->Branch("njet",&d_njet,"njet/I");
   evttree->Branch("jetpt",d_jetpt,"jetpt[njet]/F");
   evttree->Branch("jetphi",d_jetphi,"jetphi[njet]/F");
   evttree->Branch("jeteta",d_jeteta,"jeteta[njet]/F");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
DataTrans::endJob() {

}


// ------------ method called to for each event  ------------
void
DataTrans::trackCM_RECO(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace HepMC;

  double hf=0;
  int bin=-1;


   edm::Handle<reco::RecoChargedCandidateCollection> trackCollection;
   iEvent.getByLabel("allMergedPtSplit12Tracks",trackCollection);

   edm::Handle<reco::CaloJetCollection> calJets;
   bool ValidCaloJet_ = iEvent.getByLabel ("iterativeConePu5CaloJets",calJets);
   if(!ValidCaloJet_)return;
   //std::cout<<" Jet size "<<(*calJets).size()<<std::endl; 


  const CentralityBins * cbins_ = 0;
  if(!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);
  edm::Handle<reco::Centrality> cent;
  iEvent.getByLabel(edm::InputTag("hiCentrality"),cent);
  if(!cent.isValid()){
    cout<<"Error! Can't get hiCentrality product!"<<endl;
    return ;
  }
  hf = cent->EtHFhitSum();
  bin = cbins_->getBin(hf);
  d_bin=bin;

  double npart = cbins_->NpartMean(hf);
  double npartsig = cbins_->NpartSigma(hf);
  d_npart=npart;
  d_npartsig=npartsig;

  double ncoll = cbins_->NcollMean(hf);
  double ncollsig = cbins_->NcollSigma(hf);
  d_ncoll=ncoll;
  d_ncollsig=ncollsig;

  //if((*calJets).size()>=1){
  if((*calJets).size()>=0){
  int nh=0;  

       if(trackCollection.isValid())
       {
          const reco::RecoChargedCandidateCollection * tracks =
trackCollection.product();
          reco::RecoChargedCandidateCollection::const_iterator tracksItr;
          for (tracksItr=tracks->begin(); tracksItr!=tracks->end();
++tracksItr)
            { // if(nh>=20000) continue;
            double track_eta = tracksItr->eta();
            double track_phi = tracksItr->phi();
            double track_pt  = tracksItr->pt();

        d_pt[nh]=track_pt;
        d_phi[nh]=track_phi;
        d_eta[nh]=track_eta;

        nh++;

        }
       }

  cout<<"Number of tracks in this event: "<<nh<<endl;   
  d_nh=nh;

  int njet=0;


   if(calJets.isValid()){
	 reco::CaloJetCollection::const_iterator jet = calJets->begin();

	 for (; jet != calJets->end(); jet++)
            { 
            double jet_eta = jet->eta();
            double jet_phi = jet->phi();
            double jet_pt  = jet->pt();
        d_jetpt[njet]=jet_pt;
        d_jetphi[njet]=jet_phi;
        d_jeteta[njet]=jet_eta;

        njet++;

        }
       }

       d_njet=(*calJets).size();
       //cout<<"# jet from njet = "<<njet<<", (*calJets).size()="<<(*calJets).size()<<endl;

 // if(nh<20000)
  evttree->Fill(); 
  }

#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif
  
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif

}

//define this as a plug-in
DEFINE_FWK_MODULE(DataTrans);
