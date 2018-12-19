/// Change the name of the class to use for processing
// #define _ANALYSIS_  Oscillo
#define _ANALYSIS_  Analysis


/////////////////////////////////////////////////////////////
#include "UCTMFileReader.h"
#define _INCLUDANALYSIS_ <_ANALYSIS_.h>
#include _INCLUDANALYSIS_
#include "TString.h"

int main(int argv, char* argc[])
{
// read command line for inpue file
std::string file = "/partage/muon2/TP_Muon_Weinrich_Alguero.bin";
if(argv>1) file = argc[1];
int EvtMax = -1;
if(argv>2) EvtMax = TString(argc[2]).Atoi();

// instantiate analysis class and uctmreader class
_ANALYSIS_ ana;
UCTMFileReader pfr(file.c_str());
int NbEvt = 0;



// before loop
ana.Begin();

// main event loop
while(EvtMax>=0 ? NbEvt<EvtMax : 1)
  {
  if(NbEvt%1000==0) std::cout << NbEvt << "\r" << std::flush;
  UCTMEvent* evt = pfr.GetNextEvent();
  if(!evt) break;
  ana.Process(evt);
  NbEvt++;
  }
std::cout << "Processed events : " << NbEvt << std::endl;

// after loop
ana.End();

return 0;
}
