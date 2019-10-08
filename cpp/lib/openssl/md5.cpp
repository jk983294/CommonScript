#include <openssl/md5.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/**
 * g++ -std=c++11 -Wall -O3 -lcrypto md5.cpp -o md5
 */

int main(int argc, char **argv) {
    const char *data = "123";
    unsigned char md[16];
    int i;
    char tmp[3] = {'\0'}, buf[33] = {'\0'};
    MD5(reinterpret_cast<const unsigned char *>(data), strlen(data), md);
    for (i = 0; i < 16; i++) {
        sprintf(tmp, "%2.2x", md[i]);
        strcat(buf, tmp);
    }
    printf("%s\n", buf);

    memset(buf, 0, sizeof(buf));
    for (i = 0; i < 16; i++) {
        sprintf(tmp, "%2.2X", md[i]);
        strcat(buf, tmp);
    }
    printf("%s\n", buf);
    return 0;
}
