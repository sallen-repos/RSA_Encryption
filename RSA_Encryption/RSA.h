#pragma once
#include <vector>
#include "pch.h"
#include <iostream>
#include <math.h> 
#include <chrono>
#include <thread>
#include <string>
#include "XoroShiro.h"
#include  "Primality.h"


struct CDE
{
	
	double privateKey;
	double publicKeyA;
	double publicKeyB;
};

class RSA
{
private:

	Primality primality;
	XoroShiro randGen;
	static uint64_t greatestCommonDiv(uint64_t , uint64_t  );


public:

	std::vector <double> crypt(std::vector <double>, double b, double c);
	void gen(double &privateKey, double &publicKeyA, double &publicKeyB);
	//PublicKey generate(std::u32string message, double &privateKey);

	RSA();
	~RSA();
};

