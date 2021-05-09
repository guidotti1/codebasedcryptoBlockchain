#ifndef STERN_H_
#define STERN_H_

#include <algorithm> 
#include "matrixOperations.h"
#include "sha256.h"
#include "sternSig.h"
#include<bits/stdc++.h>

class stern
{

  public :

    //default and five argument constructor
    stern();
    stern(int setN, int setK, int setT, int setq, string setMessage);
    //generate a permutation in cycle notation 
    //note that n is permtuation length
    vector<vector<string> > generatePermutation();
    //generates y and s
    void generatePublicPrivateKey();
    //generate the commitments c_1, c_2, and c_3
    void generateCommitments();
    //applies the permutation omega to a string change
    void runPermutation(string & change);
    //generate challenge (0, 1, 2) to determine what the verification step will entail
    //response (when we are doing digital signatures) is based upon C_H = hash(commitments + message)
    int generateChallenge();
    //converts a given sha256 hash to binary for the purposes of generating the challenge
    string convertHashToBinary(string hash);
    //based on the challenge value (0, 1, or 2) generate a response
    //all of the preceding parameters are pass by reference, sent to the verifier to do the verification
    //note that within the generate response procedure we also call the generate 
    void generateResponse(vector<int> & sendu, vector<vector<string> > & sendomega, vector<vector<int> > & sendDirectSumUS, string & sendOmegaU, string & sendOmegaS, int challengeValue);
    //based on the response step, the signer of the message will sign with CMT||RSP
    //where CMT is the commitments (c1, c2, c3) and RSP is response from generateResponse
    void generateSignature(vector<int> sendu, vector<vector<string> > sendomega, vector<vector<int> > directSumUS, string sendOmegaU, string sendOmegaS);
    //verifies if a signature is valid after a signer generates said signature. returns true if signature is valid
    bool verifySignature();
    //erases contents of commitment information - namely c1, c2, c3, u, oursig, omega, (for the purposes of redoing those steps of the algorithm)
    //note that stern original paper suggests that we run the algorithm 40 times in order to meet a desired level of security (*may want to increase in modern day)
    void clearInformation();
    //based on the need for the stern scheme to be repeated many times in order for it to be secure-give it an integer K and we run it that many times (the signature->verifciation process)
    bool runKTrials(int K);
    //accessors for private key s, public key y, stern signature
    vector<int> getPrivateKey();
    vector<vector<int> > getPublicKey();
    sternSig getOurSig();
    //mutators for private key s, public key y, stern signature
    void setPrivateKey(vector<int> sets);
    void setPublicKey(vector<vector<int> > sety);
    void setOurSig(sternSig setsig);

  private :
    //private key
    vector<int> s;
    //public key
    vector<vector<int> > y; 
    //given a random binary (k, n) code with partiy check matrix H
    //H is common to all users
    vector<vector<int> > H;
    //use of basic matrix operations included from matrixOperations class
    matrixOperations ops;
    //the four parameters for the algorithm
    int N;
    int K;
    int T;
    int q;
    //message to be signed
    string message;
    //omega stores the permutation in cycle notation
    vector<vector<string> > omega;
    //u is randomly generated in the commitment process
    vector<int> u;
    //c1, c2, and c3 are the information for the commitments
    string c1;
    string c2;
    string c3;
    //stores the signature information - according to fiat-shamir scheme this should be CMT||RSP (CMT being commitments, RSP being response)
    sternSig oursig;

};

#endif /* STERN_H */
