// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "XoroShiro.h"
#include "Primality.h"
#include "RSA.h"
#include <stdlib.h>
#include <string>  

/*
* This console application encrypts and decrypts enterd text
* 
* The application includes a custom XoroShiro psudo-random number generator
*
*/
int main() {

	RSA encryptRES;		

	// Get user input
	std::string input;
	std::cout << "Enter message\n";	
	std::getline(std::cin, input);
	// Place message in vector of doubles
	std::vector <double> Message(input.begin(), input.end());	
	std::vector <double> encryptedMsg;
	std::vector <double> decryptedMsg;
	
	double privateKey;
	double publicKeyA;
	double publicKeyB;
	char c = 'c';
			
	std::cout << "\nEncrypted Message " <<  input;
	// Generate public and private keys
	encryptRES.gen(privateKey, publicKeyA, publicKeyB);

	// Decrypt the message
	std::cout << "\nEncrypted Message = ";	
	encryptedMsg = encryptRES.crypt(Message, publicKeyB, publicKeyA);	

	// Decrypt the message
	std::cout << "\nDecrypted Message = ";
	decryptedMsg = encryptRES.crypt(encryptedMsg, privateKey, publicKeyA);
	std::cout << "\n";

	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//, 1. Use the Solution Explorer window to add/manage files
//, 2. Use the Team Explorer window to connect to source control
//, 3. Use the Output window to see build output and other messages
//, 4. Use the Error List window to view errors
//, 5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//, 6. In the future, to open this project again, go to File > Open > Project and select the .sln file
