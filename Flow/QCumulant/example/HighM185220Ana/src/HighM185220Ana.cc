// -*- C++ -*-
//
// Package:    HighM185220Ana
// Class:      HighM185220Ana
// 
/**\class HighM185220Ana HighM185220Ana.cc TestAna/HighM185220Ana/src/HighM185220Ana.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Sat Jan 19 10:15:27 CST 2013
// $Id$
//
//


// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TRandom.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"
//const int NtrkBin=18;
//const int binboundaries[NtrkBin+1]={50000,350,290,260,240,220,185,150,120,100,80,70,65,60,55,50,40,20,0};
//const int NtrkBin=17;
//const int binboundaries[NtrkBin+1]={50000,350,290,260,240,220,185,150,120,100,80,60,50,40,30,20,10,0};  //standard
//const int binboundaries[NtrkBin+1]={50000,260,240,220,185,150,120,100,90,80,70,60,50,40,30,20,10,0};    //v1
//const int binboundaries[NtrkBin+1]={50000,220,185,150,120,100,95,90,85,80,75,70,65,60,50,40,30,0};      //v2
//const int binboundaries[NtrkBin+1]={50000,150,120,100,95,90,85,80,75,70,65,60,55,50,45,40,30,0};          //v3
//const int NtrkBin=27;
//const int binboundaries[NtrkBin+1]={50000,150,120,116,112,108,104,100,96,92,88,84,80,76,72,68,64,60,59,56,53,50,49,46,43,40,30,0};  //v7,27
//const int NtrkBin=44;
//const int binboundaries[NtrkBin+1]={50000,150,120,118,116,114,112,110,108,106,104,102,100,98,96,94,92,90,88,86,84,82,80,78,76,74,72,70,68,66,64,62,60,58,56,54,52,50,48,46,44,42,40,30,0};  //v8,44
//const int NtrkBin=20;
//const int binboundaries[NtrkBin+1]={50000,150,120,115,110,105,100,95,90,85,80,75,70,65,60,55,50,45,40,30,0};   //v9, bin of 5
const int NtrkBin=20;
const int binboundaries[NtrkBin+1]={50000,220,219,217,215,213,211,209,207,205,203,201,199,197,195,193,191,189,187,185,0};    //new HM
#include "/net/hisrv0001/home/tuos/CMSSW_5_3_8_HI_patch2/src/Analysis/HighM185220Ana/interface/HighM185220Ana.h"

//
// class declaration
//

class HighM185220Ana : public edm::EDAnalyzer {
   public:
      explicit HighM185220Ana(const edm::ParameterSet&);
      ~HighM185220Ana();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
   edm::Service<TFileService> fs;
   edm::InputTag srcTrack_;
   double vzcutmin_;
   double vzcutmax_;
   double etaMin_;
   double etaMax_;
   double ptMin_;
   double ptMax_;
   double d0cut_;
   double dzcut_;
   double chi2cut_;
   double jetptcut_;
   int minMult_;
   int maxMult_;

   TH1D* hMult;
   TH1D* hpt;
   TH1D* heta;
   TH1D* hphi;
   TH1D* hvz;
   TH1D* hvx;
   TH1D* hvy;
TH1D * NtrkBinHist_;
TH1D * trkHist_;
TH1D * trkHistFull_;
TH1D * centHist_;
TH1D * CentMult[NtrkBin];
      
CentralityProvider * centrality_;

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
HighM185220Ana::HighM185220Ana(const edm::ParameterSet& iConfig):

  srcTrack_(iConfig.getUntrackedParameter<edm::InputTag>("srcTrack")),
  vzcutmin_(iConfig.getUntrackedParameter<double>("vzcutmin")),
  vzcutmax_(iConfig.getUntrackedParameter<double>("vzcutmax")),
  etaMin_(iConfig.getUntrackedParameter<double>("etaMin")),
  etaMax_(iConfig.getUntrackedParameter<double>("etaMax")),
  ptMin_(iConfig.getUntrackedParameter<double>("ptMin")),
  ptMax_(iConfig.getUntrackedParameter<double>("ptMax")),
  d0cut_(iConfig.getUntrackedParameter<double>("d0cut")),
  dzcut_(iConfig.getUntrackedParameter<double>("dzcut")),
  chi2cut_(iConfig.getUntrackedParameter<double>("chi2cut")),
  jetptcut_(iConfig.getUntrackedParameter<double>("jetptcut")),
  minMult_(iConfig.getUntrackedParameter<int>("minMult")),
  maxMult_(iConfig.getUntrackedParameter<int>("maxMult"))
{
   //now do what ever initialization is needed

}


HighM185220Ana::~HighM185220Ana()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   fclose(outRef);
   fclose(outDiff);
}


//
// member functions
//

// ------------ method called for each event  ------------
void
HighM185220Ana::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   //using namespace HepMC;
       Nh=0; had=0; nh=0;
       w2=0.0; w4=0.0; w6=0.0; w8=0.0;
       AziCorr22=0.0; AziCorr24=0.0; AziCorr26=0.0; AziCorr28=0.0;
       Q2Re=0.0; Q4Re=0.0; Q422Re=0.0; Q6Re=0.0; Q8Re=0.0;
       Q2Im=0.0; Q4Im=0.0; Q422Im=0.0; Q6Im=0.0; Q8Im=0.0;
       for(ipt=0;ipt<NPtBin;ipt++){
         Nhp[ipt]=0;  ptm[ipt]=0; mqp[ipt]=0;
         w2p[ipt]=0; w4p[ipt]=0; w6p[ipt]=0; w8p[ipt]=0;
         q2pRe[ipt]=0; q4pRe[ipt]=0; q6pRe[ipt]=0; q8pRe[ipt]=0;
         q2pIm[ipt]=0; q4pIm[ipt]=0; q6pIm[ipt]=0; q8pIm[ipt]=0;
         mq2pRe[ipt]=0; mq4pRe[ipt]=0; mq6pRe[ipt]=0; mq8pRe[ipt]=0;
         mq2pIm[ipt]=0; mq4pIm[ipt]=0; mq6pIm[ipt]=0; mq8pIm[ipt]=0;
         AziCorr22p[ipt]=0;  AziCorr24p[ipt]=0;  AziCorr26p[ipt]=0;  AziCorr28p[ipt]=0;
       }

/*
     edm::Handle<reco::VertexCollection> vtx;
     iEvent.getByLabel("offlinePrimaryVertices",vtx);
     math::XYZPoint vtxPos(0,0,0);
     double oPVvz=-999.9, oPVvx=-999.9, oPVvy=-999.9;
     //double vzErr =0, vxErr=0, vyErr=0;
     if(vtx->size() > 0) {
        vtxPos = vtx->begin()->position();
        oPVvz=vtx->begin()->z();
        oPVvx=vtx->begin()->x();
        oPVvy=vtx->begin()->y();
    hvz->Fill(oPVvz);
    hvx->Fill(oPVvx);
    hvy->Fill(oPVvy);
    //cout<<"vz="<<oPVvz<<" ,  vzErr="<<vzErr<<endl;
     }
*/

     double vx[1000];
     double vy[1000];
     double vz[1000];
     double vxError[1000];
     double vyError[1000];
     double vzError[1000];

       const reco::VertexCollection * recoVertices;
       edm::Handle<reco::VertexCollection> vertexCollection;
       //cout <<"srcVertex_[iv]= " <<srcVertex_[iv]<<endl;
       iEvent.getByLabel("offlinePrimaryVertices",vertexCollection);
       recoVertices = vertexCollection.product();
       unsigned int daughter = 0;
       //int nVertex = 0;
       int greatestvtx = 0;

       //nVertex = recoVertices->size();
       for (unsigned int i = 0 ; i< recoVertices->size(); ++i){
         daughter = (*recoVertices)[i].tracksSize();
         if( daughter > (*recoVertices)[greatestvtx].tracksSize()) greatestvtx = i;
           //cout <<"Vertex: "<< (*recoVertices)[i].position().z()<<" , tracksSize= "<<daughter<<",  vertex size="<<recoVertices->size()<<endl;
       }

       if(recoVertices->size()>0){
         vx[1] = (*recoVertices)[greatestvtx].position().x();
         vy[1] = (*recoVertices)[greatestvtx].position().y();
         vz[1] = (*recoVertices)[greatestvtx].position().z();
         vxError[1] = (*recoVertices)[greatestvtx].xError();
         vyError[1] = (*recoVertices)[greatestvtx].yError();
         vzError[1] = (*recoVertices)[greatestvtx].zError();
        hvz->Fill(vz[1]);
        hvx->Fill(vx[1]);
        hvy->Fill(vy[1]);
       }else{
         vx[1] =  -99;
         vy[1] =  -99;
         vz[1] =  -99;
         vxError[1] =  -99;
         vyError[1] =  -99;
         vzError[1] =  -99;
       }

    math::XYZPoint v1(vx[1],vy[1], vz[1]);

    //if(fabs(vz[1])<vzcutmax_ && recoVertices->size()==1 ){
    //if(fabs(vz[1])<vzcutmax_ && (recoVertices->size()==1||recoVertices->size()==2 ) ){
    //if(fabs(vz[1])>vzcutmin_&&fabs(vz[1])<vzcutmax_){
    if(fabs(vz[1])<vzcutmax_){
    int nTracks = 0;
    edm::Handle<reco::TrackCollection> tracks;
    iEvent.getByLabel(srcTrack_,tracks);
    hMult->Fill(tracks->size());
    for(unsigned it=0; it<tracks->size(); ++it){
      const reco::Track & track = (*tracks)[it];
      double eta = track.eta();
      double phi = track.phi();
      double pt  = track.pt();
      hpt->Fill(pt);
      heta->Fill(eta);
      hphi->Fill(phi);
      //if(pt>1&&pt<2) cout<<"eta= "<<eta<<"  pt="<<pt<<"  phi="<<phi<<" #####, track.size = "<<tracks->size()<<endl;
       double dz = track.dz(v1);
       double dzsigma = sqrt(track.dzError()*track.dzError()+vzError[1]*vzError[1]);
       double dxy= track.dxy(v1);
       double dxysigma = sqrt(track.dxyError()*track.dxyError()+vxError[1]*vyError[1]);
       //if( track.quality(reco::TrackBase::highPurity) && track.pt()>0.1 && fabs(track.eta())<2.4 && track.ptError()/track.pt()<0.1 && fabs(dz/dzsigma)<3.0 && fabs(dxy/dxysigma)<3.0 && track.pt()<100.0) {
       if( track.quality(reco::TrackBase::highPurity) && track.pt()>0.1 && fabs(track.eta())<2.4 && fabs(dz/dzsigma)<5.0 && fabs(dxy/dxysigma)<5.0) {
         //if(track.pt()>0.1 && track.ptError()/track.pt()<0.05 && fabs(dz/dzsigma)<2.0 && fabs(dxy/dxysigma)<2.0){
        //if(fabs(track.eta())<2.4 && track.pt()>0.1){
           phi0[nh]=track.phi(); pt0[nh]=track.pt(); eta0[nh]=track.eta();
           nh++;
          //}         
         if(track.pt()>0.4) nTracks++;
         //if(track.pt()>0.4 && fabs(dz/dzsigma)<3.0 && fabs(dxy/dxysigma)<3.0) nTracks++;
        }
    } // tracks;

   int trkbin=-1;
   //binboundaries[0]=maxMult_; binboundaries[1]=minMult_;
   //cout<<"binboundaries="<<binboundaries[0]<<"  "<<binboundaries[1]<<endl;
   for(int i=0;i<NtrkBin;i++)
      if(nTracks<binboundaries[i]&&nTracks>=binboundaries[i+1])
        trkbin=i;
   //NtrkBinHist_->Fill(trkbin);
   trkHistFull_->Fill(nTracks);
/*
   centrality_=0;
   if(!centrality_) centrality_ = new CentralityProvider(iSetup);
   centrality_->newEvent(iEvent,iSetup); // make sure you do this first in every event
   //double c = centrality_->centralityValue();
   int bin = centrality_->getBin();
   //cout<<"bin="<<bin<<endl;
   //centHist_->Fill(bin);
   //bin=bin-20;
*/ int bin=0;
   //int CentBin=int(bin/20);
   int CentBin=int(trkbin/1);
   //CentMult[CentBin]->Fill(bin*1.0); 

  //if (CentBin < NCentBin  && fabs(oPVvz) <= vzcut_)  { 
  if (CentBin>=0 && CentBin < NCentBin )  { 
      //cout<<"CentBin="<<CentBin<<", NCentBin="<<NCentBin<<", bin="<<bin<<", vz="<<oPVvz<<endl;
      trkHist_->Fill(nTracks);  
      //CentMult[CentBin]->Fill(bin*1.0); 
      CentMult[CentBin]->Fill(nTracks); 
      centHist_->Fill(bin);
      NtrkBinHist_->Fill(trkbin);

      had=nh*1.0;
      int nha=nh;
        for(nh=0;nh<nha;nh++){
         if(pt0[nh]>ptMin_&&pt0[nh]<ptMax_&&eta0[nh]>etaMin_&&eta0[nh]<etaMax_){
           Nh=Nh+1;
          }
         }
      if(Nh>3){
        for(nh=0;nh<nha;nh++){
         if(pt0[nh]>ptMin_&&pt0[nh]<ptMax_&&eta0[nh]>etaMin_&&eta0[nh]<etaMax_){
           Q2Re+=cos(2.0*phi0[nh]);  Q2Im+=sin(2.0*phi0[nh]);
           Q4Re+=cos(4.0*phi0[nh]);  Q4Im+=sin(4.0*phi0[nh]);
           //Nh=Nh+1;
          }
         for(ipt=0;ipt<NPtBin;ipt++) {
          if((pt0[nh]>minptcut[ipt]&&pt0[nh]<=maxptcut[ipt])){
             inttemp=ipt;
             if(pt0[nh]>ptMin_&&pt0[nh]<ptMax_&&eta0[nh]>etaMin_&&eta0[nh]<etaMax_){
               mqp[inttemp] = mqp[inttemp] +1.0;
               mq2pRe[ipt]+=cos(2.0*phi0[nh]); mq2pIm[ipt]+=sin(2.0*phi0[nh]);
               mq4pRe[ipt]+=cos(4.0*phi0[nh]); mq4pIm[ipt]+=sin(4.0*phi0[nh]);            
              }  
           }
          //else inttemp=NPtBin-1;  //this makes the last pt bin biased;
         }
         ipt=inttemp;
         Nhp[ipt]=Nhp[ipt]+1.0;   ptm[ipt]=ptm[ipt]+pt0[nh];
         q2pRe[ipt]+=cos(2.0*phi0[nh]); q2pIm[ipt]+=sin(2.0*phi0[nh]);
         q4pRe[ipt]+=cos(4.0*phi0[nh]); q4pIm[ipt]+=sin(4.0*phi0[nh]);
  
         //if(ipt==0) cout<<"nh="<<nh<<", ###. pt of the track in the first pt bin="<<pt0[nh]<<",  Nhp[0]="<<Nhp[0]<<endl;
        } //end of loop over nha tracks

        Q422Re=Q4Re*(Q2Re*Q2Re-Q2Im*Q2Im)+2.0*Q4Im*Q2Re*Q2Im;
        //Q422Im=Q4Im*(Q2Re*Q2Re-Q2Im*Q2Im)-2.0*Q4Re*Q2Re*Q2Im;
        SumMult[CentBin]+=Nh*1.0;
         w2=Nh*(Nh-1)*1.0;
         w4=Nh*(Nh-1)*(Nh-2)*(Nh-3)*1.0;
         //w6=Nh*(Nh-1)*(Nh-2)*(Nh-3)*(Nh-4)*(Nh-5)*1.0;
         //w8=Nh*(Nh-1)*(Nh-2)*(Nh-3)*(Nh-4)*(Nh-5)*(Nh-6)*(Nh-7)*1.0;
         AziCorr22=(Q2Re*Q2Re+Q2Im*Q2Im-Nh*1.0)/w2;
         AziCorr24=(pow(sqrt(Q2Re*Q2Re+Q2Im*Q2Im),4)+Q4Re*Q4Re+Q4Im*Q4Im-2.0*Q422Re)/w4 - 2.0*(2.0*(Nh*1.0-2)*(Q2Re*Q2Re+Q2Im*Q2Im)-Nh*(Nh-3)*1.0)/w4;
       Sumw2[CentBin]+=w2;  Sumw4[CentBin]+=w4; Sumw2w4[CentBin]+=w2*w4;
       //Sumw6[CentBin]+=w6;  Sumw8[CentBin]+=w8;
       Sumw2sq[CentBin]+=w2*w2; Sumw4sq[CentBin]+=w4*w4;
       Sumw2A2[CentBin]+=w2*AziCorr22; Sumw4A4[CentBin]+=w4*AziCorr24;
       //Sumw6A6[CentBin]+=w6*AziCorr26; Sumw8A8[CentBin]+=w8*AziCorr28;
       Sumw2A2sq[CentBin]+=w2*AziCorr22*AziCorr22; Sumw4A4sq[CentBin]+=w4*AziCorr24*AziCorr24;
       Sumw2w4A2A4[CentBin]+=w2*w4*AziCorr22*AziCorr24;
       //cout<<"ne="<<ne<<", Nh="<<Nh<<", w2="<<w2<<", w4="<<w4<<", w6="<<w6<<", w8="<<w8<<endl;
       //cout<<"Sumw2A2="<<Sumw2A2[CentBin]<<", Sumw4A4="<<Sumw4A4[CentBin]<<", Sumw6A6="<<Sumw6A6[CentBin]<<", Sumw8A8="<<Sumw8A8[CentBin]<<endl;
//diff; 
       for(ipt=0;ipt<NPtBin;ipt++) {
         ptmp[ipt]=ptm[ipt];
         //SumMultp[CentBin][ipt]+=((double) Nhp[ipt]);
         //SumMultp[CentBin][ipt]+= 1.0*Nhp[ipt];
         //w2p[ipt]=Nhp[ipt]*(Nh-1)*1.0;  w4p[ipt]=Nhp[ipt]*(Nh-1)*(Nh-2)*(Nh-3)*1.0;
         //if(w4p[ipt]>0){ 
         if(Nhp[ipt]>0){ 
         meanPt[CentBin][ipt]=meanPt[CentBin][ipt]+ptmp[ipt];
         mptmp[CentBin][ipt]+=ptmp[ipt];
         //w2p[ipt]=Nhp[ipt]*(Nh-1)*1.0;  w4p[ipt]=Nhp[ipt]*(Nh-1)*(Nh-2)*(Nh-3)*1.0;
         w2p[ipt]=Nhp[ipt]*Nh*1.0 - mqp[ipt];  
         w4p[ipt]=(Nhp[ipt]*Nh*1.0 - 3.0*mqp[ipt])*(Nh-1)*(Nh-2)*1.0;
         SumMultp[CentBin][ipt]+= Nhp[ipt];
         //AziCorr22p[ipt]=(q2pRe[ipt]*Q2Re+q2pIm[ipt]*Q2Im-Nhp[ipt])/w2p[ipt];
         AziCorr22p[ipt]=(q2pRe[ipt]*Q2Re+q2pIm[ipt]*Q2Im-mqp[ipt])/w2p[ipt];
         //AziCorr24p[ipt]=((Q2Re*Q2Re+Q2Im*Q2Im)*(q2pRe[ipt]*Q2Re+q2pIm[ipt]*Q2Im) - (q4pRe[ipt]*(Q2Re*Q2Re-Q2Im*Q2Im)+2.0*q4pIm[ipt]*Q2Re*Q2Im)
         //- (q2pRe[ipt]*(Q2Re*Q4Re-Q2Im*Q4Im)+q2pIm[ipt]*(Q2Re*Q4Im-Q2Im*Q4Re)) + q4pRe[ipt]*Q4Re+q4pIm[ipt]*Q4Im)/w4p[ipt]
         //- 2.0*(Nhp[ipt]*(Q2Re*Q2Re+Q2Im*Q2Im)+(Nh-3)*(q2pRe[ipt]*Q2Re+q2pIm[ipt]*Q2Im)-(Q2Re*q2pRe[ipt]+Q2Im*q2pIm[ipt]))/w4p[ipt] + 2.0/(Nh-1)/(Nh-2);
         AziCorr24p[ipt]=((Q2Re*Q2Re+Q2Im*Q2Im)*(q2pRe[ipt]*Q2Re+q2pIm[ipt]*Q2Im) - (mq4pRe[ipt]*(Q2Re*Q2Re-Q2Im*Q2Im)+2.0*mq4pIm[ipt]*Q2Re*Q2Im)
         - (q2pRe[ipt]*(Q2Re*Q4Re+Q2Im*Q4Im)+q2pIm[ipt]*(Q2Re*Q4Im-Q2Im*Q4Re)) - 2.0*Nh*(q2pRe[ipt]*Q2Re+q2pIm[ipt]*Q2Im)  
         - 2.0*mqp[ipt]*(Q2Re*Q2Re+Q2Im*Q2Im) + 7.0*(mq2pRe[ipt]*Q2Re+mq2pIm[ipt]*Q2Im) - (Q2Re*mq2pRe[ipt]+Q2Im*mq2pIm[ipt])
         + (mq4pRe[ipt]*Q4Re+mq4pIm[ipt]*Q4Im) + 2.0*(q2pRe[ipt]*Q2Re+q2pIm[ipt]*Q2Im) + 2.0*mqp[ipt]*Nh -6.0*mqp[ipt])/w4p[ipt];

         Sumw2p[CentBin][ipt]+=w2p[ipt];  Sumw4p[CentBin][ipt]+=w4p[ipt];
         Sumw2A2p[CentBin][ipt]+=w2p[ipt]*AziCorr22p[ipt]; Sumw4A4p[CentBin][ipt]+=w4p[ipt]*AziCorr24p[ipt];
         //diff error, 2
         Sumw2psq[CentBin][ipt]+=w2p[ipt]*w2p[ipt]; Sumw2pA2psq[CentBin][ipt]+=w2p[ipt]*AziCorr22p[ipt]*AziCorr22p[ipt];
         Sumw2w2p[CentBin][ipt]+=w2*w2p[ipt]; Sumw2w2pA2A2p[CentBin][ipt]+=w2*w2p[ipt]*AziCorr22*AziCorr22p[ipt];
         //diff error, 4
         Sumw4psq[CentBin][ipt]+=w4p[ipt]*w4p[ipt]; Sumw4pA4psq[CentBin][ipt]+=w4p[ipt]*AziCorr24p[ipt]*AziCorr24p[ipt];
         Sumw2w4p[CentBin][ipt]+=w2*w4p[ipt]; Sumw2w4pA2A4p[CentBin][ipt]+=w2*w4p[ipt]*AziCorr22*AziCorr24p[ipt];
         Sumw4w2p[CentBin][ipt]+=w4*w2p[ipt]; Sumw4w2pA4A2p[CentBin][ipt]+=w4*w2p[ipt]*AziCorr24*AziCorr22p[ipt];
         Sumw4w4p[CentBin][ipt]+=w4*w4p[ipt]; Sumw4w4pA4A4p[CentBin][ipt]+=w4*w4p[ipt]*AziCorr24*AziCorr24p[ipt];
         Sumw2pw4p[CentBin][ipt]+=w2p[ipt]*w4p[ipt]; Sumw2pw4pA2pA4p[CentBin][ipt]+=w2p[ipt]*w4p[ipt]*AziCorr22p[ipt]*AziCorr24p[ipt];
        }
       }

       Nevt[CentBin]++;

      } //loop over Nh>3
     //for(ipt=0;ipt<NPtBin;ipt++) meanPt[CentBin][ipt]=meanPt[CentBin][ipt]+ptm[ipt];
     //if(CentBin==0) cout<<"###, CentBin="<<CentBin<<", Nh="<<Nh<<",  meanPt before deviding <Mp>="<<meanPt[0][0]<<", mptmp[0][0]="<<mptmp[0][0]<<",  SumMultp="<<SumMultp[0][0]<<",  ptm[0]="<<ptm[0]<<endl;

   }// loop over cent cuts;
  } //vz cut

/*
      for(nct=0; nct<NCentBin; nct++){
       if(Nevt[nct]>0){
       AveAziCorr22[nct]=Sumw2A2[nct]/Sumw2[nct];
       AveAziCorr24[nct]=Sumw4A4[nct]/Sumw4[nct];
       AveAziCorr22sq[nct]=Sumw2A2sq[nct]/Sumw2[nct];
       AveAziCorr24sq[nct]=Sumw4A4sq[nct]/Sumw4[nct];
       for(ipt=0;ipt<NPtBin;ipt++){
        if(Sumw4p[nct][ipt]>0){
         meanPt[nct][ipt]=mptmp[nct][ipt]/SumMultp[nct][ipt];
         ///meanPt[nct][ipt]=meanPt[nct][ipt]/SumMultp[nct][ipt];
         AveAziCorr22p[nct][ipt]=Sumw2A2p[nct][ipt]/Sumw2p[nct][ipt];
         AveAziCorr24p[nct][ipt]=Sumw4A4p[nct][ipt]/Sumw4p[nct][ipt];
         //cout<<"AveAziCorr22p= "<<AveAziCorr22p[nct][ipt]<<", Sumw2p="<<Sumw2p[nct][ipt]<<endl;
         //diff error
         AveAziCorr22psq[nct][ipt]=Sumw2pA2psq[nct][ipt]/Sumw2p[nct][ipt];
         AveAziCorr24psq[nct][ipt]=Sumw4pA4psq[nct][ipt]/Sumw4p[nct][ipt];
        }
       else{
         meanPt[nct][ipt]=0.0;
         AveAziCorr22p[nct][ipt]=0.0;
         AveAziCorr24p[nct][ipt]=0.0;
         //diff error
         AveAziCorr22psq[nct][ipt]=0.0;
         AveAziCorr24psq[nct][ipt]=0.0;
        }
       }

      }
      }
*/

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
HighM185220Ana::beginJob()
{
   if ((outRef=fopen("Ref.txt","w")) == NULL)  printf("\n ERROR: Can't open Ref.txt\n\n");
   if ((outDiff=fopen("Diff.txt","w")) == NULL)  printf("\n ERROR: Can't open Diff.txt\n\n");

   for(nct=0; nct<NCentBin; nct++){
    Nevt[nct]=0;
    SumMult[nct]=0;
    Sumw2[nct]=0; Sumw4[nct]=0; Sumw2w4[nct]=0;
    //Sumw6[nct]=0; Sumw8[nct]=0;
    Sumw2sq[nct]=0; Sumw4sq[nct]=0;
    Sumw2A2[nct]=0; Sumw4A4[nct]=0;  
    //Sumw6A6[nct]=0; Sumw8A8[nct]=0;
    Sumw2A2sq[nct]=0; Sumw4A4sq[nct]=0;
    Sumw2w4A2A4[nct]=0;
    
    for(ipt=0; ipt<NPtBin; ipt++){
     SumMultp[nct][ipt]=0;
     Evtp[nct][ipt]=0;
     meanPt[nct][ipt]=0; 
     Sumw2p[nct][ipt]=0; Sumw4p[nct][ipt]=0;
     Sumw2A2p[nct][ipt]=0; Sumw4A4p[nct][ipt]=0;
     Sumw2psq[nct][ipt]=0; Sumw2pA2psq[nct][ipt]=0;
     Sumw2w2p[nct][ipt]=0; Sumw2w2pA2A2p[nct][ipt]=0;
     Sumw4psq[nct][ipt]=0; Sumw4pA4psq[nct][ipt]=0;
     Sumw2w4p[nct][ipt]=0; Sumw2w4pA2A4p[nct][ipt]=0;
     Sumw4w2p[nct][ipt]=0; Sumw4w2pA4A2p[nct][ipt]=0;
     Sumw4w4p[nct][ipt]=0; Sumw4w4pA4A4p[nct][ipt]=0;
     Sumw2pw4p[nct][ipt]=0; Sumw2pw4pA2pA4p[nct][ipt]=0;
mptmp[nct][ipt]=0;
     }
    }

  TH1D::SetDefaultSumw2();
  hMult = fs->make<TH1D>("mult",";N",1000,0,2000);
  hvz = fs->make<TH1D>("vz",";N",200,-30,30);
  hvx = fs->make<TH1D>("vx",";N",200,-10,10);
  hvy = fs->make<TH1D>("vy",";N",200,-10,10);
  hpt = fs->make<TH1D>("pt",";Tracks",200,0,50);
  heta = fs->make<TH1D>("eta",";Tracks",200,-4,4);
  hphi = fs->make<TH1D>("phi",";Tracks",200,-4,4);

NtrkBinHist_ = fs->make<TH1D>("ntrkbinhist","NTrackOffline Bin Distribution", 10, 0., 10.);
centHist_ = fs->make<TH1D>("centhist","NTrackOffline Bin Distribution", 100, 0., 100.);
trkHist_ = fs->make<TH1D>("trkhist","NTrackOffline Distribution", 800, 0., 800.);
trkHistFull_ = fs->make<TH1D>("trkhistfull","NTrackOffline Distribution", 800, 0., 800.);
NtrkBinHist_->Sumw2();
centHist_->Sumw2();
trkHist_->Sumw2();
trkHistFull_->Sumw2();

hMult->Sumw2();
hvz->Sumw2();
hvx->Sumw2();
hvy->Sumw2();
hpt->Sumw2();
heta->Sumw2();
hphi->Sumw2();

 char hname[NtrkBin][200]={"cent_in_350_50000","cent_in_290_350","cent_in_260_290","cent_in_240_260",
// "cent_in_220_240","cent_in_185_220","cent_in_150_185","cent_in_120_150",
// "cent_in_100_120","cent_in_80_100","cent_in_60_80","cent_in_50_60",
// "cent_in_40_50","cent_in_30_40","cent_in_20_30","cent_in_10_20",
"cent_in_0_10"};
 //char hname[NtrkBin][200]={"cent_in_0_inf"}; 
 for(int hist=0;hist<NtrkBin;hist++){
  CentMult[hist] = fs->make<TH1D>(hname[hist],hname[hist], 500, 0., 500.);   
  CentMult[hist]->Sumw2();
 }

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HighM185220Ana::endJob() 
{

      for(nct=0; nct<NCentBin; nct++){
       if(Nevt[nct]>0){
       AveAziCorr22[nct]=Sumw2A2[nct]/Sumw2[nct];
       AveAziCorr24[nct]=Sumw4A4[nct]/Sumw4[nct];
       AveAziCorr22sq[nct]=Sumw2A2sq[nct]/Sumw2[nct];
       AveAziCorr24sq[nct]=Sumw4A4sq[nct]/Sumw4[nct];
       for(ipt=0;ipt<NPtBin;ipt++){
        if(Sumw4p[nct][ipt]>0){
         meanPt[nct][ipt]=mptmp[nct][ipt]/SumMultp[nct][ipt];
         ///meanPt[nct][ipt]=meanPt[nct][ipt]/SumMultp[nct][ipt];
         AveAziCorr22p[nct][ipt]=Sumw2A2p[nct][ipt]/Sumw2p[nct][ipt];
         AveAziCorr24p[nct][ipt]=Sumw4A4p[nct][ipt]/Sumw4p[nct][ipt];
         //cout<<"AveAziCorr22p= "<<AveAziCorr22p[nct][ipt]<<", Sumw2p="<<Sumw2p[nct][ipt]<<endl;
         //diff error
         AveAziCorr22psq[nct][ipt]=Sumw2pA2psq[nct][ipt]/Sumw2p[nct][ipt];
         AveAziCorr24psq[nct][ipt]=Sumw4pA4psq[nct][ipt]/Sumw4p[nct][ipt];
        }
       else{
         meanPt[nct][ipt]=0.0;
         AveAziCorr22p[nct][ipt]=0.0;
         AveAziCorr24p[nct][ipt]=0.0;
         //diff error
         AveAziCorr22psq[nct][ipt]=0.0;
         AveAziCorr24psq[nct][ipt]=0.0;
        }
       }

      }
      }


      for(nct=0; nct<NCentBin; nct++){
       if(Nevt[nct]>0) SumMult[nct]=SumMult[nct]/Nevt[nct];
       else SumMult[nct]=0;
//cout<<"nct="<<nct<<",  Sumw2[nct]="<<Sumw2[nct]<<", Sumw4[nct]="<<Sumw4[nct]<<endl;
       //fprintf(outRef,"%16.li   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g\n", Nevt[nct], SumMult[nct], AveAziCorr22[nct], Sumw2[nct], AveAziCorr24[nct], Sumw4[nct]);
       fprintf(outRef,"%16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g\n", Nevt[nct]*1.0, SumMult[nct], AveAziCorr22[nct], Sumw2[nct], AveAziCorr24[nct], Sumw4[nct]);
       fprintf(outRef,"%16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g\n", Sumw2sq[nct], Sumw4sq[nct], Sumw2w4[nct], Sumw2w4A2A4[nct], AveAziCorr22sq[nct], AveAziCorr24sq[nct]);
       for(ipt=0;ipt<NPtBin;ipt++){
//cout<<"meanPt[nct][ipt]="<<meanPt[nct][ipt]<<",  SumMultp[nct][ipt]="<<SumMultp[nct][ipt]<<endl;
         fprintf(outDiff,"%16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g\n", meanPt[nct][ipt], SumMultp[nct][ipt], AveAziCorr22p[nct][ipt], Sumw2p[nct][ipt], AveAziCorr24p[nct][ipt], Sumw4p[nct][ipt], Sumw2psq[nct][ipt], AveAziCorr22psq[nct][ipt], Sumw4psq[nct][ipt], AveAziCorr24psq[nct][ipt]);
         fprintf(outDiff,"%16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g   %16.10g\n", Sumw2w2p[nct][ipt], Sumw2w2pA2A2p[nct][ipt], Sumw2w4p[nct][ipt], Sumw2w4pA2A4p[nct][ipt], Sumw4w2p[nct][ipt], Sumw4w2pA4A2p[nct][ipt], Sumw4w4p[nct][ipt], Sumw4w4pA4A4p[nct][ipt], Sumw2pw4p[nct][ipt], Sumw2pw4pA2pA4p[nct][ipt]);
       }
      }

}

// ------------ method called when starting to processes a run  ------------
void 
HighM185220Ana::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
HighM185220Ana::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HighM185220Ana::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HighM185220Ana::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HighM185220Ana::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HighM185220Ana);
