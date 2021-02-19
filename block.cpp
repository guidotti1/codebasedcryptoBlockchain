#include "block.h"


//constructors
block::block()
{
	transaction="";
	timestamp=time(NULL);
	id=0;
	prevHash="";
	currHash="";
	nonce=0;
}

block::block(int i, time_t time, string data, string prev, int setnonce)
{
	id=i;
	timestamp=time;
	transaction=data;
	prevHash=prev;
	nonce=setnonce;
	currHash = calculateHash();
}

//accessor functions
string block::getPrevHash()
{
	return prevHash;
}

string block::getTransaction()
{
	return transaction;
}

string block::getCurrHash()
{
	return currHash;
}

int block::getid()
{
	return id;
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

void block::setTransaction(string set)
{
	transaction=set;
}

void block::setTimestamp(time_t setTime)
{
	timestamp=setTime;
}

void block::setId(int setid)
{
	id=setid;
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
	string input =  prevHash + to_string(id) + to_string(timestamp) + transaction + to_string(nonce);
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
	cout<<"Having index: " << getid()<<endl;
}

