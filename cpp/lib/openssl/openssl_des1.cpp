#include <openssl/err.h>
#include <openssl/ssl.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include "openssl/des.h"

using namespace std;

/**
 * using ecb encryption
 * g++ -std=c++11 -Wall openssl_des.cpp -o openssl_des -lcrypto
 */

int formula_encrypt_general(char *data, int data_len, const char *key, char *out_buffer, bool is_encrypt) {
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

string char2int_string(const char *c, int len) {
    ostringstream oss;
    for (int i = 0; i < len; ++i) {
        oss << (static_cast<int>(c[i]) + 128) << "|";
    }
    return oss.str();
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start, end));
    return result;
}

int int2char_string(const std::string& str, char *output) {
    auto lets = split(str, '|');
    int len = 0;
    for (const auto& let : lets) {
        if (let.empty()) continue;
        else {
            output[len++] = static_cast<char>(std::stoi(let) - 128);
        }
    }
    return len;
}

string formula_encrypt(string data, const string& key) {
    char encrypted[4098] = {};
    int len = formula_encrypt_general(data.data(), data.size(), key.data(), encrypted, true);
    return char2int_string(encrypted, len);
}

string formula_decrypt(const string& data, const string& key) {
    char decrypted[4098] = {};
    char encrypted[4098] = {};
    int len = int2char_string(data, encrypted);
    formula_encrypt_general(encrypted, len, key.data(), decrypted, false);
    return string(decrypted);
}

int main() {
    string plain_text = "In probability theory, the normal (or Gaussian or Gauss or Laplace–Gauss) |";

    std::cout << "plain text len: " << plain_text.size() << std::endl;

    string des_key = "12345";
    string encrypted = formula_encrypt(plain_text, des_key);
    std::cout << "encrypted: " << encrypted << std::endl;
    string decrypted = formula_decrypt(encrypted, des_key);
    std::cout << "decrypted: " << decrypted << std::endl;
}
