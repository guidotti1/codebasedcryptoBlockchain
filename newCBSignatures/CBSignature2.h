#ifndef CBSIGNATURE2_H_
#define CBSIGNATURE2_H_

#include<iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <algorithm>
using namespace std;

//stores new CB signature according to the algorithm - z and c
class CBSignature2
{

public : 

  vector<vector<int> > z;
  vector<vector<int> > c;

private :

  //default constructor
  CBSignature2();
  //two argument constructor 
  CBSignature2(vetor<vector<int> > setz, vector<vector<int> > setc);
  //accessor functions for the two components of the signature
  vector<vector<int> > getz();
  vector<vector<int> > getc();

}
