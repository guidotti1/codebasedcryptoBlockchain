#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<bits/stdc++.h>
#include"sha256.h"
using namespace std;


//omega is the permutation we are using
//change string is what we are applying permutation to.
void runPermutation(vector<vector<string> > perm, string &change);
//multiply a binary matrix with a column vector
string binaryMatrixMultiplication(vector<vector<int> > matrix, vector<vector<int> > messageTranspose);
//generate the transpose of a one row vector
vector<vector<int> > generateTranspose(string message);
//subtract two binary vectors
string binarySubtraction(string v1, string v2);
class sternIdentification
{
private :
    //private key
    string s;
    //public key
    string y;
    //H is a (n-k) * n binary matrix common to all users
    vector<vector<int> > H;
    //permutation
    //each cycle of the permutation is stored as a vector of strings in the vector
    vector<vector<string> > omega;
    //u is random vector over F_{2}^{N}
    string u;
    //direct sum u + s;
    string directSumUandS;
    //H times u transpose
    string HuTranspose;
    //N, K, T are the parameters used in stern's idenification
    string N;
    string K;
    string T;


public :
    //0 argument constructor
    sternIdentification();
    //3 argument constructor that takes N, K, T
    sternIdentification(string setN, string setK, string setT);
    //create magma file to run stern's identification scheme. prints all necessary information to hash commitment information
    void createSternScheme();
    //write to the system to run stern's identification scheme
    void runSternScheme();
    //read output from stern scheme
    void readSternScheme();
    //calculate c1, c2, c3 according to provision for stern scheme
    //returns vector of strings having these three and sends that to receiver 
    vector<string> calculateCs();
    //generate response (b = 0, 1, 2)
    //based on these, prover sends certain information to receiver
    int generateResponse();
    //accessor functions
    string getU(); 
    string getHuTranspose();
    string getDirectSumUandS();
    string getS();
    string getY();
    vector<vector<int> > getH();
    vector<vector<string> > getOmega();	
    
     



};

int main()
{
    sternIdentification test("1024", "512", "110");
    unsigned int microsecond = 1000000;


    test.createSternScheme();
    usleep(2 * microsecond);
    test.runSternScheme();
    usleep(2 * microsecond);
    test.readSternScheme();
	
     vector<string> cVector = test.calculateCs();
     /*
     for (int i = 0; i < cVector.size(); i++)
     {
	  cout<<" i : " << i + 1  << "c_{i} "<<  cVector[i]<<endl;
     }
     */
     int b = test.generateResponse();
     //b=0;
     string sendU; 
     string calculateHUTranspose;
     string sendDirectSum;
     vector<vector<string >> sendOmega; 
     string sendS;
     vector<vector<int >> sendH;
     //based on response (random in {0, 1, 2})
     //P sends information to V
     b=0;
     if (b == 0)
     {
	     sendU = test.getU();
	     //sendHuTranspose = test.getHuTranspose();
	     sendOmega = test.getOmega();
	     sendH = test.getH();
	     vector<vector<int> > uTranspose = generateTranspose(sendU);
	     calculateHUTranspose = binaryMatrixMultiplication(sendH, uTranspose);
     }
     if (b==1)
     {
	     sendDirectSum = test.getDirectSumUandS();
	     //sendHuTranspose = test.getHuTranspose();
	     sendOmega = test.getOmega();
	     sendH = test.getH();
	     vector<vector<int> > directSumTranspose = generateTranspose(sendDirectSum);
	     calculateHTimesDirectSum = binaryMatrixMultiplication(sendH, directSumTranspose);
     }
     if (b==2)
     {
	     sendU = test.getU();
	     sendS = test.getS();
     }
	
     bool endRes;	
     //now, based on b V will finally verify the calculations
     //b == 0, check c1 and c2
      
     if (b == 0)
     {
	     string combinedOmega="";
	     for (int i = 0; i < sendOmega.size(); i++)
	     {
		     for (int j = 0; j < sendOmega[i].size(); j++)
		     {
			     combinedOmega += sendOmega[i][j];
		     }
	     }
	     string checkc1 = sha256(combinedOmega + calculateHUTranspose);
	     if (checkc1 == cVector[0])
	     {
		     endRes = true;
	     }
	     else
	     {
		     endRes = false;
	     }
	     
	     string tempU = sendU;
	     runPermutation(sendOmega, tempU);
	     string checkc2 = sha256(tempU);
	     if (checkc2 == cVector[1])
	     {
		     endRes = true;
	     }
	     else
	     {
		     endRes =  false;
	     }
     }
     //b == 1, check c1 and c3	
	/*
     if (b == 1)
     {
	     string combinedOmega="";
	     for (int i = 0; i < sendOmega.size(); i++)
	     {
		     for (int j = 0; j < sendOmega[i].size(); j++)
		     {
			     combinedOmega += sendOmega[i][j];
		     }
	     }
	     string checkc1 = sha256(combinedOmega + sendHuTranspose);
	     if (checkc1 == cVector[0])
	     {
		     endRes = true;
	     }
	     else
	     {
		     endRes = false;
	     }
	     
	     string tempDirectSum = sendDirectSum;
             runPermutation(sendOmega, tempDirectSum);
	     string checkc3 = sha256(tempDirectSum);
	     if (checkc3 == cVector[2])
	     {
		     endRes = true;
	     }
	     else
	     {
		     endRes =  false;
	     }
     }
     */
	
	if (endRes)
	{
	cout<<"lets go "<<endl;
	}
     //if (b==1)
     //{
	     


return 0;
}

void runPermutation(vector<vector<string> > perm, string & change)
{
  vector<char> temp;
  for (int i = 0; i < perm.size(); i++)
  {
    for (int j = 0; j < perm[i].size(); j++)
    {
      temp.push_back(change[stoi(perm[i][j])]);                       
    }

    change[stoi(perm[i][0])] = temp[temp.size()-1];

    for (int j = 1; j < perm[i].size(); j++)
    {
      change[stoi(perm[i][j])] = temp[j-1]; 
    }
    temp.clear();
  }
  return;
}

sternIdentification::sternIdentification()
{
    s="";
    y="";
    vector<vector<string> > emptyVect;
    omega = emptyVect;
    u="";
    directSumUandS="";
    HuTranspose="";
    N="";
    K="";
    T="";
}

sternIdentification::sternIdentification(string setN, string setK, string setT)
{
    s="";
    y="";
    vector<vector<string> > emptyVect;
    omega = emptyVect;
    u="";
    directSumUandS="";
    HuTranspose="";
    N= setN;
    K= setK;
    T= setT;
}

void sternIdentification::createSternScheme()
{
    ofstream s;
    string filename = "createSternScheme.txt";
    s.open(filename.c_str());
    s<<"q:=2;"<<endl;
    s<<"F:=GF(q);"<<endl;

    s<<"N:="+N+";"<<endl;
    s<<"K:="+K+";"<<endl;
    s<<"T:="+T+";"<<endl;

    s<<"G:=RandomMatrix(F, K, N);"<<endl;
    s<<"C:=LinearCode(G);"<<endl;
    s<<"H:=ParityCheckMatrix(C);"<<endl;

    s<<"firstNIntegers:=[];"<<endl;
    s<<"for i in [1..N] do"<<endl;
    s<<"   Append(~firstNIntegers, i);"<<endl;
    s<<"end for;"<<endl;

    s<<"oneIndices:=[];"<<endl;
    s<<"for i in [1..T] do"<<endl;
        s<<"RandomIndex:=Random(1, #firstNIntegers);"<<endl;
        s<<"Append(~oneIndices, firstNIntegers[RandomIndex]);"<<endl;
        s<<"Remove(~firstNIntegers, RandomIndex);"<<endl;
    s<<"end for;"<<endl;
    s<<"oneIndices := Sort(oneIndices);"<<endl;

    s<<"dimensionNSpace := VectorSpace(F, N);"<<endl;
    s<<"s := Random(dimensionNSpace);"<<endl;
    s<<"oneIndicesCounter:=1;"<<endl;
    s<<"rest := N+1;"<<endl;
    s<<"for i in [1..N] do"<<endl;
        s<<"if (oneIndicesCounter eq T+1) then "<<endl;
            s<<"rest := i;"<<endl;
            s<<"break;"<<endl;
        s<<"end if;"<<endl;
        s<<"if (oneIndices[oneIndicesCounter] eq i) then"<<endl;
            s<<"s[i] := F!1;"<<endl;
            s<<"oneIndicesCounter := oneIndicesCounter + 1; "<<endl;
        s<<"else "<<endl;
            s<<"s[i] := F!0;"<<endl;
        s<<"end if;"<<endl;
    s<<"end for;"<<endl;

    s<<"for i in [rest..N] do    "<<endl;
        s<<"s[i] := F!0;"<<endl;
    s<<"end for;"<<endl;

    s<<"//print \"Weight(s)\";"<<endl;
    s<<"//Weight(s);"<<endl;
    s<<"//private key is s in F_{2}^N such that weight(s) = T"<<endl;
    s<<"privateKey := s;"<<endl;
    s<<"sMatrix := RandomMatrix(F, 1, N);"<<endl;
    s<<"sMatrix[1] := s;"<<endl;

    s<<"//publick key is y in F_{2}^N-K such that Hs^{T} = y"<<endl;
    s<<"y:= H*Transpose(sMatrix);"<<endl;
    s<<"//y is column vector so I am just storing as a row in publicKey"<<endl;
    s<<"publicKey:=Transpose(y);"<<endl;

    s<<"//commitments"<<endl;
    s<<"u := Random(dimensionNSpace);"<<endl;

    s<<"permGroup := SymmetricGroup(N);"<<endl;
    s<<"omega:= Random(permGroup);"<<endl;
    s<<"//printing our permutation omega -- need to compute permutations of stuff"<<endl;
    s<<"//for both c2 and c3. also need permutation for c1"<<endl;
    s<<"omega;"<<endl;
    s<<"print \"delimiter\";"<<endl;

    s<<"//dimTenSpace := VectorSpace(F, 10);"<<endl;
    s<<"//r := Random(dimTenSpace);"<<endl;
    s<<"//r;"<<endl;

    s<<"//print \"delimiter\";"<<endl;

    s<<"uMatrix := RandomMatrix(F, 1, N);"<<endl;
    s<<"uMatrix[1] := u;"<<endl;
    s<<"//printing information for c1"<<endl;
    s<<"Transpose(H*Transpose(uMatrix));"<<endl;
    s<<"print \"delimiter\";"<<endl;

    s<<"//information for c2 is just omega(u);"<<endl;
    s<<"u;"<<endl;
    s<<"print \"delimiter\";"<<endl;

    s<<"//information for c3 is just omega(u + s)"<<endl;
    s<<"directSum:=Random(dimensionNSpace);"<<endl;
    s<<"for i in [1..N] do"<<endl;
        s<<"res := u[i] + s[i];"<<endl;
        s<<"directSum[i] := F!res;"<<endl;
    s<<"end for;"<<endl;
    s<<"directSum;"<<endl;
    s<<"print \"delimiter\";"<<endl;
    s<<"H;"<<endl;
    s.close();

}

void sternIdentification::runSternScheme()
{
   system("nohup magma<createSternScheme.txt> sternOutput.txt");
}

void sternIdentification::readSternScheme()
{
    ifstream i;
    string next;
    vector<string> lines;
    ifstream myfile ("sternOutput.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, next))
            {
                lines.push_back(next);
            }
            myfile.close();
    }
    else
    {
        cout<<"failed to open stern output file"<<endl;
        return;
    }

    vector<string> setOmega;
    string setHUTranspose;
    string setU;
    string setDirectSumUandS;
    int count = 0;
    vector<string> nextCycle;
    vector<vector<int> > setH;
    string nextCycleElement;
    vector<int> nextHRow;
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i] == "delimiter")
        {
            count++;
            continue;
        }
        else if (lines[i].substr(0, 5) == "Magma")
	{
		continue;
	}
	else if (lines[i] == "Type ? for help.  Type <Ctrl>-D to quit.")
	{
		continue;
	}
	else if (lines[i].substr(0,5) == "Total")
	{
		continue;
	}
        else
        {
            for (int j = 0; j < lines[i].size(); j++)
            {
                //count 0 : setting our permutation omega
                if (count == 0)
                {
                    if ((lines[i][j] == '(') || (lines[i][j] == ' '))
                    {
                        continue;
                    }
                    else if (lines[i][j] == ',')
                    {
                        nextCycle.push_back(nextCycleElement);
                        nextCycleElement="";
                    }
                    else if (lines[i][j] == ')')
                    {
                        nextCycle.push_back(nextCycleElement);
                        omega.push_back(nextCycle);
                        nextCycleElement = "";
                        nextCycle.clear();
                    }
                    else
                    {
                        nextCycleElement+=lines[i][j];
                    }

                }
                //count 1 : setting the row vector H*Transpose(u)
                else if (count == 1)
                {
                    if ((lines[i][j] == '[') || (lines[i][j] == ' ') || (lines[i][j] == ']'))
                    {
                        continue;
                    }
                    else
                    {
                        setHUTranspose += lines[i][j];
                    }
                }
                //count 2 : setting the row vector u
                else if (count == 2)
                {
                    if ((lines[i][j] == '(') || (lines[i][j] == ' ') || (lines[i][j] == ')'))
                    {
                        continue;
                    }
                    else
                    {
                        setU += lines[i][j];
                    }
                }
                //count 3 : setting the direct sum
                else if (count == 3)
                {
                    if ((lines[i][j] == '(') || (lines[i][j] == ' ') || (lines[i][j] == ')'))
                    {
                        continue;
                    }
                    else
                    {
                        setDirectSumUandS += lines[i][j];
                    }
                }
		 //count 4 : setting the H matrix
		else if (count == 4)
		{
		
		     if ((lines[i][j] == '[') || (lines[i][j] == ' '))
		     {
			 continue;
		     }
		     else if (lines[i][j] == ']')
		     {
			 setH.push_back(nextHRow);
			 nextHRow.clear();
		     }
		     else
		     {
	             	 nextHRow.push_back((int)lines[i][j] - 48);
		     }
		}
            }
        }
    }

    //altering omega to agree with cpp indices
    int indexIJint;
    for (int i = 0; i < omega.size(); i++)
    {
	for (int j = 0; j < omega[i].size(); j++)
	{
	   indexIJint = stoi(omega[i][j]);
	   indexIJint--;
	   omega[i][j] = to_string(indexIJint);
	}
    }
    
    HuTranspose = setHUTranspose;
    directSumUandS = setDirectSumUandS;
    u = setU;


}
	     
vector<string> sternIdentification::calculateCs()
{
   string combineOmega="";
   for (int i = 0; i < omega.size(); i++)
   {
	   for (int j = 0; j < omega[i].size(); j++)
	   {
		   combineOmega+=omega[i][j];
	   }
   }
   string c1 = sha256(combineOmega + HuTranspose);
   string tempU = u;
   runPermutation(omega, tempU);
   string c2 = sha256(tempU);
   string tempDirectSum = directSumUandS;
   string c3 = sha256(tempDirectSum);
   vector<string> ans;
   ans.push_back(c1);
   ans.push_back(c2);
   ans.push_back(c3);
   return ans;
}

int sternIdentification::generateResponse()
{
    return rand() & 3;
}
		     
string sternIdentification::getU()
{
    return u;
}

string sternIdentification::getS()
{
    return s;
}	

string sternIdentification::getY()
{
    return y;
}
		     
string sternIdentification::getHuTranspose()
{
    return HuTranspose;
}
		     
string sternIdentification::getDirectSumUandS()
{
    return directSumUandS;
}

vector<vector<string> > sternIdentification::getOmega()
{
    return omega;
}
	
vector<vector<int> > sternIdentification::getH()
{ 
    return H;
}

string binaryMatrixMultiplication(vector<vector<int> > matrix, vector<vector<int> > messageTranspose)
{
	string res = "";
	int temp = 0;
	for (int i = 0; i < matrix.size(); i ++)
	{
	  for (int j = 0; j < messageTranspose.size(); j++)
	  {
	    temp += matrix[i][j] * messageTranspose[j][0];
	  }
	  temp = temp % 2;
	  res+= to_string(temp);
	}

	return res;
}

vector<vector<int> > generateTranspose(string message)
{
	vector<vector<int> > res;
	vector<int> next;
	string temp;
	for (int i = 0 ; i < message.size(); i++)
	{
		temp = message[i];
		next.push_back(stoi(temp));
		res.push_back(next);
		next.clear();
	}
	return res;
}

string binarySubtraction(string v1, string v2)
{
	string res;
	for (int i = 0; i < v1.size(); i++)
	{
    string t1(1, v1[i]);
    string t2(1, v2[i]);
		res += to_string((stoi(t1) + stoi(t2))%2);
	}
	return res;
}
		
