#include<iostream>
#include<vector>


using namespace std;

#ifndef PUBLICKEY_H
#define PUBLICKEY_H

class publickey
{
private:
	vector<vector<int> > FMatrix;
	vector<vector<int> > HMatrix;	
public:
	//0 argument constructor
	publickey();
	//mutator functions
	void setFMatrix(vector<vector<int> > setF);
	void setHMatrix(vector<vector<int> > setH);
	//accessor functions
	vector<vector<int> > getF();
	vector<vector<int> > getH();
	//overloading == operator -- checks to see if compare1 is equal to compare2 by checking if their 2D matrices are equal
	friend bool operator==(publickey compare1, publickey compare2);


};



#endif /* PUBLICKEY_H */
