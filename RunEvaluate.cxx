/// Change the name of the class to use for processing
#define _EVALUATE_  Evaluate


/////////////////////////////////////////////////////////////
#define _INCLUDEVALUATE_ <_EVALUATE_.h>
#include _INCLUDEVALUATE_
#include "TString.h"
#include "TFile.h"
#include "TNtuple.h"


int main(int argv, char* argc[])
{
// read command line for inpue file
std::string file = "data.root";
if(argv>=1) file = argc[1];

TFile* rootfile = new TFile(file.c_str());
TNtuple* datainput = (TNtuple*)rootfile->Get("data_AltSigCalc");
TNtuple* simpledata = (TNtuple*)rootfile->Get("data");
TNtuple* DTinput = (TNtuple*)rootfile->Get("data_cuts");


_EVALUATE_ eva(datainput, DTinput);


// before loop
eva.Begin();

eva.Histogram();

eva.Fit();


// after loop
eva.End();
 
_EVALUATE_ simpleva(simpledata, DTinput);


// before loop
simpleva.Begin();

simpleva.Histogram();

simpleva.Fit();


// after loop
eva.End();
return 0;
}
