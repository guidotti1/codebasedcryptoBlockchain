#include "newCBPublic.h"

newCBPublic::newCBPublic()
{	
	vector<vector<int> > empty;
	HMatrix=empty;
	SMatrix=empty;
}

newCBPublic::newCBPublic(vector<vector<int> >  setHMatrix, vector<vector<int> > setSMatrix)
{
	HMatrix=setHMatrix;
	SMatrix=setSMatrix;
}

vector<vector<int> > newCBPublic::getHMatrix()
{
	return HMatrix;
}

vector<vector<int> > newCBPublic::getSMatrix()
{
	return SMatrix;
}
	
void newCBPublic::setHMatrix(vector<vector<int> > setto)
{
	HMatrix=setto;
}
void newCBPublic::setSMatrix(vector<vector<int> > setto)
{
	SMatrix=setto;
}
