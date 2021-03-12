#include"publickey.h"

publickey::publickey()
{
vector<vector<int> > emptyF;
FMatrix = emptyF;
vector<vector<int> > emptyH;
HMatrix = emptyH;

}

void publickey::setFMatrix(vector<vector<int> > setF)
{
	FMatrix=setF;
}

void publickey::setHMatrix(vector<vector<int> > setH)
{
	HMatrix=setH;
}

vector<vector<int> > publickey::getF()
{
	return FMatrix;
}


vector<vector<int> > publickey::getH()
{
	return HMatrix;
}
