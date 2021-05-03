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
blockchain mychain(blockDifficulty, desiredReward);

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

	
/*
if (sigChoice == 1){
	//secure parameters for KKS signature as described by digital signature paper
	
	string setq="2";
	string setN="2000";
	string setK="1100";
	string setn="1000";
	string setk="256";
	string sett1="440";
	string sett2="560";
	encryption trial(setq, setN, setK, setn, setk, sett1, sett2);
	//note - message is a random 256 character binary string
	trial.setMessage("0101110010110000001010100010011001101100110001000110010110010010011110110001001011000100100110010001011111000111011110010110001101001100110001000001110110011010010101100110010110001011010011111101110000100000110100000001101101110100111000101011110100101011");	
	unsigned int microsecond = 1000000;
	


	while (1 == 1)
	{
		cout<<"creating public and private key for KKS signature algorithm"<<endl;
		trial.createPublicPrivateKey();
		trial.runMagmaFile("1");
		usleep(3 * microsecond);//sleeps for 3 seconds
		trial.readPublicPrivateKey();

		//cout<<"setting message"<<endl;

		//cout<<"creating sign message program"<<endl;
		trial.signMessage();
		//cout<<"running sign message program"<<endl;
		trial.runMagmaFile("2");
		usleep(3 * microsecond);
		//cout<<"reading message signature"<<endl;
		trial.readSignature();	

		//cout<<"creating verify signature program"<<endl;
		trial.verifySignature();
		usleep(3 * microsecond);
		//cout<<"running verify message program"<<endl;
		trial.runMagmaFile("3");
		//cout<<"reading message verification"<<endl;

		bool verificationControl = trial.readVerification();
		if (verificationControl)
		{
			break;
		}
		if (!verificationControl)
		{
			trial.setOmega("");
		}
	}
}
*/

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
