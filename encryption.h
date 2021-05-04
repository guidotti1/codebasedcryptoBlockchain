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

	//parameters used for the KKS signature algorithm
	string q;
	string N;
	string K;
	string n;
	string k;
	string t1;
	string t2;
	//message is a binary string to be signed
	//omega is the signature as signed by KKS algorithm
	string message;
	string omega;
	

public:
	//0 arg constructor
	encryption();
	//7 arg constructor used to set parameters for KKS signature algorithm
	encryption(string setq, string setN, string setK, string setn, string setk, string sett1, string sett2);
	//create the magma file to run (this program creates public/ private key)
	void createPublicPrivateKey();
	//create a magma file to sign a binary message
	void signMessage();
	//create a magma file to verify a signed message
	void verifySignature();
	//run magma file
	//pass variable signifies which file we run (1 : creation of public/private key
	//2 : signing of message, 3 : verification of signature)
	void runMagmaFile(string pass);
	//read input from output of public/private key program
	void readPublicPrivateKey();
	//read input from output of signature program
	void readSignature();
	//read input from output of verification program
	//return true if verification succeeds, false if fails
	bool readVerification();

	//mutator functions
	void setKeys(vector<vector<int> > G, vector<vector<int> > H, vector<vector<int> > F, vector<int> J);
	void setMessage(string ourMessage);
	void setOmega(string ourOmega);
	void setPublicKey(publickey setpublic);

	
	

};



#endif /* ENCRYPTION */
