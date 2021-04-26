#ifndef NEWCBPRIVATE_H
#define NEWCBPRIVATE_H

#include<vector>
#include<iostream>
using namespace std;

//private key is E Matrix
class  newCBPrivate
{

public:
	//default constructor
	newCBPrivate();
	//1 arg constructor
	newCBPrivate(vector<vector<int> > setE);
	//accessor
	vector<vector<int> > getEMatrix();
	//mutator
	void setEMatrix(vector<vector<int> > setto);

private:
	vector<vector<int> > EMatrix;

};

#endif /* NEWCBPRIVATE_H  */
