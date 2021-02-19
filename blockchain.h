#include<iostream>
#include<vector>
#include"block.h"
#include"transaction.h"
#include<chrono>
using namespace std;

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H



class blockchain
{
public:
	//0 argument constructor
	blockchain();
	//2 argument constructor taking in desired difficulty & transaction reward
	blockchain(int setDifficulty, int setReward);
	//create the first block
	void createGenesisBlock();
	//access the most recent block
	block getLastBlock();
	//add a new block
	void addBlock(int i, string data);
	//check validity of the chain by comparing hashes
	bool isValid();
	//change a block based on id, change that id to changeBlock
	void changeBlock(int id, block change);
	//accessor for the chain
	vector<block> getChain();
	//mutator for the chain
	void setChain(vector<block> setTo);

private:
	//vector of blocks storing the chain
	vector<block> chain;
	//node difficulty - used in mining
	int difficulty;
	//stores all pending transactions in the chain
	vector<transaction> pending;
	//determines reward for mining;
	int transactionReward;
	




};




#endif /* BLOCKCHAIN_H */