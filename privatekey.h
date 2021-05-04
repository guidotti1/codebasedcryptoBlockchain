#include<iostream>
#include<vector>


using namespace std;

#ifndef PRIVATEKEY_H
#define PRIVATEKEY_H

class privatekey
{
private:
	vector<int> JVector;
	vector<vector<int> >GMatrix;
	
	
public:
	//0 argument constructor
	privatekey();
	//mutator functions
	void setJVector(vector<int> setJ);
	void setGMatrix(vector<vector<int> > setG);
	//accessor functions
	vector<int> getJ();
	vector<vector<int> > getG();

	



};



#endif /* PRIVATEKEY_H */
