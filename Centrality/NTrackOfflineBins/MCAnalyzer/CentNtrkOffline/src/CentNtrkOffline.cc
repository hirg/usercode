// -*- C++ -*-
//
// Package:    CentNtrkOffline
// Class:      CentNtrkOffline
// 
/**\class CentNtrkOffline CentNtrkOffline.cc Analyzer/CentNtrkOffline/src/CentNtrkOffline.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tuo Shengquan
//         Created:  Thu Jan 10 18:31:22 EST 2013
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


#include <TH1.h> 
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

const int NtrkBin=4;
const int binboundaries[NtrkBin+1]={10000,110,90,35,0};
//
// class declaration
//

class CentNtrkOffline : public edm::EDAnalyzer {
   public:
      explicit CentNtrkOffline(const edm::ParameterSet&);
      ~CentNtrkOffline();

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
TH1F * centHist_;
TH1F * trkHist_;
CentralityProvider * centProvider; 

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
CentNtrkOffline::CentNtrkOffline(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

edm::Service<TFileService> fs;

centHist_ = fs->make<TH1F>("centhist","Centrality Distribution", 4, 0., 4.);
trkHist_ = fs->make<TH1F>("trkhist","NTrackOffline Distribution", 300, 0., 300.);

}


CentNtrkOffline::~CentNtrkOffline()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CentNtrkOffline::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
//   using namespace std;
//   using namespace reco;

   edm::Handle<reco::Centrality> centrality;
   centProvider = 0;
   iEvent.getByLabel("pACentrality",centrality);
   if (!centProvider) centProvider = new CentralityProvider(iSetup);
   //make supre you do this first in every event
   centProvider->newEvent(iEvent,iSetup);
   //hiBin = centProvider->getBin();
   //hiNtracks = centrality->Ntracks();
   int bin=-1;
   for(int i=0;i<NtrkBin;i++) 
      if(centrality->Ntracks()<binboundaries[i]&&centrality->Ntracks()>=binboundaries[i+1])
        bin=i;

   centHist_->Fill(bin);
   trkHist_->Fill(centrality->Ntracks());  
//   cout<<"hiNtracks="<<centrality->Ntracks()<<"  ,bin="<<bin<<endl;
  

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
CentNtrkOffline::beginJob()
{

centHist_->Sumw2(); 
trkHist_->Sumw2();

}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentNtrkOffline::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
CentNtrkOffline::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
CentNtrkOffline::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
CentNtrkOffline::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
CentNtrkOffline::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CentNtrkOffline::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentNtrkOffline);
