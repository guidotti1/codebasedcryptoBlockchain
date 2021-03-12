#include"privatekey.h"

privatekey::privatekey()
{

vector<int> emptyJ;
JVector =  emptyJ;
vector<vector<int> > emptyG;
GMatrix = emptyG;
}

void privatekey::setJVector(vector<int> setJ)
{
	JVector=setJ;
}

void privatekey::setGMatrix(vector<vector<int> > setG)
{
	GMatrix=setG;
}

vector<int> privatekey::getJ()
{
	return  JVector;
}

vector< vector<int> > privatekey::getG()
{
	return GMatrix;
}
