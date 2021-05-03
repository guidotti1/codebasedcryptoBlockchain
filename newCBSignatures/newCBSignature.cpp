#include "newCBSignature.h"

newCBSignature::newCBSignature()
{
	n=0;
	q=0;
	r=0;
	b=0;
	tsubE=0;
	wsubE=0;
	wsubC=0;
	gammaBar=0;
	k=n-r;
	vector<vector<int> > empty;
	cMatrix=empty;
	zMatrix=empty;
	message="";
}

newCBSignature::newCBSignature(int setq, int setn, int setr, int setb, int settsubE, int setwsubE, int setwsubC, int setgammaBar, int setgamma)
{	
	q=setq;
	n=setn;
	r=setr;
	b=setb;
	tsubE=settsubE;
	wsubE=setwsubE;
	wsubC=setwsubC;
	gammaBar=setgammaBar;
	gamma=setgamma;
	k=n-r;
	vector<vector<int> > empty;
	cMatrix=empty;
	zMatrix=empty;
	message="";
}

vector<vector<int> > newCBSignature::zeroIndices()
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


vector<vector<int> > newCBSignature::generateETransposeRows(vector<vector<int> > zeroIndices)
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

vector<vector<int> > newCBSignature::initializeETranspose(vector<vector<int> > rowsOfETranspose)
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

vector<int> newCBSignature::generateY(int tempq, vector<int> tempy)
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

bool newCBSignature::checkZ()
{
	bool res=true;
	bool indicator;
	vector<int> usedZ = zMatrix[0];
	for (int i=0; i<usedZ.size(); i++)
	{
		indicator=false;
		for (int j=0; j<=gammaBar; j++)
		{
			if (usedZ[i]==j)
			{
				indicator=true;
				continue;
			}
			else if(usedZ[i] == q-j)
			{
				indicator=true;
				continue;
			}
			else if ((usedZ[i]!=j) && (usedZ[i]!=q-j))
			{
		
			}
		}
		if (!indicator)
		{
			res=false;
			return res;
		}
	}
	return res;
}

void newCBSignature::setPublicPrivateKey(vector<vector<int> >  setE, vector<vector<int> > setH, vector<vector<int> >  setS)
{
	ourPrivate.setEMatrix(setE);
	ourPublic.setHMatrix(setH);
	ourPublic.setSMatrix(setS);
}

void newCBSignature::generatePublicPrivateKey()
{
	bool control=true;
	vector<vector<int> > pMatrix;
	vector<vector<int> > iMatrix;
	vector<vector<int> > hMatrix;
	
	vector<vector<int> > usedZeroIndices;
	vector<vector<int> > rowsOfE;
	
	vector<vector<int> > eTranspose;
	vector<vector<int> > eMatrix;
	
	while (control)
	{
		pMatrix = operations.generateRandomMatrix(q, r, k);
		iMatrix = operations.generateIdentityMatrix(r);
		hMatrix = operations.horizontalJoinMatrices(iMatrix, pMatrix);

		usedZeroIndices = zeroIndices();
		rowsOfE = generateETransposeRows(usedZeroIndices);

		eTranspose = initializeETranspose(rowsOfE);
		eMatrix = operations.generateTranspose(eTranspose);
		if (operations.checkSupportSizes(eMatrix, wsubE, tsubE))
		{
    		//cout<<"generated E matrix passes the support size criterion"<<endl;
    		break;
		}
		else
		{
			cout<<"fails support size criterion"<<endl;
		}

	}
	vector<vector<int> > hTranspose =  operations.generateTranspose(hMatrix);
	vector<vector<int> > sMatrix = operations.matrixMultiplication(q, eMatrix, hTranspose);
	setPublicPrivateKey(eMatrix, hMatrix, sMatrix);
	
}

void newCBSignature::generateSignature()
{
	while (true)
	{
		int tempq = 2*gamma + 1;
		vector<int> tempy = operations.generateRandomVector(tempq, n);
		vector<int> y = generateY(tempq, tempy);
		vector<vector<int> > yMatrix;
		yMatrix.push_back(y);

		vector<vector<int> > hMatrix = ourPublic.getHMatrix();
		vector<vector<int> > hTranspose = operations.generateTranspose(hMatrix);
		ssuby = operations.matrixMultiplication(q, yMatrix, hTranspose);
		string ssubystring="";
		//cout<<"ssuby becomes"<<endl;
		for (int i =0; i  < ssuby.size(); i++)
		{
			for (int j=0; j < ssuby[i].size(); j++)
			{
				ssubystring+=to_string(ssuby[i][j]);
			}
		}

		hashingtest ourhash(q, n, b, wsubC, message, ssubystring);
		string gf3Hash = ourhash.getHashGF3();
		vector<int> gfqHash = ourhash.getHashGFq(gf3Hash);
		vector<int> c=gfqHash;

		cMatrix.push_back(c);
		vector<vector<int> > eMatrix = ourPrivate.getEMatrix();
		vector<vector<int> > cTimesE = operations.matrixMultiplication(q, cMatrix, eMatrix);
		zMatrix = operations.matrixAddition(q, cTimesE, yMatrix);
	
		if (checkZ())
		{
			//cout<<"Z passes"<<endl;
			break;
		}
		else
		{
			cout<<"Z fails"<<endl;
		}
	}
	setOurSig();
}

string newCBSignature::verifySignature()
{
	cout<<"z in verify program "<<endl;
	for (int i =0; i < zMatrix.size(); i++)
	{
		for (int j =0; j <zMatrix[i].size(); j++)
		{
		cout<<zMatrix[i][j]<<" ";
		}
	}
	bool check1 = checkZ();
	cout<<"1"<<endl;
	vector<vector<int> > hMatrix = ourPublic.getHMatrix();
	cout<<"2"<<endl;
	vector<vector<int> > hTranspose = operations.generateTranspose(hMatrix);
	cout<<"3"<<endl;
	vector<vector<int> > zTimesHtranspose =  operations.matrixMultiplication(q, zMatrix, hTranspose);
	cout<<"4"<<endl;
	vector<vector<int> > sMatrix = ourPublic.getSMatrix();
	vector<vector<int> > cMatrixTimesSMatrix = operations.matrixMultiplication(q, cMatrix, sMatrix);

	vector<vector<int> > ssubyCheck =  operations.matrixSubtraction(q, zTimesHtranspose, cMatrixTimesSMatrix);
	string ssubystring="";
	for (int i=0; i<ssuby.size(); i++)
	{
		for  (int j=0; j<ssuby[i].size(); j++)
		{
			ssubystring+=to_string(ssubyCheck[i][j]);
		}
	}

	hashingtest ourhash(q, n, b, wsubC, message, ssubystring);
	string gf3Hash = ourhash.getHashGF3();
	vector<int> gfqHash = ourhash.getHashGFq(gf3Hash);
	vector<int> c=gfqHash;
	
	bool check2 = (c==cMatrix[0]);
	if (check2 && check1)
	{
		return "passes";
	}
	else 
	{
		return "fails";
	}
}

void newCBSignature::setMessage(string setto)
{
	message=setto;
}

newCBPublic newCBSignature::getPublicKey()
{
	return ourPublic;
}

newCBPrivate newCBSignature::getPrivateKey()
{
	return ourPrivate;
}

CBSignature2 newCBSignature::getOurSig()
{
	return oursig;
}

void newCBSignature::setPublicKey(newCBPublic setto)
{
	ourPublic = setto;
}

void newCBSignature::setPrivateKey(newCBPrivate setto)
{
	ourPrivate = setto;
}

void newCBSignature::setOurSig()
{
	CBSignature2 tempsig(zMatrix, cMatrix);
	oursig = tempsig;
}

void newCBSignature::setZ(vector<vector<int> > setto)
{
	zMatrix=setto;
}

void newCBSignature::setC(vector<vector<int> > setto)
{
	cMatrix=setto;
}
