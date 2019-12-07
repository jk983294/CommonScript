#include <openssl/err.h>
#include <openssl/ssl.h>
#include <cstring>
#include <iostream>
#include <vector>
#include "openssl/des.h"

using namespace std;

/**
 * using ecb encryption
 * g++ -std=c++11 -Wall openssl_des.cpp -o openssl_des -lcrypto
 */

int des_encrypt_general(char *data, int data_len, const char *key, char *out_buffer, bool is_encrypt) {
    size_t key_len = strlen(key);
    if (data_len == 0 || key_len == 0) return -1;
    int encrypt_length = 0;

    DES_cblock key_encrypt;
    memset(key_encrypt, 0, 8);

    if (key_len <= 8)
        memcpy(key_encrypt, key, key_len);
    else
        memcpy(key_encrypt, key, 8);

    DES_key_schedule key_schedule;
    DES_set_key_unchecked(&key_encrypt, &key_schedule);

    // encrypt every 8 byte
    const_DES_cblock input_text;
    DES_cblock output_text;

    int idx = 0;
    for (; idx < data_len / 8; idx++) {
        memcpy(input_text, data + idx * 8, 8);
        if (is_encrypt)
            DES_ecb_encrypt(&input_text, &output_text, &key_schedule, DES_ENCRYPT);
        else
            DES_ecb_encrypt(&input_text, &output_text, &key_schedule, DES_DECRYPT);
        memcpy(out_buffer + idx * 8, output_text, 8);
        encrypt_length += 8;
    }

    if (data_len % 8 != 0) {
        memset(input_text, 0, 8);
        memcpy(input_text, data + idx * 8, data_len % 8);
        if (is_encrypt)
            DES_ecb_encrypt(&input_text, &output_text, &key_schedule, DES_ENCRYPT);
        else
            DES_ecb_encrypt(&input_text, &output_text, &key_schedule, DES_DECRYPT);
        memcpy(out_buffer + idx * 8, output_text, 8);
        encrypt_length += 8;
    }
    return encrypt_length;
}

int des_encrypt(char *data, int data_len, const char *key, char *encrypted) {
    return des_encrypt_general(data, data_len, key, encrypted, true);
}

int des_decrypt(char *data, int data_len, const char *key, char *decrypted) {
    return des_encrypt_general(data, data_len, key, decrypted, false);
}

int main() {
    char plain_text[256] =
        "In probability theory, the normal (or Gaussian or Gauss or Laplace–Gauss) distribution is a very common "
        "continuous probability distribution";

    std::cout << "plain text len: " << strlen(plain_text) << std::endl;
    char encrypted[4098] = {};
    char decrypted[4098] = {};
    char des_key[] = "12345";
    int len = des_encrypt(plain_text, strlen(plain_text), des_key, encrypted);
    std::cout << "encrypted: " << encrypted << std::endl;
    std::cout << "encrypted len: " << len << " actual len: " << strlen(encrypted) << std::endl;
    len = des_decrypt(encrypted, len, des_key, decrypted);
    std::cout << "decrypted: " << decrypted << std::endl;
    std::cout << "decrypted len: " << len << " actual len: " << strlen(decrypted) << std::endl;
}
