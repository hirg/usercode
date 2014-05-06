
//#define NPtBin 22
//#define NCentBin 5
//#define NPtBin 50
//#define NCentBin 1
//#define NPtBin 50
#define NPtBin 18  //v4 with trk bins from v1; v5 with trk bins from standard; v6 with trk bins from v3;
//#define NCentBin 44  //v7 ,v8
//#define NCentBin 20  //v9
#define NCentBin 20  //v10

  int nct, nh, ipt, inttemp;
  double Nh, had;
  Int_t rmult=0;
  long nevt=0;
  long Nevt[NCentBin];
  double phi0[20000];
  double pt0[20000];
  double eta0[20000];
  //ref;
  double SumMult[NCentBin];
  double AveMult[NCentBin];
  //diff;
  double SumMultp[NCentBin][NPtBin];
  double AveMultp[NCentBin][NPtBin];
  double Evtp[NCentBin][NPtBin];
//  double minptcut[NPtBin] = {0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9};
//  double maxptcut[NPtBin] = {0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0}; //25
//  double minptcut[NPtBin] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0};
//  double maxptcut[NPtBin] = {0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5,100.0}; //50
  double minptcut[NPtBin] = {0.1, 0.3, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 30.0, 40.0};
  double maxptcut[NPtBin] = {0.3, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 30.0, 40.0, 100.0}; //18
//  double minptcut[NPtBin] = {0.1, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 30.0, 40.0};
//  double maxptcut[NPtBin] = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0, 16.0, 20.0, 30.0, 40.0, 100.0}; //17
//  double minptcut[NPtBin] = {0.1, 1.0, 2.0, 3.0, 4.0,  10.0};
//  double maxptcut[NPtBin] = {1.0, 2.0, 3.0, 4.0, 10.0, 100.0}; //6
  //double minptcut[NPtBin] = {0.1, 3.0, 4.0,  10.0};
  //double maxptcut[NPtBin] = {3.0, 4.0, 10.0, 100.0}; //4
  //double minptcut[NPtBin] = {0.1, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0,  10.0};
  //double maxptcut[NPtBin] = {0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 10.0, 100.0}; //8
//  double minptcut[NPtBin] = {0.3,0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.0,2.5,3.0,3.5,4.0,5.0,6.0,8.0,10.0,12.0,16.0,20.0,30.0,40.0};
//  double maxptcut[NPtBin] = {0.4,0.5,0.6,0.8,1.0,1.2,1.6,2.0,2.5,3.0,3.5,4.0,5.0,6.0,8.0,10.0,12.0,16.0,20.0,30.0,40.0,100.0}; //22

  
  ///ebe;
  double w2, w4, w6, w8;
  double AziCorr22, AziCorr24, AziCorr26, AziCorr28;
  double Q2Re, Q2Im, Q4Re, Q4Im, Q422Re, Q422Im, Q6Re, Q6Im, Q8Re, Q8Im;
  double ptm[NPtBin]; double ptmp[NPtBin]; double mptmp[NCentBin][NPtBin];
  //diff 
  double meanPt[NCentBin][NPtBin];
  double Nhp[NPtBin];  double mqp[NPtBin];
  double w2p[NPtBin], w4p[NPtBin], w6p[NPtBin], w8p[NPtBin];
  double AziCorr22p[NPtBin], AziCorr24p[NPtBin], AziCorr26p[NPtBin], AziCorr28p[NPtBin];
  double q2pRe[NPtBin], q2pIm[NPtBin], q4pRe[NPtBin], q4pIm[NPtBin], q6pRe[NPtBin], q6pIm[NPtBin], q8pRe[NPtBin], q8pIm[NPtBin];
  double mq2pRe[NPtBin], mq2pIm[NPtBin], mq4pRe[NPtBin], mq4pIm[NPtBin], mq6pRe[NPtBin], mq6pIm[NPtBin], mq8pRe[NPtBin], mq8pIm[NPtBin];
  /// all events;
  double AveAziCorr22[NCentBin]; double AveAziCorr24[NCentBin]; double AveAziCorr26[NCentBin];  double AveAziCorr28[NCentBin]; ///save;///#####
  double Cumulant22[NCentBin]; double Cumulant24[NCentBin];  double Cumulant26[NCentBin]; double Cumulant28[NCentBin];
  double V22[NCentBin]; double V24[NCentBin]; double V26[NCentBin]; double V28[NCentBin];
  //diff 
  double AveAziCorr22p[NCentBin][NPtBin]; double AveAziCorr24p[NCentBin][NPtBin]; double AveAziCorr26p[NCentBin][NPtBin]; double AveAziCorr28p[NCentBin][NPtBin]; ///save;///#####
  double Cumulant22p[NCentBin][NPtBin]; double Cumulant24p[NCentBin][NPtBin]; double Cumulant26p[NCentBin][NPtBin]; double Cumulant28p[NCentBin][NPtBin];
  double V22p[NCentBin][NPtBin]; double V24p[NCentBin][NPtBin]; double V26p[NCentBin][NPtBin]; double V28p[NCentBin][NPtBin];
  /// stat. uncertainty related; all events;
  double Sumw2[NCentBin]; double Sumw4[NCentBin];  double Sumw6[NCentBin]; double Sumw8[NCentBin]; ///save;///#####
  double Sumw2w4[NCentBin]; double Sumw2sq[NCentBin]; double Sumw4sq[NCentBin]; ///save;///#####error;
  double Sumw2A2[NCentBin]; double Sumw4A4[NCentBin];  double Sumw6A6[NCentBin]; double Sumw8A8[NCentBin];
  double Sumw2A2sq[NCentBin]; double Sumw4A4sq[NCentBin];
  double Sumw2w4A2A4[NCentBin]; double CovA2A4[NCentBin]; ///save: Sumw2w4A2A4; error;
  double AveAziCorr22sq[NCentBin]; double AveAziCorr24sq[NCentBin]; ///save;///#####error;
  double S2sq[NCentBin]; double S4sq[NCentBin];
  double SV22sq[NCentBin]; double SV24sq[NCentBin];
  //diff
  double Sumw2p[NCentBin][NPtBin]; double Sumw4p[NCentBin][NPtBin];  double Sumw6p[NCentBin][NPtBin]; double Sumw8p[NCentBin][NPtBin]; ///save;///#####
  double Sumw2A2p[NCentBin][NPtBin]; double Sumw4A4p[NCentBin][NPtBin]; double Sumw6A6p[NCentBin][NPtBin]; double Sumw8A8p[NCentBin][NPtBin];
  //diff error
  double Sumw2psq[NCentBin][NPtBin]; double S2psq[NCentBin][NPtBin]; ///save;Sumw2psq; error;
  double AveAziCorr22psq[NCentBin][NPtBin]; double Sumw2pA2psq[NCentBin][NPtBin]; ///save;AveAziCorr22psq;error
  double Sumw2w2p[NCentBin][NPtBin]; double CovA2A2p[NCentBin][NPtBin]; double Sumw2w2pA2A2p[NCentBin][NPtBin]; ///save;Sumw2w2p,Sumw2w2pA2A2p;errpr;
  double Sv22psq[NCentBin][NPtBin];
  double Sumw4psq[NCentBin][NPtBin]; double S4psq[NCentBin][NPtBin]; ///save;Sumw4psq; error;
  double AveAziCorr24psq[NCentBin][NPtBin]; double Sumw4pA4psq[NCentBin][NPtBin]; ///save;AveAziCorr24psq;error
  double Sumw2w4p[NCentBin][NPtBin]; double CovA2A4p[NCentBin][NPtBin]; double Sumw2w4pA2A4p[NCentBin][NPtBin]; ///save; two...;
  double Sumw4w2p[NCentBin][NPtBin]; double CovA4A2p[NCentBin][NPtBin]; double Sumw4w2pA4A2p[NCentBin][NPtBin]; ///save; two...;
  double Sumw4w4p[NCentBin][NPtBin]; double CovA4A4p[NCentBin][NPtBin]; double Sumw4w4pA4A4p[NCentBin][NPtBin]; ///save; two...;
  double Sumw2pw4p[NCentBin][NPtBin]; double CovA2pA4p[NCentBin][NPtBin]; double Sumw2pw4pA2pA4p[NCentBin][NPtBin]; ///save; two...;
  double Sv24psq[NCentBin][NPtBin];

  FILE *outRef, *outDiff;



