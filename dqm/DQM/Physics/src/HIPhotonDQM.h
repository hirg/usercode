#ifndef HIPhotonDQM_H
#define HIPhotonDQM_H


/** \class HIPhotonDQM
 *
 *  DQM Physics Module for Heavy Ion Centrality group
 *
 *  Based on DQM/SiPixel and DQM/Physics code
 *  Version 1.0, 7/7/10
 *  By Shengquan Tuo
 */


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"


class DQMStore;
class MonitorElement;


class HIPhotonDQM : public edm::EDAnalyzer {
 public:

  /// Constructor
  HIPhotonDQM(const edm::ParameterSet&);
  
  /// Destructor
  virtual ~HIPhotonDQM();
  
  /// Inizialize parameters for histo binning
  void beginJob();

  /// Get the analysis
  void analyze(const edm::Event&, const edm::EventSetup&);

  void endJob(void);


 private:




  // ----------member data ---------------------------


  DQMStore* theDbe; 

  //input tags for Cent
  //edm::InputTag centLabel_;

  //map of MEs
  std::map<std::string, MonitorElement*> MEcontainer_;


};
#endif  
