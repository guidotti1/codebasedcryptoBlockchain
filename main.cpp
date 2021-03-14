#include<iostream>
#include<vector>
#include"block.h"
#include"blockchain.h"
#include"sha256.h"
#include"transaction.h"
#include"encryption.h"
#include<stdlib.h>
#include<unistd.h>

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
string setk="160";
//string setk="256";//maybe I can do it with k=256? sha-256 gives 64 characters - 512 in binary. so I can do in two passes
string sett1="90";
string sett2="110";
encryption trial(setq, setN, setK, setn, setk, sett1, sett2);
trial.setMessage("1101100110110110111010001100110001001000110001100001000000111001110010011110111111110010100010011011000000100110010000110010100010011101000001110001000000111110");	
unsigned int microsecond = 1000000;
	

while (1 == 1)
{
	trial.createPublicPrivateKey();
	trial.runMagmaFile("1");
	usleep(1 * microsecond);//sleeps for 3 seconds
	trial.readPublicPrivateKey();

	//cout<<"setting message"<<endl;

	//cout<<"creating sign message program"<<endl;
	trial.signMessage();
	//cout<<"running sign message program"<<endl;
	trial.runMagmaFile("2");
	usleep(1 * microsecond);
	//cout<<"reading message signature"<<endl;
	trial.readSignature();	

	//cout<<"creating verify signature program"<<endl;
	trial.verifySignature();
	usleep(1 * microsecond);
	//cout<<"running verify message program"<<endl;
	trial.runMagmaFile("3");
	//cout<<"reading message verification"<<endl;
	
	bool verificationControl = trial.readVerification();
	if (verificationControl)
	{
		break;
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
	int n = hash.length(); 
	for (int i = 0; i <= n; i++) 
	string ans="";
	{  
	int val = int(s[i]); 

	string bin = ""; 
	while (val > 0) 
	{ 
	    (val % 2)? bin.push_back('1') : 
		       bin.push_back('0'); 
	    val /= 2; 
	} 
	reverse(bin.begin(), bin.end()); 

	//cout << bin << " ";
	ans += bin;
	} 
	return ans;
} 
