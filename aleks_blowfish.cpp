//Aleksander Mielczarek
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <openssl/blowfish.h>
#include <sstream>

using namespace std;

/* Triple DES key for Encryption and Decryption */

string encrypt_BF(string input_file, string output_file, BF_KEY* key) {
    string cipher;
    unsigned char plaintext[8];
    unsigned char cyphertext[8];
    ifstream ptxt;
    ofstream ctxt;
    ptxt.open(input_file);
    ctxt.open(output_file);
    string data;
    stringstream sbuffer;

    ptxt.open(input_file);
    sbuffer << ptxt.rdbuf();
    data = sbuffer.str();
    ptxt.close();

    BF_set_key(key, data.size(), (unsigned char*)data.c_str());

    for (int j = 0; j < data.size();) {
        //divide data into 8 char sets
        for (int i = 0; i < 8; i++) {
            if (j < data.size()) {
                plaintext[i] = data[j];
                j++;
            }
            else {
                plaintext[i] = 0;
                j++;
            }

        }

        system("pause");
        BF_ecb_encrypt(plaintext, cyphertext, key, BF_ENCRYPT);
        system("pause");
        for (int i = 0; i < sizeof(cyphertext); i++) {
            cipher.push_back(cyphertext[i]);
            //cout << output[i];
        }
    }
}

string decrpyt_BF(string input_file, string output_file, BF_KEY* key) {
    string deciphered;
    unsigned char plaintext[8];
    unsigned char cyphertext[8];
    ifstream ptxt;
    ofstream ctxt;
    ptxt.open(input_file);
    ctxt.open(output_file);
    string data;
    stringstream sbuffer;

    ptxt.open(input_file);
    sbuffer << ptxt.rdbuf();
    data = sbuffer.str();
    ptxt.close();
    system("pause");
    for (int j = 0; j < data.size();) {
        //divide data into 8 char sets
        for (int i = 0; i < 8; i++) {
            if (j < data.size()) {
                plaintext[i] = data[j];
                j++;
            }
            else {
                plaintext[i] = NULL;
                j++;
            }

        }

        system("pause");
        BF_ecb_encrypt(plaintext, cyphertext, key, BF_DECRYPT);
        for (int i = 0; i < sizeof(cyphertext); i++) {
            deciphered.push_back(cyphertext[i]);
            //cout << output[i];
        }
    }
    if (ctxt.is_open())
    {
        ctxt << deciphered;
        ctxt.close();
    }
    else
        cout << "Unable to open file\n";
    return deciphered;
}

int main() {
    BF_KEY* key = new BF_KEY;
    BF_set_key(key, 256, (const unsigned char*)"TestKey");
    cout << "Encrypted data: ";
    cout << encrypt_BF("plain.txt", "cipher.txt", key) << "\n";
    cout << "Decrypted data: ";
    cout << decrpyt_BF("cipher.txt", "deciphered.txt", key) << "\n";
    return 0;
}