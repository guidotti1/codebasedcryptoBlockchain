#ifndef  STERNSIG_H_ 
#define  STERNSIG_H_ 

#include <iostream>
#include <vector>
using namespace std;


class sternSig
{

public:
  //default constructor
  sternSig();
  //full argument constructor
  sternSig(string setc1, string setc2, string setc3, vector<int> setsendu, vector<vector<string> > setsendomega, vector<vector<int> > setdirectSumUS, string setsendOmegaU, string setsendOmegaS);
  //accessor functions
  string getc1();
  string getc2();
  string getc3();
  vector<int> getsendu();
  vector<vector<string> > getsendomega();
  vector<vector<int> > getdirectSumUS();
  string getsendOmegaU();
  string getsendOmegaS();



private:
  string c1;
  string c2;
  string c3;
  vector<int> sendu;
  vector<vector<string> > sendomega;
  vector<vector<int> > directSumUS;
  string sendOmegaU;
  string sendOmegaS;


};

#endif /* STERNSIG_H_ */
