#ifndef ANALYZE_H
#define ANALYZE_H

#include <iostream>
#include "TFile.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TF1.h"

class Evaluate{
public:
	Evaluate(TFile * inputfile);
	~Evaluate();

  void Begin();
  void End();
  void Histogram();
  void Fit();
  void MultiFit();

private:
  TFile* file;
  TNtuple* data;
  TNtuple* altdata;  
  TNtuple* DTs;

  TH1D* Hist;
  TH1D* AltHist;
  TF1* FitFunction;
  int nEvt;
};

#endif
