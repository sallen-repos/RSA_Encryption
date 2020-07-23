#pragma once
#include <stdint.h>
#include "Splitmix64.h"

//Using an array for state lead to errors
//So we have a struct instead.
struct State {

	uint32_t s0;
	uint32_t s1;
	uint32_t s2;
	uint32_t s3;
};

struct Seed {
	
	uint32_t seedVal;
	uint32_t result;
};

class XoroShiro
{

private:

	State state;
	Seed seed;
	Splitmix64 splitmix64;

	void setState();

	uint32_t rotateLeft(uint32_t, int);


public:
	XoroShiro();
	~XoroShiro();


	void setSeed(uint32_t);

	uint32_t nextState();
	uint32_t getRandOne();

	State getState();

	//uint32_t splitmix64();

};

