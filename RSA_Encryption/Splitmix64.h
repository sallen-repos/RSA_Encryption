#pragma once
#include <stdint.h>
class Splitmix64
{

private:

	uint32_t seedVal;
	uint32_t result;

public:	
	Splitmix64();
	~Splitmix64();


	void setSeed(uint32_t);
	uint32_t splitmix();




};

