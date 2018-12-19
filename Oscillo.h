#ifndef ANALYZE_H
#define ANALYZE_H

#include <iostream>
#include "UCTMFileReader.h"

#include "TFile.h"
class Oscillo{
public:
	Oscillo();
	~Oscillo();

  void Begin();
  void End();
  void Process(UCTMEvent* evt);

private:
  TFile *file;
};

#endif
