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
	if (chain[blockchainSize-1].verifyTransactions() == false)
	{
		return false;
	}
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

void blockchain::minePendingTransactions(newCBPublic rewardAddress)
{
	block prevBlock = getLastBlock();
	string prevHash = prevBlock.getCurrHash();
	block newBlock(time(NULL), prevHash, pending);
	newBlock.mineBlock(difficulty);
	chain.push_back(newBlock);
	cout<<"we have mined a block"<<endl;
	
	pending.clear();
	//giving a reward to the block that succesfully mined the transactions
	
	transaction newTransaction("NULL", rewardAddress, miningReward);
	pending.push_back(newTransaction);
}

void blockchain::addTransaction(transaction newTransaction)
{
	if (newTransaction.getFrom() == "")
	{
		cout<<"trying to add a transaction with an empty from address which is not allowed"<<endl;
		return;
	}
	if (newTransaction.getTo() == "")
	{
		cout<<"trying to add a transaction with an empty to address which is not allowed"<<endl;
		return;
	}
	if (newTransaction.isTransactionValid2() == false)
	{
		cout<<"new transaction is not valid"<<endl;
		return;
	}		
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

int blockchain::getBalanceOfAddress(newCBPublic address)
{
	int result=0;
	vector<transaction> currTransactions;
	newCBPublic fromAddress;
	newCBPublic toAddress;
	int amount;
	for (int i = 0; i < chain.size(); i++)
		{
			currTransactions=chain[i].getTransactions();
			for (int j = 0; j < currTransactions.size(); j++)
			{
				fromAddress=currTransactions[j].getfromkey();	
				toAddress=currTransactions[j].gettokey();
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

