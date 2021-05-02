#ifndef NEWCBCISGNATURE_H_
#define NEWCBCISGNATURE_H_


#include "hashingtest.h"
#include "newCBPrivate.h"
#include "newCBPublic.h"
#include "matrixOperations.h"
#include "CBSignature2.h"
using namespace std;


class   newCBSignature
{

public:

	//default constructor
	newCBSignature();
	//9 argument constructor
	newCBSignature(int setq, int setn,int setr, int setb, int settsubE, int setwsubE, int setwsubC, int setgammaBar, int setgamma);
	//get a 2D vector of zero indices (used in generating random E matrix that meets our desired criterion)
	vector<vector<int> > zeroIndices();
	//generate rows of E matrix, based on our zero indices 2-D vector
	vector<vector<int> > generateETransposeRows(vector<vector<int> > zeroIndices);
	//based on the rows of E, initialize E Transpose
	vector<vector<int> > initializeETranspose(vector<vector<int> > rowsOfETranspose);
	//generate a vector of length n y, uniformly from the elements {0, +-1, ..., +- gamma} in F_q
	vector<int> generateY(int tempq, vector<int> tempy);
	//checks to see if entries of Z are only within the subset {0, +-1, ..., +-  gammaPrime} within F_q
	bool checkZ();
	//E:private, H and S:Public
	void setPublicPrivateKey(vector<vector<int> >  setE, vector<vector<int> > setH, vector<vector<int> >  setS);
	//generate the public and private keys
	void generatePublicPrivateKey();
	//sign a given message (with z and c)
	void generateSignature();
	//verify given signature
	//involves two steps, checking if D_z(z) \ne 0 and that c=hash(m, s_y) for our calculated  s_y
	void verifySignature();
	//set message string based on what user inputs
	void setMessage(string setto);
	//functions to access the public and private keys of the algorithm
	newCBPublic getPublicKey();
	newCBPrivate getPrivateKey();
	//mutator functions to change the public and private keys of the algorithm
	void setPublicKey(newCBPublic setto);
	void setPrivateKey(newCBPrivate setto);
	//stores z matrix and c matrix as members of oursig object
	void setOurSig();
private:

	int q; 
	int n; 
	//r, b, t_e all chosen to be less than n
	int r; 
	int b; 
	int tsubE; 
	//w_e, w_c chosen to be <= b
	int wsubE; 
	int wsubC; 
	//gamma bar and gamma chosen to be gammabar<gamma<q/2
	int gammaBar; 
	int gamma; 
	//k = n - r
	int  k;
	//ourPublic stores public key of [H, S]
	newCBPublic ourPublic;
	//ourPrivate  stores private key of [E]
	newCBPrivate ourPrivate;
	matrixOperations operations;
	//Z, C used extensively in the signature generation and verification
	//Z and C are the signature themselves
	vector<vector<int> > zMatrix;
	vector<vector<int> > cMatrix;
	//our message to be signed
	string message;
	//s_y used in signature generation and verification step
	vector<vector<int> > ssuby;
	//stores the actual signature - Z and C
	CBSignature2 oursig

};


#endif /* NEWCBCISGNATURE_H_ */
