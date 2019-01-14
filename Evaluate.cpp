#include "Evaluate.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1.h"


///////////////////////////////////////////////////////
Evaluate::Evaluate(TNtuple* datainput, TNtuple* DTinput){
///////////////////////////////////////////////////////
  data = datainput;
  DTs = DTinput;
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
}

void Evaluate::Fit()
{
// Fitting the histogram created with Histogram()
    std::cout<<"Fit using the data without Cuts"<<std::endl;
    FitFunction = new TF1("f", "[0] + [1]*exp(-x/[2])", 200, 30000);
    FitFunction->SetParNames("F", "A", "tau", "B", "tau2");
    FitFunction->SetParameters(87, 1e4, 2e3);
    //FitFunction->SetParLimits(4, 1e3, 3e3);
    //FitFunction->SetParLimits(2, 1.8e3, 2.5e3);
    //FitFunction->SetParLimits(3, 0, 1e2);
    Hist->Fit("f", "R");

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
}



void Evaluate::End(){
    Hist->Write("Hist");
    file->Close();
}
