#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<bits/stdc++.h>
using namespace std;


class sternIdentification
{
private :
    //private key
    string s;
    //public key
    string y;
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



return 0;
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
    string nextCycleElement;
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i] == "delimiter")
        {
            count++;
            continue;
        }
        if (lines[i].substr(0, 5) == "Magma")
		{
			continue;
		}
		if (lines[i] == "Type ? for help.  Type <Ctrl>-D to quit.")
		{
			continue;
		}
		if (lines[i].substr(0,5) == "Total")
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
                    if ((lines[i][j] == '[') || (lines[i][j] == ' '))
                    {
                        continue;
                    }
                    else if (lines[i][j] == ']')
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
                    if ((lines[i][j] == '(') || (lines[i][j] == ' '))
                    {
                        continue;
                    }
                    else if (lines[i][j] == ')')
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
                    if ((lines[i][j] == '(') || (lines[i][j] == ' '))
                    {
                        continue;
                    }
                    else if (lines[i][j] == ')')
                    {
                        continue;
                    }
                    else
                    {
                        setDirectSumUandS += lines[i][j];
                    }
                }
            }
        }
    }

    cout<<" setDirectSumUandS : "<<endl;
    cout << setDirectSumUandS << endl << endl << endl;
    cout<<" setU : "<<endl;
    cout << setU << endl << endl << endl;
    cout<<" setHUTranspose : " << endl;
    cout << setHUTranspose << endl << endl << endl;

    cout<<"lastly lets go through omega"<<endl;
    for (int i = 0; i < omega.size(); i++)
    {
        for (int j = 0; j < omega[i].size(); j++)
        {
            cout<<omega[i][j] << " ";
        }
    cout<<endl;
    }
    cout<<endl<<endl<<endl;


}

