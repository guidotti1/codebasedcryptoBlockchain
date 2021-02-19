#include<iostream>
#include<vector>
#include"block.h"
#include"blockchain.h"
#include"sha256.h"

using namespace std;

int main()
{



//the user is able to choose their own block difficulty and the number of blocks that the chain will have 
int blockDifficulty;
int desiredReward;
int desiredNumberBlocks;
cout<<"What would you like your block difficulty to be? "<<endl;
cin>>blockDifficulty;
cout<<"What would you like your block reward to be? "<<endl;
cin>>desiredReward;
cout<<"How many blocks do you want the chain to have? "<<endl;
cin>>desiredNumberBlocks;
blockchain mychain(blockDifficulty, desiredReward);

cout<<"We are going to create a simple blockchain with " << desiredNumberBlocks << " blocks"<<endl;
cout<<"All that we ask is that you enter in some mock data for each transaction "<<endl;
int blockID=0;
vector<string> passData;
string nextTransaction;

for (int i = 1; i < desiredNumberBlocks; i++)
{
	blockID++;
	//get the information for this next transaction from the user
	cout<<"Enter transaction information (amount) and press enter "<<endl;
	cin>>nextTransaction;
	block recentBlock = mychain.getLastBlock();
	//create new block using unique ID and transaction you just entered
	mychain.addBlock(blockID, nextTransaction);
	
	block nextBlock=mychain.getLastBlock();
	//cout<<"hash info for the block you just entered " << nextBlock.getCurrHash()<<endl;

	//cout<<"hash info for previousBlock "<< recentBlock.getCurrHash()<<endl;
	//cout<<"timestamp for this block you just entered "<< nextBlock.getTimestamp()<<endl;
	//cout<<"ID for this block you just entered "<< nextBlock.getid()<<endl;
	//cout<<"transactions information for the block you just entered " <<nextBlock.getTransaction()<<endl;
	//cout<<endl<<endl;
}

/*
//mock version of messing with the chain, will give that the chain is invalid
//we can change any parameter (id, timestamp, transactions, hash) to get invalid chain
vector<block> change=mychain.getChain();
change[1].setId(100);
mychain.changeBlock(1, change[1]);
*/


/*
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