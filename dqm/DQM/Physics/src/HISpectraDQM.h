#ifndef HISpectraDQM_H
#define HISpectraDQM_H


/** \class HISpectraDQM
 *
 *  DQM Physics Module for Heavy Ion Flow group
 *
 *  Based on DQM/SiPixel and DQM/Physics code
 *  Version 1.0, 7/7/10
 *  By Shengquan Tuo
 */


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"


class DQMStore;
class MonitorElement;


class HISpectraDQM : public edm::EDAnalyzer {
 public:

  /// Constructor
  HISpectraDQM(const edm::ParameterSet&);
  
  /// Destructor
  virtual ~HISpectraDQM();
  
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
