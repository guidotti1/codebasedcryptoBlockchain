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
	string q;
	string N;
	string K;
	string n;
	string k;
	string t1;
	string t2;
	

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
	void readVerification();

	//mutator functions
	void setPublicKey(publickey setPublic);
	void setPrivateKey(privatekey setPrivate);
	void setMessage(string ourMessage);
	

	
	

};



#endif /* ENCRYPTION */
