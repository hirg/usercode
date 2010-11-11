#ifndef HICentralityDQM_H
#define HICentralityDQM_H


/** \class HICentralityDQM
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


class HICentralityDQM : public edm::EDAnalyzer {
 public:

  /// Constructor
  HICentralityDQM(const edm::ParameterSet&);
  
  /// Destructor
  virtual ~HICentralityDQM();
  
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
