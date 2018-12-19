#ifndef ANALYZE_H
#define ANALYZE_H

#include <iostream>
#include "UCTMFileReader.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH1.h"

class Analysis{
public:
	Analysis();
	~Analysis();


  void Begin();
  void End();
  bool IsSignal(UCTMEvent* evt, int index, double Th);
  void Process(UCTMEvent* evt);

private:
  TNtuple* data;
  TNtuple* DTs;
  TFile* file;
  int nEvt;
  int nSamples;
  double max;
  double I;
  TH1D* histh1;
  TH1D* histh2;
};

#endif
