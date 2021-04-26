#ifndef MATRIXOPERATIONS_H
#define  MATRIXOPERATIONS_H

#include<iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <algorithm>
using namespace std;

class matrixOperations
{

public:
	//output a matirx
	void outputMatrix(vector<vector<int> > matrix);
	//generate a random matrix over a finite field
	vector<vector<int> > generateRandomMatrix(int fieldSize, int numRows, int numCols);
	//generate identity matrix of size k x k
	vector<vector<int> > generateIdentityMatrix(int k);
	//return the horizontal join of two matrices
	vector<vector<int> > horizontalJoinMatrices(vector<vector<int> > leftMatrix, vector<vector<int> > rightMatrix);
	//return the transpose of a matrix
	vector<vector<int> > generateTranspose(vector<vector<int> > matrix);
	//check support size of a matrix so that each column has support size w_e and each row has support size >= t_e
	bool checkSupportSizes(vector<vector<int> > matrix, int wsubE, int tsubE);
	//calculate weight (number nonzero positions) for a given vector
	int calculateWeight(vector<int> check);
	//matrix multiplication over finite field of order q
	vector<vector<int> > matrixMultiplication(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix);
	//perform matrix addition over a finite field of order  q
	vector<vector<int> > matrixAddition(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix);
	//perform matrix subtraction over a finite field of order q
	vector<vector<int> > matrixSubtraction(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix);
	//generate a random vector of length n over finite field of order q
	vector<int> generateRandomVector(int q, int n);

private:

};



#endif /* MATRIXOPERATIONS_H */
