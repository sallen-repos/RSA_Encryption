#include "pch.h"
#include "RSA.h"

RSA::RSA()
{
}

RSA::~RSA()
{
}

// Finds the greates common divisor
uint64_t RSA::greatestCommonDiv(uint64_t encryptionKey, uint64_t  totient) {

	if (totient == 0)
		return encryptionKey;
	else
		return greatestCommonDiv(totient, encryptionKey % totient);
}

void RSA::gen(double &privateKey, double &publicKeyA, double &publicKeyB) {

	int seed = 134256543;
	//seeds randGen, which an instance of the XoroShiro class which is a custom made implementation of the Xoroshiro PRNG
	randGen.setSeed(seed);

	//generate random prime numbers via randGen
	//Nearest prime finds the nearest prime number to the generated random number
	double p = primality.nearestPrime(randGen.getRandOne());
	double q = primality.nearestPrime(randGen.getRandOne());

	//The first part of the public key is created by multiplying two primes
	publicKeyA = p * q;
	
	publicKeyB = 2;
	//A totient is a number less than a given number, and sharing no common factors with it
	//Here we generate a large totient of publicKeyA
	double totient = (p - 1)*(q - 1);
	
	//The toteient can be used to generate the second half of the publicKey
	while (publicKeyB < totient)
	{
		if (greatestCommonDiv(publicKeyB, totient) == 1)
			break;
		else
			publicKeyB++;
	}
	//generates our private key, fmod returns the remainder of a division.
	privateKey = fmod(1 / publicKeyB, totient);

}
/*
	Crypt() decrypts or encrypts our message depending on the parameters passed.
*/

std::vector <double> RSA::crypt(std::vector <double> inputMsg, double keyTwo, double keyOne) {
	//Function decrypts or encryps

	std::vector <double> outputMsg;
	outputMsg.reserve(inputMsg.size());
	for (int_fast16_t i = 0; i < inputMsg.size(); ++i) {
		//returns the remainder of Msg to the power of KeyTwo divided by keyOne 
		outputMsg.push_back(fmod( pow(inputMsg[i], keyTwo) , keyOne));
		
		printf("%c", ((char)outputMsg[i]) + 1);

	}
	

	return outputMsg; 

}
