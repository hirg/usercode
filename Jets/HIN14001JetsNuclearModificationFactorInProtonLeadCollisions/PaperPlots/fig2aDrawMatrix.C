#include "./root_setting.h" 

static const int nColor = 7;

static const int colorCode[nColor] = {
    1, 2, 4, 46,6, 7,8
};
static const int markerCode[nColor] = {
    20, 34, 33, 25,27, 28,24
};

void fig2aDrawMatrix(){

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
    c1->SetRightMargin(0.13);
    c1->SetTopMargin(0.02);
    c1->SetBottomMargin(0.15);
    c1->SetFrameFillStyle(0);
    c1->SetFrameBorderMode(0);

    gStyle->SetOptStat(0);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadTopMargin   (0.02);
    gStyle->SetPadLeftMargin  (0.16);
    gStyle->SetPadRightMargin (0.025);
    gStyle->SetPadTickX       (1);
    gStyle->SetPadTickY       (1);

TFile *f = TFile::Open("./PPb_UnfoPriorGen_akPu3PFKurtMCNoIDCut_MC_jtpt20_EtaBin-10_10_Inc_v8.root");
//const double binbound_pt[]={ 3, 4, 5, 7, 9, 12, 15, 18, 22, 27, 33, 39, 47, 55, 64,74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 429, 692, 1000};
const double binbound_pt[]={3, 4, 5, 7, 9, 12, 15, 18,21,24,28,32,37,43,49,56,64,74,84,97,114,133,153,174,196,220,245,272,300,330,362,395,430,468,507,548,592,638,686,1000};
int Nbin_pt=sizeof(binbound_pt)/sizeof(double)-1;
bool isLog=kTRUE;
if(isLog){c1->SetLogx();c1->SetLogy();}
c1->SetLogz();
TH2F* hMatrix_PPb = (TH2F*)f->Get("hMatrixFit_cent0;2");
hMatrix_PPb->SetMaximum(2*1e-3);
hMatrix_PPb->SetMinimum(1e-9);

TH2F* hFrame=new TH2F("","",1000,0,1000,1000,0,1000);
if(isLog){
hFrame->GetXaxis()->SetMoreLogLabels();
hFrame->GetXaxis()->SetNoExponent();
hFrame->GetYaxis()->SetMoreLogLabels();
hFrame->GetYaxis()->SetNoExponent();
//hFrame->GetYaxis()->SetNdivisions(305);
}
hFrame->GetXaxis()->SetRangeUser(24,650);
hFrame->GetXaxis()->SetTitle("Gen p_{T}^{jet} [GeV/c]");
hFrame->GetYaxis()->SetRangeUser(24,650);
hFrame->GetYaxis()->SetTitle("Reco p_{T}^{jet} [GeV/c]");
fixedFontHist(hFrame,1.3,1.8);

            hFrame->GetXaxis()->SetTitleSize(0.056);
            hFrame->GetXaxis()->SetTitleOffset(1.15);
            hFrame->GetXaxis()->SetLabelSize(0.049);
            hFrame->GetYaxis()->SetTitleSize(0.06);
            hFrame->GetYaxis()->SetLabelSize(0.0439);
            hFrame->GetYaxis()->SetTitleOffset(1.2);
//hFrame->GetYaxis()->SetMoreLogLabels();
//hFrame->GetYaxis()->SetNoExponent();
//hFrame->GetYaxis()->SetNdivisions(304);

hFrame->DrawCopy();
hMatrix_PPb->DrawCopy("colz same");
//drawCMS(0.20,0.85);

TLatex *com0 = new TLatex(0.23,0.82,"PYTHIA+HIJING");
com0->SetTextFont(43);
com0->SetTextSize(22);
com0->SetNDC();
com0->Draw();

TLatex *com1 = new TLatex(0.23,0.882,"CMS simulation");
com1->SetTextFont(43);
com1->SetTextSize(22);
com1->SetNDC();
com1->Draw();
TLatex *com2 = new TLatex(0.23,0.766,"|#eta_{CM}|< 1.0");
com2->SetTextFont(43);
com2->SetTextSize(22);
com2->SetNDC();
com2->Draw();
gPad->RedrawAxis();
if(isLog){
c1->Print("Kurtfile_Matrix_Log.pdf");
c1->Print("Kurtfile_Matrix_Log.gif");
}
else{
c1->Print("Kurtfile_Matrix.pdf");
c1->Print("Kurtfile_Matrix.gif");
}
/*TLatex *com3 = new TLatex(0.4,0.24,"Anti-k_{T} Particle Flow Jets R=0.3");
com3->SetTextFont(63);
com3->SetTextSize(17);
com3->SetNDC();
com3->Draw();*/

}
