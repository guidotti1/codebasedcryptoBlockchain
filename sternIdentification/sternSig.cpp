#include "sternSig.h"

sternSig::sternSig()
{
  c1="";
  c2="";
  c3="";
  vector<int> empty;
  sendu=empty;
  vector<vector<string> > emptys;
  sendomega = emptys;
  vector<vector<int> > emptyi;
  directSumUS=emptyi;
  sendOmegaU="";
  sendOmegaS="";
}

sternSig::sternSig(string setc1, string setc2, string setc3, vector<int> setsendu, vector<vector<string> > setsendomega, vector<vector<int> > setdirectSumUS, string setsendOmegaU, string setsendOmegaS)
{
  c1=setc1;
  c2=setc2;
  c3=setc3;
  sendu=setsendu;
  sendomega=setsendomega;
  directSumUS=setdirectSumUS;
  sendOmegaU=setsendOmegaU;
  sendOmegaS=setsendOmegaS;

}

string sternSig::getc1()
{
  return c1;
}

string sternSig::getc2()
{
  return c2;
}

string sternSig::getc3()
{
  return c3;
}

vector<int> sternSig::getsendu()
{
  return sendu;
}

vector<vector<string> > sternSig::getsendomega()
{
  return sendomega;
}

vector<vector<int> > sternSig::getdirectSumUS()
{
  return directSumUS;
}

string sternSig::getsendOmegaU()
{
  return sendOmegaU;
}

string sternSig::getsendOmegaS()
{
  return sendOmegaS;
}
