#include<iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>
#include<string>
#include<bits/stdc++.h> 
#include"block.h"
#include"blockchain.h"
#include"sha256.h"
#include"transaction.h"
#include"newCBSignature.h"
#include"encryption.h"

using namespace std;


string convertHashToBinary(string hash);
//runs the blockchain simulation based on user input
//this one is for the KKS signature algorithm
void runSimulation1(int blockDifficulty, int desiredReward, int desiredNumberTransactions);
//this one is for the new CB signature algorithm
void runSimulation2(int blockDifficulty, int desiredReward, int desiredNumberTransactions);

int main()
{
srand (time(NULL));
//the user is able to choose their own block difficulty and the number of blocks that the chain will have 
int blockDifficulty=0;
int desiredReward=0;
//int desiredNumberBlocks;
cout<<"What would you like your block difficulty to be? "<<endl;
cin>>blockDifficulty;
cout<<"What would you like your block reward to be? "<<endl;
cin>>desiredReward;
cout<<"What code based digital signtaure algorithm would you like to use?"<<endl;
cout<<"Enter 1 for KKS, Enter 2 for New CB Signature, Enter 3 for Stern Identification"<<endl;
int sigChoice;
cin >> sigChoice;

int desiredNumberTransactions;
cout<<"How many transactions do you want to process in the chain? "<<endl;
cin >> desiredNumberTransactions;

if (sigChoice == 1)
{
	runSimulation1(blockDifficulty, desiredReward, desiredNumberTransactions)
}
else if (sigChoice == 2)
{
	runSimulation2(blockDifficulty, desiredReward, desiredNumberTransactions);
}


return 0;
}

string convertHashToBinary(string hash) 
{ 
	string ans="";
	for (size_t i = 0; i < hash.size(); ++i)
	{
		bitset<8> b(hash.c_str()[i]);
    		ans+= b.to_string();
	}
	return ans;
} 

void runSimulation1(int blockDifficulty, int desiredReward, int desiredNumberTransactions)
{
	blockchain mychain(blockDifficulty, desiredReward, 1);
	
	vector<publickey> publicKeys;
	vector<privatekey> privateKeys;
	encryption temp("2", "2000", "1100", "1000", "256", "440", "560");
	int microsecond = 1000;
	for (int i = 0; i < desiredNumberTransactions; i++)
	{
		temp.createPublicPrivateKey();
		temp.runMagmaFile("1");
		usleep(3 * microsecond);//sleeps for 3 seconds
		temp.readPublicPrivateKey();	
		publicKeys.push_back(temp.getPublicKey());
		privateKeys.push_back(temp.getPrivateKey());
	}
	
	vector<transaction> transactionsToBeProcessed;
	int nextTransactionAmount;
	int fromLocation;
	int toLocation;
	for (int i = 0; i < desiredNumberTransactions; i++)
	{
		nextTransactionAmount = rand() % 40 + 1;
		nextTransactionAmount = nextTransactionAmount * 5;
		fromLocation = rand() % publicKeys.size();
		toLocation = rand() % publicKeys.size();
		while (fromLocation == toLocation)
		{
			toLocation = rand() % publicKeys.size();
		} 
		transaction nextTransaction(publicKeys[fromLocation], publicKeys[toLocation], nextTransactionAmount);
		nextTransaction.signTransaction1(publicKeys[fromLocation], privateKeys[fromLocation]);
		cout<<"adding a new transaction to the pool"<<endl;
		mychain.addTransaction(nextTransaction);
	}
	cout<<"generating your public and private keys"<<endl;
	cout<<"for simplicity, you will be the only one mining the pending transactions in the blockchain"<<endl;	
	temp.createPublicPrivateKey();
	temp.runMagmaFile("1");
	usleep(3 * microsecond);//sleeps for 3 seconds
	temp.readPublicPrivateKey();	
	publickey myPublic = temp.getPublicKey();
	privatekey myPrivate = temp.getPrivateKey();

	cout<<"starting mining"<<endl;
	mychain.minePendingTransactions(myPublic);

	cout<<"My balance"<<endl;
	cout<<mychain.getBalanceOfAddress(myPublic)<<endl;

	mychain.minePendingTransactions(myPublic);
	cout<<"Checking again"<<endl;
	cout<<mychain.getBalanceOfAddress(myPublic)<<endl;

	cout<<"let's check balances of all other adresses of nodes in the chain"<<endl;
	for (int i =0; i < publicKeys.size(); i++)
	{
		cout<<"for address number " << i <<" in the vector of nodes, the balance is :"<<endl;
		cout<<mychain.getBalanceOfAddress(publicKeys[i])<<endl;
	}
}

void runSimulation2(int blockDifficulty, int desiredReward, int desiredNumberTransactions)
{
	blockchain mychain(blockDifficulty, desiredReward, 2);

	vector<newCBPublic> publicKeys;
	vector<newCBPrivate> privateKeys;

	newCBSignature temp(16381, 400, 100, 218, 156, 141, 151, 3420, 3375);
	for (int i = 0; i < desiredNumberTransactions; i++)
	{
		temp.generatePublicPrivateKey();
		publicKeys.push_back(temp.getPublicKey());
		privateKeys.push_back(temp.getPrivateKey());
	}

	vector<transaction> transactionsToBeProcessed;
	int nextTransactionAmount;
	int fromLocation;
	int toLocation;
	for (int i = 0; i < desiredNumberTransactions; i++)
	{
		nextTransactionAmount = rand() % 40 + 1;
		nextTransactionAmount = nextTransactionAmount * 5;
		fromLocation = rand() % publicKeys.size();
		toLocation = rand() % publicKeys.size();
		while (toLocation == fromLocation)
		{
			toLocation = rand() % publicKeys.size();

		}
		transaction nextTransaction(publicKeys[fromLocation], publicKeys[toLocation], nextTransactionAmount);
		nextTransaction.signTransaction2(publicKeys[fromLocation], privateKeys[fromLocation]);
		cout<<"adding a new transaction to the pool "<<endl;
		mychain.addTransaction(nextTransaction); 
	}

	cout<<"generating your public and private keys"<<endl;
	cout<<"for simplicity, you will be the only one mining the pending transactions in the blockchain"<<endl;	
	temp.generatePublicPrivateKey();
	newCBPublic myPublic = temp.getPublicKey();
	newCBPrivate myPrivate = temp.getPrivateKey();

	cout<<"starting mining"<<endl;
	mychain.minePendingTransactions(myPublic);

	cout<<"My balance"<<endl;
	cout<<mychain.getBalanceOfAddress(myPublic)<<endl;

	mychain.minePendingTransactions(myPublic);
	cout<<"Checking again"<<endl;
	cout<<mychain.getBalanceOfAddress(myPublic)<<endl;

	cout<<"let's check balances of all other adresses of nodes in the chain"<<endl;
	for (int i =0; i < publicKeys.size(); i++)
	{
		cout<<"for address number " << i <<" in the vector of nodes, the balance is :"<<endl;
		cout<<mychain.getBalanceOfAddress(publicKeys[i])<<endl;
	}
}
