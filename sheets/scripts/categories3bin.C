#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TPie.h"
#include "TFile.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include <TCanvas.h>
#include "TROOT.h"

using namespace std;


void categories3bin()
{
    TCanvas* canv ;
    Int_t colors[] = {9, kPink+7, kOrange+8, kBlue+1, kGreen+2, kRed+1};
    
    canv = new TCanvas("canv", "canv", 800, 600);
    gStyle->SetOptStat(0);
    char hname[50];
    vector<TH1F*> cat;
    for (int i = 0; i < 4; ++i) {
        sprintf(hname, "cat%i", i);
        cat.push_back(new TH1F(hname, hname, 10, 0, 10));
    }
    cat[0]->GetXaxis()->SetBinLabel(1, "B2G");
    cat[0]->GetXaxis()->SetBinLabel(2, "BPH");
    cat[0]->GetXaxis()->SetBinLabel(3, "EXO");
    cat[0]->GetXaxis()->SetBinLabel(4, "FSQ");
    cat[0]->GetXaxis()->SetBinLabel(5, "FTR");
    cat[0]->GetXaxis()->SetBinLabel(6, "HIG");
    cat[0]->GetXaxis()->SetBinLabel(7, "HIN");
    cat[0]->GetXaxis()->SetBinLabel(8, "SMP");
    cat[0]->GetXaxis()->SetBinLabel(9, "SUS");
    cat[0]->GetXaxis()->SetBinLabel(10,"TOP");
    cat[0]->SetTitle("");
    
    // >80%  LPC
    cat[0]->SetBinContent(1, 0);
    cat[0]->SetBinContent(2, 0);
    cat[0]->SetBinContent(3, 0);
    cat[0]->SetBinContent(4, 0);
    cat[0]->SetBinContent(5, 1);
    cat[0]->SetBinContent(6, 1);
    cat[0]->SetBinContent(7, 1);
    cat[0]->SetBinContent(8, 1);
    cat[0]->SetBinContent(9, 1);
    cat[0]->SetBinContent(10, 1);
    // Majority LPC (defined as above 50%)
    cat[1]->SetBinContent(1, 0);
    cat[1]->SetBinContent(2, 0);
    cat[1]->SetBinContent(3, 0);
    cat[1]->SetBinContent(4, 0);
    cat[1]->SetBinContent(5, 1);
    cat[1]->SetBinContent(6, 2);
    cat[1]->SetBinContent(7, 2);
    cat[1]->SetBinContent(8, 2);
    cat[1]->SetBinContent(9, 2);
    cat[1]->SetBinContent(10, 2);
    // >40% LPC
    cat[2]->SetBinContent(1, 0);
    cat[2]->SetBinContent(2, 0);
    cat[2]->SetBinContent(3, 0);
    cat[2]->SetBinContent(4, 0);
    cat[2]->SetBinContent(5, 1);
    cat[2]->SetBinContent(6, 2);
    cat[2]->SetBinContent(7, 2);
    cat[2]->SetBinContent(8, 2);
    cat[2]->SetBinContent(9, 2);
    cat[2]->SetBinContent(10, 2);

    float max=0;
    for (int i=0;i<4;++i){
        cat[i]->SetBarOffset(0.15+0.25*i);
        cat[i]->SetBarWidth(0.2);
        cat[i]->SetFillColor(colors[i+1]);
    }
    
    cat[0]->SetMinimum(0);
    cat[0]->SetMaximum(45);
    cat[0]->GetYaxis()->SetTitle("Number of CADI entries");
    TH1 *h1 = cat[0]->DrawCopy("bar5");
    TH1 *h2 = cat[1]->DrawCopy("bar5,same");
    TH1 *h3 = cat[2]->DrawCopy("bar5,same");
    TLegend *legend = new TLegend(0.15,0.75,0.55,0.89);
    legend->SetFillColor(10);
    legend->SetTextSize(0.03);
    legend->SetTextFont(42);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetLineStyle(0);
    legend->AddEntry(h1,"Papers where 80\% US authors are from LPC","f");
    legend->AddEntry(h2,"Papers where 50\% US authors are from LPC","f");
    legend->AddEntry(h3,"Papers where 40\% US authors are from LPC","f");
    legend->Draw();
    canv->SaveAs("LPCmany3bin.png");
    canv->SaveAs("LPCmany3bin.C");
}
