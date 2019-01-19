
/////////////////////////////////////////////////////////////
#include "TNtuple.h"
#include "TFile.h"
#include "TString.h"
#include "TRandom.h"
#include "TF1.h"



int main(int argv, char* argc[])
{
// initialization
int NbMax_DT  = 10000;
int NbMax_PDF = 10000;
if(argv>1){

    NbMax_PDF = TString(argc[1]).Atoi();
    if (argv>2){
        NbMax_DT = TString(argc[2]).Atoi();
    }
    else{
        NbMax_DT = NbMax_PDF;
    }
    std::cout << "Events for PDF: " << NbMax_PDF << std::endl;
    std::cout << "Events for DT: "  << NbMax_DT  << std::endl;
}
TFile* file = new TFile("MC_data.root","recreate");
TNtuple* data = new TNtuple("data","data","dt");
TNtuple* data_adv = new TNtuple("data_adv","data_adv","dt");

//// singe pdf procedure
// Setting up PDF
double BG = 220;
double N = 5.5e6;
double tau = 2.193e+03;
double lambdaC = 102.6e-6;
double tauC = 1/lambdaC;
double rho = 1.268;


TF1 *f1 = new TF1("f", "[0] + [1]*exp(-x/[2])*(1/[2] + (1/[2] + [3]) * exp(-x*[3])/[4] )",200, 30000);
f1->SetParNames("BG","N","tau","lambdaC","rho");
f1->SetParameters(BG,N,tau,lambdaC,rho);

// Iteration
double dt;
int NbEvt;
for (NbEvt = 0; NbEvt < NbMax_PDF ; NbEvt++)
  {
  if(NbEvt%1000==0) std::cout << (int)((double)NbEvt/(double)NbMax_PDF *100) << "\t"<< NbEvt << "\r" << std::flush;

  dt = f1->GetRandom();

  data->Fill(dt);
  }
std::cout << "Processed events : " << NbEvt << std::endl;



//// Full Stochastic procedure
double tauP = 2197;
double tauM = 1640;

TF1 *pf1 = new TF1("pf1", "[0]*(1/[1]) * exp(-x/[1])",100, 30000);
pf1->SetParNames("N", "tau+");
pf1->SetParameters(1, tauP);
TF1 *pf2 = new TF1("pf2", "[0]*(1/[1]) * exp(-x/[1])",100, 30000);
pf2->SetParNames("N", "tauC");
pf2->SetParameters(1, tauC);
TRandom* RanGen = new TRandom();

double lambda = 6.666666666666667e-05;

TF1 *pf3 = new TF1("pf3", "[1] * exp(-x*[0])",50, 30000);
pf2->SetParNames("lambda,N");
pf2->SetParameters(lambda,1./lambda);


// procedure
double Ppm = rho/2; //muon+ / muon- ration
double PSB = 0.59; //Signal to Background ration
//

int NP=0, NM=0, NB=0, NC=0, Nm = 0;

double t_bkg, te, tC;
for (NbEvt = 0; NbEvt < NbMax_DT ; NbEvt++)
    {
    if(NbEvt%1000==0) std::cout << NbEvt << "\r" << std::flush;

    t_bkg = RanGen->Uniform(000,30000);
    if(((double)rand() / (double)RAND_MAX) > PSB){
        // muon muon only
        dt = t_bkg;
        NB++;
    }
    else if(((double)rand() / (double)RAND_MAX) > Ppm){
        // muon-
        dt = pf1->GetRandom();
        dt = std::min(dt,t_bkg);
        NM++;
    }
    else{
        // muon+
        te = pf1->GetRandom();
        tC = pf2->GetRandom();
        dt = std::min(te ,std::min(tC ,t_bkg));
        NP++;
    }


    data_adv->Fill(dt);
  }
std::cout << "Processed events : " << NbEvt << std::endl;
std::cout << "Background, Muon+, Muon-: " << NB << "\t" << NP<< "\t" << NM<< "\t" << std::endl;



//// End
data->Write("data");
data_adv->Write("data_adv");

file->Close();
return 0;
}
