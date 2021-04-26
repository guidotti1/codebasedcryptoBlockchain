#include "matrixOperations.h"


void matrixOperations::outputMatrix(vector<vector<int> > matrix)
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

vector<vector<int> > matrixOperations::generateRandomMatrix(int fieldSize, int numRows, int numCols)
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

vector<vector<int> > matrixOperations::generateIdentityMatrix(int k)
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

vector<vector<int> > matrixOperations::horizontalJoinMatrices(vector<vector<int> > leftMatrix, vector<vector<int> > rightMatrix)
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

vector<vector<int> > matrixOperations::generateTranspose(vector<vector<int> > matrix)
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

bool matrixOperations::checkSupportSizes(vector<vector<int> > matrix, int wsubE, int tsubE)
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


int matrixOperations::calculateWeight(vector<int> check)
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

vector<vector<int> > matrixOperations::matrixMultiplication(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix)
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

vector<vector<int> > matrixOperations::matrixAddition(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix)
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

vector<vector<int> > matrixOperations::matrixSubtraction(int q, vector<vector<int> > leftmatrix, vector<vector<int> > rightmatrix)
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

vector<int> matrixOperations::generateRandomVector(int q, int n)
{
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        res.push_back(rand() % q);
    }
    return res;
}

