#include "UCTMFileReader.h"
#include <iomanip>

/////////////////////////////////////////////////////////////////////////////////////
UCTMFileReader::UCTMFileReader(const char* file)
/////////////////////////////////////////////////////////////////////////////////////
{
fData.Size         = 0;
fData.SamplingTime = 5.;// in ns
fData.Data = 0;
fData.Gain=0;
fData.Index=-1;
if(file) SetFile(file);
}

/////////////////////////////////////////////////////////////////////////////////////
UCTMFileReader::~UCTMFileReader()
/////////////////////////////////////////////////////////////////////////////////////
{
if(fData.Data)   delete[] fData.Data;
}

/////////////////////////////////////////////////////////////////////////////////////
void UCTMFileReader::SetFile(const char* file)
/////////////////////////////////////////////////////////////////////////////////////
{
fFile.close();
fFile.open(file, std::fstream::binary);
if(fFile.bad()||fFile.eof()) std::cout << " Cannot open file " << file << std::endl;
std::string tmp;
fFile >> tmp >> tmp >> tmp >> fData.Gain;
fFile >> tmp >> tmp >> fData.Size; 
fFile >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> kSize ;
fFile>> tmp;
char toto;
fFile.read(&toto,1);
}

/////////////////////////////////////////////////////////////////////////////////////
UCTMEvent* UCTMFileReader::GetNextEvent()
/////////////////////////////////////////////////////////////////////////////////////
{
if(!fFile.good() || fFile.eof()) 
  {
  return 0;
  }
if(!fData.Data) fData.Data = new short[fData.Size];
fFile.read ((char*) &fData.Time, 4);
char* tmp = (char*)  fData.Data;
fFile.read (tmp, (fData.Size)*kSize);
fData.Index++;
return &fData;
}

