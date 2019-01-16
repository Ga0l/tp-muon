
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
TNtuple* data_adv = new TNtuple("data_adv","data_adv","dt");

//// singe pdf procedure
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



//// Full Stochastic procedure
TF1 *pf1 = new TF1("pf1", "[0]*exp(-x/[1])",100, 30000);
pf1->SetParNames("N", "tau");
pf1->SetParameters(A, tau);
TF1 *pf2 = new TF1("pf2", "[0]*exp(-x/[1])",100, 30000);
pf2->SetParNames("N", "tau");
pf2->SetParameters(A, tau);
TRandom* RanGen = new TRandom();


// procedure
double Ppm = 1.268/2; //muon+ to muon- ration
double PSB = 0.7; //Signal to Background ration
double Pcp = 0.05;
//

for (NbEvt = 0; NbEvt < NbMax ; NbEvt++)
    {
    if(NbEvt%1000==0) std::cout << NbEvt << "\r" << std::flush;

    if(((double)rand() / (double)RAND_MAX) >= PSB){
        // Background
        dt = RanGen->Uniform(100,30000);
    }
    else if(((double)rand() / (double)RAND_MAX) < Ppm){
        // muon-
        dt = pf1->GetRandom();
    }
    else{
        // muon+
        if(((double)rand() / (double)RAND_MAX) < Pcp){
            // Muon capture
            dt = RanGen->Uniform(100,30000);
        }
        else{
            dt = pf2->GetRandom();
        }
    }


    data_adv->Fill(dt);
  }
std::cout << "Processed events : " << NbEvt << std::endl;


//// End
data->Write("data");
data_adv->Write("data_adv");

file->Close();
return 0;
}
