#ifndef HASHINGTEST_H_
#define HASHINGTEST_H_

#include<iostream>
#include <fstream>
#include "sha256.h"
//#include<bits/stdc++.h>
#include<stdlib.h>
#include<chrono>
#include<unistd.h>
using namespace std;


class hashingtest
{


public:
	//default constructor
	hashingtest();
	//6 arg constructor
	hashingtest(int setq, int setn, int setb, int setwsubC, string setmessage, string setssuby);
	//converts hash value to binary
	string convertHashToBinary(string hash);
	//converts a specific integer to ternary
	void convertToTernary(int N, string & res);
	//converts the whole hash to ternary
	void convertHashToTernary(string hash, string & res);
	//calculate weight (support size, number of nonzero positions) of a ternary string
	int calculateWeight(string ternaryString);

	void getcTomagma(string gfqRes);
	//based on message and ssuby, get a hash from sha-256 hashing whose weight is equal to wsubc
	string getHashGF3();
	//based on the hash from GF(3), convert to GFq
	string getHashGFq(string res);
	
	
private :
	int q;
	int n;
	int b;
	int wsubC;
	string message;
	string ssuby;
	
};


#endif /* HASHINGTEST_H_ */
