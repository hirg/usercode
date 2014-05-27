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
#include <iostream>
#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <iomanip>
using namespace std;

void fig1LumiCombinePASplots()
{
  bool SavePlots = kTRUE;
  
//================rebin for the turn on shape plots===================	
  double Jet20PtBin[] = {25,27,30,34,38,42,47,53,60,70,100,150};
  const int Jet20Nbins = sizeof(Jet20PtBin)/sizeof(double)-1;
	
  double Jet40PtBin[] = {25,26,27,28,29,30,31,32,33,34,35,36,37,40,43,47,52,57,62,67,72,77,85,110,130,150}; 
  const int Jet40Nbins = sizeof(Jet40PtBin)/sizeof(double)-1;
  
  double Jet60PtBin[] = {25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,60,63,66,70,74,78,82,86,90,95,100,110,120,135,150};
  const int Jet60Nbins = sizeof(Jet60PtBin)/sizeof(double)-1;

  double Jet80PtBin[] = {25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,77,79,81,83,85,87,90,95,102,110,120,130,140,150}; 
  const int Jet80Nbins = sizeof(Jet80PtBin)/sizeof(double)-1;

  double Jet100PtBinA[65];
  for(int i=0; i<65; i++) Jet100PtBinA[i] = 25+i;//25 to 89
  double Jet100PtBinB[14] = {91,94,97,98,104,110,115,120,125,130,135,140,145,150};

  double Jet100PtBin[79];
  for(int ibin=0; ibin<79; ibin++)
  {
    if(ibin<65) Jet100PtBin[ibin] = Jet100PtBinA[ibin];
    else  Jet100PtBin[ibin] = Jet100PtBinB[ibin-65];
  }

  const int Jet100Nbins = sizeof(Jet100PtBin)/sizeof(double)-1;
//=======================================================================

//========================Rebin For the Spectra=========================
  double Jet20RebinSpectra[] = {26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,78,82,90,100,110,120,130,140}; 
  const int Jet20RebinSpectraNbins = sizeof(Jet20RebinSpectra)/sizeof(double)-1;
  
  double Jet40RebinSpectra[] = {26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,125,130,140,150};
  const int Jet40RebinSpectraNbins = sizeof(Jet40RebinSpectra)/sizeof(double)-1;

//=====================================================================
  char JetTrig[5][256] = {"20","40","60","80","100"};
  	
  TString InputDir = "./input";
  TString PlotsDir = "./plots";
  
  TFile *f = new TFile(Form("%s/DATAPPbakPu3PFJetSpectraCombineTriggerQiaoTreeNoWeightNoJetIDCutFineBin.root",InputDir.Data())); 

  TH1F *hcombine = (TH1F *) f->Get("jetptEtaBin-10_10"); 
  
  TH1F *hjet[5];
  for(int itrig=0; itrig<5; itrig++)
  hjet[itrig] = (TH1F *) f->Get(Form("jet%sEtaBin-10_10",JetTrig[itrig]));

//========histograms for rebinning==========
  TH1F * hcombine_Rebin[5];
  hcombine_Rebin[0] = (TH1F *) hcombine->Rebin(Jet20Nbins,"rebincombine_Jet20",Jet20PtBin); 
  hcombine_Rebin[1] = (TH1F *) hcombine->Rebin(Jet40Nbins,"rebincombine_Jet40",Jet40PtBin);  
  hcombine_Rebin[2] = (TH1F *) hcombine->Rebin(Jet60Nbins,"rebincombine_Jet60",Jet60PtBin);
  hcombine_Rebin[3] = (TH1F *) hcombine->Rebin(Jet80Nbins,"rebincombine_Jet80",Jet80PtBin);
  hcombine_Rebin[4] = (TH1F *) hcombine->Rebin(Jet100Nbins,"rebincombine_Jet100",Jet100PtBin);


  TH1F *hjet_Rebin[5];
  hjet_Rebin[0] = (TH1F *) hjet[0] -> Rebin(Jet20Nbins,Form("RebinJet%s",JetTrig[0]),Jet20PtBin);
  hjet_Rebin[1] = (TH1F *) hjet[1] -> Rebin(Jet40Nbins,Form("RebinJet%s",JetTrig[1]),Jet40PtBin);
  hjet_Rebin[2] = (TH1F *) hjet[2] -> Rebin(Jet60Nbins,Form("RebinJet%s",JetTrig[2]),Jet60PtBin);
  hjet_Rebin[3] = (TH1F *) hjet[3] -> Rebin(Jet80Nbins,Form("RebinJet%s",JetTrig[3]),Jet80PtBin);
  hjet_Rebin[4] = (TH1F *) hjet[4] -> Rebin(Jet100Nbins,Form("RebinJet%s",JetTrig[4]),Jet100PtBin);

  TH1F *hjet_Rebin_Jet20 = (TH1F *) hjet[0] -> Rebin(Jet20RebinSpectraNbins,"Jet20RebinSpectra",Jet20RebinSpectra);
  normalizeByBinWidth(hjet_Rebin_Jet20);

  TH1F *hjet_Rebin_Jet40 = (TH1F *) hjet[1] -> Rebin(Jet40RebinSpectraNbins,"Jet40RebinSpectra",Jet40RebinSpectra);
  normalizeByBinWidth(hjet_Rebin_Jet40);

//================================================================
  
  double StartPoint = 25.;
  double EndPoint = 152.;

  TCanvas *c1 = new TCanvas("c1","c1",50,100,599,599);	
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  c1->Range(-38.59656,-12.02472,644.9871,2.486126);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLeftMargin(0.1552174);
  c1->SetRightMargin(0.02034783);
  c1->SetTopMargin(0.08166969);
  c1->SetBottomMargin(0.1288566);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);

  c1->cd();
  c1->cd()->SetLogy(); 
 

  TH1F *hDum1 =  new TH1F("hdum1","hdum1",13,StartPoint,EndPoint);
  hDum1->SetMinimum(1.E3);
  hDum1->SetMaximum(1.E8);
  hDum1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hDum1->GetXaxis()->SetTitleSize(0.05);
  hDum1->GetXaxis()->SetLabelSize(0.045);
  hDum1->GetXaxis()->SetTitleOffset(1.18);
  hDum1->GetXaxis()->CenterTitle();
  hDum1->GetYaxis()->SetTitle("dN_{jet}/dp_{T} [(GeV/c)^{-1}]");
  hDum1->GetYaxis()->SetTitleSize(0.05);
  hDum1->GetYaxis()->SetLabelSize(0.045);
  hDum1->GetYaxis()->SetTitleOffset(1.45);
  hDum1->GetYaxis()->CenterTitle();
  hDum1->DrawCopy();

  hjet_Rebin_Jet20->GetXaxis()->SetRangeUser(StartPoint+1,EndPoint-2);
  hjet_Rebin_Jet20->SetMarkerStyle(20);
  hjet_Rebin_Jet20->SetMarkerColor(1);
  hjet_Rebin_Jet20->SetMarkerSize(1.0);
  hjet_Rebin_Jet20->SetLineColor(1);
  hjet_Rebin_Jet20->DrawCopy("same");

  hjet_Rebin_Jet40->GetXaxis()->SetRangeUser(StartPoint+1,EndPoint-2);
  hjet_Rebin_Jet40->SetMarkerStyle(20);
  hjet_Rebin_Jet40->SetMarkerColor(2);
  hjet_Rebin_Jet40->SetMarkerSize(1.0);
  hjet_Rebin_Jet40->SetLineColor(2);
  hjet_Rebin_Jet40->DrawCopy("same");

  for(int itrig=2; itrig<5; itrig++)
  {	 	  
    hjet[itrig]->Rebin(2);
    normalizeByBinWidth(hjet[itrig]);
    hjet[itrig]->GetXaxis()->SetRangeUser(StartPoint+1,EndPoint-2);	   
    hjet[itrig]->SetMarkerStyle(20);
    hjet[itrig]->SetMarkerColor(1+itrig);
    hjet[itrig]->SetMarkerSize(1.0);
    hjet[itrig]->SetLineColor(1+itrig);
    hjet[itrig]->DrawCopy("same");
  }
  hcombine->Rebin(2);
  normalizeByBinWidth(hcombine);
  hcombine->GetXaxis()->SetRangeUser(StartPoint+1,EndPoint-2);
  hcombine->SetMarkerStyle(24);
  hcombine->SetMarkerColor(1);
  hcombine->SetMarkerSize(1.5);
  hcombine->SetLineColor(1);
  hcombine->DrawCopy("same");

  TLegend *leg1 = new TLegend(0.5,0.69,0.7,0.88);
  leg1->SetBorderSize(0);
  leg1->SetTextFont(43);
  leg1->SetTextSize(20);
  leg1->AddEntry(hcombine,"Combined","P");
  leg1->AddEntry(hjet_Rebin_Jet20,"Jet20","P");
  leg1->AddEntry(hjet_Rebin_Jet40,"Jet40","P");
  leg1->SetFillColor(kWhite);
  leg1->Draw("same");

  TLegend *leg2 = new TLegend(0.72,0.69,0.86,0.88);
  leg2->SetBorderSize(0);
  leg2->SetTextFont(43);
  leg2->SetTextSize(20);
  for(int i=2; i<5; i++)
  {
    leg2->AddEntry(hjet[i],Form("Jet%s",JetTrig[i]),"P");
  }
  leg2->SetFillColor(kWhite);
  leg2->Draw("same");

  drawText("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV",0.28,0.95,20);
  drawCMS(0.68,0.640,35);

  TLatex *tex1 = new TLatex(0.68,0.5,"| #eta_{CM} | < 1.0");
  tex1->SetTextFont(43);
  tex1->SetTextSize(20);
  tex1->SetNDC();
  tex1->Draw("same");

  TLatex *tex2 = new TLatex(0.20,0.18,"Anti-k_{T} Particle Flow Jets: R=0.3");
  tex2->SetTextFont(43);
  tex2->SetTextSize(20);
  tex2->SetNDC();
  tex2->Draw("same");

//====================Relative shape=======================  
  TCanvas *c2 = new TCanvas("c2","c2",400,50,599,599);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  c2->Range(-38.59656,-12.02472,644.9871,2.486126);
  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetBorderSize(2);
  c2->SetTickx(1);
  c2->SetTicky(1);
  c2->SetLeftMargin(0.1552174);
  c2->SetRightMargin(0.02034783);
  c2->SetTopMargin(0.08166969);
  c2->SetBottomMargin(0.1288566);
  c2->SetFrameFillStyle(0);
  c2->SetFrameBorderMode(0);   
  c2->cd();
  	
  TH1F *hDum2 = new TH1F("hdum2","hdum2",13,StartPoint,EndPoint);
  hDum2->SetMinimum(0.);
  hDum2->SetMaximum(1.5);
  hDum2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hDum2->GetXaxis()->SetTitleSize(0.05);
  hDum2->GetXaxis()->SetTitleOffset(1.2);
  hDum2->GetXaxis()->SetLabelSize(0.045);
  hDum2->GetXaxis()->CenterTitle();
  hDum2->GetYaxis()->SetTitle("Rel. Shape");
  hDum2->GetYaxis()->SetTitleSize(0.05);
  hDum2->GetYaxis()->SetTitleOffset(1.4);
  hDum2->GetYaxis()->SetLabelSize(0.045);
  hDum2->GetYaxis()->CenterTitle();
  hDum2->DrawCopy();

  TH1F *hRatio[5];
  for(int itrig=0; itrig<5; itrig++)
  {
    hRatio[itrig] = (TH1F *)hjet_Rebin[itrig]->Clone(hjet[itrig]->GetName());
    hRatio[itrig] -> Divide(hcombine_Rebin[itrig]);
    hRatio[itrig] -> SetMarkerSize(1.5);
    hRatio[itrig] -> SetMarkerStyle(20);
    hRatio[itrig] -> SetMarkerColor(1+itrig);
    hRatio[itrig] -> SetLineColor(1+itrig);
    hRatio[itrig] -> GetXaxis()->SetRangeUser(StartPoint+1,EndPoint-2);
    hRatio[itrig] -> DrawCopy("same");
  }

  drawText("CMS Preliminary, pPb #sqrt{s_{NN}} = 5.02 TeV",0.28,0.95,20);   
  drawCMS(0.2383193,0.8743608,35);
  
  TLegend *leg3 = new TLegend(0.6386555,0.2304904,0.7394958,0.39098599);
  leg3->SetBorderSize(0);
  leg3->SetTextFont(43);
  leg3->SetTextSize(20);
  for(int i = 0; i<2; i++) leg3->AddEntry(hRatio[i],Form("Jet%s",JetTrig[i]));
  leg3->SetFillColor(kWhite);
  leg3->Draw("same");

  TLegend *leg4 = new TLegend(0.7831933,0.2204904,0.8823529,0.4098599);
  leg4->SetBorderSize(0);
  leg4->SetTextFont(43);
  leg4->SetTextSize(20);
  for(int i = 2; i<5; i++) leg4->AddEntry(hRatio[i],Form("Jet%s",JetTrig[i]));
  leg4->SetFillColor(kWhite);
  leg4->Draw("same");
  
  TLatex *tex3 = new TLatex(0.2234454,0.7490543,"| #eta_{CM} | < 1.0");
  tex3->SetTextFont(43);
  tex3->SetTextSize(20);
  tex3->SetNDC();
  tex3->Draw("same");

  TLatex *tex4 = new TLatex(0.4552101,0.7775832,"Anti-k_{T} Particle Flow Jets: R=0.3");
  tex4->SetTextFont(43);
  tex4->SetTextSize(20);
  tex4->SetNDC();
  tex4->Draw("same");


  TLine *l = new TLine(StartPoint,1,EndPoint,1);
  l->SetLineStyle(2);
  l->SetLineWidth(2);
  l->SetLineColor(kBlack);
  l->Draw("same");
  
  if(SavePlots) 
  {
    c1->SaveAs("LumiCombineSpectrawithunit.pdf");
    c1->SaveAs("LumiCombineSpectrawithunit.gif");
    c2->SaveAs("RelativeShapewithunit.pdf");
    c2->SaveAs("RelativeShapewithunit.gif");
  }
}

void drawText(const char *text, float xp, float yp, int textSize=20){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(textSize);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

void drawCMS(float px, float py, float nLumi) {
  TLatex *lumi = new TLatex(px-0.02,py-0.05,Form("#intL dt = %.0f nb^{-1}",nLumi));
  lumi->SetTextFont(43);
  lumi->SetTextSize(20);
  lumi->SetNDC();
  lumi->Draw();
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

