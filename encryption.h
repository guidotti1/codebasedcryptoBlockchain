#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include"publickey.h"
#include"privatekey.h"
#include<vector>

using namespace std;

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

class encryption
{

private:
	publickey ourPublic;
	privatekey ourPrivate;
	//vector<string> allFileNames;
	
	string message;
	//parameters used for the KKS signature algorithm
	string N;
	string K;
	string n;
	string k;
	string t1;
	string t1;
	

public:
	//0 arg constructor
	encryption();
	//6 arg constructor used to set parameters for KKS signature algorithm
	encryption(string setN, string setK, string setn, string setk, string sett1, string sett2);
	//create the magma file to run
	void createMagmaFile();
	//run magma file
	void runMagmaFile();
	//read input from text
	void readInput();
	//sign a binary message
	void signMessage();
	//verify a signed message
	void verifyMessage();
	//mutator functions
	void setPublicKey(publickey setPublic);
	void setPrivateKey(privatekey setPrivate);
	void setMessage(string ourMessage);
	

	
	

};



#endif /* ENCRYPTION */
