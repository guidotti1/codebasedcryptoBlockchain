#include"transaction.h"

transaction::transaction()
{
	from="";
	to="";
	amount=0;
	hash="";
}

transaction::transaction(newCBPublic setfrom, newCBPublic setto, int setAmount)
{
	fromkey=setfrom;
	tokey=setto;
	vector<vector<int> > fromKeyH = fromkey.getHMatrix();
	vector<vector<int> > fromKeyS = fromkey.getSMatrix();
	vector<vector<int> > toKeyH = tokey.getHMatrix();
	vector<vector<int> > toKeyS = tokey.getSMatrix();
	//storing all the fromkey information in a string so we can sha256() hash it
	for (int i = 0; i < fromKeyH.size(); i++)
	{
		for (int j = 0; j < fromKeyH[i].size(); j++)
		{
			from += to_string(fromKeyH[i][j]);
		}
	}
	for (int i = 0; i < fromKeyS.size(); i++)
	{
		for (int j = 0; j < fromKeyS[i].size(); j++)
		{
			from += to_string(fromKeyS[i][j]);
		}
	}
	//same for the tokey information
	for (int i = 0; i < toKeyH.size(); i++)
	{
		for (int j = 0; j < toKeyH[i].size(); j++)
		{
			to += to_string(toKeyH[i][j]);
		}
	}
	for (int i = 0; i < toKeyS.size(); i++)
	{
		for (int j = 0; j < toKeyS[i].size(); j++)
		{
			to += to_string(toKeyS[i][j]);
		}
	}
	amount=setAmount;
	hash="";
	calculateHash();
}
	
transaction::transaction(string setFrom, string setTo, int setAmount)
{
	from=setFrom;
	to=setTo;
	amount=setAmount;
	hash="";
	calculateHash();
}

transaction::transaction(string setfrom, newCBPublic setto, int setAmount)
{
	from=setfrom;
	tokey = setto;
	amount=setAmount;
	vector<vector<int> > toKeyH = tokey.getHMatrix();
	vector<vector<int> > toKeyS = tokey.getSMatrix();
	//storing all the tokey information in a string so we can sha256() hash it
	for (int i = 0; i < toKeyH.size(); i++)
	{
		for (int j = 0; j < toKeyH[i].size(); j++)
		{
			from += to_string(toKeyH[i][j]);
		}
	}
	for (int i = 0; i < toKeyS.size(); i++)
	{
		for (int j = 0; j < toKeyS[i].size(); j++)
		{
			from += to_string(toKeyS[i][j]);
		}
	}
	hash="";
	calculateHash();
}
/*
void::transaction setKKSSig()
{
	string setq="2";
	string setN="2000";
	string setK="1100";
	string setn="1000";
	string setk="256";
	string sett1="440";
	string sett2="560";
	encryption temp(setq, setN, setK, setn, setk, sett1, sett2);
	KKSsig = temp;
}
*/

string transaction::getFrom()
{
	return from;
}

string transaction::getTo()
{
	return to;
}

int transaction::getAmount()
{
	return amount;
}

newCBPublic transaction::getfromkey()
{
	return fromkey;
}

newCBPublic transaction::gettokey()
{
	return tokey;
}

void transaction::setFrom(string s)
{
	from=s;
}

void transaction::setTo(string t)
{
	to=t;
}

void transaction::setAmount(int a)
{
	amount=a;
}

void transaction::setfromkey(newCBPublic setfrom)
{
	fromkey = setfrom;
}

void transaction::settokey(newCBPublic setto)
{
	tokey = setto;
}

void transaction::calculateHash()
{
	hash = sha256(from + to + to_string(amount));
}

void transaction::signTransaction1()
{
	//setKKSSig();
}

void transaction::signTransaction2(newCBPublic usedPublic, newCBPrivate usedPrivate)
{
	vector<vector<int> > usedh = usedPublic.getHMatrix();
	vector<vector<int> > useds = usedPublic.getSMatrix();
	
	string compare="";
	for (int i = 0; i < usedh.size(); i++)
	{
		for (int j = 0; j < usedh[i].size(); j++)
		{
			compare+=to_string(usedh[i][j]);
		}
	}
	for (int i = 0; i < useds.size(); i++)
	{
		for (int j = 0; j < useds[i].size(); j++)
		{
			compare+=to_string(useds[i][j]);
		}
	}
	
	if (compare != from)
	{
		cout<<"you can't sign a transaction from other wallets"<<endl;
	}
	//parameters in order ::  q, n, r, b, t_e, w_e, w_c, gammaBar, gamma
	newCBSignature temp(16381, 400, 100, 218, 156, 141, 151, 3420, 3375);
	temp.setPublicKey(usedPublic);
	temp.setPrivateKey(usedPrivate);
	calculateHash();
	
	cout<<"this will be our message for the new cb system (hash of transaction) " << hash<<endl;
	temp.setMessage(hash);
	cout <<"generating signature for that message"<<endl;
	temp.generateSignature();
	
	usedsig =  temp.getOurSig();
}

bool transaction::isTransactionValid2()
{
	if (from == "NULL")
	{
		return true;
	}
	
	newCBSignature temp(16381, 400, 100, 218, 156, 141, 151, 3420, 3375);
	temp.setPublicKey(fromkey);

	vector<vector<int> > usedz = usedsig.getz();
	vector<vector<int> > usedc = usedsig.getc();
	temp.setZ(usedz);
	temp.setC(usedc);
	temp.setOurSig();
	temp.setMessage(hash);
	string res = temp.verifySignature();
	cout<<"9"<<endl;
	if (res=="passes")
	{
		cout<<"signature on the transaction is valid"<<endl;
		return true;
	}
	else if (res=="fails")
	{
		cout<<"signature on the transaction is invalid"<<endl;
		return false;
	}
}
