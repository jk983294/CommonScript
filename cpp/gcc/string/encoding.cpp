#include <iconv.h>
#include <cstring>
#include <iostream>

using namespace std;

inline int code_convert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen, char *outbuf,
                        size_t outlen) {
    iconv_t cd;
    char **pin = &inbuf;
    char **pout = &outbuf;

    cd = iconv_open(to_charset, from_charset);
    if (cd == 0) return -1;
    memset(outbuf, 0, outlen);
    if ((int)iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
    iconv_close(cd);
    **pout = '\0';
    return 0;
}

inline string gbk2utf8(const char *error_msg) {
    char origin[128], converted[128];
    strcpy(origin, error_msg);
    code_convert((char *)"gbk", (char *)"utf-8", origin, strlen(error_msg), converted, 128);
    return string(converted);
}

inline string utf82gbk(const char *error_msg) {
    char origin[128], converted[128];
    strcpy(origin, error_msg);
    code_convert((char *)"utf-8", (char *)"gbk", origin, strlen(error_msg), converted, 128);
    return string(converted);
}

int main(int argc, char *argv[]) {
    string msg1{"文件"};
    string msg2 = utf82gbk(msg1.c_str());
    string msg3 = gbk2utf8(msg2.c_str());
    cout << msg1 << " " << msg2 << " " << msg3 << endl;

    return 0;
}
