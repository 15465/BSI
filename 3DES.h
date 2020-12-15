#pragma once
#ifndef _3DES_H_
#define _3DES_H_
// Aleksander Mielczarek
/// This is a file containing 3DES encryption and decryption methods
///
/// This file uses the OpenSSL library and contains a function Test_3DES that runs encryption and decryption functions on files plain.txt, cipher.txt, and deciphered.txt
/// The plain.txt is the data to be encrypted, cipher.txt is the encrypted data, and deciphered.txt is the decrypted data
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <openssl/des.h>
#include <sstream>

using namespace std;


void Test_3DES();

#endif
