#include<iostream>
#include<vector>
#include"block.h"
#include"blockchain.h"
#include"sha256.h"
#include"transaction.h"
#include"encryption.h"
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<bits/stdc++.h> 

using namespace std;


string convertHashToBinary(string hash);

int main()
{

//the user is able to choose their own block difficulty and the number of blocks that the chain will have 
int blockDifficulty=0;
int desiredReward=0;
//int desiredNumberBlocks;
cout<<"What would you like your block difficulty to be? "<<endl;
cin>>blockDifficulty;
cout<<"What would you like your block reward to be? "<<endl;
cin>>desiredReward;

/*
cout<<"How many blocks do you want the chain to have? "<<endl;
cin>>desiredNumberBlocks;
*/

blockchain mychain(blockDifficulty, desiredReward);


transaction firstTransaction("address1", "address2", 100);
transaction secondTransaction("address2", "address1", 50);
mychain.addTransaction(firstTransaction);
mychain.addTransaction(secondTransaction);

cout<<"starting mining"<<endl;
mychain.minePendingTransactions("myaddress");

cout<<"My balance"<<endl;
cout<<mychain.getBalanceOfAddress("myaddress")<<endl;


mychain.minePendingTransactions("myaddress");
cout<<"Checking again"<<endl;
cout<<mychain.getBalanceOfAddress("myaddress")<<endl;


//secure parameters for KKS signature as described by digital signature paper
string setq="2";
string setN="2000";
string setK="1100";
string setn="1000";
string setk="256";
string sett1="440";
string sett2="560";
encryption trial(setq, setN, setK, setn, setk, sett1, sett2);
trial.setMessage("0101110010110000001010100010011001101100110001000110010110010010011110110001001011000100100110010001011111000111011110010110001101001100110001000001110110011010010101100110010110001011010011111101110000100000110100000001101101110100111000101011110100101011");	
unsigned int microsecond = 1000000;
	
//string sampleHash = "e9e1a8ec0345e1407e39b07e9c7a81abe5c49b6aa246495fe2ffeb173c673840";
//cout<< convertHashToBinary(sampleHash)<<endl;
	

while (1 == 1)
{
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







/*
cout<<"We are going to create a simple blockchain with " << desiredNumberBlocks << " blocks"<<endl;
//cout<<"All that we ask is that you enter in some mock data for each transaction "<<endl;
vector<int> amounts;
int nextamt;
while (mychain.getSize() != desiredNumberBlocks)
{
	amounts.clear();
	cout<<"How many transactions you want to enter? (enter a sequence of amounts ending in -1)"<<endl;
	cin>>nextamt;
	while (nextamt != -1)
	{
		amounts.push_back(nextamt);
		cin>>nextamt;
	}
	block rewardBlock = mychain.getLastBlock();
	string rewardAddress = rewardBlock.getPrevHash();
	transaction nextTransction(rewardAddress, nextamt)
	mychain.minePendingTransactions();
}
string nextAmount;
for (int i = 1; i < desiredNumberBlocks; i++)
{
	blockID++;
	//get the information for this next transaction from the user
	cout<<"Enter transaction amount and press enter "<<endl;
	cin>>nextAmount;
	transaction newTransaction(nextAmount, i-1, i);
	block recentBlock = mychain.getLastBlock();
	//create new block using unique ID and transaction you just entered
	mychain.addBlock(nextAmount);
	block nextBlock=mychain.getLastBlock();
}
if (mychain.isValid())
{
	cout<<"great job your blockchain is valid "<<endl;
}
else
{
	cout<<"oops, it seems your blockchain is invalid "<<endl;
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
