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

private:
  TFile* file;
  TNtuple* PDF_data;
  TNtuple* DT_data;

  TH1D* PDF_Hist;
  TH1D* DT_Hist;

  TF1* FitFunction;
  int nEvt;
};

#endif
