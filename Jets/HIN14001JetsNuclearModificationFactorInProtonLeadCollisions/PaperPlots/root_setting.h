void drawText(const char *text, float xp, float yp, int textSize=15){ 
TLatex *tex = new TLatex(xp,yp,text);
tex->SetTextFont(63);
tex->SetTextSize(20);
tex->SetTextSize(textSize);
tex->SetTextSize(0.05);                                                                                              
tex->SetTextColor(kBlack);
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
void drawCMS(float px, float py, float nLumi=0) {
TLatex *cms = new TLatex(px,py,"CMS Preliminary");
cms->SetTextFont(63);
cms->SetTextSize(18);
cms->SetNDC();
cms->Draw(); 
if(nLumi!=0){
TLatex *lumi = new TLatex(px,py-0.12,Form("#intL dt = %.f nb^{-1}",nLumi));
lumi->SetTextFont(63);
lumi->SetTextSize(18);
lumi->SetNDC();
lumi->Draw();
}
}

void fixedFontHist(TH1 * h, Float_t xoffset=1.3, Float_t yoffset=2.0)
{
//h->SetLabelFont(43,"X");
//h->SetLabelFont(43,"Y");
//h->SetLabelOffset(0.01);
h->SetLabelSize(0.035);
//h->SetTitleFont(44);
h->SetTitleSize(0.035);
h->SetLabelSize(0.035,"Y");
h->SetLabelSize(0.035,"X");
//h->SetTitleFont(43,"Y");
h->SetTitleSize(0.035,"Y");
h->SetTitleSize(0.035,"X");
h->SetTitleOffset(xoffset,"X");
h->SetTitleOffset(yoffset,"Y");
h->GetXaxis()->CenterTitle();
h->GetYaxis()->CenterTitle();
}

void regSun(double x1=0,double y1=0,double x2=1,double y2=1,int color=1, double width=1)
{
TLine* t1 = new TLine(x1,y1,x2,y2);
t1->SetLineWidth(width);
t1->SetLineStyle(3);
t1->SetLineColor(color);
t1->Draw();
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
