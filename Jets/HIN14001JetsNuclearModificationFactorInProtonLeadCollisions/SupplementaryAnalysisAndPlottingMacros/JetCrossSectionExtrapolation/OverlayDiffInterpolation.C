/*
 *  Perform data && MC (PYTHIA Z2) comparison for 7TeV pp collisions, data points reading from HepData below
 *  http://hepdata.cedar.ac.uk/view/ins902309
 *  http://hepdata.cedar.ac.uk/view/ins1208923
 *
 *  Created by Yaxian Mao on 04/12/14.
 *  Copyright 2014 Vanderbilt University (US). All rights reserved.
 *
 */

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
#include "TGraph.h"
#include <iostream>
#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <iomanip>
#include "TGraphAsymmErrors.h"
using namespace std;

bool SavePlot = kFALSE ;
const bool SaveFile = kTRUE ;

void OverlayDiffInterpolation(int current = 0)
{
  TString InputDir = "/Users/tuos/Dropbox/RpPbPredictions/hin14001/extrapolation/v1/plot";
    TString plotsdir = "/Users/tuos/Dropbox/RpPbPredictions/hin14001/extrapolation/v1/plot";

  TFile *f1 = new TFile(Form("R3_ScaleFactor7000TeVto5TeVStartingCone5Sys.root"));//2.76TeV
  TFile *f2 = new TFile(Form("R3_ScaleFactor7000TeVto5TeVStartingCone5SysUp.root"));//5.02TeV
  TFile *f3 = new TFile(Form("R3_ScaleFactor7000TeVto5TeVStartingCone7Sys.root"));//7.00TeV
//    TFile *f4 = new TFile(Form("R3_ScaleFactor7TeVto5TeVStartingCone7SysUp.root"));//7.00TeV
    TFile *f4 = new TFile(Form("R3_ScaleFactor7000TeVto5TeVStartingCone5SysDown.root"));//7.00TeV
    
    TFile *f5 = new TFile(Form("/Users/tuos/Dropbox/RpPbPredictions/hin14001/extrapolation/v1/plot/R3_ScaleFactor2760GeVto5TeV.root"));//7.00TeV
    
    const double deta[]={0., 0.5, 1.0, 1.5, 2.0, 2.5} ;
    int netabin = sizeof(deta)/sizeof(Double_t)-1 ;
    const int N  = netabin ;

    char *dirname[N] = {
        "Interpolated5TeVak3PFJetAbsRapidity0_5", "Interpolated5TeVak3PFJetAbsRapidity5_10", "Interpolated5TeVak3PFJetAbsRapidity10_15", "Interpolated5TeVak3PFJetAbsRapidity15_20", "Interpolated5TeVak3PFJetAbsRapidity20_25"};
    char *dirname2760[N] = {
        "hratio_5020_2760_pp_2013_2760_abs_rap_05_data_unfo_ak3PF", "hratio_5020_2760_pp_2013_2760_abs_rap_05_10_data_unfo_ak3PF",
        "hratio_5020_2760_pp_2013_2760_abs_rap_10_15_data_unfo_ak3PF", "hratio_5020_2760_pp_2013_2760_abs_rap_15_20_data_unfo_ak3PF",
        "hratio_5020_2760_pp_2013_2760_abs_rap_20_25_data_unfo_ak3PF"};
    
    int colorCode[N] = {
        1,2,4,2,1
    };
    int markerCode[N] = {
        20,34,33,24,27
    };
    int lineCode[N] = {
        1, 2, 3, 4, 5
    };
    double scalepower[N]={4, 3, 2, 1, 0};
    double scalef[N];
    
    for(int j=0; j<netabin; j++) scalef[j]=pow(10.0, scalepower[j]);
    
    TGraphErrors * jet5TeVR5[N];
    TGraphErrors * jet5TeVR5Sys[N];
    TGraphErrors * jet5TeVR7[N];
    TGraphErrors * jet5TeVR7Sys[N];
    TH1F * jet2760GeVR3[N];

    for(int ieta=0; ieta<N; ieta++)
    {
        jet5TeVR5[ieta] = (TGraphErrors*)f1->Get(Form("%s", dirname[ieta]));
        jet5TeVR5Sys[ieta] = (TGraphErrors*)f2->Get(Form("%s", dirname[ieta]));
        jet5TeVR7[ieta] = (TGraphErrors*)f3->Get(Form("%s", dirname[ieta]));
        jet5TeVR7Sys[ieta] = (TGraphErrors*)f4->Get(Form("%s", dirname[ieta]));
        
        jet2760GeVR3[ieta] = (TH1F*)f5->Get(Form("%s", dirname[ieta]));
        jet2760GeVR3[ieta]->Scale(1./1.e3);
        jet2760GeVR3[ieta]->Scale(1./0.5);
        
    }
    
    if(SaveFile){
        TFile * outf = new TFile(Form("/Users/tuos/Dropbox/RpPbPredictions/hin14001/extrapolation/v1/plot/ExtrapolatedPPDiffInput.root"), "RECREATE");
        //        TFile * outf = new TFile(Form("%s/ppMCGenNoWeightForKurt.root", kHomeDir), "UPDATE");
        for(int ieta = 0 ; ieta <netabin; ieta++){
            jet5TeVR5[ieta]->Write(Form("7TeVR5InputEtaBin_%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
            jet5TeVR7[ieta]->Write(Form("7TeVR7Input_%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
            jet2760GeVR3[ieta]->Write(Form("2760GeVR3Input_%.f_%.f", deta[ieta]*10, deta[ieta+1]*10));
        }
        outf->Close();
 
    }

    Double_t x[100],x2[100], x3[100], x4[100], y[100], yup[100], ylow[100], y7[100];

    int ieta = current ;

    int np = jet5TeVR5[current]->GetN() ;
    int np7 = jet5TeVR7[current]->GetN() ;
    cout << "np" <<np <<endl ;
    
    for(int j = 0 ; j < 33 ; j++) {
        jet5TeVR5[current]->GetPoint(j, x[j], y[j]);
    //    cout <<"jet5TeVR5[current] =" << jet5TeVR5[current]<<endl ;
        cout << " y = " << y[j]<< endl ;
        jet5TeVR5Sys[current]->GetPoint(j, x2[j], yup[j]);
        jet5TeVR7Sys[current]->GetPoint(j, x3[j], ylow[j]);
    }
    
    for(int j = 0 ; j < np7 ; j++) {
        jet5TeVR7[current]->GetPoint(j, x4[j], y7[j]);
     }

    const int Npt = np ;
    
    Double_t up[100];
    Double_t down[100] ;
    TGraph * ratioUp ;
    TGraph * ratioLow;
    for(int ip = 0 ; ip < Npt ; ip++){
        cout <<" yup ==" <<yup[ip] <<"  y" << y[ip] <<endl ;
        up[ip]=yup[ip]/y[ip];
        down[ip]=ylow[ip]/y[ip];
        
    }

    ratioUp = new TGraph(Npt, x, up);
    ratioLow = new TGraph(Npt, x, down);
    
////////////////// 
    TGraphErrors *jet2760GeVR3Sys[N];
    double ptx[N][Npt], crossSectiony[N][Npt], crossSectionyerr[N][Npt];
    for(int j=0; j<netabin; j++) {
      for(int ip = 0 ; ip < Npt ; ip++){
        //ptx[j][ip] = jet2760GeVR3[j]->FindBin(x[ip]);
        ptx[j][ip] = jet2760GeVR3[j]->GetBinCenter(jet2760GeVR3[j]->FindBin(x[ip]));
        crossSectiony[j][ip] = jet2760GeVR3[j]->GetBinContent(jet2760GeVR3[j]->FindBin(x[ip]));
        crossSectionyerr[j][ip] = jet2760GeVR3[j]->GetBinError(jet2760GeVR3[j]->FindBin(x[ip]));
        if(crossSectiony[j][ip]==0) crossSectionyerr[j][ip]=0;
        cout<<"eta= "<<j<<", ptx= "<<ptx[j][ip]<<",  y= "<<crossSectiony[j][ip]<<", yerr= "<<crossSectionyerr[j][ip]<<endl;
      }
      jet2760GeVR3Sys[j]= new TGraphErrors(Npt, ptx[j], crossSectiony[j], 0, crossSectionyerr[j]);
      jet2760GeVR3Sys[j]->SetName(dirname[j]);
    }
   TFile *out2769file = new TFile("R3_ScaleFactor2760GeVto5TeVTGraphErrors.root","recreate");
   out2769file->cd();
   for(int j=0; j<netabin; j++) jet2760GeVR3Sys[j]->Write();
   out2769file->Close();
/////////////////

    TGraph * DiffCone ;
    TGraph * DiffSqrt;
    int Npoint7TeV;
    Double_t RatioR[100],RatioColl[100];

    for(int ip = 0 ; ip < Npt ; ip++){
        int binR7 = jet2760GeVR3[current]->FindBin(x[ip]);
        double centerR7 = jet2760GeVR3[current]->GetBinContent(binR7);
        if(y[ip]){
            RatioColl[ip]=centerR7/y[ip];
        }
        else RatioColl[ip]=0.;
        cout << "2.76TeV =" << centerR7 << ", x= "<<x[ip]<<", y= "<<y[ip] << ", ratio = "<< RatioColl[ip]<<endl;

//        int ibin = 0 ;
//        for(int ip7 = 0 ; ip7 < np7 ; ip7++){
//            if(x4[ip7]>=x[ip] && x4[ip7]<x[ip+1]) ibin = ip7 ;
//        }
//        if(ibin>=0 && y[ip]) RatioR[ip] = y7[ibin]/y[ip];
//        else RatioR[ip] = 0;
//        cout << "R7 =" << y7[ibin] << " ::5TeV ="<<y[ip] << " :Cone ="<< RatioR[ip]<<endl;
//
    }
   
    for(int ip = 0 ; ip < Npt ; ip++){
        int ibin = 0 ;
        //for(int ip = 0 ; ip < Npt ; ip++){
        //    if(x4[ip]>=x[ip] && x4[ip]<x[ip+1]) ibin = ip ;
        //}
        //   if(ibin>=0 && y[ip]) RatioR[ip] = y7[ibin]/y[ip];
        //   else RatioR[ip] = 0;
           if(y[ip]>0) RatioR[ip] = y7[ip]/y[ip];
           else RatioR[ip] = 0;
        cout << "y7 = " << y7[ip] << " y ="<<y[ip] << " ratio ="<< RatioR[ip]<<endl;

    }

    DiffCone = new TGraph(Npt, x, RatioR);
    DiffSqrt = new TGraph(Npt, x, RatioColl);

    
    if(SaveFile){
        ofstream myfile;
        myfile << fixed << setprecision(5);
        myfile.open(Form("/Users/tuos/Dropbox/RpPbPredictions/hin14001/extrapolation/v1/plot/ppReferenceFrom7TeVR5SysEtaBin%.f_%.f.txt", deta[current]*10, deta[current+1]*10));
      for(int ip = 0 ; ip < Npt ; ip++){
          cout <<"pt  =" <<  x[ip]<<"sys =" <<(TMath::Abs(up[ip]-1)+TMath::Abs(down[ip]-1))/2.*100<<endl;
                myfile << x[ip]  <<" \t "<< (TMath::Abs(up[ip]-1)+TMath::Abs(down[ip]-1))/2.*100 <<" \t " <<"\n";
            
        }
        myfile.close();

    }
    TCanvas *c1 = new TCanvas("c1a", "c1",0,0,600,600);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    c1->Range(0,0,1,1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    //c1->SetLogy();
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->SetLeftMargin(0.13);
    c1->SetRightMargin(0.06);
    c1->SetTopMargin(0.05);
    c1->SetBottomMargin(0.16);
    c1->SetFrameFillStyle(0);
    c1->SetFrameBorderMode(0);
    gStyle->SetOptStat(0);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadTopMargin   (0.025);
    gStyle->SetPadLeftMargin  (0.15);
    gStyle->SetPadRightMargin (0.025);
    gStyle->SetPadTickX       (1);
    gStyle->SetPadTickY       (1);
    
    
    //   TLegend *t1=new TLegend(0.45,0.6,0.8,0.92);
    TLegend *t1=new TLegend(0.35,0.7,0.8,0.85);
    t1->SetFillColor(0);
    t1->SetBorderSize(0);
    t1->SetFillStyle(0);
    t1->SetTextFont(63);
    t1->SetTextSize(24);

    TCanvas *c2 = new TCanvas("c2a", "c2",0,0,600,600);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    c2->Range(0,0,1,1);
    c2->SetFillColor(0);
    c2->SetBorderMode(0);
    c2->SetBorderSize(2);
    //c1->SetLogy();
    c2->SetTickx(1);
    c2->SetTicky(1);
    c2->SetLeftMargin(0.13);
    c2->SetRightMargin(0.06);
    c2->SetTopMargin(0.05);
    c2->SetBottomMargin(0.16);
    c2->SetFrameFillStyle(0);
    c2->SetFrameBorderMode(0);

    TCanvas *c3 = new TCanvas("c3a", "c3",0,0,600,600);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    c3->Range(0,0,1,1);
    c3->SetFillColor(0);
    c3->SetBorderMode(0);
    c3->SetBorderSize(2);
    //c1->SetLogy();
    c3->SetTickx(1);
    c3->SetTicky(1);
    c3->SetLeftMargin(0.13);
    c3->SetRightMargin(0.06);
    c3->SetTopMargin(0.05);
    c3->SetBottomMargin(0.16);
    c3->SetFrameFillStyle(0);
    c3->SetFrameBorderMode(0);

    TLegend *t2=new TLegend(0.15,0.18,0.35,0.35);
    t2->SetFillColor(0);
    t2->SetBorderSize(0);
    t2->SetFillStyle(0);
    t2->SetTextFont(63);
    t2->SetTextSize(24);

    TLegend *t3=new TLegend(0.15,0.18,0.35,0.35);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(63);
    t3->SetTextSize(24);

    TH1F * hDum = new TH1F("hhdum","",2000,0., 2000.);
          hDum->SetAxisRange(50., 1500., "X");
    hDum->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    //    hDum->GetXaxis()->SetRangeUser(20., 600.);
    hDum->GetXaxis()->SetTitleSize(0.035);
    hDum->GetXaxis()->SetTitleOffset(1.5);
    hDum->GetXaxis()->SetLabelSize(0.035);
    hDum->GetYaxis()->SetTitleSize(0.035);
    hDum->GetYaxis()->SetLabelSize(0.035);
    hDum->GetYaxis()->SetTitleOffset(1.5);
    hDum->GetXaxis()->CenterTitle();
    hDum->GetYaxis()->CenterTitle();
    
    c1->cd();
    c1->SetLogy();
    c1->SetLogx();
    //    hDum->SetAxisRange(20., 600., "X");
    hDum->SetMinimum(1.e-15);
    hDum->SetMaximum(2.e-1);
    
    hhdum->GetYaxis()->SetTitle("d^{2}#sigma/dp_{T}dy (pb)");
    hDum->DrawCopy();

    drawText(Form("Interpolated from pp data"),0.2,0.9,18);

    drawText(Form("Interpolated jet spectra in pp #sqrt{s} = 5.02 TeV"),0.2,0.85,18);

    drawText(Form("anti-k_{T} PF jet: R = 0.3"),0.2,0.25,18);
    if(current==0) drawText(Form("|y| < %.1f ", deta[current+1]),0.2,0.3,18);
    else drawText(Form("%.1f < |y| < %.1f", deta[current],deta[current+1]),0.2,0.3,18);

    
    jet5TeVR5[ieta]->SetMarkerStyle(20);
    jet5TeVR5[ieta]->SetMarkerColor(1);
    jet5TeVR5[ieta]->SetMarkerSize(1.5);
    jet5TeVR5[ieta]->SetLineColor(1);
    jet5TeVR5[ieta]->Draw("same PE");

    jet5TeVR7[ieta]->SetMarkerStyle(27);
    jet5TeVR7[ieta]->SetMarkerColor(7);
    jet5TeVR7[ieta]->SetMarkerSize(1.5);
    jet5TeVR7[ieta]->SetLineColor(7);
    jet5TeVR7[ieta]->Draw("same PE");


    jet2760GeVR3[ieta]->SetMarkerStyle(34);
    jet2760GeVR3[ieta]->SetMarkerColor(2);
    jet2760GeVR3[ieta]->SetMarkerSize(1.5);
    jet2760GeVR3[ieta]->SetLineColor(2);
    jet2760GeVR3[ieta]->Draw("same PE");

    jet5TeVR5Sys[ieta]->SetMarkerStyle(33);
    jet5TeVR5Sys[ieta]->SetMarkerColor(4);
    jet5TeVR5Sys[ieta]->SetMarkerSize(1.5);
    jet5TeVR5Sys[ieta]->SetLineColor(4);
//    jet5TeVR5Sys[ieta]->Draw("same PE");
    
    jet5TeVR7Sys[ieta]->SetMarkerStyle(34);
    jet5TeVR7Sys[ieta]->SetMarkerColor(2);
    jet5TeVR7Sys[ieta]->SetMarkerSize(1.5);
    jet5TeVR7Sys[ieta]->SetLineColor(2);
//    jet5TeVR7Sys[ieta]->Draw("same PE");
    
    t1->AddEntry(jet2760GeVR3[ieta], "From HIN-13-005: R = 0.3","PE");
    t1->AddEntry(jet5TeVR5[ieta], "From QCD-10-011: R=0.5", "PE");
//    t1->AddEntry(jet5TeVR5Sys[ieta], "QCD-10-011 Upper Sys","PE");
//    t1->AddEntry(jet5TeVR7Sys[ieta], "QCD-11-004 Down Sys","PE");
    t1->AddEntry(jet5TeVR7[ieta], "From QCD-11-004: R=0.7","PE");

    t1->Draw("same");

    if(SavePlot)c1->Print(Form("%s/InterpolatedSpectDiffCollision.pdf", plotsdir.Data()));
    c1->Update();
    
    c2->cd();
    c2->SetLogx();
    hhdum->GetYaxis()->SetTitle("Up(Down/Norminal)");
    hDum->SetMinimum(0.);
    hDum->SetMaximum(2.);
    
    hDum->DrawCopy();
    drawText(Form("anti-k_{T} PF jet: R = 0.3"),0.2,0.85,18);
    
    
    //    int ieta = current ;
        ratioUp->SetMarkerStyle(33);
        ratioUp->SetMarkerColor(4);
        ratioUp->SetMarkerSize(1.5);
        ratioUp->SetLineColor(4);
        ratioUp->Draw("same PE");
    ratioLow->SetMarkerStyle(34);
    ratioLow->SetMarkerColor(2);
    ratioLow->SetMarkerSize(1.5);
    ratioLow->SetLineColor(2);
    ratioLow->Draw("same PE");
    
    if(current==0)
        t2->AddEntry(ratioUp, Form("|y| < %.1f ", deta[ieta+1]),"");
        else
            t2->AddEntry(ratioUp, Form("%.1f < |y| < %.1f ", deta[ieta],deta[ieta+1]),"PL");
    t2->AddEntry(ratioUp, "QCD-10-011 UpperLimit/Norminal","PL");
    t2->AddEntry(ratioLow, "QCD-10-011 LowerLimit/Norminal","PL");

        t2->Draw("same");
    
    regSun(50.,1.,1200.,1.,1, 1);
    
    if(SavePlot)c2->Print(Form("%s/pp7TeVSysErrInterpolationDiff.pdf", plotsdir.Data(),sqrt));

    c3->cd();
    c3->SetLogx();
    hhdum->GetYaxis()->SetTitle("Ratio");
    hDum->SetMinimum(0.);
    hDum->SetMaximum(2.);
    
    hDum->DrawCopy();
    drawText(Form("anti-k_{T} PF jet: R = 0.3"),0.2,0.85,18);
    
    
    //    int ieta = current ;
    DiffSqrt->SetMarkerStyle(33);
    DiffSqrt->SetMarkerColor(4);
    DiffSqrt->SetMarkerSize(1.5);
    DiffSqrt->SetLineColor(4);
    DiffSqrt->Draw("same PE");
    DiffCone->SetMarkerStyle(34);
    DiffCone->SetMarkerColor(2);
    DiffCone->SetMarkerSize(1.5);
    DiffCone->SetLineColor(2);
    DiffCone->Draw("same PE");
    
    if(current==0)
        t3->AddEntry(ratioUp, Form("|y| < %.1f ", deta[ieta+1]),"");
    else
        t3->AddEntry(ratioUp, Form("%.1f < |y| < %.1f ", deta[ieta],deta[ieta+1]),"PL");
    t3->AddEntry(DiffCone, "7 TeV extrapolation: R = 0.5 /R = 0.7","PL");
    t3->AddEntry(DiffSqrt, " 7 TeV and 2.76 TeC extrapolation","PL");
    
    t3->Draw("same");
    
    regSun(50.,1.,1200.,1.,1, 1);
    
    if(SavePlot)c3->Print(Form("%s/InterpolationDifferenceDiffInput.pdf", plotsdir.Data(),sqrt));

}

//---------------------------------------------------
void drawText(const char *text, float xp, float yp, int textSize=15){
    TLatex *tex = new TLatex(xp,yp,text);
    tex->SetTextFont(63);
    //tex->SetTextSize(20);
    tex->SetTextSize(textSize);
    //tex->SetTextSize(0.05);
    tex->SetTextColor(kBlack);
    tex->SetLineWidth(1);
    tex->SetNDC();
    tex->Draw();
}
void drawText2(const char *text, float xp, float yp, int textSize=15){
    TLatex *tex = new TLatex(xp,yp,text);
    tex->SetTextFont(63);
    tex->SetTextSize(textSize);
    //    tex->SetTextColor(kBlack);
    tex->SetTextColor(kRed);
    tex->SetLineWidth(1);
    tex->SetNDC();
    tex->Draw();
}

void makeMultiPanelCanvas(TCanvas*& canv,
                          const Int_t columns,
                          const Int_t rows,
                          const Float_t leftOffset,
                          const Float_t bottomOffset,
                          const Float_t leftMargin,
                          const Float_t bottomMargin,
                          const Float_t edge) {
    if (canv==0) {
        Error("makeMultiPanelCanvas","Got null canvas.");
        return;
    }
    canv->Clear();
    
    TPad* pad[columns][rows];
    
    Float_t Xlow[columns];
    Float_t Xup[columns];
    Float_t Ylow[rows];
    Float_t Yup[rows];
    Float_t PadWidth =
    (1.0-leftOffset)/((1.0/(1.0-leftMargin)) +
                      (1.0/(1.0-edge))+(Float_t)columns-2.0);
    Float_t PadHeight =
    (1.0-bottomOffset)/((1.0/(1.0-bottomMargin)) +
                        (1.0/(1.0-edge))+(Float_t)rows-2.0);
    Xlow[0] = leftOffset;
    Xup[0] = leftOffset + PadWidth/(1.0-leftMargin);
    Xup[columns-1] = 1;
    Xlow[columns-1] = 1.0-PadWidth/(1.0-edge);
    
    Yup[0] = 1;
    Ylow[0] = 1.0-PadHeight/(1.0-edge);
    Ylow[rows-1] = bottomOffset;
    Yup[rows-1] = bottomOffset + PadHeight/(1.0-bottomMargin);
    
    for(Int_t i=1;i<columns-1;i++) {
        Xlow[i] = Xup[0] + (i-1)*PadWidth;
        Xup[i] = Xup[0] + (i)*PadWidth;
    }
    Int_t ct = 0;
    for(Int_t i=rows-2;i>0;i--) {
        Ylow[i] = Yup[rows-1] + ct*PadHeight;
        Yup[i] = Yup[rows-1] + (ct+1)*PadHeight;
        ct++;
    }
    
    TString padName;
    for(Int_t i=0;i<columns;i++) {
        for(Int_t j=0;j<rows;j++) {
            canv->cd();
            padName = Form("p_%d_%d",i,j);
            pad[i][j] = new TPad(padName.Data(),padName.Data(),
                                 Xlow[i],Ylow[j],Xup[i],Yup[j]);
            if(i==0) pad[i][j]->SetLeftMargin(leftMargin);
            else pad[i][j]->SetLeftMargin(0);
            
            if(i==(columns-1)) pad[i][j]->SetRightMargin(edge);
            else pad[i][j]->SetRightMargin(0);
            
            if(j==0) pad[i][j]->SetTopMargin(edge);
            else pad[i][j]->SetTopMargin(0);
            
            if(j==(rows-1)) pad[i][j]->SetBottomMargin(bottomMargin);
            else pad[i][j]->SetBottomMargin(0);
            
            pad[i][j]->Draw();
            pad[i][j]->cd();
            pad[i][j]->SetNumber(columns*j+i+1);
        }
    }
}
void drawCMSmc(float px, float py, TString coll) {
    TLatex *cms = new TLatex(px,py,"CMS Preliminary");
    cms->SetTextFont(63);
    cms->SetTextSize(17);
    cms->SetNDC();
    cms->Draw();
    if(coll=="HI")TLatex *lumi = new TLatex(px,py-0.05,"PYTHIA+HYDJET");
    else TLatex *lumi = new TLatex(px,py-0.05,"PYTHIA");
    lumi->SetTextFont(63);
    lumi->SetTextSize(15);
    lumi->SetNDC();
    lumi->Draw();
}

void drawCMS(float px, float py, float nLumi) {
    TLatex *cms = new TLatex(px,py,"CMS Preliminary");
    cms->SetTextFont(63);
    cms->SetTextSize(17);
    cms->SetNDC();
    cms->Draw();
    TLatex *lumi = new TLatex(px,py-0.10,Form("#intL dt = %.1f #mub^{-1}",nLumi));
    lumi->SetTextFont(63);
    lumi->SetTextSize(15);
    lumi->SetNDC();
    lumi->Draw();
}

void drawCMSpp(float px, float py, float nLumi) {
    TLatex *cms = new TLatex(px,py,"CMS Preliminary");
    cms->SetTextFont(63);
    cms->SetTextSize(15);
    cms->SetNDC();
    cms->Draw();
    TLatex *lumi = new TLatex(px,py-0.05,Form("#intL dt = %.1f pb^{-1}",nLumi));
    //    TLatex *lumi = new TLatex(px,py-0.10,Form("#intL dt = %.1f nb^{-1}",nLumi));
    lumi->SetTextFont(63);
    lumi->SetTextSize(15);
    lumi->SetNDC();
    lumi->Draw();
}
void fixedFontHist(TH1 * h, Float_t xoffset=1.3, Float_t yoffset=1.2)
{
    h->SetLabelFont(43,"X");
    h->SetLabelFont(43,"Y");
    //h->SetLabelOffset(0.01);
    h->SetLabelSize(22);
    h->SetTitleFont(44);
    h->SetTitleSize(16);
    h->SetLabelSize(18,"Y");
    h->SetLabelSize(18,"X");
    h->SetTitleFont(43,"Y");
    h->SetTitleSize(22,"Y");
    h->SetTitleSize(20,"X");
    h->SetTitleOffset(xoffset,"X");
    h->SetTitleOffset(yoffset,"Y");
    h->GetXaxis()->CenterTitle();
    h->GetYaxis()->CenterTitle();
}

void drawSys(TGraph *h, double *sys, double width=5, int theColor= kYellow, int fillStyle = -1, int lineStyle = -1)
{
    for (int i=0;i<h->GetN();i++)
    {
        double val;
        double theX;
        h->GetPoint(i,theX,val);
        double err = val * sys[i]/100;
        TBox *b = new TBox(theX-width,val-err,theX+width,val+err);
        
        b->SetLineColor(theColor);
        b->SetFillColor(theColor);
        if ( fillStyle > -1 ) b->SetFillStyle(fillStyle);
        if ( lineStyle > -1 ) b->SetLineStyle(lineStyle);
        
        b->Draw();
    }
}
void onSun(double x1=0,double y1=0,double x2=1,double y2=1,int color=1, double width=1)
{
    TLine* t1 = new TLine(x1,y1,x2,y2);
    t1->SetLineWidth(width);
    t1->SetLineStyle(1);
    t1->SetLineColor(color);
    t1->Draw();
}
void regSun(double x1=0,double y1=0,double x2=1,double y2=1,int color=1, double width=1)
{
    TLine* t1 = new TLine(x1,y1,x2,y2);
    t1->SetLineWidth(width);
    t1->SetLineStyle(3);
    t1->SetLineColor(color);
    t1->Draw();
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
TH1 * normalizeByBinWidth(TH1 *histo) {
    for(int i = 1; i <= histo->GetNbinsX(); i++) {
        float content = histo->GetBinContent(i);
        float error = histo->GetBinError(i);
        histo->SetBinContent(i,content/histo->GetBinWidth(i));
        histo->SetBinError(i,error/histo->GetBinWidth(i));
    }
    return histo ;
}


