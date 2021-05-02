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
	vector<vector<int> > usedH = fromkey.getHMatrix();
	vector<vector<int> > usedS = fromkey.getSMatrix();
	vector<vector<int> > usedE = tokey.getEMatrix();
	for (int i = 0; i < usedH.size(); i++)
	{
		for (int j = 0; j < usedH[i].size(); j++)
		{
			from += to_string(usedH[i][j]);
		}
	}
	for (int i = 0; i < usedS.size(); i++)
	{
		for (int j = 0; j < usedS[i].size(); j++)
		{
			from += to_string(usedS[i][j]);
		}
	}
	for (int i = 0; i < usedE.size(); i++)
	{
		for (int j = 0; j < usedE[i].size(); j++)
		{
			from += to_string(usedE[i][j]);
		}
	}
	amount=setAmount;
	hash="";
	calculateHash();
}
	
transaction::transaction (string setFrom, string setTo, int setAmount)
{
	from=setFrom;
	to=setTo;
	amount=setAmount;
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
	setKKSSig();
	calculateHash();
}

void transaction::signTransaction2(newCBPublic usedPublic, newCBPrivate usedPrivate)
{
	vector<vector<int> > usedh = usedPublic.getHMatrix();
	vector<vector<int> > useds = usedPublic.getSMatrix();
	
	string compare="";
	string temp="";
	for (int i = 0; i < usedh.size(); i++)
	{
		for (int j = 0; j < usedh[i].size(); j++)
		{
			temp+=to_string(usedh[i][j]);
		}
	}
	for (int i = 0; i < useds.size(); i++)
	{
		for (int j = 0; j < useds[i].size(); j++)
		{
			temp+=to_string(useds[i][j]);
		}
	}
	compare = sha256(temp);
	
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
