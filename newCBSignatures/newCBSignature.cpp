#include<iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <algorithm>
#include "hashingtest.h"
using namespace std;

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
//get a 2D vector of zero indices (used in generating random E matrix that meets our desired criterion)
vector<vector<int> > zeroIndices(int n, int b, int wsubE);
//generate rows of E matrix, based on our zero indices 2-D vector
vector<vector<int> > generateETransposeRows(vector<vector<int> > zeroIndices, int b, int wsubE);
//based on the rows of E, initialize E Transpose
vector<vector<int> > initializeETranspose(int n, int b, int q, vector<vector<int> > rowsOfETranspose);
//generate a random vector of length n over finite field of order q
vector<int> generateRandomVector(int q, int n);
//generate a vector of length n y, uniformly from the elements {0, +-1, ..., +- gamma} in F_q
vector<int> generateY(int n, int q, int tempq, vector<int> tempy, int gamma);
//matrix multiplication over finite field of order q
vector<vector<int> > matrixMultiplication(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix);
//perform matrix addition over a finite field of order  q
vector<vector<int> > matrixAddition(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix);
//perform matrix subtraction over a finite field of order q
vector<vector<int> > matrixSubtraction(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix);

int main()
{
srand(time(NULL));
int q = 7;
int n= 400;

//r, b, t_e all chosen to be less than n
int r = 100;
int b = 218;
int tsubE = 156;

//w_e, w_c chosen to be <= b
int wsubE = 141;
int wsubC = 151;

//gamma bar and gamma chosen to be gammabar<gamma<q/2
int gammaBar = 1;
int gamma = 2;

int k = n-r;

//KEY GENERATION
vector<vector<int> > pMatrix = generateRandomMatrix(q, r, k);
vector<vector<int> > iMatrix = generateIdentityMatrix(r);
vector<vector<int> > hMatrix = horizontalJoinMatrices(iMatrix, pMatrix);


vector<vector<int> > usedZeroIndices = zeroIndices(n, b, wsubE);
vector<vector<int> > rowsOfE = generateETransposeRows(usedZeroIndices, b, wsubE);


vector<vector<int> > eTranspose = initializeETranspose(n, b, q, rowsOfE);
vector<vector<int> > eMatrix = generateTranspose(eTranspose);
if (checkSupportSizes(eMatrix, wsubE, tsubE))
{
    //cout<<"generated E matrix passes the support size criterion"<<endl;
}

vector<vector<int> > sMatrix = matrixMultiplication(q, eMatrix, generateTranspose(hMatrix));

//private key is E Matrix
//public key is [H matrix, S matrix]

//SIGNATURE GENERATION
int tempq = 2*gamma + 1;
vector<int> tempy = generateRandomVector(tempq, n);

//cout<<"generating y"<<endl;
vector<int> y = generateY(n, q, tempq, tempy, gamma);

//cout<<"y becomes "<<endl;
//for (int i =0; i <y.size(); i++)
//{
    //cout<<y[i] << " ";
//}
//cout <<endl;

vector<vector<int> > yMatrix;
yMatrix.push_back(y);

vector<vector<int> >  ssuby = matrixMultiplication(q, yMatrix, generateTranspose(hMatrix));

	
string ssubystring="";
//cout<<"ssuby becomes"<<endl;
for (int i =0; i  < ssuby.size(); i++)
{
	for (int j=0; j < ssuby[i].size(); j++)
	{
		ssubystring+=to_string(ssuby[i][j]);
		//cout<<ssuby[i][j]<<" ";
	}
	//cout<<endl;
}
//cout<<endl;

//cout<<"generating a random message (20 random numbers)"<<endl;
string message="";
for (int i=0; i<20; i++)
{
	message+=to_string(rand() % 10);
}

//cout<<"performing the desired hashing"<<endl;
hashingtest ourhash(q, n, b, wsubC, message, ssubystring);
string gf3Hash = ourhash.getHashGF3();
string gfqHash = ourhash.getHashGFq(gf3Hash);
//cout<<"hash in gfq meeting desired weight requirement"<<endl;
//cout<<gfqHash<<endl;

vector<int> c;
string nextchar;
for (int i=0; i<gfqHash.length(); i++)
{
	nextchar=gfqHash[i];
	c.push_back(stoi(nextchar));
	nextchar="";
}

vector<vector<int> > cMatrix;
cMatrix.push_back(c);


vector<vector<int> > cTimesE = matrixMultiplication(q, cMatrix, eMatrix);
vector<vector<int> > zMatrix = matrixAddition(q, cTimesE, yMatrix);





//signature part 1 is z
//signature part 2 is c

//SIGNATURE VERIFICATION
vector<vector<int> > zTimesHtranspose =  matrixMultiplication(q, zMatrix, generateTranspose(hMatrix));
vector<vector<int> > cMatrixTimesSMatrix = matrixMultiplication(q, cMatrix, sMatrix);

vector<vector<int> > ssubyCheck =  matrixSubtraction(q, zTimesHtranspose, cMatrixTimesSMatrix);

//cout<<"s sub y check"<<endl;
outputMatrix(ssubyCheck);

bool ssubyEqual=true;
for (int i=0; i<ssubyCheck[0].size(); i++)
{
	if (ssubyCheck[0][i] != ssuby[0][i])
	{
		ssubyEqual=false;
		break;
	}
}

if(ssubyEqual)
{
	cout<<"ssuby final is equal to original"<<endl;
}
else
{
	cout<<"oops"<<endl;
}


return 0;
}

void outputMatrix(vector<vector<int> > matrix)
{
    for (int i = 0; i < matrix.size(); i++)
        {
        for (int j = 0; j < matrix[i].size(); j++)
            {
                cout<<matrix[i][j]<<" ";
            }
        cout<<endl;
        }
    return;
}


vector<vector<int> > generateRandomMatrix(int fieldSize, int numRows, int numCols)
{
    vector<vector<int> > res;
    vector<int> nextRow;
    for (int i = 0; i < numRows; i++)
        {
            nextRow.clear();
            for (int j = 0; j <numCols; j++)
                {
                    nextRow.push_back(rand() % fieldSize);
                }
            res.push_back(nextRow);
        }
    return res;
}

vector<vector<int> > generateIdentityMatrix(int k)
{
    vector<vector<int> > res;
        for (int i = 0; i < k; i++)
        {
            vector<int> nextRow(k, 0);
            nextRow[i] = 1;
            res.push_back(nextRow);
        }
    return res;
}

vector<vector<int> > horizontalJoinMatrices(vector<vector<int> > leftMatrix, vector<vector<int> > rightMatrix)
{
    vector<vector<int> > res;
    vector<int> nextrow;
    for (int i = 0; i < leftMatrix.size(); i++)
        {
        nextrow.clear();
        for (int j = 0; j < leftMatrix[i].size(); j++)
            {
                nextrow.push_back(leftMatrix[i][j]);
            }
        for (int j = 0; j < rightMatrix[i].size(); j++)
            {
                nextrow.push_back(rightMatrix[i][j]);
            }
        res.push_back(nextrow);
        }
    return res;
}

vector<vector<int> > generateTranspose(vector<vector<int> > matrix)
{
    vector<vector<int> > res;
    vector<int> nextrow;
    for (int i = 0; i < matrix[0].size(); i++)
        {
            nextrow.clear();
            for (int j = 0; j < matrix.size(); j++)
                {
                nextrow.push_back(matrix[j][i]);
                }
            res.push_back(nextrow);
        }
    return res;
}

bool checkSupportSizes(vector<vector<int> > matrix, int wsubE, int tsubE)
{
    vector<vector<int> > matrixTranspose = generateTranspose(matrix);
    int weightCheck;
    bool resOne = true;
    for (int i = 0; i < matrixTranspose.size(); i++)
        {
            weightCheck = calculateWeight(matrixTranspose[i]);
            if (weightCheck != wsubE)
                {
                //BAD
                resOne = false;
                break;
                }
            else
                {
                resOne = true;
                }
        }
    bool resTwo = true;
    for (int i = 0; i < matrix.size(); i++)
        {
            weightCheck = calculateWeight(matrix[i]);
            if (weightCheck < tsubE)
                {
                //BAD
                resTwo = false;
                break;
                }
            else
                {
                resTwo = true;
                }
        }
    return ((resOne)&&(resTwo));
}


int calculateWeight(vector<int> check)
{
    int res = 0;
    for (int i =0; i <check.size(); i++)
        {
            if (check[i] != 0)
                {
                res ++;
                }
        }
    return res;
}

vector<vector<int> > zeroIndices(int n, int b, int wsubE)
{
    vector<vector<int> >  res;
    vector<int> next;
    bool control;
    int randOne;
    for (int i =0; i < n; i++)
    {
        next.clear();
        do
        {
            randOne = rand() % b;
            control = true;
            for (int j = 0; j < next.size(); j++)
            {
                if (randOne  == next[j])
                {
                    control=false;
                }
            }
            if (control)
            {
                next.push_back(randOne);
            }

        } while (next.size() < (b - wsubE));

        sort(next.begin(), next.end());
        res.push_back(next);
    }
    return res;
}


vector<vector<int> > generateETransposeRows(vector<vector<int> > zeroIndices, int b, int wsubE)
{
    vector<vector<int> > res;
    vector<int> nextRow;
    int nextIndex;
    int remaining;
    int chooseRand;
    for (int i = 0; i < zeroIndices.size(); i++)
    {
        nextRow.clear();
        nextIndex = 0;
        remaining = b+1;
        for (int j = 0; j < b; j++)
        {
            if (nextIndex == (b-wsubE))
            {
                remaining = j;
                break;
            }
            if (j == zeroIndices[i][nextIndex])
            {
                nextRow.push_back(0);
                nextIndex++;
            }
            else
            {
                chooseRand = rand() % 2 +1;
                nextRow.push_back(chooseRand);
            }
        }
        for (int j = remaining; j < b; j++)
        {
            chooseRand = rand() % 2 +1;
            nextRow.push_back(chooseRand);
        }
        res.push_back(nextRow);
    }
    return res;
}

vector<vector<int> > initializeETranspose(int n, int b, int q, vector<vector<int> > rowsOfETranspose)
{
    vector<vector<int> > res;
    vector<int> nextrow;
    for (int i =0; i <n; i++)
    {
        nextrow.clear();
        int count=0;
        for (int j =0; j<b; j++)
        {
            if (rowsOfETranspose[i][j] == 2)
            {
                nextrow.push_back(q-1);
            }
            else if (rowsOfETranspose[i][j] == 1)
            {
                nextrow.push_back(1);
            }
            else if (rowsOfETranspose[i][j] == 0)
            {
                count++;
                nextrow.push_back(0);
            }
        }
        res.push_back(nextrow);
    }
    return res;
}

vector<int> generateRandomVector(int q, int n)
{
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        res.push_back(rand() % q);
    }
    return res;
}

vector<int> generateY(int n, int q, int tempq, vector<int> tempy, int gamma)
{
    vector<int> res;
    for (int i =0 ; i <n; i++)
    {
        for (int j = 0; j<= gamma; j++)
        {
            if (tempy[i] == j)
            {
            	res.push_back(j);
            }
            else if (tempy[i]==tempq-j)
            {
            	res.push_back(q-j);
            }
        }
    }
    return res;
}

vector<vector<int> > matrixMultiplication(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix)
{
	vector<vector<int> > res;
	vector<int> nextrow;
	int temp = 0;
	for (int i = 0; i < leftmatrix.size(); i ++)
	{
	  for (int j = 0; j < rightmatrix[0].size(); j++)
	  {
        for (int k = 0; k <rightmatrix.size(); k++)
        {
            temp += (leftmatrix[i][k] * rightmatrix[k][j]) % q;
        }
        temp = temp % q;
        nextrow.push_back(temp);
        temp = 0;
	  }
	  res.push_back(nextrow);
	  nextrow.clear();
	}
	return res;
}

vector<vector<int> > matrixAddition(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix)
{
	vector<vector<int> >res;
	vector<int> nextrow;
	int temp;
	for (int i=0; i<leftmatrix.size(); i++)
	{
		for (int j=0; j<leftmatrix[i].size(); j++)
		{
			temp=(leftmatrix[i][j]+rightmatrix[i][j])%q;
			nextrow.push_back(temp);
		}
		res.push_back(nextrow);
		nextrow.clear();
	}
	return res;
}


vector<vector<int> > matrixSubtraction(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix)
{
	vector<vector<int> >res;
	vector<int> nextrow;
	int temp;
	for (int i=0; i<leftmatrix.size(); i++)
	{
		for (int j=0; j<leftmatrix[i].size(); j++)
		{
			temp=(leftmatrix[i][j]-rightmatrix[i][j])%q;
			if (temp<0)
			{
				temp+=q;
			}
			nextrow.push_back(temp);
		}
		res.push_back(nextrow);
		nextrow.clear();
	}
	return res;
}
