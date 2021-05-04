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

transaction::transaction(publickey setfrom, privatekey setto, int setAmount)
{
	fromkeyKKS = setfrom;
	tokeyKKS = setto;
	vector<vector<int> > fromkeyF = fromkeyKKS.getF();
	vector<vector<int> > fromkeyH = fromkeyKKS.getH();
	vector<vector<int> > tokeyF = tokeyKKS.getF();
	vector<vector<int> > tokeyH = tokeyKKS.getH();
	//storing all the fromkey information in a string so we can sha256() hash it
	for (int i = 0; i < fromkeyF.size(); i++)
	{
		for (int j = 0; j < fromkeyF[i].size(); j++)
		{
			from += to_string(fromkeyF[i][j]);
		}
	}
	for (int i = 0; i < fromkeyH.size(); i++)
	{
		for (int j = 0; j < fromkeyH[i].size(); j++)
		{
			from += fromkeyH(fromKeyS[i][j]);
		}
	}
	//same for the tokey information
	for (int i = 0; i < tokeyF.size(); i++)
	{
		for (int j = 0; j < tokeyF[i].size(); j++)
		{
			to += to_string(tokeyF[i][j]);
		}
	}
	for (int i = 0; i < tokeyH.size(); i++)
	{
		for (int j = 0; j < tokeyH[i].size(); j++)
		{
			to += to_string(tokeyH[i][j]);
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

transaction::transaction(string setfrom, publickey setto, int setAmount)
{
	from=setfrom;
	tokeyKKS = setto;
	amount=setAmount;
	vector<vector<int> > tokeyF = tokeyKKS.getF();
	vector<vector<int> > tokeyH = tokeyKKS.getH();
	for (int i = 0; i < tokeyF.size(); i++)
	{
		for (int j = 0; j < tokeyF[i].size(); j++)
		{
			to += to_string(tokeyF[i][j]);
		}
	}
	for (int i = 0; i < tokeyH.size(); i++)
	{
		for (int j = 0; j < tokeyH[i].size(); j++)
		{
			to += to_string(tokeyH[i][j]);
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

publickey transaction::getfromkeyKKS()
{
	return fromkeyKKS;
}

privatekey transaction::gettokeyKKS()
{
	return tokeyKKS;
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

void transaction::signTransaction1(publickey usedPublic, privatekey usedPrivate)
{
	vector<vector<int> > usedf = usedPublic.getF();
	vector<vector<int> > usedh = usedPublic.getH();
	vector<int> usedj = usedPrivate.getJ();
	vector<vector<int> > usedg = usedPrivate.getG();
	string compare="";
	for (int i = 0; i < usedf.size(); i++)
	{
		for (int j = 0; j < usedf[i].size(); j++)
		{
			compare+=to_string(usedf[i][j]);
		}
	}
	for (int i = 0; i < usedh.size(); i++)
	{
		for (int j = 0; j < usedh[i].size(); j++)
		{
			compare+=to_string(usedh[i][j]);
		}
	}
	
	if (compare != from)
	{
		cout<<"you can't sign a transaction from other wallets"<<endl;
	}
	
	encryption temp("2", "2000", "1100", "1000", "256", "440", "560");
	temp.setKeys(usedg, usedh, usedf, usedj);
	calculateHash();  
	
	cout<<"this will be our message for the new cb system (hash of transaction) " << hash<<endl;
	temp.setMessage(hash);
	int microsecond = 1000;
	//sign message program
	temp.signMessage();
	//run sign message program
	temp.runMagmaFile("2");
	usleep(3 * microsecond); //waits 3 seconds 
	//read signature
	temp.readSignature();	
	KKSOmega = temp.getMessage();
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

bool transaction::isTransactionValid1()
{
	//if from = "NULL" 
	if (from == "NULL")
	{
		return true;
	}
	
	encryption temp("2", "2000", "1100", "1000", "256", "440", "560");
	temp.setPublicKey(fromkey);
	vector<vector<int> > usedf = fromkeyKKS.getFMatrix();
	vector<vector<int> > usedh = fromkeyKKS.getHMatrix();
	temp.setOmega(KKSOmega);
	temp.setMessage(hash);
	//verifying the signature omega for the given message hash
	trial.verifySignature();
	int microsecond = 1000;
	usleep(3 * microsecond);
	//running verify signature program
	trial.runMagmaFile("3");
	bool verificationControl = trial.readVerification();
	if (verificationControl)
	{
		cout<<"KKS signature on the transaction is valid"<<endl;
		return true;
	}
	else 
	{
		cout<<"KKS signature on the transaction is invalid"<<endl;
		return false;
	}
}

bool transaction::isTransactionValid2()
{
	if (from == "NULL")
	{
		return true;
	}
	
	newCBSignature temp(16381, 400, 100, 218, 156, 141, 151, 3420, 3375);
	temp.setPublicKey(fromkey);
	vector<vector<int> > usedh = fromkey.getHMatrix();
	vector<vector<int> > useds = fromkey.getSMatrix();
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
