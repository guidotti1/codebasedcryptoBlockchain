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
	

public:
	//0 arg constructor
	encryption();
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
