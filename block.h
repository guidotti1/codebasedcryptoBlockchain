
#include<iostream>
#include<string>
#include<ctime>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<chrono>
#include"transaction.h"
#include"sha256.h"
using namespace std;
#ifndef BLOCK_H
#define BLOCK_H



class block
{
public:
	//0 arg. constructor
	block();
	//4 arg. constructor
	block(int i, long int time, string data, string prev, int setnonce);
	//accessor functions
	string getPrevHash();
	string getCurrHash();
	string getTransaction();
	time_t getTimestamp();
	int getid();
	int getNonce();
	//mutator functions
	void setPrevHash(string setPrev);
	void setCurrHash(string setCurr);
	void setTransaction(string set);
	void setTimestamp(time_t setTime);
	void setId(int setid);
	void setNonce(int newNonce);
	//calculate hash based on id, transactions, prevhash, timestamp
	string calculateHash();
	
	void mineBlock(int blockDifficulty);

	
	
private:
	//prevhash references the hash of the last block
	string prevHash;
	//currhash is the hash for this block
	string currHash;
	//vector of strings stores information of transaction
	string transaction;
	//unique timestamp based on when the block is created
	time_t timestamp;	
	//unique blockID
	int id;
	//random value used in the conext of mining
	int nonce;




};


#endif /* BLOCK_H */