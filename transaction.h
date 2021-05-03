#include<iostream>
#include<string>
#include<ctime>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<chrono>
#include "encryption.h"
#include "newCBSignature.h"
#include "sha256.h"

using namespace std;

#ifndef TRANSACTION_H
#define TRANSACTION_H



class transaction
{

private:
	//stores the from key itself
	newCBPublic fromkey;
	//stores fromkey as a string by converting matrices to string
	string from;
	//stores the to key itself
	newCBPublic tokey;
	//stores tokey as a string by converting matrices to string
	string to;
	int amount;
	//stores hash information of all of the above stuff
	string hash;
	//stores the signature (for the new CB Signature algorithm) that this transaction has
	CBSignature2 usedsig;
	
	
public:
	//0 & 3 arg constructors
	transaction();
	transaction(newCBPublic setfrom, newCBPublic setto, int setAmount);
	transaction(string setfrom, string setto, int setAmount);
	//note - I only really use this one in blockchain.minePendingTransactions() function
	//in which case setfrom = "NULL" and setto is the reward address
	transaction(string setfrom, newCBPublic setto, int setAmount);
	//accessor and mutator functions
	void setFrom(string s);
	void setTo(string t);
	void setAmount(int a);
	void setfromkey(newCBPublic setfrom);
	void settokey(newCBPublic setto);
	string getFrom();
	string getTo();
	int getAmount();
	newCBPublic getfromkey();
	newCBPublic gettokey();
	//sets sha 256 hash of this transaction- based on what is stored (fromaddress, toaddress, amount)
	void calculateHash();
	//sign a transaction using method 1 - KKS signature algorithm
	void signTransaction1();
	//sign a transaction using method 2 - new CB signature algorithm
	void signTransaction2(newCBPublic usedPublic, newCBPrivate usedPrivate);
	//verify the signature for the transaction using method 2 - new CB signature algorithm
	bool isTransactionValid2();
	
	

};



#endif /* TRANSACTION.H */
