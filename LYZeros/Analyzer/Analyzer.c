#include <stdio.h>
#include <complex>
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include <TMath.h>
#define rootJ0 2.4048256
#define J1rootJ0 0.519147 
#define J2rootJ0 0.431755 
#define kr 200
#define kt 5
#define Vmax 0.22*1000
#define Vstep 0.001*1000
#define NB_SLICE 1
#define NB_SLICE_PT 13
#define sqr(x) ((x)*(x))
#define Pi 3.14159265359 
//#define PI TMath::Pi()

 
using namespace std; 

 
double BesselJ0(double x);
double BesselJ0(double x)
{
  double tmp=1., xn=1.;
  long n, Nmax;

  Nmax=int(2.*x)+4;
  for (n=1;n<Nmax;n++)
  {
    xn*=(-sqr(x/2./((double) n)));
    tmp+=xn;
  }
  return tmp;
}

Analyzer(){

  ofstream outR;
  ofstream outG;
  ofstream output;
  ofstream outVint;
  ofstream outvdiff;
  ofstream outv2;

  cent_used=new TH1D("cent_used","",2000,0,10000);
  npart_used=new TH1D("npart_used","npartdist",500,0,500);
  npartsig_used=new TH1D("npartsig_used","npartsigdist",500,0,500);
  ncoll_used=new TH1D("ncoll_used","ncolldist",1000,0,2000);
  ncollsig_used=new TH1D("ncollsig_used","ncollsigdist",1000,0,2000);

  hpt=new TH1D("pt","ptdist_allevents",200,0,14);
  hphi=new TH1D("phi","phidist_allevents",200,-4,4);
  heta=new TH1D("eta","etadist_allevents",200,-4,4);

  int k1,k2,nh,Nh,islc,islcpt,inttemp;
  Int_t rmult=0;
  Int_t cbin=0;
  Float_t cnpart=0;
  Float_t cnpartsig=0;
  Float_t cncoll=0;
  Float_t cncollsig=0;
  long Totevt=0;
  long neve=0; 
  long Neve;
  double rpmult=0.;
  double rmultmean=0.;
  double Trmultmean=0.;  
  Float_t phi0[20000];
  Float_t pt0[20000];
  Float_t eta0[20000];
  //double w2=1.;
  double temp=0.;
  double temp2=0.; 
  double tempG[kr];
  double V2mean=0.;
  double err2mean=0.;
  double realG2=0.;
  double imagG2=0.;
  double chi2=0.;
  double sigma2=0.;
  double forG2[kr]; 
  double V2[kt];
  double r02[kt];  
  double theta[kt];
  double Qtheta[kt];
  double Qx[kt];
  double Qy[kt];
  double Qxa[kt];
  double Qya[kt];
  double Q2[kt];
  double RZ[kr];
  double G[kr];
  double err2[kt];
  double G2mod2[kt][kr];
  double rpmult2[NB_SLICE][NB_SLICE_PT];
  double totmult[NB_SLICE][NB_SLICE_PT]; 

  //16 bins - hiSelectedTracks
  //double minptcut[NB_SLICE_PT] = {0.9,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.8,3.2,3.6,4.2,5.0,6.0,8.0};
  //double maxptcut[NB_SLICE_PT] = {1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.8,3.2,3.6,4.2,5.0,6.0,8.0,10.0}; //16
  //double minptcut[NB_SLICE_PT] = {0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.0,2.5,3.0,4.0,6.0,8.0};
  //double maxptcut[NB_SLICE_PT] = {0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.0,2.5,3.0,4.0,6.0,8.0,12.0}; //15
  //double minptcut[NB_SLICE_PT] = {0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.0,2.5,3.0,4.0,7.0};
  //double maxptcut[NB_SLICE_PT] = {0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.0,2.5,3.0,4.0,7.0,12.0}; //14
  double minptcut[NB_SLICE_PT] = {0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.2,3.0,4.0,7.0};
  double maxptcut[NB_SLICE_PT] = {0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.2,3.0,4.0,7.0,12.0}; //13

  double v22[kt][NB_SLICE][NB_SLICE_PT]; 
  double v22mean[NB_SLICE][NB_SLICE_PT]; 
  //double w1[NB_SLICE][NB_SLICE_PT], w22[NB_SLICE][NB_SLICE_PT]; 
  double err22[kt][NB_SLICE][NB_SLICE_PT];
  double err22mean[NB_SLICE][NB_SLICE_PT];
  double pt[NB_SLICE_PT];
  double MeanPt[NB_SLICE_PT];
  double MofPt[NB_SLICE_PT];

  const std::complex<double> i(0.,1.);
  std::complex<double> G2[kt][kr];
  std::complex<double> g2[kt][kr];
  std::complex<double> g02[kt];
  std::complex<double> dlng02_dz[kt],dG02_dz[kt];
  std::complex<double> dlng02_dw[kt][NB_SLICE][NB_SLICE_PT],dG02_dw[kt][NB_SLICE][NB_SLICE_PT],compratio[kt][NB_SLICE][NB_SLICE_PT];

  for(k1=0;k1<kt;k1++) dG02_dz[k1]=0.;
  for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) {   
    pt[islcpt]= minptcut[islcpt]/2. + maxptcut[islcpt]/2.;    
    MeanPt[islcpt]=0.;
    MofPt[islcpt]=0.;

    for (islc=0; islc<NB_SLICE; islc++) {
      //w22[islc][islcpt]=1.; 
      //w1[islc][islcpt]=1.;
      v22mean[islc][islcpt]=0.;
      err22mean[islc][islcpt]=0.;
      rpmult2[islc][islcpt]=0.;
      totmult[islc][islcpt]=0.;
    for(k1=0; k1<kt; k1++) 
     { 
       dG02_dw[k1][islc][islcpt]=0.;
       dlng02_dw[k1][islc][islcpt]=0.;
       v22[k1][islc][islcpt]=0.;  
       err22[k1][islc][islcpt]=0.;
	}
    }
    }
     for(k2=0; k2<kr; k2++){
       tempG[k2]=0.;
     }
     for(k1=0;k1<kt;k1++)  for(k2=0;k2<kr;k2++)
       {
         G2[k1][k2]=0.;
         g2[k1][k2]=0.;
         G2mod2[k1][k2]=0.;
       }
  for(k1=0; k1<kt; k1++){
    theta[k1]=((double) k1)*Pi/((double) kt); 
    Qxa[k1]=0.;
    Qya[k1]=0.;
    Q2[k1]=0.;
  }

  outR.open("R.dat");  
  for(k2=0; k2<kr; k2++){
    RZ[k2]=rootJ0/(Vmax-Vstep*k2);  
    outR<<RZ[k2]<<endl;
    forG2[k2]=0.;
  } 
  outR.close();


     char *file1 = "/gpfs1/scratch/tuos/cmssw370/JEX/merged12.root";
     TFile *f1 = new TFile(file1);
     TTree *t1 = (TTree*)f1->Get("ana/evttree");
     t1->SetBranchAddress("nh", &rmult);
     t1->SetBranchAddress("bin", &cbin);
     t1->SetBranchAddress("pt", &pt0); 
     t1->SetBranchAddress("eta", &eta0);
     t1->SetBranchAddress("phi", &phi0);
     t1->SetBranchAddress("npart",&cnpart);
     t1->SetBranchAddress("npartsig",&cnpartsig);
     t1->SetBranchAddress("ncoll",&cncoll);
     t1->SetBranchAddress("ncollsig",&cncollsig);

     neve=t1->GetEntries();
     Neve=0;
     for(long ne=0; ne<neve; ne++)
     {
       if(ne%1000==0)  cout<<"Have run "<<ne<<" events ,"<<" First pass"<<endl;
       t1->GetEntry(ne);

       if(cbin<6||cbin>7) continue;  //30-40%
       Neve++;
       Nh=0;
       //rmultmean+=((float) rmult);
       for(k1=0; k1<kt; k1++)   for(k2=0; k2<kr; k2++) g2[k1][k2]=1.;
       for(k1=0; k1<kt; k1++)  {
	 Qtheta[k1]=0.;
	 Qx[k1]=0.;
	 Qy[k1]=0.;
       }
       for(nh=0;nh<rmult;nh++)
	 {
	   if(eta0[nh]<-1.0||eta0[nh]>1.0) continue;

	   hpt->Fill(pt0[nh]);
	   hphi->Fill(phi0[nh]);
	   heta->Fill(eta0[nh]);
           for(k1=0; k1<kt; k1++)
	     {	 
               Qtheta[k1]+=(1.*cos(2.*phi0[nh]-theta[k1])); 
	       Qx[k1]+=cos(2.*phi0[nh]);
	       Qy[k1]+=sin(2.*phi0[nh]); 
	     }
	   Nh++;
	 } // end of loop over particles
       rmultmean+=((float) Nh);
       cent_used->Fill(Nh); 
       npart_used->Fill(cnpart);
       npartsig_used->Fill(cnpartsig);
       ncoll_used->Fill(cncoll);
       ncollsig_used->Fill(cncollsig);

       for(k1=0; k1<kt; k1++) {
	 Q2[k1]+=Qx[k1]*Qx[k1]+Qy[k1]*Qy[k1];
	 Qxa[k1]+=Qx[k1];
	 Qya[k1]+=Qy[k1];
       for(k2=0; k2<kr; k2++) {

	 G2[k1][k2]+=(cos(RZ[k2]*Qtheta[k1])+i*sin(RZ[k2]*Qtheta[k1])); 
       }    
       }
     } // end of loop over events

       Trmultmean=rmultmean;

     Totevt=Neve;

     cout<<"Totevt: "<<Totevt <<  " Trmult: " <<Trmultmean<<",  <Mult> = "<<Trmultmean/Totevt<<endl;

  rmultmean=Trmultmean/Totevt;
  for(k1=0; k1<kt; k1++) 
    { 
      sigma2+=(Q2[k1]/Totevt-(Qxa[k1]/Totevt)*(Qxa[k1]/Totevt)-(Qya[k1]/Totevt)*(Qya[k1]/Totevt));
      for(k2=0; k2<kr; k2++){  
      G2mod2[k1][k2]=sqr(abs(G2[k1][k2])/Totevt); 
      tempG[k2]+=abs(G2[k1][k2])/Totevt; 
      }
      k2=0;
      while (G2mod2[k1][k2]>G2mod2[k1][k2+1]){
	k2++; 
      }
      V2[k1]=Vmax-Vstep*(k2+(G2mod2[k1][k2-1]-G2mod2[k1][k2+1])/2./(G2mod2[k1][k2-1]-2.*G2mod2[k1][k2]+G2mod2[k1][k2+1]));
      r02[k1]=rootJ0/V2[k1]; 
      V2mean+=V2[k1]; 
    }      
    V2mean/=kt; 
    sigma2/=kt;
    sigma2-=V2mean*V2mean;
    chi2=V2mean/sqrt(sigma2);
    cout<<"V2mean/sqrt(sigma2) = "<<chi2<<" ,  V2mean/sqrt(rmultmean) ="<<V2mean/sqrt(rmultmean)<<endl;


    outG.open("G.dat");
      for(k2=0; k2<kr; k2++){                                     
	outG<<tempG[k2]/kt<<endl;
      }
    outG.close();

   outVint.open("Vint.dat");
  for(k1=0; k1<kt; k1++) 
    {   
      err2[k1]=V2[k1]*sqrt((exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0)+exp(sqr(rootJ0/chi2)/2.))/2./Totevt)/rootJ0/J1rootJ0;      

      outVint<<theta[k1]/2.<<"   " <<V2[k1]/rmultmean<<"   " <<err2[k1]/rmultmean <<endl;
    }

     outVint<<"theta      <V2[k2]>_evt      V2[k2]err" <<endl;
     outVint.close();

  temp2=0.; 
  for(k1=0; k1<kt; k1++) 

    temp2+=exp(sqr(rootJ0/chi2)*cos(theta[k1])/2.)*BesselJ0(2.*rootJ0*sin(theta[k1]/2.))
      +exp(-sqr(rootJ0/chi2)*cos(theta[k1])/2.)*BesselJ0(2.*rootJ0*cos(theta[k1]/2.));
  err2mean=V2mean*sqrt(temp2/2./Totevt/kt)/rootJ0/J1rootJ0;



     char *file1 = "/gpfs1/scratch/tuos/cmssw370/JEX/merged12.root";
     TFile *f1 = new TFile(file1);
     TTree *t1 = (TTree*)f1->Get("ana/evttree");
     t1->SetBranchAddress("nh", &rmult);
     t1->SetBranchAddress("bin", &cbin);
     t1->SetBranchAddress("pt", &pt0); 
     t1->SetBranchAddress("eta", &eta0);
     t1->SetBranchAddress("phi", &phi0);
  
     neve=t1->GetEntries();

   for(long ne=0; ne<neve; ne++)
     {
       if(ne%1000==0) cout<<"Have run "<<ne<<" events ,"<<" Second pass"<<endl;
       t1->GetEntry(ne);

    if(cbin<6||cbin>7) continue;

    for(k1=0; k1<kt; k1++) {
	g02[k1]=1.;
        Qtheta[k1]=0.; 
        dlng02_dz[k1]=0.; 
  for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) {
    for (islc=0; islc<NB_SLICE; islc++) {
      dlng02_dw[k1][islc][islcpt]=0.;
	  }
      }
    }
       Nh=0;
       for(nh=0;nh<rmult;nh++)
	 {
	   if(eta0[nh]<-1.0||eta0[nh]>1.0) continue;

        for(k1=0; k1<kt; k1++)
	  { 
	    Qtheta[k1]+=(1.*cos(2.*phi0[nh]-theta[k1]));
	  }
       Nh++;
	 }
       Nh=0;
       for(nh=0;nh<rmult;nh++)
	 {
	   if(eta0[nh]<-1.0||eta0[nh]>1.0) continue;
      for(islcpt=0;islcpt<NB_SLICE_PT;islcpt++)  
	{
          if((pt0[nh]>minptcut[islcpt]&&pt0[nh]<=maxptcut[islcpt]))
	     inttemp=islcpt;
	}
      islcpt=inttemp;
      islc=0;
      rpmult2[islc][islcpt]+=1.; 
      MeanPt[islcpt]+=pt0[nh];
      MofPt[islcpt]+=1.;
      temp2=0.;

      for(k1=0; k1<kt; k1++) 
	{
	  dlng02_dw[k1][islc][islcpt]+=(cos(2.*phi0[nh]-theta[k1])*(cos(r02[k1]*Qtheta[k1])+i*sin(r02[k1]*Qtheta[k1])));
	}  
      Nh++;
	 } // end of loop over particles

       for(k1=0; k1<kt; k1++)   dlng02_dz[k1]=(Qtheta[k1]*(cos(r02[k1]*Qtheta[k1])+i*sin(r02[k1]*Qtheta[k1])));
    for(k1=0; k1<kt; k1++) {
      dG02_dz[k1]+=dlng02_dz[k1]; 
    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) {
    for (islc=0; islc<NB_SLICE; islc++) {
      dG02_dw[k1][islc][islcpt]+=dlng02_dw[k1][islc][islcpt];
      }     
    } 
    }
     } // end of loop over events


    output.open("output.dat");   
    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) {
      MeanPt[islcpt]/=MofPt[islcpt];
      //cout<<"pt= "<<pt[islcpt]<<", Mean pt = "<<MeanPt[islcpt]<<endl;
    for (islc=0; islc<NB_SLICE; islc++) {
      totmult[islc][islcpt]=rpmult2[islc][islcpt];
      output<<rpmult2[islc][islcpt]/Totevt<<endl;
      //cout<<"  rpmult2 = "<<rpmult2[islc][islcpt<<endl;
	  }
    }

      output<<"chi = "<<chi2<<endl; 
      output.close();

    for(k1=0; k1<kt; k1++){
     dG02_dz[k1]/=Totevt;
    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) {
    for (islc=0; islc<NB_SLICE; islc++) {
	    dG02_dw[k1][islc][islcpt]/=rpmult2[islc][islcpt]; 
	  }
    }
    }

  cout<<"Totevt = "<<Totevt<<"  Trmult = "<<Trmultmean<<endl;

  cout<<"For check#2, <Re>: "<<dG02_dz[3].real()<<" Im: "<<dG02_dz[3].imag()<<endl;

  //////// calcu of v2 .
    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) {
    for (islc=0; islc<NB_SLICE; islc++) {
	    totmult[islc][islcpt]/=Totevt;

      for(k1=0; k1<kt; k1++){
	compratio[k1][islc][islcpt]=dG02_dw[k1][islc][islcpt]/dG02_dz[k1];

	    v22[k1][islc][islcpt]=V2[k1]*compratio[k1][islc][islcpt].real();
	    err22[k1][islc][islcpt]=sqrt((exp(sqr(rootJ0/chi2)/2.) + exp(-sqr(rootJ0/chi2)/2.)*BesselJ0(2.*rootJ0))/totmult[islc][islcpt])/2./J1rootJ0; 

	    v22mean[islc][islcpt]+=v22[k1][islc][islcpt];

	    if(k1==3)  cout<<"real(num/den)= "<<compratio[k1][islc][islcpt].real()<<endl;
    }
    }
    }

    outvdiff.open("vdiff.dat");
    for(k1=0; k1<kt; k1++){
    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) {
    for (islc=0; islc<NB_SLICE; islc++) {
      outvdiff<<v22[k1][islc][islcpt]<<"   "<<err22[k1][islc][islcpt]<<endl;
    }
    }
    }

    outvdiff<<"Totevt = "<<Totevt<<" Tottrack =  "<<Trmultmean<<" <Mult> = "<<Trmultmean/Totevt<<endl;
    outvdiff.close();

    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) { 
    for (islc=0; islc<NB_SLICE; islc++) {
	v22mean[islc][islcpt]/=kt;
    }
    }

   temp2=0.;
   for(k1=0; k1<kt; k1++) 

    temp2+=(exp(sqr(rootJ0/chi2)*cos(theta[k1])/2.)*
	    BesselJ0(2.*rootJ0*sin(theta[k1]/2.)) -
	    exp(-sqr(rootJ0/chi2)*cos(theta[k1])/2.)*
	    BesselJ0(2.*rootJ0*cos(theta[k1]/2.)))*cos(theta[k1]);

    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) 
    for (islc=0; islc<NB_SLICE; islc++) 
    err22mean[islc][islcpt]=sqrt(temp2/totmult[islc][islcpt]/Totevt/kt)/2./J1rootJ0;

    outv2.open("v2.dat");
    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) 
      //outv2<<pt[islcpt]<<"   "<<v22mean[0][islcpt]<<"   "<<err22mean[0][islcpt]<<endl;
      outv2<<MeanPt[islcpt]<<"   "<<v22mean[0][islcpt]<<"   "<<err22mean[0][islcpt]<<endl;
      outv2.close();

    for (islcpt=0; islcpt<NB_SLICE_PT; islcpt++) 
      //cout<<pt[islcpt]<<"   "<<v22mean[0][islcpt]<<"   "<<err22mean[0][islcpt]<<endl;
        cout<<MeanPt[islcpt]<<"   "<<v22mean[0][islcpt]<<"   "<<err22mean[0][islcpt]<<endl; 
 

  TFile *f = new TFile("dist.root","recreate");
  f->cd();

  cent_used->Write();
  npart_used->Write();
  npartsig_used->Write();
  ncoll_used->Write();
  ncollsig_used->Write();
  hpt->Write();
  hphi->Write();
  heta->Write();

  f->Close();

 
}
 
