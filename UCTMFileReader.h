#ifndef UCTMFILEREADER_H
#define UCTMFILEREADER_H

#include <iostream>
#include <fstream>

struct UCTMEvent
  {
  int Index;               // Event number
  int Time;                // Temps de l'événement (s)
  double SamplingTime;     // Temps d'échantillonage
  short* Data;             // Donnes de l'oscilloscope (binADC)
  double Gain;             // Facteur de conversion mV/ADC
  int Size;                // Nombre de points
  UCTMEvent() {Data=0; Time=0; Size=0; SamplingTime=5; Index=-1;}
  };

class UCTMFileReader{
public:
	UCTMFileReader(const char* file=0) ;
	~UCTMFileReader() ;
	void SetDebug(int status=0) {kDebug=status;}

  void SetFile(const char*);
  UCTMEvent* GetNextEvent();

private:
	int kDebug;
//  int ReadTime(std::string strtime);
  std::ifstream fFile;
  UCTMEvent fData;
  int kSize   ;
};

#endif
