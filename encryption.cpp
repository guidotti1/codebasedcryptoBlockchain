#include"encryption.h"

encryption::encryption()
{
	publickey defaultPublic;
	privatekey defaultPrivate;
	ourPublic = defaultPublic;
	ourPrivate = defaultPrivate;
	message="";
	q="";
	N="";
	K="";
	n="";
	k="";
	t1="";
	t2="";
}

encryption::encryption(string setq, string setN, string setK, string setn, string setk, string sett1, string sett2)
{
	publickey defaultPublic;
	privatekey defaultPrivate;
	ourPublic = defaultPublic;
	ourPrivate = defaultPrivate;
	message="";
	q=setq;
	N=setN;
	K=setK;
	n=setn;
	k=setk;
	t1=sett1;
	t2=sett2;
}


void encryption::createPublicPrivateKey()
{
//KKS digital signatures-  ATTEMPT TWO
//seems to work roughly 60% of the time

	string fileName = "createPublicPrivateKey.txt";
	ofstream output;
	output.open(fileName.c_str());

	output<<"q:="+q+";"<<endl;
	output<<"F:=GF(q);"<<endl;

	output<<"N:="+N+";"<<endl;
	output<<"K:="+K+";"<<endl;
	output<<"n:="+n+";"<<endl;
	output<<"k:="+k+";"<<endl;

	output<<"t1:="+t1+";"<<endl;
	output<<"t2:="+t2+";"<<endl;

	output<<"//counter:=0;"<<endl;
	output<<"//for l in [1..1000] do"<<endl;
	output<<"H:=RandomMatrix(F, N-K, N);"<<endl;


	output<<"firstNIntegers:=[];"<<endl;
	output<<"for i in [1..N] do"<<endl;
	output<<"    Append(~firstNIntegers, i);"<<endl;
	output<<"end for;"<<endl;

	output<<"//making J-Random subset of {1..N}"<<endl;
	output<<"//having cardinality n"<<endl;
	output<<"J:=[];"<<endl;
	output<<"for i in [1..n] do"<<endl;
	output<<"    RandomIndex:=Random(1, #firstNIntegers);"<<endl;
	output<<"    Append(~J, firstNIntegers[RandomIndex]);"<<endl;
	output<<"    Remove(~firstNIntegers, RandomIndex);"<<endl;
	output<<"end for;"<<endl;
	output<<"J:=Sort(J);"<<endl;

	output<<"G:=RandomMatrix(F, k, n);"<<endl;
	output<<"CHidden:=LinearCode(G);"<<endl;


	output<<"HTranspose:=Transpose(H);"<<endl;
	output<<"SubmatrixNumberRows := NumberOfRows(H);"<<endl;
	output<<"SubmatrixNumberCols := #J;"<<endl;
	output<<"SubmatrixHJ:=RandomMatrix(F, SubmatrixNumberCols, SubmatrixNumberRows);"<<endl;


	output<<"for i in [1..#J] do"<<endl;
	output<<"    SubmatrixHJ[i] := HTranspose[J[i]];"<<endl;
	output<<"end for;"<<endl;


	output<<"SubmatrixHJ:=Transpose(SubmatrixHJ);"<<endl;


	output<<"GTranspose:=Transpose(G);"<<endl;
	output<<"FMatrix:=SubmatrixHJ*GTranspose;"<<endl;

	output<<"PrivateKey:=<J, G>;"<<endl;
	output<<"PublicKey:=<FMatrix, H>;"<<endl;

	//printing public key, then private key
	output<<"PublicKey[1];"<<endl;
	output<<"print \"delimiter\";"<<endl;
	output<<"PublicKey[2];"<<endl;
	output<<"print \"delimiter\";"<<endl;

	output<<"PrivateKey[1];"<<endl;
	output<<"print \"delimiter\";"<<endl;
	output<<"PrivateKey[2];"<<endl;

	/*
	output<<"//end for;"<<endl;
	output<<"//print\"number successes\";"<<endl;
	output<<"//counter;"<<endl;
	*/
	output.close();
}


void encryption::runMagmaFile(string pass)
{
	if (pass == "1")
	{
		system("nohup magma<createPublicPrivateKey.txt> output.txt");
	}
	else if (pass == "2")
	{
		system("nohup magma<signMessage.txt> signMessageOutput.txt");
	}
	else if (pass== "3")
	{
		system("nohup magma<verifyMessage.txt> verifyMessageOutput.txt");
	}
}
        
        
void encryption::readPublicPrivateKey()
{
	string next;
	vector<string> lines;
	ifstream myfile ("output.txt");
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
		cout<<"failed to open output.txt file"<<endl;
		return;
	}

	vector<vector<int> > setF;
	vector<vector<int> > setH;
	vector<int>  setJ;
	vector<vector<int> > setG;

	//count : 0 signifies setting F
	//1 : setting H
	//2 : setting J
	//3 : setting G
	int count=0;
	vector<int> temp;
	for (int i = 0; i <  lines.size(); i++)
	{
		//cout<<"parsing the line " << lines[i]<<endl;
		if (lines[i] == "delimiter")
		{
			//cout<<"reading next"<<endl;
			count++;
			//cout<<"count "<<count<<endl;
			continue;
		}
		if (lines[i].substr(0, 5) == "Magma")
		{
			//cout<<"passing first line"<<endl;
			continue;
		}
		if (lines[i] == "Type ? for help.  Type <Ctrl>-D to quit.")
		{
			//cout<<"passing second line"<<endl;
			continue;
		}
		if (lines[i].substr(0,5) == "Total")
		{
			//cout<<"last line"<<endl;
			continue;
		}
		else 
		{
			string nextIntString="";
			for (int j =  0;  j < lines[i].size(); j++)
			{
				if (count==0)
				{
					if ((lines[i][j] == '[') || (lines[i][j]==' '))
					{
						continue;
					}
					else if (lines[i][j] == ']')
					{
						setF.push_back(temp);
						temp.clear();
					}
					else
					{
						//cout<<"the character "<<lines[i][j];
						//cout<<" converts to the integer  "<<(int)lines[i][j]<<endl;
						temp.push_back((int)lines[i][j] -  48);
					}
				}
				else if (count==1)
				{
					if ((lines[i][j] == '[') || (lines[i][j]==' '))
					{
						continue;
					}
					else if (lines[i][j] == ']')
					{
						setH.push_back(temp);
						temp.clear();
					}
					else
					{
						temp.push_back((int)lines[i][j] - 48);
					}
				}
				else if (count==2)
				{

					if ((lines[i][j] == '[') || (lines[i][j]==' '))
					{
						continue;
					}
					else if ((lines[i][j]  == ',') || (lines[i][j]==']'))
					{
						setJ.push_back(stoi(nextIntString));
						nextIntString="";
					}
					else
					{
						nextIntString+=lines[i][j];
					}

				}
				else if (count==3)
				{
					if ((lines[i][j] == '[') || (lines[i][j]==' '))
					{
						continue;
					}
					else if (lines[i][j] == ']')
					{
						setG.push_back(temp);
						temp.clear();
					}
					else
					{
						temp.push_back((int)lines[i][j] - 48);
					}
				}
			}
		}
}

/*
cout<<"let's go through set F matrix"<<endl;
for (int i =  0;  i <setF.size(); i++)
{
	for (int j  =  0; j < setF[i].size(); j++)
	{
		cout<<setF[i][j]<<" ";
	}
	cout<<endl<<endl<<endl;
}
cout<<"let's go through set H matrix"<<endl;
for (int i =  0;  i <setH.size(); i++)
{
	for (int j  =  0; j < setH[i].size(); j++)
	{
		cout<<setH[i][j]<<" ";
	}
	cout<<endl<<endl<<endl;
}
cout<<"let's go through set J vector "<<endl;
for (int i = 0; i < setJ.size(); i++)
{
	cout<<setJ[i]<<" ";
}
cout<<endl;
cout<<"let's go through set G matrix"<<endl;
for (int i =  0;  i <setG.size(); i++)
{
	for (int j  =  0; j < setG[i].size(); j++)
	{
		cout<<setG[i][j]<<" ";
	}
	cout<<endl<<endl<<endl;
}
*/

setKeys(setG, setH, setF, setJ);
}

void encryption::signMessage()
{
	vector<vector<int> > usedG = ourPrivate.getG();
	vector<int> usedJ = ourPrivate.getJ();
	int GNumRows = usedG.size();
	int GNumColumns = usedG[0].size();
	ofstream output;
	string filename = "signMessage.txt";
	output.open(filename.c_str());
	output<<"q := "+q+";"<<endl;
	output<<"F := GF(q);"<<endl;
	output<<"G := RandomMatrix(F, "+to_string(GNumRows)+", "+to_string(GNumColumns)+");"<<endl;
	output<<"V := VectorSpace(F, "+to_string(GNumColumns)+");"<<endl;
	string nextRow="";
	for (int i = 0; i < GNumRows; i++)
	{
		nextRow+='[';
		for (int j = 0;  j < GNumColumns; j++)
		{
			nextRow+= to_string(usedG[i][j]);
			if (j < GNumColumns-1)
			{
				nextRow+= ',';
				nextRow+= ' ';
			}
		}
		nextRow+= ']';
		output<<"G["+to_string(i+1)+"] := V!"+nextRow+";"<<endl;
		nextRow="";
	}
	output<<"J:=[];"<<endl;
	for (int i = 0; i  < usedJ.size(); i++)
	{
		output<<"J["+to_string(i+1)+"] := "+to_string(usedJ[i])+";"<<endl;
	}
	output<<"messageSpace:=VectorSpace(F, "+k+");"<<endl;
	string ourMessage="";
	ourMessage+= "[";
	for (int i = 0; i < message.size(); i++)
	{
		ourMessage+= message[i];
		if (i < message.size()-1)
		{
			ourMessage+= ',';
			ourMessage+= ' ';
		}
	}
	ourMessage+=']';
	output<<"x := messageSpace!"+ourMessage+";"<<endl;
	output<<"xG := x*G;"<<endl;

	output<<"omegaSpace:=VectorSpace(F, "+N+");"<<endl;
	output<<"omega:=Random(omegaSpace);"<<endl;
	output<<"jCounter := 1;"<<endl;
	output<<"for i in [1..+"+N+"] do"<<endl;
	output<<"    if (jCounter eq (#J+1)) then    "<<endl;
	output<<"        break;   "<<endl;
	output<<"    end if;"<<endl;
	output<<"    if (J[jCounter] eq i) then"<<endl;
	output<<"        omega[i]:= xG[jCounter];"<<endl;
	output<<"        jCounter:=jCounter+1;"<<endl;
	output<<"    else"<<endl;
	output<<"        omega[i]:=F!0;"<<endl;
	output<<"    end if;"<<endl;
	output<<"end for; "<<endl;
	output<<"omega;"<<endl;
	output.close();

}

void encryption::readSignature()
{
	string next;
	vector<string> lines;
	ifstream myfile ("signMessageOutput.txt");
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
		cout<<"failed to open signMessageOutput.txt file"<<endl;
		return;
	}
	
	vector<int> setOmega;
	for (int i = 0; i <  lines.size(); i++)
	{
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
		for (int j = 0; j < lines[i].size(); j++)
		{	
			if ((lines[i][j] == '(') || (lines[i][j]==' '))
			{
				continue;
			}
			else if (lines[i][j] == ')')
			{
				break;
			}
			else
			{
				setOmega.push_back((int)lines[i][j] - 48);
			}
		}
	}
	
	cout << "let us run through setOmega"<<endl;
	for (int i = 0; i < setOmega.size(); i++)
	{
		cout<<setOmega[i]<<" ";
	}
	cout<<endl;
	
}


void encryption::setKeys(vector<vector<int> > G, vector<vector<int> > H, vector<vector<int> > F, vector<int> J)
{
	ourPrivate.setJVector(J);
	ourPrivate.setGMatrix(G);
	ourPublic.setFMatrix(F);
	ourPublic.setHMatrix(H);
}

void encryption::setMessage(string ourMessage)
{
	message=ourMessage;
}

void encryption::setOmega(string ourOmega)
{
	omega=ourOmega;
}


void encryption::verifySignature()
{

	vector<vector<int> > usedH = ourPublic.getH();
	int HNumRows = usedH.size();
	int HNumColumns = usedH[1].size();
	string filename = "verifyMessage.txt";
	ofstream output;
	output.open(filename.c_str());
	output<<"q:="+q+";"<<endl;
	output<<"F:=GF(q);"<<endl;
	output<<"H:=RandomMatrix(F, "+to_string(HNumRows)+", "+to_string(HNumColumns)+");"<<endl;
	output<<"for i in [1.."+to_string(HNumRows)+"] do"<<endl;
	output<<"	for j in [1.."+to_string(HNumColumns)+"] do "<<endl;
	output<<"	end for;"<<endl;
	output<<"end for;"<<endl;
	output<<"omegaMatrix:=RandomMatrix(F, 1, "+N+");"<<endl;
	output<<"omegaMatrix[1]:=omega;"<<endl;
	output<<"xMatrix:=RandomMatrix(F, 1, "+k+");"<<endl;
	output<<"xMatrix[1]:=x;"<<endl;
	output<<"HomegaT := H*Transpose(omegaMatrix);"<<endl;
	output<<"FxT := FMatrix*Transpose(xMatrix);"<<endl;
	output<<"verifiedOne:=true;"<<endl;
	output<<"if (HomegaT eq FxT) then"<<endl;
	output<<"    verifiedOne:=true;"<<endl;
	output<<"else "<<endl;
	output<<"    verifiedOne:=false; "<<endl;
	output<<"    //print \"one fails\";"<<endl;
	output<<"end if;"<<endl;
	output<<"verifiedTwo:=true;"<<endl;
	output<<"if (Weight(omega) lt 520) then"<<endl;
	output<<"    if (Weight(omega) gt 480) then"<<endl;
	output<<"        verifiedTwo:=true;    "<<endl;
	output<<"    else"<<endl;
	output<<"        verifiedTwo:=false;"<<endl;
	output<<"        //print\"two fails\";"<<endl;
	output<<"    end if;"<<endl;
	output<<"end if;"<<endl;
	output<<"if ((verifiedOne eq true) and (verifiedTwo eq true)) then"<<endl;
	output<<"    print \"verification was succesful\";"<<endl;
	 output<<"   //counter:=counter+1;"<<endl;
	output<<"else"<<endl;
	output<<"    print \"verification was a failure\";"<<endl;

	output<<"end if;"<<endl;
	output.close();

}


