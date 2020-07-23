#pragma once
#include <stdint.h>
#include <vector>
#include <deque>
#include <algorithm>

class Primality
{
	
const int SIEVE_LIMIT = 65357;

const int PRIMES_SIZE = 6527;

const std::vector <uint16_t> KNOWN_PRIMES = sieveOfAtkin(SIEVE_LIMIT);

private:
	
	uint32_t binarySearch(uint16_t root);
	
	uint32_t rootSearch(uint32_t candidate);		
	
	const std::vector <uint16_t> sieveOfAtkin(const int);

	uint32_t addOneifEven(uint32_t value);

public:
	uint32_t nearestPrime(uint32_t candidate);

	Primality();
	~Primality();
};

