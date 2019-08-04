#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/**
 * g++ -std=c++11 -Wall openssl_base64.cpp -o openssl_base64 -lcrypto
 */

bool with_new_line = false;

char* Base64Encode(const char* input, size_t length);
char* Base64Decode(char* input, size_t length);

int main(int argc, char* argv[]) {
    string enc_input =
        "The normal distribution is useful because of the central limit theorem. In its most general form, under some "
        "conditions (which include finite variance), it states that averages of samples of observations of random "
        "variables independently drawn from independent distributions converge in distribution to the normal, that is, "
        "they become normally distributed when the number of observations is sufficiently large.";

    cout << "To be encoded:" << endl << "~" << enc_input << "~" << endl << endl;

    char* enc_output = Base64Encode(enc_input.c_str(), enc_input.length());
    cout << "Base64 Encoded:" << endl << "~" << enc_output << "~" << endl << endl;

    string dec_input = enc_output;
    char* dec_output = Base64Decode((char*)dec_input.c_str(), dec_input.length());
    cout << "Base64 Decoded:" << endl << "~" << dec_output << "~" << endl << endl;

    delete[] enc_output;
    delete[] dec_output;
}

char* Base64Encode(const char* input, size_t length) {
    BIO* pBio = nullptr;
    BIO* b64 = nullptr;
    BUF_MEM* pBuf = nullptr;

    b64 = BIO_new(BIO_f_base64());
    if (!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    pBio = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, pBio);
    BIO_write(b64, input, static_cast<int>(length));
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &pBuf);

    char* buff = new char[pBuf->length + 1];
    memcpy(buff, pBuf->data, pBuf->length);
    buff[pBuf->length] = '\0';
    BIO_free_all(b64);
    return buff;
}

char* Base64Decode(char* input, size_t length) {
    BIO* b64 = nullptr;
    BIO* pBio = nullptr;
    char* buffer = new char[length];
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    if (!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    pBio = BIO_new_mem_buf(input, static_cast<int>(length));
    pBio = BIO_push(b64, pBio);
    BIO_read(pBio, buffer, static_cast<int>(length));
    BIO_free_all(pBio);
    return buffer;
}
