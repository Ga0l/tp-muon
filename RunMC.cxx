
/////////////////////////////////////////////////////////////
#include "TNtuple.h"
#include "TFile.h"
#include "TString.h"
#include "TRandom.h"
#include "TF1.h"



int main(int argv, char* argc[])
{
// initialization
int NbMax = 10000;
if(argv>1){
    std::cout << "Events : " << argc[1] << std::endl;

    NbMax = TString(argc[1]).Atoi();
}
TFile* file = new TFile("MC_data.root","recreate");
TNtuple* data = new TNtuple("data","data","dt");

// Setting up PDF
double A = 1.95365e+03;
double F = 8.81427e+01;
double tau = 2.189e+03;

TF1 *f1 = new TF1("f", "[0] + [1]*exp(-x/[2])",200, 30000);
f1->SetParNames("F", "A", "tau");
f1->SetParameters(F, A, tau);

// Iteration
double dt;
int NbEvt;
for (NbEvt = 0; NbEvt < NbMax ; NbEvt++)
  {
  if(NbEvt%1000==0) std::cout << NbEvt << "\r" << std::flush;

  dt = f1->GetRandom();

  data->Fill(dt);
  }
std::cout << "Processed events : " << NbEvt << std::endl;

data->Write("data");
file->Close();
return 0;
}
