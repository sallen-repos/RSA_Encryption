#include "pch.h"
#include "XoroShiro.h"
#include <limits.h>
#include <iostream>
#include <bitset>

Splitmix64 splitmix64;

static uint32_t seedValue;

XoroShiro::XoroShiro()
{
}

XoroShiro::~XoroShiro()
{
}

//uses a SplitMix64 PRNG to Generates a seed with 64 bits of state 
void XoroShiro::setSeed(uint32_t input)
{	
	splitmix64.setSeed(input);
	
	setState();
}

uint32_t XoroShiro::getRandOne()
{
	nextState();
	return state.s0;
}

State XoroShiro::getState()
{
	nextState();
	return state;
}
//sets state of each series
void XoroShiro::setState()		
{	
	state.s0 = splitmix64.splitmix();		//is less repetative shortHand for state s(state)
	state.s1 = splitmix64.splitmix();		
	state.s2 = splitmix64.splitmix();
	state.s3 = splitmix64.splitmix();
}
//main xoroshiro** function, XORs
uint32_t XoroShiro::nextState()
{
	//the ** multiplication
	const uint32_t result = rotateLeft(state.s1 * 5, 7) * 9;

	//left shift
	const uint32_t temp = state.s1 << 9;
	//XOR
	state.s2 ^= state.s0;
	state.s3 ^= state.s1;
	state.s1 ^= state.s2;
	state.s0 ^= state.s3;

	state.s2 ^= temp;
	//shift rotate
	state.s3 = rotateLeft(state.s3, 11);

	return result;
}

//shifts and rotates values bits to the left
uint32_t XoroShiro::rotateLeft(uint32_t value, int offset)
{
	return (value << offset) | (value >> (64 - offset));
}
