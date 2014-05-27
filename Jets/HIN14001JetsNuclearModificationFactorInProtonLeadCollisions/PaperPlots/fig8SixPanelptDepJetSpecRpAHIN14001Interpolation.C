#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include <TF1.h>
#include <TMath.h>
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TCut.h"
#include <TMath.h>
#include <TSystem.h>
#include "THStack.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include <iostream>
#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <iomanip>
using namespace std;

bool SavePlot = kTRUE ;
const bool SaveFile = kFALSE ;
const bool IsMC = kFALSE ;
const bool DoWideBinCorr=kFALSE;
const bool UsePYTHIARef=kFALSE ;
const bool UseFit=kTRUE ;
const bool DoIDCut=kFALSE ;

//const Double_t jetPtBin[]={3, 4, 5, 7, 9, 12, 15, 18, 22, 27, 33, 39, 47, 55, 64,74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 429, 692, 1000};
const Double_t jetPtBin[]={3, 4, 5, 7, 9, 12, 15, 18,21,24,28,32,37,43,49,56,64,74,84,97,114,133,153,174,196,220,245,272,300,330,362,395,430,468,507,548,592,638,686,1000};
const int nJetPtBin = sizeof(jetPtBin)/sizeof(Double_t)-1 ;

//const double deta[]={-2.2, -1.2, -0.7, -0.3, 0.3, 0.7,1.2,2.2} ;
const double deta[]={-2.0, -1.5, -1.0, -0.5, 0.5, 1.0,1.5,2.0} ;
//const double deta[]={-1.0, 1.0} ;
const int netabin = sizeof(deta)/sizeof(Double_t)-1 ;
const double ptmin = 50. ;
const double ptmax = 700.; ;
const double ptboundary[]={270., 350., 400., 600., 400., 350., 270., 600.};

static const int nColor = 8;
static const int colorCode[nColor] = {
//    1,2,4,1,4,2,1,1    //for spectra and Asy
 //   2, 4, 6, 7, 8, 9, 46,1
//    2, 4, 6, 1, 8, 9, 4,1
    //4, 9, 8, 1, 6, 4, 2,1 //RpA
    //4, 9, 8, 3, 6, 4, 2,3 //RpA
    4, 9, 8, 2, 6, 4, 1,2 //RpA
//    2, 7, 6, 1, 8, 4, 46,1  //for Forward-backward asymmetery
};
static const int markerCode[nColor] = {
 //  34,29,20,25,27,28,30,20
 //   29,34,33,25,27,28,30,20
 //   20,34,33,25,27,28,30,20
 //   33, 34, 29, 20, 30, 28,27,20   //for Forward-backward Asymmetry
    27, 28, 30, 20, 29, 34,33,20 //RpA
};

const int sigma = 70 ; // units in minibarn
const double Ncoll = 6.9 ;
const double pPbSigma = 2.061 ; // units in barn
const double A = 208 ;
const double pPbLumi = 20.7 ; //excluded the old alignment run for pPb
const double PbpLumi = 14.0 ; //excluded the old alignment run for pPb
const double frac = 0.85 ;
enum Display_t {kSpecPP, kSpecPb, kRpA, kAsy, kEtaDep, kCompATLAS, kRpAEtaDep, kAsyEtaDep} ;
enum Level_t {kMeas, kUnfold} ;
enum DataSet_t{kPPb, kPbP, kAll};
//void JetSpecRpAHIN14001Interpolation(Display_t dis = kRpAEtaDep, Level_t lev = kUnfold, DataSet_t data=kAll)
void fig8SixPanelptDepJetSpecRpAHIN14001Interpolation(Display_t dis = kRpA, Level_t lev = kUnfold, DataSet_t data=kAll)
{
    TH1::SetDefaultSumw2();
    gStyle->SetErrorX(0.0001);
    
    TString algo ="akPu3PF"; //"AkPu3PF" ;
    TString residual = ""; //"NoResidual" ;
    TString coll;
    if(data==kPPb) coll = "PPb" ; // or "PbP" ;
    else if(data==kPbP) coll = "PbP" ;
    else coll = "pA" ;
    TString class = "HFsumEta4Bin1" ;// "HF90Cent" ; // "" for inclusive ;
    TString effTab = "TrkEffHIN12017v5TrkCorr2DCut" ;  //"HistIterTrkCorrtestFilterCut"; //  "Trk" ; "HistIterTrkCorrtest" ;
    double Lumi ;
    if(data==kPPb) Lumi = pPbLumi ;
    else if(data==kPbP) Lumi = PbpLumi ;
    else Lumi = 35.0 ;
    TString dep  ;
    TString val ;
    if(lev==kUnfold) val = "Unfolded";
    else val = "Measured";
    if(dis==kSpecPb) dep = "SpectPA";
    else if(dis==kSpecPP)dep = "SpectPP";
    else if(dis==kEtaDep)dep = "FMSpectRatio";
    else if(dis==kRpA)dep = "RpAvsPt";
    else if(dis==kRpAEtaDep)dep = "RpAvsEta";
    else if(dis==kCompATLAS)dep = "ALICEComp";
    else if(dis==kAsyEtaDep)dep = "AsyvsEta";
    else dep ="Asymmetry" ;
    
    TString ana ;
    if(DoIDCut) ana="JetIDCut";
    else ana="";
    TString widebin;
    if(DoWideBinCorr) widebin ="WideBinCorr";
    else widebin="" ;
    
    const int N = netabin ;
    //TString plotsdir = "/Users/ymao/group/CMS/plots/pA/JetRpA/HIN-14-001";
    TString plotsdir = "/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/plots";
        //const char * kHomeDir = "/Users/ymao/group/CMS/anaOutputs/pPb/RpPb" ;
        const char * kHomeDir = "/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log" ;

    if(UsePYTHIARef){
    
    char *ppsubdir[N+1]={"ak3GenJetSpectrum_QCD10001_15_20", "ak3GenJetSpectrum_QCD10001_10_15", "ak3GenJetSpectrum_QCD10001_05_10", "ak3GenJetSpectrum_QCD10001_00_05", "ak3GenJetSpectrum_QCD10001_05_10", "ak3GenJetSpectrum_QCD10001_10_15", "ak3GenJetSpectrum_QCD10001_15_20", "ak3GenJetSpectrum_QCD10001_00_05"};
    }
    else {

    char *ppsubdir[N+1] = {"Interpolated5TeVak3PFJetAbsRapidity15_20",
        "Interpolated5TeVak3PFJetAbsRapidity10_15",
        "Interpolated5TeVak3PFJetAbsRapidity5_10",
        "Interpolated5TeVak3PFJetAbsRapidity0_5", "Interpolated5TeVak3PFJetAbsRapidity5_10", "Interpolated5TeVak3PFJetAbsRapidity10_15", "Interpolated5TeVak3PFJetAbsRapidity15_20", "Interpolated5TeVak3PFJetAbsRapidity0_5"};
    }
    
    double scalepower[N+1]={3, 2, 1, 0, -1, -2, -3, 0 };
    double scalef[N+1];
    
    const int nptpoint[]={28, 31, 32, 33, 32, 31, 28, 33};
    
    const double ptboundary[]={270., 350., 400., 460., 400., 350., 270., 460.};

    for(int j=0; j<=netabin; j++) scalef[j]=pow(4.0, scalepower[j]);
    
    TFile * f1[N+1];
    TFile * f2[N+1];
    TFile * file;
    TFile * reffile;
    TFile * fcorr;
    
    TH1F * jet1[N+1];
    TH1F * jet2[N+1];
    TH1F * jet[N+1];
    
    TH1F * ppjet1[N+1];
    TH1F * ppjet2[N+1];
    TH1F * ppjet[N+1];
    
    TH1F * ppbcorr[N+1];
    TH1F * ppcorr[N+1];
    
    TH1F * rebinjet1[N+1];
    TH1F * rebinjet2[N+1];
    TH1F * rebinjet[N+1];
    
    TH1F * rebinppjet[N+1];
    
    TH1F * scaledjet1[N+1];
    TH1F * scaledjet2[N+1];
    TH1F * scaledjet[N+1];
    
    TH1F * scaledppjet[N+1];
    TH1F * PARatio[N+1];
    TH1F * FBRatio[N];
    TH1F * FMRatio[N];
    TH1F * PARatioRpA[N+1];
    
    TF1 * ftrue = new TF1("ftrue", "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/4000.,[3])", 30, 800) ;
    double fitpar[N+1][5]={  //these parameters are when using 4000 in the function
        {19498.8, -18.2422, -4.87197, 5.33697, -2.23802}, //-2.0 - -1.5
        {212474, -42.167, -5.3189, 4.72771, -1.88974}, //-1.5 - -1.0
        {246345, -45.0343, -5.32513, 7.52221, -1.25485}, //-1.0 - -0.5
        {281440, -47.3063, -5.34283, 6.97004, -1.20499},  //-0.5 - 0.5
        {246345, -45.0343, -5.32513, 7.52221, -1.25485},  //0.5 - 1.0
        {212474, -42.167, -5.3189, 4.72771, -1.88974},  //1.0 - 1.5
        {19498.8, -18.2422, -4.87197, 5.33697, -2.23802},  //1.5 - 2.0
        {281440, -47.3063, -5.34283, 6.97004, -1.20499}};
//    TF1 * ftrue = new TF1("ftrue", "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/3500.,[3])", 30, 800) ;
//    double fitpar[N+1][5]={  //these parameters are when using 3500 in the function
//        {18607.9, -17.7766, -4.86191, 5.4041, -2.09498}, //-2.0 - -1.5
//        {208330, -41.9575, -5.31473, 4.77265, -1.74351}, //-1.5 - -1.0
//        {246351, -45.0347, -5.32513, 7.52254, -1.09294}, //-1.0 - -0.5
//        {286101, -47.4919, -5.34629, 6.8595, -1.05411},  //-0.5 - 0.5
//        {246351, -45.0347, -5.32513, 7.52254, -1.09294},  //0.5 - 1.0
//        {208330, -41.9575, -5.31473, 4.77265, -1.74351},  //1.0 - 1.5
//        {18607.9, -17.7766, -4.86191, 5.4041, -2.09498},  //1.5 - 2.0
//        {286101, -47.4919, -5.34629, 6.8595, -1.05411}};
  
    double ptCen[N+1][100], sys[N+1][100], ppsys[N+1][100];
    double ptCenShift[N+1][100];
    ifstream infile;
    
    std::string inname ;
    for(int ieta = 0 ; ieta <=netabin; ieta++){
        if(ieta==netabin){
            if(dis==kSpecPb || dis==kRpA || dis==kRpAEtaDep)
                //inname = Form("/Users/ymao/group/CMS/Sys/HIN-14-001/sysSpectrumTotalEtaBin%.f_%.f.txt", -1.0*10, 1.0*10);
                inname = Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/sys/sysSpectrumTotalEtaBin%.f_%.f.txt", -1.0*10, 1.0*10);
            else
               //inname =Form("/Users/ymao/group/CMS/Sys/HIN-14-001/sysAsymmetetryTotalEtaBin%.f_%.f.txt",-1.0*10, 1.0*10);
               inname =Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/sys/sysAsymmetetryTotalEtaBin%.f_%.f.txt",-1.0*10, 1.0*10);
        }
        else {
            if(dis==kSpecPb || dis==kRpA || dis==kRpAEtaDep)
                //inname = Form("/Users/ymao/group/CMS/Sys/HIN-14-001/sysSpectrumTotalEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
                inname = Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/sys/sysSpectrumTotalEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
            else
                //inname =Form("/Users/ymao/group/CMS/Sys/HIN-14-001/sysAsymmetetryTotalEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
                inname =Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/sys/sysAsymmetetryTotalEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
        }
        infile.open(inname.c_str());
        //   infile.open("JESsystematic.txt");
        std::string line;
        int ifile = 0;
        int np=0;
        double v1, v2;

        while(std::getline(infile,line,'\n'))
        {
            int res = sscanf(line.c_str(),"%lg %lg",&v1,&v2);
            if (res!=2) continue;
            ptCen[ieta][np]=v1;
            if(dis==kAsy || dis==kAsyEtaDep)  sys[ieta][np]=v2;
            else
                sys[ieta][np]=v2;
            //      sys[np]=v2*TMath::Sqrt(2);
            cout <<" np = " <<np << " : pt =" <<ptCen[ieta][np] << " : sys=" <<sys[ieta][np]<<endl;
            if(ptCen[ieta][np]<ptmin) sys[ieta][np]= 0.;
            if(ptCen[ieta][np]>ptboundary[ieta]) sys[ieta][np]= 0.;

            //if(ieta==6) ptCen[ieta][np]=ptCen[ieta][np]*0.95;
            //if(ieta==0) ptCen[ieta][np]=ptCen[ieta][np]*1.05;

            np++;
        }
        infile.close();
    }
    
    //for pp reference systematics
    std::string innamepp ;
    for(int ieta = 0 ; ieta <=netabin; ieta++){
        if(ieta==netabin){
            //    if(dis==kSpecPb || dis==kAsy || dis==kAsyEtaDep)
            //innamepp = Form("/Users/ymao/group/CMS/Sys/HIN-14-001/ppReferenceFrom7TeVR5SysEtaBin%.f_%.f.txt", -1.0*10, 1.0*10);
            //innamepp = Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/pp/ppReferenceFrom7TeVR5SysEtaBin%.f_%.f.txt", -1.0*10, 1.0*10);
            innamepp = Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/pp/ppRefSysTotalEtaBin%.f_%.f.txt", -1.0*10, 1.0*10);
            //            else
            //                inname =Form("/Users/ymao/group/CMS/Sys/HIN-14-001/sysRpATotalEtaBin%.f_%.f.txt",-1.0*10, 1.0*10);
        }
        else {
            //           if(dis==kSpecPb || dis==kAsy)
            //innamepp = Form("/Users/ymao/group/CMS/Sys/HIN-14-001/ppReferenceFrom7TeVR5SysEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
            //innamepp = Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/pp/ppReferenceFrom7TeVR5SysEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
            innamepp = Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/pp/ppRefSysTotalEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
            //            else
            //                inname =Form("/Users/ymao/group/CMS/Sys/HIN-14-001/sysRpATotalEtaBin%.f_%.f.txt",deta[ieta]*10, deta[ieta+1]*10);
        }
        infile.open(innamepp.c_str());
        //   infile.open("JESsystematic.txt");
        std::string line;
        int ifile = 0;
        int np=0;
        double v1, v2;
        
        while(std::getline(infile,line,'\n'))
        {
            int res = sscanf(line.c_str(),"%lg %lg",&v1,&v2);
            if (res!=2) continue;
            ptCen[ieta][np]=v1;
            ppsys[ieta][np]=v2;
            //      sys[np]=v2*TMath::Sqrt(2);
            cout <<" npp = " <<np << " : pt =" <<ptCen[ieta][np] << " : sys=" <<ppsys[ieta][np]<<endl;
            if(ptCen[ieta][np]<ptmin) ppsys[ieta][np]= -1.e99;
            if(ptCen[ieta][np]>ptboundary[ieta]) ppsys[ieta][np]= -1.e99;

            ptCenShift[ieta][np]=ptCen[ieta][np];
            if(ieta==6) ptCenShift[ieta][np]=ptCenShift[ieta][np]*0.9;
            if(ieta==0) ptCenShift[ieta][np]=ptCenShift[ieta][np]*1.1;
            //cout<<"ieta= "<<ieta <<",  npq = " <<np << " : pt =" <<ptCenShift[ieta][np] << " : sys=" <<ppsys[ieta][np]<<endl;

            np++;
        }
        infile.close();
    }
    
    //fcorr = TFile::Open("/Users/ymao/group/CMS/anaOutputs/pPb/RpPb/QCD10011Binning/correctionfactor.root", "readonly");
    fcorr = TFile::Open("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/QCD10011Binning/correctionfactor.root", "readonly");
    
    if(UsePYTHIARef){
        reffile = new TFile(Form("/Users/ymao/group/CMS/anaOutputs/pPb/RpPb/AnaGENJetR357_5020GeV_Apr15_Z2Combined.root"));

    }
    else
        //reffile = new TFile(Form("/Users/ymao/group/CMS/macros/ppRef/7TeV_PRL107_132001/R3_ScaleFactor7TeVto5TeVStartingCone5Sys.root"));
        reffile = new TFile(Form("/Users/tuos/Analysis/CMS/eps09/jetpp/hplot9May17log/pp/R3_ScaleFactor7TeVto5TeVStartingCone5Sys-2.root"));
    
    TGraphErrors * jet5TeVR5[N];
    double x[N+1][100],y[N+1][100];

    for(int ieta = 0 ; ieta <=netabin; ieta++){
        
        if(UsePYTHIARef){
            ppjet[ieta] = (TH1F*)reffile->Get(Form("%s/JetSpectrum", ppsubdir[ieta]));
        }
        else {
            jet5TeVR5[ieta] = (TGraphErrors*)reffile->Get(Form("%s", ppsubdir[ieta]));
            cout <<"nptpoint = " << nptpoint[ieta] <<endl ;
            for(int j = 0 ; j < nptpoint[ieta]; j++) {
                jet5TeVR5[ieta]->GetPoint(j, x[ieta][j], y[ieta][j]);
                cout << "x[np] = " << x[ieta][j] << "y[np] = " << y[ieta][j]  <<endl ;
                
            }
        }
        ftrue->SetParameters(fitpar[ieta]);
        
   //     cout << "  0 " <<fitpar[ieta][0] << "  1 " <<fitpar[ieta][1] << "  2 " <<fitpar[ieta][2] << "  3 " <<fitpar[ieta][3] << "  4 " <<fitpar[ieta][4]  <<endl ;
        
        if(ieta==netabin){
            if(IsMC){
                f1[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PPb_UnfoPriorGen_%sKurtMCQiaoIDCut_MC_jtpt20_EtaBin%.f_%.f_Inc_v7.root", kHomeDir, algo.Data(),  -1.0*10, 1.0*10), "readonly");
                f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PbP_UnfoPriorGen_%sKurtMCQiaoIDCut_MC_jtpt20_EtaBin%.f_%.f_Inc_v7.root", kHomeDir, algo.Data(),  -1.0*10, 1.0*10), "readonly");
            }
            else{
                if(DoIDCut){
            f1[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PPb_UnfoPriorGen_%sKurtForestEtaWeightQiaoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v12.root", kHomeDir, algo.Data(),  -1.0*10, 1.0*10), "readonly");
            f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PbP_UnfoPriorGen_%sKurtForestEtaWeightQiaoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v12.root", kHomeDir, algo.Data(),  -1.0*10, 1.0*10), "readonly");
                }
                else {
                    f1[ieta] = TFile::Open(Form("%s/QCD10011Binning/NoJetIDCut/PPb_UnfoPriorGen_%sKurtForestEtaWeightNoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v13.root", kHomeDir, algo.Data(),  -1.0*10, 1.0*10), "readonly");
                    //f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/NoJetIDCut/PbP_UnfoPriorGen_%sKurtForestEtaWeightNoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v13.root", kHomeDir, algo.Data(),  -1.0*10, 1.0*10), "readonly");
                    f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/NoJetIDCut/PbP_UnfoPriorGen_%sKurtForestJetPtEtaWeightNoIDCutJECv17_jtpt20_EtaBin%.f_%.f_Inc_v17.root", kHomeDir, algo.Data(),  -1.0*10, 1.0*10), "readonly");
                }
            }
            ppcorr[ieta] = (TH1F*)fcorr->Get(Form("hcorrpPbEtaBin%.f_%.f",-1.0*10, 1.0*10));
            ppbcorr[ieta] = (TH1F*)fcorr->Get(Form("hcorrpPbEtaBin%.f_%.f",-1.0*10, 1.0*10));
        }  //! for central eta bin |eta| <1
        else {
            if(IsMC){
                f1[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PPb_UnfoPriorGen_%sKurtMCQiaoIDCut_MC_jtpt20_EtaBin%.f_%.f_Inc_v7.root", kHomeDir, algo.Data(),  deta[ieta]*10, deta[ieta+1]*10), "readonly");
                f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PbP_UnfoPriorGen_%sKurtMCQiaoIDCut_MC_jtpt20_EtaBin%.f_%.f_Inc_v7.root", kHomeDir, algo.Data(),  deta[ieta]*10, deta[ieta+1]*10), "readonly");
  
            }
            else{
                if(DoIDCut){
                f1[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PPb_UnfoPriorGen_%sKurtForestEtaWeightQiaoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v12.root", kHomeDir, algo.Data(),  deta[ieta]*10, deta[ieta+1]*10), "readonly");
                f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/QiaoJetIDCut/PbP_UnfoPriorGen_%sKurtForestEtaWeightQiaoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v12.root", kHomeDir, algo.Data(),  deta[ieta]*10, deta[ieta+1]*10), "readonly");
                }
                else{
                    f1[ieta] = TFile::Open(Form("%s/QCD10011Binning/NoJetIDCut/PPb_UnfoPriorGen_%sKurtForestEtaWeightNoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v13.root", kHomeDir, algo.Data(),  deta[ieta]*10, deta[ieta+1]*10), "readonly");
                    //f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/NoJetIDCut/PbP_UnfoPriorGen_%sKurtForestEtaWeightNoIDCut_jtpt20_EtaBin%.f_%.f_Inc_v13.root", kHomeDir, algo.Data(),  deta[ieta]*10, deta[ieta+1]*10), "readonly");
                    f2[ieta] = TFile::Open(Form("%s/QCD10011Binning/NoJetIDCut/PbP_UnfoPriorGen_%sKurtForestJetPtEtaWeightNoIDCutJECv17_jtpt20_EtaBin%.f_%.f_Inc_v17.root", kHomeDir, algo.Data(),  deta[ieta]*10, deta[ieta+1]*10), "readonly");
                }
            }
           
            ppcorr[ieta] = (TH1F*)fcorr->Get(Form("hcorrppEtaBin%.f_%.f",deta[ieta]*10, deta[ieta+1]*10));
            ppbcorr[ieta] = (TH1F*)fcorr->Get(Form("hcorrpPbEtaBin%.f_%.f",deta[ieta]*10, deta[ieta+1]*10));
        }
        
        switch(lev){
            case kMeas:
                jet1[ieta] = (TH1F*)f1[ieta]->Get("hMeas0");
                jet2[ieta] = (TH1F*)f2[ieta]->Get("hMeas0");
                break ;
            case kUnfold:
                if(IsMC){
                    jet1[ieta] = (TH1F*)f1[ieta]->Get("hReco0");
                    jet2[ieta] = (TH1F*)f2[ieta]->Get("hReco0");
                    ppjet1[ieta] = (TH1F*)f1[ieta]->Get("hGen0");
                    ppjet2[ieta] = (TH1F*)f2[ieta]->Get("hGen0");
                }
                else {
                    jet1[ieta] = (TH1F*)f1[ieta]->Get("hReco0");
                    jet2[ieta] = (TH1F*)f2[ieta]->Get("hReco0");
                }
                break ;
        }
        
        if(ieta==netabin){
            rebinjet1[ieta] = (TH1F*)jet1[ieta]->Clone(Form("PPbJetInEtaBin%.f_%.f", -1.0*10, 1.0*10));
            rebinjet2[ieta] = (TH1F*)jet2[ieta]->Clone(Form("PbPJetInEtaBin%.f_%.f", -1.0*10, 1.0*10));
            if(IsMC){
               rebinppjet[ieta] = (TH1F*)ppjet1[ieta]->Clone(Form("MCPPbJetInEtaBin%.f_%.f_Cen0-100%%", -1.0*10, 1.0*10));
                rebinppjet2[ieta] = (TH1F*)ppjet2[ieta]->Clone(Form("MCPbpJetInEtaBin%.f_%.f_Cen0-100%%", -1.0*10, 1.0*10));
//                if(DoWideBinCorr){
//                    for(int ibin = rebinppjet[ieta]->FindBin(50.); ibin <rebinppjet[ieta]->GetNbinsX(); ibin++){
//                        double binCenter = rebinppjet[ieta]->GetBinCenter(ibin);
//                        rebinppjet[ieta]->SetBinContent(ibin, (rebinppjet[ieta]->GetBinContent(ibin)/ppcorr[ieta]->GetBinContent(ppcorr[ieta]->FindBin(binCenter))));
//                    }
//                }
            }
        }
        else {
            rebinjet1[ieta] = (TH1F*)jet1[ieta]->Clone(Form("PPbJetInEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
            rebinjet2[ieta] = (TH1F*)jet2[ieta]->Clone(Form("PbPJetInEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
            if(IsMC){
                rebinppjet[ieta] = (TH1F*)ppjet1[ieta]->Clone(Form("PYTHIAJetInEtaBin%.f_%.f_Cen0-100%%", deta[ieta]*10, deta[ieta+1]*10));
                rebinppjet2[ieta] = (TH1F*)ppjet2[ieta]->Clone(Form("MCPbpJetInEtaBin%.f_%.f_Cen0-100%%", deta[ieta]*10, deta[ieta+1]*10));
//                if(DoWideBinCorr){
//                    for(int ibin = rebinppjet[ieta]->FindBin(50.); ibin <rebinppjet[ieta]->GetNbinsX(); ibin++){
//                        double binCenter = rebinppjet[ieta]->GetBinCenter(ibin);
//                        rebinppjet[ieta]->SetBinContent(ibin, (rebinppjet[ieta]->GetBinContent(ibin)/ppcorr[ieta]->GetBinContent(ppcorr[ieta]->FindBin(binCenter))));
//                    }
//                }
            }
        }
     }
    for(int ieta = 0 ; ieta <=netabin; ieta++){
        if(ieta==netabin){
            switch(data){
                case kPPb:
                    rebinjet[ieta] = (TH1F*)rebinjet1[ieta]->Clone(Form("PAJetInEtaBin%.f_%.f", -1.0*10, 1.0*10));
                    break;
                case kPbP:
                    rebinjet[ieta] = (TH1F*)rebinjet2[ieta]->Clone(Form("PAJetInEtaBin%.f_%.f", -1.0*10, 1.0*10));
                    break;
                case kAll:
                    rebinjet[ieta] = (TH1F*)rebinjet1[ieta]->Clone(Form("PAJetInEtaBin%.f_%.f", -1.0*10, 1.0*10));
                    rebinjet[ieta]->Add(rebinjet2[ieta]);
                    break;
                    
            }
            if(DoWideBinCorr){
                for(int ibin = rebinjet[ieta]->FindBin(45.); ibin <rebinjet[ieta]->GetNbinsX(); ibin++){
                    double binCenter = rebinjet[ieta]->GetBinCenter(ibin);
                    rebinjet[ieta]->SetBinContent(ibin, (rebinjet[ieta]->GetBinContent(ibin)/ppbcorr[ieta]->GetBinContent(ppbcorr[ieta]->FindBin(binCenter))));
                }
            }
            rebinjet[ieta]->Scale(1./(2.));
            for(int ibin = rebinjet[ieta]->FindBin(45.); ibin <rebinjet[ieta]->GetNbinsX(); ibin++){
                double binCenter = rebinjet[ieta]->GetBinCenter(ibin);
                if(binCenter>ptboundary[ieta]) {
                    rebinjet[ieta]->SetBinContent(ibin,0. );
                    rebinjet[ieta]->SetBinError(ibin,0. );
                }
            }
  
        }
        else {
            switch(data){
                case kPPb:
                    rebinjet[ieta] = (TH1F*)rebinjet1[netabin-ieta-1]->Clone(Form("PAJetInEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
                    break;
                case kPbP:
                    rebinjet[ieta] = (TH1F*)rebinjet2[ieta]->Clone(Form("PAJetInEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
                    break;
                case kAll:
                    rebinjet[ieta] = (TH1F*)rebinjet1[netabin-ieta-1]->Clone(Form("PAJetInEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
                    rebinjet[ieta]->Add(rebinjet2[ieta]);
                    break;
            }
            if(DoWideBinCorr){
                for(int ibin = rebinjet[ieta]->FindBin(45.); ibin <rebinjet[ieta]->GetNbinsX(); ibin++){
                    double binCenter = rebinjet[ieta]->GetBinCenter(ibin);
                    rebinjet[ieta]->SetBinContent(ibin, (rebinjet[ieta]->GetBinContent(ibin)/ppbcorr[ieta]->GetBinContent(ppbcorr[ieta]->FindBin(binCenter))));
                }
            }
            rebinjet[ieta]->Scale(1./(deta[ieta+1]-deta[ieta]));
            //  rebinppjet[ieta]->Scale(1./(deta[ieta+1]-deta[ieta]));
        }
        for(int ibin = rebinjet[ieta]->FindBin(45.); ibin <rebinjet[ieta]->GetNbinsX(); ibin++){
            double binCenter = rebinjet[ieta]->GetBinCenter(ibin);
            if(binCenter>ptboundary[ieta]) {
                rebinjet[ieta]->SetBinContent(ibin,-1.e-9 );
                rebinjet[ieta]->SetBinError(ibin,-1.e-9 );
            }
        }
        
        removeZero(rebinjet[ieta]);
        switch(data){
            case kPPb:
                rebinjet[ieta]->Scale(1./(pPbLumi*1.e6*frac));
                break ;
            case kPbP:
                rebinjet[ieta]->Scale(1./(PbpLumi*1.e6*frac));
                break ;
            case kAll:
                rebinjet[ieta]->Scale(1./((pPbLumi+PbpLumi)*1.e6*frac));
                break ;
        }

    }
    
    for(int ieta = 0 ; ieta <=netabin; ieta++){
        if(ieta==netabin)
            scaledjet[ieta] = (TH1F*)rebinjet[ieta]->Clone(Form("jetptNcollScaled_Eta%.f_%.f", -1.0*10, 1.0*10));
        else
            scaledjet[ieta] = (TH1F*)rebinjet[ieta]->Clone(Form("jetptNcollScaled_Eta%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
        if(IsMC==kFALSE)scaledjet[ieta]->Scale(1./A);
        
        if(IsMC){
            if(ieta==netabin)
                scaledppjet[ieta] = (TH1F*)rebinppjet[ieta]->Clone(Form("ppjetptNcollScaled_Eta%.f_%.f", -1.0*10, 1.0*10));
            else
                scaledppjet[ieta] = (TH1F*)rebinppjet[ieta]->Clone(Form("ppjetptNcollScaled_Eta%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
        }
        if(ieta==netabin)
            PARatio[ieta] = (TH1F*)scaledjet[ieta]->Clone(Form("JetRpAInEtaBin%.f_%.f",  -1.0*10, 1.0*10));
        else
            PARatio[ieta] = (TH1F*)scaledjet[ieta]->Clone(Form("JetRpAInEtaBin%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
        
        for(int ibin = 0; ibin <PARatio[ieta]->GetNbinsX(); ibin++){
            PARatio[ieta]->SetBinContent(ibin, 0.);
        }
        
        ftrue->SetParameters(fitpar[ieta]);
        
        //when using PYTHIA as reference
        if(UsePYTHIARef){
            for(int ibin = PARatio[ieta]->FindBin(45.); ibin <PARatio[ieta]->GetNbinsX(); ibin++){
                double binCenter = scaledjet[ieta]->GetBinCenter(ibin);
                //         double binCenter = scaledjet[ieta]->GetBinLowEdge(ibin);
                double binContent = scaledjet[ieta]->GetBinContent(ibin);
                double binError = scaledjet[ieta]->GetBinError(ibin);
                int i = scaledppjet[ieta]->FindBin(binCenter);
                double ppContent = scaledppjet[ieta]->GetBinContent(i);
                if(ppContent){
                    PARatio[ieta]->SetBinContent(ibin, binContent/ppContent);
                    PARatio[ieta]->SetBinError(ibin, binError/ppContent);
                    
                }
                else {
                    PARatio[ieta]->SetBinError(ibin, -1.e-99);
                    PARatio[ieta]->SetBinContent(ibin, -1.e-99);
                }
            }
        }
        else {
            for(int ibin = scaledjet[ieta]->FindBin(45.); ibin <PARatio[ieta]->GetNbinsX(); ibin++){
                double binCenter = scaledjet[ieta]->GetBinCenter(ibin);
                //         double binCenter = scaledjet[ieta]->GetBinLowEdge(ibin);
                double binContent = scaledjet[ieta]->GetBinContent(ibin);
                double binError = scaledjet[ieta]->GetBinError(ibin);
                double ppvalue = ftrue->Eval(binCenter);
                int ip =-1;
                for(int j = 0 ; j < nptpoint[ieta]-1 ; j++){
                    if(x[ieta][j]<=binCenter && x[ieta][j+1]>binCenter) ip = j;
                }
                if(ip<0) continue ;
                cout << "ieta  = " << deta[ieta] << " - " << deta[ieta+1] << "x[np] = " << x[ieta][ip] << "y[np] = " << y[ieta][ip] << " binCenter =" << binCenter << " fun = " << ppvalue <<endl ;
                if(UseFit){
                    if(ppvalue){
                        PARatio[ieta]->SetBinContent(ibin, binContent/ppvalue);
                        PARatio[ieta]->SetBinError(ibin, binError/ppvalue);
                        if(binCenter>ptboundary) {
                            PARatio[ieta]->SetBinError(ibin, -1.e-99);
                            PARatio[ieta]->SetBinContent(ibin, -1.e-99);
                        }
                    }
                    else {
                        PARatio[ieta]->SetBinError(ibin, -1.e-99);
                        PARatio[ieta]->SetBinContent(ibin, -1.e-99);
                    }
                }
                else {
                    if(y[ieta][ip]){
                        PARatio[ieta]->SetBinContent(ibin, binContent/y[ieta][ip]);
                        PARatio[ieta]->SetBinError(ibin, binError/y[ieta][ip]);
                        if(binCenter>ptboundary) {
                            PARatio[ieta]->SetBinError(ibin, -1.e-99);
                            PARatio[ieta]->SetBinContent(ibin, -1.e-99);
                        }
                        
                    }
                    else {
                        PARatio[ieta]->SetBinError(ibin, -1.e-99);
                        PARatio[ieta]->SetBinContent(ibin, -1.e-99);
                    }
                }
            }
        }
        removeZero(PARatio[ieta]);
    }

    for(int ieta = 0 ; ieta <netabin; ieta++){
//        FBRatio[ieta] = (TH1F*)rebinjet[netabin-ieta-1]->Clone(Form("JetAsymmetry_Eta%.f_%.f", deta[netabin-ieta-1]*10, deta[netabin-ieta]*10));
        FBRatio[ieta] = (TH1F*)rebinjet[ieta]->Clone(Form("JetAsymmetry_Eta%.f_%.f", deta[ieta]*10, deta[ieta]*10));
        cout <<"ieta B=" << ieta << " etaLow =" << deta[ieta] << "  etaUp =" << deta[ieta+1]<<endl;
        cout <<"ieta F=" << ieta << " etaLow =" << deta[netabin-ieta-1] << " etaUp =" << deta[netabin-ieta]<<endl;
        FBRatio[ieta]->Divide(rebinjet[netabin-ieta-1]);
        
        FMRatio[ieta] = (TH1F*)rebinjet[ieta]->Clone(Form("JetForwardMidRapidity_Eta%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
        FMRatio[ieta]->Divide(rebinjet[netabin]);

        for(int ibin = FBRatio[ieta]->FindBin(45.); ibin <FBRatio[ieta]->GetNbinsX(); ibin++){
            double binCenter = FBRatio[ieta]->GetBinCenter(ibin);
            if(binCenter>ptboundary[ieta]) {
                FBRatio[ieta]->SetBinContent(ibin,-1.e-9 );
                FBRatio[ieta]->SetBinError(ibin,-1.e-9 );
            }
        }
        for(int ibin = FMRatio[ieta]->FindBin(45.); ibin <FMRatio[ieta]->GetNbinsX(); ibin++){
            double binCenter = FMRatio[ieta]->GetBinCenter(ibin);
            if(binCenter>ptboundary[ieta]) {
                FMRatio[ieta]->SetBinContent(ibin,-1.e-9 );
                FMRatio[ieta]->SetBinError(ibin,-1.e-9 );
            }
        }

        removeZero(FBRatio[ieta]);
        removeZero(FMRatio[ieta]);
  
    }
    
    if(SaveFile){
        TFile * outf = new TFile(Form("%s/%sJetTrigPYTHIA%sJet%sSpectraRpA%sForEric.root", kHomeDir, coll.Data(), algo.Data(), residual.Data(),class.Data()), "RECREATE");
//        TFile * outf = new TFile(Form("%s/ppMCGenNoWeightForKurt.root", kHomeDir), "UPDATE");
        for(int ieta = 0 ; ieta <=netabin; ieta++){
            rebinjet[ieta]->Write();
            rebinppjet[ieta]->Write();
            PARatio[ieta]->Write();
        }
        outf->Close();
        
    }

//    TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,600);
//    gStyle->SetOptFit(1);
//    gStyle->SetOptStat(0);
//    gStyle->SetOptTitle(0);
//    
//    c1->Range(0,0,1,1);
//    c1->SetFillColor(0);
//    c1->SetBorderMode(0);
//    c1->SetBorderSize(2);
//    //c1->SetLogy();
//    c1->SetTickx(1);
//    c1->SetTicky(1);
//    c1->SetLeftMargin(0.13);
//    c1->SetRightMargin(0.06);
//    c1->SetTopMargin(0.05);
//    c1->SetBottomMargin(0.16);
//    c1->SetFrameFillStyle(0);
//    c1->SetFrameBorderMode(0);

    TCanvas *c1 = new TCanvas("c1", "c1",9,2,959,669);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    c1->Range(-38.59656,-12.02472,644.9871,2.486126);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
//    c1->SetLogy();
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->SetLeftMargin(0.162174);
    c1->SetRightMargin(0.00434783);
    c1->SetTopMargin(0.1759166969);
    c1->SetBottomMargin(0.1788566);
    c1->SetFrameFillStyle(0);
    c1->SetFrameLineColor(0);
    c1->SetFrameBorderMode(0);
    c1->SetFrameLineColor(0);
    c1->SetFrameBorderMode(0);
    c1->Divide(3,2,0,0);
/*
    gStyle->SetOptStat(0);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadTopMargin   (0.025);
    gStyle->SetPadLeftMargin  (0.15);
    gStyle->SetPadRightMargin (0.025);
    gStyle->SetPadTickX       (1);
    gStyle->SetPadTickY       (1);
  */  
    
    TLegend *t1=new TLegend(0.45,0.6,0.85,0.9);
  //     TLegend *t1=new TLegend(0.55,0.7,0.8,0.92);
    t1->SetFillColor(0);
    t1->SetBorderSize(0);
    t1->SetFillStyle(0);
    t1->SetTextFont(43);
    t1->SetTextSize(20);

    //TLegend *t2=new TLegend(0.63,0.7,0.85,0.84);
    TLegend *t2=new TLegend(0.64,0.67,0.87,0.84);
 //   TLegend *t2=new TLegend(0.2,0.18,0.6,0.45);
    t2->SetFillColor(0);
    t2->SetBorderSize(0);
    t2->SetFillStyle(0);
    t2->SetTextFont(43);
    t2->SetTextSize(20);

    TLegend *t3=new TLegend(0.43,0.15,0.68,0.38);
 //      TLegend *t3=new TLegend(0.25,0.7,0.8,0.85);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(20);

 //   TLegend *t4=new TLegend(0.56,0.18,0.78,0.38);
    TLegend *t4=new TLegend(0.65,0.15,0.84,0.42);
    t4->SetFillColor(0);
    t4->SetBorderSize(0);
    t4->SetFillStyle(0);
    t4->SetTextFont(43);
    t4->SetTextSize(20);

    TH1F * hDum = new TH1F("hhdum","",1500,0., 1500.);
    //TH1F * hDum = new TH1F("hhdum","",1508,8., 1500.);
    if(netabin==1){
        hDum->SetAxisRange(47.5, 700., "X");
    }
    else {

            hDum->SetAxisRange(47.5, 600., "X");
    }

      hDum->GetXaxis()->SetTitle("p_{T} [GeV/c]");
//    hDum->GetXaxis()->SetRangeUser(20., 600.);
    hDum->GetXaxis()->SetTitleSize(0.07);
    hDum->GetXaxis()->SetTitleOffset(1.08);
    hDum->GetXaxis()->SetLabelSize(0.05);
    hDum->GetYaxis()->SetTitleSize(0.07);
    hDum->GetYaxis()->SetLabelSize(0.05);
    hDum->GetYaxis()->SetTitleOffset(1.15);
    hDum->GetXaxis()->CenterTitle();
    hDum->GetYaxis()->CenterTitle();

    switch(dis){
        case kSpecPb:
            c1->cd();
            c1->SetLogy();
            c1->SetLogx();
            hDum->GetXaxis()->SetMoreLogLabels();
            hDum->GetXaxis()->SetNoExponent();
            hDum->SetAxisRange(47.5, 600., "X");
            hDum->SetMinimum(7.e-11);
            hDum->SetMaximum(500.);
            hhdum->GetYaxis()->SetTitle("d^{2}#sigma/dp_{T}d#eta (mb)");
//            hhdum->GetYaxis()->SetTitle("1/N_{ev}d^{2}N/dp_{T}d#eta");
            hDum->Draw();
            drawCMS(0.22,0.88,Lumi);
 //           drawText(Form("anti-k_{T} PF non-PU jet: R = 0.3"),0.2,0.2,18);
            drawText(Form("Anti-k_{T} Particle Flow PU Jets: R = 0.3"),0.2,0.18,20);
//            drawText(Form("%s: %s jets %s", coll.Data(), algo.Data(), residual.Data()),0.2,0.9,18);

            for(int ieta = 0 ; ieta <=netabin; ieta++){
                rebinjet[ieta]->Scale(scalef[ieta]);
//                if(netabin==1)
//                    drawSys(rebinjet[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], 5, 1001, 1);
//                else
                    drawSys(rebinjet[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], 5, 1001, 1);
//                    drawSys(rebinjet[ieta], ptCen, sys, colorCode[ieta], 3001, 1);
            }
                for(int ieta = 0 ; ieta <=netabin; ieta++){
                rebinjet[ieta]->SetMarkerStyle(markerCode[ieta]);
                rebinjet[ieta]->SetMarkerColor(colorCode[ieta]);
                rebinjet[ieta]->SetMarkerSize(1.5);
                rebinjet[ieta]->SetLineColor(colorCode[ieta]);
                rebinjet[ieta]->DrawCopy("same");
                if(ieta<netabin) rebinjet[ieta]->DrawCopy("same");
                if(ieta==netabin)
                    t1->AddEntry(rebinjet[ieta], Form("%.1f < #eta_{CM} < %.1f ", -1.0, 1.0),"P");
                else {
                 if(ieta==3)
                     t1->AddEntry(rebinjet[ieta], Form("%.1f < #eta_{CM} < %.1f ", deta[netabin-ieta-1],deta[netabin-ieta]),"P");
                    else
                t1->AddEntry(rebinjet[ieta], Form("%.1f < #eta_{CM} < %.1f (x4^{%.f})", deta[netabin-ieta-1],deta[netabin-ieta], scalepower[ieta]),"P");
                }
 //               t1->AddEntry(rebinjet[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[ieta],deta[ieta+1]),"P");
                t1->Draw("same");
            }
      drawText(Form("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV "),0.2,0.95,20);
            break ;
        case kSpecPP:
            c1->cd();
            c1->SetLogy();
   //         hDum->SetAxisRange(20., 600., "X");
            hDum->SetMinimum(7.e-13);
            hDum->SetMaximum(5.e-2);
                hDum->GetYaxis()->SetTitle("d^{2}#sigma_{}/dp_{T}d#eta (mb)");
//            hhdum->GetYaxis()->SetTitle("1/N_{ev}d^{2}N/dp_{T}d#eta");
            hDum->Draw();
            drawText(Form("PYTHIA Z2 tune: ak3GenPF Jet"),0.2,0.2,20);

            for(int ieta = 0 ; ieta <=netabin; ieta++){
                rebinppjet[ieta]->Scale(scalef[ieta]);

                rebinppjet[ieta]->SetMarkerStyle(markerCode[ieta]);
                rebinppjet[ieta]->SetMarkerColor(colorCode[ieta]);
                rebinppjet[ieta]->SetMarkerSize(1.5);
                rebinppjet[ieta]->SetLineColor(colorCode[ieta]);
                rebinppjet[ieta]->DrawCopy("same");
                //               t1->AddEntry(rebinppjet[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[netabin-ieta-1],deta[netabin-ieta]),"P");
                if(ieta==netabin)
                    t1->AddEntry(rebinppjet[ieta], Form("%.1f < #eta_{CM} < %.1f", -1.0, 1.0),"P");
                else
                t1->AddEntry(rebinppjet[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[ieta],deta[ieta+1]),"P");
                t1->Draw("same");
            }
            break ;
        case kRpA:

            hDum->GetXaxis()->SetMoreLogLabels();
            hDum->GetXaxis()->SetNoExponent();
            if(IsMC){
                hDum->SetMinimum(0.6);
                hDum->SetMaximum(1.42);
            }
            else {
            hDum->SetMinimum(0.26);
            hDum->SetMaximum(1.9);
            }
            if(netabin==1)
                hDum->SetAxisRange(1, 550., "X");
            else
                hDum->SetAxisRange(1.0, 550., "X");
            if(IsMC)
                hDum->GetYaxis()->SetTitle("Reco/Truth");
            else
                hDum->GetYaxis()->SetTitle("R_{pPb}");

    TH1F *hDum0, *hDum1, *hDum2;
         for(int ieta = 0 ; ieta <6; ieta++){
            c1->cd(ieta+1);
            //gPad->SetLogx();
    gStyle->SetOptStat(0);
    //gStyle->SetPadBottomMargin(0.12);
    //gStyle->SetPadTopMargin   (0.025);
    //gStyle->SetPadLeftMargin  (0.15);
    //gStyle->SetPadRightMargin (0.025);
    gPad->SetTicks(-1);
    //if(ieta==0) gPad->SetLeftMargin(0.15);
    if(ieta==2||ieta==5) gPad->SetRightMargin(0.02);
            gStyle->SetErrorX(0.5);
    if(ieta<3){
        hDum0=(TH1F*)hDum->Clone();
        hDum0->GetYaxis()->SetTitleSize(0.094);
        hDum0->GetYaxis()->SetTitleOffset(0.92);
        hDum0->GetYaxis()->SetLabelSize(0.0665);
        hDum0->Draw();
     }
    if(ieta==3){
        hDum0x=(TH1F*)hDum->Clone();
        hDum0x->SetAxisRange(0.0, 550., "X");
        hDum0x->GetXaxis()->SetTitleSize(0.08);
        hDum0x->GetXaxis()->SetTitleOffset(0.99);
        hDum0x->GetXaxis()->SetLabelSize(0.056);
        hDum0x->GetYaxis()->SetTitleSize(0.08);
        hDum0x->GetYaxis()->SetTitleOffset(1.09);
        hDum0x->GetYaxis()->SetLabelSize(0.056);
        hDum0x->GetXaxis()->SetLabelOffset(0.0005);
        hDum0x->Draw();
     }
    if(ieta==4){
        hDum1=(TH1F*)hDum->Clone();
        hDum1->GetXaxis()->SetTitleSize(0.085);
        hDum1->GetXaxis()->SetTitleOffset(0.93);
        hDum1->GetXaxis()->SetLabelSize(0.06);
        hDum1->GetXaxis()->SetLabelOffset(0.000);
        hDum1->Draw();
     }
    if(ieta==5){
        hDum2=(TH1F*)hDum->Clone();
        hDum2->GetXaxis()->SetTitleSize(0.085);
        hDum2->GetXaxis()->SetTitleOffset(0.93);
        hDum2->GetXaxis()->SetLabelSize(0.06);
        hDum2->GetXaxis()->SetLabelOffset(0.000);
        hDum2->Draw();
     }

    }
            c1->cd();
            //if(IsMC) drawCMSmc(0.20,0.9);
            //else drawCMS(0.23,0.8,Lumi);
            drawText(Form("CMS Preliminary pPb #sqrt{s_{NN}} = 5.02 TeV "),0.275,0.95,20);
            //drawCMS(0.645,0.996,Lumi);
            drawCMS(0.655,0.999,Lumi);
            c1->cd(2);
            drawText(Form("Anti-k_{T} Particle Flow Jets: R = 0.3"),0.052,0.82,19);
            c1->cd();
            //     int ieta=netabin ;
/*
            double veta3[3][19]={
            {52.5, 60, 69, 79, 90.5, 105.5, 123.5, 143, 163.5, 185, 208, 232.5, 258.5, 286, 315, 346, 378.5, 412.5, 449}, 
            {52.5, 60, 69, 79, 90.5, 105.5, 123.5, 143, 163.5, 185, 208, 232.5, 258.5, 286, 315, 346, 378.5, 412.5, 449}, 
            {52.5, 60, 69, 79, 90.5, 105.5, 123.5, 143, 163.5, 185, 208, 232.5, 258.5, 286, 315, 346, 378.5, 412.5, 449}};
            for(int s=0; s<19; s++){
              veta3[0][s]=veta3[0][s]*0.95;
              veta3[2][s]=veta3[2][s]*1.05;
            }

            double vRpPb3[3][19], RpPbstat3[3][19], RpPbsys3[3][19], ppsys3[3][19];
            for(int i=0; i<19; i++){

                vRpPb3[0][i]=PARatio[6]->GetBinContent(i+15);
                vRpPb3[1][i]=PARatio[3]->GetBinContent(i+15);
                vRpPb3[2][i]=PARatio[0]->GetBinContent(i+15);
                RpPbstat3[0][i]=PARatio[6]->GetBinError(i+15);
                RpPbstat3[1][i]=PARatio[3]->GetBinError(i+15);
                RpPbstat3[2][i]=PARatio[0]->GetBinError(i+15);
                RpPbsys3[0][i]=sys[6][i+1]*0.01*vRpPb3[0][i];
                RpPbsys3[1][i]=sys[3][i+1]*0.01*vRpPb3[1][i];
                RpPbsys3[2][i]=sys[0][i+1]*0.01*vRpPb3[2][i];
                ppsys3[0][i]=ppsys[6][i+1]*0.01*vRpPb3[0][i];
                ppsys3[1][i]=ppsys[3][i+1]*0.01*vRpPb3[1][i];
                ppsys3[2][i]=ppsys[0][i+1]*0.01*vRpPb3[2][i];
//                RpPbsys2[0][i]=sys[i][4];
//                RpPbsys2[1][i]=sys[i][6];
//                RpPbsys2[2][i]=sys[i][10];
                cout<<"test: "<<veta3[1][i]<<"  "<<vRpPb3[1][i]<<"  "<<RpPbstat3[1][i]<<"  "<<RpPbsys3[1][i]<<endl;
            }
*/
            
 //           drawSys(PARatio[netabin], ptCen[netabin], sys[netabin], 5, 1001, 1);

            PARatio[netabin]->SetMarkerStyle(markerCode[netabin]);
            PARatio[netabin]->SetMarkerColor(colorCode[netabin]);
            PARatio[netabin]->SetMarkerSize(1.);
            PARatio[netabin]->SetLineColor(colorCode[netabin]);

            //PARatio[netabin]->SetLineWidth(2);

 //           for(int ieta = 0 ; ieta <=netabin; ieta+=3){
char histnames[8][200];
            for(int ieta = netabin-2 ; ieta >=0; ieta-=1){
            //    if(ieta==netabin&&IsMC==kFALSE)
                //    drawSys(PARatio[ieta], ptCen, sys, 16, 3003, 1);
                        //drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 11-ieta, 1001, ieta);
                        //if(ieta==6) for(int i = 1; i <= PARatio[ieta]->GetNbinsX(); i++){
                        //   PARatio[ieta]->SetBinCenter(i);
                       // }
                  if(ieta==0) c1->cd(1);    
                  if(ieta==1) c1->cd(2);    
                  if(ieta==2) c1->cd(3);    
                  if(ieta==3) c1->cd(4);    
                  if(ieta==4) c1->cd(5);    
                  if(ieta==5) c1->cd(6);    
//                        if(ieta==6) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 7, 4000, ieta);
//                        if(ieta==3) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 4000, ieta);
//                        if(ieta==0) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 16, 4000, ieta);
   //             drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5+ieta, 1001, ieta+1);
                       //drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, netabin-ieta);
                       //drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, 1);
                        
//xxx
                PARatio[ieta]->SetMarkerStyle(20);
                PARatio[ieta]->SetMarkerColor(1);
                PARatio[ieta]->SetMarkerSize(1.);
                PARatio[ieta]->SetLineColor(1);
 sprintf(histnames[ieta],"JetRpAEtaBin_%d",ieta);
                PARatio[ieta]->SetName(histnames[ieta]);
 PARatio[ieta]->SetBinContent(PARatio[ieta]->FindBin(46),-10);
      for(int i=1; i<60; i++){
        if(PARatio[ieta]->GetBinContent(i)>1.8||PARatio[ieta]->GetBinContent(i)<0.3) PARatio[ieta]->SetBinContent(i, -10);
      }
                //PARatio[ieta]->DrawCopy("same PE");
                //if(netabin==1)
                //    regSun(47.5,1.,700.,1.,1, 1);
                //else
                //    regSun(47.5,1.,790.,1.,1, 1);
 //               t2->AddEntry(PARatio[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[netabin-ieta-1],deta[netabin-ieta]),"P");
                //t2->AddEntry(PARatio[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[ieta],deta[ieta+1]),"P");
            }

   TLine *lines = new TLine(-2,-1,-1,-1);
   lines->SetLineStyle(1);
   lines->SetLineWidth(1);
            for(int ieta = netabin-2 ; ieta >=0; ieta-=2){
                  //if(ieta==1) c1->cd(1);
                  //if(ieta==3) c1->cd(2);
                  //if(ieta==5) c1->cd(3);
               //drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, ieta);
             }
            for(int ieta = 0 ; ieta <=netabin-2; ieta+=1){
                  if(ieta==0) c1->cd(1);
                  if(ieta==1) c1->cd(2);
                  if(ieta==2) c1->cd(3);
                  if(ieta==3) c1->cd(4);
                  if(ieta==4) c1->cd(5);
                  if(ieta==5) c1->cd(6);
                  //if(ieta==5) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 3000, ieta);
                  //if(ieta==4) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 3000, ieta);
                  //if(ieta==3) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 3000, ieta);
                  //if(ieta==2) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 3000, ieta);
                  //if(ieta==1) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 3000, ieta);
                  //if(ieta==0) drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 3000, ieta);
                  drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], ppsys[ieta], 5, 3000, ieta);
              drawSys(PARatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], 42, 0, ieta);
             
      for(int i=1; i<20; i++){
       //if(ieta==3) cout<<"test ptcen :"<<ptCen[ieta][i]<<"  "<<PARatio[ieta]->GetBinContent(i+14)<<"  "<<ppsys[ieta][i]<<"  "<<sys[ieta][i]<<endl;
        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+ppsys[ieta][i]*0.01),
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+ppsys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+ppsys[ieta][i]*0.01)-0.02,
                        ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+ppsys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+ppsys[ieta][i]*0.01)-0.02,
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+ppsys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-ppsys[ieta][i]*0.01),
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-ppsys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-ppsys[ieta][i]*0.01),
                        ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-ppsys[ieta][i]*0.01)+0.02);
        lines->DrawLine(ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-ppsys[ieta][i]*0.01),
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-ppsys[ieta][i]*0.01)+0.02);

        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+sys[ieta][i]*0.01),
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+sys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+sys[ieta][i]*0.01)-0.02,
                        ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+sys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+sys[ieta][i]*0.01)-0.02,
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1+sys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-sys[ieta][i]*0.01),
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-sys[ieta][i]*0.01));
        lines->DrawLine(ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-sys[ieta][i]*0.01),
                        ptCen[ieta][i]-findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-sys[ieta][i]*0.01)+0.02);
        lines->DrawLine(ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-sys[ieta][i]*0.01),
                        ptCen[ieta][i]+findptbinfactor(ptCen[ieta][i]),  PARatio[ieta]->GetBinContent(i+14)*(1-sys[ieta][i]*0.01)+0.02);
 
      }

              PARatio[ieta]->DrawCopy("same");
            double boxxx = 510;
            TBox *box = new TBox(boxxx-boxxx*0.015,1.0-0.035,boxxx+boxxx*0.03,1.0+0.035);
            box->SetLineColor(kGreen+3);
            box->SetFillColor(kGreen+3);
            box->SetFillStyle(1001);
            box->SetLineStyle(1);
            box->SetLineWidth(2);
            box->Draw();
            double yetap=0.43;
            double xetap=135;
            if(ieta==0) TLatex *tex1= new TLatex(xetap,yetap,"-2.0 < #eta_{CM} < -1.5");
            if(ieta==1) TLatex *tex1= new TLatex(xetap,yetap,"-1.5 < #eta_{CM} < -1.0");
            if(ieta==2) TLatex *tex1= new TLatex(xetap,yetap,"-1.0 < #eta_{CM} < -0.5");
            if(ieta==3) TLatex *tex1= new TLatex(xetap,yetap,"-0.5 < #eta_{CM} < 0.5 ");
            if(ieta==4) TLatex *tex1= new TLatex(xetap,yetap," 0.5 < #eta_{CM} < 1.0 ");
            if(ieta==5) TLatex *tex1= new TLatex(xetap,yetap," 1.0 < #eta_{CM} < 1.5 ");
            tex1->SetTextColor(1);
            tex1->SetTextSize(20);
            tex1->SetTextFont(43);
            tex1->Draw();
              }
             //PARatio[0]->DrawCopy("same");


//            PARatio[netabin]->DrawCopy("same");
//            t2->AddEntry(PARatio[0], Form("%.1f < #eta_{CM} < %.1f", deta[netabin-0-1],deta[netabin-0]),"P");
//            t2->AddEntry(PARatio[netabin], Form("%.1f < #eta_{CM} < %.1f", -1.0, 1.0),"P");
//            t2->AddEntry(PARatio[6], Form("%.1f < #eta_{CM} < %.1f", deta[netabin-6-1],deta[netabin-6]),"P");
/*
            int npts[3]={13, 19, 13};
            for(int j=0; j<3; j++){
                int np=0;
                while (np < npts[j]) {
                    //TBox *box1 = new TBox(veta3[j][np]-0.02*veta3[j][np],vRpPb3[j][np]-ppsys3[j][np],veta3[j][np]+0.02*veta3[j][np],vRpPb3[j][np]+ppsys3[j][np]);
                    TBox *box1 = new TBox(veta3[j][np]-0.03*veta3[j][np],vRpPb3[j][np]-ppsys3[j][np],veta3[j][np]+0.03*veta3[j][np],vRpPb3[j][np]+ppsys3[j][np]);
                    if(j==0) box1->SetFillColor(7);
                    if(j==1) box1->SetFillColor(5);
                    if(j==2) box1->SetFillColor(16);
                    box1->SetFillStyle(1001);
                    box1->Draw();
                    np++;
                }
            }
            for(int j=0; j<3; j++){
                int np=0;
                while (np < npts[j]) {
                    TBox *box = new TBox(veta3[j][np]-0.03*veta3[j][np],vRpPb3[j][np]-RpPbsys3[j][np],veta3[j][np]+0.03*veta3[j][np],vRpPb3[j][np]+RpPbsys3[j][np]);
                    if(j==0) {box->SetLineStyle(1); box->SetLineColor(1);}
                    if(j==1) {box->SetLineStyle(1);box->SetLineColor(2);}
                    if(j==2) {box->SetLineStyle(1); box->SetLineColor(4);}
                    box->SetFillStyle(0);
                    box->SetLineWidth(2);
                    box->Draw();
                    np++;
                }
            }
*/            

            c1->cd(1);
            TBox *box1 = new TBox(145.,1.70,193.5,1.76);
            box1->SetFillColor(5);
            box1->SetLineColor(5);
            //box1->SetFillStyle(1001);
            box1->Draw("same");
            TLatex *tex1= new TLatex(215.0,1.70,"pp uncertainties");
            tex1->SetTextColor(1);
            tex1->SetTextSize(20);
            tex1->SetTextFont(43);
            tex1->Draw();
            TBox *box2 = new TBox(145.,1.54,193.5,1.6);
         //   box2->SetFillColor(kYellow);
            //box2->SetFillStyle(0);
            box2->SetLineColor(42);
            box2->SetFillColor(42);
            //box2->SetLineWidth(2);
            box2->Draw("same");
            TLatex *tex1= new TLatex(215.0,1.54,"pPb uncertainties");
            tex1->SetTextColor(1);
            tex1->SetTextSize(20);
            tex1->SetTextFont(43);
            tex1->Draw();
            //t2->AddEntry(box1, "pp uncertainty","f");
            //t2->AddEntry(box2, "pPb uncertainty","f");

            //t2->Draw("same");
            c1->cd(3);
            TBox *box1 = new TBox(62.8,1.63,108.5,1.69);
            box1->SetFillColor(kGreen+3);
            box1->SetLineColor(kGreen+3);
            //box1->SetFillStyle(1001);
            box1->Draw("same");
            TLatex *tex1= new TLatex(125.0,1.63,"Luminosity uncertainties");
            tex1->SetTextColor(1);
            tex1->SetTextSize(20);
            tex1->SetTextFont(43);
            tex1->Draw();

            c1->cd(1);
            regSun(1,1.,550.,1.,1, 1);
            c1->cd(2);
            regSun(1,1.,550.,1.,1, 1);
            c1->cd(3);
            regSun(1,1.,550.,1.,1, 1);
            c1->cd(4);
            regSun(1,1.,550.,1.,1, 1);
            c1->cd(5);
            regSun(1,1.,550.,1.,1, 1);
            c1->cd(6);
            regSun(1,1.,550.,1.,1, 1);

            break ;
        case kAsy:
            c1->cd();
            c1->SetLogx();
            hDum->GetXaxis()->SetMoreLogLabels();
            hDum->GetXaxis()->SetNoExponent();
            hDum->SetMinimum(0.);
            hDum->SetMaximum(1.7);
            hDum->SetAxisRange(47.5, 600., "X");
            hhdum->GetYaxis()->SetTitle("Yield_{Pb going}/Yield_{p going}");
            hDum->Draw();
      //      drawText(Form("R_{pPb}: %s jets %s", algo.Data(), residual.Data()),0.2,0.9,18);
            drawCMS(0.25,0.85,Lumi);
    //        drawText(Form("anti-k_{T} PF jet: R = 0.3, Generator Level"),0.2,0.8,18);
   //         drawText(Form("PYTHIA Z2 tune: ak3Gen Jet"),0.2,0.9,18);
            drawText(Form("Anti-k_{T} Particle Flow Jets: R = 0.3"),0.2,0.75,20);
            drawText(Form("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV "),0.2,0.95,20);
   //       drawText(Form("anti-k_{T} PF PU jet: R = 0.3, Baysian unfolded"),0.2,0.8,18);
            for(int ieta = netabin/2-1 ; ieta >=0; ieta--){
//            for(int ieta = 0 ; ieta <netabin/2; ieta++){
//                if(netabin==1)
//                    drawSys(FBRatio[ieta], ptCen[ieta], sys[ieta], 5, 1001, 1);
//                else
             //       drawSys(FBRatio[ieta], ptCen, sys, colorCode[ieta], 3003, 1);
 //               drawSys(FBRatio[ieta], ptboundary[ieta], ptCen[ieta], sys[netabin-ieta-1], colorCode[ieta], 0, ieta+1);
                    //drawSys(FBRatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, 1);
                FBRatio[ieta]->SetMarkerStyle(markerCode[ieta]);
                FBRatio[ieta]->SetMarkerColor(colorCode[ieta]);
                FBRatio[ieta]->SetMarkerSize(1.5);
                FBRatio[ieta]->SetLineColor(colorCode[ieta]);
//                if(ieta>0)
//                    FBRatio[ieta]->SetMarkerStyle(32+ieta);
//                if(ieta>1){
//                    FBRatio[ieta]->SetMarkerStyle(32+ieta);
//                    FBRatio[ieta]->SetMarkerColor(2+ieta);
//                    FBRatio[ieta]->SetLineColor(2+ieta);
//                }
//                if(netabin==1)
//                    drawSys(FBRatio[ieta], ptCen, sys, 5, 1001, 1);
//                else
//                    drawSys(FBRatio[ieta], ptCen, sys, colorCode[ieta], 3003, 1);

                FBRatio[ieta]->DrawCopy("same PE");
                if(netabin==1)
                    regSun(47.5,1.,600.,1.,1, 1);
                else
                    regSun(47.5,1.,600.,1.,1, 1);
                t3->AddEntry(FBRatio[ieta], Form("%.1f<#eta_{CM}<%.1f/%.1f< #eta_{CM}<%.1f",  deta[ieta],deta[ieta+1],deta[netabin-ieta-1],deta[netabin-ieta]),"P");
//                t3->AddEntry(FBRatio[ieta], Form("%.1f<#eta_{CM}<%.1f/%.1f< #eta_{CM}<%.1f",  deta[ieta],deta[ieta+1],deta[netabin-ieta-1],deta[netabin-ieta]),"P");
            }
            TBox *box2 = new TBox(0.45,0.65,0.8,0.9);
            //   box2->SetFillColor(kYellow);
            box2->SetFillStyle(0);
            box2->SetLineColor(1);
            //    box2->Draw("same");
        //    t3->AddEntry(box2, "pPb uncertainty","f");
            t3->Draw("same");

            TBox *box = new TBox(590-4.5,1.0-0.035,590+4.5,1.0+0.035);
            box->SetFillColor(kBlue-7);
            box->SetFillStyle(-1);
        //    box->Draw();

            break ;
        case kRpAEtaDep:
            c1->cd();
            if(IsMC){
                hDum->SetMinimum(0.6);
                hDum->SetMaximum(1.42);
            }
            else {
                hDum->SetMinimum(0.48);
                hDum->SetMaximum(2.02);
            }
            TH1D* hist2 = new TH1D("hist2","hist2",100,-2.2,2.2);
            hist2->SetXTitle("#eta_{CM}");
   //         hist2->SetYTitle("R_{pPb}^{PYTHIA}");
            hist2->SetYTitle("R_{pPb}");
            hist2->SetMinimum(0.66);
            hist2->SetMaximum(2.1);
            hist2->GetXaxis()->SetTitleSize(0.056);
            hist2->GetXaxis()->SetTitleOffset(1.15);
            hist2->GetXaxis()->SetLabelSize(0.05);
            hist2->GetYaxis()->SetTitleSize(0.05);
            hist2->GetYaxis()->SetLabelSize(0.045);
            hist2->GetYaxis()->SetTitleOffset(1.25);
            hist2->GetXaxis()->CenterTitle();
            hist2->GetYaxis()->CenterTitle();
            hist2->DrawCopy();
            double ptvalue[] = {90, 120, 200};
            int  ptRange[3];
            TH1F * ptIntegral[N][3];
            int sysbin0, sysbin1, sysbin2;
            double veta2[3][N]={{-1.85, -1.35, -0.85, -0.1, 0.65, 1.15, 1.65}, {-1.75, -1.25, -0.75, 0., 0.75, 1.25, 1.75}, {-1.65, -1.15, -0.65, 0.1, 0.85, 1.35, 1.85}};

            double vRpPb2[3][N], RpPbstat2[3][N], RpPbsys2[3][N], ppsys2[3][N];

            if(IsMC) drawCMSmc(0.20,0.9);
            //else drawCMS(0.20,0.88,Lumi);
            //drawText(Form("Anti-k_{T} Particle Flow PU Jets: R = 0.3"),0.2,0.6,20);
            //drawText(Form("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV "),0.2,0.95,20);
            else drawCMS(0.23,0.8,Lumi);
            drawText(Form("Anti-k_{T} Particle Flow PU Jets: R = 0.3"),0.2,0.86,20);
            drawText(Form("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV "),0.25,0.95,20);
          //  drawText(Form("anti-k_{T} PF PU jet: R = 0.3, Baysian unfolded"),0.2,0.2,18);
//            for(int ieta=0; ieta<netabin; ieta++){
//                  for(int i= 0 ; i < 3 ; i++){
//                      ptIntegral[ieta][i] = (TH1F*)PARatio[netabin-1-ieta]->Clone(Form("Integralpt%.f_%.fEtaBin%.f_%.f", ptvalue[i], ptvalue[i+1], deta[ieta]*10, deta[ieta+1]*10));
//                      ptIntegral[ieta][i]->GetXaxis()->SetRange(ptvalue[i], ptvalue[i+1]);
//                      int binLow =ptIntegral[ieta][i]->FindBin(ptvalue[i]);
//                      int binHigh =ptIntegral[ieta][i]->FindBin(ptvalue[i+1]);
//                      
//                      vRpPb2[i][ieta] =ptIntegral[ieta][i]->Integral(binLow, binHigh)/(binHigh-binLow);
//                      RpPbstat2[i][ieta]=ptIntegral[ieta][i]->GetRMSError()/(binHigh-binLow);
//                      RpPbsys2[i][ieta]=sys[ieta][5]*0.01*vRpPb2[i][ieta];
//                     ppsys2[i][ieta]=ppsys[ieta][5]*0.01*vRpPb2[i][ieta];
//
//                      cout<<veta2[i][ieta]<<"  "<<vRpPb2[i][ieta]<<"  "<<RpPbstat2[i][ieta]<<"  "<<RpPbsys2[i][ieta]<<endl;
//                  }
//            }
            for(int i= 0 ; i < 3 ; i++){
                for(int ipt = 1 ; ipt < nJetPtBin ; ipt++) {
                    if(ptvalue[i]>=jetPtBin[ipt] && ptvalue[i]<jetPtBin[ipt+1]) ptRange[i] = ipt ;
                  }
                }
                for(int ip = 0 ; ip < np ; ip++) {
               //     for(int i= 0 ; i < 3 ; i++){
                    if(jetPtBin[ptRange[0]]>=ptCen[0][ip] && jetPtBin[ptRange[0]]<ptCen[0][ip]) sysbin0 = ip+1 ;
                }
            for(int ip = 0 ; ip < np ; ip++) {
                    if(jetPtBin[ptRange[1]]>=ptCen[0][ip] && jetPtBin[ptRange[1]]<ptCen[0][ip]) sysbin1 = ip+1 ;
            }
            for(int ip = 0 ; ip < np ; ip++) {
                    if(jetPtBin[ptRange[2]]>=ptCen[0][ip] && jetPtBin[ptRange[2]]<ptCen[0][ip]) sysbin2 = ip+1 ;
                }
            cout <<"sys bin  =" << sysbin0 << " 1=" << sysbin1 << "  2 =" <<sysbin2 <<endl ;
            for(int i=0; i<netabin; i++){
                int ptbin1 = PARatio[i]->FindBin(ptvalue[0]);
                int ptbin2 = PARatio[i]->FindBin(ptvalue[1]);
                int ptbin3 = PARatio[i]->FindBin(ptvalue[2]);


                vRpPb2[0][i]=PARatio[i]->GetBinContent(ptbin1);
                vRpPb2[1][i]=PARatio[i]->GetBinContent(ptbin2);
                vRpPb2[2][i]=PARatio[i]->GetBinContent(ptbin3);
                RpPbstat2[0][i]=PARatio[i]->GetBinError(ptbin1);
                RpPbstat2[1][i]=PARatio[i]->GetBinError(ptbin2);
                RpPbstat2[2][i]=PARatio[i]->GetBinError(ptbin3);
                RpPbsys2[0][i]=sys[i][5]*0.01*vRpPb2[0][i];
                RpPbsys2[1][i]=sys[i][7]*0.01*vRpPb2[1][i];
                RpPbsys2[2][i]=sys[i][11]*0.01*vRpPb2[2][i];
                ppsys2[0][i]=ppsys[i][5]*0.01*vRpPb2[0][i];
                ppsys2[1][i]=ppsys[i][7]*0.01*vRpPb2[1][i];
                ppsys2[2][i]=ppsys[i][11]*0.01*vRpPb2[2][i];
//                RpPbsys2[0][i]=sys[i][4];
//                RpPbsys2[1][i]=sys[i][6];
//                RpPbsys2[2][i]=sys[i][10];
                cout<<veta2[0][i]<<"  "<<vRpPb2[0][i]<<"  "<<RpPbstat2[0][i]<<"  "<<RpPbsys2[0][i]<<endl;
            }
            
            for(int j=0; j<3; j++){
                int np=0;
                while (np < netabin) {
                    TBox *box1 = new TBox(veta2[j][np]-0.05,vRpPb2[j][np]-ppsys2[j][np],veta2[j][np]+0.05,vRpPb2[j][np]+ppsys2[j][np]);
                    if(j==0) box1->SetFillColor(5);
                    if(j==1) box1->SetFillColor(8);
                    if(j==2) box1->SetFillColor(11);
                    box1->SetFillStyle(1001);
                    box1->Draw();
                    np++;
                }
            }
            for(int j=0; j<3; j++){
                int np=0;
                while (np < netabin) {
                    TBox *box = new TBox(veta2[j][np]-0.05,vRpPb2[j][np]-RpPbsys2[j][np],veta2[j][np]+0.05,vRpPb2[j][np]+RpPbsys2[j][np]);
                    if(j==0) {box->SetLineStyle(1); box->SetLineColor(2);}
                    if(j==1) {box->SetLineStyle(1);box->SetLineColor(1);}
                    if(j==2) {box->SetLineStyle(1); box->SetLineColor(4);}
                    box->SetFillStyle(0);
                    box->SetLineWidth(2);
                    box->Draw();
                    np++;
                }
            }
            
            TBox *box = new TBox(2.05-0.05,1.0-0.035,2.05+0.05,1.0+0.035);
            box->SetFillColor(kMagenta);
            box->SetFillStyle(-1);
            box->Draw();
            TGraphErrors *graph = new TGraphErrors(N,veta2[0],vRpPb2[0],0,RpPbstat2[0]);
            graph->SetTitle("gr");
            graph->SetMarkerStyle(33);
            graph->SetMarkerColor(2);
            graph->SetLineColor(2);
            graph->SetLineWidth(2);
            graph->SetMarkerSize(1.5);
            drawSysTGraph(graph, veta2[0], ppsys2[0], 5, 1001, 1);
            drawSysTGraph(graph, veta2[0], RpPbsys2[0], colorCode[0], 0, 1);
            graph->Draw("psameez");
            TGraphErrors *graph2 = new TGraphErrors(N,veta2[1],vRpPb2[1],0,RpPbstat2[1]);
            graph2->SetTitle("gr2");
            graph2->SetMarkerStyle(20);
            graph2->SetMarkerColor(1);
            graph2->SetLineColor(1);
            graph2->SetMarkerSize(1.5);
            graph2->SetLineWidth(1);
            drawSysTGraph(graph2, veta2[1], ppsys2[1], kGreen-6, 1001, 1);
            drawSysTGraph(graph2, veta2[1], RpPbsys2[1], colorCode[1], 0, 2);
            graph2->SetMarkerSize(1.5);
            graph2->Draw("psameez");
            TGraphErrors *graph3 = new TGraphErrors(N,veta2[2],vRpPb2[2],0,RpPbstat2[2]);
            graph3->SetTitle("gr3");
            graph3->SetMarkerStyle(27);
            graph3->SetMarkerColor(4);
            graph3->SetLineColor(4);
            graph3->SetLineWidth(2);
            graph3->SetMarkerSize(1.5);
            drawSysTGraph(graph3, veta2[2], ppsys2[2], 7, 1001, 1);
            drawSysTGraph(graph3, veta2[2], RpPbsys2[2], colorCode[2], 0, 3);
            graph3->Draw("psameez");
            
            regSun(-2.3.,1.,2.3.,1.,1, 1);

            
            TLegend *leg0 = new TLegend(0.49,0.66,0.68,0.82);
            leg0->SetFillColor(10);
            leg0->SetBorderSize(0.05);
            leg0->SetTextFont(43);
            leg0->SetTextSize(20.0);
            leg0->AddEntry(graph,Form("%.f < p_{T} < %.f GeV/c",jetPtBin[ptRange[0]], jetPtBin[ptRange[0]+1]) ,"P");
            leg0->AddEntry(graph2,Form("%.f < p_{T} < %.f GeV/c",jetPtBin[ptRange[1]], jetPtBin[ptRange[1]+1]),"P");
            leg0->AddEntry(graph3,Form("%.f < p_{T} < %.f GeV/c",jetPtBin[ptRange[2]], jetPtBin[ptRange[2]+1]),"P");
/*            
            TBox *box1 = new TBox(0.45,0.65,0.8,0.9);
            box1->SetFillColor(kYellow);
            box1->SetLineColor(5);
            box1->SetFillStyle(1001);
            //     box1->Draw("same");
            TBox *box2 = new TBox(0.45,0.65,0.8,0.9);
            //   box2->SetFillColor(kYellow);
            box2->SetFillStyle(0);
            box2->SetLineColor(2);
            //    box2->Draw("same");
            //leg0->AddEntry(box1, "pp uncertainty","f");
            //leg0->AddEntry(box2, "pPb uncertainty","f");
*/
            leg0->Draw();
            TBox *box1 = new TBox(-0.255,1.555,-0.155,1.59);
            box1->SetFillColor(kGreen-6);
            box1->SetLineColor(kGreen-6);
            box1->SetFillStyle(1001);
            box1->Draw("same");
            TLatex *tex1= new TLatex(-0.06,1.56,"pp uncertainties");
            tex1->SetTextColor(1);
            tex1->SetTextSize(20);
            tex1->SetTextFont(43);
            tex1->Draw();
            TBox *box2 = new TBox(-0.25,1.465,-0.16,1.5);
         //   box2->SetFillColor(kYellow);
            box2->SetFillStyle(0);
            box2->SetLineColor(kBlack);
            box2->SetLineWidth(2);
            box2->Draw("same");
            TLatex *tex1= new TLatex(-0.06,1.47,"pPb uncertainties");
            tex1->SetTextColor(1);
            tex1->SetTextSize(20);
            tex1->SetTextFont(43);
            tex1->Draw();
            
            break ;
        case kEtaDep:
            c1->cd();
            c1->SetLogx();
            hDum->GetXaxis()->SetMoreLogLabels();
            hDum->GetXaxis()->SetNoExponent();
            hDum->SetMinimum(0.);
            hDum->SetMaximum(1.7);
            hDum->SetAxisRange(47.5, 1500., "X");
            hhdum->GetYaxis()->SetTitle("(d^{2}#sigma/dp_{T}d#eta)/(d^{2}#sigma/dp_{T}d#eta(|#eta_{CM}|<1))");
            hDum->Draw();
            drawCMS(0.25,0.85,Lumi);
  //         drawText(Form("anti-k_{T} PF jet: R = 0.3, Generator Level"),0.2,0.8,18);
 //           drawText(Form("PYTHIA Z2 tune: %s jets %s", algo.Data(), residual.Data()),0.2,0.9,18);
  //          drawText(Form("anti-k_{T} PF non-PU jet: R = 0.3"),0.2,0.8,18);
            drawText(Form("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV "),0.2,0.95,20);
            drawText(Form("Anti-k_{T} Particle Flow PU Jets: R = 0.3"),0.2,0.75,20);
//          drawText(Form("anti-k_{T} PF PU jet: R = 0.3, Baysian unfolded"),0.2,0.8,18);
            for(int ieta = netabin-1 ; ieta >=0; ieta--){
//            for(int ieta = 0 ; ieta <netabin; ieta++){
                    drawSys(FMRatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, 1);
//            if(ieta==0 ) drawSys(FMRatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, ieta+1);
//            if(ieta==3 ) drawSys(FMRatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, ieta+1);
//            if(ieta==netabin-1 ) drawSys(FMRatio[ieta], ptboundary[ieta], ptCen[ieta], sys[ieta], colorCode[ieta], 0, ieta+1);
                FMRatio[ieta]->SetMarkerStyle(markerCode[ieta]);
                FMRatio[ieta]->SetMarkerColor(colorCode[ieta]);
                FMRatio[ieta]->SetMarkerSize(1.5);
                FMRatio[ieta]->SetLineColor(colorCode[ieta]);
 
                FMRatio[ieta]->DrawCopy("same");
                    regSun(47.5,1.,1500.,1.,1, 1);
                //    if(ieta<netabin) PARatio[ieta]->DrawCopy("same");
                t4->AddEntry(FMRatio[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[ieta],deta[ieta+1]),"P");
    //                t4->AddEntry(FMRatio[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[netabin-ieta-1],deta[netabin-ieta]),"P");
                t4->Draw("same");
            }
             for(int ieta = 0 ; ieta <netabin; ieta++)FMRatio[ieta]->DrawCopy("same");
            break ;
        case kAsyEtaDep:
            c1->cd();
            TH1D* hist2 = new TH1D("hist2","hist2",100,-2.2,2.2);
            hist2->SetXTitle("#eta_{CM}");
            //         hist2->SetYTitle("R_{pPb}^{PYTHIA}");
            hist2->SetYTitle("(d^{2}#sigma/dp_{T}d#eta)/(d^{2}#sigma/dp_{T}d#eta(|#eta_{CM}|<1))");
            hist2->SetMinimum(0.);
            hist2->SetMaximum(1.7);
            hist2->GetXaxis()->SetTitleSize(0.056);
            hist2->GetXaxis()->SetTitleOffset(0.95);
            hist2->GetXaxis()->SetLabelSize(0.05);
            hist2->GetYaxis()->SetTitleSize(0.05);
            hist2->GetYaxis()->SetLabelSize(0.045);
            hist2->GetYaxis()->SetTitleOffset(1.25);
            hist2->GetXaxis()->CenterTitle();
            hist2->GetYaxis()->CenterTitle();
            hist2->DrawCopy();
            double ptvalue[] = {90, 120, 200};
            int  ptRange[3];
            TH1F * ptIntegral[N][3];
            int sysbin0, sysbin1, sysbin2;
            double veta2[3][N]={{-1.85, -1.35, -0.85, -0.1, 0.65, 1.15, 1.65}, {-1.75, -1.25, -0.75, 0., 0.75, 1.25, 1.75}, {-1.65, -1.15, -0.65, 0.1, 0.85, 1.35, 1.85}};
            
            double vRpPb2[3][N], RpPbstat2[3][N], RpPbsys2[3][N], ppsys2[3][N];
            
            if(IsMC) drawCMSmc(0.20,0.9);
            else drawCMS(0.20,0.88,Lumi);
            drawText(Form("Anti-k_{T} Particle Flow PU Jets: R = 0.3"),0.2,0.75,20);
            drawText(Form("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV "),0.2,0.95,20);            //  drawText(Form("anti-k_{T} PF PU jet: R = 0.3, Baysian unfolded"),0.2,0.2,18);
            //            for(int ieta=0; ieta<netabin; ieta++){
            //                  for(int i= 0 ; i < 3 ; i++){
            //                      ptIntegral[ieta][i] = (TH1F*)PARatio[netabin-1-ieta]->Clone(Form("Integralpt%.f_%.fEtaBin%.f_%.f", ptvalue[i], ptvalue[i+1], deta[ieta]*10, deta[ieta+1]*10));
            //                      ptIntegral[ieta][i]->GetXaxis()->SetRange(ptvalue[i], ptvalue[i+1]);
            //                      int binLow =ptIntegral[ieta][i]->FindBin(ptvalue[i]);
            //                      int binHigh =ptIntegral[ieta][i]->FindBin(ptvalue[i+1]);
            //
            //                      vRpPb2[i][ieta] =ptIntegral[ieta][i]->Integral(binLow, binHigh)/(binHigh-binLow);
            //                      RpPbstat2[i][ieta]=ptIntegral[ieta][i]->GetRMSError()/(binHigh-binLow);
            //                      RpPbsys2[i][ieta]=sys[ieta][5]*0.01*vRpPb2[i][ieta];
            //                     ppsys2[i][ieta]=ppsys[ieta][5]*0.01*vRpPb2[i][ieta];
            //
            //                      cout<<veta2[i][ieta]<<"  "<<vRpPb2[i][ieta]<<"  "<<RpPbstat2[i][ieta]<<"  "<<RpPbsys2[i][ieta]<<endl;
            //                  }
            //            }
            for(int i= 0 ; i < 3 ; i++){
                for(int ipt = 1 ; ipt < nJetPtBin ; ipt++) {
                    if(ptvalue[i]>=jetPtBin[ipt] && ptvalue[i]<jetPtBin[ipt+1]) ptRange[i] = ipt ;
                }
            }
            for(int ip = 0 ; ip < np ; ip++) {
                //     for(int i= 0 ; i < 3 ; i++){
                if(jetPtBin[ptRange[0]]>=ptCen[0][ip] && jetPtBin[ptRange[0]]<ptCen[0][ip]) sysbin0 = ip+1 ;
            }
            for(int ip = 0 ; ip < np ; ip++) {
                if(jetPtBin[ptRange[1]]>=ptCen[0][ip] && jetPtBin[ptRange[1]]<ptCen[0][ip]) sysbin1 = ip+1 ;
            }
            for(int ip = 0 ; ip < np ; ip++) {
                if(jetPtBin[ptRange[2]]>=ptCen[0][ip] && jetPtBin[ptRange[2]]<ptCen[0][ip]) sysbin2 = ip+1 ;
            }
            cout <<"sys bin  =" << sysbin0 << " 1=" << sysbin1 << "  2 =" <<sysbin2 <<endl ;
            for(int i=0; i<netabin; i++){
                int ptbin1 = FMRatio[i]->FindBin(ptvalue[0]);
                int ptbin2 = FMRatio[i]->FindBin(ptvalue[1]);
                int ptbin3 = FMRatio[i]->FindBin(ptvalue[2]);
                
                
                vRpPb2[0][i]=FMRatio[i]->GetBinContent(ptbin1);
                vRpPb2[1][i]=FMRatio[i]->GetBinContent(ptbin2);
                vRpPb2[2][i]=FMRatio[i]->GetBinContent(ptbin3);
                RpPbstat2[0][i]=FMRatio[i]->GetBinError(ptbin1);
                RpPbstat2[1][i]=FMRatio[i]->GetBinError(ptbin2);
                RpPbstat2[2][i]=FMRatio[i]->GetBinError(ptbin3);
                RpPbsys2[0][i]=sys[i][5]*0.01*vRpPb2[0][i];
                RpPbsys2[1][i]=sys[i][7]*0.01*vRpPb2[1][i];
                RpPbsys2[2][i]=sys[i][11]*0.01*vRpPb2[2][i];
                ppsys2[0][i]=ppsys[i][5]*0.01*vRpPb2[0][i];
                ppsys2[1][i]=ppsys[i][7]*0.01*vRpPb2[1][i];
                ppsys2[2][i]=ppsys[i][11]*0.01*vRpPb2[2][i];
                //                RpPbsys2[0][i]=sys[i][4];
                //                RpPbsys2[1][i]=sys[i][6];
                //                RpPbsys2[2][i]=sys[i][10];
                cout<<veta2[0][i]<<"  "<<vRpPb2[0][i]<<"  "<<RpPbstat2[0][i]<<"  "<<RpPbsys2[0][i]<<endl;
            }
            for(int j=0; j<3; j++){
                int np=0;
                while (np < netabin) {
                    TBox *box = new TBox(veta2[j][np]-0.05,vRpPb2[j][np]-RpPbsys2[j][np],veta2[j][np]+0.05,vRpPb2[j][np]+RpPbsys2[j][np]);
                    if(j==0) {box->SetLineStyle(1); box->SetLineColor(2);}
                    if(j==1) {box->SetLineStyle(2);box->SetLineColor(1);}
                    if(j==2) {box->SetLineStyle(3); box->SetLineColor(4);}
                    box->SetFillStyle(0);
                    box->SetLineWidth(2);
                    box->Draw();
                    np++;
                }
            }
            
            TBox *box = new TBox(2.1-0.05,1.0-0.035,2.1+0.05,1.0+0.035);
            box->SetFillColor(kBlue-7);
            box->SetFillStyle(-1);
        //    box->Draw();
            TGraphErrors *graph = new TGraphErrors(N,veta2[0],vRpPb2[0],0,RpPbstat2[0]);
            graph->SetTitle("gr");
            graph->SetMarkerStyle(33);
            graph->SetMarkerColor(2);
            graph->SetLineColor(2);
            graph->SetLineWidth(2);
            graph->SetMarkerSize(1.5);
            drawSysTGraph(graph, veta2[0], ppsys2[0], 5, 1001, 1);
            drawSysTGraph(graph, veta2[0], RpPbsys2[0], colorCode[0], 0, 1);
            graph->Draw("psameez");
            TGraphErrors *graph2 = new TGraphErrors(N,veta2[1],vRpPb2[1],0,RpPbstat2[1]);
            graph2->SetTitle("gr2");
            graph2->SetMarkerStyle(20);
            graph2->SetMarkerColor(1);
            graph2->SetLineColor(1);
            graph2->SetMarkerSize(1.5);
            graph2->SetLineWidth(1);
            drawSysTGraph(graph2, veta2[1], ppsys2[1], kGreen-6, 1001, 1);
            drawSysTGraph(graph2, veta2[1], RpPbsys2[1], colorCode[1], 0, 2);
            graph2->SetMarkerSize(1.5);
            graph2->Draw("psameez");
            TGraphErrors *graph3 = new TGraphErrors(N,veta2[2],vRpPb2[2],0,RpPbstat2[2]);
            graph3->SetTitle("gr3");
            graph3->SetMarkerStyle(27);
            graph3->SetMarkerColor(4);
            graph3->SetLineColor(4);
            graph3->SetLineWidth(2);
            graph3->SetMarkerSize(1.5);
            drawSysTGraph(graph3, veta2[2], ppsys2[2], 7, 1001, 1);
            drawSysTGraph(graph3, veta2[2], RpPbsys2[2], colorCode[2], 0, 3);
            graph3->Draw("psameez");
            
            regSun(-2.3.,1.,2.3.,1.,1, 1);
            
            TLegend *leg0 = new TLegend(0.45,0.25,0.64,0.4);
            leg0->SetFillColor(10);
            leg0->SetBorderSize(0.05);
            leg0->SetTextFont(43);
            leg0->SetTextSize(20.0);
            leg0->AddEntry(graph,Form("%.f < p_{T} < %.f GeV/c",jetPtBin[ptRange[0]], jetPtBin[ptRange[0]+1]) ,"P");
            leg0->AddEntry(graph2,Form("%.f < p_{T} < %.f GeV/c",jetPtBin[ptRange[1]], jetPtBin[ptRange[1]+1]),"P");
            leg0->AddEntry(graph3,Form("%.f < p_{T} < %.f GeV/c",jetPtBin[ptRange[2]], jetPtBin[ptRange[2]+1]),"P");
            //            leg0->AddEntry(graph,Form("%.f < p_{T} < %.f GeV/c",ptvalue[0], ptvalue[0+1]) ,"P");
            //            leg0->AddEntry(graph2,Form("%.f < p_{T} < %.f GeV/c",ptvalue[1], ptvalue[1+1]),"P");
            //            leg0->AddEntry(graph3,Form("%.f < p_{T} < %.f GeV/c",ptvalue[2], ptvalue[2+1]),"P");
            leg0->Draw();
            
            break ;
        case kCompATLAS:
            c1->cd();
            c1->cd()->SetLogx();
            hDum->SetMinimum(0.);
            hDum->SetMaximum(2.);
   //         hDum->SetAxisRange(45., 150., "X");
            hDum->SetAxisRange(45., 600., "X");
            hhdum->GetYaxis()->SetTitle("R_{pPb}^{PYTHIA}");
            hDum->Draw();
            drawCMS(0.20,0.9,Lumi);
            drawText(Form("CMS: jet R = 0.3, Interpolated pp"),0.4,0.82,20);
//            drawText(Form("CMS: jet R = 0.3, PYTHIA AMBT2"),0.4,0.82,18);
            drawText(Form("ATLAS: jet R = 0.4, PYTHIA AMBT2"),0.4,0.77,20);
    //        drawText(Form("ALICE: jet R = 0.4, Interpolation"),0.4,0.77,18);
            
            PARatio[3]->SetMarkerStyle(20);
            PARatio[3]->SetMarkerColor(1);
            PARatio[3]->SetMarkerSize(1.5);
            PARatio[3]->SetLineColor(1);

            double ATLASpointx[7] = {112.,141.,178.,224.,284.,356.,448.};
            double ATLASpointy[7] = {1.136,1.154,1.205,1.197,1.224,1.195,1.457};
            double ex[7] = {8.,9.,13.,16.,18.,26.,32.};
            double sysmeticy[7] = {0.086,0.08,0.082,0.083,0.087,0.09,0.11};
            
            TGraphErrors * atlas = new TGraphErrors(7,ATLASpointx,ATLASpointy,ex,sysmeticy);
            atlas->SetMarkerStyle(24);
            atlas->SetMarkerSize(1.5);
            atlas->SetMarkerColor(kRed);
            atlas->SetLineColor(kRed);
            atlas->SetFillColor(kGray);
            atlas->SetFillColor(0);
            atlas->Draw("psameez");
            
            PARatio[3]->DrawCopy("same");
            drawSys(PARatio[3], ptboundary[3], ptCen[3], sys[3], 5, 1001, 1);
            t3->AddEntry(PARatio[3],"CMS (0-100%):-0.5<#eta_{CM}<+0.5","P");
//            t3->AddEntry(PARatio[3],"CMS (0-100%):-0.3<#eta_{CM}<+0.3","P");
            t3->AddEntry(atlas,"ATLAS(0-90%): -0.3<y*<+0.3","P");
 //           t3->AddEntry(atlas,"ALICE: |#eta|<+0.5","P");
            t3->Draw("same");
//            regSun(45.,1.,150.,1.,1, 1);
            regSun(45.,1.,510.,1.,1, 1);

  
//            for(int ieta = 0 ; ieta <=netabin; ieta++){
//                if(ieta==netabin)
//                    //    drawSys(PARatio[ieta], ptCen, sys, 16, 3003, 1);
//                    drawSys(PARatio[ieta], ptCen, sys, 5, 3003, 1);
//                PARatio[ieta]->SetMarkerStyle(markerCode[ieta]);
//                PARatio[ieta]->SetMarkerColor(colorCode[ieta]);
//                PARatio[ieta]->SetMarkerSize(1.5);
//                PARatio[ieta]->SetLineColor(colorCode[ieta]);
//                if(ieta==netabin) PARatio[ieta]->DrawCopy("same");
//                    regSun(20.,1.,1000.,1.,1, 1);
//                if(ieta==netabin)
//                    t2->AddEntry(PARatio[ieta], Form("%.1f < #eta_{CM} < %.1f", -1.0, 1.0),"P");
//               if(ieta==3)
//                    t2->AddEntry(PARatio[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[netabin-ieta-1],deta[netabin-ieta]),"P");
////                    t2->AddEntry(PARatio[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[netabin-ieta-1],deta[netabin-ieta]),"P");
//                //            t2->AddEntry(PARatio[ieta], Form("%.1f < #eta_{CM} < %.1f", deta[ieta],deta[ieta+1]),"P");
//               if(ieta==netabin || ieta==3) t2->Draw("same");
//            }
            PARatio[3]->DrawCopy("same");
            atlas->Draw("psameez");

            TBox *box = new TBox(500-4.5,1.0-0.035,500+4.5,1.0+0.035);
            box->SetFillColor(kBlue-7);
            box->SetFillStyle(-1);
            box->Draw();

            break ;
    }
    
    if(SavePlot)c1->Print(Form("%s/%s%sIncJet%s%s%s%sInterpolatedRefEtaBin%d6panelE.gif", plotsdir.Data(), val.Data(), algo.Data(),residual.Data(), ana.Data(), widebin.Data(), dep.Data(),netabin));
    if(SavePlot)c1->Print(Form("%s/%s%sIncJet%s%s%s%sInterpolatedRefEtaBin%d6panelE.C", plotsdir.Data(), val.Data(), algo.Data(),residual.Data(), ana.Data(), widebin.Data(), dep.Data(),netabin));
    if(SavePlot)c1->Print(Form("%s/%s%sIncJet%s%s%s%sInterpolatedRefEtaBin%d6panelE.pdf", plotsdir.Data(), val.Data(), algo.Data(),residual.Data(), ana.Data(), widebin.Data(), dep.Data(),netabin));
    c1->Update();



}

TH1 * normalizeByBinWidth(TH1 *histo) {
    for(int i = 1; i <= histo->GetNbinsX(); i++) {
        float content = histo->GetBinContent(i);
        float error = histo->GetBinError(i);
        histo->SetBinContent(i,content/histo->GetBinWidth(i));
        histo->SetBinError(i,error/histo->GetBinWidth(i));
    }
    return histo ;
}
TH1 * convertToInvYield(TH1 *hist) {
    for(int i = 1; i<=hist->GetNbinsX(); i++) {
        double content = hist->GetBinContent(i);
        double pt = hist->GetBinCenter(i);
        double error = hist->GetBinError(i);
        
        double new_content = content/(2.*TMath::Pi()*pt);
        double new_error = error/(2.*TMath::Pi()*pt);
        
        hist->SetBinContent(i,new_content);
        hist->SetBinError(i,new_error);
    }
    return hist ;
}
void regSun(double x1=0,double y1=0,double x2=1,double y2=1,int color=1, double width=1)
{
    TLine* t1 = new TLine(x1,y1,x2,y2);
    t1->SetLineWidth(width);
    t1->SetLineStyle(3);
    t1->SetLineColor(color);
    t1->Draw();
}
//---------------------------------------------------
void drawText(const char *text, float xp, float yp, int textSize=20){
    TLatex *tex = new TLatex(xp,yp,text);
    tex->SetTextFont(43);
 //   tex->SetTextSize(20);
    tex->SetTextSize(textSize);
  //  tex->SetTextSize(0.05);
    tex->SetTextColor(kBlack);
    tex->SetLineWidth(1);
    tex->SetNDC();
    tex->Draw();
}
void drawSys(TH1 * h, double limit, double *ptCen, double *sys, int theColor= kYellow, int fillStyle = -1, int lineStyle = -1)
{
    for (int i=0;i<nJetPtBin;i++)
    {
        double val;
        double theX;
        if(ptCen[i]<ptmin) continue ;
        if(ptCen[i]>limit) continue ;
        int ibin = h->FindBin(ptCen[i]);
        val = h->GetBinContent(ibin);
        theX = h->GetBinCenter(ibin);
        double err = val * sys[i]/100;
        double width = (h->GetBinLowEdge(ibin+1)-h->GetBinLowEdge(ibin))/2. ;
//        TBox *b = new TBox(theX-width,val-err,theX+width,val+err);
 //       if(width<50.)
 //           TBox *b = new TBox(theX-width*0.4,val-err,theX+width*0.4,val+err);
//        else
        if(theX<75)TBox *b = new TBox(theX-4,val-err,theX+4,val+err);
        else if(theX<120)TBox *b = new TBox(theX-5,val-err,theX+5,val+err);
        else if(theX<180) TBox *b = new TBox(theX-8,val-err,theX+8,val+err);
        else TBox *b = new TBox(theX-10,val-err,theX+10,val+err);
//        TBox *b = new TBox(theX-theX*0.03,val-err,theX+theX*0.03,val+err);
        //if(lineStyle==6)TBox *b = new TBox(theX-theX*0.055,val-err,theX+theX*0.055,val+err);
        //else if (lineStyle==3)TBox *b = new TBox(theX-theX*0.04,val-err,theX+theX*0.04,val+err);
        //else if (lineStyle==0)TBox *b = new TBox(theX-theX*0.025,val-err,theX+theX*0.025,val+err);
        
        b->SetLineColor(theColor);
        if ( fillStyle > -1 )b->SetFillColor(theColor);
        //if ( fillStyle > -1 ) b->SetFillStyle(fillStyle);
        //if ( lineStyle > -1 ) b->SetLineStyle(lineStyle);
        if ( lineStyle > -1 ) b->SetLineStyle(1);
        if ( lineStyle > -1 ) b->SetLineWidth(2);
        
        b->Draw();
        
    }

}

void drawSysTGraph(TGraph * h, double *ptCen, double *sys, int theColor= kYellow, int fillStyle = -1, int lineStyle = -1)
{
    double val[100];
    double theX[100];
    for (int i=0;i<h->GetN();i++)
    {
        h->GetPoint(i, theX[i], val[i]);
         double err = val[i] * sys[i]/100;
    //    double width = (h->GetBinLowEdge(ibin+1)-h->GetBinLowEdge(ibin))/2. ;
        //        TBox *b = new TBox(theX-width,val-err,theX+width,val+err);
//        if(width<10.)  TBox *b = new TBox(theX-width,val-err,theX+width,val+err);
//        else
            TBox *b = new TBox(theX[i]-0.05,val-err,theX+0.05,val+err);
        
        b->SetLineColor(theColor);
        if ( fillStyle > -1 )b->SetFillColor(theColor);
        if ( fillStyle > -1 ) b->SetFillStyle(fillStyle);
        if ( lineStyle > -1 ) b->SetLineStyle(lineStyle);
        if ( lineStyle > -1 ) b->SetLineWidth(2);
        
        b->Draw();
        
    }
    
}
void drawCMS(float px, float py, float nLumi) {
    TLatex *cms = new TLatex(px,py,"CMS Preliminary");
    cms->SetTextFont(43);
    cms->SetTextSize(20);
    cms->SetNDC();
 //   cms->Draw();
    //TLatex *lumi = new TLatex(px-0.02,py-0.05,Form("#intL dt = %.0f nb^{-1}",nLumi));
    TLatex *lumi = new TLatex(px-0.02,py-0.05,Form("L_{int} = %.0f nb^{-1}",nLumi));
//    TLatex *lumi = new TLatex(px-0.02,py-0.05,Form("pPb, #intL dt = %.0f nb^{-1}",nLumi));
//    TLatex *lumi = new TLatex(px,py-0.05,Form("PYTHIA 6: Z2"));
    lumi->SetTextFont(43);
    lumi->SetTextSize(20);
    lumi->SetNDC();
    lumi->Draw();
}

void drawCMSpp(float px, float py, float nLumi) {
    TLatex *cms = new TLatex(px,py,"CMS Preliminary");
    cms->SetTextFont(43);
    cms->SetTextSize(20);
    cms->SetNDC();
    //    cms->Draw();
    //TLatex *lumi = new TLatex(px,py-0.05,Form("pp, #intL dt = %.1f pb^{-1}",nLumi));
    TLatex *lumi = new TLatex(px,py-0.05,Form("pp, L_{int} = %.1f pb^{-1}",nLumi));
    //    TLatex *lumi = new TLatex(px,py-0.05,Form("#intL dt = %.1f nb^{-1}",nLumi));
    lumi->SetTextFont(43);
    lumi->SetTextSize(20);
    lumi->SetNDC();
    lumi->Draw();
}

void drawCMSmc(float px, float py) {
    TLatex *cms = new TLatex(px,py,"CMS Preliminary");
    cms->SetTextFont(43);
    cms->SetTextSize(20);
    cms->SetNDC();
    cms->Draw();
    TLatex *lumi = new TLatex(px,py-0.05,Form("PYTHIA+HIJING"));
    //    TLatex *lumi = new TLatex(px,py-0.05,Form("PYTHIA 6: Z2"));
    lumi->SetTextFont(43);
    lumi->SetTextSize(10);
    lumi->SetNDC();
    lumi->Draw();
}

void removeZero(TH1 *h)
{
    double min = 0;
    for (int i=1;i<h->GetNbinsX();i++)
    {
        if (h->GetBinContent(i)>min&&h->GetBinContent(i)>0) min=h->GetBinContent(i);
    }
    for (int i=1;i<h->GetNbinsX();i++)
    {
        if (h->GetBinContent(i)==0) {
            h->SetBinContent(i,min/1.e99);
            h->SetBinError(i,min/1.e99);
        }
    }
}

void findptbinfactor(double pt){
if(pt<75) return 4;
else if(pt<120) return 5;
else if(pt<180) return 8;
else return 10;
}



