ratioPlotDiJetBalance(){

  TFile * fileMC = TFile::Open("MCPPbakPu3PFJetSpectraCombineTriggerJetPtNoJetIDCutTrkCorr.root","read");
  TFile * fileDATA = TFile::Open("DATAPPbakPu3PFJetSpectraCombineTriggerJetPtNoJetIDCutTrkCorrCombined.root","read");
  TH2D *h2MCmid, *h2DATAmid, *h2MCforward, *h2DATAforward;
  h2MCmid = (TH2D)fileMC->Get("AvgPtBalanceMid");
  h2MCforward = (TH2D)fileMC->Get("AvgPtBalanceForward");
  h2DATAmid = (TH2D)fileDATA->Get("AvgPtBalanceMid");
  h2DATAforward = (TH2D)fileDATA->Get("AvgPtBalanceForward");

  TH1D* h1MCmid = h2MCmid->ProjectionY("h1MCmid",100,140);
  TH1D* h1MCforward = h2MCforward->ProjectionY("h1MCforward",100,140);
  TH1D* h1DATAmid = h2DATAmid->ProjectionY("h1DATAmid",100,140);
  TH1D* h1DATAforward = h2DATAforward->ProjectionY("h1DATAforward",100,140);


  h1MCmid->Scale(1.0/h1MCmid->Integral(0,100));
  h1MCforward->Scale(1.0/h1MCforward->Integral(0,100));
  h1DATAmid->Scale(1.0/h1DATAmid->Integral(0,100));
  h1DATAforward->Scale(1.0/h1DATAforward->Integral(0,100));

  TH1D *hRatiomid, *hRatioforward;
  hRatiomid=(TH1D*)h1DATAmid->Clone();
  hRatioforward=(TH1D*)h1DATAforward->Clone();
  hRatiomid->Divide(h1DATAmid, h1MCmid,1,1, "");
  hRatioforward->Divide(h1DATAforward,h1MCforward,1,1, "");
//hRatiomid->Draw();
//hRatioforward->SetLineColor(2);
//hRatioforward->Draw("same");

  TCanvas *c2 = new TCanvas("c2","c2",3,2,699,339);
  c2->SetFillColor(10);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderSize(0);
  c2->SetFrameBorderMode(0);
  c2->SetLeftMargin(0.17);
  c2->SetBottomMargin(0.14);
  c2->SetTopMargin(0.1);
  c2->SetRightMargin(0.02);
  c2->Divide(2,1);
  c2->SetTicks(-1);
 gStyle->SetOptStat(0);

  c2->cd(1);
 gPad->SetTicks(-1);
 gPad->SetLeftMargin(0.17);
 gPad->SetBottomMargin(0.14);
 gPad->SetTopMargin(0.02);
 gPad->SetRightMargin(0.02);

 hRatiomid->SetTitle("");
 hRatiomid->SetXTitle("Dijet Balance");
 hRatiomid->SetYTitle("DATA/MC");
 hRatiomid->GetXaxis()->SetRangeUser(-0.999, 0.999);
 hRatiomid->SetMinimum(0.49);
 hRatiomid->SetMaximum(1.51);
 hRatiomid->GetXaxis()->CenterTitle(1);
 hRatiomid->GetYaxis()->CenterTitle(1);
 hRatiomid->GetYaxis()->SetTitleOffset(1.45);
 hRatiomid->GetXaxis()->SetTitleOffset(1.15);
 hRatiomid->GetXaxis()->SetTitleSize(0.056);
 hRatiomid->GetYaxis()->SetTitleSize(0.056);
 hRatiomid->GetXaxis()->SetLabelSize(0.05);
 hRatiomid->GetYaxis()->SetLabelSize(0.05);
 //hRatiomid->GetXaxis()->SetNdivisions(506);
 //hRatiomid->GetYaxis()->SetNdivisions(506);
 hRatiomid->SetMarkerStyle(20);
 hRatiomid->SetMarkerColor(1);
 hRatiomid->SetLineColor(1);
 hRatiomid->SetLineStyle(1);
 hRatiomid->SetLineWidth(2);
 hRatiomid->SetMarkerSize(1.0);
 hRatiomid->Draw("pEZ");

    TLegend *leg0 = new TLegend(0.52,0.66,0.89,0.77);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.04);
    leg0->SetTextFont(43);
    leg0->SetTextSize(13.0);
    leg0->AddEntry(hRatiomid,"DATA/MC","pl");
    leg0->Draw();
    TLatex *tex = new TLatex(-0.1,0.21,"Anti-k_{T} R=0.3 PF Jet");
    tex->SetTextFont(42);
    tex->SetTextSize(0.043);
    tex->SetLineWidth(2);
    tex->Draw();
    TLatex *tex = new TLatex(-0.1,0.195,"100 < p_{T}^{avg} < 140 GeV/c");
    tex->SetTextFont(42);
    tex->SetTextSize(0.043);
    tex->SetLineWidth(2);
    tex->Draw();
    TLatex *tex = new TLatex(-0.1,0.18,"|#eta_{jet ref}|<1.3, |#eta_{jet probe}|<1.3");
    tex->SetTextFont(42);
    tex->SetTextSize(0.043);
    tex->SetLineWidth(2);
    tex->Draw();

  c2->cd(2);
 gPad->SetTicks(-1);
 gPad->SetLeftMargin(0.17);
 gPad->SetBottomMargin(0.14);
 gPad->SetTopMargin(0.02);
 gPad->SetRightMargin(0.02);
 hRatioforward->SetTitle("");
 hRatioforward->SetXTitle("Dijet Balance");
 hRatioforward->SetYTitle("DATA/MC");
 hRatioforward->GetXaxis()->SetRangeUser(-0.999, 0.999);
 hRatioforward->SetMinimum(0.49);
 hRatioforward->SetMaximum(1.51);
 hRatioforward->GetXaxis()->CenterTitle(1);
 hRatioforward->GetYaxis()->CenterTitle(1);
 hRatioforward->GetYaxis()->SetTitleOffset(1.45);
 hRatioforward->GetXaxis()->SetTitleOffset(1.15);
 hRatioforward->GetXaxis()->SetTitleSize(0.056);
 hRatioforward->GetYaxis()->SetTitleSize(0.056);
 hRatioforward->GetXaxis()->SetLabelSize(0.05);
 hRatioforward->GetYaxis()->SetLabelSize(0.05);
 //hRatioforward->GetXaxis()->SetNdivisions(506);
 //hRatioforward->GetYaxis()->SetNdivisions(506);
 hRatioforward->SetMarkerStyle(20);
 hRatioforward->SetMarkerColor(1);
 hRatioforward->SetLineColor(1);
 hRatioforward->SetLineStyle(1);
 hRatioforward->SetLineWidth(2);
 hRatioforward->SetMarkerSize(1.0);
 hRatioforward->Draw("pEZ");
    TLegend *leg0 = new TLegend(0.52,0.67,0.89,0.77);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.04);
    leg0->SetTextFont(43);
    leg0->SetTextSize(13.0);
    leg0->AddEntry(hRatioforward,"pPb Data","pl");
    leg0->Draw();
    TLatex *tex = new TLatex(-0.1,0.21,"Anti-k_{T} R=0.3 PF Jet");
    tex->SetTextFont(42);
    tex->SetTextSize(0.043);
    tex->SetLineWidth(2);
    tex->Draw();
    TLatex *tex = new TLatex(-0.1,0.195,"100 < p_{T}^{avg} < 140 GeV/c");
    tex->SetTextFont(42);
    tex->SetTextSize(0.043);
    tex->SetLineWidth(2);
    tex->Draw();
    TLatex *tex = new TLatex(-0.1,0.18,"|#eta_{jet ref}|<1.3, |#eta_{jet probe}|>1.3");
    tex->SetTextFont(42);
    tex->SetTextSize(0.043);
    tex->SetLineWidth(2);
    tex->Draw();

  c2->SaveAs("hin14001DiJetBalanceRatio.gif");

}

