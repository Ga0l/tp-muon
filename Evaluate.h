#ifndef ANALYZE_H
#define ANALYZE_H

#include <iostream>
#include "TFile.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TF1.h"

class Evaluate{
public:
	Evaluate(TNtuple* data, TNtuple* DTs);
	~Evaluate();

  void Begin();
  void End();
  void Histogram();
  void Fit();
  void MultiFit();

private:
  TFile* file;
  TNtuple* data;
  TNtuple* DTs;

  TH1D* Hist;
  TF1* FitFunction;
  int nEvt;
};

#endif
