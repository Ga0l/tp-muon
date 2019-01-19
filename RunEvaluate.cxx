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
if(argv > 1){
    file = argc[1];
}

TFile* rootfile = new TFile(file.c_str());



_EVALUATE_ eva(rootfile);

// before loop
eva.Begin();

eva.Histogram();

eva.Fit();



// after loop
eva.End();

return 0;
}
