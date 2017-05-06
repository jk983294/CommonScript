#include <stdio.h>
#include <string.h>

/**
void * memset(void* buffer, int c, int count) {
    char * buffer_p=(char*)buffer;
    while(count-->0)
        *buffer_p++=(char)c;
    return buffer;
}
*/

// do not memset object contians pointer, it will cause memory leak
struct Parameters {
    int x;
    int* p_x;
};

// do not memset object contains virtual table
class BaseParameters {
public:
    virtual void reset() {}
};

class MyParameters : public BaseParameters {
public:
    int data[3];
    int buf[3];
};

int main() {
    char cdata[10];
    memset(cdata, 1, sizeof(cdata));  // right
    memset(cdata, 0, sizeof(cdata));  // right

    int data[10];
    memset(data, 0, sizeof(data));   // right
    memset(data, -1, sizeof(data));  // right
    printf("%d\n", data[0]);
    memset(data, 1, sizeof(data));  // wrong, data[x] would be 0x0101 instead of 1, because byte wise memset
    printf("%d\n", data[0]);

    Parameters par;
    par.p_x = new int[10];
    memset(&par, 0, sizeof(par));  // wrong, memory leak because par.p_x not released

    MyParameters my_pars;
    memset(&my_pars, 0, sizeof(my_pars));  // wrong, virtual table damaged
    BaseParameters* pars = &my_pars;
    return 0;
}
