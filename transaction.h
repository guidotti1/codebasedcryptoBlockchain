#include<iostream>
#include<string>
#include<ctime>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<chrono>
#include"sha256.h"

using namepace std;

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
	

};



#endif /* TRANSACTION.H /