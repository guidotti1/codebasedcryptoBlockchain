#include"newCBPrivate.h"

newCBPrivate::newCBPrivate()
{
	vector<vector<int> > empty;
	EMatrix=empty;
}

newCBPrivate::newCBPrivate(vector<vector<int> > setE)
{
	EMatrix=setE;
}

vector<vector<int> > newCBPrivate::getEMatrix()
{
	return EMatrix;
}

void newCBPrivate::setEMatrix(vector<vector<int> > setto)
{
	EMatrix=setto;
}
