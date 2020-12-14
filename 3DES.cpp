#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <openssl/des.h>
#include <sstream>

using namespace std;

/* Triple DES key for Encryption and Decryption */
DES_cblock Key1 = { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 };
DES_cblock Key2 = { 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 };
DES_cblock Key3 = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
DES_key_schedule SchKey1, SchKey2, SchKey3;

/* Print Encrypted and Decrypted data packets */
void print_data(const char* tittle, const void* data, int len);

string encrypt(string input_file, string output_file) {
    string cipher;

    ifstream ptxt;
    ofstream ctxt;
    ptxt.open(input_file);
    ctxt.open(output_file);
    string data;
    stringstream sbuffer;
    DES_cblock buffer;

    ptxt.open(input_file);
    sbuffer << ptxt.rdbuf();
    data = sbuffer.str();
    ptxt.close();

    
    for (int j = 0; j < data.size();) {
        //divide data into 8 char sets
        for (int i = 0; i < 8; i++) {
            if (j < data.size()) {
                buffer[i] = data[j];
                j++;
            }
            else {
                buffer[i] = NULL;
                j++;
            }
                
        }

        //encrpyt
        DES_cblock output;
        /* Triple-DES ECB Encryption */
        DES_ecb3_encrypt(&buffer, &output, &SchKey1, &SchKey2, &SchKey3, DES_ENCRYPT);
        for (int i = 0; i < sizeof(output); i++) {
            cipher.push_back(output[i]);
            //cout << output[i];
        }
        /*
        DES_cblock decipher;
        DES_ecb3_encrypt(&output, &decipher, &SchKey1, &SchKey2, &SchKey3, DES_ENCRYPT);
        for (int i = 0; i < sizeof(decipher); i++)
            cout << decipher[i];*/
    }
    if (ctxt.is_open())
    {
        ctxt << cipher;
        ctxt.close();
    }
    else
        cout << "Unable to open file\n";
    return cipher;
}

string decrpyt(string input_file, string output_file) {
    string deciphered;

    ifstream ptxt;
    ofstream ctxt;
    ptxt.open(input_file);
    ctxt.open(output_file);
    string data;
    stringstream sbuffer;
    DES_cblock buffer;
    
    ptxt.open(input_file);
    sbuffer << ptxt.rdbuf();
    data = sbuffer.str();
    ptxt.close();

    //fix_newlines(data);
    //cout << "\n kawabunga: \n";
    //cout << data;

    for (int j = 0; j < data.size();) {
        //divide data into 8 char sets
        for (int i = 0; i < 8; i++) {
            if (j < data.size()) {
                buffer[i] = data[j];
                j++;
            }
            else {
                buffer[i] = NULL;
                j++;
            }
                
        }
        //cout << data;
        //encrpyt
        DES_cblock output;
        /* Triple-DES ECB Encryption */
        DES_ecb3_encrypt(&buffer, &output, &SchKey1, &SchKey2, &SchKey3, DES_DECRYPT);
        for (int i = 0; i < sizeof(output); i++)
            deciphered += output[i];
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

int work() {
    cout << "Encrypted data: ";
    cout << encrypt("plain.txt", "cipher.txt") << "\n";
    cout << "Decrypted data: ";
    cout << decrpyt("cipher.txt", "deciphered.txt") << "\n";;
}

void print_data(const char* tittle, const void* data, int len)
{
    printf("%s : ", tittle);
    const unsigned char* p = (const unsigned char*)data;
    int i = 0;

    for (; i < len; ++i)
        printf("%02X ", *p++);

    printf("\n");
}