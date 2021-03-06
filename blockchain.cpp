#include "blockchain.h"


blockchain::blockchain()
{
	createGenesisBlock();
	blockchainSize=0;
}

blockchain::blockchain(int setDifficulty, int setReward)
{
	createGenesisBlock();
	difficulty=setDifficulty;
	miningReward = setReward;
	blockchainSize=0;
}


void blockchain::createGenesisBlock()
{
	vector<transaction> emptyTransactions;
	block genesisBlock(time(NULL), emptyTransactions, "0", 0);
	chain.push_back(genesisBlock);
	
}

block blockchain::getLastBlock()
{
	return chain[chain.size()-1];
}


/*void blockchain::addBlock(string data)
{
	block lastBlock=getLastBlock();
	string prev = lastBlock.getCurrHash();
	block nextBlock;
	nextBlock.setPrevHash(prev);
	nextBlock.setNonce(0);
	//block nextBlock(i, time(NULL), data, prev);
	nextBlock.mineBlock(difficulty);
	chain.push_back(nextBlock);
	updateSize();
}
*/


bool blockchain::isValid()
{
	for (int i = 1; i < chain.size(); i++)
	{
		block curr = chain[i];
		block prev=chain[i-1];
		if (curr.getCurrHash()!= curr.calculateHash())
		{
			return false;
		}
		
		if (curr.getPrevHash() != prev.getCurrHash())
		{
			return false;
		}
	}
	return true;
}


vector<block> blockchain::getChain()
{
	return chain;
}


void blockchain::setChain(vector<block> setTo)
{
	chain=setTo;
}



void blockchain::minePendingTransactions(string rewardAddress)
{
	block prevBlock = getLastBlock();
	string prevHash = prevBlock.getCurrHash();
	block newBlock(time(NULL), prevHash, pending);
	newBlock.mineBlock(difficulty);
	chain.push_back(newBlock);
	cout<<"we have mined a block"<<endl;
	
	pending.clear();
	//giving a reward to the block that succesfully mined the transactions
	transaction newTransaction("", rewardAddress, miningReward);
	pending.push_back(newTransaction);
}


void blockchain::addTransaction(transaction newTransaction)
{
	pending.push_back(newTransaction);
}

void blockchain::updateSize()
{
	blockchainSize=chain.size();
}

int blockchain::getSize()
{
	return blockchainSize;
}

int blockchain::getBalanceOfAddress(string address)
{
int result=0;
vector<transaction> currTransactions;
string fromAddress;
string toAddress;
int amount;
for (int i = 0; i < chain.size(); i++)
	{
		currTransactions=chain[i].getTransactions();
		for (int j = 0; j < currTransactions.size(); j++)
		{
			fromAddress=currTransactions[j].getFrom();	
			toAddress=currTransactions[j].getTo();
			amount=currTransactions[j].getAmount();
			if (fromAddress==address)
			{
				result-=amount;
			}
			if (toAddress==address)
			{
				result+=amount;
			}
		}
		currTransactions.clear();
	}
return result;

}

