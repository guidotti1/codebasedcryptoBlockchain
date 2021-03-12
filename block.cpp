#include "block.h"


//constructors
block::block()
{
	vector<transaction> emptyTransactions;
	transactions = emptyTransactions;
	timestamp=time(NULL);
	prevHash="";
	nonce=0;
	currHash = calculateHash();
}

block::block(time_t time, string prevHash, vector<transaction> setTransactions)
{

transactions=setTransactions;
timestamp=time;
prevHash=prevHash;
nonce=0;
currHash = calculateHash();
}


block::block (time_t time, vector<transaction> setTransactions, string prev, int setnonce)
{
	timestamp=time;
	transactions=setTransactions;
	prevHash=prev;
	nonce=setnonce;
	currHash = calculateHash();
}

//accessor functions
string block::getPrevHash()
{
	return prevHash;
}

vector<transaction> block::getTransactions()
{
	return transactions;
}

string block::getCurrHash()
{
	return currHash;
}


time_t block::getTimestamp()
{
	return timestamp;
}

int block::getNonce()
{
	return nonce;
}

//mutator functions
void block::setPrevHash(string setPrev)
{
	prevHash=setPrev;
}
	
void block::setCurrHash(string setCurr)
{
	currHash=setCurr;
}

void block::setTransactions(vector<transaction> set)
{
	transactions=set;
}

void block::setTimestamp(time_t setTime)
{
	timestamp=setTime;
}


void block::setNonce(int newNonce)
{
	nonce=newNonce;
}


//calculate currhash
string block::calculateHash()
{
	//ADD prevHash, index, transaction(ie. data), timestamp. Hash this all using 
	//ourhash - SHA3_256
	string input =  prevHash +  to_string(timestamp) + to_string(nonce);
	for(int i = 0; i < transactions.size(); i++)
	{
		int amt=transactions[i].getAmount();
		string from=transactions[i].getFrom();
		string to=transactions[i].getTo();
		input+=to_string(amt) + from + to;
	}

	return sha256(input);
	
}

//mine a block based on the given difficulty of the block
void block::mineBlock(int difficulty)
{
	string temp = currHash;
	string zeroesString ="";
	for (int i = 0; i < difficulty; i++)
	{
		zeroesString += '0';
	}

	while (temp.substr(0, difficulty) != zeroesString)
	{
		setCurrHash(calculateHash());
		temp=currHash;
		nonce++;
	}
	
	cout<<"We mined the block with hash: " << getCurrHash()<<endl;
}

