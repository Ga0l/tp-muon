#include "Evaluate.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH1.h"


///////////////////////////////////////////////////////
Evaluate::Evaluate(TFile * inputfile){
///////////////////////////////////////////////////////
  PDF_data = (TNtuple*)inputfile->Get("data");
  DT_data = (TNtuple*)inputfile->Get("data_adv");
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
    PDF_Hist = new TH1D("PDF_Hist", "Histogram of dt", 200, 0, 30000);
    PDF_Hist->Sumw2();
    PDF_data->Draw("dt>>PDF_Hist");

    DT_Hist = new TH1D("DT_Hist", "Histogram of dt", 200, 0, 30000);
    DT_Hist->Sumw2();
    DT_data->Draw("dt>>DT_Hist");
}

void Evaluate::Fit()
{
// Fitting the histogram created with Histogram()

    FitFunction = new TF1("f", "[0] + [1]*exp(-x/[2])*(1/[2] + (1/[2]+[3])*exp(-x*[3])/[4])", 300, 30000);
    FitFunction->SetParNames("BG", "N", "tau", "lambdaC", "rho");
    FitFunction->SetParameters(220, 5.5e6, 2.19e3, 102.6e-6, 1.268);
    FitFunction->FixParameter(4, 1.268);
    FitFunction->FixParameter(3, 102.6e-6);

    std::cout << "Single-PDF MC" << std::endl;
    PDF_Hist->Fit("f", "R");
    std::cout << "Chi2/Ndof =" << FitFunction->GetChisquare()/PDF_Hist->GetNbinsX() << std::endl;
    std::cout << "Decision-Tree MC" << std::endl;
    DT_Hist->Fit("f", "R");
    std::cout << "Chi2/Ndof =" << FitFunction->GetChisquare()/DT_Hist->GetNbinsX() << std::endl;


}



void Evaluate::End(){
    PDF_Hist->Write("PDF_Hist");
    DT_Hist->Write("DT_Hist");
    file->Close();
}
