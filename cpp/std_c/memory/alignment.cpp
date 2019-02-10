#include <iostream>
#include <malloc.h>

using namespace std;

/**
 * The address returned by malloc or realloc in GNU systems always aligned to 16 on 64-bit systems
 */

int main()
{
    void* p1 = memalign(64, 32);    // align to 64, size is 32
    uint64_t addr = reinterpret_cast<uint64_t>(p1);
    cout << (addr % 64) << " " << (addr % 128) << " " << addr << endl;
    free(p1);

    posix_memalign(&p1, 128, 32);   // align to 64, size is 32
    addr = reinterpret_cast<uint64_t>(p1);
    cout << (addr % 64) << " " << (addr % 128) << " " << addr << endl;
    free(p1);

    /**
     * using memalign and passing the page size as the value of the second argument.
     * like memalign (getpagesize(), size);
     */
    p1 = valloc(32);    // align to page size, size is 32
    cout << (addr % 64) << " " << (addr % 128) << " " << addr << endl;
    free(p1);
    return 0;
}
