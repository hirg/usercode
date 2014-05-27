#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
zcalSys(){

const int nBin[8]={19, 19, 19, 24, 19, 19, 19, 24};
double pt[50], sys[50];
char files[8][200]={"sys/sysSpectrumTotalEtaBin-20_-15.txt",
"sys/sysSpectrumTotalEtaBin-15_-10.txt",
"sys/sysSpectrumTotalEtaBin-10_-5.txt",
"sys/sysSpectrumTotalEtaBin-5_5.txt",
"sys/sysSpectrumTotalEtaBin5_10.txt",
"sys/sysSpectrumTotalEtaBin10_15.txt",
"sys/sysSpectrumTotalEtaBin15_20.txt",
"sys/sysSpectrumTotalEtaBin-10_10.txt"};
char etabins[8][200]={"(-2.0, -1.5)",
"(-1.5, -1.0)",
"(-1.0, -0.5)",
"(-0.5, 0.5)",
"(0.5, 1.0)",
"(1.0, 1.5)",
"(1.5, 2.0)",
"(-1.0, 1.0)"};

char efiles[8][200]={"esys/sysSpectrumTotalEtaBin-20_-15.txt",
"esys/sysSpectrumTotalEtaBin-15_-10.txt",
"esys/sysSpectrumTotalEtaBin-10_-5.txt",
"esys/sysSpectrumTotalEtaBin-5_5.txt",
"esys/sysSpectrumTotalEtaBin5_10.txt",
"esys/sysSpectrumTotalEtaBin10_15.txt",
"esys/sysSpectrumTotalEtaBin15_20.txt",
"esys/sysSpectrumTotalEtaBin-10_10.txt"};

  TCanvas *c1 = new TCanvas("c1","c1",1,1,799,399);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.17);
  c1->SetBottomMargin(0.14);
  c1->SetTopMargin(0.1);
  c1->SetRightMargin(0.02);
  c1->Divide(4,2,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",500,47.,430.0);
 hist->SetXTitle("p_{T} [GeV/c]");
 hist->SetYTitle("Systematic uncertainties (%)");
 hist->SetMinimum(-1);
 hist->SetMaximum(32);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.45);
 hist->GetXaxis()->SetTitleOffset(1.15);
 hist->GetXaxis()->SetTitleSize(0.056);
 hist->GetYaxis()->SetTitleSize(0.056);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->GetXaxis()->SetNdivisions(506);
 hist->GetYaxis()->SetNdivisions(506);
 hist->GetXaxis()->SetMoreLogLabels();
 hist->GetXaxis()->SetNoExponent();
 //hist->Draw();

for(int k=0; k<8; k++){
ifstream infile;
infile.open(files[k]);
for(int i=0; i<nBin[k]; i++){
infile>>pt[i]; infile>>sys[i];
}
infile.close();

c1->cd(k+1);
gPad->SetTicks(-1);
gPad->SetGridx(1);
gPad->SetGridy(1);
if(k==3||k==7) gPad->SetRightMargin(0.02);
 hist->Draw();

            TGraphErrors *graph = new TGraphErrors(nBin[k],pt,sys,0,0);
            graph->SetTitle("gr");
            graph->SetMarkerStyle(33);
            graph->SetMarkerColor(2);
            graph->SetLineColor(2);
            graph->SetLineWidth(2);
            graph->SetMarkerSize(1.5);
            graph->Draw("psameez");

 TF1 *ftrue;
 //ftrue = new TF1("ffun", "[0]+[1]/x", 50, 230) ;
 //ftrue->SetParameters(0.1, 1);
 ftrue = new TF1("ffun", "[0]+[1]*x+[2]*x*x", 50, 400) ;
 ftrue->SetParameters(0.1, 1, 1);
 ftrue->SetLineColor(1);
 ftrue->SetLineWidth(2);
 ftrue->SetLineStyle(1);
 graph->Fit("ffun","R+");

 TF1 *f2 = new TF1("f2", "5.46229+303.413/x",50, 400);
 f2->SetLineColor(4);
 f2->SetLineWidth(3);
 f2->SetLineStyle(2); 
 //f2->Draw("same");

    TLatex *tex3= new TLatex(120.,25,etabins[k]);
    tex3->SetTextColor(1);
    tex3->SetTextSize(20.0);
    tex3->SetTextFont(43);
    tex3->Draw();

ofstream outfile;
outfile.open(efiles[k]);
for(int i=0; i<nBin[k]; i++){
//outfile<< setw(5)<<setprecision(4)<<pt[i]<<"     "<<setw(6)<<setprecision(3)<<ftrue->Eval(pt[i])<<endl;
if(pt[i]<250)outfile<< setw(5)<<setprecision(4)<<pt[i]<<"     "<<setw(6)<<setprecision(3)<<ftrue->Eval(pt[i])<<endl;
else outfile<< setw(5)<<setprecision(4)<<pt[i]<<"     "<<setw(6)<<setprecision(3)<<ftrue->Eval(250)<<endl;
}

}

 c1->Print("sysFitSpe.gif");

}

