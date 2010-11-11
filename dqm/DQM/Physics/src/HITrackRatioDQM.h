#ifndef HITrackRatioDQM_H
#define HITrackRatioDQM_H


/** \class HITrackRatioDQM
 *
 *  DQM Physics Module for Event Selection
 *
 *  Based on DQM/SiPixel and DQM/Physics code
 *  Version 1.0, 7/19/10
 *  By Shengquan Tuo
 */


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include <string>
#include <fstream>


//class DQMStore;
//class MonitorElement;


class HITrackRatioDQM : public edm::EDAnalyzer {
 public:

  /// Constructor
  HITrackRatioDQM(const edm::ParameterSet&);
  
  /// Destructor
  virtual ~HITrackRatioDQM();
  
  /// Inizialize parameters for histo binning
  void beginJob();

  /// Get the analysis
  void analyze(const edm::Event&, const edm::EventSetup&);

  void endJob(void);


 private:




  // ----------member data ---------------------------


  DQMStore* theDbe; 
  //DQMStore* dbe_;

  //input tags for Cent
  //edm::InputTag centLabel_;

  //map of MEs
  //MonitorElement * testResults; 
  //std::map<std::string, MonitorElement*> MEcontainer_;
  //std::map<TString, MonitorElement*> hs;
  std::map<TString, MonitorElement*> MEcontainer_;


};
#endif  
