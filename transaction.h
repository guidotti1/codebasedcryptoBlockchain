#include<iostream>
#include<string>
#include<ctime>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<chrono>
#include"sha256.h"

using namespace std;

#ifndef TRANSACTION_H
#define TRANSACTION_H



class transaction
{

private:
	string from;
	string to;
	int amount;
	
	
public:
	//0 & 3 arg constructors
	transaction();
	transaction(string setfrom, string setto, int amount);
	//accessor and mutator functions
	void setFrom(string s);
	void setTo(string t);
	void setAmount(int a);
	string getFrom();
	string getTo();
	int getAmount();
	

};



#endif /* TRANSACTION.H */
