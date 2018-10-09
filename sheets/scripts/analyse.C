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
#include "TFile.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include <TCanvas.h>
#include "TROOT.h"
#include "TStyle.h" // gStyle
#include <iomanip>      // std::setprecision
using namespace std;

unsigned int theIndex = 1; // Orduna
std::ofstream theTableHTML("ztable.html");
std::ofstream theCADIcsv("zLPCMajorityCADI.csv");
std::ofstream allCADIcsv("zAllCADI.csv");
std::ofstream PlotContentcsv("zPlotContentCADI.csv");

TCanvas* canv ;
static const char category[6][30] ={"Inactive", "Published", "PAS-Only PUB", "Active", "Published_PAS", "Published_PAS_Active"};
//static const char category[4][20] ={"Inactive", "Published", "PAS-Only PUB", "Active"};
//static const char categorySum[2][30]={"Published+PAS-Only-PUB", "Published+PAS-Only-PUB+Active"};
// inactive 0
// Published 1
// PAS-Only-PUB 2
// active 3
// Published+PAS-Only-PUB 4
// Published+PAS-Only-PUB+Active 5
    int LeastYear(){
        return 16;
    }
    
void categories3bin(std::map<TString,int> map40,
                    std::map<TString,int> map50,
                    std::map<TString,int> map70)
{
    TCanvas* canv2c ;
    Int_t colors[] = {9, kPink+7, kOrange+8, kBlue+1, kGreen+2, kRed+1};
    
    canv2c = new TCanvas("canv2c", "canv2c", 800, 600);
    gStyle->SetOptStat(0);
    char hname[50];
    vector<TH1F*> cat;
    for (int i = 0; i < 4; ++i) {
        sprintf(hname, "cat%i", i);
        cat.push_back(new TH1F(hname, hname, 8, 0, 8));
    }
    cat[0]->GetXaxis()->SetBinLabel(1, "B2G");
    cat[0]->GetXaxis()->SetBinLabel(2, "BPH");
    cat[0]->GetXaxis()->SetBinLabel(3, "EXO");
    cat[0]->GetXaxis()->SetBinLabel(4, "FSQ");
//    cat[0]->GetXaxis()->SetBinLabel(5, "FTR");
    cat[0]->GetXaxis()->SetBinLabel(5, "HIG");
//    cat[0]->GetXaxis()->SetBinLabel(7, "HIN");
    cat[0]->GetXaxis()->SetBinLabel(6, "SMP");
    cat[0]->GetXaxis()->SetBinLabel(7, "SUS");
    cat[0]->GetXaxis()->SetBinLabel(8,"TOP");
    cat[0]->SetTitle("");

    std::map<TString,int> mapPAGnames;
    mapPAGnames["B2G"]=1;
    mapPAGnames["BPH"]=2;
    mapPAGnames["EXO"]=3;
    mapPAGnames["FSQ"]=4;
//    mapPAGnames["FTR"]=5;
    mapPAGnames["HIG"]=5;
//    mapPAGnames["HIN"]=7;
    mapPAGnames["SMP"]=6;
    mapPAGnames["SUS"]=7;
    mapPAGnames["TOP"]=8;

    
    // >70%  LPC
    for(const auto &it : map70) {
        cat[0]->SetBinContent(mapPAGnames[it.first],it.second);
    }
    
    // Majority LPC (defined as above 50%)
    for(const auto &it : map50) {
        cat[1]->SetBinContent(mapPAGnames[it.first],it.second);
    }
    
    // >40% LPC
    for(const auto &it : map40) {
        cat[2]->SetBinContent(mapPAGnames[it.first],it.second);
    }
// cat[3] not used
    float max=0;
    for (int i=0;i<4;++i){
        cat[i]->SetBarOffset(0.15+0.25*i);
        cat[i]->SetBarWidth(0.2);
        cat[i]->SetFillColor(colors[i+1]);
    }
    
    cat[0]->SetMinimum(0);
    cat[0]->SetMaximum(cat[2]->GetMaximum()*1.25);
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
    legend->AddEntry(h1,"Papers where 70\% US authors; 70\% from LPC","f");
    legend->AddEntry(h2,"Papers where 50\% US authors; 50\% from LPC","f");
    legend->AddEntry(h3,"Papers where 30\% US authors; 30\% from LPC","f");
    legend->Draw();
    canv2c->SaveAs("LPCmany3bin.png");
    canv2c->SaveAs("zcode/LPCmany3bin.C");
}
void categories3binActive(std::map<TString,int> map40,
                    std::map<TString,int> map50,
                    std::map<TString,int> map70)
{
    TCanvas* canv3c ;
    Int_t colorsA[] = {9, kPink+7, kOrange+8, kBlue+1, kGreen+2, kRed+1};
    
    canv3c = new TCanvas("canv3c", "canv3c", 800, 600);
    gStyle->SetOptStat(0);
    char hname[50];
    vector<TH1F*> catA;
    for (int i = 0; i < 4; ++i) {
        sprintf(hname, "catA%i", i);
        catA.push_back(new TH1F(hname, hname, 8, 0, 8));
    }
    catA[0]->GetXaxis()->SetBinLabel(1, "B2G");
    catA[0]->GetXaxis()->SetBinLabel(2, "BPH");
    catA[0]->GetXaxis()->SetBinLabel(3, "EXO");
    catA[0]->GetXaxis()->SetBinLabel(4, "FSQ");
//    catA[0]->GetXaxis()->SetBinLabel(5, "FTR");
    catA[0]->GetXaxis()->SetBinLabel(5, "HIG");
//    catA[0]->GetXaxis()->SetBinLabel(7, "HIN");
    catA[0]->GetXaxis()->SetBinLabel(6, "SMP");
    catA[0]->GetXaxis()->SetBinLabel(7, "SUS");
    catA[0]->GetXaxis()->SetBinLabel(8,"TOP");
    catA[0]->SetTitle("");

    std::map<TString,int> mapPAGnamesA;
    mapPAGnamesA["B2G"]=1;
    mapPAGnamesA["BPH"]=2;
    mapPAGnamesA["EXO"]=3;
    mapPAGnamesA["FSQ"]=4;
//    mapPAGnames["FTR"]=5;
    mapPAGnamesA["HIG"]=5;
//    mapPAGnames["HIN"]=7;
    mapPAGnamesA["SMP"]=6;
    mapPAGnamesA["SUS"]=7;
    mapPAGnamesA["TOP"]=8;

    
    // >70%  LPC
    for(const auto &it : map70) {
        catA[0]->SetBinContent(mapPAGnamesA[it.first],it.second);
    }
    
    // Majority LPC (defined as above 50%)
    for(const auto &it : map50) {
        catA[1]->SetBinContent(mapPAGnamesA[it.first],it.second);
    }
    
    // >40% LPC
    for(const auto &it : map40) {
        catA[2]->SetBinContent(mapPAGnamesA[it.first],it.second);
    }

    float max=0;
    for (int i=0;i<4;++i){
        catA[i]->SetBarOffset(0.15+0.25*i);
        catA[i]->SetBarWidth(0.2);
        catA[i]->SetFillColor(colorsA[i+1]);
    }
    
    catA[0]->SetMinimum(0);
    catA[0]->SetMaximum(catA[2]->GetMaximum()*1.25);
    catA[0]->GetYaxis()->SetTitle("Number of CADI entries");
    TH1 *h1A = catA[0]->DrawCopy("bar5");
    TH1 *h2A = catA[1]->DrawCopy("bar5,same");
    TH1 *h3A = catA[2]->DrawCopy("bar5,same");
    TLegend *legend = new TLegend(0.15,0.75,0.55,0.89);
    legend->SetFillColor(10);
    legend->SetTextSize(0.03);
    legend->SetTextFont(42);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetLineStyle(0);
    legend->AddEntry(h1A,"Active analyses where 70\% US authors; 70\% from LPC","f");
    legend->AddEntry(h2A,"Active analyses where 50\% US authors; 50\% from LPC","f");
    legend->AddEntry(h3A,"Active analyses where 30\% US authors; 30\% from LPC","f");
    legend->Draw();
    canv3c->SaveAs("LPCmany3binActive.png");
    canv3c->SaveAs("zcode/LPCmany3binActive.C");
}

std::string trim(const std::string& str, const std::string& whitespace = " \t")
{
    const size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content
    
    const size_t strEnd = str.find_last_not_of(whitespace);
    const size_t strRange = strEnd - strBegin + 1;
    
    return str.substr(strBegin, strRange);
}

class CVSRow
{
public:
    CVSRow(char a=','):separator(a) {}
    std::string const& operator[](std::size_t index) const
    {
        return m_data[index];
    }
    
    float flt(std::size_t index) const
    {
        float f;
        sscanf(m_data[index].c_str(), "%f", &f);
        return f;
    }
    int integer(std::size_t index) const
    {
        int i;
        if (m_data[index]=="-") return 0;
        sscanf(m_data[index].c_str(), "%d", &i);
        return i;
    }
    
    std::size_t size() const
    {
        return m_data.size();
    }
    void readNextRow(std::istream& str)
    {
        std::string         line;
        std::getline(str,line);
        
        std::stringstream   lineStream(line);
        std::string         cell;
        
        m_data.clear();
        while(std::getline(lineStream,cell,separator))
        {
            m_data.push_back(trim(cell));
        }
    }
private:
    std::vector<std::string>    m_data;
    char separator;
};

std::istream& operator>>(std::istream& str,CVSRow& data)
{
    // std::cout << str<<endl;
    data.readNextRow(str);
    return str;
}

class CadiEntry {
public:
    CadiEntry(const CVSRow & row)
    {
        int n = 0;
        code = row[n++];
        status = row[n++];
        samples = row[n++];
        arcChairUSA = row.integer(n++); 
        arcChairLPC = row.integer(n++); 
        arcChairLPCnew = row.integer(n++);
        cadiUSA = row.integer(n++); 
        cadiLPC = row.integer(n++); 
        cadiLPCnew = row.integer(n++);
        arc = row.integer(n++); 
        arcUSA = row.integer(n++); 
        arcLPC = row.integer(n++); 
        arcLPCnew = row.integer(n++);
        anSub = row.integer(n++); 
        anSubUSA = row.integer(n++); 
        anSubLPC = row.integer(n++);
        anSubLPCnew = row.integer(n++);
        anAuth = row.integer(n++); 
        anAuthUSA = row.integer(n++); 
        anAuthLPC = row.integer(n++);
        anAuthLPCnew = row.integer(n++);
        anAuthLPCFel = row.integer(n++);
        anAuthLPCFelChair = row.integer(n++);
        anAuthLPCFelMembers = row.integer(n++);
        inst = row.integer(n++); 
        instUSA = row.integer(n++); 
        instLPC = row.integer(n++); 
        instLPCnew = row.integer(n++);
        n=0;
        //       code2 = row2[n++]; notes = row2[n++];
        //       auth = row2.integer(n++); authUSA = row2.integer(n++);
        //       institutes = row2[n++];
       //   if (code=="SMP-16-002") std::cout<<"SMP-16-002: anAuth: "<<anAuth<<", anAuthUSA: "<<anAuthUSA<<", anAuthLPCnew: "<<anAuthLPCnew<<std::endl;      
    }
    
    bool correct() {
        bool zero = false;
        //    if (code=="TOP-13-003") std::cout << anAuthUSA<<cadiUSA<<anSubUSA<<endl;
        //    if (code=="TOP-13-003") std::cout << anAuthLPCnew<<cadiLPCnew<<anSubLPCnew<<endl;
        if ((anAuthUSA == 0) && (cadiUSA > 0 || anSubUSA > 0)) { ++anAuthUSA; zero = true; }
        if ((anAuthLPCnew == 0) && (cadiLPCnew > 0 || anSubLPCnew >0)) { ++anAuthLPCnew; zero = true; }
        if ((anAuth > 0) && zero) std::cout << "Had to correct " << code << std::endl;
        return zero;
    }
    
    std::string category() {
        std::string theCategory = code.substr(0, 3);
        if (theCategory == "FWD" || theCategory == "GEN") {
            std::cout << "CERN considers " << code << " as FSQ. Adding to FSQ." << std::endl;
            theCategory = "FSQ";
        }
        if (theCategory == "QCD" || theCategory == "EWK") {
            std::cout << "CERN considers " << code << " as SMP. Adding to SMP." << std::endl;
            theCategory = "SMP";
        }
        return theCategory;
    }
    
    bool category(const string & c) {
        return c == code.substr(0, 3);
    }
    
    TString getsamples() {
        return TString(samples);
    }
    
    int year() {
        return atoi(code.substr(4,2).c_str());
    }
    
    bool year(int y) {
        return y == year();
    }
    
    int LPCscholars() {
        return anAuthLPCFel;
    }

    int LPCARCChairscholars() {
        return anAuthLPCFelChair;
    }

    int LPCARCscholars() {
        return anAuthLPCFelMembers;
    }

    //   int cadiYear() {return
    
    /// are there any US authors
    bool isUS() { return (anAuthUSA>0); }
    
    /// are there any US & LPC authors
    bool isUS_LPC(){return (anAuthUSA>0)&&(anAuthLPC>0);}
    
    /// are there any US authors, but no LPC author
    bool isUS_nonLPC(){return (anAuthUSA>0)&&(anAuthLPC==0);}
    
    /// are there any US & LPC authors
    bool isUS_LPCnew(){return (anAuthUSA>0)&&(anAuthLPCnew>0);}
    
    /// are there any US authors, but no LPC author
    bool isUS_nonLPCnew(){return (anAuthUSA>0)&&(anAuthLPCnew==0);}
    
    /// are there any US ARC member
    bool hasArcUS(){return (arcUSA>0);}
    
    /// are there any US & LPC authors
    bool hasArcUS_LPC(){return hasArcUS()&&(arcLPC>0);}
    
    /// are there any US ARC member, but no LPC ARC member
    bool hasArcUS_nonLPC(){return hasArcUS()&&(arcLPC==0);}
    
    /// are there any US & LPC authors
    bool hasArcUS_LPCnew(){return hasArcUS()&&(arcLPCnew>0);}
    
    /// are there any US ARC member, but no LPC ARC member
    bool hasArcUS_nonLPCnew(){return hasArcUS()&&(!hasArcUS_LPCnew());}
    
    /// are there any US ARC member
    bool hasAnyArcUS(){return ((arcUSA>0)||(arcChairUSA>0));}
    
    /// are there any US & LPC authors
    bool hasAnyArcUS_LPC(){return hasAnyArcUS()&&(arcLPC>0);}
    
    /// are there any US ARC member, but no LPC ARC member
    bool hasAnyArcUS_nonLPC(){return hasAnyArcUS()&&(arcLPC==0);}
    
    /// are there any US & LPC authors
    bool hasAnyArcUS_LPCnew(){return hasAnyArcUS()&&((arcLPCnew>0)||(arcChairLPCnew>0));}
    
    /// are there any US ARC member, but no LPC ARC member
    bool hasAnyArcUS_nonLPCnew(){return (hasAnyArcUS()&&(arcLPCnew+arcChairLPCnew==0));}

// new code for majority
//    if ( anAuth>5 ) { std::cout <<"anAuth: "<<anAuth<<std::endl; }
   bool MajAuthNotUS(){return (float)anAuthUSA/anAuth < 0.5; }
   
   bool MajAuthUS(){return (!MajAuthNotUS()); }
   
   bool MajAuthUS_notLPCnew(){return (MajAuthUS()&& ((float)anAuthLPCnew/anAuthUSA)<0.5)  ;}
   
   bool MajAuthUSLPCnew(){return (MajAuthUS()&& ((float)anAuthLPCnew/anAuthUSA)>=0.5) ; }

   
    /// Is a majority of the authors from the US
    bool majorityUS(){return (((float)anAuthUSA/anAuth)>=0.5);}
 

       
    /// Is a majority of the authors from the LPC
    bool majorityLPC(){return (isUS() && ((float)anAuthLPC/anAuthUSA)>=0.5);}
    
    bool majorityUS_LPC(){return majorityUS()&&majorityLPC();}
    
    /// Is a majority of the authors from the LPC
    bool majorityLPCnew(){return (isUS() && ((float)anAuthLPCnew/anAuthUSA)>=0.5);}
    
    bool majorityUS_LPCnew(){return majorityUS()&&majorityLPCnew();}
//	bool majorityUS_LPCnew(){return AuthLPCnew;}
    
    /// Is a majority of the authors from the US, but not from the LPC
    bool majorityUS_nonLPC(){return majorityUS()&&!majorityLPC();}
    
    
    /// Is a majority of the authors from the US, but not from the LPC
    bool majorityUS_nonLPCnew(){return majorityUS()&&!majorityLPCnew();}

// new code for majority 70%
//    if ( anAuth>5 ) { std::cout <<"anAuth: "<<anAuth<<std::endl; }
   bool Maj70AuthNotUS(){return (float)anAuthUSA/anAuth < 0.7; }
   
   bool Maj70AuthUS(){return (!Maj70AuthNotUS()); }
   
   bool Maj70AuthUS_notLPCnew(){return (Maj70AuthUS()&& ((float)anAuthLPCnew/anAuthUSA)<0.7)  ;}
   
   bool Maj70AuthUSLPCnew(){return (Maj70AuthUS()&& ((float)anAuthLPCnew/anAuthUSA)>=0.7) ; }

    /// Is a 70% majority of the authors from the US

    bool majority70US(){return (((float)anAuthUSA/anAuth)>=0.7);}

    /// Is a majority of the authors from the LPC --> see }
    bool majority70LPC(){return (isUS() && ((float)anAuthLPC/anAuthUSA)>=0.7);}
    bool majority70US_LPC(){return majority70US()&&majority70LPC();}

    /// Is a majority of the authors from the LPC
    bool majority70LPCnew(){return (isUS() && ((float)anAuthLPCnew/anAuthUSA)>=0.7);}
    
    bool majority70US_LPCnew(){return majority70US()&&majority70LPCnew();}

    /// Is a 70% majority of the authors from the US, but not from the LPC
    bool majority70US_nonLPCnew(){return majority70US()&&!majority70LPCnew();}

//	bool majorityUS_nonLPC(){return AuthUS_notLPCnew;} 

     /// Is a significant # of the authors from the LPC
    bool significantLPC(){return (isUS() && ((float)anAuthLPC/anAuthUSA)>=0.3);}
        
    /// Is a significant # of the authors from the US
    bool significantUS(){return (((float)anAuthUSA/anAuth)>=0.3);}
    
    bool significantLPCnew(){return (isUS() && ((float)anAuthLPCnew/anAuthUSA)>=0.3);}


    bool significantUS_LPC(){return significantUS()&&significantLPC();}
    
        
    bool significantUS_LPCnew(){return significantUS()&&significantLPCnew();}
//	bool significantUS_LPCnew(){return AuthLPCnew;}
    
    /// Is a significant # of the authors from the US, but not from the LPC
    bool significantUS_nonLPC(){return significantUS()&&!significantLPC();}
    
    
    /// Is a significant of the authors from the US, but not from the LPC
    bool significantUS_nonLPCnew(){return significantUS()&&!significantLPCnew();}
    
    /// are there any US ARC chair
    bool isChairUS()           { return (arcChairUSA > 0); }
    bool isChairUS_LPC()       { return (arcChairUSA > 0) && (arcChairLPC > 0);}
    bool isChairUS_nonLPC()    { return (arcChairUSA > 0) && (arcChairLPC == 0);}
    bool isChairUS_LPCnew()    { return (arcChairUSA > 0) && (arcChairLPCnew > 0);}
    bool isChairUS_nonLPCnew() { return (arcChairUSA > 0) && (arcChairLPCnew == 0);}
    
    /// are there any US ARC Cadi
    bool isCadiUS(){return (cadiUSA>0);}
    
    /// are there any US & LPC authors
    bool isCadiUS_LPC(){return (cadiUSA>0)&&(cadiLPC>0);}
    
    /// are there any US authors, but no LPC author
    bool isCadiUS_nonLPC(){return (cadiUSA>0)&&(cadiLPC==0);}
    
    /// Is a majority of the authors from the US
    /// are there any US & LPC authors
    bool isCadiUS_LPCnew(){return (cadiUSA>0)&&(cadiLPCnew>0);}
    
    /// are there any US authors, but no LPC author
    bool isCadiUS_nonLPCnew(){return (cadiUSA>0)&&(cadiLPCnew==0);}
    /// Is a majority of the authors from the US
    
    
    /**
     * Activity:
     * 	1 = published, submitted or accepted.
     * 	2 = PAS-only-PUB
     * 	3 = active
     * 	0 = all the other states, dormant, etc
     */
// inactive 0
// Published 1
// PAS-Only-PUB 2
// active 3
    
    int activity() {
        //     if ((status.substr(status.length()-3)=="PUB")|| (status=="ACCEPT")) return 1
        // Published, submitted or accepted.
        if ((status.compare(0, 6,  "ACCEPT") == 0) ||
            (status.compare(0, 3,  "PUB") == 0) ||
            (status.compare(0, 11, "ReadyForSub") == 0) ||
            (status.compare(0, 11, "RefComments") == 0) ||
            (status.compare(0, 11, "ReSubmitted") == 0) ||
            (status.compare(0, 5,  "ReSub") == 0) ||
            (status.compare(0, 3,  "SUB") == 0)
            ) return 1;

        // pas-only pub
        if (status.compare(0, 12, "PAS-only-PUB") == 0) return 2;

        // active (previous version had only PUB-Draft)
        if ((status.compare(0, 14, "ARC-GreenLight") == 0) ||
            (status.compare(0, 3, "CWR") == 0) ||
            (status.compare(0, 9, "CWR-ended") == 0) ||
            (status.compare(0, 12, "FinalReading") == 0) ||
            (status.compare(0, 7, "PRE-APP") == 0) ||
            (status.compare(0, 10, "ReadyForLE") == 0) ||
            (status.compare(0, 9, "PUB-Draft") == 0)
            ) return 3;
            
// has no ARC maybe:
//            (status.compare(0, 7, "PRE-APP") == 0) ||
        // inactive
        if ((status.compare(0,4,"Free")==0) || (status.compare(0,7,"Planned")==0) || (status.compare(0,7,"Started")==0) ||
            (status.compare(0,3,"AWG")==0) || (status.compare(0,10,"SUPERSEDED")==0) || (status.compare(0,15,"Thesis-Approved")==0) ||
            (status.compare(0,9,"Completed")==0) || (status.compare(0,8,"Inactive")==0)) return 0;
   // default is active if no other categories are selected above which is why 
   // this will work to fill out more options in active or not (only PRE-APP) and get the same result     
        return 3;
    }
// Published+PAS-Only-PUB 4
int activitySum(){
  if ((activity()==1) || (activity()==2)){ return 4; }
  return 0;
}
// Published+PAS-Only-PUB+Active 5
int activitySumAll(){ 
  if ((activity()==1) || (activity()==2) || (activity()==3)){ return 5; }
  return 0;
}
// activitySum()
// Published+PAS-Only-PUB 0
// Published+PAS-Only-PUB+Active 1
//    int activitySum(){
//  // Published+PAS-Only-PUB 4       
//         if ((status.compare(0, 6,  "ACCEPT") == 0) ||
//             (status.compare(0, 3,  "PUB") == 0) ||
//             (status.compare(0, 11, "ReadyForSub") == 0) ||
//             (status.compare(0, 11, "RefComments") == 0) ||
//             (status.compare(0, 11, "ReSubmitted") == 0) ||
//             (status.compare(0, 5,  "ReSub") == 0) ||
//             (status.compare(0, 3,  "SUB") == 0) ||
//             (status.compare(0, 12, "PAS-only-PUB") == 0) 
//            ) return 4;
//   // Published+PAS-Only-PUB+Active 5   
//   // presuming Active above contains all the possible statuses then sum will equal sum of plots. 
//   // If it doesn't, you're missing a CADI status from Active and below. 
//         if ((status.compare(0, 6,  "ACCEPT") == 0) ||
//             (status.compare(0, 3,  "PUB") == 0) ||
//             (status.compare(0, 11, "ReadyForSub") == 0) ||
//             (status.compare(0, 11, "RefComments") == 0) ||
//             (status.compare(0, 11, "ReSubmitted") == 0) ||
//             (status.compare(0, 5,  "ReSub") == 0) ||
//             (status.compare(0, 3,  "SUB") == 0) ||
//             (status.compare(0, 12, "PAS-only-PUB") == 0)  ||
//             (status.compare(0, 14, "ARC-GreenLight") == 0) ||
//             (status.compare(0, 3, "CWR") == 0) ||
//             (status.compare(0, 9, "CWR-ended") == 0) ||
//             (status.compare(0, 12, "FinalReading") == 0) ||
//             (status.compare(0, 7, "PRE-APP") == 0) ||
//             (status.compare(0, 10, "ReadyForLE") == 0) ||
//             (status.compare(0, 9, "PUB-Draft") == 0)          
//            ) return 5;   
//      return 5;
//    }

    int TonjesPrint(){
       float LPC_frac = 0;
       if (anAuthUSA==0){
          LPC_frac = 0;
       } else {
          LPC_frac = (float)anAuthLPCnew/anAuthUSA;
       }
       float USAfrac = 0;
       if (anAuth==0){
          USAfrac = 0;
       } else {
          USAfrac = (float)anAuthUSA/anAuth;
       }       
       if (activity() == 1 && majorityUS_LPCnew() && year()>=LeastYear() ){
       	std::cout << "analyse.C plot published analysis: " << code << ", total auth: " << anAuth << ", anAuthUSA: " << anAuthUSA << ", anAuthLPCnew: " << anAuthLPCnew << ", anAuthUSA/anAuth: " << USAfrac << ", anAuthLPCnew/anAuthUSA: " << LPC_frac << std::endl;
       	std::cout << "select analyse.C plot published analysis with >=0.5 LPCnew authors : " << code << ", booleans: majorityUS_nonLPCnew(): "<<majorityUS_nonLPCnew()<<", majorityUS(): " << majorityUS() << ", majorityUS_LPCnew(): " << majorityUS_LPCnew() <<", just for check: majorityLPCnew(): "<<majorityLPCnew()<< std::endl;
//       	std::cout << "analyse.C plot check pub, analysis: " << code << ", my version: MajAuthUS_notLPCnew(): "<<MajAuthUS_notLPCnew()<< ", MajAuthUS(): " << MajAuthUS() << ", MajAuthUSLPCnew(): " << MajAuthUSLPCnew() <<", MajAuthNotUS(): " << MajAuthNotUS()<<  std::endl;
       }
       if (activity() == 1 && significantUS_LPCnew() && year()>=LeastYear() ){       
       	std::cout << "select analyse.C plot published analysis with >=0.3 LPCnew authors : " << code << ", booleans: significantUS_nonLPCnew(): "<<significantUS_nonLPCnew()<<", significantUS(): " << significantUS() << ", significantUS_LPCnew(): " << significantUS_LPCnew() <<", just for check: significantLPCnew(): "<<significantLPCnew()<< std::endl;
       }
       if (activity() == 1 && year()>=LeastYear() ){  
        std::cout << "ALL analyse.C plot published analysis: " << code << ", total auth: " << anAuth << ", anAuthUSA: " << anAuthUSA << ", anAuthLPCnew: " << anAuthLPCnew << ", anAuthUSA/anAuth: " << USAfrac << ", anAuthLPCnew/anAuthUSA: " << LPC_frac << std::endl;     
       	std::cout << "ALL analyse.C plot published analysis: " << code << ", booleans: significantUS_nonLPCnew(): "<<significantUS_nonLPCnew()<<", significantUS(): " << significantUS() << ", significantUS_LPCnew(): " << significantUS_LPCnew() <<", just for check: significantLPCnew(): "<<significantLPCnew()<< std::endl;
       }       
       if (activity() == 3 && majorityUS_LPCnew() && year()>=LeastYear()){
       	std::cout << "analyse.C plot Active analysis: " << code << ", total auth: " << anAuth << ", anAuthUSA: " << anAuthUSA << ", anAuthLPCnew: " << anAuthLPCnew << ", anAuthUSA/anAuth: " << USAfrac << ", anAuthLPCnew/anAuthUSA: " << LPC_frac << std::endl;
       	std::cout << "select analyse.C plot Active analysis with >=0.5 LPCnew authors : " << code << ", booleans: majorityUS_nonLPCnew(): "<<majorityUS_nonLPCnew()<<", majorityUS(): " << majorityUS() << ", majorityUS_LPCnew(): " << majorityUS_LPCnew() <<", just for check: majorityLPCnew(): "<<majorityLPCnew()<< std::endl;
//       	std::cout << "analyse.C plot check pub, analysis: " << code << ", my version: MajAuthUS_notLPCnew(): "<<MajAuthUS_notLPCnew()<< ", MajAuthUS(): " << MajAuthUS() << ", MajAuthUSLPCnew(): " << MajAuthUSLPCnew() <<", MajAuthNotUS(): " << MajAuthNotUS()<<  std::endl;
       }  
        if (activity() == 3 && significantUS_LPCnew() && year()>=LeastYear()){
       	std::cout << "select analyse.C plot Active analysis with >=0.3 LPCnew authors : " << code << ", booleans: significantUS_nonLPCnew(): "<<significantUS_nonLPCnew()<<", significantUS(): " << significantUS() << ", significantUS_LPCnew(): " << significantUS_LPCnew() <<", just for check: significantLPCnew(): "<<significantLPCnew()<< std::endl;
       }
       if (activity() == 2 && majorityUS_LPCnew() && year()>=LeastYear()){
       	std::cout << "analyse.C plot PAS-only analysis: " << code << ", total auth: " << anAuth << ", anAuthUSA: " << anAuthUSA << ", anAuthLPCnew: " << anAuthLPCnew << ", anAuthUSA/anAuth: " << USAfrac << ", anAuthLPCnew/anAuthUSA: " << LPC_frac << std::endl;
       	std::cout << "select analyse.C plot PAS-only analysis with >=0.5 LPCnew authors : " << code << ", booleans: majorityUS_nonLPCnew(): "<<majorityUS_nonLPCnew()<<", majorityUS(): " << majorityUS() << ", majorityUS_LPCnew(): " << majorityUS_LPCnew() <<", just for check: majorityLPCnew(): "<<majorityLPCnew()<< std::endl;
//       	std::cout << "analyse.C plot check pub, analysis: " << code << ", my version: MajAuthUS_notLPCnew(): "<<MajAuthUS_notLPCnew()<< ", MajAuthUS(): " << MajAuthUS() << ", MajAuthUSLPCnew(): " << MajAuthUSLPCnew() <<", MajAuthNotUS(): " << MajAuthNotUS()<<  std::endl;
       }  
       if (activity() == 2 && significantUS_LPCnew() && year()>=LeastYear()){
        	std::cout << "select analyse.C plot PAS-only analysis with >=0.3 LPCnew authors : " << code << ", booleans: significantUS_nonLPCnew(): "<<significantUS_nonLPCnew()<<", significantUS(): " << significantUS() << ", significantUS_LPCnew(): " << significantUS_LPCnew() <<", just for check: significantLPCnew(): "<<significantLPCnew()<< std::endl;
       }     
       if (majorityUS_LPCnew() && activity()!=0 && year()>=LeastYear()){
            theCADIcsv<<code<<","<<activity()<<","<<anAuth<<","<<anAuthUSA<<","<<anAuthLPCnew<<","<<(float)anAuthUSA/anAuth<<","<<(float)anAuthLPCnew/anAuthUSA<<","<<majorityUS_LPCnew()<<","<<majorityLPCnew()<<","<<majorityUS_nonLPCnew()<<","<<majorityUS()<<",>=0.5 LPCnew/USA"<<std::endl;          
       }
       float myUSAfrac = -1.;
       if (anAuth > 0) { myUSAfrac = (float)anAuthUSA/anAuth; }
       allCADIcsv<<code<<","<<activity()<<","<<anAuth<<","<<anAuthUSA<<","<<myUSAfrac<<","<<majorityUS()<<","<<significantUS()<<std::endl;          
       return 0;
    }
   void IfCalculate ( bool CalcAuthNotUS, bool CalcAuthLPCnew, bool CalcAuthUS_notLPCnew ){
//   if ( anAuth > 15 )  Int_t variable=1; 
//	{
    bool NoAuth = false;
    if ( anAuth == 0){
      NoAuth = true;
       	 	CalcAuthLPCnew = false;
       	 	CalcAuthNotUS = false;
       	 	CalcAuthUS_notLPCnew = false;       
    }
	if ( (!NoAuth) && ((float)anAuthUSA/anAuth < 0.5) ) 
    {
     CalcAuthNotUS = true;
     CalcAuthLPCnew = false;
     CalcAuthUS_notLPCnew = false;  
  	} 
  	else {
		if ( (!NoAuth) &&((float)anAuthLPCnew/anAuthUSA >= 0.5 )){
// bool = 1 for US LPC
       	 	CalcAuthLPCnew = true;
       	 	CalcAuthNotUS = false;
       	 	CalcAuthUS_notLPCnew = false; 
		}
		else if ((!NoAuth)){
// bool = 1 true for US nonLPC  
       	 	CalcAuthUS_notLPCnew = true;
        	CalcAuthLPCnew = false;
        	CalcAuthNotUS = false;
		}  
	}
//	if (activity() == 1){
//		std::cout << "analyse.C plot check, analysis: " << code << ", my version IfCalculate: NoAuth: "<<NoAuth<<", CalcAuthUS_notLPCnew: " << CalcAuthUS_notLPCnew << ", CalcAuthLPCnew: " << CalcAuthLPCnew <<", CalcAuthNotUS: " << CalcAuthNotUS <<  std::endl;
 //   }
 
   }

    
public:
    string code, status, samples;
    int arcChairUSA, arcChairLPC, cadiUSA, cadiLPC, arc, arcUSA, arcLPC,
    anSub, anSubUSA, anSubLPC, anAuth, anAuthUSA, anAuthLPC,
    inst, instUSA, instLPC, anSubLPCnew, anAuthLPCnew, anAuthLPCFel, anAuthLPCFelChair, anAuthLPCFelMembers;
    int arcChairLPCnew, cadiLPCnew, arcLPCnew, instLPCnew;
    
    
    
    //   string code2, notes, institutes;
    //  int auth, authUSA;
    
};

vector<string> groups, PAG;
std::map<TString,int> PAGcounts30;
std::map<TString,int> PAGcounts50;
std::map<TString,int> PAGcounts70;

std::map<TString,int> PAGcounts30A;
std::map<TString,int> PAGcounts50A;
std::map<TString,int> PAGcounts70A;

TH1F* prepareHisto(string a, const vector<string> & list = PAG)
{
    TH1F* histo = new TH1F(a.c_str(),a.c_str(),list.size(),0.,list.size());
    for (unsigned int j = 0;j<list.size();++j) {
        histo->GetXaxis()->SetBinLabel(j+1, list[j].c_str());
        //       active->Fill(groups[j].c_str(),1.0);
        //       std::cout << groups[j].c_str()<<endl;
    }
    histo->LabelsOption("v", "X");
    return histo;
    // all->SetNdivisions(26);
}

TH2F* prepareHisto2D(string a, const vector<string> & list = PAG)
{
    TH2F* histo = new TH2F(a.c_str(),a.c_str(),list.size(),0.,list.size(), 6, -0.5, 5.5);
    for (unsigned int j = 0;j<list.size();++j) {
        histo->GetXaxis()->SetBinLabel(j+1, list[j].c_str());
        //       active->Fill(groups[j].c_str(),1.0);
        //       std::cout << groups[j].c_str()<<endl;
    }
    histo->LabelsOption("v", "X");
    return histo;
    // all->SetNdivisions(26);
}

THStack* tstack(TH2* histo, string nameOfFile, bool print=false, TString axis="CADI entries")
{
    std::string name = "";
    histo->LabelsDeflate("X");
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    
    TH1D* pub = histo->ProjectionX("a", 2, 2);
    pub->SetFillColor(kBlue+1);
    mystack->Add(pub);
    TH1D* pas = histo->ProjectionX("b", 3, 3);
    pas->SetFillColor(kRed+2);
    mystack->Add(pas);
    TH1D* act = histo->ProjectionX("c", 4, 4);
    act->SetFillColor(kCyan+2);
    mystack->Add(act);
    //   mystack->LabelsOption("v", "X");
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << nameOfFile << std::endl;
        std::cout << "Published: " << pub->GetEntries() << std::endl;
        std::cout << "PAS-only- PUB: " << pas->GetEntries() << std::endl;
        std::cout << "Active: " << act->GetEntries() << std::endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a><br></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "Published: " << pub->GetEntries() << "<br>" << std::endl;
        theTableHTML << "PAS-only- PUB: " << pas->GetEntries() << "<br>" << std::endl;
        theTableHTML << "Active: " << act->GetEntries() << "</td></tr>" << std::endl;
    }

    TLegend *leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
//    TLegend * leg = new TLegend(0.6, 0.725, 0.88, 0.875, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    leg->AddEntry(pub, "Published", "f");
    leg->AddEntry(pas, "PAS-Only Pub", "f");
    leg->AddEntry(act, "Active", "f");
    mystack->Draw();
    leg->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    title = TString("Number of ")+axis;
    mystack->GetYaxis()->SetTitle(title);
    mystack->GetYaxis()->SetTitleOffset(1.3) ;    
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    return mystack;
    
}

THStack* DRstack(TH2* histo, string nameOfFile, bool print=false, TString axis="CADI entries")
{
    std::string name = "";
    histo->LabelsDeflate("X");
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    
    TH1D* pub = histo->ProjectionX("a", 2, 2);
    pub->SetFillColor(kBlue+1);
    mystack->Add(pub);
    TH1D* pas = histo->ProjectionX("b", 3, 3);
    pas->SetFillColor(kRed+2);
    mystack->Add(pas);
    TH1D* act = histo->ProjectionX("c", 4, 4);
    act->SetFillColor(kCyan+2);
    mystack->Add(act);
    //   mystack->LabelsOption("v", "X");
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << nameOfFile << std::endl;
        std::cout << "Published or PAS-only-PUB: " << pub->GetEntries() << std::endl;
//        std::cout << "PAS-only- PUB: " << pas->GetEntries() << std::endl;
//        std::cout << "Active: " << act->GetEntries() << std::endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a><br></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "Published or PAS-only-PUB: " << pub->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "PAS-only- PUB: " << pas->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Active: " << act->GetEntries() << "</td></tr>" << std::endl;
    }

    TLegend *leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
//    TLegend * leg = new TLegend(0.6, 0.725, 0.88, 0.875, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    leg->AddEntry(pub, "Published/PAS", "f");
//    leg->AddEntry(pas, "PAS-Only Pub", "f");
//    leg->AddEntry(act, "Active", "f");
    mystack->Draw();
    leg->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    title = TString("Number of ")+axis;
    mystack->GetYaxis()->SetTitle(title);
    mystack->GetYaxis()->SetTitleOffset(1.3) ;    
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    return mystack;
    
}
THStack* cat1stack(TH2* histo, string nameOfFile, bool print=false, TString axis="CADI entries")
{
    std::string name = "";
    histo->LabelsDeflate("X");
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    
    TH1D* pub = histo->ProjectionX("a", 2, 2);
    pub->SetFillColor(kBlue+1);
    mystack->Add(pub);
    TH1D* pas = histo->ProjectionX("b", 3, 3);
    pas->SetFillColor(kRed+2);
    mystack->Add(pas);
    TH1D* act = histo->ProjectionX("c", 4, 4);
    act->SetFillColor(kCyan+2);
    mystack->Add(act);
    //   mystack->LabelsOption("v", "X");
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << nameOfFile << std::endl;
        std::cout << "Published: " << pub->GetEntries() << std::endl;
//        std::cout << "PAS-only- PUB: " << pas->GetEntries() << std::endl;
//        std::cout << "Active: " << act->GetEntries() << std::endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a><br></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "Published: " << pub->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "PAS-only- PUB: " << pas->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Active: " << act->GetEntries() << "</td></tr>" << std::endl;
    }

    TLegend *leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
//    TLegend * leg = new TLegend(0.6, 0.725, 0.88, 0.875, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    leg->AddEntry(pub, "Published", "f");
//    leg->AddEntry(pas, "PAS-Only Pub", "f");
//    leg->AddEntry(act, "Active", "f");
    mystack->Draw();
    leg->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    title = TString("Number of ")+axis;
    mystack->GetYaxis()->SetTitle(title);
    mystack->GetYaxis()->SetTitleOffset(1.3) ;    
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    return mystack;
    
}

THStack* cat2stack(TH2* histo, string nameOfFile, bool print=false, TString axis="CADI entries")
{
    std::string name = "";
    histo->LabelsDeflate("X");
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    
    TH1D* pub = histo->ProjectionX("a", 2, 2);
    pub->SetFillColor(kBlue+1);
    mystack->Add(pub);
    TH1D* pas = histo->ProjectionX("b", 3, 3);
    pas->SetFillColor(kRed+2);
    mystack->Add(pas);
    TH1D* act = histo->ProjectionX("c", 4, 4);
    act->SetFillColor(kCyan+2);
    mystack->Add(act);
    //   mystack->LabelsOption("v", "X");
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << nameOfFile << std::endl;
        std::cout << "PAS-Only: " << pub->GetEntries() << std::endl;
//        std::cout << "PAS-only- PUB: " << pas->GetEntries() << std::endl;
//        std::cout << "Active: " << act->GetEntries() << std::endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a><br></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "PAS-Only: " << pub->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "PAS-only- PUB: " << pas->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Active: " << act->GetEntries() << "</td></tr>" << std::endl;
    }

    TLegend *leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
//    TLegend * leg = new TLegend(0.6, 0.725, 0.88, 0.875, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    leg->AddEntry(pub, "PAS-Only", "f");
//    leg->AddEntry(pas, "PAS-Only Pub", "f");
//    leg->AddEntry(act, "Active", "f");
    mystack->Draw();
    leg->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    title = TString("Number of ")+axis;
    mystack->GetYaxis()->SetTitle(title);
    mystack->GetYaxis()->SetTitleOffset(1.3) ;    
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    return mystack;
    
}
THStack* cat3stack(TH2* histo, string nameOfFile, bool print=false, TString axis="CADI entries")
{
    std::string name = "";
    histo->LabelsDeflate("X");
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    
    TH1D* pub = histo->ProjectionX("a", 2, 2);
    pub->SetFillColor(kBlue+1);
    mystack->Add(pub);
    TH1D* pas = histo->ProjectionX("b", 3, 3);
    pas->SetFillColor(kRed+2);
    mystack->Add(pas);
    TH1D* act = histo->ProjectionX("c", 4, 4);
    act->SetFillColor(kCyan+2);
    mystack->Add(act);
    //   mystack->LabelsOption("v", "X");
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << nameOfFile << std::endl;
        std::cout << "Active: " << pub->GetEntries() << std::endl;
//        std::cout << "Active- PUB: " << pas->GetEntries() << std::endl;
//        std::cout << "Active: " << act->GetEntries() << std::endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a><br></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "Active: " << pub->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Active- PUB: " << pas->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Active: " << act->GetEntries() << "</td></tr>" << std::endl;
    }

    TLegend *leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
//    TLegend * leg = new TLegend(0.6, 0.725, 0.88, 0.875, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    leg->AddEntry(pub, "Active", "f");
//    leg->AddEntry(pas, "Active Pub", "f");
//    leg->AddEntry(act, "Active", "f");
    mystack->Draw();
    leg->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    title = TString("Number of ")+axis;
    mystack->GetYaxis()->SetTitle(title);
    mystack->GetYaxis()->SetTitleOffset(1.3) ;    
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    return mystack;
    
}
THStack* cat4stack(TH2* histo, string nameOfFile, bool print=false, TString axis="CADI entries")
{
    std::string name = "";
    histo->LabelsDeflate("X");
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    
    TH1D* pub = histo->ProjectionX("a", 2, 2);
    pub->SetFillColor(kBlue+1);
    mystack->Add(pub);
    TH1D* pas = histo->ProjectionX("b", 3, 3);
    pas->SetFillColor(kRed+2);
    mystack->Add(pas);
    TH1D* act = histo->ProjectionX("c", 4, 4);
    act->SetFillColor(kCyan+2);
    mystack->Add(act);
    //   mystack->LabelsOption("v", "X");
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << nameOfFile << std::endl;
        std::cout << "Published+PAS: " << pub->GetEntries() << std::endl;
//        std::cout << "Published+PAS- PUB: " << pas->GetEntries() << std::endl;
//        std::cout << "Published+PAS: " << act->GetEntries() << std::endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a><br></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "Published+PAS: " << pub->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Published+PAS- PUB: " << pas->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Published+PAS: " << act->GetEntries() << "</td></tr>" << std::endl;
    }

    TLegend *leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
//    TLegend * leg = new TLegend(0.6, 0.725, 0.88, 0.875, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    leg->AddEntry(pub, "Published+PAS", "f");
//    leg->AddEntry(pas, "Published+PAS Pub", "f");
//    leg->AddEntry(act, "Published+PAS", "f");
    mystack->Draw();
    leg->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    title = TString("Number of ")+axis;
    mystack->GetYaxis()->SetTitle(title);
    mystack->GetYaxis()->SetTitleOffset(1.3) ;    
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    return mystack;
    
}
THStack* cat5stack(TH2* histo, string nameOfFile, bool print=false, TString axis="CADI entries")
{
    std::string name = "";
    histo->LabelsDeflate("X");
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    
    TH1D* pub = histo->ProjectionX("a", 2, 2);
    pub->SetFillColor(kBlue+1);
    mystack->Add(pub);
    TH1D* pas = histo->ProjectionX("b", 3, 3);
    pas->SetFillColor(kRed+2);
    mystack->Add(pas);
    TH1D* act = histo->ProjectionX("c", 4, 4);
    act->SetFillColor(kCyan+2);
    mystack->Add(act);
    //   mystack->LabelsOption("v", "X");
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << nameOfFile << std::endl;
        std::cout << "Published+PAS+Active: " << pub->GetEntries() << std::endl;
//        std::cout << "Published+PAS+Active- PUB: " << pas->GetEntries() << std::endl;
//        std::cout << "Published+PAS+Active: " << act->GetEntries() << std::endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a><br></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "Published+PAS+Active: " << pub->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Published+PAS+Active- PUB: " << pas->GetEntries() << "<br>" << std::endl;
 //       theTableHTML << "Published+PAS+Active: " << act->GetEntries() << "</td></tr>" << std::endl;
    }

    TLegend *leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
//    TLegend * leg = new TLegend(0.6, 0.725, 0.88, 0.875, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    leg->AddEntry(pub, "Published+PAS+Active", "f");
//    leg->AddEntry(pas, "Published+PAS+Active Pub", "f");
//    leg->AddEntry(act, "Published+PAS+Active", "f");
    mystack->Draw();
    leg->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    title = TString("Number of ")+axis;
    mystack->GetYaxis()->SetTitle(title);
    mystack->GetYaxis()->SetTitleOffset(1.3) ;    
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    return mystack;
    
}

THStack* combine(TH2* histo, TH2F* US, TH2F* US_LPC, TH2F* US_nonLP, string nameOfFile, string auth, string yAxis = "")
{
    std::string name = "";
    
    histo->LabelsDeflate("X");
    
    vector<TH1D *> nonus;
    vector<TH1D *> us;
    vector<TH1D *> us_lpc;
    vector<TH1D *> us_nonlpc;
    
    THStack* mystack = new THStack(name.c_str(), name.c_str());

    for (int bin = 2; bin < 5; bin++) {
        nonus    .push_back(   histo->ProjectionX((name+"a").c_str(), bin, bin));
        us       .push_back(      US->ProjectionX((name+"b").c_str(), bin, bin));
        us_lpc   .push_back(  US_LPC->ProjectionX((name+"c").c_str(), bin, bin));
        us_nonlpc.push_back(US_nonLP->ProjectionX((name+"d").c_str(), bin, bin));
        std::cout << "testOrduna nous:"      << (    nonus.at(bin-2))->GetEntries() << std::endl;
        std::cout << "testOrduna us:"        << (       us.at(bin-2))->GetEntries() << std::endl;
        std::cout << "testOrduna us_lpc:"    << (   us_lpc.at(bin-2))->GetEntries() << std::endl;
        std::cout << "testOrduna us_nonlpc:" << (us_nonlpc.at(bin-2))->GetEntries() << std::endl;
        
        nonus.at(bin-2)->SetFillColor(46);
        mystack->Add(nonus.at(bin-2));
    }
    TH1D *nonusTot = nonus.at(0);
    TH1D *usTot = us.at(0) ;
    TH1D *us_lpcTot = us_lpc.at(0) ;
    TH1D *us_nonlpcTot = us_nonlpc.at(0) ;
    
    for (theIndex = 0; theIndex < 10; theIndex++) {
        nonusTot->SetBinContent(theIndex, nonus.at(0)->GetBinContent(theIndex)+nonus.at(1)->GetBinContent(theIndex)+nonus.at(2)->GetBinContent(theIndex));
        usTot   ->SetBinContent(theIndex, us.at(0)->GetBinContent(theIndex)+us.at(1)->GetBinContent(theIndex)+us.at(2)->GetBinContent(theIndex));
        us_lpcTot->SetBinContent(theIndex, us_lpc.at(0)->GetBinContent(theIndex)+us_lpc.at(1)->GetBinContent(theIndex)+us_lpc.at(2)->GetBinContent(theIndex));
        us_nonlpcTot->SetBinContent(theIndex, us_nonlpc.at(0)->GetBinContent(theIndex)+us_nonlpc.at(1)->GetBinContent(theIndex)+us_nonlpc.at(2)->GetBinContent(theIndex));
    }
    std::cout << "testOrduna nonusTot:" << nonusTot->GetEntries() << std::endl;
    std::cout << "testOrduna usTot:" << usTot->GetEntries() << std::endl;
    std::cout << "testOrduna us_lpcTot:" << us_lpcTot->GetEntries() << std::endl;
    std::cout << "testOrduna us_nonlpcTot:" << us_nonlpcTot->GetEntries() << std::endl;
    
//    nonus->Add(us,-1.);
//    nonus->SetFillColor(46);
//    mystack->Add(nonus);
//    us_lpc->SetFillColor(30);
//    mystack->Add(us_lpc);
//    us_nonlpc->SetFillColor(38);
//    mystack->Add(us_nonlpc);
//    //   mystack->LabelsOption("v", "X");
//    
//    
//    mystack->Draw();
//    mystack->GetYaxis()->SetTitle(yAxis.c_str());
//    mystack->GetYaxis()->SetTitleOffset(1.1) ;
//    mystack->SetMaximum(mystack->GetMaximum()*1.25);
//    
//    TLegend * leg;
//    //if (max<60)
//    leg = new TLegend(0.15, 0.85, 0.4, 0.94, "","brNDC");
//    //else leg = new TLegend(0.45, 0.85, 0.8, 0.94, "","brNDC");
//    leg->SetFillColor(10);
//    leg->SetTextSize(0.03);
//    leg->SetTextFont(42);
//    leg->SetBorderSize(0);
//    leg->SetFillStyle(0);
//    leg->SetLineStyle(0);
//    char hname[50];
//    sprintf(hname, "%s not from US", auth.c_str());
//    leg->AddEntry(nonus, hname, "f");
//    sprintf(hname, "%s from US, LPC", auth.c_str());
//    // Orduna: next line commented out 05/19/16
//    //    if (name.find("New")==std::string::npos) sprintf(hname, "%s-I", hname);
//    leg->AddEntry(us_lpc,hname, "f");
//    sprintf(hname, "%s from US, non-LPC", auth.c_str());
//    // Orduna: next line commented out 05/19/16
//    //    if (name.find("New")==std::string::npos) sprintf(hname, "%s-I", hname);
//    leg->AddEntry(us_nonlpc, hname, "f");
//    leg->Draw();
//    
//    TLatex* text1 = new TLatex(3.570061,23.08044,category[bin-1]);
//    text1->SetNDC();
//    text1->SetTextAlign(13);
//    text1->SetX(0.17);
//    text1->SetY(0.989);
//    text1->SetTextFont(42);
//    text1->SetTextSizePixels(24);
//    text1->Draw();
//    
//    canv->SaveAs((nameOfFile+".png").c_str());
//    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
//    
//    THStack* mystack2 = new THStack(name.c_str(),name.c_str());
//    //     std::cout << nonus->GetBinContent(1.)<<endl;
//    //     std::cout << us->GetBinContent(1.)<<endl;
//    //     std::cout << us_lpc->GetBinContent(1.)<<endl;
//    //     std::cout << us_nonlpc->GetBinContent(1.)<<endl;
//    nonus->SetFillColor(46);
//    mystack2->Add(nonus);
//    us->SetFillColor(38);
//    mystack2->Add(us);
//    
//    mystack2->Draw();
//    mystack2->GetYaxis()->SetTitle(yAxis.c_str());
//    mystack2->GetYaxis()->SetTitleOffset(1.1) ;
//    mystack2->SetMaximum(mystack2->GetMaximum()*1.15);
//    
//    //   TLegend * leg;
//    delete leg;
//    //if (max<60)
//    leg = new TLegend(0.15, 0.85, 0.4, 0.94, "","brNDC");
//    //else leg = new TLegend(0.45, 0.85, 0.8, 0.94, "","brNDC");
//    leg->SetFillColor(10);
//    leg->SetTextSize(0.03);
//    leg->SetTextFont(42);
//    leg->SetBorderSize(0);
//    leg->SetFillStyle(0);
//    leg->SetLineStyle(0);
//    sprintf(hname, "%s not from US", auth.c_str());
//    leg->AddEntry(nonus, hname, "f");
//    sprintf(hname, "%s from US", auth.c_str());
//    leg->AddEntry(us,hname, "f");
//    leg->Draw();
//    
//    text1->Draw();
//    
//    
//    canv->SaveAs((nameOfFile+"_uscms.png").c_str());
    
    
    return mystack;
    
}


THStack* tstack(int bin, TH2* histo, TH2F* US, TH2F* US_LPC, TH2F* US_nonLP, string nameOfFile, string auth, string yAxis="", bool print=false)
{
    std::string name = "";
    
    histo->LabelsDeflate("X");
    
    THStack* mystack = new THStack(name.c_str(),name.c_str());
    TH1D *nonus     = histo->ProjectionX((name+"a").c_str(), bin, bin);
    TH1D *us        = US->ProjectionX((name+"b").c_str(), bin, bin);
    TH1D *us_lpc    = US_LPC->ProjectionX((name+"c").c_str(),bin, bin);
    TH1D *us_nonlpc = US_nonLP->ProjectionX((name+"d").c_str(),bin, bin);
    
    if (print) {
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        std::cout << auth << " " << nameOfFile << std::endl;
        std::cout << "All: " << nonus->GetEntries() << std::endl;
        std::cout << "US:  " << us->GetEntries() << " -> " << us->GetEntries()/nonus->GetEntries() << std::endl;
        std::cout << "LPC: " << us_lpc->GetEntries() << " -> " << us_lpc->GetEntries()/us->GetEntries()*100 << "% -> " << us_lpc->GetEntries()/nonus->GetEntries()*100 << "% from all" << std::endl;
        //      std::cout << "us_nonlpc "<<us_nonlpc->GetBinContent(3)<<endl;
        //     std::cout << "NonUS: "<<nonus->GetBinContent(3)<<endl;
        std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
        theTableHTML << "<tr><td><a href='" << nameOfFile << ".png'><img src='" << nameOfFile << ".png' height='200' alt='" << nameOfFile << ".png'></a></td>" << std::endl;
        theTableHTML << "<td>" << nameOfFile << "<br>" << std::endl;
        theTableHTML << "All: " << nonus->GetEntries() << "<br>" << std::endl;
        theTableHTML << "USCMS:  " << us->GetEntries() << "<br>" << std::endl;
        theTableHTML << "LPC: " << us_lpc->GetEntries() << "</td></tr>" << std::endl;
//        std::cout << nonus->GetEntries() << '\t' << us->GetEntries() << '\t' << us_lpc->GetEntries() << '\t' << us_nonlpc->GetEntries() << std::endl;
//        int test ; std::cin >> test;
    }
// calculate nonUS by leftover CADI entries?    
    nonus->Add(us,-1.);
    nonus->SetFillColor(46);
    mystack->Add(nonus);
    us_lpc->SetFillColor(38);
    mystack->Add(us_lpc);
    us_nonlpc->SetFillColor(kYellow-9);
    mystack->Add(us_nonlpc);
    //   mystack->LabelsOption("v", "X");
    
    
    mystack->Draw();
    mystack->GetXaxis()->SetRangeUser(0,PAG.size());
    mystack->GetYaxis()->SetTitle(yAxis.c_str());
    mystack->GetYaxis()->SetTitleOffset(1.15) ;
    mystack->SetMaximum(mystack->GetMaximum()*1.25);
    std::cout << "mystack name "<<nameOfFile<<", has Maximum: "<<mystack->GetMaximum()*1.125<<std::endl;
    
    TLegend * leg;
    //if (max<60)
    leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
    //else leg = new TLegend(0.45, 0.85, 0.8, 0.94, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    char hname[50];
    sprintf(hname, "%s not from US", auth.c_str());
    leg->AddEntry(nonus, hname, "f");
    sprintf(hname, "%s from US, LPC", auth.c_str());
    // Orduna: next line commented out 05/19/16
//    if (name.find("New")==std::string::npos) sprintf(hname, "%s-I", hname);
    leg->AddEntry(us_lpc,hname, "f");
    sprintf(hname, "%s from US, non-LPC", auth.c_str());
    // Orduna: next line commented out 05/19/16
//    if (name.find("New")==std::string::npos) sprintf(hname, "%s-I", hname);
    leg->AddEntry(us_nonlpc, hname, "f");
    leg->Draw();
    
    TLatex* text1 = new TLatex(3.570061,23.08044,category[bin-1]);
    text1->SetNDC();
    text1->SetTextAlign(13);
    text1->SetX(0.13);
    text1->SetY(0.95);
    text1->SetTextFont(42);
    text1->SetTextSizePixels(24);
    text1->Draw();
    
    canv->SaveAs((nameOfFile+".png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+".C").c_str());
    
    THStack* mystack2 = new THStack(name.c_str(),name.c_str());
    //     std::cout << nonus->GetBinContent(1.)<<endl;
    //     std::cout << us->GetBinContent(1.)<<endl;
    //     std::cout << us_lpc->GetBinContent(1.)<<endl;
    //     std::cout << us_nonlpc->GetBinContent(1.)<<endl;
    nonus->SetFillColor(46);
    mystack2->Add(nonus);
    us->SetFillColor(30);
    mystack2->Add(us);
    
    mystack2->Draw();
    mystack2->GetXaxis()->SetRangeUser(0,PAG.size());
    mystack2->GetYaxis()->SetTitle(yAxis.c_str());
    mystack2->GetYaxis()->SetTitleOffset(1.15) ;
    mystack2->SetMaximum(mystack2->GetMaximum()*1.25);
    
    //   TLegend * leg;
    delete leg;
    //if (max<60)
    leg = new TLegend(0.15, 0.775, 0.4, 0.875, "","brNDC");
    //else leg = new TLegend(0.45, 0.85, 0.8, 0.94, "","brNDC");
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetLineStyle(0);
    sprintf(hname, "%s not from US", auth.c_str());
    leg->AddEntry(nonus, hname, "f");
    sprintf(hname, "%s from US", auth.c_str());
    leg->AddEntry(us,hname, "f");
    leg->Draw();
    
    text1->Draw();
    
    
    canv->SaveAs((nameOfFile+"_uscms.png").c_str());
    canv->SaveAs(("zcode/"+nameOfFile+"_uscms.C").c_str());
    
    
    return mystack;
    
}

void startTableHTML() {
    theTableHTML << "<html><head></head><body><center><table style='width:50%'><tbody>" << std::endl;
    theTableHTML << "<br>Plots below use papers from 2016-2018.<br>" << std::endl;
    theTableHTML << "<br>CADI queried Oct. 8, 2018 4:45pm.<br>" << std::endl;
    theTableHTML << "Plots that have 'New' in the names use April 2016 LPC survey + 2016-2018 DR(US) + 2015-(Summer)2018 G&V(US) + 2017 LPC office survey for LPC assignment."  << std::endl;
    theTableHTML << "<br>Plots with <i>Scholars</i> in the name use Distinguished Researchers for selection.<br>"<< std::endl;
}

void startCADIcsv(){
    theCADIcsv <<"Code,Status(1=pub;2=PAS;3=Active),anAuth,anAuthUSA,anAuthLPCnew,anAuthUSA/anAuth,anAuthLPCnew/anAuthUSA,majorityUS_LPCnew(),majorityLPCnew(),majorityUS_nonLPCnew(),majorityUS(),Notes"<<std::endl;
    allCADIcsv <<"CADI entry,Status(1=pub;2=PAS;3=Active),total AN note Authors,AN Note AuthorsUSA,(AN Authors USA)/(total AN Authors),majorityUS boolean, significantUS boolean"<<std::endl;
}

void endTableHTML() {
    theTableHTML << "</tbody></table></center></body></html>" << std::endl;
}

void analyse()
{
    startTableHTML();
    startCADIcsv();
    gROOT->SetBatch();
    canv = new TCanvas("canv", "canv", 600, 600);
    
    groups.push_back("B2G");
    groups.push_back("BPH");
    groups.push_back("BTV");
    groups.push_back("CFT");
    groups.push_back("DIF");
    groups.push_back("EGM");
    groups.push_back("EWK");
    groups.push_back("EXO");
    groups.push_back("FSQ");
    groups.push_back("FTR");
    groups.push_back("FWD");
    groups.push_back("GEN");
    groups.push_back("HIG");
    groups.push_back("HIN");
    groups.push_back("JME");
    groups.push_back("LUM");
    groups.push_back("MUO");
    groups.push_back("PFT");
    groups.push_back("PRF");
    groups.push_back("QCD");
    groups.push_back("SBM");
    groups.push_back("SMP");
    groups.push_back("SUS");
    groups.push_back("TAU");
    groups.push_back("TOP");
    groups.push_back("TRG");
    groups.push_back("TRK");
    
    PAG=std::vector<string>(0);
    PAG.push_back("B2G"); // CERN plots: b2gs = [ B2G ]
    PAG.push_back("BPH"); // CERN plots: bphs = [ BPH ]
    //   PAG.push_back("DIF");
    //   PAG.push_back("EWK");
    PAG.push_back("EXO"); // CERN plots: exos = [ EXO ]
    PAG.push_back("FSQ"); // CERN plots: fwds = [ FWD, FSQ, GEN ]
    //PAG.push_back("FTR");
    //   PAG.push_back("FWD");
    PAG.push_back("HIG"); // CERN plots: higs = [ HIG ]
    //PAG.push_back("HIN"); // CERN plots: hins = [ HIN ]
      // PAG.push_back("QCD");
    PAG.push_back("SMP"); // CERN plots: smps = [ SMP, QCD, EWK ]
    PAG.push_back("SUS"); // CERN plots: suss = [ SUS ]
    PAG.push_back("TOP"); // CERN plots: tops = [ TOP ]
    
    for(size_t i=0; i < PAG.size(); i++) {
        PAGcounts30[PAG.at(i).c_str()]=0;
        PAGcounts50[PAG.at(i).c_str()]=0;
        PAGcounts70[PAG.at(i).c_str()]=0;
        PAGcounts30A[PAG.at(i).c_str()]=0;
        PAGcounts50A[PAG.at(i).c_str()]=0;
        PAGcounts70A[PAG.at(i).c_str()]=0;
    }

    vector<CadiEntry> entries;
    
    std::ifstream  file("sheet5.csv");
    CVSRow row('|');
    //   std::ifstream  file2("sheet3.csv");
    //   CVSRow row2('|');
    
    int i = 0;
    file >> row;
    //   file2 >> row2;
    int wrong = 0;
    while(file >> row)
    {
        
        //      std::cout << "plouc " << i<<" "<<row[0]<<" "<<row[1]<<"\n";
        //      std::cout <<row[0].length()<<endl;
        if (row[0].length()==10) {
            entries.push_back(CadiEntry(row));
            entries.back().correct();
            entries.back().TonjesPrint(); // make void, just print content of specific instance of class
            bool MyCalcAuthNotUS = false;
            bool MyCalcAuthLPCnew = false; 
            bool MyCalcAuthUS_notLPCnew = false;           
            entries.back().IfCalculate(MyCalcAuthNotUS, MyCalcAuthLPCnew, MyCalcAuthUS_notLPCnew);
            //       if (entries.back().correct()){
            // // (entries.back().category()=="SUS")(entries.back().cadiUSA>0) && (entries.back().anAuth>0)
            // //       if  ((entries.back().year()>11)&& (entries.back().cadiUSA>0) && (entries.back().anAuthUSA==0)&&(entries.back().activity()==1)){
            //        //if ((entries.back().majorityUS()) &&  (entries.back().category()=="FTR")) {
            //        std::cout << i<<" "<<entries.back().code<<" "<<entries.back().status<<" "<<entries.back().category()<<" "<<entries.back().cadiUSA<<" ";
            //        std::cout << entries.back().cadiLPC<<" "<<entries.back().cadiLPCnew
            // //        <<" "<<entries.back().isUS()<<" "<<entries.back().isUS_LPC()<<" "<<entries.back().isUS_nonLPC()
            // //  	<<" "<<entries.back().activity()
            // 	<<"\n";
            // 	++wrong;
            // }
            ++i;
        }
    }
    // bits leading to this commented out? std::cout << "wrong entries " << wrong << std::endl;
    //   return;
    TFile* rootfile = new TFile("zcode/analysis.root","RECREATE");
    
    TH1F* all = prepareHisto("all");
    
    TH1F* active = prepareHisto("active");
    TH1F* withUSauthors = prepareHisto("withUSauthors");
    TH1F* withUS_LPCauthors = prepareHisto("withUS_LPCauthors");
    TH1F* withUS_nonLPCauthors = prepareHisto("withUS_nonLPCauthors");
    
    TH1F* majUSauthors = prepareHisto("majUSauthors");
    TH1F* majUS_LPCauthors = prepareHisto("majUS_LPCauthors");
    TH1F* majUS_nonLPCauthors = prepareHisto("majUS_nonLPCauthors");
    
    TH2F* active2D = prepareHisto2D("active2D");
    TH2F* active1auth2D = prepareHisto2D("active1auth2D");
    TH2F* activeMany2D = prepareHisto2D("activeMany2D");
    TH2F* withUSauthors2D = prepareHisto2D("withUSauthors2D");
    TH2F* withUS_LPCauthors2D = prepareHisto2D("withUS_LPCauthors2D");
    TH2F* withUS_nonLPCauthors2D = prepareHisto2D("withUS_nonLPCauthors2D");
    TH2F* withUS_LPCnewauthors2D = prepareHisto2D("withUS_LPCnewauthors2D");
    TH2F* withUS_nonLPCnewauthors2D = prepareHisto2D("withUS_nonLPCnewauthors2D");
    TH2F* withUS_LPCScholars2D = prepareHisto2D("LPCscholars");
    TH2F* withUS_LPCNumScholars2D = prepareHisto2D("nLPCscholars");
    TH2F* withUS_LPCARCChairScholars2D = prepareHisto2D("LPCARCChairscholars");
    TH2F* withUS_LPCARCScholars2D = prepareHisto2D("nLPCARCscholars");
    TH2F* withUS_LPCNumARCScholars2D = prepareHisto2D("nLPCNumARCscholars");
 
// more scholars plots
    TH2F* withUS_LPCScholarsActive2D = prepareHisto2D("LPCscholarsActive");
    TH2F* withUS_LPCNumScholarsActive2D = prepareHisto2D("nLPCscholarsActive");
    TH2F* withUS_LPCScholarsPublished2D = prepareHisto2D("LPCscholarsPublished");
    TH2F* withUS_LPCNumScholarsPublished2D = prepareHisto2D("nLPCscholarsPublished");
    TH2F* withUS_LPCScholarsPASOnly2D = prepareHisto2D("LPCscholarsPASOnly");
    TH2F* withUS_LPCNumScholarsPASOnly2D = prepareHisto2D("nLPCscholarsPASOnly");    
    TH2F* withUS_LPCScholarsPublished_PAS2D = prepareHisto2D("LPCscholarsPublished_PAS");
    TH2F* withUS_LPCNumScholarsPublished_PAS2D = prepareHisto2D("nLPCscholarsPublished_PAS");
    TH2F* withUS_LPCScholarsPublished_PAS_Active2D = prepareHisto2D("LPCscholarsPublished_PAS_Active");
    TH2F* withUS_LPCNumScholarsPublished_PAS_Active2D = prepareHisto2D("nLPCscholarsPublished_PAS_Active"); 
    
    TH2F* majUSauthors2D = prepareHisto2D("majUSauthors2D");
    TH2F* majUS_LPCauthors2D = prepareHisto2D("majUS_LPCauthors2D");
    TH2F* majUS_nonLPCauthors2D = prepareHisto2D("majUS_nonLPCauthors2D");
    TH2F* majUS_LPCnewauthors2D = prepareHisto2D("majUS_LPCnewauthors2D");
    TH2F* majUS_nonLPCnewauthors2D = prepareHisto2D("majUS_nonLPCnewauthors2D");

// majority 70 numbers:    
///*
    TH1F* maj70USauthors = prepareHisto("maj70USauthors");
    TH1F* maj70US_LPCauthors = prepareHisto("maj70US_LPCauthors");
    TH1F* maj70US_nonLPCauthors = prepareHisto("maj70US_nonLPCauthors");
    
    TH2F* maj70USauthors2D = prepareHisto2D("maj70USauthors2D");
    TH2F* maj70US_LPCauthors2D = prepareHisto2D("maj70US_LPCauthors2D");
    TH2F* maj70US_nonLPCauthors2D = prepareHisto2D("maj70US_nonLPCauthors2D");
    TH2F* maj70US_LPCnewauthors2D = prepareHisto2D("maj70US_LPCnewauthors2D");
    TH2F* maj70US_nonLPCnewauthors2D = prepareHisto2D("maj70US_nonLPCnewauthors2D");    

    TH2F* signifUSauthors2D = prepareHisto2D("signifUSauthors2D");
    TH2F* signifUS_LPCauthors2D = prepareHisto2D("signifUS_LPCauthors2D");
    TH2F* signifUS_nonLPCauthors2D = prepareHisto2D("signifUS_nonLPCauthors2D");
    TH2F* signifUS_LPCnewauthors2D = prepareHisto2D("signifUS_LPCnewauthors2D");
    TH2F* signifUS_nonLPCnewauthors2D = prepareHisto2D("signifUS_nonLPCnewauthors2D");
  
    TH2F* MymajauthorsNonUS2D = prepareHisto2D("MymajauthorsNonUS2D");
    TH2F* MymajUSauthors2D = prepareHisto2D("MymajUSauthors2D");
    TH2F* MymajUS_LPCnewauthors2D = prepareHisto2D("MymajUS_LPCnewauthors2D");
    TH2F* MymajUS_nonLPCnewauthors2D = prepareHisto2D("MymajUS_nonLPCnewauthors2D");    

    TH2F* CalcmajauthorsNonUS2D = prepareHisto2D("CalcmajauthorsNonUS2D");
    TH2F* CalcmajUSauthors2D = prepareHisto2D("CalcmajUSauthors2D");
    TH2F* CalcmajUS_LPCnewauthors2D = prepareHisto2D("CalcmajUS_LPCnewauthors2D");
    TH2F* CalcmajUS_nonLPCnewauthors2D = prepareHisto2D("CalcmajUS_nonLPCnewauthors2D");   
    
    TH2F* chairUS2D = prepareHisto2D("chairUS2D");
    TH2F* chairLPC2D = prepareHisto2D("chairLPC2D");
    TH2F* chairnonLPC2D = prepareHisto2D("chairnonLPC2D");
    TH2F* chairLPCnew2D = prepareHisto2D("chairLPCnew2D");
    TH2F* chairnonLPCnew2D = prepareHisto2D("chairnonLPCnew2D");
    
    TH2F* contactUS2D = prepareHisto2D("contactUS2D");
    TH2F* contactLPC2D = prepareHisto2D("contactLPC2D");
    TH2F* contactnonLPC2D = prepareHisto2D("contactnonLPC2D");
    TH2F* contactLPCnew2D = prepareHisto2D("contactLPCnew2D");
    TH2F* contactnonLPCnew2D = prepareHisto2D("contactnonLPCnew2D");
    
    TH2F* arcUS2D = prepareHisto2D("arcUS2D");
    TH2F* arcLPC2D = prepareHisto2D("arcLPC2D");
    TH2F* arcnonLPC2D = prepareHisto2D("arcnonLPC2D");
    TH2F* arcLPCnew2D = prepareHisto2D("arcLPCnew2D");
    TH2F* arcnonLPCnew2D = prepareHisto2D("arcnonLPCnew2D");
    
    TH2F* arcCMUS2D = prepareHisto2D("arcCMUS2D");
    TH2F* arcCMLPCnew2D = prepareHisto2D("arcCMLPCnew2D");
    TH2F* arcCMnonLPCnew2D = prepareHisto2D("arcCMnonLPCnew2D");
    
    TH2F* totArc2D = prepareHisto2D("totArc2D");
    TH2F* totArcUS2D = prepareHisto2D("totArcUS2D");
    TH2F* totArcLPC2D = prepareHisto2D("totArcLPC2D");
    TH2F* totArcnonLPC2D = prepareHisto2D("totArcnonLPC2D");
    TH2F* totArcLPCnew2D = prepareHisto2D("totArcLPCnew2D");
    TH2F* totArcnonLPCnew2D = prepareHisto2D("totArcnonLPCnew2D");

    TH2F* totAuthors2D = prepareHisto2D("totAuthors2D");
    TH2F* totAuthorsUS2D = prepareHisto2D("totAuthorsUS2D");
    TH2F* totAuthorsLPCnew2D = prepareHisto2D("totAuthorsLPCnew2D");
    TH2F* totAuthorsnonLPCnew2D = prepareHisto2D("totAuthorsnonLPCnew2D");
    
    TH2F* totArcCM2D = prepareHisto2D("totarcCM2D");
    TH2F* totArcCMUS2D = prepareHisto2D("totarcCMUS2D");
    TH2F* totArcCMLPCnew2D = prepareHisto2D("totarcCMLPCnew2D");
    TH2F* totArcCMnonLPCnew2D = prepareHisto2D("totarcCMnonLPCnew2D");
    
    vector<TH1F*> nbrAuth, fracUS, fracLPC, fracNonLPC, arcFracUS, arcFracLPC, arcFracNonLPC, fracLPCnew, fracNonLPCnew, arcFracLPCnew, arcFracNonLPCnew, nbrARC;
    vector<TH2F*> usVsLpcFrac, usVsLpcNbr,usVsLPCnewFrac, usVsLPCnewNbr;
    
    char hname[50], name[50];
    for (int j = 0; j < 6; ++j) {
        sprintf(hname, "nbrARC%i", j);
        sprintf(name, "Number of ARC members, category %i", j);
        nbrARC.push_back(new TH1F(hname, name,10,-0.5,9.5));
        
        sprintf(hname, "nbrAuth%i", j);
        sprintf(name, "Number of authors, category %i", j);
        nbrAuth.push_back(new TH1F(hname, name,50,0.,50.));
        
        sprintf(hname, "fracUS%i", j);
        sprintf(name, "fraction of US authors, category %i", j);
        fracUS.push_back(new TH1F(hname, name,21,0.,1.05));
        sprintf(hname, "fracLPC%i", j);
        sprintf(name, "fraction of US authors from LPC, category %i", j);
        fracLPC.push_back(new TH1F(hname, name,21,0.,1.05));
        sprintf(hname, "fracNonLPC%i", j);
        sprintf(name, "fraction of US authors not LPC, category %i", j);
        fracNonLPC.push_back(new TH1F(hname, name,21,0.,1.05));
        sprintf(hname, "fracLPCnew%i", j);
        sprintf(name, "fraction of US authors from LPCnew, category %i", j);
        fracLPCnew.push_back(new TH1F(hname, name,21,0.,1.05));
        sprintf(hname, "fracNonLPCnew%i", j);
        sprintf(name, "fraction of US authors not LPCnew, category %i", j);
        fracNonLPCnew.push_back(new TH1F(hname, name,21,0.,1.05));
        
        sprintf(hname, "arcFracUS%i", j);
        sprintf(name, "Fraction of US ARC members, category %i", j);
        arcFracUS.push_back(new TH1F(hname, name,21,0.,1.05));
        sprintf(hname, "arcFracLPC%i", j);
        sprintf(name, "Fraction of US ARC members from LPC, category %i", j);
        arcFracLPC.push_back(new TH1F(hname, name,21,0.,1.05));
        sprintf(hname, "arcFracNonLPC%i", j);
        sprintf(name, "Fraction of US ARC members not LPC, category %i", j);
        arcFracNonLPC.push_back(new TH1F(hname, name,21,0.,1.05));
        
        sprintf(hname, "arcFracLPCnew%i", j);
        sprintf(name, "Fraction of US ARC members from LPC, category %i", j);
        arcFracLPCnew.push_back(new TH1F(hname, name,21,0.,1.05));
        sprintf(hname, "arcFracNonLPCnew%i", j);
        sprintf(name, "Fraction of US ARC members not LPC, category %i", j);
        arcFracNonLPCnew.push_back(new TH1F(hname, name,21,0.,1.05));
        
        sprintf(hname, "usVsLpcFrac%i", j);
        sprintf(name, "Fraction of US authors from LPC vs. US authors, category %i", j);
        usVsLpcFrac.push_back(new TH2F(hname,name,10, 0., 1.1, 10, 0., 1.1));
        
        sprintf(hname, "usVsLpcNbr%i", j);
        sprintf(name, "Numbers of US authors from LPC vs. US authors, category %i", j);
        usVsLpcNbr.push_back(new TH2F(hname,name,8, 0., 40., 6, 0., 1.2));
        
        sprintf(hname, "usVsLPCnewFrac%i", j);
        sprintf(name, "Fraction of US authors from LPCnew vs. US authors, category %i", j);
        usVsLPCnewFrac.push_back(new TH2F(hname,name,6, 0., 1.2, 6, 0., 1.2));
        
        sprintf(hname, "usVsLPCnewNbr%i", j);
        sprintf(name, "Numbers of US authors from LPCnew vs. US authors, category %i", j);
        usVsLPCnewNbr.push_back(new TH2F(hname,name,8, 0., 40., 6, 0., 1.2));
        
        nbrAuth[j]         ->SetFillColor(kGray);
        fracUS[j]          ->SetFillColor(kGray);
        fracLPC[j]         ->SetFillColor(kGray);
        fracNonLPC[j]      ->SetFillColor(kGray);
        arcFracUS[j]       ->SetFillColor(kGray);
        arcFracLPC[j]      ->SetFillColor(kGray);
        arcFracNonLPC[j]   ->SetFillColor(kGray);
        arcFracLPCnew[j]   ->SetFillColor(kGray);
        arcFracNonLPCnew[j]->SetFillColor(kGray);
        usVsLpcFrac[j]     ->SetFillColor(kGray);
        usVsLpcNbr[j]      ->SetFillColor(kGray);
        fracLPCnew[j]      ->SetFillColor(kGray);
        fracNonLPCnew[j]   ->SetFillColor(kGray);
        usVsLPCnewFrac[j]  ->SetFillColor(30);
        usVsLPCnewNbr[j]   ->SetFillColor(30);
    }
    
    // Fraction of ARC members
    int count = 0;
    int arc = 0, arcUSA = 0, arcLPC = 0;
    int arcCh = 0, arcChUSA = 0, arcChLPC = 0;
    int count40 = 0, count50 = 0, count70 = 0;
    
    for (int j = 0; j < i; ++j) {
        all->Fill(entries[j].category().c_str(),1.0);
        // Select year
        // 2012
//        if (entries[j].year() < 12) continue ;

        // 2012-2014
//        if (entries[j].year() < 12 || entries[j].year() > 14) continue ;
        
        // 2015 and after
        // if (entries[j].year() < 15) continue ;
        
        // Select run
        //if (entries[j].getsamples() == "Run1") continue;
        //if (entries[j].getsamples() == "Run2") continue;
        if(entries[j].year() < LeastYear()) continue;
        std::cout <<"Checking each CADI entry, j:"<< j<<", entries[j].code(): "<<entries[j].code<<", entries[j].year(): "<<entries[j].year()<<", entries[j].status: "<<entries[j].status<<", entries[j].activity(): "<<entries[j].activity()<< std::endl;
        
        // Select only PAGs
        if (find(PAG.begin(),PAG.end(),entries[j].category().c_str())==PAG.end()) continue;
        
        //      if (entries[j].anAuth<2 && entries[j].activity()>0 && entries[j].arc<2) {
        //       std::cout << j<<" "<<entries[j].code<<" "<<entries[j].year()<<" "<<entries[j].year(13)<<"- ";
        //       std::cout << entries[j].anAuth<<" "<<entries[j].arc<<" "<<entries[j].arcChairUSA<<" "<<entries[j].isUS_LPC()<<" "<<entries[j].isUS_nonLPC()
        //  	<<" "<<entries[j].activity()
        // 	<<"\n";
        // 	}
        
        nbrAuth[entries[j].activity()]->Fill(entries[j].anAuth);
        
        // Plot of fraction of US/LPC authors, for cadi with >1 authors
        if (entries[j].anAuth>1)
            fracUS[entries[j].activity()]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth);
        if ((entries[j].anAuth>1) && (entries[j].anAuthUSA>0)) {
            fracLPC[entries[j].activity()]->Fill((float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            fracNonLPC[entries[j].activity()]->Fill(1-((float)entries[j].anAuthLPC/entries[j].anAuthUSA));
            usVsLpcFrac[entries[j].activity()]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth, (float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            usVsLpcNbr[entries[j].activity()]->Fill(entries[j].anAuthUSA, (float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            
            fracLPCnew[entries[j].activity()]->Fill((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
            fracNonLPCnew[entries[j].activity()]->Fill(1-((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA));
            usVsLPCnewFrac[entries[j].activity()]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth, (float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
            //        if (entries[j].activity()==1){cout << "-"<<entries[j].code
            // //        <<" "<<entries[j].status
            // //        <<" "<<entries[j].category()
            //        <<"\t"<<entries[j].anAuth<<"\t";
            //        std::cout << entries[j].anAuthUSA//<<"\t"<<entries[j].cadiLPCnew
            // //        <<"\t"<<entries[j].anAuthLPC
            //        <<"\t"<<entries[j].anAuthLPCnew
            //        <<"\t"<<((float)entries[j].anAuthUSA/entries[j].anAuth)
            //        <<"\t"<<((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)
            //        <<endl;}
            usVsLPCnewNbr[entries[j].activity()]->Fill(entries[j].anAuthUSA, (float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
        }
        
        // Plot of fraction of US/LPC arcs, for cadi with >1 authors
        if (entries[j].arc>0)
            arcFracUS[entries[j].activity()]->Fill((float) entries[j].arcUSA/entries[j].arc);
        if (entries[j].arc>0)
            nbrARC[entries[j].activity()]->Fill((float) entries[j].arc);
        if ((entries[j].arc>0) && (entries[j].arcUSA>0)) {
            arcFracLPC[entries[j].activity()]->Fill((float)entries[j].arcLPC/entries[j].arcUSA);
            arcFracNonLPC[entries[j].activity()]->Fill(1-((float)entries[j].arcLPC/entries[j].arcUSA));
            arcFracLPCnew[entries[j].activity()]->Fill((float)entries[j].arcLPCnew/entries[j].arcUSA);
            arcFracNonLPCnew[entries[j].activity()]->Fill(1-((float)entries[j].arcLPCnew/entries[j].arcUSA));
        }
        
        // 2D plots of authors
        if (entries[j].activity()>-1 ) {
            if (entries[j].anAuth<=0) active1auth2D->Fill(entries[j].category().c_str(), entries[j].activity(),1.0);
            else {
               // not filled if anAuth<0, try anAuth <=0 !
                activeMany2D->Fill(entries[j].category().c_str(),entries[j].activity(),1.0);
                if (entries[j].isUS()) withUSauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].isUS_LPC()) withUS_LPCauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].isUS_nonLPC()) withUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].isUS_LPCnew()) withUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].isUS_nonLPCnew()) withUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].LPCscholars() > 0 && (entries[j].activity() == 2 || entries[j].activity() == 1)) {
                    withUS_LPCNumScholars2D->Fill(entries[j].category().c_str(), 1, entries[j].LPCscholars());
                    withUS_LPCScholars2D->Fill(entries[j].category().c_str(), 1, 1);
                }
                if (entries[j].LPCARCscholars() > 0 && (entries[j].activity() == 2 || entries[j].activity() == 1)) {
                    withUS_LPCNumARCScholars2D->Fill(entries[j].category().c_str(), 1, entries[j].LPCARCscholars());
                    withUS_LPCARCScholars2D->Fill(entries[j].category().c_str(), 1, 1);
                }
                if (entries[j].LPCARCChairscholars() > 0 && (entries[j].activity() == 2 || entries[j].activity() == 1)) {
                    withUS_LPCARCChairScholars2D->Fill(entries[j].category().c_str(), 1, 1);
                }
// more scholars plots
                if (entries[j].LPCscholars() > 0 && (entries[j].activity() == 1)) {
                    withUS_LPCNumScholarsPublished2D->Fill(entries[j].category().c_str(), 1, entries[j].LPCscholars());
                    withUS_LPCScholarsPublished2D->Fill(entries[j].category().c_str(), 1, 1);
                }    
                
                 if ((entries[j].LPCscholars() > 0) && (entries[j].activity() == 2)) {
                    withUS_LPCNumScholarsPASOnly2D->Fill(entries[j].category().c_str(), 1, entries[j].LPCscholars());
                    withUS_LPCScholarsPASOnly2D->Fill(entries[j].category().c_str(), 1, 1);
                }                   
                 if ((entries[j].LPCscholars() > 0) && (entries[j].activity() == 3)) {
                    withUS_LPCNumScholarsActive2D->Fill(entries[j].category().c_str(), 1, entries[j].LPCscholars());
                    withUS_LPCScholarsActive2D->Fill(entries[j].category().c_str(), 1, 1);
                }                        
                  if ((entries[j].LPCscholars() > 0) && ( (entries[j].activity() == 1) || (entries[j].activity() == 2) )) {
                    withUS_LPCNumScholarsPublished_PAS2D->Fill(entries[j].category().c_str(), 1, entries[j].LPCscholars());
                    withUS_LPCScholarsPublished_PAS2D->Fill(entries[j].category().c_str(), 1, 1);
                }                     
                  if ((entries[j].LPCscholars() > 0) && ((entries[j].activity() == 1)||(entries[j].activity() == 2) || (entries[j].activity() == 3))) {
                    withUS_LPCNumScholarsPublished_PAS_Active2D->Fill(entries[j].category().c_str(), 1, entries[j].LPCscholars());
                    withUS_LPCScholarsPublished_PAS_Active2D->Fill(entries[j].category().c_str(), 1, 1);
                }    
//                
                if (entries[j].majorityUS()) {majUSauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                    // 	if (entries[j].category()=="FTR") std::cout << "Found : "<<entries[j].code<< " "<<entries[j].activity() << "	"<<majUSauthors2D->GetBinContent(7,3)<<endl;
                }
                if (entries[j].majorityUS_LPC()) majUS_LPCauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].majorityUS_nonLPC()) majUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].majorityUS_LPCnew()) majUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].majorityUS_nonLPCnew()) majUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);

                if (entries[j].significantUS()) signifUSauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].significantUS_LPC()) signifUS_LPCauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].significantUS_nonLPC()) signifUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].significantUS_LPCnew()) signifUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].significantUS_nonLPCnew()) signifUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                
                if (entries[j].MajAuthUS()) MymajUSauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].MajAuthNotUS()) MymajauthorsNonUS2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].MajAuthUSLPCnew()) MymajUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].MajAuthUS_notLPCnew()) MymajUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);  

//                if (entries[j].NoAuth) CalcNOauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthNotUS) CalcmajauthorsNonUS2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthLPCnew) CalcmajUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthUS_notLPCnew) CalcmajUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);  

// majority 70 numbers:
///*     

                if (entries[j].majority70US()) {maj70USauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0); }

///*   
                if (entries[j].majority70US_LPCnew()) maj70US_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
                if (entries[j].majority70US_nonLPCnew()) maj70US_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
///*  

            }
            
            active2D->Fill(entries[j].category().c_str(),entries[j].activity(),1.0);
            if (entries[j].isChairUS()) chairUS2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isChairUS_LPC()) chairLPC2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isChairUS_nonLPC()) chairnonLPC2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isChairUS_LPCnew()) chairLPCnew2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isChairUS_nonLPCnew()) chairnonLPCnew2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            
            if (entries[j].isCadiUS()) contactUS2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isCadiUS_LPC()) contactLPC2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isCadiUS_nonLPC()) contactnonLPC2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isCadiUS_LPCnew()) contactLPCnew2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].isCadiUS_nonLPCnew()) contactnonLPCnew2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            //if (entries[j].category("TOP") && entries[j].activity()==1) (entries[j].anAuth==entries[j].anAuthUSA)
            //entries[j].majorityUS_LPCnew()
            // if ((entries[j].anAuth>=0)&& (entries[j].isUS_LPCnew())&& (entries[j].activity()==1)&& (entries[j].year()>11)){
            
            // if ((entries[j].anAuth>0)&& (entries[j].anAuth==entries[j].anAuthUSA)&&(entries[j].majorityUS_LPCnew())&& (entries[j].activity()==1)&& (entries[j].year()>11)){
            
            //CAT2 & 3:
            //if ((entries[j].anAuth>=0) && (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)>0.8) && entries[j].activity()==1) {
            //        std::cout << entries[j].code
            // //        <<" "<<entries[j].status
            // //        <<" "<<entries[j].category()
            //        <<"\t"<<entries[j].anAuth<<"\t";
            //        std::cout << entries[j].anAuthUSA//<<"\t"<<entries[j].cadiLPCnew
            // //        <<"\t"<<entries[j].anAuthLPC
            //        <<"\t"<<entries[j].anAuthLPCnew
            //        <<"\t"<<((float)entries[j].anAuthUSA/entries[j].anAuth)
            //        <<"\t"<<((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)
            //        <<endl;
            //
            // }
            // if (!entries[j].hasArcUS()&& entries[j].activity()==1)
            double theRatio = -1.0;
            if (entries[j].anAuth > 0 && entries[j].anAuthUSA > 0 && entries[j].activity() == 1) {
            // if 1 or more total authors, and 1 or more US authors and published
            // theRatio is LPCnew/US
                theRatio = (float)entries[j].anAuthLPCnew / entries[j].anAuthUSA ; 
                // theOtherRatio is US/AllAuthors
                double theOtherRatio = (float)entries[j].anAuthUSA/entries[j].anAuth;
                if (theRatio >= 0.3) {
                    count40++;
                    std::cout << "THE30 Active" << entries[j].code << std::endl;
                        std::cout << "Fractions: Published" << entries[j].code 
                                  << '\t' 
                                  << ((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA) 
                                  << '\t'
                                  << ((float)entries[j].anAuthUSA/entries[j].anAuth) 
                                  << std::endl;
                    if (theRatio >= 0.5) {
                        count50++;
                        std::cout << "THE50 Active" << entries[j].code << std::endl;
                        if (theRatio >= 0.7) {
                            count70++;
                            std::cout << "THE70 Active" << entries[j].code << std::endl;
                        } 
                    }
                }

                if(theRatio>=0.3 && theOtherRatio>=0.3) PAGcounts30[entries[j].category().c_str()]+=1;
                if(theRatio>=0.5 && theOtherRatio>=0.5) PAGcounts50[entries[j].category().c_str()]+=1;
                if(theRatio>=0.7 && theOtherRatio>=0.7) PAGcounts70[entries[j].category().c_str()]+=1;
            }
// same but for active authors:
            double theRatioA = -1.0;
            if (entries[j].anAuth > 0 && entries[j].anAuthUSA > 0 && entries[j].activity() == 3) {
                theRatioA = (float)entries[j].anAuthLPCnew / entries[j].anAuthUSA ;
                double theOtherRatioA = (float)entries[j].anAuthUSA/entries[j].anAuth;
                if (theRatioA >= 0.3) {
                    count40++;
                    std::cout << "THE30 Active" << entries[j].code << std::endl;
                        std::cout << "Fractions: Active" << entries[j].code 
                                  << '\t' 
                                  << ((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA) 
                                  << '\t'
                                  << ((float)entries[j].anAuthUSA/entries[j].anAuth) 
                                  << std::endl;
                    if (theRatioA >= 0.5) {
                        count50++;
                        std::cout << "THE50 Active " << entries[j].code << std::endl;
                        if (theRatioA >= 0.7) {
                            count70++;
                            std::cout << "THE70 Active " << entries[j].code << std::endl;
                        } 
                    }
                }

                if(theRatioA>=0.3 && theOtherRatioA>=0.3) PAGcounts30A[entries[j].category().c_str()]+=1;
                if(theRatioA>=0.5 && theOtherRatioA>=0.5) PAGcounts50A[entries[j].category().c_str()]+=1;
                if(theRatioA>=0.7 && theOtherRatioA>=0.7) PAGcounts70A[entries[j].category().c_str()]+=1;
            }            
            //            if (entries[j].anAuth > 0 && (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA) > 0.4) && entries[j].activity() == 1) {++count40;}
            //            if (entries[j].anAuth > 0 && (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA) > 0.5) && entries[j].activity() == 1) {++count50;}
            //            if (entries[j].anAuth > 0 && (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA) > 0.8) && entries[j].activity() == 1) {++count70;}
            
            // if (
            // // entries[j].isUS()
            // entries[j].anAuth>1
            // && entries[j].anAuthUSA>0
            // && (((((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)>=0.6) && (((float)entries[j].anAuthUSA/entries[j].anAuth)>=0.6)) ||
            //    ((((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)>0.6) && (((float)entries[j].anAuthUSA/entries[j].anAuth)>0.4) &&
            // (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)<0.8) && (((float)entries[j].anAuthUSA/entries[j].anAuth)<0.6)  ))
            //
            // // && (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)+0.2+((float)entries[j].anAuthUSA/entries[j].anAuth))>1.
            //
            //
            // // && (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)>=((float)entries[j].anAuthUSA/entries[j].anAuth))
            // // //entries[j].majorityUS_LPCnew()
            // // &&
            // // entries[j].cadiLPCnew>0 &&
            // //entries[j].isCadiUS()
            //  && entries[j].activity()==1)
            
            // This is the selection for the categories3bin.C plot, the first bin, called "upper right corner, with cut at 60%"
            // but that plot reads from a different section of code, with PAGNames, I think this isn't used at all, instead the theRatio is used
            if (
                entries[j].anAuth > 1 &&
                entries[j].anAuthUSA > 0 &&
                entries[j].activity() == 1 &&
                ((((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA) >= 0.6) &&
                  (((float)entries[j].anAuthUSA/entries[j].anAuth) >= 0.6)))
//                  &&
//                  (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA) < 0.8) &&
//                  (((float)entries[j].anAuthUSA/entries[j].anAuth) < 0.6)
                // This is the selection for the categories3bin.C plot, the second bin, called " >80& LPC"
                // if (entries[j].anAuth>0&& (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)>0.8) && entries[j].activity()==1)
                // // This is the selection for the categories3bin.C plot, the third bin, called " >40& LPC"
                // if (entries[j].anAuth>0&& (((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)>0.4) && entries[j].activity()==1)
                
            {
                arc    += entries[j].arc;
                arcUSA += entries[j].arcUSA;
                arcLPC += entries[j].arcLPCnew;
                ++arcCh;
                arcChUSA += entries[j].arcChairUSA;
                arcChLPC += entries[j].arcChairLPCnew;
                std::cout << "\t\t\t --- NUMBERS for CAT3:\t";// EAC 
                std::cout << theIndex << '\t'; theIndex++; // Orduna
                std::cout << entries[j].code
                //                << '\t' << entries[j].status
                //                << '\t' << entries[j].category()
                << '\t' <<entries[j].anAuth << '\t';
                std::cout << entries[j].anAuthUSA
                //                << '\t' <<entries[j].cadiLPCnew
                //                << '\t' <<entries[j].anAuthLPC
                << '\t' <<entries[j].anAuthLPCnew
                << std::setiosflags(std::ios::left)
                << std::setprecision(3)
                << '\t' << ((float)entries[j].anAuthUSA/entries[j].anAuth)
                << '\t' << ((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)
                << '\t' << entries[j].arcChairUSA
                << '\t' << entries[j].arcChairLPCnew
                << '\t' << entries[j].arcUSA
                << '\t' << entries[j].arcLPCnew << std::endl;
                ++count;
                //PAGcounts[entries[j].category().c_str()]++;
            }
            
            
            //       if (entries[j].category("EXO") && entries[j].activity()==1) std::cout << entries[j].code
            //       <<" "<<entries[j].arcChairUSA
            //       <<" "<<entries[j].arcChairLPCnew
            //       <<" "<<entries[j].arcUSA
            //       <<" "<<entries[j].arcLPCnew
            //       <<"-"<<entries[j].hasArcUS_LPCnew()
            //       <<" "<<entries[j].hasArcUS_nonLPCnew()
            //       <<"-"<<entries[j].hasAnyArcUS_LPCnew()
            //       <<" "<<entries[j].hasAnyArcUS_nonLPCnew()
            //       << endl;
            if (entries[j].hasArcUS())              arcUS2D         ->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].hasArcUS_LPC())          arcLPC2D        ->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].hasArcUS_nonLPC())       arcnonLPC2D     ->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].hasArcUS_LPCnew())       arcLPCnew2D     ->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].hasArcUS_nonLPCnew())    arcnonLPCnew2D  ->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].hasAnyArcUS())           arcCMUS2D       ->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].hasAnyArcUS_LPCnew())    arcCMLPCnew2D   ->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            if (entries[j].hasAnyArcUS_nonLPCnew()) arcCMnonLPCnew2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
            
            totArc2D           ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arc);
            totArcUS2D         ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcUSA);
            totArcLPC2D        ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcLPC);
            totArcnonLPC2D     ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcUSA-entries[j].arcLPC);
            totArcLPCnew2D     ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcLPCnew);
            totArcnonLPCnew2D  ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcUSA-entries[j].arcLPCnew);
            totArcCM2D         ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arc+1);
            totArcCMUS2D       ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcUSA+entries[j].arcChairUSA);
            totArcCMLPCnew2D   ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcLPCnew+entries[j].arcChairLPCnew);
            totArcCMnonLPCnew2D->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].arcUSA
                                                                                            +entries[j].arcChairUSA
                                                                                            -entries[j].arcLPCnew
                                                                                            -entries[j].arcChairLPCnew);
// added Jan 2018, total authors plots                                                                                            
            totAuthors2D           ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].anAuth);
            totAuthorsUS2D         ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].anAuthUSA);
            totAuthorsLPCnew2D     ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].anAuthLPCnew);
            totAuthorsnonLPCnew2D  ->Fill(entries[j].category().c_str(), entries[j].activity(), entries[j].anAuthUSA-entries[j].anAuthLPCnew); 
 
        }
        
        if (entries[j].activity() == 1) {
            //       if (entries[j].arcLPCnew > 0) {
            //       std::cout << entries[j].code <<" "<<entries[j].status<<"- ";
            //       std::cout << entries[j].anAuth<<" "<<entries[j].anAuthUSA<<" "<<entries[j].anAuthLPC<<" "<<entries[j].anAuthLPCnew
            //       <<" "<<entries[j].isUS_nonLPC()
            //  	<<" "<<entries[j].activity()
            // 	<< std::endl;}
            active->Fill(entries[j].category().c_str(), 1.0);
            if (entries[j].isUS())              withUSauthors       ->Fill(entries[j].category().c_str(), 1.0);
            if (entries[j].isUS_LPC())          withUS_LPCauthors   ->Fill(entries[j].category().c_str(), 1.0);
            if (entries[j].isUS_nonLPC())       withUS_nonLPCauthors->Fill(entries[j].category().c_str(), 1.0);
            if (entries[j].majorityUS())        majUSauthors        ->Fill(entries[j].category().c_str(), 1.0);
            if (entries[j].majorityUS_LPC())    majUS_LPCauthors    ->Fill(entries[j].category().c_str(), 1.0);
            if (entries[j].majorityUS_nonLPC()) majUS_nonLPCauthors ->Fill(entries[j].category().c_str(), 1.0);
        }
        
// summed plots stuff
// inactive 0
// Published 1
// PAS-Only-PUB 2
// active 3
       if(((entries[j].activity()==1) || (entries[j].activity()==2)) && (entries[j].activitySum()!=0) && (entries[j].activity()!=0)){
        std::cout<<"activitySum: "<<entries[j].activitySum()<<std::endl;
        nbrAuth[4]->Fill(entries[j].anAuth);
        
        // Plot of fraction of US/LPC authors, for cadi with >1 authors
        if (entries[j].anAuth>1)
            fracUS[4]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth);
        if ((entries[j].anAuth>1) && (entries[j].anAuthUSA>0)) {
            fracLPC[4]->Fill((float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            fracNonLPC[4]->Fill(1-((float)entries[j].anAuthLPC/entries[j].anAuthUSA));
            usVsLpcFrac[4]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth, (float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            usVsLpcNbr[4]->Fill(entries[j].anAuthUSA, (float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            
            fracLPCnew[4]->Fill((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
            fracNonLPCnew[4]->Fill(1-((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA));
            usVsLPCnewFrac[4]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth, (float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
            //        if (entries[j].activity()==1){cout << "-"<<entries[j].code
            // //        <<" "<<entries[j].status
            // //        <<" "<<entries[j].category()
            //        <<"\t"<<entries[j].anAuth<<"\t";
            //        std::cout << entries[j].anAuthUSA//<<"\t"<<entries[j].cadiLPCnew
            // //        <<"\t"<<entries[j].anAuthLPC
            //        <<"\t"<<entries[j].anAuthLPCnew
            //        <<"\t"<<((float)entries[j].anAuthUSA/entries[j].anAuth)
            //        <<"\t"<<((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)
            //        <<endl;}
            usVsLPCnewNbr[4]->Fill(entries[j].anAuthUSA, (float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
        }
        
        // Plot of fraction of US/LPC arcs, for cadi with >1 authors
        if (entries[j].arc>0)
            arcFracUS[4]->Fill((float) entries[j].arcUSA/entries[j].arc);
        if (entries[j].arc>0)
            nbrARC[4]->Fill((float) entries[j].arc);
        if ((entries[j].arc>0) && (entries[j].arcUSA>0)) {
            arcFracLPC[4]->Fill((float)entries[j].arcLPC/entries[j].arcUSA);
            arcFracNonLPC[4]->Fill(1-((float)entries[j].arcLPC/entries[j].arcUSA));
            arcFracLPCnew[4]->Fill((float)entries[j].arcLPCnew/entries[j].arcUSA);
            arcFracNonLPCnew[4]->Fill(1-((float)entries[j].arcLPCnew/entries[j].arcUSA));
        }
        
        // 2D plots of authors
        if (entries[j].activitySum()!=0) {
            if (entries[j].anAuth<=0) active1auth2D->Fill(entries[j].category().c_str(), 4,1.0);
            else {
               // not filled if anAuth<0, try anAuth <=0 !
                activeMany2D->Fill(entries[j].category().c_str(),4,1.0);
                if (entries[j].isUS()) withUSauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].isUS_LPC()) withUS_LPCauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].isUS_nonLPC()) withUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].isUS_LPCnew()) withUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].isUS_nonLPCnew()) withUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);

                if (entries[j].majorityUS()) {majUSauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                    // 	if (entries[j].category()=="FTR") std::cout << "Found : "<<entries[j].code<< " "<<entries[j].activity() << "	"<<majUSauthors2D->GetBinContent(7,3)<<endl;
                }
                if (entries[j].majorityUS_LPC()) majUS_LPCauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].majorityUS_nonLPC()) majUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].majorityUS_LPCnew()) majUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].majorityUS_nonLPCnew()) majUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);

                if (entries[j].significantUS()) signifUSauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].significantUS_LPC()) signifUS_LPCauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].significantUS_nonLPC()) signifUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].significantUS_LPCnew()) signifUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].significantUS_nonLPCnew()) signifUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                
                if (entries[j].MajAuthUS()) MymajUSauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].MajAuthNotUS()) MymajauthorsNonUS2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].MajAuthUSLPCnew()) MymajUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].MajAuthUS_notLPCnew()) MymajUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);  
// majority 70 numbers:
                if (entries[j].majority70US()) {maj70USauthors2D->Fill(entries[j].category().c_str(), 4, 1.0); }
                if (entries[j].majority70US_LPCnew()) maj70US_LPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);
                if (entries[j].majority70US_nonLPCnew()) maj70US_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 4, 1.0);

///* 

//                if (entries[j].NoAuth) CalcNOauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthNotUS) CalcmajauthorsNonUS2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthLPCnew) CalcmajUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthUS_notLPCnew) CalcmajUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);  

            }
            
            active2D->Fill(entries[j].category().c_str(),4,1.0);
            if (entries[j].isChairUS()) chairUS2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isChairUS_LPC()) chairLPC2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isChairUS_nonLPC()) chairnonLPC2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isChairUS_LPCnew()) chairLPCnew2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isChairUS_nonLPCnew()) chairnonLPCnew2D->Fill(entries[j].category().c_str(), 4, 1.0);
            
            if (entries[j].isCadiUS()) contactUS2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isCadiUS_LPC()) contactLPC2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isCadiUS_nonLPC()) contactnonLPC2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isCadiUS_LPCnew()) contactLPCnew2D->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].isCadiUS_nonLPCnew()) contactnonLPCnew2D->Fill(entries[j].category().c_str(), 4, 1.0);
// 
            if (entries[j].hasArcUS())              arcUS2D         ->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].hasArcUS_LPC())          arcLPC2D        ->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].hasArcUS_nonLPC())       arcnonLPC2D     ->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].hasArcUS_LPCnew())       arcLPCnew2D     ->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].hasArcUS_nonLPCnew())    arcnonLPCnew2D  ->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].hasAnyArcUS())           arcCMUS2D       ->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].hasAnyArcUS_LPCnew())    arcCMLPCnew2D   ->Fill(entries[j].category().c_str(), 4, 1.0);
            if (entries[j].hasAnyArcUS_nonLPCnew()) arcCMnonLPCnew2D->Fill(entries[j].category().c_str(), 4, 1.0);
            
            totArc2D           ->Fill(entries[j].category().c_str(), 4, entries[j].arc);
            totArcUS2D         ->Fill(entries[j].category().c_str(), 4, entries[j].arcUSA);
            totArcLPC2D        ->Fill(entries[j].category().c_str(), 4, entries[j].arcLPC);
            totArcnonLPC2D     ->Fill(entries[j].category().c_str(), 4, entries[j].arcUSA-entries[j].arcLPC);
            totArcLPCnew2D     ->Fill(entries[j].category().c_str(), 4, entries[j].arcLPCnew);
            totArcnonLPCnew2D  ->Fill(entries[j].category().c_str(), 4, entries[j].arcUSA-entries[j].arcLPCnew);
            totArcCM2D         ->Fill(entries[j].category().c_str(), 4, entries[j].arc+1);
            totArcCMUS2D       ->Fill(entries[j].category().c_str(), 4, entries[j].arcUSA+entries[j].arcChairUSA);
            totArcCMLPCnew2D   ->Fill(entries[j].category().c_str(), 4, entries[j].arcLPCnew+entries[j].arcChairLPCnew);
            totArcCMnonLPCnew2D->Fill(entries[j].category().c_str(), 4, entries[j].arcUSA
                                                                                            +entries[j].arcChairUSA
                                                                                            -entries[j].arcLPCnew
                                                                                            -entries[j].arcChairLPCnew);
// Jan 2018 addition total authors:
            totAuthors2D           ->Fill(entries[j].category().c_str(), 4, entries[j].anAuth);
            totAuthorsUS2D         ->Fill(entries[j].category().c_str(), 4, entries[j].anAuthUSA);
            totAuthorsLPCnew2D     ->Fill(entries[j].category().c_str(), 4, entries[j].anAuthLPCnew);
            totAuthorsnonLPCnew2D  ->Fill(entries[j].category().c_str(), 4, entries[j].anAuthUSA-entries[j].anAuthLPCnew);
        } 
     }    
 // Sum of all
       if(((entries[j].activity()==1) || (entries[j].activity()==2) || (entries[j].activity()==3)) && (entries[j].activitySumAll()!=0) && (entries[j].activity()!=0)){
        std::cout<<"activitySumAll: "<<entries[j].activitySumAll()<<std::endl;
        nbrAuth[5]->Fill(entries[j].anAuth);
        
        // Plot of fraction of US/LPC authors, for cadi with >1 authors
        if (entries[j].anAuth>1)
            fracUS[5]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth);
        if ((entries[j].anAuth>1) && (entries[j].anAuthUSA>0)) {
            fracLPC[5]->Fill((float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            fracNonLPC[5]->Fill(1-((float)entries[j].anAuthLPC/entries[j].anAuthUSA));
            usVsLpcFrac[5]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth, (float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            usVsLpcNbr[5]->Fill(entries[j].anAuthUSA, (float)entries[j].anAuthLPC/entries[j].anAuthUSA);
            
            fracLPCnew[5]->Fill((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
            fracNonLPCnew[5]->Fill(1-((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA));
            usVsLPCnewFrac[5]->Fill((float) entries[j].anAuthUSA/entries[j].anAuth, (float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
            //        if (entries[j].activity()==1){cout << "-"<<entries[j].code
            // //        <<" "<<entries[j].status
            // //        <<" "<<entries[j].category()
            //        <<"\t"<<entries[j].anAuth<<"\t";
            //        std::cout << entries[j].anAuthUSA//<<"\t"<<entries[j].cadiLPCnew
            // //        <<"\t"<<entries[j].anAuthLPC
            //        <<"\t"<<entries[j].anAuthLPCnew
            //        <<"\t"<<((float)entries[j].anAuthUSA/entries[j].anAuth)
            //        <<"\t"<<((float)entries[j].anAuthLPCnew/entries[j].anAuthUSA)
            //        <<endl;}
            usVsLPCnewNbr[5]->Fill(entries[j].anAuthUSA, (float)entries[j].anAuthLPCnew/entries[j].anAuthUSA);
        }
        
        // Plot of fraction of US/LPC arcs, for cadi with >1 authors
        if (entries[j].arc>0)
            arcFracUS[5]->Fill((float) entries[j].arcUSA/entries[j].arc);
        if (entries[j].arc>0)
            nbrARC[5]->Fill((float) entries[j].arc);
        if ((entries[j].arc>0) && (entries[j].arcUSA>0)) {
            arcFracLPC[5]->Fill((float)entries[j].arcLPC/entries[j].arcUSA);
            arcFracNonLPC[5]->Fill(1-((float)entries[j].arcLPC/entries[j].arcUSA));
            arcFracLPCnew[5]->Fill((float)entries[j].arcLPCnew/entries[j].arcUSA);
            arcFracNonLPCnew[5]->Fill(1-((float)entries[j].arcLPCnew/entries[j].arcUSA));
        }
        
        // 2D plots of authors
        if (entries[j].activitySumAll()!=0 ) {
            if (entries[j].anAuth<=0) active1auth2D->Fill(entries[j].category().c_str(), 5,1.0);
            else {
               // not filled if anAuth<0, try anAuth <=0 !
                activeMany2D->Fill(entries[j].category().c_str(),5,1.0);
                if (entries[j].isUS()) withUSauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].isUS_LPC()) withUS_LPCauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].isUS_nonLPC()) withUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].isUS_LPCnew()) withUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].isUS_nonLPCnew()) withUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);

                if (entries[j].majorityUS()) {majUSauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                    // 	if (entries[j].category()=="FTR") std::cout << "Found : "<<entries[j].code<< " "<<entries[j].activity() << "	"<<majUSauthors2D->GetBinContent(7,3)<<endl;
                }
                if (entries[j].majorityUS_LPC()) majUS_LPCauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].majorityUS_nonLPC()) majUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].majorityUS_LPCnew()) majUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].majorityUS_nonLPCnew()) majUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);

                if (entries[j].significantUS()) signifUSauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].significantUS_LPC()) signifUS_LPCauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].significantUS_nonLPC()) signifUS_nonLPCauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].significantUS_LPCnew()) signifUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].significantUS_nonLPCnew()) signifUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                
                if (entries[j].MajAuthUS()) MymajUSauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].MajAuthNotUS()) MymajauthorsNonUS2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].MajAuthUSLPCnew()) MymajUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].MajAuthUS_notLPCnew()) MymajUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);  
// majority 70 numbers:
                if (entries[j].majority70US()) {maj70USauthors2D->Fill(entries[j].category().c_str(), 5, 1.0); }

                if (entries[j].majority70US_LPCnew()) maj70US_LPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);
                if (entries[j].majority70US_nonLPCnew()) maj70US_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), 5, 1.0);

///* 

//                if (entries[j].NoAuth) CalcNOauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthNotUS) CalcmajauthorsNonUS2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthLPCnew) CalcmajUS_LPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);
//                if (entries[j].MyCalcAuthUS_notLPCnew) CalcmajUS_nonLPCnewauthors2D->Fill(entries[j].category().c_str(), entries[j].activity(), 1.0);  

            }
            
            active2D->Fill(entries[j].category().c_str(),5,1.0);
            if (entries[j].isChairUS()) chairUS2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isChairUS_LPC()) chairLPC2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isChairUS_nonLPC()) chairnonLPC2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isChairUS_LPCnew()) chairLPCnew2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isChairUS_nonLPCnew()) chairnonLPCnew2D->Fill(entries[j].category().c_str(), 5, 1.0);
            
            if (entries[j].isCadiUS()) contactUS2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isCadiUS_LPC()) contactLPC2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isCadiUS_nonLPC()) contactnonLPC2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isCadiUS_LPCnew()) contactLPCnew2D->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].isCadiUS_nonLPCnew()) contactnonLPCnew2D->Fill(entries[j].category().c_str(), 5, 1.0);

            if (entries[j].hasArcUS())              arcUS2D         ->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].hasArcUS_LPC())          arcLPC2D        ->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].hasArcUS_nonLPC())       arcnonLPC2D     ->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].hasArcUS_LPCnew())       arcLPCnew2D     ->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].hasArcUS_nonLPCnew())    arcnonLPCnew2D  ->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].hasAnyArcUS())           arcCMUS2D       ->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].hasAnyArcUS_LPCnew())    arcCMLPCnew2D   ->Fill(entries[j].category().c_str(), 5, 1.0);
            if (entries[j].hasAnyArcUS_nonLPCnew()) arcCMnonLPCnew2D->Fill(entries[j].category().c_str(), 5, 1.0);
            
            totArc2D           ->Fill(entries[j].category().c_str(), 5, entries[j].arc);
            totArcUS2D         ->Fill(entries[j].category().c_str(), 5, entries[j].arcUSA);
            totArcLPC2D        ->Fill(entries[j].category().c_str(), 5, entries[j].arcLPC);
            totArcnonLPC2D     ->Fill(entries[j].category().c_str(), 5, entries[j].arcUSA-entries[j].arcLPC);
            totArcLPCnew2D     ->Fill(entries[j].category().c_str(), 5, entries[j].arcLPCnew);
            totArcnonLPCnew2D  ->Fill(entries[j].category().c_str(), 5, entries[j].arcUSA-entries[j].arcLPCnew);
            totArcCM2D         ->Fill(entries[j].category().c_str(), 5, entries[j].arc+1);
            totArcCMUS2D       ->Fill(entries[j].category().c_str(), 5, entries[j].arcUSA+entries[j].arcChairUSA);
            totArcCMLPCnew2D   ->Fill(entries[j].category().c_str(), 5, entries[j].arcLPCnew+entries[j].arcChairLPCnew);
            totArcCMnonLPCnew2D->Fill(entries[j].category().c_str(), 5, entries[j].arcUSA
                                                                                            +entries[j].arcChairUSA
                                                                                            -entries[j].arcLPCnew
                                                                                            -entries[j].arcChairLPCnew);
// Jan 2018 total authors
            totAuthors2D           ->Fill(entries[j].category().c_str(), 5, entries[j].anAuth);
            totAuthorsUS2D         ->Fill(entries[j].category().c_str(), 5, entries[j].anAuthUSA);
            totAuthorsLPCnew2D     ->Fill(entries[j].category().c_str(), 5, entries[j].anAuthLPCnew);
            totAuthorsnonLPCnew2D  ->Fill(entries[j].category().c_str(), 5, entries[j].anAuthUSA-entries[j].anAuthLPCnew);

        } 
     }           
        //     if (entries[j].category("B2G") && entries[j].activity()==3 ){
        //       std::cout << j<<" "<<entries[j].code<<" "<<entries[j].status<<"- ";
        //       std::cout << entries[j].anAuth<<" "<<entries[j].anAuthUSA<<" "<<entries[j].isUS()<<" "<<entries[j].isUS_LPC()<<" "<<entries[j].isUS_nonLPC()
        //  	<<" "<<(float)entries[j].anAuthUSA/entries[j].anAuth<<" "<<entries[j].majorityUS()
        // 	<<"\n";
        //     }
    }
    
    std::cout << "Found " << entries.size() << " cadi entries" << std::endl;
    std::cout << "Found " << count << " counts" << std::endl;
    std::cout << "Total Arc members: "           << arc             << std::endl;
    std::cout << "Arc members from US: "         << arcUSA          << std::endl;
    std::cout << "Arc members from LPC: "        << arcLPC          << std::endl;
    std::cout << "Total Arc chairs: "            << arcCh           << std::endl;
    std::cout << "Arc chairs from US:  "         << arcChUSA        << std::endl;
    std::cout << "Arc chairs from LPC: "         << arcChLPC        << std::endl;
    std::cout << "Total Arc chairs+members: "    << arc+arcCh       << std::endl;
    std::cout << "Arc chairs+members from US:  " << arcUSA+arcChUSA << std::endl;
    std::cout << "Arc chairs+members from LPC: " << arcLPC+arcChLPC << std::endl;
    std::cout << "Count 40: "   << count40 ;
    std::cout << "\tCount 50: " << count50 ;
    std::cout << "\tCount 70: " << count70 << std::endl;
    std::cout << "\t\t\t PAG COUNTS: 40 " << std::endl;
    for(const auto &it : PAGcounts30) { 
        std::cout<<"\t\t\t\t- "<<it.first<<": "<<it.second<<std::endl;
    }
    std::cout << "\t\t\t PAG COUNTS: 50 " << std::endl;
    for(const auto &it : PAGcounts50) { 
        std::cout<<"\t\t\t\t- "<<it.first<<": "<<it.second<<std::endl;
    }
    std::cout << "\t\t\t PAG COUNTS: 70 " << std::endl;
    for(const auto &it : PAGcounts70) { 
        std::cout<<"\t\t\t\t- "<<it.first<<": "<<it.second<<std::endl;
    }
    
    // return;
    
    //   active2D
    //   THStack* allSt = stack(active2D, "allStack");
    
    DRstack(withUS_LPCScholars2D, "LPCscholars");
    DRstack(withUS_LPCNumScholars2D, "nLPCscholars", false, "LPC DRs as authors");
    DRstack(withUS_LPCARCChairScholars2D, "LPCChairscholars", false, "LPC DRs as ARC chairs");
    DRstack(withUS_LPCARCScholars2D, "LPCARCscholars", false, "CADI entries");
    DRstack(withUS_LPCNumARCScholars2D, "nLPCNumARCscholars", false, "LPC DRs as ARC members");

    cat3stack(withUS_LPCScholarsActive2D, "LPCScholarsActive", true);
    cat3stack(withUS_LPCNumScholarsActive2D, "LPCNumScholarsActive", true, "LPC DRs as authors Active");
    cat1stack(withUS_LPCScholarsPublished2D, "LPCScholarsPublished", true);
    cat1stack(withUS_LPCNumScholarsPublished2D, "LPCNumScholarsPublished", true, "LPC DRs as authors Published");    
    cat2stack(withUS_LPCScholarsPASOnly2D, "LPCScholarsPASOnly", true);
    cat2stack(withUS_LPCNumScholarsPASOnly2D, "LPCNumScholarsPASOnly", true, "LPC DRs as authors PAS-Only");    
    cat4stack(withUS_LPCScholarsPublished_PAS2D, "LPCScholarsPublished_PAS", true);
    cat4stack(withUS_LPCNumScholarsPublished_PAS2D, "LPCNumScholarsPublished_PAS", true, "LPC DRs as authors Published+PAS");        
    cat5stack(withUS_LPCScholarsPublished_PAS_Active2D, "LPCScholarsPublished_PAS_Active", true);
    cat5stack(withUS_LPCNumScholarsPublished_PAS_Active2D, "LPCNumScholarsPublished_PAS_Active", true, "LPC DRs as authors Published+PAS+Active");    
    
    tstack(activeMany2D, "CADIentriesMany", true);
    tstack(active2D, "CADIentries");

// here the first number in tstack is "bin" which is the activity()+1, it is analyzed in the code with text of category[bin-1]   
// modified for tstack:  
// inactive tstack(1
// Published tstack(2
// PAS-Only-PUB tstack(3
// active tstack(4
// Published+PAS-Only-PUB tstack(5
// Published+PAS-Only-PUB+Active tstack(6

    tstack(4, activeMany2D, withUSauthors2D, withUS_LPCauthors2D, withUS_nonLPCauthors2D, "authActive",    "With Authors", "CADI entries");
    tstack(2, activeMany2D, withUSauthors2D, withUS_LPCauthors2D, withUS_nonLPCauthors2D, "authPublished", "With Authors", "CADI entries");
    tstack(3, activeMany2D, withUSauthors2D, withUS_LPCauthors2D, withUS_nonLPCauthors2D, "authPasOnly",   "With Authors", "CADI entries");
// true here means these plots get printed to the html    
    tstack(4, activeMany2D, withUSauthors2D, withUS_LPCnewauthors2D, withUS_nonLPCnewauthors2D, "authActiveNew",    "With Authors", "CADI entries", true);
    tstack(2, activeMany2D, withUSauthors2D, withUS_LPCnewauthors2D, withUS_nonLPCnewauthors2D, "authPublishedNew", "With Authors", "CADI entries", true);
    tstack(3, activeMany2D, withUSauthors2D, withUS_LPCnewauthors2D, withUS_nonLPCnewauthors2D, "authPasOnlyNew",   "With Authors", "CADI entries",true);
    combine(activeMany2D, withUSauthors2D, withUS_LPCnewauthors2D, withUS_nonLPCnewauthors2D, "auth_Active-PasOnly-Published_New", "With Authors", "CADI entries");
    tstack(5, activeMany2D, withUSauthors2D, withUS_LPCnewauthors2D, withUS_nonLPCnewauthors2D, "authPublished+PAS-Only-PUBNew",    "With Authors", "CADI entries", true);
    tstack(6, activeMany2D, withUSauthors2D, withUS_LPCnewauthors2D, withUS_nonLPCnewauthors2D, "authPublished+PAS-Only-PUB+ActiveNew", "With Authors", "CADI entries", true);
    
    tstack(4, activeMany2D, majUSauthors2D, majUS_LPCauthors2D, majUS_nonLPCauthors2D, "majAuthActive",    "Majority of authors","CADI entries");
    tstack(2, activeMany2D, majUSauthors2D, majUS_LPCauthors2D, majUS_nonLPCauthors2D, "majAuthPublished", "Majority of authors","CADI entries");
    tstack(3, activeMany2D, majUSauthors2D, majUS_LPCauthors2D, majUS_nonLPCauthors2D, "majAuthPasOnly",   "Majority of authors","CADI entries");

    tstack(4, activeMany2D, signifUSauthors2D, signifUS_LPCnewauthors2D, signifUS_nonLPCnewauthors2D, "signifAuthActiveNew",    "Significant number of authors","CADI entries",true);
    tstack(2, activeMany2D, signifUSauthors2D, signifUS_LPCnewauthors2D, signifUS_nonLPCnewauthors2D, "signifAuthPublishedNew", "Significant number of authors","CADI entries",true);
    tstack(3, activeMany2D, signifUSauthors2D, signifUS_LPCnewauthors2D, signifUS_nonLPCnewauthors2D, "signifAuthPasOnlyNew",   "Significant number of authors","CADI entries",true);
    tstack(5, activeMany2D, signifUSauthors2D, signifUS_LPCnewauthors2D, signifUS_nonLPCnewauthors2D, "signifAuthPublished+PAS-Only-PUBNew", "Significant number of authors","CADI entries",true);
    tstack(6, activeMany2D, signifUSauthors2D, signifUS_LPCnewauthors2D, signifUS_nonLPCnewauthors2D, "signifAuthPublished+PAS-Only-PUB+ActiveNew",   "Significant number of authors","CADI entries",true);
        
    tstack(4, activeMany2D, majUSauthors2D, majUS_LPCnewauthors2D, majUS_nonLPCnewauthors2D, "majAuthActiveNew",    "Majority of authors","CADI entries",true);
    tstack(2, activeMany2D, majUSauthors2D, majUS_LPCnewauthors2D, majUS_nonLPCnewauthors2D, "majAuthPublishedNew", "Majority of authors","CADI entries",true);
    tstack(3, activeMany2D, majUSauthors2D, majUS_LPCnewauthors2D, majUS_nonLPCnewauthors2D, "majAuthPasOnlyNew",   "Majority of authors","CADI entries",true);
    tstack(5, activeMany2D, majUSauthors2D, majUS_LPCnewauthors2D, majUS_nonLPCnewauthors2D, "majAuthPublished+PAS-Only-PUBNew", "Majority of authors","CADI entries",true);
    tstack(6, activeMany2D, majUSauthors2D, majUS_LPCnewauthors2D, majUS_nonLPCnewauthors2D, "majAuthPublished+PAS-Only-PUB+ActiveNew",   "Majority of authors","CADI entries",true);
    //     std::cout << "active2D "<<active2D[j]->GetEntries()<<endl;

// 70% Majority authors    
    tstack(4, activeMany2D, maj70USauthors2D, maj70US_LPCnewauthors2D, maj70US_nonLPCnewauthors2D, "maj70AuthActiveNew",    "SuperMajority of authors","CADI entries",true);
    tstack(2, activeMany2D, maj70USauthors2D, maj70US_LPCnewauthors2D, maj70US_nonLPCnewauthors2D, "maj70AuthPublishedNew", "SuperMajority of authors","CADI entries",true);
    tstack(3, activeMany2D, maj70USauthors2D, maj70US_LPCnewauthors2D, maj70US_nonLPCnewauthors2D, "maj70AuthPasOnlyNew",   "SuperMajority of authors","CADI entries",true);
    tstack(5, activeMany2D, maj70USauthors2D, maj70US_LPCnewauthors2D, maj70US_nonLPCnewauthors2D, "maj70AuthPublished+PAS-Only-PUBNew", "SuperMajority of authors","CADI entries",true);
    tstack(6, activeMany2D, maj70USauthors2D, maj70US_LPCnewauthors2D, maj70US_nonLPCnewauthors2D, "maj70AuthPublished+PAS-Only-PUB+ActiveNew",   "SuperMajority of authors","CADI entries",true);        

    tstack(4, activeMany2D, MymajUSauthors2D, MymajUS_LPCnewauthors2D, MymajUS_nonLPCnewauthors2D, "TonjesMajAuthActiveNew_USgteq50",    "Majority of authors","CADI entries");
    tstack(2, activeMany2D, MymajUSauthors2D, MymajUS_LPCnewauthors2D, MymajUS_nonLPCnewauthors2D, "TonjesMajAuthPublishedNew_USgteq50", "Majority of authors","CADI entries");
    tstack(3, activeMany2D, MymajUSauthors2D, MymajUS_LPCnewauthors2D, MymajUS_nonLPCnewauthors2D, "TonjesMajAuthPasOnlyNew_USgteq50",   "Majority of authors","CADI entries");  
    
    tstack(4, active2D, chairUS2D ,chairLPC2D, chairnonLPC2D, "arcChairActive", "ARC chairs","CADI entries");
    tstack(2, active2D, chairUS2D ,chairLPC2D, chairnonLPC2D, "arcChairPublished", "ARC chairs","CADI entries");
    tstack(3, active2D, chairUS2D ,chairLPC2D, chairnonLPC2D, "arcChairPasOnly", "ARC chairs","CADI entries");
    
    
    tstack(4, active2D, arcUS2D ,arcLPC2D, arcnonLPC2D, "arcMemberActive", "With ARC members","CADI entries");
    tstack(2, active2D, arcUS2D ,arcLPC2D, arcnonLPC2D, "arcMemberPublished", "With ARC members","CADI entries");
    tstack(3, active2D, arcUS2D ,arcLPC2D, arcnonLPC2D, "arcMemberPasOnly", "With ARC members","CADI entries");
    
    tstack(4, active2D, chairUS2D ,chairLPCnew2D, chairnonLPCnew2D, "arcChairActiveNew", "ARC chairs","CADI entries");
    tstack(2, active2D, chairUS2D ,chairLPCnew2D, chairnonLPCnew2D, "arcChairPublishedNew", "ARC chairs","CADI entries");
    tstack(3, active2D, chairUS2D ,chairLPCnew2D, chairnonLPCnew2D, "arcChairPasOnlyNew", "ARC chairs","CADI entries");
    
    tstack(4, active2D, arcUS2D ,arcLPCnew2D, arcnonLPCnew2D, "arcMemberActiveNew", "With ARC members","CADI entries");
    tstack(2, active2D, arcUS2D ,arcLPCnew2D, arcnonLPCnew2D, "arcMemberPublishedNew", "With ARC members","CADI entries");
    tstack(3, active2D, arcUS2D ,arcLPCnew2D, arcnonLPCnew2D, "arcMemberPasOnlyNew", "With ARC members","CADI entries");
    
    tstack(4, active2D, arcCMUS2D ,arcCMLPCnew2D, arcCMnonLPCnew2D, "arcMemberChairActiveNew", "With ARC members","CADI entries");
    tstack(2, active2D, arcCMUS2D ,arcCMLPCnew2D, arcCMnonLPCnew2D, "arcMemberChairPublishedNew", "With ARC members","CADI entries");
    tstack(3, active2D, arcCMUS2D ,arcCMLPCnew2D, arcCMnonLPCnew2D, "arcMemberChairPasOnlyNew", "With ARC members","CADI entries");
    
    tstack(4, active2D, contactUS2D , contactLPC2D, contactnonLPC2D, "cadiContactActive", "CADI contacts","CADI entries");
    tstack(2, active2D, contactUS2D , contactLPC2D, contactnonLPC2D, "cadiContactPublished", "CADI contacts","CADI entries");
    tstack(3, active2D, contactUS2D , contactLPC2D, contactnonLPC2D, "cadiContactPasOnly", "CADI contacts","CADI entries");
    
    tstack(4, active2D, contactUS2D , contactLPCnew2D, contactnonLPCnew2D, "cadiContactActiveNew", "CADI contacts","CADI entries");
    tstack(2, active2D, contactUS2D , contactLPCnew2D, contactnonLPCnew2D, "cadiContactPublishedNew", "CADI contacts","CADI entries");
    tstack(3, active2D, contactUS2D , contactLPCnew2D, contactnonLPCnew2D, "cadiContactPasOnlyNew", "CADI contacts","CADI entries");
    
    tstack(4, totArc2D, totArcUS2D , totArcLPC2D, totArcnonLPC2D, "totArcActive", "Total ARC members", "ARC members");
    tstack(2, totArc2D, totArcUS2D , totArcLPC2D, totArcnonLPC2D, "totArcPublished", "Total ARC members", "ARC members");
    tstack(3, totArc2D, totArcUS2D , totArcLPC2D, totArcnonLPC2D, "totArcPasOnly", "Total ARC members", "ARC members");
    
    tstack(4, totArc2D, totArcUS2D , totArcLPCnew2D, totArcnonLPCnew2D, "totArcActiveNew", "Total ARC members", "ARC members");
    tstack(2, totArc2D, totArcUS2D , totArcLPCnew2D, totArcnonLPCnew2D, "totArcPublishedNew", "Total ARC members", "ARC members");
    tstack(3, totArc2D, totArcUS2D , totArcLPCnew2D, totArcnonLPCnew2D, "totArcPasOnlyNew", "Total ARC members", "ARC members");

    tstack(4, totAuthors2D, totAuthorsUS2D , totAuthorsLPCnew2D, totAuthorsnonLPCnew2D, "totAuthorsActiveNew", "Total Authors", "Authors");
    tstack(2, totAuthors2D, totAuthorsUS2D , totAuthorsLPCnew2D, totAuthorsnonLPCnew2D, "totAuthorsPublishedNew", "Total Authors", "Authors");
    tstack(3, totAuthors2D, totAuthorsUS2D , totAuthorsLPCnew2D, totAuthorsnonLPCnew2D, "totAuthorsPasOnlyNew", "Total Authors", "Authors");
    
    tstack(4, totArcCM2D, totArcCMUS2D , totArcCMLPCnew2D, totArcCMnonLPCnew2D, "totArcCMActiveNew", "Total ARC members", "ARC members");
    tstack(2, totArcCM2D, totArcCMUS2D , totArcCMLPCnew2D, totArcCMnonLPCnew2D, "totArcCMPublishedNew", "Total ARC members", "ARC members");
    tstack(3, totArcCM2D, totArcCMUS2D , totArcCMLPCnew2D, totArcCMnonLPCnew2D, "totArcCMPasOnlyNew", "Total ARC members", "ARC members");
    
    //   allSt->Draw();
    //   allSt->Draw();
    
    // Plot fractions
    
    
    TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600);
    for (int j=0;j<6;++j) {
        // No stats box
        gStyle->SetOptStat(0);
        // No title
        gStyle->SetOptTitle(0);
        
        nbrAuth[j]->GetXaxis()->SetTitle("Number of authors");
        nbrAuth[j]->GetYaxis()->SetTitleOffset(1.15) ;
        nbrAuth[j]->SetFillColor(kViolet-7);
        nbrAuth[j]->Draw();
            //(at least the text->Draw(); statements.
            TLatex* text1 = new TLatex(3.570061,23.08044,category[j]);
            text1->SetNDC();
            text1->SetTextAlign(13);
            text1->SetX(0.13);
            text1->SetY(0.95);
            text1->SetTextFont(42);
            text1->SetTextSizePixels(24);
            text1->Draw();
        sprintf(hname, "authorsC%i.png", j);
        canv3->Print(hname);
        
        // EAC
        usVsLpcFrac[j]->GetXaxis()->SetTitle("Authors from USA");
        std::cout << "usVsLpcFrac[j] "<<usVsLpcFrac[j]->GetEntries()<<endl;
        usVsLpcFrac[j]->GetYaxis()->SetTitle("USA authors from LPC-I");
        usVsLpcFrac[j]->GetYaxis()->SetTitleOffset(1.5) ;
        usVsLpcFrac[j]->Draw("box");
        text1->Draw();
        sprintf(hname, "usVsLpcFracBoxC%i.png", j);
        canv3->Print(hname);
        
        usVsLPCnewFrac[j]->GetXaxis()->SetTitle("Authors from USA");
        usVsLPCnewFrac[j]->GetYaxis()->SetTitle("USA authors from LPC");
        usVsLPCnewFrac[j]->GetYaxis()->SetTitleOffset(1.15) ;
        usVsLPCnewFrac[j]->Draw("box");
        text1->Draw();
        sprintf(hname, "usVsLpcNewFracBoxC%i.png", j);
        canv3->Print(hname);
        
        //     usVsLpcFrac[j]->GetXaxis()->SetTitleOffset(1.8) ;
        //     usVsLpcFrac[j]->GetYaxis()->SetTitleOffset(1.8) ;
        //     usVsLpcFrac[j]->GetXaxis()->SetTitleSize(0.045);
        //     usVsLpcFrac[j]->GetYaxis()->SetTitleSize(0.045);
        usVsLpcFrac[j]->Draw("text");
        text1->Draw();
        sprintf(hname, "usVsLpcFracTextC%i.png", j);
        canv3->Print(hname);
        
        //     usVsLPCnewFrac[j]->GetXaxis()->SetTitleOffset(1.8) ;
        //     usVsLPCnewFrac[j]->GetYaxis()->SetTitleOffset(1.8) ;
        //     usVsLPCnewFrac[j]->GetXaxis()->SetTitleSize(0.045);
        //     usVsLPCnewFrac[j]->GetYaxis()->SetTitleSize(0.045);
        usVsLPCnewFrac[j]->SetMarkerSize(2.5);
        usVsLPCnewFrac[j]->Draw("text");
        text1->Draw();
        sprintf(hname, "usVsLpcNewFracTextC%i.png", j);
        std::cout << hname << " " << usVsLPCnewFrac[j]->GetEntries()<<endl;
        canv3->Print(hname);
        
        
        usVsLpcNbr[j]->GetXaxis()->SetTitle("Authors from USA");
        usVsLpcNbr[j]->GetYaxis()->SetTitle("USA authors from LPC-I");
        usVsLpcNbr[j]->GetYaxis()->SetTitleOffset(1.15) ;
        usVsLpcNbr[j]->Draw("box");
        text1->Draw();
        sprintf(hname, "usVsLpcNbrBoxC%i.png", j);
        canv3->Print(hname);
        //     usVsLpcNbr[j]->GetXaxis()->SetTitleOffset(1.8) ;
        //     usVsLpcNbr[j]->GetYaxis()->SetTitleOffset(1.8) ;
        //     usVsLpcNbr[j]->GetXaxis()->SetTitleSize(0.045);
        //     usVsLpcNbr[j]->GetYaxis()->SetTitleSize(0.045);
        usVsLpcNbr[j]->SetMarkerSize(2.5);
        usVsLpcNbr[j]->Draw("text");
        //        text1->Draw();
        sprintf(hname, "usVsLpcNbrTextC%i.png", j);
        canv3->Print(hname);
        
        usVsLPCnewNbr[j]->GetXaxis()->SetTitle("Authors from USA");
        usVsLPCnewNbr[j]->GetYaxis()->SetTitle("USA authors from LPC");
        usVsLPCnewNbr[j]->GetYaxis()->SetTitleOffset(1.15) ;
        usVsLPCnewNbr[j]->Draw("box");
        text1->Draw();
        sprintf(hname, "usVsLpcNbrNewBoxC%i.png", j);
        canv3->Print(hname);
        //     usVsLPCnewNbr[j]->GetXaxis()->SetTitleOffset(1.8) ;
        //     usVsLPCnewNbr[j]->GetYaxis()->SetTitleOffset(1.8) ;
        //     usVsLPCnewNbr[j]->GetXaxis()->SetTitleSize(0.045);
        //     usVsLPCnewNbr[j]->GetYaxis()->SetTitleSize(0.045);
        usVsLPCnewNbr[j]->SetMarkerSize(2.5);
        usVsLPCnewNbr[j]->Draw("text");
        text1->Draw();
        sprintf(hname, "usVsLpcNbrNewTextC%i.png", j);
        canv3->Print(hname);
        
    }
    /////////////////////////////////
    
    TCanvas* canv2 = new TCanvas("canv2", "canv2", 750, 300);
    canv2->Divide(3,1) ;
    
    for (int j=0;j<6;++j) {
        canv2->cd(1);
        fracUS[j]->GetXaxis()->SetTitle("Fraction of authors from USA");
        fracUS[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracUS[j]->Draw();
        TLatex* text1 = new TLatex(3.570061,23.08044,category[j]);
        text1->SetNDC();
        text1->SetTextAlign(13);
        text1->SetX(0.13);
        text1->SetY(0.95);
        text1->SetTextFont(42);
        text1->SetTextSizePixels(24);
        //        text1->Draw(); // Orduna: get rid of the title
        canv2->cd(2);
        fracLPC[j]->GetXaxis()->SetTitle("Fraction of USA authors from LPC-I");
        fracLPC[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracLPC[j]->Draw();
        canv2->cd(3);
        fracNonLPC[j]->GetXaxis()->SetTitle("Fraction of USA authors not from LPC-I");
        fracNonLPC[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracNonLPC[j]->Draw();
        sprintf(hname, "authorFracC%i.png", j);
        canv2->Print(hname);
        
        
        canv2->cd(1);
        fracUS[j]->GetXaxis()->SetTitle("Fraction of authors from USA");
        fracUS[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracUS[j]->Draw();
        text1->Draw();
        canv2->cd(2);
        fracLPCnew[j]->GetXaxis()->SetTitle("Fraction of USA authors from LPC");
        fracLPCnew[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracLPCnew[j]->Draw();
        canv2->cd(3);
        fracNonLPCnew[j]->GetXaxis()->SetTitle("Fraction of USA authors not from LPC");
        fracNonLPCnew[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracNonLPCnew[j]->Draw();
        
        
        sprintf(hname, "authorFracNewC%i.png", j);
        canv2->Print(hname);
        
    }
    delete canv;
    canv = new TCanvas("canv", "canv", 600, 600);
    
    for (int j=0;j<6;++j) {
        fracUS[j]->GetXaxis()->SetTitle("Fraction of authors from USA");
        fracUS[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracUS[j]->Draw();
        TLatex* text1 = new TLatex(3.570061,23.08044,category[j]);
        text1->SetNDC();
        text1->SetTextAlign(13);
        text1->SetX(0.13);
        text1->SetY(0.95);
        text1->SetTextFont(42);
        text1->SetTextSizePixels(24);
        //        text1->Draw(); // Orduna: get rid of the title
        
        sprintf(hname, "authorFracC%i_uscms.png", j);
        canv->Print(hname);
        
        canv->cd(1);
        fracUS[j]->GetXaxis()->SetTitle("Fraction of authors from USA");
        fracUS[j]->GetYaxis()->SetTitleOffset(1.15) ;
        fracUS[j]->Draw();
        text1->Draw();
        
        sprintf(hname, "authorFracNewC%i_uscms.png", j);
        canv->Print(hname);
        
    }
    /////////////////////////////////
    for (int j=0;j<6;++j) {
        canv2->cd(1);
        arcFracUS[j]->GetXaxis()->SetTitle("Fraction of ARC from USA");
        arcFracUS[j]->GetYaxis()->SetTitleOffset(1.15) ;
        arcFracUS[j]->Draw();
        std::cout << "Average arc number "<< j<<" : "<<nbrARC[j]->GetMean()<<endl;
        std::cout << "Fraction of ARC from USA "<< j<<" : "<<arcFracUS[j]->GetMean()<<endl;
        TLatex* text1 = new TLatex(3.570061,23.08044,category[j]);
        text1->SetNDC();
        text1->SetTextAlign(13);
        text1->SetX(0.13);
        text1->SetY(0.95);
        text1->SetTextFont(42);
        text1->SetTextSizePixels(24);
        //        text1->Draw(); // Orduna: get rid of the title
        canv2->cd(2);
        arcFracLPC[j]->GetXaxis()->SetTitle("Fraction of USA ARC from LPC-I");
        arcFracLPC[j]->GetYaxis()->SetTitleOffset(1.15) ;
        arcFracLPC[j]->Draw();
        canv2->cd(3);
        arcFracNonLPC[j]->GetXaxis()->SetTitle("Fraction of USA ARC not from LPC-I");
        arcFracNonLPC[j]->GetYaxis()->SetTitleOffset(1.15) ;
        arcFracNonLPC[j]->Draw();
        sprintf(hname, "arcFracC%i.png", j);
        canv2->Print(hname);
        
        canv2->cd(1);
        arcFracUS[j]->GetXaxis()->SetTitle("Fraction of ARC from USA");
        arcFracUS[j]->GetYaxis()->SetTitleOffset(1.15) ;
        arcFracUS[j]->Draw();
        text1->Draw();
        canv2->cd(2);
        arcFracLPCnew[j]->GetXaxis()->SetTitle("Fraction of USA ARC from LPC");
        arcFracLPCnew[j]->GetYaxis()->SetTitleOffset(1.15) ;
        arcFracLPCnew[j]->Draw();
        std::cout << "Fraction of USA ARC from LPC "<< j<<" : "<<arcFracLPCnew[j]->GetMean()<<endl;
        canv2->cd(3);
        arcFracNonLPCnew[j]->GetXaxis()->SetTitle("Fraction of USA ARC not from LPC");
        arcFracNonLPCnew[j]->GetYaxis()->SetTitleOffset(1.15) ;
        arcFracNonLPCnew[j]->Draw();
        sprintf(hname, "arcFracNewC%i.png", j);
        canv2->Print(hname);
    }
    delete canv;
    canv = new TCanvas("canv", "canv", 600, 600);
    
    for (int j=0;j<6;++j) {
        arcFracUS[j]->GetXaxis()->SetTitle("Fraction of ARC from USA");
        arcFracUS[j]->GetYaxis()->SetTitleOffset(1.15) ;
        arcFracUS[j]->Draw();
        TLatex* text1 = new TLatex(3.570061,23.08044,category[j]);
        text1->SetNDC();
        text1->SetTextAlign(13);
        text1->SetX(0.13);
        text1->SetY(0.95);
        text1->SetTextFont(42);
        text1->SetTextSizePixels(24);
        //        text1->Draw(); // Orduna: get rid of the title
        
        
        sprintf(hname, "arcFracC%i_uscms.png", j);
        canv->Print(hname);
    }
    
    for (int cat=0;cat<6;++cat) {
        std::cout << "Category "<<cat<<": "<<category[cat]<<std::endl;
        std::cout << "PAG & \tTotal & \tAuth US & \tLPCnew & \tnon-LPCnew & \t";
        std::cout << "Majr US & \tnonMajr US & \tLPCnew & \tnon-LPCnew & \t";
        std::cout << "Signif US & \tnonSignif US & \tLPCnew & \tnon-LPCnew & \t";
        std::cout << "Chai US & \tLPCnew & \tnon-LPCnew & \t";
        std::cout << "Cont US & \tCont nonUS & \tLPCnew  & \tnon-LPCnew & \t";
        std::cout << "ARC & \tARC US & \tLPCnew & \tnon-LPCnew & \n";
        for (unsigned gr = 0; gr < PAG.size(); ++gr) {
            std::cout << PAG[gr]<<" & \t"<< active2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< withUSauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< withUS_LPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< withUS_nonLPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< majUSauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - majUSauthors2D->GetBinContent(gr+1,cat+1)                    
            <<" & \t"<< majUS_LPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< majUS_nonLPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< signifUSauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - signifUSauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< signifUS_LPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< signifUS_nonLPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< chairUS2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< chairLPCnew2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< chairnonLPCnew2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< contactUS2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - contactUS2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< contactLPCnew2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< contactnonLPCnew2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< totArc2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< totArcUS2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< totArcLPCnew2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< totArcnonLPCnew2D->GetBinContent(gr+1,cat+1)
            <<endl;
            //      <<"\t"<< ->GetBinContent(cat+1,gr+1)
        }
        std::cout << std::endl;
    }
        std::cout <<" Different smaller spreadsheet \n"<< std::endl;    
    for (int cat=0;cat<6;++cat) {
        std::cout << "Category "<<cat<<": "<<category[cat]<<std::endl;
        std::cout << "PAG & \tTotal & \t";
        std::cout << "Majr US & \tnonMajr US & \t";
        std::cout << "Signif US & \tnonSignif US & \t";
        std::cout << "Arc Chair US & \tArc Chair nonUS & \t";
        std::cout << "A least 1 ARC member US & \tNo ARC members US & \t";
        std::cout << "Cont US & \tCont nonUS & \n";
        for (unsigned gr = 0; gr < PAG.size(); ++gr) {
            std::cout << PAG[gr]<<" & \t"<< active2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< majUSauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - majUSauthors2D->GetBinContent(gr+1,cat+1)                    
            <<" & \t"<< signifUSauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - signifUSauthors2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< chairUS2D->GetBinContent(gr+1,cat+1)  
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - chairUS2D->GetBinContent(gr+1,cat+1)    
            <<" & \t"<< arcUS2D->GetBinContent(gr+1,cat+1)                       
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - arcUS2D->GetBinContent(gr+1,cat+1)                       
            <<" & \t"<< contactUS2D->GetBinContent(gr+1,cat+1)
            <<" & \t"<< active2D->GetBinContent(gr+1,cat+1) - contactUS2D->GetBinContent(gr+1,cat+1)
            <<endl;
            //      <<"\t"<< ->GetBinContent(cat+1,gr+1)
        }
        std::cout << std::endl;
    }
// csv file for Jan 2018 DOE Portfolio review of many possible numbers. 
// Note that US(LPC) and US(Non-LPC) refers to the division within the US part 
// of the plots in the non-uscms LPCNew type plots
	for (int cat=0;cat<6;++cat) {
		PlotContentcsv<<"Category"<<","<<cat<<","<<category[cat]<<std::endl;
		PlotContentcsv<<"PAG,Total CADI,Authors US,Authors Not US,70% Majority authors US,70% Majority authors Not US,70% Majority of authors US(LPC),70% Majority of authors US(Non-LPC),Majority authors US,Majority authors Not US,Majority of authors US(LPC),Majority of authors US(Non-LPC),Significant Authors US,Not Significant Authors US,Significant Authors US(LPC),Significant Authors US(Non-LPC),Arc Chair US,Arc Chair nonUS,Arc Chair US(LPC),Arc Chair US(Non-LPC),A least 1 ARC member US,No ARC members US,A least 1 ARC member US(LPC),A least 1 ARC member US(Non-LPC),CADI Contact US,Not CADI Contact US,CADI Contact US(LPC),CADI Contact US(Non-LPC),Total ARC Members(All),Total ARC Members US,Total ARC Members NonUS,Total ARC Members US(LPC),Total ARC Members US(Non-LPC),Total Authors(All),Total Authors US,Total Authors NonUS,Total Authors US(LPC),Total Authors US(Non-LPC)"<<std::endl;
        for (unsigned gr = 0; gr < PAG.size(); ++gr) {
			PlotContentcsv << PAG[gr] <<","<< active2D->GetBinContent(gr+1,cat+1)
			<<","<< withUSauthors2D->GetBinContent(gr+1,cat+1)
			<<","<< activeMany2D->GetBinContent(gr+1,cat+1) - withUSauthors2D->GetBinContent(gr+1,cat+1)			
			<<","<< maj70USauthors2D->GetBinContent(gr+1,cat+1)
			<<","<< activeMany2D->GetBinContent(gr+1,cat+1) - maj70USauthors2D->GetBinContent(gr+1,cat+1)
			<<","<< maj70US_LPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<","<< maj70US_nonLPCnewauthors2D->GetBinContent(gr+1,cat+1)
			<<","<< majUSauthors2D->GetBinContent(gr+1,cat+1)
			<<","<< activeMany2D->GetBinContent(gr+1,cat+1) - majUSauthors2D->GetBinContent(gr+1,cat+1)
			<<","<< majUS_LPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<","<< majUS_nonLPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<","<< signifUSauthors2D->GetBinContent(gr+1,cat+1)
            <<","<< activeMany2D->GetBinContent(gr+1,cat+1) - signifUSauthors2D->GetBinContent(gr+1,cat+1)            
            <<","<< signifUS_LPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<","<< signifUS_nonLPCnewauthors2D->GetBinContent(gr+1,cat+1)
            <<","<< chairUS2D->GetBinContent(gr+1,cat+1)
            <<","<< active2D->GetBinContent(gr+1,cat+1) - chairUS2D->GetBinContent(gr+1,cat+1)            
            <<","<< chairLPCnew2D->GetBinContent(gr+1,cat+1)
            <<","<< chairnonLPCnew2D->GetBinContent(gr+1,cat+1)
            <<","<< arcUS2D->GetBinContent(gr+1,cat+1)                       
            <<","<< active2D->GetBinContent(gr+1,cat+1) - arcUS2D->GetBinContent(gr+1,cat+1) 
            <<","<< arcLPCnew2D->GetBinContent(gr+1,cat+1)   
            <<","<< arcnonLPCnew2D->GetBinContent(gr+1,cat+1)   
            <<","<< contactUS2D->GetBinContent(gr+1,cat+1)
            <<","<< active2D->GetBinContent(gr+1,cat+1) - contactUS2D->GetBinContent(gr+1,cat+1)         
            <<","<< contactLPCnew2D->GetBinContent(gr+1,cat+1)
            <<","<< contactnonLPCnew2D->GetBinContent(gr+1,cat+1)
            <<","<< totArc2D->GetBinContent(gr+1,cat+1)
            <<","<< totArcUS2D->GetBinContent(gr+1,cat+1)
            <<","<< totArc2D->GetBinContent(gr+1,cat+1) - totArcUS2D->GetBinContent(gr+1,cat+1)
            <<","<< totArcLPCnew2D->GetBinContent(gr+1,cat+1)
            <<","<< totArcnonLPCnew2D->GetBinContent(gr+1,cat+1)
            <<","<< totAuthors2D->GetBinContent(gr+1,cat+1)
            <<","<< totAuthorsUS2D->GetBinContent(gr+1,cat+1)
            <<","<< totAuthors2D->GetBinContent(gr+1,cat+1) - totAuthorsUS2D->GetBinContent(gr+1,cat+1)            
            <<","<< totAuthorsLPCnew2D->GetBinContent(gr+1,cat+1)
            <<","<< totAuthorsnonLPCnew2D->GetBinContent(gr+1,cat+1)
             <<std::endl;
        }
        std::cout << std::endl;
    }           
    rootfile->Write();
    rootfile->Close();
    endTableHTML();
    theTableHTML.close();
    theCADIcsv.close();
    allCADIcsv.close();
    PlotContentcsv.close();
     
    categories3bin(PAGcounts30,PAGcounts50,PAGcounts70);
    categories3binActive(PAGcounts30A,PAGcounts50A,PAGcounts70A);
    
}
