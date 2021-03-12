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
	void addBlock(string data);
	//check validity of the chain by comparing hashes
	bool isValid();
	//accessor for the chain
	vector<block> getChain();
	//mutator for the chain
	void setChain(vector<block> setTo);
	//send the reward for mining to rewardAddress
	void minePendingTransactions(string rewardAddress);
	//add a new transaction to pending transactions
	void addTransaction(transaction newTransaction);
	//accessor function for size
	int getSize();
	//increment size if a block is added
	void updateSize();
	//get the balance for a specific address by checking all transactions involving that address
	int getBalanceOfAddress(string address);
		
	
private:
	//vector of blocks storing the chain
	vector<block> chain;
	//node difficulty - used in mining
	int difficulty;
	//stores all pending transactions in the chain
	vector<transaction> pending;
	//determines reward for mining;
	int miningReward;
	//number of elements in blockchain
	int blockchainSize;
	




};




#endif /* BLOCKCHAIN_H */
