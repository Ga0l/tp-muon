#include "Evaluate.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1.h"


///////////////////////////////////////////////////////
Evaluate::Evaluate(TFile * inputfile){
///////////////////////////////////////////////////////
  data = (TNtuple*)inputfile->Get("data");
  altdata = (TNtuple*)inputfile->Get("data_AltSigCalc");
  DTs = (TNtuple*)inputfile->Get("data_cuts");
}

///////////////////////////////////////////////////////
Evaluate::~Evaluate(){
///////////////////////////////////////////////////////
}

void Evaluate::Begin(){
    file = new TFile("evaluate.root", "recreate");

}


void Evaluate::Histogram()
{
// Filling the histogram with the dt values from TNtuple
    Hist = new TH1D("Hist", "Histogram of dt", 200, 0, 30000);
    Hist->Sumw2();
    data->Draw("dt>>Hist");

    AltHist = new TH1D("AltHist", "Histogram of dt", 200, 0, 30000);
    AltHist->Sumw2();
    altdata->Draw("dt>>AltHist");
}

void Evaluate::Fit()
{
// Fitting the histogram created with Histogram()

    FitFunction = new TF1("f", "[0] + [1]*exp(-x/[2])*(1/[2] + (1/[2]+[3])*exp(-x*[3])/[4])", 300, 30000);
    FitFunction->SetParNames("BG", "N", "tau", "lambdaC", "rho");
    FitFunction->SetParameters(220, 5.5e6, 2.19e3, 102.6e-6, 1.268);
    FitFunction->FixParameter(4, 1.268);
    FitFunction->FixParameter(3, 102.6e-6);
    
    Hist->Fit("f", "R");
    std::cout << "Chi2/Ndof =" << FitFunction->GetChisquare()/Hist->GetNbinsX() << std::endl;
    AltHist->Fit("f", "R");
    std::cout << "Chi2/Ndof =" << FitFunction->GetChisquare()/AltHist->GetNbinsX() << std::endl;


}


void Evaluate::MultiFit(){
    //Fitting all the histograms with different cuts

    FitFunction = new TF1("f", "[0] + [1]*exp(-x/[2])", 200, 30000);
    FitFunction->SetParNames("F", "A", "tau", "B", "tau2");
    FitFunction->SetParameters(87, 1e4, 2e3);

    TH1D* Hist20 = new TH1D("Hist", "Histogram of dt", 200, 0, 30000);
    Hist20->Sumw2();
    DTs->Draw("dt20>>Hist");

    TH1D* Hist25 = new TH1D("Hist", "Histogram of dt", 200, 0, 30000);
    Hist25->Sumw2();
    DTs->Draw("dt25>>Hist");

    TH1D* Hist30 = new TH1D("Hist", "Histogram of dt", 200, 0, 30000);
    Hist30->Sumw2();
    DTs->Draw("dt30>>Hist");

    TH1D* Hist35 = new TH1D("Hist", "Histogram of dt", 200, 0, 30000);
    Hist35->Sumw2();
    DTs->Draw("dt35>>Hist");

    TH1D* Hist40 = new TH1D("Hist", "Histogram of dt", 200, 0, 30000);
    Hist40->Sumw2();
    DTs->Draw("dt40>>Hist");

    std::cout<<"Fits using the data with thresholds beeing applied"<<std::endl;

    std::cout<<"20"<<std::endl;
    Hist20->Fit("f", "R");
    std::cout<<"25"<<std::endl;
    Hist25->Fit("f", "R");
    std::cout<<"30"<<std::endl;
    Hist30->Fit("f", "R");
    std::cout<<"35"<<std::endl;
    Hist35->Fit("f", "R");
    std::cout<<"40"<<std::endl;
    Hist40->Fit("f", "R");

    Hist25->Write("Hist25");
    Hist30->Write("Hist30");
    Hist35->Write("Hist35");
    Hist40->Write("Hist40");

}



void Evaluate::End(){
    Hist->Write("Hist");
    AltHist->Write("AltHist");
    file->Close();
}
