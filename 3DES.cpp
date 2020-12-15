//Aleksander Mielczarek
///3DES to algorytm stosuj¹cy algorytm DES trzykrotnie do ka¿dego bloku danych, u¿ywaj¹c trzech kluczy
///
///DES to block cipher, bior¹cy ci¹g znaków o sta³ej d³ugoœci i transformuje go na inny ci¹g znaków o tej samej d³ugoœci za pomoc¹ klucza.

#include <stdio.h>
#include "3DES.h"

DES_cblock Key1 = { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 };
DES_cblock Key2 = { 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 };
DES_cblock Key3 = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
DES_key_schedule SchKey1, SchKey2, SchKey3;

//encription algorithm
string Encrypt_3DES(string input_file, string output_file) {
    string cipher; //string of encrypted data

    ifstream ptxt; //input file
    ofstream ctxt; // output file
    ptxt.open(input_file); // open input file
    ctxt.open(output_file); //open output file
    string data; //string of input file
    stringstream sbuffer; //stringstream for conversion of file to string
    DES_cblock buffer; // 8 char buffer for encryption function

    ptxt.open(input_file);
    sbuffer << ptxt.rdbuf();
    data = sbuffer.str();
    ptxt.close();

    //divide data into 8 char sets
    for (int j = 0; j < data.size();) {

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
        }
    }
    /* Save encrypted data to file */
    if (ctxt.is_open())
    {
        ctxt << cipher;
        ctxt.close();
    }
    else
        cout << "Unable to open file\n";
    return cipher;
}
//decryption algorithm
string Decrypt_3DES(string input_file, string output_file) {
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

void Test_3DES() {
    cout << "Encrypted data: ";
    cout << Encrypt_3DES("plain.txt", "cipher.txt") << "\n";
    cout << "Decrypted data: ";
    cout << Decrypt_3DES("cipher.txt", "deciphered.txt") << "\n";;
}