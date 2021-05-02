#include "CBSignature2.h";



//default constructor
CBSignature2::CBSignature2()
{
  vector<vector<int> > empty;
  z=empty;
  c=empty;
}

//two argument constructor 
CBSignature2::CBSignature2(vetor<vector<int> > setz, vector<vector<int> > setc)
{
  z = setz;
  c = setc;
}

vector<vector<int> > CBSignature2::getz()
{
  return z;
}
vector<vector<int> > CBSignature2::getc()
{
  return c;
}
