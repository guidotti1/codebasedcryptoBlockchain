#include <iostream>
#include <vector>
#include <stdio.h>     
#include <stdlib.h>  
#include <time.h>      
#include "stern.h"
using namespace std;





int main() {
  //simple test program for stern scheme
  vector<bool> results;
  srand(time(NULL));

  //basic parameters
  int N = 1024;
  int K = 512;
  int T = 110;

  int q = 2; //field size

  //increase based on desired level of security
  int numtrials = 60;
  cout<<"we are going to run the stern scheme "<<numtrials<<" times and see the results"<<endl;
  string sampleMessage = "asfahosypabvioxasdfh";
  cout<<"our random sample message is "<<sampleMessage<<endl;
  
  stern sternTest(N, K, T, q, sampleMessage);
  cout<<"generating public and private keys (for the signer of the message)"<<endl;
  sternTest.generatePublicPrivateKey();
  
  bool result=sternTest.runKTrials(numtrials);
  if (result)
  {
    cout<<"we are succesful after "<<numtrials<<" trials"<<endl;
  }
  else
  {
    cout<<"failure"<<endl;
  }

  return 0;
    
}

