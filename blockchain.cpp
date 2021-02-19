#include "blockchain.h"


//0 arg and 1 arg constructors
blockchain::blockchain()
{
	createGenesisBlock();
}

blockchain::blockchain(int setDifficulty, setReward)
{
	createGenesisBlock();
	difficulty=setDifficulty;
	transactionReward = setReward;
}

//used to create gensisblock in constructor
void blockchain::createGenesisBlock()
{
	string data="Genesis block";
	block genesisBlock(0, time(NULL), data, "0", 0);
	chain.push_back(genesisBlock);
	
}

//last block in the chain
block blockchain::getLastBlock()
{
	return chain[chain.size()-1];
}


//adds a block by mining first, then adding
void blockchain::addBlock(int i, string data)
{
	block lastBlock=getLastBlock();
	string prev = lastBlock.getCurrHash();
	block nextBlock;
	nextBlock.setPrevHash(prev);
	nextBlock.setNonce(0);
	nextBlock.setId(i);
	nextBlock.setTransaction(data);
	//block nextBlock(i, time(NULL), data, prev);
	nextBlock.mineBlock(difficulty);
	chain.push_back(nextBlock);
}

//check the validity of chain by recalculating hashes
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

//changes a block in the chain to "change" based on unique index
void blockchain::changeBlock(int id, block change)
{
	chain[id]=change;
}

//access the chain
vector<block> blockchain::getChain()
{
	return chain;
}

//mutate the chain
void blockchain::setChain(vector<block> setTo)
{
	chain=setTo;
}
