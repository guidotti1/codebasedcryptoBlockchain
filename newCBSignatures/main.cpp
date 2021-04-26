#include<iostream>
#include  "newCBSignature.h"

using namespace std;

//test program for new CB signature algorithm;
int main()
{

	srand(time(NULL));

	//parameters in order ::  q, n, r, b, t_e, w_e, w_c, gammaBar, gamma
	//newCBSignature ourSignature(16381, 400, 100, 218, 156, 141, 151, 8189, 8190); //parameters that work
	newCBSignature ourSignature(16381, 400, 100, 218, 156, 141, 151, 3420, 3375);
	

	cout<<"generating public and private keys"<<endl;
	ourSignature.generatePublicPrivateKey();
	string message="";
	for (int i=0; i<20; i++)
	{
		message+=to_string(rand() % 10);
	}
	cout<<"sending message to be signed :"<<message<<endl;
	ourSignature.setMessage(message);
	ourSignature.generateSignature();
	cout<<"verifying that signature"<<endl;
	ourSignature.verifySignature();
	return 0;
}
