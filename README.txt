Encrypts input
Using RSA encryption, Coded in C++

Open and Run Using Visual Studio
Simply Type input, and press enter to encrypt!

Architecture
* main() function
* RSA() class generated keys, encrypts and decrypts
* Xoroshiro() A bespoke PRNG called on by RSA to generate a random number
* SplitMix()  A simple PRNG called by  XoroShiro to generate an appropriate seed
* Primality() Called by RSA to generate the nearest prime to the number input

