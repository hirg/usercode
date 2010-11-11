/*
 *  See header file for a description of this class.
 *
 *  $Date: 2010/07/20 $
 *  $Revision: 1.0 $
 *  \author Shengquan Tuo - Vanderbilt
 */

#include "DQM/Physics/src/HITrackRatioDQM.h"


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <vector>

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

#include <iostream>
#include <fstream>



#include "DQMServices/Core/interface/QReport.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidate.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidateCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include <numeric>
#include <math.h>
#include <TMath.h>
#include <iostream>
#include <TStyle.h>
#include <stdio.h>

  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace math;
  using namespace HepMC;

  //int neve;
  //int neveLumi;
  //int neveCent0;
  //int neveCent1;
  //int neveCent2;
  //int neveCent3;
  //int neveCent4;
  ///int neveCent5;
  //int neveCent6;
  //int neveCent7;
  //int neveCent8;
  ///int neveCent9;
  int numLumiL;
  unsigned int eventID;
  unsigned int lumiID;
  unsigned int runID;
  int NE;
  int hpos_;
  int hneg_;
  int etapos_;
  int etaneg_;
  int phipos_;
  int phineg_;

HITrackRatioDQM::HITrackRatioDQM(const edm::ParameterSet& iConfig)//:
  //  centLabel_(iConfig.getUntrackedParameter<edm::InputTag>("hiCentrality"))
{

}

HITrackRatioDQM::~HITrackRatioDQM() { 
  

}


void HITrackRatioDQM::beginJob() {
 
  theDbe = Service<DQMStore>().operator->();

  //Book MEs
 
  theDbe->setCurrentFolder("Physics/HITrackRatio");  

  //booking histograms

  MEcontainer_["h_hiSelected"] = theDbe->book1D("h_hiSelected", "(hp-hm)/(hp+hm) vs. LumisectionID", 10, 0, 10);
  MEcontainer_["eta_hiSelected"] = theDbe->book1D("eta_hiSelected", "(etap-etam)/(etap+etam) vs. LumiSectionID", 10, 0, 10);
  MEcontainer_["phi_hiSelected"] = theDbe->book1D("phi_hiSelected", "(phip-phim)/(phip+phim) vs. LumiSectionID", 10, 0, 10);

  //MEcontainer_["h_pixel"] = theDbe->book1D("h_pixel", "(hp-hm)/(hp+hm) vs. LumisectionID", 10, 0, 10);
  //MEcontainer_["eta_pixel"] = theDbe->book1D("eta_pixel", "(etap-etam)/(etap+etam) vs. LumiSectionID", 10, 0, 10);
  //MEcontainer_["phi_pixel"] = theDbe->book1D("phi_pixel", "(phip-phim)/(phip+phim) vs. LumiSectionID", 10, 0, 10);



   eventID=0;
   lumiID=0;
   runID=0;
   numLumiL=0;
   NE=0;
   hpos_=0;
   hneg_=0;
   etapos_=0;
   etaneg_=0;
   phipos_=0;
   phineg_=0;

} 

void HITrackRatioDQM::endJob(void) {

}


void HITrackRatioDQM::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel("hiSelectedTracks", tracks);
  
  //Handle<reco::TrackCollection> trackslowpt;
  //iEvent.getByLabel("hiLowPtPixelTracks", trackslowpt);
  

  //initializing 
  double hf=0;
  int bin=0;
  //int nh[11]={0};  
  //int hpos;
  //int hneg;
  //int etapos;
  //int etaneg;
  //int phipos;
  //int phineg;

  int hposlowpt;
  int hneglowpt;
  int etaposlowpt;
  int etaneglowpt;
  int phiposlowpt;
  int phineglowpt;

  char zeroneg[200];
  char axistitle[200];
  char temp[200];

  //long eventID=0;
  //long lumiID=0;
  //long runID=0; 


  //const CentralityBins * cbins_ = 0;
  //if(!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);
  //edm::Handle<reco::Centrality> cent;
  //iEvent.getByLabel(edm::InputTag("hiCentrality"),cent);
  //iEvent.getByLabel(centLabel_,cent);

  //hf = cent->EtHFhitSum();
  //bin = cbins_->getBin(hf);

  
  if(lumiID!=iEvent.luminosityBlock()){
    //numLumiL++;
   numLumiL++; 
   hpos_=0;
   hneg_=0;
   etapos_=0;
   etaneg_=0;
   phipos_=0;
   phineg_=0;
   NE=1;

     for ( TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); track++) {
       if(track->charge()<0) hneg_++;
       if(track->charge()>0) hpos_++;
       if(track->eta()<0) etaneg_++;
       if(track->eta()>0) etapos_++;
       if(track->phi()<0) phineg_++;
       if(track->phi()>0) phipos_++;
     }

     lumiID=iEvent.luminosityBlock();
  }
  

  cout<<"lumiID = "<<lumiID<<endl;
  if(lumiID==iEvent.luminosityBlock()){

     for ( TrackCollection::const_iterator track = tracks->begin(); track != tracks->end(); track++) {
       if(track->charge()<0) hneg_++;
       if(track->charge()>0) hpos_++;
       if(track->eta()<0) etaneg_++;
       if(track->eta()>0) etapos_++;
       if(track->phi()<0) phineg_++;
       if(track->phi()>0) phipos_++;
     }
     NE++;
  }


  if(NE==15){

    //numLumiL++; 
     cout<<"numLumiL = "<<numLumiL<<endl;

     if(numLumiL==1){  // new Cent
       cout<<"hpos_="<<hpos_<<",  hneg_="<<hneg_<<endl;
       cout<<"hadron = "<<((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_)<<endl;

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==2){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==3){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL
 
     if(numLumiL==4){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==5){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==6){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==7){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==8){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==9){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

     if(numLumiL==10){  // new Cent

       if(hpos_+hneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["h_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["h_hiSelected"]->setBinContent(numLumiL,((double)hpos_-(double)hneg_)/((double)hpos_+(double)hneg_));
       }
       if(etapos_+etaneg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["eta_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["eta_hiSelected"]->setBinContent(numLumiL,((double)etapos_-(double)etaneg_)/((double)etapos_+(double)etaneg_));
       }
       if(phipos_+phineg_==0){
	 sprintf(temp,"%d,#trk=0",iEvent.luminosityBlock());
	 MEcontainer_["pih_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       }
       else{
       sprintf(temp,"%d",iEvent.luminosityBlock());
       MEcontainer_["phi_hiSelected"]->setBinLabel(numLumiL,temp,1); 
       MEcontainer_["phi_hiSelected"]->setBinContent(numLumiL,((double)phipos_-(double)phineg_)/((double)phipos_+(double)phineg_));
       }

     }  //end of numLumiL

  }  //end of if ...
     //neve++;
     //neveLumi++;


    
}













