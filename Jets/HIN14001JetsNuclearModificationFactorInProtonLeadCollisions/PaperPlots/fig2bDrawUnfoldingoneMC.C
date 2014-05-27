#include "./root_setting.h" 

static const int nColor = 7;

static const int colorCode[nColor] = {
    1, 2, 4, 46,6, 7,8
};
static const int markerCode[nColor] = {
    20, 34, 33, 25,27, 28,24
};

const double pPbLumi = 20.7 ;
void fig2bDrawUnfoldingoneMC(){

    TCanvas *c1 = new TCanvas("c1a", "c1",0,0,600,600);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetErrorX(0);   
    c1->Range(0,0,1,1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->SetLeftMargin(0.16);
    c1->SetRightMargin(0.02);
    c1->SetTopMargin(0.02);
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
const int binbound_pt[] = { 3, 4, 5, 7, 9, 12, 15, 18,21,24,28,32,37,43,49,56,64,74,84,97,114,133,153,174,196,220,245,272,300,330,362,395,430,468,507,548,592,638,686,1000};

TFile *f = TFile::Open("./PPb_UnfoPriorGen_akPu3PFKurtMCNoIDCut_MC_jtpt20_EtaBin-10_10_Inc_v8.root");
TH1D* hBay = (TH1D*)f->Get("hRecoScaled_Cent0");
TH1F* hMeas = (TH1F*)f->Get("hMeasScaled_Cent0");
TH1F* hBin = (TH1F*)f->Get("hRecoBinByBinScaled_Cent0");

/*hGen_PPb=(TH1F*)hGen_PPb->Rebin(Nbin_pt,hGen_PPb->GetName(),binbound_pt);
hBay=(TH1F*)hBay->Rebin(Nbin_pt,hBay->GetName(),binbound_pt);
hMeas=(TH1F*)hMeas->Rebin(Nbin_pt,hMeas->GetName(),binbound_pt);
hBin=(TH1F*)hBin->Rebin(Nbin_pt,hBin->GetName(),binbound_pt);
*/

TH1F* hBay_Cl = (TH1F*)hBay->Clone("hBay_Cl");
TH1F* hBin_Cl = (TH1F*)hBin->Clone("hBin_Cl");
TH1F* hMeas_Cl = (TH1F*)hMeas->Clone("hMeas_Cl");

//hBay_Cl->Divide(hGen_PPb);
//hBin_Cl->Divide(hGen_PPb);
//hMeas_Cl->Divide(hGen_PPb);


TH1F* hFrame=new TH1F("","",1000,0,1000);
hFrame->GetXaxis()->SetLimits(47,520);
//hFrame->GetXaxis()->SetLabelSize(1.5);
hFrame->GetXaxis()->SetTitle("p_{T}^{jet} [GeV/c]");
hFrame->GetXaxis()->SetNdivisions(506);
hFrame->GetYaxis()->SetRangeUser(0.89,1.2);
//hFrame->GetYaxis()->SetLabelSize(1.5);
hFrame->GetYaxis()->SetTitle("Reco / Truth");
fixedFontHist(hFrame,1.2,1.6);
            hFrame->GetXaxis()->SetTitleSize(0.06);
            hFrame->GetXaxis()->SetTitleOffset(1.15);
            hFrame->GetXaxis()->SetLabelSize(0.05);
            hFrame->GetYaxis()->SetTitleSize(0.06);
            hFrame->GetYaxis()->SetLabelSize(0.05);
            hFrame->GetYaxis()->SetTitleOffset(1.3);

hFrame->DrawCopy();
hMeas_Cl->SetMarkerStyle(20);
hMeas_Cl->SetLineColor(2);
hMeas_Cl->SetMarkerColor(2);
hMeas_Cl->SetMarkerSize(1.2);

hBay_Cl->SetMarkerStyle(20);
hBay_Cl->SetLineColor(1);
hBay_Cl->SetMarkerColor(1);
hBay_Cl->SetMarkerSize(1.2);

hBin_Cl->SetMarkerStyle(24);
hBin_Cl->SetLineColor(2);
hBin_Cl->SetMarkerColor(2);
hBin_Cl->SetMarkerSize(1.2);

//hMeas_Cl->DrawCopy("same");
hBin_Cl->DrawCopy("same");
hBay_Cl->DrawCopy("same");
TLegend* leg=new TLegend(0.65,0.78,0.82,0.93);
leg->SetBorderSize(0);
leg->SetFillColor(0);
leg->SetTextFont(43);
leg->SetTextSize(22);
leg->AddEntry(hBay_Cl,"Bayesian","lp");
leg->AddEntry(hBin_Cl,"Bin-by-bin","lp");
//leg->AddEntry(hMeas_Cl,"no unfolding","lp");
leg->Draw("same");

//drawCMS(0.18,0.85);
//drawCMS(0.2,0.88,pPbLumi);
TLatex *com0 = new TLatex(0.22,0.84,"PYTHIA+HIJING");
com0->SetTextFont(43);
com0->SetTextSize(22);
com0->SetNDC();
com0->Draw();

TLatex *com1 = new TLatex(0.22,0.9,"CMS simulation");
com1->SetTextFont(43);
com1->SetTextSize(22);
com1->SetNDC();
com1->Draw();

TLatex *com2 = new TLatex(0.22,0.78,"|#eta_{CM}| < 1.0");
com2->SetTextFont(43);
com2->SetTextSize(22);
com2->SetNDC();
com2->Draw();
TLatex *com3 = new TLatex(0.32,0.69,"Anti-k_{T} Particle Flow Jet R=0.3");
com3->SetTextFont(43);
com3->SetTextSize(22);
com3->SetNDC();
com3->Draw();

TLine *l=new TLine(hFrame->GetXaxis()->GetXmin(),1,hFrame->GetXaxis()->GetXmax(),1);
l->SetLineStyle(2);
l->Draw("same");

c1->Print("Unfolding_Kurtfile_oneMC_noRed.pdf");
c1->Print("Unfolding_Kurtfile_oneMC_noRed.gif");
}

