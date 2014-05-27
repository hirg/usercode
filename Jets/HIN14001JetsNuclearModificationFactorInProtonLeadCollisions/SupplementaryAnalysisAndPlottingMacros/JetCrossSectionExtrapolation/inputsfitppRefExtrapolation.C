#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
inputsfitppRefExtrapolation(){

  bool eta0005=true;
  bool eta0510=false;
  bool eta1015=false;
  bool eta1520=false;
  const int nEta=6;
  TGraphErrors *graph[nEta];
  TGraphErrors *graph2[nEta];
  TFile *file1 = new TFile("R3_ScaleFactor7000TeVto5TeVStartingCone5Sys.root","read");
  TFile *file2 = new TFile("R3_ScaleFactor7000TeVto5TeVStartingCone5SysUp.root","read");
  TFile *file3 = new TFile("R3_ScaleFactor7000TeVto5TeVStartingCone5SysDown.root","read");
  TFile *file4 = new TFile("R3_ScaleFactor7000TeVto5TeVStartingCone7Sys.root","read");
  TFile *file5 = new TFile("R3_AMBT2ScaleFactor7000TeVto5TeVStartingCone5Sys.root","read");
  //TFile *file6 = new TFile("R3_ScaleFactor2760GeVto5TeV.root","read");
  //TFile *file6 = new TFile("R3_ScaleFactor2760GeVto5TeVTGraphErrors.root","read");
  //TFile *file6 = new TFile("R3_DATA2760ScaleFactor7000TeVto5TeVStartingCone5Sys.root","read");
  TFile *file6 = new TFile("R3_DATA2760yDepScaleFactor7000TeVto5TeVStartingCone5Sys.root","read");
if(eta0005){
  graph[0]= (TGraphErrors*)file1->Get("Interpolated5TeVak3PFJetAbsRapidity0_5");
  graph[1]= (TGraphErrors*)file2->Get("Interpolated5TeVak3PFJetAbsRapidity0_5");
  graph[2]= (TGraphErrors*)file3->Get("Interpolated5TeVak3PFJetAbsRapidity0_5");
  graph[3]= (TGraphErrors*)file4->Get("Interpolated5TeVak3PFJetAbsRapidity0_5");
  graph[4]= (TGraphErrors*)file5->Get("Interpolated5TeVak3PFJetAbsRapidity0_5");
  graph[5]= (TGraphErrors*)file6->Get("Interpolated5TeVak3PFJetAbsRapidity0_5");
}
if(eta0510){
  graph[0]= (TGraphErrors*)file1->Get("Interpolated5TeVak3PFJetAbsRapidity5_10");
  graph[1]= (TGraphErrors*)file2->Get("Interpolated5TeVak3PFJetAbsRapidity5_10");
  graph[2]= (TGraphErrors*)file3->Get("Interpolated5TeVak3PFJetAbsRapidity5_10");
  graph[3]= (TGraphErrors*)file4->Get("Interpolated5TeVak3PFJetAbsRapidity5_10");
  graph[4]= (TGraphErrors*)file5->Get("Interpolated5TeVak3PFJetAbsRapidity5_10");
  graph[5]= (TGraphErrors*)file6->Get("Interpolated5TeVak3PFJetAbsRapidity5_10");
}
if(eta1015){
  graph[0]= (TGraphErrors*)file1->Get("Interpolated5TeVak3PFJetAbsRapidity10_15");
  graph[1]= (TGraphErrors*)file2->Get("Interpolated5TeVak3PFJetAbsRapidity10_15");
  graph[2]= (TGraphErrors*)file3->Get("Interpolated5TeVak3PFJetAbsRapidity10_15");
  graph[3]= (TGraphErrors*)file4->Get("Interpolated5TeVak3PFJetAbsRapidity10_15");
  graph[4]= (TGraphErrors*)file5->Get("Interpolated5TeVak3PFJetAbsRapidity10_15");
  graph[5]= (TGraphErrors*)file6->Get("Interpolated5TeVak3PFJetAbsRapidity10_15");
}
if(eta1520){
  graph[0]= (TGraphErrors*)file1->Get("Interpolated5TeVak3PFJetAbsRapidity15_20");
  graph[1]= (TGraphErrors*)file2->Get("Interpolated5TeVak3PFJetAbsRapidity15_20");
  graph[2]= (TGraphErrors*)file3->Get("Interpolated5TeVak3PFJetAbsRapidity15_20");
  graph[3]= (TGraphErrors*)file4->Get("Interpolated5TeVak3PFJetAbsRapidity15_20");
  graph[4]= (TGraphErrors*)file5->Get("Interpolated5TeVak3PFJetAbsRapidity15_20");
  graph[5]= (TGraphErrors*)file6->Get("Interpolated5TeVak3PFJetAbsRapidity15_20");
}

  //for(int i=0; i<6; i++)
  //cout<<"Nbins="<<graph[i]->GetN()<<endl;
  Double_t ptx[nEta][33],scaledY[nEta][33], errorY[nEta][33], errorX[nEta][33];
  Int_t nBin;
  for(int i=0; i<nEta; i++){
   nBin=graph[i]->GetN();
   for(int j=0; j<nBin; j++){
    graph[i]->GetPoint(j,ptx[i][j],scaledY[i][j]);
    errorY[i][j]= graph[i]->GetErrorY(j);
    
    //scaledY[i][j]=scaledY[i][j]/10e9;
    //errorY[i][j]=errorY[i][j]/10e9;
    //errorY[i][j]= scaledY[i][j]*0.11;
    //if(i==0) cout<<errorY[i][j]/scaledY[i][j]<<endl;
    //graph[i]->SetPoint(j,ptx[i][j],scaledY[i][j]);
    cout<<"i= "<<i<<", pt= "<<ptx[i][j]<<",  Y= "<<scaledY[i][j]<<endl;
    //if(i==1)cout<<"0.5<y<1 / 0<y<0.5 :  pt="<<ptx[0][j]<<", spectra ratio= "<<scaledY[1][j]/scaledY[0][j]<<endl;
   }
      for(int j=0; j<nBin; j++){
          if(j<nBin-1) errorX[i][j]= (ptx[i][j+1]-ptx[i][j])/2.;
          else errorX[i][j]= (ptx[i][j]-ptx[i][j-1])/2.;
      }
  }
/*
   for(int j=0; j<33; j++){
    scaledY[0][j]=scaledY[0][j]*pow(4.0,0);
    scaledY[1][j]=scaledY[1][j]*pow(4.0,-1);
    scaledY[2][j]=scaledY[2][j]*pow(4.0,-2);
    scaledY[3][j]=scaledY[3][j]*pow(4.0,-3);
    scaledY[4][j]=scaledY[4][j]*pow(4.0,-4);
    scaledY[5][j]=scaledY[5][j]*pow(4.0,-5);

    errorY[0][j]=errorY[0][j]*pow(4.0,0);
    errorY[1][j]=errorY[1][j]*pow(4.0,-1);
    errorY[2][j]=errorY[2][j]*pow(4.0,-2);
    errorY[3][j]=errorY[3][j]*pow(4.0,-3);
    errorY[4][j]=errorY[4][j]*pow(4.0,-4);
    errorY[5][j]=errorY[5][j]*pow(4.0,-5);
   }
*/
    int msty[nEta+2]={25,27,28,30,24,31};
    int mcol[nEta+2]={1,4,2,2,4,2};
    float msiz[nEta+2]={1.2,1.4,1.3,1.4,1.2,1.4};
  for(int i=0; i<nEta; i++){
   nBin=graph[i]->GetN();
   graph2[i] = new TGraphErrors(nBin, ptx[i], scaledY[i], errorX[i], errorY[i]);
   if(i==3)graph2[i] = new TGraphErrors(23, ptx[i], scaledY[i], errorX[i], errorY[i]);
   if(i==5)graph2[i] = new TGraphErrors(23, ptx[i], scaledY[i], errorX[i], errorY[i]);
  graph2[i]->SetMarkerStyle(msty[i]);
  graph2[i]->SetMarkerColor(mcol[i]);
  graph2[i]->SetLineColor(mcol[i]);
  graph2[i]->SetLineStyle(1);
  graph2[i]->SetMarkerSize(msiz[i]);
   //for(int j=0; j<nBin; j++){
    //graph2[i]->SetPoint(j,ptx[i][j],scaledY[i][j]);
    //graph2[i]->SetPointError(j,0,errorY[i][j]);
   //}
  }

  double sysError[nEta][33]; double mpt[nEta][33];
  ifstream infile1, infile2, infile3, infile4;
  infile1.open("./pp/ppRefSysTotalEtaBin-5_5.txt");
  infile2.open("./pp/ppRefSysTotalEtaBin5_10.txt");
  infile3.open("./pp/ppRefSysTotalEtaBin10_15.txt");
  infile4.open("./pp/ppRefSysTotalEtaBin15_20.txt");
  for(int j=0; j<26; j++){ infile1>>mpt[0][j];  infile1>>sysError[0][j]; sysError[0][j]=sysError[0][j]*0.01*scaledY[0][j+7]; }
  for(int j=0; j<25; j++){ infile2>>mpt[1][j];  infile2>>sysError[1][j]; sysError[1][j]=sysError[1][j]*0.01*scaledY[1][j+7]; }
  for(int j=0; j<24; j++){ infile3>>mpt[2][j];  infile3>>sysError[2][j]; sysError[2][j]=sysError[2][j]*0.01*scaledY[2][j+7]; }
  for(int j=0; j<21; j++){ infile4>>mpt[3][j];  infile4>>sysError[3][j]; sysError[3][j]=sysError[3][j]*0.01*scaledY[3][j+7]; }
  //cout<<"read sys : "<<sysError[3][21]<<endl;

  TCanvas *c1 = new TCanvas("c1","c1",1,1,599,599);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.17);
  c1->SetBottomMargin(0.14);
  c1->SetTopMargin(0.1);
  c1->SetRightMargin(0.02);
  //c1->Divide(1,2,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
  gPad->SetLogy();
  gPad->SetLogx();

 TH1D* hist = new TH1D("hist","",1000,47.,1210.0);
 hist->SetXTitle("p_{T} [GeV/c]");
 hist->SetYTitle("d^{2}#sigma/dp_{T}dy [mb/GeV]");
 hist->SetMinimum(0.8*10e-14*1.0/16);
 hist->SetMaximum(4*10e-2*1.0/16);
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
 hist->Draw();
/*
    int ndata[4]={26, 25, 24, 21};
    for(int j=0; j<4; j++){
     int np=0;
        while (np <ndata[j] ) {
          TBox *box = new TBox(mpt[j][np]-mpt[j][np]*0.03,scaledY[j][np+7]-sysError[j][np],mpt[j][np]+mpt[j][np]*0.04, scaledY[j][np+7]+sysError[j][np]);
          box->SetFillColor(5);
          box->SetFillStyle(-1);
          box->Draw();
          np++;
        }
     }
*/
  TF1 *ftrue[nEta];
  char ffun[nEta][200]={"ftrue1","ftrue2","ftrue3","ftrue4","ftrue5","ftrue6"};
  for(int i=0; i<nEta; i++){
  if(i==0||i==3||i==4)graph2[i]->Draw("psameEZ");  
 if(i==0)ftrue[i] = new TF1(ffun[i], "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/3500.,[3])", 50, 800) ;
 if(i==1)ftrue[i] = new TF1(ffun[i], "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/3500.,[3])", 50, 770) ;
 if(i==2)ftrue[i] = new TF1(ffun[i], "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/3500.,[3])", 50, 700) ;
 if(i==3)ftrue[i] = new TF1(ffun[i], "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/3500.,[3])", 120,990) ;
 if(i==4)ftrue[i] = new TF1(ffun[i], "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/3500.,[3])", 50, 770) ;
 if(i==5)ftrue[i] = new TF1(ffun[i], "[0]*exp([1]/x)*pow(x,[2])*pow(1-x*cosh([4])/3500.,[3])", 50, 530) ;
 ftrue[i]->SetParameters(2.86100e+05, -4.74921e+01 , -5.34629e+00, 6.85952e+00, -1.05411e+00);
 ftrue[i]->SetLineColor(mcol[i]);
 ftrue[i]->SetLineWidth(2);
 ftrue[i]->SetLineStyle(1);
 if(i<1)graph2[i]->Fit(ffun[i],"R+");
 //gr1->Draw("psameZE");

//cout<<"Nbin="<<gr1->GetN()<<endl;
 float ndf=ftrue[i]->GetNDF();
 double chi2=ftrue[i]->GetChisquare();
 if(ndf==0) ndf=1;
 cout<<"ieta= "<<i<<" , ndf= "<<ndf<<" #chi^2/ndf= "<<chi2/ndf<<endl;
 }
char ebins[nEta][200]={"0-0.5","0.5-1.0","1.0-1.5","1.5-2.0","2.0-2.5","2.5-3.0"};
cout<<endl;
  for(int i=0; i<nEta; i++){
if(i<6){
    cout<<"y range in "<<ebins[i]<<":"<<endl;
    //cout<<ftrue[i]->GetParError(0)<<", "<<ftrue[i]->GetParError(1)<<endl;
    cout<<ftrue[i]->GetParameter(0)+ftrue[i]->GetParError(0)<<", "<<ftrue[i]->GetParameter(1)+ftrue[i]->GetParError(1)<<", "<<ftrue[i]->GetParameter(2)+ftrue[i]->GetParError(2)<<", "<<ftrue[i]->GetParameter(3)+ftrue[i]->GetParError(3)<<", "<<ftrue[i]->GetParameter(4)+ftrue[i]->GetParError(4)<<endl;
    cout<<ftrue[i]->GetParameter(0)<<", "<<ftrue[i]->GetParameter(1)<<", "<<ftrue[i]->GetParameter(2)<<", "<<ftrue[i]->GetParameter(3)<<", "<<ftrue[i]->GetParameter(4)<<endl;
    cout<<ftrue[i]->GetParameter(0)-ftrue[i]->GetParError(0)<<", "<<ftrue[i]->GetParameter(1)-ftrue[i]->GetParError(1)<<", "<<ftrue[i]->GetParameter(2)-ftrue[i]->GetParError(2)<<", "<<ftrue[i]->GetParameter(3)-ftrue[i]->GetParError(3)<<", "<<ftrue[i]->GetParameter(4)-ftrue[i]->GetParError(4)<<endl;
   }
  }

    TLatex *tex1= new TLatex(75.,1.7*10e-1*1.0/16,"CMS Preliminary,  pp \#sqrt{s} = 5.02 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(20.);
    tex1->SetTextFont(43);
    tex1->Draw();
    //TLatex *tex2= new TLatex(81.3,2*10e-3*1.0/16,"Interpolated pp jet cross section");
    TLatex *tex2= new TLatex(81.3,2*10e-3*1.0/6,"Extrapolated pp jet cross section");
    tex2->SetTextColor(1);
    tex2->SetTextSize(20.0);
    tex2->SetTextFont(43);
    tex2->Draw();
    TLatex *tex2x= new TLatex(481.3, 10e-8/3,"0 < |y| < 0.5");
    tex2x->SetTextColor(1);
    tex2x->SetTextSize(20.0);
    tex2x->SetTextFont(43);
    tex2x->Draw();
    TLatex *tex3= new TLatex(58.,9*10e-12*1.0/16,"References:");
    tex3->SetTextColor(1);
    tex3->SetTextSize(20.0);
    tex3->SetTextFont(43);
    tex3->Draw();
    TLatex *tex4= new TLatex(58.,2.*10e-12*1.0/16,"PRL 107 (2011) 132001");
    tex4->SetTextColor(1);
    tex4->SetTextSize(18.0);
    tex4->SetTextFont(43);
    tex4->Draw();
    tex4->DrawLatex(58.,3.8*10e-13*1.0/16,"PRD  87 (2013) 112002");
    tex4->DrawLatex(58.,7*10e-14*1.0/16,"(CMS pp jet cross section at 7 TeV)");

    TLegend *leg0 = new TLegend(0.51,0.63,0.65,0.83);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.05);
    leg0->SetTextFont(43);
    leg0->SetTextSize(20.0);
    leg0->AddEntry(graph2[0],"7 TeV, R=0.5 + Z2 (Default)","p");
    //leg0->AddEntry(graph2[1],"7 TeV, R=0.5 Up + Z2","p");
    //leg0->AddEntry(graph2[2],"7 TeV, R=0.5 Down + Z2","p");
    leg0->AddEntry(graph2[3],"7 TeV, R=0.7 + Z2","p");
    leg0->AddEntry(graph2[4],"7 TeV, R=0.5 + AMBT2","p");
    //leg0->AddEntry(graph2[5],"7 TeV, R=0.5 + DATA","p");
    leg0->Draw();

c1->Print("ppCrossSectionExtrapolationZ2AMBT2.gif");

  TCanvas *c2 = new TCanvas("c2","c2",500,1,599,599);
  c2->SetFillColor(10);
  c2->SetFrameFillColor(0);
  c2->SetFrameBorderSize(0);
  c2->SetFrameBorderMode(0);
  c2->SetLeftMargin(0.15);
  c2->SetBottomMargin(0.14);
  c2->SetTopMargin(0.02);
  c2->SetRightMargin(0.02);
  //c2->Divide(1,2,0,0);
  gStyle->SetOptStat(0);
  c2->SetTicks(-1);
  gPad->SetLogx();
  gPad->SetGridy();
  gPad->SetGridx();

 TH1D* hist2 = new TH1D("hist2","",1000,47.,1210.0);
 hist2->SetXTitle("p_{T} [GeV/c]");
 hist2->SetYTitle("(Different inputs)/(Fitted default)");
 hist2->SetMinimum(0.5);
 hist2->SetMaximum(1.5);
 hist2->GetXaxis()->CenterTitle(1);
 hist2->GetYaxis()->CenterTitle(1);
 hist2->GetYaxis()->SetTitleOffset(1.2);
 hist2->GetXaxis()->SetTitleOffset(1.15);
 hist2->GetXaxis()->SetTitleSize(0.056);
 hist2->GetYaxis()->SetTitleSize(0.056);
 hist2->GetXaxis()->SetLabelSize(0.05);
 hist2->GetYaxis()->SetLabelSize(0.05);
 hist2->GetXaxis()->SetNdivisions(509);
 hist2->GetYaxis()->SetNdivisions(506);
 hist2->GetXaxis()->SetMoreLogLabels();
 hist2->GetXaxis()->SetNoExponent();
 hist2->Draw();

  TGraphErrors *gr2[nEta];
  double fratio[nEta][33], ratioError[nEta][33];
  double absfratio[nEta][33];
  for(int i=0; i<nEta; i++){
   nBin=graph[i]->GetN();
   for(int j=0; j<nBin; j++){
    fratio[i][j]=scaledY[i][j]/ftrue[0]->Eval(ptx[i][j]);
    //if(i==1) cout<<"ratio="<<scaledY[i][j]/ftrue[0]->Eval(ptx[i][j])<<endl;
    ratioError[i][j]=errorY[i][j]/scaledY[i][j]*sqrt(1);
    absfratio[i][j]=fabs(fratio[i][j]-1);
   }
  //cout<<"i="<<i<<", nBin="<<nBin<<endl;
  //gr2[i] = new TGraphErrors(nBin, ptx[i], fratio[i], 0, ratioError[i]);
  gr2[i] = new TGraphErrors(30, ptx[i], fratio[i], 0, ratioError[i]);
  if(i==3)gr2[i] = new TGraphErrors(18, ptx[i], fratio[i], 0, ratioError[i]);
  gr2[i]->SetMarkerStyle(msty[i]);
  gr2[i]->SetMarkerColor(mcol[i]);
  gr2[i]->SetLineColor(mcol[i]);
  gr2[i]->SetLineStyle(1);
  gr2[i]->SetLineWidth(2);
  gr2[i]->SetMarkerSize(msiz[i]);
  if(i==0||i==3||i==4)gr2[i]->Draw("psameEZ");
  }

    TLatex *tex1= new TLatex(63.,1.38,"CMS Preliminary,  pp \#sqrt{s} = 5.02 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(20.);
    tex1->SetTextFont(43);
    tex1->Draw();
    //TLatex *tex2= new TLatex(63.,1.25,"Interpolated pp jet cross section/Fit");
    TLatex *tex2= new TLatex(103.,1.285,"0 < |y| < 0.5");
    tex2->SetTextColor(1);
    tex2->SetTextSize(20.0);
    tex2->SetTextFont(43);
    tex2->Draw();
    TLatex *tex2x= new TLatex(481.3, 10e-8/3,"0 < |y| < 0.5");
    tex2x->SetTextColor(1);
    tex2x->SetTextSize(20.0);
    tex2x->SetTextFont(43);
    //tex2x->Draw();
    TLegend *leg0 = new TLegend(0.2,0.19,0.36,0.38);
    leg0->SetFillColor(10);
    leg0->SetBorderSize(0.05);
    leg0->SetTextFont(43);
    leg0->SetTextSize(20.0);
    leg0->AddEntry(gr2[0],"(7 TeV, R=0.5 + Z2)/(Fitted Default)","p");
    //leg0->AddEntry(gr2[1],"(7 TeV, R=0.5 Up + Z2)/(Fitted Default)","p");
    //leg0->AddEntry(gr2[2],"(7 TeV, R=0.5 Down + Z2)/(Fitted Default)","p");
    leg0->AddEntry(gr2[3],"(7 TeV, R=0.7 + Z2)/(Fitted Default)","p");
    leg0->AddEntry(gr2[4],"(7 TeV, R=0.5 + AMBT2)/(Fitted Default)","p");
    //leg0->AddEntry(gr2[5],"(7 TeV, R=0.5 + DATA)/(Fitted Default)","p");
    leg0->Draw();

if(1){ // different inputs
for(int j=0; j<33; j++) if(j>18) absfratio[5][j]=0.0;
for(int j=0; j<33; j++) if(j>=13) absfratio[3][j]=absfratio[3][j-13];
for(int j=0; j<33; j++) if(j<13) absfratio[3][j]=0.0;
for(int j=0; j<33; j++) cout<<"test for n=3 , pt = "<<ptx[0][j]<<", absfratio = "<<absfratio[3][j]<<endl;
int n[4]={0,3,4,5};
double maxerr[33][4];
for(int j=0; j<33; j++){
  for(int i=0; i<4; i++){
    maxerr[j][i]=absfratio[n[i]][j];
  }
}
for(int j=0; j<33; j++) cout<<"pt= "<<ptx[0][j]<<", max err= "<<TMath::MaxElement(4, maxerr[j])<<endl;

ofstream outfile;
if(eta0005) outfile.open("ppsysFromExtrapolationWithDifferentInputsEta0_5.txt");
if(eta0510) outfile.open("ppsysFromExtrapolationWithDifferentInputsEta5_10.txt");
if(eta1015) outfile.open("ppsysFromExtrapolationWithDifferentInputsEta10_15.txt");
if(eta1520) outfile.open("ppsysFromExtrapolationWithDifferentInputsEta15_20.txt");
for(int i=6; i<33; i++){
outfile<< setw(5)<<setprecision(4)<<ptx[0][i]<<"     "<<setw(6)<<setprecision(3)<<TMath::MaxElement(4, maxerr[i])*100<<endl;
}

}
// up/down
if(0){
for(int j=0; j<33; j++) cout<<"test for n=2 , pt = "<<ptx[0][j]<<", absfratio = "<<absfratio[2][j]<<endl;
int n[2]={1,2};
double maxerr[33][2];
for(int j=0; j<33; j++){
  for(int i=0; i<2; i++){
    maxerr[j][i]=absfratio[n[i]][j];
  }
}
for(int j=0; j<33; j++) cout<<"pt= "<<ptx[0][j]<<", max err= "<<TMath::MaxElement(2, maxerr[j])<<endl;

ofstream outfile;
if(eta0005) outfile.open("ppsysFromExtrapolationWithUpDownEta0_5.txt");
if(eta0510) outfile.open("ppsysFromExtrapolationWithUpDownEta5_10.txt");
if(eta1015) outfile.open("ppsysFromExtrapolationWithUpDownEta10_15.txt");
if(eta1520) outfile.open("ppsysFromExtrapolationWithUpDownEta15_20.txt");
for(int i=6; i<33; i++){
outfile<< setw(5)<<setprecision(4)<<ptx[0][i]<<"     "<<setw(6)<<setprecision(3)<<TMath::MaxElement(2, maxerr[i])*100<<endl;
}

}

   //graph2[i] = new TGraphErrors(nBin, ptx[i], scaledY[i], 0, errorY[i]);
   //gr2[0]->Draw("psame");

//c2->Print("ppFit4EtaBinsRatio.pdf");
//c2->Print("ppFit4EtaBinsRatio.png");
c2->Print("ppFitExtrapolationRatioZ2AMBT2.gif");

}


