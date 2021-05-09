#include "stern.h"
void stern::generatePublicPrivateKey()
{
  H = ops.generateRandomMatrix(2, N-K, N);

  vector<int> firstNIntegers;
  for (int i = 1; i <= N; i++)
  {
    firstNIntegers.push_back(i);
  }

  vector<int> oneIndices;
  int randomIndex;
  bool control=true;
  do 
  {
    control=true;
    randomIndex = rand() % firstNIntegers.size();
    for (int i =0; i < oneIndices.size(); i++)
    {
      if (randomIndex == oneIndices[i])
      {
        control=false;
      }
    }
     if (control)
     {
      oneIndices.push_back(randomIndex);
     }

  } while(oneIndices.size() != T);

  s = ops.generateRandomVector(2, N);
  int oneIndicesCounter=0;
  int rest = N;
  sort(oneIndices.begin(), oneIndices.end());
  for (int i = 0; i < N; i++)
  { 
    if (oneIndicesCounter == T) 
    {
      rest = i;
      break;
    }
    if (oneIndices[oneIndicesCounter] == i) 
    {
      s[i] = 1;
      oneIndicesCounter++;
    }
    else 
    {
      s[i] = 0;
    }
  }

  for (int i = rest; i < N; i++)
  {
    s[i] = 0;
  }

  vector<vector<int> > sMatrix;
  sMatrix.push_back(s);
  y = ops.matrixMultiplication(2, H, ops.generateTranspose(sMatrix));
}

stern::stern(int setN, int setK, int setT, int setq, string setMessage)
{
  N = setN;
  K = setK;
  T = setT;
  q = setq;
  message = setMessage;
}

vector<vector<string> > stern::generatePermutation()
{
  vector<string> firstn;
  for (int i = 1; i <= N; i++)
  {
    firstn.push_back(to_string(i));
  }

  vector<string> permutation;
  vector<int> usedpos;
  int nextpos;
  bool control;
  do 
  {
    nextpos = rand() % firstn.size();
    control=true;
    for (int i = 0; i < usedpos.size(); i++)
    {
      if (usedpos[i] == nextpos)
      {
        control=false;
      }
    }
    if (control)
    {
      usedpos.push_back(nextpos);
    }

  }while (usedpos.size() != N);

  for (int i = 0; i < usedpos.size(); i++)
  {
    permutation.push_back(firstn[usedpos[i]]);
  }

  vector<vector<string> > cycleNotation;
  vector<string> nextCycle;
  vector<int> usedPermPos;
  string first;
  string temp;
  for (int i = 0; i < permutation.size(); i++)
  {
    control=true;
    for (int j = 0; j < usedPermPos.size(); j++)
    {
      if (usedPermPos[j] == i)
        {
          control=false;
        }
    }
    if (control)
    {
      first = to_string(i+1);
      temp =  permutation[i];
      usedPermPos.push_back(i);
      usedPermPos.push_back(stoi(temp)-1);
      nextCycle.push_back(first);
      if (first != temp)
      {
        nextCycle.push_back(temp);
      }
      while (temp != first)
      {
        temp = permutation[stoi(temp) - 1];
        usedPermPos.push_back(stoi(temp)-1);
        if (temp != first)
        {
          nextCycle.push_back(temp);
        }
      }
      if (nextCycle.size() > 1)
      {
        cycleNotation.push_back(nextCycle);
      }
       nextCycle.clear();
    }

  }
  
  return cycleNotation;
}

void stern::generateCommitments()
{
  u = ops.generateRandomVector(2, N);
  omega = generatePermutation();
  vector<vector<int> > uMatrix;
  uMatrix.push_back(u);

  //information for c1
  vector<vector<int> > HuTranspose = ops.matrixMultiplication(2, H, ops.generateTranspose(uMatrix));
  string omegaString;
  for (int i = 0; i < omega.size(); i++)
  {
    for (int j =0; j < omega[i].size(); j++)
    { 
      omegaString += omega[i][j];
    }
  }

  string HuTransposeString;
  for (int i =0; i<HuTranspose.size(); i++)
  {
    for (int j =0; j<HuTranspose[i].size(); j++)
    {
      HuTransposeString += to_string(HuTranspose[i][j]);
    }
  }
  c1 = sha256(omegaString + HuTransposeString);
  
  //information for c2
  for (int i =0; i < u.size(); i++)
  {
    c2 += to_string(u[i]);
  }
  runPermutation(c2);
  c2 = sha256(c2);

  //information for c3
  vector<vector<int> > sMatrix;
  sMatrix.push_back(s);
  c3="";
  vector<vector<int> > directSumUS = ops.matrixAddition(2, uMatrix, sMatrix);
  for (int i = 0; i < directSumUS.size(); i++)
  {
    for (int j = 0; j < directSumUS[i].size(); j++)
    {
      c3 += to_string(directSumUS[i][j]);
    }
  }
  runPermutation(c3);
  string temp = c3;
  c3 = sha256(temp);

}

void stern::runPermutation(string & change)
{
  vector<char> temp;
  for (int i = 0; i < omega.size(); i++)
  {
    for (int j = 0; j < omega[i].size(); j++)
    {
      temp.push_back(change[stoi(omega[i][j])-1]);                       
    }

    change[stoi(omega[i][0])-1] = temp[temp.size()-1];
    for (int j = 1; j < omega[i].size(); j++)
    {
      change[stoi(omega[i][j])-1] = temp[j-1]; 
    }
    temp.clear();
  }
  return;
}

int stern::generateChallenge()
{
  //combining commitments (c1, c2, c3) and message into one string
  string commitmentsAndMessage = c1 + c2 + c3 + message;

  string hashed = sha256(commitmentsAndMessage);
  string binaryHash = convertHashToBinary(hashed);
  int temp;
  string temps;
  for (int i =0; i < binaryHash.length(); i++)
  {
    temps=binaryHash[i];
    temp += stoi(temps);
  }
  return (temp % 3);
}

string stern::convertHashToBinary(string hash)
{
	string ans="";
	for (size_t i = 0; i < hash.size(); ++i)
	{
		bitset<8> b(hash.c_str()[i]);
    		ans+= b.to_string();
	}
	return ans;
}

void stern::generateResponse(vector<int> & sendu, vector<vector<string> > & sendomega, vector<vector<int> > & sendDirectSumUS, string & sendOmegaU, string & sendOmegaS, int challengeValue)
{
  if (challengeValue == 0)
  {
      sendu = u;
      sendomega = omega;
  }
  else if (challengeValue == 1)
  {
      vector<vector<int> > uMatrix;
      uMatrix.push_back(u);
      vector<vector<int> > sMatrix;
      sMatrix.push_back(s);
      sendDirectSumUS = ops.matrixAddition(2, uMatrix, sMatrix);
      sendomega = omega;
  }
  else if (challengeValue == 2)
  {
     string temps;
     string tempu;
     for (int i = 0; i < s.size(); i++)
     {
      temps+=to_string(s[i]);
     };
     for (int i = 0; i < u.size(); i++)
     {
       tempu+=to_string(u[i]);
       sendu.push_back(u[i]);
     }
    runPermutation(temps);
    runPermutation(tempu);
    sendOmegaS = temps;
    sendOmegaU = tempu;

  }
  generateSignature(sendu, sendomega, sendDirectSumUS, sendOmegaU, sendOmegaS);

}

void stern::generateSignature(vector<int> sendu, vector<vector<string> > sendomega, vector<vector<int> > senddirectSumUS, string sendOmegaU, string sendOmegaS)
{
  sternSig tempsig(c1, c2, c3, sendu, sendomega, senddirectSumUS, sendOmegaU, sendOmegaS);
  oursig = tempsig;
}

bool stern::verifySignature()
{
  string CsubH = oursig.getc1() + oursig.getc2() + oursig.getc3() + message;
  CsubH = sha256(CsubH);
  CsubH = convertHashToBinary(CsubH);
  int res;
  string temp;
  for (int i = 0; i < CsubH.length(); i++)
  {
    temp=CsubH[i];
    res += stoi(temp);
  }
  res = (res)%3;
  if (res == 0)
  {
    //then we have to verify if c1 and c2 are honestly computed
    string combinedOmega;
    vector<vector<string> > getomega = oursig.getsendomega();
    for (int i =0; i < getomega.size(); i++)
    {
      for (int j = 0; j < getomega[i].size(); j++)
      {
        combinedOmega += getomega[i][j];
      }
    }
    vector<vector<int> > uMatrix;
    uMatrix.push_back(u);
    vector<vector<int> > calculateHUTranpose = ops.matrixMultiplication(q, H, ops.generateTranspose(uMatrix));
    string HuTranposeString;
    for (int i =0; i < calculateHUTranpose.size(); i++)
    {
      for (int j = 0; j < calculateHUTranpose[i].size(); j++)
      {
        HuTranposeString += to_string(calculateHUTranpose[i][j]);
      }
    }
    string checkc1 = sha256(combinedOmega + HuTranposeString);

    vector<int> getu = oursig.getsendu();
    string getustring;
    for (int i =0; i < getu.size(); i++)
    {
      getustring+=to_string(getu[i]);
    }
    runPermutation(getustring);
    string checkc2 = sha256(getustring);

    return ((checkc1==oursig.getc1())&&(checkc2==oursig.getc2()));
  }
  else if(res == 1)
  {
    //then we have to verify if c1 and c3 are honestly computed
    string combinedOmega;
    vector<vector<string> > getomega = oursig.getsendomega();
    for (int i =0; i < getomega.size(); i++)
    {
      for (int j = 0; j < getomega[i].size(); j++)
      {
        combinedOmega += getomega[i][j];
      }
    }
    vector<vector<int> > uMatrix;
    uMatrix.push_back(u);
    vector<vector<int> > calculateHUTranpose = ops.matrixMultiplication(q, H, ops.generateTranspose(uMatrix));
    string HuTranposeString;
    for (int i =0; i < calculateHUTranpose.size(); i++)
    {
      for (int j = 0; j < calculateHUTranpose[i].size(); j++)
      {
        HuTranposeString += to_string(calculateHUTranpose[i][j]);
      }
    }
    string checkc1 = sha256(combinedOmega + HuTranposeString);

    vector<vector<int> > getDirectSum = oursig.getdirectSumUS();
    string directSumString;
    for (int i =0; i < getDirectSum.size(); i++)
    {
      for (int j = 0; j < getDirectSum[i].size(); j++)
      {
        directSumString += to_string(getDirectSum[i][j]);
      }
    }
    runPermutation(directSumString);
    string checkc3 = sha256(directSumString);
    return ((checkc1 == oursig.getc1()) && (checkc3 == oursig.getc3()));
  }
  else if (res == 2)
  {
    //then we have to verify if c2 and c3 are honestly computed and if weight(omega(s)) == t
    vector<int> getu = oursig.getsendu();
    string getustring;
    for (int i =0; i < getu.size(); i++)
    {
      getustring+=to_string(getu[i]);
    }
    runPermutation(getustring);
    string checkc2 = sha256(getustring);
  
    string getomegau = oursig.getsendOmegaU();
    string getomegas = oursig.getsendOmegaS();
    string checkc3;
    for (int i = 0; i < getomegas.size(); i++)
    {
      if (getomegau[i] == getomegas[i])
      {
        checkc3 += '0';
      }
      else
      {
        checkc3 += '1';
      }
    }
    string temp = checkc3;
    checkc3 = sha256(temp);

    int weightCheck=0;
    for (int i = 0; i <getomegas.size(); i++)
    {
      if (getomegas[i] == '1')
      {
        weightCheck++;
      }
    }
    return ((T == weightCheck) && (checkc3 == oursig.getc3()) && (checkc2 == oursig.getc2()));
  }
}

void stern::clearInformation()
{
  omega.clear();
  u.clear();
  c1="";
  c2="";
  c3="";
  sternSig emptysig;
  oursig=emptysig;
}

bool stern::runKTrials(int K)
{
  int challenge;
  //run the K trials
  for (int i=0; i < K; i++)
  {
    //needed for generate response (signature)
    vector<int> sendu;
    vector<vector<string> > sendomega;
    vector<vector<int> > sendDirectSumUS;
    string sendOmegaU;
    string sendOmegaS;
    generateCommitments();
    challenge = generateChallenge();
    generateResponse(sendu, sendomega, sendDirectSumUS, sendOmegaU, sendOmegaS, challenge);
    
    if (!verifySignature())
    {
      cout<<"on number "<<i<<" fails "<<endl;
      return false;
    }
    clearInformation();
  }
  return true;

}

vector<int> stern::getPrivateKey()
{
  return s;
}

vector<vector<int> > stern::getPublicKey()
{
  return y;
}

sternSig stern::getOurSig()
{
  return oursig;
}
     
void stern::setPrivateKey(vector<int> sets)
{
  s=sets;
}
  
void stern::setPublicKey(vector<vector<int> > sety)
{
  y=sety;
}
  
void stern::setOurSig(sternSig setsig)
{
  oursig=setsig;
}
