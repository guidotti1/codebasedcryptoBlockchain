#include "hashingtest.h"


string hashingtest::getHashGF3()
{
	string toBeHashed  = message+ssuby;
	string randomHash = sha256(toBeHashed);
	string res = "";
	int i = 0;
	do {
   		do
        	{
            	res = "";
            	//cout << "we are hasing " << toBeHashed << endl;
            	convertHashToTernary(randomHash, res);
            	//cout <<  res.size()<<endl;
            	toBeHashed += to_string(i);
            	randomHash = sha256(toBeHashed);
            	i++;
        	}
    	while (res.size() != b);
    	//cout << "res.size(): "<< res.size() << " calculateWeight(res): " << calculateWeight(res)<<endl;
	}
	while (calculateWeight(res) != wsubC);
	return res;

}

vector<int> hashingtest::getHashGFq(string res)
{
	//string gfqRes = "";
	vector<int> gfqRes;
	int negativeoneGFq = q-1;
	
	for (int i = 0; i < res.size(); i++)
	{
    	if (res[i] == '2')
    	{
        	//gfqRes += to_string(negativeoneGFq);
        	gfqRes.push_back(negativeoneGFq);
    	}
   		else if (res[i] == '1')
    	{
        	//gfqRes += '1';
        	gfqRes.push_back(1);
    	}
   		else if (res[i] == '0')
    	{
     	   //gfqRes += '0';
     	   gfqRes.push_back(0);
    	}
	}
	return gfqRes;
}


hashingtest::hashingtest()
{
	q=0;
	n=0;
	b=0;
	wsubC=0;
	message="";
}

hashingtest::hashingtest(int setq, int setn, int setb, int setwsubC, string setmessage, string setssuby)
{
	q=setq;
	n=setn;
	b=setb;
	wsubC=setwsubC;	
	message=setmessage;
	ssuby=setssuby;
}

void hashingtest::convertHashToTernary(string hash, string & res)
{
    int nextAscii;
    for (int i = 0; i < hash.size(); i++)
    {
        nextAscii = (int) hash[i];
        if ((nextAscii >= 48) && (nextAscii <= 57))
        {
            //dealing with a number
            nextAscii -= 48;
            if (nextAscii != 0)
            {
                convertToTernary(nextAscii, res);
            }
            else
            {
                res+="0";
            }
        }
        else if ((nextAscii >= 97) && (nextAscii <= 122))
        {
            //dealing with a character
            convertToTernary(nextAscii, res);
        }

    }
}


void hashingtest::convertToTernary(int N, string & res)
{
    if (N == 0)
        return;

    int x = N % 3;
    N /= 3;
    if (x < 0)
        N += 1;

    convertToTernary(N, res);

    if (x < 0)
    {
        res += to_string(x + (3 * -1));
    }
    else
    {
       res += to_string(x);
    }
}

string hashingtest::convertHashToBinary(string hash)
{
	string ans="";
	for (size_t i = 0; i < hash.size(); ++i)
	{
		bitset<8> b(hash.c_str()[i]);
    		ans+= b.to_string();
	}
	return ans;
}

int hashingtest::calculateWeight(string ternaryString)
{
    int res = 0;
    for (int i = 0; i < ternaryString.size(); i++)
        {
        if (ternaryString[i] != '0')
            {
            res++;
            }
        }
    return res;
}
