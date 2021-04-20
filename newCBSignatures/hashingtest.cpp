
#include "hashingtest.h"


/*
int q = 7;
int n = 400;
int b = 218;
int wsubC = 151;
//hashing our message together with s_{y}
//becomes c in the magma shit

auto begin = std::chrono::high_resolution_clock::now();


cout << "done"<<endl;
cout << "we get the resulting hash fulfilling those conditions :  " << res << endl;
cout << "with size : " << res.size() << endl;
cout << "and support size : " << calculateWeight(res) <<endl;
auto end = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
printf("Time measured to do all those calculation: %.3f seconds.\n", elapsed.count() * 1e-9);

cout<<"putting that shit in the proper magma format"<<endl;
//putting c(resulting hash) in magma format
getcTomagma(to_string(b), to_string(q), gfqRes);
*/


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

string hashingtest::getHashGFq(string res)
{
	string gfqRes = "";
	int negativeoneGFq = q-1;
	
	for (int i = 0; i < res.size(); i++)
	{
    	if (res[i] == '2')
    	{
        	gfqRes += to_string(negativeoneGFq);
    	}
   		else if (res[i] == '1')
    	{
        	gfqRes += '1';
    	}
   		else if (res[i] == '0')
    	{
     	   gfqRes += '0';
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


void hashingtest::getcTomagma(string gfqRes)
{
    ofstream o;
    o.open("gfqres.txt");
    o << "q := "+to_string(q)+";"<<endl;
    o << "F := GF(q);"<<endl;
    o << "b := "+to_string(b)+";"<<endl;
    o << "y := Random(VectorSpace(F, b));"<<endl;
    cout << "gfqres.size() : " << gfqRes.size() << endl;
    int counter = 0;
    for (int i = 0; i < gfqRes.size(); i++)
    {
        if (gfqRes[i] == '-')
        {

            o<<"y["+to_string(i+1-counter)+"] := F!-1;"<<endl;
            i++;
            counter++;
        }
        else
        {
            o<<"y["+to_string(i+1-counter)+"] := F!"+gfqRes[i]+";"<<endl;
        }

    }
    o << "y;"<<endl;

    o <<"for i in [1..b] do"<<endl;
    o <<"   printf (\"%o, \"), y[i];"<<endl;
    o <<"end for;"<<endl;
    o.close();

    system("nohup magma<gfqres.txt> gfqout.txt");

}

void hashingtest::convertHashToTernary(string hash, string & res)
{
    //cout << "Ternary number of our hash value "
     //    << hash << " is: ";

    int nextAscii;
    for (int i = 0; i < hash.size(); i++)
    {
        //cout<<"converting " << hash[i] << endl;
        //cout<<"represented by ascii " << (int) hash[i] << endl;
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
    //res+="\n";

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
        //cout<<x + (3 * -1);
        //outputFile<<x + (3 * -1);
    }
    else
    {
       res += to_string(x);
       //cout<<x;
       //outputFile<<x;
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
