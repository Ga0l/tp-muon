#include "Evaluate.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1.h"


///////////////////////////////////////////////////////
Evaluate::Evaluate(TNtuple* datainput){
///////////////////////////////////////////////////////
  data = datainput;
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
    Hist = new TH1D("Hist", "Histogram of dt", 500, 0, 30000);
    Hist->Sumw2();
    data->Draw("dt>>Hist");
}

void Evaluate::Fit()
{
// Fitting the histogram created with Histogram()
    std::cout<<"Fit .."<<std::endl;
    FitFunction = new TF1("f", "[0] + [1]*exp(-x/[2])", 200, 30000);
    FitFunction->SetParNames("F", "A", "tau");
    FitFunction->SetParameters(87, 1e4, 2e3);
    //FitFunction->SetParLimits(4, 1e3, 3e3);
    //FitFunction->SetParLimits(2, 1.8e3, 2.5e3);
    //FitFunction->SetParLimits(3, 0, 1e2);
    Hist->Fit("f", "R");

}




void Evaluate::End(){
    Hist->Write("Hist");
    file->Close();
}
