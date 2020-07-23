#include "pch.h"
#include "Primality.h"
#include <iostream>


/*
	Class Generates a sorted vector of known prime using sieveOfAtkin
	Which includes all primes up to 65,536 which is the square root of 2^32

	Since every compound number upto 2^32 must have a prime number at or below 65,536 as a factor,
	We can check any 32Bit integers square roots uing the list of KNOWN_PRIMES
*/


Primality::Primality()
{
}


Primality::~Primality()
{
}


// Returns the nearest prime > our candidate number
uint32_t Primality::nearestPrime(uint32_t candidate) {

	if (candidate <= KNOWN_PRIMES.back()) {// If candidate is < 65357 we simple check against the pre-generated sieve KNOWN_PRIMES 

		addOneifEven(candidate);

		return KNOWN_PRIMES[(binarySearch(candidate))];
	}

	uint32_t squareRoot = addOneifEven(sqrt(candidate)); // If candidate is > 65357 we look for a prime factors in KNOWN_PRIMES

	return rootSearch(squareRoot);

	// Since 65357 the square root of 2^32) all composite numbers below 2^32
	// must have prime factors within the range of our KNOWN_FACTORS
}



// Finds every prime up to and including 65357 (the square root of 2^32)
const std::vector <uint16_t> Primality::sieveOfAtkin(const int LIMIT) {

	//using deque instead of vector to avoid nasty errors with bools and vectors (c++ issues)
	std::deque <bool> sieve;
	sieve.resize(LIMIT);

	std::vector <uint16_t> knownPrimes;
	knownPrimes.reserve(PRIMES_SIZE);
	
	sieve[2] = true;
	sieve[3] = true;
	
	int xSquared = 0;
	int ySquared = 0;
	
	for (int x = 1; x * x < LIMIT; x++) {
		xSquared = x * x;
		for (int y = 1; y * y < LIMIT; y++) {
			
			ySquared = y * y;
			// Main part of Sieve of Atkin 
			int n = (4 * xSquared) + ySquared;
			if (n < LIMIT && (n % 12 == 1 || n % 12 == 5))
				sieve[n] ^= true;

			n = (3 * xSquared) + ySquared;
			if (n < LIMIT && n % 12 == 7)
				sieve[n] ^= true;

			n = (3 * xSquared) - ySquared;
			if (x > y && n < LIMIT && n % 12 == 11)
				sieve[n] ^= true;
		}
	}
	// Declare false positives thus far as false
	for (int i = 5; i * i < LIMIT; i++) {
		if (sieve[i] == true) {
			for (int j = i * i; j < LIMIT; j += i * i) {
				sieve[j] = false;
			}
		}
	}

	int c = 0;
	//add all known primes to knowPrimes (which exists for quickly indexing of all know primes)
	for (int i = 0; i < LIMIT; i++) {
		if (sieve[i] == true) {
			knownPrimes.push_back(i);
		}
	}
	return knownPrimes;
}


uint32_t Primality::addOneifEven(uint32_t value) {

	if ((value & 1) == 0)	//evaluate lowest bit to check if candidate is an odd number and potentially prime
		value++;

	return value;
}



// Searches vector of known primes for values equal to candidate, otherwise a near by prime
uint32_t Primality::binarySearch(uint16_t candidate)
{
	uint32_t length = KNOWN_PRIMES.size() - 1;
	uint32_t right = length;
	uint32_t left = 0;
	uint32_t i;
	while (left + 1 <= length) {
		i = left + (right - left) / 2;

		if (KNOWN_PRIMES[i] <= candidate) {
		
			left = i + 1;										
												
			if (KNOWN_PRIMES[i + 1] >= candidate) {	// If candidate is between or equal to known_Primes[i]	
													// and known_Primes[i + 1] then return know_Primes[i]
				return i;							// return the index > candidate
			}			
		}
		else {		
			right = i - 1;
			if (KNOWN_PRIMES[i - 1] <= candidate) {	// Return index if canditate is between knownPrims[i]
													// and knownPrimes[i - 1]
				return i;
			}	
		}
	}
	return -1;
}

// Calls a binary search upon values incremented from the square root of candidate
uint32_t Primality::rootSearch(uint32_t root) {

	uint_fast32_t plus = root;

	while (plus <= KNOWN_PRIMES.back()) {			//search for prime factors above the squareRoot.
		plus += 2;
		if (binarySearch(plus) != -1)
			return plus;
	}

	uint_fast32_t minus = root;

	while (minus > 0) {						//search for prime factors below the squareRoot.
		minus -= 2;
		if (binarySearch(minus) != -1)
			return minus;
	}
}
