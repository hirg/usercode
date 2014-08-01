// -*- C++ -*-
//
// Package:    TrackOfflineExample
// Class:      TrackOfflineExample
// 
/**\class TrackOfflineExample TrackOfflineExample.cc TrackOffline/TrackOfflineExample/src/TrackOfflineExample.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Fri Aug  1 10:04:22 CDT 2014
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

#include <TH1D.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"
//const int NtrkBin=4;
//const int binboundaries[NtrkBin+1]={10000,110,90,35,0};

//
// class declaration
//

class TrackOfflineExample : public edm::EDAnalyzer {
   public:
      explicit TrackOfflineExample(const edm::ParameterSet&);
      ~TrackOfflineExample();

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
TH1D *trkHist;
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
TrackOfflineExample::TrackOfflineExample(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
edm::Service<TFileService> fs;
trkHist = fs->make<TH1D>("ntrkhist","Ntrkoffline Distribution", 300, 0., 300.);
}


TrackOfflineExample::~TrackOfflineExample()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TrackOfflineExample::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   edm::Handle<reco::Centrality> centrality;
   centProvider = 0;
   iEvent.getByLabel("pACentrality",centrality);
   if (!centProvider) centProvider = new CentralityProvider(iSetup);
   centProvider->newEvent(iEvent,iSetup);
   //int bin= centrality_->getBin();
   trkHist->Fill(centrality->Ntracks());


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
TrackOfflineExample::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TrackOfflineExample::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TrackOfflineExample::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TrackOfflineExample::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TrackOfflineExample::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TrackOfflineExample::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TrackOfflineExample::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackOfflineExample);
