#ifndef NEWCBPUBLIC_H
#define NEWCBPUBLIC_H

#include<vector>
#include<iostream>
using namespace std;


//public key is [H matrix, S matrix]

class newCBPublic
{

public:
	//0 argument constructor
	newCBPublic();
	//2 argument constructor
	newCBPublic(vector<vector<int> >  setHMatrix, vector<vector<int> > setSMatrix);
	//accessors
	vector<vector<int> > getHMatrix();
	vector<vector<int> > getSMatrix();
	//mutators
	void setHMatrix(vector<vector<int> > setto);
	void setSMatrix(vector<vector<int> > setto);
	//overloading == operator -- checks to see if compare1 is equal to compare2 by checking if their 2D matrices are equal
	friend bool operator==(newCBPublic compare1, newCBPublic compare2);

private:
	vector<vector<int> > HMatrix;
	vector<vector<int> > SMatrix;

};

#endif /* NEWCBPUBLIC_H  */
