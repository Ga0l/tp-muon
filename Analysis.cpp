#include "Analysis.h"
#include "TNtuple.h"
#include "TFile.h"


///////////////////////////////////////////////////////
Analysis::Analysis(){
///////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////
Analysis::~Analysis(){
///////////////////////////////////////////////////////
}

void Analysis::Begin()
{
// Things to do before the event loop (open file, objects initialization...)
  file = new TFile("data.root","recreate");

  data = new TNtuple("data","data","index:t1:t2:dt");
  DTs   =  new TNtuple("DTs","DTs","dt20:dt25:dt30:dt35:dt40");
  DT_AltSigCalc =  new TNtuple("DTs","DTs","t1_alt:t2_alt:dt_alt");
  histh1 = new TH1D("h1", "Height of the first peak", 100, 0, 200);
  histh2 = new TH1D("h2", "Height of the second peak", 100, 0, 200);
  nEvt = 0;
}

void Analysis::End()
{
// Things to do after the event loop (save data, close file, free memory...)
  data->Write("data");
  DTs->Write("data");
  DT_AltSigCalc->Write("data_AltSigCalc");
  histh1->Write("histh1");
  histh2->Write("histh2");


  file->Close();
  std::cout << nEvt << " events processed" << std::endl;
}

bool Analysis::IsSignal(UCTMEvent* evt, int index, double Th){
  //Basic method: A peak is detected when the voltage is above a defined value
  double threshold = Th;
  // Converting and inverting adc channel to mV
  double value = -evt->Data[index]*evt->Gain;
  //return  value > threshold;

  //With the time at half maximum
  if(value < 0.5*threshold){
    return false;
  }

  max = 0;
  I = 0;
  for(int j = index ; j < index +20; j++){
    value =-evt->Data[j]*evt->Gain;
    max = std::max(value, max);
  }

  for(int j = index-10 ; j < index +20; j++){
    I = I + value;
  }
  value = -evt->Data[index]*evt->Gain;

  return (value > 0.5*max);
}

double AltSigCalc(UCTMEvent* evt, int index, int range){
    double D = 0;
    double D_mean;
    double value_m = -evt->Data[index]*evt->Gain;
    double value;

    for(int j = index - range ; j <= index + range ; j++){
        if (j == index) continue;
        value = -evt->Data[j]*evt->Gain;
        D = (value_m - value)/(index - j);
        D_mean += D/(2*double(range));
    }
    double i_0 =  - value_m/D_mean + index;
    return i_0 * evt->SamplingTime;
}

void Analysis::Process(UCTMEvent* evt)
{
// Thing to do for each event
nEvt++;
// Preselecting
if(false){
  return;
  }

// Peak finding
//double threshold = 20.0;
 double t = 0, t1 = -1, t2 =-1, dt;
 double h1, h2, I1, I2;
 double t1_alt = -1, t2_alt = -1, dt_alt = 0;
 //double value;

for(int i=0;i<evt->Size;i++){
  // Converting time step to time in ns
  t = i*evt->SamplingTime;
  if(IsSignal(evt, i, 20) && t1 < 0){
    t1 = t;
    h1 = max;
    I1 = I;

    t1_alt = AltSigCalc(evt, i , 3);
  }
  if(IsSignal(evt, i, 20) && t1 > 0   && t - t1 > 100){
    t2 = t;
    dt = t2- t1;
    h2 = max;
    I2 = I;

    t2_alt = AltSigCalc(evt, i , 3);
    dt_alt = t2_alt - t1_alt;

    break;
  }

 }

 histh1->Fill(h1);
 histh2->Fill(h2);

// Filling the tuple

data->Fill(evt->Index, t1, t2, dt);

DT_AltSigCalc->Fill(t1_alt, t2_alt, dt_alt);


// Filling the time differences with different cuts

if (h1>= 0 && h2>=40)         DTs->Fill(dt, dt, dt, dt, dt);
else if (h1>= 0 && h2>=35)    DTs->Fill(dt, dt, dt, dt,-100);
else if (h1>= 0 && h2>=30)    DTs->Fill(dt, dt, dt,-100,-100);
else if (h1>= 0 && h2>=25)    DTs->Fill(dt, dt,-100,-100,-100);
else if (h1>= 0 && h2>=20)    DTs->Fill(dt,-100,-100,-100,-100);

}
